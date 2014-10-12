
#ifndef __NODE__
#define __NODE__

#include <iostream>
#include <vector>
#include <unordered_map>
#include <array>

//void node_too_far_solve(std::istream& in, std::ostream& out);

void floyd_warshall(int graph[][4], int numberOfNodes);

void read_graph(std::istream& in, int numberOfPairs, int graph[][31], std::unordered_map<int, int>& mappingToIndex);
bool read_query(std::istream& in, std::pair<int, int>& pair);
int breath_first_search(std::array<std::vector<int>, 31>& graph, std::unordered_map<int, int>& mappingToIndex, int start, int ttl);
void print_results(std::ostream& out, int caseNumber, int numberNotReachable, int startingNode, int ttl);
#endif
