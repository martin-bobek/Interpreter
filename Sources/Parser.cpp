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