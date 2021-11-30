#ifndef GAMEFUNCTIONS_H
#define GAMEFUNCTIONS_H

#include "PlaceClass.hpp"

int getNumberOfPlayers(string N);

void initializeChance(unordered_map<int, string> &Chance);

void initializeCommunityChest(unordered_map<int, string> &CommunityChest);

void initializePlaces(vector<place> &board);

void constructBoard(vector<vector<string>> &AJ, vector<place> &board, vector<string> &players, unordered_map<string, long> &moneyowned,
        int n, unordered_map<int, string> &Chance, unordered_map<int, string> &CommunityChest);

#endif