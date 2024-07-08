#include <iostream>
#include <vector>
#include <map>
#include <cmath>

using namespace std;

const int MAX_NODES = 10; // Maximum number of nodes in the Chord ring

// Define a structure for Chord Node
struct ChordNode {
    int id;
    map<int, string> data; // Data stored at this node
    ChordNode* successor;
    ChordNode* predecessor;

    ChordNode(int _id) : id(_id), successor(nullptr), predecessor(nullptr) {}

    // Function to print node information
    void printInfo() {
        cout << "Node ID: " << id << endl;
        cout << "Successor ID: " << (successor ? successor->id : -1) << endl;
        cout << "Predecessor ID: " << (predecessor ? predecessor->id : -1) << endl;

        // Print data stored at the node
        if (!data.empty()) {
            cout << "Data stored at this node:" << endl;
            for (const auto& entry : data) {
                cout << "  Key: " << entry.first << ", Value: " << entry.second << endl;
            }
        } else {
            cout << "No data stored at this node." << endl;
        }
    }
};

// Define a class for the Chord DHT
class ChordDHT {
private:
    vector<ChordNode*> nodes; // Vector to store Chord nodes

public:
    // Function to create the Chord ring with specified number of nodes
    void createChordRing(int num_nodes) {
        // Create nodes and assign identifiers
        for (int i = 0; i < num_nodes; ++i) {
            ChordNode* node = new ChordNode(i);
            nodes.push_back(node);
        }

        // Join nodes to form the ring
        for (int i = 0; i < num_nodes; ++i) {
            nodes[i]->successor = nodes[(i + 1) % num_nodes];
            nodes[i]->predecessor = nodes[(i + num_nodes - 1) % num_nodes];
        }
    }

    // Function to add a new node to the Chord ring
    void addNode() {
        if (nodes.size() >= MAX_NODES) {
            cout << "Maximum number of nodes reached." << endl;
            return;
        }

        ChordNode* new_node = new ChordNode(nodes.size());
        new_node->successor = nodes[0];
        new_node->predecessor = nodes.back();
        nodes.push_back(new_node);
    }

    // Function to remove a node from the Chord ring
    void removeNode(int node_id) {
        if (node_id < 0 || node_id >= nodes.size()) {
            cout << "Invalid node ID." << endl;
            return;
        }

        delete nodes[node_id];
        nodes.erase(nodes.begin() + node_id);
    }

    // Function to print information of all nodes in the Chord ring
    void printAllNodeInfo() {
        cout << "Node Information:" << endl;
        for (const auto& node : nodes) {
            node->printInfo();
            cout << endl;
        }
    }

    // Destructor to clean up allocated memory
    ~ChordDHT() {
        for (auto& node : nodes) {
            delete node;
        }
    }
};

int main() {
    // Create a Chord DHT with 5 nodes
    ChordDHT dht;
    dht.createChordRing(5);

    // Add a new node to the Chord ring
    dht.addNode();

    // Remove a node from the Chord ring
    dht.removeNode(2);

    // Print information of all nodes in the Chord DHT
    dht.printAllNodeInfo();

    return 0;
}
