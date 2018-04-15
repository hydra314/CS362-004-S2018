int greatHallCard(int *currentPlayer, int *handPos, struct gameState *state){
	// +1 card
	drawCard(*currentPlayer, state);

	// +1 actions
	state->numActions++;

	// discard card from hand
	discardCard(*handPos, *currentPlayer, state, 0);
	return 0;
}