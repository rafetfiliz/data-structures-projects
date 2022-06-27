//run: g++ src/main.cpp src/tree.cpp -I include -o blg223e_hw2

#include <cstdlib>
#include <iostream>
#include <fstream>
#include "tree.h"

using namespace std;

/* @Author
Student Name: Rafet Filiz
Student ID: 150200028
E-mail: filiz20@itu.edu.tr
Date: 29.12.2021
*/

void read_file(string file_name, Tree* my_tree) // Function to read file and construct tree-like data structure
{
    ifstream read_text(file_name);
    ifstream read_number(file_name);
    

    string source_city, dest_city, text_from_file, temp;
    int distance;
    for(int i = 0; read_text >> text_from_file; i++)
    {
        if(i % 3 == 0)
        {
            read_number >> temp;
            source_city = text_from_file;
        }

        else if(i % 3 == 1)
        {
            read_number >> temp;
            dest_city = text_from_file;    
        }

        else if(i % 3 == 2)
        {
            read_number >> distance;
            my_tree->addCity(source_city, dest_city, distance);
        }
    }
    read_text.close();
    read_number.close();
}



int main(int argc, char** argv){

    string file1 = argv[1];
    string file2 = argv[2];
    Tree* tree1 = new Tree;
    Tree* tree2 = new Tree;
    read_file(file1, tree1);
    read_file(file2, tree2);
    tree1->traverse();
    tree2->traverse();
    tree1->prune();
    tree2->prune();
    string meeting_point;
    int duration_cost = inf;
    
    for (map<string, int>::iterator it = tree1->CITY_DIST.begin(); it != tree1->CITY_DIST.end(); it++) {
        int dist1 = tree1->CITY_DIST[it->first];
        int dist2 = inf;
        if (tree2->CITY_DIST.find(it->first) != tree2->CITY_DIST.end()){
            dist2 = tree2->CITY_DIST[it->first];
        }
        
        if(dist1+dist2 < duration_cost){
            duration_cost = dist1 + dist2;
            meeting_point = it->first;
        }
    }
    cout << "FRIEND-1: ";
    tree1->preorder(tree1->root);
    cout << endl;
    cout << "FRIEND-2: ";
    tree2->preorder(tree2->root);
    cout << endl;
    cout << "MEETING POINT: " << meeting_point << endl;
    cout << "TOTAL DURATION COST: " << duration_cost << endl;
    return EXIT_SUCCESS;
}

