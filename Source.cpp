#include <iostream>
#include <istream>
#include <memory>
#include <stack>
#include <string>
#include <vector>
#include <sstream>

using std::move;

class Symbol;
class Stat1;
class Stat2;
class Exp;
class Terminal;
class OpenB;
class CloseB;
class IntT;
class Name;
class Term;
class DoubleT;
class Assign;
class Add;
class Sub;
class Mult;
class Div;
class OpenP;
class CloseP;
class IntL;
class DoubleL;

typedef std::unique_ptr<Symbol> pSymbol;
typedef std::unique_ptr<Stat1> pStat1;
typedef std::unique_ptr<Stat2> pStat2;
typedef std::unique_ptr<Exp> pExp;
typedef std::unique_ptr<Terminal> pTerminal;
typedef std::unique_ptr<OpenB> pOpenB;
typedef std::unique_ptr<CloseB> pCloseB;
typedef std::unique_ptr<IntT> pIntT;
typedef std::unique_ptr<Name> pName;
typedef std::unique_ptr<Term> pTerm;
typedef std::unique_ptr<DoubleT> pDoubleT;
typedef std::unique_ptr<Assign> pAssign;
typedef std::unique_ptr<Add> pAdd;
typedef std::unique_ptr<Sub> pSub;
typedef std::unique_ptr<Mult> pMult;
typedef std::unique_ptr<Div> pDiv;
typedef std::unique_ptr<OpenP> pOpenP;
typedef std::unique_ptr<CloseP> pCloseP;
typedef std::unique_ptr<IntL> pIntL;
typedef std::unique_ptr<DoubleL> pDoubleL;
typedef std::stack<size_t, std::vector<size_t>> Stack;
typedef std::stack<pSymbol, std::vector<pSymbol>> SymStack;
typedef std::string::const_iterator Iterator;

template<typename Dest, typename Source>
std::unique_ptr<Dest> pCast(std::unique_ptr<Source> &&src)
{
	return std::unique_ptr<Dest>(static_cast<Dest *>(src.release()));
}

class Parser
{
public:
	Parser(std::vector<pTerminal> &&in) : input(move(in)) {}
	bool CreateTree();
	pStat1 GetTree() { return move(tree); };

	struct Error
	{
		std::string Location;
		std::string Message;
	};
	Error GetErrorReport() { return move(err); }
private:
	pStat1 tree;
	std::vector<pTerminal> input;
	Error err;
};
class Lexer
{
public:
	struct Error
	{
		std::string Token;
	};

	Lexer(std::istream &in) : in(in) {}
	bool CreateTokens();
	std::vector<pTerminal> GetTokens() { return move(tokens); };
	Error GetErrorReport() { return move(err); }
private:
	enum Type { INVALID, INTT, DOUBLET, TERM, OPENP, CLOSEP, OPENB, CLOSEB, ASSIGN, ADD, SUB, MULT, DIV, INTL, DOUBLEL, NAME };

	static Type State_1(Iterator &it, Iterator end);
	static Type State_2(Iterator &it, Iterator end);
	static Type State_3(Iterator &it, Iterator end);
	static Type State_4(Iterator &it, Iterator end);
	static Type State_5(Iterator &it, Iterator end);
	static Type State_6(Iterator &it, Iterator end);
	static Type State_7(Iterator &it, Iterator end);
	static Type State_8(Iterator &it, Iterator end);
	static Type State_9(Iterator &it, Iterator end);
	static Type State_10(Iterator &it, Iterator end);
	static Type State_11(Iterator &it, Iterator end);
	static Type State_12(Iterator &it, Iterator end);
	static Type State_13(Iterator &it, Iterator end);
	static Type State_14(Iterator &it, Iterator end);

	std::istream &in;
	std::vector<pTerminal> tokens;
	Error err;
};

