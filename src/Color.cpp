#include "Color.h"

const float Color::matrix_XYZtosRGB[] = {3.2404542,  -1.5371385, -0.4985314,
										-0.9692660,  1.8760108,  0.0415560,
										 0.0556434, -0.2040259,  1.0572252};

const float Color::matrix_sRGBtoXYZ[] = {0.4124564,  0.3575761,  0.1804375,
										 0.2126729,  0.7151522,  0.0721750,
										 0.0193339,  0.1191920,  0.9503041};

const float Color::array_referenceWhiteD65[] = {0.95047, 1.00000, 1.08883};

Color::Color(){


}

void Color::init(int tesselationLvl){
	
	m_show = false;
	m_alpha = 1.0;
	m_normalized = false;
	m_renderType = def_render_shade;
	m_tesselationLvl = tesselationLvl;

}

void Color::tesselate(std::vector<Vertex<float> >** vertices){
	
	std::vector<Vertex<float> >* newVertices = new std::vector<Vertex<float> >();
	//std::vector<Vec3<float>*>* newValues = new std::vector<Vec3<float>*>();
	for(int i=0; i<(*vertices)->size(); i+=3){
		
		Vertex<float> vertex0 = Vertex<float>((*vertices)->at(i).pos.x, (*vertices)->at(i).pos.y, (*vertices)->at(i).pos.z);
		Vertex<float> vertex1 = Vertex<float>((*vertices)->at(i+1).pos.x, (*vertices)->at(i+1).pos.y, (*vertices)->at(i+1).pos.z);
		Vertex<float> vertex2 = Vertex<float>((*vertices)->at(i+2).pos.x, (*vertices)->at(i+2).pos.y, (*vertices)->at(i+2).pos.z);


		//New vertices
		Vertex<float> vertex01 = Vertex<float>((vertex0.pos.x + vertex1.pos.x)/2.0, (vertex0.pos.y + vertex1.pos.y)/2.0, (vertex0.pos.z + vertex1.pos.z)/2.0);
		Vertex<float> vertex02 = Vertex<float>((vertex0.pos.x + vertex2.pos.x)/2.0, (vertex0.pos.y + vertex2.pos.y)/2.0, (vertex0.pos.z + vertex2.pos.z)/2.0);
		Vertex<float> vertex12 = Vertex<float>((vertex1.pos.x + vertex2.pos.x)/2.0, (vertex1.pos.y + vertex2.pos.y)/2.0, (vertex1.pos.z + vertex2.pos.z)/2.0);

		//add new ones
		newVertices->push_back(vertex0); //newValues->push_back(vertex0.pos);
		newVertices->push_back(vertex01); //newValues->push_back(vertex01.pos);
		newVertices->push_back(vertex02); //newValues->push_back(vertex02.pos);

		newVertices->push_back(vertex01); //newValues->push_back(vertex01.pos);
		newVertices->push_back(vertex1); //newValues->push_back(vertex1.pos);
		newVertices->push_back(vertex12); //newValues->push_back(vertex12.pos);

		newVertices->push_back(vertex02); //newValues->push_back(vertex02.pos);
		newVertices->push_back(vertex12); //newValues->push_back(vertex12.pos);
		newVertices->push_back(vertex2); //newValues->push_back(vertex2.pos);

		newVertices->push_back(vertex01); //newValues->push_back(vertex01.pos);
		newVertices->push_back(vertex12); //newValues->push_back(vertex12.pos);
		newVertices->push_back(vertex02); //newValues->push_back(vertex02.pos);

	}
	(*vertices)->clear();
	*vertices = newVertices;
	//m_values = newValues;
	

}

