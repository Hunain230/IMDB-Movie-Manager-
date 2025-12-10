🎬 Movie Database Management System

A C++ application to efficiently store, retrieve, and analyze movie metadata using advanced data structures. Features intelligent recommendations, co-actor discovery, and multi-criteria search.

✨ Key Features

Advanced Search

Title Search: O(log n) via AVL Tree

Genre Search: O(1) average using Hash Map with separate chaining

Actor Search: O(1) average with collision handling

Director Search: Fast lookup by director

Range Search: By year and rating

Co-actor Discovery: Identify actors who worked together

Intelligent Features

Personalized Recommendations (shared actors & genres)

Shortest Path Discovery (minimum movie connections)

Relationship Analysis (graph-based connections)

Multi-criteria Filtering

📊 Performance

Fast retrieval using optimized data structures

Memory-efficient storage with hashing

Scalable to thousands of movie records

🏗️ System Architecture

AVL Tree: Primary storage (balanced, O(log n) operations)

Hash Maps: Indexing by actor & genre

Graph: Movie relationship analysis (undirected, unweighted)

Linked Lists: Handle hash collisions

Queue: BFS for recommendations

Connection Criteria: Movies are connected if they share:

At least one actor

Same or related genres

📂 Project Structure

/MovieDB

│-- main.cpp

│-- LinkedList.h 

│-- AVLTree.h 

│-- HashMap.h 

│-- Graph.h

│-- Queue.h 

│-- README.md
