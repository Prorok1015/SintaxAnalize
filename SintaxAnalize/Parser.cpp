#include "Parser.h"


void Parser::A()
{
	if (currentLexem.status != lastLexStatus)
	{
		lastLexStatus = currentLexem.status;
	}
	setMachineStatus(currentLexem.status);
}

void Parser::B()
{
	if (currentLexem.status != lastLexStatus)
	{
		lastLexStatus = currentLexem.status;
	}
	setMachineStatus(currentLexem.status);
}

void Parser::C()
{
	if (currentLexem.status != lastLexStatus)
	{
		lastLexStatus = currentLexem.status;
	}
	setMachineStatus(currentLexem.status);
}

void Parser::E()
{
	if (currentLexem.status == Lex::LexStatus::error && currentLexem.status != lastLexStatus)
	{
		setMachineStatus(Lex::LexStatus::endline);

		std::cout << "error E";
	}

}

void Parser::WrongSeq()
{
	switch (currentLexem.status)
	{
	case Lex::LexStatus::condition: std::cout << "Wrong Condition" << std::endl;
		break;
	case Lex::LexStatus::lexem: std::cout << "Wrong Lexem" << std::endl;
		break;
	}
}

void Parser::setMachineStatus(Lex::LexStatus wieght)
{
	if (stateMachineMap[(int)machineState][(int)wieght] != State::NoTurn)
	{
		machineState = stateMachineMap[(int)machineState][(int)wieght];
	}
	else
		machineState = State::NoTurn;
};

void Parser::analize()
{
	currentLexem = scan.getLexem();
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
	case Parser::State::WrongSeq: WrongSeq(); return;
		break;
	default: return;
		break;
	}
	analize();
}
;
