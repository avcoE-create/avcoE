// Practical 10: Addition of two binary numbers using Doubly Linked List
#include <iostream>
#include <string>
using namespace std;

// Doubly linked list node: one bit + pointers to BOTH previous and next nodes
struct Node {
    int bit;
    Node *prev, *next;
    Node(int b) : bit(b), prev(NULL), next(NULL) {}
};

class BinaryDLL {
public:
    Node *head, *tail;
    BinaryDLL() { head = tail = NULL; }

    void append(int b) {           // insert at end
        Node *t = new Node(b);
        if (!head) head = tail = t;
        else { tail->next = t; t->prev = tail; tail = t; }
    }

    // Insert at beginning (result bits are produced from right to left)
    void prepend(int b) {          // insert at beginning
        Node *t = new Node(b);
        if (!head) head = tail = t;
        else { t->next = head; head->prev = t; head = t; }
    }

    bool build(const string &s) {
        if (s.empty()) return false;
        for (char c : s) if (c != '0' && c != '1') return false;
        for (char c : s) append(c - '0');
        return true;
    }

    void display() {
        for (Node *p = head; p; p = p->next) cout << p->bit;
        cout << "\n";
    }
};

// Add from the tail of both lists moving backwards with prev pointers
// Like school addition: start from last bits and move left using prev.
// sum bit = (x+y+carry) % 2, new carry = (x+y+carry) / 2
BinaryDLL addBinary(BinaryDLL &a, BinaryDLL &b) {
    BinaryDLL sum;
    Node *p = a.tail, *q = b.tail;
    int carry = 0;
    // Continue while any number has bits left or a carry remains (handles different lengths)
    while (p || q || carry) {
        int x = p ? p->bit : 0;
        int y = q ? q->bit : 0;
        int s = x + y + carry;
        sum.prepend(s % 2);
        carry = s / 2;
        if (p) p = p->prev;
        if (q) q = q->prev;
    }
    return sum;
}

int main() {
    int ch;
    string s1, s2;
    do {
        cout << "\n--- MENU ---\n1. Add two binary numbers\n2. Exit\nChoice: ";
        cin >> ch;
        if (ch == 1) {
            cout << "Enter first binary number: ";  cin >> s1;
            cout << "Enter second binary number: "; cin >> s2;
            BinaryDLL a, b;
            if (!a.build(s1) || !b.build(s2)) { cout << "Invalid binary number.\n"; continue; }
            BinaryDLL r = addBinary(a, b);
            cout << "  "; a.display();
            cout << "+ "; b.display();
            cout << "= "; r.display();
        }
    } while (ch != 2);
    return 0;
}
