#include <iostream>
#include <vector>

using namespace std; 

const double tau = 20.0; 
const double R = 20.0; /// résistance de la membrane
const int C = 1; 
const int Vth = 20.0; 
const double Vreset = 10;
const double h = 0.1;
const double Tref = 2.0; 

class Neuron 
{ 
	private: 
		double membrane_potential;
		double num_spikes;  
		vector <double> PotMem; 
		vector <double> SpikeTime; 
	
		
	public: 
		Neuron (double mp, int s, int t); 
		Neuron() ;
		~Neuron () = default; 
		
	
		double getMembPot (); 
		double getLastSpike (); 
	
		void setMembPot (double mp); 
		
		bool isSpiking (); 
		bool isRefractory (double t); 
		
		void update (double current, double t); 
	
	
}; 
