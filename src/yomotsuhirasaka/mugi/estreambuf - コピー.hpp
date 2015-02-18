#pragma once

#include <iostream>
#include <sstream>
#include <array>
#include <vector>
#include <memory> // for std::allocator

#include "mugi_gen.hpp"

namespace yomotsuhirasaka	{
namespace mugi			{

template<typename Allocator=std::allocator<int8_t>>
class estreambuf
	: public std::basic_streambuf<int8_t, std::char_traits<int8_t>>
{
public:
	typedef int8_t byte;

public:
	const static uint16_t block_size = 1;

private:
	mugi_gen gen_;

	std::array<int8_t, block_size> block_buffer_;
	std::vector<int8_t, Allocator> encrypted_buffer_;

	size_t current_block_index_;
	size_t current_putting_index_;
	size_t current_getting_index_;

public:
	estreambuf()=default;

	template<class RandomAccessRange>
	explicit estreambuf(const RandomAccessRange& key_, const RandomAccessRange& iv) :gen_(key, iv)
	{
	}

public:
	template<class RandomAccessRange>
	void init()
		{
			block_buffer_.fill(0);
			encrypted_buffer_.resize(4096, 0);
			
			int8_t* first=block_buffer_.data();
			setp(first, first); // pptr()==first, epptr()==last

			first=&encrypted_buffer_.front();
			setg(first, first, first+1);

			current_block_index_=0;
			current_putting_index_=0;
			current_getting_index_=0;

			gen_.init();//乱数生成器をinit()する set_key(), set_iv()後のinitが必要
		}

	template<class RandomAccessRange>
	void set_key(const RandomAccessRange& key)
		{
			gen_.set_key(key);
		}

	template<class RandomAccessRange>
	void set_iv(const RandomAccessRange& iv)
		{
			gen_.set_iv(iv);
		}
public:
	int_type overflow(int_type val)
		{
			if(val==traits_type::eof())
			{
				sync();
				return val; // return eof
			}

			block_buffer_[current_block_index_++]=traits_type::to_char_type(val);
			
			// 満杯になったので移し替える
			if(current_block_index_>=block_size)
			{
				encrypt_block_buffer();
				copy_block_to_encrypted();
				current_block_index_=0;
			}

			int8_t* current=&block_buffer_[current_block_index_];
			setp(current, current);

			return val;
		}

	int_type underflow()
		{
			if(eof()) return traits_type::eof();

			int8_t* current=&encrypted_buffer_[current_getting_index_];
			setg(&encrypted_buffer_.front(), current, current+1);

			return traits_type::to_int_type(encrypted_buffer_[current_getting_index_++]);
		}

public:
	int sync()
		{
			return 0;
		}

public:
	bool eof()
		{
			return (current_getting_index_>=current_putting_index_);
		}

private:
	void encrypt_block_buffer()
		{
			for(int8_t& v : block_buffer_) v^=gen_();
		}

	void copy_block_to_encrypted()
		{
			size_t buf_size=encrypted_buffer_.size();

			// resize
			if(current_getting_index_+block_size>=buf_size)
				encrypted_buffer_.resize(buf_size+64*block_size, 0);

			// copy
			for(size_t i=0; i<block_buffer_.size(); ++i)
			{
				encrypted_buffer_[current_putting_index_]=block_buffer_[i];
				++current_putting_index_;
			}
		}
};

} } // namespace yomotsuhirasaka::mugi
