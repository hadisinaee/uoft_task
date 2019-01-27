//
// Created by Hadi Sinaee on 2019-01-18.
//

#include "gtest/gtest.h"
#include "../src/utils/dfs.cpp"

TEST(DFS_Tests, one_node_dfs) {
    // creating a graph, G(V,E), where:
    // V = {0,1,2,3}
    // E = {(0, 1), (0, 2), (1, 2), (2, 0), (2, 3), (3, 3)}
    int V = 4;

    Graph g(V);

    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);

    // DFS from node 2
    g.DFS(2);

    // check the result of DFS
    auto resultVector = g.getResultList();
    int expectedOutput[] = {2, 0, 1, 3};

    int idx = 0;
    for (auto it = resultVector->begin(); it != resultVector->end(); it++, idx++) {
        EXPECT_EQ(*it, expectedOutput[idx]);
    }
}

TEST(DFS_Tests, two_nodes_dfs) {
    // creating a graph, G(V,E), where:
    // V = {0,1,2,3}
    // E = {(0, 1), (0, 2), (1, 2), (2, 0), (2, 3), (3, 3)}
    int V = 4;

    Graph g(V);

    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);

    // DFS from node 2 and 0
    g.DFS(2);
    g.DFS(0);

    // check the result of DFS, it has to be the same as the previous one
    auto resultVector = g.getResultList();
    int expectedOutput[] = {2, 0, 1, 3};

    int idx = 0;
    for (auto it = resultVector->begin(); it != resultVector->end(); it++, idx++) {
        EXPECT_EQ(*it, expectedOutput[idx]);
    }

}