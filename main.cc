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
	unsigned int time_simulation = 5000; 
	
	///see how 2 neurons interact
	net.run2neurons(5000); 
	
	///run the simulation during 1000 steps 
	net.run(1000); 
	
	return 0; 
  
}



