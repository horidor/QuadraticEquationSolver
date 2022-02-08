#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>

std::string parseUserInput();

void outputEquation(std::string);
void outputAnswer(std::vector<double>);

std::vector<double> solveEquation(std::string);

int main(int _argc, char* _argv[]) {
	std::string input;

	if (_argc < 2) {
		input = parseUserInput();
	}
	else if (_argc >= 2)
	{
		for (int i = 1; i < _argc; i++)
			std::cout << _argv[i] << std::endl;
	}

	outputEquation(input);
	std::vector<double> roots = solveEquation(input);

	outputAnswer(roots);

	return EXIT_SUCCESS;
}

//
// Parsing input
//

std::string parseUserInput() {
	std::string a, b, c;

	std::cout << "a = ";
	getline(std::cin, a);

	std::cout << "b = ";
	getline(std::cin, b);

	std::cout << "c = ";
	getline(std::cin, c);

	return (a + " " + b + " " + c);
}

//
// Output
//

void outputEquation(std::string coefficients) {
	std::stringstream equationStream(coefficients);
	double number;

	std::cout << "Equation is: ";
	
	equationStream >> number;
	std::cout << "(" << number << ") x^2 + ";

	equationStream >> number;
	std::cout << "(" << number << ") x + ";

	equationStream >> number;
	std::cout << "(" << number << ") = 0\n";
}

void outputAnswer(std::vector<double> roots) {
	if (roots.size() == 2) {
		std::cout << "There are 2 roots.\n";
		std::cout << "x1 = " << roots[0] << "\n";
		std::cout << "x2 = " << roots[1];
	}
	else if (roots.size() == 1) {
		std::cout << "There are 1 root.\n";
		std::cout << "x = " << roots[0];
	}
	else {
		std::cout << "There are 0 roots.\n";
	}
}

//
// Solving
//

std::vector<double> solveEquation(std::string coefficients) {
	std::stringstream coefficientStream(coefficients);
	std::vector<double> roots;
	
	double a, b, c;

	coefficientStream >> a >> b >> c;

	double discriminant = pow(b, 2) - (4 * a * c);

	if (discriminant > 0) {
		double x1, x2;

		x1 = ((-b) + sqrt(discriminant)) / (2 * a);
		x2 = ((-b) - sqrt(discriminant)) / (2 * a);

		roots.push_back(x1);
		roots.push_back(x2);
	}
	else if (discriminant == 0) {
		double x;

		x = (-b) / (2 * a);

		roots.push_back(x);
	}
	
	return roots;
}