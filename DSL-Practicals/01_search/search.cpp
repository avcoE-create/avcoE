// Practical 1: Linear & Binary Search on roll numbers with comparison count
#include <iostream>
#include <algorithm>
using namespace std;

const int MAX = 100;

// Linear search: check elements one by one. Works on unsorted data. Worst case n comparisons -> O(n)
int linearSearch(int a[], int n, int key, int &comp) {
    comp = 0;
    for (int i = 0; i < n; i++) {
        // Count every comparison (this is how we analyse the algorithm)
        comp++;
        if (a[i] == key) return i;
    }
    return -1;
}

// Binary search: needs a SORTED array. Compare with middle, discard half each time.
// Worst case about log2(n) comparisons -> O(log n)
int binarySearch(int a[], int n, int key, int &comp) {
    int lo = 0, hi = n - 1;
    comp = 0;
    while (lo <= hi) {
        // Middle element of the current range
        int mid = (lo + hi) / 2;
        comp++;
        if (a[mid] == key) return mid;
        // Key is smaller -> search the left half
        else if (key < a[mid]) hi = mid - 1;
        // Key is bigger -> search the right half
        else lo = mid + 1;
    }
    return -1;
}

void display(int a[], int n) {
    if (n == 0) { cout << "No records.\n"; return; }
    for (int i = 0; i < n; i++) cout << a[i] << " ";
    cout << "\n";
}

int main() {
    int roll[MAX], n = 0, ch;
    do {
        cout << "\n--- MENU ---\n1. Enter roll numbers\n2. Display\n"
                "3. Linear Search\n4. Binary Search\n5. Exit\nChoice: ";
        cin >> ch;
        switch (ch) {
        case 1:
            cout << "How many students attended? ";
            cin >> n;
            if (n > MAX) n = MAX;
            cout << "Enter roll numbers (random order):\n";
            for (int i = 0; i < n; i++) cin >> roll[i];
            break;
        case 2:
            display(roll, n);
            break;
        case 3: {
            int key, comp;
            cout << "Enter roll no to search: ";
            cin >> key;
            int pos = linearSearch(roll, n, key, comp);
            if (pos != -1) cout << "Student attended (index " << pos << ").\n";
            else cout << "Student did NOT attend.\n";
            cout << "Total comparisons (Linear): " << comp << "\n";
            break;
        }
        case 4: {
            int key, comp, sorted_arr[MAX];
            copy(roll, roll + n, sorted_arr);
            // Binary search needs sorted data, so sort a COPY (original order stays unchanged)
            sort(sorted_arr, sorted_arr + n);   // binary search requires sorted data
            cout << "Sorted array: ";
            display(sorted_arr, n);
            cout << "Enter roll no to search: ";
            cin >> key;
            int pos = binarySearch(sorted_arr, n, key, comp);
            if (pos != -1) cout << "Student attended (index " << pos << " in sorted array).\n";
            else cout << "Student did NOT attend.\n";
            cout << "Total comparisons (Binary): " << comp << "\n";
            break;
        }
        case 5: cout << "Bye!\n"; break;
        default: cout << "Invalid choice.\n";
        }
    } while (ch != 5);
    return 0;
}
