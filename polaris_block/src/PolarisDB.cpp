#include "PolarisDB.h"

PolarisDB PolarisDB::getInstance()
{
	static PolarisDB instance;
	return instance;
}

PolarisDB::PolarisDB() : dbSession(Session(SessionFactory::instance().create("SQLite", "polaris.db")))
{
	dbSession << "CREATE TABLE IF NOT EXISTS Users(id INTEGER PRIMARY KEY AUTOINCREMENT, username TEXT NOT NULL, password TEXT NOT NULL)";
	dbSession << "CREATE TABLE IF NOT EXISTS Players(id INTEGER PRIMARY KEY AUTOINCREMENT, userID INTEGER, name TEXT, jobs BLOB, looks BLOB)";
}
