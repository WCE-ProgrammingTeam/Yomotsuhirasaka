#pragma once

#include <algorithm>
#include <iterator>

namespace yomotsuhirasaka	{

struct endd_t {};
endd_t endd;

struct key
{
	std::vector<uint8_t> key_;

	template<typename ForwardRange>
	explicit key(const ForwardRange& range)
		: key_(range.begin(), range.end())
		{}
};

struct iv
{
	std::vector<uint8_t> iv_;

	template<typename ForwardRange>
	explicit iv(const ForwardRange& range)
		: iv_(range.begin(), range.end())
	{}
};

} // namespace yomotsuhirasaka
