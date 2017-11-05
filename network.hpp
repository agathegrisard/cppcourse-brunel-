#ifndef NETWORK_H
#define NETWORK_H

#include <vector>
#include <cassert>
#include <algorithm>
#include <random>
#include <iostream>

#include "constant.hpp"
#include "Neuron.hpp"

/*! \class Network
 * 
 * structure where we connect several neurons and see how they interact 
 * 
 */

class Network 
{ 
	private: 
	
		/// vector where we regroup all the neurons composing the network 
		std::vector<Neuron> ntw; 
		
		/** vector of vector where we put the value of connections
		 *  between two neurons 
		 * on the horizontal we have the receiving one 
		 * on the vertical the sending ones 
		 * */
		std::vector<std::vector<int>> connexions; 
		
		/// correspond to the size of the vectors 
		size_t neurons_nb; 
		
		/** needed to generate aleatory network 
		 * init random distribution and engine 
		 * */ 
		std::random_device random_nb;
		std::mt19937 list_random; 
		std::uniform_int_distribution<> excitatories; 
		std::uniform_int_distribution<> inhibitories; 
	
	public: 
	
		/** \fn neuron constructor 
		 * 
		 * does not take any parameter 
		 * 
		 * \brief initializes the attributs with constants 
		 * 
		 * */ 
		Network ();
		
		/** neuron destructor 
		 * 
		 * defined by default 
		 * just erase the ibject when finished using it 
		 * 
		 * */  
		~Network() = default; 
		
		/** \fn addNeuron 
		 * 
		 * \brief creates the network 
		 * 
		 * until we reach the good number of excitatory neurons 
		 * they are all refractory 
		 * 
		 * then we add the good number of inhibitory 
		 * 
		 * each time we set the "identity" of the neuron which one 
		 * of its attribute 
		 * 
		 * */ 
		void addNeuron (); 
		
		/** \fn creatConnections
		 * 
		 * \brief we call the random values to connect the neurons between 
		 * each other 
		 * 
		 * the value of the case is therefore not known if we don't 
		 * show the grid 
		 * 
		 * */ 
		void createConnections (); 
		
		/** \fn update 
		 * 
		 * \brief updates each neuron with the current he received from 
		 * the neurons he is connected to
		 * 
		 * \param specified number of time steps
		 * 
		 * */
		void update (unsigned long time); 
		
		/** \fn run2neurons 
		 * 
		 * \brief see the interactions between two neurons 
		 * 
		 * \param specified number of time steps 
		 * 
		 * */ 
		void run2neurons (unsigned long time); 
		
		/** \fn run the simulation for multiple neurons 
		 * 
		 * \brief save he values of the spikes so we can print the plot
		 * 
		 * \param specified number of time steps 
		 * 
		 * */  
		void run (unsigned long time);
	
	
};

#endif
