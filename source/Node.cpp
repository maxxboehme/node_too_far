#include <iostream>
#include <vector>
#include <unordered_map>
#include <utility>
#include <unordered_set>
#include <queue>
#include <array>
#include <cstring>

#include "prints.h"

inline void read_graph(std::istream& in, int numberOfPairs, std::array<std::vector<int>, 30>& graph, std::unordered_map<int, int>& mapToIndex){
   int node1;
   int node2;

   int index = 0;
   while(--numberOfPairs >= 0 && in >> node1 >> node2){
      if(mapToIndex.find(node1) == mapToIndex.end()) {
         mapToIndex[node1] = index++;
      }
      if(mapToIndex.find(node2) == mapToIndex.end()) {
         mapToIndex[node2] = index++;
      }
      graph[mapToIndex[node1]].push_back(mapToIndex[node2]);
      graph[mapToIndex[node2]].push_back(mapToIndex[node1]);
   }
}

inline bool read_query(std::istream& in, std::pair<int, int>& pair){
   in >> pair.first >> pair.second;
   if(pair.first || pair.second){
     return true;
   } else {
      return false;
   }
}

inline void print_results(std::ostream& out, int caseNumber, int numberNotReachable, int startingNode, int ttl){
   out << "Case " << caseNumber << ": " << numberNotReachable << " nodes not reachable from node " << startingNode << " with TTL = " << ttl << "." << std::endl;
}

inline int breath_first_search(std::array<std::vector<int>, 30>& graph, std::unordered_map<int, int>& mappingToIndex, int start, int ttl){
   if(mappingToIndex.find(start) == mappingToIndex.end())
      return 0;
   int cost[30];
   memset (cost, -1, sizeof (cost));
   
   std::queue<int> fringe;
   fringe.push(mappingToIndex[start]);

   cost[mappingToIndex[start]] = 0;
   int reachable = 0;
   while(!fringe.empty()){
      int node = fringe.front();
      fringe.pop();
      ++reachable;
      if((ttl - cost[node]) > 0){
         for(int child: graph[node]){
            if(cost[child] == -1){
               cost[child] = cost[node] + 1;
               fringe.push(child);
            }
         }
      }
   }
   return reachable;
}


void node_too_far_solve(std::istream& in, std::ostream& out){
   // turn off synchronization with C I/O
   std::ios_base::sync_with_stdio(false);
   
   int numberOfPairs = 0;
   int caseNumber = 0;
   
   while(in >> numberOfPairs && numberOfPairs){
      std::array<std::vector<int>, 30> graph;
      std::unordered_map<int, int> mappingToIndex;
      read_graph(in, numberOfPairs, graph, mappingToIndex);
      int graphSize = mappingToIndex.size();
      std::pair<int, int> p;
      while(read_query(in, p)){
          int result = breath_first_search(graph, mappingToIndex, p.first, p.second);
          print_results(out, ++caseNumber, graphSize - result, p.first, p.second);
      }
   }
}


// Was surprisingly no faster then just using the inline functions.
void all_in_on_node_too_far_solve(std::istream& in, std::ostream& out){
   // turn off synchronization with C I/O
   std::ios_base::sync_with_stdio(false);
   
   int numberOfPairs = 0;
   int caseNumber = 0;
   
   while(in >> numberOfPairs && numberOfPairs){
      std::array<std::vector<int>, 30> graph;
      std::unordered_map<int, int> mappingToIndex;

      int node1;
      int node2;

      int index = 0;
      while(--numberOfPairs >= 0 && in >> node1 >> node2){
         if(mappingToIndex.find(node1) == mappingToIndex.end()) {
            mappingToIndex[node1] = index++;
         }
         if(mappingToIndex.find(node2) == mappingToIndex.end()) {
            mappingToIndex[node2] = index++;
         }
         graph[mappingToIndex[node1]].push_back(mappingToIndex[node2]);
         graph[mappingToIndex[node2]].push_back(mappingToIndex[node1]);
      }      



      int graphSize = mappingToIndex.size();
      int start = 0;
      int ttl = 0;
      while(in >> start >> ttl && (start || ttl)){
         int result = 0;
         if(mappingToIndex.find(start) != mappingToIndex.end()){
            int cost[30];
            memset (cost, -1, sizeof (cost));

            std::queue<int> fringe;
            fringe.push(mappingToIndex[start]);

            cost[mappingToIndex[start]] = 0;
            int reachable = 0;
            while(!fringe.empty()){
               int node = fringe.front();
               fringe.pop();
               ++reachable;
               if((ttl - cost[node]) > 0){
                  for(int child: graph[node]){
                     if(cost[child] == -1){
                        cost[child] = cost[node] + 1;
                        fringe.push(child);
                     }
                  }
               }
             }
             result = reachable;
          }
          out << "Case " << ++caseNumber << ": " << (graphSize - result) << " nodes not reachable from node " << start << " with TTL = " << ttl << "." << std::endl;
      }
   }
}
