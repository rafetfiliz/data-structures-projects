#include <fstream>
#include <iostream>

#include "StudentsTrie.h"

using namespace std;

/* @Author
Student Name: Rafet Filiz
Student ID : 150200028
Date: 28.12.2021 */

TrieNode::TrieNode (const char& digit){
   this->digit = digit;
   for(int i=0; i<MAX_CHILDREN; children[i++] = NULL); 
};

// Construct a StudentsTrie using the records in 'file_name' 
StudentsTrie::StudentsTrie ( const string& file_name  ) { 
    ifstream student_ids_file ( file_name );   // ifstream object for input file
    string current_student_id;

    root = new TrieNode('r');

    if( student_ids_file.is_open() ) {
        for(int i=1; student_ids_file >> current_student_id; i++ ) {
           insert_id(current_student_id); // YOU HAVE TO IMPLEMENT insert_id() METHOD
        }
        student_ids_file.close();
    }
    else {
        cout << "File: " << file_name << " could NOT be opened!!";
        exit(1);
    }

    student_ids_file.close();
};

void StudentsTrie::trie_traversal(string student_number, TrieNode* current){
   string set_of_digits;
   int num = 0;
   char target;
   bool flag = false;

   for (int i = 0;i < MAX_CHILDREN; i++){
      target = 127;
      if(current->children[i] == NULL){
         if(current->children[0] == NULL){
            cout << student_number << " ";
         }
         break;
      }
      else{
         for(int j = 0;j<MAX_CHILDREN;j++){
            if (current->children[j] == NULL)
               break;
            else{
               for(int k = 0; k < set_of_digits.length(); k++){
                  if (set_of_digits[k] == current->children[j]->digit)
                     flag = true;
               }
               if (flag == false && j == 0){
                  num = j;
                  target = current->children[j]->digit;
               }
               else if (target > current->children[j]->digit && flag == false){
                  num = j;
                  target = current->children[j]->digit;
               }
               flag = false;
            }
         }
         if (current->children[num] != NULL){
            set_of_digits += current->children[num]->digit;
            student_number += current->children[num]->digit;
            trie_traversal(student_number, current->children[num]);
            student_number.pop_back();
         }
      }
   }
}

// Insert a student ID into the StudentsTrie 
void StudentsTrie::insert_id ( const string& student_id ) {
   // IMPLEMENT THIS METHOD
   TrieNode* current = root;

   for(int i = 0; i < 9 ; i++){
      for (int j = 0; j < MAX_CHILDREN; j++){
         if (current->children[j] == NULL){
            const char& digit = student_id[i];
            TrieNode* new_node = new TrieNode(digit);
            current->children[j] = new_node;
            current = current->children[j];
            break;
         }
         else if (student_id[i] == current->children[j]->digit){
            current=current->children[j];
            break;
         }
      }
   }
}; 

// Print Student IDs in Trie in ascending order 
void StudentsTrie::print_trie(){
   // IMPLEMENT THIS METHOD
   trie_traversal("", this->root);
   
}

// StudentsTrie Destructor
StudentsTrie::~StudentsTrie() {
   for (int i=0; i < MAX_CHILDREN; i++){
      if( root->children[i] ) delete root->children[i];
   };
};

