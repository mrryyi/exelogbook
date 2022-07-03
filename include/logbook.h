#pragma once
#include <sqlite3.h>
#include <string>
#include <tuple>
#include <vector>
#include <iostream>
#include "entry.h"

auto get_logbook(const std::string& dbname, std::vector<entry>& entries) -> void {
    // Gets all entries from the logbook table

    sqlite3* db;
    int rc = sqlite3_open(dbname.c_str(), &db);
    if (rc != SQLITE_OK) {
        std::cout << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    // run the sql query and catch eventual errors
    char* errmsg = nullptr;
    const std::string sql = "SELECT * FROM logbook_entry;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cout << "SQL error: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        entry e;
        e.exercise_name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        e.weight = sqlite3_column_int(stmt, 2);
        e.sets = sqlite3_column_int(stmt, 3);
        e.reps = sqlite3_column_int(stmt, 4);
        entries.push_back(e);
    }
}

auto create_tables(const std::string& dbname) -> const bool {
    sqlite3* db;
    int rc = sqlite3_open(dbname.c_str(), &db);
    if (rc != SQLITE_OK) {
        std::cout << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return false;
    }

    // run the sql query and catch eventual errors

    char* errmsg = nullptr;
    const std::string sql = "CREATE TABLE IF NOT EXISTS logbook_entry ("
                            "id INTEGER PRIMARY KEY"
                            ",exercise_name TEXT"
                            ",weight INTEGER"
                            ",sets INTEGER"
                            ",reps INTEGER"
                            ");";
    if (sqlite3_exec(db, sql.c_str(), nullptr, 0, &errmsg) != SQLITE_OK) {
        std::cout << "SQL error: " << errmsg << std::endl;
        sqlite3_free(errmsg);
        return false;
    }

    sqlite3_close(db);

    return true;
}

auto logbook_entry(const std::string& dbname,entry e) -> const bool {
    // Insert parameters into the logbook table
    sqlite3* db;
    int rc = sqlite3_open(dbname.c_str(), &db);
    if (rc != SQLITE_OK) {
        std::cout << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return false;
    }

    // run the sql query and catch eventual errors
    char* errmsg = nullptr;
    const std::string sql = "INSERT INTO logbook_entry (exercise_name, weight, sets, reps) VALUES ("
                            "'" + e.exercise_name + "'"
                            "," + std::to_string(e.weight) +
                            "," + std::to_string(e.sets) +
                            "," + std::to_string(e.reps) +
                            ");";
    
    if (sqlite3_exec(db, sql.c_str(), nullptr, 0, &errmsg) != SQLITE_OK) {
        std::cout << "SQL error: " << errmsg << std::endl;
        sqlite3_free(errmsg);
        return false;
    }

    sqlite3_close(db);
    return true;
}
