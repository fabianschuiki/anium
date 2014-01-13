/* Copyright (c) 2014 Fabian Schuiki */
#pragma once
#include "view.hpp"
#define ANIUM_HAS_BUTTON

namespace anium {

struct button : public view
{
	typedef boost::shared_ptr<button> ptr;
};

} // namespace anium