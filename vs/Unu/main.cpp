#include <fstream>
#include "UnuEvaluator.h"
#include "UnuException.h"

using std::string;
using std::ifstream;
using Unu::UnuEvaluator;
using Unu::ParseException;
using Unu::EvaluationException;

int main(int argc, char* argv[])
{
	if (argc == 2)
	{
		UnuEvaluator evaluator = UnuEvaluator();

		string code = "";
		ifstream fs;
		fs.open(argv[1]);
		while (!fs.eof())
			code += fs.get();
		fs.close();

		try
		{
			evaluator.Parse(code);
			evaluator.Evaluate();
		}
		catch (ParseException e)
		{
			printf("\n---------\nParseException: ");
			printf(e.what());
		}
		catch (EvaluationException e)
		{
			printf("\n---------\nEvaluationException: ");
			printf(e.what());
		}
	}

	printf("\n");
	system("pause");
}