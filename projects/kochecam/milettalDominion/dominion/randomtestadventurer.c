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
int adventurerWasPlayed = 0;
int twoTreasuresAdded = 0;
int adventurerDidNotDiscardTreasure = 0;
int adventurerWasDiscarded = 0;

void setRandomState(struct gameState *G, int player){
	int i;

	G->deckCount[player] = rand() % 15;			// Deck: from 0 to 15
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

	// Give the player an Adventurer card
	int handPos = rand() % G->handCount[player];
	G->hand[player][handPos] = adventurer;
}

void testAdventurer(struct gameState *G, struct gameState *testG){
	// Goals:
	//	- see if Adventurer was played (in played cards list)
	//	- see if two Treasure cards were added to hand
	//	- make sure no Treasure cards were discarded
	//	- see if Adventurer was discarded

	// Check that Adventurer was played
	int i;
	for(i = 0; i < testG->playedCardCount; i++){
		if(testG->playedCards[i] == adventurer)
			adventurerWasPlayed++;
	}

	// Check that two Treasure cards were added to player's hand
	// Net gain of 1 card: -1 from Adventurer, +2 Treasure
	int treasureCount = 0, testTreasureCount = 0;
	for(i = 0; i < G->handCount[G->whoseTurn]; i++){
		if(G->hand[G->whoseTurn][i] < 3){
			treasureCount++;
		}
	}
	for(i = 0; i < testG->handCount[testG->whoseTurn]; i++){
		if(testG->hand[testG->whoseTurn][i] < 3)
			testTreasureCount++;
	}
	if(testTreasureCount == treasureCount + 2)
		twoTreasuresAdded++;

	// Make sure no Treasure cards were discarded
	int treasureDiscarded = 0, testTreasureDiscarded = 0;
	for(i = 0; i < G->discardCount[G->whoseTurn]; i++){
		if(G->discard[G->whoseTurn][i] < 3){
			treasureDiscarded++;
		}
	}
	for(i = 0; i < testG->discardCount[testG->whoseTurn]; i++){
		if(testG->discard[testG->whoseTurn][i] < 3)
			testTreasureDiscarded++;
	}
	if(testTreasureDiscarded > treasureDiscarded)
		adventurerDidNotDiscardTreasure++;

	// See if Adventurer was added to discard pile
	if(testG->discardCount[testG->whoseTurn] == G->discardCount[G->whoseTurn] + 1){
		if(testG->discard[testG->whoseTurn][testG->discardCount[testG->whoseTurn] - 1] == adventurer){
			adventurerWasDiscarded++;
		}
	}
}

void printResults(){
	printf("Results for random test of Adventurer:\n");
	printf("Adventurer was played: %d/%d passed\n", adventurerWasPlayed, iterations);
	printf("Added two Treasures to hand: %d/%d passed\n", twoTreasuresAdded, iterations);
	printf("Did not discard Treasure cards: %d/%d passed\n", adventurerDidNotDiscardTreasure, iterations);
	printf("Discarded Adventurer: %d/%d passed\n", adventurerWasDiscarded, iterations);
}

int main(){
	srand(time(NULL));
	int i, j;
	int seed = 2;
	int choice1 = 0, choice2 = 0, choice3 = 0;
	int bonus = 0;

	struct gameState G, testG;

	printf("================================================\n");
	printf("            Random test: Adventurer             \n");
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

		cardEffect(adventurer, choice1, choice2, choice3, &testG, handPos, &bonus);
		testAdventurer(&G, &testG);
	}

	printResults();

	return 0;
}