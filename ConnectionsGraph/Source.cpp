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
	std::cout << "Adjacency List before wrapping circuits" << std::endl;
	graph.PrintAdjacencyMap();

	// build list of all nodes that are part of a circuit
	std::set<Graph::Node*> circulars;
	for (auto n : graph.GetAllNodes())
	{
		if (graph.IsCircularNode(n))
		{
			circulars.insert(n);
		}
	}
	// wrap all circular nodes into 1
	std::cout << "Wrapping nodes that are part of a circuit: ";
	for (auto n : circulars)
	{
		Graph::Node* neighbor = nullptr;
		for (auto e : n->edges)
		{
			if (circulars.find(e->end) != circulars.end())
			{
				neighbor = e->end;
				break;
			}
		}
		std::cout << n->name <<", ";
		graph.WrapCircularNodeInto(n,neighbor);
	}
	std::cout << "\nAdjacency List before wrapping circuits" << std::endl;
	graph.PrintAdjacencyMap();

	// Count all nodes that have no incoming && are not the startingAirport
	int count = 0;
	for (auto n : graph.nodemap)
	{
		if (n.second->CountIncoming() == 0 && n.first != startingAirport)
		{
			count++;
		}
	}
	return count;
}

void RunExample()
{
	std::vector<std::string> airports = {
		"BGI", "CDG", "DEL", "DOH", "DSM", "EWR", "EYW", "HND", "ICN", "JFK", "LGA", "LHR", "ORD", "SAN", "SFO", "SIN", "TLV", "BUD"
	};
	std::vector<std::pair<std::string, std::string>> routes = {
		{"DSM","ORD"}, {"ORD","BGI"},{"BGI","LGA"},{"SIN","CDG"},{"CDG","SIN"},{"CDG","BUD"},
		{"DEL","DOH"}, {"DEL","CDG"},{"TLV","DEL"},{"EWR","HND"},{"HND","ICN"},{"HND","JFK"},
		{"ICN","JFK"}, {"JFK","LGA"},{"EYW","LHR"},{"LHR","SFO"},{"SFO","SAN"},{"SFO","DSM"},
		{"SAN","EYW"} 
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