int councilRoomCard(int *currentPlayer, struct gameState *state, int *handPos, int *i){
	//+4 Cards
	for (*i = 0; *i < 4; (*i)++){
  		drawCard(*currentPlayer, state);
	}
		
	//+1 Buy
	state->numBuys++;
		
	//Each other player draws a card
	for (*i = 0; *i < state->numPlayers; (*i)++){
		if ( *i != *currentPlayer ){
			drawCard(*i, state);
		}
	}
		
	//put played card in played card pile
	discardCard(*handPos, *currentPlayer, state, 0);
		
	return 0;
}