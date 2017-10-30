
#include <iostream>
#include <cassert>
#include "constant.cc"
#include "network.hpp"


Network::Network ()
		: neurons_nb (C::Ntot),list_random(random_nb()), excitatories(0,C::Nexc-1), inhibitories(C::Nexc,C::Ntot-1)
{
	ntw.resize(neurons_nb);  
	connexions.resize(neurons_nb); 
	
	for (auto i=0; i<neurons_nb; ++i) 
	{ 
		connexions[i].resize(neurons_nb); 
	}
}
		
virtual Network::~Network()
{//~ { for(auto& neuron: netw) 
	//~ { delete neuron; 
		//~ neuron = nullptr; }
} 
		
void Network::addNeuron ()
{ 
	
	for (auto i=0; i<C::Nexc; ++i) 
	{ 
		ntw.push_back(Neuron n);
		n.setId(ntw.size());  
		n.setExcitatory();
	}
	
	for (auto i=0; i<C::Ninh; ++i)
	{ 
		ntw.push_back(Neuron n);
		n.setId(ntw.size());  
	}
 }


void Network::createConnections ()
{
	for (int target =0; target<C::Ntot; ++target)
	{
		for (size_t i=0; i<C::Ce; ++i) 
		{
			auto source = excitatories (list_random); 
			connexions[source][target] +=1; 	
		}
		for (size_t i=C::Ce; i<C::Ctot; ++i) 
		{ 
			auto source = inhibitories (list_random); 
			connexions[source][target] +=1; 
		}
	}
}
		
void Network::update ()
{ 
	//assert(t_stop-t_start <= C::delay_steps)
	
	for (auto i=0; i<neurons_nb; ++i) 
	{ 
		ntw[i].update(1);
		
		if (ntw[i].isSpiking()) 
		{ 
			for (size_t target=0; target<connexions[i].size(); ++i) 
			{ 
				if(connexions[i][target] > 0)
				{ 
					connexions[i][target].receive(ntw[i]);
				}
			}
		}
		
		
		
	}
}