void Color::addTesselatedTriangle(int tesselationLevel, Vertex<float> vertex0, Vertex<float> vertex1, Vertex<float> vertex2){

	//New vertices
	Vertex<float> vertex01 = Vertex<float>((vertex0.pos.x + vertex1.pos.x)/2.0, (vertex0.pos.y + vertex1.pos.y)/2.0, (vertex0.pos.z + vertex1.pos.z)/2.0);
	Vertex<float> vertex02 = Vertex<float>((vertex0.pos.x + vertex2.pos.x)/2.0, (vertex0.pos.y + vertex2.pos.y)/2.0, (vertex0.pos.z + vertex2.pos.z)/2.0);
	Vertex<float> vertex12 = Vertex<float>((vertex1.pos.x + vertex2.pos.x)/2.0, (vertex1.pos.y + vertex2.pos.y)/2.0, (vertex1.pos.z + vertex2.pos.z)/2.0);

	if(tesselationLevel == 0){
		m_vertices->push_back(Vertex<float>(vertex0));
		m_vertices->push_back(Vertex<float>(vertex1));
		m_vertices->push_back(Vertex<float>(vertex2));
	}
	else if(tesselationLevel == 1){
		//add new ones
		m_vertices->push_back(Vertex<float>(vertex0));// m_values->push_back(vertex0.pos);
		m_vertices->push_back(Vertex<float>(vertex01));// m_values->push_back(vertex01.pos);
		m_vertices->push_back(Vertex<float>(vertex02));// m_values->push_back(vertex02.pos);

		m_vertices->push_back(Vertex<float>(vertex01));// m_values->push_back(vertex01.pos);
		m_vertices->push_back(Vertex<float>(vertex1));// m_values->push_back(vertex1.pos);
		m_vertices->push_back(Vertex<float>(vertex12));// m_values->push_back(vertex12.pos);

		m_vertices->push_back(Vertex<float>(vertex02));// m_values->push_back(vertex02.pos);
		m_vertices->push_back(Vertex<float>(vertex12));// m_values->push_back(vertex12.pos);
		m_vertices->push_back(Vertex<float>(vertex2));// m_values->push_back(vertex2.pos);

		m_vertices->push_back(Vertex<float>(vertex01));// m_values->push_back(vertex01.pos);
		m_vertices->push_back(Vertex<float>(vertex12));// m_values->push_back(vertex12.pos);
		m_vertices->push_back(Vertex<float>(vertex02));// m_values->push_back(vertex02.pos);
	}
	else{
		addTesselatedTriangle(tesselationLevel-1, vertex0, vertex01, vertex02);
		addTesselatedTriangle(tesselationLevel-1, vertex01, vertex1, vertex12);
		addTesselatedTriangle(tesselationLevel-1, vertex02, vertex12, vertex2);
		addTesselatedTriangle(tesselationLevel-1, vertex01, vertex12, vertex02);
	}
}

void Color::render(short currentColorSpace){
	
	if(!m_show) return;

	if(m_renderType == def_render_wire) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if(m_renderType == def_render_shade) glShadeModel(GL_SMOOTH);
	else glShadeModel(GL_FLAT);


	int size, vboIdVertices, vboIdColor;
	if(currentColorSpace == def_CIE_XYZ){
		size = m_verticesXYZColorSpace->size();
		vboIdColor = m_vboIdColorXYZ;
		if(!m_normalized) vboIdVertices = m_vboIdVerticesXYZ;
		else vboIdVertices = m_vboIdVerticesNormalizedXYZ;
	}
	else if(currentColorSpace == def_CIE_Lab){
		size = m_verticesLabColorSpace->size();
		vboIdColor = m_vboIdColorLab;
		if(!m_normalized) vboIdVertices = m_vboIdVerticesLab;
		else vboIdVertices = m_vboIdVerticesNormalizedLab;
	}
	else{
		size = m_verticessRGBColorSpace->size();
		vboIdColor = m_vboIdColorsRGB;
		if(!m_normalized) vboIdVertices = m_vboIdVerticessRGB;
		else vboIdVertices = m_vboIdVerticesNormalizedsRGB;
	}

	
	glEnableClientState(GL_VERTEX_ARRAY);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, vboIdVertices);
	glVertexPointer( 3, GL_FLOAT, 0, 0);
	
	glEnableClientState(GL_COLOR_ARRAY);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, vboIdColor);
	glColorPointer(4, GL_FLOAT, 0, 0);

	if(m_renderType == def_render_points) glDrawArrays(GL_POINTS, 0, size);
	else glDrawArrays(GL_TRIANGLES, 0, size);

	glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
	glDisableClientState(GL_VERTEX_ARRAY);
	
	
	/*
	std::vector<Vertex<float>*>* verticesToRender;
	if(currentColorSpace == def_CIE_XYZ){
		verticesToRender = m_verticesXYZColorSpace;
	}
	else if(currentColorSpace == def_CIE_Lab){
		verticesToRender = m_verticesLabColorSpace;
	}
	else{
		verticesToRender = m_verticessRGBColorSpace;
	}

	if(m_renderType == def_render_flat || m_renderType == def_render_wire){

		glBegin(GL_TRIANGLES);
		for(int i=0; i<verticesToRender->size(); i++){

			float sum = 1.0;
			if(m_normalized) sum = verticesToRender->at(i).pos.x + verticesToRender->at(i).pos.y + verticesToRender->at(i).pos.z;

			glColor4f(verticesToRender->at(i)->color.x, verticesToRender->at(i)->color.y, verticesToRender->at(i)->color.z, m_alpha);
			glVertex3f(verticesToRender->at(i).pos.x/sum, verticesToRender->at(i).pos.y/sum, verticesToRender->at(i).pos.z/sum);
			//glTranslated(verticesToRender->at(i).pos.x, verticesToRender->at(i).pos.y, verticesToRender->at(i).pos.z);
			//glutSolidCube(0.03);
			//glTranslated(-verticesToRender->at(i).pos.x, -verticesToRender->at(i).pos.y, -verticesToRender->at(i).pos.z);
		}
		glEnd();
	}
	else if(m_renderType == def_render_points){
		//glBegin(GL_POINTS);
		for(int i=0; i<verticesToRender->size(); i++){
			
			//float sum = 1.0;
			//if(m_normalized) sum = verticesToRender->at(i).pos.x + verticesToRender->at(i).pos.y + verticesToRender->at(i).pos.z;

			glColor4f(verticesToRender->at(i)->color.x, verticesToRender->at(i)->color.y, verticesToRender->at(i)->color.z, m_alpha);
			//glVertex3f(verticesToRender->at(i).pos.x/sum, verticesToRender->at(i).pos.y/sum, verticesToRender->at(i).pos.z/sum);
			glTranslated(verticesToRender->at(i).pos.x, verticesToRender->at(i).pos.y, verticesToRender->at(i).pos.z);
			//glScalef(1, 1, 1);
			glutSolidCube(0.03);
			glTranslated(-verticesToRender->at(i).pos.x, -verticesToRender->at(i).pos.y, -verticesToRender->at(i).pos.z);
		}
		//glEnd();
		
	}
	*/
	

}

