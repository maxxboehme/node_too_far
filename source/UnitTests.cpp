#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <utility>
#include <cstring>
#include <climits>

#include "gtest/gtest.h"

#include "prints.h"
#include "Node.h"

TEST(Node, read_graph){
   int graph[31][31];
   for(int i = 0; i < 31; ++i)
      memset(graph[i], -1, sizeof(graph[i]));
   std::unordered_map<int, int> mappingToIndex;
   std::istringstream r("10 15   15 20   20 25   10 30   30 47   47 50   25 45   45 65\n15 35   35 55   20 40   50 55   35 40   55 60   40 60   60 65\n35  2   35  3    0  0");
   std::ostringstream wM;
   std::ostringstream wA;
   read_graph(r, 16, graph, mappingToIndex);
   wM << mappingToIndex;
   ASSERT_EQ(wM.str(), "{{10 : 1}, {15 : 2}, {20 : 3}, {25 : 4}, {30 : 5}, {35 : 10}, {40 : 12}, {45 : 8}, {47 : 6}, {50 : 7}, {55 : 11}, {60 : 13}, {65 : 9}}");
   //Array2DToStream(std::cout, graph, 31);
   //ArrayToStream(wA, graph);
   //ASSERT_EQ(wA.str(), "[[], [15, 30], [10, 20, 35], [15, 25, 40], [20, 45], [10, 47], [30, 50], [47, 55], [25, 65], [45, 60], [15, 55, 40], [35, 50, 60], [20, 35, 60], [55, 40, 65], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], []]");
}


TEST(Node, read_query){
   std::unordered_map<int, std::vector<int> > graph;
   std::istringstream r("35  2   33  3   0  0\n");
   std::pair<int, int> p;
   read_query(r, p);
   ASSERT_EQ(p.first, 35);
   ASSERT_EQ(p.second, 2);

   read_query(r, p);
   ASSERT_EQ(p.first, 33);
   ASSERT_EQ(p.second, 3);

   read_query(r, p);
   ASSERT_EQ(p.first, 0);
   ASSERT_EQ(p.second, 0);
}

