
#ifndef __NODE__
#define __NODE__

#include <iostream>
#include <vector>
#include <unordered_map>

void node_too_far_solve(std::istream& in, std::ostream& out);

void read_graph(std::istream& in, int numberOfPairs, std::unordered_map<int, std::vector<int> >& graph);
void read_graph2(std::istream& in, int numberOfPairs, std::unordered_map<int, std::vector<int> >& graph);
bool read_query(std::istream& in, std::pair<int, int>& pair);
int breath_first_search(std::unordered_map<int, std::vector<int> >& graph, int start, int ttl);
void print_results(std::ostream& out, int caseNumber, int numberNotReachable, int startingNode, int ttl);
#endif
