/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*****************************************
 ** File:    Player.cpp
 ** Project: CMSC 202 Project_2, Spring 2017
 ** Author:  Uzoma Uwanamodo
 ** Date:    03/08/2017
 ** Section: 05
 ** E-mail:  uu3@umbc.edu
 ** 
 ** This file contains the definition for the Player class.
 ** 
 ** 
 ** 
 ** 
 *********************************************/
#include <iostream>
#include <string>

#include "Player.h"

using namespace std;

Player::Player() {
}

Player::Player(string playerName, int playerNumber) : m_name(playerName), m_playerNumber(playerNumber) {
    //    sprintf(m_playerNumber,"%d",playerNumber);
    m_playerHandle = new char[10 + m_name.size()];
    sprintf(m_playerHandle, "Player %d: %s", m_playerNumber, m_name.c_str());
    SetLost(false);
    SetExtraTurn(false);
}

// SetLost
// Set the players to to whether or not they've lost

void Player::SetLost(bool lost) {
    m_lost = lost;
}

// HasLost
// Return whether or not the player has lost

bool Player::HasLost() {
    return m_lost;
}


// AddToHand
// Given a card, add it to the hand

int Player::AddToHand(Card card) {
    m_hand.push_back(card);
    return m_hand.size();
}


// GetName
// Return the name of the player

string Player::GetName() {
    return m_playerHandle;
    //    return "Player " + m_playerNumber + ": " + m_name;
}

// GetNumberOfCards
// Return the amount of card's in the player's hand

int Player::GetNumberOfCards() {
    return m_hand.size();
}


// DisplayHand
// Display the contents of the player's hand

void Player::DisplayHand() {
    cout << endl;
    for (int i = 0; i < GetNumberOfCards(); i++)
        cout << i << ". " << m_hand[i].ToString() << endl;
}

// PlayCard
// Take the card the player chose and play

Card Player::PlayCard(int index) {
    Card selectedCard = m_hand[index];
    m_hand.erase(m_hand.begin() + index);
    return selectedCard;
}


// SetExtraTurn
// Given a boolean, set m_extraTurn

void Player::SetExtraTurn(bool extraTurn) {
    m_extraTurn = extraTurn;
}


// HasExtraTurn
// Return value indicating whether or not player has an extra turn

bool Player::HasExtraTurn() {
    return m_extraTurn;
}

// LostCard
// Given the index, return the card at that index and remove it from the hand

Card Player::LoseCard(int index) {
    Card selectedCard = m_hand[index];
    m_hand.erase(m_hand.begin() + index);
    return selectedCard;
}

// HasCard
// Returns whether or not the hand is empty

bool Player::HasCards() {
    return !m_hand.empty();
}


// HasDefuse
// Return whether or not there is a defuse card in the hand

bool Player::HasDefuse() {
    for (int i =0; i<m_hand.size(); i++)
        if (m_hand[i].GetType() == 1)
            return true;
    return false;
}

// PlayDefuse
// Return the defuse card
Card Player::PlayDefuse() {
    for (int i = 0; i<m_hand.size(); i++)
        if (m_hand[i].GetType()==1)
            return PlayCard(i);
}


// ReturnBomb
// Return the bomb card
Card Player::ReturnBomb() {
    for (int i = 0; i<m_hand.size(); i++)
        if (m_hand[i].GetType()==0)
            return LoseCard(i);
}
