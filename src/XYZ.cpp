#include "XYZ.h"

XYZ::XYZ(char* fileName){
	readFileSpectrum(fileName);
	Color::init(0);

	allSpectrumToXYZ(380, 780);
	createTriangles();
	toRGB();
}

void XYZ::readFileSpectrum(char* fileName){

	m_wavelengths = new Wavelength*[531];
	
	std::ifstream* file = new std::ifstream(fileName, std::ifstream::in);
	std::string value;
	int i = 0;
	while ( file->good() ){
		getline(*file, value, ';' );
		if(value == "") break;
		int nm = atoi(value.c_str());
		getline(*file, value, ';' );
		float CIE_A = atof(value.c_str());
		getline(*file, value, ';' );
		float CIE_D65 = atof(value.c_str());
		getline(*file, value, ';' );
		float Vm = atof(value.c_str());
		getline(*file, value, ';' );
		float Vlinha = atof(value.c_str());
		getline(*file, value, ';' );
		float CIE2_x_bar = atof(value.c_str());
		getline(*file, value, ';' );
		float CIE2_y_bar = atof(value.c_str());
		getline(*file, value, ';' );
		float CIE2_z_bar = atof(value.c_str());
		getline(*file, value, ';' );
		float CIE10_x_bar = atof(value.c_str());
		getline(*file, value, ';' );
		float CIE10_y_bar = atof(value.c_str());
		getline(*file, value, ';' );
		float CIE10_z_bar = atof(value.c_str());


		m_wavelengths[i] = new Wavelength(nm, CIE_A, CIE_D65, Vm, Vlinha, CIE2_x_bar, CIE2_y_bar, CIE2_z_bar, CIE10_x_bar, CIE10_y_bar, CIE10_z_bar);
		i++;
	}
	file->close();
}

void XYZ::createGeometries(){

}



void XYZ::allSpectrumToXYZ(int p_bottom, int p_top){

	m_values = new std::vector<Vec3<float> >();
	/*
	float* spectrum = new float[401];
	for(int i=0; i<401; i++){
		spectrum[i] = p_wavelengths[p_top - p_bottom - 300 + i]->CIE_D65;
	}

	for(int i=0; i<p_top - p_bottom; i++){
		float X, Y, Z;
		//ccGetCIEXYZfromLambda(p_bottom + i, &X, &Y, &Z);
		ccGetCIEXYZfromSpectrum(spectrum, &X, &Y, &Z);
		colors[i] = new Vec3<float>(X, Y , Z);
	}
	*/
	/*
	float n = 0;
	
	for(int i=0; i< p_top - p_bottom; i++){
		n += p_wavelengths[81+i]->CIE10_y_bar * p_wavelengths[81+i]->CIE_D65;
	}
	*/

	for(int i=0; i< p_top - p_bottom; i++){
		m_values->push_back(Vec3<float>(0,0,0));
		/*
		m_values->at(i).x = p_wavelengths[81 + i]->CIE10_x_bar * p_wavelengths[81 + i]->CIE_D65 * 1.0;
		m_values->at(i).y = p_wavelengths[81 + i]->CIE10_y_bar * p_wavelengths[81 + i]->CIE_D65 * 1.0;
		m_values->at(i).z = p_wavelengths[81 + i]->CIE10_z_bar * p_wavelengths[81 + i]->CIE_D65 * 1.0;

		
		m_values->at(i).x = (1.0/n)*m_values->at(i).x;
		m_values->at(i).y = (1.0/n)*m_values->at(i).y;
		m_values->at(i).z = (1.0/n)*m_values->at(i).z;
		*/
		
		Vec3<float> xyz = Vec3<float>(m_wavelengths[81 + i]->CIE2_x_bar, m_wavelengths[81 + i]->CIE2_y_bar, m_wavelengths[81 + i]->CIE2_z_bar);

		float x = xyz.x/(xyz.x+xyz.y+xyz.z);
		float y = xyz.y/(xyz.x+xyz.y+xyz.z);

		//TODO: Check this multiplication by 10.0
		//m_values->at(i).y = (xyz.y>0.1f)?xyz.y:10.0; 
		m_values->at(i).y = 10.0 * xyz.y;
		m_values->at(i).x = (x/y)*(m_values->at(i).y);
		m_values->at(i).z = ((1.0-x-y)/y)*(m_values->at(i).y);
		
	}

}

void XYZ::createTriangles(){

	m_vertices = new std::vector<Vertex<float> >();
	for(int i=0; i<m_values->size()-1; i++){
		
		m_vertices->push_back(Vertex<float>(0,0,0));
		m_vertices->push_back(Vertex<float>(m_values->at(i).x, m_values->at(i).y, m_values->at(i).z));
		m_vertices->push_back(Vertex<float>(m_values->at(i+1).x, m_values->at(i+1).y, m_values->at(i+1).z));

	}

	m_verticesXYZColorSpace = m_vertices;

}

