#ifndef Vec_H
#define Vec_H


template <class T>
class Vec3{
public:
	T x; T y; T z;
	Vec3() : x(0), y(0), z(0){};
	Vec3(T px, T py, T pz): x(px), y(py), z(pz){};
	//Vec3(Vec3<T>* vec) : x(vec.x), y(vec.y), z(vec.z){};
	
	~Vec3(){
		//delete &x;
		//delete &y;
		//delete &z;
	}
	
};

template <class T>
class SpherCoord{
public:
	T r; T a; T t;
	SpherCoord() : r(0), a(0), t(0){};
	SpherCoord(T px, T py, T pz): r(px), a(py), t(pz){};
	// SpherCoord(Vec3<T>* vec) : r(vec.x), a(vec.y), t(vec.z){};
};

template <class T>
class Vertex{
public:
	Vertex(T px, T py, T pz){
		pos = Vec3<T>();
		pos.x = px;
		pos.y = py;
		pos.z = pz;
		//color = 0;
	}
	
	~Vertex(){
		//delete pos;
		//delete color;
	}

	void setColor(T r, T g, T b){
		color.x = r;
		color.y = g;
		color.z = b;
	}
	

	Vec3<T> pos;
	Vec3<T> color;
};


template <class T>
class Vec4{
public:
	T x; T y; T z; T w;
	Vec4() : x(0), y(0), z(0), w(0){};
	Vec4(T px, T py, T pz, T pw): x(px), y(py), z(pz), w(pw){};
};


#endif