TEST(Node, test){
  int graph[][4] = { {0,   5,  -1, 10},
                           {-1,  0,  3,  -1},
                           {-1, -1, 0,   1},
                           {-1, -1, -1, 0} };
  //Array2DToStream(std::cout, graph, 4);
  floyd_warshall(graph, 4);
  Array2DToStream(std::cout, graph, 4);
}
/*
TEST(Node, floyd_warshall){
   unsigned int graph[31][31];
   for(int i = 0; i < 31; ++i)
      memset(graph[i], -1, sizeof(graph[i]));
   //Array2DToStream(std::cout, graph, 31);
   std::unordered_map<int, int> mappingToIndex;
   std::istringstream r("10 15   15 20   20 25   10 30   30 47   47 50   25 45   45 65\n15 35   35 55   20 40   50 55   35 40   55 60   40 60   60 65\n35  2   35  3    0  0");
   std::ostringstream wM;
   std::ostringstream wA;
   read_graph(r, 16, graph, mappingToIndex);
   Array2DToStream(std::cout, graph, 18);
   floyd_warshall(graph, mappingToIndex.size());
   std::cout << mappingToIndex << std::endl;
   Array2DToStream(std::cout, graph, 18);
}*/
/*
TEST(Node, breath_first_search){
   std::array<std::vector<int>, 31> graph;
   std::unordered_map<int, int> mappingToIndex;
   std::istringstream r("10 15   15 20   20 25   10 30   30 47   47 50   25 45   45 65\n15 35   35 55   20 40   50 55   35 40   55 60   40 60   60 65\n35  2   35  3    0  0");
   read_graph(r, 16, graph, mappingToIndex);
   int num = breath_first_search(graph, mappingToIndex, 35, 2);
   ASSERT_EQ(num, 8);
}

TEST(Node, breath_first_search_2){
   std::array<std::vector<int>, 31> graph;
   std::unordered_map<int, int> mappingToIndex;
   std::istringstream r("10 15   15 20   20 25   10 30   30 47   47 50   25 45   45 65\n15 35   35 55   20 40   50 55   35 40   55 60   40 60   60 65\n35  2   35  3    0  0");
   read_graph(r, 16, graph, mappingToIndex);
   int num = breath_first_search(graph, mappingToIndex, 35, 3);
   ASSERT_EQ(num, 12);
}

TEST(Node, breath_first_search_3){
   std::array<std::vector<int>, 31> graph;
   std::unordered_map<int, int> mappingToIndex;
   std::istringstream r("10 15   15 20   20 25   10 30   30 47   47 50   25 45   45 65\n15 35   35 55   20 40   50 55   35 40   55 60   40 60   60 65\n35  2   35  3    0  0");
   read_graph(r, 16, graph, mappingToIndex);
   int num = breath_first_search(graph, mappingToIndex, 35, 2);
   ASSERT_EQ(num, 8);
   num = breath_first_search(graph, mappingToIndex, 35, 3);
   ASSERT_EQ(num, 12);
}

TEST(Node, print_results){
   std::ostringstream w;
   print_results(w, 1 , 5, 35, 2);
   ASSERT_EQ(w.str(), "Case 1: 5 nodes not reachable from node 35 with TTL = 2.\n");
}

TEST(Node, solve){
  std::istringstream r("16\n10 15   15 20   20 25   10 30   30 47   47 50   25 45   45 65\n15 35   35 55   20 40   50 55   35 40   55 60   40 60   60 65\n35  2   35  3    0  0\n\n0\n");
  std::ostringstream w;
  node_too_far_solve(r, w);
  ASSERT_EQ(w.str(), "Case 1: 5 nodes not reachable from node 35 with TTL = 2.\nCase 2: 1 nodes not reachable from node 35 with TTL = 3.\n");
}

TEST(Node, solve_2){
  std::istringstream r("16\n"
                       "10 15   15 20   20 25   10 30   30 47   47 50   25 45   45 65\n"
                       "15 35   35 55   20 40   50 55   35 40   55 60   40 60   60 65\n"
                       "35  2   35  3    0  0\n\n"
                       "14\n"
                       "1 2   2 7   1 3   3 4   3 5   5 10   5 11\n"
                       "4 6   7 6   7 8   7 9   8 9   8  6   6 11\n"
                       "1 1   1 2   3 2   3 3   0 0\n\n"
                       "0");
  std::ostringstream w;
  node_too_far_solve(r, w);
  ASSERT_EQ(w.str(), "Case 1: 5 nodes not reachable from node 35 with TTL = 2.\n"
                     "Case 2: 1 nodes not reachable from node 35 with TTL = 3.\n"
                     "Case 3: 8 nodes not reachable from node 1 with TTL = 1.\n"
                     "Case 4: 5 nodes not reachable from node 1 with TTL = 2.\n"
                     "Case 5: 3 nodes not reachable from node 3 with TTL = 2.\n"
                     "Case 6: 1 nodes not reachable from node 3 with TTL = 3.\n");
}

TEST(Node, solve_3){
  std::istringstream r("16\n"
                       "10 15   15 20   20 25   10 30   30 47   47 50   25 45   45 65\n"
                       "15 35   35 55   20 40   50 55   35 40   55 60   40 60   60 65\n"
                       "35  2   35  0    0  0\n\n"
                       "14\n"
                       "1 2   2 7   1 3   3 4   3 5   5 10   5 11\n"
                       "4 6   7 6   7 8   7 9   8 9   8  6   6 11\n"
                       "1 1   1 2   3 2   3 3   0 0\n\n"
                       "0");
  std::ostringstream w;
  node_too_far_solve(r, w);
  ASSERT_EQ(w.str(), "Case 1: 5 nodes not reachable from node 35 with TTL = 2.\n"
                     "Case 2: 12 nodes not reachable from node 35 with TTL = 0.\n"
                     "Case 3: 8 nodes not reachable from node 1 with TTL = 1.\n"
                     "Case 4: 5 nodes not reachable from node 1 with TTL = 2.\n"
                     "Case 5: 3 nodes not reachable from node 3 with TTL = 2.\n"
                     "Case 6: 1 nodes not reachable from node 3 with TTL = 3.\n");
}

TEST(Node, solve_4){
  std::istringstream r("16\n"
                       "10 15   15 20   20 25   10 30   30 47   47 50   25 45   45 65\n"
                       "15 35   35 55   20 40   50 55   35 40   55 60   40 60   60 65\n"
                       "35  2   1  3    0  0\n\n"
                       "14\n"
                       "1 2   2 7   1 3   3 4   3 5   5 10   5 11\n"
                       "4 6   7 6   7 8   7 9   8 9   8  6   6 11\n"
                       "1 1   1 2   3 2   3 3   0 0\n\n"
                       "0");
  std::ostringstream w;
  node_too_far_solve(r, w);
  ASSERT_EQ(w.str(), "Case 1: 5 nodes not reachable from node 35 with TTL = 2.\n"
                     "Case 2: 13 nodes not reachable from node 1 with TTL = 3.\n"
                     "Case 3: 8 nodes not reachable from node 1 with TTL = 1.\n"
                     "Case 4: 5 nodes not reachable from node 1 with TTL = 2.\n"
                     "Case 5: 3 nodes not reachable from node 3 with TTL = 2.\n"
                     "Case 6: 1 nodes not reachable from node 3 with TTL = 3.\n");
}

TEST(Node, solve_5){
  std::istringstream r("16\n"
                       "10 15   15 20   20 25   10 30   30 47   47 50   25 45   45 65\n"
                       "15 35   35 55   20 40   50 55   35 40   55 60   40 60   60 65\n\n\n"
                       "35  2   35  50   0  0\n\n\n\n\n"
                       "14\n\n\n\n\n"
                       "1 2   2 7   1 3   3 4   3 5   5 10   5 11\n"
                       "4 6   7 6   7 8   7 9   8 9   8  6   6 11\n"
                       "1 1   1 2   3 2   3 3   0 0\n\n"
                       "0\n\n");
  std::ostringstream w;
  node_too_far_solve(r, w);
  ASSERT_EQ(w.str(), "Case 1: 5 nodes not reachable from node 35 with TTL = 2.\n"
                     "Case 2: 0 nodes not reachable from node 35 with TTL = 50.\n"
                     "Case 3: 8 nodes not reachable from node 1 with TTL = 1.\n"
                     "Case 4: 5 nodes not reachable from node 1 with TTL = 2.\n"
                     "Case 5: 3 nodes not reachable from node 3 with TTL = 2.\n"
                     "Case 6: 1 nodes not reachable from node 3 with TTL = 3.\n");
}

TEST(Node, solve_6){
  std::istringstream r("10\n"
                       "1 2 1 3 3 5 2 5 3 4 5 4 6 4 7 10 10 9 8 9\n"
                       "2 3 7 2 10 1 0 0\n"
                       "0");
  std::ostringstream w;
  node_too_far_solve(r, w);
  ASSERT_EQ(w.str(), "Case 1: 4 nodes not reachable from node 2 with TTL = 3.\n"
                     "Case 2: 7 nodes not reachable from node 7 with TTL = 2.\n"
                     "Case 3: 7 nodes not reachable from node 10 with TTL = 1.\n");
}*/

