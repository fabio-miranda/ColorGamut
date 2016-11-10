#ifndef Color_H
#define Color_H

#include "Wavelength.h"
#include "Vec.h"
#include "Defines.h"

#include <vector>
#include <GL/glew.h>
#include <GL/glut.h>
#include <math.h>
#include <time.h>




class Color {

public:
	Color();
	void init(int tesselationLvl);
	void tesselate(std::vector<Vertex<float> >** vertices);
	void addTesselatedTriangle(int tesselationLevel, Vertex<float> vertex0, Vertex<float> vertex1, Vertex<float> vertex2);
	Vec3<float> XYZtosRGB(Vec3<float> valueXYZ);
	float rgbToRGB(float value);	
	Vec3<float> sRGBtoXYZ(Vec3<float> valueRGB);
	Vec3<float> LabtoXYZ(Vec3<float> valueLab);
	Vec3<float> XYZtoLab(Vec3<float> valueXYZ);
	Vec3<float> xyYtoXYZ(Vec3<float> valueXYZ);
	void setColorArrayLabtosRGB(std::vector<Vertex<float> >* verticesArray);
	void setColorArrayXYZtosRGB(std::vector<Vertex<float> >* verticesArray);
	void setColorArraysRGB(std::vector<Vertex<float> >* verticesArray);
	float RGBtorgb(float value);
	void render(short currentColorSpace);
	virtual void createGeometries() = 0;
	void createVBOs(float displacement);
	void createVBO(float displacement, std::vector<Vertex<float> >* vertices, GLuint* vboIdVertices, GLuint* vboIdVerticesNormalized, GLuint* vboIdColor);
	void clear();
	void changeAlpha(short currentColorSpace);
	

	static const float matrix_XYZtosRGB[];
	static const float matrix_sRGBtoXYZ[];
	static const float array_referenceWhiteD65[];
	

	std::vector<Vec3<float> >* m_values;
	std::vector<Vertex<float> >* m_vertices;
	std::vector<Vertex<float> >* m_verticesXYZColorSpace;
	std::vector<Vertex<float> >* m_verticessRGBColorSpace;
	std::vector<Vertex<float> >* m_verticesLabColorSpace;

	GLuint m_vboIdVerticesXYZ;
	GLuint m_vboIdVerticesLab;
	GLuint m_vboIdVerticessRGB;
	GLuint m_vboIdVerticesNormalizedXYZ;
	GLuint m_vboIdVerticesNormalizedLab;
	GLuint m_vboIdVerticesNormalizedsRGB;
	GLuint m_vboIdColorXYZ;
	GLuint m_vboIdColorLab;
	GLuint m_vboIdColorsRGB;


	bool m_show;
	bool m_normalized;
	float m_alpha;
	int m_tesselationLvl;
	int m_renderType;
private:


};


#endif