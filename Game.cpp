/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*****************************************
 ** File:    Game.cpp
 ** Project: CMSC 202 Project_2, Spring 2017
 ** Author:  Uzoma Uwanamodo
 ** Date:    03/08/2017
 ** Section: 05
 ** E-mail:  uu3@umbc.edu
 ** 
 ** This file contains the definition for the Game class.
 ** 
 ** 
 ** 
 ** 
 *********************************************/
#include <iostream>
#include <fstream>
#include "Game.h"
#include "Player.h"
#include <time.h>

using namespace std;

Game::Game() : m_turn(0) {
    // Welcome Player
    cout << "MEOWMEOWMEOWMEOWMEOWMEOWMEOWMEOWMEOW" << endl;
    cout << "Welcome to Exploding Kittens" << endl;
    cout << "A Game By Elan Lee, Shane Small, and Matthew Inman" << endl;
    cout << "MEOWMEOWMEOWMEOWMEOWMEOWMEOWMEOWMEOW" << endl;

    // Iniitalize Players
    cout << "\nHow many players would you like?" << endl;

    do {
        cout << "Choose 2 - 4 players:" << endl;
        cin >> m_numPlayers;
    } while (m_numPlayers < 2 || m_numPlayers > 4);

    SetNumPlayers(m_numPlayers);

    // Load the deck
    LoadDeck(DECK_NAME);

    // Shuffle the cards
    cout << "\nShuffling the cards" << endl;
    Shuffle();

    // Deal the players
    cout << "Dealing" << endl;
    DealPlayers();

    // Add and shuffle the bomb cards
    cout << "Shuffling in the exploding kittens!" << endl;
    AddBombCards(BOMB_NAME);
    Shuffle();

    // Begin Game
    PlayGame();
}

// SetNumPlayers
// Given a number of players, name and initialize them

void Game::SetNumPlayers(int numPlayers) {

    // Name and initialize players
    for (int i = 0; i < numPlayers; i++) {
        cout << "\nWhat is the name of Player " << i + 1 << "?:" << endl;
        string playerName; // Contains the name of the player
        cin >> playerName;
        m_players[i] = Player(playerName, i + 1);
    }
}




// LoadDeck
// Given a valid filename, load the deck

int Game::LoadDeck(string filename) {
    ifstream deck(filename.c_str()); // Variable that contains the deck file
    int lineIndicator = 0; // Indicates whether the current line is the card type (0) or the card description (1)
    string line; // Stores the data for the line being read
    int typeNumber; // The type number of the card

    // Read the entire file and parse it into new cards
    // Add the new cards to the deck
    while (getline(deck, line)) {
        if (lineIndicator)
            m_deck.push_back(Card(typeNumber, line));
        else
            typeNumber = atoi(line.c_str());
        lineIndicator ^= 1;
    }
    return m_deck.size();
}

// Shuffle
// Given a deck, shuffle it

void Game::Shuffle() {
    //    srand(RAND_SEED); // Randomize seed
    srand(time(NULL));
    int size = m_deck.size(); // Size of the deck

    // Shuffle the deck 10 times by swapping each element for a random element
    for (int i = 0; i < SHUFFLE_NUMBER; i++)
        for (int j = 0; j < size; j++) {

            // Swap the cards
            int newIndex = rand() % size; // index of element to be swapped with current element
            Card temp = m_deck[j];
            m_deck[j] = m_deck[newIndex];
            m_deck[newIndex] = temp;
        }
}


// DealPlayers
// Deal each player a hand of 4 cards

void Game::DealPlayers() {
    for (int i = 0; i < m_numPlayers; i++)
        for (int j = 0; j < INIT_CARDS; j++)
            m_players[i].AddToHand(DrawCard());
}

// DrawCard
// Get the top card from the deck

Card Game::DrawCard() {
    Card currentCard = m_deck.back(); // The card at the top of the deck
    m_deck.pop_back(); // Remove the card from the deck
    return currentCard;
}

// AddBombCards
// Given a valid filename, load the bomb cards

