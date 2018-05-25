#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>


int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
int allCards[16] = {copper, silver, gold, estate, duchy, province, adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
int handPos;
const int iterations = 1000;
int villageWasPlayed = 0;
int oneCardAdded = 0;
int oneTakenFromDeck = 0;
int twoActionsAdded = 0;
int villageWasDiscarded = 0;

void setRandomState(struct gameState *G, int player){
	int i;

	G->deckCount[player] = (rand() % 15) + 1;			// Deck: from 1 to 15 so Village can always draw 1
	G->discardCount[player] = 15 - G->deckCount[player];	// Always 15 between deck and discard
	G->handCount[player] = (rand() % 7) + 3;	// Hand: between 3 and 10

	// Insert random cards into deck, discard, and hand
	for(i = 0; i < G->deckCount[player]; i++){
		G->deck[player][i] = allCards[rand() % 16];
	}
	for(i = 0; i < G->handCount[player]; i++){
		G->hand[player][i] = allCards[rand() % 16];
	}
	for(i = 0; i < G->discardCount[player]; i++){
		G->discard[player][i] = allCards[rand() % 16];
	}

	// Give the player a Village card
	int handPos = rand() % G->handCount[player];
	G->hand[player][handPos] = village;
}

void testVillage(struct gameState *G, struct gameState *testG){
	// Goals:
	//	- see if Village was played (in played cards list)
	//	- see if one card was added to hand
	//	- see if one card was taken from deck
	//	- see if two Actions were added (action decrement not done in cardEffect)
	//	- see if Village was added to discard pile

	// Check that Village was played
	int i;
	for(i = 0; i < testG->playedCardCount; i++){
		if(testG->playedCards[i] == village)
			villageWasPlayed++;
	}

	// Check that one card was added to player's hand
	// Net gain of 0 cards: -1 from Village, +1 from drawn cards
	if(testG->handCount[testG->whoseTurn] == G->handCount[G->whoseTurn])
		oneCardAdded++;

	// See if one card was taken from deck
	if(testG->deckCount[testG->whoseTurn] == G->deckCount[G->whoseTurn] - 1)
		oneTakenFromDeck++;

	// See if two Actions were added
	if(testG->numActions == G->numActions + 2)
		twoActionsAdded++;

	// See if Village was added to discard pile
	if(testG->discardCount[testG->whoseTurn] == G->discardCount[G->whoseTurn] + 1){
		if(testG->discard[testG->whoseTurn][testG->discardCount[testG->whoseTurn] - 1] == village){
			villageWasDiscarded++;
		}
	}
}

void printResults(){
	printf("Results for random test of Village:\n");
	printf("Village was played: %d/%d passed\n", villageWasPlayed, iterations);
	printf("Added one card to hand: %d/%d passed\n", oneCardAdded, iterations);
	printf("Took one card from deck: %d/%d passed\n", oneTakenFromDeck, iterations);
	printf("Added two actions: %d/%d passed\n", twoActionsAdded, iterations);
	printf("Discarded Village: %d/%d passed\n", villageWasDiscarded, iterations);
}

int main(){
	srand(time(NULL));
	int i, j;
	int seed = 2;
	int choice1 = 0, choice2 = 0, choice3 = 0;
	int bonus = 0;

	struct gameState G, testG;

	printf("================================================\n");
	printf("              Random test: Village               \n");
	printf("================================================\n\n");

	for(i = 0; i < iterations; i++){
		// Select number of players (max of 4) and initialize game states
		int players = (rand() % (MAX_PLAYERS - 1)) + 2;
		for(j = 0; j < players; j++){
			initializeGame(players, k, seed, &G);
			setRandomState(&G, j);
		}

		G.whoseTurn = rand() % players;
		memcpy(&testG, &G, sizeof(struct gameState));

		cardEffect(village, choice1, choice2, choice3, &testG, handPos, &bonus);
		testVillage(&G, &testG);
	}

	printResults();

	return 0;
}