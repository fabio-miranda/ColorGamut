#ifndef sRGB_H
#define sRGB_H

#include <vector>
#include <GL/glew.h>
#include <GL/glut.h>
#include <math.h>

#include "Wavelength.h"
#include "Vec.h"
#include "Color.h"
#include "Defines.h"




class sRGB : public Color{

public:
	sRGB(int tesselationLvl);
	Vec3<float> XYZtosRGB(Vec3<float> valueXYZ);
	float rgbToRGB(float value);
	void createTriangles();
	void createGeometries();
	void toRGB();
	void toXYZColorSpace();
	void toLabColorSpace();
	void tosRGBColorSpace();

	Wavelength** waveLength;
									

private:


};




#endif