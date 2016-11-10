#include "SegmentMaximaColor.h"

SegmentMaximaColor::SegmentMaximaColor(){

}

SegmentMaximaColor::SegmentMaximaColor(int tesselationLvl, int n){
	init(tesselationLvl, n);	
	
}

void SegmentMaximaColor::init(int tesselationLvl, int n){
	
	Color::init(tesselationLvl);
	m_n = n;
	m_showAllPoints = false;

	
	changeGBDSize();

}

void SegmentMaximaColor::changeGBDSize(){
	
	m_gbdMatrixSize = m_n;

	createGeometries();
	
	

}

void SegmentMaximaColor::createGeometries(){
	calculateSphericalCoord(m_verticesLabColorSpace, m_gbdMatrixSize);

	createTriangles(&m_verticesLabColorSpace);
	createTriangles(&m_verticessRGBColorSpace);
	createTriangles(&m_verticesXYZColorSpace);
	
	for(int i=0; i<m_tesselationLvl; i++){
		tesselate(&m_verticesLabColorSpace);
		tesselate(&m_verticessRGBColorSpace);
		tesselate(&m_verticesXYZColorSpace);
	}
	
	
	setColorArrayLabtosRGB(m_verticesLabColorSpace);
	setColorArrayXYZtosRGB(m_verticesXYZColorSpace);
	setColorArraysRGB(m_verticessRGBColorSpace);
	
	createVBOs(0.05);
}

void SegmentMaximaColor::render(short currentColorSpace){
	
	if(!m_show) return;
	
	if(m_showAllPoints){	

		std::vector<Vec3<float> >* vertexToRender;
		if(currentColorSpace == def_CIE_Lab)
			vertexToRender = m_allPointsLabColorSpace;
		else if(currentColorSpace == def_CIE_XYZ)
			vertexToRender = m_allPointsXYZColorSpace;
		else
			vertexToRender = m_allPointssRGBColorSpace;

		glPointSize(5.0);
		glBegin(GL_POINTS);
		for(int i=0; i<vertexToRender->size(); i++){
			glColor3f(vertexToRender->at(i).x, vertexToRender->at(i).y, vertexToRender->at(i).z);
			glVertex3f(vertexToRender->at(i).x, vertexToRender->at(i).y, vertexToRender->at(i).z);
			//glTranslatef(vertexToRender->at(i).x, vertexToRender->at(i).y, vertexToRender->at(i).z);
			//glutSolidCube(0.02);
			//glTranslatef(-vertexToRender->at(i).x, -vertexToRender->at(i).y, -vertexToRender->at(i).z);
		}
		glEnd();
	}
	
	Color::render(currentColorSpace);

	
	
	
	
}


void SegmentMaximaColor::toXYZColorSpace(){

	m_verticesXYZColorSpace = new std::vector<Vertex<float> >();
	m_allPointsXYZColorSpace = new std::vector<Vec3<float> >();
	for(int i=0; i<m_values->size(); i++){
		
		Vec3<float> XYZ = xyYtoXYZ(m_values->at(i));
		float sum = XYZ.x + XYZ.y + XYZ.z;
		/*
		XYZ.x = XYZ.x / sum;
		XYZ.y = XYZ.y / sum;
		XYZ.z = XYZ.z / sum;
		*/
		m_verticesXYZColorSpace->push_back(Vertex<float>(XYZ.x, XYZ.y, XYZ.z));
		m_allPointsXYZColorSpace->push_back(XYZ);

	}
}

void SegmentMaximaColor::toLabColorSpace(){

	m_verticesLabColorSpace = new std::vector<Vertex<float> >();
	m_allPointsLabColorSpace = new std::vector<Vec3<float> >();
	for(int i=0; i<m_values->size(); i++){
		
		Vec3<float> Lab = XYZtoLab(xyYtoXYZ(m_values->at(i)));
		m_verticesLabColorSpace->push_back(Vertex<float>(Lab.x, Lab.y, Lab.z));
		m_allPointsLabColorSpace->push_back(Lab);

	}
}

void SegmentMaximaColor::tosRGBColorSpace(){
	
	m_verticessRGBColorSpace = new std::vector<Vertex<float> >();
	m_allPointssRGBColorSpace = new std::vector<Vec3<float> >();
	for(int i=0; i<m_values->size(); i++){
		
		Vec3<float> sRGB = XYZtosRGB(xyYtoXYZ(m_values->at(i)));
		m_verticessRGBColorSpace->push_back(Vertex<float>(sRGB.x, sRGB.y, sRGB.z));
		m_allPointssRGBColorSpace->push_back(sRGB);

	}

}

