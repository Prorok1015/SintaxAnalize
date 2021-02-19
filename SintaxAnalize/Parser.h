#pragma once

#include "Scanner.h"
#include <string>

class Parser
{
	enum class State 
	{
		A,
		B,
		C,
		E,
		WrongSeq,
		NoTurn
	};
	
	Scanner scan;
	Lex currentLexem;
	Lex::LexStatus lastLexStatus = Lex::LexStatus::endline;
	State machineState = State::A;
	State stateMachineMap[4][4] = { 
		{ State::WrongSeq,	State::B,		State::E,		State::C},
		{ State::A,			State::WrongSeq,State::E,		State::WrongSeq},
		{ State::NoTurn,	State::NoTurn,	State::NoTurn,	State::NoTurn},
		{ State::NoTurn,	State::NoTurn,	State::NoTurn,	State::C}
	};

	void A();
	void B();
	void C();
	void E();
	void WrongSeq();
	void setMachineStatus(Lex::LexStatus wieght);

public:
	Parser() {};
	void analize();
};

