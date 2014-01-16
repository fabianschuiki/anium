/* Copyright (c) 2014 Fabian Schuiki */
#pragma once
#include "view.hpp"
#define ANIUM_HAS_WINDOW

namespace anium {

struct window : public view
{
	typedef boost::shared_ptr<window> ptr;
	view::ptr content;
};

} // namespace anium