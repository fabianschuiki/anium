/* Copyright (c) 2014 Fabian Schuiki */
#pragma once
#include <gamma/vector.hpp>
#define ANIUM_HAS_EVENT

namespace anium {

using gamma::convenience::vector2f;

struct pointer_button_event
{
	int button;
	bool down;
};

struct event
{
	enum event_type {
		kPointerButton,
	} type;
	vector2f position;
	union {
		pointer_button_event pointer_button;
	};
};

} // namespace anium