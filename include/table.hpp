#pragma once
#include<bits/stdc++.h>
using namespace std;

class Table {
private:
    string name;
    vector<string> cols;
    vector<vector<string>> rows;

public:
    Table() = default;
    Table(const string &name, const vector<string> &cols);
    
    string getName() const;
    vector<string> getCols() const;
    vector<vector<string>> getRows() const;
    void describe() const;
    void insertRow(const vector<string> &row);
    void selectAll() const;
    void selectWhere(const string &colName, const string &val) const;
    void deleteWhere(const string &colName, const string &val);
    void updateWhere(const string &targetCol, const string &newVal, const string &condCol, const string &condVal);
};