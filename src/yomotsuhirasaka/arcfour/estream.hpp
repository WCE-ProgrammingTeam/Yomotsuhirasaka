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

template<class Allocator=std::allocator<int8_t>>
class estream
	: public std::basic_iostream<int8_t, std::char_traits<int8_t>>
{
private:
	typedef estream<Allocator> this_type;
	typedef uint8_t byte;

private:
	typedef estreambuf<Allocator>* ebuf_ptr;
	typedef typename estreambuf<Allocator>::traits_type traits_type;

public:
	estream()
		: basic_iostream(new estreambuf<Allocator>{})
		{}

	template<class RandomAccessRange>
	explicit estream(const RandomAccessRange& key_)
		: basic_iostream(new estreambuf<Allocator>{key_})
		{}

	estream(estream& another)=default; // copy constructor

	virtual ~estream()
		{}

public:
	this_type& operator<<(const ::yomotsuhirasaka::key& k)
		{
			reinterpret_cast<ebuf_ptr>(rdbuf())->set_key(k.key_);
			return *this;
		}

	this_type& operator<<(const ::yomotsuhirasaka::endd_t&)
		{
			return *this;
		}

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
			detail::to_big_endian(val, temp);
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
			detail::to_local_endian(res, temp, true);
			val=res;

			return *this;
		}
};

namespace detail	{
// operator<<
template<class Container, class StreamAllocator>
estream<StreamAllocator>& op_in(estream<StreamAllocator>& stream, Container& container)
{
	for(auto val : container) stream<<val;
	return stream;
}

// operator>>
template<typename T, class Container, class StreamAllocator>
estream<StreamAllocator>& op_out(estream<StreamAllocator>& stream, Container& container)
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

template<class StreamAllocator, typename CharT, class Traits, class StringAllocator>
estream<StreamAllocator>& operator<<(estream<StreamAllocator>& stream, std::basic_string<CharT, Traits, StringAllocator>& container)
{
	return detail::op_in(stream, container);
}

template<class StreamAllocator, typename T, class VectorAllocator>
estream<StreamAllocator>& operator<<(estream<StreamAllocator>& stream, std::vector<T, VectorAllocator>& container)
{
	return detail::op_in(stream, container);
}

template<class StreamAllocator, typename CharT, class Traits, class StringAllocator>
estream<StreamAllocator>& operator>>(estream<StreamAllocator>& stream, std::basic_string<CharT, Traits, StringAllocator>& container)
{
	return detail::op_out<CharT>(stream, container);
}

template<class StreamAllocator, typename T, class VectorAllocator>
estream<StreamAllocator>& operator>>(estream<StreamAllocator>& stream, std::vector<T, VectorAllocator>& container)
{
	return detail::op_out<T>(stream, container);
}

} } // namespace yomotsuhirasaka::arcfour
