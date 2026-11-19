// Practical 2: Selection Sort on first-year percentages + top five scores
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
