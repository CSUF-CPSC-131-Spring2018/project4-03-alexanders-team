//
//  graph.cpp
//  Project4
//
//  Created by Bein, Doina on 4/21/18.
//  Copyright © 2018 Bein, Doina. All rights reserved.
//
#include	<fstream>
#include	<iostream>
#include	<string>
#include	<sstream>
#include	"graph.h"

using namespace std;

// TO BE COMPLETED WITH IMPLEMENTATIONS OF GRAPH MEMBER FUNCTIONS
Graph::Graph() {
	numNodes = 0;
	numEdges = 0;
	current_budget = 0;
}
Graph::Graph(int rno, float rbudget) {  // constructor with two arguments representing the number of nodes, initial budget
	numNodes = rno;
	numEdges = 0;
	current_budget = rbudget;
} 
void Graph::addEdge(int node1, int node2) { // adds an edge between two nodes in the graph node1 and node2
	if (adjacencyMatrix[node1][node2] == 0) { // If the edge does not already exist.....
		adjacencyMatrix[node1][node2] = 1; //add the edge
		adjacencyMatrix[node2][node1] = 1; //both ways for undirected graph
		numEdges++;
	}
} 
void Graph::setValue(int node, float rval) {  // sets a value for a node
	nodeValue[node] = rval;
}
void Graph::setBudget(float rbu) { // sets the initial budget
	current_budget = rbu;
}
int Graph::getNSize() { // return number of nodes
	return numNodes;
} 
int Graph::getESize() { // return number of edges
	return numEdges;
} 
float Graph::getBudget() { // return current budget
	return current_budget;
} 
float Graph::getValue(int node) {  // returns the value of the node
	return nodeValue[node];
}
void Graph::readData(string fileName) {
	fstream fileReader(fileName);
	if (fileReader.is_open()) {
		fileReader >> numNodes;	//Store number of nodes
		fileReader >> current_budget; // store the starting budget
		for (int i = 0; i < numNodes; i++) { //Store values for each node
			int nodeValue;
			fileReader >> nodeValue;
			setValue(i,nodeValue);
		}
		while (!fileReader.eof()){	
			int current, adjacent;
			fileReader >> current;
			fileReader >> adjacent;
			addEdge(current, adjacent);
		}
		fileReader.close();
	}
} // reads data from a specified file
int Graph::DFS(int startNode) {  //return the number of nodes visited using DFS starting at startNode and accumulating values at each node, as long as the budget remains positive
	int pathLength = 0; //stores the length of the path of every unvisited node adjacent to current node. Used to ensure that we attempt to visit every unvisited node before recursion unwinds.
	visited[startNode] = true; //Mark starting node as visited
	current_budget += nodeValue[startNode]; //Update budget with value of the current node
	for (int w = 0; w < numNodes; w++) { //Cycle through adjacency list
		if (adjacencyMatrix[startNode][w] == 1) { //If the nodes are adjacent....
			if (!visited[w]) { // and the node has not yet been visited....
				if (current_budget > 0) { // if current budget is not negative..
					pathLength += DFS(w);// explore that node and update run length.
				}
			}
		}
	}
	return 1 + pathLength;
}



int Graph::bestStartVertex() { // return the starting node that gives a longest DFS run before running out of budget if there are multiple nodes with the same DFS run length, return the smallest node
	int maxRunLength = 0;
	int maxRunStartNode = 0;
	for (int i = 0; i < numNodes; i++) {
		int runLength = DFS(i);
		if (runLength > maxRunLength) {
			maxRunLength = runLength;
			maxRunStartNode = i;
		}
	}
	return maxRunStartNode;
}