void XYZ::render(short currentColorSpace){
	
	//Not normalized
	
	glBegin(GL_TRIANGLES);
	//glColor3f(0, 0, 0);
	//glVertex3f(0, 0, 0);
	for(int i=0; i<m_vertices->size(); i++){
		//float sum = m_values->at(i).x + m_values->at(i).y + m_values->at(i).z;

		//glColor3f(1, 1, 1);
		glColor3f(m_vertices->at(i).color.x, m_vertices->at(i).color.y, m_vertices->at(i).color.z);
		glVertex3f(m_vertices->at(i).pos.x, m_vertices->at(i).pos.y, m_vertices->at(i).pos.z);
		//Vec3<float>* color = XYZtosRGB(m_values->at(i));
		//glColor3f(color.x, color.y, color.z);
		//glColor3f(m_values->at(i).x * 100.0 , m_values->at(i).y * 100.0 , m_values->at(i).z * 100.0 );
		//glVertex3f(m_values->at(i).x * 100.0 , m_values->at(i).y * 100.0, m_values->at(i).z * 100.0);
	}
	glEnd();
	

	/*	
	//Normalized
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0, 0, 0);
	glVertex3f(0, 0, 0);
	for(int i=0; i<m_values->size(); i++){
		glColor3f(valuesNormalizedArray[i].x, valuesNormalizedArray[i].y, valuesNormalizedArray[i].z);
		glVertex3f(valuesNormalizedArray[i].x, valuesNormalizedArray[i].y, valuesNormalizedArray[i].z);
	}
	glEnd();
	
	
	//Horseshoe
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1, 1, 1);
	glVertex3f(0.333333, 0.333333, 0.333333);
	for(int i=0; i<m_values->size(); i++){
		glColor3f(valuesNormalizedArray[i].x, valuesNormalizedArray[i].y, valuesNormalizedArray[i].z);
		glVertex3f(valuesNormalizedArray[i].x, valuesNormalizedArray[i].y, valuesNormalizedArray[i].z);
	}
	glEnd();
	

	//Line of purple
	glBegin(GL_TRIANGLES);
	glColor3f(valuesNormalizedArray[0].x, valuesNormalizedArray[0].y, valuesNormalizedArray[0].z);
	glVertex3f(valuesNormalizedArray[0].x, valuesNormalizedArray[0].y, valuesNormalizedArray[0].z);
	glColor3f(1, 1, 1);
	glVertex3f(0.333333, 0.333333, 0.333333);
	glColor3f(valuesNormalizedArray[numVertices-1].x, valuesNormalizedArray[numVertices-1].y, valuesNormalizedArray[numVertices-1].z);
	glVertex3f(valuesNormalizedArray[numVertices-1].x, valuesNormalizedArray[numVertices-1].y, valuesNormalizedArray[numVertices-1].z);
	glEnd();

	//Bottom
	glBegin(GL_TRIANGLES);
	glColor3f(0, 0, 0);
	glVertex3f(0, 0, 0);
	glColor3f(valuesNormalizedArray[0].x, valuesNormalizedArray[0].y, valuesNormalizedArray[0].z);
	glVertex3f(valuesNormalizedArray[0].x, valuesNormalizedArray[0].y, valuesNormalizedArray[0].z);
	glColor3f(valuesNormalizedArray[numVertices-1].x, valuesNormalizedArray[numVertices-1].y, valuesNormalizedArray[numVertices-1].z);
	glVertex3f(valuesNormalizedArray[numVertices-1].x, valuesNormalizedArray[numVertices-1].y, valuesNormalizedArray[numVertices-1].z);
	glEnd();
	*/

}

void XYZ::toRGB(){

	for(int i=0; i<m_vertices->size(); i++){
		
		Vec3<float> color = XYZtosRGB(m_vertices->at(i).pos);
		m_vertices->at(i).setColor(color.x, color.y, color.z);

	}

}

void XYZ::toLabColorSpace(){
	
	for(int i=0; i<m_vertices->size(); i++){
		
		Vec3<float> XYZ = XYZtoLab(m_vertices->at(i).pos);
		m_vertices->at(i).pos = XYZ;
	}
}

void XYZ::tosRGBColorSpace(){
	
	for(int i=0; i<m_vertices->size(); i++){
		
		Vec3<float> sRGB = XYZtosRGB(m_vertices->at(i).pos);
		m_vertices->at(i).pos = sRGB;
	}
}


