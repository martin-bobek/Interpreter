#ifndef SYNTAXTREE_H_
#define SYNTAXTREE_H_

#include <memory>
#include <vector>
#include <string>
#include <stack>
#include <iostream>

using std::move;
using std::tuple;

class CompilerError;
class Symbol;
class Stat1;
class Stat2;
class ValueExp;
class AssignExp;
class Exp;
class Terminal;
class If;
class OpenP;
class CloseP;
class Else;
class OpenB;
class CloseB;
class IntT;
class Name;
class Term;
class DoubleT;
class BoolT;
class Assign;
class Sub;
class Add;
class Mult;
class Div;
class Greater;
class Less;
class GreaterEqual;
class LessEqual;
class Equal;
class NotEqual;
class IntL;
class DoubleL;
class BoolL;

typedef std::unique_ptr<CompilerError> pCompilerError;
typedef std::unique_ptr<Symbol> pSymbol;
typedef std::unique_ptr<Stat1> pStat1;
typedef std::unique_ptr<Stat2> pStat2;
typedef std::unique_ptr<ValueExp> pValueExp;
typedef std::unique_ptr<AssignExp> pAssignExp;
typedef std::unique_ptr<Exp> pExp;
typedef std::unique_ptr<Terminal> pTerminal;
typedef std::unique_ptr<If> pIf;
typedef std::unique_ptr<OpenP> pOpenP;
typedef std::unique_ptr<CloseP> pCloseP;
typedef std::unique_ptr<Else> pElse;
typedef std::unique_ptr<OpenB> pOpenB;
typedef std::unique_ptr<CloseB> pCloseB;
typedef std::unique_ptr<IntT> pIntT;
typedef std::unique_ptr<Name> pName;
typedef std::unique_ptr<Term> pTerm;
typedef std::unique_ptr<DoubleT> pDoubleT;
typedef std::unique_ptr<BoolT> pBoolT;
typedef std::unique_ptr<Assign> pAssign;
typedef std::unique_ptr<Sub> pSub;
typedef std::unique_ptr<Add> pAdd;
typedef std::unique_ptr<Mult> pMult;
typedef std::unique_ptr<Div> pDiv;
typedef std::unique_ptr<Greater> pGreater;
typedef std::unique_ptr<Less> pLess;
typedef std::unique_ptr<GreaterEqual> pGreaterEqual;
typedef std::unique_ptr<LessEqual> pLessEqual;
typedef std::unique_ptr<Equal> pEqual;
typedef std::unique_ptr<NotEqual> pNotEqual;
typedef std::unique_ptr<IntL> pIntL;
typedef std::unique_ptr<DoubleL> pDoubleL;
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
	enum Type { INVALID, IF, ELSE, BOOLT, INTT, DOUBLET, TERM, OPENP, CLOSEP, OPENB, CLOSEB, ASSIGN, ADD, SUB, MULT, DIV, EQUAL, NOTEQUAL, GREATER, LESS, GREATEREQUAL, LESSEQUAL, BOOLL, INTL, DOUBLEL, NAME };

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
	static Type State_30(Iterator &it, Iterator end);
	static Type State_31(Iterator &it, Iterator end);
	static Type State_32(Iterator &it, Iterator end);
	static Type State_33(Iterator &it, Iterator end);
	static Type State_34(Iterator &it, Iterator end);

	std::istream &in;
	std::vector<pTerminal> tokens;
	Error err;
};
class Value
{
public:
	template<typename T> static Value Create(T value);
	static Value Create() { return 0; }
	template<typename T> static tuple<pCompilerError, Value> Cast(Value value);
	tuple<pCompilerError, Value> Assign(Value value);
	tuple<pCompilerError, Value> operator+(Value rhs) const;
	tuple<pCompilerError, Value> operator-(Value rhs) const;
	tuple<pCompilerError, Value> operator*(Value rhs) const;
	tuple<pCompilerError, Value> operator/(Value rhs) const;
	tuple<pCompilerError, Value> operator-() const;
	tuple<pCompilerError, Value> operator==(Value rhs) const;
	tuple<pCompilerError, Value> operator!=(Value rhs) const;
	tuple<pCompilerError, Value> operator<(Value rhs) const;
	tuple<pCompilerError, Value> operator>(Value rhs) const;
	tuple<pCompilerError, Value> operator<=(Value rhs) const;
	tuple<pCompilerError, Value> operator>=(Value rhs) const;
	tuple<pCompilerError, bool> IsTrue() const;
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
	template<typename T> tuple<pCompilerError, Value> Initialize(const std::string &name, Value value);
	tuple<pCompilerError, Value> Assign(const std::string &name, Value value);
	tuple<pCompilerError, Value> Get(const std::string &name) const;
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
class Stat1_Node : public Stat1
{
public:
	Stat1_Node(pStat1 &&sym1, pStat2 &&sym2) : stat1(move(sym1)), stat2(move(sym2)) {}
	pCompilerError Evaluate(SymTable &syms) const;
private:
	const pStat1 stat1;
	const pStat2 stat2;
};
class Stat1_End : public Stat1
{
public:
	Stat1_End() = default;
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
class Stat2_If : public Stat2
{
public:
	Stat2_If(pIf &&sym1, pOpenP &&sym2, pValueExp &&sym3, pCloseP &&sym4, pStat2 &&sym5) : ifKey(move(sym1)), open(move(sym2)), condition(move(sym3)), close(move(sym4)), stat2(move(sym5)) {}
	pCompilerError Evaluate(SymTable &syms) const;
private:
	const pIf ifKey;
	const pOpenP open;
	const pValueExp condition;
	const pCloseP close;
	const pStat2 stat2;
};
class Stat2_IfElse : public Stat2
{
public:
	Stat2_IfElse(pIf &&sym1, pOpenP &&sym2, pValueExp &&sym3, pCloseP &&sym4, pStat2 &&sym5, pElse &&sym6, pStat2 &&sym7) : ifKey(move(sym1)), open(move(sym2)), condition(move(sym3)), close(move(sym4)), statIf(move(sym5)), elseKey(move(sym6)), statElse(move(sym7)) {}
	pCompilerError Evaluate(SymTable &syms) const;
private:
	const pIf ifKey;
	const pOpenP open;
	const pValueExp condition;
	const pCloseP close;
	const pStat2 statIf;
	const pElse elseKey;
	const pStat2 statElse;
};
class Stat2_Scope : public Stat2
{
public:
	Stat2_Scope(pOpenB &&sym1, pStat1 &&sym2, pCloseB &&sym3) : open(move(sym1)), stat1(move(sym2)), close(move(sym3)) {}
	pCompilerError Evaluate(SymTable &syms) const;
private:
	const pOpenB open;
	const pStat1 stat1;
	const pCloseB close;
};
class Stat2_DeclInt : public Stat2
{
public:
	Stat2_DeclInt(pIntT &&sym1, pName &&sym2, pTerm &&sym3) : type(move(sym1)), name(move(sym2)), end(move(sym3)) {}
	pCompilerError Evaluate(SymTable &syms) const;
private:
	const pIntT type;
	const pName name;
	const pTerm end;
};
class Stat2_DeclDouble : public Stat2
{
public:
	Stat2_DeclDouble(pDoubleT &&sym1, pName &&sym2, pTerm &&sym3) : type(move(sym1)), name(move(sym2)), end(move(sym3)) {}
	pCompilerError Evaluate(SymTable &syms) const;
private:
	const pDoubleT type;
	const pName name;
	const pTerm end;
};
class Stat2_DeclBool : public Stat2
{
public:
	Stat2_DeclBool(pBoolT &&sym1, pName &&sym2, pTerm &&sym3) : type(move(sym1)), name(move(sym2)), end(move(sym3)) {}
	pCompilerError Evaluate(SymTable &syms) const;
private:
	const pBoolT type;
	const pName name;
	const pTerm end;
};
class Stat2_Value : public Stat2
{
public:
	Stat2_Value(pValueExp &&sym1, pTerm &&sym2) : expression(move(sym1)), end(move(sym2)) {}
	pCompilerError Evaluate(SymTable &syms) const;
private:
	const pValueExp expression;
	const pTerm end;
};
class ValueExp : public Symbol
{
public:
	virtual ~ValueExp() = 0;
	static bool Process(Stack &stack, SymStack &symStack, Parser::Error &err);
	virtual tuple<pCompilerError, Value> Evaluate(SymTable &syms) const = 0;
};
inline ValueExp::~ValueExp() = default;
class ValueExp_InitInt : public ValueExp
{
public:
	ValueExp_InitInt(pIntT &&sym1, pName &&sym2, pAssign &&sym3, pAssignExp &&sym4) : type(move(sym1)), name(move(sym2)), assign(move(sym3)), expression(move(sym4)) {}
	tuple<pCompilerError, Value> Evaluate(SymTable &syms) const;
private:
	const pIntT type;
	const pName name;
	const pAssign assign;
	const pAssignExp expression;
};
class ValueExp_InitDouble : public ValueExp
{
public:
	ValueExp_InitDouble(pDoubleT &&sym1, pName &&sym2, pAssign &&sym3, pAssignExp &&sym4) : type(move(sym1)), name(move(sym2)), assign(move(sym3)), expression(move(sym4)) {}
	tuple<pCompilerError, Value> Evaluate(SymTable &syms) const;
private:
	const pDoubleT type;
	const pName name;
	const pAssign assign;
	const pAssignExp expression;
};
class ValueExp_InitBool : public ValueExp
{
public:
	ValueExp_InitBool(pBoolT &&sym1, pName &&sym2, pAssign &&sym3, pAssignExp &&sym4) : type(move(sym1)), name(move(sym2)), assign(move(sym3)), expression(move(sym4)) {}
	tuple<pCompilerError, Value> Evaluate(SymTable &syms) const;
private:
	const pBoolT type;
	const pName name;
	const pAssign assign;
	const pAssignExp expression;
};
class ValueExp_Assign : public ValueExp
{
public:
	ValueExp_Assign(pAssignExp &&sym1) : expression(move(sym1)) {}
	tuple<pCompilerError, Value> Evaluate(SymTable &syms) const;
private:
	const pAssignExp expression;
};
class AssignExp : public Symbol
{
public:
	virtual ~AssignExp() = 0;
	static bool Process(Stack &stack, SymStack &symStack, Parser::Error &err);
	virtual tuple<pCompilerError, Value> Evaluate(SymTable &syms) const = 0;
};
inline AssignExp::~AssignExp() = default;
class AssignExp_Chain : public AssignExp
{
public:
	AssignExp_Chain(pName &&sym1, pAssign &&sym2, pAssignExp &&sym3) : name(move(sym1)), assign(move(sym2)), expression(move(sym3)) {}
	tuple<pCompilerError, Value> Evaluate(SymTable &syms) const;
private:
	const pName name;
	const pAssign assign;
	const pAssignExp expression;
};
class AssignExp_Exp : public AssignExp
{
public:
	AssignExp_Exp(pExp &&sym1) : expression(move(sym1)) {}
	tuple<pCompilerError, Value> Evaluate(SymTable &syms) const;
private:
	const pExp expression;
};
class Exp : public Symbol
{
public:
	virtual ~Exp() = 0;
	static bool Process(Stack &stack, SymStack &symStack, Parser::Error &err);
	virtual tuple<pCompilerError, Value> Evaluate(SymTable &syms) const = 0;
};
inline Exp::~Exp() = default;
class Exp_Prec : public Exp
{
public:
	Exp_Prec(pOpenP &&sym1, pExp &&sym2, pCloseP &&sym3) : open(move(sym1)), expression(move(sym2)), close(move(sym3)) {}
	tuple<pCompilerError, Value> Evaluate(SymTable &syms) const;
private:
	const pOpenP open;
	const pExp expression;
	const pCloseP close;
};
class Exp_CastInt : public Exp
{
public:
	Exp_CastInt(pOpenP &&sym1, pIntT &&sym2, pCloseP &&sym3, pExp &&sym4) : open(move(sym1)), type(move(sym2)), close(move(sym3)), expression(move(sym4)) {}
	tuple<pCompilerError, Value> Evaluate(SymTable &syms) const;
private:
	const pOpenP open;
	const pIntT type;
	const pCloseP close;
	const pExp expression;
};
class Exp_CastDouble : public Exp
{
public:
	Exp_CastDouble(pOpenP &&sym1, pDoubleT &&sym2, pCloseP &&sym3, pExp &&sym4) : open(move(sym1)), type(move(sym2)), close(move(sym3)), expression(move(sym4)) {}
	tuple<pCompilerError, Value> Evaluate(SymTable &syms) const;
private:
	const pOpenP open;
	const pDoubleT type;
	const pCloseP close;
	const pExp expression;
};
class Exp_CastBool : public Exp
{
public:
	Exp_CastBool(pOpenP &&sym1, pBoolT &&sym2, pCloseP &&sym3, pExp &&sym4) : open(move(sym1)), type(move(sym2)), close(move(sym3)), expression(move(sym4)) {}
	tuple<pCompilerError, Value> Evaluate(SymTable &syms) const;
private:
	const pOpenP open;
	const pBoolT type;
	const pCloseP close;
	const pExp expression;
};
class Exp_Negate : public Exp
{
public:
	Exp_Negate(pSub &&sym1, pExp &&sym2) : negative(move(sym1)), expression(move(sym2)) {}
	tuple<pCompilerError, Value> Evaluate(SymTable &syms) const;
private:
	const pSub negative;
	const pExp expression;
};
class Exp_Add : public Exp
{
public:
	Exp_Add(pExp &&sym1, pAdd &&sym2, pExp &&sym3) : expressionL(move(sym1)), add(move(sym2)), expressionR(move(sym3)) {}
	tuple<pCompilerError, Value> Evaluate(SymTable &syms) const;
private:
	const pExp expressionL;
	const pAdd add;
	const pExp expressionR;
};
class Exp_Sub : public Exp
{
public:
	Exp_Sub(pExp &&sym1, pSub &&sym2, pExp &&sym3) : expressionL(move(sym1)), sub(move(sym2)), expressionR(move(sym3)) {}
	tuple<pCompilerError, Value> Evaluate(SymTable &syms) const;
private:
	const pExp expressionL;
	const pSub sub;
	const pExp expressionR;
};
class Exp_Mult : public Exp
{
public:
	Exp_Mult(pExp &&sym1, pMult &&sym2, pExp &&sym3) : expressionL(move(sym1)), mult(move(sym2)), expressionR(move(sym3)) {}
	tuple<pCompilerError, Value> Evaluate(SymTable &syms) const;
private:
	const pExp expressionL;
	const pMult mult;
	const pExp expressionR;
};
class Exp_Div : public Exp
{
public:
	Exp_Div(pExp &&sym1, pDiv &&sym2, pExp &&sym3) : expressionL(move(sym1)), div(move(sym2)), expressionR(move(sym3)) {}
	tuple<pCompilerError, Value> Evaluate(SymTable &syms) const;
private:
	const pExp expressionL;
	const pDiv div;
	const pExp expressionR;
};
class Exp_Greater : public Exp
{
public:
	Exp_Greater(pExp &&sym1, pGreater &&sym2, pExp &&sym3) : expressionL(move(sym1)), greater(move(sym2)), expressionR(move(sym3)) {}
	tuple<pCompilerError, Value> Evaluate(SymTable &syms) const;
private:
	const pExp expressionL;
	const pGreater greater;
	const pExp expressionR;
};
class Exp_Less : public Exp
{
public:
	Exp_Less(pExp &&sym1, pLess &&sym2, pExp &&sym3) : expressionL(move(sym1)), less(move(sym2)), expressionR(move(sym3)) {}
	tuple<pCompilerError, Value> Evaluate(SymTable &syms) const;
private:
	const pExp expressionL;
	const pLess less;
	const pExp expressionR;
};
class Exp_GreaterEqual : public Exp
{
public:
	Exp_GreaterEqual(pExp &&sym1, pGreaterEqual &&sym2, pExp &&sym3) : expressionL(move(sym1)), greaterEqual(move(sym2)), expressionR(move(sym3)) {}
	tuple<pCompilerError, Value> Evaluate(SymTable &syms) const;
private:
	const pExp expressionL;
	const pGreaterEqual greaterEqual;
	const pExp expressionR;
};
class Exp_LessEqual : public Exp
{
public:
	Exp_LessEqual(pExp &&sym1, pLessEqual &&sym2, pExp &&sym3) : expressionL(move(sym1)), lessEqual(move(sym2)), expressionR(move(sym3)) {}
	tuple<pCompilerError, Value> Evaluate(SymTable &syms) const;
private:
	const pExp expressionL;
	const pLessEqual lessEqual;
	const pExp expressionR;
};
class Exp_Equal : public Exp
{
public:
	Exp_Equal(pExp &&sym1, pEqual &&sym2, pExp &&sym3) : expressionL(move(sym1)), equal(move(sym2)), expressionR(move(sym3)) {}
	tuple<pCompilerError, Value> Evaluate(SymTable &syms) const;
private:
	const pExp expressionL;
	const pEqual equal;
	const pExp expressionR;
};
class Exp_NotEqual : public Exp
{
public:
	Exp_NotEqual(pExp &&sym1, pNotEqual &&sym2, pExp &&sym3) : expressionL(move(sym1)), notEqual(move(sym2)), expressionR(move(sym3)) {}
	tuple<pCompilerError, Value> Evaluate(SymTable &syms) const;
private:
	const pExp expressionL;
	const pNotEqual notEqual;
	const pExp expressionR;
};
class Exp_Variable : public Exp
{
public:
	Exp_Variable(pName &&sym1) : name(move(sym1)) {}
	tuple<pCompilerError, Value> Evaluate(SymTable &syms) const;
private:
	const pName name;
};
class Exp_LiteralInt : public Exp
{
public:
	Exp_LiteralInt(pIntL &&sym1) : literal(move(sym1)) { }
	tuple<pCompilerError, Value> Evaluate(SymTable &syms) const;
private:
	const pIntL literal;
};
class Exp_LiteralDouble : public Exp
{
public:
	Exp_LiteralDouble(pDoubleL &&sym1) : literal(move(sym1)) {}
	tuple<pCompilerError, Value> Evaluate(SymTable &syms) const;
private:
	const pDoubleL literal;
};
class Exp_LiteralBool : public Exp
{
public:
	Exp_LiteralBool(pBoolL &&sym1) : literal(move(sym1)) {}
	tuple<pCompilerError, Value> Evaluate(SymTable &syms) const;
private:
	const pBoolL literal;
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
class If : public Terminal
{
public:
	If(std::string &&value) : value(move(value)) {}
	bool Process(Stack &stack, SymStack &symStack, Parser::Error &err) const;
private:
	std::ostream &print(std::ostream &os) const { return os << "IF[" << value << ']'; }
	const std::string value;
};
class Else : public Terminal
{
public:
	Else(std::string &&value) : value(move(value)) {}
	bool Process(Stack &stack, SymStack &symStack, Parser::Error &err) const;
private:
	std::ostream &print(std::ostream &os) const { return os << "ELSE[" << value << ']'; }
	const std::string value;
};
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