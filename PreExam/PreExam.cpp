#include "preExam.h"

int main()
{
	dynamicCalcNew();
	//task1();
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
		if (a == 0 && currentLetter < 58 && currentLetter>47) {//This is only here to avoid getting an out of bounds error
			currentNum = letterToNum(currentLetter);
			eq.input1 = currentNum;
		}
		else if (a != 0 && currentLetter > 41 && currentLetter < 48) //I check if the current char is a modifier
			eq.modifier = currentLetter;
		else if (a != 0 && input[a - 1] < 58 && input[a - 1]>47) { // I check if the previous char was a number
			if (currentLetter < 58 && currentLetter>47) {// now I check if the current char is a number
				currentNum = tennify(currentNum) + letterToNum(currentLetter); // If the previous char was a number, I need to multiply it by 10 and add the new number.
				if (eq.input2 == 0) // I check if my equation has already had a number input
					eq.input1 = currentNum;
				else
					eq.input2 = currentNum;
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

void dynamicCalcNew() {
	std::string input = "";
	std::vector<char> modifiers{ ' ' };
	std::vector<int> numbers;
	std::getline(std::cin, input);
	int currentNum = 0;
	int lastNum = -1;
	bool wasMod = true;
	float lastResult = 0;
	for (int a = 0; a < input.size(); a++) {
		if (isModifier(input[a])==true&&a!=0) {
			modifiers.push_back(input[a]);
			wasMod = true;
		}
		if (isNumber(input[a])==true&&wasMod==true) {
			currentNum = letterToNum(input[a]);
			numbers.push_back(currentNum);
			lastNum++;
			wasMod = false;
		}
		else if (isNumber(input[a])==true && wasMod==false) {
			numbers[lastNum] = tennify(numbers[lastNum]) + letterToNum(input[a]);
		}
	}
	for (int a = 0; a < modifiers.size(); a++) {
		//std::cout << numbers[a] << modifiers[a];
		if (a == 0) {
			std::cout << numbers[a] << modifiers[a + 1];
			lastResult = numbers[a];
		}
		else if (a == modifiers.size() - 1) {
			lastResult = bigboyalculate(lastResult, numbers[a], modifiers[a]);
			std::cout << numbers[a];
		}
		else {
			lastResult = bigboyalculate(lastResult, numbers[a], modifiers[a]);
			std::cout << numbers[a] << modifiers[a+1];
		}
	}
	std::cout << '='<<lastResult;
}
bool isModifier(char a) {
	if (a == '*' || a == '/' || a == '+' || a == '-')
		return true;
	else
		return false;
}
bool isNumber(char a){
	if (a < 58 && a>47)
		return true;
	else
		return false;
}
float bigboyalculate(float x, int y, char a) {
	if (a == '*')
		return x * y;
	if (a == '/')
		return x / y;
	if (a == '+')
		return x + y;
	if (a == '-')
		return x - y;
}
int letterToNum(char a) {
	return a - 48;
}
int tennify(int x) {
	return x * 10;
}