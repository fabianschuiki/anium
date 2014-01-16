/* Copyright (c) 2014 Fabian Schuiki */
#pragma once
#include "view.hpp"
#include <boost/enable_shared_from_this.hpp>
#define ANIUM_HAS_RENDERER

namespace anium {
namespace renderer {

struct base;
typedef boost::shared_ptr<base> ptr;
static ptr make(const view::ptr& v);

struct base : boost::enable_shared_from_this<base>
{
	const view::ptr vw;

	base(const view::ptr& v): vw(v)
	{
	}

	ptr update(const view::ptr& v)
	{
		if (needs_update(v))
			return make(v);
		return shared_from_this();
	}

	virtual bool needs_update(const view::ptr& v)
	{
		return v != vw;
	}

	virtual void draw()
	{
		glColor3f(0,1,0);
		glBegin(GL_LINE_STRIP);
		vector2f p0 = vw->position, p1 = vw->position + vw->size;
		glVertex2f(p0.x, p0.y);
		glVertex2f(p1.x, p0.y);
		glVertex2f(p1.x, p1.y);
		glVertex2f(p0.x, p1.y);
		glVertex2f(p0.x, p0.y);
		glEnd();
	}
};

static ptr make(const view::ptr& v)
{
	return ptr(new base(v));
}

} // namespace renderer
} // namespace anium