void SegmentMaximaColor::calculateSphericalCoord(std::vector<Vertex<float> >* p_vertices, int n){

	m_sphericalCoordLabColorSpace = new std::vector<SpherCoord<float> >();

	m_gbdMatrix = new int*[n];
	for(int i=0; i<n; i++){
		m_gbdMatrix[i] = new int[n];
		for(int j=0; j<n; j++)
			m_gbdMatrix[i][j] = -1;
	}

	//Calculate center
	Vec3<float> center = Vec3<float>(0, 50, 0);
	
	for(int i=0; i<p_vertices->size(); i++){
		center.x += p_vertices->at(i).pos.x;
		center.y += p_vertices->at(i).pos.y;
		center.z += p_vertices->at(i).pos.z;
	}
	center.x = center.x / p_vertices->size();
	center.y = center.y / p_vertices->size();
	center.z = center.z / p_vertices->size();
	

	//Calculate r, alpha, tetha
	for(int i=0; i<p_vertices->size(); i++){
		float L = p_vertices->at(i).pos.x;
		float a = p_vertices->at(i).pos.y;
		float b = p_vertices->at(i).pos.z;

		float r = pow((pow(L - center.x, 2.0f) + pow(a - center.y, 2.0f) + pow(b - center.z, 2.0f)), 1.0f/2.0f);
		float alpha = atan2f((b - center.z) , (a - center.y)) + PI;
		float tetha = atan2f((L - center.x) , pow((pow(a - center.y, 2.0f) + pow(b - center.z, 2.0f)), 1.0f/2.0f)) + PI;
		
		m_sphericalCoordLabColorSpace->push_back(SpherCoord<float>(r, alpha, tetha));

	}

	//Find the greatest r for each cell of the matrix
	float TwoPi = 2.0 * PI;
	for(int i=0; i<m_sphericalCoordLabColorSpace->size(); i++){
		float alpha = m_sphericalCoordLabColorSpace->at(i).a;
		float tetha = m_sphericalCoordLabColorSpace->at(i).t;

		int gbdMatrix_x = (int)(((alpha / TwoPi)) * (m_gbdMatrixSize));
		int gbdMatrix_y = (int)(((tetha / TwoPi)) * (m_gbdMatrixSize));
		int index = m_gbdMatrix[gbdMatrix_x][gbdMatrix_y];
		if(index == -1)
			m_gbdMatrix[gbdMatrix_x][gbdMatrix_y] = i;
		else if(m_sphericalCoordLabColorSpace->at(i).r >= m_sphericalCoordLabColorSpace->at(index).r)
			m_gbdMatrix[gbdMatrix_x][gbdMatrix_y] = i;

	}

	/*
	for(int i=0; i<m_gbdMatrixSize; i++){
		for(int j=0; j<m_gbdMatrixSize; j++){
			std::cout << m_gbdMatrix[i][j] << " ";
		}
		std::cout << "\n";
	}

	std::cout << "\n";
	std::cout << "\n";
	*/
	

}

void SegmentMaximaColor::createTriangles(std::vector<Vertex<float> >** verticesToRender){
	
	std::vector<Vertex<float> >* newVertices = new std::vector<Vertex<float> >();

	bool foundFirstPoint = false;
	for(int i=0; i<m_gbdMatrixSize; i++){
		for(int j=0; j<m_gbdMatrixSize-1; j++){
			//Mend the end with the begin
			int index1, index2, index3, index4;
			if(i == m_gbdMatrixSize-1){
				index1 = findClosestValue(0,j);
				index2 = findClosestValue(m_gbdMatrixSize-1,j);
				index3 = findClosestValue(0,j+1);
				index4 = findClosestValue(m_gbdMatrixSize-1,j+1);
			}
			else{
 				index1 = findClosestValue(i,j);
				index2 = findClosestValue(i+1,j);
				index3 = findClosestValue(i,j+1);
				index4 = findClosestValue(i+1,j+1);
			}
			

			
			//if(index1 == -1 && i < m_gbdMatrixSize) index1 = m_gbdMatrix[i+1][j];
			/*
			if(foundFirstPoint){
				if(index2 == -1 && index4 == -1 && index1 != -1 && index3 != -1){
					for(int k=0; k<m_gbdMatrixSize; k++) {
						if(m_gbdMatrix[k][j] != -1){
							index2 = m_gbdMatrix[k][j];
							break;
						}
					}
					for(int k=0; k<m_gbdMatrixSize; k++) {
						if(m_gbdMatrix[k][j+1] != -1){
							index4 = m_gbdMatrix[k][j+1];
							break;
						}
					}
				}
			}
			*/

			
			
					

			if(index1 >= 0 && index2 >= 0 && index3 >= 0 && index4 >= 0){
				foundFirstPoint = true;
				Vertex<float> vertex0 = Vertex<float>((*verticesToRender)->at(index1).pos.x, (*verticesToRender)->at(index1).pos.y, (*verticesToRender)->at(index1).pos.z);
				Vertex<float> vertex1 = Vertex<float>((*verticesToRender)->at(index2).pos.x, (*verticesToRender)->at(index2).pos.y, (*verticesToRender)->at(index2).pos.z);
				Vertex<float> vertex2 = Vertex<float>((*verticesToRender)->at(index3).pos.x, (*verticesToRender)->at(index3).pos.y, (*verticesToRender)->at(index3).pos.z);
				Vertex<float> vertex3 = Vertex<float>((*verticesToRender)->at(index4).pos.x, (*verticesToRender)->at(index4).pos.y, (*verticesToRender)->at(index4).pos.z);
				Vertex<float> vertex4 = Vertex<float>((*verticesToRender)->at(index2).pos.x, (*verticesToRender)->at(index2).pos.y, (*verticesToRender)->at(index2).pos.z);
				Vertex<float> vertex5 = Vertex<float>((*verticesToRender)->at(index3).pos.x, (*verticesToRender)->at(index3).pos.y, (*verticesToRender)->at(index3).pos.z);
				
				newVertices->push_back(vertex0);
				newVertices->push_back(vertex1);
				newVertices->push_back(vertex2);
				newVertices->push_back(vertex3);
				newVertices->push_back(vertex4);
				newVertices->push_back(vertex5);
				
			}
			
		}
	}

	//Top
	int column = -1;
	for(int i=0; i<m_gbdMatrixSize && column == -1; i++){
		for(int j=0; j<m_gbdMatrixSize; j++){
			if(m_gbdMatrix[i][j] != -1){
				column = j;
				break;
			}
		}
	}
	closeExtreme(verticesToRender, newVertices, column);
	


	//Bottom
	column = -1;
	for(int i=m_gbdMatrixSize-1; i>= 0 && column == -1; i--){
		for(int j=m_gbdMatrixSize-1; j>=0; j--){
			if(m_gbdMatrix[i][j] != -1){
				column = j;
				break;
			}
		}
	}
	closeExtreme(verticesToRender, newVertices, column);

	*verticesToRender = newVertices;
}

