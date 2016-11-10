#include "Munsell.h"

Munsell::Munsell(int tesselationLvl, char* fileName, int n){
	
	readFileMunsell(fileName);
	toLabColorSpace();
	tosRGBColorSpace();
	toXYZColorSpace();
	SegmentMaximaColor::init(tesselationLvl, n);
	
}

void Munsell::readFileMunsell(char* fileName){

	m_values = new std::vector<Vec3<float> >();

	std::ifstream* file = new std::ifstream(fileName, std::ifstream::in);
	std::string value;
	while ( file->good() ){
		getline(*file, value, ';' );
		if(value == "") break;
		float hue = atof(value.c_str());
		getline(*file, value, ';' );
		const char* RP = value.c_str();
		getline(*file, value, ';' );
		float V = atof(value.c_str());
		getline(*file, value, ';' );
		float C = atof(value.c_str());
		getline(*file, value, ';' );
		float x = atof(value.c_str());
		getline(*file, value, ';' );
		float y = atof(value.c_str());
		getline(*file, value, ';' );
		float Y = atof(value.c_str());


		m_values->push_back(Vec3<float>(x, y, Y/100.0));
	}
	file->close();
}

