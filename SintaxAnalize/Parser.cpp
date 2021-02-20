#include "Parser.h"


void Parser::A()
{
	if (currentLexem.status != lastLexStatus)
	{
		lastLexStatus = currentLexem.status;
	}

}

void Parser::B()
{
	if (currentLexem.status != lastLexStatus)
	{
		lastLexStatus = currentLexem.status;
	}
	
}

void Parser::C()
{
	/*if (currentLexem.status != lastLexStatus)
	{
		lastLexStatus = currentLexem.status;
	}
	setMachineStatus(currentLexem.status);*/

	std::cout << std::endl;
}

void Parser::E()
{
	//std::cout << "error E";
}

void Parser::WrongSeq()
{
	SetColor(12);
	switch (lastLexStatus)
	{
	case Lex::LexStatus::condition:  std::cout << "<--[Ожидалось слово] ";
		break;
	case Lex::LexStatus::lexem: std::cout << "<--[Ожидался знак] ";
		break;
	case Lex::LexStatus::endline: std::cout << "<--[Выражение не может кончаться знаком] ";
		break;
	}
	SetColor(15);
}

/*
	TODO:Сделать отдельный класс конечного автомата
*/
void Parser::setMachineStatus(Lex::LexStatus wieght)
{
	machineState = stateMachineMap[(int)machineState][(int)wieght];
};

void Parser::printLex(Lex lex)
{

	if (lex.errors.empty())
	{
		SetColor(15);
		std::cout << lex.lex << " ";
	}
	else
	{
/*
		TODO:            Оптимизировать алгорит              
*/
		std::vector<size_t>::iterator iError = lex.errors.begin();
		for (size_t i = 0; i < lex.lex.length(); ++i)
		{
			if (iError != lex.errors.end() && (*iError == i))
			{
				SetColor(12);
				++iError;
			}
			else
				SetColor(15);
			std::cout << lex.lex[i];

		}
		SetColor(14);
		std::cout << "<--[Грамматическая ошибка] "; // , слово может состоять только из символов от 'A' до 'Z'
		SetColor(15);
	}
};

void Parser::analize()
{

	switch (machineState)
	{
	case Parser::State::A: A();
		break;
	case Parser::State::B: B();
		break;
	case Parser::State::C: C(); return;
		break;
	case Parser::State::E: E(); 
		break;
	case Parser::State::WrongSeq: WrongSeq();
		break;
	default: std::cout << std::endl << " Critical ERROR <No Turn>" << std::endl; return;
		break;
	}

	printLex(currentLexem);

	setMachineStatus(currentLexem.status);
	currentLexem = scan.getLexem();
	analize();
};

/*
	TODO: Создать список возможного цвета тектса. Для ясного понимания человеоком.
*/
void Parser::SetColor(int ForgC)
{

	WORD wColor;
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	if (GetConsoleScreenBufferInfo(handle, &csbi))
	{
		wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
		SetConsoleTextAttribute(handle, wColor);
	}
	return;
}