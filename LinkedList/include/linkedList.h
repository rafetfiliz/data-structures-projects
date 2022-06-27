#ifndef _H
#define _H

#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

/* @Author 
Student Name: Rafet Filiz
Student ID : 150200028 
Date: 10/11/2021 */

class materialNode{
    public:
        char id;
        int weight;
        materialNode* next;
};

class wagonNode{
    public:
        int wagonId;
        void sortMaterials();
        void removeMaterial();
        materialNode* material;
        wagonNode* next;
};

class Train{  

    wagonNode* head;
    
    public:
        void create();
        void addMaterial(char,int);
        void deleteFromWagon(char, int); 
        void printWagon(); //Prints wagon info
        void addWagon();
        void deleteWagon();
        void reverseTrain();
};

#endif