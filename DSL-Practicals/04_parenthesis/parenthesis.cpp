// Practical 4: Check whether an expression is well parenthesized using a stack
#include <iostream>
#include <string>
using namespace std;

const int MAX = 100;

// Stack = LIFO (Last In First Out). 'top' points to the most recently pushed element
class Stack {
    char arr[MAX];
    int top;
public:
    Stack() { top = -1; }
    bool isEmpty() { return top == -1; }
    bool isFull() { return top == MAX - 1; }
    void push(char c) { if (!isFull()) arr[++top] = c; }
    // pop: return the top element and move top down
    char pop() { return isEmpty() ? '\0' : arr[top--]; }
    char peek() { return isEmpty() ? '\0' : arr[top]; }
};

bool isMatching(char open, char close) {
    return (open == '(' && close == ')') ||
           (open == '{' && close == '}') ||
           (open == '[' && close == ']');
}

// Logic: push every opening bracket; on a closing bracket pop and check it matches.
// At the end the stack must be empty.
bool isBalanced(const string &expr) {
    Stack s;
    for (char c : expr) {
        if (c == '(' || c == '{' || c == '[') {
            s.push(c);
        } else if (c == ')' || c == '}' || c == ']') {
            // Closing bracket with empty stack, or of the wrong type -> not balanced
            if (s.isEmpty() || !isMatching(s.pop(), c))
                return false;
        }
    }
    return s.isEmpty();   // leftover openers => unbalanced
}

int main() {
    int ch;
    string expr;
    do {
        cout << "\n--- MENU ---\n1. Check expression\n2. Exit\nChoice: ";
        cin >> ch;
        if (ch == 1) {
            cout << "Enter expression (no spaces): ";
            cin >> expr;
            if (isBalanced(expr)) cout << expr << " is WELL parenthesized.\n";
            else cout << expr << " is NOT well parenthesized.\n";
        }
    } while (ch != 2);
    return 0;
}
