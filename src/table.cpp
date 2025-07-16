#include<bits/stdc++.h>
#include "table.hpp"
using namespace std;

Table::Table(const string &name, const vector<string> &cols): name(name), cols(cols) {}

string Table::getName() const {
    return name;
}

vector<string> Table::getCols() const {
    return cols;
}

vector<vector<string>> Table::getRows() const {
    return rows;
}

void Table::describe() const {
    cout << "Table: " << name << "\nColumns: ";
    for(const auto &col: cols) {
        cout << col << " ";
    }
    cout << "\n";
}

void Table::insertRow(const vector<string> &row) {
    if(row.size() != cols.size()) {
        cerr << "Column count does not match" << endl;
        return;
    }
    rows.push_back(row);
    cout << "Row inserted successfully" << endl;
}

void Table::selectAll() const {
    cout << "Table: '" << name << "' " << endl;
    // column headers
    for(const auto &col: cols) {
        cout << col << "\t";
    }
    cout << endl;
    // row
    for(const auto &row: rows) {
        for(const auto &val: row) {
            cout << val << "\t";
        }
        cout << endl;
    }
}

void Table::selectWhere(const string &colName, const string &val) const {
    // find requested col
    auto it = find(cols.begin(), cols.end(), colName);  
    if(it == cols.end()) {
        cout << "Error: Column '" << colName << "' does not exist.\n";
        return;
    }
    // find the index of col and set the value
    int colInd = distance(cols.begin(), it);
    cout << "Table: '" << name << "' WHERE " << colName << " = " << val << endl;
    for(const auto &col: cols) {
        cout << col << "\t";
    }
    cout << endl;

    bool found = false;
    for(const auto &row: rows) {
        if(row[colInd] == val) {
            found = true;
            for(const auto &val: row) {
                cout << val << "\t";
            }
            cout << endl;
        }
    }
    if(!found) {
        cerr << "No matching row found" << endl;
    }
}

void Table::deleteWhere(const string &colName, const string &val) {
    auto it = find(cols.begin(), cols.end(), colName);
    if(it == cols.end()) {
        cout << "Error: Column '" << colName << "' does not exist.\n";
        return;
    }
    int colInd = distance(cols.begin(), it);
    int before = rows.size();
    // remove matched rows
    rows.erase(remove_if(rows.begin(), rows.end(), 
        [&](const vector<string> &row) {
            return row[colInd] == val;
        }), rows.end());
    
    int after = rows.size();
    cout << (before-after) << " rows deleted" << endl;
}

void Table::updateWhere(const string &targetCol, const string &newVal, const string &condCol, const string &condVal) {
    auto condit = find(cols.begin(), cols.end(), condCol);
    auto targetit = find(cols.begin(), cols.end(), targetCol);

    if(condit==cols.end() || targetit==cols.end()) {
        cout << "Error: Column doesn't exist.\n";
        return;
    }
    int condInd = distance(cols.begin(), condit);
    int targetInd = distance(cols.begin(), targetit);

    int cnt = 0;
    for(auto &row: rows) {
        if(row[condInd] == condVal) {
            row[targetInd] = newVal;
            cnt++;
        }
    }
    cout << cnt << " rows updated" << endl;
}