Vec3<float> Color::XYZtosRGB(Vec3<float> valueXYZ){


	Vec3<float> clamped = Vec3<float>(valueXYZ.x, valueXYZ.y, valueXYZ.z);
	clamped.x = clamped.x / array_referenceWhiteD65[0];
	clamped.y = clamped.y / array_referenceWhiteD65[1];
	clamped.z = clamped.z / array_referenceWhiteD65[2];

	/*
	if(valueXYZ.x > 1.0) clamped.x = 1.0;
	else if(valueXYZ.x < 0) clamped.x = 0;
	if(valueXYZ.y > 1.0) clamped.y = 1.0;
	else if(valueXYZ.y < 0) clamped.y = 0;
	if(valueXYZ.z > 1.0) clamped.z = 1.0;
	else if(valueXYZ.z < 0) clamped.z = 0;
	*/
	/*
	float sum = clamped.x + clamped.y + clamped.z;
	clamped.x = clamped.x / sum;
	clamped.y = clamped.y / sum;
	clamped.z = clamped.z / sum;
	*/

	float r, g, b;
	r = (matrix_XYZtosRGB[0] * clamped.x + matrix_XYZtosRGB[1] * clamped.y + matrix_XYZtosRGB[2] * clamped.z);
	g = (matrix_XYZtosRGB[3] * clamped.x + matrix_XYZtosRGB[4] * clamped.y + matrix_XYZtosRGB[5] * clamped.z);
	b = (matrix_XYZtosRGB[6] * clamped.x + matrix_XYZtosRGB[7] * clamped.y + matrix_XYZtosRGB[8] * clamped.z);
	

	return Vec3<float>(rgbToRGB(r), rgbToRGB(g), rgbToRGB(b));

}

