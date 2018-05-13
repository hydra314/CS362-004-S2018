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
int smithyWasPlayed = 0;
int threeCardsAdded = 0;
int threeTakenFromDeck = 0;
int smithyWasDiscarded = 0;

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

	// Give the player a Smithy card
	int handPos = rand() % G->handCount[player];
	G->hand[player][handPos] = smithy;
}

void testSmithy(struct gameState *G, struct gameState *testG){
	// Goals:
	//	- see if Smithy was played (in played cards list)
	//	- see if three cards were added to hand
	//	- see if three cards were taken from deck
	//	- see if Smithy was added to discard pile

	// Check that Smithy was played
	int i;
	for(i = 0; i < testG->playedCardCount; i++){
		if(testG->playedCards[i] == smithy)
			smithyWasPlayed++;
	}

	// Check that three cards were added to player's hand
	// Net gain of 2 cards: -1 from Smithy, +3 from drawn cards
	if(testG->handCount[testG->whoseTurn] == G->handCount[G->whoseTurn] + 2)
		threeCardsAdded++;

	// See if three cards were taken from deck
	if(testG->deckCount[testG->whoseTurn] == G->deckCount[G->whoseTurn] - 3)
		threeTakenFromDeck++;

	// See if Smithy was added to discard pile
	if(testG->discardCount[testG->whoseTurn] == G->discardCount[G->whoseTurn] + 1){
		if(testG->discard[testG->whoseTurn][testG->discardCount[testG->whoseTurn] - 1] == smithy){
			smithyWasDiscarded++;
		}
	}
}

void printResults(){
	printf("Results for random test of Smithy:\n");
	printf("Smithy was played: %d/%d passed\n", smithyWasPlayed, iterations);
	printf("Added three cards to hand: %d/%d passed\n", threeCardsAdded, iterations);
	printf("Took three cards from deck: %d/%d passed\n", threeTakenFromDeck, iterations);
	printf("Discarded Smithy: %d/%d passed\n", smithyWasDiscarded, iterations);
}

int main(){
	srand(time(NULL));
	int i, j;
	int seed = 2;
	int choice1 = 0, choice2 = 0, choice3 = 0;
	int bonus = 0;

	struct gameState G, testG;

	printf("================================================\n");
	printf("              Random test: Smithy               \n");
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

		cardEffect(smithy, choice1, choice2, choice3, &testG, handPos, &bonus);
		testSmithy(&G, &testG);
	}

	printResults();

	return 0;
}