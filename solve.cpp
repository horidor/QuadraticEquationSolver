#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <fstream>

std::string parseUserInput();
std::string parseNumber(std::string);

std::string parseFile(std::string);

void outputEquation(std::string);
void outputAnswer(std::vector<double>);

std::vector<double> solveEquation(std::string);

int main(int _argc, char* _argv[]) {
	std::string input;

	try {
		if (_argc < 2) {
			input = parseUserInput();
		}
		else if (_argc == 2)
		{
			input = parseFile(std::string(_argv[1]));
		}
		else
		{
			throw std::exception("Error: too much arguments in command line");
		}
	}
	catch (std::exception excpt) {
		std::cout << excpt.what();
		return EXIT_FAILURE;
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

	a = parseNumber("a");
	b = parseNumber("b");
	c = parseNumber("c");

	return (a + " " + b + " " + c);
}

std::string parseNumber(std::string number) {
	std::string input;
	bool doubleflag = false;

	while (true) {

		try {
			std::cout << number << " = ";
			getline(std::cin, input);

			if ((number == "a") && (stod(input) == 0.0f)) throw std::exception("a = 0");

			for (auto it : input) {
				if (!isdigit(it) && (it != '-'))
				{
					if ((it == '.') && (!doubleflag))
						doubleflag = true;
					else
						throw std::exception(input.c_str());
				}
			}

			break;

		}
		catch (std::exception excpt) {
			std::cout << "Error. Expected a valid real number, got " << excpt.what() << " instead.\n";
		}

	}

	return input;
}

//
// Parsing file
//

std::string parseFile(std::string filename) {
	std::string input, check;
	std::stringstream checkinput;

	std::fstream file(filename, std::ios::in);
	if (file.fail()) {
		throw std::exception(("Error: file " + filename + " doesn't exist").c_str());
	}

	getline(file, input);
	checkinput.str(input);
	
	file >> check;

	if (check != "") {
		throw std::exception("Error: incorrect file format.");
	}

	double number;

	checkinput >> number;
	if (!checkinput.bad()) {
		if (number == 0.0f) {
			throw std::exception("Error: a is zero");
		}
	}

	for (int i = 0; i < 2; i++) {
		checkinput >> number;
		if (checkinput.bad()) {
			throw std::exception("Error: incorrect file format.");
		}
	}

	checkinput >> number;
	if (!checkinput.eof()) {
		throw std::exception("Error: incorrect file format.");
	}

	return input;
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
		std::cout << "There is 1 root.\n";
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