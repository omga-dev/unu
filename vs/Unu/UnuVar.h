#pragma once

#include <vector>

namespace Unu
{
	typedef long long int64;

	enum ListType { Integer, List, Reference };

	class UnuVar
	{
		ListType type;
		int64 intValue;
		std::vector<UnuVar> listValue;
		UnuVar* referenceValue;

	public:
		UnuVar(int64 value);
		UnuVar(std::vector<UnuVar> value);
		UnuVar(UnuVar* value);

		bool IsInteger();
		int64 GetIntValue();
		void SetIntValue(int64 value);

		bool IsList();
		std::vector<UnuVar> GetListItems();
		void AddItem(UnuVar item);

		bool IsIntegerReference();
		bool IsListReference();
		UnuVar GetReferenceValue();
		size_t GetReferencedListSize();
		UnuVar GetItemReferenceAt(int index);

		static bool IsSameReference(UnuVar a, UnuVar b);
	};
}