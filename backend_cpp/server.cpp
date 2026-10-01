#include <arpa/inet.h>
#include <ctime>
#include <fstream>
#include <iostream>
#include <netinet/in.h>
#include <sstream>
#include <string>
#include <thread>
#include <unistd.h>
#include <vector>
#include <sqlite3.h>

using namespace std;

struct SensorNode {
    int node_id;
    int moisture;
    int temperature;
    int battery;
    string status;
    string recommendation;
};

vector<SensorNode> sensor_data = {
    {1, 25, 25, 100, "DRY", "WATERING RECOMMENDED"},
    {2, 45, 26, 97, "NORMAL", "NO ACTION"},
    {3, 50, 27, 94, "NORMAL", "NO ACTION"},
    {4, 55, 28, 91, "NORMAL", "NO ACTION"},
    {5, 65, 29, 88, "WET", "NO ACTION"},
    {6, 35, 26, 85, "DRY", "WATERING RECOMMENDED"},
    {7, 70, 30, 82, "WET", "NO ACTION"},
    {8, 48, 27, 79, "NORMAL", "NO ACTION"}
};

const string DATABASE = "backend/sensor_data.db";
const int PORT = 5000;

// ------------------------------------------------------------
// Utility: escape text for JSON
// ------------------------------------------------------------
string jsonEscape(const string& value) {
    string result;

    for (char c : value) {
        if (c == '"')
            result += "\\\"";
        else if (c == '\\')
            result += "\\\\";
        else if (c == '\n')
            result += "\\n";
        else
            result += c;
    }

    return result;
}

// ------------------------------------------------------------
// Convert sensor node to JSON
// ------------------------------------------------------------
string nodeToJson(const SensorNode& node) {
    stringstream ss;

    ss << "{"
       << "\"node_id\":" << node.node_id << ","
       << "\"moisture\":" << node.moisture << ","
       << "\"temperature\":" << node.temperature << ","
       << "\"battery\":" << node.battery << ","
       << "\"status\":\"" << jsonEscape(node.status) << "\","
       << "\"recommendation\":\""
       << jsonEscape(node.recommendation) << "\""
       << "}";

    return ss.str();
}

// ------------------------------------------------------------
// Get all nodes
// ------------------------------------------------------------
string getNodesJson() {
    stringstream ss;

    ss << "[";

    for (size_t i = 0; i < sensor_data.size(); ++i) {
        if (i > 0)
            ss << ",";

        ss << nodeToJson(sensor_data[i]);
    }

    ss << "]";

    return ss.str();
}

// ------------------------------------------------------------
// Get analytics
// ------------------------------------------------------------
string getAnalyticsJson() {
    int total = sensor_data.size();

    double moisture = 0;
    double temperature = 0;
    double battery = 0;

    int dry = 0;
    int normal = 0;
    int wet = 0;

    for (const auto& node : sensor_data) {
        moisture += node.moisture;
        temperature += node.temperature;
        battery += node.battery;

        if (node.status == "DRY")
            dry++;
        else if (node.status == "NORMAL")
            normal++;
        else if (node.status == "WET")
            wet++;
    }

    if (total > 0) {
        moisture /= total;
        temperature /= total;
        battery /= total;
    }

    stringstream ss;

    ss << "{"
       << "\"total_nodes\":" << total << ","
       << "\"average_moisture\":" << moisture << ","
       << "\"average_temperature\":" << temperature << ","
       << "\"average_battery\":" << battery << ","
       << "\"dry_nodes\":" << dry << ","
       << "\"normal_nodes\":" << normal << ","
       << "\"wet_nodes\":" << wet
       << "}";

    return ss.str();
}

// ------------------------------------------------------------
// Get a single node
// ------------------------------------------------------------
string getNodeJson(int node_id) {
    for (const auto& node : sensor_data) {
        if (node.node_id == node_id)
            return nodeToJson(node);
    }

    return "";
}

