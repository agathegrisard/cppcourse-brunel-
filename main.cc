#include <iostream>
#include <cassert>
#include "neuron.hpp"
#include "network.hpp"

using namespace std; 

int main(int argc, char** argv)
{
	Network net; 
	unsigned int time_simulation = 5000; 
	
	net.run2neurons(5000); 
	net.run(5000); 
	
	return 0; 
  
}



