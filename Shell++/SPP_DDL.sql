-- The tables for the commands available in the system

CREATE TABLE IF NOT EXISTS Commands(
	c_id			INTEGER PRIMARY KEY AUTOINCREMENT,
	c_name			TEXT UNIQUE NOT NULL,
	c_path			TEXT NOT NULL,
	c_description	TEXT
);

CREATE TABLE IF NOT EXISTS CommnadsHistory(
	ch_id			INTEGER PRIMARY KEY,
	ch_c_id			INTEGER,
	ch_date			DATETIME DEFAULT CURRENT_TIMESTAMP
);