// ------------------------------------------------------------
// Database initialization
// ------------------------------------------------------------
void initializeDatabase() {
    sqlite3* db = nullptr;

    if (sqlite3_open(DATABASE.c_str(), &db) != SQLITE_OK) {
        cerr << "Could not open database.\n";
        return;
    }

    const char* sql =
        "CREATE TABLE IF NOT EXISTS sensor_logs ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "timestamp TEXT NOT NULL,"
        "node_id INTEGER NOT NULL,"
        "moisture INTEGER NOT NULL,"
        "temperature INTEGER NOT NULL,"
        "battery INTEGER NOT NULL,"
        "status TEXT NOT NULL,"
        "recommendation TEXT NOT NULL"
        ");";

    char* error = nullptr;

    if (sqlite3_exec(db, sql, nullptr, nullptr, &error) != SQLITE_OK) {
        cerr << "Database error: " << error << endl;
        sqlite3_free(error);
    }

    sqlite3_close(db);
}

// ------------------------------------------------------------
// Store sensor readings
// ------------------------------------------------------------
void logSensorData() {
    sqlite3* db = nullptr;

    if (sqlite3_open(DATABASE.c_str(), &db) != SQLITE_OK)
        return;

    string sql =
        "INSERT INTO sensor_logs "
        "(timestamp,node_id,moisture,temperature,battery,status,recommendation) "
        "VALUES (datetime('now'),?,?,?,?,?,?);";

    sqlite3_stmt* stmt = nullptr;

    for (const auto& node : sensor_data) {

        if (sqlite3_prepare_v2(
                db,
                sql.c_str(),
                -1,
                &stmt,
                nullptr) != SQLITE_OK) {
            continue;
        }

        sqlite3_bind_int(stmt, 1, node.node_id);
        sqlite3_bind_int(stmt, 2, node.moisture);
        sqlite3_bind_int(stmt, 3, node.temperature);
        sqlite3_bind_int(stmt, 4, node.battery);
        sqlite3_bind_text(
            stmt,
            5,
            node.status.c_str(),
            -1,
            SQLITE_TRANSIENT
        );
        sqlite3_bind_text(
            stmt,
            6,
            node.recommendation.c_str(),
            -1,
            SQLITE_TRANSIENT
        );

        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }

    sqlite3_close(db);
}

// ------------------------------------------------------------
// Background logging
// ------------------------------------------------------------
void loggingLoop() {
    while (true) {
        logSensorData();

        // Log every 5 minutes
        this_thread::sleep_for(chrono::seconds(300));
    }
}

// ------------------------------------------------------------
// Read dashboard HTML
// ------------------------------------------------------------
string readDashboard() {
    ifstream file("backend_cpp/index.html");

    if (!file.is_open())
        return "<h1>Dashboard file not found</h1>";

    stringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}

// ------------------------------------------------------------
// HTTP response
// ------------------------------------------------------------
void sendResponse(
    int client,
    const string& status,
    const string& contentType,
    const string& body
) {
    stringstream response;

    response << "HTTP/1.1 " << status << "\r\n"
             << "Content-Type: " << contentType << "\r\n"
             << "Content-Length: " << body.size() << "\r\n"
             << "Access-Control-Allow-Origin: *\r\n"
             << "Connection: close\r\n"
             << "\r\n"
             << body;

    string output = response.str();

    send(
        client,
        output.c_str(),
        output.size(),
        0
    );
}

