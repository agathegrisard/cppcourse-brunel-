#include <iostream>
#include <vector>
#include <cmath>

using namespace std; 

const double tau = 20;
const int C = 1; 
const int Vth = 20; 
const double sVreset = 10;
const double h = 0.01;
const double Tref = 1.0; 

class Neuron 
{ 
	private: 
		double membrane_potential;
		double spikes;  
		vector <double> PotMem; 
		vector<double> SpikeTime; 
	
		
	public: 
		Neuron (double mp, int s, int t); 
		Neuron() ;
		~Neuron () = default; 
		
		int getSpike (); 
		double getMembPot (); 
		
		void setSpike (int s); 
		void setMembPot (double mp); 
		
		bool isSpiking (); 
		bool isRefractory (double t); 
		
		void update (double current, double t); 
	
	
}; 

Neuron::Neuron (double mp, int s, int t)
	: membrane_potential (mp), spikes (s), SpikeTime (t)
	{}
	
Neuron::Neuron () 
	:membrane_potential(0.0), spikes (0), SpikeTime (0)
	{}

int Neuron::getSpike ()
{ return spikes;}

double Neuron::getMembPot ()
{ return membrane_potential; }

		
void Neuron::setSpike (int s)
{ spikes = s; }

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
			double p (exp(-h/tau)*membrane_potential + current * (tau / C) * (1-exp(-h/tau))); 
			setMembPot(p); 
			PotMem.push_back(p); 
		
		if (isSpiking ()) { SpikeTime.push_back(t); }
	}
}


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
	 
	 while (simTime < Tstop) 
	 {
		if (simTime >= a and simTime<b ) 
		{ 
			n.update (current, simTime); 
		} else { n.update (0.0, simTime); }
		
		simTime += h; 
	}
	
	return 0; 
}
