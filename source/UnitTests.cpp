#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <utility>

#include "gtest/gtest.h"

#include "prints.h"
#include "Node.h"

TEST(Node, read_graph){
   std::unordered_map<int, std::vector<int> > graph;
   std::istringstream r("10 15   15 20   20 25   10 30   30 47   47 50   25 45   45 65\n15 35   35 55   20 40   50 55   35 40   55 60   40 60   60 65\n");
   std::ostringstream w;
   read_graph(r, 16, graph);
   w << graph;
   ASSERT_EQ("{{10 : [15, 30]}, {15 : [10, 20, 35]}, {20 : [15, 25, 40]}, {25 : [20, 45]}, {30 : [10, 47]}, {35 : [15, 55, 40]}, {40 : [20, 35, 60]}, {45 : [25, 65]}, {47 : [30, 50]}, {50 : [47, 55]}, {55 : [35, 50, 60]}, {60 : [55, 40, 65]}, {65 : [45, 60]}}", w.str());
   ASSERT_EQ(graph.size(), 13);
}

TEST(Node, read_graph_2){
   std::unordered_map<int, std::vector<int> > graph;
   std::istringstream r("10 15   15 20   20 25   10 30   30 47   47 50   25 45   45 65\n15 35   35 55   20 40   50 55   35 40   55 60   40 60   60 65\n35  2   35  3    0  0");
   std::ostringstream w;
   read_graph(r, 16, graph);
   w << graph;
   ASSERT_EQ("{{10 : [15, 30]}, {15 : [10, 20, 35]}, {20 : [15, 25, 40]}, {25 : [20, 45]}, {30 : [10, 47]}, {35 : [15, 55, 40]}, {40 : [20, 35, 60]}, {45 : [25, 65]}, {47 : [30, 50]}, {50 : [47, 55]}, {55 : [35, 50, 60]}, {60 : [55, 40, 65]}, {65 : [45, 60]}}", w.str());
   ASSERT_EQ(graph.size(), 13);
}

TEST(Node, read_graph2){
   std::unordered_map<int, std::vector<int> > graph;
   std::istringstream r("10 15   15 20   20 25   10 30   30 47   47 50   25 45   45 65\n15 35   35 55   20 40   50 55   35 40   55 60   40 60   60 65\n");
   std::ostringstream w;
   read_graph2(r, 16, graph);
   w << graph;
   ASSERT_EQ("{{10 : [15, 30]}, {15 : [10, 20, 35]}, {20 : [15, 25, 40]}, {25 : [20, 45]}, {30 : [10, 47]}, {35 : [15, 55, 40]}, {40 : [20, 35, 60]}, {45 : [25, 65]}, {47 : [30, 50]}, {50 : [47, 55]}, {55 : [35, 50, 60]}, {60 : [55, 40, 65]}, {65 : [45, 60]}}", w.str());
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

TEST(Node, breath_first_search){
   std::unordered_map<int, std::vector<int> > graph;
   std::istringstream r("10 15   15 20   20 25   10 30   30 47   47 50   25 45   45 65\n15 35   35 55   20 40   50 55   35 40   55 60   40 60   60 65\n");
   std::ostringstream w;
   read_graph(r, 16, graph);
   int num = breath_first_search(graph, 35, 2);
   ASSERT_EQ(num, 8);
}

TEST(Node, breath_first_search_2){
   std::unordered_map<int, std::vector<int> > graph;
   std::istringstream r("10 15   15 20   20 25   10 30   30 47   47 50   25 45   45 65\n15 35   35 55   20 40   50 55   35 40   55 60   40 60   60 65\n");
   std::ostringstream w;
   read_graph(r, 16, graph);
   int num = breath_first_search(graph, 35, 3);
   ASSERT_EQ(num, 12);
}

TEST(Node, breath_first_search_3){
   std::unordered_map<int, std::vector<int> > graph;
   std::istringstream r("10 15   15 20   20 25   10 30   30 47   47 50   25 45   45 65\n15 35   35 55   20 40   50 55   35 40   55 60   40 60   60 65\n");
   std::ostringstream w;
   read_graph(r, 16, graph);
   int num = breath_first_search(graph, 35, 2);
   ASSERT_EQ(num, 8);
   num = breath_first_search(graph, 35, 3);
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

