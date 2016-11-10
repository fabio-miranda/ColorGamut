#include "NormalizedXYZ.h"

NormalizedXYZ::NormalizedXYZ(){

}

NormalizedXYZ::NormalizedXYZ(int tesselationLvl, std::vector<Vec3<float> >* valuesXYZ){
	Color::init(tesselationLvl);

	normalizeXYZ(valuesXYZ);
	createGeometries();

}



void NormalizedXYZ::normalizeXYZ(std::vector<Vec3<float> >* valuesXYZ){

	m_values = new std::vector<Vec3<float> >();



	for(int i=0; i< valuesXYZ->size(); i++){

		float sum = valuesXYZ->at(i).x + valuesXYZ->at(i).y + valuesXYZ->at(i).z;
		m_values->push_back(Vec3<float>(0,0,0));

		//TODO: Check this multiplication by 3.0

		m_values->at(i).x = 3.0 * valuesXYZ->at(i).x / sum;
		m_values->at(i).y = 3.0 * valuesXYZ->at(i).y / sum;
		m_values->at(i).z = 3.0 * valuesXYZ->at(i).z / sum;
		
	}

}


void NormalizedXYZ::createGeometries(){
	
	createTriangles();
	
	for(int i=0; i<m_tesselationLvl; i++){
		tesselate(&m_vertices);
	}
	
	toXYZColorSpace();
	toLabColorSpace();
	tosRGBColorSpace();


	createVBOs(0.0);
	
	
}

