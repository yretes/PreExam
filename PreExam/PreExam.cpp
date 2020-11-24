#include "preExam.h"

int main()
{
	dynamicCalc();
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

void dynamicCalc() {
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
	int currentEquation = 0;
	std::vector<Equation> equations;
	std::vector<char> modifiers;
	equations.push_back(Equation());


	std::cout << "input multiple equations, seperate with spacebar. . ." << std::endl;
	std::getline(std::cin, input);
	for (int a = 0; a < input.size(); a++) {
		currentLetter = input[a];
		if (a!=0&&currentLetter == ' ') { // As ' ' seperates input equations, I need to first check If I'm starting a new equation.
			modifiers.push_back(currentLetter);
			equations.push_back(Equation());
			currentEquation++;
		}
		else if (a == 0 && currentLetter < 58 && currentLetter>47) //This is only here to avoid getting an out of bounds error
			equations[currentEquation].input1 = letterToNum(currentLetter);
		else if (a != 0 && currentLetter > 41 && currentLetter < 48) { //I check if the current char is a modifier
			if (equations[currentEquation].input2 > 0) {// If the previous equation is finished, but a new modifier is added, I have to save that in a vector
				modifiers.push_back(currentLetter);
				equations.push_back(Equation());
				currentEquation++;
			}
			equations[currentEquation].modifier = currentLetter;
		}
		else if (a != 0 && input[a - 1] < 58 && input[a - 1]>47) { // I check if the previous char was a number
			if (currentLetter < 58 && currentLetter>47) {// now I check if the current char is a number
				currentNum = tennify(currentNum) + letterToNum(currentLetter); // If the previous char was a number, I need to multiply it by 10 and add the new number.
				if (equations[currentEquation].input2 == 0) // I check if my equation has already had a number input
					equations[currentEquation].input1 = currentNum;
				else
					equations[currentEquation].input2 = currentNum;
			}
		}
		else if (a != 0 && input[a - 1] > 57 || a != 0 && input[a - 1] < 48) {// I check if the previous char was not a number
			if (currentLetter < 58 && currentLetter>47) { // I check if the current char is a number
				currentNum = letterToNum(currentLetter);
				if (equations[currentEquation].input1 > 0) // I check if my equation has already had a number input
					equations[currentEquation].input2 = currentNum;
				else
					equations[currentEquation].input1 = currentNum;
			}
		}
	}
	modifiers.push_back(' ');
	// Now I can print the equations
	float prevResult = 0;
	int b = 0;
	std::vector<Equation> solvedEquations;
	for (int a = 0; a < equations.size(); a++) {
		if (equations[a].modifier == 'a') { // if the modifier is 'a', the equation hasn't been filled out correctly and is invalid.
			std::cout << "invalid equation" << std::endl;
		}
		if (modifiers[a] == ' ')
			std::cout << equations[a].input1 << equations[a].modifier << equations[a].input2 << '=' << equations[a].calculate()<<std::endl;
		if (modifiers[a] != ' ') {
				prevResult =bigboyalculate(prevResult, equations[a].calculate(), modifiers[a]);
				solvedEquations.push_back(Equation());
				solvedEquations[b] = equations[a];
				b++;
		}
	}
	for (int a = 0; a < solvedEquations.size(); a++) {
		std::cout << solvedEquations[a].input1 << solvedEquations[a].modifier << solvedEquations[a].input2;
		if (modifiers[a] != ' ') {
			std::cout << modifiers[a];
		}
	}
	std::cout << "=" << prevResult;
}

float bigboyalculate(float x, float y, char a) {
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