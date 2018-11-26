#include <iostream>
#include <cstdlib>
#include <ctime>

//shows hand on screen, also changes 1, 11, 12, 13 to A, J, Q, K respectively
int displayCardToScreen(int cardValue){
	int displayCard = cardValue;
	std::cout << '[';
	if (displayCard == 1){
		std::cout << "A]";
	}
	else if (displayCard == 11){
		std::cout << "J]";
	}
	else if (displayCard == 12){
		std::cout << "Q]";
	}
	else if (displayCard == 13){
		std::cout << "K]";
	}
	else{
		std::cout << displayCard << "]";
	}
}

//returns score based on hand
int calculateHandScore(int playerHand[5]){
	int score = 0;
	for (int i = 0; i < 5; i++){
		// std::cout << "[DEBUG] currently evaluating: " << playerHand[i] << std::endl;
		if(playerHand[i] == 0){
			// std::cout << "[DEBUG] score = " << score << std::endl;
			break;
		}
		if(playerHand[i] >= 10){
			// std::cout << "[DEBUG] " << playerHand[i] << " >= 10" << std::endl;
			score += 10;
			// std::cout << "[DEBUG] score = " << score << std::endl;
		}
		else if(playerHand[i] == 1){
			// std::cout << "[DEBUG]" << playerHand[i] << " == A" << std::endl;
			if (score + 11 < 22){
				// std::cout << "[DEBUG] A is counted as 11" << std::endl;
				score += 11;
				// std::cout << "[DEBUG] score = " << score << std::endl;
			}
			else{
				// std::cout << "[DEBUG]" << playerHand[i] << "A is counted as 1" << std::endl;
				score += 1;
			}
		}
		else{
			score += playerHand[i];
			// std::cout << "[DEBUG]" << playerHand[i] << " added" << std::endl;
			// std::cout << "[DEBUG] score = " << score << std::endl;
		}

	}
	return score;
}

//wait for action from player (hit or stand)
//implementation of double and splits do be decided
int hitOrStand(int playerHand[5]){
	int playerDecision = 0;
	int runningScoreTotal = 0;
	int i = 2;
	while (playerDecision != 2){
		runningScoreTotal = calculateHandScore(playerHand);

		if (runningScoreTotal >= 21){
			playerDecision == 2;
			break;
		}

		std::cout << std::endl << "\nPlayer's has " << runningScoreTotal << std::endl;
		std::cout << "[(1) to hit | (2) to stand]" << std::endl;
		std::cout << "Player's action: ";
		std::cin >> playerDecision;

		//error message when 1 or 2 is not inputed
		while( (playerDecision != 1) && (playerDecision != 2) ){
			std::cout << '(' << playerDecision << ')' << " is not a valid action." << std::endl;
			std::cout << "[(1) to hit | (2) to stand]" << std::endl;
			std::cout << "Player's action: ";
			std::cin >> playerDecision;
		}

		if (playerDecision == 2){
			break;
		}

		playerHand[i] = rand() % 13 + 1;

		for (int i = 0; i < 5; i++){
			if (playerHand[i] != 0){
				displayCardToScreen(playerHand[i]);
			}
		}
		i++;
		runningScoreTotal = calculateHandScore(playerHand);
		if (i == 5){
			playerDecision = 2;
			std::cout << '\n';
			break;
		}
	}

	// std::cout << "[DEBUG] playerDecision = " << playerDecision << '\n';
	// std::cout << std::endl << "Player has " << runningScoreTotal << std::endl;

	return runningScoreTotal;
}

//controller for dealer's hand, hit on 16, stand on 17
int dealerController(int dealerHand[5], int playerHandValue, double credits, double bet){
	int dealerScore = calculateHandScore(dealerHand);
	int i = 2;
	// std::cout << "[DEBUG] dealerScore = " << dealerScore << '\n' << '\n';
	while(i < 5){
		if(dealerScore >= 17){
			break;
		}
		dealerHand[i] = rand() % 13 + 1;

		std::cout << "Dealer's hand: ";
		int k = 0;
		while(k < 5){
			if(dealerHand[k] != 0){
				displayCardToScreen(dealerHand[k]);
			}
			k++;
		}
		std::cout << '\n';
		dealerScore = calculateHandScore(dealerHand);
		i++;
	}

	std::cout << '\n';

	std::cout << "Dealer has " << dealerScore << '\n';
	std::cout << "Player has " << playerHandValue << "\n\n";
	if(dealerScore > 21){
		std::cout << "Dealer busts, Player Wins." << '\n';
		credits += bet;
		std::cout << "You have " << credits << " credits" << '\n';
		return 1;
	}
	else if(dealerScore > playerHandValue){
		std::cout << "Dealer Wins" << '\n';
		credits -= bet;
		std::cout << "You have " << credits << " credits" << '\n';
		return 2;
	}
	else if(dealerScore < playerHandValue){
		std::cout << "Player Wins" << '\n';
		credits += bet;
		std::cout << "You have " << credits << " credits" << '\n';
		return 1;
	}
	else{
		std::cout << "Draw" << '\n';
		std::cout << "You have " << credits << " credits" << '\n';
		return 0;
	}
}
