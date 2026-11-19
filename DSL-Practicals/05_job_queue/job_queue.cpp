// Practical 5: Job queue (FCFS) simulation using an array (circular queue)
#include <iostream>
using namespace std;

const int SIZE = 5;

// Queue = FIFO (First In First Out): the first job added is the first one processed
class JobQueue {
    int jobs[SIZE];
    int front, rear, count;
public:
    JobQueue() { front = 0; rear = -1; count = 0; }
    // 'count' = jobs present now; it tells full from empty in a circular queue
    bool isEmpty() { return count == 0; }
    bool isFull()  { return count == SIZE; }

    // Enqueue: insert at REAR. '% SIZE' wraps rear to the start (circular queue) so freed space is reused
    void addJob(int id) {
        if (isFull()) { cout << "Queue is FULL. Cannot add job " << id << ".\n"; return; }
        rear = (rear + 1) % SIZE;
        jobs[rear] = id;
        count++;
        cout << "Job " << id << " added.\n";
    }

    // Dequeue: remove job from FRONT
    void deleteJob() {
        if (isEmpty()) { cout << "Queue is EMPTY. No job to process.\n"; return; }
        cout << "Job " << jobs[front] << " processed and removed.\n";
        front = (front + 1) % SIZE;
        count--;
    }

    void display() {
        if (isEmpty()) { cout << "Queue is EMPTY.\n"; return; }
        cout << "Job queue (front -> rear): ";
        for (int i = 0, idx = front; i < count; i++, idx = (idx + 1) % SIZE)
            cout << jobs[idx] << " ";
        cout << "\n";
    }
};

int main() {
    JobQueue q;
    int ch, id;
    do {
        cout << "\n--- MENU ---\n1. Add job\n2. Delete job\n3. Display queue\n4. Exit\nChoice: ";
        cin >> ch;
        switch (ch) {
        case 1: cout << "Enter job ID: "; cin >> id; q.addJob(id); break;
        case 2: q.deleteJob(); break;
        case 3: q.display(); break;
        case 4: cout << "Bye!\n"; break;
        default: cout << "Invalid choice.\n";
        }
    } while (ch != 4);
    return 0;
}
