#include "sRGB.h"




sRGB::sRGB(int tesselationLvl){
	Color::init(tesselationLvl);

	createGeometries();
	
}

void sRGB::createGeometries(){
	
	createTriangles();
	
	for(int i=0; i<m_tesselationLvl; i++){
		tesselate(&m_vertices);
	}
	
	toXYZColorSpace();
	toLabColorSpace();
	tosRGBColorSpace();

	setColorArraysRGB(m_verticessRGBColorSpace);
	setColorArrayXYZtosRGB(m_verticesXYZColorSpace);
	setColorArrayLabtosRGB(m_verticesLabColorSpace);

	createVBOs(0.01);

	
}

void sRGB::createTriangles(){
	
	m_vertices = new std::vector<Vertex<float> >();
	int tesselationLevel = 0;
	
	addTesselatedTriangle(tesselationLevel, Vertex<float>(0, 0, 0), Vertex<float>(1, 1, 0), Vertex<float>(1, 0, 0));
	addTesselatedTriangle(tesselationLevel, Vertex<float>(0, 0, 0), Vertex<float>(0, 1, 0), Vertex<float>(1, 1, 0));
	
	
	addTesselatedTriangle(tesselationLevel, Vertex<float>(0, 0, 1), Vertex<float>(1, 0, 1), Vertex<float>(1, 1, 1));
	addTesselatedTriangle(tesselationLevel, Vertex<float>(0, 0, 1), Vertex<float>(0, 1, 1), Vertex<float>(1, 1, 1));
	
	addTesselatedTriangle(tesselationLevel, Vertex<float>(0, 0, 0), Vertex<float>(0, 0, 1), Vertex<float>(0, 1, 1));
	addTesselatedTriangle(tesselationLevel, Vertex<float>(0, 0, 0), Vertex<float>(0, 1, 0), Vertex<float>(0, 1, 1));
	
	addTesselatedTriangle(tesselationLevel, Vertex<float>(1, 0, 0), Vertex<float>(1, 0, 1), Vertex<float>(1, 1, 1));
	addTesselatedTriangle(tesselationLevel, Vertex<float>(1, 0, 0), Vertex<float>(1, 1, 0), Vertex<float>(1, 1, 1));
	
	addTesselatedTriangle(tesselationLevel, Vertex<float>(0, 1, 0), Vertex<float>(1, 1, 0), Vertex<float>(1, 1, 1));
	addTesselatedTriangle(tesselationLevel, Vertex<float>(0, 1, 0), Vertex<float>(0, 1, 1), Vertex<float>(1, 1, 1));

	addTesselatedTriangle(tesselationLevel, Vertex<float>(0, 0, 0), Vertex<float>(1, 0, 0), Vertex<float>(1, 0, 1));
	addTesselatedTriangle(tesselationLevel, Vertex<float>(0, 0, 0), Vertex<float>(0, 0, 1), Vertex<float>(1, 0, 1));
	
}

float sRGB::rgbToRGB(float value){

	//float vc =(value>0?value:-value);
	float vc = value;

	if(value <= 0.0031308){
		vc = 12.92 * value;
	}
	else{
		vc = (1.055 * pow(vc, 1.0f/2.4f)) - 0.055; 
	}

	//return (value>0?vc:-vc);
	return vc;
}

Vec3<float> sRGB::XYZtosRGB(Vec3<float> valueXYZ){

	Vec3<float> clamped = Vec3<float>(valueXYZ.x, valueXYZ.y, valueXYZ.z);
	/*
	if(valueXYZ.x > 1.0) clamped.x = 1.0;
	else if(valueXYZ.x < 0) clamped.x = 0;
	if(valueXYZ.y > 1.0) clamped.y = 1.0;
	else if(valueXYZ.y < 0) clamped.y = 0;
	if(valueXYZ.z > 1.0) clamped.z = 1.0;
	else if(valueXYZ.z < 0) clamped.z = 0;
	*/

	float r, g, b;
	r = (matrix_XYZtosRGB[0] * clamped.x + matrix_XYZtosRGB[1] * clamped.y + matrix_XYZtosRGB[2] * clamped.z);
	g = (matrix_XYZtosRGB[3] * clamped.x + matrix_XYZtosRGB[4] * clamped.y + matrix_XYZtosRGB[5] * clamped.z);
	b = (matrix_XYZtosRGB[6] * clamped.x + matrix_XYZtosRGB[7] * clamped.y + matrix_XYZtosRGB[8] * clamped.z);
	

	return Vec3<float>(rgbToRGB(r), rgbToRGB(g), rgbToRGB(b));

}


void sRGB::toRGB(){



}

void sRGB::toXYZColorSpace(){
	
	m_verticesXYZColorSpace = new std::vector<Vertex<float> >();
	for(int i=0; i<m_vertices->size(); i++){
		
		Vec3<float> XYZ = sRGBtoXYZ(m_vertices->at(i).pos);
		m_verticesXYZColorSpace->push_back(Vertex<float>(XYZ.x, XYZ.y, XYZ.z));

	}
}

void sRGB::tosRGBColorSpace(){

	m_verticessRGBColorSpace = new std::vector<Vertex<float> >();
	for(int i=0; i<m_vertices->size(); i++){
		
		m_verticessRGBColorSpace->push_back(Vertex<float>(m_vertices->at(i)));
	}

}

void sRGB::toLabColorSpace(){
	
	m_verticesLabColorSpace = new std::vector<Vertex<float> >();
	for(int i=0; i<m_vertices->size(); i++){
		
		Vec3<float> Lab = XYZtoLab(sRGBtoXYZ(m_vertices->at(i).pos));
		m_verticesLabColorSpace->push_back(Vertex<float>(Lab.x, Lab.y, Lab.z));
	}
}