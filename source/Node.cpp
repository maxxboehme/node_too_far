#include <iostream>
#include <vector>
#include <unordered_map>
#include <utility>
#include <unordered_set>
#include <queue>
#include <array>
#include <cstring>

#include "prints.h"

inline void read_graph(std::istream& in, int numberOfPairs, int graph[][30], std::unordered_map<int, int>& mapToIndex){
   int node1;
   int node2;

   int index = 0;
   while(--numberOfPairs >= 0 && in >> node1 >> node2){
      if(mapToIndex.find(node1) == mapToIndex.end()) {
         mapToIndex[node1] = index++;
         graph[mapToIndex[node1]][mapToIndex[node1]] = 0;
      }
      if(mapToIndex.find(node2) == mapToIndex.end()) {
         mapToIndex[node2] = index++;
         graph[mapToIndex[node2]][mapToIndex[node2]] = 0;
      }
      graph[mapToIndex[node1]][mapToIndex[node2]] = 1;
      graph[mapToIndex[node2]][mapToIndex[node1]] = 1;
      //std::cout << mapToIndex << std::endl;
      //ArrayToStream(std::cout, graph);
      //std::cout << std::endl;
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

inline void floyd_warshall(int graph[][30], int numberOfNodes){
   for(int k = 0; k < numberOfNodes; ++k){
      for(int i = 0; i < numberOfNodes; ++i){
         for(int j = 0; j < numberOfNodes; ++j){
            if(graph[i][k] != -1 && graph[k][j] != -1){
               if(graph[i][k] + graph[k][j] < graph[i][j] || graph[i][j]==-1){
                  graph[i][j] = graph[i][k] + graph[k][j];
               }
            }
         }
      }
   }
}

inline int number_reachable_nodes(int graph[][30], std::unordered_map<int, int> mappingToIndex, int start, int ttl, int numberOfNodes){
   if(mappingToIndex.find(start) == mappingToIndex.end())
      return 0;
   int startNode = mappingToIndex[start];
   //std::cout << mappingToIndex << std::endl;
   //std::cout << start << " : " << startNode << std::endl;
   //Array2DToStream(std::cout, graph, numberOfNodes);
   //std::cout << std::endl;
   int reachable = 0;
   for(int i = 0; i < numberOfNodes; ++i){
      if(graph[startNode][i] != -1 && graph[startNode][i] <= ttl){
         ++reachable;
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
      //std::cout << "Number of Pairs: " << numberOfPairs << std::endl;
      int graph[30][30];
      for(int i = 0; i < 30; ++i){
         memset(graph[i], -1, sizeof(graph[i]));
      }
      std::unordered_map<int, int> mappingToIndex;
      read_graph(in, numberOfPairs, graph, mappingToIndex);
      int graphSize = mappingToIndex.size();
      floyd_warshall(graph, graphSize);
      //std::cout << "graph size: " << graphSize << std::endl;
      std::pair<int, int> p;
      while(read_query(in, p)){
          //std::cout << "Node: " << p.first << " ttl: " << p.second << std::endl;
          int result = number_reachable_nodes(graph, mappingToIndex, p.first, p.second, graphSize);
          print_results(out, ++caseNumber, graphSize - result, p.first, p.second);
      }
   }
}
