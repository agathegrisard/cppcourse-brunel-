#ifndef CONSTANT_H 
#define CONSTANT_H 

#include <cmath> 

namespace C { 
	
		
	const double tau = 20.0; ///tau of neuron membrane (20 ms)
	const double R = 20.0;	/// membrane resistance
	const int C = 1; 		/// neuron's capacity 
	const double Vth = 20.0; /// treshold value 
	const double h = 0.1;
	const double Tref = 20; /// time of refractory phase
	

	const double c1 = exp(-h/tau);/// first constant used for the membrane potential computation 
	const double c2 = R*(1.0-c1);/// second constant needed

	const double step_value = 0.1; /// a step corespond to 0.1 ms 
	
	const int Ntot=12500; ///total number of neurons in the network 
	const int Nexc=0.8*Ntot; ///more excitatories neurons than inhibitories 
	const int Ninh= 0.2*Ntot; ///corresponds to 20% of the total number of neurons 
	
	const int Ctot=0.1*Ntot;///the number of connections is 10% of the total number of neurons
	const int Ce = 0.1*Nexc;///it is also true for the respective excitatory 
	const int Ci = 0.1*Ninh; /// and inhibitory 
	
	const double Jexc =0.1;///current sent by excitatories neurons
	const double Jinh = - 0.5;/// current sent by inhibitories neurons 
	
}

#endif
