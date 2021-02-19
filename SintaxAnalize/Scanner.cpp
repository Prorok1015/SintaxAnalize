#include "Scanner.h"

void Scanner::scanFile()
{
	if (!sourseFile.empty())
	{
		int firstIndex = 0;
		std::vector<size_t> errorsIndex(10);
		Lex::LexStatus status = Lex::LexStatus::error;
		for (size_t index = 0; index <= sourseFile.length(); ++index)
		{	
			char value = sourseFile[index];
			if ((value == separatorC || value == endFileC) && index != 0)
			{

				int countChar = index - firstIndex;
				Lex l(sourseFile.substr(firstIndex, countChar));
				l.status = status;
				l.errors = errorsIndex;
				lexems.push(l);

				#ifdef DEBUGING
					std::cout << l.lex << " " << (int)l.status << std::endl;
				#endif

				firstIndex = index + 1;
				errorsIndex.clear();
			}
			else
			{
				status = isCorrect(value);
				if (status == Lex::LexStatus::error)
				{
					errorsIndex.push_back(index);
				}
			}
		}
	}
}

Scanner::Scanner()
{
	sourseFile = "ABC - BCA + DFG";
	scanFile();
}

Lex Scanner::getLexem()
{	
	if (lexems.empty())
		return Lex(Lex::LexStatus::endline);
	Lex result = lexems.front();
	lexems.pop();
	return result;
}

Lex::LexStatus Scanner::isCorrect(const char ch)
{
	for (size_t i = 0; i < conditions.length(); ++i)
	{
		if (ch == conditions[i])
			return Lex::LexStatus::condition;
	}
	if (('A' <= ch) && (ch <= 'Z'))
	{
		return Lex::LexStatus::lexem;
	}

	return Lex::LexStatus::error;
}