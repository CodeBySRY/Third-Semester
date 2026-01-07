#include <iostream>
using namespace std;

/*
================================================================================
                    ADJACENCY LIST - COMPLETE TUTORIAL
================================================================================

WHAT IS AN ADJACENCY LIST?
---------------------------
An adjacency list is a way to represent a GRAPH data structure.

A GRAPH consists of:
- VERTICES (also called nodes): The points/entities in the graph
- EDGES: The connections between vertices

Example Graph:
    0 --- 1
    |     |
    2 --- 3
    |
    4

This graph has:
- 5 vertices (0, 1, 2, 3, 4)
- 6 edges: (0-1), (0-2), (1-3), (2-3), (2-4)


WHY USE ADJACENCY LISTS?
-------------------------
There are two main ways to represent graphs:

1. ADJACENCY MATRIX: A 2D array where matrix[i][j] = 1 if edge exists
   - Space: O(V²) where V = number of vertices
   - Good for dense graphs (many edges)

2. ADJACENCY LIST: For each vertex, store a list of its neighbors
   - Space: O(V + E) where E = number of edges
   - Good for sparse graphs (few edges)
   - MORE COMMON and more efficient for most real-world graphs


ARRAY-BASED ADJACENCY LIST EXPLAINED
-------------------------------------
The code you showed:
    int *arr[6];          // Array of 6 pointers to int
    arr[0] = new int[2];  // Vertex 0 has 2 neighbors
    arr[1] = new int[4];  // Vertex 1 has 4 neighbors
    arr[2] = new int[3];  // Vertex 2 has 3 neighbors
    arr[3] = new int[2];  // Vertex 3 has 2 neighbors
    arr[4] = new int[3];  // Vertex 4 has 3 neighbors
    arr[5] = new int[2];  // Vertex 5 has 2 neighbors

Let's break this down:

1. int *arr[6]
   - This declares an ARRAY of 6 POINTERS
   - Each pointer will point to a dynamic array
   - arr[0] represents vertex 0
   - arr[1] represents vertex 1, etc.

2. arr[0] = new int[2]
   - Allocates a dynamic array of size 2 for vertex 0
   - This means vertex 0 has 2 neighbors
   - We'll store the neighbor vertex numbers in this array

VISUAL REPRESENTATION:
----------------------
    arr[0] --> [neighbor1][neighbor2]           (2 neighbors)
    arr[1] --> [n1][n2][n3][n4]                (4 neighbors)
    arr[2] --> [n1][n2][n3]                    (3 neighbors)
    arr[3] --> [n1][n2]                        (2 neighbors)
    arr[4] --> [n1][n2][n3]                    (3 neighbors)
    arr[5] --> [n1][n2]                        (2 neighbors)

================================================================================
*/

// Function to create and populate an adjacency list
void exampleArrayBasedAdjacencyList() {
    cout << "=== ARRAY-BASED ADJACENCY LIST EXAMPLE ===" << endl;
    cout << "\nGraph Structure:" << endl;
    cout << "    0 --- 1" << endl;
    cout << "    |     |" << endl;
    cout << "    2 --- 3" << endl;
    cout << "    |" << endl;
    cout << "    4" << endl;
    
    // Step 1: Declare array of pointers
    // We have 5 vertices (0 to 4)
    int *adjList[5];
    
    // Step 2: Determine how many neighbors each vertex has
    // Vertex 0: connects to 1, 2 (2 neighbors)
    // Vertex 1: connects to 0, 3 (2 neighbors)
    // Vertex 2: connects to 0, 3, 4 (3 neighbors)
    // Vertex 3: connects to 1, 2 (2 neighbors)
    // Vertex 4: connects to 2 (1 neighbor)
    
    // Step 3: Allocate memory for each vertex's neighbor list
    adjList[0] = new int[2];  // Vertex 0 has 2 neighbors
    adjList[1] = new int[2];  // Vertex 1 has 2 neighbors
    adjList[2] = new int[3];  // Vertex 2 has 3 neighbors
    adjList[3] = new int[2];  // Vertex 3 has 2 neighbors
    adjList[4] = new int[1];  // Vertex 4 has 1 neighbor
    
    // Step 4: Store the actual neighbors
    // Vertex 0 connects to: 1, 2
    adjList[0][0] = 1;
    adjList[0][1] = 2;
    
    // Vertex 1 connects to: 0, 3
    adjList[1][0] = 0;
    adjList[1][1] = 3;
    
    // Vertex 2 connects to: 0, 3, 4
    adjList[2][0] = 0;
    adjList[2][1] = 3;
    adjList[2][2] = 4;
    
    // Vertex 3 connects to: 1, 2
    adjList[3][0] = 1;
    adjList[3][1] = 2;
    
    // Vertex 4 connects to: 2
    adjList[4][0] = 2;
    
    // Step 5: Display the adjacency list
    cout << "\nAdjacency List Representation:" << endl;
    int sizes[] = {2, 2, 3, 2, 1};  // Size of each neighbor list
    
    for (int i = 0; i < 5; i++) {
        cout << "Vertex " << i << " -> ";
        for (int j = 0; j < sizes[i]; j++) {
            cout << adjList[i][j];
            if (j < sizes[i] - 1) cout << ", ";
        }
        cout << endl;
    }
    
    // Step 6: IMPORTANT - Free memory (prevent memory leaks)
    for (int i = 0; i < 5; i++) {
        delete[] adjList[i];
    }
    
    cout << "\n=== END OF ARRAY-BASED EXAMPLE ===" << endl;
}

