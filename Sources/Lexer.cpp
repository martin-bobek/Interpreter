#include "SyntaxTree.h"

bool Lexer::CreateTokens()
{
	std::string word;
	while (in >> word)
	{
		Iterator begin = word.begin(), it = begin, end = word.end();
		do
		{
			Type type = State_1(it, end);
			switch (type)
			{
			case IF:
				tokens.emplace_back(new If(std::string(begin, it)));
				break;
			case ELSE:
				tokens.emplace_back(new Else(std::string(begin, it)));
				break;
			case WHILE:
				tokens.emplace_back(new While(std::string(begin, it)));
				break;
			case BOOLT:
				tokens.emplace_back(new BoolT(std::string(begin, it)));
				break;
			case INTT:
				tokens.emplace_back(new IntT(std::string(begin, it)));
				break;
			case DOUBLET:
				tokens.emplace_back(new DoubleT(std::string(begin, it)));
				break;
			case TERM:
				tokens.emplace_back(new Term(std::string(begin, it)));
				break;
			case OPENP:
				tokens.emplace_back(new OpenP(std::string(begin, it)));
				break;
			case CLOSEP:
				tokens.emplace_back(new CloseP(std::string(begin, it)));
				break;
			case OPENB:
				tokens.emplace_back(new OpenB(std::string(begin, it)));
				break;
			case CLOSEB:
				tokens.emplace_back(new CloseB(std::string(begin, it)));
				break;
			case ASSIGN:
				tokens.emplace_back(new Assign(std::string(begin, it)));
				break;
			case ADD:
				tokens.emplace_back(new Add(std::string(begin, it)));
				break;
			case SUB:
				tokens.emplace_back(new Sub(std::string(begin, it)));
				break;
			case MULT:
				tokens.emplace_back(new Mult(std::string(begin, it)));
				break;
			case DIV:
				tokens.emplace_back(new Div(std::string(begin, it)));
				break;
			case EQUAL:
				tokens.emplace_back(new Equal(std::string(begin, it)));
				break;
			case NOTEQUAL:
				tokens.emplace_back(new NotEqual(std::string(begin, it)));
				break;
			case GREATER:
				tokens.emplace_back(new Greater(std::string(begin, it)));
				break;
			case LESS:
				tokens.emplace_back(new Less(std::string(begin, it)));
				break;
			case GREATEREQUAL:
				tokens.emplace_back(new GreaterEqual(std::string(begin, it)));
				break;
			case LESSEQUAL:
				tokens.emplace_back(new LessEqual(std::string(begin, it)));
				break;
			case BOOLL:
				tokens.emplace_back(new BoolL(std::string(begin, it)));
				break;
			case INTL:
				tokens.emplace_back(new IntL(std::string(begin, it)));
				break;
			case DOUBLEL:
				tokens.emplace_back(new DoubleL(std::string(begin, it)));
				break;
			case NAME:
				tokens.emplace_back(new Name(std::string(begin, it)));
				break;
			default:
				err = { std::string(begin, end) };
				return false;
			}
			begin = it;
		} while (it != end);
	}
	return true;
}
Lexer::Type Lexer::State_1(Iterator &it, Iterator end)
{
	if (it != end)
	{
		switch (*it++)
		{
		case 'i':
			return State_14(it, end);
		case 'f':
			return State_16(it, end);
		case 'e':
			return State_34(it, end);
		case 'l':
		case 's':
		case 'h':
		case 'o':
		case 'n':
		case 'u':
		case 'r':
		case 'a':
		case 'c':
		case 'g':
		case 'j':
		case 'k':
		case 'm':
		case 'p':
		case 'q':
		case 'v':
		case 'x':
		case 'y':
		case 'z':
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':
		case '_':
			return State_39(it, end);
		case 'w':
			return State_36(it, end);
		case 'b':
			return State_37(it, end);
		case 't':
			return State_32(it, end);
		case 'd':
			return State_38(it, end);
		case ';':
			return TERM;
		case '(':
			return OPENP;
		case ')':
			return CLOSEP;
		case '{':
			return OPENB;
		case '}':
			return CLOSEB;
		case '=':
			return State_8(it, end);
		case '+':
			return ADD;
		case '-':
			return SUB;
		case '*':
			return MULT;
		case '/':
			return DIV;
		case '!':
			return State_15(it, end);
		case '>':
			return State_9(it, end);
		case '<':
			return State_10(it, end);
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			return State_12(it, end);
		case '.':
			return State_31(it, end);
		}
	}
	return INVALID;
}
Lexer::Type Lexer::State_2(Iterator &it, Iterator end)
{
	if (it != end)
	{
		Iterator cont = it;
		Type contValid = INVALID;
		switch (*cont++)
		{
		case 'i':
		case 'f':
		case 'e':
		case 'l':
		case 's':
		case 'w':
		case 'h':
		case 'b':
		case 'o':
		case 'n':
		case 't':
		case 'd':
		case 'u':
		case 'r':
		case 'a':
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case 'c':
		case 'g':
		case 'j':
		case 'k':
		case 'm':
		case 'p':
		case 'q':
		case 'v':
		case 'x':
		case 'y':
		case 'z':
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':
		case '_':
			contValid = State_39(cont, end);
			break;
		}
		if (contValid != INVALID) {
			it = cont;
			return contValid;
		}
	}
	return IF;
}
Lexer::Type Lexer::State_3(Iterator &it, Iterator end)
{
	if (it != end)
	{
		Iterator cont = it;
		Type contValid = INVALID;
		switch (*cont++)
		{
		case 'i':
		case 'f':
		case 'e':
		case 'l':
		case 's':
		case 'w':
		case 'h':
		case 'b':
		case 'o':
		case 'n':
		case 't':
		case 'd':
		case 'u':
		case 'r':
		case 'a':
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case 'c':
		case 'g':
		case 'j':
		case 'k':
		case 'm':
		case 'p':
		case 'q':
		case 'v':
		case 'x':
		case 'y':
		case 'z':
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':
		case '_':
			contValid = State_39(cont, end);
			break;
		}
		if (contValid != INVALID) {
			it = cont;
			return contValid;
		}
	}
	return ELSE;
}
Lexer::Type Lexer::State_4(Iterator &it, Iterator end)
{
	if (it != end)
	{
		Iterator cont = it;
		Type contValid = INVALID;
		switch (*cont++)
		{
		case 'i':
		case 'f':
		case 'e':
		case 'l':
		case 's':
		case 'w':
		case 'h':
		case 'b':
		case 'o':
		case 'n':
		case 't':
		case 'd':
		case 'u':
		case 'r':
		case 'a':
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case 'c':
		case 'g':
		case 'j':
		case 'k':
		case 'm':
		case 'p':
		case 'q':
		case 'v':
		case 'x':
		case 'y':
		case 'z':
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':
		case '_':
			contValid = State_39(cont, end);
			break;
		}
		if (contValid != INVALID) {
			it = cont;
			return contValid;
		}
	}
	return WHILE;
}
Lexer::Type Lexer::State_5(Iterator &it, Iterator end)
{
	if (it != end)
	{
		Iterator cont = it;
		Type contValid = INVALID;
		switch (*cont++)
		{
		case 'i':
		case 'f':
		case 'e':
		case 'l':
		case 's':
		case 'w':
		case 'h':
		case 'b':
		case 'o':
		case 'n':
		case 't':
		case 'd':
		case 'u':
		case 'r':
		case 'a':
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case 'c':
		case 'g':
		case 'j':
		case 'k':
		case 'm':
		case 'p':
		case 'q':
		case 'v':
		case 'x':
		case 'y':
		case 'z':
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':
		case '_':
			contValid = State_39(cont, end);
			break;
		}
		if (contValid != INVALID) {
			it = cont;
			return contValid;
		}
	}
	return BOOLT;
}
Lexer::Type Lexer::State_6(Iterator &it, Iterator end)
{
	if (it != end)
	{
		Iterator cont = it;
		Type contValid = INVALID;
		switch (*cont++)
		{
		case 'i':
		case 'f':
		case 'e':
		case 'l':
		case 's':
		case 'w':
		case 'h':
		case 'b':
		case 'o':
		case 'n':
		case 't':
		case 'd':
		case 'u':
		case 'r':
		case 'a':
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case 'c':
		case 'g':
		case 'j':
		case 'k':
		case 'm':
		case 'p':
		case 'q':
		case 'v':
		case 'x':
		case 'y':
		case 'z':
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':
		case '_':
			contValid = State_39(cont, end);
			break;
		}
		if (contValid != INVALID) {
			it = cont;
			return contValid;
		}
	}
	return INTT;
}
Lexer::Type Lexer::State_7(Iterator &it, Iterator end)
{
	if (it != end)
	{
		Iterator cont = it;
		Type contValid = INVALID;
		switch (*cont++)
		{
		case 'i':
		case 'f':
		case 'e':
		case 'l':
		case 's':
		case 'w':
		case 'h':
		case 'b':
		case 'o':
		case 'n':
		case 't':
		case 'd':
		case 'u':
		case 'r':
		case 'a':
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case 'c':
		case 'g':
		case 'j':
		case 'k':
		case 'm':
		case 'p':
		case 'q':
		case 'v':
		case 'x':
		case 'y':
		case 'z':
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':
		case '_':
			contValid = State_39(cont, end);
			break;
		}
		if (contValid != INVALID) {
			it = cont;
			return contValid;
		}
	}
	return DOUBLET;
}
Lexer::Type Lexer::State_8(Iterator &it, Iterator end)
{
	if (it != end)
	{
		Iterator cont = it;
		Type contValid = INVALID;
		switch (*cont++)
		{
		case '=':
			contValid = EQUAL;
			break;
		}
		if (contValid != INVALID) {
			it = cont;
			return contValid;
		}
	}
	return ASSIGN;
}
Lexer::Type Lexer::State_9(Iterator &it, Iterator end)
{
	if (it != end)
	{
		Iterator cont = it;
		Type contValid = INVALID;
		switch (*cont++)
		{
		case '=':
			contValid = GREATEREQUAL;
			break;
		}
		if (contValid != INVALID) {
			it = cont;
			return contValid;
		}
	}
	return GREATER;
}
Lexer::Type Lexer::State_10(Iterator &it, Iterator end)
{
	if (it != end)
	{
		Iterator cont = it;
		Type contValid = INVALID;
		switch (*cont++)
		{
		case '=':
			contValid = LESSEQUAL;
			break;
		}
		if (contValid != INVALID) {
			it = cont;
			return contValid;
		}
	}
	return LESS;
}
Lexer::Type Lexer::State_11(Iterator &it, Iterator end)
{
	if (it != end)
	{
		Iterator cont = it;
		Type contValid = INVALID;
		switch (*cont++)
		{
		case 'i':
		case 'f':
		case 'e':
		case 'l':
		case 's':
		case 'w':
		case 'h':
		case 'b':
		case 'o':
		case 'n':
		case 't':
		case 'd':
		case 'u':
		case 'r':
		case 'a':
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case 'c':
		case 'g':
		case 'j':
		case 'k':
		case 'm':
		case 'p':
		case 'q':
		case 'v':
		case 'x':
		case 'y':
		case 'z':
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':
		case '_':
			contValid = State_39(cont, end);
			break;
		}
		if (contValid != INVALID) {
			it = cont;
			return contValid;
		}
	}
	return BOOLL;
}
Lexer::Type Lexer::State_12(Iterator &it, Iterator end)
{
	if (it != end)
	{
		Iterator cont = it;
		Type contValid = INVALID;
		switch (*cont++)
		{
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			contValid = State_12(cont, end);
			break;
		case '.':
			contValid = State_13(cont, end);
			break;
		}
		if (contValid != INVALID) {
			it = cont;
			return contValid;
		}
	}
	return INTL;
}
Lexer::Type Lexer::State_13(Iterator &it, Iterator end)
{
	if (it != end)
	{
		Iterator cont = it;
		Type contValid = INVALID;
		switch (*cont++)
		{
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			contValid = State_13(cont, end);
			break;
		}
		if (contValid != INVALID) {
			it = cont;
			return contValid;
		}
	}
	return DOUBLEL;
}
Lexer::Type Lexer::State_14(Iterator &it, Iterator end)
{
	if (it != end)
	{
		Iterator cont = it;
		Type contValid = INVALID;
		switch (*cont++)
		{
		case 'i':
		case 'e':
		case 'l':
		case 's':
		case 'w':
		case 'h':
		case 'b':
		case 'o':
		case 't':
		case 'd':
		case 'u':
		case 'r':
		case 'a':
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case 'c':
		case 'g':
		case 'j':
		case 'k':
		case 'm':
		case 'p':
		case 'q':
		case 'v':
		case 'x':
		case 'y':
		case 'z':
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':
		case '_':
			contValid = State_39(cont, end);
			break;
		case 'f':
			contValid = State_2(cont, end);
			break;
		case 'n':
			contValid = State_28(cont, end);
			break;
		}
		if (contValid != INVALID) {
			it = cont;
			return contValid;
		}
	}
	return NAME;
}
Lexer::Type Lexer::State_15(Iterator &it, Iterator end)
{
	if (it != end)
	{
		switch (*it++)
		{
		case '=':
			return NOTEQUAL;
		}
	}
	return INVALID;
}
Lexer::Type Lexer::State_16(Iterator &it, Iterator end)
{
	if (it != end)
	{
		Iterator cont = it;
		Type contValid = INVALID;
		switch (*cont++)
		{
		case 'i':
		case 'f':
		case 'e':
		case 'l':
		case 's':
		case 'w':
		case 'h':
		case 'b':
		case 'o':
		case 'n':
		case 't':
		case 'd':
		case 'u':
		case 'r':
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case 'c':
		case 'g':
		case 'j':
		case 'k':
		case 'm':
		case 'p':
		case 'q':
		case 'v':
		case 'x':
		case 'y':
		case 'z':
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':
		case '_':
			contValid = State_39(cont, end);
			break;
		case 'a':
			contValid = State_35(cont, end);
			break;
		}
		if (contValid != INVALID) {
			it = cont;
			return contValid;
		}
	}
	return NAME;
}
Lexer::Type Lexer::State_17(Iterator &it, Iterator end)
{
	if (it != end)
	{
		Iterator cont = it;
		Type contValid = INVALID;
		switch (*cont++)
		{
		case 'i':
		case 'f':
		case 'l':
		case 's':
		case 'w':
		case 'h':
		case 'b':
		case 'o':
		case 'n':
		case 't':
		case 'd':
		case 'u':
		case 'r':
		case 'a':
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case 'c':
		case 'g':
		case 'j':
		case 'k':
		case 'm':
		case 'p':
		case 'q':
		case 'v':
		case 'x':
		case 'y':
		case 'z':
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':
		case '_':
			contValid = State_39(cont, end);
			break;
		case 'e':
			contValid = State_3(cont, end);
			break;
		}
		if (contValid != INVALID) {
			it = cont;
			return contValid;
		}
	}
	return NAME;
}
Lexer::Type Lexer::State_18(Iterator &it, Iterator end)
{
	if (it != end)
	{
		Iterator cont = it;
		Type contValid = INVALID;
		switch (*cont++)
		{
		case 'i':
		case 'f':
		case 'l':
		case 's':
		case 'w':
		case 'h':
		case 'b':
		case 'o':
		case 'n':
		case 't':
		case 'd':
		case 'u':
		case 'r':
		case 'a':
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case 'c':
		case 'g':
		case 'j':
		case 'k':
		case 'm':
		case 'p':
		case 'q':
		case 'v':
		case 'x':
		case 'y':
		case 'z':
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':
		case '_':
			contValid = State_39(cont, end);
			break;
		case 'e':
			contValid = State_11(cont, end);
			break;
		}
		if (contValid != INVALID) {
			it = cont;
			return contValid;
		}
	}
	return NAME;
}
Lexer::Type Lexer::State_19(Iterator &it, Iterator end)
{
	if (it != end)
	{
		Iterator cont = it;
		Type contValid = INVALID;
		switch (*cont++)
		{
		case 'i':
		case 'f':
		case 'l':
		case 's':
		case 'w':
		case 'h':
		case 'b':
		case 'o':
		case 'n':
		case 't':
		case 'd':
		case 'u':
		case 'r':
		case 'a':
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case 'c':
		case 'g':
		case 'j':
		case 'k':
		case 'm':
		case 'p':
		case 'q':
		case 'v':
		case 'x':
		case 'y':
		case 'z':
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':
		case '_':
			contValid = State_39(cont, end);
			break;
		case 'e':
			contValid = State_4(cont, end);
			break;
		}
		if (contValid != INVALID) {
			it = cont;
			return contValid;
		}
	}
	return NAME;
}
Lexer::Type Lexer::State_20(Iterator &it, Iterator end)
{
	if (it != end)
	{
		Iterator cont = it;
		Type contValid = INVALID;
		switch (*cont++)
		{
		case 'i':
		case 'f':
		case 'l':
		case 's':
		case 'w':
		case 'h':
		case 'b':
		case 'o':
		case 'n':
		case 't':
		case 'd':
		case 'u':
		case 'r':
		case 'a':
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case 'c':
		case 'g':
		case 'j':
		case 'k':
		case 'm':
		case 'p':
		case 'q':
		case 'v':
		case 'x':
		case 'y':
		case 'z':
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':
		case '_':
			contValid = State_39(cont, end);
			break;
		case 'e':
			contValid = State_7(cont, end);
			break;
		}
		if (contValid != INVALID) {
			it = cont;
			return contValid;
		}
	}
	return NAME;
}
Lexer::Type Lexer::State_21(Iterator &it, Iterator end)
{
	if (it != end)
	{
		Iterator cont = it;
		Type contValid = INVALID;
		switch (*cont++)
		{
		case 'i':
		case 'f':
		case 'e':
		case 's':
		case 'w':
		case 'h':
		case 'b':
		case 'o':
		case 'n':
		case 't':
		case 'd':
		case 'u':
		case 'r':
		case 'a':
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case 'c':
		case 'g':
		case 'j':
		case 'k':
		case 'm':
		case 'p':
		case 'q':
		case 'v':
		case 'x':
		case 'y':
		case 'z':
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':
		case '_':
			contValid = State_39(cont, end);
			break;
		case 'l':
			contValid = State_19(cont, end);
			break;
		}
		if (contValid != INVALID) {
			it = cont;
			return contValid;
		}
	}
	return NAME;
}
Lexer::Type Lexer::State_22(Iterator &it, Iterator end)
{
	if (it != end)
	{
		Iterator cont = it;
		Type contValid = INVALID;
		switch (*cont++)
		{
		case 'i':
		case 'f':
		case 'e':
		case 's':
		case 'w':
		case 'h':
		case 'b':
		case 'o':
		case 'n':
		case 't':
		case 'd':
		case 'u':
		case 'r':
		case 'a':
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case 'c':
		case 'g':
		case 'j':
		case 'k':
		case 'm':
		case 'p':
		case 'q':
		case 'v':
		case 'x':
		case 'y':
		case 'z':
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':
		case '_':
			contValid = State_39(cont, end);
			break;
		case 'l':
			contValid = State_5(cont, end);
			break;
		}
		if (contValid != INVALID) {
			it = cont;
			return contValid;
		}
	}
	return NAME;
}
Lexer::Type Lexer::State_23(Iterator &it, Iterator end)
{
	if (it != end)
	{
		Iterator cont = it;
		Type contValid = INVALID;
		switch (*cont++)
		{
		case 'i':
		case 'f':
		case 'e':
		case 's':
		case 'w':
		case 'h':
		case 'b':
		case 'o':
		case 'n':
		case 't':
		case 'd':
		case 'u':
		case 'r':
		case 'a':
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case 'c':
		case 'g':
		case 'j':
		case 'k':
		case 'm':
		case 'p':
		case 'q':
		case 'v':
		case 'x':
		case 'y':
		case 'z':
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':
		case '_':
			contValid = State_39(cont, end);
			break;
		case 'l':
			contValid = State_20(cont, end);
			break;
		}
		if (contValid != INVALID) {
			it = cont;
			return contValid;
		}
	}
	return NAME;
}
Lexer::Type Lexer::State_24(Iterator &it, Iterator end)
{
	if (it != end)
	{
		Iterator cont = it;
		Type contValid = INVALID;
		switch (*cont++)
		{
		case 'i':
		case 'f':
		case 'e':
		case 'l':
		case 'w':
		case 'h':
		case 'b':
		case 'o':
		case 'n':
		case 't':
		case 'd':
		case 'u':
		case 'r':
		case 'a':
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case 'c':
		case 'g':
		case 'j':
		case 'k':
		case 'm':
		case 'p':
		case 'q':
		case 'v':
		case 'x':
		case 'y':
		case 'z':
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':
		case '_':
			contValid = State_39(cont, end);
			break;
		case 's':
			contValid = State_17(cont, end);
			break;
		}
		if (contValid != INVALID) {
			it = cont;
			return contValid;
		}
	}
	return NAME;
}
Lexer::Type Lexer::State_25(Iterator &it, Iterator end)
{
	if (it != end)
	{
		Iterator cont = it;
		Type contValid = INVALID;
		switch (*cont++)
		{
		case 'i':
		case 'f':
		case 'e':
		case 'l':
		case 'w':
		case 'h':
		case 'b':
		case 'o':
		case 'n':
		case 't':
		case 'd':
		case 'u':
		case 'r':
		case 'a':
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case 'c':
		case 'g':
		case 'j':
		case 'k':
		case 'm':
		case 'p':
		case 'q':
		case 'v':
		case 'x':
		case 'y':
		case 'z':
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':
		case '_':
			contValid = State_39(cont, end);
			break;
		case 's':
			contValid = State_18(cont, end);
			break;
		}
		if (contValid != INVALID) {
			it = cont;
			return contValid;
		}
	}
	return NAME;
}
Lexer::Type Lexer::State_26(Iterator &it, Iterator end)
{
	if (it != end)
	{
		Iterator cont = it;
		Type contValid = INVALID;
		switch (*cont++)
		{
		case 'i':
		case 'f':
		case 'e':
		case 'l':
		case 's':
		case 'w':
		case 'h':
		case 'o':
		case 'n':
		case 't':
		case 'd':
		case 'u':
		case 'r':
		case 'a':
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case 'c':
		case 'g':
		case 'j':
		case 'k':
		case 'm':
		case 'p':
		case 'q':
		case 'v':
		case 'x':
		case 'y':
		case 'z':
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':
		case '_':
			contValid = State_39(cont, end);
			break;
		case 'b':
			contValid = State_23(cont, end);
			break;
		}
		if (contValid != INVALID) {
			it = cont;
			return contValid;
		}
	}
	return NAME;
}
Lexer::Type Lexer::State_27(Iterator &it, Iterator end)
{
	if (it != end)
	{
		Iterator cont = it;
		Type contValid = INVALID;
		switch (*cont++)
		{
		case 'i':
		case 'f':
		case 'e':
		case 'l':
		case 's':
		case 'w':
		case 'h':
		case 'b':
		case 'n':
		case 't':
		case 'd':
		case 'u':
		case 'r':
		case 'a':
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case 'c':
		case 'g':
		case 'j':
		case 'k':
		case 'm':
		case 'p':
		case 'q':
		case 'v':
		case 'x':
		case 'y':
		case 'z':
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':
		case '_':
			contValid = State_39(cont, end);
			break;
		case 'o':
			contValid = State_22(cont, end);
			break;
		}
		if (contValid != INVALID) {
			it = cont;
			return contValid;
		}
	}
	return NAME;
}
Lexer::Type Lexer::State_28(Iterator &it, Iterator end)
{
	if (it != end)
	{
		Iterator cont = it;
		Type contValid = INVALID;
		switch (*cont++)
		{
		case 'i':
		case 'f':
		case 'e':
		case 'l':
		case 's':
		case 'w':
		case 'h':
		case 'b':
		case 'o':
		case 'n':
		case 'd':
		case 'u':
		case 'r':
		case 'a':
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case 'c':
		case 'g':
		case 'j':
		case 'k':
		case 'm':
		case 'p':
		case 'q':
		case 'v':
		case 'x':
		case 'y':
		case 'z':
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':
		case '_':
			contValid = State_39(cont, end);
			break;
		case 't':
			contValid = State_6(cont, end);
			break;
		}
		if (contValid != INVALID) {
			it = cont;
			return contValid;
		}
	}
	return NAME;
}
Lexer::Type Lexer::State_29(Iterator &it, Iterator end)
{
	if (it != end)
	{
		Iterator cont = it;
		Type contValid = INVALID;
		switch (*cont++)
		{
		case 'i':
		case 'f':
		case 'e':
		case 'l':
		case 's':
		case 'w':
		case 'h':
		case 'b':
		case 'o':
		case 'n':
		case 't':
		case 'd':
		case 'r':
		case 'a':
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case 'c':
		case 'g':
		case 'j':
		case 'k':
		case 'm':
		case 'p':
		case 'q':
		case 'v':
		case 'x':
		case 'y':
		case 'z':
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':
		case '_':
			contValid = State_39(cont, end);
			break;
		case 'u':
			contValid = State_18(cont, end);
			break;
		}
		if (contValid != INVALID) {
			it = cont;
			return contValid;
		}
	}
	return NAME;
}
Lexer::Type Lexer::State_30(Iterator &it, Iterator end)
{
	if (it != end)
	{
		Iterator cont = it;
		Type contValid = INVALID;
		switch (*cont++)
		{
		case 'i':
		case 'f':
		case 'e':
		case 'l':
		case 's':
		case 'w':
		case 'h':
		case 'b':
		case 'o':
		case 'n':
		case 't':
		case 'd':
		case 'r':
		case 'a':
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case 'c':
		case 'g':
		case 'j':
		case 'k':
		case 'm':
		case 'p':
		case 'q':
		case 'v':
		case 'x':
		case 'y':
		case 'z':
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':
		case '_':
			contValid = State_39(cont, end);
			break;
		case 'u':
			contValid = State_26(cont, end);
			break;
		}
		if (contValid != INVALID) {
			it = cont;
			return contValid;
		}
	}
	return NAME;
}
Lexer::Type Lexer::State_31(Iterator &it, Iterator end)
{
	if (it != end)
	{
		switch (*it++)
		{
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			return State_13(it, end);
		}
	}
	return INVALID;
}
Lexer::Type Lexer::State_32(Iterator &it, Iterator end)
{
	if (it != end)
	{
		Iterator cont = it;
		Type contValid = INVALID;
		switch (*cont++)
		{
		case 'i':
		case 'f':
		case 'e':
		case 'l':
		case 's':
		case 'w':
		case 'h':
		case 'b':
		case 'o':
		case 'n':
		case 't':
		case 'd':
		case 'u':
		case 'a':
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case 'c':
		case 'g':
		case 'j':
		case 'k':
		case 'm':
		case 'p':
		case 'q':
		case 'v':
		case 'x':
		case 'y':
		case 'z':
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':
		case '_':
			contValid = State_39(cont, end);
			break;
		case 'r':
			contValid = State_29(cont, end);
			break;
		}
		if (contValid != INVALID) {
			it = cont;
			return contValid;
		}
	}
	return NAME;
}
Lexer::Type Lexer::State_33(Iterator &it, Iterator end)
{
	if (it != end)
	{
		Iterator cont = it;
		Type contValid = INVALID;
		switch (*cont++)
		{
		case 'i':
			contValid = State_21(cont, end);
			break;
		case 'f':
		case 'e':
		case 'l':
		case 's':
		case 'w':
		case 'h':
		case 'b':
		case 'o':
		case 'n':
		case 't':
		case 'd':
		case 'u':
		case 'r':
		case 'a':
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case 'c':
		case 'g':
		case 'j':
		case 'k':
		case 'm':
		case 'p':
		case 'q':
		case 'v':
		case 'x':
		case 'y':
		case 'z':
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':
		case '_':
			contValid = State_39(cont, end);
			break;
		}
		if (contValid != INVALID) {
			it = cont;
			return contValid;
		}
	}
	return NAME;
}
Lexer::Type Lexer::State_34(Iterator &it, Iterator end)
{
	if (it != end)
	{
		Iterator cont = it;
		Type contValid = INVALID;
		switch (*cont++)
		{
		case 'i':
		case 'f':
		case 'e':
		case 's':
		case 'w':
		case 'h':
		case 'b':
		case 'o':
		case 'n':
		case 't':
		case 'd':
		case 'u':
		case 'r':
		case 'a':
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case 'c':
		case 'g':
		case 'j':
		case 'k':
		case 'm':
		case 'p':
		case 'q':
		case 'v':
		case 'x':
		case 'y':
		case 'z':
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':
		case '_':
			contValid = State_39(cont, end);
			break;
		case 'l':
			contValid = State_24(cont, end);
			break;
		}
		if (contValid != INVALID) {
			it = cont;
			return contValid;
		}
	}
	return NAME;
}
Lexer::Type Lexer::State_35(Iterator &it, Iterator end)
{
	if (it != end)
	{
		Iterator cont = it;
		Type contValid = INVALID;
		switch (*cont++)
		{
		case 'i':
		case 'f':
		case 'e':
		case 's':
		case 'w':
		case 'h':
		case 'b':
		case 'o':
		case 'n':
		case 't':
		case 'd':
		case 'u':
		case 'r':
		case 'a':
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case 'c':
		case 'g':
		case 'j':
		case 'k':
		case 'm':
		case 'p':
		case 'q':
		case 'v':
		case 'x':
		case 'y':
		case 'z':
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':
		case '_':
			contValid = State_39(cont, end);
			break;
		case 'l':
			contValid = State_25(cont, end);
			break;
		}
		if (contValid != INVALID) {
			it = cont;
			return contValid;
		}
	}
	return NAME;
}
Lexer::Type Lexer::State_36(Iterator &it, Iterator end)
{
	if (it != end)
	{
		Iterator cont = it;
		Type contValid = INVALID;
		switch (*cont++)
		{
		case 'i':
		case 'f':
		case 'e':
		case 'l':
		case 's':
		case 'w':
		case 'b':
		case 'o':
		case 'n':
		case 't':
		case 'd':
		case 'u':
		case 'r':
		case 'a':
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case 'c':
		case 'g':
		case 'j':
		case 'k':
		case 'm':
		case 'p':
		case 'q':
		case 'v':
		case 'x':
		case 'y':
		case 'z':
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':
		case '_':
			contValid = State_39(cont, end);
			break;
		case 'h':
			contValid = State_33(cont, end);
			break;
		}
		if (contValid != INVALID) {
			it = cont;
			return contValid;
		}
	}
	return NAME;
}
Lexer::Type Lexer::State_37(Iterator &it, Iterator end)
{
	if (it != end)
	{
		Iterator cont = it;
		Type contValid = INVALID;
		switch (*cont++)
		{
		case 'i':
		case 'f':
		case 'e':
		case 'l':
		case 's':
		case 'w':
		case 'h':
		case 'b':
		case 'n':
		case 't':
		case 'd':
		case 'u':
		case 'r':
		case 'a':
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case 'c':
		case 'g':
		case 'j':
		case 'k':
		case 'm':
		case 'p':
		case 'q':
		case 'v':
		case 'x':
		case 'y':
		case 'z':
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':
		case '_':
			contValid = State_39(cont, end);
			break;
		case 'o':
			contValid = State_27(cont, end);
			break;
		}
		if (contValid != INVALID) {
			it = cont;
			return contValid;
		}
	}
	return NAME;
}
Lexer::Type Lexer::State_38(Iterator &it, Iterator end)
{
	if (it != end)
	{
		Iterator cont = it;
		Type contValid = INVALID;
		switch (*cont++)
		{
		case 'i':
		case 'f':
		case 'e':
		case 'l':
		case 's':
		case 'w':
		case 'h':
		case 'b':
		case 'n':
		case 't':
		case 'd':
		case 'u':
		case 'r':
		case 'a':
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case 'c':
		case 'g':
		case 'j':
		case 'k':
		case 'm':
		case 'p':
		case 'q':
		case 'v':
		case 'x':
		case 'y':
		case 'z':
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':
		case '_':
			contValid = State_39(cont, end);
			break;
		case 'o':
			contValid = State_30(cont, end);
			break;
		}
		if (contValid != INVALID) {
			it = cont;
			return contValid;
		}
	}
	return NAME;
}
Lexer::Type Lexer::State_39(Iterator &it, Iterator end)
{
	if (it != end)
	{
		Iterator cont = it;
		Type contValid = INVALID;
		switch (*cont++)
		{
		case 'i':
		case 'f':
		case 'e':
		case 'l':
		case 's':
		case 'w':
		case 'h':
		case 'b':
		case 'o':
		case 'n':
		case 't':
		case 'd':
		case 'u':
		case 'r':
		case 'a':
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case 'c':
		case 'g':
		case 'j':
		case 'k':
		case 'm':
		case 'p':
		case 'q':
		case 'v':
		case 'x':
		case 'y':
		case 'z':
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':
		case '_':
			contValid = State_39(cont, end);
			break;
		}
		if (contValid != INVALID) {
			it = cont;
			return contValid;
		}
	}
	return NAME;
}