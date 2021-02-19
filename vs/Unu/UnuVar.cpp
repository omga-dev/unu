#include "UnuVar.h"

using std::vector;

namespace Unu
{
	UnuVar::UnuVar(int64 value) : type(Integer), intValue(value)
	{

	}

	UnuVar::UnuVar(vector<UnuVar> value) : type(List), listValue(value)
	{

	}

	UnuVar::UnuVar(UnuVar* value) : type(Reference), referenceValue(value)
	{

	}

	bool UnuVar::IsInteger()
	{
		return type == Integer;
	}

	int64 UnuVar::GetIntValue()
	{
		if (IsInteger())
			return intValue;
		else
			return 0;
	}
	
	void UnuVar::SetIntValue(int64 value)
	{
		if (IsIntegerReference())
			referenceValue->intValue = value;
	}

	bool UnuVar::IsList()
	{
		return type == List;
	}

	vector<UnuVar> UnuVar::GetListItems()
	{
		if (IsList())
			return listValue;
		else
			return vector<UnuVar>();
	}
	
	void UnuVar::AddItem(UnuVar item)
	{
		if (IsList())
			listValue.push_back(item);
	}

	bool UnuVar::IsIntegerReference()
	{
		return type == Reference && referenceValue->type == Integer;
	}

	bool UnuVar::IsListReference()
	{
		return type == Reference && referenceValue->type == List;
	}

	UnuVar UnuVar::GetReferenceValue()
	{
		return *referenceValue;
	}

	size_t UnuVar::GetReferencedListSize()
	{
		return referenceValue->listValue.size();
	}

	UnuVar UnuVar::GetItemReferenceAt(int index)
	{
		if (IsListReference())
			return UnuVar(&(referenceValue->listValue[index]));
		else if (IsList())
			return UnuVar(&(listValue[index]));
		else
			return UnuVar(nullptr);
	}

	bool UnuVar::IsSameReference(UnuVar a, UnuVar b)
	{
		return a.referenceValue == b.referenceValue;
	}
}