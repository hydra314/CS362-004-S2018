#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "Great Hall"

int main(int argc, char *argv[]){
	int newCards = 0;
	int discarded = 1;
	int extraCoins = 0;
	int extraActions = 0;
	int shuffledCards = 0;

	int i, j, m;
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int seed = 1000;
	int numPlayers = 2;
	int player = 0;
	struct gameState state, test;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, great_hall, smithy, council_room};
	initializeGame(numPlayers, k, seed, &state);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
	memcpy(&test, &state, sizeof(struct gameState));
	cardEffect(great_hall, choice1, choice2, choice3, &test, handpos, &bonus);
	newCards = 1;
	extraActions = 1;


	// Verify (to user) that the number of cards in the hand is as expected
	printf("Hand count: %d, Expected: %d\n", test.handCount[player], state.handCount[player] + newCards - discarded);

	// Verify (to user) that the number of cards in the deck is as expected
	printf("Deck count: %d, Expected: %d\n", test.deckCount[player], state.deckCount[player] - newCards + shuffledCards);

	// Verify (to user) that the player's coin count is as expected
	printf("Coins: %d, Expected: %d\n", test.coins, state.coins + extraCoins);

	// Verify (to user) that the player's action count is as expected
	printf("Actions: %d, Expected: %d\n", test.numActions, state.numActions + extraActions);

	// Verify (to machine) that the above values are as expected
	/*assert(test.handCount[player] == state.handCount[player] + newCards - discarded);
	assert(test.deckCount[player] == state.deckCount[player] - newCards + shuffledCards);
	assert(test.coins == state.coins + extraCoins);
	assert(test.numActions == state.numActions + extraActions);*/

	return 0;
}