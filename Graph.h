#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <string>
#include "AVL.h"
#include "Queue.h"
using namespace std;


/*
        Implementing the graph using the adjacency list 
*/

// forward declaration for the code 

struct Node; 

struct GraphNode {

    int vertex;
    GraphNode* next;

};


class Graph {

private:

    int V;                          // No of movies 
    string* movies;                 // movie titles 

    GraphNode** adj;  

 
    void addEdgeInternal(int u, int v) {

        if (u == v) {
            return;
        }

        // check if edge already exists

        GraphNode* temp = adj[u];
        while (temp != NULL) {
            if (temp->vertex == v) return;
            temp = temp->next;
        }

        GraphNode* newNode = new GraphNode();

        newNode->vertex = v;

        newNode->next = adj[u];
        adj[u] = newNode;

        // for the undirected graph make it bidirectional 

        newNode = new GraphNode();

        newNode->vertex = u;

        newNode->next = adj[v];
        adj[v] = newNode;
    }


    int findMovieIndex(const string& title) {

        for (int i = 0; i < V; i++) {
            if (movies[i] == title) {
                return i;
            }
        }
        return -1;
    }

    // Check if two movies share actors or genres

    bool shareConnection(const string& actor1_1, const string& actor2_1, const string& actor3_1,const string& genre1,
        const string& actor1_2, const string& actor2_2, const string& actor3_2, const string& genre2) {
        // first check for the actors 

        if (actor1_1 != "Unknown" && actor1_1 != "") {
            if (actor1_1 == actor1_2 || actor1_1 == actor2_2 || actor1_1 == actor3_2) {
                return true;
            }
        }
        if (actor2_1 != "Unknown" && actor2_1 != "") {
            if (actor2_1 == actor1_2 || actor2_1 == actor2_2 || actor2_1 == actor3_2) {
                return true;
            }
        }
        if (actor3_1 != "Unknown" && actor3_1 != "") {
            if (actor3_1 == actor1_2 || actor3_1 == actor2_2 || actor3_1 == actor3_2) {
                return true;
            }
        }

        // then check for the genres 

        if (genre1.find(genre2) != string::npos || genre2.find(genre1) != string::npos) {
            return true;
        }

        return false;
    }

public:

    Graph(int numMovies) {

        V = numMovies;
        movies = new string[V];

        adj = new GraphNode * [V];

        for (int i = 0; i < V; i++) {

            adj[i] = nullptr;
            movies[i] = "";
        }
    }

    void setMovie(int index, const string& title) {

        if (index >= 0 && index < V) {

            movies[index] = title;

        }
    }

    // construct the given graph 

    void buildGraph(Node** allMovies, int count) {

        cout << "Building graph connections..." << endl;

        // Create edges between movies that share actors or genres


        for (int i = 0; i < count; i++) {
            for (int j = i + 1; j < count; j++) {

                Node* movie1 = allMovies[i];
                Node* movie2 = allMovies[j];

                if (shareConnection(movie1->actor1, movie1->actor2, movie1->actor3, movie1->genre,
                    movie2->actor1, movie2->actor2, movie2->actor3, movie2->genre)) {
                    addEdgeInternal(i, j);
                }
            }
        }
        cout << "Graph construction complete!" << endl;
    }

    // RECOMMENDATION SYSTEM USING BFS


    void getRecommendations(const string& movieTitle, int maxDepth = 1) {

        int start = findMovieIndex(movieTitle);

        if (start == -1) {
            cout << "Connot find the movie " << endl;
            return;
        }

        cout << "=== Recommendations for '" << movieTitle << "' ===" << endl;

        // BFS setup

        bool* visited = new bool[V];
        int* level = new int[V];

        for (int i = 0; i < V; i++) {
            visited[i] = false;
            level[i] = -1;
        }

        Queue q;

        visited[start] = true;
        level[start] = 0;

        q.enqueue(start);

        int count = 0;

        while (!q.isEmpty()) {
            int curr = q.dequeue();
            int currlvl = level[curr];

            // Stop if we've reached max depth skipping the 0 

            if (currlvl > maxDepth) {
                continue;
            }

            // Visit all neighbors

            GraphNode* neighbor = adj[curr];

            while (neighbor != NULL) {

                if (!visited[neighbor->vertex]) {

                    visited[neighbor->vertex] = true;
                    level[neighbor->vertex] = currlvl + 1;
                    q.enqueue(neighbor->vertex);

                    // Print recommendation if not the starting movie

                    if (neighbor->vertex != start && currlvl + 1 <= maxDepth) {
                        cout << count + 1 << " : " << "- " << movies[neighbor->vertex] << endl;
                        count++;
                    }
                }
                neighbor = neighbor->next;
            }
        }

        if (count == 0) {

            cout << endl; 
            cout << "No recommendations found." << endl;
        }

        else {

            cout << endl;
            cout << "Total recommendations: " << count << endl;
        }

        delete[] visited;
        delete[] level;
    }

/*
    for the shortest path the implementation is done using the BFS : since the graph were unweighted 
*/


    void findShortestPath(const string& startTitle, const string& targetTitle) {

        int start = findMovieIndex(startTitle);
        int target = findMovieIndex(targetTitle);

        if (start == -1 || target == -1) {
            cout << "Movie not found " << endl;
            return;
        }

        if (start == target) {
            cout << "start and the target are same movie " << endl;
            return;
        }

        // BFS setup

        bool* visited = new bool[V];

        int* parent = new int[V];

        for (int i = 0; i < V; i++) {

            visited[i] = false;
            parent[i] = -1;
        }

        Queue q;

        visited[start] = true;

        q.enqueue(start);

        bool found = false;

        while (!q.isEmpty() && !found) {    
            int current = q.dequeue();

            // Visit all neighbors

            GraphNode* neighbor = adj[current];

            while (neighbor != NULL) {

                if (!visited[neighbor->vertex]) {

                    visited[neighbor->vertex] = true;
                    parent[neighbor->vertex] = current;

                    q.enqueue(neighbor->vertex);

                    if (neighbor->vertex == target) {
                        found = true;
                        break;
                    }
                }
                neighbor = neighbor->next;
            }
        }

        if (!found) {
            cout << "No path exists between '" << startTitle << "' and '" << targetTitle << "'" << endl;
        }
        else {

            // Reconstruct path

            cout << endl; 
            cout << endl; 
            cout << "=== Shortest Path ===" << endl;

            int* path = new int[V];
            int pathLen = 0;

            // Backtrack from target to start

            int current = target;
            while (current != -1) {

                path[pathLen++] = current;
                current = parent[current];
            }

            // Print path in reverse order

            for (int i = pathLen - 1; i >= 0; i--) {
                cout << movies[path[i]];
                if (i > 0) {
                    cout << " -> ";
                }
            }

            cout << endl;
            cout << "Path length: " << pathLen - 1  << endl;

            delete[] path;
        }

        delete[] visited;
        delete[] parent;
    }

    ~Graph() {
        for (int i = 0; i < V; i++) {

            GraphNode* curr = adj[i];

            while (curr != nullptr) {

                GraphNode* next = curr->next;

                delete curr;
                curr = next;
            }
        }
        delete[] adj;
        delete[] movies;
    }


};

#endif