#ifndef NEURON_H
#define NEURON_H


#include <vector>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <random>

#include "constant.hpp"




 

class Neuron 															///  class representing a neuron 
{ 
	private:
	 
		double membrane_potential;
		int num_spikes;  												/// number of the spikes
		double i_ext; 													/// value of the incoming current 
		long clock; 													/// refractory clock initialised to 0 expressed in steps 
		
		double delay;													/// delay expressed in ms
		int delay_steps;												/// delay in spike transmission expressed in steps
		
		std::vector <double> PotMem; 										/// where we store all the membrane potentials 
		std::vector <double> SpikeTime; 										/// where we store all the time where the neuron spikes 
		std::vector <double> buffer ; 										/// circular incoming buffer
		 
		
		size_t id; 
		bool excitatory; 
		
	
		
	public: 
		Neuron() ;
		~Neuron () = default; 											/// default destructor
		
	
		double getMembPot ()const;										/// get the membrane potential 
		double getLastSpike () const; 									/// gets the last spike registered in the vector 
		long getClock() const; 											/// gets the neuron's clock 
		double getExtCurrent () const; 									/// gets the external current 
		double getDelay() const;
		int getDelaySteps() const; 
		int getNumSpikes () const; 
		bool getExcitatory () const; 
		double getTransmittedPot () const;
		
		
		void setMembPot (double mp); 
		void setExtCurrent (double i); 
		void setId(size_t i); 
		void setExcitatory(); 
		
		bool isSpiking () const; 										/// says if the neuron is spiking 
		bool isRefractory (long c) const; 								/// says if the neuron is in a refractory phase 
			
		void update (int time_steps); 									/// main update function: reset after spiking, increment the clock 
		void updatePotential ();										/// function which changes the membrane potential according to time 
	
		void receive (unsigned long t_arrive, double p);				/// receive incoming current
	
		double convert_ms (long t); 										/// convert a step_time to a time in ms
		
		void connect (size_t target_neuron); 
}; 

#endif 
