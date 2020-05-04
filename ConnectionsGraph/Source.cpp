#include "Graph.h"
#include <iostream>
#include <vector>

struct InputData
{
	std::vector<std::string> airports;
	std::vector<std::pair<std::string, std::string>> routes;
	std::string startingAirport;
};
void BuildGraph(Graph& graph, const InputData& inputData)
{
	for (auto s : inputData.airports) graph.AddNode(s);
	for (auto p : inputData.routes)
	{
		graph.AddEdge(p.first, p.second, 1);
	}
}

int MinNewRoutes(std::vector<std::string> airports, std::vector<std::pair<std::string, std::string>> routes, std::string startingAirport)
{
	InputData inputData({ airports, routes, startingAirport });
	Graph graph;
	BuildGraph(graph, inputData);
	graph.PrintAdjacencyMap();
	return 0;
}

void RunExample()
{
	std::vector<std::string> airports = {
		"BGI", "CDG", "DEL", "DOH", "DSM", "EWR", "EYW", "HND", "ICN", "JFK", "LGA", "LHR", "ORD", "SAN", "SFO", "SIN", "TLV", "BUD"
	};
	std::vector<std::pair<std::string, std::string>> routes = {
		{"DSM","ORD"},{"ORD","BGI"},{"BGI","LGA"},{"SIN","CDG"},{"CDG","SIN"},{"CGD","BUD"},
		{"DEL","DOH"},{"DEL","CDG"},{"TLV","DEL"},{"EWR","HND"},{"HND","ICN"},{"HND","JFK"},
		{"JFK","LGA"},{"EYW","LHR"},{"LHR","SFO"},{"SFO","SAN"},{"SFO","DSM"},{"SAN","EYW"}
	};
	std::string startingAirport = "LGA";
	int answer = MinNewRoutes(airports, routes, startingAirport);
}

int main()
{
	RunExample();
	std::cin.get();
	return 0;
}