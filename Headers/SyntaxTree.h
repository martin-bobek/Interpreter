#ifndef SYNTAXTREE_H_
#define SYNTAXTREE_H_

#include <memory>
#include <vector>
#include <string>
#include <stack>
#include <iostream>

using std::move;

class CompilerError;
class Symbol;
class Stat1;
class Stat2;
class AssignExp;
class Exp;
class Terminal;
class OpenB;
class CloseB;
class IntT;
class Name;
class Term;
class DoubleT;
class Assign;
class BoolT;
class Add;
class Sub;
class Mult;
class Div;
class OpenP;
class CloseP;
class IntL;
class DoubleL;
class Equal;
class NotEqual;
class Greater;
class Less;
class GreaterEqual;
class LessEqual;
class BoolL;

typedef std::unique_ptr<CompilerError> pCompilerError;
typedef std::unique_ptr<Symbol> pSymbol;
typedef std::unique_ptr<Stat1> pStat1;
typedef std::unique_ptr<Stat2> pStat2;
typedef std::unique_ptr<AssignExp> pAssignExp;
typedef std::unique_ptr<Exp> pExp;
typedef std::unique_ptr<Terminal> pTerminal;
typedef std::unique_ptr<OpenB> pOpenB;
typedef std::unique_ptr<CloseB> pCloseB;
typedef std::unique_ptr<IntT> pIntT;
typedef std::unique_ptr<Name> pName;
typedef std::unique_ptr<Term> pTerm;
typedef std::unique_ptr<DoubleT> pDoubleT;
typedef std::unique_ptr<Assign> pAssign;
typedef std::unique_ptr<BoolT> pBoolT;
typedef std::unique_ptr<Add> pAdd;
typedef std::unique_ptr<Sub> pSub;
typedef std::unique_ptr<Mult> pMult;
typedef std::unique_ptr<Div> pDiv;
typedef std::unique_ptr<OpenP> pOpenP;
typedef std::unique_ptr<CloseP> pCloseP;
typedef std::unique_ptr<IntL> pIntL;
typedef std::unique_ptr<DoubleL> pDoubleL;
typedef std::unique_ptr<Equal> pEqual;
typedef std::unique_ptr<NotEqual> pNotEqual;
typedef std::unique_ptr<Greater> pGreater;
typedef std::unique_ptr<Less> pLess;
typedef std::unique_ptr<GreaterEqual> pGreaterEqual;
typedef std::unique_ptr<LessEqual> pLessEqual;
typedef std::unique_ptr<BoolL> pBoolL;
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
	Error GetErrorReport() { return std::move(err); }
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
	enum Type { INVALID, BOOLT, INTT, DOUBLET, TERM, OPENP, CLOSEP, OPENB, CLOSEB, ASSIGN, ADD, SUB, MULT, DIV, EQUAL, NOTEQUAL, GREATER, LESS, GREATEREQUAL, LESSEQUAL, BOOLL, INTL, DOUBLEL, NAME };

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
	static Type State_15(Iterator &it, Iterator end);
	static Type State_16(Iterator &it, Iterator end);
	static Type State_17(Iterator &it, Iterator end);
	static Type State_18(Iterator &it, Iterator end);
	static Type State_19(Iterator &it, Iterator end);
	static Type State_20(Iterator &it, Iterator end);
	static Type State_21(Iterator &it, Iterator end);
	static Type State_22(Iterator &it, Iterator end);
	static Type State_23(Iterator &it, Iterator end);
	static Type State_24(Iterator &it, Iterator end);
	static Type State_25(Iterator &it, Iterator end);
	static Type State_26(Iterator &it, Iterator end);
	static Type State_27(Iterator &it, Iterator end);
	static Type State_28(Iterator &it, Iterator end);
	static Type State_29(Iterator &it, Iterator end);

	std::istream &in;
	std::vector<pTerminal> tokens;
	Error err;
};
class Value
{
public:
	template<typename T> static Value Create(T value);
	static Value Create() { return 0; }
	template<typename T> static std::tuple<pCompilerError, Value> Cast(Value value);
	void Assign(Value value);
	std::tuple<pCompilerError, Value> operator+(Value rhs) const;
	std::tuple<pCompilerError, Value> operator-(Value rhs) const;
	std::tuple<pCompilerError, Value> operator*(Value rhs) const;
	std::tuple<pCompilerError, Value> operator/(Value rhs) const;
	std::tuple<pCompilerError, Value> operator-() const;
	std::tuple<pCompilerError, Value> operator==(Value rhs) const;
	std::tuple<pCompilerError, Value> operator!=(Value rhs) const;
	std::tuple<pCompilerError, Value> operator<(Value rhs) const;
	std::tuple<pCompilerError, Value> operator>(Value rhs) const;
	std::tuple<pCompilerError, Value> operator<=(Value rhs) const;
	std::tuple<pCompilerError, Value> operator>=(Value rhs) const;
	void PrintType(std::ostream &out) const;
	void PrintValue(std::ostream &out) const;
private:
	enum Type { INT, DOUBLE, BOOL };
	Value(int value) : type(INT), vInt(value) {}
	Value(double value) : type(DOUBLE), vDouble(value) {}
	Value(bool value) : type(BOOL), vBool(value) {}
	const Type type;
	union {
		double vDouble;
		int vInt;
		bool vBool;
	};
};
class SymTable
{
public:
	void Print(std::ostream &out) const;
	void EnterScope();
	void ExitScope(); // function will fail if a scope has not previously been entered
	template<typename T> pCompilerError Declare(const std::string &name);
	template<typename T> pCompilerError Initialize(const std::string &name, Value value);
	pCompilerError Assign(const std::string &name, Value value);
	std::tuple<pCompilerError, Value> AssignChain(const std::string &name, Value value);
	std::tuple<pCompilerError, Value> Get(const std::string &name) const;
private:
	bool inCurrentScope(const std::string &name) const;
	struct Variable
	{
		Variable(const std::string &name = std::string(), Value value = Value::Create()) : name(name), value(value) {}
		bool ScopeMarker() const { return name.empty(); }
		std::string name;
		Value value;
	};
	std::vector<Variable> stack;
};
class CompilerError
{
public:
	static constexpr CompilerError *NoError = nullptr;
	static pCompilerError New(std::string &&location, std::string &&message) { return pCompilerError(new CompilerError(move(location), move(message))); }
	CompilerError() = delete;
	const std::string &Location() const { return location; }
	const std::string &Message() const { return message; }
private:
	CompilerError(std::string &&location, std::string &&message) : location(location), message(message) {}
	std::string location;
	std::string message;
};

