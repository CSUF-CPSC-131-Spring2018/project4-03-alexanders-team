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
	for (int i = 0; i < MAXSIZE; i++) {
		for (int j = 0; j < MAXSIZE; i++) {
			adjacencyMatrix[i][j] = 0;
		}
	}
	for (int i = 0; i < MAXSIZE; i++) {
		visited[i] = false;
	}
	numNodes = 0;
	numEdges = 0;
	current_budget = 0;
}
Graph::Graph(int rno, float rbudget) {  // constructor with two arguments representing the number of nodes, initial budget
	for (int i = 0; i < rno; i++) {
		for (int j = 0; j < rno; i++) {
			adjacencyMatrix[i][j] = 0;
		}
	}
	for (int i = 0; i < rno; i++) {
		visited[i] = false;
	}
	numNodes = rno;
	numEdges = 0;
	current_budget = rbudget;
} 
void Graph::addEdge(int node1, int node2) { // adds an edge between two nodes in the graph node1 and node2
	adjacencyMatrix[node1][node2] = 1;
	numEdges++;
} 
void Graph::setValue(int node, float rval) {  // sets a value for a node
	nodes[node] = rval;
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
	return nodes[node];
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
int Graph::DFS(int startNode) {  // return the starting node that gives a longest DFS run before running out of budget if there are multiple nodes with the same DFS run length, return the smallest node
	visited[startNode] = true; //Mark starting node as visited
	for (int w = 0; w < numNodes; w++) {
		if (adjacencyMatrix[startNode][w] == 1) {
			if (!visited[w]) {
				DFS(w);
			}
		}
	}
}

int Graph::bestStartVertex() {//return the number of nodes visited using BFS starting at startNode and accumulating values at each node, as long as the budget remains positive

	current_budget += nodes[startNode];
}
