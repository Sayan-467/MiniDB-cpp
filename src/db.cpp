#include<bits/stdc++.h>
#include "db.hpp"
using namespace std;

void Database::createTable(const string &name, const vector<string> &cols) {
    if(tableExists(name)) {
        cerr << "Table" << name << " already exists" << endl;
        return;
    }
    tables[name] = Table(name, cols);
    cout << "Table '" << name << "' created successfully" << endl;
}

bool Database::tableExists(const string &name) const {
    return tables.find(name) != tables.end();
}

void Database::describeTable(const string &name) const {
    if(!tableExists(name)) {
        cerr << "Table" << name << " does not exist" << endl;
        return;
    }
    tables.at(name).describe();
}

void Database::insertIntoTable(const string &name, const vector<string> &val) {
    if(!tableExists(name)) {
        cerr << "Table '" << name << "' does not exist.\n";
        return;
    }
    tables[name].insertRow(val);
}

void Database::selectFromTable(const string &name) const {
    if(!tableExists(name)) {
        cerr << "Table '" << name << "' does not exist.\n";
        return;
    }
    tables.at(name).selectAll();
}

void Database::selectWhere(const string &tableName, const string &colName, const string &val) const {
    if(!tableExists(tableName)) {
        cerr << "Table '" << tableName << "' does not exist.\n";
        return;
    }
    tables.at(tableName).selectWhere(colName, val);
}

void Database::deleteFromTable(const string &tableName, const string &colName, const string &val) {
    if(!tableExists(tableName)) {
        cerr << "Table '" << tableName << "' does not exist.\n";
        return;
    }
    tables[tableName].deleteWhere(colName, val);
}

void Database::updateTable(const string &tableName, const string &targetCol, const string &newVal, const string &condCol, const string &condVal) {
    if(!tableExists(tableName)) {
        cerr << "Table '" << tableName << "' does not exist.\n";
        return;
    }
    tables[tableName].updateWhere(targetCol, newVal, condCol, condVal);
}

void Database::saveToFile(const string &fileName) const {
    ofstream out(fileName);
    if(!out) {
        cerr << "Error opening file for writing.\n";
        return;
    }

    for(auto it = tables.begin(); it != tables.end(); ++it) {
        out << "Table: " << it->first << endl;
        for(const auto &col: it->second.getCols()) {
            out << col << " ";
        }
        out << endl;

        const auto &rows = (it->second).getRows();
        for(const auto &row: rows) {
            for(const auto &val: row) {
                out << val << endl;
            }
            out << endl;
        }
        out << "END" << endl;
    }
    cout << "Database saved to '" << fileName << "' successfully" << endl;
}

void Database::loadFromFile(const string &fileName) {
    ifstream in(fileName);
    if(!in) {
        cerr << "Error opening file for reading.\n";
        return;
    }

    string line;
    if(getline(in, line)) {
        if (line.rfind("TABLE", 0) == 0) {
            string tableName = line.substr(6);
            getline(in, line);
            vector<string> columns;
            istringstream colStream(line);
            string col;
            while (colStream >> col) columns.push_back(col);

            tables[tableName] = Table(tableName, columns);

            while (getline(in, line) && line != "END") {
                istringstream rowStream(line);
                vector<string> row;
                string val;
                while (rowStream >> val) row.push_back(val);
                tables[tableName].insertRow(row);
            }
        }
    }
    cout << "Database loaded from '" << fileName << "' successfully" << endl;
}