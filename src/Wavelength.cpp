#include "Wavelength.h"

Wavelength::Wavelength(){

}

Wavelength::Wavelength(int p_nm, float p_CIE_A, float p_CIE_D65, float p_Vm, float p_Vlinha, float p_CIE2_x_bar, float p_CIE2_y_bar, 
		   float p_CIE2_z_bar, float p_CIE10_x_bar, float p_CIE10_y_bar, float p_CIE10_z_bar){

	
	nm = p_nm;
	CIE_A = p_CIE_A;
	CIE_D65 = p_CIE_D65;
	Vm = p_Vm;
	Vlinha = p_Vlinha;
	CIE2_x_bar = p_CIE2_x_bar;
	CIE2_y_bar = p_CIE2_y_bar;
	CIE2_z_bar = p_CIE2_z_bar;
	CIE10_x_bar = p_CIE10_x_bar;
	CIE10_y_bar = p_CIE10_y_bar;
	CIE10_z_bar = p_CIE10_z_bar;


}