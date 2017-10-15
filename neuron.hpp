#ifndef NEURON_H
#define NEURON_H

#include <iostream>
#include <vector>

#include "constant.hpp" 

using namespace std; 

const double tau = 20.0; 
const double R = 20.0; /// résistance de la membrane
const int C = 1; /// capacité d'un neurone 
const int Vth = 20.0; /// valeur de treshold 
const double Vreset = 10; /// valeur à laquelle il revient apès avoir spike
const double h = 0.1;
const double Tref = 2.0; /// temps pour revenir après avoir redescendu
						/// => dans constant.hpp on a la valeur en step
class Neuron 
{ 
	private: 
		double membrane_potential;
		double num_spikes;  
		vector <double> PotMem; 
		vector <double> SpikeTime; 
		long clock; /// refractory clock initialised to 0
		vector <double> buffer (CST:: DELAY_OF_TRANSMISSION); 
		/// circular incoming buffer
	
		
	public: 
		Neuron (double mp, int s, int t); 
		Neuron() ;
		~Neuron () = default; 
		
	
		double getMembPot ()const; 
		double getLastSpike (); 
		long getClock() const;
	
		void setMembPot (double mp); 
		
		bool isSpiking (); 
		bool isRefractory (double t) const; 
		
		void update (double current, int step); 
		void updatePotential (double current, int step);
	
		void receive (double pot);
	
}; 

#endif 