/*
================================================================================
                    BETTER APPROACH: USING STRUCT
================================================================================

PROBLEM WITH ARRAY-BASED APPROACH:
-----------------------------------
1. You need to know the number of neighbors in advance
2. You need a separate array to track sizes
3. Less flexible - can't easily add/remove neighbors

SOLUTION: Use a struct to store both the neighbors and the count
*/

// Structure to represent a vertex's adjacency list
struct AdjListNode {
    int* neighbors;      // Dynamic array of neighbor vertices
    int neighborCount;   // Number of neighbors
    int capacity;        // Capacity of the array (for dynamic resizing)
    
    // Constructor to initialize
    AdjListNode() {
        neighbors = NULL;
        neighborCount = 0;
        capacity = 0;
    }
    
    // Add a neighbor to this vertex
    void addNeighbor(int vertex) {
        // If array is full, resize it
        if (neighborCount == capacity) {
            int newCapacity = (capacity == 0) ? 2 : capacity * 2;
            int* newNeighbors = new int[newCapacity];
            
            // Copy old neighbors
            for (int i = 0; i < neighborCount; i++) {
                newNeighbors[i] = neighbors[i];
            }
            
            // Free old memory and update
            delete[] neighbors;
            neighbors = newNeighbors;
            capacity = newCapacity;
        }
        
        // Add the new neighbor
        neighbors[neighborCount] = vertex;
        neighborCount++;
    }
    
    // Display this vertex's neighbors
    void display() {
        for (int i = 0; i < neighborCount; i++) {
            cout << neighbors[i];
            if (i < neighborCount - 1) cout << ", ";
        }
    }
    
    // Destructor to free memory
    ~AdjListNode() {
        delete[] neighbors;
    }
};

// Class to represent the entire graph
class Graph {
private:
    AdjListNode* adjList;  // Array of adjacency list nodes
    int numVertices;       // Number of vertices in the graph
    bool isDirected;       // Is this a directed graph?
    
public:
    // Constructor
    Graph(int vertices, bool directed = false) {
        numVertices = vertices;
        isDirected = directed;
        adjList = new AdjListNode[numVertices];
    }
    
    // Destructor
    ~Graph() {
        delete[] adjList;
    }
    
    // Add an edge between two vertices
    void addEdge(int src, int dest) {
        // Validate vertices
        if (src < 0 || src >= numVertices || dest < 0 || dest >= numVertices) {
            cout << "Invalid vertex!" << endl;
            return;
        }
        
        // Add edge from src to dest
        adjList[src].addNeighbor(dest);
        
        // If undirected, also add edge from dest to src
        if (!isDirected) {
            adjList[dest].addNeighbor(src);
        }
    }
    
    // Display the adjacency list
    void display() {
        cout << "\nGraph Adjacency List:" << endl;
        for (int i = 0; i < numVertices; i++) {
            cout << "Vertex " << i << " -> ";
            adjList[i].display();
            cout << endl;
        }
    }
    
    // Get the neighbors of a vertex (useful for graph algorithms)
    void getNeighbors(int vertex) {
        if (vertex < 0 || vertex >= numVertices) {
            cout << "Invalid vertex!" << endl;
            return;
        }
        
        cout << "Neighbors of vertex " << vertex << ": ";
        adjList[vertex].display();
        cout << endl;
    }
    
    // Get the degree of a vertex (number of neighbors)
    int getDegree(int vertex) {
        if (vertex < 0 || vertex >= numVertices) {
            return -1;
        }
        return adjList[vertex].neighborCount;
    }
};

/*
================================================================================
                    LINKED LIST APPROACH (MOST FLEXIBLE)
================================================================================

Another common way to implement adjacency lists is using LINKED LISTS
instead of dynamic arrays. This is more flexible for adding/removing edges.
*/

// Node in the linked list (represents an edge)
struct EdgeNode {
    int vertex;          // The destination vertex
    EdgeNode* next;      // Pointer to next edge
    
    EdgeNode(int v) {
        vertex = v;
        next = NULL;
    }
};

// Class for graph using linked list adjacency list
class GraphLinkedList {
private:
    EdgeNode** adjList;  // Array of pointers to edge nodes
    int numVertices;
    bool isDirected;
    
public:
    // Constructor
    GraphLinkedList(int vertices, bool directed = false) {
        numVertices = vertices;
        isDirected = directed;
        
        // Initialize array of head pointers to NULL
        adjList = new EdgeNode*[numVertices];
        for (int i = 0; i < numVertices; i++) {
            adjList[i] = NULL;
        }
    }
    
