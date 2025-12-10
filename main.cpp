#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "AVL.h"
#include "LinkedList.h"
#include "HashMap.h"
#include "Graph.h"


void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}


void YearRange(AVL& tree, int start, int end) {

    int total = tree.getCount();

    if (total == 0) {
        cout << " NO movies inserted !" << endl; 
        return; 
    }
    

    Node** movies = new Node * [total];

    for (int i = 0; i < total; i++) {
        movies[i] = NULL;
    }


    tree.getAllMovies(movies);


    cout << "--- Movies Between " << start << " and " << end << "---" << endl;

    int count = 0;

    for (int i = 0; i < total && movies[i] != NULL; i++) {

        if (movies[i]->year >= start && movies[i]->year <= end) {

            tree.DisplayNode(movies[i]);
            count++;
        }
    }

    cout << "Total Movies in the Range :" << count << endl;

    delete[] movies;
}


void RatingRangeSearch(AVL & tree , float min , float max ) {

    int total = tree.getCount();

    if (total == 0) {
        cout << " NO movies inserted !" << endl;
        return;
    }

    Node** movies = new Node * [total];

    for (int i = 0; i < total; i++) {
        movies[i] = NULL; 
    }

    tree.getAllMovies(movies);

    cout << "--- Movies with rating " << min << " and " << max << "---" << endl;

    int count = 0;

    for (int i = 0; i < total && movies[i] != NULL ; i++) {

        if (movies[i]->rating >= min && movies[i]->rating <= max) {
            tree.DisplayNode(movies[i]);
            count++;
        }
    }

    cout << "Total Movies in the Range :" << count << endl;

    delete[] movies;
}

// this will check wether te actor is already added or not 

void AddActor(string* arr, int& count, const string& actor) {

    for (int i = 0; i < count; i++) {
        if (arr[i] == actor) {
            return;
        }
    }
    arr[count++] = actor;
}

void CoactorSearch(HashMap& actorMap, const string& actorName) {

    LinkedList* list = actorMap.GetMovie(actorName);

    if (list == NULL) {
        cout << "Actor Not found " << endl;
        return;
    }

    cout << "=== Co-Actors for " << actorName << " ===" << endl;

    const int max = 200;
    string* coActors = new string[max];

    int count = 0;

    LLnode* curr = list->getHead();

    while (curr != NULL) {
        Node* movie = curr->MovieNode;

        if (movie->actor1 != actorName && movie->actor1 != "Unknown") {
            AddActor(coActors, count, movie->actor1);
        }
        if (movie->actor2 != actorName && movie->actor2 != "Unknown") {
            AddActor(coActors, count, movie->actor2);
        }
        if (movie->actor3 != actorName && movie->actor3 != "Unknown") {
            AddActor(coActors, count, movie->actor3);
        }

        curr = curr->next;
    }

    if (count == 0) {
        cout << "No Co-Actor Exists " << endl;
    }
    else {

        for (int i = 0; i < count; i++) {

            cout << i + 1 << ". " << coActors[i] << endl;
        }

        cout << "Total Unique Co-Actors " << count << endl;
    }

    delete[] coActors;
}




