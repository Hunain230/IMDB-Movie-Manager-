#ifndef AVL_H
#define AVL_H

#include<iostream>
#include<string>
using namespace std; 

/*
         Implementing the storage using the  AVL TREE 
*/

struct Node {

	string director;
	string actor2;
	string genre;
	string actor1;
	string title; 
	string actor3;
	int year;
	float rating;

	Node* left;
	Node* right; 

	void* graphRef;

	int height; 

	Node(string d, string act1, string act2, string act3, string g, string t, int y ,float r) {

		director = d; 
		actor1 = act1;
		actor2 = act2;
		actor3 = act3;
		genre = g; 
		title = t; 
		year = y;
		rating = r; 

		left = NULL; 
		right = NULL;

		height = 1; 

		graphRef = NULL; 
	}

};

class AVL {

	Node* root = NULL; 

	int getheight(Node * n ) {

		if (n == NULL) {
			return 0; 
		}

		else {
			return n->height; 
		}
	}

	int CalculateBF(Node* n) {

		if (n == NULL) {
			return 0;
		}
		else {
			return getheight(n->left) - getheight(n->right);
		}
	}

/*
				COVERING ALL THE CASES 
*/ 

	Node* RightRotation(Node * k1 ) {
		
		Node* k2 = k1->left; 
		k1->left = k2->right; 
		k2->right = k1; 

		k1->height = max(getheight(k1->left), getheight(k1->right)) + 1;
		k2->height = max(getheight(k2->left), getheight(k2->right)) + 1;

		return k2; 
	}

	Node* LeftRotation(Node * k1 ) {
		Node* k2 = k1->right;
		k1->right = k2->left; 
		k2->left = k1;

		k1->height = max(getheight(k1->left), getheight(k1->right)) + 1;
		k2->height = max(getheight(k2->left), getheight(k2->right)) + 1;

		return k2; 
	}

	Node* RightLeftRotation(Node * k1 ) {

		k1->right = RightRotation(k1->right);

		return LeftRotation(k1);
	}

	Node* LeftRightRotation(Node * k1 ) {

		k1->left = LeftRotation(k1->left);
		return RightRotation(k1);
	}
/*
							Insertion /  Deletion / Search Operations
*/

	Node* Insert(Node * node , Node * nn ) {

		if (node == NULL) {
			return nn;
		}

		if (nn->title < node->title) {
			node->left = Insert(node->left, nn);
		}
		else if (nn->title > node->title) {
			node->right = Insert(node->right, nn);
		}
		else
			return node;

		node->height = 1 + max(getheight(node->left), getheight(node->right));
		
		int bf = CalculateBF(node);

		if (bf > 1 and nn->title < node->left->title) {
			return RightRotation(node);
		}
		if (bf < -1 and nn->title > node->right->title) {
			return LeftRotation(node);
		}
		if (bf > 1 and nn->title > node->left->title) {

			node->left = LeftRotation(node->left);
			return RightRotation(node);

		}
		if (bf < -1 and nn->title < node->right->title) {

			node->right = RightRotation(node->right);
			return LeftRotation(node);

		}

		return node;
	}

	Node* Search(Node * node , const string &title ) {

		if (node == NULL) {
			return NULL;
		}

		if (node->title == title) {
			return node; 
		}
		if (title < node->title) {
			return Search(node->left, title);
		}

		return Search(node->right, title);

	}


	Node* FindMin(Node * node ) {

		Node* current = node; 

		while (current != NULL and current ->left != NULL) {
			current = current->left;
		}
		return current; 
	}

	Node* Delete(Node* node, const string& title) {

		if (node == NULL) {
			return node;
		}

		if (title < node->title) {
			node->left = Delete(node->left, title);
		}
		else if (title > node->title) {
			node->right = Delete(node->right, title);
		}
		else {

			if (node->left == NULL && node->right == NULL) {
				delete node;
				return NULL;
			}
			else if (node->left == NULL) {
				Node* temp = node->right;

				delete node;
				return temp;
			}
			else if (node->right == NULL) {

				Node* temp = node->left;

				delete node;
				return temp;
			}
			else {    // inorder successor 

				Node* sucessor = FindMin(node->right);

				node->title = sucessor->title;
				node->director = sucessor->director;
				node->actor1 = sucessor->actor1;
				node->actor2 = sucessor->actor2;
				node->actor3 = sucessor->actor3;
				node->genre = sucessor->genre;
				node->year = sucessor->year;
				node->rating = sucessor->rating;

				node->right = Delete(node->right, sucessor->title);
			}

		}


		node->height = 1 + max(getheight(node->left), getheight(node->right));

		int bf = CalculateBF(node);

		if (bf > 1 && CalculateBF(node->left) >= 0)
			return RightRotation(node);

		if (bf > 1 && CalculateBF(node->left) < 0) {
			node->left = LeftRotation(node->left);
			return RightRotation(node);
		}

		if (bf < -1 && CalculateBF(node->right) <= 0)
			return LeftRotation(node);

		if (bf < -1 && CalculateBF(node->right) > 0) {
			node->right = RightRotation(node->right);
			return LeftRotation(node);
		}

		return node;
	}

	int countNodes(Node * node ) {

		if (node == NULL) {
			return 0; 
		}

		return 1 + countNodes(node->left) + countNodes(node->right);
	}


	void fillArray(Node* node, Node** array, int& index) {

		if (node == NULL) {
			return;
		}

		fillArray(node->left, array, index);

		array[index++] = node;

		fillArray(node->right, array, index);
	}

public:


	void insert(string d, string act1, string act2, string act3, string g, string t, int y , float r ) {
		Node* newNode = new Node(d, act1, act2, act3, g, t, y , r);
		root = Insert(root, newNode);
	}

	Node* search(const string& title) {

		return Search(root, title);

	}

	void deletemovie(const string& title) {
		root = Delete(root, title);
	}
	
	int getCount() {
		return countNodes(root);
	}

	void getAllMovies(Node** array) {
		int index = 0;
		fillArray(root, array, index);
	}


	void DisplayNode(Node* node) {

		if (node == NULL)  return;

		cout << endl; 
		cout << "========================================" << endl;
		cout << "Title :" << node->title << endl;
		cout << "Director :" << node->director << endl;
		cout << "Actors :" << node->actor1 << " , " << node->actor2 << " , " << node->actor3 << endl;
		cout << "Genre :" << node->genre << endl;
		cout << "Year :" << node->year << endl;
		cout << "Rating :" << node->rating << endl;
		cout << "========================================" << endl;
		cout << endl;
	}

	Node* getRoot() {
		return root;
	}

};

#endif