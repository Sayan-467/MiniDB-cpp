#pragma once
#include<bits/stdc++.h>
#include "table.hpp"
using namespace std;

class Database {
private:
    unordered_map<string, Table> tables;

public:
    void createTable(const string &name, const vector<string> &cols);
    bool tableExists(const string &name) const;
    void describeTable(const string &name) const;
    void insertIntoTable(const string &name, const vector<string> &val);
    void selectFromTable(const string &name) const;
    void selectWhere(const string &tableName, const string &colName, const string &val) const;
    void deleteFromTable(const string &tableName, const string &colName, const string &val);
    void updateTable(const string &tableName, const string &targetCol, const string &newVal, const string &condCol, const string &condVal);
    void saveToFile(const string &fileName) const;
    void loadFromFile(const string &fileName);
};