#ifndef XYZ_H
#define XYZ_H

#include <vector>
#include <GL/glew.h>
#include <GL/glut.h>
#include <string>
#include <fstream>
#include <iostream>

#include "Wavelength.h"
#include "Vec.h"
#include "Color.h"


class XYZ : public Color{

public:
	XYZ(char* fileName);
	void readFileSpectrum(char* fileName);
	void allSpectrumToXYZ(int p_bottom, int p_top);
	void render(short currentColorSpace);
	void createTriangles();
	void toRGB();
	void toLabColorSpace();
	void tosRGBColorSpace();
	void createGeometries();

	Wavelength** m_wavelengths;

private:


};


#endif