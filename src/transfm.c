#include <stdlib.h>
#include <math.h>
#include "transfm.h"

#define PTOL 1e-6f

struct poly {
	int n;    /* number of vertices */
	float* vertex;  /* vertex[3*n] contains the coordinates of the vertices */
	float* u;    /* u[n] is the parametric coordinate of each vertex [0..1] */
	float lenght; /* size of the polyline */
};

Poly* create_poly_line(int n, float* vertex){
	Poly* p=(Poly*)malloc(sizeof(Poly));
	int i;
	p->n=n;
	p->vertex=(float*)malloc(3*n*sizeof(float));
	for(i=0;i<3*n;i++)
		p->vertex[i]=vertex[i];

	p->u=(float*)malloc(n*sizeof(float));
	p->u[0]=0;
	for (i=1;i<n;i++){
		float dx = vertex[3*i+0]-vertex[3*(i-1)+0];
		float dy = vertex[3*i+1]-vertex[3*(i-1)+1];
		float dz = vertex[3*i+2]-vertex[3*(i-1)+2];
		float delta_L = (float) sqrt(dx*dx+dy*dy+dz*dz);
		p->u[i]= p->u[i-1]+delta_L;
	}
	p->lenght=p->u[p->n-1];
	for (i=1; i<n; i++)
		p->u[i]/=p->lenght;

	return p;
}

int interpol_poly_line(Poly* p, float u, float resp[3]){
	int i;
	if (u<0||u>(1+PTOL)||p==NULL||p->n<2) return 0;
	for (i=1;i<p->n;i++) 
		if (u<=p->u[i]+PTOL){
			float t=(u-p->u[i-1])/(p->u[i]-p->u[i-1]);
			resp[0]= (1-t)*p->vertex[3*(i-1)+0]+t*p->vertex[3*i+0];
			resp[1]= (1-t)*p->vertex[3*(i-1)+1]+t*p->vertex[3*i+1];
			resp[2]= (1-t)*p->vertex[3*(i-1)+2]+t*p->vertex[3*i+2];
			return 1;
		}
	return 0;
}

int  tri_mesh_point(float u, float v, float w, Poly* f, Poly* g, Poly* h, float resp[3]){
	float fu[3],gv[3],hw[3];
	float f1_w[3],g1_u[3],h1_v[3];
	int i;
	

    if (fabs(u)<PTOL) 
        interpol_poly_line(h,w,resp);
    else if (fabs(v)<PTOL)
        interpol_poly_line(f,u,resp);
    else if (fabs(w)<PTOL)
        interpol_poly_line(g,v,resp);
    else {
        interpol_poly_line(f,u,fu);     /* f(u) */
        interpol_poly_line(f,1-w,f1_w); /* f(1-w) */
        interpol_poly_line(g,v,gv);     /* g(v) */
        interpol_poly_line(g,1-u,g1_u); /* g(1-u) */
        interpol_poly_line(h,w,hw);     /* h(w) */
        interpol_poly_line(h,1-v,h1_v); /* h(1-v) */
        for (i=0;i<3;i++) 
            resp[i]=( u*gv[i]/(1-v)+w*h1_v[i]/(1-v)+v*hw[i]/(1-w)
            +u*f1_w[i]/(1-w)+w*fu[i]/(1-u)+v*g1_u[i]/(1-u)
            -w*f->vertex[i] - u*g->vertex[i] -v*h->vertex[i])/2;
        }

	return 1;
}

#undef PTOL