// ------------------------------------------------------------
// HTTP request handler
// ------------------------------------------------------------
void handleClient(int client) {

    char buffer[8192] = {0};

    int received = recv(
        client,
        buffer,
        sizeof(buffer) - 1,
        0
    );

    if (received <= 0) {
        close(client);
        return;
    }

    string request(buffer);

    string method;
    string path;

    stringstream requestStream(request);
    requestStream >> method >> path;

    cout << "[HTTP] " << method << " " << path << endl;

    // Dashboard
    if (path == "/" || path == "/index.html") {

        string html = readDashboard();

        sendResponse(
            client,
            "200 OK",
            "text/html; charset=UTF-8",
            html
        );
    }

    // Nodes
    else if (path == "/api/nodes") {

        sendResponse(
            client,
            "200 OK",
            "application/json",
            getNodesJson()
        );
    }

    // Analytics
    else if (path == "/api/analytics") {

        sendResponse(
            client,
            "200 OK",
            "application/json",
            getAnalyticsJson()
        );
    }

    // History
    else if (path == "/api/history") {

        sqlite3* db = nullptr;

        if (sqlite3_open(DATABASE.c_str(), &db) != SQLITE_OK) {

            sendResponse(
                client,
                "500 Internal Server Error",
                "application/json",
                "{\"error\":\"Database error\"}"
            );

        } else {

            const char* sql =
                "SELECT timestamp,node_id,moisture,"
                "temperature,battery,status,recommendation "
                "FROM sensor_logs "
                "ORDER BY id DESC LIMIT 50;";

            sqlite3_stmt* stmt = nullptr;

            stringstream json;
            json << "[";

            bool first = true;

            if (sqlite3_prepare_v2(
                    db,
                    sql,
                    -1,
                    &stmt,
                    nullptr
                ) == SQLITE_OK) {

                while (sqlite3_step(stmt) == SQLITE_ROW) {

                    if (!first)
                        json << ",";

                    first = false;

                    json << "{"
                         << "\"timestamp\":\""
                         << sqlite3_column_text(stmt, 0)
                         << "\","
                         << "\"node_id\":"
                         << sqlite3_column_int(stmt, 1)
                         << ","
                         << "\"moisture\":"
                         << sqlite3_column_int(stmt, 2)
                         << ","
                         << "\"temperature\":"
                         << sqlite3_column_int(stmt, 3)
                         << ","
                         << "\"battery\":"
                         << sqlite3_column_int(stmt, 4)
                         << ","
                         << "\"status\":\""
                         << sqlite3_column_text(stmt, 5)
                         << "\","
                         << "\"recommendation\":\""
                         << sqlite3_column_text(stmt, 6)
                         << "\""
                         << "}";
                }

                sqlite3_finalize(stmt);
            }

            json << "]";

            sqlite3_close(db);

            sendResponse(
                client,
                "200 OK",
                "application/json",
                json.str()
            );
        }
    }

    // Single node
    else if (path.rfind("/api/nodes/", 0) == 0) {

        string idText = path.substr(
            string("/api/nodes/").length()
        );

        int node_id = stoi(idText);

        string result = getNodeJson(node_id);

        if (result.empty()) {

            sendResponse(
                client,
                "404 Not Found",
                "application/json",
                "{\"error\":\"Node not found\"}"
            );

        } else {

            sendResponse(
                client,
                "200 OK",
                "application/json",
                result
            );
        }
    }

    // Unknown endpoint
    else {

        sendResponse(
            client,
            "404 Not Found",
            "application/json",
            "{\"error\":\"Not found\"}"
        );
    }

    close(client);
}

// ------------------------------------------------------------
// Main HTTP server
// ------------------------------------------------------------
int main() {

    cout << "========================================\n";
    cout << " Smart Agricultural Soil-Moisture Gateway\n";
    cout << " C++ Backend Server\n";
    cout << "========================================\n";

    initializeDatabase();

    thread loggingThread(loggingLoop);
    loggingThread.detach();

    int serverSocket = socket(
        AF_INET,
        SOCK_STREAM,
        0
    );

    if (serverSocket < 0) {
        cerr << "Failed to create socket.\n";
        return 1;
    }

    int option = 1;

    setsockopt(
        serverSocket,
        SOL_SOCKET,
        SO_REUSEADDR,
        &option,
        sizeof(option)
    );

    sockaddr_in serverAddress{};

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(PORT);

    if (bind(
            serverSocket,
            (sockaddr*)&serverAddress,
            sizeof(serverAddress)
        ) < 0) {

        cerr << "Failed to bind port " << PORT << ".\n";
        close(serverSocket);
        return 1;
    }

    if (listen(serverSocket, 10) < 0) {

        cerr << "Failed to listen.\n";
        close(serverSocket);
        return 1;
    }

    cout << "C++ backend started successfully.\n";
    cout << "Server: http://127.0.0.1:" << PORT << "\n";
    cout << "Dashboard: http://127.0.0.1:" << PORT << "/\n";
    cout << "Press Ctrl+C to stop.\n\n";

    while (true) {

        sockaddr_in clientAddress{};
        socklen_t clientLength =
            sizeof(clientAddress);

        int client = accept(
            serverSocket,
            (sockaddr*)&clientAddress,
            &clientLength
        );

        if (client < 0)
            continue;

        thread clientThread(
            handleClient,
            client
        );

        clientThread.detach();
    }

    close(serverSocket);

    return 0;
}
