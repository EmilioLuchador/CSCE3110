#include <iostream>
#include <fstream>
#include <sstream>
#include <climits>
#include <queue>
#include <stack>
#include <unordered_set>

using namespace std;

//Define a struct for linked list nodes
struct Node {
    int vertex;
    int weight;
    Node* next;
};

//Define a class for the adjacency list
class Graph {
private:
    Node** adjList;
    int V; //Number of vertices

public:
    //Constructor to create a graph by reading input from file
Graph(const string& filename) 

{
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    //Determine the number of vertices by scanning the file
    int max_vertex = 0;
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        int u, v, weight;
        if (!(iss >> u >> v >> weight)) {
            cerr << "Invalid input format in file: " << filename << endl;
            continue;
        }
        max_vertex = max(max_vertex, max(u, v));
    }
    file.clear(); //clear the file stream
    file.seekg(0); //move file pointer to the beginning

    V = max_vertex + 1; //Number of vertices
    adjList = new Node*[V];
    for (int i = 0; i < V; ++i)
        adjList[i] = nullptr;

    //Populate the adjacency list from the file
    while (getline(file, line)) {
        istringstream iss(line);
        int u, v, weight;
        if (!(iss >> u >> v >> weight)) {
            cerr << "Invalid input format in file: " << filename << endl;
            continue;
        }
        addEdge(u, v, weight);
    }
    file.close();
    }

    //Function to add an edge with weight to the graph
    void addEdge(int u, int v, int weight) {
        //Add v to the adjacency list of u
        Node* newNode = new Node();
        newNode->vertex = v;
        newNode->weight = weight;
        newNode->next = adjList[u];
        adjList[u] = newNode;

        //Add u to the adjacency list of v (if the graph is undirected)
        newNode = new Node();
        newNode->vertex = u;
        newNode->weight = weight;
        newNode->next = adjList[v];
        adjList[v] = newNode;
    }

    //Function to print the adjacency list with weights
    void printAdjList() {
        for (int i = 0; i < V; ++i) {
            cout << "Vertex " << i << " -> ";
            Node* temp = adjList[i];
            while (temp) {
                cout << "(" << temp->vertex << ", " << temp->weight << ") ";
                temp = temp->next;
            }
            cout << endl;
        }
    }

    //Depth-First Search (DFS) algorithm
    void DFS(int startVertex) {
        unordered_set<int> visited;
        stack<int> stack;
        stack.push(startVertex);

        while (!stack.empty()) {
            int currentVertex = stack.top();
            stack.pop();

            if (visited.find(currentVertex) == visited.end()) {
                cout << currentVertex << " ";
                visited.insert(currentVertex);
            }

            Node* temp = adjList[currentVertex];
            while (temp) {
                if (visited.find(temp->vertex) == visited.end()) {
                    stack.push(temp->vertex);
                }
                temp = temp->next;
            }
        }
        cout << endl;
    }

    //Breadth-First Search (BFS) algorithm
    void BFS(int startVertex) {
        unordered_set<int> visited;
        queue<int> queue;
        queue.push(startVertex);
        visited.insert(startVertex);

        while (!queue.empty()) {
            int currentVertex = queue.front();
            queue.pop();
            cout << currentVertex << " ";

            Node* temp = adjList[currentVertex];
            while (temp) {
                if (visited.find(temp->vertex) == visited.end()) {
                    queue.push(temp->vertex);
                    visited.insert(temp->vertex);
                }
                temp = temp->next;
            }
        }
        cout << endl;
    }

    //Function to find the minimum spanning tree using Prim's algorithm
    void primMST() {
        vector<int> parent(V, -1); //Array to store parent of each vertex in MST
        vector<int> key(V, INT_MAX);    //Array to store key values used to pick minimum weight edge

        unordered_set<int> inMST; //Set to track if a vertex is already included in MST

        //Priority queue to store vertices with their corresponding key values
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        //Start with vertex 0
        int src = 0;
        key[src] = 0;
        pq.push(make_pair(0, src));

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            // Add vertex u to MST
            inMST.insert(u);

            //Explores all adjacent vertices of u
            Node* temp = adjList[u];
            while (temp != nullptr) {
                int v = temp->vertex;
                int weight = temp->weight;

                //If v is not already in MST and weight of (u,v) is smaller than current key of v
                if (inMST.find(v) == inMST.end() && weight < key[v]) {
                    //Update parent and key of v
                    parent[v] = u;
                    key[v] = weight;
                    pq.push(make_pair(key[v], v));
                }

                temp = temp->next;
            }
        }

        //Prints the edges of the MST
        printMST(parent);
    }

    //Helper function to print the constructed MST stored in parent array
    void printMST(const vector<int>& parent) {
        cout << "Minimum Spanning Tree (MST) Edges:" << endl;
        for (int i = 1; i < V; ++i)
            cout << "Edge: " << parent[i] << " - " << i << endl;
    }

    //Destructor to free dynamically allocated memory
    ~Graph() {
        for (int i = 0; i < V; ++i) {
            Node* temp = adjList[i];
            while (temp) {
                Node* prev = temp;
                temp = temp->next;
                delete prev;
            }
        }
        delete[] adjList;
    }

    
};

int main() {
    //Create a graph by reading input from file
    Graph graph("input.txt");

    //Print adjacency list with weights
    cout << "Adjacency List:" << endl;
    graph.printAdjList();

    //Find and print the minimum spanning tree (MST)
    graph.primMST();

    //Perform Depth-First Search (DFS) starting from vertex 0
    cout << "Depth-First Search (DFS): ";
    graph.DFS(0);

    //Perform Breadth-First Search (BFS) starting from vertex 0
    cout << "Breadth-First Search (BFS): ";
    graph.BFS(0);

    return 0;
}