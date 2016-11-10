#ifndef KodakMinilab_H
#define KodakMinilab_H

#include <vector>
#include <GL/glew.h>
#include <GL/glut.h>
#include <string>
#include <fstream>
#include <iostream>

#include "Wavelength.h"
#include "Vec.h"
#include "Color.h"
#include "Defines.h"
#include "SegmentMaximaColor.h"




class KodakMinilab : public SegmentMaximaColor{

public:
	KodakMinilab();
	KodakMinilab(int tesselationLvl, char* fileName, int n);
	void readFileKodakMinilab(char* fileName);
	//void toLabColorSpace();
									

private:


};


#endif