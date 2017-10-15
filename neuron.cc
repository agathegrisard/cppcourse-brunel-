#include <iostream>
#include <cmath>
#include "neuron.hpp" 

using namespace std; 

Neuron::Neuron (double mp, int s, int t)
	: membrane_potential (mp), num_spikes (s), SpikeTime (t)
	{}
	
Neuron::Neuron () 
	:membrane_potential(0.0), num_spikes (0), SpikeTime (0)
	{}


double Neuron::getMembPot () const 
{ return membrane_potential; }

double Neuron::getLastSpike ()
{ if (! SpikeTime.empty ())
	{ return SpikeTime.back();}
	else { return 0; }
 }

long Neuron::getClock() const
{ return clock; }

void Neuron::setMembPot (double mp)
{ membrane_potential = mp; } 



bool Neuron::isSpiking ()
{ return membrane_potential > Vth; }

bool Neuron::isRefractory (double t) const 
{ return !SpikeTime.empty() && (t - SpikeTime.back() < Tref ); }


		
void Neuron::update (double current, int step)
{
	if (isRefractory (clock) ) 
	{ setMembPot(0.0); }
		else { 
			updatePotential (current, step); 
			PotMem.push_back(membrane_potential); 
		
		if (isSpiking ()) { SpikeTime.push_back(clock); /// add the time of spike if it does so 
							++num_spikes; } /// increment the number of spikes
	}
	
	buffer [ clock % CST::DELAY_OF_TRANSMISSION] = 0.0; /// reset the buffer 
	
	++clock; 
}

void Neuron::updatePotential (double current, int step) 
{ 
	for (auto i=0; i<step, ++i) 
	{ membrane_potential = exp(- CST::STEP_VALUE / tau)* membrane_potential 
							+ R * (1.0 - exp(- CST::STEP_VALUE / tau))*current; }
	
	membrane_potential += buffer [ clock % CST::DELAY_OF_TRANSMISSION]; 
} // revoir cette formule 
		

void Neuron::receive (double p) /// receive incoming spike
{ if (!isRefractory()) /// buffered transmission
	{ buffer[clock % CST::DELAY_OF_TRANSMISSION] += p; }
}
		
		
		
© 2017 GitHub, Inc.
