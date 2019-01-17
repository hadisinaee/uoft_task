#include "dfs.h"
#include <iostream>
#include <list>

Graph::Graph(int V) {
  this->V = V;
  adj = new std::list<int>[V];
}

void Graph::addEdge(int v, int w) {
  adj[v].push_back(w); // Add w to v’s list.
}

void Graph::DFSUtil(int v, bool visited[]) {
  // Mark the current node as visited and add it the result vector
  visited[v] = true;

  // v is the parent of all the following direct nodes
  const int parent = v;

  // add v, the visited node, to the result vector, filtering duplicate items
  if (visitedNodes.count(v) == 0) {
    // v dosen't exist in the vector
    this->resultVector.push_back(v);
    this->visitedNodes.insert(v);
  }

  // Recur for all the vertices adjacent
  // to this vertex
  std::list<int>::iterator i;
  for (i = adj[v].begin(); i != adj[v].end(); ++i) {
    this->spanTree[*i].insert(parent);
    if (!visited[*i])
      DFSUtil(*i, visited);
  }
}

// DFS traversal of the vertices reachable from v.
// It uses recursive DFSUtil()
void Graph::DFS(int v) {
  // Mark all the vertices as not visited
  bool *visited = new bool[V];
  for (int i = 0; i < V; i++)
    visited[i] = false;

  // Call the recursive helper function
  // to print DFS traversal
  DFSUtil(v, visited);
}

std::vector<int> *Graph::getResultList() { return &this->resultVector; }

std::set<int> Graph::getParentOf(const int child) { return spanTree[child]; }
