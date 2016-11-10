#ifndef Transfm_H
#define Transfm_H

typedef struct poly Poly;

/* 
 * Creates a polygonal with n points 
 */
Poly* create_poly_line(int n, float* xyz);

/* 
 * Find a point in the polygonal according to 
 * the parameter u.  u=0 => first point.
 * u=1 => last point.
 */
int interpol_poly_line(Poly* p, float u, float resp[3]);

int  tri_mesh_point(float u, float v, float w, Poly* f, Poly* g, Poly* h, float resp[3]);


#endif