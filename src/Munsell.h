#ifndef Munsell_H
#define Munsell_H

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
#include "SegmentMaximaColor.h"




class Munsell : public SegmentMaximaColor{

public:
	Munsell(int tesselationLvl, char* fileName, int n);
	void readFileMunsell(char* fileName);

private:


};


#endif