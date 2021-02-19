#include "UnuException.h"

using std::vector;

namespace Unu
{
	UnuException::UnuException(string message) : message(message) {}
	const char* UnuException::what() { return message.c_str(); }

	ParseException::ParseException(string message) : UnuException(message) {}
	EvaluationException::EvaluationException(string message) : UnuException(message) {}
}