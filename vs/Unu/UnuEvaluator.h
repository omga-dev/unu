#pragma once

#include "UnuVar.h"

namespace Unu
{
	class UnuEvaluator
	{
	private:
		UnuVar program;

		std::vector<UnuVar*> programStack;
		std::vector<UnuVar> calcStack;

		void TwoArgCmd(UnuVar r, UnuVar i);
		void FourArgCmd(UnuVar d, UnuVar a, UnuVar b, UnuVar s);

	protected:
		virtual void OnRead(UnuVar i);
		virtual void OnWrite(UnuVar i);

	public:
		UnuEvaluator();
		void Parse(std::string code);
		void Evaluate();
	};
}