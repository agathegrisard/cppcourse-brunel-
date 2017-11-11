#include <iostream>
#include <cassert>
#include "neuron.hpp"
#include "network.hpp"

using namespace std; 

int main(int argc, char** argv)
{
	///initialized a network 
	Network net; 
	
	///set a time for our simulation
	unsigned int time_simulation = 1000; 
	
	///see how 2 neurons interact
	net.run2neurons(time_simulation); 
	
	///run the simulation during 1000 steps 
	net.run(time_simulation); 
	
	return 0; 
  
}