void NormalizedXYZ::createTriangles(){
	
	float u[64*3*3]= {  1.000000, 0.000000, 0.000000,    0.875000, 0.125000, 0.000000,   0.875000, 0.000000, 0.125000, 
                    0.875000, 0.125000, 0.000000,    0.750000, 0.125000, 0.125000,   0.875000, 0.000000, 0.125000, 
                    0.875000, 0.125000, 0.000000,    0.750000, 0.250000, 0.000000,   0.750000, 0.125000, 0.125000, 
                    0.875000, 0.000000, 0.125000,    0.750000, 0.125000, 0.125000,   0.750000, 0.000000, 0.250000, 
                    0.750000, 0.250000, 0.000000,    0.625000, 0.250000, 0.125000,   0.750000, 0.125000, 0.125000, 
                    0.625000, 0.250000, 0.125000,    0.625000, 0.125000, 0.250000,   0.750000, 0.125000, 0.125000, 
                    0.625000, 0.250000, 0.125000,    0.500000, 0.250000, 0.250000,   0.625000, 0.125000, 0.250000, 
                    0.750000, 0.125000, 0.125000,    0.625000, 0.125000, 0.250000,   0.750000, 0.000000, 0.250000, 
                    0.750000, 0.250000, 0.000000,    0.625000, 0.375000, 0.000000,   0.625000, 0.250000, 0.125000, 
                    0.625000, 0.375000, 0.000000,    0.500000, 0.375000, 0.125000,   0.625000, 0.250000, 0.125000, 
                    0.625000, 0.375000, 0.000000,    0.500000, 0.500000, 0.000000,   0.500000, 0.375000, 0.125000, 
                    0.625000, 0.250000, 0.125000,    0.500000, 0.375000, 0.125000,   0.500000, 0.250000, 0.250000, 
                    0.750000, 0.000000, 0.250000,    0.625000, 0.125000, 0.250000,   0.625000, 0.000000, 0.375000, 
                    0.625000, 0.125000, 0.250000,    0.500000, 0.125000, 0.375000,   0.625000, 0.000000, 0.375000, 
                    0.625000, 0.125000, 0.250000,    0.500000, 0.250000, 0.250000,   0.500000, 0.125000, 0.375000, 
                    0.625000, 0.000000, 0.375000,    0.500000, 0.125000, 0.375000,   0.500000, 0.000000, 0.500000, 
                    0.500000, 0.500000, 0.000000,    0.375000, 0.500000, 0.125000,   0.500000, 0.375000, 0.125000, 
                    0.375000, 0.500000, 0.125000,    0.375000, 0.375000, 0.250000,   0.500000, 0.375000, 0.125000, 
                    0.375000, 0.500000, 0.125000,    0.250000, 0.500000, 0.250000,   0.375000, 0.375000, 0.250000, 
                    0.500000, 0.375000, 0.125000,    0.375000, 0.375000, 0.250000,   0.500000, 0.250000, 0.250000, 
                    0.250000, 0.500000, 0.250000,    0.250000, 0.375000, 0.375000,   0.375000, 0.375000, 0.250000, 
                    0.250000, 0.375000, 0.375000,    0.375000, 0.250000, 0.375000,   0.375000, 0.375000, 0.250000, 
                    0.250000, 0.375000, 0.375000,    0.250000, 0.250000, 0.500000,   0.375000, 0.250000, 0.375000, 
                    0.375000, 0.375000, 0.250000,    0.375000, 0.250000, 0.375000,   0.500000, 0.250000, 0.250000, 
                    0.250000, 0.500000, 0.250000,    0.125000, 0.500000, 0.375000,   0.250000, 0.375000, 0.375000, 
                    0.125000, 0.500000, 0.375000,    0.125000, 0.375000, 0.500000,   0.250000, 0.375000, 0.375000, 
                    0.125000, 0.500000, 0.375000,    0.000000, 0.500000, 0.500000,   0.125000, 0.375000, 0.500000, 
                    0.250000, 0.375000, 0.375000,    0.125000, 0.375000, 0.500000,   0.250000, 0.250000, 0.500000, 
                    0.500000, 0.250000, 0.250000,    0.375000, 0.250000, 0.375000,   0.500000, 0.125000, 0.375000, 
                    0.375000, 0.250000, 0.375000,    0.375000, 0.125000, 0.500000,   0.500000, 0.125000, 0.375000, 
                    0.375000, 0.250000, 0.375000,    0.250000, 0.250000, 0.500000,   0.375000, 0.125000, 0.500000, 
                    0.500000, 0.125000, 0.375000,    0.375000, 0.125000, 0.500000,   0.500000, 0.000000, 0.500000, 
                    0.500000, 0.500000, 0.000000,    0.375000, 0.625000, 0.000000,   0.375000, 0.500000, 0.125000, 
                    0.375000, 0.625000, 0.000000,    0.250000, 0.625000, 0.125000,   0.375000, 0.500000, 0.125000, 
                    0.375000, 0.625000, 0.000000,    0.250000, 0.750000, 0.000000,   0.250000, 0.625000, 0.125000, 
                    0.375000, 0.500000, 0.125000,    0.250000, 0.625000, 0.125000,   0.250000, 0.500000, 0.250000, 
                    0.250000, 0.750000, 0.000000,    0.125000, 0.750000, 0.125000,   0.250000, 0.625000, 0.125000, 
                    0.125000, 0.750000, 0.125000,    0.125000, 0.625000, 0.250000,   0.250000, 0.625000, 0.125000, 
                    0.125000, 0.750000, 0.125000,    0.000000, 0.750000, 0.250000,   0.125000, 0.625000, 0.250000, 
                    0.250000, 0.625000, 0.125000,    0.125000, 0.625000, 0.250000,   0.250000, 0.500000, 0.250000, 
                    0.250000, 0.750000, 0.000000,    0.125000, 0.875000, 0.000000,   0.125000, 0.750000, 0.125000, 
                    0.125000, 0.875000, 0.000000,    0.000000, 0.875000, 0.125000,   0.125000, 0.750000, 0.125000, 
                    0.125000, 0.875000, 0.000000,    0.000000, 1.000000, 0.000000,   0.000000, 0.875000, 0.125000, 
                    0.125000, 0.750000, 0.125000,    0.000000, 0.875000, 0.125000,   0.000000, 0.750000, 0.250000, 
                    0.250000, 0.500000, 0.250000,    0.125000, 0.625000, 0.250000,   0.125000, 0.500000, 0.375000, 
                    0.125000, 0.625000, 0.250000,    0.000000, 0.625000, 0.375000,   0.125000, 0.500000, 0.375000, 
                    0.125000, 0.625000, 0.250000,    0.000000, 0.750000, 0.250000,   0.000000, 0.625000, 0.375000, 
                    0.125000, 0.500000, 0.375000,    0.000000, 0.625000, 0.375000,   0.000000, 0.500000, 0.500000, 
                    0.500000, 0.000000, 0.500000,    0.375000, 0.125000, 0.500000,   0.375000, 0.000000, 0.625000, 
                    0.375000, 0.125000, 0.500000,    0.250000, 0.125000, 0.625000,   0.375000, 0.000000, 0.625000, 
                    0.375000, 0.125000, 0.500000,    0.250000, 0.250000, 0.500000,   0.250000, 0.125000, 0.625000, 
                    0.375000, 0.000000, 0.625000,    0.250000, 0.125000, 0.625000,   0.250000, 0.000000, 0.750000, 
                    0.250000, 0.250000, 0.500000,    0.125000, 0.250000, 0.625000,   0.250000, 0.125000, 0.625000, 
                    0.125000, 0.250000, 0.625000,    0.125000, 0.125000, 0.750000,   0.250000, 0.125000, 0.625000, 
                    0.125000, 0.250000, 0.625000,    0.000000, 0.250000, 0.750000,   0.125000, 0.125000, 0.750000, 
                    0.250000, 0.125000, 0.625000,    0.125000, 0.125000, 0.750000,   0.250000, 0.000000, 0.750000, 
                    0.250000, 0.250000, 0.500000,    0.125000, 0.375000, 0.500000,   0.125000, 0.250000, 0.625000, 
                    0.125000, 0.375000, 0.500000,    0.000000, 0.375000, 0.625000,   0.125000, 0.250000, 0.625000, 
                    0.125000, 0.375000, 0.500000,    0.000000, 0.500000, 0.500000,   0.000000, 0.375000, 0.625000, 
                    0.125000, 0.250000, 0.625000,    0.000000, 0.375000, 0.625000,   0.000000, 0.250000, 0.750000, 
                    0.250000, 0.000000, 0.750000,    0.125000, 0.125000, 0.750000,   0.125000, 0.000000, 0.875000, 
                    0.125000, 0.125000, 0.750000,    0.000000, 0.125000, 0.875000,   0.125000, 0.000000, 0.875000, 
                    0.125000, 0.125000, 0.750000,    0.000000, 0.250000, 0.750000,   0.000000, 0.125000, 0.875000, 
                    0.125000, 0.000000, 0.875000,    0.000000, 0.125000, 0.875000,   0.000000, 0.000000, 1.000000 };


	int half = 100;
	float* fv = new float[half * 3];
	float* gv = new float[(m_values->size() - half) * 3];

	int cont = 0;
	for(int i=0; i<half; i++){
		fv[cont] = m_values->at(i).x;
		fv[cont+1] = m_values->at(i).y;
		fv[cont+2] = m_values->at(i).z;
		cont+=3;
	}
	
	cont = 0;
	for(int i=half; i<m_values->size(); i++){
		gv[cont] = m_values->at(i).x;
		gv[cont+1] = m_values->at(i).y;
		gv[cont+2] = m_values->at(i).z;
		cont+=3;
	}
	
	/*
	float fv[2*3]={m_values->at(0).x,m_values->at(0).y,m_values->at(0).z, 0.5000f,0.8660f,0.0000f};
	float gv[2*3]={0.5000f,0.8660f,0.0000f, m_values->at(m_values->size()-1).x,m_values->at(m_values->size()-1).y,m_values->at(m_values->size()-1).z};
	*/
	float hv[2*3]={m_values->at(m_values->size()-1).x,m_values->at(m_values->size()-1).y,m_values->at(m_values->size()-1).z, m_values->at(0).x,m_values->at(0).y,m_values->at(0).z};

	Poly* f=create_poly_line(half ,fv); /* curvas de borda */
	Poly* g=create_poly_line((m_values->size() - half) ,gv);  
	Poly* h=create_poly_line(2,hv);
   int i;
   
   //FILE* fp=fopen("curved.txt","wt");

   m_vertices = new std::vector<Vertex<float> >();
   for (i=0;i<64;i++){
		float tri[9];  /* as nove coordenadas dos tres vertices do triangulo */
		tri_mesh_point(u[9*i+0],u[9*i+1],u[9*i+2],f,g,h,&tri[0]);
		tri_mesh_point(u[9*i+3],u[9*i+4],u[9*i+5],f,g,h,&tri[3]);
		tri_mesh_point(u[9*i+6],u[9*i+7],u[9*i+8],f,g,h,&tri[6]);
		m_vertices->push_back(Vertex<float>(tri[0], tri[1], tri[2]));
		m_vertices->push_back(Vertex<float>(tri[3], tri[4], tri[5]));
		m_vertices->push_back(Vertex<float>(tri[6], tri[7], tri[8]));
    }

   //delete [] f;
   //delete [] g;
   //delete [] h;

   //Bottom	
	addTesselatedTriangle(5, Vertex<float>(0,0,0),
							  Vertex<float>(m_values->at(0).x, m_values->at(0).y, m_values->at(0).z),
							  Vertex<float>(m_values->at(m_values->size()-1).x, m_values->at(m_values->size()-1).y, m_values->at(m_values->size()-1).z));
	//Surface
	for(int i=0; i<m_values->size()-1; i++){
		
		m_vertices->push_back(Vertex<float>(0,0,0));
		m_vertices->push_back(Vertex<float>(m_values->at(i).x, m_values->at(i).y, m_values->at(i).z));
		m_vertices->push_back(Vertex<float>(m_values->at(i+1).x, m_values->at(i+1).y, m_values->at(i+1).z));

	}

}

