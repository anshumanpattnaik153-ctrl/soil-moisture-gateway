import sqlite3

DATABASE = "sensor_data.db"


def init_database():
    connection = sqlite3.connect(DATABASE)

    cursor = connection.cursor()

    cursor.execute("""
        CREATE TABLE IF NOT EXISTS sensor_logs (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            timestamp TEXT NOT NULL,
            node_id INTEGER NOT NULL,
            moisture INTEGER NOT NULL,
            temperature INTEGER NOT NULL,
            battery INTEGER NOT NULL,
            status TEXT NOT NULL,
            recommendation TEXT NOT NULL
        )
    """)

    connection.commit()
    connection.close()


if __name__ == "__main__":
    init_database()
    print("Database initialized successfully.")
