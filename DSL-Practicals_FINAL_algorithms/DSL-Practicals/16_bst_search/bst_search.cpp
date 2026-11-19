// Practical 16: Binary Search Tree
// i. Insert new node  ii. Search values  iii. Minimum data value
//
// ALGORITHM
// ---------
// Data: binary search tree, node = (data, left, right). Smaller values go left, larger go right.
//
// A. insert(node, val)  (recursive)
//    1. If node is NULL, create and return a new node with val.
//    2. If val == node->data, print "duplicate ignored" and return.
//    3. If val < node->data: node->left = insert(node->left, val).
//       Else: node->right = insert(node->right, val).
//    4. Return node.
//
// B. search(key)
//    1. Set p = root, comp = 0.
//    2. While p is not NULL:
//         a. comp = comp + 1.
//         b. If key == p->data, print FOUND with comp and stop.
//         c. If key < p->data, p = p->left; else p = p->right.
//    3. If the loop ends, print NOT found with comp.
//                                             [O(log n) for a balanced tree, O(n) worst case]
// C. findMin()
//    1. If the tree is empty, print a message and stop.
//    2. Start at the root and keep moving LEFT while a left child exists.
//    3. Print the data of the last node reached.
//
// D. display(): print Inorder (L, Root, R), Preorder (Root, L, R) and Postorder (L, R, Root).
//
// E. main(): menu (construct / insert / search / minimum / display / exit); repeat until Exit.

#include <iostream>
using namespace std;

// BST node: left subtree holds smaller values, right subtree holds larger values
struct Node {
    int data;
    Node *left, *right;
    Node(int d) : data(d), left(NULL), right(NULL) {}
};

class BST {
    Node *root;

    // Recursive insert: go left if smaller, right if larger, until an empty (NULL) place is found
    Node *insert(Node *n, int val) {
        if (!n) return new Node(val);
        if (val == n->data) { cout << "Duplicate " << val << " ignored.\n"; return n; }
        if (val < n->data) n->left = insert(n->left, val);
        else n->right = insert(n->right, val);
        return n;
    }

    // Inorder = L,Root,R (sorted order in a BST) | Preorder = Root,L,R | Postorder = L,R,Root
    void inorder(Node *n)   { if (n) { inorder(n->left); cout << n->data << " "; inorder(n->right); } }
    void preorder(Node *n)  { if (n) { cout << n->data << " "; preorder(n->left); preorder(n->right); } }
    void postorder(Node *n) { if (n) { postorder(n->left); postorder(n->right); cout << n->data << " "; } }

public:
    BST() { root = NULL; }

    void insert(int val) { root = insert(root, val); }

    // Search: smaller -> go left, larger -> go right. O(log n) for a balanced tree, O(n) worst case
    void search(int key) {
        Node *p = root;
        int comp = 0;
        while (p) {
            comp++;
            if (key == p->data) {
                cout << key << " FOUND (comparisons: " << comp << ").\n";
                return;
            }
            p = key < p->data ? p->left : p->right;
        }
        cout << key << " NOT found (comparisons: " << comp << ").\n";
    }

    void findMin() {
        if (!root) { cout << "Tree is empty.\n"; return; }
        Node *p = root;
        // Minimum = leftmost node
        while (p->left) p = p->left;
        cout << "Minimum value: " << p->data << "\n";
    }

    void display() {
        if (!root) { cout << "Tree is empty.\n"; return; }
        cout << "Inorder   : "; inorder(root);   cout << "\n";
        cout << "Preorder  : "; preorder(root);  cout << "\n";
        cout << "Postorder : "; postorder(root); cout << "\n";
    }
};

int main() {
    BST t;
    int ch, n, v;
    do {
        cout << "\n--- BST MENU ---\n1. Construct tree (enter n values)\n2. Insert new node\n"
                "3. Search value\n4. Minimum value\n5. Display traversals\n6. Exit\nChoice: ";
        cin >> ch;
        switch (ch) {
        case 1:
            cout << "How many values? "; cin >> n;
            cout << "Enter values in order:\n";
            for (int i = 0; i < n; i++) { cin >> v; t.insert(v); }
            break;
        case 2: cout << "Enter value: "; cin >> v; t.insert(v); break;
        case 3: cout << "Enter value to search: "; cin >> v; t.search(v); break;
        case 4: t.findMin(); break;
        case 5: t.display(); break;
        case 6: cout << "Bye!\n"; break;
        default: cout << "Invalid choice.\n";
        }
    } while (ch != 6);
    return 0;
}
