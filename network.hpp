#ifndef NETWORK_H
#define NETWORK_H

#include <vector>
#include "Neuron.hpp"

using namespace std; 

constexpr double J = 10.0; /// value after spiking of the post-synaptic excitement post-synaptic excitement value after spike

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
