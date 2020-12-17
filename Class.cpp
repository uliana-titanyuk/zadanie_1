#include "Class.h"
#include "Header.h"
using namespace std;

List::List() {
	Size = 0;
	head = nullptr;
}

List::~List() {
clear();
}

void List::pop_front() {
	Node *temp = head;
	head = head->pNext;
	delete temp;
	Size--;
}

void List::push_back(string par, string val) {
	if (head == nullptr) {
		head = new Node(par, val);
	}
	else {
		Node* current = this->head;
		while (current->pNext != nullptr) {
			current = current->pNext;
		}
		current->pNext = new Node(par, val);
	}
	Size++;
}

void List::clear() {
	while (Size) {
		pop_front();
	}
}

string& List::operator[](const string par) {

	Node* current = this->head;

	while (current != nullptr)
	{
		if (current->par == par)
		{
			return current->val;
		}
		current = current->pNext;

	}
}

string& List::operator[](const int index) {
	int counter = 0;

	Node* current = this->head;

	while (current != nullptr)
	{
		if (counter == index)
		{
			return current->par;
		}
		current = current->pNext;
		counter++;
	}
}

int List::GetSize() {
	return Size;
}

List::Node::Node(string par, string val, Node* pNext) {
	this->par = par;
	this->val = val;
	this->pNext = pNext;
}

void List::Print(){
	Node* current = this->head;
	while (current != nullptr) {
		cout << current->par << " = " << current->val << endl;
		current = current->pNext;
	}
}
