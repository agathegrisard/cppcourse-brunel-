#ifndef NEURON_H
#define NEURON_H

#include <iostream>
#include <vector>
 

using namespace std; 

const double tau = 20.0; 
const double R = 20.0; 													/// résistance de la membrane
const int C = 1; 														/// capacité d'un neurone 
const int Vth = 20.0; 													/// valeur de treshold 
const double Vreset = 10; 												/// valeur à laquelle il revient apès avoir spike
const double h = 0.1;
const double Tref = 2.0; 												/// temps pour revenir après avoir redescendu
const int refract_time  = 20;											/// la valeur en step

const double step_value = 0.1; 											/// a step corresponds to 0.1 ms
 


class Neuron 															///  class representing a neuron 
{ 
	private:
	
		const double c1; 
		const double c2;
	 
		double membrane_potential;
		double num_spikes;  											/// number of the spikes
		double i_ext; 													/// value of the incoming current 
		long clock; 													/// refractory clock initialised to 0
		
		double delay;													/// delay expressed in ms
		int delay_steps;												/// delay in spike transmission expressed in steps
		
		vector <double> PotMem; 										/// where we store all the membrane potentials 
		vector <double> SpikeTime; 										/// where we store all the time where the neuron spikes 
		vector <double> buffer ; 										/// circular incoming buffer
	
		
	public: 
		Neuron() ;
		~Neuron () = default; 									/// default destructor
		
	
		double getMembPot ()const;										/// get the membrane potential 
		double getLastSpike () const; 									/// gets the last spike registered in the vector 
		long getClock() const; 											/// gets the neuron's clock 
		double getExtCurrent () const; 									/// gets the external current 
	
		void setMembPot (double mp); 
		void setExtCurrent (double i); 
		
		bool isSpiking () const; 										/// says if the neuron is spiking 
		bool isRefractory (double t) const; 							/// says if the neuron is in a refractory phase 
			
		void update (int steps); 										/// main updtae function: reset after spiking, increment the clock 
		void updatePotential (int steps);								/// function which changes the membrane potential according to time 
	
		void receive (unsigned long t_arrive, double p); 				/// receive incoming current
	
}; 

#endif 
