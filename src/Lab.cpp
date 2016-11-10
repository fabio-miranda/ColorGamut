/*
#include "Lab.h"




Lab::Lab(){

}

void Lab::createTriangles(){
	
	m_vertices = new std::vector<Vertex<float>*>();
	int tesselationLevel = 0;
	
	addTesselatedTriangle(tesselationLevel, new Vertex<float>(0, 0, 0), new Vertex<float>(1, 1, 0), new Vertex<float>(1, 0, 0));
	addTesselatedTriangle(tesselationLevel, new Vertex<float>(0, 0, 0), new Vertex<float>(0, 1, 0), new Vertex<float>(1, 1, 0));
	
	
	addTesselatedTriangle(tesselationLevel, new Vertex<float>(0, 0, 1), new Vertex<float>(1, 0, 1), new Vertex<float>(1, 1, 1));
	addTesselatedTriangle(tesselationLevel, new Vertex<float>(0, 0, 1), new Vertex<float>(0, 1, 1), new Vertex<float>(1, 1, 1));
	
	addTesselatedTriangle(tesselationLevel, new Vertex<float>(0, 0, 0), new Vertex<float>(0, 0, 1), new Vertex<float>(0, 1, 1));
	addTesselatedTriangle(tesselationLevel, new Vertex<float>(0, 0, 0), new Vertex<float>(0, 1, 0), new Vertex<float>(0, 1, 1));
	
	addTesselatedTriangle(tesselationLevel, new Vertex<float>(1, 0, 0), new Vertex<float>(1, 0, 1), new Vertex<float>(1, 1, 1));
	addTesselatedTriangle(tesselationLevel, new Vertex<float>(1, 0, 0), new Vertex<float>(1, 1, 0), new Vertex<float>(1, 1, 1));
	
	addTesselatedTriangle(tesselationLevel, new Vertex<float>(0, 1, 0), new Vertex<float>(1, 1, 0), new Vertex<float>(1, 1, 1));
	addTesselatedTriangle(tesselationLevel, new Vertex<float>(0, 1, 0), new Vertex<float>(0, 1, 1), new Vertex<float>(1, 1, 1));

	addTesselatedTriangle(tesselationLevel, new Vertex<float>(0, 0, 0), new Vertex<float>(1, 0, 0), new Vertex<float>(1, 0, 1));
	addTesselatedTriangle(tesselationLevel, new Vertex<float>(0, 0, 0), new Vertex<float>(0, 0, 1), new Vertex<float>(1, 0, 1));
	
}



void Lab::render(){
	
	glBegin(GL_TRIANGLES);
	for(int i=0; i<m_vertices->size(); i++){

		glColor3f(m_vertices->at(i)->pos.x, m_vertices->at(i)->pos.y, m_vertices->at(i)->pos.z);
		glVertex3f(m_vertices->at(i)->pos.x, m_vertices->at(i)->pos.y, m_vertices->at(i)->pos.z);
	}
	glEnd();

}

void Lab::toRGB(){



}

void Lab::toXYZColorSpace(){
	
	for(int i=0; i<m_vertices->size(); i++){
		
		Vec3<float>* XYZ = LabtoXYZ(m_vertices->at(i)->pos);
		m_vertices->at(i)->pos = XYZ;
		
		

	}

}
*/