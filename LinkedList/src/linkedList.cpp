#include <iostream>
#include <stdio.h>
#include <string.h>

#include "linkedList.h"

using namespace std;

/* @Author 
Student Name: Rafet Filiz
Student ID : 150200028 
Date: 10/11/2021 */

void Train::create(){
    head = NULL;
}; 

void Train::addMaterial(char material, int weight){    
    //FILL THIS FUNCTION ACCORDINGLY  

    if (head == NULL){
            addWagon();
        }
    
    
    wagonNode* current = head;
    materialNode* p = current->material;
    int remaining = weight;

    while(remaining > 0){
        
       
        if(p == NULL){
            materialNode* new_material = new materialNode();
            p = new_material;
            p->id = material;
            current->material = p;
        }
        
        else{
            while(p->id != material)  
            {
                if (p->next != NULL){
                    p = p->next;
                }
                else{
                    materialNode* add_material = new materialNode(); 
                    p->next = add_material;
                    p->next->id = material;
                    p->next->weight = 0; 
                    p = p->next;
                }           
            }
        }
        
        if(2000-(p->weight) >= weight){
            p->weight += weight;
            remaining = 0;
        }

        else{
            remaining = weight - (2000-(p->weight));
            p->weight = 2000;
        }

        current->sortMaterials();

        if (remaining != 0)
        {
            if(current->next != NULL){
                current = current->next;
                
            }
            else{
                addWagon();
                current = current->next;
            }
            p = current->material;
            weight = remaining;
        }
    }  
}; 


void Train::deleteFromWagon(char material, int weight){
    
    //FILL THIS FUNCTION ACCORDINGLY
    this->reverseTrain();

    wagonNode* current = head;
    materialNode* p = current->material;

    int remaining = weight;

    
    while(remaining > 0){
        while(p->id != material)  
        {
            if (p->next != NULL){
                p = p->next;
            }
            else{
                current = current->next;
                p = current->material;
            }
        }

        if(p->weight >= remaining){
            p->weight -= remaining;
            remaining = 0;
            
        }
        else{
            remaining = remaining - p->weight;
            p->weight = 0;
        }

        if(p->weight == 0){
            current->removeMaterial(); 
        }

        if(remaining > 0){
            current = current -> next; 
            p = current->material;
            weight = remaining;
            }
        this->deleteWagon();
    }
    this->reverseTrain();
    
    
 
};  

void Train::addWagon(){
    wagonNode* newWagon = new wagonNode();
    if(head == NULL){
        head = newWagon;
        newWagon->wagonId = 1;
    }
    else{
        int s = 1;
        wagonNode* p = head;
        while(p->next != NULL){
            p = p->next;
            s++;
        }
        p->next = newWagon;
        newWagon->wagonId = s+1;
        
    }
}

void Train::deleteWagon(){
    this->reverseTrain();
    wagonNode* current = head;

    if(current->material == NULL && current == head && current->next != NULL){
        wagonNode* p = current;
        head = p->next;
        current = p->next;
        p->next = NULL;
        delete p;
    }

    else if (current->material == NULL && current == head && current->next == NULL){
        head = NULL;
        delete head;
        return;
    }

    else if (current->next->next == NULL && current->next->material == NULL)
    {
        wagonNode* p = current->next;
        current->next = NULL;
        delete p;
        return;
    }

    else{
        while(current->next->next != NULL) {
            if(current->next->material == NULL && current->next->next == NULL){
                wagonNode* p = current->next;
                current->next = NULL;
                delete p;
                return;
            }

            else if(current->next->material == NULL && current->next->next != NULL){
                wagonNode* p = current->next;
                current->next = p->next;
                p->next = NULL;
                delete p;
                return;
            }
            current = current->next;
        }

        
    }
    this->reverseTrain();
}

void Train::printWagon(){
    wagonNode* tempWagon = head;

    if(tempWagon == NULL){
            cout<<"Train is empty!!!"<<endl;
            return;
    }

    while(tempWagon != NULL){
        materialNode* tempMat = tempWagon->material;
        cout<<tempWagon->wagonId<<". Wagon:"<<endl; 
        while (tempMat != NULL){
            cout<<tempMat->id<<": "<<tempMat->weight<<"KG, "; 
            tempMat = tempMat->next;  
        }
        cout<<endl; 
        tempWagon = tempWagon->next;
    }
    cout<<endl;
}; 

void Train::reverseTrain(){ 
    if (head == NULL) return;
    wagonNode* prev_wagon  = NULL;
    wagonNode* current_wagon  = NULL;
    wagonNode* next_wagon  = NULL;
    current_wagon = head;

    while(current_wagon != NULL){
        next_wagon = current_wagon->next;
        current_wagon->next = prev_wagon;
        prev_wagon = current_wagon;
        current_wagon = next_wagon;
    }
    head = prev_wagon;

}

void wagonNode::sortMaterials(){ 
    materialNode* current_material = this->material;  
    materialNode* next_material = current_material->next;
    bool exchange = false;
    
    while(current_material != NULL && next_material != NULL){
        if(current_material->id > next_material->id){
            char temp_id = current_material->id;
            current_material->id = next_material->id;
            next_material->id = temp_id;
            int temp_weight = current_material->weight;
            current_material->weight = next_material->weight;
            next_material->weight = temp_weight;
            exchange = true; 
        }

        current_material = current_material->next;
        if(current_material != NULL){
            next_material = current_material->next;
        }

        if(current_material == NULL || next_material == NULL){
            if(exchange == true){
                current_material = this->material;
                next_material = current_material->next;
                exchange = false;
            }
        }

    }

}

void wagonNode::removeMaterial(){
    materialNode* prev = new materialNode;
    materialNode* current = this->material;

    if(current->weight == 0 && current->next == NULL){
        this->material = NULL;
        delete current;
    }

    else if(current->weight == 0 && current->next != NULL){
        materialNode* temp = new materialNode;
        temp = current;
        this->material = this->material->next;
        current = current->next;
        temp->next = NULL;
        delete temp;
    }

    else{
        prev = current;
        current = current->next;
        if(current->weight == 0 && current->next == NULL){
            materialNode* temp = new materialNode;
            temp = current;
            current = prev;
            current->next = NULL;
            delete temp;
        }

        else if(current->weight == 0 && current->next != NULL){
            materialNode* temp = current;
            current = current->next;
            prev->next = current;
            temp->next = NULL;
            delete temp;   
        }
    
        while(current->weight != 0){
            prev = current;
            current = current->next;
            if(current->weight == 0 && current->next != NULL){
                materialNode* temp = new materialNode;
                temp = current;
                prev->next = current->next;
                current = current->next;
                temp->next = NULL;
                delete temp;
            }
            else if(current->weight == 0 && current->next == NULL){
                materialNode* temp = new materialNode;
                temp = current;
                current = prev;
                current->next = NULL;
                delete temp;
            }

            if(current->weight != 0 && current->next == NULL){
                break;
            }
        }

    }
}