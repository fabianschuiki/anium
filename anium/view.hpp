/* Copyright (c) 2014 Fabian Schuiki */
#pragma once
#include <gamma/vector.hpp>
#include <boost/shared_ptr.hpp>

namespace anium {

using namespace gamma::convenience;

struct view
{
	typedef boost::shared_ptr<view> ptr;
	vector2f position, size;
};

} // namespace anium