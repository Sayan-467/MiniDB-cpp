// Temporary placeholder for command handling

#include<bits/stdc++.h>
#include "parser.hpp"
#include "db.hpp"
using namespace std;

Database db;

vector<string> parseColList(const string &rawCols) {
    vector<string> cols;
    stringstream ss(rawCols);
    string col;

    while(getline(ss, col, ',')) {
        col.erase(remove_if(col.begin(), col.end(), ::isspace), col.end());
        if(!col.empty()) {
            cols.push_back(col);
        }
    }
    return cols;
}

vector<string> parseValList(const string &raw) {
    vector<string> val;
    string token;
    bool inQuote = false;
    string curr;

    for(char ch: raw) {
        if(ch == '"') {
            inQuote = !inQuote;
            continue;
        }
        else if(ch == ',' && !inQuote) {
            val.push_back(curr);
            curr.clear();
        }
        else {
            curr += ch;
        }
    }
    
    if(!curr.empty()) {
        val.push_back(curr);
    }
    // remove surrounding spaces
    for(auto &v: val) {
        v.erase(remove_if(v.begin(), v.end(), ::isspace), v.end());
    }
    return val;
}

void handleCommand(const string &command) {
    stringstream ss(command);
    string keyword;
    ss >> keyword;

    if(keyword == "CREATE") {
        // CREATE TABLE table_name(col1, col2)
        string temp, table, tableName, colPart;
        ss >> table >> tableName;
        if(table != "TABLE") {
            cerr << "Syntax error. Use: CREATE TABLE table_name (col1, col2)" << endl;
            return;
        }
        getline(ss, colPart, '(');
        getline(ss, colPart, ')');
        vector<string> cols = parseColList(colPart);
        db.createTable(tableName, cols);
    }
    else if(keyword == "DESCRIBE") {
        string tableName;
        ss >> tableName;
        db.describeTable(tableName);
    }
    else if(keyword == "INSERT") {
        // INSERT INTO table VALUES(...)
        string into, tableName, temp;
        ss >> into >> tableName >> temp;
        if(into != "INTO" || temp != "VALUES") {
            cerr << "Syntax error. Use: INSERT INTO table VALUES (...)\n";
            return;
        }
        string valPart;
        getline(ss, valPart, '(');  // skip until (
        getline(ss, valPart, ')');  // read inside (...)
        vector<string> val = parseValList(valPart);
        db.insertIntoTable(tableName, val);
    }
    else if(keyword == "SELECT") {
        // SELECT * FROM table
        string star, from, tableName;
        ss >> star >> from >> tableName;
        if (star != "*" || from != "FROM") {
            cerr << "Syntax error. Use: SELECT * FROM table\n";
            return;
        }
        string whereClause;
        ss >> ws;
        getline(ss, whereClause);
        // if no WHERE clause do simple SELECT
        if(whereClause.empty()) {
            db.selectFromTable(tableName);
            return;
        }
        // handle WHERE
        string whereWord = "WHERE ";
        if(whereClause.find(whereWord) != 0) {
            cerr << "Syntax error: expected WHERE\n";
            return;
        }

        whereClause = whereClause.substr(whereWord.size());
        auto eqPos = whereClause.find('=');
        if(eqPos == string::npos) {
            cerr << "Syntax error in WHERE clause\n";
            return;
        }
        string colName = whereClause.substr(0, eqPos);
        string val = whereClause.substr(eqPos+1);
        // trim whitespaces
        colName.erase(remove_if(colName.begin(), colName.end(), ::isspace), colName.end());
        val.erase(remove_if(val.begin(), val.end(), ::isspace), val.end());
        // remove surrounding quotes
        if(val.front() == '"' && val.back() == '"') {
            val = val.substr(1, val.length()-2);
        }

        db.selectWhere(tableName, colName, val);
    }
    else if (keyword == "DELETE") {
        string from, tableName;
        ss >> from >> tableName;
        if (from != "FROM") {
            cerr << "Syntax error. Use: DELETE FROM table WHERE col = value\n";
            return;
        }
        string token;
        ss >> token;
        if (token != "WHERE") {
            cerr << "Syntax error: expected WHERE clause.\n";
            return;
        }

        string colExpr;
        getline(ss, colExpr);
        colExpr.erase(0, colExpr.find_first_not_of(" \t"));
        auto eqPos = colExpr.find('=');
        if (eqPos == string::npos) {
            cerr << "Syntax error in WHERE clause.\n";
            return;
        }

        string colName = colExpr.substr(0, eqPos);
        string value = colExpr.substr(eqPos + 1);
        // Trim
        colName.erase(remove_if(colName.begin(), colName.end(), ::isspace), colName.end());
        value.erase(remove_if(value.begin(), value.end(), ::isspace), value.end());
        // Remove surrounding quotes
        if (!value.empty() && value.front() == '"' && value.back() == '"') {
            value = value.substr(1, value.size() - 2);
        }
        db.deleteFromTable(tableName, colName, value);
    }
    else if (keyword == "UPDATE") {
        string tableName;
        ss >> tableName;
        string token;
        ss >> token;
        if (token != "SET") {
            cerr << "Syntax error: expected SET clause.\n";
            return;
        }
        string setExpr;
        getline(ss, setExpr);
        // Merge the remaining into one string for full parsing
        string fullExpr = setExpr;
        auto wherePos = fullExpr.find("WHERE");
        if (wherePos == string::npos) {
            cerr << "Syntax error: expected WHERE clause.\n";
            return;
        }
        string setClause = fullExpr.substr(0, wherePos);
        string whereClause = fullExpr.substr(wherePos + 5); // skip "WHERE"
        // Parse SET 
        auto eqSet = setClause.find('=');
        if (eqSet == string::npos) {
            cerr << "Syntax error in SET clause.\n";
            return;
        }
        string targetCol = setClause.substr(0, eqSet);
        string newValue = setClause.substr(eqSet + 1);
        targetCol.erase(remove_if(targetCol.begin(), targetCol.end(), ::isspace), targetCol.end());
        newValue.erase(remove_if(newValue.begin(), newValue.end(), ::isspace), newValue.end());
        if (newValue.front() == '"' && newValue.back() == '"') {
            newValue = newValue.substr(1, newValue.length() - 2);
        }
        // Parse WHERE
        size_t eqCond = whereClause.find('=');
        if (eqCond == string::npos) {
            cerr << "Syntax error in WHERE clause.\n";
            return;
        }
        string condCol = whereClause.substr(0, eqCond);
        string condValue = whereClause.substr(eqCond + 1);
        condCol.erase(remove_if(condCol.begin(), condCol.end(), ::isspace), condCol.end());
        condValue.erase(remove_if(condValue.begin(), condValue.end(), ::isspace), condValue.end());
        if (condValue.front() == '"' && condValue.back() == '"') {
            condValue = condValue.substr(1, condValue.length() - 2);
        }
        db.updateTable(tableName, targetCol, newValue, condCol, condValue);
    }
    else if(keyword == "SAVE") {
        string fileName;
        ss >> fileName;
        if(fileName.empty()) {
            fileName = "minidb.txt";
        }
        db.saveToFile(fileName);
    }
    else if(keyword == "LOAD") {
        string fileName;
        ss >> fileName;
        if(fileName.empty()) {
            fileName = "minidb.txt";
        }
        db.loadFromFile(fileName);
    }
    else {
        cerr << "Unknown command " << keyword << endl;
    }
}