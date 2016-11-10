#ifndef SegmentMaximaColor_H
#define SegmentMaximaColor_H

#include <vector>
#include <GL/glew.h>
#include <GL/glut.h>
#include <string>
#include <fstream>
#include <iostream>
#include <math.h>

#include "Wavelength.h"
#include "Vec.h"
#include "Color.h"
#include "Defines.h"




class SegmentMaximaColor : public Color{

public:
	SegmentMaximaColor();
	SegmentMaximaColor(int tesselationLvl, int n);
	void init(int tesselationLvl, int n);
	void render(short currentColorSpace);
	void createTriangles(std::vector<Vertex<float> >** verticesToRender);
	void tosRGBColorSpace();
	void toXYZColorSpace();
	void toLabColorSpace();
	void calculateSphericalCoord(std::vector<Vertex<float> >* p_vertices, int n);
	void changeGBDSize();
	void createGeometries();
	void clear();
	int findClosestValue(int i, int j);
	void closeExtreme(std::vector<Vertex<float> >** verticesToRender, std::vector<Vertex<float> >* newVertices, int column);
					

	std::vector<SpherCoord<float> >* m_sphericalCoordLabColorSpace;
	std::vector<Vec3<float> >* m_allPointsLabColorSpace;
	std::vector<Vec3<float> >* m_allPointsXYZColorSpace;
	std::vector<Vec3<float> >* m_allPointssRGBColorSpace;
	int** m_gbdMatrix;
	int m_gbdMatrixSize;
	int m_n;
	bool m_showAllPoints;

private:


};


#endif