float Color::rgbToRGB(float value){

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

float Color::RGBtorgb(float value){

	if(value <= 0.04045)
		return value / 12.92;
	else
		return pow(((value + 0.055)/1.055), 2.4);

}

Vec3<float> Color::sRGBtoXYZ(Vec3<float> valueRGB){

	float r, g, b;
	r = RGBtorgb(valueRGB.x);
	g = RGBtorgb(valueRGB.y);
	b = RGBtorgb(valueRGB.z);

	
	Vec3<float> XYZ = Vec3<float>();
	XYZ.x = (matrix_sRGBtoXYZ[0] * r + matrix_sRGBtoXYZ[1] * g + matrix_sRGBtoXYZ[2] * b);
	XYZ.y = (matrix_sRGBtoXYZ[3] * r + matrix_sRGBtoXYZ[4] * g + matrix_sRGBtoXYZ[5] * b);
	XYZ.z = (matrix_sRGBtoXYZ[6] * r + matrix_sRGBtoXYZ[7] * g + matrix_sRGBtoXYZ[8] * b);

	//if(XYZ.x > 1.0) XYZ.x = 1.0;
	//if(XYZ.y > 1.0) XYZ.y = 1.0;
	//if(XYZ.z > 1.0) XYZ.z = 1.0;
	
	

	return XYZ;

}

Vec3<float> Color::LabtoXYZ(Vec3<float> valueLab){

	float e=216.0/24389;
	float k=24389.0/27;

	float fy = (valueLab.x + 16.0)/116.0;
	float fx = (valueLab.y/500.0) + fy;
	float fz = fy - (valueLab.z/200.0);

	float fx3 = fx*fx*fx;
	float fy3 = fy*fy*fy;
	float fz3 = fz*fz*fz;

	float xr, yr, zr;

	if(fx3 > e)
		xr = fx3;
	else
		xr = (116.0 * fx - 16.0)/k;
	
	if(valueLab.x > k * e)
		yr = pow((valueLab.x + 16.0)/116.0, 3);
	else
		yr = valueLab.x / k;

	if(fz3 > e)
		zr = fz3;
	else
		zr = (116.0 * fz - 16.0)/k;

	Vec3<float> XYZ = Vec3<float>();
	XYZ.x = Color::array_referenceWhiteD65[0] * fx;
	XYZ.y = Color::array_referenceWhiteD65[1] * fy;
	XYZ.z = Color::array_referenceWhiteD65[2] * fz;

	/*
	float sum = XYZ.x + XYZ.y + XYZ.z;
	XYZ.x = XYZ.x / sum;
	XYZ.y = XYZ.y / sum;
	XYZ.z = XYZ.z / sum;
	*/

	return XYZ;

}

Vec3<float> Color::xyYtoXYZ(Vec3<float> valuexyY){

	if(valuexyY.y == 0)
		return Vec3<float>(0, 0, 0);
	else
		return Vec3<float>((valuexyY.x * valuexyY.z)/valuexyY.y, valuexyY.z, ((1 - valuexyY.x - valuexyY.y)*valuexyY.z)/valuexyY.y);

}

Vec3<float> Color::XYZtoLab(Vec3<float> valueXYZ){

	float k = 24389.0/27.0;
	float e = 0.008856;

	float var_X = valueXYZ.x/array_referenceWhiteD65[0];
	float var_Y = valueXYZ.y/array_referenceWhiteD65[1];
	float var_Z = valueXYZ.z/array_referenceWhiteD65[2];

	if ( var_X > e ) var_X = pow(var_X,( 1.0f/3.0f ));
	else             var_X = ( k * var_X + 16.0)/116.0;
	if ( var_Y > e ) var_Y = pow(var_Y,( 1.0f/3.0f ));
	else             var_Y = ( k * var_Y + 16.0)/116.0;
	if ( var_Z > e ) var_Z = pow(var_Z,( 1.0f/3.0f ));
	else             var_Z = ( k * var_Z + 16.0)/116.0;

	Vec3<float> Lab = Vec3<float>();
	Lab.x = ( 116.0 * var_Y ) - 16.0;
	Lab.y = 500.0 * ( var_X - var_Y );
	Lab.z = 200.0 * ( var_Y - var_Z );


	return Lab;

}

void Color::setColorArrayLabtosRGB(std::vector<Vertex<float> >* verticesArray){
	
	for(int i=0; i<verticesArray->size(); i++){
		Vec3<float> color = XYZtosRGB(LabtoXYZ(verticesArray->at(i).pos));
		verticesArray->at(i).setColor(color.x, color.y, color.z);
	}
}

void Color::setColorArrayXYZtosRGB(std::vector<Vertex<float> >* verticesArray){
	
	for(int i=0; i<verticesArray->size(); i++){
		Vec3<float> color = XYZtosRGB(verticesArray->at(i).pos);
		verticesArray->at(i).setColor(color.x, color.y, color.z);
	}
}

void Color::setColorArraysRGB(std::vector<Vertex<float> >* verticesArray){
	
	for(int i=0; i<verticesArray->size(); i++){
		Vec3<float> color = (verticesArray->at(i).pos);
		verticesArray->at(i).setColor(color.x, color.y, color.z);
	}
}


void Color::createVBOs(float displacement){
	createVBO(displacement, m_verticesXYZColorSpace, &m_vboIdVerticesXYZ, &m_vboIdVerticesNormalizedXYZ, &m_vboIdColorXYZ);
	createVBO(displacement, m_verticessRGBColorSpace, &m_vboIdVerticessRGB, &m_vboIdVerticesNormalizedsRGB, &m_vboIdColorsRGB);
	createVBO(displacement, m_verticesLabColorSpace, &m_vboIdVerticesLab, &m_vboIdVerticesNormalizedLab, &m_vboIdColorLab);	
}

void Color::createVBO(float displacement, std::vector<Vertex<float> >* vertices, GLuint* vboIdVertices, GLuint* vboIdVerticesNormalized, GLuint* vboIdColor){


	float* vboVerticesArray = new float[m_verticesXYZColorSpace->size() * 3];
	float* vboVerticesNormalizedArray = new float[m_verticesXYZColorSpace->size() * 3];
	float* vboColorArray = new float[m_verticesXYZColorSpace->size() * 4];
	int cont = 0;
	int cont_color = 0;
	float sum = 0;
	for(int i=0; i<vertices->size(); i++){
		sum = vertices->at(i).pos.x + vertices->at(i).pos.y + vertices->at(i).pos.z;
		vboVerticesArray[cont] = vertices->at(i).pos.x;
		vboVerticesArray[cont+1] = vertices->at(i).pos.y;
		vboVerticesArray[cont+2] = vertices->at(i).pos.z;

		vboVerticesNormalizedArray[cont] = (vertices->at(i).pos.x / sum) + displacement;
		vboVerticesNormalizedArray[cont+1] = (vertices->at(i).pos.y / sum) + displacement;
		vboVerticesNormalizedArray[cont+2] = (vertices->at(i).pos.z / sum) + displacement;

		vboColorArray[cont_color] = vertices->at(i).color.x;
		vboColorArray[cont_color+1] = vertices->at(i).color.y;
		vboColorArray[cont_color+2] = vertices->at(i).color.z;
		vboColorArray[cont_color+3] = 1.0;
		cont+=3;
		cont_color+=4;
	}
	*vboIdVertices = 0;
	glGenBuffersARB( 1, vboIdVertices );
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, *vboIdVertices );
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, vertices->size() * 3*sizeof(float), vboVerticesArray, GL_STATIC_DRAW_ARB);

	*vboIdColor = 0;
	glGenBuffersARB( 1, vboIdColor );
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, *vboIdColor );
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, vertices->size() * 4*sizeof(float), vboColorArray, GL_STATIC_DRAW_ARB);

	*vboIdVerticesNormalized = 0;
	glGenBuffersARB( 1, vboIdVerticesNormalized );
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, *vboIdVerticesNormalized );
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, vertices->size() * 3*sizeof(float), vboVerticesNormalizedArray, GL_STATIC_DRAW_ARB);

	delete [] vboVerticesArray;
	delete [] vboColorArray;
	delete [] vboVerticesNormalizedArray;


}

