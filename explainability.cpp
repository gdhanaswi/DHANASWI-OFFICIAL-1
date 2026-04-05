#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Rule {
    string pattern;
    string type;
    string explanation;
};

vector<Rule> rules = {
    {"expected ';'", "MissingSemicolon", "Semicolon is missing at end"},
    {"not declared", "UndeclaredVariable", "Variable used before declaration"},
    {"division by zero", "DivisionByZero", "Cannot divide by zero"}
};

void explainSystem(string input) {

    cout << "\n--- Explainability Report ---\n";

    for (auto r : rules) {

        if (input.find(r.pattern) != string::npos) {

            cout << "Matched Pattern: " << r.pattern << endl;
            cout << "Classified As: " << r.type << endl;
            cout << "Reason: Rule-based pattern matching\n";
            cout << "Explanation: " << r.explanation << endl;

            return;
        }
    }

    cout << "No matching rule found.\n";
}

int main() {

    string input;

    cout << "Enter compiler error:\n";
    getline(cin, input);

    explainSystem(input);

    return 0;
}
