/* Copyright (c) 2014 Fabian Schuiki */
#include <cairo/cairo.h>
#include <gamma/vector.hpp>
#include <iostream>
#include <list>
#include <map>

namespace anium {

using namespace gamma::convenience;

struct renderer;

struct view
{
	vector2i position;
	vector2i size;
	bool buffered;
	view(): buffered(false) {}
	virtual void draw(cairo_t* cr, renderer* rnd) {}
};

struct renderer
{
	view* subject;
	std::map<view*, renderer*> children;
	cairo_surface_t* buffer;

	renderer(): subject(NULL), buffer(NULL) {}
	renderer(view* subject): subject(subject), buffer(NULL) {}

	void draw(cairo_t* cr = NULL)
	{
		cairo_t* target = cr;
		if (subject->buffered || !cr) {
			if (!buffer) {
				buffer = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, subject->size.x, subject->size.y);
			}
		} else {
			if (buffer) {
				cairo_surface_destroy(buffer);
				buffer = NULL;
			}
		}
		if (buffer) {
			target = cairo_create(buffer);
		}
		if (cr) {
			cairo_save(cr);
			cairo_translate(cr, subject->position.x, subject->position.y);
		}

		subject->draw(target, this);

		if (buffer) {
			cairo_destroy(target);
		}
		if (cr && target != cr) {
			cairo_set_source_surface(cr, buffer, 0, 0);
			cairo_paint(cr);
		}
		if (cr) {
			cairo_restore(cr);
		}
	}

	renderer* child(view* v)
	{
		std::map<view*, renderer*>::iterator it = children.find(v);
		if (it != children.end())
			return it->second;
		renderer*& r = children[v];
		r = new renderer(v);
		return r;
	}
};

struct button : public view
{
	virtual void draw(cairo_t* cr, renderer* rnd)
	{
		cairo_rectangle(cr, 0, 0, size.x, size.y);
		cairo_set_source_rgb(cr, 0.75, 0.75, 0.75);
		cairo_fill(cr);
		cairo_rectangle(cr, 0, 0, size.x, size.y);
		cairo_set_source_rgb(cr, 0, 0, 0);
		// cairo_set_line_width(cr, 3.0);
		cairo_stroke(cr);
	}
};

struct window : public view
{
	view* content;
	window(): content(NULL) {}
	virtual void draw(cairo_t* cr, renderer* rnd)
	{
		cairo_rectangle(cr, 0, 0, size.x, size.y);
		cairo_set_source_rgb(cr, 1, 1, 1);
		cairo_fill(cr);

		if (!content) return;
		rnd->child(content)->draw(cr);
	}
};

struct canvas : public view
{
	std::list<view*> children;
	virtual void draw(cairo_t* cr, renderer* rnd)
	{
		for (std::list<view*>::iterator it = children.begin(); it != children.end(); it++)
			rnd->child(*it)->draw(cr);
	}
};

} // namespace anium

using namespace gamma::convenience;

int main()
{
	anium::button button;
	button.position = vector2i(50,50);
	button.size = vector2i(150,30);

	anium::canvas canvas;
	canvas.position = vector2i(20, 20);
	canvas.size = vector2i(250, 250);
	canvas.children.push_back(&button);

	anium::window window;
	window.buffered = true;
	window.position = vector2i(200, 100);
	window.size = canvas.size + 2*canvas.position;
	window.content = &canvas;

	anium::canvas screen;
	screen.size = vector2i(640,480);
	screen.children.push_back(&window);

	// create the rendering tree
	anium::renderer renderer(&screen);
	renderer.draw();
	cairo_surface_write_to_png(renderer.buffer, "test-cairo.png");

	// cairo_surface_t* surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 250, 250);
	// cairo_t* cr = cairo_create(surface);

	// cairo_move_to(cr, 50.0, 75.0);
	// cairo_line_to(cr, 200.0, 75.0);

	// cairo_move_to(cr, 50.0, 125.0);
	// cairo_line_to(cr, 200.0, 125.0);

	// cairo_move_to(cr, 50.0, 175.0);
	// cairo_line_to(cr, 200.0, 175.0);

	// cairo_set_line_width(cr, 30.0);
	// cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);
	// cairo_stroke(cr);

	// cairo_surface_write_to_png(surface, "test-cairo.png");
	// cairo_destroy(cr);
	// cairo_surface_destroy(surface);

	return 0;
}