    // Destructor
    ~GraphLinkedList() {
        for (int i = 0; i < numVertices; i++) {
            EdgeNode* current = adjList[i];
            while (current != NULL) {
                EdgeNode* temp = current;
                current = current->next;
                delete temp;
            }
        }
        delete[] adjList;
    }
    
    // Add an edge
    void addEdge(int src, int dest) {
        if (src < 0 || src >= numVertices || dest < 0 || dest >= numVertices) {
            cout << "Invalid vertex!" << endl;
            return;
        }
        
        // Add edge from src to dest (insert at beginning)
        EdgeNode* newNode = new EdgeNode(dest);
        newNode->next = adjList[src];
        adjList[src] = newNode;
        
        // If undirected, add reverse edge
        if (!isDirected) {
            newNode = new EdgeNode(src);
            newNode->next = adjList[dest];
            adjList[dest] = newNode;
        }
    }
    
    // Display the adjacency list
    void display() {
        cout << "\nGraph Adjacency List (Linked List):" << endl;
        for (int i = 0; i < numVertices; i++) {
            cout << "Vertex " << i << " -> ";
            EdgeNode* current = adjList[i];
            while (current != NULL) {
                cout << current->vertex;
                if (current->next != NULL) cout << ", ";
                current = current->next;
            }
            cout << endl;
        }
    }
};

/*
================================================================================
                    MAIN FUNCTION - DEMONSTRATIONS
================================================================================
*/

int main() {
    cout << "======================================================" << endl;
    cout << "          ADJACENCY LIST TUTORIAL" << endl;
    cout << "======================================================" << endl;
    
    // Example 1: Basic array-based adjacency list
    cout << "\n\n### EXAMPLE 1: Array-Based Adjacency List ###" << endl;
    exampleArrayBasedAdjacencyList();
    
    // Example 2: Using struct-based approach
    cout << "\n\n### EXAMPLE 2: Struct-Based Adjacency List ###" << endl;
    Graph g1(5, false);  // 5 vertices, undirected
    
    // Add edges for the same graph
    g1.addEdge(0, 1);
    g1.addEdge(0, 2);
    g1.addEdge(1, 3);
    g1.addEdge(2, 3);
    g1.addEdge(2, 4);
    
    g1.display();
    
    cout << "\nVertex degrees:" << endl;
    for (int i = 0; i < 5; i++) {
        cout << "Degree of vertex " << i << ": " << g1.getDegree(i) << endl;
    }
    
    // Example 3: Directed graph
    cout << "\n\n### EXAMPLE 3: Directed Graph ###" << endl;
    cout << "Graph Structure:" << endl;
    cout << "    0 --> 1" << endl;
    cout << "    |     |" << endl;
    cout << "    v     v" << endl;
    cout << "    2 --> 3" << endl;
    cout << "    |" << endl;
    cout << "    v" << endl;
    cout << "    4" << endl;
    
    Graph g2(5, true);  // 5 vertices, directed
    g2.addEdge(0, 1);
    g2.addEdge(0, 2);
    g2.addEdge(1, 3);
    g2.addEdge(2, 3);
    g2.addEdge(2, 4);
    
    g2.display();
    
    // Example 4: Linked list approach
    cout << "\n\n### EXAMPLE 4: Linked List Adjacency List ###" << endl;
    GraphLinkedList g3(5, false);  // 5 vertices, undirected
    
    g3.addEdge(0, 1);
    g3.addEdge(0, 2);
    g3.addEdge(1, 3);
    g3.addEdge(2, 3);
    g3.addEdge(2, 4);
    
    g3.display();
    
    cout << "\n======================================================" << endl;
    cout << "              END OF TUTORIAL" << endl;
    cout << "======================================================" << endl;
    
    return 0;
}

/*
================================================================================
                    KEY TAKEAWAYS FOR YOUR EXAM
================================================================================

1. WHAT IS ADJACENCY LIST?
   - A way to represent graphs by storing neighbors for each vertex
   - Space efficient: O(V + E)

2. THREE MAIN IMPLEMENTATIONS:
   a) Array of dynamic arrays (int *arr[])
   b) Array of structs (with neighbor array + count)
   c) Array of linked lists (most flexible)

3. OPERATIONS:
   - Add edge: O(1) for all implementations
   - Check if edge exists: O(degree) - need to search through neighbors
   - Get all neighbors: O(degree)
   - Space: O(V + E)

4. WHEN TO USE:
   - Sparse graphs (few edges relative to vertices)
   - When you need to iterate through neighbors frequently
   - Most real-world graphs (social networks, maps, etc.)

5. DIRECTED vs UNDIRECTED:
   - Undirected: Add edge in both directions
   - Directed: Add edge in only one direction

6. COMMON GRAPH ALGORITHMS USING ADJACENCY LISTS:
   - BFS (Breadth-First Search)
   - DFS (Depth-First Search)
   - Dijkstra's shortest path
   - Topological sort
   - Connected components

PRACTICE PROBLEMS:
------------------
1. Given an adjacency list, count the total number of edges
2. Determine if a graph has a cycle
3. Find all vertices reachable from a given vertex
4. Convert adjacency matrix to adjacency list
5. Find the vertex with the highest degree

Good luck on your quiz and exam!
================================================================================
*/  