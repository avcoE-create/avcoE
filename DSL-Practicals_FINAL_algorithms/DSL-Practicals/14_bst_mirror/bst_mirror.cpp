// Practical 14: Binary Search Tree
// i. Insert new node  ii. Minimum data value  iii. Mirror the tree (swap left/right at every node)
// Note: after mirroring, the ordering of the tree is reversed. A 'mirrored' flag keeps
// insert and minimum correct afterwards (min becomes the rightmost node).
//
// ALGORITHM
// ---------
// Data: binary search tree, node = (data, left, right). Smaller values go left, larger go right.
//       A 'mirrored' flag (initially false) records whether the tree has been mirrored.
//
// A. insert(node, val)  (recursive)
//    1. If node is NULL, create and return a new node with val.
//    2. If val == node->data, print "duplicate ignored" and return.
//    3. If val goes left (val < data, or val > data when mirrored): node->left = insert(node->left, val).
//       Else: node->right = insert(node->right, val).
//    4. Return node.
//
// B. findMin()
//    1. If the tree is empty, print a message and stop.
//    2. Start at the root. If not mirrored, keep moving LEFT while a left child exists;
//       if mirrored, keep moving RIGHT while a right child exists.
//    3. Print the data of the node reached.
//
// C. mirror()
//    1. swapChildren(root):
//         a. If node is NULL, return.
//         b. Swap node->left and node->right.
//         c. swapChildren(node->left) and swapChildren(node->right).
//    2. Toggle the mirrored flag.
//
// D. display(): print Inorder (L, Root, R), Preorder (Root, L, R) and Postorder (L, R, Root).
//
// E. main(): menu (construct / insert / minimum / mirror / display / exit); repeat until Exit.

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
    // Remembers whether tree is mirrored (so insert and minimum still work correctly)
    bool mirrored;

    // smaller values go left normally, right when mirrored
    bool goLeft(int val, int nodeVal) { return mirrored ? val > nodeVal : val < nodeVal; }

    // Recursive insert: go left if smaller, right if larger, until an empty (NULL) place is found
    Node *insert(Node *n, int val) {
        if (!n) return new Node(val);
        if (val == n->data) { cout << "Duplicate " << val << " ignored.\n"; return n; }
        if (goLeft(val, n->data)) n->left = insert(n->left, val);
        else n->right = insert(n->right, val);
        return n;
    }

    // Mirror: swap left and right child of EVERY node (done recursively)
    void swapChildren(Node *n) {
        if (!n) return;
        Node *t = n->left; n->left = n->right; n->right = t;
        swapChildren(n->left);
        swapChildren(n->right);
    }

    // Inorder = L,Root,R (sorted order in a BST) | Preorder = Root,L,R | Postorder = L,R,Root
    void inorder(Node *n)   { if (n) { inorder(n->left); cout << n->data << " "; inorder(n->right); } }
    void preorder(Node *n)  { if (n) { cout << n->data << " "; preorder(n->left); preorder(n->right); } }
    void postorder(Node *n) { if (n) { postorder(n->left); postorder(n->right); cout << n->data << " "; } }

public:
    BST() { root = NULL; mirrored = false; }

    void insert(int val) { root = insert(root, val); }

    void findMin() {
        if (!root) { cout << "Tree is empty.\n"; return; }
        Node *p = root;
        // Minimum = leftmost node (rightmost node after mirroring)
        if (!mirrored) while (p->left) p = p->left;
        else           while (p->right) p = p->right;
        cout << "Minimum value: " << p->data << "\n";
    }

    void mirror() {
        swapChildren(root);
        mirrored = !mirrored;
        cout << "Tree mirrored.\n";
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
                "3. Minimum value\n4. Mirror the tree\n5. Display traversals\n6. Exit\nChoice: ";
        cin >> ch;
        switch (ch) {
        case 1:
            cout << "How many values? "; cin >> n;
            cout << "Enter values in order:\n";
            for (int i = 0; i < n; i++) { cin >> v; t.insert(v); }
            break;
        case 2: cout << "Enter value: "; cin >> v; t.insert(v); break;
        case 3: t.findMin(); break;
        case 4: t.mirror(); break;
        case 5: t.display(); break;
        case 6: cout << "Bye!\n"; break;
        default: cout << "Invalid choice.\n";
        }
    } while (ch != 6);
    return 0;
}
