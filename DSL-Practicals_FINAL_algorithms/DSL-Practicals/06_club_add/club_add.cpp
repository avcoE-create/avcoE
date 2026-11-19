// Practical 6: Pinnacle Club using Singly Linked List
// First node = President, Last node = Secretary
// Functions: add member / president / secretary, count members, display
//
// ALGORITHM
// ---------
// Data: singly linked list, node = (PRN, name, next). First node = President,
//       last node = Secretary. Flags hasPresident / hasSecretary record whether they exist.
//
// A. addPresident(prn, name)
//    1. If a president already exists, print a message and stop.
//    2. Create a new node t.
//    3. t->next = head, head = t   (insert at the BEGINNING).
//    4. Set hasPresident = true.
//
// B. addSecretary(prn, name)
//    1. If a secretary already exists, print a message and stop.
//    2. Create a new node t.
//    3. If the list is empty, head = t.
//       Else move p to the last node (while p->next != NULL) and set p->next = t   (insert at the END).
//    4. Set hasSecretary = true.
//
// C. addMember(prn, name)   (goes between president and secretary)
//    1. Create a new node t.
//    2. If the list is empty, head = t.
//    3. Else if only the secretary exists (one node), put t before it: t->next = head, head = t.
//    4. Else move p to the node just BEFORE the secretary
//       (while p->next->next != NULL), or to the last node if there is no secretary.
//       Then t->next = p->next and p->next = t.
//
// D. countMembers(): set c = 0; traverse from head to NULL, c++ for each node; return c.
//
// E. display()
//    1. If head is NULL, print "no members" and stop.
//    2. Traverse the list; role = President for head, Secretary for the last node
//       (if those flags are set), otherwise Member. Print PRN, name, role.
//    3. Print the total count.
//
// F. main(): menu (add president / secretary / member / count / display / exit); repeat until Exit.

#include <iostream>
#include <string>
using namespace std;

// One node = one member: data (PRN, name) + pointer to the next node
struct Node {
    string prn, name;
    Node *next;
    Node(string p, string n) : prn(p), name(n), next(NULL) {}
};

class Club {
    Node *head;
    // Flags tell whether a president / secretary node exists
    bool hasPresident, hasSecretary;
public:
    Club() { head = NULL; hasPresident = hasSecretary = false; }

    // President is always the first node
    // President is always the FIRST node -> insert at beginning
    void addPresident(string prn, string name) {
        if (hasPresident) { cout << "President already exists.\n"; return; }
        Node *t = new Node(prn, name);
        t->next = head;
        head = t;
        hasPresident = true;
        cout << "President added.\n";
    }

    // Secretary is always the last node
    // Secretary is always the LAST node -> insert at end
    void addSecretary(string prn, string name) {
        if (hasSecretary) { cout << "Secretary already exists.\n"; return; }
        Node *t = new Node(prn, name);
        if (!head) head = t;
        else {
            Node *p = head;
            while (p->next) p = p->next;
            p->next = t;
        }
        hasSecretary = true;
        cout << "Secretary added.\n";
    }

    // Ordinary member goes after president, before secretary (i.e. before the secretary if present)
    // Ordinary member goes in the middle: just before the secretary (or at end if no secretary)
    void addMember(string prn, string name) {
        Node *t = new Node(prn, name);
        if (!head) { head = t; }
        else if (hasSecretary && head->next == NULL) {
            // only the secretary exists -> new member goes before it
            t->next = head;
            head = t;
        } else {
            Node *p = head;
            if (hasSecretary) {
                while (p->next->next) p = p->next;   // stop before secretary
            } else {
                while (p->next) p = p->next;          // append at end
            }
            t->next = p->next;
            p->next = t;
        }
        cout << "Member added.\n";
    }

    // Count nodes by traversing from head until NULL
    int countMembers() {
        int c = 0;
        for (Node *p = head; p; p = p->next) c++;
        return c;
    }

    void display() {
        if (!head) { cout << "Club has no members.\n"; return; }
        cout << "\nPRN\t\tName\t\tRole\n";
        for (Node *p = head; p; p = p->next) {
            string role = "Member";
            if (hasPresident && p == head) role = "President";
            else if (hasSecretary && p->next == NULL) role = "Secretary";
            cout << p->prn << "\t\t" << p->name << "\t\t" << role << "\n";
        }
        cout << "Total members: " << countMembers() << "\n";
    }
};

int main() {
    Club c;
    int ch;
    string prn, name;
    do {
        cout << "\n--- PINNACLE CLUB ---\n1. Add President\n2. Add Secretary\n3. Add Member\n"
                "4. Total members\n5. Display\n6. Exit\nChoice: ";
        cin >> ch;
        if (ch >= 1 && ch <= 3) {
            cout << "Enter PRN: ";  cin >> prn;
            cout << "Enter Name: "; cin >> name;
        }
        switch (ch) {
        case 1: c.addPresident(prn, name); break;
        case 2: c.addSecretary(prn, name); break;
        case 3: c.addMember(prn, name); break;
        case 4: cout << "Total members: " << c.countMembers() << "\n"; break;
        case 5: c.display(); break;
        case 6: cout << "Bye!\n"; break;
        default: cout << "Invalid choice.\n";
        }
    } while (ch != 6);
    return 0;
}
