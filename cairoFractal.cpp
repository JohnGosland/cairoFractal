#include <cairo.h>
#include <cmath>
#include <cairo-svg.h>

const double PI = 3.14159265358979323846;

void branch(cairo_t* cr, double x, double y, double angle, int depth)
{
    if (depth == 0) return;

    double x2 = x + std::cos(angle) * depth * 10;
    double y2 = y + std::sin(angle) * depth * 10;

    cairo_move_to(cr, x, y);
    cairo_line_to(cr, x2, y2);
    cairo_stroke(cr);

    branch(cr, x2, y2, angle - 0.4, depth - 1);
    branch(cr, x2, y2, angle + 0.4, depth - 1);
}

int main()
{
    cairo_surface_t* surface = cairo_svg_surface_create("fractal.svg", 500, 500);
    cairo_t* cr = cairo_create(surface);

    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_set_line_width(cr, 1);

    double x = 250;
    double y = 500;
    double angle = -PI/2;

    branch(cr, x, y, angle, 10);

    cairo_surface_finish(surface);
    cairo_destroy(cr);
    cairo_surface_destroy(surface);

    return 0;
}
