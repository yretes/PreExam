#include "preExam.h"

int main()
{
	task1();
}

void task1() {
	class Equation {
	public:
		float input1;
		float input2;
		char modifier;
		Equation() {
			input1 = 0;
			input2 = 0;
			modifier = 'a';
		}
		float calculate() {
			if (modifier == '*')
				return input1 * input2;
			if (modifier == '/')
				return input1 / input2;
			if (modifier == '+')
				return input1 + input2;
			if (modifier == '-')
				return input1 - input2;
		}

	};
	std::string input = "";
	char currentLetter = ' ';
	int currentNum = 0;
	Equation eq;

	std::cout << "input an equation. . ." << std::endl;
	std::getline(std::cin, input);

	for (int a = 0; a < input.size(); a++) {
		currentLetter = input[a];
		if (a == 0 && currentLetter < 58 && currentLetter>47) //This is only here to avoid getting an out of bounds error
			eq.input1 = letterToNum(currentLetter);
		else if (a != 0 && currentLetter > 41 && currentLetter < 48) //I check if the current char is a modifier
			eq.modifier = currentLetter;
		else if (a != 0 && input[a - 1] < 58 && input[a - 1]>47) { // I check if the previous char was a number
			if (currentLetter < 58 && currentLetter>47) {// now I check if the current char is a number
				currentNum = (currentNum * 10) + letterToNum(currentLetter); // If the previous char was a number, I need to multiply it by 10 and add the new number.
				if (eq.input1 > 0) // I check if my equation has already had a number input
					eq.input2 = currentNum;
				else
					eq.input1 = currentNum;
			}
		}
		else if (a != 0 && input[a - 1] > 57 || a != 0 && input[a - 1] < 48) {// I check if the previous char was not a number
			if (currentLetter < 58 && currentLetter>47) { // I check if the current char is a number
				currentNum = letterToNum(currentLetter);
				if (eq.input1 > 0) // I check if my equation has already had a number input
					eq.input2 = currentNum;
				else
					eq.input1 = currentNum;
			}
		}
		
	}
	std::cout << eq.input1 << eq.modifier << eq.input2 << "=" << eq.calculate();
	
}

int letterToNum(char a) {
	return a - 48;
}