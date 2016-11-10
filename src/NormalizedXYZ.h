#ifndef NormalizedXYZ_H
#define NormalizedXYZ_H

#include <vector>
#include <GL/glew.h>
#include <GL/glut.h>
#include <math.h>

#include "Wavelength.h"
#include "Vec.h"
#include "Color.h"
#include "Defines.h"

extern "C"{
	#include "transfm.h"
}


class NormalizedXYZ : public Color{

public:
	NormalizedXYZ();
	NormalizedXYZ(int tesselationLvl, std::vector<Vec3<float> >* valuesXYZ);
	void normalizeXYZ(std::vector<Vec3<float> >* valuesXYZ);
	void createTriangles();
	void createGeometries();
	void toRGB(std::vector<Vertex<float> >* verticesArray);
	void toLabColorSpace();
	void tosRGBColorSpace();
	void toXYZColorSpace();

	static const float matrix_XYZtosRGB[];


private:


};


#endif