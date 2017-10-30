#include <iostream>
#include <cmath>
#include "neuron.hpp" 

using namespace std; 

	
Neuron::Neuron () 														/// constructor 
	:membrane_potential(0.0), num_spikes (0), i_ext (0.0), SpikeTime (0), 
	delay (1.5), buffer (), clock (0), excitatory (false)
	
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

double Neuron::getDelay() const 
{ return delay; }

int Neuron::getDelaySteps() const 
{ return delay_steps; }

int Neuron::getNumSpikes () const
{ return num_spikes; }

bool Neuron::getExcitatory () const
{ return excitatory; }

/// setters 

void Neuron::setMembPot (double mp)
{ membrane_potential = mp; } 

void Neuron::setExtCurrent (double i) 
 { i_ext = i; } 
 
void Neuron::setId(size_t i)
{ id = i; }

void Neuron::setExcitatory()
{ excitatory = true; }

/// boolean functions 

bool Neuron::isSpiking () const 
{ return membrane_potential >= Vth; }

bool Neuron::isRefractory (long c) const 
{ return !SpikeTime.empty() && (c - SpikeTime.back() < Tref ); }


/// update functions
	
void Neuron::update (int time_steps)
{
	const auto t_stop = clock + time_steps; 
	
	while (clock <t_stop) 
	{
		if (isRefractory (clock) ) 
		{ setMembPot(0.0); }
			else { 
				updatePotential (); 
				PotMem.push_back(membrane_potential); 
			
			if (isSpiking ()) { SpikeTime.push_back(clock); 			/// add the time of spike if it does so 
								++num_spikes; } 						/// increment the number of spikes
		}
		
		buffer [ clock % delay_steps] = 0.0; 							/// reset the buffer 
		
		++clock; 
	}
}

void Neuron::updatePotential () 
{ 
	membrane_potential = c1 * membrane_potential + c2*i_ext; 
	
	membrane_potential += buffer [ clock % delay_steps]; 
	
	random_device random; 
	mt19937 gen(random()); 
	poisson_distribution<int> poisson(2);
	
	membrane_potential += poisson(2)*C::Jexc;
	
} 
		
/// function related to network 

void Neuron::receive (unsigned long t_arrive, double p) 				/// receive incoming spike
{
	const size_t t_print = t_arrive % (delay_steps +1); 
	assert (t_print < buffer.size ()); 
	buffer [t_print] += p; 
}

/// convert from step to ms
double Neuron::convert_ms (long t)
{ return t* step_value; }

/// background noise and connections 


