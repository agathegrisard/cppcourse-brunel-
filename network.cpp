#include <fstream>
#include <iostream>
#include <cassert>
#include "constant.hpp"
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

		
void Network::addNeuron ()
{ 
	
	for (auto i=0; i<C::Nexc; ++i) 
	{ 
		Neuron n;
		ntw.push_back(n);
		n.setId(ntw.size());  
		n.setExcitatory();
	}
	
	for (auto i=0; i<C::Ninh; ++i)
	{ 
		Neuron n;
		ntw.push_back(n);
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
		
void Network::update (unsigned long time)
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
					ntw[target].receive(time, ntw[i].getTransmittedPot()*connexions[i][target]);
				}
			}
		}
		
		
		
	}
}

void Network::run2neurons(unsigned long time)
{ 
		std::ofstream n2spike; 
		n2spike.open("../spikes.gdf"); 
		
		Neuron n1, n2;
	   
		int i_start=1000;           										///time when the step current starts
		int i_stop=4000;           											///time when the step current ends
		int t_stop= time; //5000;            										///total simulation time
		double I_ext=1.01;                									///amplitude of the current
	   
	   
	   for(int t=0; t<=t_stop; ++t)											/// 
		{
			if((t>=i_start) and (t<=i_stop))
			{
				n1.setExtCurrent(I_ext);
			}
			else
			{
				n1.setExtCurrent(0.0);
			}
		   
			n1.update(1);
			n2.update(1);
		   
			if (n1.isSpiking()) {
			   n2spike<< "Spikes from 1 at : " << n1.convert_ms(n1.getLastSpike());
			  n2.receive (t + n1.getDelay(), n1.getMembPot()); 
			}
			
			if (n2.isSpiking()) 
			 {
				n2spike<< " spikes from 2 at: " <<n2.convert_ms(n2.getLastSpike()) << std::endl;
			}
		   
		   
		}
		
		n2spike.close();
		
}

void Network::run (unsigned long time)
{ 
	unsigned long t=0;
	
	std::ofstream spike; 
	spike.open("../sim.gdf"); 
	
	addNeuron(); 
	createConnections(); 
	
	while (t<time) 
	{
		update(t); 
		
		for (auto i=0; i<neurons_nb; ++i) 
		{ 
			if (ntw[i].isSpiking())
			{
				spike<<"neuron "<<i<<"'s last spike is at: "<<ntw[i].getLastSpike()<<std::endl;
			}
			
		}
		
		++t;
	}
	
	spike.close(); 
	
}


//{}
