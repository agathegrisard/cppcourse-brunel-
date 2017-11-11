#ifndef NEURON_H
#define NEURON_H


#include <vector>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <random>

#include "constant.hpp"



/*! \class Neuron
 * 
 * structure that can spike and changes its membrane potential 
 * we study its evolution and interactions with others 
 * 
 */
 
 

class Neuron 															
{ 
	private:
	 
		double membrane_potential;
		int num_spikes;  												/// number of the spikes
		double i_ext; 													/// value of the incoming current 
		long clock; 													/// refractory clock initialised to 0 expressed in steps 
		
		int delay_steps;												/// delay in spike transmission expressed in steps
		
		std::vector <double> PotMem; 									/// where we store all the membrane potentials 
		std::vector <double> SpikeTime; 								/// where we store all the time where the neuron spikes 
		std::vector <double> buffer ; 									/// circular incoming buffer
		 
		bool excitatory; 
		
		
		
	
		
	public: 
	
		/*! \brief neuron constructor 
		 * 
		 * when creating a neuron, we put all his values at 0 or false
		 * only the delay takes the value of 1.5 
		 * 
		 * therefore, there is no parameters 
		 * 
		 */ 
		Neuron() ;
		
		/*! \brief neuron destructor 
		 * 
		 * given by default because it does not need to get rid of 
		 * specific data 
		 * 
		 */ 
		~Neuron () = default; 											
		
	
		double getMembPot ()const;										/// get the membrane potential 
		double getLastSpike () const; 									/// get the last spike registered in the vector 
		long getClock() const; 											/// get the neuron's clock 
		double getExtCurrent () const; 									/// get the external current   
		int getDelaySteps() const; 										/// get the delay in steps (more used than the previous getDelay() ) 
		int getNumSpikes () const; 										/// get the number of spikes
		std::vector<double> getSpikeTime () const; 						/// get the vector where are registered all the pikes of a neuron 
		bool getExcitatory () const; 									/// get the parameter excitatory - if it's false then the neuron is inhibitory
		double getTransmittedPot () const;								/// get the potential transmitted by another neuron 
		
		
		void setMembPot (double mp); 									/// set the membrane potential of a neuron at the given number
		void setExtCurrent (double i); 									/// set the external current at the given parameter i
		void setExcitatory(); 											/// set the bool excitatoy at true which means that the neuron becomes excitatory 
		
		
		/*! \fn isSpiking 
		 * 
		 * \brief tells if the the neuron completes the conditions to 
		 * spike 
		 * 
		 * constant because does not change anything in the class 
		 * 
		 * \return a bool 
		 * 
		 */ 
		bool isSpiking () const; 
		
		
		/*! \fn isRefractory 
		 * 
		 * \brief tells if the neuron has spiked and is now in the 
		 * refractroy time 
		 * 
		 * \param a long which corresponds to th time in step 
		 * 
		 * \return  if the table of spike times is not empty 
		 * and the instant time minus the last time it spikes is
		 *  inferior o the refractory time		
		 * 
		 */ 								
		bool isRefractory (long c) const; 								
		
		
		/*! \fn main update function 
		 * 
		 * \brief reset after spiking and increment the clock 
		 * 
		 * \param take the time it will turn
		 * because it is needed to set the time where it's stop 
		 * 
		 * \return nothing 
		 * 
		 */ 
		void update (int time_steps); 			
		
		/*! \fn update the membrane potential 
		 * 
		 * \brief called each time the update turns if it is not 
		 * in refractory 
		 * add any transmitted potential from the ring buffer 
		 * add background noise which is not stable 
		 * 
		 */ 			
		void updatePotential ();
		
		
		/*! \fn update used for the googleTest 
		 * 
		 * \brief call the updatePotentialTest 
		 * 
		 * it has no background noise so we can predict the value 
		 * 
		 * */ 										
		void updateTest(int t_step); 
		
		/*! \fn updatePotentialTest 
		 * 
		 * \brief used for the googleTests because no background noise $
		 * 
		 */ 
		void updatePotentialTest(); 
	
	
		/*! \fn receive
		 * 
		 * \brief changes the membran potential if it receives current 
		 * from another neuron 
		 * 
		 *\param time when he receives the spike an the added value 
		 * which corresponds to the membrane potentil of the other neuron 
		 * 
		 */ 
		void receive (unsigned long t_arrive, double p);				
	
		double convert_ms (long t); 									/// convert a step_time to a time in ms
		
}; 

#endif 
