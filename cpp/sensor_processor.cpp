#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

struct SensorNode {
    int nodeId;
    int moisture;
    int temperature;
    int battery;
};

string getStatus(int moisture) {
    if (moisture < 40)
        return "DRY";
    else if (moisture <= 60)
        return "NORMAL";
    else
        return "WET";
}

string getRecommendation(int moisture) {
    if (moisture < 40)
        return "IRRIGATION RECOMMENDED";
    else if (moisture > 60)
        return "NO ACTION";
    else
        return "NO ACTION";
}

int main() {

    vector<SensorNode> nodes = {
        {1, 25, 25, 100},
        {2, 45, 26, 97},
        {3, 50, 27, 94},
        {4, 55, 28, 91},
        {5, 60, 29, 88},
        {6, 65, 30, 85},
        {7, 70, 31, 82},
        {8, 35, 26, 90}
    };

    cout << "SMART AGRICULTURAL SENSOR PROCESSOR\n";
    cout << "====================================\n\n";

    for (const auto& node : nodes) {

        string status = getStatus(node.moisture);
        string recommendation = getRecommendation(node.moisture);

        cout << "Node ID: " << node.nodeId << endl;
        cout << "Moisture: " << node.moisture << "%" << endl;
        cout << "Temperature: " << node.temperature << " C" << endl;
        cout << "Battery: " << node.battery << "%" << endl;
        cout << "Status: " << status << endl;
        cout << "Recommendation: " << recommendation << endl;
        cout << "------------------------------------\n";
    }

    return 0;
}
