#pragma once

#include <memory>
#include "edstream_base.hpp"

namespace yomotsuhirasaka	{
namespace arcfour			{

template<class Allocator=std::allocator<int8_t>>
class estream
	:public edstream_base<Allocator>
{
private:
	typedef estream<Allocator> this_type;

public:
	template<typename T, typename SFINAE=typename std::enable_if<std::is_integral<T>::value>::type>
	this_type& operator<<(T& val)
		{
			byte temp[sizeof(T)];
			::yomotsuhirasaka::detail::to_big_endian(val, temp);
			for(uint16_t i=0; i<sizeof(T); ++i) operator<<(temp[i]);
			return *this;
		}
};

} } // namespace yomotsuhirasaka::arcfour

