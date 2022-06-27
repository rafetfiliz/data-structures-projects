#include <iostream>
#include <stdio.h>

#include "linkedList.h"

using namespace std;

/* @Author
Student Name: Rafet Filiz
Student ID : 150200028
Date: 26.10.2021 */

Node::Node(char data){
    this->letter = data;
    this->next = NULL;
}

LinkedList::LinkedList(){
    head = NULL;
}

void LinkedList::addNode(char character){ // I created this function for adding nodes to the linked list.
    Node* new_node = new Node(character);
    if(head == NULL){
        head = new_node;
    }
    else{
        Node* p = head;
        while(p->next != NULL){
            p = p->next;
        }
        p->next = new_node;
    }
}

void LinkedList::reorderList(){
    //FILL THIS FUNCTION ACCORDINGLY
    Node* current_node = head;
    Node* next_node = current_node->next;
    bool flag = false;
    while(current_node != NULL && next_node != NULL){
        if( current_node->letter > next_node->letter ){
            char temp_letter = current_node->letter;
            current_node->letter = next_node->letter;
            next_node->letter = temp_letter;
            flag = true;    
        }
        current_node = current_node->next;
        if(current_node) next_node = current_node->next;

        if((current_node == NULL) || (next_node == NULL)){
            if (flag == true){
                current_node = head;
                next_node = current_node->next;
                flag = false;
            }
        } 
    }
};

void LinkedList::removeDublicates(){
    //FILL THIS FUNCTION ACCORDINGLY
    Node* current_node = head;
    while(current_node != NULL && current_node->next != NULL){
        while (current_node->letter == current_node->next->letter){
            Node* duplicate = current_node -> next;
            if (duplicate->next == NULL) {
                current_node->next = NULL;
                delete duplicate;
                break;
            }
            current_node->next = duplicate->next;    
            duplicate->next = NULL;
            delete duplicate;         
        }

        if (current_node->next != NULL){
        current_node = current_node->next;
        }
    
    }

};

void LinkedList::reverseList(){
    //FILL THIS FUNCTION ACCORDINGLY
    if (head == NULL) return;
    Node *prev_node = NULL, *current_node = NULL, *next_node  = NULL;
    current_node = head;
    
    while(current_node != NULL){
        next_node = current_node->next;
        current_node->next = prev_node;
        prev_node = current_node;
        current_node = next_node;
    }
    head = prev_node;   
};

void LinkedList::printList(){
    Node* temp = head;
    while(temp != NULL){
        cout<<temp->letter<<" ";
        temp = temp->next;
    }
    cout<<endl;
};