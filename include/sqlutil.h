#pragma once
#include <sqlite3.h>
#include <string>
#include <iostream>

auto quick_execute(const std::string& dbname, const std::string& query) -> const bool {
    sqlite3* db;
    int rc = sqlite3_open(dbname.c_str(), &db);
    if (rc != SQLITE_OK) {
        std::cout << "Can't open database: " << sqlite3_errmsg(db) << "\n";
        sqlite3_close(db);
        return false;
    }

    // run the sql query and catch eventual errors
    char* errmsg = nullptr;
    if (sqlite3_exec(db, query.c_str(), nullptr, 0, &errmsg) != SQLITE_OK) {
        std::cout << "SQL error: " << errmsg << "\n";
        sqlite3_free(errmsg);
        return false;
    }

    sqlite3_close(db);
    return true;
}