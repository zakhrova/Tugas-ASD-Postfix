#include <iostream>
#include <stack>
#include <sstream>
#include <vector>
using namespace std;

struct Node {
    string value;
    Node* left;
    Node* right;
    Node(string val) : value(val), left(nullptr), right(nullptr) {}
};

bool isOperator(const string& s) {
    return s == "+" || s == "-" || s == "*" || s == "/";
}

Node* buildTree(const vector<string>& postfix) {
    stack<Node*> stk;
    for (const string& token : postfix) {
        if (!isOperator(token)) {
            stk.push(new Node(token));
        } else {
            Node* right = stk.top(); stk.pop();
            Node* left = stk.top(); stk.pop();
            Node* opNode = new Node(token);
            opNode->left = left;
            opNode->right = right;
            stk.push(opNode);
        }
    }
    return stk.top();
}

void postorder(Node* node) {
    if (!node) return;
    postorder(node->left);
    postorder(node->right);
    cout << node->value << " ";
}

int evaluate(Node* node) {
    if (!node->left && !node->right) return stoi(node->value);
    int left = evaluate(node->left);
    int right = evaluate(node->right);
    if (node->value == "+") return left + right;
    if (node->value == "-") return left - right;
    if (node->value == "*") return left * right;
    if (node->value == "/") return left / right;
    return 0;
}

vector<string> split(const string& expr) {
    stringstream ss(expr);
    string token;
    vector<string> result;
    while (ss >> token) result.push_back(token);
    return result;
}

int main() {
    string postfixExpr = "1 7 + 1 1 - *"; // Example postfix
    vector<string> tokens = split(postfixExpr);

    Node* root = buildTree(tokens);

    cout << "Postorder Traversal: ";
    postorder(root);
    cout << "\nEvaluated Result: " << evaluate(root) << endl;

    return 0;
}