void Color::changeAlpha(short currentColorSpace){

	std::vector<Vertex<float> >* vertices;
	GLuint* vboIdColor;
	if(currentColorSpace == def_CIE_XYZ){
		vertices = m_verticesXYZColorSpace;
		vboIdColor = &m_vboIdColorXYZ;
	}
	else if(currentColorSpace == def_CIE_Lab){
		vertices = m_verticesLabColorSpace;
		vboIdColor = &m_vboIdColorLab;
	}
	else{
		vertices = m_verticessRGBColorSpace;
		vboIdColor = &m_vboIdColorsRGB;
	}

	
	float* vboColorArray = new float[vertices->size() * 4];
	int cont_color = 0;
	for(int i=0; i<vertices->size(); i++){
		vboColorArray[cont_color] = vertices->at(i).color.x;
		vboColorArray[cont_color+1] = vertices->at(i).color.y;
		vboColorArray[cont_color+2] = vertices->at(i).color.z;
		vboColorArray[cont_color+3] = m_alpha;
		cont_color+=4;
	}


	*vboIdColor = 0;
	glGenBuffersARB( 1, vboIdColor );
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, *vboIdColor );
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, vertices->size() * 4*sizeof(float), vboColorArray, GL_STATIC_DRAW_ARB);


	delete [] vboColorArray;

}

void Color::clear(){

	if(m_vertices != 0) m_vertices->clear();
	m_verticesXYZColorSpace->clear();
	m_verticessRGBColorSpace->clear();
	m_verticesLabColorSpace->clear();

}

