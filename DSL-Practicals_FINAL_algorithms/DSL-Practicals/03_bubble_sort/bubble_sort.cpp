// Practical 3: Bubble Sort on first-year percentages + top five scores
//
// ALGORITHM
// ---------
// Input : n first-year percentages
// Output: sorted (ascending) array and the top five scores
//
// A. Bubble Sort
//    1. For i = 0 to n-2 (one pass per iteration):
//         a. Set swapped = false.
//         b. For j = 0 to n-i-2 (last i elements are already in place):
//              if a[j] > a[j+1], swap them and set swapped = true.
//         c. If swapped is still false, the array is sorted -> stop early.
//    2. After each pass the largest remaining value has moved to the end.
//                                             [Worst case O(n^2), best case O(n)]
// B. Top Five Scores
//    1. The array is ascending, so the highest scores are at the END.
//    2. count = min(n, 5).
//    3. For i = 0 to count-1: print a[n-1-i].
//
// C. main(): read n, allocate array, read percentages, display original,
//    sort, display sorted, print top five, free the array.

#include <iostream>
using namespace std;

// Bubble sort: compare neighbours and swap if out of order; the largest value 'bubbles' to the end each pass.
// Worst case O(n^2), best case O(n) because of the swapped flag.
void bubbleSort(float a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        // Flag to detect whether any swap happened in this pass
        bool swapped = false;
        // Last i elements are already in place, so skip them
        for (int j = 0; j < n - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                float t = a[j]; a[j] = a[j + 1]; a[j + 1] = t;
                swapped = true;
            }
        }
        // No swap in a full pass means array is sorted -> stop early
        if (!swapped) break;   // already sorted
    }
}

void display(float a[], int n) {
    for (int i = 0; i < n; i++) cout << a[i] << " ";
    cout << "\n";
}

// Array is ascending, so the highest scores are at the END -> print from last index backwards
void topFive(float a[], int n) {
    int count = n < 5 ? n : 5;
    cout << "Top " << count << " scores:\n";
    for (int i = 0; i < count; i++)
        cout << i + 1 << ". " << a[n - 1 - i] << "%\n";
}

int main() {
    int n;
    cout << "Enter number of students: ";
    cin >> n;
    float *p = new float[n];
    cout << "Enter first-year percentages:\n";
    for (int i = 0; i < n; i++) cin >> p[i];

    cout << "\nOriginal array: "; display(p, n);
    bubbleSort(p, n);
    cout << "Sorted (ascending): "; display(p, n);
    topFive(p, n);
    delete[] p;
    return 0;
}
