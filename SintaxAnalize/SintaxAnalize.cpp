#include <iostream> 
#include "Parser.h"

int main()
{
	setlocale(0, "ru");
	std::cout << " Введите простое выражение соответствуюзее услувию [[Слово] [Знак] [Слово]]" << std::endl;
	std::string AnText;
	std::getline(std::cin, AnText);

	Parser pars(AnText);
	pars.analize();

	system("PAUSE");
	return 0;
}

