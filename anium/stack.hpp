/* Copyright (c) 2014 Fabian Schuiki */
#pragma once
#include "view.hpp"
#include <vector>
#define ANIUM_HAS_STACK

namespace anium {

struct stack : public view
{
	typedef boost::shared_ptr<stack> ptr;
	std::vector<view::ptr> subviews;
};

} // namespace anium