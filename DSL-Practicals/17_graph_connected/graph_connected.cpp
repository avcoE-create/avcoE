// Practical 17: Flight paths between cities as a graph (adjacency list)
// Undirected weighted graph: vertex = city, edge = flight, weight = cost (e.g. flight time in hours).
// Check whether the graph is connected using DFS.
#include <iostream>
#include <string>
using namespace std;

const int MAXC = 20;

// Adjacency-list node: destination city + cost + next flight of the same city
struct Edge {
    int to;
    float cost;
    Edge *next;
    Edge(int t, float c) : to(t), cost(c), next(NULL) {}
};

class FlightGraph {
    string city[MAXC];
    // adj[i] = linked list of all flights from city i
    Edge *adj[MAXC];
    int n;

    int find(const string &name) {
        for (int i = 0; i < n; i++) if (city[i] == name) return i;
        return -1;
    }

    void addEdge(int u, int v, float cost) {   // insert at front of list
        Edge *e = new Edge(v, cost);
        e->next = adj[u];
        adj[u] = e;
    }

    // DFS: mark the city visited, then visit every unvisited neighbour recursively
    void dfs(int u, bool visited[]) {
        visited[u] = true;
        for (Edge *e = adj[u]; e; e = e->next)
            if (!visited[e->to]) dfs(e->to, visited);
    }

public:
    FlightGraph() { n = 0; for (int i = 0; i < MAXC; i++) adj[i] = NULL; }

    void addCity(string name) {
        if (n == MAXC) { cout << "Maximum cities reached.\n"; return; }
        if (find(name) != -1) { cout << name << " already exists.\n"; return; }
        city[n++] = name;
        cout << name << " added.\n";
    }

    void addFlight(string a, string b, float cost) {
        int u = find(a), v = find(b);
        if (u == -1 || v == -1) { cout << "Both cities must be added first.\n"; return; }
        if (u == v) { cout << "A flight needs two different cities.\n"; return; }
        for (Edge *e = adj[u]; e; e = e->next)
            if (e->to == v) { cout << "Flight already exists.\n"; return; }
        addEdge(u, v, cost);
        addEdge(v, u, cost);   // flights go both ways
        cout << "Flight " << a << " <-> " << b << " (cost " << cost << ") added.\n";
    }

    void display() {
        if (n == 0) { cout << "No cities.\n"; return; }
        cout << "\nAdjacency list:\n";
        for (int i = 0; i < n; i++) {
            cout << city[i] << " : ";
            for (Edge *e = adj[i]; e; e = e->next)
                cout << city[e->to] << "(" << e->cost << ") -> ";
            cout << "NULL\n";
        }
    }

    // Graph is connected if DFS from one city reaches ALL cities
    void checkConnected() {
        if (n == 0) { cout << "Graph is empty.\n"; return; }
        bool visited[MAXC] = {false};
        // Start DFS from the first city
        dfs(0, visited);
        bool all = true;
        cout << "Cities not reachable from " << city[0] << ": ";
        bool any = false;
        for (int i = 0; i < n; i++)
            if (!visited[i]) { cout << city[i] << " "; all = false; any = true; }
        if (!any) cout << "none";
        cout << "\n";
        cout << (all ? "The graph is CONNECTED.\n" : "The graph is NOT connected.\n");
    }
};

int main() {
    FlightGraph g;
    int ch;
    string a, b;
    float cost;
    do {
        cout << "\n--- FLIGHT GRAPH ---\n1. Add city\n2. Add flight\n3. Display graph\n"
                "4. Check if connected\n5. Exit\nChoice: ";
        cin >> ch;
        switch (ch) {
        case 1: cout << "City name: "; cin >> a; g.addCity(a); break;
        case 2:
            cout << "From city: "; cin >> a;
            cout << "To city: "; cin >> b;
            cout << "Cost (time/fuel): "; cin >> cost;
            g.addFlight(a, b, cost);
            break;
        case 3: g.display(); break;
        case 4: g.checkConnected(); break;
        case 5: cout << "Bye!\n"; break;
        default: cout << "Invalid choice.\n";
        }
    } while (ch != 5);
    return 0;
}
