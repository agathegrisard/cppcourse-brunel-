#include <iostream>
#include "neuron.hpp"
#includ "constant.hpp"

using namespace std; 


int main ()
{
	 
	double Tstart (0.0); 
	double Tstop (0.0); 
	double simTime (Tstart);
	double a (0.0); 
	double b (0.0); 
	double current (0.0);  
	Neuron n; 
	
	
	cout << " How long does the simulation last?" << endl; 
	 cin >> Tstop; 
	 
	 cout << " what is the time interval for the external current? " << endl; 
	 cin >> a; 
	 cin >> b; 
	 
	 cout << " What is the external current value ? " << endl; 
	 cin >> current;
	
	 
	 while (simTime <= Tstop) 
	 {
		if (simTime >= a and simTime<b ) 
		{ 
			n.update (current, simTime); 
		} else { n.update (0.0, simTime); }
		
		simTime += h; 
		cout << "SpikeTime at : " << simTime << " " << n.getLastSpike() << endl; 
	}
	
	return 0; 
}
