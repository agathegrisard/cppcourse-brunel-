#ifndef CONSTANT_H 
#define CONSTANT_H 

#include <cmath> 

namespace C { 
	
		
	const double tau = 20.0; 
	const double R = 20.0; 													/// résistance de la membrane
	const int C = 1; 														/// capacité d'un neurone 
	const double Vth = 20.0; 													/// valeur de treshold 
	const double Vreset = 10; 												/// valeur à laquelle il revient apès avoir spike
	const double h = 0.1;
	const double Tref = 2.0; 												/// temps pour revenir après avoir redescendu
	const int refract_time  = 20;											/// la valeur en step

	const double c1 = exp(-h/tau);
	const double c2 = R*(1.0-c1);

	const double step_value = 0.1; 	
	
	const int Ntot=12500; 
	const int Nexc=0.8*Ntot; 
	const int Ninh= 0.2*Ntot; 
	
	const int Ctot=0.1*Ntot; 
	const int Ce = 0.1*Nexc; 
	const int Ci = 0.1*Ninh; 
	
	const double Jexc =0.1; 
	const double Jinh = 0.5;
	
}