/*
void NormalizedXYZ::createTriangles(){

	
	m_vertices = new std::vector<Vertex<float>*>();

	//Bottom	
	addTesselatedTriangle(0, new Vertex<float>(new Vec3<float>(0,0,0)),
							  new Vertex<float>(new Vec3<float>(m_values->at(0))),
							  new Vertex<float>(new Vec3<float>(m_values->at(m_values->size()-1))));
	
	//Line of purple	
	addTesselatedTriangle(0, new Vertex<float>(new Vec3<float>(m_values->at(0))), 
							  new Vertex<float>(new Vec3<float>(0.950471, 0.999999, 1.088830)),
							  new Vertex<float>(new Vec3<float>(m_values->at(m_values->size()-1))));
	
	
	//Surface
	for(int i=0; i<m_values->size()-1; i++){
		
		m_vertices->push_back(new Vertex<float>(new Vec3<float>(0,0,0)));
		m_vertices->push_back(new Vertex<float>(new Vec3<float>(m_values->at(i))));
		m_vertices->push_back(new Vertex<float>(new Vec3<float>(m_values->at(i+1))));

	}

	//Horseshoe
	for(int i=0; i<m_values->size()-1; i++){
		
		m_vertices->push_back(new Vertex<float>(new Vec3<float>(0.950471, 0.999999, 1.088830)));
		m_vertices->push_back(new Vertex<float>(new Vec3<float>(m_values->at(i))));
		m_vertices->push_back(new Vertex<float>(new Vec3<float>(m_values->at(i+1))));

	}
	
	toRGB(m_vertices);

}
*/
/*
void NormalizedXYZ::toRGB(std::vector<Vertex<float> >* verticesArray){
	
	for(int i=0; i<verticesArray->size(); i++){
		Vec3<float> color = XYZtosRGB(verticesArray->at(i).pos);
		verticesArray->at(i).setColor(color.x, color.y, color.z);
	}

}
*/

