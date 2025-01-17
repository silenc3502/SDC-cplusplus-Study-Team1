//
// Created by eddi on 23. 11. 29.
//

#include "DbProcess.h"
#include <iostream>
#include <memory>

DbProcess* DbProcess::instance = nullptr;

DbProcess::DbProcess(const char* host, const char* user, const char* pass, const char* dbName)
        : conn(nullptr), DB_HOST(host), DB_USER(user), DB_PASS(pass), DB_NAME(dbName) {}

DbProcess::~DbProcess() {
    if (conn != nullptr) {
        mysql_close(conn);
    }
}


bool DbProcess::connect() {
    conn = mysql_init(nullptr);
    return (mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, nullptr, 0) != nullptr);
}


// 쿼리문 실행을 위한 함수(?)
bool DbProcess::insertData(const std::string& queryString) {

    std::string insertQuery;
    insertQuery = queryString;

    return (mysql_query(conn, insertQuery.c_str()) == 0);
}


bool DbProcess::updateData(int boardId, const std::string& newTitle, const std::string& newContent) {
    std::string updateQuery = "UPDATE board SET title = '" + newTitle +
                              "', content = '" + newContent +
                              "' WHERE board_id = " + std::to_string(boardId);

    return (mysql_query(conn, updateQuery.c_str()) == 0);
}

bool DbProcess::deleteData(int boardId) {
    std::string deleteQuery = "DELETE FROM board WHERE board_id = " + std::to_string(boardId);

    return (mysql_query(conn, deleteQuery.c_str()) == 0);
}

void DbProcess::selectData() {
    std::string selectQuery = "SELECT * FROM board";

    if (mysql_query(conn, selectQuery.c_str()) == 0) {
        MYSQL_RES* result = mysql_store_result(conn);
        if (result == nullptr) {
            std::cerr << "mysql_store_result() failed" << std::endl;
            return;
        }

        MYSQL_ROW row;
        while ((row = mysql_fetch_row(result)) != nullptr) {
            std::cout << "board_id: " << row[0] << ", content: " << row[1]
                      << ", reg_date: " << (row[2] ? row[2] : "NULL") << ", title: " << row[3]
                      << ", upd_date: " << (row[4] ? row[4] : "NULL") << ", writer: " << row[5] << std::endl;
        }

        mysql_free_result(result);
    } else {
        std::cerr << "mysql_query() failed" << std::endl;
    }
}

void DbProcess::readData(int boardId) {
    std::string readQuery = "SELECT * FROM board WHERE board_id = " + std::to_string(boardId);
    if (mysql_query(conn, readQuery.c_str()) == 0) {
        MYSQL_RES* result = mysql_store_result(conn);
        if (result == nullptr) {
            std::cerr << "mysql_store_result() failed" << std::endl;
            return;
        }

        MYSQL_ROW row = mysql_fetch_row(result);
        if (row != nullptr) {
            std::cout << "board_id: " << row[0] << ", content: " << row[1]
                      << ", reg_date: " << (row[2] ? row[2] : "NULL") << ", title: " << row[3]
                      << ", upd_date: " << (row[4] ? row[4] : "NULL") << ", writer: " << row[5] << std::endl;
        } else {
            std::cout << "Record not found for board_id: " << boardId << std::endl;
        }

        mysql_free_result(result);
    } else {
        std::cerr << "mysql_query() failed" << std::endl;
    }
}

 DbProcess* DbProcess::getInstance(const char* host, const char* user, const char* pass, const char* dbName) {

    if(instance == nullptr) {
        instance = new DbProcess(host, user,pass, dbName);
        if(!(instance->connect()))
        {
            std::cout << "연결이 안 됩니다." << std::endl;
        }

    }
    return instance;
}

DbProcess* DbProcess::getInstance()
{
    return instance;
}

MYSQL *DbProcess::getConn()
{
    return conn;
}