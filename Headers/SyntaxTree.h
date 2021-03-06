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
class Cond;
class ValueStat;
class ChainAssign;
class AssignExp;
class Exp;
class Terminal;
class If;
class OpenP;
class CloseP;
class Else;
class While;
class OpenB;
class CloseB;
class IntT;
class Name;
class Term;
class DoubleT;
class BoolT;
class Assign;
class AddAssign;
class SubAssign;
class MultAssign;
class DivAssign;
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
typedef std::unique_ptr<Cond> pCond;
typedef std::unique_ptr<ValueStat> pValueStat;
typedef std::unique_ptr<ChainAssign> pChainAssign;
typedef std::unique_ptr<AssignExp> pAssignExp;
typedef std::unique_ptr<Exp> pExp;
typedef std::unique_ptr<Terminal> pTerminal;
typedef std::unique_ptr<If> pIf;
typedef std::unique_ptr<OpenP> pOpenP;
typedef std::unique_ptr<CloseP> pCloseP;
typedef std::unique_ptr<Else> pElse;
typedef std::unique_ptr<While> pWhile;
typedef std::unique_ptr<OpenB> pOpenB;
typedef std::unique_ptr<CloseB> pCloseB;
typedef std::unique_ptr<IntT> pIntT;
typedef std::unique_ptr<Name> pName;
typedef std::unique_ptr<Term> pTerm;
typedef std::unique_ptr<DoubleT> pDoubleT;
typedef std::unique_ptr<BoolT> pBoolT;
typedef std::unique_ptr<Assign> pAssign;
typedef std::unique_ptr<AddAssign> pAddAssign;
typedef std::unique_ptr<SubAssign> pSubAssign;
typedef std::unique_ptr<MultAssign> pMultAssign;
typedef std::unique_ptr<DivAssign> pDivAssign;
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
	enum Type { INVALID, IF, ELSE, WHILE, BOOLT, INTT, DOUBLET, TERM, OPENP, CLOSEP, OPENB, CLOSEB, ASSIGN, ADDASSIGN, SUBASSIGN, MULTASSIGN, DIVASSIGN, ADD, SUB, MULT, DIV, EQUAL, NOTEQUAL, GREATER, LESS, GREATEREQUAL, LESSEQUAL, BOOLL, INTL, DOUBLEL, NAME };

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
	static Type State_35(Iterator &it, Iterator end);
	static Type State_36(Iterator &it, Iterator end);
	static Type State_37(Iterator &it, Iterator end);
	static Type State_38(Iterator &it, Iterator end);
	static Type State_39(Iterator &it, Iterator end);
	static Type State_40(Iterator &it, Iterator end);
	static Type State_41(Iterator &it, Iterator end);
	static Type State_42(Iterator &it, Iterator end);
	static Type State_43(Iterator &it, Iterator end);

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
	Stat2_If(pIf &&sym1, pOpenP &&sym2, pCond &&sym3, pCloseP &&sym4, pStat2 &&sym5) : ifKey(move(sym1)), open(move(sym2)), condition(move(sym3)), close(move(sym4)), statement(move(sym5)) {}
	pCompilerError Evaluate(SymTable &syms) const;
