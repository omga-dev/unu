#include "UnuException.h"

using std::vector;

namespace Unu
{
	UnuException::UnuException(const string& message) : message(message) {}
	const char* UnuException::what() { return message.c_str(); }

	ParseException::ParseException(const string& message) : UnuException(message) {}
	EvaluationException::EvaluationException(const string&  message) : UnuException(message) {}
}