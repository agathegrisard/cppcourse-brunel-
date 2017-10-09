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


double Neuron::getMembPot ()
{ return membrane_potential; }

double Neuron::getLastSpike ()
{ if (! SpikeTime.empty ())
	{ return SpikeTime.back();}
	else { return 0; }
 }


void Neuron::setMembPot (double mp)
{ membrane_potential = mp; } 



bool Neuron::isSpiking ()
{ return membrane_potential > Vth; }

bool Neuron::isRefractory (double t)
{ return !SpikeTime.empty() && (t - SpikeTime.back() < Tref ); }


		
void Neuron::update (double current, double t)
{
	if (isRefractory (t) ) 
	{ setMembPot(0.0); }
		else { 
			double p (exp(-h/tau)*membrane_potential + current * (tau / C) * (1-exp(-h/tau))); 
			setMembPot(p); 
			PotMem.push_back(p); 
		
		if (isSpiking ()) { SpikeTime.push_back(t); }
	}
}
