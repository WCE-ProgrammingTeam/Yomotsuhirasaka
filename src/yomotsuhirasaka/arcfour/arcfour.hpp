#pragma once

#include <cmath> // for std::ceil
#include <algorithm> // for std::swap
#include <array>
#include <iterator>

namespace yomotsuhirasaka	{
namespace arcfour			{

class arcfour_gen
{
public:
	typedef uint8_t type;

private:
	type x_;
	type y_;
	std::array<type, 0x100> state_;

public:
	arcfour_gen() = default;

	template<class RandomAccessRange>
	arcfour_gen(const RandomAccessRange& key)
		{
			init(key);
		}

	~arcfour_gen()
		{
			x_=0; y_=0;
			for(type i=0; i<0x100; ++i) state_[i]=i;
		}

public:
	template<class RandomAccessRange>
	void init(const RandomAccessRange& key)
		{
			x_=0; y_=0;
			for(type i=0; i<0x100; ++i) state_[i]=i;

			type state_index=0; type key_index=0;
			auto head_itr=std::begin(key);
			const uint32_t length=std::distance(std::begin(key), std::end(key));
			const uint32_t loop_time=std::ceil(static_cast<double>(length)/0x100)*0x100;

			for(uint32_t i=0; i<loop_time; ++i)
			{
				state_index+=*std::advance(head_itr, key_index)+state_[i];
				std::swap(state_[state_index], state_[i]);

				++key_index;
				if(key_index>=length) key_index=0;
			}
		}

	type operator()()
		{
			x_+=1;
			y_+=state_[x_];
			std::swap(state_[x_], state_[y_]);

			return state_[(state_[x_]+state_[y_])&0xFF];
		}
};

} } // namespace yomotsuhirasaka::arcfour
