#include "SyntaxTree.h"

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