#pragma once

//#define DEBUGING


#include <string>
#include <queue>
#include <iostream>



struct Lex
{
	enum class LexStatus
	{
		condition,
		lexem,
		error,
		endline
	};
	std::string lex;
	LexStatus status;
	Lex(std::string Lex) :lex(Lex) {};
	Lex() {};
	Lex(LexStatus state) :status(state) {};
	std::vector<size_t> errors;
};

class Scanner
{
	std::string sourseFile;
	std::string currentLexems;
	std::queue<Lex> lexems;
	std::string conditions = "+-/*";
	const char separatorC = ' ';
	const char endFileC = '\0';

	void scanFile();
	Lex::LexStatus isCorrect(const char ch);
public: 
	Scanner(std::string File) :sourseFile(File) {};
	Scanner();

	Lex getLexem();

};

