#include <iostream>
#include <cmath>
#include "neuron.hpp" 

using namespace std; 

Neuron::Neuron (double mp, int s, int t)
	: membrane_potential (mp), spikes (s), SpikeTime (t)
	{}
	
Neuron::Neuron () 
	:membrane_potential(0.0), spikes (0), SpikeTime (0)
	{}

int Neuron::getSpike ()
{ return spikes;}

int Neuron::getSpikeTime ()
{ return SpikeTime;}

double Neuron::getMembPot ()
{ return membrane_potential; }

		
void Neuron::setSpike (int s)
{ spikes = s; }

void Neuron::setSpikeTime (int t)
{ SpikeTime = t; }

void Neuron::setMembPot (double mp)
{ membrane_potential = mp; } 

bool Neuron::isSpiking ()
{ return membrane_potential > Vth; }

bool Neuron::isRefractory (double t)
{ return (t - SpikeTime [SpikeTime.size () ] < Tref ); }
		
void Neuron::update (double current, double t)
{
	if (isRefractory (t) ) 
	{ setMembPot(0.0); }
		else { 
			double p (exp(-h/tau). membrane_potential + current * tau / C * (1-exp(-h/tau)); 
			setMembPot(p); 
			PotMem.push_back(p); 
		
		if (isSpiking ()) { SpikeTime.pushback(t); }
}
