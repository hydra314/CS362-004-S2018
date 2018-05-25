#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>

void testShuffle(){
	printf("\n\n========================================\n");
	printf("Testing SHUFFLE function from dominion.c\n");
	printf("========================================\n");

	int player = 1;
	struct gameState state;

	/* shuffle() should only modify state->deck.
	 * Test to see whether all other state variables are left alone.
	 * Player number should also remain unchanged.
	 */

	// Try with an empty deck
	state.deckCount[player] = 0;
	if(shuffle(player, &state) == -1 && state.deckCount[player] == 0){
		printf("PASS when the deck is empty\n");
	}
	else{
		printf("FAIL when the deck is empty\n");
	}

	// Try with a deck with 1 card
	state.deckCount[player] = 1;
	state.deck[player][0] = 1;
	if(shuffle(player, &state) == 0){
		if(state.deckCount[player] == 1 && state.deck[player][0] == 1){
			printf("PASS when the deck has one card\n");
		}
		else{
			printf("FAIL when the deck has one card:\n");
			if(state.deckCount[player] != 1) printf("- deckCount was changed\n");
			if(state.deck[player][0] != 1) printf("- deck was changed\n");
		}
	}
	else{
		printf("FAIL when the deck has one card: function thinks the deck is empty\n");
	}

	// Try a deck with 2 cards
	state.deckCount[player] = 2;
	state.deck[player][1] = 2;
	if(shuffle(player, &state) == 0){
		if(state.deckCount[player] == 2){
			if((state.deck[player][0] == 1 && state.deck[player][1] == 2) || (state.deck[player][0] == 2 && state.deck[player][1] == 1)){
				printf("PASS when the deck has two cards\n");
			}
			else{
				printf("FAIL when the deck has two cards: card values were changed\n");
				printf("First card: %d\nSecond card:%d\n", state.deck[player][0], state.deck[player][1]);
			}
		}
		else{
			printf("FAIL when the deck has two cards: card count was changed\n");
		}
	}
	else{
		printf("FAIL when the deck has two cards: function thinks the deck is empty\n");
	}

	// Try a deck with several cards
	state.deckCount[player] = 5;
	state.deck[player][2] = 3;
	state.deck[player][3] = 4;
	state.deck[player][4] = 5;
	if(shuffle(player, &state) == 0){
		if(state.deckCount[player] == 5){
			int i, j, pass = 1;
			int arr[] = {1, 2, 3, 4, 5};
			for(i = 0; i < 5; i++){
				for(j = 0; j < 5; j++){
					if(state.deck[player][i] == arr[j]){
						arr[j] = 0;
					}
				}
			}
			for(i = 0; i < 5; i++){
				if(arr[i] != 0) pass = 0;
			}

			if(pass == 1){
				if(state.deck[player][0] == 1 && state.deck[player][1] == 2 && state.deck[player][2] == 3 && state.deck[player][3] == 4 && state.deck[player][4] == 5){
					printf("POSSIBLE FAILURE: deck has the same order as before when tested with five cards.\n"); 
					printf("This has a low chance of happening, but try running the test again to ensure accuracy.\n");
				}
				else{
					printf("PASS when the deck has five cards\n");
				}
			}
			else{
				printf("FAIL when the deck has five cards: card values were changed\n");
			}
		}
		else{
			printf("FAIL when the deck has five cards: card count was changed\n");
		}
	}
	else{
		printf("FAIL when the deck has five cards: function thinks the deck is empty\n");
	}
}

int main(int argc, char *argv[]){
	testShuffle();
	return 0;
}