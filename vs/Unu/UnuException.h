#pragma once

#include <iostream>
#include <vector>

using std::string;
using std::exception;

namespace Unu
{
	class UnuException : public exception
	{
		string message;
	public:
		UnuException(const string&  message);
		virtual const char* what();
	};

	class ParseException : public UnuException
	{
	public:
		ParseException(const string&  message);
	};

	class EvaluationException : public UnuException
	{
	public:
		EvaluationException(const string&  message);
	};
}