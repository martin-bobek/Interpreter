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
		stack.push(14);
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
	case 14:
		stack.push(9);
		break;
	case 60:
		stack.push(79);
		break;
	case 71:
		stack.push(90);
		break;
	case 94:
		stack.push(95);
		break;
	default:
		err = { "Stat2::Process", "Syntax Error!" };
		return false;
	}
	return true;
}
bool Cond::Process(Stack &stack, SymStack &symStack, Parser::Error &err)
{
	switch (stack.top())
	{
	case 12:
		stack.push(33);
		break;
	case 13:
		stack.push(36);
		break;
	default:
		err = { "Cond::Process", "Syntax Error!" };
		return false;
	}
	return true;
}
bool ValueStat::Process(Stack &stack, SymStack &symStack, Parser::Error &err)
{
	switch (stack.top())
	{
	case 1:
	case 14:
	case 60:
	case 71:
	case 94:
		stack.push(10);
		break;
	case 12:
	case 13:
		stack.push(34);
		break;
	default:
		err = { "ValueStat::Process", "Syntax Error!" };
		return false;
	}
	return true;
}
bool ChainAssign::Process(Stack &stack, SymStack &symStack, Parser::Error &err)
{
	switch (stack.top())
	{
	case 16:
		stack.push(40);
		break;
	case 17:
		stack.push(43);
		break;
	case 18:
		stack.push(44);
		break;
	case 19:
		stack.push(45);
		break;
	case 20:
		stack.push(46);
		break;
	case 39:
		stack.push(72);
		break;
	case 48:
		stack.push(73);
		break;
	case 50:
		stack.push(74);
		break;
	default:
		err = { "ChainAssign::Process", "Syntax Error!" };
		return false;
	}
	return true;
}
bool AssignExp::Process(Stack &stack, SymStack &symStack, Parser::Error &err)
{
	switch (stack.top())
	{
	case 1:
	case 12:
	case 13:
	case 14:
	case 60:
	case 71:
	case 94:
		stack.push(11);
		break;
	case 16:
	case 17:
	case 18:
	case 19:
	case 20:
	case 39:
	case 48:
	case 50:
		stack.push(41);
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
	case 12:
	case 13:
		stack.push(35);
		break;
	case 16:
	case 17:
	case 18:
	case 19:
	case 20:
	case 39:
	case 48:
	case 50:
		stack.push(42);
		break;
	case 24:
		stack.push(55);
		break;
	case 29:
		stack.push(59);
		break;
	case 61:
		stack.push(80);
		break;
	case 62:
		stack.push(81);
		break;
	case 63:
		stack.push(82);
		break;
	case 64:
		stack.push(83);
		break;
	case 65:
		stack.push(84);
		break;
	case 66:
		stack.push(85);
		break;
	case 67:
		stack.push(86);
		break;
	case 68:
		stack.push(87);
		break;
	case 69:
		stack.push(88);
		break;
	case 70:
		stack.push(89);
		break;
	case 75:
		stack.push(91);
		break;
	case 76:
		stack.push(92);
		break;
	case 77:
		stack.push(93);
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
	case 14:
	case 60:
	case 71:
	case 94:
		stack.push(2);
		break;
	case 9:
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
	{
		stack.pop();
		stack.pop();
		pTerm sym2 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pValueStat sym1 = pCast<ValueStat>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat2_Value(move(sym1), move(sym2)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 37:
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
	case 38:
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
	case 47:
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
	case 49:
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
	case 79:
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
		pCond sym3 = pCast<Cond>(move(symStack.top()));
		symStack.pop();
		pOpenP sym2 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		pIf sym1 = pCast<If>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat2_If(move(sym1), move(sym2), move(sym3), move(sym4), move(sym5)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 90:
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
		pCond sym3 = pCast<Cond>(move(symStack.top()));
		symStack.pop();
		pOpenP sym2 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		pWhile sym1 = pCast<While>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat2_While(move(sym1), move(sym2), move(sym3), move(sym4), move(sym5)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 95:
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
		pCond sym3 = pCast<Cond>(move(symStack.top()));
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
	case 2:
		stack.push(12);
		break;
	case 3:
		stack.push(13);
		break;
	case 12:
	case 13:
	case 16:
	case 17:
	case 18:
	case 19:
	case 20:
	case 24:
	case 29:
	case 39:
	case 48:
	case 50:
	case 61:
	case 62:
	case 63:
	case 64:
	case 65:
	case 66:
	case 67:
	case 68:
	case 69:
	case 70:
	case 75:
	case 76:
	case 77:
		stack.push(24);
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
	case 11:
	{
		stack.pop();
		pAssignExp sym1 = pCast<AssignExp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new ValueStat_Assign(move(sym1)));
		return ValueStat::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 26:
	case 52:
	{
		stack.pop();
		pName sym1 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_Variable(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 30:
	{
		stack.pop();
		pIntL sym1 = pCast<IntL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_LiteralInt(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 31:
	{
		stack.pop();
		pDoubleL sym1 = pCast<DoubleL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_LiteralDouble(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 32:
	{
		stack.pop();
		pBoolL sym1 = pCast<BoolL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_LiteralBool(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 33:
		stack.push(60);
		break;
	case 34:
	{
		stack.pop();
		pValueStat sym1 = pCast<ValueStat>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Cond_Assign(move(sym1)));
		return Cond::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 35:
	{
		stack.pop();
		pExp sym1 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Cond_Exp(move(sym1)));
		return Cond::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 36:
		stack.push(71);
		break;
	case 40:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pChainAssign sym3 = pCast<ChainAssign>(move(symStack.top()));
		symStack.pop();
		pAssign sym2 = pCast<Assign>(move(symStack.top()));
		symStack.pop();
		pName sym1 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new AssignExp_Assign(move(sym1), move(sym2), move(sym3)));
		return AssignExp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 41:
	{
		stack.pop();
		pAssignExp sym1 = pCast<AssignExp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new ChainAssign_Chain(move(sym1)));
		return ChainAssign::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 42:
	{
		stack.pop();
		pExp sym1 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new ChainAssign_Exp(move(sym1)));
		return ChainAssign::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 43:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pChainAssign sym3 = pCast<ChainAssign>(move(symStack.top()));
		symStack.pop();
		pAddAssign sym2 = pCast<AddAssign>(move(symStack.top()));
		symStack.pop();
		pName sym1 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new AssignExp_AddAssign(move(sym1), move(sym2), move(sym3)));
		return AssignExp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 44:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pChainAssign sym3 = pCast<ChainAssign>(move(symStack.top()));
		symStack.pop();
		pSubAssign sym2 = pCast<SubAssign>(move(symStack.top()));
		symStack.pop();
		pName sym1 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new AssignExp_SubAssign(move(sym1), move(sym2), move(sym3)));
		return AssignExp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 45:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pChainAssign sym3 = pCast<ChainAssign>(move(symStack.top()));
		symStack.pop();
		pMultAssign sym2 = pCast<MultAssign>(move(symStack.top()));
		symStack.pop();
		pName sym1 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new AssignExp_MultAssign(move(sym1), move(sym2), move(sym3)));
		return AssignExp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 46:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pChainAssign sym3 = pCast<ChainAssign>(move(symStack.top()));
		symStack.pop();
		pDivAssign sym2 = pCast<DivAssign>(move(symStack.top()));
		symStack.pop();
		pName sym1 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new AssignExp_DivAssign(move(sym1), move(sym2), move(sym3)));
		return AssignExp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 51:
		stack.push(75);
		break;
	case 53:
		stack.push(76);
		break;
	case 54:
		stack.push(77);
		break;
	case 55:
		stack.push(78);
		break;
	case 59:
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
	case 72:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pChainAssign sym4 = pCast<ChainAssign>(move(symStack.top()));
		symStack.pop();
		pAssign sym3 = pCast<Assign>(move(symStack.top()));
		symStack.pop();
		pName sym2 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		pIntT sym1 = pCast<IntT>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new ValueStat_InitInt(move(sym1), move(sym2), move(sym3), move(sym4)));
		return ValueStat::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 73:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pChainAssign sym4 = pCast<ChainAssign>(move(symStack.top()));
		symStack.pop();
		pAssign sym3 = pCast<Assign>(move(symStack.top()));
		symStack.pop();
		pName sym2 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		pDoubleT sym1 = pCast<DoubleT>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new ValueStat_InitDouble(move(sym1), move(sym2), move(sym3), move(sym4)));
		return ValueStat::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 74:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pChainAssign sym4 = pCast<ChainAssign>(move(symStack.top()));
		symStack.pop();
		pAssign sym3 = pCast<Assign>(move(symStack.top()));
		symStack.pop();
		pName sym2 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		pBoolT sym1 = pCast<BoolT>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new ValueStat_InitBool(move(sym1), move(sym2), move(sym3), move(sym4)));
		return ValueStat::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 78:
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
	case 80:
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
	case 81:
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
	case 82:
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
	case 83:
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
	case 84:
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
	case 85:
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
	case 86:
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
	case 87:
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
	case 88:
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
	case 89:
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
	case 91:
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
	case 92:
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
	case 93:
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
		err = { "CloseP::Process", "Syntax Error!" };
		return false;
	}
	return true;
}
bool Else::Process(Stack &stack, SymStack &symStack, Parser::Error &err) const
{
	switch (stack.top())
	{
	case 23:
	{
		stack.pop();
		stack.pop();
		pTerm sym2 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pValueStat sym1 = pCast<ValueStat>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat2_Value(move(sym1), move(sym2)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 37:
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
	case 38:
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
	case 47:
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
	case 49:
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
	case 79:
		stack.push(94);
		break;
	case 90:
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
		pCond sym3 = pCast<Cond>(move(symStack.top()));
		symStack.pop();
		pOpenP sym2 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		pWhile sym1 = pCast<While>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat2_While(move(sym1), move(sym2), move(sym3), move(sym4), move(sym5)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 95:
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
		pCond sym3 = pCast<Cond>(move(symStack.top()));
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
bool While::Process(Stack &stack, SymStack &symStack, Parser::Error &err) const
{
	switch (stack.top())
	{
	case 0:
	case 4:
		symStack.emplace(new Stat1_End());
		return Stat1::Process(stack, symStack, err) && Process(stack, symStack, err);
	case 1:
	case 14:
	case 60:
	case 71:
	case 94:
		stack.push(3);
		break;
	case 9:
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
	{
		stack.pop();
		stack.pop();
		pTerm sym2 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pValueStat sym1 = pCast<ValueStat>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat2_Value(move(sym1), move(sym2)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 37:
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
	case 38:
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
	case 47:
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
	case 49:
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
	case 79:
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
		pCond sym3 = pCast<Cond>(move(symStack.top()));
		symStack.pop();
		pOpenP sym2 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		pIf sym1 = pCast<If>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat2_If(move(sym1), move(sym2), move(sym3), move(sym4), move(sym5)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 90:
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
		pCond sym3 = pCast<Cond>(move(symStack.top()));
		symStack.pop();
		pOpenP sym2 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		pWhile sym1 = pCast<While>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat2_While(move(sym1), move(sym2), move(sym3), move(sym4), move(sym5)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 95:
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
		pCond sym3 = pCast<Cond>(move(symStack.top()));
		symStack.pop();
		pOpenP sym2 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		pIf sym1 = pCast<If>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat2_IfElse(move(sym1), move(sym2), move(sym3), move(sym4), move(sym5), move(sym6), move(sym7)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	default:
		err = { "While::Process", "Syntax Error!" };
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
	case 14:
	case 60:
	case 71:
	case 94:
		stack.push(4);
		break;
	case 9:
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
	{
		stack.pop();
		stack.pop();
		pTerm sym2 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pValueStat sym1 = pCast<ValueStat>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat2_Value(move(sym1), move(sym2)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 37:
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
	case 38:
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
	case 47:
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
	case 49:
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
	case 79:
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
		pCond sym3 = pCast<Cond>(move(symStack.top()));
		symStack.pop();
		pOpenP sym2 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		pIf sym1 = pCast<If>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat2_If(move(sym1), move(sym2), move(sym3), move(sym4), move(sym5)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 90:
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
		pCond sym3 = pCast<Cond>(move(symStack.top()));
		symStack.pop();
		pOpenP sym2 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		pWhile sym1 = pCast<While>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat2_While(move(sym1), move(sym2), move(sym3), move(sym4), move(sym5)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 95:
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
		pCond sym3 = pCast<Cond>(move(symStack.top()));
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
	case 9:
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
	case 14:
		stack.push(37);
		break;
	case 23:
	{
		stack.pop();
		stack.pop();
		pTerm sym2 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pValueStat sym1 = pCast<ValueStat>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat2_Value(move(sym1), move(sym2)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 37:
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
	case 38:
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
	case 47:
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
	case 49:
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
	case 79:
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
		pCond sym3 = pCast<Cond>(move(symStack.top()));
		symStack.pop();
		pOpenP sym2 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		pIf sym1 = pCast<If>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat2_If(move(sym1), move(sym2), move(sym3), move(sym4), move(sym5)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 90:
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
		pCond sym3 = pCast<Cond>(move(symStack.top()));
		symStack.pop();
		pOpenP sym2 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		pWhile sym1 = pCast<While>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat2_While(move(sym1), move(sym2), move(sym3), move(sym4), move(sym5)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 95:
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
		pCond sym3 = pCast<Cond>(move(symStack.top()));
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
	case 14:
	case 60:
	case 71:
	case 94:
		stack.push(5);
		break;
	case 9:
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
	case 12:
	case 13:
		stack.push(25);
		break;
	case 23:
	{
		stack.pop();
		stack.pop();
		pTerm sym2 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pValueStat sym1 = pCast<ValueStat>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat2_Value(move(sym1), move(sym2)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 24:
		stack.push(51);
		break;
	case 37:
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
	case 38:
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
	case 47:
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
	case 49:
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
	case 79:
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
		pCond sym3 = pCast<Cond>(move(symStack.top()));
		symStack.pop();
		pOpenP sym2 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		pIf sym1 = pCast<If>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat2_If(move(sym1), move(sym2), move(sym3), move(sym4), move(sym5)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 90:
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
		pCond sym3 = pCast<Cond>(move(symStack.top()));
		symStack.pop();
		pOpenP sym2 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		pWhile sym1 = pCast<While>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat2_While(move(sym1), move(sym2), move(sym3), move(sym4), move(sym5)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 95:
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
		pCond sym3 = pCast<Cond>(move(symStack.top()));
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
	case 14:
	case 60:
	case 71:
	case 94:
		stack.push(6);
		break;
	case 5:
		stack.push(15);
		break;
	case 7:
		stack.push(21);
		break;
	case 8:
		stack.push(22);
		break;
	case 9:
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
	case 12:
	case 13:
	case 16:
	case 17:
	case 18:
	case 19:
	case 20:
	case 39:
	case 48:
	case 50:
		stack.push(26);
		break;
	case 23:
	{
		stack.pop();
		stack.pop();
		pTerm sym2 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pValueStat sym1 = pCast<ValueStat>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat2_Value(move(sym1), move(sym2)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 24:
	case 29:
	case 61:
	case 62:
	case 63:
	case 64:
	case 65:
	case 66:
	case 67:
	case 68:
	case 69:
	case 70:
	case 75:
	case 76:
	case 77:
		stack.push(52);
		break;
	case 25:
		stack.push(56);
		break;
	case 27:
		stack.push(57);
		break;
	case 28:
		stack.push(58);
		break;
	case 37:
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
	case 38:
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
	case 47:
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
	case 49:
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
	case 79:
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
		pCond sym3 = pCast<Cond>(move(symStack.top()));
		symStack.pop();
		pOpenP sym2 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		pIf sym1 = pCast<If>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat2_If(move(sym1), move(sym2), move(sym3), move(sym4), move(sym5)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 90:
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
		pCond sym3 = pCast<Cond>(move(symStack.top()));
		symStack.pop();
		pOpenP sym2 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		pWhile sym1 = pCast<While>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat2_While(move(sym1), move(sym2), move(sym3), move(sym4), move(sym5)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 95:
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
		pCond sym3 = pCast<Cond>(move(symStack.top()));
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
	case 10:
		stack.push(23);
		break;
	case 11:
	{
		stack.pop();
		pAssignExp sym1 = pCast<AssignExp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new ValueStat_Assign(move(sym1)));
		return ValueStat::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 15:
		stack.push(38);
		break;
	case 21:
		stack.push(47);
		break;
	case 22:
		stack.push(49);
		break;
	case 26:
	case 52:
	{
		stack.pop();
		pName sym1 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_Variable(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 30:
	{
		stack.pop();
		pIntL sym1 = pCast<IntL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_LiteralInt(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 31:
	{
		stack.pop();
		pDoubleL sym1 = pCast<DoubleL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_LiteralDouble(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 32:
	{
		stack.pop();
		pBoolL sym1 = pCast<BoolL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_LiteralBool(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 40:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pChainAssign sym3 = pCast<ChainAssign>(move(symStack.top()));
		symStack.pop();
		pAssign sym2 = pCast<Assign>(move(symStack.top()));
		symStack.pop();
		pName sym1 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new AssignExp_Assign(move(sym1), move(sym2), move(sym3)));
		return AssignExp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 41:
	{
		stack.pop();
		pAssignExp sym1 = pCast<AssignExp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new ChainAssign_Chain(move(sym1)));
		return ChainAssign::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 42:
	{
		stack.pop();
		pExp sym1 = pCast<Exp>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new ChainAssign_Exp(move(sym1)));
		return ChainAssign::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 43:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pChainAssign sym3 = pCast<ChainAssign>(move(symStack.top()));
		symStack.pop();
		pAddAssign sym2 = pCast<AddAssign>(move(symStack.top()));
		symStack.pop();
		pName sym1 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new AssignExp_AddAssign(move(sym1), move(sym2), move(sym3)));
		return AssignExp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 44:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pChainAssign sym3 = pCast<ChainAssign>(move(symStack.top()));
		symStack.pop();
		pSubAssign sym2 = pCast<SubAssign>(move(symStack.top()));
		symStack.pop();
		pName sym1 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new AssignExp_SubAssign(move(sym1), move(sym2), move(sym3)));
		return AssignExp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 45:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pChainAssign sym3 = pCast<ChainAssign>(move(symStack.top()));
		symStack.pop();
		pMultAssign sym2 = pCast<MultAssign>(move(symStack.top()));
		symStack.pop();
		pName sym1 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new AssignExp_MultAssign(move(sym1), move(sym2), move(sym3)));
		return AssignExp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 46:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		pChainAssign sym3 = pCast<ChainAssign>(move(symStack.top()));
		symStack.pop();
		pDivAssign sym2 = pCast<DivAssign>(move(symStack.top()));
		symStack.pop();
		pName sym1 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new AssignExp_DivAssign(move(sym1), move(sym2), move(sym3)));
		return AssignExp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 59:
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
	case 72:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pChainAssign sym4 = pCast<ChainAssign>(move(symStack.top()));
		symStack.pop();
		pAssign sym3 = pCast<Assign>(move(symStack.top()));
		symStack.pop();
		pName sym2 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		pIntT sym1 = pCast<IntT>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new ValueStat_InitInt(move(sym1), move(sym2), move(sym3), move(sym4)));
		return ValueStat::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 73:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pChainAssign sym4 = pCast<ChainAssign>(move(symStack.top()));
		symStack.pop();
		pAssign sym3 = pCast<Assign>(move(symStack.top()));
		symStack.pop();
		pName sym2 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		pDoubleT sym1 = pCast<DoubleT>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new ValueStat_InitDouble(move(sym1), move(sym2), move(sym3), move(sym4)));
		return ValueStat::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 74:
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
		pChainAssign sym4 = pCast<ChainAssign>(move(symStack.top()));
		symStack.pop();
		pAssign sym3 = pCast<Assign>(move(symStack.top()));
		symStack.pop();
		pName sym2 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		pBoolT sym1 = pCast<BoolT>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new ValueStat_InitBool(move(sym1), move(sym2), move(sym3), move(sym4)));
		return ValueStat::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 78:
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
	case 80:
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
	case 81:
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
	case 82:
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
	case 83:
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
	case 84:
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
	case 85:
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
	case 86:
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
	case 87:
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
	case 88:
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
	case 89:
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
	case 91:
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
	case 92:
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
	case 93:
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
	case 14:
	case 60:
	case 71:
	case 94:
		stack.push(7);
		break;
	case 9:
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
	case 12:
	case 13:
		stack.push(27);
		break;
	case 23:
	{
		stack.pop();
		stack.pop();
		pTerm sym2 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pValueStat sym1 = pCast<ValueStat>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat2_Value(move(sym1), move(sym2)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 24:
		stack.push(53);
		break;
	case 37:
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
	case 38:
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
	case 47:
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
	case 49:
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
	case 79:
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
		pCond sym3 = pCast<Cond>(move(symStack.top()));
		symStack.pop();
		pOpenP sym2 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		pIf sym1 = pCast<If>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat2_If(move(sym1), move(sym2), move(sym3), move(sym4), move(sym5)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 90:
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
		pCond sym3 = pCast<Cond>(move(symStack.top()));
		symStack.pop();
		pOpenP sym2 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		pWhile sym1 = pCast<While>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat2_While(move(sym1), move(sym2), move(sym3), move(sym4), move(sym5)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 95:
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
		pCond sym3 = pCast<Cond>(move(symStack.top()));
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
	case 14:
	case 60:
	case 71:
	case 94:
		stack.push(8);
		break;
	case 9:
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
	case 12:
	case 13:
		stack.push(28);
		break;
	case 23:
	{
		stack.pop();
		stack.pop();
		pTerm sym2 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pValueStat sym1 = pCast<ValueStat>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat2_Value(move(sym1), move(sym2)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 24:
		stack.push(54);
		break;
	case 37:
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
	case 38:
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
	case 47:
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
	case 49:
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
	case 79:
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
		pCond sym3 = pCast<Cond>(move(symStack.top()));
		symStack.pop();
		pOpenP sym2 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		pIf sym1 = pCast<If>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat2_If(move(sym1), move(sym2), move(sym3), move(sym4), move(sym5)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 90:
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
		pCond sym3 = pCast<Cond>(move(symStack.top()));
		symStack.pop();
		pOpenP sym2 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		pWhile sym1 = pCast<While>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat2_While(move(sym1), move(sym2), move(sym3), move(sym4), move(sym5)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 95:
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
		pCond sym3 = pCast<Cond>(move(symStack.top()));
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
	case 26:
		stack.push(16);
		break;
	case 15:
	case 56:
		stack.push(39);
		break;
	case 21:
	case 57:
		stack.push(48);
		break;
	case 22:
	case 58:
		stack.push(50);
		break;
	default:
		err = { "Assign::Process", "Syntax Error!" };
		return false;
	}
	return true;
}
bool AddAssign::Process(Stack &stack, SymStack &symStack, Parser::Error &err) const
{
	switch (stack.top())
	{
	case 6:
	case 26:
		stack.push(17);
		break;
	default:
		err = { "AddAssign::Process", "Syntax Error!" };
		return false;
	}
	return true;
}
bool SubAssign::Process(Stack &stack, SymStack &symStack, Parser::Error &err) const
{
	switch (stack.top())
	{
	case 6:
	case 26:
		stack.push(18);
		break;
	default:
		err = { "SubAssign::Process", "Syntax Error!" };
		return false;
	}
	return true;
}
bool MultAssign::Process(Stack &stack, SymStack &symStack, Parser::Error &err) const
{
	switch (stack.top())
	{
	case 6:
	case 26:
		stack.push(19);
		break;
	default:
		err = { "MultAssign::Process", "Syntax Error!" };
		return false;
	}
	return true;
}
bool DivAssign::Process(Stack &stack, SymStack &symStack, Parser::Error &err) const
{
	switch (stack.top())
	{
	case 6:
	case 26:
		stack.push(20);
		break;
	default:
		err = { "DivAssign::Process", "Syntax Error!" };
		return false;
	}
	return true;
}
bool Sub::Process(Stack &stack, SymStack &symStack, Parser::Error &err) const
{
	switch (stack.top())
	{
	case 12:
	case 13:
	case 16:
	case 17:
	case 18:
	case 19:
	case 20:
	case 24:
	case 29:
	case 39:
	case 48:
	case 50:
	case 61:
	case 62:
	case 63:
	case 64:
	case 65:
	case 66:
	case 67:
	case 68:
	case 69:
	case 70:
	case 75:
	case 76:
	case 77:
		stack.push(29);
		break;
	case 26:
	case 52:
	{
		stack.pop();
		pName sym1 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_Variable(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 30:
	{
		stack.pop();
		pIntL sym1 = pCast<IntL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_LiteralInt(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 31:
	{
		stack.pop();
		pDoubleL sym1 = pCast<DoubleL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_LiteralDouble(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 32:
	{
		stack.pop();
		pBoolL sym1 = pCast<BoolL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_LiteralBool(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 35:
	case 42:
	case 55:
	case 84:
	case 85:
	case 86:
	case 87:
	case 88:
	case 89:
		stack.push(61);
		break;
	case 59:
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
	case 78:
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
	case 80:
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
	case 81:
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
	case 82:
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
	case 83:
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
	case 91:
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
	case 92:
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
	case 93:
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
		err = { "Sub::Process", "Syntax Error!" };
		return false;
	}
	return true;
}
bool Add::Process(Stack &stack, SymStack &symStack, Parser::Error &err) const
{
	switch (stack.top())
	{
	case 26:
	case 52:
	{
		stack.pop();
		pName sym1 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_Variable(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 30:
	{
		stack.pop();
		pIntL sym1 = pCast<IntL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_LiteralInt(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 31:
	{
		stack.pop();
		pDoubleL sym1 = pCast<DoubleL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_LiteralDouble(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 32:
	{
		stack.pop();
		pBoolL sym1 = pCast<BoolL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_LiteralBool(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 35:
	case 42:
	case 55:
	case 84:
	case 85:
	case 86:
	case 87:
	case 88:
	case 89:
		stack.push(62);
		break;
	case 59:
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
	case 78:
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
	case 80:
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
	case 81:
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
	case 82:
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
	case 83:
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
	case 91:
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
	case 92:
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
	case 93:
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
	case 26:
	case 52:
	{
		stack.pop();
		pName sym1 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_Variable(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 30:
	{
		stack.pop();
		pIntL sym1 = pCast<IntL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_LiteralInt(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 31:
	{
		stack.pop();
		pDoubleL sym1 = pCast<DoubleL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_LiteralDouble(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 32:
	{
		stack.pop();
		pBoolL sym1 = pCast<BoolL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_LiteralBool(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 35:
	case 42:
	case 55:
	case 80:
	case 81:
	case 84:
	case 85:
	case 86:
	case 87:
	case 88:
	case 89:
		stack.push(63);
		break;
	case 59:
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
	case 78:
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
	case 82:
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
	case 83:
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
	case 91:
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
	case 92:
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
	case 93:
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
	case 26:
	case 52:
	{
		stack.pop();
		pName sym1 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_Variable(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 30:
	{
		stack.pop();
		pIntL sym1 = pCast<IntL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_LiteralInt(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 31:
	{
		stack.pop();
		pDoubleL sym1 = pCast<DoubleL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_LiteralDouble(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 32:
	{
		stack.pop();
		pBoolL sym1 = pCast<BoolL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_LiteralBool(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 35:
	case 42:
	case 55:
	case 80:
	case 81:
	case 84:
	case 85:
	case 86:
	case 87:
	case 88:
	case 89:
		stack.push(64);
		break;
	case 59:
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
	case 78:
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
	case 82:
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
	case 83:
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
	case 91:
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
	case 92:
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
	case 93:
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
	case 26:
	case 52:
	{
		stack.pop();
		pName sym1 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_Variable(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 30:
	{
		stack.pop();
		pIntL sym1 = pCast<IntL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_LiteralInt(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 31:
	{
		stack.pop();
		pDoubleL sym1 = pCast<DoubleL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_LiteralDouble(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 32:
	{
		stack.pop();
		pBoolL sym1 = pCast<BoolL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_LiteralBool(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 35:
	case 42:
	case 55:
	case 88:
	case 89:
		stack.push(65);
		break;
	case 59:
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
	case 78:
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
	case 80:
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
	case 81:
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
	case 82:
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
	case 83:
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
	case 84:
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
	case 85:
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
	case 86:
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
	case 87:
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
	case 91:
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
	case 92:
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
	case 93:
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
	case 26:
	case 52:
	{
		stack.pop();
		pName sym1 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_Variable(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 30:
	{
		stack.pop();
		pIntL sym1 = pCast<IntL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_LiteralInt(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 31:
	{
		stack.pop();
		pDoubleL sym1 = pCast<DoubleL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_LiteralDouble(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 32:
	{
		stack.pop();
		pBoolL sym1 = pCast<BoolL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_LiteralBool(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 35:
	case 42:
	case 55:
	case 88:
	case 89:
		stack.push(66);
		break;
	case 59:
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
	case 78:
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
	case 80:
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
	case 81:
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
	case 82:
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
	case 83:
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
	case 84:
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
	case 85:
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
	case 86:
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
	case 87:
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
	case 91:
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
	case 92:
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
	case 93:
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
	case 26:
	case 52:
	{
		stack.pop();
		pName sym1 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_Variable(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 30:
	{
		stack.pop();
		pIntL sym1 = pCast<IntL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_LiteralInt(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 31:
	{
		stack.pop();
		pDoubleL sym1 = pCast<DoubleL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_LiteralDouble(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 32:
	{
		stack.pop();
		pBoolL sym1 = pCast<BoolL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_LiteralBool(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 35:
	case 42:
	case 55:
	case 88:
	case 89:
		stack.push(67);
		break;
	case 59:
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
	case 78:
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
	case 80:
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
	case 81:
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
	case 82:
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
	case 83:
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
	case 84:
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
	case 85:
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
	case 86:
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
	case 87:
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
	case 91:
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
	case 92:
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
	case 93:
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
	case 26:
	case 52:
	{
		stack.pop();
		pName sym1 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_Variable(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 30:
	{
		stack.pop();
		pIntL sym1 = pCast<IntL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_LiteralInt(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 31:
	{
		stack.pop();
		pDoubleL sym1 = pCast<DoubleL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_LiteralDouble(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 32:
	{
		stack.pop();
		pBoolL sym1 = pCast<BoolL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_LiteralBool(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 35:
	case 42:
	case 55:
	case 88:
	case 89:
		stack.push(68);
		break;
	case 59:
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
	case 78:
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
	case 80:
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
	case 81:
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
	case 82:
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
	case 83:
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
	case 84:
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
	case 85:
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
	case 86:
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
	case 87:
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
	case 91:
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
	case 92:
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
	case 93:
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
	case 26:
	case 52:
	{
		stack.pop();
		pName sym1 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_Variable(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 30:
	{
		stack.pop();
		pIntL sym1 = pCast<IntL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_LiteralInt(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 31:
	{
		stack.pop();
		pDoubleL sym1 = pCast<DoubleL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_LiteralDouble(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 32:
	{
		stack.pop();
		pBoolL sym1 = pCast<BoolL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_LiteralBool(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 35:
	case 42:
	case 55:
		stack.push(69);
		break;
	case 59:
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
	case 78:
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
	case 80:
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
	case 81:
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
	case 82:
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
	case 83:
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
	case 84:
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
	case 85:
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
	case 86:
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
	case 87:
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
	case 88:
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
	case 89:
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
	case 91:
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
	case 92:
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
	case 93:
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
	case 26:
	case 52:
	{
		stack.pop();
		pName sym1 = pCast<Name>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_Variable(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 30:
	{
		stack.pop();
		pIntL sym1 = pCast<IntL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_LiteralInt(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 31:
	{
		stack.pop();
		pDoubleL sym1 = pCast<DoubleL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_LiteralDouble(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 32:
	{
		stack.pop();
		pBoolL sym1 = pCast<BoolL>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Exp_LiteralBool(move(sym1)));
		return Exp::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 35:
	case 42:
	case 55:
		stack.push(70);
		break;
	case 59:
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
	case 78:
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
	case 80:
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
	case 81:
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
	case 82:
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
	case 83:
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
	case 84:
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
	case 85:
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
	case 86:
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
	case 87:
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
	case 88:
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
	case 89:
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
	case 91:
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
	case 92:
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
	case 93:
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
	case 12:
	case 13:
	case 16:
	case 17:
	case 18:
	case 19:
	case 20:
	case 24:
	case 29:
	case 39:
	case 48:
	case 50:
	case 61:
	case 62:
	case 63:
	case 64:
	case 65:
	case 66:
	case 67:
	case 68:
	case 69:
	case 70:
	case 75:
	case 76:
	case 77:
		stack.push(30);
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
	case 12:
	case 13:
	case 16:
	case 17:
	case 18:
	case 19:
	case 20:
	case 24:
	case 29:
	case 39:
	case 48:
	case 50:
	case 61:
	case 62:
	case 63:
	case 64:
	case 65:
	case 66:
	case 67:
	case 68:
	case 69:
	case 70:
	case 75:
	case 76:
	case 77:
		stack.push(31);
		break;
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
	case 12:
	case 13:
	case 16:
	case 17:
	case 18:
	case 19:
	case 20:
	case 24:
	case 29:
	case 39:
	case 48:
	case 50:
	case 61:
	case 62:
	case 63:
	case 64:
	case 65:
	case 66:
	case 67:
	case 68:
	case 69:
	case 70:
	case 75:
	case 76:
	case 77:
		stack.push(32);
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
	case 4:
		symStack.emplace(new Stat1_End());
		return Stat1::Process(stack, symStack, err) && Process(stack, symStack, err);
	case 1:
		break;
	case 9:
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
	{
		stack.pop();
		stack.pop();
		pTerm sym2 = pCast<Term>(move(symStack.top()));
		symStack.pop();
		pValueStat sym1 = pCast<ValueStat>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat2_Value(move(sym1), move(sym2)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 37:
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
	case 38:
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
	case 47:
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
	case 49:
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
	case 79:
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
		pCond sym3 = pCast<Cond>(move(symStack.top()));
		symStack.pop();
		pOpenP sym2 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		pIf sym1 = pCast<If>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat2_If(move(sym1), move(sym2), move(sym3), move(sym4), move(sym5)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 90:
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
		pCond sym3 = pCast<Cond>(move(symStack.top()));
		symStack.pop();
		pOpenP sym2 = pCast<OpenP>(move(symStack.top()));
		symStack.pop();
		pWhile sym1 = pCast<While>(move(symStack.top()));
		symStack.pop();
		symStack.emplace(new Stat2_While(move(sym1), move(sym2), move(sym3), move(sym4), move(sym5)));
		return Stat2::Process(stack, symStack, err) && Process(stack, symStack, err);
	}
	case 95:
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
		pCond sym3 = pCast<Cond>(move(symStack.top()));
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