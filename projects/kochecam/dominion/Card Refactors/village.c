int villageCard(int *currentPlayer, struct gameState *state, int *handPos){
	// +1 card
	drawCard(*currentPlayer, state);

	// +2 actions
	state->numActions = state->numActions + 2;

	// discard played card from hand
	discardCard(*handPos, *currentPlayer, state, 0);
	return 0; 
}