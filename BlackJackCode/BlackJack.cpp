#include <iostream>
#include <cstdlib>
#include <cmath>
#include "BlackJack.h"

int main(){
	double credits = 100;
	double bet = 0;
	srand(time(NULL));
	bool playAgain = true;
	int playAgainInput = 0;

	while(playAgain == true){
		if(credits == 0){
			std::cout << "You have run out of credits." << '\n';
			break;
		}

		std::cout << "Credits: " << credits << '\n';
		std::cout << "Place your Bet: ";
		std::cin >> bet;
		while (bet > credits){
			std::cout << "not enough credits." << '\n';
			std::cout << "Place your Bet: ";
			std::cin >> bet;
		}

		std::cout << "\n-----Player's Hand-----" << std::endl;
		// int playerHand[5] = {5, 2, 0, 0, 0};
		// int dealerHand[5] = {2, 1, 0, 0, 0};
		int playerHand[5] = {0};
		int dealerHand[5] = {0};

		//deal player's and dealer's hand
		for (int i = 0; i < 2; i++){
			playerHand[i] = rand() % 13 + 1;
		}

		for (int i = 0; i < 2; i++){
			dealerHand[i] = rand() % 13 + 1;
		}


		//show player's hand on screen, also changes 1, 11, 12, and 13 to A, J, Q, K respectively
		int i = 0;
		std::cout << "Player's Hand: ";
		while (playerHand[i] != 0){
			displayCardToScreen(playerHand[i]);
			i++;
		}
		std::cout << std::endl;

		//display only one of the two dealer cards
		std::cout << "Dealer's Hand: ";
		displayCardToScreen(dealerHand[0]);
		std::cout << "[?]" << '\n';

		//goes through hit/stand action from player
		int afterhitOrStandValue = hitOrStand(playerHand);
		std::cout << '\n';

		//detect if player busts hand.  Will continue to dealer if player does not bust
		if(afterhitOrStandValue > 21){
			std::cout << "Player Busts, House Wins." << std::endl;
			credits -= bet;
			std::cout << "You have " << credits << " credits" << '\n';

			//play again controller
			std::cout << "\n[(1) to play again | (2) to quit]: ";
			std::cin >> playAgainInput;

			while ( (playAgainInput != 1) && (playAgainInput != 2) ){
				std::cout << "(" << playAgainInput << ") is not a option listed above." << '\n';
				std::cout << "[(1) to play again | (2) to quit]: ";
				std::cin >> playAgainInput;
			}

			if(playAgainInput == 2){
				playAgain = false;
			}

		}
		else if(afterhitOrStandValue == 21){
			std::cout << "Player has BlackJack!" << '\n';
			credits += bet*1.5;
			std::cout << "You have " << credits << " credits" << '\n';

			//play again controller
			std::cout << "\n[(1) to play again | (2) to quit]: ";
			std::cin >> playAgainInput;

			while ( (playAgainInput != 1) && (playAgainInput != 2) ){
				std::cout << "(" << playAgainInput << ") is not a option listed above." << '\n';
				std::cout << "[(1) to play again | (2) to quit]: ";
				std::cin >> playAgainInput;
			}

			if(playAgainInput == 2){
				playAgain = false;
			}
		}
		else{
			//dealer controller
			int k = 0;
			std::cout << "Dealer's Hand: ";
			while (k < 5){
				if (dealerHand[k] != 0){
					displayCardToScreen(dealerHand[k]);
				}
				k++;
			}
			std::cout << '\n';


			int winLossOutcome = dealerController(dealerHand, afterhitOrStandValue, credits, bet);
			if(winLossOutcome == 1){
				credits += bet;
			}
			else if(winLossOutcome == 2){
				credits -= bet;
			}

			//allows player to continue playing
			std::cout << "\n[(1) to play again | (2) to quit]: ";
			std::cin >> playAgainInput;

			while ( (playAgainInput != 1) && (playAgainInput != 2) ){
				std::cout << "(" << playAgainInput << ") is not a option listed above." << '\n';
				std::cout << "[(1) to play again | (2) to quit]: ";
				std::cin >> playAgainInput;
			}

			if(playAgainInput == 2){
				playAgain = false;
			}
		}
	}

	return 0;
}
