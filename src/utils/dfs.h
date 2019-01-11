#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <set>
#include <vector>

// TODO: add support for different types of vertex
/*
 * Graph class represents a directed graph
 * using adjacency list representation
 * source:
 * https://www.geeksforgeeks.org/depth-first-search-or-dfs-for-a-graph/
 * modified to support caching the result of last search.
 */
class Graph {
  // No. of vertices
  int V;

  // Pointer to an array containing adjacency lists
  std::list<int> *adj;
  std::vector<int> resultVector;
  std::set<int> visitedNodes;

  // A recursive function used by DFS
  void DFSUtil(int, bool[]);

public:
  // Constructor
  Graph(int V);

  // function to add an edge to graph
  void addEdge(int, int);

  // DFS traversal of the vertices
  // reachable from v
  void DFS(int);

  std::vector<int> *getResultList();
};

#endif
