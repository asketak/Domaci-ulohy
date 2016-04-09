#include <cairo/cairo.h>
#include <math.h>

void writeFirstImage(){

    int size = 240;
    int steps = 8;
    float stepSize = size / 2 / steps;

    cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, size, size);
    cairo_t *cr = cairo_create (surface); 

    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_paint(cr);

    cairo_set_source_rgb (cr, 0, 0, 0);
    //cairo_set_line_size (cr, 1);

    for (int i = 0; i < steps; ++i)
    {
        cairo_move_to (cr, size/2, stepSize*i);
        cairo_line_to (cr, size/2+stepSize*i, size/2);
        cairo_move_to (cr, size/2, stepSize*i);
        cairo_line_to (cr, size/2-stepSize*i, size/2);
        cairo_stroke (cr);
    }

    for (int i = 0; i < steps; ++i)
    {
        cairo_move_to (cr, size/2, size - stepSize*i);
        cairo_line_to (cr, size/2+stepSize*i, size/2);
        cairo_move_to (cr, size/2, size - stepSize*i);
        cairo_line_to (cr, size/2-stepSize*i, size/2);
        cairo_stroke (cr);
    }

    cairo_move_to (cr, 0, size/2 );
    cairo_line_to (cr, size, size/2);
    cairo_stroke (cr);

    cairo_destroy (cr);
    cairo_surface_write_to_png (surface, "1.png");
    cairo_surface_destroy (surface);
}

void writeSecondImage(){

    int size = 240;

    cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, size, size);
    cairo_t *cr = cairo_create (surface); 
    cairo_set_source_rgb (cr, 0, 0, 0);
    cairo_paint(cr);


    cairo_pattern_t *r1; 
    r1 = cairo_pattern_create_radial(0, size, 50, size, size, 300);  
    cairo_pattern_add_color_stop_rgba(r1, 0, 1, 0, 0,1);
    cairo_pattern_add_color_stop_rgba(r1, 1, 0, 0, 0,0);
    cairo_set_source(cr, r1);
    cairo_arc(cr, 0, 0, 150, 0, M_PI * 2);
    cairo_paint(cr); 

    cairo_set_operator(cr, CAIRO_OPERATOR_ADD);
    cairo_pattern_t *r2; 
    r2 = cairo_pattern_create_radial(size, 0, 50, size, size, 300);  
    cairo_pattern_add_color_stop_rgba(r2, 0, 0, 0, 1,1);
    cairo_pattern_add_color_stop_rgba(r2, 1, 0, 0, 0,0);
    cairo_set_source(cr, r2);
    cairo_arc(cr, 0, 0, 150, 0, M_PI * 2);
    cairo_paint(cr); 


    cairo_destroy (cr);
    cairo_surface_write_to_png (surface, "2.png");
    cairo_surface_destroy (surface);
}

int
main (int argc, char *argv[]){
    writeFirstImage();
    writeSecondImage();
    return 0;
}

