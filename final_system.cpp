#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <set>
using namespace std;

/* ===============================
   IR STRUCTURE
   =============================== */

struct Statement {
    string type;
    string variable;
    int line;
};

struct ErrorNode {
    string raw;
    string type;
};

/* ===============================
   GLOBAL DATA
   =============================== */

unordered_map<string, string> errorMap = {
    {"expected ';'", "MissingSemicolon"},
    {"not declared", "UndeclaredVariable"},
    {"division by zero", "DivisionByZero"},
    {"expected ')'", "MissingBracket"}
};

/* ===============================
   PARSER
   =============================== */

Statement parseLine(string line, int lineNo) {

    Statement stmt;
    stmt.line = lineNo;

    if (line.find("int") != string::npos)
        stmt.type = "Declaration";
    else if (line.find("return") != string::npos)
        stmt.type = "Return";
    else
        stmt.type = "Assignment";

    stmt.variable = line;

    return stmt;
}

/* ===============================
   DATA FLOW ANALYSIS
   =============================== */

void dataFlow(vector<Statement> &stmts) {

    set<string> declared;

    cout << "\n--- Data Flow Analysis ---\n";

    for (auto &s : stmts) {

        if (s.type == "Declaration") {
            declared.insert(s.variable);
        }

        if (s.type == "Assignment") {
            if (declared.find(s.variable) == declared.end()) {
                cout << "Warning: Variable may be undeclared (Line "
                     << s.line << ")\n";
            }
        }
    }
}

/* ===============================
   CONTROL FLOW
   =============================== */

void controlFlow(vector<Statement> &stmts) {

    bool hasReturn = false;

    cout << "\n--- Control Flow Analysis ---\n";

    for (auto &s : stmts) {
        if (s.type == "Return")
            hasReturn = true;
    }

    if (!hasReturn)
        cout << "Warning: No return statement found\n";
}

/* ===============================
   AI CLASSIFIER
   =============================== */

string classify(string msg) {

    for (auto &e : errorMap) {
        if (msg.find(e.first) != string::npos)
            return e.second;
    }
    return "UnknownError";
}

/* ===============================
   EXPLAINABILITY
   =============================== */

void explain(string msg, string type) {

    cout << "\n--- Explainability ---\n";

    cout << "Input Error: " << msg << endl;
    cout << "Detected Type: " << type << endl;

    if (type == "MissingSemicolon") {
        cout << "Reason: Pattern 'expected ;' matched\n";
        cout << "Fix: Add semicolon\n";
    }
    else if (type == "UndeclaredVariable") {
        cout << "Reason: Variable not declared\n";
        cout << "Fix: Declare variable\n";
    }
    else if (type == "DivisionByZero") {
        cout << "Reason: Division by zero\n";
        cout << "Fix: Check denominator\n";
    }
    else {
        cout << "Reason: Unknown pattern\n";
    }
}

/* ===============================
   MAIN SYSTEM
   =============================== */

int main() {

    int n;
    cout << "Enter number of code lines: ";
    cin >> n;
    cin.ignore();

    vector<Statement> stmts;

    cout << "Enter code:\n";

    for (int i = 1; i <= n; i++) {
        string line;
        getline(cin, line);
        stmts.push_back(parseLine(line, i));
    }

    string errorMsg;
    cout << "\nEnter compiler error:\n";
    getline(cin, errorMsg);

    // ANALYSIS
    dataFlow(stmts);
    controlFlow(stmts);

    // CLASSIFICATION
    string type = classify(errorMsg);

    cout << "\nDetected Error Type: " << type << endl;

    // EXPLANATION
    explain(errorMsg, type);

    cout << "\n--- Final System Execution Completed ---\n";

    return 0;
}
