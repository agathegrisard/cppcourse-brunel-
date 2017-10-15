#ifndef NETWORK_H
#define NETWORK_H

#include <vector>
#include "Neuron.hpp"

using namespace std; 

constexpr double E = 10.0;

class Network 
{ 
	private: 
		vector<Neuron*> netw; /// regroups all the neurons composing the network 
		vector<vector<int>> n_connect; ///all the connexions between the neurons of the network
	
	public: 
		Network (); 
		virtual ~Network(); 
		
		void addNeuron (Neuron* n); 
		
		void update (double current); 
	
	
} 

#endif
