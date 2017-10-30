#ifndef NETWORK_H
#define NETWORK_H

#include <vector>
#include "Neuron.hpp"
#include "Constant.hpp"


constexpr double J = 10.0; /// value after spiking of the post-synaptic excitement post-synaptic excitement value after spike

class Network 
{ 
	private: 
		std::vector<Neuron> netw; /// regroups all the neurons composing the network 
		std::vector<std::vector<int>> connexions; 
		
		size_t neurons_nb; 
		
		std::random_device random_nb;
		std::mt19937 list_random; 
		std::uniform_int_distribution<> excitatories; 
		std::uniform_int_distribution<> inhibitories; 
	
	public: 
		Network (); 
		virtual ~Network(); 
		
		void addNeuron (Neuron n); 
		void createConnections (); 
		
		void update (double current); 
	
	
} 

#endif
