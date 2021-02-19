#pragma once

#include "UnuVar.h"

namespace Unu
{
	class UnuEvaluator
	{
	private:
		UnuVar program;

		void EvalList(UnuVar var);
		UnuVar EvalCmd(UnuVar var, bool lvalue = false);
		UnuVar TwoArgCmd(UnuVar r, UnuVar i, bool lvalue = false);
		UnuVar FourArgCmd(UnuVar d, UnuVar a, UnuVar b, UnuVar s);

	protected:
		virtual void OnRead(UnuVar i);
		virtual void OnWrite(UnuVar i, int64 v);

	public:
		UnuEvaluator();
		void Parse(std::string code);
		void Evaluate();
	};
}