#include <iostream>
#include <cmath>
#include "neuron.hpp" 

using namespace std; 

	
Neuron::Neuron () 														/// constructor 
	:membrane_potential(0.0), num_spikes (0), i_ext (0.0), SpikeTime (0), 
	delay (1.5), buffer (), clock (0), excitatory (false)
	
	{
		/// changes the delay expressed in time in ms
		/// get the value of a step in the constant file 
		delay_steps = delay / C::step_value; 
		
		/// give a size to the buffer 
		buffer.resize (delay_steps+1, 0.0);
		/// check the error 
		assert (buffer.size() == delay_steps +1);
	
	}

/// getters

double Neuron::getMembPot () const 
{ return membrane_potential; }

double Neuron::getLastSpike () const
{
	/// make sure that the vector is not empty 
	 if (! SpikeTime.empty ())
	{ return SpikeTime.back();}
	
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

std::vector<double> Neuron::getSpikeTime () const
{return SpikeTime; }

bool Neuron::getExcitatory () const
{ return excitatory; }

double Neuron::getTransmittedPot () const
{ 
	///depending on the type of the neuro, it does not send the same current 
	///all the values are find in the constant file 
	if (excitatory)
	{ return C::Jexc; }
	else { return C::Jinh; }
	
}

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
{ 
	/** the neuron spikes if its membrane potential is superior to a 
	 * given value 
	 * */
	return membrane_potential >= C::Vth;
}

bool Neuron::isRefractory (long c) const 
{ 
	/** first condition: the vector of spike has to have registered 
	 * values so it won't create any error 
	 * the refractory phase has a certain length `
	 * */
	
	return !SpikeTime.empty() && (c - SpikeTime.back() < C::Tref ); }


/// update functions
	
void Neuron::update (int time_steps)
{
	/// set the time in steps during which the function turns 
	const auto t_stop = clock + time_steps; 
	
	while (clock <t_stop) 
	{
		if (isRefractory (clock) ) 
		{ 
			/// if the neuron is refractory the membran ehas to be at 0
			setMembPot(0.0); }
			else { 
				updatePotential (); 
				
				/// we register the potential of the membrane in the vector
				PotMem.push_back(membrane_potential); 
			
			if (isSpiking ()) 
			{ 
				/** if the neuron is spiking we have to add the tme at
				 *  which it happens in the vector 
				 * */
				SpikeTime.push_back(clock); 
				
				/// we incement the number of spikes 			
				++num_spikes;
			 } 					
		}
		
		/// it is important to reset the buffer at 0 
		buffer [ clock % delay_steps] = 0.0; 							
		
		/// we increment the clock 
		++clock; 
	}
}

void Neuron::updatePotential () 
{ 
	membrane_potential = C::c1 * membrane_potential + C::c2*i_ext; 
	
	/// it add the value of incoming spikes
	membrane_potential += buffer [ clock % delay_steps]; 
	
	/// generate the background noise 
	random_device random; 
	mt19937 gen(random()); 
	poisson_distribution<> poisson(2);
	
	membrane_potential += poisson(gen)  * C::Jexc;
	
} 

void Neuron::updateTest(int t_step) 
{
	const auto t_stop = clock + t_step; 
	
	while (clock <t_stop) 
	{
		if (isRefractory (clock) ) 
		{ setMembPot(0.0); }
			else { 
				updatePotentialTest (); 
				PotMem.push_back(membrane_potential); 
			
			if (isSpiking ()) { SpikeTime.push_back(clock); 			/// add the time of spike if it does so 
								++num_spikes; } 						/// increment the number of spikes
		}
		
		buffer [ clock % delay_steps] = 0.0; 							/// reset the buffer 
		
		++clock; 
	}
}

void Neuron::updatePotentialTest () 
{ 
	/** does the same thing that the first updatePotential function 
	 * but it doesn't take into account the background noise 
	 * */ 
	membrane_potential = C::c1 * membrane_potential + C::c2*i_ext; 
	
	membrane_potential += buffer [ clock % delay_steps]; 
	
} 
		
/// function related to network 

void Neuron::receive (unsigned long t_arrive,double p) 				
{
	/** the time at which it prints is the time at which it arrives 
	 * modulo the size of the buffer
	 * that is why we check than the tim of printing is smaller than the 
	 * buffer size 
	 * */
	const size_t t_print = t_arrive % (delay_steps +1); 
	assert (t_print < buffer.size ()); 
	
	/** we add at the time print of the buffer the value of the membrane 
	 * of the sending neuron 
	 * */ 
	
	buffer [t_print] += p; 
}

/// convert from step to ms
double Neuron::convert_ms (long t)
{ return t* C::step_value; }