private:
	const pIf ifKey;
	const pOpenP open;
	const pCond condition;
	const pCloseP close;
	const pStat2 statement;
};
class Stat2_IfElse : public Stat2
{
public:
	Stat2_IfElse(pIf &&sym1, pOpenP &&sym2, pCond &&sym3, pCloseP &&sym4, pStat2 &&sym5, pElse &&sym6, pStat2 &&sym7) : ifKey(move(sym1)), open(move(sym2)), condition(move(sym3)), close(move(sym4)), statIf(move(sym5)), elseKey(move(sym6)), statElse(move(sym7)) {}
	pCompilerError Evaluate(SymTable &syms) const;
private:
	const pIf ifKey;
	const pOpenP open;
	const pCond condition;
	const pCloseP close;
	const pStat2 statIf;
	const pElse elseKey;
	const pStat2 statElse;
};
class Stat2_While : public Stat2
{
public:
	Stat2_While(pWhile &&sym1, pOpenP &&sym2, pCond &&sym3, pCloseP &&sym4, pStat2 &&sym5) : whileKey(move(sym1)), open(move(sym2)), condition(move(sym3)), close(move(sym4)), statement(move(sym5)) {}
	pCompilerError Evaluate(SymTable &syms) const;
private:
	const pWhile whileKey;
	const pOpenP open;
	const pCond condition;
	const pCloseP close;
	const pStat2 statement;
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
	Stat2_Value(pValueStat &&sym1, pTerm &&sym2) : statement(move(sym1)), end(move(sym2)) {}
	pCompilerError Evaluate(SymTable &syms) const;
private:
	const pValueStat statement;
	const pTerm end;
};
class Cond : public Symbol
{
public:
	virtual ~Cond() = 0;
	static bool Process(Stack &stack, SymStack &symStack, Parser::Error &err);
	virtual tuple<pCompilerError, Value> Evaluate(SymTable &syms) const = 0;
};
inline Cond::~Cond() = default;
class Cond_Exp : public Cond
{
public:
	Cond_Exp(pExp &&sym1) : expression(move(sym1)) {}
	tuple<pCompilerError, Value> Evaluate(SymTable &syms) const;
private:
	const pExp expression;
};
class Cond_Assign : public Cond
{
public:
	Cond_Assign(pValueStat &&sym1) : expression(move(sym1)) {}
	tuple<pCompilerError, Value> Evaluate(SymTable &syms) const;
private:
	const pValueStat expression;
};
class ValueStat : public Symbol
{
public:
	virtual ~ValueStat() = 0;
	static bool Process(Stack &stack, SymStack &symStack, Parser::Error &err);
	virtual tuple<pCompilerError, Value> Evaluate(SymTable &syms) const = 0;
};
inline ValueStat::~ValueStat() = default;
class ValueStat_InitInt : public ValueStat
{
public:
	ValueStat_InitInt(pIntT &&sym1, pName &&sym2, pAssign &&sym3, pChainAssign &&sym4) : type(move(sym1)), name(move(sym2)), assign(move(sym3)), expression(move(sym4)) {}
	tuple<pCompilerError, Value> Evaluate(SymTable &syms) const;
private:
	const pIntT type;
	const pName name;
	const pAssign assign;
	const pChainAssign expression;
};
class ValueStat_InitDouble : public ValueStat
{
public:
	ValueStat_InitDouble(pDoubleT &&sym1, pName &&sym2, pAssign &&sym3, pChainAssign &&sym4) : type(move(sym1)), name(move(sym2)), assign(move(sym3)), expression(move(sym4)) {}
	tuple<pCompilerError, Value> Evaluate(SymTable &syms) const;
private:
	const pDoubleT type;
	const pName name;
	const pAssign assign;
	const pChainAssign expression;
};
class ValueStat_InitBool : public ValueStat
{
public:
	ValueStat_InitBool(pBoolT &&sym1, pName &&sym2, pAssign &&sym3, pChainAssign &&sym4) : type(move(sym1)), name(move(sym2)), assign(move(sym3)), expression(move(sym4)) {}
	tuple<pCompilerError, Value> Evaluate(SymTable &syms) const;
private:
	const pBoolT type;
	const pName name;
	const pAssign assign;
	const pChainAssign expression;
};
class ValueStat_Assign : public ValueStat
{
public:
	ValueStat_Assign(pAssignExp &&sym1) : expression(move(sym1)) {}
	tuple<pCompilerError, Value> Evaluate(SymTable &syms) const;
private:
	const pAssignExp expression;
};
class ChainAssign : public Symbol
{
public:
	virtual ~ChainAssign() = 0;
	static bool Process(Stack &stack, SymStack &symStack, Parser::Error &err);
	virtual tuple<pCompilerError, Value> Evaluate(SymTable &syms) const = 0;
};
inline ChainAssign::~ChainAssign() = default;
class ChainAssign_Chain : public ChainAssign
{
public:
	ChainAssign_Chain(pAssignExp &&sym1) : expression(move(sym1)) {}
	tuple<pCompilerError, Value> Evaluate(SymTable &syms) const;
private:
	const pAssignExp expression;
};
class ChainAssign_Exp : public ChainAssign
{
public:
	ChainAssign_Exp(pExp &&sym1) : expression(move(sym1)) {}
	tuple<pCompilerError, Value> Evaluate(SymTable &syms) const;
private:
	const pExp expression;
};
class AssignExp : public Symbol
{
public:
	virtual ~AssignExp() = 0;
	static bool Process(Stack &stack, SymStack &symStack, Parser::Error &err);
	virtual tuple<pCompilerError, Value> Evaluate(SymTable &syms) const = 0;
};
inline AssignExp::~AssignExp() = default;
class AssignExp_Assign : public AssignExp
{
public:
	AssignExp_Assign(pName &&sym1, pAssign &&sym2, pChainAssign &&sym3) : name(move(sym1)), assign(move(sym2)), expression(move(sym3)) {}
	tuple<pCompilerError, Value> Evaluate(SymTable &syms) const;
private:
	const pName name;
	const pAssign assign;
	const pChainAssign expression;
};
class AssignExp_AddAssign : public AssignExp
{
public:
	AssignExp_AddAssign(pName &&sym1, pAddAssign &&sym2, pChainAssign &&sym3) : name(move(sym1)), addAssign(move(sym2)), expression(move(sym3)) {}
	tuple<pCompilerError, Value> Evaluate(SymTable &syms) const;
private:
	const pName name;
	const pAddAssign addAssign;
	const pChainAssign expression;
};
class AssignExp_SubAssign : public AssignExp
{
public:
	AssignExp_SubAssign(pName &&sym1, pSubAssign &&sym2, pChainAssign &&sym3) : name(move(sym1)), subAssign(move(sym2)), expression(move(sym3)) {}
	tuple<pCompilerError, Value> Evaluate(SymTable &syms) const;
private:
	const pName name;
	const pSubAssign subAssign;
	const pChainAssign expression;
};
class AssignExp_MultAssign : public AssignExp
{
public:
	AssignExp_MultAssign(pName &&sym1, pMultAssign &&sym2, pChainAssign &&sym3) : name(move(sym1)), multAssign(move(sym2)), expression(move(sym3)) {}
	tuple<pCompilerError, Value> Evaluate(SymTable &syms) const;
private:
	const pName name;
	const pMultAssign multAssign;
	const pChainAssign expression;
};
class AssignExp_DivAssign : public AssignExp
{
public:
	AssignExp_DivAssign(pName &&sym1, pDivAssign &&sym2, pChainAssign &&sym3) : name(move(sym1)), divAssign(move(sym2)), expression(move(sym3)) {}
	tuple<pCompilerError, Value> Evaluate(SymTable &syms) const;
private:
	const pName name;
	const pDivAssign divAssign;
	const pChainAssign expression;
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
class While : public Terminal
{
public:
	While(std::string &&value) : value(move(value)) {}
	bool Process(Stack &stack, SymStack &symStack, Parser::Error &err) const;
private:
	std::ostream &print(std::ostream &os) const { return os << "WHILE[" << value << ']'; }
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
class AddAssign : public Terminal
{
public:
	AddAssign(std::string &&value) : value(move(value)) {}
	bool Process(Stack &stack, SymStack &symStack, Parser::Error &err) const;
private:
	std::ostream &print(std::ostream &os) const { return os << "ADDASSIGN[" << value << ']'; }
	const std::string value;
};
class SubAssign : public Terminal
{
public:
	SubAssign(std::string &&value) : value(move(value)) {}
	bool Process(Stack &stack, SymStack &symStack, Parser::Error &err) const;
private:
	std::ostream &print(std::ostream &os) const { return os << "SUBASSIGN[" << value << ']'; }
	const std::string value;
};
class MultAssign : public Terminal
{
public:
	MultAssign(std::string &&value) : value(move(value)) {}
	bool Process(Stack &stack, SymStack &symStack, Parser::Error &err) const;
private:
	std::ostream &print(std::ostream &os) const { return os << "MULTASSIGN[" << value << ']'; }
	const std::string value;
};
class DivAssign : public Terminal
{
public:
	DivAssign(std::string &&value) : value(move(value)) {}
	bool Process(Stack &stack, SymStack &symStack, Parser::Error &err) const;
private:
	std::ostream &print(std::ostream &os) const { return os << "DIVASSIGN[" << value << ']'; }
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