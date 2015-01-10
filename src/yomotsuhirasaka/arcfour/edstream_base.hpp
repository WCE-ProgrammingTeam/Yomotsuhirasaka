#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "estreambuf.hpp"
#include "../detail/endian.hpp"
#include "../detail/manipulator.hpp"

namespace yomotsuhirasaka	{
namespace arcfour			{

template<class Allocator>
class edstream_base
	: public std::basic_iostream<int8_t, std::char_traits<int8_t>>
{
private:
	typedef edstream_base<Allocator> this_type;
	typedef uint8_t byte;

protected:
	typedef estreambuf<Allocator>* ebuf_ptr;
	typedef typename estreambuf<Allocator>::traits_type traits_type;

public:
	edstream_base()
		: basic_iostream(new estreambuf<Allocator>{})
		{}

	template<class RandomAccessRange>
	explicit edstream_base(const RandomAccessRange& key_)
		: basic_iostream(new estreambuf<Allocator>{key_})
		{}

	edstream_base(edstream_base& another)=default; // copy constructor

	virtual ~edstream_base()
		{}

public:
	template<class RandomAccessRange>
	void set_key(const RandomAccessRange& key)
		{
			reinterpret_cast<ebuf_ptr>(rdbuf())->set_key(key);
		}

   void end_of_data()
		{}

public:
	this_type& operator<<(byte val)
		{
			rdbuf()->sputc(val);
			return *this;
		}

	this_type& operator<<(char val)
		{
			rdbuf()->sputc(val);
			return *this;
		}

	template<typename T, typename SFINAE=typename std::enable_if<std::is_integral<T>::value>::type>
	this_type& operator<<(T& val)
		{
			byte temp[sizeof(T)];
			::yomotsuhirasaka::detail::to_big_endian(val, temp);
			for(uint16_t i=0; i<sizeof(T); ++i) operator<<(temp[i]);
			return *this;
		}

public:
	this_type& operator>>(byte& val)
		{
			char temp=traits_type::to_char_type(rdbuf()->snextc());
			val=static_cast<byte>(temp);
			return *this;
		}

	this_type& operator>>(char& val)
		{
			val=traits_type::to_char_type(rdbuf()->snextc());
			return *this;
		}

	template<typename T, typename SFINAE=typename std::enable_if<std::is_integral<T>::value>::type>
	this_type& operator>>(T& val)
		{
			byte temp[sizeof(T)];
			for(uint16_t i=0; i<sizeof(T); ++i)
			{
				assert(reinterpret_cast<ebuf_ptr>(rdbuf())->eof() && "buffer is too small.");
				operator>>(temp[i]);
			}
			T res=*reinterpret_cast<T*>(temp);
			::yomotsuhirasaka::detail::to_local_endian(res, temp, true);
			val=res;

			return *this;
		}
};

namespace detail	{
// operator<<
template<class Container, class StreamAllocator>
edstream_base<StreamAllocator>& op_in(edstream_base<StreamAllocator>& stream, Container& container)
{
	for(auto val : container) stream<<val;
	return stream;
}

// operator>>
template<typename T, class Container, class StreamAllocator>
edstream_base<StreamAllocator>& op_out(edstream_base<StreamAllocator>& stream, Container& container)
{
	while(!reinterpret_cast<estreambuf<StreamAllocator>*>(stream.rdbuf())->eof())
	{
		T temp{};
		stream>>temp;
		container.push_back(temp);
	}
	return stream;
}
} // namespace detail

template<class StreamAllocator>
edstream_base<StreamAllocator>& operator<<(edstream_base<StreamAllocator>& stream, const ::yomotsuhirasaka::key& k)
{
	stream.set_key(k.key_);
	return stream;
}

template<class StreamAllocator>
edstream_base<StreamAllocator>& operator<<(edstream_base<StreamAllocator>& stream, const ::yomotsuhirasaka::endd_t&)
{
	stream.end_of_data();
	return stream;
}

template<class StreamAllocator, typename CharT, class Traits, class StringAllocator>
edstream_base<StreamAllocator>& operator<<(edstream_base<StreamAllocator>& stream, std::basic_string<CharT, Traits, StringAllocator>& container)
{
	return detail::op_in(stream, container);
}

template<class StreamAllocator, typename T, class VectorAllocator>
edstream_base<StreamAllocator>& operator<<(edstream_base<StreamAllocator>& stream, std::vector<T, VectorAllocator>& container)
{
	return detail::op_in(stream, container);
}

template<class StreamAllocator, typename CharT, class Traits, class StringAllocator>
edstream_base<StreamAllocator>& operator>>(edstream_base<StreamAllocator>& stream, std::basic_string<CharT, Traits, StringAllocator>& container)
{
	return detail::op_out<CharT>(stream, container);
}

template<class StreamAllocator, typename T, class VectorAllocator>
edstream_base<StreamAllocator>& operator>>(edstream_base<StreamAllocator>& stream, std::vector<T, VectorAllocator>& container)
{
	return detail::op_out<T>(stream, container);
}

} } // namespace yomotsuhirasaka::arcfour
