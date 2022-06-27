#include <iostream> 
#include <stdlib.h>
#include <string>
#include <fstream>

#include "linkedList.h"

using namespace std;

/* @Author
Student Name: Rafet Filiz
Student ID : 150200028
Date: 26.10.2021 */


int row_number_of_text(char* text_path){   // This is the function for reading number of rows of the text file.
    ifstream text(text_path);
    int rows;
    string str;
    if (text.is_open()){
        while (!text.eof()){
            getline(text, str);
            rows++;
        }
    }
    text.close();
    return rows;
}

void read_letter(char* arr, char* text_path){ // This is the function for reading letters from a text file and pass them in an array.
    ifstream text(text_path);
    char letter;
    if (text.is_open()){
        int i = 0;
        while(text>>letter){
            *(arr+i) = letter;
            i++;
        }
    }
    text.close();
}


int main(int argc, char* argv[]) {
	system("clear");// make this line as comment if you are compiling on Linux or Mac
	//system("cls"); // make this line as comment if you are compiling on Windows
    LinkedList newLinkedList;

    int number_of_rows = row_number_of_text(argv[1]);
    char* letters = new char[number_of_rows];
    read_letter(letters, argv[1]);

    for(int i=0; i< number_of_rows; i++){
        newLinkedList.addNode(letters[i]);
    }


    cout<<"Readed letters in linked list: ";
    newLinkedList.printList();

    newLinkedList.reorderList();
    cout<<"After reordering: ";
    newLinkedList.printList();

    newLinkedList.removeDublicates();
    cout<<"After removing dublicates: ";
    newLinkedList.printList();
    
    newLinkedList.reverseList();
    cout<<"Reversed list: ";
    newLinkedList.printList();

    delete[] letters;
    letters = NULL;

    return EXIT_SUCCESS;
}