from flask import Flask, jsonify,render_template
from datetime import datetime
import sqlite3
import time
import threading
import os

app = Flask(__name__)

sensor_data = [
    {
        "node_id": 1,
        "moisture": 25,
        "temperature": 25,
        "battery": 100,
        "status": "DRY",
        "recommendation": "WATERING RECOMMENDED"
    },
    {
        "node_id": 2,
        "moisture": 45,
        "temperature": 26,
        "battery": 97,
        "status": "NORMAL",
        "recommendation": "NO ACTION"
    },
    {
        "node_id": 3,
        "moisture": 50,
        "temperature": 27,
        "battery": 94,
        "status": "NORMAL",
        "recommendation": "NO ACTION"
    },
    {
        "node_id": 4,
        "moisture": 55,
        "temperature": 28,
        "battery": 91,
        "status": "NORMAL",
        "recommendation": "NO ACTION"
    },
    {
        "node_id": 5,
        "moisture": 60,
        "temperature": 29,
        "battery": 88,
        "status": "NORMAL",
        "recommendation": "NO ACTION"
    },
    {
        "node_id": 6,
        "moisture": 65,
        "temperature": 30,
        "battery": 85,
        "status": "WET",
        "recommendation": "NO ACTION"
    },
    {
        "node_id": 7,
        "moisture": 70,
        "temperature": 31,
        "battery": 82,
        "status": "WET",
        "recommendation": "NO ACTION"
    },
    {
        "node_id": 8,
        "moisture": 75,
        "temperature": 32,
        "battery": 79,
        "status": "WET",
        "recommendation": "NO ACTION"
    }
]
def log_sensor_data():
    connection = sqlite3.connect("sensor_data.db")
    cursor = connection.cursor()

    timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")

    for node in sensor_data:
        cursor.execute("""
            INSERT INTO sensor_logs
            (timestamp, node_id, moisture, temperature, battery, status, recommendation)
            VALUES (?, ?, ?, ?, ?, ?, ?)
        """, (
            timestamp,
            node["node_id"],
            node["moisture"],
            node["temperature"],
            node["battery"],
            node["status"],
            node["recommendation"]
        ))

    connection.commit()
    connection.close()

def get_analytics():
    total = len(sensor_data)

    average_moisture = sum(node["moisture"] for node in sensor_data) / total
    average_temperature = sum(node["temperature"] for node in sensor_data) / total
    average_battery = sum(node["battery"] for node in sensor_data) / total

    dry_nodes = sum(1 for node in sensor_data if node["status"] == "DRY")
    normal_nodes = sum(1 for node in sensor_data if node["status"] == "NORMAL")
    wet_nodes = sum(1 for node in sensor_data if node["status"] == "WET")

    return {
        "total_nodes": total,
        "average_moisture": round(average_moisture, 2),
        "average_temperature": round(average_temperature, 2),
        "average_battery": round(average_battery, 2),
        "dry_nodes": dry_nodes,
        "normal_nodes": normal_nodes,
        "wet_nodes": wet_nodes
    }
@app.route("/api/analytics")
def analytics():
    return jsonify(get_analytics())

@app.route("/api/history")
def history():
    connection = sqlite3.connect("sensor_data.db")
    cursor = connection.cursor()

    cursor.execute("""
        SELECT timestamp, node_id, moisture, temperature,
               battery, status, recommendation
        FROM sensor_logs
        ORDER BY id DESC
        LIMIT 50
    """)

    rows = cursor.fetchall()
    connection.close()

    history_data = []

    for row in rows:
        history_data.append({
            "timestamp": row[0],
            "node_id": row[1],
            "moisture": row[2],
            "temperature": row[3],
            "battery": row[4],
            "status": row[5],
            "recommendation": row[6]
        })

    return jsonify(history_data)
@app.route("/")
def home():
    return render_template("index.html")


@app.route("/api/nodes")
def get_nodes():
    return jsonify(sensor_data)


@app.route("/api/nodes/<int:node_id>")
def get_node(node_id):
    for node in sensor_data:
        if node["node_id"] == node_id:
            return jsonify(node)

    return jsonify({"error": "Node not found"}), 404

def logging_loop():
    while True:
        log_sensor_data()
        time.sleep(300)


if not app.debug or os.environ.get("WERKZEUG_RUN_MAIN") == "true":
    logging_thread = threading.Thread(target=logging_loop, daemon=True)
    logging_thread.start()
if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000, debug=True)
