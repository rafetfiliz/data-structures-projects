#include <string>
#include <map>

/* @Author
Student Name: Rafet Filiz
Student ID: 150200028
E-mail: filiz20@itu.edu.tr
Date: 29.12.2021
*/

using namespace std;
const long long inf = 1000000000;

class Node{
    public:
        string cityName;
        Node* left;
        Node* right;
        Node* prev = NULL;
        int distance_to_left = 0;
        int distance_to_right = 0;   
        int distance_to_root = inf;   
};

class Tree{
    public:
        Tree();
        ~Tree();
        Node* root;
        map<string, int> CITY_DIST;
        void addCity(string, string, int); // Function to add a city to the tree
        void traverse();  // Function to traverse the tree
        void _traverse(Node*);
        void preorder(Node*); // Function to print preorder traversal of the tree
        void prune(); // Function to prune the tree
        void _prune(Node*);
        
};