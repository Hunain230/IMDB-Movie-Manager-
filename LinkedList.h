#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include<iostream>
#include<string>
#include "AVL.h"
using namespace std; 


struct LLnode {

	Node* MovieNode; 
	LLnode* next; 

	LLnode() {
		next = NULL;
		MovieNode = NULL; 
	}
};

class LinkedList {

	LLnode* head; 

public:

	LLnode* getHead() {
		return head;
	}

	LinkedList() {
		head = NULL;
	}

	void Insert(Node* movie) {

		// we will insert at head making insertion O(1)

		if (movie == NULL) return; 

		LLnode* temp = new LLnode;
		temp->MovieNode = movie; 
		temp->next = head; 
		head = temp; 
	}

	Node* Search(string title) {

		LLnode* temp = head;

		while (temp != NULL) {
			if (temp->MovieNode->title == title) {
				return temp->MovieNode;
			}
			temp = temp->next; 
		}
		return NULL;
	}

	void DisplayList() {

		LLnode* temp = head;
		int i = 0;

		while (temp != NULL) {
		
			if (temp->MovieNode != NULL) {
				i++;
				cout << i << " : " << temp->MovieNode->title << endl;
			}
			temp = temp->next; 
		}
		cout << "END OF THE LIST  ." << endl; 

		cout << endl; 

		cout << "Total Entries " << i << endl; 
	}

	~LinkedList() {

		while (head) {

			LLnode* temp = head;
			head = head->next;

			delete temp;
		}
	}
};


#endif