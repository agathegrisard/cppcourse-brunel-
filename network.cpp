
#include <iostream>
#include <cassert>
#include "constant.hpp"
#include "network.hpp"


Network::Network ()
{}
		
virtual Network::~Network()
{ for(auto& neuron: netw) 
	{ delete neuron; 
		neuron = nullptr; }
} 
		
void Network::addNeuron (Neuron* n)
{ netw.push_back(n); }

void Network::update (double current)
{ 
	for(size_t i=0; i<netw.size(); ++i) 
	{ Neuron* neuron = netw.at(i); 
		
		///update the neuron 
		neuron->update(1, current); 
		
		if (neuron->isSpiking())
		{ std::cout << i << ": spike at" << CST::STEP_VALUE * neuron->getClock() << 
			" ms, " << neuron->getPotential() <<" mV " <<endl;
		
		/// transmit spike to targets immediately
		for (auto target: n_connect.at(i))
		{ neurons.at(target)->receive(E); }
	}
}
}
