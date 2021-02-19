#include "UnuEvaluator.h"
#include "UnuException.h"

using std::cin;
using std::cout;
using std::string;
using std::vector;

namespace Unu
{
	UnuEvaluator::UnuEvaluator() : program(UnuVar(vector<UnuVar>()))
	{

	}

	void UnuEvaluator::Parse(string code)
	{
		vector<UnuVar> stack = vector<UnuVar>();
		UnuVar back = UnuVar(vector<UnuVar>());
		bool comment = false;

		for (char c : code)
		{
			if (!comment && c == '(')
			{
				stack.push_back(UnuVar(vector<UnuVar>()));
			}
			else if (!comment && c == '1')
			{
				if (stack.size() == 0)
					throw ParseException("Expected EOF, read '1'.");
				stack.back().AddItem(UnuVar(1));
			}
			else if (!comment && c == ')')
			{
				if (stack.size() == 0)
					throw ParseException("Expected EOF, read ')'.");
				back = stack.back();
				stack.pop_back();
				if (stack.size() != 0)
					stack.back().AddItem(back);
			}
			else if (c == '#')
			{
				comment = true;
			}
			else if (c == '\n')
			{
				comment = false;
			}
		}

		if (stack.size() != 0)
			throw ParseException("Expected ')', read EOF.");

		program = back;
	}

	void UnuEvaluator::Evaluate()
	{
		EvalList(program);
	}

	void UnuEvaluator::EvalList(UnuVar var)
	{
		for (UnuVar& item : var.GetListItems())
			EvalCmd(item);
	}

	UnuVar UnuEvaluator::EvalCmd(UnuVar var, bool lvalue)
	{
		if (var.IsList())
		{
			vector<UnuVar> args = var.GetListItems();
			size_t size = args.size();

			if (size == 1)
				return TwoArgCmd(UnuVar(&program), EvalCmd(args[0]), lvalue);
			else if (size == 2)
				return TwoArgCmd(EvalCmd(args[0], true), EvalCmd(args[1]), lvalue);
			else if (size == 3)
				return FourArgCmd(UnuVar(&program), EvalCmd(args[0]), EvalCmd(args[1]), EvalCmd(args[2]));
			else if (size == 4)
				return FourArgCmd(EvalCmd(args[0], true), EvalCmd(args[1]), EvalCmd(args[2]), EvalCmd(args[3]));
			else
				return var;
		}
		else
		{
			return var;
		}
	}

	UnuVar UnuEvaluator::TwoArgCmd(UnuVar r, UnuVar i, bool lvalue)
	{
		if (!r.IsListReference())
			throw EvaluationException("the first argument of the 2-argument-instruction should be a reference to a list.");

		if (!i.IsInteger())
			throw EvaluationException("the second argument of the 2-argument-instruction should be integer.");

		if ((int)r.GetReferencedListSize() <= i.GetIntValue())
			throw EvaluationException("list out of index.");

		UnuVar reference = r.GetItemReferenceAt((int)i.GetIntValue());

		if (lvalue)
			return reference;
		else
		{
			OnRead(reference);
			return reference.GetReferenceValue();
		}
	}

	UnuVar UnuEvaluator::FourArgCmd(UnuVar d, UnuVar a, UnuVar b, UnuVar s)
	{
		int64 v = 0;

		if (a.IsInteger())
			v += a.GetIntValue();

		if (b.IsInteger())
			v -= b.GetIntValue();

		if (d.IsIntegerReference())
		{
			d.SetIntValue(v);
			OnWrite(d, v);
		}

		if (v > 0)
		{
			EvalList(s);
		}

		return UnuVar(v);
	}

	void UnuEvaluator::OnRead(UnuVar i)
	{
		if (UnuVar::IsSameReference(i, program.GetItemReferenceAt(0)))
		{
			i.SetIntValue(cin.get());
		}
	}

	void UnuEvaluator::OnWrite(UnuVar i, int64 v)
	{
		if (UnuVar::IsSameReference(i, program.GetItemReferenceAt(0)) && v != 0)
		{
			cout << (char)v;
		}
	}
}