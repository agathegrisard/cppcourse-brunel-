#include <iostream>
#include <cmath>
#include "neuron.hpp" 

using namespace std; 

	
Neuron::Neuron () 														/// constructor 
	:membrane_potential(0.0), num_spikes (0), i_ext (0.0), SpikeTime (0), 
	delay (1.5), buffer (), clock (0)
	
	{
		delay_steps = delay / step_value; 
		buffer.resize (delay_steps+1, 0.0);
		assert (buffer.size() == delay_steps +1);
	}

/// getters

double Neuron::getMembPot () const 
{ return membrane_potential; }

double Neuron::getLastSpike () const
{
	 if (! SpikeTime.empty ())
	{ return SpikeTime.back();}
	else { return 0; }
 }

double Neuron::getExtCurrent () const
 { return i_ext; }

long Neuron::getClock() const
{ return clock; }


/// setters 

void Neuron::setMembPot (double mp)
{ membrane_potential = mp; } 

void Neuron::setExtCurrent (double i) 
 { i_ext = i; } 


/// boolean functions 

bool Neuron::isSpiking () const 
{ return membrane_potential >= Vth; }

bool Neuron::isRefractory (long c) const 
{ return !SpikeTime.empty() && (c - SpikeTime.back() < Tref ); }


/// update functions
	
void Neuron::update ()
{
		if (isRefractory (clock) ) 
		{ setMembPot(0.0); }
			else { 
				updatePotential (); 
				PotMem.push_back(membrane_potential); 
			
			if (isSpiking ()) { SpikeTime.push_back(clock); 			/// add the time of spike if it does so 
								++num_spikes; } 						/// increment the number of spikes
		}
		
	buffer [ clock % delay_steps] = 0.0; 								/// reset the buffer 
	
	++clock; 
}

void Neuron::updatePotential () 
{ 
	membrane_potential = c1 * membrane_potential + c2*i_ext; 
	
	membrane_potential += buffer [ clock % delay_steps]; 
} 
		
/// function related to network 

void Neuron::receive (unsigned long t_arrive, double p) 				/// receive incoming spike
{
	const size_t t_print = t_arrive % (delay_steps +1); 
	assert (t_print < buffer.size ()); 
	buffer [t_print] += p; 
}


double Neuron::convert_ms (long t)
{ return t* step_value; }
