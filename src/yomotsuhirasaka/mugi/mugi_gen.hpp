#pragma once

#include <algorithm> // for std::swap
#include <array>
#include <iterator>

namespace yomotsuhirasaka	{
namespace mugi			{

static const uint8_t key_length = 0x80;
static const uint8_t iv_length = 0x80;
static const uint8_t state_length = 0x80;

class mugi_gen
{
public:
	typedef uint8_t type;

private:
	std::array<type, key_length> key_;
	std::array<type, iv_length> iv_;
	std::array<type, state_length> state_;
public:
	mugi_gen() = default;

	template<class RandomAccessRange>
	mugi_gen(const RandomAccessRange& key, const RandomAccessRange& iv) :
		{
			set_key(key);
			set_iv(iv);
			init();
		}
	
	~mugi_gen()
		{
			for (uint8_t i = 0; i < key_length; ++i) key_[i] = static_cast<type>(i);
			for (uint8_t i = 0; i < iv_length; ++i) iv_[i] = static_cast<type>(i);
			for (uint8_t i = 0; i < state_length; ++i) state_[i] = static_cast<type>(i);
	}

public:
	mugi_gen& operator=(mugi_gen&& rhs)
		{
			key_ = rhs.key_;
			iv_ = rhs.iv_;
			state_ = rhs.state_;
			return *this;
		}

	void swap(mugi_gen& another)
		{
			std::swap(key_, another.key_);
			std::swap(iv_, another.iv_);
	}

public:

	//メンバのiv_とkey_を使って初期状態をセット
	void init()
		{
			//TODO
			for (uint8_t i = 0; i < state_length; ++i) state_[i] = key_[i] + iv_[i];	//temp
		}

	template<class RandomAccessRange>
	void set_key(const RandomAccessRange& key)
	{
		const uint32_t length = std::distance(std::begin(key), std::end(key));

		const uint32_t loop_time = std::min<uint32_t>(key_length, length);
		
		uint32_t i = 0;
		
		for (; i < loop_time; ++i) key_[i] = static_cast<type>(key[i]);
		for (; i < key_length; ++i) key_[i] = 0;	//padding
	}

	template<class RandomAccessRange>
	void set_iv(const RandomAccessRange& iv)
	{
		const uint32_t length = std::distance(std::begin(iv), std::end(iv));

		const uint32_t loop_time = std::min<uint32_t>(iv_length, length);

		uint32_t i = 0;

		for (; i < loop_time; ++i) iv_[i] = static_cast<type>(iv[i]);
		for (; i < iv_length; ++i) iv_[i] = 0;	//padding

		init();//ivをセットしたら初期状態を作成
	}

	//乱数生成
	type operator()()
	{
		//require set_key(key), set_iv(iv);

		//TODO
		return state_[rand()%state_length];	//temp
	
	}
};

} } // namespace yomotsuhirasaka::mugi
