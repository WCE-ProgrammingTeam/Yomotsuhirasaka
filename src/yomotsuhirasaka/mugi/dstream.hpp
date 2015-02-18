#pragma once

#include <memory>
#include "estream.hpp"

namespace yomotsuhirasaka	{
namespace mugi			{

template<class Allocator=std::allocator<int8_t>>
using dstream=estream<Allocator>;

} } // namespace yomotsuhirasaka::mugi