#ifndef HASHMAP_H
#define HASHMAP_H

#include<iostream>
#include<string>
#include "AVL.h"
#include"LinkedList.h"

using namespace std;

struct HashNode {
	string key;
	LinkedList movies;
	HashNode* next;

	HashNode() {
		key = "";
		next = NULL; 
	}
};

class HashMap {

	int size;
	HashNode** table; 

	int Hash(const string& key) {

/*		 using the technique similar to double hashing using the prime number
		 which reduces the collosions 
*/
		unsigned long int hash = 0; 

		for (char c : key) {
			hash = (hash * 31 + c) % size; 
		}
		return hash; 
	}

public:

	HashMap(int s = 100) {
		size = s; 
		table = new HashNode*[size];

		for (int i = 0; i < size; i++) {
			table[i] = NULL;
		}

	}

	void Insert(const string& key , Node * movie ) {

		int index = Hash(key);

		HashNode* curr = table[index];

		while (curr != NULL) {

			if (curr->key == key) {
				curr->movies.Insert(movie);
				return; 
			}
			curr = curr->next; 
		}

		HashNode* nn = new HashNode;

		nn->key = key;
		nn->movies.Insert(movie);
		nn->next = table[index];

		table[index] = nn;
	}

	LinkedList* GetMovie(const string & key) {

		int index = Hash(key);
		HashNode* curr = table[index];

		while (curr != NULL) {

			if (curr->key == key) {

				return &curr->movies; // return the in litreal address without copying the whole list 
			}

			curr = curr->next; 
		}

		return NULL; 
	}


	~HashMap() {

		for (int i = 0; i < size; i++) {

			HashNode* curr = table[i];

			while (curr != NULL ) {
				HashNode* temp = curr;
				curr = curr->next;
				delete temp;
			}

		}
		delete[] table;
	}
};

#endif