#include<bits/stdc++.h>
#include "parser.hpp"
using namespace std;
 
int main() {
    string input;
    cout << "Welcome to MiniDB" << endl;

    while(true) {
        // set a prompt and read the input
        cout << "MiniDB> ";
        getline(cin, input);
        // exit condition
        if(input=="EXIT" || input=="exit") break;

        try {
            // route to parser
            handleCommand(input);   // command dispatcher
        }
        catch(const std::exception& e) {
            // handle any error
            std::cerr << e.what() << '\n';
        }
    }
    cout << "Exit from MiniDB" << endl;
    return 0;
}