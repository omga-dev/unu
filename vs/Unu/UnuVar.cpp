#include "UnuVar.h"

using std::vector;

namespace Unu
{
	UnuVar::UnuVar(int64 value) : type(Integer), intValue(value), listValue()
	{

	}

	UnuVar::UnuVar(vector<UnuVar> value) : type(List), intValue(0), listValue(value)
	{

	}

	UnuVar::UnuVar(UnuVar* value) : type(Reference), intValue(0), reference(value)
	{

	}
}