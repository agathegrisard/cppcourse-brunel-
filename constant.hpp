#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace CST {
	
	/// time after spiking expressed in steps 
	constexpr int REFRACTORY_TIME = 20;
	
	/// membrane potential threshold
	/// spiking if the membrane potential of a neuron is above this value
	constexpr int THRESHOLD = 20;

	/// delay in spike transmission expressed in steps
	constexpr int DELAY_OF_TRANSMISSION = 15;
	
	/// size of the ring buffer which store the transmission delay
	constexpr int BUFFER_SIZE = 2 * DELAY_OF_TRANSMISSION;
	
	/// name of the file which edit the membrane potentials for a unique neuron
	constexpr char POTENTIAL_FILE = "potential.file.txt";
	
	/// value after spiking of the post-synaptic excitement post-synaptic excitement value after spike
	constexpr double E = 10.0;
	
	/// a step corresponds to 0.1 ms
	constexpr double STEP_VALUE = 0.1;
	
	/// default current for some spikes
	constexpr double DEFAULT_CURRENT= 1.5;
}

#endif
