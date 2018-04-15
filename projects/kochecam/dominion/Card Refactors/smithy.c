int smithyCard(int *i, int *currentPlayer, struct gameState *state, int *handPos){
	// +3 cards
	for(*i = 0; *i < 3; (*i)++){
		drawCard(*currentPlayer, state);
	}

	// discard card from hand
	discardCard(*handPos, *currentPlayer, state, 0);
	return 0;
}