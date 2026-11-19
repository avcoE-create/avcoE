// Practical 3: Bubble Sort on first-year percentages + top five scores
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