void NormalizedXYZ::toXYZColorSpace(){

	m_verticesXYZColorSpace = new std::vector<Vertex<float> >();
	for(int i=0; i<m_vertices->size(); i++){
		
		m_verticesXYZColorSpace->push_back(Vertex<float>(m_vertices->at(i).pos.x, m_vertices->at(i).pos.y, m_vertices->at(i).pos.z));

		Vec3<float> color = XYZtosRGB(Vec3<float>(m_vertices->at(i).pos.x, m_vertices->at(i).pos.y, m_vertices->at(i).pos.z));
		m_verticesXYZColorSpace->at(m_verticesXYZColorSpace->size()-1).setColor(color.x, color.y, color.z);
	}

	//toRGB(m_verticesXYZColorSpace);

}

void NormalizedXYZ::toLabColorSpace(){
	
	m_verticesLabColorSpace = new std::vector<Vertex<float> >();
	for(int i=0; i<m_vertices->size(); i++){
		
		Vec3<float> Lab = XYZtoLab(m_vertices->at(i).pos);
		m_verticesLabColorSpace->push_back(Vertex<float>(Lab.x, Lab.y, Lab.z));

		Vec3<float> color = XYZtosRGB(LabtoXYZ(Lab));
		m_verticesLabColorSpace->at(m_verticesLabColorSpace->size()-1).setColor(color.x, color.y, color.z);
	}

	//toRGB(m_verticesLabColorSpace);
}

void NormalizedXYZ::tosRGBColorSpace(){
	
	m_verticessRGBColorSpace = new std::vector<Vertex<float> >();
	for(int i=0; i<m_vertices->size(); i++){
		
		Vec3<float> sRGB = XYZtosRGB(m_vertices->at(i).pos);
		m_verticessRGBColorSpace->push_back(Vertex<float>(sRGB.x, sRGB.y, sRGB.z));
		m_verticessRGBColorSpace->at(m_verticessRGBColorSpace->size()-1).setColor(sRGB.x, sRGB.y, sRGB.z);
	}

	//toRGB(m_verticessRGBColorSpace);
}