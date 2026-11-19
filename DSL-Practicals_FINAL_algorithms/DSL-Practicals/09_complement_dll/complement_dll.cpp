// Practical 9: 1's complement and 2's complement of a binary number using Doubly Linked List
//
// ALGORITHM
// ---------
// Data: doubly linked list, node = (bit, prev, next); one node per binary digit.
//
// A. build(s)
//    1. If s is empty or has a character other than '0' / '1', report invalid input.
//    2. For every character c, append a new node with bit = c - '0' at the TAIL.
//
// B. 1's complement
//    1. Create an empty result list.
//    2. Traverse the original list from head to tail.
//    3. For every bit, append (bit XOR 1) to the result   (0 -> 1, 1 -> 0).
//
// C. 2's complement = 1's complement + 1
//    1. Compute the 1's complement list.
//    2. Set carry = 1 and start at the TAIL (last bit).
//    3. While carry == 1 and the node exists:
//         - if bit == 0: set it to 1 and carry = 0.
//         - else (bit == 1): set it to 0 (1 + 1 = 0, carry stays 1).
//         - move to the previous node using the prev pointer.
//    4. A carry left after the first bit is ignored (same width is kept).
//
// D. main(): menu (1's complement / 2's complement / exit); read the binary string,
//    build the list, display the original and the result. Repeat until Exit.

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

    void append(int b) {
        Node *t = new Node(b);
        if (!head) head = tail = t;
        else { tail->next = t; t->prev = tail; tail = t; }
    }

    // Store each character of the binary string as one node
    bool build(const string &s) {
        for (char c : s) if (c != '0' && c != '1') return false;
        for (char c : s) append(c - '0');
        return !s.empty();
    }

    void display() {
        for (Node *p = head; p; p = p->next) cout << p->bit;
        cout << "\n";
    }

    // New list with every bit flipped
    // 1's complement: flip every bit (0->1, 1->0). XOR with 1 does the flip
    BinaryDLL onesComplement() {
        BinaryDLL r;
        for (Node *p = head; p; p = p->next) r.append(p->bit ^ 1);
        return r;
    }

    // 2's complement = 1's complement + 1 (add from the tail using prev pointers)
    // 2's complement = 1's complement + 1
    BinaryDLL twosComplement() {
        BinaryDLL r = onesComplement();
        int carry = 1;
        // Add 1 starting from the LAST bit, moving left with prev (this is why we use a DLL)
        for (Node *p = r.tail; p && carry; p = p->prev) {
            if (p->bit == 0) { p->bit = 1; carry = 0; }
            else p->bit = 0;     // 1 + 1 = 0 carry 1
        }
        // carry left over means overflow (input was all zeros): ignored, same width kept
        return r;
    }
};

int main() {
    int ch;
    string s;
    do {
        cout << "\n--- MENU ---\n1. 1's complement\n2. 2's complement\n3. Exit\nChoice: ";
        cin >> ch;
        if (ch == 1 || ch == 2) {
            cout << "Enter binary number: ";
            cin >> s;
            BinaryDLL b;
            if (!b.build(s)) { cout << "Invalid binary number.\n"; continue; }
            cout << "Original      : "; b.display();
            if (ch == 1) { cout << "1's complement: "; b.onesComplement().display(); }
            else         { cout << "2's complement: "; b.twosComplement().display(); }
        }
    } while (ch != 3);
    return 0;
}
