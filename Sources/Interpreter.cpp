#include "SyntaxTree.h"
#include <tuple>

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