// Practical 2: Selection Sort on first-year percentages + top five scores
//
// ALGORITHM
// ---------
// Input : n first-year percentages
// Output: sorted (ascending) array and the top five scores
//
// A. Selection Sort
//    1. For i = 0 to n-2:
//         a. Assume the first unsorted element is the smallest: minIdx = i.
//         b. For j = i+1 to n-1:
//              if a[j] < a[minIdx], set minIdx = j.
//         c. If minIdx != i, swap a[i] and a[minIdx].
//    2. After pass i, the first i+1 elements are in their final place.
//                                             [n(n-1)/2 comparisons -> O(n^2), one swap per pass]
// B. Top Five Scores
//    1. The array is ascending, so the highest scores are at the END.
//    2. count = min(n, 5).
//    3. For i = 0 to count-1: print a[n-1-i].
//
// C. main(): read n, allocate array, read percentages, display original,
//    sort, display sorted, print top five, free the array.

#include <iostream>
using namespace std;

// Selection sort: pick the smallest element of the unsorted part and swap it to the front.
// Always n(n-1)/2 comparisons -> O(n^2). Only one swap per pass.
void selectionSort(float a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        // Assume the first unsorted element is the smallest
        int minIdx = i;
        for (int j = i + 1; j < n; j++)
            // Found a smaller element -> remember its index
            if (a[j] < a[minIdx]) minIdx = j;
        // Swap the smallest element into position i
        if (minIdx != i) {
            float t = a[i]; a[i] = a[minIdx]; a[minIdx] = t;
        }
    }
}

void display(float a[], int n) {
    for (int i = 0; i < n; i++) cout << a[i] << " ";
    cout << "\n";
}

// Array is ascending, so the highest scores are at the END -> print from last index backwards
void topFive(float a[], int n) {   // array must be sorted ascending
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
    selectionSort(p, n);
    cout << "Sorted (ascending): "; display(p, n);
    topFive(p, n);
    delete[] p;
    return 0;
}
