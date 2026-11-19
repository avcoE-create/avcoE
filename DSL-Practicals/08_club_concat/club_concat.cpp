// Practical 8: Pinnacle Club using Singly Linked List
// Two divisions have separate lists. Functions: total members, display, concatenate two lists.
// After concatenation: President of list 1 stays first, Secretary of list 2 stays last.
// (Secretary of list 1 and President of list 2 become ordinary members.)
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
public:
    Node *head;
    // Flags tell whether a president / secretary node exists
    bool hasPresident, hasSecretary;

    Club() { head = NULL; hasPresident = hasSecretary = false; }

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

    // Append list b to this list; b becomes empty
    // Concatenate: travel to last node of list 1 and link it to head of list 2 -> O(n)
    void concatenate(Club &b) {
        if (!b.head) return;
        if (!head) {                       // this list empty: take b entirely
            head = b.head;
            hasPresident = b.hasPresident;
            hasSecretary = b.hasSecretary;
        } else {
            Node *p = head;
            while (p->next) p = p->next;
            // Last node of list 1 now points to first node of list 2
            p->next = b.head;
            // hasPresident stays as list 1's; secretary now comes from list 2
            hasSecretary = b.hasSecretary;
        }
        // List 2 is now empty because its nodes belong to list 1
        b.head = NULL;
        b.hasPresident = b.hasSecretary = false;
    }
};

int main() {
    Club div[2];
    int ch, d;
    string prn, name;
    do {
        cout << "\n--- PINNACLE CLUB (2 divisions) ---\n1. Add President\n2. Add Secretary\n"
                "3. Add Member\n4. Total members\n5. Display\n"
                "6. Concatenate (Division 1 + Division 2)\n7. Exit\nChoice: ";
        cin >> ch;
        if (ch >= 1 && ch <= 5) {
            cout << "Division (1 or 2): "; cin >> d;
            if (d != 1 && d != 2) { cout << "Invalid division.\n"; continue; }
            d--;
        }
        if (ch >= 1 && ch <= 3) { cout << "Enter PRN: "; cin >> prn; cout << "Enter Name: "; cin >> name; }
        switch (ch) {
        case 1: div[d].addPresident(prn, name); break;
        case 2: div[d].addSecretary(prn, name); break;
        case 3: div[d].addMember(prn, name); break;
        case 4: cout << "Total members: " << div[d].countMembers() << "\n"; break;
        case 5: div[d].display(); break;
        case 6:
            div[0].concatenate(div[1]);
            cout << "Concatenated. Merged list (stored in Division 1):\n";
            div[0].display();
            break;
        case 7: cout << "Bye!\n"; break;
        default: cout << "Invalid choice.\n";
        }
    } while (ch != 7);
    return 0;
}
