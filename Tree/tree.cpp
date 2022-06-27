#include <iostream>
#include "tree.h"

/* @Author
Student Name: Rafet Filiz
Student ID: 150200028
E-mail: filiz20@itu.edu.tr
Date: 29.12.2021
*/

Tree::Tree(){
    this->root = NULL;
}

Node* findCity(Node* current_node, string city_name){ // Function to check if a city is in the tree and return its node
    if(current_node != NULL){
        if(current_node->cityName == city_name)
            return current_node;
        else{
            Node* foundNode = findCity(current_node->left, city_name);
            if(foundNode == NULL) {
                foundNode = findCity(current_node->right, city_name);
            }
            return foundNode;
        }
    }
    else
        return NULL;   
}

void Tree::addCity(string city_name1, string city_name2, int dist){
    Node* current = this->root;
    CITY_DIST[city_name1] = inf;
    CITY_DIST[city_name2] = inf;

    if(this->root == NULL){
        Node* new_node = new Node;
        Node* new_node2 = new Node;
        this->root = new_node;
        this->root->left = new_node2;
        this->root->cityName = city_name1;
        this->root->distance_to_left = dist;
        this->root->left->cityName = city_name2;
    }
    else{
        if(findCity(this->root, city_name2) == NULL){
            Node* this_city = findCity(this->root, city_name1);
            Node* new_node = new Node;
            if(this_city->left == NULL){
                this_city->left = new_node;
                this_city->left->cityName = city_name2;
                this_city->distance_to_left = dist;
            }
            else{
                this_city->right = new_node;
                this_city->right->cityName = city_name2;
                this_city->distance_to_right = dist;
            }
        }
        else{
            Node* this_city = findCity(this->root, city_name1);
            if(this_city->left == NULL){
                this_city->left = findCity(this->root, city_name2);
                this_city->distance_to_left = dist;
            }
            else{
                this_city->right = findCity(this->root, city_name2);
                this_city->distance_to_right = dist;
            }
        }
    }
    
}

void Tree::traverse(){
    this->root->distance_to_root = 0;
    this->CITY_DIST[this->root->cityName] = 0;
    this->_traverse(this->root);
}

void Tree::_traverse(Node* current){
    if(current == NULL)
        return;

    if(current->left != NULL){
        if(current->distance_to_root + current->distance_to_left < current->left->distance_to_root){
            current->left->prev = current;
            current->left->distance_to_root = current->distance_to_root + current->distance_to_left;
            CITY_DIST[current->left->cityName] = current->left->distance_to_root;
        }
    }

    if(current->right != NULL){
        if(current->distance_to_root + current->distance_to_right < current->right->distance_to_root){
            current->right->prev = current;
            current->right->distance_to_root = current->distance_to_root + current->distance_to_right;
            CITY_DIST[current->right->cityName] = current->right->distance_to_root;
        }
    }

    this->_traverse(current->left);
    this->_traverse(current->right);
}

void Tree::prune(){
    this->_prune(this->root);
}

void Tree::_prune(Node* current){
    if(current == NULL)
        return;
    if(current->left != NULL){
        if(current->left->prev != current){
            current->left = NULL;
        }
    }
    if(current->right != NULL){
        if(current->right->prev != current){
            current->right = NULL;
        }
    }
    _prune(current->left);
    _prune(current->right);
}

void Tree::preorder(Node* node){
    if (node != NULL) {
       cout << node->cityName << " ";
       preorder(node->left);
       preorder(node->right);
   }
}