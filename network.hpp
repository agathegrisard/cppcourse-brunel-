#ifndef NETWORK_H
#define NETWORK_H

#include <vector>
#include <cassert>
#include <algorithm>
#include <random>
#include <iostream>

#include "constant.hpp"
#include "Neuron.hpp"



constexpr double J = 10.0; /// value after spiking of the post-synaptic excitement post-synaptic excitement value after spike

class Network 
{ 
	private: 
	
		std::vector<Neuron> ntw; /// regroups all the neurons composing the network 
		std::vector<std::vector<int>> connexions; 
		
		size_t neurons_nb; 
		
		std::random_device random_nb;
		std::mt19937 list_random; 
		std::uniform_int_distribution<> excitatories; 
		std::uniform_int_distribution<> inhibitories; 
	
	public: 
		Network (); 
		~Network() = default; 
		
		void addNeuron (); 
		void createConnections (); 
		
		void update (unsigned long time); 
		
		void run2neurons (unsigned long time); 
		void run (unsigned long time);
	
	
};

#endif