class Symbol
{
public:
	virtual ~Symbol() = 0;
};
Symbol::~Symbol() = default;
class Stat1 : public Symbol
{
public:
	virtual ~Stat1() = 0;
	static bool Process(Stack &stack, SymStack &symStack, Parser::Error &err);
};
Stat1::~Stat1() = default;
class Stat11 : public Stat1
{
public:
	Stat11(pStat1 &&sym1, pStat2 &&sym2) : symbol_1(move(sym1)), symbol_2(move(sym2)) {}
private:
	const pStat1 symbol_1;
	const pStat2 symbol_2;
};
class Stat12 : public Stat1
{
public:
	Stat12() = default;
};
class Stat2 : public Symbol
{
public:
	virtual ~Stat2() = 0;
	static bool Process(Stack &stack, SymStack &symStack, Parser::Error &err);
};
Stat2::~Stat2() = default;
class Stat21 : public Stat2
{
public:
	Stat21(pOpenB &&sym1, pStat1 &&sym2, pCloseB &&sym3) : symbol_1(move(sym1)), symbol_2(move(sym2)), symbol_3(move(sym3)) {}
private:
	const pOpenB symbol_1;
	const pStat1 symbol_2;
	const pCloseB symbol_3;
};
class Stat22 : public Stat2
{
public:
	Stat22(pIntT &&sym1, pName &&sym2, pTerm &&sym3) : symbol_1(move(sym1)), symbol_2(move(sym2)), symbol_3(move(sym3)) {}
private:
	const pIntT symbol_1;
	const pName symbol_2;
	const pTerm symbol_3;
};
class Stat23 : public Stat2
{
public:
	Stat23(pDoubleT &&sym1, pName &&sym2, pTerm &&sym3) : symbol_1(move(sym1)), symbol_2(move(sym2)), symbol_3(move(sym3)) {}
private:
	const pDoubleT symbol_1;
	const pName symbol_2;
	const pTerm symbol_3;
};
class Stat24 : public Stat2
{
public:
	Stat24(pIntT &&sym1, pName &&sym2, pAssign &&sym3, pExp &&sym4, pTerm &&sym5) : symbol_1(move(sym1)), symbol_2(move(sym2)), symbol_3(move(sym3)), symbol_4(move(sym4)), symbol_5(move(sym5)) {}
private:
	const pIntT symbol_1;
	const pName symbol_2;
	const pAssign symbol_3;
	const pExp symbol_4;
	const pTerm symbol_5;
};
class Stat25 : public Stat2
{
public:
	Stat25(pDoubleT &&sym1, pName &&sym2, pAssign &&sym3, pExp &&sym4, pTerm &&sym5) : symbol_1(move(sym1)), symbol_2(move(sym2)), symbol_3(move(sym3)), symbol_4(move(sym4)), symbol_5(move(sym5)) {}
private:
	const pDoubleT symbol_1;
	const pName symbol_2;
	const pAssign symbol_3;
	const pExp symbol_4;
	const pTerm symbol_5;
};
class Stat26 : public Stat2
{
public:
	Stat26(pName &&sym1, pAssign &&sym2, pExp &&sym3, pTerm &&sym4) : symbol_1(move(sym1)), symbol_2(move(sym2)), symbol_3(move(sym3)), symbol_4(move(sym4)) {}
private:
	const pName symbol_1;
	const pAssign symbol_2;
	const pExp symbol_3;
	const pTerm symbol_4;
};
class Exp : public Symbol
{
public:
	virtual ~Exp() = 0;
	static bool Process(Stack &stack, SymStack &symStack, Parser::Error &err);
};
Exp::~Exp() = default;
class Exp1 : public Exp
{
public:
	Exp1(pExp &&sym1, pAdd &&sym2, pExp &&sym3) : symbol_1(move(sym1)), symbol_2(move(sym2)), symbol_3(move(sym3)) {}
private:
	const pExp symbol_1;
	const pAdd symbol_2;
	const pExp symbol_3;
};
class Exp2 : public Exp
{
public:
	Exp2(pExp &&sym1, pSub &&sym2, pExp &&sym3) : symbol_1(move(sym1)), symbol_2(move(sym2)), symbol_3(move(sym3)) {}
private:
	const pExp symbol_1;
	const pSub symbol_2;
	const pExp symbol_3;
};
class Exp3 : public Exp
{
public:
	Exp3(pExp &&sym1, pMult &&sym2, pExp &&sym3) : symbol_1(move(sym1)), symbol_2(move(sym2)), symbol_3(move(sym3)) {}
private:
	const pExp symbol_1;
	const pMult symbol_2;
	const pExp symbol_3;
};
class Exp4 : public Exp
{
public:
	Exp4(pExp &&sym1, pDiv &&sym2, pExp &&sym3) : symbol_1(move(sym1)), symbol_2(move(sym2)), symbol_3(move(sym3)) {}
private:
	const pExp symbol_1;
	const pDiv symbol_2;
	const pExp symbol_3;
};
class Exp5 : public Exp
{
public:
	Exp5(pOpenP &&sym1, pExp &&sym2, pCloseP &&sym3) : symbol_1(move(sym1)), symbol_2(move(sym2)), symbol_3(move(sym3)) {}
private:
	const pOpenP symbol_1;
	const pExp symbol_2;
	const pCloseP symbol_3;
};
class Exp6 : public Exp
{
public:
	Exp6(pIntL &&sym1) : symbol_1(move(sym1)) {}
private:
	const pIntL symbol_1;
};
class Exp7 : public Exp
{
public:
	Exp7(pDoubleL &&sym1) : symbol_1(move(sym1)) {}
private:
	const pDoubleL symbol_1;
};
class Exp8 : public Exp
{
public:
	Exp8(pName &&sym1) : symbol_1(move(sym1)) {}
private:
	const pName symbol_1;
};
class Terminal : public Symbol
{
public:
	virtual ~Terminal() = 0;
	virtual bool Process(Stack &stack, SymStack &symStack, Parser::Error &err) const = 0;
	friend std::ostream &operator<<(std::ostream &os, const Terminal &term) { return term.print(os); }
private:
	virtual std::ostream &print(std::ostream &os) const = 0;
};
Terminal::~Terminal() = default;
class IntT : public Terminal
{
public:
	IntT(std::string &&value) : value(move(value)) {}
	bool Process(Stack &stack, SymStack &symStack, Parser::Error &err) const;
private:
	std::ostream &print(std::ostream &os) const { return os << "INTT[" << value << ']'; }
	const std::string value;
};
class DoubleT : public Terminal
{
public:
	DoubleT(std::string &&value) : value(move(value)) {}
	bool Process(Stack &stack, SymStack &symStack, Parser::Error &err) const;
private:
	std::ostream &print(std::ostream &os) const { return os << "DOUBLET[" << value << ']'; }
	const std::string value;
};
class Term : public Terminal
{
public:
	Term(std::string &&value) : value(move(value)) {}
	bool Process(Stack &stack, SymStack &symStack, Parser::Error &err) const;
private:
	std::ostream &print(std::ostream &os) const { return os << "TERM[" << value << ']'; }
	const std::string value;
};
class OpenP : public Terminal
{
public:
	OpenP(std::string &&value) : value(move(value)) {}
	bool Process(Stack &stack, SymStack &symStack, Parser::Error &err) const;
private:
	std::ostream &print(std::ostream &os) const { return os << "OPENP[" << value << ']'; }
	const std::string value;
};
class CloseP : public Terminal
{
public:
	CloseP(std::string &&value) : value(move(value)) {}
	bool Process(Stack &stack, SymStack &symStack, Parser::Error &err) const;
private:
	std::ostream &print(std::ostream &os) const { return os << "CLOSEP[" << value << ']'; }
	const std::string value;
};
class OpenB : public Terminal
{
public:
	OpenB(std::string &&value) : value(move(value)) {}
	bool Process(Stack &stack, SymStack &symStack, Parser::Error &err) const;
private:
	std::ostream &print(std::ostream &os) const { return os << "OPENB[" << value << ']'; }
	const std::string value;
};
class CloseB : public Terminal
{
public:
	CloseB(std::string &&value) : value(move(value)) {}
	bool Process(Stack &stack, SymStack &symStack, Parser::Error &err) const;
private:
	std::ostream &print(std::ostream &os) const { return os << "CLOSEB[" << value << ']'; }
	const std::string value;
};
class Assign : public Terminal
{
public:
	Assign(std::string &&value) : value(move(value)) {}
	bool Process(Stack &stack, SymStack &symStack, Parser::Error &err) const;
private:
	std::ostream &print(std::ostream &os) const { return os << "ASSIGN[" << value << ']'; }
	const std::string value;
};
class Add : public Terminal
{
public:
	Add(std::string &&value) : value(move(value)) {}
	bool Process(Stack &stack, SymStack &symStack, Parser::Error &err) const;
private:
	std::ostream &print(std::ostream &os) const { return os << "ADD[" << value << ']'; }
	const std::string value;
};
class Sub : public Terminal
{
public:
	Sub(std::string &&value) : value(move(value)) {}
	bool Process(Stack &stack, SymStack &symStack, Parser::Error &err) const;
private:
	std::ostream &print(std::ostream &os) const { return os << "SUB[" << value << ']'; }
	const std::string value;
};
class Mult : public Terminal
{
public:
	Mult(std::string &&value) : value(move(value)) {}
	bool Process(Stack &stack, SymStack &symStack, Parser::Error &err) const;
private:
	std::ostream &print(std::ostream &os) const { return os << "MULT[" << value << ']'; }
	const std::string value;
};
class Div : public Terminal
{
public:
	Div(std::string &&value) : value(move(value)) {}
	bool Process(Stack &stack, SymStack &symStack, Parser::Error &err) const;
private:
	std::ostream &print(std::ostream &os) const { return os << "DIV[" << value << ']'; }
	const std::string value;
};
class IntL : public Terminal
{
public:
	IntL(std::string &&value) : value(move(value)) {}
	bool Process(Stack &stack, SymStack &symStack, Parser::Error &err) const;
private:
	std::ostream &print(std::ostream &os) const { return os << "INTL[" << value << ']'; }
	const std::string value;
};
class DoubleL : public Terminal
{
public:
	DoubleL(std::string &&value) : value(move(value)) {}
	bool Process(Stack &stack, SymStack &symStack, Parser::Error &err) const;
private:
	std::ostream &print(std::ostream &os) const { return os << "DOUBLEL[" << value << ']'; }
	const std::string value;
};
class Name : public Terminal
{
public:
	Name(std::string &&value) : value(move(value)) {}
	bool Process(Stack &stack, SymStack &symStack, Parser::Error &err) const;
private:
	std::ostream &print(std::ostream &os) const { return os << "NAME[" << value << ']'; }
	const std::string value;
};
namespace End
{
	bool Process(Stack &stack, SymStack &symStack, Parser::Error &err);
}

