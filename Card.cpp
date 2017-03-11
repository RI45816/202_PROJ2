/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*****************************************
 ** File:    Card.cpp
 ** Project: CMSC 202 Project_2, Spring 2017
 ** Author:  Uzoma Uwanamodo
 ** Date:    03/08/2017
 ** Section: 05
 ** E-mail:  uu3@umbc.edu
 ** 
 ** This file contains the definition for the Card class.
 ** 
 ** 
 ** 
 ** 
 *********************************************/
#include <iostream>
#include "Card.h"

using namespace std;

Card::Card() {
}

//  Card
// Constructor that takes card type number and description and initializes a card object

Card::Card(int cardType, string cardDescription) : m_type(cardType), m_desc(cardDescription) {
}


// GetType
// Returns the type number of the card

int Card::GetType() {
    return m_type;
}

// ToString()
// Returns the description and type of the card.

string Card::ToString() {
    // If the card is a special card, add to the string, otherwise, just return the description
    return m_type < CARD_TYPES_SIZE ? CARD_TYPES[m_type] + ": " + m_desc : m_desc;
//    return m_desc;
}