int main() {


    AVL tree; 

    HashMap actorMap(101); 
    HashMap genreMap(101); 
    HashMap directorMap(101);


    /*
    we need only few components.
    so just read sequentially and skip cols we dont need using  getline(ss, field, ',');
    */

    ifstream file("movie_metadata.csv");

    string line;
    getline(file, line); 

    while (getline(file, line)) {

        stringstream ss(line);
        string field;

        string director, actor2, genre, actor1, title, actor3, yearstr , ratingstr ;

        getline(ss, field, ',');
        getline(ss, director, ',');

        for (int i = 0; i < 4; i++) {
            getline(ss, field, ',');
        }

        getline(ss, actor1, ',');

        for (int i = 0; i < 2; i++) {
            getline(ss, field, ',');
        }

        getline(ss, genre, ',');

        getline(ss, actor2, ',');


        // for the title we have some movies with , which donot load with this logic so we use .get and .ignore function 

        char firstChar = ss.peek(); 

        if (firstChar == '"') {
            ss.get();  // Skip the opening quote

            getline(ss, title, '"');
            ss.ignore();  
        }
        else {

            getline(ss, title, ',');
        }

        for (int i = 0; i < 2; i++) {
            getline(ss, field, ',');
        }

        getline(ss, actor3, ',');

        for (int i = 0; i < 8; i++) {
            getline(ss, field, ',');
        }

        getline(ss, yearstr, ',');

        getline(ss, field, ',');
        
        getline(ss, ratingstr, ',');

/*
            SKIP the title which have empty values as an edge case 
*/

        if (title.empty()) {
            continue;
        }

//          Clean the title 

        string cleanTitle;
        for (char c : title) {
            
            if (c >= ' ' && c <= '~' && c != '"') {  // Printable ASCII range
                cleanTitle += c;
            }
        }
        title = cleanTitle;

        title.erase(title.find_last_not_of(" ") + 1);


        // now fix the Missing values in the data set 

        if (director.empty()) {
            director = "Unknown";
        }
        if (actor1.empty()) {
            actor1 = "Unknown";
        }
        if (actor2.empty()) {
            actor2 = "Unknown";
        }
        if (actor3.empty()) {
            actor3 = "Unknown";
        }
        if (genre.empty()) {
            genre = "Unknown";
        }
        if (yearstr.empty()) {
            yearstr = "0";
        }
        if (ratingstr.empty()) {
            ratingstr = "0";
        }

        int year = 0;
        float rating = 0.0; 
        try {
            year = stoi(yearstr);
            rating = stof(ratingstr);
        }
        catch (...) {
            year = 0;
            rating = 0.0;
        }

       /* cout << "Title: " << title
            << " | Director: " << director
            << " | Actor1: " << actor1
            << " | Actor2: " << actor2
            << " | Actor3: " << actor3
            << " | Genre: " << genre
            << " | Year: " << year
            << " | Rating: "<< rating << endl;*/

        // Insert for the AVL tree

       tree.insert(director, actor1, actor2, actor3, genre, title, year , rating);
       cout << "Inserted: " << title << endl;


        Node* MovieNode = tree.search(title);

        if (!actor1.empty()) {
            actorMap.Insert(actor1, MovieNode);
        }
        if (!actor2.empty()) {
            actorMap.Insert(actor2, MovieNode);
        }
        if (!actor3.empty()) {
            actorMap.Insert(actor3, MovieNode);
        }

        if (!director.empty()) {
            directorMap.Insert(director, MovieNode);
        }

        // for the genre hashmap we will insert by removing |

        stringstream sss(genre);
        string single; 

        while (getline(sss , single , '|')) {

            if (!single.empty()) {
                genreMap.Insert(single, MovieNode);
            }

        }

    }

    clearScreen();

    // an array is created for storing all the moives and making connections 

    int movieCount = tree.getCount();

    Node** movieArray = new Node * [movieCount];

    tree.getAllMovies(movieArray);


    Graph recGraph(movieCount);                        // create the graph 

    // set movie title

    for (int i = 0; i < movieCount; i++) {
        recGraph.setMovie(i, movieArray[i]->title);
    }

    // build connections 

    recGraph.buildGraph(movieArray, movieCount);
    cout << endl;
    clearScreen();


    // Interactive Menu Simulation 

    int choice; 
    string input; 

    do {
        cout << "======== Movie Data Manager ========" << endl; 
        cout << "1. Search by title " << endl; 
        cout << "2. Search by genre " << endl; 
        cout << "3. Search by Actor " << endl; 
        cout << "4. Get Movie Recommendations " << endl;
        cout << "5. Find Shortest Path " << endl;
        cout << "6. Search by the year range " << endl; 
        cout << "7. Search by the rating range " << endl; 
        cout << "8. Search by director name  " << endl;
        cout << "9. Find Co-Actors for any Actor " << endl; 
        cout << "10. Exit" << endl; 

        cout << "Enter your choice " << endl; 
        cin >> choice; 

        cin.ignore();

        if (choice == 1) {

            cout << "Enter the title of the movie " << endl; 
            getline(cin , input);

            {
                Node* movie = tree.search(input);

                if (movie != NULL) {
                    tree.DisplayNode(movie);
                }

                else {
                    cout << "Movie Not Found " << endl; 
                }
            } 

            cout << endl;
            cout << "Press Enter to return to menu...";
            cin.get();
            
            clearScreen();
        }
        else if (choice == 2) {

            cout << "Enter the genre " << endl; 
            getline(cin, input);

            LinkedList* list = genreMap.GetMovie(input);

            if (list != NULL) {
                list->DisplayList();
                cout << endl;
            }
            else
                cout << "No movie found for the entered genre !" << endl; 

            cout << endl;
            cout << "Press Enter to return to menu...";
            cin.get();

            clearScreen();
        }
        else if (choice == 3) {

            cout << "Enter the actor name " << endl; 
            getline(cin, input);

            LinkedList* list = actorMap.GetMovie(input);

            if (list != NULL) {
                list->DisplayList();
                cout << endl; 
            }
            else
                cout << "No movie found for the given actor name " << endl; 


            cout << endl;
            cout << "Press Enter to return to menu...";
            cin.get();

            clearScreen();

        }
        else if (choice == 4) {
            // Movie recommendations

            cout << "Enter movie title: ";

            getline(cin, input);

            recGraph.getRecommendations(input);

            cout << endl;
            cout << "Press Enter to return to menu...";
            cin.get();

            clearScreen();
        }

        else if (choice == 5) {
        
             // Shortest path

            string start, target;
            cout << "Enter starting movie: ";
            getline(cin, start);

            cout << "Enter target movie: ";
            getline(cin, target);

            recGraph.findShortestPath(start, target);

            cout << endl;
            cout << "Press Enter to return to menu...";
            cin.get();

            clearScreen();
        }

        else if (choice == 6) {
           
            int start, end; 

            cout << "ENter the start year" << endl; 
            cin >> start; 

            if (start < 0 ) {
                cout << "Invalid year entered " << endl;
                continue;
            }

            cout << "ENter the end year " << endl; 
            cin >> end; 

            if (end < 0 ) {
                cout << "Invalid range entered " << endl;
                continue;
            }

            if (start > end) {
                cout << "The starting year cannot be greater then ending year " << endl; 
                cout << endl; 
            }

            YearRange(tree, start, end);

            cin.ignore();
            
            cout << endl;
            cout << "Press Enter to return to menu...";
            cin.get();


            clearScreen();

        }
        else if (choice == 7) {
           
            float min, max; 

            cout << "Enter the min rating (0 - 10)" << endl; 
            cin >> min; 

            if (min < 0 || min > 10) {
                cout << "Invalid range entered " << endl;
                continue;
            }

            cout << "Enter the max rating (0 - 10 )" << endl;
            cin >> max;

            if (max < 0 || max > 10) {
                cout << "Invalid range entered " << endl;
                continue;
            }

            if (min > max) {
                cout << "The min rating cannot be grater than max rating " << endl;
                cout << endl; 
            }

            cin.ignore();

            RatingRangeSearch(tree, min, max);

            cout << endl;
            cout << "Press Enter to return to menu...";
            cin.get();

            clearScreen();

        }
        else if (choice == 8) {
          
            cout << "Enter the director name " << endl; 
            getline(cin, input);

            LinkedList* list = directorMap.GetMovie(input);

            if (list != NULL) {
                list->DisplayList();
            }

            cout << endl;
            cout << "Press Enter to return to menu...";
            cin.get();

            clearScreen();
        }

        else if (choice == 9) {

            cout << "Enter the Actor name " << endl; 
            getline(cin, input);


            CoactorSearch(actorMap, input);


            cout << endl;
            cout << "Press Enter to return to menu...";
            cin.get();

            clearScreen();
        }

        else if (choice == 10) {
            clearScreen();

            cout << "Good Bye :)" << endl; 
            break;

        }
        else {
            cout << "Invalid choice Entered " << endl;
            continue;

            cout << endl;
            cout << "Press Enter to return to menu...";
            cin.get();

            clearScreen();
        }



    } while (choice != 10 );


    file.close();

    delete[] movieArray;
    return 0;
}
