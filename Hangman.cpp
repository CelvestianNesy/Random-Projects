
#include <iostream>
#include <vector>
#include <string>
#include <set>



std::string menu()
{
	std::string word = "engineering";
	return word;
}
	
std::vector<char> wordHider(std::vector<char> wordanswer, std::vector<char> Guess)
{
	for (char element : wordanswer)
	{
		Guess.push_back('_');
	}
	return Guess;
	
}




void mainGame(std::vector<char> wordGuess, std::vector<char> word, std::string stringAnswer)
{
	bool Running = true;
	int guesses = 0;
	std::cout << "How many guesses?";
	std::cin >> guesses;

	std::vector<char> gameGuess = wordGuess; //This is where our answer is hidden, and shown when a user inputs the correct letters. 
	std::vector<char> answer = word; //This is our answered, stored in here. 
	std::vector<char> forbidden; //Used letters.
	 
	int counter = 0;

	while (Running)
	{

		std::vector<char> components;
		std::cout << "\n\n";

		for (char lines : gameGuess)
		{
			int lineCount = 0;

			if (lines == '_')
			{
				lineCount += 1;
			}
		}

		std::cout << "used letters:";

		for (char forbiddenstuff : forbidden)
		{
			int lineCount = 0;

			std::cout << forbiddenstuff;
		}

		std::cout << "\n\n";

		for (char letters : gameGuess)
		{
			std::cout << "" << letters << "";
		}

		std::string guess;
		std::cout << "\n\n" << "Guess the word or the letter in the word: _\b"; 
		std::getline(std::cin >> std::ws, guess); 	

		if (guess == stringAnswer and guess.length() > 1)
		{
			std::cout << "\nYou won the game. Answer was: " << stringAnswer;
			break;
		}
		else if (guess != stringAnswer and guess.length() > 1)
		{
			std::cout << "\nWrong answer! This is the incorrect word. \n";
			counter += 1;
		}

		int isIn = stringAnswer.find(guess);
		guess = std::tolower(guess.at(0)); 


		if (isIn >= 0)
		{
			for (int index = 0; index < stringAnswer.length(); index++)
			{
				if (guess.at(0) == stringAnswer.at(index))
				{
					components.push_back(index);
				}
			}
			for (int component : components)
			{
				gameGuess[component] = guess.at(0);
			}
		}
		else
		{
			counter += 1;
			std::cout << "Wrong answer! \n";
			forbidden.push_back(guess.at(0));
		}

		if (counter == guesses)
		{
			std::cout << "You lost, lol. Answer was:" << stringAnswer;
			break;
		}

		if (gameGuess == answer)
		{
			
			std::cout << "You fucking win! The answer was: " << stringAnswer;
			std::cout << "\n";
			break;
		}
	}
}

void gameInitialization(std::string word)
{
	std::vector<char> wordAnswer; 
	std::vector<char> Guess;

	for (int index = 0 ; index < word.length( ) ; index++)
	{
		char letter = word.at(index);
		wordAnswer.push_back(letter);
	}

	std::vector<char> WordGuess = wordHider(wordAnswer,Guess); 
	mainGame(WordGuess, wordAnswer,word);

}


int main()
{
	std::string word = menu();
	gameInitialization(word);

	return 0;
}
