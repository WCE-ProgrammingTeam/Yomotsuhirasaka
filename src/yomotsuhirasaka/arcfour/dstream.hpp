#pragma once

#include <memory>
#include "edstream_base.hpp"

namespace yomotsuhirasaka	{
namespace arcfour			{

template<class Allocator=std::allocator<int8_t>>
class dstream
	: public edstream_base<Allocator>
{
private:
	typedef dstream<Allocator> this_type;
	using typename edstream_base<Allocator>::ebuf_ptr;

public:
	template<typename T, typename SFINAE=typename std::enable_if<std::is_integral<T>::value>::type>
	this_type& operator>>(T& val)
		{
			byte temp[sizeof(T)];
			for(uint16_t i=0; i<sizeof(T); ++i)
			{
				assert(reinterpret_cast<ebuf_ptr>(this->rdbuf())->eof() && "buffer is too small.");
				operator>>(temp[i]);
			}
			T res=*reinterpret_cast<T*>(temp);
			::yomotsuhirasaka::detail::to_local_endian(res, temp, true);
			val=res;

			return *this;
		}
};

} } // namespace yomotsuhirasaka::arcfour

