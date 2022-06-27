#include "team.h"
using namespace std;

/* @Author 
Student Name:  Rafet Filiz
Student ID :  150200028
Date: 12.10.2021 */

Team::Team(){};
string Team::getName() { return name; };
int Team::getCurrentSize() { return current_size; };
int Team::getId() { return id; };
int Team::getCapacity() { return capacity; };
Player *Team::getPlayer(int number)
{
    for (int i = 0; i < current_size; i++)
    {
        if (player_list[i].getNumber() == number)
            return &player_list[i];
    }
    return nullptr;
};
Player *Team::getPlayerList()
{
    return player_list;
};
void Team::setName(string new_name) { name = new_name; };
void Team::setId(int newId) { id = newId; };
void Team::listPlayers()
{
    cout << "Number"
         << " Name"
         << " Age"
         << " #Goals"
         << " #Assists"
         << " #Matches" << endl;
    ;
    for (int i = 0; i < current_size; i++)
    {
        cout << player_list[i].getNumber() << " - ";
        cout << player_list[i].getName() << " - ";
        cout << player_list[i].getAge() << " - ";
        cout << player_list[i].getGoalNumber() << " - ";
        cout << player_list[i].getAssistNumber() << " - ";
        cout << player_list[i].getMatchNumber() << endl;
    }
};
void Team::addPlayer(int number, string name, int age, int goals, int assists, int matches)
{
    if (this->capacity == 0)
    {
        this->capacity = 3;
        this->player_list = new Player[this->capacity];
    }

    else if (this->current_size == this->capacity)
    {
        int old_capacity = capacity;
        capacity = capacity * 2;
        Player* doubled_list = new Player[capacity];
        for (int i = 0;i<old_capacity;i++)
        {
            doubled_list[i] = player_list[i];
        }
        delete[] player_list;
        player_list = doubled_list;
    }
    


    for(int i=0;i<capacity;i++)
    {
        if (player_list[i].getNumber() == 0)
        {
            player_list[i].setNumber(number);
            player_list[i].setName(name);
            player_list[i].setAge(age);
            player_list[i].setGoalNumber(goals);
            player_list[i].setAssistNumber(assists);
            player_list[i].setMatchNumber(matches);
            current_size += 1;
            break;
        }
    
    }
  
    return;
};

bool Team::checkNumber(int number)
{
     for (int i = 0; i < current_size; i++)
    {
        if (player_list[i].getNumber() == number)
            return true;
    }
    return false;
}