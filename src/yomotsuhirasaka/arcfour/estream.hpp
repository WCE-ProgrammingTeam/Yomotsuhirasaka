#pragma once

#include <array>
#include <iterator>
#include <streambuf>

#include "arcfour.hpp"

namespace yomotsuhirasaka	{
namespace arcfour			{

class estream
	: protected std::basic_streambuf<uint8_t>
{
public:
	typedef estream this_type;
	typedef uint8_t type;

private:

public:
	template<class ForwardRange>
	this_type& operator<<()
		{}

	// ref : http://cpprefjp.github.io/reference/string/basic_string/op_istream.html
	template<class Container>
	this_type& operator>>()
		{}
};

} } // namespace yomotsuhirasaka::arcfour

