#include <iostream>
#include <vector>

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
		~Neuron (); 
		
		int getSpike (); 
		int getSpikeTime (); 
		double getMembPot (); 
		
		void setSpike (int s); 
		void setSpikeTime (int t); 
		void setMembPot (double mp); 
		
		bool isSpiking (); 
		bool isRefractory (); 
		
		void update (double current, double t); 
	
	
}; 
