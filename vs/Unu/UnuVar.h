#pragma once

#include <vector>

namespace Unu
{
	typedef long long int64;

	enum UnuVarType { Integer, List, Reference };

	struct UnuVar
	{
	public:
		UnuVarType type;
		int64 intValue;
		std::vector<UnuVar> listValue;
		UnuVar* reference;

		UnuVar(int64 value);
		UnuVar(std::vector<UnuVar> value);
		UnuVar(UnuVar* value);
	};
}