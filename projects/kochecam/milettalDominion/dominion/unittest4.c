#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>

void testWhoseTurn(){
	printf("\n\n==========================================\n");
	printf("Testing WHOSETURN function from dominion.c\n");
	printf("==========================================\n");

	struct gameState state;
	int i;

	for(i = 1; i <= 4; i++){
		state.whoseTurn = i;
		if(whoseTurn(&state) == i){
			printf("PASS with 4 players when it's the turn of Player %d\n", i);
		}
		else{
			printf("FAIL with 4 players when it's the turn of Player %d\n", i);
		}
	}

	state.whoseTurn = 0;
	if(whoseTurn(&state) == 0){
		printf("PASS when it's the turn of Player 0\n");
	}
	else{
		printf("FAIL when it's the turn of Player 0\n");
	}

	state.whoseTurn = -1;
	if(whoseTurn(&state) == -1){
		printf("FAIL: function does not check state.whoseTurn to see if it is a positive value\n");
	}
	else{
		printf("PASS: function checks state.whoseTurn and verifies that it is a postive value\n");
	}

	state.whoseTurn = INT_MAX;
	if(whoseTurn(&state) == INT_MAX){
		printf("PASS when passed value INT_MAX\n");
	}
	else{
		printf("FAIL when passed value INT_MAX\n");
	}
}

int main(int argc, char *argv[]){
	testWhoseTurn();
	return 0;
}