int Game::AddBombCards(string filename) {
    ifstream deck(filename.c_str()); // Variable that contains the bomb file
    int lineIndicator = 0; // Indicates whether the current line is the card type (0) or the card description (1)
    string line; // Stores the data for the line being read
    int typeNumber; // The type number of the card
    int numBombs = 0; // The number of bombs already in the deck

    // Read the entire file and parse it into new cards
    // Add the new cards to the deck
    while (getline(deck, line) && numBombs != m_numPlayers) {
        if (lineIndicator) {
            m_deck.push_back(Card(typeNumber, line));
            numBombs++;
        } else
            typeNumber = atoi(line.c_str());
        lineIndicator ^= 1;
    }
    return m_deck.size();
}

// Peek
// Take a look at the next [const] amount of cards

void Game::Peek() {

    // Tailor the response message
    if (PEEK_NUM < m_deck.size())
        cout << "The next " << PEEK_NUM << " cards are:" << endl;
    else
        cout << "The remaining " << m_deck.size() << " cards are:" << endl;

    // Retrieve the [const int] topmost cards
    for (int i = 1; i < (PEEK_NUM < m_deck.size() ? PEEK_NUM : m_deck.size()) + 1; i++)
        cout << m_deck[m_deck.size() - i].ToString() << endl;
}


// HandleCard
// Given a card, handle it according to it's description

int Game::HandleCard(int player) {
    Card playedCard = m_discard.back(); // Retrieve recently played card from the dispatch
    int cardType = playedCard.GetType(); // Retrieve card's type number
    Player* currentPlayer = GetPlayer(player); // Retrieve the current player
    cout << "Player: " << player << endl;
    switch (cardType) {
        case 1:
            cout << "Perhaps you should save this for an emergency" << endl;
            m_discard.pop_back();
            currentPlayer->AddToHand(playedCard);
        case 2: // Attack Card
        {
            Player* attackedPlayer = GetPlayer((player + 1) % m_numPlayers); // Retrieve the attacked player
            cout << "You attacked " << attackedPlayer->GetName() << "!" << endl;
            attackedPlayer->SetExtraTurn(true);
        }
            return 1;
            break;
        case 3: // Skip Card
            cout << currentPlayer->GetName() << " skips their turn" << endl;
            return 1;
            break;
        case 4: // See into the future card
            Peek();
            return 0;
            break;
        case 5: // Shuffle Card
            Shuffle();
            cout << "Shuffling the cards" << endl;
            return 0;
            break;
        default: // Cat card

            // If the card is second in a pair, steal a card from another player
            if (m_discard[m_discard.size() - 2].GetType() == cardType) {
                cout << "You played a pair! You can now steal a card from another player!" << endl;
                int victimNumber; // Index number of the player to steal from

                // Qualify player number
                int remainingPlayersWithCards; // Track how many remaining players there are with cards other than the current player
                do {
                    cout << "Select a Player" << endl;
                    for (int i = 0; i < m_numPlayers; i++)
                        if (i != player && !m_players[i].HasLost() && m_players[i].HasCards()) {
                            cout << i << ". " << m_players[i].GetName() << endl;
                            remainingPlayersWithCards++;
                        }
                    if (remainingPlayersWithCards)
                        cin >> victimNumber;
                    else {
                        cout << "There are no other players with cards" << endl;
                        m_discard.pop_back();
                        currentPlayer->AddToHand(playedCard);
                        return 0;
                    }
                } while (victimNumber < 0 || victimNumber >= m_numPlayers || m_players[victimNumber].HasLost() || !m_players[victimNumber].HasCards());

                Player * robbedPlayer = GetPlayer(victimNumber);
                int cardNumber; // The card the player chooses to remove

                // Qualify card number
                do {
                    for (int i = 0; i < robbedPlayer->GetNumberOfCards(); i++)
                        cout << "Card " << i << endl;
                    cout << "Select a card:" << endl;
                    cin >> cardNumber;
                } while (cardNumber < 0 || cardNumber >= robbedPlayer->GetNumberOfCards());

                currentPlayer->AddToHand(robbedPlayer->LoseCard(cardNumber));
            }
            return 0;
            break;
    }
}

// GetPlayer
// Given an index, retrieve the player at that index

Player * Game::GetPlayer(int playerNum) {
    return &m_players[playerNum];
}


// PlayGame
// The actual gameplay

