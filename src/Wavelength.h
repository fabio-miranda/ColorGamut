#ifndef Wavelength_H
#define Wavelength_H

class Wavelength{

public:
	Wavelength();
	Wavelength(int nm, float p_CIE_A, float p_CIE_D65, float p_Vm, float p_Vlinha, float p_CIE2_x_bar, float p_CIE2_y_bar, 
				float p_CIE2_z_bar, float p_CIE10_x_bar, float p_CIE10_y_bar, float p_CIE10_z_bar);

	int nm;
	float CIE_A;
	float CIE_D65;
	float Vm;
	float Vlinha;
	float CIE2_x_bar;
	float CIE2_y_bar;
	float CIE2_z_bar;
	float CIE10_x_bar;
	float CIE10_y_bar;
	float CIE10_z_bar;



};

#endif