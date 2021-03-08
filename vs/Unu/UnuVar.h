#pragma once

#include <vector>
#include <cstdint>

namespace Unu
{
	using int64 = std::int64_t;

	enum UnuVarType { Integer, List, Reference };

	struct UnuVar
	{
		UnuVarType type;
		int64 intValue;
		std::vector<UnuVar> listValue;
		UnuVar* reference;

		UnuVar(int64 value);
		UnuVar(std::vector<UnuVar> value);
		UnuVar(UnuVar* value);
	};
}