void Game::PlayGame() {
    Player* currentPlayer = GetPlayer(m_turn++ % m_numPlayers); // The current player
    int playersRemaining = m_numPlayers;

    while (playersRemaining - 1) {
        cout << "\nPlayers Remaining: " << playersRemaining << endl;
        cout << "Num cards remaining: " << m_deck.size() << endl;

        // Skip player if they've already lost
        if (currentPlayer->HasLost()) {
            currentPlayer = GetPlayer(m_turn++ % m_numPlayers);
            continue;
        }

        int turnOver = 0; // Determines whether or not the turn is still going on

        // Take turn
        while (!turnOver) {
            // Show menu
            cout << "\nIt is " << currentPlayer->GetName() << "'s turn" << endl;
            cout << "What would you like to do:" << endl;
            cout << "1. View Cards" << endl;
            cout << "2. Play A Card" << endl;
            cout << "3. Draw A Card" << endl;
            int menuChoice; // Store the choice the user selects
            cin >> menuChoice;

            // Qualifier for menuChoice
            while (menuChoice < 1 || menuChoice > 3 || (menuChoice == 2 && !currentPlayer->HasCards())) {
                if (menuChoice == 2 && !currentPlayer->HasCards())
                    cout << "You don't have any cards" << endl;
                else
                    cout << "Please enter a number from 1-3" << endl;
                cin >> menuChoice;
            }

            // Do menu option
            switch (menuChoice) {
                case 1: // View cards
                    if (currentPlayer->HasCards())
                        currentPlayer->DisplayHand();
                    else
                        cout << "You do not have any cards" << endl;
                    break;
                case 2:
                { // Play card
                    if (!currentPlayer -> HasCards()) {
                        cout << "You do not have any cards" << endl;
                        break;
                    }
                    currentPlayer->DisplayHand();
                    cout << "Select a card:" << endl;
                    int cardIndex; // Index of selected card
                    cin >> cardIndex;

                    // Qualifier for the card
                    while (cardIndex >= currentPlayer->GetNumberOfCards()) {
                        cout << "Invalid index" << endl;
                        cin >> cardIndex;
                    }

                    // Play the card
                    m_discard.push_back(currentPlayer->PlayCard(cardIndex));
                    turnOver = HandleCard((m_turn - 1) % m_numPlayers);
                    break;
                }
                case 3:
                {
                    Card drawnCard = DrawCard(); // The card drawn from the deck
                    //                    Card drawnCard(0, "Litter Bomb");
                    currentPlayer->AddToHand(drawnCard);

                    // If the card is an exploding kitten
                    if (!drawnCard.GetType()) {
                        cout << "Oh No! You drew " << drawnCard.ToString() << endl;

                        // If the player has a defuse card, they should use it
                        if (currentPlayer->HasDefuse()) {
                            cout << "But you have a defuse card! Play it or lose!" << endl;
                            currentPlayer->DisplayHand();
                            cout << "Select a card:" << endl;

                            int cardIndex; // index of the card
                            cin >> cardIndex;
                            Card playedCard = currentPlayer->PlayCard(cardIndex);
                            if (playedCard.GetType() == 1) {
                                cout << "Whew! That was a close one! Good thing you had that defuse card" << endl;
                                m_discard.push_back(playedCard);
                                m_deck.push_back(currentPlayer->ReturnBomb());
                                Shuffle();
                            } else {
                                cout << "Are you sure you don't want to play your defuse card? (y - yes, I'm sure; n - no, play it)" << endl;
                                char decision; // User's decision
                                cin >> decision;
                                if (decision == 'y') {
                                    cout << "Sorry! You're out of the game!" << endl;
                                    currentPlayer->SetLost(true);
                                    playersRemaining--;
                                } else {
                                    m_discard.push_back(currentPlayer->PlayDefuse());
                                    m_deck.push_back(currentPlayer->ReturnBomb());
                                    Shuffle();
                                }
                            }
                        } else {
                            cout << "Sorry! You're out of the game!" << endl;
                            currentPlayer->SetLost(true);
                            playersRemaining--;
                        }
                    }
                    turnOver = 1;
                    break;
                }
            }

            menuChoice = 0; // Reset menu choice


        }

        // Change turns, unless the player has an extra
        if (!currentPlayer->HasExtraTurn())
            currentPlayer = GetPlayer(m_turn++ % m_numPlayers);
        else {
            currentPlayer->SetExtraTurn(false);
            cout << "Take another turn!" << endl;
        }
    }

    // Determine who the winner is
    Player* winner;
    for (int i = 0; i < m_numPlayers; i++) {
        winner = GetPlayer(i);
        if (!winner->HasLost())
            cout << "The winner is " << winner->GetName() << "!" << endl;
    }

}

