// Practical 13: Hash Table with CHAINING (separate chaining using linked lists)
// index = key % SIZE ; each slot holds a linked list of (key, value) pairs
#include <iostream>
#include <string>
using namespace std;

const int SIZE = 10;

// Each node holds one key-value pair and a pointer to the next node in the same chain
struct Node {
    int key;
    string value;
    Node *next;
    Node(int k, string v) : key(k), value(v), next(NULL) {}
};

class HashTable {
    // Array of linked-list heads: table[i] is the chain for index i
    Node *table[SIZE];
    // Hash function: key % SIZE
    int hashFn(int key) { return key % SIZE; }
public:
    HashTable() { for (int i = 0; i < SIZE; i++) table[i] = NULL; }

    // Collision handling: keys with the same index are added to that index's linked list.
    // Table never becomes 'full'.
    void insert(int key, string value) {
        int idx = hashFn(key);
        for (Node *p = table[idx]; p; p = p->next)
            if (p->key == key) { cout << "Key " << key << " already exists.\n"; return; }
        Node *t = new Node(key, value);
        if (!table[idx]) table[idx] = t;
        else {
            Node *p = table[idx];
            while (p->next) p = p->next;
            p->next = t;
            cout << "Collision at index " << idx << " -> chained.\n";
        }
        cout << "Inserted key " << key << " at index " << idx << ".\n";
    }

    // Go to the chain at the hashed index and search only that chain
    void search(int key) {
        int idx = hashFn(key), comp = 0;
        for (Node *p = table[idx]; p; p = p->next) {
            comp++;
            if (p->key == key) {
                cout << "Found: " << key << " -> " << p->value
                     << " (index " << idx << ", comparisons: " << comp << ")\n";
                return;
            }
        }
        cout << "Key " << key << " not found (comparisons: " << comp << ").\n";
    }

    void remove(int key) {
        int idx = hashFn(key);
        Node *prev = NULL, *cur = table[idx];
        while (cur && cur->key != key) { prev = cur; cur = cur->next; }
        if (!cur) { cout << "Key " << key << " not found.\n"; return; }
        if (!prev) table[idx] = cur->next;
        else prev->next = cur->next;
        delete cur;
        cout << "Key " << key << " deleted.\n";
    }

    void display() {
        for (int i = 0; i < SIZE; i++) {
            cout << i << " : ";
            for (Node *p = table[i]; p; p = p->next)
                cout << "[" << p->key << "," << p->value << "] -> ";
            cout << "NULL\n";
        }
    }
};

int main() {
    HashTable ht;
    int ch, key;
    string value;
    do {
        cout << "\n--- HASH TABLE (Chaining) ---\n1. Insert\n2. Search\n3. Delete\n"
                "4. Display\n5. Exit\nChoice: ";
        cin >> ch;
        switch (ch) {
        case 1: cout << "Key (integer): "; cin >> key; cout << "Value: "; cin >> value; ht.insert(key, value); break;
        case 2: cout << "Key to search: "; cin >> key; ht.search(key); break;
        case 3: cout << "Key to delete: "; cin >> key; ht.remove(key); break;
        case 4: ht.display(); break;
        case 5: cout << "Bye!\n"; break;
        default: cout << "Invalid choice.\n";
        }
    } while (ch != 5);
    return 0;
}
