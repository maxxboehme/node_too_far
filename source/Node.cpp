#include <iostream>
#include <vector>
#include <unordered_map>
#include <utility>
#include <unordered_set>
#include <queue>
#include <array>
#include <cstring>

#include "prints.h"

void read_graph(std::istream& in, int numberOfPairs, int graph[][31], std::unordered_map<int, int>& mapToIndex){
   int node1;
   int node2;

   int index = 1;
   while(--numberOfPairs >= 0 && in >> node1 >> node2){
      if(!mapToIndex[node1]) {
         mapToIndex[node1] = index++;
      }
      if(!mapToIndex[node2]) {
         mapToIndex[node2] = index++;
      }
      graph[mapToIndex[node1]][mapToIndex[node2]] = 1;
      graph[mapToIndex[node1]][mapToIndex[node1]] = 0;
      graph[mapToIndex[node2]][mapToIndex[node1]] = 1;
      graph[mapToIndex[node1]][mapToIndex[node1]] = 0;
      //std::cout << mapToIndex << std::endl;
      //ArrayToStream(std::cout, graph);
      //std::cout << std::endl;
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

void floyd_warshall(int graph[][4], int numberOfNodes){
   for(int k = 0; k < numberOfNodes; ++k){
      for(int i = 0; i < numberOfNodes; ++i){
         for(int j = 0; j < numberOfNodes; ++j){
            if(graph[i][k] != -1 && graph[k][j] != -1){
               if(graph[i][k] + graph[k][j] < graph[i][j]){
                  graph[i][j] = graph[i][k] + graph[k][j];
               }
            }
         }
      }
   }
}

int breath_first_search(std::array<std::vector<int>, 31>& graph, std::unordered_map<int, int>& mappingToIndex, int start, int ttl){
   if(mappingToIndex.find(start) == mappingToIndex.end())
      return 0;
   int cost[31];
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

/*
void node_too_far_solve(std::istream& in, std::ostream& out){
   // turn off synchronization with C I/O
   std::ios_base::sync_with_stdio(false);
   
   int numberOfPairs = 0;
   int caseNumber = 0;
   
   while(in >> numberOfPairs && numberOfPairs){
      //std::cout << "Number of Pairs: " << numberOfPairs << std::endl;
      std::array<std::vector<int>, 31> graph;
      std::unordered_map<int, int> mappingToIndex;
      read_graph(in, numberOfPairs, graph, mappingToIndex);
      int graphSize = mappingToIndex.size();
      //std::cout << "graph size: " << graphSize << std::endl;
      std::pair<int, int> p;
      while(read_query(in, p)){
          //std::cout << "Node: " << p.first << " ttl: " << p.second << std::endl;
          int result = breath_first_search(graph, mappingToIndex, p.first, p.second);
          print_results(out, ++caseNumber, graphSize - result, p.first, p.second);
      }
   }
}*/
