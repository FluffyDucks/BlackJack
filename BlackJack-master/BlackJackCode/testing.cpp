#include <iostream>
#include <cstdlib>
#include <ctime>

//file to test features for main code to use

int chooseValue(){
	srand(time(NULL));
	int randomNum = rand() % 13 + 1;
	return randomNum;
}

int main(){
	for(int i = 0; i < 10; i++){
		// std::cout << chooseValue() << '\n';
		std::cout << (rand() % 13 + 1) << '\n';

	}

	return 0;
}
