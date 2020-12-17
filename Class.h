#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstdio>
using namespace std;

class List {

public:
	List();
	~List();

	void pop_front();
	void push_back(string par, string val);
	void clear();
	int GetSize();
	void Print();
	string& operator[](const string par);
	string& operator[](const int index);

private:

	class Node {
	public:
		Node* pNext;
		string par;
		string val;

		Node(string par, string val, Node* pNext = nullptr);
		
	};
	int Size;
	Node* head;
}; 
