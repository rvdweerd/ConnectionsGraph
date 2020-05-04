#pragma once
#include <string>
#include <set>
#include <map>
#include <vector>
#include <iostream>
#include <cassert>
#include <queue>

class Graph
{
	struct Edge;
	struct Node
	{
		Node(std::string n)
			:
			name(n)
		{}
		std::string name;
		std::set<Edge*> edges;
	};
	struct Edge
	{
		Edge(Node* s, Node* e, int c)
			:
			start(s),
			end(e),
			cost(c)
		{}
		Node* start;
		Node* end;
		int cost;
	};
	std::map<std::string,Node*> nodemap;
	std::set<Edge*> edgelist;
public:
	void AddNode(std::string name)
	{
		nodemap[name] = new Node(name);
	}
	void AddEdge(std::string n1, std::string n2, int cost)
	{
		assert(nodemap.find(n1) != nodemap.end() && nodemap.find(n2) != nodemap.end());
		if (nodemap.find(n1) == nodemap.end() || nodemap.find(n2) == nodemap.end()) return;
		Node* node1 = nodemap[n1]; 
		Node* node2 = nodemap[n2];
		Edge* e = new Edge(node1, node2, cost);
		node1->edges.insert(e);
		edgelist.insert(e);
	}
	std::vector<Node*> GetAllNodes() const
	{
		std::vector<Node*> vec;
		for (auto p : nodemap)
		{
			vec.push_back(p.second);
		}
		return vec;
	}
	void PrintAdjacencyMap() const
	{
		for (auto p : nodemap)
		{
			std::cout << p.first << ", Name: " << p.second->name << ", Connected to: ";
			for (auto e : p.second->edges)
			{
				std::cout << e->end->name << "["<<e->cost <<"], ";
			}
			std::cout << std::endl;
		}
	}
	bool IsCircularNode(std::string node) 
	{
		return IsCircularNode(nodemap[node]);
	}
	bool IsCircularNode(Node* node) const
	{
		std::queue<Node*> queue;
		std::set<Node*> visited;
		queue.push(node);
		while (!queue.empty())
		{
			Node* current = queue.front(); queue.pop();
			if (visited.find(current) != visited.end() && current == node) return true;
			visited.insert(current);
			for (auto e : current->edges)
			{
				if (e->end == node || visited.find(e->end) == visited.end()) // only  add if not visited earlier (node under investigation gets readded)
				//if (visited.find(e->end) == visited.end()) // only  add if not visited earlier 
				{
					queue.push(e->end);
				}
			}
		}
		return false;
	}
};
