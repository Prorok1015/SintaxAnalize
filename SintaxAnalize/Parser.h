#pragma once

#include "Scanner.h"
#include <string>
#include <Windows.h>

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
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	Scanner scan;
	Lex currentLexem;
	Lex::LexStatus lastLexStatus = Lex::LexStatus::endline;
	State machineState = State::A;												//	  |	lexem | condition | error | endline
	State stateMachineMap[5][4] = {												//----|-------|-----------|-------|----------
		{ State::WrongSeq,	State::B,		State::E,		State::WrongSeq},	//	A |		W |		B	  |   E   |     C
		{ State::A,			State::WrongSeq,State::E,		State::C},			//	B |		A |		W     |	  E   |		W         
		{ State::NoTurn,	State::NoTurn,	State::NoTurn,	State::NoTurn},		//	C |	  End |	  End	  |	End   |	  End
		{ State::A,			State::B,		State::B,		State::C},			//	E |		A |		B     |	  B	  |	    C
		{ State::A,			State::B,		State::E,		State::C}			//	W |		A |		B     |	  E	  |	    C
	};

	void A();
	void B();
	void C();
	void E();
	void WrongSeq();
	void setMachineStatus(Lex::LexStatus wieght);
	void printLex(Lex lex);
	void SetColor(int ForgC);
public:
	Parser(std::string AnalizeText) {
		scan.setScanFile(AnalizeText);
		currentLexem = scan.getLexem();
	};
	void analize();
};

