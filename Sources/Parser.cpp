#include "SyntaxTree.h"

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
	case 4:
		stack.push(23);
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
	case 23:
		stack.push(13);
		break;
	case 69:
		stack.push(76);
		break;
	case 77:
		stack.push(78);
		break;
	default:
		err = { "Stat2::Process", "Syntax Error!" };
		return false;
	}
	return true;
}
bool ValueExp::Process(Stack &stack, SymStack &symStack, Parser::Error &err)
{
	switch (stack.top())
	{
	case 1:
	case 23:
	case 69:
	case 77:
		stack.push(14);
		break;
	case 17:
		stack.push(43);
		break;
	default:
		err = { "ValueExp::Process", "Syntax Error!" };
		return false;
	}
	return true;
}
bool AssignExp::Process(Stack &stack, SymStack &symStack, Parser::Error &err)
{
	switch (stack.top())
	{
	case 1:
	case 17:
	case 23:
	case 69:
	case 77:
		stack.push(15);
		break;
	case 25:
		stack.push(51);
		break;
	case 50:
		stack.push(73);
		break;
	case 53:
		stack.push(74);
		break;
	case 55:
		stack.push(75);
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
	case 1:
	case 17:
	case 23:
	case 25:
	case 50:
	case 53:
	case 55:
	case 69:
	case 77:
		stack.push(16);
		break;
	case 3:
		stack.push(22);
		break;
	case 9:
		stack.push(28);
		break;
	case 30:
		stack.push(56);
		break;
	case 31:
		stack.push(57);
		break;
	case 32:
		stack.push(58);
		break;
	case 33:
		stack.push(59);
		break;
	case 34:
		stack.push(60);
		break;
	case 35:
		stack.push(61);
		break;
	case 36:
		stack.push(62);
		break;
	case 37:
		stack.push(63);
		break;
	case 38:
		stack.push(64);
		break;
	case 39:
		stack.push(65);
		break;
	case 44:
		stack.push(70);
		break;
	case 45:
		stack.push(71);
		break;
	case 46:
		stack.push(72);
		break;
	default:
		err = { "Exp::Process", "Syntax Error!" };
		return false;
	}
	return true;
}
bool If::Process(Stack &stack, SymStack &symStack, Parser::Error &err) const
{
	switch (stack.top())
	{
	case 0:
	case 4:
		symStack.emplace(new Stat1_End());
		return Stat1::Process(stack, symStack, err) && Process(stack, symStack, err);
	case 1:
	case 23:
	case 69:
	case 77:
		stack.push(2);
		break;
	case 13:
	{
		stack.pop();
		stack.pop();
		pStat2 sym2 = pCast<Stat2>(move(symStack.top()));
		symStack.pop();
		pStat1 sym1 = pCast<Stat1>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat1_Node(move(sym1), move(sym2)));
		return Stat1::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 29:
	{
		stack.pop();
		stack.pop();
		pTerm sym2 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pValueExp sym1 = pCast<ValueExp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat2_Value(move(sym1), move(sym2)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 48:
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
		symStack.emplace(new Stat2_Scope(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 49:
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
		symStack.emplace(new Stat2_DeclInt(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 52:
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
		symStack.emplace(new Stat2_DeclDouble(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 54:
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
		symStack.emplace(new Stat2_DeclBool(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 76:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pStat2 sym5 = pCast<Stat2>(move(symStack.top()));
		symStack.pop();
		pCloseP sym4 = pCast<CloseP>(move(symStack.top()));
		symStack.pop();
		pValueExp sym3 = pCast<ValueExp>(move(symStack.top()));
		symStack.pop();
		pOpenP sym2 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		pIf sym1 = pCast<If>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat2_If(move(sym1), move(sym2), move(sym3), move(sym4), move(sym5)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 78:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pStat2 sym7 = pCast<Stat2>(move(symStack.top()));
		symStack.pop();
		pElse sym6 = pCast<Else>(move(symStack.top()));
		symStack.pop();
		pStat2 sym5 = pCast<Stat2>(move(symStack.top()));
		symStack.pop();
		pCloseP sym4 = pCast<CloseP>(move(symStack.top()));
		symStack.pop();
		pValueExp sym3 = pCast<ValueExp>(move(symStack.top()));
		symStack.pop();
		pOpenP sym2 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		pIf sym1 = pCast<If>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat2_IfElse(move(sym1), move(sym2), move(sym3), move(sym4), move(sym5), move(sym6), move(sym7)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	default:
		err = { "If::Process", "Syntax Error!" };
		return false;
	}
	return true;
}
bool OpenP::Process(Stack &stack, SymStack &symStack, Parser::Error &err) const
{
	switch (stack.top())
	{
	case 0:
	case 4:
		symStack.emplace(new Stat1_End());
		return Stat1::Process(stack, symStack, err) && Process(stack, symStack, err);
	case 1:
	case 3:
	case 9:
	case 17:
	case 23:
	case 25:
	case 30:
	case 31:
	case 32:
	case 33:
	case 34:
	case 35:
	case 36:
	case 37:
	case 38:
	case 39:
	case 44:
	case 45:
	case 46:
	case 50:
	case 53:
	case 55:
	case 69:
	case 77:
		stack.push(3);
		break;
	case 2:
		stack.push(17);
		break;
	case 13:
	{
		stack.pop();
		stack.pop();
		pStat2 sym2 = pCast<Stat2>(move(symStack.top()));
		symStack.pop();
		pStat1 sym1 = pCast<Stat1>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat1_Node(move(sym1), move(sym2)));
		return Stat1::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 29:
	{
		stack.pop();
		stack.pop();
		pTerm sym2 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pValueExp sym1 = pCast<ValueExp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat2_Value(move(sym1), move(sym2)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 48:
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
		symStack.emplace(new Stat2_Scope(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 49:
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
		symStack.emplace(new Stat2_DeclInt(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 52:
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
		symStack.emplace(new Stat2_DeclDouble(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 54:
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
		symStack.emplace(new Stat2_DeclBool(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 76:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pStat2 sym5 = pCast<Stat2>(move(symStack.top()));
		symStack.pop();
		pCloseP sym4 = pCast<CloseP>(move(symStack.top()));
		symStack.pop();
		pValueExp sym3 = pCast<ValueExp>(move(symStack.top()));
		symStack.pop();
		pOpenP sym2 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		pIf sym1 = pCast<If>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat2_If(move(sym1), move(sym2), move(sym3), move(sym4), move(sym5)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 78:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pStat2 sym7 = pCast<Stat2>(move(symStack.top()));
		symStack.pop();
		pElse sym6 = pCast<Else>(move(symStack.top()));
		symStack.pop();
		pStat2 sym5 = pCast<Stat2>(move(symStack.top()));
		symStack.pop();
		pCloseP sym4 = pCast<CloseP>(move(symStack.top()));
		symStack.pop();
		pValueExp sym3 = pCast<ValueExp>(move(symStack.top()));
		symStack.pop();
		pOpenP sym2 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		pIf sym1 = pCast<If>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat2_IfElse(move(sym1), move(sym2), move(sym3), move(sym4), move(sym5), move(sym6), move(sym7)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
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
	case 6:
	case 19:
	{
		stack.pop();
		pName sym1 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_Variable(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 10:
	{
		stack.pop();
		pIntL sym1 = pCast<IntL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_LiteralInt(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 11:
	{
		stack.pop();
		pDoubleL sym1 = pCast<DoubleL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_LiteralDouble(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 12:
	{
		stack.pop();
		pBoolL sym1 = pCast<BoolL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_LiteralBool(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 15:
	{
		stack.pop();
		pAssignExp sym1 = pCast<AssignExp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new ValueExp_Assign(move(sym1)));
		return ValueExp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 16:
	{
		stack.pop();
		pExp sym1 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new AssignExp_Exp(move(sym1)));
		return AssignExp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 18:
		stack.push(44);
		break;
	case 20:
		stack.push(45);
		break;
	case 21:
		stack.push(46);
		break;
	case 22:
		stack.push(47);
		break;
	case 28:
	{
		stack.pop();
		stack.pop();
		pExp sym2 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pSub sym1 = pCast<Sub>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_Negate(move(sym1), move(sym2)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 43:
		stack.push(69);
		break;
	case 47:
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
		symStack.emplace(new Exp_Prec(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 51:
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
		symStack.emplace(new AssignExp_Chain(move(sym1), move(sym2), move(sym3)));
		return AssignExp::Process(stack, symStack, err) && Process(stack, symStack, err);
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
		symStack.emplace(new Exp_Sub(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 57:
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
		symStack.emplace(new Exp_Add(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 58:
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
		symStack.emplace(new Exp_Mult(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 59:
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
		symStack.emplace(new Exp_Div(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 60:
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
		symStack.emplace(new Exp_Greater(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 61:
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
		symStack.emplace(new Exp_Less(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 62:
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
		symStack.emplace(new Exp_GreaterEqual(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 63:
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
		symStack.emplace(new Exp_LessEqual(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 64:
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
		symStack.emplace(new Exp_Equal(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 65:
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
		symStack.emplace(new Exp_NotEqual(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 70:
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
		symStack.emplace(new Exp_CastInt(move(sym1), move(sym2), move(sym3), move(sym4)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 71:
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
		symStack.emplace(new Exp_CastDouble(move(sym1), move(sym2), move(sym3), move(sym4)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 72:
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
		symStack.emplace(new Exp_CastBool(move(sym1), move(sym2), move(sym3), move(sym4)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 73:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pAssignExp sym4 = pCast<AssignExp>(move(symStack.top()));
		symStack.pop();
		pAssign sym3 = pCast<Assign>(move(symStack.top()));
		symStack.pop();
		pName sym2 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		pIntT sym1 = pCast<IntT>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new ValueExp_InitInt(move(sym1), move(sym2), move(sym3), move(sym4)));
		return ValueExp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 74:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pAssignExp sym4 = pCast<AssignExp>(move(symStack.top()));
		symStack.pop();
		pAssign sym3 = pCast<Assign>(move(symStack.top()));
		symStack.pop();
		pName sym2 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		pDoubleT sym1 = pCast<DoubleT>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new ValueExp_InitDouble(move(sym1), move(sym2), move(sym3), move(sym4)));
		return ValueExp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 75:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pAssignExp sym4 = pCast<AssignExp>(move(symStack.top()));
		symStack.pop();
		pAssign sym3 = pCast<Assign>(move(symStack.top()));
		symStack.pop();
		pName sym2 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		pBoolT sym1 = pCast<BoolT>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new ValueExp_InitBool(move(sym1), move(sym2), move(sym3), move(sym4)));
		return ValueExp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	default:
		err = { "CloseP::Process", "Syntax Error!" };
		return false;
	}
	return true;
}
bool Else::Process(Stack &stack, SymStack &symStack, Parser::Error &err) const
{
	switch (stack.top())
	{
	case 29:
	{
		stack.pop();
		stack.pop();
		pTerm sym2 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pValueExp sym1 = pCast<ValueExp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat2_Value(move(sym1), move(sym2)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 48:
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
		symStack.emplace(new Stat2_Scope(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 49:
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
		symStack.emplace(new Stat2_DeclInt(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 52:
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
		symStack.emplace(new Stat2_DeclDouble(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 54:
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
		symStack.emplace(new Stat2_DeclBool(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 76:
		stack.push(77);
		break;
	case 78:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pStat2 sym7 = pCast<Stat2>(move(symStack.top()));
		symStack.pop();
		pElse sym6 = pCast<Else>(move(symStack.top()));
		symStack.pop();
		pStat2 sym5 = pCast<Stat2>(move(symStack.top()));
		symStack.pop();
		pCloseP sym4 = pCast<CloseP>(move(symStack.top()));
		symStack.pop();
		pValueExp sym3 = pCast<ValueExp>(move(symStack.top()));
		symStack.pop();
		pOpenP sym2 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		pIf sym1 = pCast<If>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat2_IfElse(move(sym1), move(sym2), move(sym3), move(sym4), move(sym5), move(sym6), move(sym7)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	default:
		err = { "Else::Process", "Syntax Error!" };
		return false;
	}
	return true;
}
bool OpenB::Process(Stack &stack, SymStack &symStack, Parser::Error &err) const
{
	switch (stack.top())
	{
	case 0:
	case 4:
		symStack.emplace(new Stat1_End());
		return Stat1::Process(stack, symStack, err) && Process(stack, symStack, err);
	case 1:
	case 23:
	case 69:
	case 77:
		stack.push(4);
		break;
	case 13:
	{
		stack.pop();
		stack.pop();
		pStat2 sym2 = pCast<Stat2>(move(symStack.top()));
		symStack.pop();
		pStat1 sym1 = pCast<Stat1>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat1_Node(move(sym1), move(sym2)));
		return Stat1::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 29:
	{
		stack.pop();
		stack.pop();
		pTerm sym2 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pValueExp sym1 = pCast<ValueExp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat2_Value(move(sym1), move(sym2)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 48:
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
		symStack.emplace(new Stat2_Scope(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 49:
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
		symStack.emplace(new Stat2_DeclInt(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 52:
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
		symStack.emplace(new Stat2_DeclDouble(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 54:
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
		symStack.emplace(new Stat2_DeclBool(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 76:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pStat2 sym5 = pCast<Stat2>(move(symStack.top()));
		symStack.pop();
		pCloseP sym4 = pCast<CloseP>(move(symStack.top()));
		symStack.pop();
		pValueExp sym3 = pCast<ValueExp>(move(symStack.top()));
		symStack.pop();
		pOpenP sym2 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		pIf sym1 = pCast<If>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat2_If(move(sym1), move(sym2), move(sym3), move(sym4), move(sym5)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 78:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pStat2 sym7 = pCast<Stat2>(move(symStack.top()));
		symStack.pop();
		pElse sym6 = pCast<Else>(move(symStack.top()));
		symStack.pop();
		pStat2 sym5 = pCast<Stat2>(move(symStack.top()));
		symStack.pop();
		pCloseP sym4 = pCast<CloseP>(move(symStack.top()));
		symStack.pop();
		pValueExp sym3 = pCast<ValueExp>(move(symStack.top()));
		symStack.pop();
		pOpenP sym2 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		pIf sym1 = pCast<If>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat2_IfElse(move(sym1), move(sym2), move(sym3), move(sym4), move(sym5), move(sym6), move(sym7)));
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
	case 4:
		symStack.emplace(new Stat1_End());
		return Stat1::Process(stack, symStack, err) && Process(stack, symStack, err);
	case 13:
	{
		stack.pop();
		stack.pop();
		pStat2 sym2 = pCast<Stat2>(move(symStack.top()));
		symStack.pop();
		pStat1 sym1 = pCast<Stat1>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat1_Node(move(sym1), move(sym2)));
		return Stat1::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 23:
		stack.push(48);
		break;
	case 29:
	{
		stack.pop();
		stack.pop();
		pTerm sym2 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pValueExp sym1 = pCast<ValueExp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat2_Value(move(sym1), move(sym2)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 48:
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
		symStack.emplace(new Stat2_Scope(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 49:
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
		symStack.emplace(new Stat2_DeclInt(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 52:
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
		symStack.emplace(new Stat2_DeclDouble(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 54:
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
		symStack.emplace(new Stat2_DeclBool(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 76:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pStat2 sym5 = pCast<Stat2>(move(symStack.top()));
		symStack.pop();
		pCloseP sym4 = pCast<CloseP>(move(symStack.top()));
		symStack.pop();
		pValueExp sym3 = pCast<ValueExp>(move(symStack.top()));
		symStack.pop();
		pOpenP sym2 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		pIf sym1 = pCast<If>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat2_If(move(sym1), move(sym2), move(sym3), move(sym4), move(sym5)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 78:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pStat2 sym7 = pCast<Stat2>(move(symStack.top()));
		symStack.pop();
		pElse sym6 = pCast<Else>(move(symStack.top()));
		symStack.pop();
		pStat2 sym5 = pCast<Stat2>(move(symStack.top()));
		symStack.pop();
		pCloseP sym4 = pCast<CloseP>(move(symStack.top()));
		symStack.pop();
		pValueExp sym3 = pCast<ValueExp>(move(symStack.top()));
		symStack.pop();
		pOpenP sym2 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		pIf sym1 = pCast<If>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat2_IfElse(move(sym1), move(sym2), move(sym3), move(sym4), move(sym5), move(sym6), move(sym7)));
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
	case 4:
		symStack.emplace(new Stat1_End());
		return Stat1::Process(stack, symStack, err) && Process(stack, symStack, err);
	case 1:
	case 23:
	case 69:
	case 77:
		stack.push(5);
		break;
	case 3:
		stack.push(18);
		break;
	case 13:
	{
		stack.pop();
		stack.pop();
		pStat2 sym2 = pCast<Stat2>(move(symStack.top()));
		symStack.pop();
		pStat1 sym1 = pCast<Stat1>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat1_Node(move(sym1), move(sym2)));
		return Stat1::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 17:
		stack.push(40);
		break;
	case 29:
	{
		stack.pop();
		stack.pop();
		pTerm sym2 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pValueExp sym1 = pCast<ValueExp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat2_Value(move(sym1), move(sym2)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 48:
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
		symStack.emplace(new Stat2_Scope(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 49:
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
		symStack.emplace(new Stat2_DeclInt(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 52:
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
		symStack.emplace(new Stat2_DeclDouble(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 54:
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
		symStack.emplace(new Stat2_DeclBool(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 76:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pStat2 sym5 = pCast<Stat2>(move(symStack.top()));
		symStack.pop();
		pCloseP sym4 = pCast<CloseP>(move(symStack.top()));
		symStack.pop();
		pValueExp sym3 = pCast<ValueExp>(move(symStack.top()));
		symStack.pop();
		pOpenP sym2 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		pIf sym1 = pCast<If>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat2_If(move(sym1), move(sym2), move(sym3), move(sym4), move(sym5)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 78:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pStat2 sym7 = pCast<Stat2>(move(symStack.top()));
		symStack.pop();
		pElse sym6 = pCast<Else>(move(symStack.top()));
		symStack.pop();
		pStat2 sym5 = pCast<Stat2>(move(symStack.top()));
		symStack.pop();
		pCloseP sym4 = pCast<CloseP>(move(symStack.top()));
		symStack.pop();
		pValueExp sym3 = pCast<ValueExp>(move(symStack.top()));
		symStack.pop();
		pOpenP sym2 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		pIf sym1 = pCast<If>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat2_IfElse(move(sym1), move(sym2), move(sym3), move(sym4), move(sym5), move(sym6), move(sym7)));
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
	case 4:
		symStack.emplace(new Stat1_End());
		return Stat1::Process(stack, symStack, err) && Process(stack, symStack, err);
	case 1:
	case 17:
	case 23:
	case 25:
	case 50:
	case 53:
	case 55:
	case 69:
	case 77:
		stack.push(6);
		break;
	case 3:
	case 9:
	case 30:
	case 31:
	case 32:
	case 33:
	case 34:
	case 35:
	case 36:
	case 37:
	case 38:
	case 39:
	case 44:
	case 45:
	case 46:
		stack.push(19);
		break;
	case 5:
		stack.push(24);
		break;
	case 7:
		stack.push(26);
		break;
	case 8:
		stack.push(27);
		break;
	case 13:
	{
		stack.pop();
		stack.pop();
		pStat2 sym2 = pCast<Stat2>(move(symStack.top()));
		symStack.pop();
		pStat1 sym1 = pCast<Stat1>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat1_Node(move(sym1), move(sym2)));
		return Stat1::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 29:
	{
		stack.pop();
		stack.pop();
		pTerm sym2 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pValueExp sym1 = pCast<ValueExp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat2_Value(move(sym1), move(sym2)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 40:
		stack.push(66);
		break;
	case 41:
		stack.push(67);
		break;
	case 42:
		stack.push(68);
		break;
	case 48:
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
		symStack.emplace(new Stat2_Scope(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 49:
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
		symStack.emplace(new Stat2_DeclInt(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 52:
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
		symStack.emplace(new Stat2_DeclDouble(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 54:
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
		symStack.emplace(new Stat2_DeclBool(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 76:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pStat2 sym5 = pCast<Stat2>(move(symStack.top()));
		symStack.pop();
		pCloseP sym4 = pCast<CloseP>(move(symStack.top()));
		symStack.pop();
		pValueExp sym3 = pCast<ValueExp>(move(symStack.top()));
		symStack.pop();
		pOpenP sym2 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		pIf sym1 = pCast<If>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat2_If(move(sym1), move(sym2), move(sym3), move(sym4), move(sym5)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 78:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pStat2 sym7 = pCast<Stat2>(move(symStack.top()));
		symStack.pop();
		pElse sym6 = pCast<Else>(move(symStack.top()));
		symStack.pop();
		pStat2 sym5 = pCast<Stat2>(move(symStack.top()));
		symStack.pop();
		pCloseP sym4 = pCast<CloseP>(move(symStack.top()));
		symStack.pop();
		pValueExp sym3 = pCast<ValueExp>(move(symStack.top()));
		symStack.pop();
		pOpenP sym2 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		pIf sym1 = pCast<If>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat2_IfElse(move(sym1), move(sym2), move(sym3), move(sym4), move(sym5), move(sym6), move(sym7)));
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
	case 6:
	case 19:
	{
		stack.pop();
		pName sym1 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_Variable(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 10:
	{
		stack.pop();
		pIntL sym1 = pCast<IntL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_LiteralInt(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 11:
	{
		stack.pop();
		pDoubleL sym1 = pCast<DoubleL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_LiteralDouble(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 12:
	{
		stack.pop();
		pBoolL sym1 = pCast<BoolL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_LiteralBool(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 14:
		stack.push(29);
		break;
	case 15:
	{
		stack.pop();
		pAssignExp sym1 = pCast<AssignExp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new ValueExp_Assign(move(sym1)));
		return ValueExp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 16:
	{
		stack.pop();
		pExp sym1 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new AssignExp_Exp(move(sym1)));
		return AssignExp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 24:
		stack.push(49);
		break;
	case 26:
		stack.push(52);
		break;
	case 27:
		stack.push(54);
		break;
	case 28:
	{
		stack.pop();
		stack.pop();
		pExp sym2 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pSub sym1 = pCast<Sub>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_Negate(move(sym1), move(sym2)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 47:
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
		symStack.emplace(new Exp_Prec(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 51:
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
		symStack.emplace(new AssignExp_Chain(move(sym1), move(sym2), move(sym3)));
		return AssignExp::Process(stack, symStack, err) && Process(stack, symStack, err);
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
		symStack.emplace(new Exp_Sub(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 57:
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
		symStack.emplace(new Exp_Add(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 58:
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
		symStack.emplace(new Exp_Mult(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 59:
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
		symStack.emplace(new Exp_Div(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 60:
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
		symStack.emplace(new Exp_Greater(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 61:
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
		symStack.emplace(new Exp_Less(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 62:
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
		symStack.emplace(new Exp_GreaterEqual(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 63:
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
		symStack.emplace(new Exp_LessEqual(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 64:
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
		symStack.emplace(new Exp_Equal(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 65:
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
		symStack.emplace(new Exp_NotEqual(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 70:
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
		symStack.emplace(new Exp_CastInt(move(sym1), move(sym2), move(sym3), move(sym4)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 71:
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
		symStack.emplace(new Exp_CastDouble(move(sym1), move(sym2), move(sym3), move(sym4)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 72:
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
		symStack.emplace(new Exp_CastBool(move(sym1), move(sym2), move(sym3), move(sym4)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 73:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pAssignExp sym4 = pCast<AssignExp>(move(symStack.top()));
		symStack.pop();
		pAssign sym3 = pCast<Assign>(move(symStack.top()));
		symStack.pop();
		pName sym2 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		pIntT sym1 = pCast<IntT>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new ValueExp_InitInt(move(sym1), move(sym2), move(sym3), move(sym4)));
		return ValueExp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 74:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pAssignExp sym4 = pCast<AssignExp>(move(symStack.top()));
		symStack.pop();
		pAssign sym3 = pCast<Assign>(move(symStack.top()));
		symStack.pop();
		pName sym2 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		pDoubleT sym1 = pCast<DoubleT>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new ValueExp_InitDouble(move(sym1), move(sym2), move(sym3), move(sym4)));
		return ValueExp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 75:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pAssignExp sym4 = pCast<AssignExp>(move(symStack.top()));
		symStack.pop();
		pAssign sym3 = pCast<Assign>(move(symStack.top()));
		symStack.pop();
		pName sym2 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		pBoolT sym1 = pCast<BoolT>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new ValueExp_InitBool(move(sym1), move(sym2), move(sym3), move(sym4)));
		return ValueExp::Process(stack, symStack, err) && Process(stack, symStack, err);
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
	case 4:
		symStack.emplace(new Stat1_End());
		return Stat1::Process(stack, symStack, err) && Process(stack, symStack, err);
	case 1:
	case 23:
	case 69:
	case 77:
		stack.push(7);
		break;
	case 3:
		stack.push(20);
		break;
	case 13:
	{
		stack.pop();
		stack.pop();
		pStat2 sym2 = pCast<Stat2>(move(symStack.top()));
		symStack.pop();
		pStat1 sym1 = pCast<Stat1>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat1_Node(move(sym1), move(sym2)));
		return Stat1::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 17:
		stack.push(41);
		break;
	case 29:
	{
		stack.pop();
		stack.pop();
		pTerm sym2 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pValueExp sym1 = pCast<ValueExp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat2_Value(move(sym1), move(sym2)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 48:
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
		symStack.emplace(new Stat2_Scope(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 49:
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
		symStack.emplace(new Stat2_DeclInt(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 52:
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
		symStack.emplace(new Stat2_DeclDouble(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 54:
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
		symStack.emplace(new Stat2_DeclBool(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 76:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pStat2 sym5 = pCast<Stat2>(move(symStack.top()));
		symStack.pop();
		pCloseP sym4 = pCast<CloseP>(move(symStack.top()));
		symStack.pop();
		pValueExp sym3 = pCast<ValueExp>(move(symStack.top()));
		symStack.pop();
		pOpenP sym2 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		pIf sym1 = pCast<If>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat2_If(move(sym1), move(sym2), move(sym3), move(sym4), move(sym5)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 78:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pStat2 sym7 = pCast<Stat2>(move(symStack.top()));
		symStack.pop();
		pElse sym6 = pCast<Else>(move(symStack.top()));
		symStack.pop();
		pStat2 sym5 = pCast<Stat2>(move(symStack.top()));
		symStack.pop();
		pCloseP sym4 = pCast<CloseP>(move(symStack.top()));
		symStack.pop();
		pValueExp sym3 = pCast<ValueExp>(move(symStack.top()));
		symStack.pop();
		pOpenP sym2 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		pIf sym1 = pCast<If>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat2_IfElse(move(sym1), move(sym2), move(sym3), move(sym4), move(sym5), move(sym6), move(sym7)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	default:
		err = { "DoubleT::Process", "Syntax Error!" };
		return false;
	}
	return true;
}
bool BoolT::Process(Stack &stack, SymStack &symStack, Parser::Error &err) const
{
	switch (stack.top())
	{
	case 0:
	case 4:
		symStack.emplace(new Stat1_End());
		return Stat1::Process(stack, symStack, err) && Process(stack, symStack, err);
	case 1:
	case 23:
	case 69:
	case 77:
		stack.push(8);
		break;
	case 3:
		stack.push(21);
		break;
	case 13:
	{
		stack.pop();
		stack.pop();
		pStat2 sym2 = pCast<Stat2>(move(symStack.top()));
		symStack.pop();
		pStat1 sym1 = pCast<Stat1>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat1_Node(move(sym1), move(sym2)));
		return Stat1::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 17:
		stack.push(42);
		break;
	case 29:
	{
		stack.pop();
		stack.pop();
		pTerm sym2 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pValueExp sym1 = pCast<ValueExp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat2_Value(move(sym1), move(sym2)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 48:
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
		symStack.emplace(new Stat2_Scope(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 49:
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
		symStack.emplace(new Stat2_DeclInt(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 52:
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
		symStack.emplace(new Stat2_DeclDouble(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 54:
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
		symStack.emplace(new Stat2_DeclBool(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 76:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pStat2 sym5 = pCast<Stat2>(move(symStack.top()));
		symStack.pop();
		pCloseP sym4 = pCast<CloseP>(move(symStack.top()));
		symStack.pop();
		pValueExp sym3 = pCast<ValueExp>(move(symStack.top()));
		symStack.pop();
		pOpenP sym2 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		pIf sym1 = pCast<If>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat2_If(move(sym1), move(sym2), move(sym3), move(sym4), move(sym5)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 78:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pStat2 sym7 = pCast<Stat2>(move(symStack.top()));
		symStack.pop();
		pElse sym6 = pCast<Else>(move(symStack.top()));
		symStack.pop();
		pStat2 sym5 = pCast<Stat2>(move(symStack.top()));
		symStack.pop();
		pCloseP sym4 = pCast<CloseP>(move(symStack.top()));
		symStack.pop();
		pValueExp sym3 = pCast<ValueExp>(move(symStack.top()));
		symStack.pop();
		pOpenP sym2 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		pIf sym1 = pCast<If>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat2_IfElse(move(sym1), move(sym2), move(sym3), move(sym4), move(sym5), move(sym6), move(sym7)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	default:
		err = { "BoolT::Process", "Syntax Error!" };
		return false;
	}
	return true;
}
bool Assign::Process(Stack &stack, SymStack &symStack, Parser::Error &err) const
{
	switch (stack.top())
	{
	case 6:
		stack.push(25);
		break;
	case 24:
	case 66:
		stack.push(50);
		break;
	case 26:
	case 67:
		stack.push(53);
		break;
	case 27:
	case 68:
		stack.push(55);
		break;
	default:
		err = { "Assign::Process", "Syntax Error!" };
		return false;
	}
	return true;
}
bool Sub::Process(Stack &stack, SymStack &symStack, Parser::Error &err) const
{
	switch (stack.top())
	{
	case 0:
	case 4:
		symStack.emplace(new Stat1_End());
		return Stat1::Process(stack, symStack, err) && Process(stack, symStack, err);
	case 1:
	case 3:
	case 9:
	case 17:
	case 23:
	case 25:
	case 30:
	case 31:
	case 32:
	case 33:
	case 34:
	case 35:
	case 36:
	case 37:
	case 38:
	case 39:
	case 44:
	case 45:
	case 46:
	case 50:
	case 53:
	case 55:
	case 69:
	case 77:
		stack.push(9);
		break;
	case 6:
	case 19:
	{
		stack.pop();
		pName sym1 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_Variable(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 10:
	{
		stack.pop();
		pIntL sym1 = pCast<IntL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_LiteralInt(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 11:
	{
		stack.pop();
		pDoubleL sym1 = pCast<DoubleL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_LiteralDouble(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 12:
	{
		stack.pop();
		pBoolL sym1 = pCast<BoolL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_LiteralBool(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 13:
	{
		stack.pop();
		stack.pop();
		pStat2 sym2 = pCast<Stat2>(move(symStack.top()));
		symStack.pop();
		pStat1 sym1 = pCast<Stat1>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat1_Node(move(sym1), move(sym2)));
		return Stat1::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 16:
	case 22:
	case 60:
	case 61:
	case 62:
	case 63:
	case 64:
	case 65:
		stack.push(30);
		break;
	case 28:
	{
		stack.pop();
		stack.pop();
		pExp sym2 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pSub sym1 = pCast<Sub>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_Negate(move(sym1), move(sym2)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 29:
	{
		stack.pop();
		stack.pop();
		pTerm sym2 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pValueExp sym1 = pCast<ValueExp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat2_Value(move(sym1), move(sym2)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 47:
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
		symStack.emplace(new Exp_Prec(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 48:
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
		symStack.emplace(new Stat2_Scope(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 49:
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
		symStack.emplace(new Stat2_DeclInt(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 52:
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
		symStack.emplace(new Stat2_DeclDouble(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 54:
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
		symStack.emplace(new Stat2_DeclBool(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
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
		symStack.emplace(new Exp_Sub(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 57:
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
		symStack.emplace(new Exp_Add(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 58:
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
		symStack.emplace(new Exp_Mult(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 59:
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
		symStack.emplace(new Exp_Div(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 70:
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
		symStack.emplace(new Exp_CastInt(move(sym1), move(sym2), move(sym3), move(sym4)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 71:
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
		symStack.emplace(new Exp_CastDouble(move(sym1), move(sym2), move(sym3), move(sym4)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 72:
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
		symStack.emplace(new Exp_CastBool(move(sym1), move(sym2), move(sym3), move(sym4)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 76:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pStat2 sym5 = pCast<Stat2>(move(symStack.top()));
		symStack.pop();
		pCloseP sym4 = pCast<CloseP>(move(symStack.top()));
		symStack.pop();
		pValueExp sym3 = pCast<ValueExp>(move(symStack.top()));
		symStack.pop();
		pOpenP sym2 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		pIf sym1 = pCast<If>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat2_If(move(sym1), move(sym2), move(sym3), move(sym4), move(sym5)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 78:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pStat2 sym7 = pCast<Stat2>(move(symStack.top()));
		symStack.pop();
		pElse sym6 = pCast<Else>(move(symStack.top()));
		symStack.pop();
		pStat2 sym5 = pCast<Stat2>(move(symStack.top()));
		symStack.pop();
		pCloseP sym4 = pCast<CloseP>(move(symStack.top()));
		symStack.pop();
		pValueExp sym3 = pCast<ValueExp>(move(symStack.top()));
		symStack.pop();
		pOpenP sym2 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		pIf sym1 = pCast<If>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat2_IfElse(move(sym1), move(sym2), move(sym3), move(sym4), move(sym5), move(sym6), move(sym7)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	default:
		err = { "Sub::Process", "Syntax Error!" };
		return false;
	}
	return true;
}
bool Add::Process(Stack &stack, SymStack &symStack, Parser::Error &err) const
{
	switch (stack.top())
	{
	case 6:
	case 19:
	{
		stack.pop();
		pName sym1 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_Variable(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 10:
	{
		stack.pop();
		pIntL sym1 = pCast<IntL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_LiteralInt(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 11:
	{
		stack.pop();
		pDoubleL sym1 = pCast<DoubleL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_LiteralDouble(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 12:
	{
		stack.pop();
		pBoolL sym1 = pCast<BoolL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_LiteralBool(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 16:
	case 22:
	case 60:
	case 61:
	case 62:
	case 63:
	case 64:
	case 65:
		stack.push(31);
		break;
	case 28:
	{
		stack.pop();
		stack.pop();
		pExp sym2 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pSub sym1 = pCast<Sub>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_Negate(move(sym1), move(sym2)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 47:
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
		symStack.emplace(new Exp_Prec(move(sym1), move(sym2), move(sym3)));
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
		symStack.emplace(new Exp_Sub(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 57:
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
		symStack.emplace(new Exp_Add(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 58:
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
		symStack.emplace(new Exp_Mult(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 59:
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
		symStack.emplace(new Exp_Div(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 70:
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
		symStack.emplace(new Exp_CastInt(move(sym1), move(sym2), move(sym3), move(sym4)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 71:
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
		symStack.emplace(new Exp_CastDouble(move(sym1), move(sym2), move(sym3), move(sym4)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 72:
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
		symStack.emplace(new Exp_CastBool(move(sym1), move(sym2), move(sym3), move(sym4)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	default:
		err = { "Add::Process", "Syntax Error!" };
		return false;
	}
	return true;
}
bool Mult::Process(Stack &stack, SymStack &symStack, Parser::Error &err) const
{
	switch (stack.top())
	{
	case 6:
	case 19:
	{
		stack.pop();
		pName sym1 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_Variable(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 10:
	{
		stack.pop();
		pIntL sym1 = pCast<IntL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_LiteralInt(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 11:
	{
		stack.pop();
		pDoubleL sym1 = pCast<DoubleL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_LiteralDouble(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 12:
	{
		stack.pop();
		pBoolL sym1 = pCast<BoolL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_LiteralBool(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 16:
	case 22:
	case 56:
	case 57:
	case 60:
	case 61:
	case 62:
	case 63:
	case 64:
	case 65:
		stack.push(32);
		break;
	case 28:
	{
		stack.pop();
		stack.pop();
		pExp sym2 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pSub sym1 = pCast<Sub>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_Negate(move(sym1), move(sym2)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 47:
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
		symStack.emplace(new Exp_Prec(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 58:
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
		symStack.emplace(new Exp_Mult(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 59:
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
		symStack.emplace(new Exp_Div(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 70:
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
		symStack.emplace(new Exp_CastInt(move(sym1), move(sym2), move(sym3), move(sym4)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 71:
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
		symStack.emplace(new Exp_CastDouble(move(sym1), move(sym2), move(sym3), move(sym4)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 72:
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
		symStack.emplace(new Exp_CastBool(move(sym1), move(sym2), move(sym3), move(sym4)));
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
	case 6:
	case 19:
	{
		stack.pop();
		pName sym1 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_Variable(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 10:
	{
		stack.pop();
		pIntL sym1 = pCast<IntL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_LiteralInt(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 11:
	{
		stack.pop();
		pDoubleL sym1 = pCast<DoubleL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_LiteralDouble(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 12:
	{
		stack.pop();
		pBoolL sym1 = pCast<BoolL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_LiteralBool(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 16:
	case 22:
	case 56:
	case 57:
	case 60:
	case 61:
	case 62:
	case 63:
	case 64:
	case 65:
		stack.push(33);
		break;
	case 28:
	{
		stack.pop();
		stack.pop();
		pExp sym2 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pSub sym1 = pCast<Sub>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_Negate(move(sym1), move(sym2)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 47:
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
		symStack.emplace(new Exp_Prec(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 58:
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
		symStack.emplace(new Exp_Mult(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 59:
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
		symStack.emplace(new Exp_Div(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 70:
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
		symStack.emplace(new Exp_CastInt(move(sym1), move(sym2), move(sym3), move(sym4)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 71:
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
		symStack.emplace(new Exp_CastDouble(move(sym1), move(sym2), move(sym3), move(sym4)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 72:
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
		symStack.emplace(new Exp_CastBool(move(sym1), move(sym2), move(sym3), move(sym4)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	default:
		err = { "Div::Process", "Syntax Error!" };
		return false;
	}
	return true;
}
bool Greater::Process(Stack &stack, SymStack &symStack, Parser::Error &err) const
{
	switch (stack.top())
	{
	case 6:
	case 19:
	{
		stack.pop();
		pName sym1 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_Variable(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 10:
	{
		stack.pop();
		pIntL sym1 = pCast<IntL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_LiteralInt(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 11:
	{
		stack.pop();
		pDoubleL sym1 = pCast<DoubleL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_LiteralDouble(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 12:
	{
		stack.pop();
		pBoolL sym1 = pCast<BoolL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_LiteralBool(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 16:
	case 22:
	case 64:
	case 65:
		stack.push(34);
		break;
	case 28:
	{
		stack.pop();
		stack.pop();
		pExp sym2 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pSub sym1 = pCast<Sub>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_Negate(move(sym1), move(sym2)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 47:
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
		symStack.emplace(new Exp_Prec(move(sym1), move(sym2), move(sym3)));
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
		symStack.emplace(new Exp_Sub(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 57:
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
		symStack.emplace(new Exp_Add(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 58:
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
		symStack.emplace(new Exp_Mult(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 59:
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
		symStack.emplace(new Exp_Div(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 60:
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
		symStack.emplace(new Exp_Greater(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 61:
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
		symStack.emplace(new Exp_Less(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 62:
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
		symStack.emplace(new Exp_GreaterEqual(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 63:
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
		symStack.emplace(new Exp_LessEqual(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 70:
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
		symStack.emplace(new Exp_CastInt(move(sym1), move(sym2), move(sym3), move(sym4)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 71:
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
		symStack.emplace(new Exp_CastDouble(move(sym1), move(sym2), move(sym3), move(sym4)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 72:
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
		symStack.emplace(new Exp_CastBool(move(sym1), move(sym2), move(sym3), move(sym4)));
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
	case 6:
	case 19:
	{
		stack.pop();
		pName sym1 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_Variable(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 10:
	{
		stack.pop();
		pIntL sym1 = pCast<IntL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_LiteralInt(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 11:
	{
		stack.pop();
		pDoubleL sym1 = pCast<DoubleL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_LiteralDouble(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 12:
	{
		stack.pop();
		pBoolL sym1 = pCast<BoolL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_LiteralBool(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 16:
	case 22:
	case 64:
	case 65:
		stack.push(35);
		break;
	case 28:
	{
		stack.pop();
		stack.pop();
		pExp sym2 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pSub sym1 = pCast<Sub>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_Negate(move(sym1), move(sym2)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 47:
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
		symStack.emplace(new Exp_Prec(move(sym1), move(sym2), move(sym3)));
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
		symStack.emplace(new Exp_Sub(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 57:
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
		symStack.emplace(new Exp_Add(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 58:
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
		symStack.emplace(new Exp_Mult(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 59:
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
		symStack.emplace(new Exp_Div(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 60:
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
		symStack.emplace(new Exp_Greater(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 61:
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
		symStack.emplace(new Exp_Less(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 62:
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
		symStack.emplace(new Exp_GreaterEqual(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 63:
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
		symStack.emplace(new Exp_LessEqual(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 70:
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
		symStack.emplace(new Exp_CastInt(move(sym1), move(sym2), move(sym3), move(sym4)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 71:
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
		symStack.emplace(new Exp_CastDouble(move(sym1), move(sym2), move(sym3), move(sym4)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 72:
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
		symStack.emplace(new Exp_CastBool(move(sym1), move(sym2), move(sym3), move(sym4)));
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
	case 6:
	case 19:
	{
		stack.pop();
		pName sym1 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_Variable(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 10:
	{
		stack.pop();
		pIntL sym1 = pCast<IntL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_LiteralInt(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 11:
	{
		stack.pop();
		pDoubleL sym1 = pCast<DoubleL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_LiteralDouble(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 12:
	{
		stack.pop();
		pBoolL sym1 = pCast<BoolL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_LiteralBool(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 16:
	case 22:
	case 64:
	case 65:
		stack.push(36);
		break;
	case 28:
	{
		stack.pop();
		stack.pop();
		pExp sym2 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pSub sym1 = pCast<Sub>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_Negate(move(sym1), move(sym2)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 47:
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
		symStack.emplace(new Exp_Prec(move(sym1), move(sym2), move(sym3)));
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
		symStack.emplace(new Exp_Sub(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 57:
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
		symStack.emplace(new Exp_Add(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 58:
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
		symStack.emplace(new Exp_Mult(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 59:
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
		symStack.emplace(new Exp_Div(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 60:
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
		symStack.emplace(new Exp_Greater(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 61:
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
		symStack.emplace(new Exp_Less(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 62:
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
		symStack.emplace(new Exp_GreaterEqual(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 63:
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
		symStack.emplace(new Exp_LessEqual(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 70:
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
		symStack.emplace(new Exp_CastInt(move(sym1), move(sym2), move(sym3), move(sym4)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 71:
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
		symStack.emplace(new Exp_CastDouble(move(sym1), move(sym2), move(sym3), move(sym4)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 72:
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
		symStack.emplace(new Exp_CastBool(move(sym1), move(sym2), move(sym3), move(sym4)));
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
	case 6:
	case 19:
	{
		stack.pop();
		pName sym1 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_Variable(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 10:
	{
		stack.pop();
		pIntL sym1 = pCast<IntL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_LiteralInt(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 11:
	{
		stack.pop();
		pDoubleL sym1 = pCast<DoubleL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_LiteralDouble(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 12:
	{
		stack.pop();
		pBoolL sym1 = pCast<BoolL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_LiteralBool(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 16:
	case 22:
	case 64:
	case 65:
		stack.push(37);
		break;
	case 28:
	{
		stack.pop();
		stack.pop();
		pExp sym2 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pSub sym1 = pCast<Sub>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_Negate(move(sym1), move(sym2)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 47:
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
		symStack.emplace(new Exp_Prec(move(sym1), move(sym2), move(sym3)));
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
		symStack.emplace(new Exp_Sub(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 57:
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
		symStack.emplace(new Exp_Add(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 58:
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
		symStack.emplace(new Exp_Mult(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 59:
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
		symStack.emplace(new Exp_Div(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 60:
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
		symStack.emplace(new Exp_Greater(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 61:
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
		symStack.emplace(new Exp_Less(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 62:
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
		symStack.emplace(new Exp_GreaterEqual(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 63:
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
		symStack.emplace(new Exp_LessEqual(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 70:
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
		symStack.emplace(new Exp_CastInt(move(sym1), move(sym2), move(sym3), move(sym4)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 71:
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
		symStack.emplace(new Exp_CastDouble(move(sym1), move(sym2), move(sym3), move(sym4)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 72:
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
		symStack.emplace(new Exp_CastBool(move(sym1), move(sym2), move(sym3), move(sym4)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	default:
		err = { "LessEqual::Process", "Syntax Error!" };
		return false;
	}
	return true;
}
bool Equal::Process(Stack &stack, SymStack &symStack, Parser::Error &err) const
{
	switch (stack.top())
	{
	case 6:
	case 19:
	{
		stack.pop();
		pName sym1 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_Variable(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 10:
	{
		stack.pop();
		pIntL sym1 = pCast<IntL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_LiteralInt(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 11:
	{
		stack.pop();
		pDoubleL sym1 = pCast<DoubleL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_LiteralDouble(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 12:
	{
		stack.pop();
		pBoolL sym1 = pCast<BoolL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_LiteralBool(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 16:
	case 22:
		stack.push(38);
		break;
	case 28:
	{
		stack.pop();
		stack.pop();
		pExp sym2 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pSub sym1 = pCast<Sub>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_Negate(move(sym1), move(sym2)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 47:
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
		symStack.emplace(new Exp_Prec(move(sym1), move(sym2), move(sym3)));
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
		symStack.emplace(new Exp_Sub(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 57:
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
		symStack.emplace(new Exp_Add(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 58:
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
		symStack.emplace(new Exp_Mult(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 59:
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
		symStack.emplace(new Exp_Div(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 60:
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
		symStack.emplace(new Exp_Greater(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 61:
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
		symStack.emplace(new Exp_Less(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 62:
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
		symStack.emplace(new Exp_GreaterEqual(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 63:
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
		symStack.emplace(new Exp_LessEqual(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 64:
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
		symStack.emplace(new Exp_Equal(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 65:
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
		symStack.emplace(new Exp_NotEqual(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 70:
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
		symStack.emplace(new Exp_CastInt(move(sym1), move(sym2), move(sym3), move(sym4)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 71:
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
		symStack.emplace(new Exp_CastDouble(move(sym1), move(sym2), move(sym3), move(sym4)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 72:
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
		symStack.emplace(new Exp_CastBool(move(sym1), move(sym2), move(sym3), move(sym4)));
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
	case 6:
	case 19:
	{
		stack.pop();
		pName sym1 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_Variable(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 10:
	{
		stack.pop();
		pIntL sym1 = pCast<IntL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_LiteralInt(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 11:
	{
		stack.pop();
		pDoubleL sym1 = pCast<DoubleL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_LiteralDouble(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 12:
	{
		stack.pop();
		pBoolL sym1 = pCast<BoolL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_LiteralBool(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 16:
	case 22:
		stack.push(39);
		break;
	case 28:
	{
		stack.pop();
		stack.pop();
		pExp sym2 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		pSub sym1 = pCast<Sub>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_Negate(move(sym1), move(sym2)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 47:
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
		symStack.emplace(new Exp_Prec(move(sym1), move(sym2), move(sym3)));
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
		symStack.emplace(new Exp_Sub(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 57:
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
		symStack.emplace(new Exp_Add(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 58:
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
		symStack.emplace(new Exp_Mult(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 59:
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
		symStack.emplace(new Exp_Div(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 60:
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
		symStack.emplace(new Exp_Greater(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 61:
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
		symStack.emplace(new Exp_Less(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 62:
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
		symStack.emplace(new Exp_GreaterEqual(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 63:
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
		symStack.emplace(new Exp_LessEqual(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 64:
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
		symStack.emplace(new Exp_Equal(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 65:
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
		symStack.emplace(new Exp_NotEqual(move(sym1), move(sym2), move(sym3)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 70:
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
		symStack.emplace(new Exp_CastInt(move(sym1), move(sym2), move(sym3), move(sym4)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 71:
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
		symStack.emplace(new Exp_CastDouble(move(sym1), move(sym2), move(sym3), move(sym4)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 72:
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
		symStack.emplace(new Exp_CastBool(move(sym1), move(sym2), move(sym3), move(sym4)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	default:
		err = { "NotEqual::Process", "Syntax Error!" };
		return false;
	}
	return true;
}
bool IntL::Process(Stack &stack, SymStack &symStack, Parser::Error &err) const
{
	switch (stack.top())
	{
	case 0:
	case 4:
		symStack.emplace(new Stat1_End());
		return Stat1::Process(stack, symStack, err) && Process(stack, symStack, err);
	case 1:
	case 3:
	case 9:
	case 17:
	case 23:
	case 25:
	case 30:
	case 31:
	case 32:
	case 33:
	case 34:
	case 35:
	case 36:
	case 37:
	case 38:
	case 39:
	case 44:
	case 45:
	case 46:
	case 50:
	case 53:
	case 55:
	case 69:
	case 77:
		stack.push(10);
		break;
	case 13:
	{
		stack.pop();
		stack.pop();
		pStat2 sym2 = pCast<Stat2>(move(symStack.top()));
		symStack.pop();
		pStat1 sym1 = pCast<Stat1>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat1_Node(move(sym1), move(sym2)));
		return Stat1::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 29:
	{
		stack.pop();
		stack.pop();
		pTerm sym2 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pValueExp sym1 = pCast<ValueExp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat2_Value(move(sym1), move(sym2)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 48:
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
		symStack.emplace(new Stat2_Scope(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 49:
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
		symStack.emplace(new Stat2_DeclInt(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 52:
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
		symStack.emplace(new Stat2_DeclDouble(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 54:
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
		symStack.emplace(new Stat2_DeclBool(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 76:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pStat2 sym5 = pCast<Stat2>(move(symStack.top()));
		symStack.pop();
		pCloseP sym4 = pCast<CloseP>(move(symStack.top()));
		symStack.pop();
		pValueExp sym3 = pCast<ValueExp>(move(symStack.top()));
		symStack.pop();
		pOpenP sym2 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		pIf sym1 = pCast<If>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat2_If(move(sym1), move(sym2), move(sym3), move(sym4), move(sym5)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 78:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pStat2 sym7 = pCast<Stat2>(move(symStack.top()));
		symStack.pop();
		pElse sym6 = pCast<Else>(move(symStack.top()));
		symStack.pop();
		pStat2 sym5 = pCast<Stat2>(move(symStack.top()));
		symStack.pop();
		pCloseP sym4 = pCast<CloseP>(move(symStack.top()));
		symStack.pop();
		pValueExp sym3 = pCast<ValueExp>(move(symStack.top()));
		symStack.pop();
		pOpenP sym2 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		pIf sym1 = pCast<If>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat2_IfElse(move(sym1), move(sym2), move(sym3), move(sym4), move(sym5), move(sym6), move(sym7)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
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
	case 0:
	case 4:
		symStack.emplace(new Stat1_End());
		return Stat1::Process(stack, symStack, err) && Process(stack, symStack, err);
	case 1:
	case 3:
	case 9:
	case 17:
	case 23:
	case 25:
	case 30:
	case 31:
	case 32:
	case 33:
	case 34:
	case 35:
	case 36:
	case 37:
	case 38:
	case 39:
	case 44:
	case 45:
	case 46:
	case 50:
	case 53:
	case 55:
	case 69:
	case 77:
		stack.push(11);
		break;
	case 13:
	{
		stack.pop();
		stack.pop();
		pStat2 sym2 = pCast<Stat2>(move(symStack.top()));
		symStack.pop();
		pStat1 sym1 = pCast<Stat1>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat1_Node(move(sym1), move(sym2)));
		return Stat1::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 29:
	{
		stack.pop();
		stack.pop();
		pTerm sym2 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pValueExp sym1 = pCast<ValueExp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat2_Value(move(sym1), move(sym2)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 48:
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
		symStack.emplace(new Stat2_Scope(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 49:
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
		symStack.emplace(new Stat2_DeclInt(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 52:
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
		symStack.emplace(new Stat2_DeclDouble(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 54:
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
		symStack.emplace(new Stat2_DeclBool(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 76:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pStat2 sym5 = pCast<Stat2>(move(symStack.top()));
		symStack.pop();
		pCloseP sym4 = pCast<CloseP>(move(symStack.top()));
		symStack.pop();
		pValueExp sym3 = pCast<ValueExp>(move(symStack.top()));
		symStack.pop();
		pOpenP sym2 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		pIf sym1 = pCast<If>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat2_If(move(sym1), move(sym2), move(sym3), move(sym4), move(sym5)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 78:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pStat2 sym7 = pCast<Stat2>(move(symStack.top()));
		symStack.pop();
		pElse sym6 = pCast<Else>(move(symStack.top()));
		symStack.pop();
		pStat2 sym5 = pCast<Stat2>(move(symStack.top()));
		symStack.pop();
		pCloseP sym4 = pCast<CloseP>(move(symStack.top()));
		symStack.pop();
		pValueExp sym3 = pCast<ValueExp>(move(symStack.top()));
		symStack.pop();
		pOpenP sym2 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		pIf sym1 = pCast<If>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat2_IfElse(move(sym1), move(sym2), move(sym3), move(sym4), move(sym5), move(sym6), move(sym7)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	default:
		err = { "DoubleL::Process", "Syntax Error!" };
		return false;
	}
	return true;
}
bool BoolL::Process(Stack &stack, SymStack &symStack, Parser::Error &err) const
{
	switch (stack.top())
	{
	case 0:
	case 4:
		symStack.emplace(new Stat1_End());
		return Stat1::Process(stack, symStack, err) && Process(stack, symStack, err);
	case 1:
	case 3:
	case 9:
	case 17:
	case 23:
	case 25:
	case 30:
	case 31:
	case 32:
	case 33:
	case 34:
	case 35:
	case 36:
	case 37:
	case 38:
	case 39:
	case 44:
	case 45:
	case 46:
	case 50:
	case 53:
	case 55:
	case 69:
	case 77:
		stack.push(12);
		break;
	case 13:
	{
		stack.pop();
		stack.pop();
		pStat2 sym2 = pCast<Stat2>(move(symStack.top()));
		symStack.pop();
		pStat1 sym1 = pCast<Stat1>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat1_Node(move(sym1), move(sym2)));
		return Stat1::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 29:
	{
		stack.pop();
		stack.pop();
		pTerm sym2 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pValueExp sym1 = pCast<ValueExp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat2_Value(move(sym1), move(sym2)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 48:
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
		symStack.emplace(new Stat2_Scope(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 49:
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
		symStack.emplace(new Stat2_DeclInt(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 52:
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
		symStack.emplace(new Stat2_DeclDouble(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 54:
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
		symStack.emplace(new Stat2_DeclBool(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 76:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pStat2 sym5 = pCast<Stat2>(move(symStack.top()));
		symStack.pop();
		pCloseP sym4 = pCast<CloseP>(move(symStack.top()));
		symStack.pop();
		pValueExp sym3 = pCast<ValueExp>(move(symStack.top()));
		symStack.pop();
		pOpenP sym2 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		pIf sym1 = pCast<If>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat2_If(move(sym1), move(sym2), move(sym3), move(sym4), move(sym5)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 78:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pStat2 sym7 = pCast<Stat2>(move(symStack.top()));
		symStack.pop();
		pElse sym6 = pCast<Else>(move(symStack.top()));
		symStack.pop();
		pStat2 sym5 = pCast<Stat2>(move(symStack.top()));
		symStack.pop();
		pCloseP sym4 = pCast<CloseP>(move(symStack.top()));
		symStack.pop();
		pValueExp sym3 = pCast<ValueExp>(move(symStack.top()));
		symStack.pop();
		pOpenP sym2 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		pIf sym1 = pCast<If>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat2_IfElse(move(sym1), move(sym2), move(sym3), move(sym4), move(sym5), move(sym6), move(sym7)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
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
	case 4:
		symStack.emplace(new Stat1_End());
		return Stat1::Process(stack, symStack, err) && Process(stack, symStack, err);
	case 1:
		break;
	case 13:
	{
		stack.pop();
		stack.pop();
		pStat2 sym2 = pCast<Stat2>(move(symStack.top()));
		symStack.pop();
		pStat1 sym1 = pCast<Stat1>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat1_Node(move(sym1), move(sym2)));
		return Stat1::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 29:
	{
		stack.pop();
		stack.pop();
		pTerm sym2 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pValueExp sym1 = pCast<ValueExp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat2_Value(move(sym1), move(sym2)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 48:
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
		symStack.emplace(new Stat2_Scope(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 49:
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
		symStack.emplace(new Stat2_DeclInt(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 52:
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
		symStack.emplace(new Stat2_DeclDouble(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 54:
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
		symStack.emplace(new Stat2_DeclBool(move(sym1), move(sym2), move(sym3)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 76:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pStat2 sym5 = pCast<Stat2>(move(symStack.top()));
		symStack.pop();
		pCloseP sym4 = pCast<CloseP>(move(symStack.top()));
		symStack.pop();
		pValueExp sym3 = pCast<ValueExp>(move(symStack.top()));
		symStack.pop();
		pOpenP sym2 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		pIf sym1 = pCast<If>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat2_If(move(sym1), move(sym2), move(sym3), move(sym4), move(sym5)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 78:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pStat2 sym7 = pCast<Stat2>(move(symStack.top()));
		symStack.pop();
		pElse sym6 = pCast<Else>(move(symStack.top()));
		symStack.pop();
		pStat2 sym5 = pCast<Stat2>(move(symStack.top()));
		symStack.pop();
		pCloseP sym4 = pCast<CloseP>(move(symStack.top()));
		symStack.pop();
		pValueExp sym3 = pCast<ValueExp>(move(symStack.top()));
		symStack.pop();
		pOpenP sym2 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		pIf sym1 = pCast<If>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat2_IfElse(move(sym1), move(sym2), move(sym3), move(sym4), move(sym5), move(sym6), move(sym7)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	default:
		err = { "End::Process", "Syntax Error!" };
		return false;
	}
	return true;
}