/*
 * BreadthFirstSearch.h
 *
 *  Created on: Dec 17, 2022
 *      Author: Tyrien Gilpin
 */
#ifndef NETWORK_BREADTHFIRSTSEARCH_H_
#define NETWORK_BREADTHFIRSTSEARCH_H_

#include "PersonNode.h"
#include <map>
#include <queue>
#include <iostream>
using namespace std;

class BreadthFirstSearch {
private:
	PersonNode start;
	PersonNode destination;
	map<PersonNode, set<PersonNode>> RBTree;
	list<PersonNode> printer = list<PersonNode>();

public:
	//Utilization of the member initializer list to avoid the have a
	//default constructor before assignment
	BreadthFirstSearch(PersonNode begin, PersonNode stop,
			map<PersonNode, set<PersonNode>> tree):
		start(begin), destination(stop), RBTree(tree)
	{
	}

	virtual ~BreadthFirstSearch() {
	}

	//Getters and Setters
	PersonNode getStart() {
		return start;
	}

	void setStart(PersonNode start) {
		this->start = start;
	}

	PersonNode getDestination() {
		return destination;
	}

	void setDestination(PersonNode destination) {
		this->destination = destination;
	}

	map<PersonNode, set<PersonNode>> getRBTree() {
		return RBTree;
	}

	void setRBTree(map<PersonNode, set<PersonNode>> rBTree) {
		RBTree = rBTree;
	}

	void clear(queue<PersonNode> &q) {
		queue<PersonNode> empty;
		swap(q, empty);
	}

	//BFS Algorithm Demonstration
	string separationDegree() {
		queue<PersonNode> que = queue<PersonNode>(); // queue to store nodes to be visited along the breadth
		string output = "";
		start.setVisited(true); // mark source node as visited
		que.push(start); // push src node to queue
		while (!(que.empty())) {
			PersonNode currentNode = que.front(); // traverse all nodes along the breadth
			que.pop();
			for (PersonNode node : getRBTree().find(currentNode)->second) { //currentNode.getFriends()
				if (node.isVisited() == false) {
					node.setVisited(true); //mark it visited
					que.push(node);
					node.setPrevious(&currentNode);///NTS: CHECK THIS LINE LATER
					printer.push_back(node);
					//update the key of the node to this now
					if (node.getData().getFirstName()
							== destination.getData().getFirstName()
							&& node.getData().getLastName()
									== destination.getData().getLastName()) {
						output = "Degree found to be: \n";
						clear(que);
						break;
					}
				}
			}

		}
		return traceRoute(output);
	}

	// Computes and prints shortest path
private:
	string traceRoute(string output) {
		list<PersonNode> route = list<PersonNode>();
		for (auto node : printer) {
			if (node.getData().getLastName()
					== destination.getData().getLastName()) {
				while (node.getPrevious() != NULL) { //NTS: CHECK BACK ON THIS
					route.push_back(node);
					node = *node.getPrevious();
				}
			}
		}
		// Reverse the route - bring start to the front
		route.reverse();
		// Output the route
		for (PersonNode links : route) {
			output += links.getData().getFirstName() + "-->";
		}
		if ((route.size() - 1) < 0) {
			string display = "No Direct Connection.\n";
			int i = 0;
			if (start.getData().getCommunity()
					== destination.getData().getCommunity()) {
				display += start.getData().getFirstName() + "(you) and "
						+ destination.getData().getFirstName()
						+ " has community in common\n";
				i = 1;
			}
			if (start.getData().getSchool()
					== destination.getData().getSchool()) {
				display += start.getData().getFirstName() + "(you) and "
						+ destination.getData().getFirstName()
						+ " has school in common\n";
				i = 1;
			}
			if (start.getData().getEmployer()
					== destination.getData().getEmployer()) {
				display += start.getData().getFirstName() + "(you) and "
						+ destination.getData().getFirstName()
						+ " has employer in common\n";
				i = 1;
			}
			if (i == 1) {
				display +=
						"Possible connect is 1-2 degrees, i.e., < 6 degrees away\n";
			}
			return display;
		}
		return output += "\n" + route.size() - 1;
	}

};

#endif /* NETWORK_BREADTHFIRSTSEARCH_H_ */
