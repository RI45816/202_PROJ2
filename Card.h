/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*****************************************
 ** File:    Card.h
 ** Project: CMSC 202 Project_2, Spring 2017
 ** Author:  Uzoma Uwanamodo
 ** Date:    03/08/2017
 ** Section: 05
 ** E-mail:  uu3@umbc.edu
 ** 
 ** This file contains the header for the Card class.
 ** 
 ** 
 ** 
 ** 
 *********************************************/

#ifndef CARD_H
#define CARD_H

#include <string>


using namespace std;


const int CARD_TYPES_SIZE = 6;
const string CARD_TYPES[CARD_TYPES_SIZE] = {"Exploding Kitten","Defuse","Attack","Skip","See into the Future","Shuffle"};



class Card {
public:
    // Default Constructor
    // Unused
    Card();

    // Name - Constructor
    // Preconditions - valid int type for type of card, string name
    // Postcontions - A card object with the given input values
    Card(int, string);

    // Name -  GetType() - Returns the type of card
    // Preconditions - an initialized card
    // Postconditions - integer representing the type of card
    // (see reference chart below)
    int GetType();

    // Name - ToString() - Returns a string representation of the card
    // Preconditions - An intitalized card
    // Postcontitions - Returns a string containing the representation of the card
    string ToString();

private:
    // 0 Bomb
    // 1 Defuse
    // 2 Attack
    // 3 Skip
    // 4 Peek
    // 5 Shuffle
    // 6,7,8,9 Normal Cards
    int m_type; //Defined by the types of cards above
    string m_desc; //Description comes from deck.txt file or bomb.txt file
};

#endif // CARD_H
