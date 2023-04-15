#include <cairo.h>
#include <cairo-svg.h>
#include <cmath>

const double PI = 3.14159265358979323846;

void branch(cairo_t* beetle, double x, double y, double angle, int depth)
{
    if (depth < 1) return;

    double x2 = x + std::cos(angle) * depth * 10;
    double y2 = y + std::sin(angle) * depth * 10;

    cairo_move_to(beetle, x, y);
    cairo_line_to(beetle, x2, y2);
    cairo_stroke(beetle);

    branch(beetle, x2, y2, angle - 0.4, depth - 1);
    branch(beetle, x2, y2, angle + 0.4, depth - 1);
}

int main()
{
    

    cairo_surface_t* surface = cairo_svg_surface_create("fractal.svg", 2000, 2000);
    cairo_t* beetle = cairo_create(surface);
    cairo_set_source_surface(beetle, surface, 0, 0);
    cairo_paint(beetle);

    cairo_set_source_rgb(beetle, 0, 0, 0);
    cairo_set_line_width(beetle, 1);

    double x = 250;
    double y = 500;
    double angle = -PI/2;

    for(int i = 0; i < 4; i++){
        branch(beetle, x, y, angle + (i * PI * .5), 10);
    };

    



    cairo_surface_finish(surface);
    cairo_destroy(beetle);
    cairo_surface_destroy(surface);

    return 0;
}
