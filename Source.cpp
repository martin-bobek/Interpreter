#include <iostream>
#include <istream>
#include <memory>
#include <stack>
#include <string>
#include <vector>
#include <sstream>
#include <type_traits>
#include <tuple>

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
Symbol::~Symbol() = default;
class Stat1 : public Symbol
{
public:
	virtual ~Stat1() = 0;
	static bool Process(Stack &stack, SymStack &symStack, Parser::Error &err);
	virtual pCompilerError Evaluate(SymTable &syms) const = 0;
};
Stat1::~Stat1() = default;
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
Stat2::~Stat2() = default;
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
AssignExp::~AssignExp() = default;
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
Exp::~Exp() = default;
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
Terminal::~Terminal() = default;
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

int main()
{
	while (true)
	{
		std::cout << "Enter input:" << std::endl;
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
		SymTable syms;
		pCompilerError error = tree->Evaluate(syms);
		if (error)
		{
			std::cout << "Error in " << error->Location() << ": " << error->Message() << std::endl;
			continue;
		}
		std::cout << "Input accepted!" << std::endl;
		syms.Print(std::cout);
		std::cout << std::endl;
	}
}

pCompilerError Stat11::Evaluate(SymTable &syms) const
{
	pCompilerError error = symbol_1->Evaluate(syms);
	if (error)
		return error;
	return symbol_2->Evaluate(syms);
}
pCompilerError Stat12::Evaluate(SymTable &syms) const
{
	return pCompilerError(CompilerError::NoError);
}
pCompilerError Stat21::Evaluate(SymTable &syms) const
{
	syms.EnterScope();
	pCompilerError error = symbol_2->Evaluate(syms);
	syms.ExitScope();
	return error;
}
pCompilerError Stat22::Evaluate(SymTable &syms) const
{
	return syms.Declare<int>(symbol_2->Value());
}
pCompilerError Stat23::Evaluate(SymTable &syms) const
{
	return syms.Declare<double>(symbol_2->Value());
}
pCompilerError Stat24::Evaluate(SymTable &syms) const
{
	auto[error, value] = symbol_4->Evaluate(syms);
	if (error)
		return move(error);
	return syms.Initialize<int>(symbol_2->Value(), value);
}
pCompilerError Stat25::Evaluate(SymTable &syms) const
{
	auto[error, value] = symbol_4->Evaluate(syms);
	if (error)
		return move(error);
	return syms.Initialize<double>(symbol_2->Value(), value);
}
pCompilerError Stat26::Evaluate(SymTable &syms) const
{
	auto[error, value] = symbol_3->Evaluate(syms);
	if (error)
		return move(error);
	return syms.Assign(symbol_1->Value(), value);
}
pCompilerError Stat27::Evaluate(SymTable &syms) const
{
	return syms.Declare<bool>(symbol_2->Value());
}
pCompilerError Stat28::Evaluate(SymTable &syms) const
{
	auto[error, value] = symbol_4->Evaluate(syms);
	if (error)
		return move(error);
	return syms.Initialize<bool>(symbol_2->Value(), value);
}
std::tuple<pCompilerError, Value> AssignExp1::Evaluate(SymTable &syms) const
{
	auto[error, value] = symbol_3->Evaluate(syms);
	if (error)
		return { move(error), value };
	return syms.AssignChain(symbol_1->Value(), value);
}
std::tuple<pCompilerError, Value> AssignExp2::Evaluate(SymTable &syms) const
{
	return symbol_1->Evaluate(syms);
}
std::tuple<pCompilerError, Value> Exp1::Evaluate(SymTable &syms) const
{
	auto[errorL, valueL] = symbol_1->Evaluate(syms);
	if (errorL)
		return { move(errorL), valueL };
	auto[errorR, valueR] = symbol_3->Evaluate(syms);
	if (errorR)
		return { move(errorR), valueL };
	return valueL + valueR;

}
std::tuple<pCompilerError, Value> Exp2::Evaluate(SymTable &syms) const
{
	auto[errorL, valueL] = symbol_1->Evaluate(syms);
	if (errorL)
		return { move(errorL), valueL };
	auto[errorR, valueR] = symbol_3->Evaluate(syms);
	if (errorR)
		return { move(errorR), valueL };
	return valueL - valueR;
}
std::tuple<pCompilerError, Value> Exp3::Evaluate(SymTable &syms) const
{
	auto[errorL, valueL] = symbol_1->Evaluate(syms);
	if (errorL)
		return { move(errorL), valueL };
	auto[errorR, valueR] = symbol_3->Evaluate(syms);
	if (errorR)
		return { move(errorR), valueL };
	return valueL * valueR;
}
std::tuple<pCompilerError, Value> Exp4::Evaluate(SymTable &syms) const
{
	auto[errorL, valueL] = symbol_1->Evaluate(syms);
	if (errorL)
		return { move(errorL), valueL };
	auto[errorR, valueR] = symbol_3->Evaluate(syms);
	if (errorR)
		return { move(errorR), valueL };
	return valueL / valueR;
}
std::tuple<pCompilerError, Value> Exp5::Evaluate(SymTable &syms) const
{
	return symbol_2->Evaluate(syms);
}
std::tuple<pCompilerError, Value> Exp6::Evaluate(SymTable &syms) const
{
	return { pCompilerError(CompilerError::NoError), Value::Create(symbol_1->Value()) };
}
std::tuple<pCompilerError, Value> Exp7::Evaluate(SymTable &syms) const
{
	return { pCompilerError(CompilerError::NoError), Value::Create(symbol_1->Value()) };
}
std::tuple<pCompilerError, Value> Exp8::Evaluate(SymTable &syms) const
{
	return syms.Get(symbol_1->Value());
}
std::tuple<pCompilerError, Value> Exp9::Evaluate(SymTable &syms) const
{
	auto[error, value] = symbol_2->Evaluate(syms);
	if (error)
		return { move(error), value };
	return -value;
}
std::tuple<pCompilerError, Value> Exp10::Evaluate(SymTable &syms) const
{
	auto[error, value] = symbol_4->Evaluate(syms);
	if (error)
		return { move(error), value };
	return Value::Cast<int>(value);
}
std::tuple<pCompilerError, Value> Exp11::Evaluate(SymTable &syms) const
{
	auto[error, value] = symbol_4->Evaluate(syms);
	if (error)
		return { move(error), value };
	return Value::Cast<double>(value);
}
std::tuple<pCompilerError, Value> Exp12::Evaluate(SymTable &syms) const
{
	auto[error, value] = symbol_4->Evaluate(syms);
	if (error)
		return { move(error), value };
	return Value::Cast<bool>(value);
}
std::tuple<pCompilerError, Value> Exp13::Evaluate(SymTable &syms) const
{
	auto[errorL, valueL] = symbol_1->Evaluate(syms);
	if (errorL)
		return { move(errorL), valueL };
	auto[errorR, valueR] = symbol_3->Evaluate(syms);
	if (errorR)
		return { move(errorR), valueR };
	return valueL == valueR;
}
std::tuple<pCompilerError, Value> Exp14::Evaluate(SymTable &syms) const
{
	auto[errorL, valueL] = symbol_1->Evaluate(syms);
	if (errorL)
		return { move(errorL), valueL };
	auto[errorR, valueR] = symbol_3->Evaluate(syms);
	if (errorR)
		return { move(errorR), valueR };
	return valueL != valueR;
}
std::tuple<pCompilerError, Value> Exp15::Evaluate(SymTable &syms) const
{
	auto[errorL, valueL] = symbol_1->Evaluate(syms);
	if (errorL)
		return { move(errorL), valueL };
	auto[errorR, valueR] = symbol_3->Evaluate(syms);
	if (errorR)
		return { move(errorR), valueR };
	return valueL > valueR;
}
std::tuple<pCompilerError, Value> Exp16::Evaluate(SymTable &syms) const
{
	auto[errorL, valueL] = symbol_1->Evaluate(syms);
	if (errorL)
		return { move(errorL), valueL };
	auto[errorR, valueR] = symbol_3->Evaluate(syms);
	if (errorR)
		return { move(errorR), valueR };
	return valueL < valueR;
}
std::tuple<pCompilerError, Value> Exp17::Evaluate(SymTable &syms) const
{
	auto[errorL, valueL] = symbol_1->Evaluate(syms);
	if (errorL)
		return { move(errorL), valueL };
	auto[errorR, valueR] = symbol_3->Evaluate(syms);
	if (errorR)
		return { move(errorR), valueR };
	return valueL >= valueR;
}
std::tuple<pCompilerError, Value> Exp18::Evaluate(SymTable &syms) const
{
	auto[errorL, valueL] = symbol_1->Evaluate(syms);
	if (errorL)
		return { move(errorL), valueL };
	auto[errorR, valueR] = symbol_3->Evaluate(syms);
	if (errorR)
		return { move(errorR), valueR };
	return valueL <= valueR;
}
std::tuple<pCompilerError, Value> Exp19::Evaluate(SymTable &syms) const
{
	return { pCompilerError(CompilerError::NoError), Value::Create(symbol_1->Value()) };
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
		stack.push(8);
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
	case 8:
		stack.push(7);
		break;
	default:
		err = { "Stat2::Process", "Syntax Error!" };
		return false;
	}
	return true;
}
bool AssignExp::Process(Stack &stack, SymStack &symStack, Parser::Error &err)
{
	switch (stack.top())
	{
	case 10:
		stack.push(22);
		break;
	case 15:
		stack.push(28);
		break;
	case 25:
		stack.push(47);
		break;
	case 27:
		stack.push(48);
		break;
	case 29:
		stack.push(50);
		break;
	default:
		err = { "AssignExp::Process", "Syntax Error!" };
		return false;
	}
	return true;
}
bool Exp::Process(Stack &stack, SymStack &symStack, Parser::Error &err)
{
	switch (stack.top())
	{
	case 10:
	case 15:
	case 25:
	case 27:
	case 29:
		stack.push(23);
		break;
	case 17:
		stack.push(31);
		break;
	case 18:
		stack.push(35);
		break;
	case 37:
		stack.push(55);
		break;
	case 38:
		stack.push(56);
		break;
	case 39:
		stack.push(57);
		break;
	case 40:
		stack.push(58);
		break;
	case 41:
		stack.push(59);
		break;
	case 42:
		stack.push(60);
		break;
	case 43:
		stack.push(61);
		break;
	case 44:
		stack.push(62);
		break;
	case 45:
		stack.push(63);
		break;
	case 46:
		stack.push(64);
		break;
	case 51:
		stack.push(67);
		break;
	case 52:
		stack.push(68);
		break;
	case 53:
		stack.push(69);
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
	case 8:
		stack.push(2);
		break;
	case 7:
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
	case 13:
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
	case 14:
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
	case 24:
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
	case 26:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pTerm sym3 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pName sym2 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		pBoolT sym1 = pCast<BoolT>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat27(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 36:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pTerm sym4 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pAssignExp sym3 = pCast<AssignExp>(move(symStack.top()));
		symStack.pop();
		pAssign sym2 = pCast<Assign>(move(symStack.top()));
		symStack.pop();
		pName sym1 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat26(move(sym1), move(sym2), move(sym3), move(sym4)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 49:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pTerm sym5 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pAssignExp sym4 = pCast<AssignExp>(move(symStack.top()));
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
	case 65:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pTerm sym5 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pAssignExp sym4 = pCast<AssignExp>(move(symStack.top()));
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
	case 66:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pTerm sym5 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pAssignExp sym4 = pCast<AssignExp>(move(symStack.top()));
		symStack.pop();
		pAssign sym3 = pCast<Assign>(move(symStack.top()));
		symStack.pop();
		pName sym2 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		pBoolT sym1 = pCast<BoolT>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat28(move(sym1), move(sym2), move(sym3), move(sym4), move(sym5)));
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
	case 7:
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
	case 8:
		stack.push(13);
		break;
	case 13:
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
	case 14:
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
	case 24:
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
	case 26:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pTerm sym3 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pName sym2 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		pBoolT sym1 = pCast<BoolT>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat27(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 36:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pTerm sym4 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pAssignExp sym3 = pCast<AssignExp>(move(symStack.top()));
		symStack.pop();
		pAssign sym2 = pCast<Assign>(move(symStack.top()));
		symStack.pop();
		pName sym1 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat26(move(sym1), move(sym2), move(sym3), move(sym4)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 49:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pTerm sym5 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pAssignExp sym4 = pCast<AssignExp>(move(symStack.top()));
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
	case 65:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pTerm sym5 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pAssignExp sym4 = pCast<AssignExp>(move(symStack.top()));
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
	case 66:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pTerm sym5 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pAssignExp sym4 = pCast<AssignExp>(move(symStack.top()));
		symStack.pop();
		pAssign sym3 = pCast<Assign>(move(symStack.top()));
		symStack.pop();
		pName sym2 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		pBoolT sym1 = pCast<BoolT>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat28(move(sym1), move(sym2), move(sym3), move(sym4), move(sym5)));
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
	case 8:
		stack.push(3);
		break;
	case 7:
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
	case 13:
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
	case 14:
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
	case 18:
		stack.push(32);
		break;
	case 24:
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
	case 26:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pTerm sym3 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pName sym2 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		pBoolT sym1 = pCast<BoolT>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat27(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 36:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pTerm sym4 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pAssignExp sym3 = pCast<AssignExp>(move(symStack.top()));
		symStack.pop();
		pAssign sym2 = pCast<Assign>(move(symStack.top()));
		symStack.pop();
		pName sym1 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat26(move(sym1), move(sym2), move(sym3), move(sym4)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 49:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pTerm sym5 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pAssignExp sym4 = pCast<AssignExp>(move(symStack.top()));
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
	case 65:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pTerm sym5 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pAssignExp sym4 = pCast<AssignExp>(move(symStack.top()));
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
	case 66:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pTerm sym5 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pAssignExp sym4 = pCast<AssignExp>(move(symStack.top()));
		symStack.pop();
		pAssign sym3 = pCast<Assign>(move(symStack.top()));
		symStack.pop();
		pName sym2 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		pBoolT sym1 = pCast<BoolT>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat28(move(sym1), move(sym2), move(sym3), move(sym4), move(sym5)));
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
	case 8:
		stack.push(4);
		break;
	case 3:
		stack.push(9);
		break;
	case 5:
		stack.push(11);
		break;
	case 6:
		stack.push(12);
		break;
	case 7:
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
	case 10:
	case 15:
	case 25:
	case 27:
	case 29:
		stack.push(16);
		break;
	case 13:
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
	case 14:
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
	case 17:
	case 18:
	case 37:
	case 38:
	case 39:
	case 40:
	case 41:
	case 42:
	case 43:
	case 44:
	case 45:
	case 46:
	case 51:
	case 52:
	case 53:
		stack.push(30);
		break;
	case 24:
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
	case 26:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pTerm sym3 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pName sym2 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		pBoolT sym1 = pCast<BoolT>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat27(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 36:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pTerm sym4 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pAssignExp sym3 = pCast<AssignExp>(move(symStack.top()));
		symStack.pop();
		pAssign sym2 = pCast<Assign>(move(symStack.top()));
		symStack.pop();
		pName sym1 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat26(move(sym1), move(sym2), move(sym3), move(sym4)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 49:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pTerm sym5 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pAssignExp sym4 = pCast<AssignExp>(move(symStack.top()));
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
	case 65:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pTerm sym5 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pAssignExp sym4 = pCast<AssignExp>(move(symStack.top()));
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
	case 66:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pTerm sym5 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pAssignExp sym4 = pCast<AssignExp>(move(symStack.top()));
		symStack.pop();
		pAssign sym3 = pCast<Assign>(move(symStack.top()));
		symStack.pop();
		pName sym2 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		pBoolT sym1 = pCast<BoolT>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat28(move(sym1), move(sym2), move(sym3), move(sym4), move(sym5)));
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
	case 9:
		stack.push(14);
		break;
	case 11:
		stack.push(24);
		break;
	case 12:
		stack.push(26);
		break;
	case 16:
	case 30:
	{
		stack.pop();
		pName sym1 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp8(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 19:
	{
		stack.pop();
		pIntL sym1 = pCast<IntL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp6(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 20:
	{
		stack.pop();
		pDoubleL sym1 = pCast<DoubleL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp7(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 21:
	{
		stack.pop();
		pBoolL sym1 = pCast<BoolL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp19(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 22:
		stack.push(36);
		break;
	case 23:
	{
		stack.pop();
		pExp sym1 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new AssignExp2(move(sym1)));
		return AssignExp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 28:
		stack.push(49);
		break;
	case 31:
	{
		stack.pop();
		stack.pop();
		pExp sym2 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pSub sym1 = pCast<Sub>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp9(move(sym1), move(sym2)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 47:
		stack.push(65);
		break;
	case 48:
		stack.push(66);
		break;
	case 50:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pAssignExp sym3 = pCast<AssignExp>(move(symStack.top()));
		symStack.pop();
		pAssign sym2 = pCast<Assign>(move(symStack.top()));
		symStack.pop();
		pName sym1 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new AssignExp1(move(sym1), move(sym2), move(sym3)));
		return AssignExp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 54:
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
	case 55:
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
	case 56:
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
	case 57:
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
	case 58:
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
	case 59:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym3 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pEqual sym2 = pCast<Equal>(move(symStack.top()));
		symStack.pop();
		pExp sym1 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp13(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 60:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym3 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pNotEqual sym2 = pCast<NotEqual>(move(symStack.top()));
		symStack.pop();
		pExp sym1 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp14(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 61:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym3 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pGreater sym2 = pCast<Greater>(move(symStack.top()));
		symStack.pop();
		pExp sym1 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp15(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 62:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym3 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pLess sym2 = pCast<Less>(move(symStack.top()));
		symStack.pop();
		pExp sym1 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp16(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 63:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym3 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pGreaterEqual sym2 = pCast<GreaterEqual>(move(symStack.top()));
		symStack.pop();
		pExp sym1 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp17(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 64:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym3 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pLessEqual sym2 = pCast<LessEqual>(move(symStack.top()));
		symStack.pop();
		pExp sym1 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp18(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 67:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym4 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pCloseP sym3 = pCast<CloseP>(move(symStack.top()));
		symStack.pop();
		pIntT sym2 = pCast<IntT>(move(symStack.top()));
		symStack.pop();
		pOpenP sym1 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp10(move(sym1), move(sym2), move(sym3), move(sym4)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 68:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym4 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pCloseP sym3 = pCast<CloseP>(move(symStack.top()));
		symStack.pop();
		pDoubleT sym2 = pCast<DoubleT>(move(symStack.top()));
		symStack.pop();
		pOpenP sym1 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp11(move(sym1), move(sym2), move(sym3), move(sym4)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 69:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym4 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pCloseP sym3 = pCast<CloseP>(move(symStack.top()));
		symStack.pop();
		pBoolT sym2 = pCast<BoolT>(move(symStack.top()));
		symStack.pop();
		pOpenP sym1 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp12(move(sym1), move(sym2), move(sym3), move(sym4)));
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
	case 8:
		stack.push(5);
		break;
	case 7:
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
	case 13:
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
	case 14:
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
	case 18:
		stack.push(33);
		break;
	case 24:
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
	case 26:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pTerm sym3 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pName sym2 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		pBoolT sym1 = pCast<BoolT>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat27(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 36:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pTerm sym4 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pAssignExp sym3 = pCast<AssignExp>(move(symStack.top()));
		symStack.pop();
		pAssign sym2 = pCast<Assign>(move(symStack.top()));
		symStack.pop();
		pName sym1 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat26(move(sym1), move(sym2), move(sym3), move(sym4)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 49:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pTerm sym5 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pAssignExp sym4 = pCast<AssignExp>(move(symStack.top()));
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
	case 65:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pTerm sym5 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pAssignExp sym4 = pCast<AssignExp>(move(symStack.top()));
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
	case 66:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pTerm sym5 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pAssignExp sym4 = pCast<AssignExp>(move(symStack.top()));
		symStack.pop();
		pAssign sym3 = pCast<Assign>(move(symStack.top()));
		symStack.pop();
		pName sym2 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		pBoolT sym1 = pCast<BoolT>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat28(move(sym1), move(sym2), move(sym3), move(sym4), move(sym5)));
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
		stack.push(10);
		break;
	case 9:
		stack.push(15);
		break;
	case 11:
		stack.push(25);
		break;
	case 12:
		stack.push(27);
		break;
	case 16:
		stack.push(29);
		break;
	default:
		err = { "Assign::Process", "Syntax Error!" };
		return false;
	}
	return true;
}
bool BoolT::Process(Stack &stack, SymStack &symStack, Parser::Error &err) const
{
	switch (stack.top())
	{
	case 0:
	case 2:
		symStack.emplace(new Stat12());
		return Stat1::Process(stack, symStack, err) && Process(stack, symStack, err);
	case 1:
	case 8:
		stack.push(6);
		break;
	case 7:
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
	case 13:
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
	case 14:
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
	case 18:
		stack.push(34);
		break;
	case 24:
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
	case 26:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pTerm sym3 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pName sym2 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		pBoolT sym1 = pCast<BoolT>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat27(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 36:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pTerm sym4 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pAssignExp sym3 = pCast<AssignExp>(move(symStack.top()));
		symStack.pop();
		pAssign sym2 = pCast<Assign>(move(symStack.top()));
		symStack.pop();
		pName sym1 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat26(move(sym1), move(sym2), move(sym3), move(sym4)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 49:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pTerm sym5 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pAssignExp sym4 = pCast<AssignExp>(move(symStack.top()));
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
	case 65:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pTerm sym5 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pAssignExp sym4 = pCast<AssignExp>(move(symStack.top()));
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
	case 66:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pTerm sym5 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pAssignExp sym4 = pCast<AssignExp>(move(symStack.top()));
		symStack.pop();
		pAssign sym3 = pCast<Assign>(move(symStack.top()));
		symStack.pop();
		pName sym2 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		pBoolT sym1 = pCast<BoolT>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat28(move(sym1), move(sym2), move(sym3), move(sym4), move(sym5)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	default:
		err = { "BoolT::Process", "Syntax Error!" };
		return false;
	}
	return true;
}
bool Add::Process(Stack &stack, SymStack &symStack, Parser::Error &err) const
{
	switch (stack.top())
	{
	case 16:
	case 30:
	{
		stack.pop();
		pName sym1 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp8(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 19:
	{
		stack.pop();
		pIntL sym1 = pCast<IntL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp6(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 20:
	{
		stack.pop();
		pDoubleL sym1 = pCast<DoubleL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp7(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 21:
	{
		stack.pop();
		pBoolL sym1 = pCast<BoolL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp19(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 23:
	case 35:
	case 59:
	case 60:
	case 61:
	case 62:
	case 63:
	case 64:
		stack.push(37);
		break;
	case 31:
	{
		stack.pop();
		stack.pop();
		pExp sym2 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pSub sym1 = pCast<Sub>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp9(move(sym1), move(sym2)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 54:
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
	case 55:
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
	case 56:
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
	case 57:
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
	case 58:
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
	case 67:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym4 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pCloseP sym3 = pCast<CloseP>(move(symStack.top()));
		symStack.pop();
		pIntT sym2 = pCast<IntT>(move(symStack.top()));
		symStack.pop();
		pOpenP sym1 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp10(move(sym1), move(sym2), move(sym3), move(sym4)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 68:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym4 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pCloseP sym3 = pCast<CloseP>(move(symStack.top()));
		symStack.pop();
		pDoubleT sym2 = pCast<DoubleT>(move(symStack.top()));
		symStack.pop();
		pOpenP sym1 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp11(move(sym1), move(sym2), move(sym3), move(sym4)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 69:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym4 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pCloseP sym3 = pCast<CloseP>(move(symStack.top()));
		symStack.pop();
		pBoolT sym2 = pCast<BoolT>(move(symStack.top()));
		symStack.pop();
		pOpenP sym1 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp12(move(sym1), move(sym2), move(sym3), move(sym4)));
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
	case 10:
	case 15:
	case 17:
	case 18:
	case 25:
	case 27:
	case 29:
	case 37:
	case 38:
	case 39:
	case 40:
	case 41:
	case 42:
	case 43:
	case 44:
	case 45:
	case 46:
	case 51:
	case 52:
	case 53:
		stack.push(17);
		break;
	case 16:
	case 30:
	{
		stack.pop();
		pName sym1 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp8(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 19:
	{
		stack.pop();
		pIntL sym1 = pCast<IntL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp6(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 20:
	{
		stack.pop();
		pDoubleL sym1 = pCast<DoubleL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp7(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 21:
	{
		stack.pop();
		pBoolL sym1 = pCast<BoolL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp19(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 23:
	case 35:
	case 59:
	case 60:
	case 61:
	case 62:
	case 63:
	case 64:
		stack.push(38);
		break;
	case 31:
	{
		stack.pop();
		stack.pop();
		pExp sym2 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pSub sym1 = pCast<Sub>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp9(move(sym1), move(sym2)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 54:
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
	case 55:
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
	case 56:
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
	case 57:
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
	case 58:
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
	case 67:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym4 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pCloseP sym3 = pCast<CloseP>(move(symStack.top()));
		symStack.pop();
		pIntT sym2 = pCast<IntT>(move(symStack.top()));
		symStack.pop();
		pOpenP sym1 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp10(move(sym1), move(sym2), move(sym3), move(sym4)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 68:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym4 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pCloseP sym3 = pCast<CloseP>(move(symStack.top()));
		symStack.pop();
		pDoubleT sym2 = pCast<DoubleT>(move(symStack.top()));
		symStack.pop();
		pOpenP sym1 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp11(move(sym1), move(sym2), move(sym3), move(sym4)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 69:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym4 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pCloseP sym3 = pCast<CloseP>(move(symStack.top()));
		symStack.pop();
		pBoolT sym2 = pCast<BoolT>(move(symStack.top()));
		symStack.pop();
		pOpenP sym1 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp12(move(sym1), move(sym2), move(sym3), move(sym4)));
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
	case 16:
	case 30:
	{
		stack.pop();
		pName sym1 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp8(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 19:
	{
		stack.pop();
		pIntL sym1 = pCast<IntL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp6(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 20:
	{
		stack.pop();
		pDoubleL sym1 = pCast<DoubleL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp7(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 21:
	{
		stack.pop();
		pBoolL sym1 = pCast<BoolL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp19(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 23:
	case 35:
	case 55:
	case 56:
	case 59:
	case 60:
	case 61:
	case 62:
	case 63:
	case 64:
		stack.push(39);
		break;
	case 31:
	{
		stack.pop();
		stack.pop();
		pExp sym2 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pSub sym1 = pCast<Sub>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp9(move(sym1), move(sym2)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 54:
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
	case 57:
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
	case 58:
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
	case 67:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym4 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pCloseP sym3 = pCast<CloseP>(move(symStack.top()));
		symStack.pop();
		pIntT sym2 = pCast<IntT>(move(symStack.top()));
		symStack.pop();
		pOpenP sym1 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp10(move(sym1), move(sym2), move(sym3), move(sym4)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 68:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym4 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pCloseP sym3 = pCast<CloseP>(move(symStack.top()));
		symStack.pop();
		pDoubleT sym2 = pCast<DoubleT>(move(symStack.top()));
		symStack.pop();
		pOpenP sym1 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp11(move(sym1), move(sym2), move(sym3), move(sym4)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 69:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym4 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pCloseP sym3 = pCast<CloseP>(move(symStack.top()));
		symStack.pop();
		pBoolT sym2 = pCast<BoolT>(move(symStack.top()));
		symStack.pop();
		pOpenP sym1 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp12(move(sym1), move(sym2), move(sym3), move(sym4)));
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
	case 16:
	case 30:
	{
		stack.pop();
		pName sym1 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp8(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 19:
	{
		stack.pop();
		pIntL sym1 = pCast<IntL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp6(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 20:
	{
		stack.pop();
		pDoubleL sym1 = pCast<DoubleL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp7(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 21:
	{
		stack.pop();
		pBoolL sym1 = pCast<BoolL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp19(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 23:
	case 35:
	case 55:
	case 56:
	case 59:
	case 60:
	case 61:
	case 62:
	case 63:
	case 64:
		stack.push(40);
		break;
	case 31:
	{
		stack.pop();
		stack.pop();
		pExp sym2 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pSub sym1 = pCast<Sub>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp9(move(sym1), move(sym2)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 54:
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
	case 57:
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
	case 58:
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
	case 67:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym4 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pCloseP sym3 = pCast<CloseP>(move(symStack.top()));
		symStack.pop();
		pIntT sym2 = pCast<IntT>(move(symStack.top()));
		symStack.pop();
		pOpenP sym1 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp10(move(sym1), move(sym2), move(sym3), move(sym4)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 68:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym4 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pCloseP sym3 = pCast<CloseP>(move(symStack.top()));
		symStack.pop();
		pDoubleT sym2 = pCast<DoubleT>(move(symStack.top()));
		symStack.pop();
		pOpenP sym1 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp11(move(sym1), move(sym2), move(sym3), move(sym4)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 69:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym4 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pCloseP sym3 = pCast<CloseP>(move(symStack.top()));
		symStack.pop();
		pBoolT sym2 = pCast<BoolT>(move(symStack.top()));
		symStack.pop();
		pOpenP sym1 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp12(move(sym1), move(sym2), move(sym3), move(sym4)));
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
	case 10:
	case 15:
	case 17:
	case 18:
	case 25:
	case 27:
	case 29:
	case 37:
	case 38:
	case 39:
	case 40:
	case 41:
	case 42:
	case 43:
	case 44:
	case 45:
	case 46:
	case 51:
	case 52:
	case 53:
		stack.push(18);
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
	case 16:
	case 30:
	{
		stack.pop();
		pName sym1 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp8(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 19:
	{
		stack.pop();
		pIntL sym1 = pCast<IntL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp6(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 20:
	{
		stack.pop();
		pDoubleL sym1 = pCast<DoubleL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp7(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 21:
	{
		stack.pop();
		pBoolL sym1 = pCast<BoolL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp19(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 31:
	{
		stack.pop();
		stack.pop();
		pExp sym2 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pSub sym1 = pCast<Sub>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp9(move(sym1), move(sym2)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 32:
		stack.push(51);
		break;
	case 33:
		stack.push(52);
		break;
	case 34:
		stack.push(53);
		break;
	case 35:
		stack.push(54);
		break;
	case 54:
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
	case 55:
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
	case 56:
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
	case 57:
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
	case 58:
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
	case 59:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym3 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pEqual sym2 = pCast<Equal>(move(symStack.top()));
		symStack.pop();
		pExp sym1 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp13(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 60:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym3 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pNotEqual sym2 = pCast<NotEqual>(move(symStack.top()));
		symStack.pop();
		pExp sym1 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp14(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 61:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym3 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pGreater sym2 = pCast<Greater>(move(symStack.top()));
		symStack.pop();
		pExp sym1 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp15(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 62:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym3 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pLess sym2 = pCast<Less>(move(symStack.top()));
		symStack.pop();
		pExp sym1 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp16(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 63:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym3 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pGreaterEqual sym2 = pCast<GreaterEqual>(move(symStack.top()));
		symStack.pop();
		pExp sym1 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp17(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 64:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym3 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pLessEqual sym2 = pCast<LessEqual>(move(symStack.top()));
		symStack.pop();
		pExp sym1 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp18(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 67:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym4 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pCloseP sym3 = pCast<CloseP>(move(symStack.top()));
		symStack.pop();
		pIntT sym2 = pCast<IntT>(move(symStack.top()));
		symStack.pop();
		pOpenP sym1 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp10(move(sym1), move(sym2), move(sym3), move(sym4)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 68:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym4 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pCloseP sym3 = pCast<CloseP>(move(symStack.top()));
		symStack.pop();
		pDoubleT sym2 = pCast<DoubleT>(move(symStack.top()));
		symStack.pop();
		pOpenP sym1 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp11(move(sym1), move(sym2), move(sym3), move(sym4)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 69:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym4 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pCloseP sym3 = pCast<CloseP>(move(symStack.top()));
		symStack.pop();
		pBoolT sym2 = pCast<BoolT>(move(symStack.top()));
		symStack.pop();
		pOpenP sym1 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp12(move(sym1), move(sym2), move(sym3), move(sym4)));
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
	case 10:
	case 15:
	case 17:
	case 18:
	case 25:
	case 27:
	case 29:
	case 37:
	case 38:
	case 39:
	case 40:
	case 41:
	case 42:
	case 43:
	case 44:
	case 45:
	case 46:
	case 51:
	case 52:
	case 53:
		stack.push(19);
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
	case 10:
	case 15:
	case 17:
	case 18:
	case 25:
	case 27:
	case 29:
	case 37:
	case 38:
	case 39:
	case 40:
	case 41:
	case 42:
	case 43:
	case 44:
	case 45:
	case 46:
	case 51:
	case 52:
	case 53:
		stack.push(20);
		break;
	default:
		err = { "DoubleL::Process", "Syntax Error!" };
		return false;
	}
	return true;
}
bool Equal::Process(Stack &stack, SymStack &symStack, Parser::Error &err) const
{
	switch (stack.top())
	{
	case 16:
	case 30:
	{
		stack.pop();
		pName sym1 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp8(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 19:
	{
		stack.pop();
		pIntL sym1 = pCast<IntL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp6(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 20:
	{
		stack.pop();
		pDoubleL sym1 = pCast<DoubleL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp7(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 21:
	{
		stack.pop();
		pBoolL sym1 = pCast<BoolL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp19(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 23:
	case 35:
		stack.push(41);
		break;
	case 31:
	{
		stack.pop();
		stack.pop();
		pExp sym2 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pSub sym1 = pCast<Sub>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp9(move(sym1), move(sym2)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 54:
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
	case 55:
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
	case 56:
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
	case 57:
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
	case 58:
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
	case 59:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym3 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pEqual sym2 = pCast<Equal>(move(symStack.top()));
		symStack.pop();
		pExp sym1 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp13(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 60:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym3 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pNotEqual sym2 = pCast<NotEqual>(move(symStack.top()));
		symStack.pop();
		pExp sym1 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp14(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 61:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym3 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pGreater sym2 = pCast<Greater>(move(symStack.top()));
		symStack.pop();
		pExp sym1 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp15(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 62:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym3 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pLess sym2 = pCast<Less>(move(symStack.top()));
		symStack.pop();
		pExp sym1 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp16(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 63:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym3 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pGreaterEqual sym2 = pCast<GreaterEqual>(move(symStack.top()));
		symStack.pop();
		pExp sym1 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp17(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 64:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym3 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pLessEqual sym2 = pCast<LessEqual>(move(symStack.top()));
		symStack.pop();
		pExp sym1 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp18(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 67:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym4 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pCloseP sym3 = pCast<CloseP>(move(symStack.top()));
		symStack.pop();
		pIntT sym2 = pCast<IntT>(move(symStack.top()));
		symStack.pop();
		pOpenP sym1 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp10(move(sym1), move(sym2), move(sym3), move(sym4)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 68:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym4 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pCloseP sym3 = pCast<CloseP>(move(symStack.top()));
		symStack.pop();
		pDoubleT sym2 = pCast<DoubleT>(move(symStack.top()));
		symStack.pop();
		pOpenP sym1 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp11(move(sym1), move(sym2), move(sym3), move(sym4)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 69:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym4 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pCloseP sym3 = pCast<CloseP>(move(symStack.top()));
		symStack.pop();
		pBoolT sym2 = pCast<BoolT>(move(symStack.top()));
		symStack.pop();
		pOpenP sym1 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp12(move(sym1), move(sym2), move(sym3), move(sym4)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	default:
		err = { "Equal::Process", "Syntax Error!" };
		return false;
	}
	return true;
}
bool NotEqual::Process(Stack &stack, SymStack &symStack, Parser::Error &err) const
{
	switch (stack.top())
	{
	case 16:
	case 30:
	{
		stack.pop();
		pName sym1 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp8(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 19:
	{
		stack.pop();
		pIntL sym1 = pCast<IntL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp6(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 20:
	{
		stack.pop();
		pDoubleL sym1 = pCast<DoubleL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp7(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 21:
	{
		stack.pop();
		pBoolL sym1 = pCast<BoolL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp19(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 23:
	case 35:
		stack.push(42);
		break;
	case 31:
	{
		stack.pop();
		stack.pop();
		pExp sym2 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pSub sym1 = pCast<Sub>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp9(move(sym1), move(sym2)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 54:
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
	case 55:
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
	case 56:
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
	case 57:
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
	case 58:
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
	case 59:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym3 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pEqual sym2 = pCast<Equal>(move(symStack.top()));
		symStack.pop();
		pExp sym1 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp13(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 60:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym3 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pNotEqual sym2 = pCast<NotEqual>(move(symStack.top()));
		symStack.pop();
		pExp sym1 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp14(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 61:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym3 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pGreater sym2 = pCast<Greater>(move(symStack.top()));
		symStack.pop();
		pExp sym1 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp15(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 62:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym3 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pLess sym2 = pCast<Less>(move(symStack.top()));
		symStack.pop();
		pExp sym1 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp16(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 63:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym3 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pGreaterEqual sym2 = pCast<GreaterEqual>(move(symStack.top()));
		symStack.pop();
		pExp sym1 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp17(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 64:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym3 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pLessEqual sym2 = pCast<LessEqual>(move(symStack.top()));
		symStack.pop();
		pExp sym1 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp18(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 67:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym4 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pCloseP sym3 = pCast<CloseP>(move(symStack.top()));
		symStack.pop();
		pIntT sym2 = pCast<IntT>(move(symStack.top()));
		symStack.pop();
		pOpenP sym1 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp10(move(sym1), move(sym2), move(sym3), move(sym4)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 68:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym4 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pCloseP sym3 = pCast<CloseP>(move(symStack.top()));
		symStack.pop();
		pDoubleT sym2 = pCast<DoubleT>(move(symStack.top()));
		symStack.pop();
		pOpenP sym1 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp11(move(sym1), move(sym2), move(sym3), move(sym4)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 69:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym4 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pCloseP sym3 = pCast<CloseP>(move(symStack.top()));
		symStack.pop();
		pBoolT sym2 = pCast<BoolT>(move(symStack.top()));
		symStack.pop();
		pOpenP sym1 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp12(move(sym1), move(sym2), move(sym3), move(sym4)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	default:
		err = { "NotEqual::Process", "Syntax Error!" };
		return false;
	}
	return true;
}
bool Greater::Process(Stack &stack, SymStack &symStack, Parser::Error &err) const
{
	switch (stack.top())
	{
	case 16:
	case 30:
	{
		stack.pop();
		pName sym1 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp8(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 19:
	{
		stack.pop();
		pIntL sym1 = pCast<IntL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp6(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 20:
	{
		stack.pop();
		pDoubleL sym1 = pCast<DoubleL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp7(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 21:
	{
		stack.pop();
		pBoolL sym1 = pCast<BoolL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp19(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 23:
	case 35:
	case 59:
	case 60:
		stack.push(43);
		break;
	case 31:
	{
		stack.pop();
		stack.pop();
		pExp sym2 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pSub sym1 = pCast<Sub>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp9(move(sym1), move(sym2)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 54:
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
	case 55:
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
	case 56:
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
	case 57:
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
	case 58:
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
	case 61:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym3 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pGreater sym2 = pCast<Greater>(move(symStack.top()));
		symStack.pop();
		pExp sym1 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp15(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 62:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym3 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pLess sym2 = pCast<Less>(move(symStack.top()));
		symStack.pop();
		pExp sym1 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp16(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 63:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym3 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pGreaterEqual sym2 = pCast<GreaterEqual>(move(symStack.top()));
		symStack.pop();
		pExp sym1 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp17(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 64:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym3 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pLessEqual sym2 = pCast<LessEqual>(move(symStack.top()));
		symStack.pop();
		pExp sym1 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp18(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 67:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym4 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pCloseP sym3 = pCast<CloseP>(move(symStack.top()));
		symStack.pop();
		pIntT sym2 = pCast<IntT>(move(symStack.top()));
		symStack.pop();
		pOpenP sym1 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp10(move(sym1), move(sym2), move(sym3), move(sym4)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 68:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym4 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pCloseP sym3 = pCast<CloseP>(move(symStack.top()));
		symStack.pop();
		pDoubleT sym2 = pCast<DoubleT>(move(symStack.top()));
		symStack.pop();
		pOpenP sym1 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp11(move(sym1), move(sym2), move(sym3), move(sym4)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 69:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym4 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pCloseP sym3 = pCast<CloseP>(move(symStack.top()));
		symStack.pop();
		pBoolT sym2 = pCast<BoolT>(move(symStack.top()));
		symStack.pop();
		pOpenP sym1 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp12(move(sym1), move(sym2), move(sym3), move(sym4)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	default:
		err = { "Greater::Process", "Syntax Error!" };
		return false;
	}
	return true;
}
bool Less::Process(Stack &stack, SymStack &symStack, Parser::Error &err) const
{
	switch (stack.top())
	{
	case 16:
	case 30:
	{
		stack.pop();
		pName sym1 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp8(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 19:
	{
		stack.pop();
		pIntL sym1 = pCast<IntL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp6(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 20:
	{
		stack.pop();
		pDoubleL sym1 = pCast<DoubleL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp7(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 21:
	{
		stack.pop();
		pBoolL sym1 = pCast<BoolL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp19(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 23:
	case 35:
	case 59:
	case 60:
		stack.push(44);
		break;
	case 31:
	{
		stack.pop();
		stack.pop();
		pExp sym2 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pSub sym1 = pCast<Sub>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp9(move(sym1), move(sym2)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 54:
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
	case 55:
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
	case 56:
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
	case 57:
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
	case 58:
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
	case 61:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym3 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pGreater sym2 = pCast<Greater>(move(symStack.top()));
		symStack.pop();
		pExp sym1 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp15(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 62:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym3 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pLess sym2 = pCast<Less>(move(symStack.top()));
		symStack.pop();
		pExp sym1 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp16(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 63:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym3 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pGreaterEqual sym2 = pCast<GreaterEqual>(move(symStack.top()));
		symStack.pop();
		pExp sym1 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp17(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 64:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym3 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pLessEqual sym2 = pCast<LessEqual>(move(symStack.top()));
		symStack.pop();
		pExp sym1 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp18(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 67:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym4 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pCloseP sym3 = pCast<CloseP>(move(symStack.top()));
		symStack.pop();
		pIntT sym2 = pCast<IntT>(move(symStack.top()));
		symStack.pop();
		pOpenP sym1 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp10(move(sym1), move(sym2), move(sym3), move(sym4)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 68:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym4 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pCloseP sym3 = pCast<CloseP>(move(symStack.top()));
		symStack.pop();
		pDoubleT sym2 = pCast<DoubleT>(move(symStack.top()));
		symStack.pop();
		pOpenP sym1 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp11(move(sym1), move(sym2), move(sym3), move(sym4)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 69:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym4 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pCloseP sym3 = pCast<CloseP>(move(symStack.top()));
		symStack.pop();
		pBoolT sym2 = pCast<BoolT>(move(symStack.top()));
		symStack.pop();
		pOpenP sym1 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp12(move(sym1), move(sym2), move(sym3), move(sym4)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	default:
		err = { "Less::Process", "Syntax Error!" };
		return false;
	}
	return true;
}
bool GreaterEqual::Process(Stack &stack, SymStack &symStack, Parser::Error &err) const
{
	switch (stack.top())
	{
	case 16:
	case 30:
	{
		stack.pop();
		pName sym1 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp8(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 19:
	{
		stack.pop();
		pIntL sym1 = pCast<IntL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp6(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 20:
	{
		stack.pop();
		pDoubleL sym1 = pCast<DoubleL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp7(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 21:
	{
		stack.pop();
		pBoolL sym1 = pCast<BoolL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp19(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 23:
	case 35:
	case 59:
	case 60:
		stack.push(45);
		break;
	case 31:
	{
		stack.pop();
		stack.pop();
		pExp sym2 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pSub sym1 = pCast<Sub>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp9(move(sym1), move(sym2)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 54:
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
	case 55:
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
	case 56:
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
	case 57:
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
	case 58:
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
	case 61:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym3 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pGreater sym2 = pCast<Greater>(move(symStack.top()));
		symStack.pop();
		pExp sym1 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp15(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 62:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym3 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pLess sym2 = pCast<Less>(move(symStack.top()));
		symStack.pop();
		pExp sym1 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp16(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 63:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym3 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pGreaterEqual sym2 = pCast<GreaterEqual>(move(symStack.top()));
		symStack.pop();
		pExp sym1 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp17(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 64:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym3 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pLessEqual sym2 = pCast<LessEqual>(move(symStack.top()));
		symStack.pop();
		pExp sym1 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp18(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 67:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym4 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pCloseP sym3 = pCast<CloseP>(move(symStack.top()));
		symStack.pop();
		pIntT sym2 = pCast<IntT>(move(symStack.top()));
		symStack.pop();
		pOpenP sym1 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp10(move(sym1), move(sym2), move(sym3), move(sym4)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 68:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym4 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pCloseP sym3 = pCast<CloseP>(move(symStack.top()));
		symStack.pop();
		pDoubleT sym2 = pCast<DoubleT>(move(symStack.top()));
		symStack.pop();
		pOpenP sym1 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp11(move(sym1), move(sym2), move(sym3), move(sym4)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 69:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym4 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pCloseP sym3 = pCast<CloseP>(move(symStack.top()));
		symStack.pop();
		pBoolT sym2 = pCast<BoolT>(move(symStack.top()));
		symStack.pop();
		pOpenP sym1 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp12(move(sym1), move(sym2), move(sym3), move(sym4)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	default:
		err = { "GreaterEqual::Process", "Syntax Error!" };
		return false;
	}
	return true;
}
bool LessEqual::Process(Stack &stack, SymStack &symStack, Parser::Error &err) const
{
	switch (stack.top())
	{
	case 16:
	case 30:
	{
		stack.pop();
		pName sym1 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp8(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 19:
	{
		stack.pop();
		pIntL sym1 = pCast<IntL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp6(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 20:
	{
		stack.pop();
		pDoubleL sym1 = pCast<DoubleL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp7(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 21:
	{
		stack.pop();
		pBoolL sym1 = pCast<BoolL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp19(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 23:
	case 35:
	case 59:
	case 60:
		stack.push(46);
		break;
	case 31:
	{
		stack.pop();
		stack.pop();
		pExp sym2 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pSub sym1 = pCast<Sub>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp9(move(sym1), move(sym2)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 54:
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
	case 55:
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
	case 56:
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
	case 57:
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
	case 58:
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
	case 61:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym3 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pGreater sym2 = pCast<Greater>(move(symStack.top()));
		symStack.pop();
		pExp sym1 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp15(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 62:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym3 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pLess sym2 = pCast<Less>(move(symStack.top()));
		symStack.pop();
		pExp sym1 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp16(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 63:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym3 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pGreaterEqual sym2 = pCast<GreaterEqual>(move(symStack.top()));
		symStack.pop();
		pExp sym1 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp17(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 64:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym3 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pLessEqual sym2 = pCast<LessEqual>(move(symStack.top()));
		symStack.pop();
		pExp sym1 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp18(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 67:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym4 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pCloseP sym3 = pCast<CloseP>(move(symStack.top()));
		symStack.pop();
		pIntT sym2 = pCast<IntT>(move(symStack.top()));
		symStack.pop();
		pOpenP sym1 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp10(move(sym1), move(sym2), move(sym3), move(sym4)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 68:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym4 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pCloseP sym3 = pCast<CloseP>(move(symStack.top()));
		symStack.pop();
		pDoubleT sym2 = pCast<DoubleT>(move(symStack.top()));
		symStack.pop();
		pOpenP sym1 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp11(move(sym1), move(sym2), move(sym3), move(sym4)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 69:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pExp sym4 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pCloseP sym3 = pCast<CloseP>(move(symStack.top()));
		symStack.pop();
		pBoolT sym2 = pCast<BoolT>(move(symStack.top()));
		symStack.pop();
		pOpenP sym1 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp12(move(sym1), move(sym2), move(sym3), move(sym4)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	default:
		err = { "LessEqual::Process", "Syntax Error!" };
		return false;
	}
	return true;
}
bool BoolL::Process(Stack &stack, SymStack &symStack, Parser::Error &err) const
{
	switch (stack.top())
	{
	case 10:
	case 15:
	case 17:
	case 18:
	case 25:
	case 27:
	case 29:
	case 37:
	case 38:
	case 39:
	case 40:
	case 41:
	case 42:
	case 43:
	case 44:
	case 45:
	case 46:
	case 51:
	case 52:
	case 53:
		stack.push(21);
		break;
	default:
		err = { "BoolL::Process", "Syntax Error!" };
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
	case 7:
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
	case 13:
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
	case 14:
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
	case 24:
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
	case 26:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pTerm sym3 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pName sym2 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		pBoolT sym1 = pCast<BoolT>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat27(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 36:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pTerm sym4 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pAssignExp sym3 = pCast<AssignExp>(move(symStack.top()));
		symStack.pop();
		pAssign sym2 = pCast<Assign>(move(symStack.top()));
		symStack.pop();
		pName sym1 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat26(move(sym1), move(sym2), move(sym3), move(sym4)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 49:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pTerm sym5 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pAssignExp sym4 = pCast<AssignExp>(move(symStack.top()));
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
	case 65:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pTerm sym5 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pAssignExp sym4 = pCast<AssignExp>(move(symStack.top()));
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
	case 66:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pTerm sym5 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pAssignExp sym4 = pCast<AssignExp>(move(symStack.top()));
		symStack.pop();
		pAssign sym3 = pCast<Assign>(move(symStack.top()));
		symStack.pop();
		pName sym2 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		pBoolT sym1 = pCast<BoolT>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat28(move(sym1), move(sym2), move(sym3), move(sym4), move(sym5)));
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
		case 'b':
			return State_11(it, end);
		case 'o':
		case 'l':
		case 'n':
		case 'u':
		case 'e':
		case 'r':
		case 'a':
		case 's':
		case 'c':
		case 'g':
		case 'h':
		case 'j':
		case 'k':
		case 'm':
		case 'p':
		case 'q':
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
			return State_27(it, end);
		case 'i':
			return State_22(it, end);
		case 't':
			return State_24(it, end);
		case 'd':
			return State_29(it, end);
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
			return State_5(it, end);
		case '+':
			return ADD;
		case '-':
			return SUB;
		case '*':
			return MULT;
		case '/':
			return DIV;
		case '!':
			return State_12(it, end);
		case '>':
			return State_6(it, end);
		case '<':
			return State_7(it, end);
		case 'f':
			return State_25(it, end);
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
			return State_9(it, end);
		case '.':
			return State_17(it, end);
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
		case 'b':
		case 'o':
		case 'l':
		case 'i':
		case 'n':
		case 't':
		case 'd':
		case 'u':
		case 'e':
		case 'r':
		case 'f':
		case 'a':
		case 's':
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
		case 'h':
		case 'j':
		case 'k':
		case 'm':
		case 'p':
		case 'q':
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
			contValid = State_27(cont, end);
			break;
		}
		if (contValid != INVALID) {
			it = cont;
			return contValid;
		}
	}
	return BOOLT;
}
Lexer::Type Lexer::State_3(Iterator &it, Iterator end)
{
	if (it != end)
	{
		Iterator cont = it;
		Type contValid = INVALID;
		switch (*cont++)
		{
		case 'b':
		case 'o':
		case 'l':
		case 'i':
		case 'n':
		case 't':
		case 'd':
		case 'u':
		case 'e':
		case 'r':
		case 'f':
		case 'a':
		case 's':
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
		case 'h':
		case 'j':
		case 'k':
		case 'm':
		case 'p':
		case 'q':
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
			contValid = State_27(cont, end);
			break;
		}
		if (contValid != INVALID) {
			it = cont;
			return contValid;
		}
	}
	return INTT;
}
Lexer::Type Lexer::State_4(Iterator &it, Iterator end)
{
	if (it != end)
	{
		Iterator cont = it;
		Type contValid = INVALID;
		switch (*cont++)
		{
		case 'b':
		case 'o':
		case 'l':
		case 'i':
		case 'n':
		case 't':
		case 'd':
		case 'u':
		case 'e':
		case 'r':
		case 'f':
		case 'a':
		case 's':
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
		case 'h':
		case 'j':
		case 'k':
		case 'm':
		case 'p':
		case 'q':
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
			contValid = State_27(cont, end);
			break;
		}
		if (contValid != INVALID) {
			it = cont;
			return contValid;
		}
	}
	return DOUBLET;
}
Lexer::Type Lexer::State_5(Iterator &it, Iterator end)
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
Lexer::Type Lexer::State_6(Iterator &it, Iterator end)
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
Lexer::Type Lexer::State_7(Iterator &it, Iterator end)
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
Lexer::Type Lexer::State_8(Iterator &it, Iterator end)
{
	if (it != end)
	{
		Iterator cont = it;
		Type contValid = INVALID;
		switch (*cont++)
		{
		case 'b':
		case 'o':
		case 'l':
		case 'i':
		case 'n':
		case 't':
		case 'd':
		case 'u':
		case 'e':
		case 'r':
		case 'f':
		case 'a':
		case 's':
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
		case 'h':
		case 'j':
		case 'k':
		case 'm':
		case 'p':
		case 'q':
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
			contValid = State_27(cont, end);
			break;
		}
		if (contValid != INVALID) {
			it = cont;
			return contValid;
		}
	}
	return BOOLL;
}
Lexer::Type Lexer::State_9(Iterator &it, Iterator end)
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
			contValid = State_9(cont, end);
			break;
		case '.':
			contValid = State_10(cont, end);
			break;
		}
		if (contValid != INVALID) {
			it = cont;
			return contValid;
		}
	}
	return INTL;
}
Lexer::Type Lexer::State_10(Iterator &it, Iterator end)
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
			contValid = State_10(cont, end);
			break;
		}
		if (contValid != INVALID) {
			it = cont;
			return contValid;
		}
	}
	return DOUBLEL;
}
Lexer::Type Lexer::State_11(Iterator &it, Iterator end)
{
	if (it != end)
	{
		Iterator cont = it;
		Type contValid = INVALID;
		switch (*cont++)
		{
		case 'b':
		case 'l':
		case 'i':
		case 'n':
		case 't':
		case 'd':
		case 'u':
		case 'e':
		case 'r':
		case 'f':
		case 'a':
		case 's':
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
		case 'h':
		case 'j':
		case 'k':
		case 'm':
		case 'p':
		case 'q':
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
			contValid = State_27(cont, end);
			break;
		case 'o':
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
Lexer::Type Lexer::State_12(Iterator &it, Iterator end)
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
Lexer::Type Lexer::State_13(Iterator &it, Iterator end)
{
	if (it != end)
	{
		Iterator cont = it;
		Type contValid = INVALID;
		switch (*cont++)
		{
		case 'b':
		case 'o':
		case 'i':
		case 'n':
		case 't':
		case 'd':
		case 'u':
		case 'e':
		case 'r':
		case 'f':
		case 'a':
		case 's':
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
		case 'h':
		case 'j':
		case 'k':
		case 'm':
		case 'p':
		case 'q':
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
			contValid = State_27(cont, end);
			break;
		case 'l':
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
Lexer::Type Lexer::State_14(Iterator &it, Iterator end)
{
	if (it != end)
	{
		Iterator cont = it;
		Type contValid = INVALID;
		switch (*cont++)
		{
		case 'b':
		case 'o':
		case 'l':
		case 'i':
		case 'n':
		case 'd':
		case 'u':
		case 'e':
		case 'r':
		case 'f':
		case 'a':
		case 's':
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
		case 'h':
		case 'j':
		case 'k':
		case 'm':
		case 'p':
		case 'q':
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
			contValid = State_27(cont, end);
			break;
		case 't':
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
Lexer::Type Lexer::State_15(Iterator &it, Iterator end)
{
	if (it != end)
	{
		Iterator cont = it;
		Type contValid = INVALID;
		switch (*cont++)
		{
		case 'b':
		case 'o':
		case 'l':
		case 'i':
		case 'n':
		case 't':
		case 'd':
		case 'u':
		case 'r':
		case 'f':
		case 'a':
		case 's':
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
		case 'h':
		case 'j':
		case 'k':
		case 'm':
		case 'p':
		case 'q':
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
			contValid = State_27(cont, end);
			break;
		case 'e':
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
Lexer::Type Lexer::State_16(Iterator &it, Iterator end)
{
	if (it != end)
	{
		Iterator cont = it;
		Type contValid = INVALID;
		switch (*cont++)
		{
		case 'b':
		case 'o':
		case 'l':
		case 'i':
		case 'n':
		case 't':
		case 'd':
		case 'u':
		case 'r':
		case 'f':
		case 'a':
		case 's':
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
		case 'h':
		case 'j':
		case 'k':
		case 'm':
		case 'p':
		case 'q':
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
			contValid = State_27(cont, end);
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
Lexer::Type Lexer::State_17(Iterator &it, Iterator end)
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
			return State_10(it, end);
		}
	}
	return INVALID;
}
Lexer::Type Lexer::State_18(Iterator &it, Iterator end)
{
	if (it != end)
	{
		Iterator cont = it;
		Type contValid = INVALID;
		switch (*cont++)
		{
		case 'b':
		case 'o':
		case 'l':
		case 'i':
		case 'n':
		case 't':
		case 'd':
		case 'u':
		case 'e':
		case 'r':
		case 'f':
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
		case 'h':
		case 'j':
		case 'k':
		case 'm':
		case 'p':
		case 'q':
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
			contValid = State_27(cont, end);
			break;
		case 's':
			contValid = State_15(cont, end);
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
		case 'b':
		case 'l':
		case 'i':
		case 'n':
		case 't':
		case 'd':
		case 'u':
		case 'e':
		case 'r':
		case 'f':
		case 'a':
		case 's':
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
		case 'h':
		case 'j':
		case 'k':
		case 'm':
		case 'p':
		case 'q':
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
			contValid = State_27(cont, end);
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
Lexer::Type Lexer::State_20(Iterator &it, Iterator end)
{
	if (it != end)
	{
		Iterator cont = it;
		Type contValid = INVALID;
		switch (*cont++)
		{
		case 'b':
		case 'o':
		case 'i':
		case 'n':
		case 't':
		case 'd':
		case 'u':
		case 'e':
		case 'r':
		case 'f':
		case 'a':
		case 's':
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
		case 'h':
		case 'j':
		case 'k':
		case 'm':
		case 'p':
		case 'q':
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
			contValid = State_27(cont, end);
			break;
		case 'l':
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
Lexer::Type Lexer::State_21(Iterator &it, Iterator end)
{
	if (it != end)
	{
		Iterator cont = it;
		Type contValid = INVALID;
		switch (*cont++)
		{
		case 'b':
		case 'o':
		case 'i':
		case 'n':
		case 't':
		case 'd':
		case 'u':
		case 'e':
		case 'r':
		case 'f':
		case 'a':
		case 's':
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
		case 'h':
		case 'j':
		case 'k':
		case 'm':
		case 'p':
		case 'q':
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
			contValid = State_27(cont, end);
			break;
		case 'l':
			contValid = State_16(cont, end);
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
		case 'b':
		case 'o':
		case 'l':
		case 'i':
		case 't':
		case 'd':
		case 'u':
		case 'e':
		case 'r':
		case 'f':
		case 'a':
		case 's':
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
		case 'h':
		case 'j':
		case 'k':
		case 'm':
		case 'p':
		case 'q':
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
			contValid = State_27(cont, end);
			break;
		case 'n':
			contValid = State_14(cont, end);
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
		case 'b':
		case 'o':
		case 'l':
		case 'i':
		case 'n':
		case 't':
		case 'd':
		case 'e':
		case 'r':
		case 'f':
		case 'a':
		case 's':
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
		case 'h':
		case 'j':
		case 'k':
		case 'm':
		case 'p':
		case 'q':
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
			contValid = State_27(cont, end);
			break;
		case 'u':
			contValid = State_15(cont, end);
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
		case 'b':
		case 'o':
		case 'l':
		case 'i':
		case 'n':
		case 't':
		case 'd':
		case 'u':
		case 'e':
		case 'f':
		case 'a':
		case 's':
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
		case 'h':
		case 'j':
		case 'k':
		case 'm':
		case 'p':
		case 'q':
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
			contValid = State_27(cont, end);
			break;
		case 'r':
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
Lexer::Type Lexer::State_25(Iterator &it, Iterator end)
{
	if (it != end)
	{
		Iterator cont = it;
		Type contValid = INVALID;
		switch (*cont++)
		{
		case 'b':
		case 'o':
		case 'l':
		case 'i':
		case 'n':
		case 't':
		case 'd':
		case 'u':
		case 'e':
		case 'r':
		case 'f':
		case 's':
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
		case 'h':
		case 'j':
		case 'k':
		case 'm':
		case 'p':
		case 'q':
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
			contValid = State_27(cont, end);
			break;
		case 'a':
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
Lexer::Type Lexer::State_26(Iterator &it, Iterator end)
{
	if (it != end)
	{
		Iterator cont = it;
		Type contValid = INVALID;
		switch (*cont++)
		{
		case 'b':
			contValid = State_21(cont, end);
			break;
		case 'o':
		case 'l':
		case 'i':
		case 'n':
		case 't':
		case 'd':
		case 'u':
		case 'e':
		case 'r':
		case 'f':
		case 'a':
		case 's':
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
		case 'h':
		case 'j':
		case 'k':
		case 'm':
		case 'p':
		case 'q':
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
Lexer::Type Lexer::State_27(Iterator &it, Iterator end)
{
	if (it != end)
	{
		Iterator cont = it;
		Type contValid = INVALID;
		switch (*cont++)
		{
		case 'b':
		case 'o':
		case 'l':
		case 'i':
		case 'n':
		case 't':
		case 'd':
		case 'u':
		case 'e':
		case 'r':
		case 'f':
		case 'a':
		case 's':
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
		case 'h':
		case 'j':
		case 'k':
		case 'm':
		case 'p':
		case 'q':
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
Lexer::Type Lexer::State_28(Iterator &it, Iterator end)
{
	if (it != end)
	{
		Iterator cont = it;
		Type contValid = INVALID;
		switch (*cont++)
		{
		case 'b':
		case 'o':
		case 'l':
		case 'i':
		case 'n':
		case 't':
		case 'd':
		case 'e':
		case 'r':
		case 'f':
		case 'a':
		case 's':
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
		case 'h':
		case 'j':
		case 'k':
		case 'm':
		case 'p':
		case 'q':
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
			contValid = State_27(cont, end);
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
Lexer::Type Lexer::State_29(Iterator &it, Iterator end)
{
	if (it != end)
	{
		Iterator cont = it;
		Type contValid = INVALID;
		switch (*cont++)
		{
		case 'b':
		case 'l':
		case 'i':
		case 'n':
		case 't':
		case 'd':
		case 'u':
		case 'e':
		case 'r':
		case 'f':
		case 'a':
		case 's':
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
		case 'h':
		case 'j':
		case 'k':
		case 'm':
		case 'p':
		case 'q':
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
			contValid = State_27(cont, end);
			break;
		case 'o':
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

void SymTable::Print(std::ostream &out) const
{
	for (const Variable &var : stack)
	{
		var.value.PrintType(out);
		out << ' ' << var.name << " = ";
		var.value.PrintValue(out);
		out << std::endl;
	}
}
void SymTable::EnterScope()
{
	stack.emplace_back();	// pushes an empty Variable object, which indicates a new scope;
}
void SymTable::ExitScope()
{
	while (!stack.back().ScopeMarker()) // pops the stack until an empty object is found and then pops the empty marker.
		stack.pop_back();
	stack.pop_back();
}
template<typename T> pCompilerError SymTable::Declare(const std::string &name)
{
	if (inCurrentScope(name))
		return CompilerError::New("SymTable::Declare", name + " is already used in the current scope.");
	stack.emplace_back(name, Value::Create<T>(0));
	return pCompilerError(CompilerError::NoError);
}
template<typename T> pCompilerError SymTable::Initialize(const std::string &name, Value value)
{
	if (inCurrentScope(name))
		return CompilerError::New("SymTable::Declare", name + " is already used in the current scope.");
	auto[error, valueC] = Value::Cast<T>(value);
	if (error)
		return move(error);
	stack.emplace_back(name, valueC);
	return pCompilerError(CompilerError::NoError);
}
pCompilerError SymTable::Assign(const std::string &name, Value value)
{
	for (auto it = stack.rbegin(); it != stack.rend(); it++)
	{
		if (it->name == name)
		{
			it->value.Assign(value);
			return pCompilerError(CompilerError::NoError);
		}
	}
	return CompilerError::New("SymTable::Assign", name + " is not defined.");
}
std::tuple<pCompilerError, Value> SymTable::AssignChain(const std::string &name, Value value)
{
	for (auto it = stack.rbegin(); it != stack.rend(); it++)
	{
		if (it->name == name)
		{
			it->value.Assign(value);
			return { pCompilerError(CompilerError::NoError), it->value };
		}
	}
	return { CompilerError::New("SymTable::AssignChain", name + " is not defined."), value };
}
std::tuple<pCompilerError, Value> SymTable::Get(const std::string &name) const
{
	for (auto it = stack.rbegin(); it != stack.rend(); it++)
		if (it->name == name)
			return { pCompilerError(CompilerError::NoError), it->value };
	return { CompilerError::New("SymTable::Get", name + " is not defined."), Value::Create() };
}
bool SymTable::inCurrentScope(const std::string &name) const
{
	for (auto it = stack.crbegin(); it != stack.crend(); it++)
	{
		if (it->ScopeMarker())
			return false;
		if (it->name == name)
			return true;
	}
	return false;
}

#define VALID_T(T) (std::is_same<T, int>::value || std::is_same<T, double>::value || std::is_same<T, bool>::value)
#define VALUE(OBJ) ((OBJ).type == INT ? (OBJ).vInt : ((OBJ).type == DOUBLE ? (OBJ).vDouble : (OBJ).vBool))
void Value::PrintValue(std::ostream &out) const
{
	switch (type)
	{
	case INT:
		out << vInt;
	case DOUBLE:
		out << vDouble;
	case BOOL:
		if (vBool == true)
			out << "true";
		else
			out << "false";
	}
}
void Value::PrintType(std::ostream &out) const
{
	switch (type)
	{
	case INT:
		out << "int";
	case DOUBLE:
		out << "double";
	case BOOL:
		out << "bool";
	}
}
template<typename T> Value Value::Create(T value)
{
	static_assert(VALID_T(T), "Value::Create: invalid type used to initialize Value object.");
	return value;
}
template<typename T> std::tuple<pCompilerError, Value> Value::Cast(Value value)
{
	static_assert(VALID_T(T), "Value::Cast: invalid type used to initialize Value object.");
	switch (value.type)
	{
	case INT:
		return { pCompilerError(CompilerError::NoError), Value((T)value.vInt) };
	case DOUBLE:
		return { pCompilerError(CompilerError::NoError), Value((T)value.vDouble) };
	case BOOL:
		if (std::is_same<T, int>::value)
			return { CompilerError::New("Value::Cast", "Object of type bool cannot be cast to type int."), value };
		if (std::is_same<T, double>::value)
			return { CompilerError::New("Value::Cast", "Object of type bool cannot be cast to type double."), value };
		return { pCompilerError(CompilerError::NoError), Value((T)value.vBool) };
	}
	return { CompilerError::New("","") , value };
}
void Value::Assign(Value value)
{
	switch (type)
	{
	case INT:
		vInt = (int)VALUE(value);
		break;
	case DOUBLE:
		vDouble = (double)VALUE(value);
		break;
	case BOOL:
		vBool = (bool)VALUE(value);
	}
}
std::tuple<pCompilerError, Value> Value::operator+(Value rhs) const
{
	if (type == BOOL || rhs.type == BOOL)
		return { CompilerError::New("Value::operator+", "No .+. operator defined for type bool."), *this };
	return { pCompilerError(CompilerError::NoError), Value(VALUE(*this) + VALUE(rhs)) };
}
std::tuple<pCompilerError, Value> Value::operator-(Value rhs) const
{
	if (type == BOOL || rhs.type == BOOL)
		return { CompilerError::New("Value::operator-", "No .-. operator defined for type bool."), *this };
	return { pCompilerError(CompilerError::NoError), Value(VALUE(*this) - VALUE(rhs)) };
}
std::tuple<pCompilerError, Value> Value::operator*(Value rhs) const
{
	if (type == BOOL || rhs.type == BOOL)
		return { CompilerError::New("Value::operator*", "No .*. operator defined for type bool."), *this };
	return { pCompilerError(CompilerError::NoError), Value(VALUE(*this) * VALUE(rhs)) };
}
std::tuple<pCompilerError, Value> Value::operator/(Value rhs) const
{
	if (type == BOOL || rhs.type == BOOL)
		return { CompilerError::New("Value::operator/", "No ./. operator defined for type bool."), *this };
	return { pCompilerError(CompilerError::NoError), Value(VALUE(*this) / VALUE(rhs)) };
}
std::tuple<pCompilerError, Value> Value::operator-() const
{
	if (type == BOOL)
		return { CompilerError::New("Value::operator-", "No -. operator defined for type bool."), *this };
	return { pCompilerError(CompilerError::NoError), Value(-VALUE(*this)) };
}
std::tuple<pCompilerError, Value> Value::operator==(Value rhs) const
{
	if ((type == BOOL) != (rhs.type == BOOL))
		return { CompilerError::New("Value::operator==", "No .==. operator defined for types bool and numeric."), *this };
	return { pCompilerError(CompilerError::NoError), Value(VALUE(*this) == VALUE(rhs)) };
}
std::tuple<pCompilerError, Value> Value::operator!=(Value rhs) const
{
	if ((type == BOOL) != (rhs.type == BOOL))
		return { CompilerError::New("Value::operator!=", "No .!=. operator defined for types bool and numeric."), *this };
	return { pCompilerError(CompilerError::NoError), Value(VALUE(*this) != VALUE(rhs)) };
}
std::tuple<pCompilerError, Value> Value::operator<(Value rhs) const
{
	if ((type == BOOL) != (rhs.type == BOOL))
		return { CompilerError::New("Value::operator<", "No .<. operator defined for types bool and numeric."), *this };
	return { pCompilerError(CompilerError::NoError), Value(VALUE(*this) < VALUE(rhs)) };
}
std::tuple<pCompilerError, Value> Value::operator>(Value rhs) const
{
	if ((type == BOOL) != (rhs.type == BOOL))
		return { CompilerError::New("Value::operator>", "No .>. operator defined for types bool and numeric."), *this };
	return { pCompilerError(CompilerError::NoError), Value(VALUE(*this) > VALUE(rhs)) };
}
std::tuple<pCompilerError, Value> Value::operator<=(Value rhs) const
{
	if ((type == BOOL) != (rhs.type == BOOL))
		return { CompilerError::New("Value::operator<=", "No .<=. operator defined for types bool and numeric."), *this };
	return { pCompilerError(CompilerError::NoError), Value(VALUE(*this) <= VALUE(rhs)) };
}
std::tuple<pCompilerError, Value> Value::operator>=(Value rhs) const
{
	if ((type == BOOL) != (rhs.type == BOOL))
		return { CompilerError::New("Value::operator>=", "No .>=. operator defined for types bool and numeric."), *this };
	return { pCompilerError(CompilerError::NoError), Value(VALUE(*this) >= VALUE(rhs)) };
}