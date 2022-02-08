#include <iostream>
#include <string>

int main(int _argc, char* _argv[]) {
	if (_argc < 2) {
		std::string input;

		getline(std::cin, input);

		std::cout << input << std::endl;
	}
	else if (_argc >= 2)
	{
		for (int i = 1; i < _argc; i++)
			std::cout << _argv[i] << std::endl;
	}

	return EXIT_SUCCESS;
}