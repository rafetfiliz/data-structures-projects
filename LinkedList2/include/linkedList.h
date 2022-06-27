#ifndef _H
#define _H

#include <iostream>
#include <stdio.h>

using namespace std;

/* @Author
Student Name: Rafet Filiz
Student ID : 150200028
Date: 26.10.2021 */

class Node{
    public:
        Node(char);
        char letter;
        Node* next;
};


class LinkedList{

    Node* head;

    public:
        LinkedList();
        void addNode(char);
        void reorderList();
        void removeDublicates();
        void reverseList();
        void printList();
};

#endif