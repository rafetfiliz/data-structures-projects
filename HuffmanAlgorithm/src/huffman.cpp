#include <fstream>
#include <iostream>
#include <cstring>
#include <iomanip>
#include <cmath>
#include "huffman.h"

using namespace std;

/* @Author
Student Name: Rafet Filiz
Student ID : 150200028
Date: 14.12.2021 */


int Huffman::findindex(Token *arr,string elem){
	// YOU HAVE TO COMPLETE THIS PART
	// THIS FUNCTION RETURNS THE INDEX OF STRING ON TOKEN ARRAY, IF STRING IS NOT IN TOKEN ARRAY, RETURNS -1
    int i = 0;
    int count = 0;

    for(int j = 0; j< ARRAY_SIZE; j++){
        if(arr[j].symbol == elem)
            count++;
    }
    
    if(count == 0)
        return -1;
    else{
        while(arr[i].symbol != elem){
            i++;
        }
        return i;
    }
}

void Huffman::find_frequencies()
{
    int index = -1;
    ifstream file_obj; //object to read file
    file_obj.open("../input.txt",ifstream::in);
    char symbol = 0;
    if (!file_obj.is_open()) {
        file_obj.open("input.txt",ifstream::in);
        if (!file_obj.is_open()) {
            cerr << "Could not open the file" << endl;
            exit(1);
        }
    }

    while (file_obj.get(symbol)) 
    {     
        string s;
        s.push_back(symbol);
        // YOU HAVE TO COMPLETE THIS PART
        int counter = 0;
        for(index = 0; index<ARRAY_SIZE; index++){
            if(this->token_array[index].symbol == s){
                counter++;
            }
        }

        if(counter == 0){
            for(index = 0; index<ARRAY_SIZE; index++){
                if(this->token_array[index].symbol.size() == 0){
                    this->token_array[index].symbol = s;
                    this->token_array[index].count = 1;
                    this->token_count++;
                    break;
                }
                
            }
        }

        else{
            for(index = 0; index<ARRAY_SIZE; index++){
                if(this->token_array[index].symbol == s){
                    token_array[index].count++;
                }
            }

        }
    }
    file_obj.close();
}

PriorityQueue::PriorityQueue()
{
    head = NULL;
    token_count = 0;
}

void PriorityQueue::push(Node *newnode)
{
	// YOU HAVE TO COMPLETE THIS PART
    token_count++;
    Node* temp_node = new Node;
    temp_node = head;
    if(this->head == NULL){
        head = newnode;
        return;
    }

    while(temp_node->next != NULL && temp_node->next->token.count <= newnode->token.count){
        temp_node = temp_node->next;
    }



    if(temp_node->next != NULL){
        if(temp_node->token.count <= newnode->token.count){
            newnode->next = temp_node->next;
            temp_node->next = newnode;
            return;
        }
        else{
            newnode->next = temp_node;
            head = newnode;
            return;
        }
    }

    else
    {   if(temp_node->token.count <= newnode->token.count){
            temp_node->next = newnode;
            return;
        }
        else{
            newnode->next = temp_node;
            head = newnode;
            return;
        }

    }
}

Node* PriorityQueue::pop()
{
    // YOU HAVE TO COMPLETE THIS PART
    Node* popped_node = this->head;
    head = head->next;
    popped_node->next = NULL;
    return popped_node;
}

void Huffman::get_priority_queue()
{
    // YOU HAVE TO COMPLETE THIS PART  
    for (int i = 0; i < this->token_count; i++)
    {
        Node* tmp_node = new Node;
        tmp_node->token = this->token_array[i];
        this->priority_queue.push(tmp_node);
    }
}

HuffmanBinaryTree::HuffmanBinaryTree()
{
    root = NULL;
}

Node * HuffmanBinaryTree::merge(Node *node1, Node *node2)
{
    // YOU HAVE TO COMPLETE THIS PART
    Node* new_node = new Node;
    string new_symbol = node1->token.symbol + node2->token.symbol;
    int new_count = node1->token.count + node2->token.count;
    new_node->token.symbol = new_symbol;
    new_node->token.count = new_count;
    
    new_node->left = node1;
    new_node->right = node2;
  
    return new_node;
}

void HuffmanBinaryTree::delete_postorder_traversal(Node *traversal)
{
    if(traversal!=NULL) 
    {
        delete_postorder_traversal(traversal->left);
        delete_postorder_traversal(traversal->right);
        delete traversal;
    }
}

HuffmanBinaryTree::~HuffmanBinaryTree()
{
    delete_postorder_traversal(root);
    cout<<"Code with no memory leak ;)"<<endl;
    root = NULL;
}

void Huffman::get_huffman_tree()
{
    // YOU HAVE TO COMPLETE THIS PART 
    while(this->priority_queue.get_count() > 1){
        Node* node1 = this->priority_queue.pop();
        Node* node2 = this->priority_queue.pop();
        Node* new_node = this->huffman_binary_tree.merge(node1, node2);
        this->priority_queue.push(new_node);
    }
    this->huffman_binary_tree.root = this->priority_queue.pop();
}

void Huffman::get_codes(Node *traversal,string codepart)
{    
    // YOU HAVE TO COMPLETE THIS PART
    // A RECURSIVE FUNCTION APPENDS CODEPART STRING 1 OR 0 ACCORDING TO THE HUFFMAN BINARY TREE
    if (traversal->left != NULL)
    {
        get_codes(traversal->left,codepart+"0");
    }
    if (traversal->right != NULL)
    {
        get_codes(traversal->right,codepart+"1");
    }
    if (traversal->left == NULL && traversal->right == NULL)
    {
        int leaf_index = findindex(token_array,traversal->token.symbol);
        token_array[leaf_index].code = codepart;
    }  
}

string Huffman::return_code(string target)
{
    int index = findindex(token_array,target);
    return token_array[index].code;
}

double Huffman::calculate_compression_ratio()
{
    double bit_required_before = 0;
    for(int i=0;i<token_count;i++)
        bit_required_before += token_array[i].count * 8;
    double bit_required_after = 0;
    for(int i=0;i<token_count;i++)
        bit_required_after += token_array[i].count * token_array[i].code.length();
    return bit_required_before / bit_required_after;
}

int PriorityQueue::get_count(){
    int count = 0;
    Node* current = head;
    while (current != NULL) 
    { 
        count++; 
        current = current->next; 
    } 
    return count;
}