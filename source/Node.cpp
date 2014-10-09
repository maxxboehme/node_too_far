#include <iostream>
#include <vector>
#include <unordered_map>
#include <utility>
#include <unordered_set>
#include <queue>

#include "prints.h"

void read_graph(std::istream& in, int numberOfPairs, std::unordered_map<int, std::vector<int> >& graph){
   int node1;
   int node2;
   while(--numberOfPairs >= 0 && in >> node1 >> node2){
      //std::cout << node1 << " " << node2 << std::endl;
      std::unordered_map<int, std::vector<int> >::iterator got = graph.find(node1);
      if(got == graph.end()){
          std::vector<int> temp;
          temp.push_back(node2);
          graph.emplace(node1, temp);
      } else {
         std::vector<int>& children = got->second;
         children.push_back(node2);
         //std::cout << children << std::endl;
      }
      got = graph.find(node2);
      if(got == graph.end()){
         std::vector<int> temp;
         temp.push_back(node1);
         graph.emplace(node2, temp);
      } else {
         std::vector<int>& children = got->second;
         children.push_back(node1);
        // std::cout << children << std::endl;
      }

   }
}

void read_graph2(std::istream& in, int numberOfPairs, std::unordered_map<int, std::vector<int> >& graph){
   int node1;
   int node2;
   while(--numberOfPairs >= 0 && in >> node1 >> node2){
      graph[node1].push_back(node2);
      graph[node2].push_back(node1);
   }
}

bool read_query(std::istream& in, std::pair<int, int>& pair){
   in >> pair.first >> pair.second;
   if(pair.first || pair.second){
     return true;
   } else {
      return false;
   }
}

void print_results(std::ostream& out, int caseNumber, int numberNotReachable, int startingNode, int ttl){
   out << "Case " << caseNumber << ": " << numberNotReachable << " nodes not reachable from node " << startingNode << " with TTL = " << ttl << "." << std::endl;
}

int breath_first_search(std::unordered_map<int, std::vector<int> >& graph, int start, int ttl){
   std::unordered_set<int> visited;
   std::unordered_map<int, int> cost;
   
   std::queue<int> fringe;
   fringe.push(start);
   cost[start] = 0;
   int reachable = 0;
   while(!fringe.empty()){
      int node = fringe.front();
      fringe.pop();
      if(visited.find(node) == visited.end()){
         visited.insert(node);
         ++reachable;
         if((ttl - cost[node]) > 0){
            std::vector<int> children = graph[node];
            for(int child: children){
               if(visited.find(child) == visited.end()){
                  cost[child] = cost[node] + 1;
                  fringe.push(child);
               }
            }
         }
      }
   }
   return reachable;
}


void node_too_far_solve(std::istream& in, std::ostream& out){
   int numberOfPairs = 0;
   int caseNumber = 0;
   
   in >> numberOfPairs;
   while(numberOfPairs){
      //std::cout << "Number of Pairs: " << numberOfPairs << std::endl;
      std::unordered_map<int, std::vector<int> > graph;
      read_graph2(in, numberOfPairs, graph);
      int graphSize = graph.size();
      //std::cout << "graph size: " << graphSize << std::endl;
      std::pair<int, int> p;
      while(read_query(in, p)){
          //std::cout << "Node: " << p.first << " ttl: " << p.second << std::endl;
          int result = breath_first_search(graph, p.first, p.second);
          print_results(out, ++caseNumber, graphSize - result, p.first, p.second);
      }
      in >> numberOfPairs;
   }
}