int main()
{
	while (true)
	{
		Lexer lexer(std::cin);
		bool accepted = lexer.CreateTokens();
		std::cin.clear();
		std::cin.ignore();
		if (!accepted)
		{
			Lexer::Error err = lexer.GetErrorReport();
			std::cout << "Error: " << err.Token << std::endl;
			continue;
		}
		Parser parser(lexer.GetTokens());
		if (!parser.CreateTree())
		{
			Parser::Error err = parser.GetErrorReport();
			std::cout << "Error in " << err.Location << ": " << err.Message << std::endl;
			continue;
		}
		pStat1 tree = parser.GetTree();
		std::cout << "Input accepted" << std::endl;
	}
}

bool Parser::CreateTree()
{
	Stack stack;
	SymStack symStack;
	stack.push(0);
	for (auto &symbol : input)
	{
		if (!symbol->Process(stack, symStack, err))
			return false;
		symStack.push(move(symbol));
	}
	if (!End::Process(stack, symStack, err))
		return false;
	tree = pCast<Stat1>(move(symStack.top()));
	return true;
}
bool Stat1::Process(Stack &stack, SymStack &symStack, Parser::Error &err)
{
	switch (stack.top())
	{
	case 0:
		stack.push(1);
		break;
	case 2:
		stack.push(7);
		break;
	default:
		err = { "Stat1::Process", "Syntax Error!" };
		return false;
	}
	return true;
}
bool Stat2::Process(Stack &stack, SymStack &symStack, Parser::Error &err)
{
	switch (stack.top())
	{
	case 1:
	case 7:
		stack.push(6);
		break;
	default:
		err = { "Stat2::Process", "Syntax Error!" };
		return false;
	}
	return true;
}
bool Exp::Process(Stack &stack, SymStack &symStack, Parser::Error &err)
{
	switch (stack.top())
	{
	case 9:
		stack.push(18);
		break;
	case 13:
		stack.push(21);
		break;
	case 15:
		stack.push(22);
		break;
	case 20:
		stack.push(28);
		break;
	case 24:
		stack.push(31);
		break;
	case 25:
		stack.push(32);
		break;
	case 26:
		stack.push(33);
		break;
	case 27:
		stack.push(34);
		break;
	default:
		err = { "Exp::Process", "Syntax Error!" };
		return false;
	}
	return true;
}
bool OpenB::Process(Stack &stack, SymStack &symStack, Parser::Error &err) const
{
	switch (stack.top())
	{
	case 0:
	case 2:
		symStack.emplace(new Stat12());
		return Stat1::Process(stack, symStack, err) && Process(stack, symStack, err);
	case 1:
	case 7:
		stack.push(2);
		break;
	case 6:
	{
		stack.pop();
		stack.pop();
		pStat2 sym2 = pCast<Stat2>(move(symStack.top()));
		symStack.pop();
		pStat1 sym1 = pCast<Stat1>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat11(move(sym1), move(sym2)));
		return Stat1::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 11:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pCloseB sym3 = pCast<CloseB>(move(symStack.top()));
		symStack.pop();
		pStat1 sym2 = pCast<Stat1>(move(symStack.top()));
		symStack.pop();
		pOpenB sym1 = pCast<OpenB>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat21(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 12:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pTerm sym3 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pName sym2 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		pIntT sym1 = pCast<IntT>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat22(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 19:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pTerm sym3 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pName sym2 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		pDoubleT sym1 = pCast<DoubleT>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat23(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 23:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pTerm sym4 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pExp sym3 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pAssign sym2 = pCast<Assign>(move(symStack.top()));
		symStack.pop();
		pName sym1 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat26(move(sym1), move(sym2), move(sym3), move(sym4)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 29:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pTerm sym5 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pExp sym4 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pAssign sym3 = pCast<Assign>(move(symStack.top()));
		symStack.pop();
		pName sym2 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		pIntT sym1 = pCast<IntT>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat24(move(sym1), move(sym2), move(sym3), move(sym4), move(sym5)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 35:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pTerm sym5 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pExp sym4 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pAssign sym3 = pCast<Assign>(move(symStack.top()));
		symStack.pop();
		pName sym2 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		pDoubleT sym1 = pCast<DoubleT>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat25(move(sym1), move(sym2), move(sym3), move(sym4), move(sym5)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	default:
		err = { "OpenB::Process", "Syntax Error!" };
		return false;
	}
	return true;
}
bool CloseB::Process(Stack &stack, SymStack &symStack, Parser::Error &err) const
{
	switch (stack.top())
	{
	case 0:
	case 2:
		symStack.emplace(new Stat12());
		return Stat1::Process(stack, symStack, err) && Process(stack, symStack, err);
	case 6:
	{
		stack.pop();
		stack.pop();
		pStat2 sym2 = pCast<Stat2>(move(symStack.top()));
		symStack.pop();
		pStat1 sym1 = pCast<Stat1>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat11(move(sym1), move(sym2)));
		return Stat1::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 7:
		stack.push(11);
		break;
	case 11:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pCloseB sym3 = pCast<CloseB>(move(symStack.top()));
		symStack.pop();
		pStat1 sym2 = pCast<Stat1>(move(symStack.top()));
		symStack.pop();
		pOpenB sym1 = pCast<OpenB>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat21(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 12:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pTerm sym3 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pName sym2 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		pIntT sym1 = pCast<IntT>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat22(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 19:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pTerm sym3 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pName sym2 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		pDoubleT sym1 = pCast<DoubleT>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat23(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 23:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pTerm sym4 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pExp sym3 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pAssign sym2 = pCast<Assign>(move(symStack.top()));
		symStack.pop();
		pName sym1 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat26(move(sym1), move(sym2), move(sym3), move(sym4)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 29:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pTerm sym5 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pExp sym4 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pAssign sym3 = pCast<Assign>(move(symStack.top()));
		symStack.pop();
		pName sym2 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		pIntT sym1 = pCast<IntT>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat24(move(sym1), move(sym2), move(sym3), move(sym4), move(sym5)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 35:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pTerm sym5 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pExp sym4 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pAssign sym3 = pCast<Assign>(move(symStack.top()));
		symStack.pop();
		pName sym2 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		pDoubleT sym1 = pCast<DoubleT>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat25(move(sym1), move(sym2), move(sym3), move(sym4), move(sym5)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	default:
		err = { "CloseB::Process", "Syntax Error!" };
		return false;
	}
	return true;
}
bool IntT::Process(Stack &stack, SymStack &symStack, Parser::Error &err) const
{
	switch (stack.top())
	{
	case 0:
	case 2:
		symStack.emplace(new Stat12());
		return Stat1::Process(stack, symStack, err) && Process(stack, symStack, err);
	case 1:
	case 7:
		stack.push(3);
		break;
	case 6:
	{
		stack.pop();
		stack.pop();
		pStat2 sym2 = pCast<Stat2>(move(symStack.top()));
		symStack.pop();
		pStat1 sym1 = pCast<Stat1>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat11(move(sym1), move(sym2)));
		return Stat1::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 11:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pCloseB sym3 = pCast<CloseB>(move(symStack.top()));
		symStack.pop();
		pStat1 sym2 = pCast<Stat1>(move(symStack.top()));
		symStack.pop();
		pOpenB sym1 = pCast<OpenB>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat21(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 12:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pTerm sym3 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pName sym2 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		pIntT sym1 = pCast<IntT>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat22(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 19:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pTerm sym3 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pName sym2 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		pDoubleT sym1 = pCast<DoubleT>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat23(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 23:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pTerm sym4 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pExp sym3 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pAssign sym2 = pCast<Assign>(move(symStack.top()));
		symStack.pop();
		pName sym1 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat26(move(sym1), move(sym2), move(sym3), move(sym4)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 29:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pTerm sym5 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pExp sym4 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pAssign sym3 = pCast<Assign>(move(symStack.top()));
		symStack.pop();
		pName sym2 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		pIntT sym1 = pCast<IntT>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat24(move(sym1), move(sym2), move(sym3), move(sym4), move(sym5)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 35:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pTerm sym5 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pExp sym4 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pAssign sym3 = pCast<Assign>(move(symStack.top()));
		symStack.pop();
		pName sym2 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		pDoubleT sym1 = pCast<DoubleT>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat25(move(sym1), move(sym2), move(sym3), move(sym4), move(sym5)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	default:
		err = { "IntT::Process", "Syntax Error!" };
		return false;
	}
	return true;
}
bool Name::Process(Stack &stack, SymStack &symStack, Parser::Error &err) const
{
	switch (stack.top())
	{
	case 0:
	case 2:
		symStack.emplace(new Stat12());
		return Stat1::Process(stack, symStack, err) && Process(stack, symStack, err);
	case 1:
	case 7:
		stack.push(4);
		break;
	case 3:
		stack.push(8);
		break;
	case 5:
		stack.push(10);
		break;
	case 6:
	{
		stack.pop();
		stack.pop();
		pStat2 sym2 = pCast<Stat2>(move(symStack.top()));
		symStack.pop();
		pStat1 sym1 = pCast<Stat1>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat11(move(sym1), move(sym2)));
		return Stat1::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 9:
	case 13:
	case 15:
	case 20:
	case 24:
	case 25:
	case 26:
	case 27:
		stack.push(14);
		break;
	case 11:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pCloseB sym3 = pCast<CloseB>(move(symStack.top()));
		symStack.pop();
		pStat1 sym2 = pCast<Stat1>(move(symStack.top()));
		symStack.pop();
		pOpenB sym1 = pCast<OpenB>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat21(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 12:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pTerm sym3 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pName sym2 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		pIntT sym1 = pCast<IntT>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat22(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 19:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pTerm sym3 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pName sym2 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		pDoubleT sym1 = pCast<DoubleT>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat23(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 23:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pTerm sym4 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pExp sym3 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pAssign sym2 = pCast<Assign>(move(symStack.top()));
		symStack.pop();
		pName sym1 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat26(move(sym1), move(sym2), move(sym3), move(sym4)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 29:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pTerm sym5 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pExp sym4 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pAssign sym3 = pCast<Assign>(move(symStack.top()));
		symStack.pop();
		pName sym2 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		pIntT sym1 = pCast<IntT>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat24(move(sym1), move(sym2), move(sym3), move(sym4), move(sym5)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 35:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pTerm sym5 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pExp sym4 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pAssign sym3 = pCast<Assign>(move(symStack.top()));
		symStack.pop();
		pName sym2 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		pDoubleT sym1 = pCast<DoubleT>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat25(move(sym1), move(sym2), move(sym3), move(sym4), move(sym5)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	default:
		err = { "Name::Process", "Syntax Error!" };
		return false;
	}
	return true;
}
bool Term::Process(Stack &stack, SymStack &symStack, Parser::Error &err) const
{
	switch (stack.top())
	{
	case 8:
		stack.push(12);
		break;
	case 10:
		stack.push(19);
		break;
	case 14:
	{
		stack.pop();
		pName sym1 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp8(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 16:
	{
		stack.pop();
		pIntL sym1 = pCast<IntL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp6(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 17:
	{
		stack.pop();
		pDoubleL sym1 = pCast<DoubleL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp7(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 18:
		stack.push(23);
		break;
	case 21:
		stack.push(29);
		break;
	case 28:
		stack.push(35);
		break;
	case 30:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pCloseP sym3 = pCast<CloseP>(move(symStack.top()));
		symStack.pop();
		pExp sym2 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pOpenP sym1 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp5(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 31:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym3 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pAdd sym2 = pCast<Add>(move(symStack.top()));
		symStack.pop();
		pExp sym1 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp1(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 32:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym3 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pSub sym2 = pCast<Sub>(move(symStack.top()));
		symStack.pop();
		pExp sym1 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp2(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 33:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym3 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pMult sym2 = pCast<Mult>(move(symStack.top()));
		symStack.pop();
		pExp sym1 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp3(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 34:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym3 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pDiv sym2 = pCast<Div>(move(symStack.top()));
		symStack.pop();
		pExp sym1 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp4(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	default:
		err = { "Term::Process", "Syntax Error!" };
		return false;
	}
	return true;
}
bool DoubleT::Process(Stack &stack, SymStack &symStack, Parser::Error &err) const
{
	switch (stack.top())
	{
	case 0:
	case 2:
		symStack.emplace(new Stat12());
		return Stat1::Process(stack, symStack, err) && Process(stack, symStack, err);
	case 1:
	case 7:
		stack.push(5);
		break;
	case 6:
	{
		stack.pop();
		stack.pop();
		pStat2 sym2 = pCast<Stat2>(move(symStack.top()));
		symStack.pop();
		pStat1 sym1 = pCast<Stat1>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat11(move(sym1), move(sym2)));
		return Stat1::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 11:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pCloseB sym3 = pCast<CloseB>(move(symStack.top()));
		symStack.pop();
		pStat1 sym2 = pCast<Stat1>(move(symStack.top()));
		symStack.pop();
		pOpenB sym1 = pCast<OpenB>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat21(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 12:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pTerm sym3 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pName sym2 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		pIntT sym1 = pCast<IntT>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat22(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 19:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pTerm sym3 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pName sym2 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		pDoubleT sym1 = pCast<DoubleT>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat23(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 23:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pTerm sym4 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pExp sym3 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pAssign sym2 = pCast<Assign>(move(symStack.top()));
		symStack.pop();
		pName sym1 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat26(move(sym1), move(sym2), move(sym3), move(sym4)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 29:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pTerm sym5 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pExp sym4 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pAssign sym3 = pCast<Assign>(move(symStack.top()));
		symStack.pop();
		pName sym2 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		pIntT sym1 = pCast<IntT>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat24(move(sym1), move(sym2), move(sym3), move(sym4), move(sym5)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 35:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pTerm sym5 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pExp sym4 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pAssign sym3 = pCast<Assign>(move(symStack.top()));
		symStack.pop();
		pName sym2 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		pDoubleT sym1 = pCast<DoubleT>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat25(move(sym1), move(sym2), move(sym3), move(sym4), move(sym5)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	default:
		err = { "DoubleT::Process", "Syntax Error!" };
		return false;
	}
	return true;
}
bool Assign::Process(Stack &stack, SymStack &symStack, Parser::Error &err) const
{
	switch (stack.top())
	{
	case 4:
		stack.push(9);
		break;
	case 8:
		stack.push(13);
		break;
	case 10:
		stack.push(20);
		break;
	default:
		err = { "Assign::Process", "Syntax Error!" };
		return false;
	}
	return true;
}
bool Add::Process(Stack &stack, SymStack &symStack, Parser::Error &err) const
{
	switch (stack.top())
	{
	case 14:
	{
		stack.pop();
		pName sym1 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp8(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 16:
	{
		stack.pop();
		pIntL sym1 = pCast<IntL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp6(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 17:
	{
		stack.pop();
		pDoubleL sym1 = pCast<DoubleL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp7(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 18:
	case 21:
	case 22:
	case 28:
		stack.push(24);
		break;
	case 30:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pCloseP sym3 = pCast<CloseP>(move(symStack.top()));
		symStack.pop();
		pExp sym2 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pOpenP sym1 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp5(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 31:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym3 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pAdd sym2 = pCast<Add>(move(symStack.top()));
		symStack.pop();
		pExp sym1 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp1(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 32:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym3 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pSub sym2 = pCast<Sub>(move(symStack.top()));
		symStack.pop();
		pExp sym1 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp2(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 33:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym3 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pMult sym2 = pCast<Mult>(move(symStack.top()));
		symStack.pop();
		pExp sym1 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp3(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 34:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym3 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pDiv sym2 = pCast<Div>(move(symStack.top()));
		symStack.pop();
		pExp sym1 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp4(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	default:
		err = { "Add::Process", "Syntax Error!" };
		return false;
	}
	return true;
}
bool Sub::Process(Stack &stack, SymStack &symStack, Parser::Error &err) const
{
	switch (stack.top())
	{
	case 14:
	{
		stack.pop();
		pName sym1 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp8(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 16:
	{
		stack.pop();
		pIntL sym1 = pCast<IntL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp6(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 17:
	{
		stack.pop();
		pDoubleL sym1 = pCast<DoubleL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp7(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 18:
	case 21:
	case 22:
	case 28:
		stack.push(25);
		break;
	case 30:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pCloseP sym3 = pCast<CloseP>(move(symStack.top()));
		symStack.pop();
		pExp sym2 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pOpenP sym1 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp5(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 31:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym3 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pAdd sym2 = pCast<Add>(move(symStack.top()));
		symStack.pop();
		pExp sym1 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp1(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 32:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym3 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pSub sym2 = pCast<Sub>(move(symStack.top()));
		symStack.pop();
		pExp sym1 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp2(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 33:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym3 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pMult sym2 = pCast<Mult>(move(symStack.top()));
		symStack.pop();
		pExp sym1 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp3(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 34:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym3 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pDiv sym2 = pCast<Div>(move(symStack.top()));
		symStack.pop();
		pExp sym1 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp4(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	default:
		err = { "Sub::Process", "Syntax Error!" };
		return false;
	}
	return true;
}
bool Mult::Process(Stack &stack, SymStack &symStack, Parser::Error &err) const
{
	switch (stack.top())
	{
	case 14:
	{
		stack.pop();
		pName sym1 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp8(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 16:
	{
		stack.pop();
		pIntL sym1 = pCast<IntL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp6(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 17:
	{
		stack.pop();
		pDoubleL sym1 = pCast<DoubleL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp7(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 18:
	case 21:
	case 22:
	case 28:
	case 31:
	case 32:
		stack.push(26);
		break;
	case 30:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pCloseP sym3 = pCast<CloseP>(move(symStack.top()));
		symStack.pop();
		pExp sym2 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pOpenP sym1 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp5(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 33:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym3 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pMult sym2 = pCast<Mult>(move(symStack.top()));
		symStack.pop();
		pExp sym1 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp3(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 34:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym3 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pDiv sym2 = pCast<Div>(move(symStack.top()));
		symStack.pop();
		pExp sym1 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp4(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	default:
		err = { "Mult::Process", "Syntax Error!" };
		return false;
	}
	return true;
}
bool Div::Process(Stack &stack, SymStack &symStack, Parser::Error &err) const
{
	switch (stack.top())
	{
	case 14:
	{
		stack.pop();
		pName sym1 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp8(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 16:
	{
		stack.pop();
		pIntL sym1 = pCast<IntL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp6(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 17:
	{
		stack.pop();
		pDoubleL sym1 = pCast<DoubleL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp7(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 18:
	case 21:
	case 22:
	case 28:
	case 31:
	case 32:
		stack.push(27);
		break;
	case 30:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pCloseP sym3 = pCast<CloseP>(move(symStack.top()));
		symStack.pop();
		pExp sym2 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pOpenP sym1 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp5(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 33:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym3 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pMult sym2 = pCast<Mult>(move(symStack.top()));
		symStack.pop();
		pExp sym1 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp3(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 34:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym3 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pDiv sym2 = pCast<Div>(move(symStack.top()));
		symStack.pop();
		pExp sym1 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp4(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	default:
		err = { "Div::Process", "Syntax Error!" };
		return false;
	}
	return true;
}
bool OpenP::Process(Stack &stack, SymStack &symStack, Parser::Error &err) const
{
	switch (stack.top())
	{
	case 9:
	case 13:
	case 15:
	case 20:
	case 24:
	case 25:
	case 26:
	case 27:
		stack.push(15);
		break;
	default:
		err = { "OpenP::Process", "Syntax Error!" };
		return false;
	}
	return true;
}
bool CloseP::Process(Stack &stack, SymStack &symStack, Parser::Error &err) const
{
	switch (stack.top())
	{
	case 14:
	{
		stack.pop();
		pName sym1 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp8(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 16:
	{
		stack.pop();
		pIntL sym1 = pCast<IntL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp6(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 17:
	{
		stack.pop();
		pDoubleL sym1 = pCast<DoubleL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp7(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 22:
		stack.push(30);
		break;
	case 30:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pCloseP sym3 = pCast<CloseP>(move(symStack.top()));
		symStack.pop();
		pExp sym2 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pOpenP sym1 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp5(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 31:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym3 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pAdd sym2 = pCast<Add>(move(symStack.top()));
		symStack.pop();
		pExp sym1 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp1(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 32:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym3 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pSub sym2 = pCast<Sub>(move(symStack.top()));
		symStack.pop();
		pExp sym1 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp2(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 33:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym3 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pMult sym2 = pCast<Mult>(move(symStack.top()));
		symStack.pop();
		pExp sym1 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp3(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 34:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym3 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pDiv sym2 = pCast<Div>(move(symStack.top()));
		symStack.pop();
		pExp sym1 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp4(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	default:
		err = { "CloseP::Process", "Syntax Error!" };
		return false;
	}
	return true;
}
bool IntL::Process(Stack &stack, SymStack &symStack, Parser::Error &err) const
{
	switch (stack.top())
	{
	case 9:
	case 13:
	case 15:
	case 20:
	case 24:
	case 25:
	case 26:
	case 27:
		stack.push(16);
		break;
	default:
		err = { "IntL::Process", "Syntax Error!" };
		return false;
	}
	return true;
}
bool DoubleL::Process(Stack &stack, SymStack &symStack, Parser::Error &err) const
{
	switch (stack.top())
	{
	case 9:
	case 13:
	case 15:
	case 20:
	case 24:
	case 25:
	case 26:
	case 27:
		stack.push(17);
		break;
	default:
		err = { "DoubleL::Process", "Syntax Error!" };
		return false;
	}
	return true;
}
bool End::Process(Stack &stack, SymStack &symStack, Parser::Error &err)
{
	switch (stack.top())
	{
	case 0:
	case 2:
		symStack.emplace(new Stat12());
		return Stat1::Process(stack, symStack, err) && Process(stack, symStack, err);
	case 1:
		break;
	case 6:
	{
		stack.pop();
		stack.pop();
		pStat2 sym2 = pCast<Stat2>(move(symStack.top()));
		symStack.pop();
		pStat1 sym1 = pCast<Stat1>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat11(move(sym1), move(sym2)));
		return Stat1::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 11:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pCloseB sym3 = pCast<CloseB>(move(symStack.top()));
		symStack.pop();
		pStat1 sym2 = pCast<Stat1>(move(symStack.top()));
		symStack.pop();
		pOpenB sym1 = pCast<OpenB>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat21(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 12:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pTerm sym3 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pName sym2 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		pIntT sym1 = pCast<IntT>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat22(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 19:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pTerm sym3 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pName sym2 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		pDoubleT sym1 = pCast<DoubleT>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat23(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 23:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pTerm sym4 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pExp sym3 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pAssign sym2 = pCast<Assign>(move(symStack.top()));
		symStack.pop();
		pName sym1 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat26(move(sym1), move(sym2), move(sym3), move(sym4)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 29:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pTerm sym5 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pExp sym4 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pAssign sym3 = pCast<Assign>(move(symStack.top()));
		symStack.pop();
		pName sym2 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		pIntT sym1 = pCast<IntT>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat24(move(sym1), move(sym2), move(sym3), move(sym4), move(sym5)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 35:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pTerm sym5 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pExp sym4 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pAssign sym3 = pCast<Assign>(move(symStack.top()));
		symStack.pop();
		pName sym2 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		pDoubleT sym1 = pCast<DoubleT>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat25(move(sym1), move(sym2), move(sym3), move(sym4), move(sym5)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	default:
		err = { "End::Process", "Syntax Error!" };
		return false;
	}
	return true;
}

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
			return State_6(it, end);
		case 'n':
		case 't':
		case 'o':
		case 'u':
		case 'b':
		case 'l':
		case 'e':
		case 'a':
		case 'c':
		case 'f':
		case 'g':
		case 'h':
		case 'j':
		case 'k':
		case 'm':
		case 'p':
		case 'q':
		case 'r':
		case 's':
		case 'v':
		case 'w':
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
			return State_10(it, end);
		case 'd':
			return State_14(it, end);
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
			return ASSIGN;
		case '+':
			return ADD;
		case '-':
			return SUB;
		case '*':
			return MULT;
		case '/':
			return DIV;
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
			return State_4(it, end);
		case '.':
			return State_7(it, end);
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
		case 'n':
		case 't':
		case 'd':
		case 'o':
		case 'u':
		case 'b':
		case 'l':
		case 'e':
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
		case 'a':
		case 'c':
		case 'f':
		case 'g':
		case 'h':
		case 'j':
		case 'k':
		case 'm':
		case 'p':
		case 'q':
		case 'r':
		case 's':
		case 'v':
		case 'w':
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
			contValid = State_10(cont, end);
			break;
		}
		if (contValid != INVALID) {
			it = cont;
			return contValid;
		}
	}
	return INTT;
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
		case 'n':
		case 't':
		case 'd':
		case 'o':
		case 'u':
		case 'b':
		case 'l':
		case 'e':
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
		case 'a':
		case 'c':
		case 'f':
		case 'g':
		case 'h':
		case 'j':
		case 'k':
		case 'm':
		case 'p':
		case 'q':
		case 'r':
		case 's':
		case 'v':
		case 'w':
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
			contValid = State_10(cont, end);
			break;
		}
		if (contValid != INVALID) {
			it = cont;
			return contValid;
		}
	}
	return DOUBLET;
}
Lexer::Type Lexer::State_4(Iterator &it, Iterator end)
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
			contValid = State_4(cont, end);
			break;
		case '.':
			contValid = State_5(cont, end);
			break;
		}
		if (contValid != INVALID) {
			it = cont;
			return contValid;
		}
	}
	return INTL;
}
Lexer::Type Lexer::State_5(Iterator &it, Iterator end)
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
			contValid = State_5(cont, end);
			break;
		}
		if (contValid != INVALID) {
			it = cont;
			return contValid;
		}
	}
	return DOUBLEL;
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
		case 't':
		case 'd':
		case 'o':
		case 'u':
		case 'b':
		case 'l':
		case 'e':
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
		case 'a':
		case 'c':
		case 'f':
		case 'g':
		case 'h':
		case 'j':
		case 'k':
		case 'm':
		case 'p':
		case 'q':
		case 'r':
		case 's':
		case 'v':
		case 'w':
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
			contValid = State_10(cont, end);
			break;
		case 'n':
			contValid = State_8(cont, end);
			break;
		}
		if (contValid != INVALID) {
			it = cont;
			return contValid;
		}
	}
	return NAME;
}
Lexer::Type Lexer::State_7(Iterator &it, Iterator end)
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
			return State_5(it, end);
		}
	}
	return INVALID;
}
Lexer::Type Lexer::State_8(Iterator &it, Iterator end)
{
	if (it != end)
	{
		Iterator cont = it;
		Type contValid = INVALID;
		switch (*cont++)
		{
		case 'i':
		case 'n':
		case 'd':
		case 'o':
		case 'u':
		case 'b':
		case 'l':
		case 'e':
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
		case 'a':
		case 'c':
		case 'f':
		case 'g':
		case 'h':
		case 'j':
		case 'k':
		case 'm':
		case 'p':
		case 'q':
		case 'r':
		case 's':
		case 'v':
		case 'w':
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
			contValid = State_10(cont, end);
			break;
		case 't':
			contValid = State_2(cont, end);
			break;
		}
		if (contValid != INVALID) {
			it = cont;
			return contValid;
		}
	}
	return NAME;
}
Lexer::Type Lexer::State_9(Iterator &it, Iterator end)
{
	if (it != end)
	{
		Iterator cont = it;
		Type contValid = INVALID;
		switch (*cont++)
		{
		case 'i':
		case 'n':
		case 't':
		case 'd':
		case 'o':
		case 'u':
		case 'b':
		case 'l':
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
		case 'a':
		case 'c':
		case 'f':
		case 'g':
		case 'h':
		case 'j':
		case 'k':
		case 'm':
		case 'p':
		case 'q':
		case 'r':
		case 's':
		case 'v':
		case 'w':
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
			contValid = State_10(cont, end);
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
Lexer::Type Lexer::State_10(Iterator &it, Iterator end)
{
	if (it != end)
	{
		Iterator cont = it;
		Type contValid = INVALID;
		switch (*cont++)
		{
		case 'i':
		case 'n':
		case 't':
		case 'd':
		case 'o':
		case 'u':
		case 'b':
		case 'l':
		case 'e':
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
		case 'a':
		case 'c':
		case 'f':
		case 'g':
		case 'h':
		case 'j':
		case 'k':
		case 'm':
		case 'p':
		case 'q':
		case 'r':
		case 's':
		case 'v':
		case 'w':
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
			contValid = State_10(cont, end);
			break;
		}
		if (contValid != INVALID) {
			it = cont;
			return contValid;
		}
	}
	return NAME;
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
		case 'n':
		case 't':
		case 'd':
		case 'o':
		case 'u':
		case 'b':
		case 'e':
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
		case 'a':
		case 'c':
		case 'f':
		case 'g':
		case 'h':
		case 'j':
		case 'k':
		case 'm':
		case 'p':
		case 'q':
		case 'r':
		case 's':
		case 'v':
		case 'w':
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
			contValid = State_10(cont, end);
			break;
		case 'l':
			contValid = State_9(cont, end);
			break;
		}
		if (contValid != INVALID) {
			it = cont;
			return contValid;
		}
	}
	return NAME;
}
Lexer::Type Lexer::State_12(Iterator &it, Iterator end)
{
	if (it != end)
	{
		Iterator cont = it;
		Type contValid = INVALID;
		switch (*cont++)
		{
		case 'i':
		case 'n':
		case 't':
		case 'd':
		case 'o':
		case 'u':
		case 'l':
		case 'e':
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
		case 'a':
		case 'c':
		case 'f':
		case 'g':
		case 'h':
		case 'j':
		case 'k':
		case 'm':
		case 'p':
		case 'q':
		case 'r':
		case 's':
		case 'v':
		case 'w':
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
			contValid = State_10(cont, end);
			break;
		case 'b':
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
Lexer::Type Lexer::State_13(Iterator &it, Iterator end)
{
	if (it != end)
	{
		Iterator cont = it;
		Type contValid = INVALID;
		switch (*cont++)
		{
		case 'i':
		case 'n':
		case 't':
		case 'd':
		case 'o':
		case 'b':
		case 'l':
		case 'e':
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
		case 'a':
		case 'c':
		case 'f':
		case 'g':
		case 'h':
		case 'j':
		case 'k':
		case 'm':
		case 'p':
		case 'q':
		case 'r':
		case 's':
		case 'v':
		case 'w':
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
			contValid = State_10(cont, end);
			break;
		case 'u':
			contValid = State_12(cont, end);
			break;
		}
		if (contValid != INVALID) {
			it = cont;
			return contValid;
		}
	}
	return NAME;
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
		case 'n':
		case 't':
		case 'd':
		case 'u':
		case 'b':
		case 'l':
		case 'e':
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
		case 'a':
		case 'c':
		case 'f':
		case 'g':
		case 'h':
		case 'j':
		case 'k':
		case 'm':
		case 'p':
		case 'q':
		case 'r':
		case 's':
		case 'v':
		case 'w':
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
			contValid = State_10(cont, end);
			break;
		case 'o':
			contValid = State_13(cont, end);
			break;
		}
		if (contValid != INVALID) {
			it = cont;
			return contValid;
		}
	}
	return NAME;
}