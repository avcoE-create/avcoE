// Practical 7: Pinnacle Club using Singly Linked List
// First node = President, Last node = Secretary
// Functions: delete member / president / secretary, count members, display
// (add functions are included so the list can be built for testing)
//
// ALGORITHM
// ---------
// Data: singly linked list, node = (PRN, name, next). First node = President,
//       last node = Secretary. Flags hasPresident / hasSecretary record whether they exist.
//       (The add functions work as in Practical 6 and are used only to build the list.)
//
// A. deletePresident()
//    1. If there is no president, print a message and stop.
//    2. t = head, head = head->next   (move head to the next node).
//    3. Free t and set hasPresident = false.
//
// B. deleteSecretary()
//    1. If there is no secretary, print a message and stop.
//    2. If the list has only one node, free it and set head = NULL.
//    3. Else move p to the SECOND LAST node (while p->next->next != NULL),
//       free p->next and set p->next = NULL.
//    4. Set hasSecretary = false.
//
// C. deleteMember(prn)   (works for any node)
//    1. If the list is empty, print a message and stop.
//    2. Set prev = NULL, cur = head. While cur != NULL and cur->prn != prn: prev = cur, cur = cur->next.
//    3. If cur is NULL, the PRN is not found -> stop.
//    4. If cur is the head, clear hasPresident; if cur is the last node, clear hasSecretary.
//    5. If prev is NULL, head = cur->next; else prev->next = cur->next   (unlink the node).
//    6. Free cur.
//
// D. countMembers(): set c = 0; traverse from head to NULL, c++ for each node; return c.
//
// E. display(): traverse the list printing PRN, name and role (President / Member / Secretary), then the total.
//
// F. main(): menu (add / delete president / delete secretary / delete member / count / display / exit);
//    repeat until Exit.

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

    // ---------- add (needed to build the list) ----------
    void addPresident(string prn, string name) {
        if (hasPresident) { cout << "President already exists.\n"; return; }
        Node *t = new Node(prn, name);
        t->next = head; head = t; hasPresident = true;
    }
    void addSecretary(string prn, string name) {
        if (hasSecretary) { cout << "Secretary already exists.\n"; return; }
        Node *t = new Node(prn, name);
        if (!head) head = t;
        else { Node *p = head; while (p->next) p = p->next; p->next = t; }
        hasSecretary = true;
    }
    void addMember(string prn, string name) {
        Node *t = new Node(prn, name);
        if (!head) head = t;
        else if (hasSecretary && head->next == NULL) { t->next = head; head = t; }
        else {
            Node *p = head;
            if (hasSecretary) while (p->next->next) p = p->next;
            else while (p->next) p = p->next;
            t->next = p->next; p->next = t;
        }
    }

    // ---------- delete ----------
    // President is the head node: move head to next node and free the old head
    void deletePresident() {
        if (!hasPresident) { cout << "No president to delete.\n"; return; }
        Node *t = head;
        head = head->next;
        delete t;
        hasPresident = false;
        cout << "President deleted.\n";
    }

    // Secretary is the last node: stop at second last node, free last, set its next = NULL
    void deleteSecretary() {
        if (!hasSecretary) { cout << "No secretary to delete.\n"; return; }
        if (head->next == NULL) { delete head; head = NULL; }
        else {
            Node *p = head;
            while (p->next->next) p = p->next;
            delete p->next;
            p->next = NULL;
        }
        hasSecretary = false;
        cout << "Secretary deleted.\n";
    }

    // Delete any member by PRN (works for president/secretary too)
    // Search by PRN while keeping a 'prev' pointer; then prev->next = cur->next unlinks the node
    void deleteMember(string prn) {
        if (!head) { cout << "Club is empty.\n"; return; }
        Node *prev = NULL, *cur = head;
        while (cur && cur->prn != prn) { prev = cur; cur = cur->next; }
        if (!cur) { cout << "PRN " << prn << " not found.\n"; return; }

        // If the deleted node was president / secretary, update the flag
        if (cur == head && hasPresident) hasPresident = false;
        if (cur->next == NULL && hasSecretary) hasSecretary = false;

        if (!prev) head = cur->next;
        else prev->next = cur->next;
        delete cur;
        cout << "Member deleted.\n";
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
                "4. Delete President\n5. Delete Secretary\n6. Delete Member (by PRN)\n"
                "7. Total members\n8. Display\n9. Exit\nChoice: ";
        cin >> ch;
        if (ch >= 1 && ch <= 3) { cout << "Enter PRN: "; cin >> prn; cout << "Enter Name: "; cin >> name; }
        if (ch == 6) { cout << "Enter PRN to delete: "; cin >> prn; }
        switch (ch) {
        case 1: c.addPresident(prn, name); break;
        case 2: c.addSecretary(prn, name); break;
        case 3: c.addMember(prn, name); break;
        case 4: c.deletePresident(); break;
        case 5: c.deleteSecretary(); break;
        case 6: c.deleteMember(prn); break;
        case 7: cout << "Total members: " << c.countMembers() << "\n"; break;
        case 8: c.display(); break;
        case 9: cout << "Bye!\n"; break;
        default: cout << "Invalid choice.\n";
        }
    } while (ch != 9);
    return 0;
}
