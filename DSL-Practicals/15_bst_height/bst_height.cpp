// Practical 15: Binary Search Tree
// i. Insert new node  ii. Number of nodes in the longest path from root  iii. Minimum data value
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

    // number of NODES on the longest root-to-leaf path
    int longestPath(Node *n) {
        if (!n) return 0;
        // Height = 1 + larger of (left height, right height); empty tree = 0
        int l = longestPath(n->left), r = longestPath(n->right);
        return 1 + (l > r ? l : r);
    }

    // Inorder = L,Root,R (sorted order in a BST) | Preorder = Root,L,R | Postorder = L,R,Root
    void inorder(Node *n)   { if (n) { inorder(n->left); cout << n->data << " "; inorder(n->right); } }
    void preorder(Node *n)  { if (n) { cout << n->data << " "; preorder(n->left); preorder(n->right); } }
    void postorder(Node *n) { if (n) { postorder(n->left); postorder(n->right); cout << n->data << " "; } }

public:
    BST() { root = NULL; }

    void insert(int val) { root = insert(root, val); }

    void height() { cout << "Nodes in longest path from root: " << longestPath(root) << "\n"; }

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
                "3. Longest path (number of nodes)\n4. Minimum value\n5. Display traversals\n6. Exit\nChoice: ";
        cin >> ch;
        switch (ch) {
        case 1:
            cout << "How many values? "; cin >> n;
            cout << "Enter values in order:\n";
            for (int i = 0; i < n; i++) { cin >> v; t.insert(v); }
            break;
        case 2: cout << "Enter value: "; cin >> v; t.insert(v); break;
        case 3: t.height(); break;
        case 4: t.findMin(); break;
        case 5: t.display(); break;
        case 6: cout << "Bye!\n"; break;
        default: cout << "Invalid choice.\n";
        }
    } while (ch != 6);
    return 0;
}
