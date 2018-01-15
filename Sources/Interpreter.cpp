#include "SyntaxTree.h"
#include <tuple>

pCompilerError Stat1_Node::Evaluate(SymTable &syms) const
{
	pCompilerError error = stat1->Evaluate(syms);
	if (error)
		return error;
	return stat2->Evaluate(syms);
}
pCompilerError Stat1_End::Evaluate(SymTable &syms) const
{
	return pCompilerError(CompilerError::NoError);
}
pCompilerError Stat2_If::Evaluate(SymTable &syms) const
{
	syms.EnterScope();
	auto[errorE, valueE] = condition->Evaluate(syms);
	if (errorE)
		return move(errorE);
	auto[errorC, condVal] = valueE.IsTrue();
	if (errorC)
		return move(errorC);
	if (condVal)
	{
		pCompilerError errorS = statement->Evaluate(syms);
		if (errorS)
			return errorS;
	}
	syms.ExitScope();
	return pCompilerError(CompilerError::NoError);
}
pCompilerError Stat2_IfElse::Evaluate(SymTable &syms) const
{
	syms.EnterScope();
	auto[errorE, valueE] = condition->Evaluate(syms);
	if (errorE)
		return move(errorE);
	auto[errorC, condVal] = valueE.IsTrue();
	if (errorC)
		return move(errorC);
	if (condVal)
	{
		pCompilerError errorS = statIf->Evaluate(syms);
		if (errorS)
			return errorS;
	}
	else
	{
		pCompilerError errorS = statElse->Evaluate(syms);
		if (errorS)
			return errorS;
	}
	syms.ExitScope();
	return pCompilerError(CompilerError::NoError);
}
pCompilerError Stat2_While::Evaluate(SymTable &syms) const
{
	while (true)
	{
		syms.EnterScope();
		auto[errorE, valueE] = condition->Evaluate(syms);
		if (errorE)
			return move(errorE);
		auto[errorC, condVal] = valueE.IsTrue();
		if (errorC)
			return move(errorC);
		if (!condVal)
			break;
		pCompilerError errorS = statement->Evaluate(syms);
		if (errorS)
			return errorS;
		syms.ExitScope();
	}
	syms.ExitScope();
	return pCompilerError(CompilerError::NoError);
}
pCompilerError Stat2_Scope::Evaluate(SymTable &syms) const
{
	syms.EnterScope();
	pCompilerError error = stat1->Evaluate(syms);
	syms.ExitScope();
	return error;
}
pCompilerError Stat2_DeclInt::Evaluate(SymTable &syms) const
{
	return syms.Declare<int>(name->Value());
}
pCompilerError Stat2_DeclDouble::Evaluate(SymTable &syms) const
{
	return syms.Declare<double>(name->Value());
}
pCompilerError Stat2_DeclBool::Evaluate(SymTable &syms) const
{
	return syms.Declare<bool>(name->Value());
}
pCompilerError Stat2_Value::Evaluate(SymTable &syms) const
{
	return std::get<0>(expression->Evaluate(syms));
}
tuple<pCompilerError, Value> ValueExp_InitInt::Evaluate(SymTable &syms) const
{
	auto[error, value] = expression->Evaluate(syms);
	if (error)
		return { move(error), value };
	return syms.Initialize<int>(name->Value(), value);
}
tuple<pCompilerError, Value> ValueExp_InitDouble::Evaluate(SymTable &syms) const
{
	auto[error, value] = expression->Evaluate(syms);
	if (error)
		return { move(error), value };
	return syms.Initialize<double>(name->Value(), value);
}
tuple<pCompilerError, Value> ValueExp_InitBool::Evaluate(SymTable &syms) const
{
	auto[error, value] = expression->Evaluate(syms);
	if (error)
		return { move(error), value };
	return syms.Initialize<bool>(name->Value(), value);
}
tuple<pCompilerError, Value> ValueExp_Assign::Evaluate(SymTable &syms) const
{
	return expression->Evaluate(syms);
}
tuple<pCompilerError, Value> AssignExp_Chain::Evaluate(SymTable &syms) const
{
	auto[error, value] = expression->Evaluate(syms);
	if (error)
		return { move(error), value };
	return syms.Assign(name->Value(), value);
}
tuple<pCompilerError, Value> AssignExp_Exp::Evaluate(SymTable &syms) const
{
	return expression->Evaluate(syms);
}
tuple<pCompilerError, Value> Exp_Prec::Evaluate(SymTable &syms) const
{
	return expression->Evaluate(syms);
}
tuple<pCompilerError, Value> Exp_CastInt::Evaluate(SymTable &syms) const
{
	auto[error, value] = expression->Evaluate(syms);
	if (error)
		return { move(error), value };
	return Value::Cast<int>(value);
}
tuple<pCompilerError, Value> Exp_CastDouble::Evaluate(SymTable &syms) const
{
	auto[error, value] = expression->Evaluate(syms);
	if (error)
		return { move(error), value };
	return Value::Cast<double>(value);
}
tuple<pCompilerError, Value> Exp_CastBool::Evaluate(SymTable &syms) const
{
	auto[error, value] = expression->Evaluate(syms);
	if (error)
		return { move(error), value };
	return Value::Cast<bool>(value);
}
tuple<pCompilerError, Value> Exp_Negate::Evaluate(SymTable &syms) const
{
	auto[error, value] = expression->Evaluate(syms);
	if (error)
		return { move(error), value };
	return -value;
}
tuple<pCompilerError, Value> Exp_Add::Evaluate(SymTable &syms) const
{
	auto[errorL, valueL] = expressionL->Evaluate(syms);
	if (errorL)
		return { move(errorL), valueL };
	auto[errorR, valueR] = expressionR->Evaluate(syms);
	if (errorR)
		return { move(errorR), valueL };
	return valueL + valueR;

}
tuple<pCompilerError, Value> Exp_Sub::Evaluate(SymTable &syms) const
{
	auto[errorL, valueL] = expressionL->Evaluate(syms);
	if (errorL)
		return { move(errorL), valueL };
	auto[errorR, valueR] = expressionR->Evaluate(syms);
	if (errorR)
		return { move(errorR), valueL };
	return valueL - valueR;
}
tuple<pCompilerError, Value> Exp_Mult::Evaluate(SymTable &syms) const
{
	auto[errorL, valueL] = expressionL->Evaluate(syms);
	if (errorL)
		return { move(errorL), valueL };
	auto[errorR, valueR] = expressionR->Evaluate(syms);
	if (errorR)
		return { move(errorR), valueL };
	return valueL * valueR;
}
tuple<pCompilerError, Value> Exp_Div::Evaluate(SymTable &syms) const
{
	auto[errorL, valueL] = expressionL->Evaluate(syms);
	if (errorL)
		return { move(errorL), valueL };
	auto[errorR, valueR] = expressionR->Evaluate(syms);
	if (errorR)
		return { move(errorR), valueL };
	return valueL / valueR;
}
tuple<pCompilerError, Value> Exp_Greater::Evaluate(SymTable &syms) const
{
	auto[errorL, valueL] = expressionL->Evaluate(syms);
	if (errorL)
		return { move(errorL), valueL };
	auto[errorR, valueR] = expressionR->Evaluate(syms);
	if (errorR)
		return { move(errorR), valueR };
	return valueL > valueR;
}
tuple<pCompilerError, Value> Exp_Less::Evaluate(SymTable &syms) const
{
	auto[errorL, valueL] = expressionL->Evaluate(syms);
	if (errorL)
		return { move(errorL), valueL };
	auto[errorR, valueR] = expressionR->Evaluate(syms);
	if (errorR)
		return { move(errorR), valueR };
	return valueL < valueR;
}
tuple<pCompilerError, Value> Exp_GreaterEqual::Evaluate(SymTable &syms) const
{
	auto[errorL, valueL] = expressionL->Evaluate(syms);
	if (errorL)
		return { move(errorL), valueL };
	auto[errorR, valueR] = expressionR->Evaluate(syms);
	if (errorR)
		return { move(errorR), valueR };
	return valueL >= valueR;
}
tuple<pCompilerError, Value> Exp_LessEqual::Evaluate(SymTable &syms) const
{
	auto[errorL, valueL] = expressionL->Evaluate(syms);
	if (errorL)
		return { move(errorL), valueL };
	auto[errorR, valueR] = expressionR->Evaluate(syms);
	if (errorR)
		return { move(errorR), valueR };
	return valueL <= valueR;
}
tuple<pCompilerError, Value> Exp_Equal::Evaluate(SymTable &syms) const
{
	auto[errorL, valueL] = expressionL->Evaluate(syms);
	if (errorL)
		return { move(errorL), valueL };
	auto[errorR, valueR] = expressionR->Evaluate(syms);
	if (errorR)
		return { move(errorR), valueR };
	return valueL == valueR;
}
tuple<pCompilerError, Value> Exp_NotEqual::Evaluate(SymTable &syms) const
{
	auto[errorL, valueL] = expressionL->Evaluate(syms);
	if (errorL)
		return { move(errorL), valueL };
	auto[errorR, valueR] = expressionR->Evaluate(syms);
	if (errorR)
		return { move(errorR), valueR };
	return valueL != valueR;
}
tuple<pCompilerError, Value> Exp_Variable::Evaluate(SymTable &syms) const
{
	return syms.Get(name->Value());
}
tuple<pCompilerError, Value> Exp_LiteralInt::Evaluate(SymTable &syms) const
{
	return { pCompilerError(CompilerError::NoError), Value::Create(literal->Value()) };
}
tuple<pCompilerError, Value> Exp_LiteralDouble::Evaluate(SymTable &syms) const
{
	return { pCompilerError(CompilerError::NoError), Value::Create(literal->Value()) };
}
tuple<pCompilerError, Value> Exp_LiteralBool::Evaluate(SymTable &syms) const
{
	return { pCompilerError(CompilerError::NoError), Value::Create(literal->Value()) };
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
template<typename T> tuple<pCompilerError, Value> SymTable::Initialize(const std::string &name, Value value)
{
	if (inCurrentScope(name))
		return { CompilerError::New("SymTable::Declare", name + " is already used in the current scope."), value };
	auto[error, valueC] = Value::Cast<T>(value);
	if (error)
		return { move(error), value };
	stack.emplace_back(name, valueC);
	return { pCompilerError(CompilerError::NoError), valueC };
}
tuple<pCompilerError, Value> SymTable::Assign(const std::string &name, Value value)
{
	for (auto it = stack.rbegin(); it != stack.rend(); it++)
		if (it->name == name)
			return it->value.Assign(value);
	return { CompilerError::New("SymTable::Assign", name + " is not defined."), value };
}
tuple<pCompilerError, Value> SymTable::Get(const std::string &name) const
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
		break;
	case DOUBLE:
		out << vDouble;
		break;
	case BOOL:
		if (vBool == true)
			out << "true";
		else
			out << "false";
		break;
	}
}
void Value::PrintType(std::ostream &out) const
{
	switch (type)
	{
	case INT:
		out << "int";
		break;
	case DOUBLE:
		out << "double";
		break;
	case BOOL:
		out << "bool";
		break;
	}
}
template<typename T> Value Value::Create(T value)
{
	static_assert(VALID_T(T), "Value::Create: invalid type used to initialize Value object.");
	return value;
}
template<typename T> tuple<pCompilerError, Value> Value::Cast(Value value)
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
tuple<pCompilerError, Value> Value::Assign(Value value)
{
	switch (type)
	{
	case INT:
		if (value.type == BOOL)
			return { CompilerError::New("Value::Cast", "Object of type bool cannot be cast to type int.") , *this };
		vInt = (int)VALUE(value);
		break;
	case DOUBLE:
		if (value.type == BOOL)
			return { CompilerError::New("Value::Cast", "Object of type bool cannot be cast to type double."), *this };
		vDouble = (double)VALUE(value);
		break;
	case BOOL:
		vBool = (bool)VALUE(value);
		break;
	}
	return { pCompilerError(CompilerError::NoError), *this };
}
tuple<pCompilerError, Value> Value::operator+(Value rhs) const
{
	if (type == BOOL || rhs.type == BOOL)
		return { CompilerError::New("Value::operator+", "No .+. operator defined for type bool."), *this };
	return { pCompilerError(CompilerError::NoError), Value(VALUE(*this) + VALUE(rhs)) };
}
tuple<pCompilerError, Value> Value::operator-(Value rhs) const
{
	if (type == BOOL || rhs.type == BOOL)
		return { CompilerError::New("Value::operator-", "No .-. operator defined for type bool."), *this };
	return { pCompilerError(CompilerError::NoError), Value(VALUE(*this) - VALUE(rhs)) };
}
tuple<pCompilerError, Value> Value::operator*(Value rhs) const
{
	if (type == BOOL || rhs.type == BOOL)
		return { CompilerError::New("Value::operator*", "No .*. operator defined for type bool."), *this };
	return { pCompilerError(CompilerError::NoError), Value(VALUE(*this) * VALUE(rhs)) };
}
tuple<pCompilerError, Value> Value::operator/(Value rhs) const
{
	if (type == BOOL || rhs.type == BOOL)
		return { CompilerError::New("Value::operator/", "No ./. operator defined for type bool."), *this };
	return { pCompilerError(CompilerError::NoError), Value(VALUE(*this) / VALUE(rhs)) };
}
tuple<pCompilerError, Value> Value::operator-() const
{
	if (type == BOOL)
		return { CompilerError::New("Value::operator-", "No -. operator defined for type bool."), *this };
	return { pCompilerError(CompilerError::NoError), Value(-VALUE(*this)) };
}
tuple<pCompilerError, Value> Value::operator==(Value rhs) const
{
	if ((type == BOOL) != (rhs.type == BOOL))
		return { CompilerError::New("Value::operator==", "No .==. operator defined for types bool and numeric."), *this };
	return { pCompilerError(CompilerError::NoError), Value(VALUE(*this) == VALUE(rhs)) };
}
tuple<pCompilerError, Value> Value::operator!=(Value rhs) const
{
	if ((type == BOOL) != (rhs.type == BOOL))
		return { CompilerError::New("Value::operator!=", "No .!=. operator defined for types bool and numeric."), *this };
	return { pCompilerError(CompilerError::NoError), Value(VALUE(*this) != VALUE(rhs)) };
}
tuple<pCompilerError, Value> Value::operator<(Value rhs) const
{
	if ((type == BOOL) != (rhs.type == BOOL))
		return { CompilerError::New("Value::operator<", "No .<. operator defined for types bool and numeric."), *this };
	return { pCompilerError(CompilerError::NoError), Value(VALUE(*this) < VALUE(rhs)) };
}
tuple<pCompilerError, Value> Value::operator>(Value rhs) const
{
	if ((type == BOOL) != (rhs.type == BOOL))
		return { CompilerError::New("Value::operator>", "No .>. operator defined for types bool and numeric."), *this };
	return { pCompilerError(CompilerError::NoError), Value(VALUE(*this) > VALUE(rhs)) };
}
tuple<pCompilerError, Value> Value::operator<=(Value rhs) const
{
	if ((type == BOOL) != (rhs.type == BOOL))
		return { CompilerError::New("Value::operator<=", "No .<=. operator defined for types bool and numeric."), *this };
	return { pCompilerError(CompilerError::NoError), Value(VALUE(*this) <= VALUE(rhs)) };
}
tuple<pCompilerError, Value> Value::operator>=(Value rhs) const
{
	if ((type == BOOL) != (rhs.type == BOOL))
		return { CompilerError::New("Value::operator>=", "No .>=. operator defined for types bool and numeric."), *this };
	return { pCompilerError(CompilerError::NoError), Value(VALUE(*this) >= VALUE(rhs)) };
}
tuple<pCompilerError, bool> Value::IsTrue() const
{
	auto[error, value] = Cast<bool>(*this);
	if (error)
		return { move(error), false };
	return { pCompilerError(CompilerError::NoError), value.vBool };
}