void SegmentMaximaColor::closeExtreme(std::vector<Vertex<float> >** verticesToRender, std::vector<Vertex<float> >* newVertices, int column){

	Vec3<float> avg = Vec3<float>(0,0,0);
	int cont = 0;
	for(int i=0; i<m_gbdMatrixSize; i++){
		if(m_gbdMatrix[i][column] != -1){
			int index = m_gbdMatrix[i][column];
			avg.x += (*verticesToRender)->at(index).pos.x;
			avg.y += (*verticesToRender)->at(index).pos.y;
			avg.z += (*verticesToRender)->at(index).pos.z;
			cont ++;
		}
	}
	avg.x = avg.x / cont; avg.y = avg.y / cont; avg.z = avg.z / cont;
	for(int i=0; i<m_gbdMatrixSize; i++){

		int index1, index2;

		if(i == m_gbdMatrixSize -1){
			index1 = findClosestValue(i, column);
			index2 = findClosestValue(0, column);
		}
		else{
			index1 = findClosestValue(i, column);
			index2 = findClosestValue(i+1, column);
		}


		Vertex<float> vertex0 = Vertex<float>(avg.x, avg.y, avg.z);
		Vertex<float> vertex1 = Vertex<float>((*verticesToRender)->at(index1).pos.x, (*verticesToRender)->at(index1).pos.y, (*verticesToRender)->at(index1).pos.z);
		Vertex<float> vertex2 = Vertex<float>((*verticesToRender)->at(index2).pos.x, (*verticesToRender)->at(index2).pos.y, (*verticesToRender)->at(index2).pos.z);

		newVertices->push_back(vertex0);
		newVertices->push_back(vertex1);
		newVertices->push_back(vertex2);
	}


}

int SegmentMaximaColor::findClosestValue(int i, int j){

	if(m_gbdMatrix[i][j] != -1)
		return m_gbdMatrix[i][j];
	else{
		if(i > 0)
			if(m_gbdMatrix[i-1][j] != -1) return m_gbdMatrix[i-1][j];
		else if(i < m_gbdMatrixSize-1)
			if(m_gbdMatrix[i+1][j] != -1) return m_gbdMatrix[i+1][j];
		else if(j > 0)
			if(m_gbdMatrix[i][j-1] != -1) return m_gbdMatrix[i][j-1];
		else if(j < m_gbdMatrixSize-1)
			if(m_gbdMatrix[i][j+1] != -1) return m_gbdMatrix[i][j+1];
		else if(i < m_gbdMatrixSize-1 && j < m_gbdMatrixSize-1)
			if(m_gbdMatrix[i+1][j+1] != -1) return m_gbdMatrix[i+1][j+1];
		else if(i < m_gbdMatrixSize-1 && j > 0)
			if(m_gbdMatrix[i+1][j-1] != -1) return m_gbdMatrix[i+1][j-1];
		else if(i > 0 && j < m_gbdMatrixSize-1)
			if(m_gbdMatrix[i-1][j+1] != -1) return m_gbdMatrix[i-1][j+1];
		else if(i > 0 && j > 0)
			if(m_gbdMatrix[i-1][j-1] != -1) return m_gbdMatrix[i-1][j-1];
		
	}
	return -1;
}

void SegmentMaximaColor::clear(){

	//Color::clear();
	
	m_sphericalCoordLabColorSpace->clear();
	//m_allPointsLabColorSpace->clear();
	//m_allPointsXYZColorSpace->clear();
	//m_allPointssRGBColorSpace->clear();

}