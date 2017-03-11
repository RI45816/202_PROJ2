/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*****************************************
 ** File:    Player.h
 ** Project: CMSC 202 Project_2, Spring 2017
 ** Author:  Uzoma Uwanamodo
 ** Date:    03/08/2017
 ** Section: 05
 ** E-mail:  uu3@umbc.edu
 ** 
 ** This file contains the header for the Player class.
 ** 
 ** 
 ** 
 ** 
 *********************************************/

#ifndef PLAYER_H //Include guard to protect against multiple declarations
#define PLAYER_H //Include guard

#include <stdio.h>
#include <iostream>
#include <vector>
#include "Card.h"

class Player {
public:
    // Name - Default Constructor
    // Unused
    Player();

    // Name - Constructor (Overloaded)
    // Preconditions: A valid input string for the name, and a valid player number from 1-4
    // Postcondition: A player with a name, an empty hand, and m_lost set to false
    Player(string,int);

    // Name - PlayCard()
    // Desc - Function for moving a card from a player's hand to the discard pile
    // Preconditions - A hand with at least 1 card, a valid index
    // Postconditions - Returns a card from the hand at index i and deletes it from the array
    Card PlayCard(int);

    // Name - LoseCard() 
    // Desc - Function where a player steals card from another player
    // Preconditions - A hand with at least 1 card, a valid index
    // Postconditions - Returns and deletes the card at index i
    Card LoseCard(int);

    // Name - HasCards() 
    // Desc - Function to check if the player has cards
    // Preconditions - None
    // Postconditions - True if the player has cards, false otherwise
    bool HasCards();

    // Name - HasLost()
    // Desc - Function checks to see if player already lost.
    //        If already lost, skips turn.
    // Preconditions - None
    // Postconditions - The state of m_lost
    bool HasLost();

    // Name - HasExtraTurn()
    // Desc - Function checks to see if player has extra turn.
    //        If already lost, skips turn.
    // Preconditions - None
    // Postconditions - The state of m_extraTurn
    bool HasExtraTurn();

    // Name - AddToHand()
    // Desc - Function to add a card to the players hand.
    //        This also detects if the player has drawn a bomb
    // Preconditions - A valid Card input
    // Postconditions - A integer status about the player in regards to the card
    //                  that was just added to his hand (see .cpp for more info)
    int AddToHand(Card);

    // Name - GetName()
    // Desc - Function to get the name of the player
    // Preconditions - None
    // Postconditions - Returns the name of the player
    string GetName();

    // Name - DisplayHand()
    // Desc - Function to print out the cards in the hand
    // Preconditions - None
    // Postconditions - Uses cout to print the player's hand
    void DisplayHand();

    // Name - GetNumberOfCards()
    // Desc - Returns the number of cards in the player's hand
    // Preconditions - None
    // Postconditions - Returns an integer number for the number of cards
    //                  in the player's hand
    int GetNumberOfCards();

    // Name - ReturnBomb()
    // Desc - Returns the bomb card the player drew in the event of a defusal
    // Preconditions - A bomb in the player's hand
    // Postconditions - A card object that is the bomb the player drew
    Card ReturnBomb();

    // Name - HasDefuse()
    // Desc - Checks the hand to see if the player has a defuse card
    // Preconditions - A nonempty hand
    // Postconditions - Returns whether or not there's a defuse card
    bool HasDefuse();
    
    // Name - PlayDefuse()
    // Desc - Searches through the hand and plays a defuse card
    // Preconditions - A nonempty hand with a defuse card
    // Postconditions- Return the defuse card
    Card PlayDefuse();
    
    // Name - SetLost() 
    // Desc - Sets if the player lost or not
    // Preconditions - a bool
    // Postconditions - m_lost is set to the input
    void SetLost(bool);

    // Name - SetExtraTurn()
    // Desc - Sets if the player was attacked or not
    // Preconditions - a bool
    // Postconditions - m_extraTurn is toggled
    void SetExtraTurn(bool);
    
    

private:
    vector<Card> m_hand;
    int m_playerNumber;
    char* m_playerHandle;
    string m_name;
    bool m_lost;
    bool m_extraTurn;
};

#endif // PLAYER_H
