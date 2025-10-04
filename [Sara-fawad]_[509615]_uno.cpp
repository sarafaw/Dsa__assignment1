#include "UNO.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <sstream>

class SimpleUNOGame : public UNOGame{
private:
     int numPlayers;
    std::vector<std::vector<Card>> players;
     std::vector<Card> deck;
    std::vector<Card> discardPile;
    int currentPlayer;
     bool clockwise;
     bool gameOver;
     int winner;

   std::mt19937 rng; 

public:
    SimpleUNOGame(int n) : numPlayers(n), currentPlayer(0), clockwise(true), gameOver(false), winner(-1), rng(1234) {}

    void initialize() override {
        deck.clear();
        discardPile.clear();
        players.assign(numPlayers, {});
        currentPlayer =0;
        clockwise =true;
        gameOver =false;
        winner =-1;

        std::vector<std::string> colors = { "Red", "Green", "Blue", "Yellow" };
        std::vector<std::string> actions = { "Skip", "Reverse", "Draw Two" };

        for (auto& color : colors) {
            deck.push_back({ color, "0" });
            for (int i = 1;i <= 9; ++i) {
                deck.push_back({ color, std::to_string(i) });
                deck.push_back({ color, std::to_string(i) });
            }
            for (auto& act : actions) {
                deck.push_back({ color, act });
                deck.push_back({ color, act });
            }
        }

        std::shuffle(deck.begin(), deck.end(), rng);

        for (int i = 0; i < numPlayers; ++i)
            for (int j = 0; j < 7; ++j)
                drawCard(i);

        discardPile.push_back(deck.back());
        deck.pop_back();
    }

    void drawCard(int player) {
        if (!deck.empty()) {
            players[player].push_back(deck.back());
            deck.pop_back();
        }
    }

    bool canPlay(const Card& card, const Card& top) {
        return (card.color == top.color || card.value == top.value);
    }

    void playTurn() override {
        if (gameOver) return;

        Card top = discardPile.back();
        auto& hand = players[currentPlayer];

        bool played = false;
        for (size_t i = 0; i < hand.size(); ++i) {
            if (canPlay(hand[i], top)) {
                Card chosen = hand[i];
                discardPile.push_back(chosen);
                hand.erase(hand.begin() + i);
                played = true;

                if (chosen.value == "Skip") {
                    nextPlayer(); 
                }
                else if (chosen.value == "Reverse") {
                    clockwise = !clockwise;
                }
                else if (chosen.value == "Draw Two") {
                    int nxt = nextPlayerIndex();
                    drawCard(nxt);
                    drawCard(nxt);
                    nextPlayer(); 
                }
                break;
            }
        }
        if (!played) {
            drawCard(currentPlayer);
            if (!hand.empty() && canPlay(hand.back(), top)) {
                discardPile.push_back(hand.back());
                hand.pop_back();
            }
        }
        if (hand.size() == 1)
            std::cout <<"Player "<< currentPlayer <<" says UNO!\n";
        else if (hand.empty()) {
            gameOver = true;
            winner = currentPlayer;
            return;
        }
        nextPlayer();
    }
    void nextPlayer() {
        currentPlayer = nextPlayerIndex();
    }
    int nextPlayerIndex() const {
        if (clockwise)
            return (currentPlayer + 1) % numPlayers;
        else
            return (currentPlayer - 1 + numPlayers) % numPlayers;
    }
    bool isGameOver() const override {
        return gameOver;
    }
    int getWinner() const override {
        return winner;
    }
    std::string getState() const override{
        std::ostringstream out;
        out <<"Player " << currentPlayer
            <<"'s turn, Direction: " << (clockwise ? "Clockwise" : "Counter-clockwise")
            <<", Top: " << discardPile.back().color << " " << discardPile.back().value
            <<", Players cards: ";

        for (int i = 0; i< numPlayers; ++i) {
            out << "P" << i << ":" << players[i].size();
            if (i != numPlayers - 1) out << ", ";

        }

         return out.str();
    }
};
       UNOGame* createGame(int n) {
         return new SimpleUNOGame(n);
       }
