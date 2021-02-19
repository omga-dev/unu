#include "UnuEvaluator.h"
#include "UnuException.h"

using std::cin;
using std::cout;
using std::string;
using std::vector;

namespace Unu
{
	UnuEvaluator::UnuEvaluator() : program(UnuVar(vector<UnuVar>())), programStack(), calcStack()
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
				stack.back().listValue.push_back(UnuVar(1));
			}
			else if (!comment && c == ')')
			{
				if (stack.size() == 0)
					throw ParseException("Expected EOF, read ')'.");
				back = stack.back();
				stack.pop_back();
				if (stack.size() != 0)
					stack.back().listValue.push_back(back);
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
		vector<UnuVar*> commandStack = vector<UnuVar*>();

		programStack.clear();
		for (auto i = program.listValue.rbegin(); i != program.listValue.rend(); i++)
			programStack.push_back(&*i);

		while (!programStack.empty())
		{
			commandStack.clear();
			calcStack.clear();
			
			commandStack.push_back(programStack.back());
			programStack.pop_back();

			UnuVar* root = nullptr;
			UnuVar* last = nullptr;

			while (!commandStack.empty())
			{
				root = commandStack.back();

				size_t itemCount = root->listValue.size();
				
				if (root->type == List && last == &(root->listValue.back()))
				{
					if (itemCount <= 2)
					{
						UnuVar i = calcStack.back();
						calcStack.pop_back();

						UnuVar r = UnuVar(&program);
						if (itemCount == 2)
						{
							r = calcStack.back();
							calcStack.pop_back();
						}

						TwoArgCmd(r, i);
					}
					else if (itemCount <= 4)
					{
						UnuVar s = calcStack.back();
						calcStack.pop_back();
						UnuVar b = calcStack.back();
						calcStack.pop_back();
						UnuVar a = calcStack.back();
						calcStack.pop_back();
						UnuVar d = UnuVar(&program);
						if (itemCount == 4)
						{
							d = calcStack.back();
							calcStack.pop_back();
						}

						FourArgCmd(d, a, b, s);
					}
					commandStack.pop_back();
					last = root;
				}
				else if (itemCount == 0 || itemCount > 4)
				{
					calcStack.push_back(UnuVar(*root));
					commandStack.pop_back();
					last = root;
				}
				else
				{
					for (auto i = root->listValue.rbegin(); i != root->listValue.rend(); i++)
						commandStack.push_back(&*i);
				}
			}
		}
	}

	void UnuEvaluator::TwoArgCmd(UnuVar r, UnuVar i)
	{
		UnuVar* reference = nullptr;
		if (r.type == Reference && r.reference->type == List)
			reference = r.reference;
		else
			throw EvaluationException("the first argument of the 2-argument-instruction should be a reference to a list.");

		int64 index = 0;
		if (i.type == Integer)
			index = i.intValue;
		else if (i.type == Reference && i.reference->type == Integer)
		{
			OnRead(i);
			index = i.reference->intValue;
		}
		else
			throw EvaluationException("the second argument of the 2-argument-instruction should be integer.");

		if ((int)reference->listValue.size() <= index)
			throw EvaluationException("list out of index.");

		calcStack.push_back(&(reference->listValue[index]));
	}

	void UnuEvaluator::FourArgCmd(UnuVar d, UnuVar a, UnuVar b, UnuVar s)
	{
		int64 v = 0;

		if (a.type == Integer)
			v += a.intValue;
		else if (a.type == Reference && a.reference->type == Integer)
		{
			OnRead(a);
			v += a.reference->intValue;
		}

		if (b.type == Integer)
			v -= b.intValue;
		else if (b.type == Reference && b.reference->type == Integer)
		{
			OnRead(b);
			v -= b.reference->intValue;
		}

		if (d.type == Reference && d.reference->type == Integer)
		{
			d.reference->intValue = v;
			OnWrite(d);
		}
		else if (d.type != Reference)
			throw EvaluationException("the first argument of the 4-argument-instruction should be a reference.");

		if (v > 0)
		{
			if (s.type == List)
			{
				for (auto i = s.listValue.rbegin(); i != s.listValue.rend(); i++)
					programStack.push_back(&*i);
			}
			else if (s.type == Reference && s.reference->type == List)
			{
				for (auto i = s.reference->listValue.rbegin(); i != s.reference->listValue.rend(); i++)
					programStack.push_back(&*i);
			}
		}

		calcStack.push_back(UnuVar(v));
	}

	void UnuEvaluator::OnRead(UnuVar i)
	{
		if (i.reference == &(program.listValue[0]))
		{
			i.reference->intValue = cin.get();
		}
	}

	void UnuEvaluator::OnWrite(UnuVar i)
	{
		if (i.reference == &(program.listValue[0]))
		{
			cout << (char)i.reference->intValue;
		}
	}
}