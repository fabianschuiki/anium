/* Copyright (c) 2014 Fabian Schuiki */
#include <anium/event.hpp>
#include <anium/button.hpp>
#include <anium/stack.hpp>
#include <iostream>

int main()
{
	anium::button::ptr b0(new anium::button), b1(new anium::button);
	anium::stack::ptr s(new anium::stack);
	s->subviews.push_back(b0);
	s->subviews.push_back(b1);

	return 0;
}