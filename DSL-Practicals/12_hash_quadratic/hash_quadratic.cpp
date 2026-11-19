// Practical 12: Telephone book using Hash Table with QUADRATIC PROBING
// index = (hash(name) + i*i) % SIZE, i = 0,1,2,...
// SIZE is prime; quadratic probing is guaranteed to find a free slot only
// while the table is at most half full, so a failed probe is reported.
#include <iostream>
#include <string>
using namespace std;

const int SIZE = 11;

// EMPTY = never used, OCCUPIED = has data, DELETED = removed (marker keeps the probe chain unbroken)
enum State { EMPTY, OCCUPIED, DELETED };

struct Entry {
    string name, phone;
    State state;
    Entry() : state(EMPTY) {}
};

class PhoneBook {
    Entry table[SIZE];
    int count;

    // Hash function: sum of ASCII values of the name % SIZE gives the index
    int hashFn(const string &key) {
        int sum = 0;
        for (char c : key) sum += c;
        return sum % SIZE;
    }
public:
    PhoneBook() { count = 0; }

    // Quadratic probing: on collision try h+1^2, h+2^2, h+3^2 ...
    // This reduces primary clustering seen in linear probing
    void insert(string name, string phone) {
        int h = hashFn(name);
        int firstFree = -1;
        for (int i = 0; i < SIZE; i++) {
            int idx = (h + i * i) % SIZE;
            if (table[idx].state == OCCUPIED && table[idx].name == name) {
                cout << "Client already exists.\n"; return;
            }
            if (table[idx].state != OCCUPIED && firstFree == -1) firstFree = idx;
            if (table[idx].state == EMPTY) break;
        }
        // All probed slots were occupied -> insertion failed
        if (firstFree == -1) {
            cout << "No free slot found by quadratic probing (table too full).\n";
            return;
        }
        table[firstFree].name = name;
        table[firstFree].phone = phone;
        table[firstFree].state = OCCUPIED;
        count++;
        cout << "Inserted at index " << firstFree
             << (firstFree != h ? " (collision resolved)" : "") << ".\n";
    }

    // Follow the same probe sequence; stop at an EMPTY slot
    void search(string name) {
        int h = hashFn(name);
        for (int i = 0; i < SIZE; i++) {
            int idx = (h + i * i) % SIZE;
            if (table[idx].state == EMPTY) break;
            if (table[idx].state == OCCUPIED && table[idx].name == name) {
                cout << "Found: " << name << " -> " << table[idx].phone
                     << " (index " << idx << ", comparisons: " << i + 1 << ")\n";
                return;
            }
        }
        cout << name << " not found.\n";
    }

    void remove(string name) {
        int h = hashFn(name);
        for (int i = 0; i < SIZE; i++) {
            int idx = (h + i * i) % SIZE;
            if (table[idx].state == EMPTY) break;
            if (table[idx].state == OCCUPIED && table[idx].name == name) {
                table[idx].state = DELETED;
                count--;
                cout << "Deleted " << name << ".\n";
                return;
            }
        }
        cout << name << " not found.\n";
    }

    void display() {
        cout << "\nIndex\tName\t\tPhone\n";
        for (int i = 0; i < SIZE; i++) {
            cout << i << "\t";
            if (table[i].state == OCCUPIED) cout << table[i].name << "\t\t" << table[i].phone;
            else if (table[i].state == DELETED) cout << "(deleted)";
            else cout << "-";
            cout << "\n";
        }
    }
};

int main() {
    PhoneBook pb;
    int ch;
    string name, phone;
    do {
        cout << "\n--- TELEPHONE BOOK (Quadratic Probing) ---\n1. Insert\n2. Search\n"
                "3. Delete\n4. Display\n5. Exit\nChoice: ";
        cin >> ch;
        switch (ch) {
        case 1: cout << "Name: "; cin >> name; cout << "Phone: "; cin >> phone; pb.insert(name, phone); break;
        case 2: cout << "Name to search: "; cin >> name; pb.search(name); break;
        case 3: cout << "Name to delete: "; cin >> name; pb.remove(name); break;
        case 4: pb.display(); break;
        case 5: cout << "Bye!\n"; break;
        default: cout << "Invalid choice.\n";
        }
    } while (ch != 5);
    return 0;
}
