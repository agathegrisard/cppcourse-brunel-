#include <fstream>
#include <iostream>
#include <cassert>
#include "constant.hpp"
#include "network.hpp"


Network::Network ()
		: neurons_nb (C::Ntot),list_random(random_nb()), 
		excitatories(0,C::Nexc-1), inhibitories(C::Nexc,C::Ntot-1)
		/// the number of excitatories goes from 0 to the Number of excitatories -1
		/** the number of inhibitories goes from the number of 
		 * excitatories to the total number of neurons - 1 
		 * */ 
{
	/// the vector of neurons has a size of the attribute number of neurons 
	ntw.resize(neurons_nb);  
	/// the connexions grid also have this size 
	connexions.resize(neurons_nb); 
	
	/** for each neuorn in vertical we have to give him the same size  
	 * in horizontal so we can form a 2 entries table 
	 * */ 
	for (auto i=0; i<neurons_nb; ++i) 
	{ 
		connexions[i].resize(neurons_nb); 
	}
}

		
void Network::addNeuron ()
{ 
	///we start to create excitatories neurons 
	for (auto i=0; i<C::Nexc; ++i) 
	{ 
		Neuron n;
		
		/// we push back a random neuron in the ntw vector 
		ntw.push_back(n);
		
		/** we set the identifiant of the neuron which corresponds
		 * to its number in the grid 
		 * */  
		n.setId(ntw.size());  
		
		/// we change its excitatory attribute at true 
		n.setExcitatory();
	}
	
	/// then we add the good amount of inhibitories at the end of the vector
	for (auto i=0; i<C::Ninh; ++i)
	{ 
		Neuron n;
		
		/// we create a random neuron 
		ntw.push_back(n);
		
		/// we set its identifiant 
		n.setId(ntw.size()); 
		
		/** we don't need to change its excitatory attribute because 
		 * it is by default at false (see neuron's constructor) 
		 * */
	} 
 }


void Network::createConnections ()
{
	/// we scroll until we reach the total number of neurons in the network 
	for (int target =0; target<C::Ntot; ++target)
	{
		///we scroll until we have the good number of excitatories connections
		for (size_t i=0; i<C::Ce; ++i) 
		{
			/// we get randomly the number of the sending neuron 
			auto source = excitatories (list_random);
			
			/** we put the right amount of connections in the table 
			 * the source is the number of the sending neuron 
			 * target is the number which will receive the signal 
			 * */ 
			connexions[source][target] +=1; 	
		}
		
		/// we do the same thing as for the excitatories for the inhibitories 
		for (size_t i=C::Ce; i<C::Ctot; ++i) 
		{ 
			auto source = inhibitories (list_random); 
			connexions[source][target] +=1; 
		}
	}
}
		
void Network::update (unsigned long time)
{ 
	/// for each neuron we will call its update function 
	for (auto i=0; i<neurons_nb; ++i) 
	{ 
		ntw[i].update(1);
		
		/** when the neuron spikes, we have to make sure it sends current 
		 * to his connected neurons 
		 * */ 
		if (ntw[i].isSpiking()) 
		{ 
			/// we scroll all the neurons to whom he sends a signal 
			for (size_t target=0; target<connexions[i].size(); ++i) 
			{ 
				/** we have that the connection is not 0, which means he has 
				 * a connection or more with this specific neuron 
				 * */
				if(connexions[i][target] > 0)
				{ 
					/** we call the function receive for each connected neuron
					 * the parameter are the instant time steps 
					 * and the membrane potential of the sending neuron 
					 * */ 
					ntw[target].receive(time, ntw[i].getTransmittedPot()*connexions[i][target]);
				}
			}
		}
		
	}
		
}

void Network::run2neurons(unsigned long time)
{ 
	/// we create a file where we save the time of spiking and the membrane potential
		std::ofstream n2spike; 
		n2spike.open("../spikes.gdf"); 
	
	/// we create 2 neuron s
		Neuron n1, n2;
	   
		int i_start=1000;           									///time when the step current starts
		int i_stop=4000;           										///time when the step current ends
		int t_stop= time; 												///total simulation time in steps 
		double I_ext=1.01;                								///amplitude of the current
	   
	   
	   for(int t=0; t<=t_stop; ++t)										///turns until the time is done  
		{
			if((t>=i_start) and (t<=i_stop))							///we only send current during a certain time
			{
				n1.setExtCurrent(I_ext);
			}
			else
			{
				n1.setExtCurrent(0.0);									///otherwise there will be no external current
			}
		   
		   /// we update each neuron for a time step of 1 because each loop we call again update 
			n1.update(1);
			n2.update(1);
		   
			if (n1.isSpiking()) {
			   n2spike<< "Spikes from 1 at : " << n1.convert_ms(n1.getLastSpike())<<std::endl;
			  /// teh second neuron has a delay before receiving the current from the first neuron 
			  n2.receive (t + n1.getDelay(), n1.getMembPot());  
			}
			
			if (n2.isSpiking()) 
			 {
				n2spike<< " spikes from 2 at: " <<n2.convert_ms(n2.getLastSpike()) << std::endl;
			}
		   
		   
		}
		
		/// we close the file where we stored all the values 
		n2spike.close();
		
}

void Network::run (unsigned long time)
{ 
	unsigned long t=0;
	
	/// cerate a file where we save the values of spiking time for each neuron
	std::ofstream spike; 
	spike.open("../sim.gdf"); 
	
	///creation of the network 
	addNeuron(); 
	
	///create the connections between the neurons 
	createConnections(); 
	
	
	///make the loop turns until it reaches the time of simulation 
	while (t<time) 
	{
		update(t); ///we update for each step the network 
		
		++t; ///incrementation of the time 
	}
	
	///saving of the values in the file 
	
	for (auto i=0; i<neurons_nb; ++i) 
		{ 
			for (auto j=0; j<ntw[i].getNumSpikes(); ++j) 
			{ 
				spike<<ntw[i].getSpikeTime()[j]<<"\t"<<i<<"\n"; 
				}
			
		}
	
	///close the file 	
	spike.close(); 
	
}



