#include "KodakMinilab.h"

KodakMinilab::KodakMinilab(){

}

KodakMinilab::KodakMinilab(int tesselationLvl, char* fileName, int n){
	readFileKodakMinilab(fileName);

	SegmentMaximaColor::init(tesselationLvl, n);
}

void KodakMinilab::readFileKodakMinilab(char* fileName){

	m_values = new std::vector<Vec3<float> >();
	m_verticesXYZColorSpace = new std::vector<Vertex<float> >();
	m_verticesLabColorSpace = new std::vector<Vertex<float> >();
	m_verticessRGBColorSpace = new std::vector<Vertex<float> >();

	m_allPointsLabColorSpace = new std::vector<Vec3<float> >();
	m_allPointsXYZColorSpace = new std::vector<Vec3<float> >();
	m_allPointssRGBColorSpace = new std::vector<Vec3<float> >();

	std::ifstream* file = new std::ifstream(fileName, std::ifstream::in);
	std::string value;
	while ( file->good() ){
		getline(*file, value, ';' );
		if(value == "") break;
		const char* sampleId = value.c_str();
		getline(*file, value, ';' );
		const char* sampleName = value.c_str();
		getline(*file, value, ';' );
		float X = atof(value.c_str());
		getline(*file, value, ';' );
		float Y = atof(value.c_str());
		getline(*file, value, ';' );
		float Z = atof(value.c_str());
		getline(*file, value, ';' );
		float L = atof(value.c_str());
		getline(*file, value, ';' );
		float a = atof(value.c_str());
		getline(*file, value, ';' );
		float b = atof(value.c_str());
		getline(*file, value, ';' );
		float R = atof(value.c_str());
		getline(*file, value, ';' );
		float G = atof(value.c_str());
		getline(*file, value, ';' );
		float B = atof(value.c_str());

		//Vertex<float> vertexXYZ = Vertex<float>(X, Y, Z);
		Vertex<float> vertexLab = Vertex<float>(L, a, b);
		//Vertex<float> vertexsRGB = Vertex<float>(R/255.0, G/255.0, B/255.0);

		m_verticesLabColorSpace->push_back(vertexLab);
		m_allPointsLabColorSpace->push_back(vertexLab.pos);

		Vec3<float> vec3XYZ = Vec3<float>(0,0,0);
		vec3XYZ = LabtoXYZ(vertexLab.pos);
		m_verticesXYZColorSpace->push_back(Vertex<float>(vec3XYZ.x, vec3XYZ.y, vec3XYZ.z));
		m_allPointsXYZColorSpace->push_back(vec3XYZ);
		
		Vec3<float> vec3sRGB = Vec3<float>(0,0,0);
		vec3sRGB = XYZtosRGB(vec3XYZ);
		m_verticessRGBColorSpace->push_back(Vertex<float>(vec3sRGB.x, vec3sRGB.y, vec3sRGB.z));
		m_allPointssRGBColorSpace->push_back(vec3sRGB);
	}
	file->close();
}