class Symbol
{
public:
	virtual ~Symbol() = 0;
};
inline Symbol::~Symbol() = default;
class Stat1 : public Symbol
{
public:
	virtual ~Stat1() = 0;
	static bool Process(Stack &stack, SymStack &symStack, Parser::Error &err);
	virtual pCompilerError Evaluate(SymTable &syms) const = 0;
};
inline Stat1::~Stat1() = default;
class Stat11 : public Stat1
{
public:
	Stat11(pStat1 &&sym1, pStat2 &&sym2) : symbol_1(move(sym1)), symbol_2(move(sym2)) {}
	pCompilerError Evaluate(SymTable &syms) const;
private:
	const pStat1 symbol_1;
	const pStat2 symbol_2;
};
class Stat12 : public Stat1
{
public:
	Stat12() = default;
	pCompilerError Evaluate(SymTable &syms) const;
};
class Stat2 : public Symbol
{
public:
	virtual ~Stat2() = 0;
	static bool Process(Stack &stack, SymStack &symStack, Parser::Error &err);
	virtual pCompilerError Evaluate(SymTable &syms) const = 0;
};
inline Stat2::~Stat2() = default;
class Stat21 : public Stat2
{
public:
	Stat21(pOpenB &&sym1, pStat1 &&sym2, pCloseB &&sym3) : symbol_1(move(sym1)), symbol_2(move(sym2)), symbol_3(move(sym3)) {}
	pCompilerError Evaluate(SymTable &syms) const;
private:
	const pOpenB symbol_1;
	const pStat1 symbol_2;
	const pCloseB symbol_3;
};
class Stat22 : public Stat2
{
public:
	Stat22(pIntT &&sym1, pName &&sym2, pTerm &&sym3) : symbol_1(move(sym1)), symbol_2(move(sym2)), symbol_3(move(sym3)) {}
	pCompilerError Evaluate(SymTable &syms) const;
private:
	const pIntT symbol_1;
	const pName symbol_2;
	const pTerm symbol_3;
};
class Stat23 : public Stat2
{
public:
	Stat23(pDoubleT &&sym1, pName &&sym2, pTerm &&sym3) : symbol_1(move(sym1)), symbol_2(move(sym2)), symbol_3(move(sym3)) {}
	pCompilerError Evaluate(SymTable &syms) const;
private:
	const pDoubleT symbol_1;
	const pName symbol_2;
	const pTerm symbol_3;
};
class Stat24 : public Stat2
{
public:
	Stat24(pIntT &&sym1, pName &&sym2, pAssign &&sym3, pAssignExp &&sym4, pTerm &&sym5) : symbol_1(move(sym1)), symbol_2(move(sym2)), symbol_3(move(sym3)), symbol_4(move(sym4)), symbol_5(move(sym5)) {}
	pCompilerError Evaluate(SymTable &syms) const;
private:
	const pIntT symbol_1;
	const pName symbol_2;
	const pAssign symbol_3;
	const pAssignExp symbol_4;
	const pTerm symbol_5;
};
class Stat25 : public Stat2
{
public:
	Stat25(pDoubleT &&sym1, pName &&sym2, pAssign &&sym3, pAssignExp &&sym4, pTerm &&sym5) : symbol_1(move(sym1)), symbol_2(move(sym2)), symbol_3(move(sym3)), symbol_4(move(sym4)), symbol_5(move(sym5)) {}
	pCompilerError Evaluate(SymTable &syms) const;
private:
	const pDoubleT symbol_1;
	const pName symbol_2;
	const pAssign symbol_3;
	const pAssignExp symbol_4;
	const pTerm symbol_5;
};
class Stat26 : public Stat2
{
public:
	Stat26(pName &&sym1, pAssign &&sym2, pAssignExp &&sym3, pTerm &&sym4) : symbol_1(move(sym1)), symbol_2(move(sym2)), symbol_3(move(sym3)), symbol_4(move(sym4)) {}
	pCompilerError Evaluate(SymTable &syms) const;
private:
	const pName symbol_1;
	const pAssign symbol_2;
	const pAssignExp symbol_3;
	const pTerm symbol_4;
};
class Stat27 : public Stat2
{
public:
	Stat27(pBoolT &&sym1, pName &&sym2, pTerm &&sym3) : symbol_1(move(sym1)), symbol_2(move(sym2)), symbol_3(move(sym3)) {}
	pCompilerError Evaluate(SymTable &syms) const;
private:
	const pBoolT symbol_1;
	const pName symbol_2;
	const pTerm symbol_3;
};
class Stat28 : public Stat2
{
public:
	Stat28(pBoolT &&sym1, pName &&sym2, pAssign &&sym3, pAssignExp &&sym4, pTerm &&sym5) : symbol_1(move(sym1)), symbol_2(move(sym2)), symbol_3(move(sym3)), symbol_4(move(sym4)), symbol_5(move(sym5)) {}
	pCompilerError Evaluate(SymTable &syms) const;
private:
	const pBoolT symbol_1;
	const pName symbol_2;
	const pAssign symbol_3;
	const pAssignExp symbol_4;
	const pTerm symbol_5;
};
class AssignExp : public Symbol
{
public:
	virtual ~AssignExp() = 0;
	static bool Process(Stack &stack, SymStack &symStack, Parser::Error &err);
	virtual std::tuple<pCompilerError, Value> Evaluate(SymTable &syms) const = 0;
};
inline AssignExp::~AssignExp() = default;
class AssignExp1 : public AssignExp
{
public:
	AssignExp1(pName &&sym1, pAssign &&sym2, pAssignExp &&sym3) : symbol_1(move(sym1)), symbol_2(move(sym2)), symbol_3(move(sym3)) {}
	std::tuple<pCompilerError, Value> Evaluate(SymTable &syms) const;
private:
	const pName symbol_1;
	const pAssign symbol_2;
	const pAssignExp symbol_3;
};
class AssignExp2 : public AssignExp
{
public:
	AssignExp2(pExp &&sym1) : symbol_1(move(sym1)) {}
	std::tuple<pCompilerError, Value> Evaluate(SymTable &syms) const;
private:
	const pExp symbol_1;
};
class Exp : public Symbol
{
public:
	virtual ~Exp() = 0;
	static bool Process(Stack &stack, SymStack &symStack, Parser::Error &err);
	virtual std::tuple<pCompilerError, Value> Evaluate(SymTable &syms) const = 0;
};
inline Exp::~Exp() = default;
class Exp1 : public Exp
{
public:
	Exp1(pExp &&sym1, pAdd &&sym2, pExp &&sym3) : symbol_1(move(sym1)), symbol_2(move(sym2)), symbol_3(move(sym3)) {}
	std::tuple<pCompilerError, Value> Evaluate(SymTable &syms) const;
private:
	const pExp symbol_1;
	const pAdd symbol_2;
	const pExp symbol_3;
};
class Exp2 : public Exp
{
public:
	Exp2(pExp &&sym1, pSub &&sym2, pExp &&sym3) : symbol_1(move(sym1)), symbol_2(move(sym2)), symbol_3(move(sym3)) {}
	std::tuple<pCompilerError, Value> Evaluate(SymTable &syms) const;
private:
	const pExp symbol_1;
	const pSub symbol_2;
	const pExp symbol_3;
};
class Exp3 : public Exp
{
public:
	Exp3(pExp &&sym1, pMult &&sym2, pExp &&sym3) : symbol_1(move(sym1)), symbol_2(move(sym2)), symbol_3(move(sym3)) {}
	std::tuple<pCompilerError, Value> Evaluate(SymTable &syms) const;
private:
	const pExp symbol_1;
	const pMult symbol_2;
	const pExp symbol_3;
};
class Exp4 : public Exp
{
public:
	Exp4(pExp &&sym1, pDiv &&sym2, pExp &&sym3) : symbol_1(move(sym1)), symbol_2(move(sym2)), symbol_3(move(sym3)) {}
	std::tuple<pCompilerError, Value> Evaluate(SymTable &syms) const;
private:
	const pExp symbol_1;
	const pDiv symbol_2;
	const pExp symbol_3;
};
class Exp5 : public Exp
{
public:
	Exp5(pOpenP &&sym1, pExp &&sym2, pCloseP &&sym3) : symbol_1(move(sym1)), symbol_2(move(sym2)), symbol_3(move(sym3)) {}
	std::tuple<pCompilerError, Value> Evaluate(SymTable &syms) const;
private:
	const pOpenP symbol_1;
	const pExp symbol_2;
	const pCloseP symbol_3;
};
class Exp6 : public Exp
{
public:
	Exp6(pIntL &&sym1) : symbol_1(move(sym1)) {}
	std::tuple<pCompilerError, Value> Evaluate(SymTable &syms) const;
private:
	const pIntL symbol_1;
};
class Exp7 : public Exp
{
public:
	Exp7(pDoubleL &&sym1) : symbol_1(move(sym1)) {}
	std::tuple<pCompilerError, Value> Evaluate(SymTable &syms) const;
private:
	const pDoubleL symbol_1;
};
class Exp8 : public Exp
{
public:
	Exp8(pName &&sym1) : symbol_1(move(sym1)) {}
	std::tuple<pCompilerError, Value> Evaluate(SymTable &syms) const;
private:
	const pName symbol_1;
};
class Exp9 : public Exp
{
public:
	Exp9(pSub &&sym1, pExp &&sym2) : symbol_1(move(sym1)), symbol_2(move(sym2)) {}
	std::tuple<pCompilerError, Value> Evaluate(SymTable &syms) const;
private:
	const pSub symbol_1;
	const pExp symbol_2;
};
class Exp10 : public Exp
{
public:
	Exp10(pOpenP &&sym1, pIntT &&sym2, pCloseP &&sym3, pExp &&sym4) : symbol_1(move(sym1)), symbol_2(move(sym2)), symbol_3(move(sym3)), symbol_4(move(sym4)) {}
	std::tuple<pCompilerError, Value> Evaluate(SymTable &syms) const;
private:
	const pOpenP symbol_1;
	const pIntT symbol_2;
	const pCloseP symbol_3;
	const pExp symbol_4;
};
class Exp11 : public Exp
{
public:
	Exp11(pOpenP &&sym1, pDoubleT &&sym2, pCloseP &&sym3, pExp &&sym4) : symbol_1(move(sym1)), symbol_2(move(sym2)), symbol_3(move(sym3)), symbol_4(move(sym4)) {}
	std::tuple<pCompilerError, Value> Evaluate(SymTable &syms) const;
private:
	const pOpenP symbol_1;
	const pDoubleT symbol_2;
	const pCloseP symbol_3;
	const pExp symbol_4;
};
class Exp12 : public Exp
{
public:
	Exp12(pOpenP &&sym1, pBoolT &&sym2, pCloseP &&sym3, pExp &&sym4) : symbol_1(move(sym1)), symbol_2(move(sym2)), symbol_3(move(sym3)), symbol_4(move(sym4)) {}
	std::tuple<pCompilerError, Value> Evaluate(SymTable &syms) const;
private:
	const pOpenP symbol_1;
	const pBoolT symbol_2;
	const pCloseP symbol_3;
	const pExp symbol_4;
};
class Exp13 : public Exp
{
public:
	Exp13(pExp &&sym1, pEqual &&sym2, pExp &&sym3) : symbol_1(move(sym1)), symbol_2(move(sym2)), symbol_3(move(sym3)) {}
	std::tuple<pCompilerError, Value> Evaluate(SymTable &syms) const;
private:
	const pExp symbol_1;
	const pEqual symbol_2;
	const pExp symbol_3;
};
class Exp14 : public Exp
{
public:
	Exp14(pExp &&sym1, pNotEqual &&sym2, pExp &&sym3) : symbol_1(move(sym1)), symbol_2(move(sym2)), symbol_3(move(sym3)) {}
	std::tuple<pCompilerError, Value> Evaluate(SymTable &syms) const;
private:
	const pExp symbol_1;
	const pNotEqual symbol_2;
	const pExp symbol_3;
};
class Exp15 : public Exp
{
public:
	Exp15(pExp &&sym1, pGreater &&sym2, pExp &&sym3) : symbol_1(move(sym1)), symbol_2(move(sym2)), symbol_3(move(sym3)) {}
	std::tuple<pCompilerError, Value> Evaluate(SymTable &syms) const;
private:
	const pExp symbol_1;
	const pGreater symbol_2;
	const pExp symbol_3;
};
class Exp16 : public Exp
{
public:
	Exp16(pExp &&sym1, pLess &&sym2, pExp &&sym3) : symbol_1(move(sym1)), symbol_2(move(sym2)), symbol_3(move(sym3)) {}
	std::tuple<pCompilerError, Value> Evaluate(SymTable &syms) const;
private:
	const pExp symbol_1;
	const pLess symbol_2;
	const pExp symbol_3;
};
class Exp17 : public Exp
{
public:
	Exp17(pExp &&sym1, pGreaterEqual &&sym2, pExp &&sym3) : symbol_1(move(sym1)), symbol_2(move(sym2)), symbol_3(move(sym3)) {}
	std::tuple<pCompilerError, Value> Evaluate(SymTable &syms) const;
private:
	const pExp symbol_1;
	const pGreaterEqual symbol_2;
	const pExp symbol_3;
};
class Exp18 : public Exp
{
public:
	Exp18(pExp &&sym1, pLessEqual &&sym2, pExp &&sym3) : symbol_1(move(sym1)), symbol_2(move(sym2)), symbol_3(move(sym3)) {}
	std::tuple<pCompilerError, Value> Evaluate(SymTable &syms) const;
private:
	const pExp symbol_1;
	const pLessEqual symbol_2;
	const pExp symbol_3;
};
class Exp19 : public Exp
{
public:
	Exp19(pBoolL &&sym1) : symbol_1(move(sym1)) {}
	std::tuple<pCompilerError, Value> Evaluate(SymTable &syms) const;
private:
	const pBoolL symbol_1;
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
inline Terminal::~Terminal() = default;
class BoolT : public Terminal
{
public:
	BoolT(std::string &&value) : value(move(value)) {}
	bool Process(Stack &stack, SymStack &symStack, Parser::Error &err) const;
private:
	std::ostream &print(std::ostream &os) const { return os << "BOOLT[" << value << ']'; }
	const std::string value;
};
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
class Equal : public Terminal
{
public:
	Equal(std::string &&value) : value(move(value)) {}
	bool Process(Stack &stack, SymStack &symStack, Parser::Error &err) const;
private:
	std::ostream &print(std::ostream &os) const { return os << "EQUAL[" << value << ']'; }
	const std::string value;
};
class NotEqual : public Terminal
{
public:
	NotEqual(std::string &&value) : value(move(value)) {}
	bool Process(Stack &stack, SymStack &symStack, Parser::Error &err) const;
private:
	std::ostream &print(std::ostream &os) const { return os << "NOTEQUAL[" << value << ']'; }
	const std::string value;
};
class Greater : public Terminal
{
public:
	Greater(std::string &&value) : value(move(value)) {}
	bool Process(Stack &stack, SymStack &symStack, Parser::Error &err) const;
private:
	std::ostream &print(std::ostream &os) const { return os << "GREATER[" << value << ']'; }
	const std::string value;
};
class Less : public Terminal
{
public:
	Less(std::string &&value) : value(move(value)) {}
	bool Process(Stack &stack, SymStack &symStack, Parser::Error &err) const;
private:
	std::ostream &print(std::ostream &os) const { return os << "LESS[" << value << ']'; }
	const std::string value;
};
class GreaterEqual : public Terminal
{
public:
	GreaterEqual(std::string &&value) : value(move(value)) {}
	bool Process(Stack &stack, SymStack &symStack, Parser::Error &err) const;
private:
	std::ostream &print(std::ostream &os) const { return os << "GREATEREQUAL[" << value << ']'; }
	const std::string value;
};
class LessEqual : public Terminal
{
public:
	LessEqual(std::string &&value) : value(move(value)) {}
	bool Process(Stack &stack, SymStack &symStack, Parser::Error &err) const;
private:
	std::ostream &print(std::ostream &os) const { return os << "LESSEQUAL[" << value << ']'; }
	const std::string value;
};
class BoolL : public Terminal
{
public:
	BoolL(std::string &&value) : value(move(value)) {}
	bool Process(Stack &stack, SymStack &symStack, Parser::Error &err) const;
	bool Value() const { return value[0] == 't'; };
private:
	std::ostream &print(std::ostream &os) const { return os << "BOOLL[" << value << ']'; }
	const std::string value;
};
class IntL : public Terminal
{
public:
	IntL(std::string &&value) : value(move(value)) {}
	bool Process(Stack &stack, SymStack &symStack, Parser::Error &err) const;
	int Value() const { return std::stoi(value); }
private:
	std::ostream &print(std::ostream &os) const { return os << "INTL[" << value << ']'; }
	const std::string value;
};
class DoubleL : public Terminal
{
public:
	DoubleL(std::string &&value) : value(move(value)) {}
	bool Process(Stack &stack, SymStack &symStack, Parser::Error &err) const;
	double Value() const { return std::stod(value); }
private:
	std::ostream &print(std::ostream &os) const { return os << "DOUBLEL[" << value << ']'; }
	const std::string value;
};
class Name : public Terminal
{
public:
	Name(std::string &&value) : value(move(value)) {}
	bool Process(Stack &stack, SymStack &symStack, Parser::Error &err) const;
	const std::string &Value() const { return value; }
private:
	std::ostream &print(std::ostream &os) const { return os << "NAME[" << value << ']'; }
	const std::string value;
};
namespace End
{
	bool Process(Stack &stack, SymStack &symStack, Parser::Error &err);
}

#endif