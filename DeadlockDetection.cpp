#include<bits/stdc++.h>
using namespace std;

class Node {
public:
    string name;
    vector<Node*> outgoing_arcs;
    bool visited;

    Node(const string& n) : name(n), visited(false) {}
};

unordered_map<string, Node*> createGraph(const vector<string>& nodes, const vector<string>& edges) {
    unordered_map<string, Node*> graph;

    for (const string& nodeName : nodes) {
        graph[nodeName] = new Node(nodeName);
    }

    for (const string& edge : edges) {
        size_t separator = edge.find(" to ");
        string sourceName = edge.substr(0, separator);
        string destName = edge.substr(separator + 4);

        graph[sourceName]->outgoing_arcs.push_back(graph[destName]);
    }

    return graph;
}

bool detectCycle(Node* currentNode, vector<Node*>& cycleNodes) {
    if (currentNode->visited) {
        cycleNodes.push_back(currentNode);
        return true;
    }

    currentNode->visited = true;
    cycleNodes.push_back(currentNode);

    for (Node* arc : currentNode->outgoing_arcs) {
        if (detectCycle(arc, cycleNodes)) {
            return true;
        }
    }

    cycleNodes.pop_back();
    return false;
}

int main() {
    vector<string> graphNodes = {"R", "A", "C", "S", "D", "T", "B", "E", "F", "U", "V", "W", "G"};
    vector<string> graphEdges = {
        "R to A", "A to S", "C to S", "D to S", "D to T", "T to E",
        "E to V", "V to G", "G to U", "U to D", "W to F", "F to S", 
        "B to T"
    };

    unordered_map<string, Node*> graph = createGraph(graphNodes, graphEdges);

    vector<Node*> cycleNodes;

    for (const auto& entry : graph) {
        if (!entry.second->visited) {
            if (detectCycle(entry.second, cycleNodes)) {
                cout << "Deadlock Detected Among nodes:";
                for (Node* node : cycleNodes) {
                    cout << " " << node->name;
                }
                cout << endl;
                break;
            }
        }
    }

    if (cycleNodes.empty()) {
        cout << "No Deadlocks Detected" << endl;
    }

    for (const auto& entry : graph) {
        delete entry.second;
    }

    return 0;
}
