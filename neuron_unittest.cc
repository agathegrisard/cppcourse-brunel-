#include "gtest/gtest.h"
#include <cassert>
#include "neuron.hpp"


/// we check that the mebrane potential has the good value 
TEST(NeuronTest, Membrane) 
{
	Neuron neuron;
	
	neuron.setExtCurrent(1.0);
	
	/// test one update 
	neuron.updateTest(1);													
	
	EXPECT_EQ(20.0 * (1.0 - std::exp(-0.1 / 20.0)), neuron.getMembPot());
}

/// we check that the neuron is refractory after spiking 
TEST (NeuronTest, refractory) 
{ 
	Neuron neuron;  
	
	/// neuron should not be refractory after initiation1.0
	ASSERT_FALSE (neuron.isRefractory(1.0));					
}

/// we check that the neuron spikes at the right time 
TEST (NeuronTest, SpikeTimes)
{ 
	Neuron n;
	n.setExtCurrent(1.01); 
	
	///update until 923 steps - no spikes yet 
	n.updateTest (923); 
	EXPECT_EQ(0, n.getNumSpikes());
	
	/// at 924, spiking occurs 
	n.updateTest (1); 
	///incrementation of number of spikes
	EXPECT_EQ(1, n.getNumSpikes());  
	
	/**at 925 steps, the membrane potential should be 0 because 
	 * the neuron is refractory
	 * */
	n.updateTest(1); 
	EXPECT_EQ(0, n.getMembPot());  
	
	///second spiking at 942 steps 
	n.updateTest (941); 
	EXPECT_EQ(1, n.getNumSpikes()); 
	n.updateTest(1); 
	EXPECT_EQ(2, n.getNumSpikes()); 
	
}

/// we check that we obtain good values when we set a positive input
TEST (NeuronTest, PositiveInput) 
{
	Neuron n; 
	n.setExtCurrent(1.0); 
	
	///test the membrane potential for one step 
	n.updateTest(1); 
	EXPECT_EQ(20.0 * (1.0 - std::exp(-0.1 / 20.0)), n.getMembPot());
	
	///update 10000 steps but should not spike 
	for (int i(0); i<10000;++i)
	{n.updateTest(i); } 
	EXPECT_EQ(0, n.getNumSpikes()); 
	EXPECT_GT(1E-3, std::fabs(19.999 - n.getMembPot())); 
	
	///when the external current is 0 the membrane potential does not change
	n.setExtCurrent(0.0); 
	for (int i(0); i<2000; ++i)
	{n.updateTest(2000); }
	EXPECT_NEAR(0,n.getMembPot(), 1e-3); 
	
}

/// we check that we get the good values if we put a negative current 
TEST (NeuronTest, NegativeInput) 
{
	Neuron n; 
	n.setExtCurrent(-1.0); 
	
	/// when the input is negative the membrane potential is also negative
	n.updateTest(1); 
	EXPECT_EQ(-20.0*(1.0-std::exp(-0.1/20.0)), n.getMembPot()); 
	
	///there is no spiking during 1000 steps 
	for (int i(0); i<1000; ++i) 
	{n.updateTest(i); }
	EXPECT_EQ(0, n.getNumSpikes()); 
	EXPECT_GT(1E-3, std::fabs(-19.999 - n.getMembPot()));
	
	///when we set the current at 0, the membrane potential is 0 
	n.setExtCurrent(0.0); 
	
	for(int i(0); i<2000; ++i) 
	{ n.updateTest(i); }
	EXPECT_NEAR (0, n.getMembPot(), 1e-3); 
}

TEST (NeuronTest, StandAloneSimulation) 
{ 
	///we turn a simulation for one neuron 
	Neuron n; 
	n.setExtCurrent(10.1); 
	
	for (int i(0); i<110; ++i) 
	{ n.updateTest(i); }
	EXPECT_EQ (150, n.getNumSpikes());
}

/// we see if there is no spiking for two neurons 
TEST (TwoNeurons,NoSpike) 
{ 
	Neuron n1, n2; 
	
	/// we set an external current for the first neuron 
	n1.setExtCurrent(1.01); 
	
	/** we make it turn 925 steps plus its delay to reach the secind neuron 
	 * if it spikes, we call the function receive of the othe neuron 
	 *  we update again neuron 1 so it is in refractory phase 
	 * and then we update the second neuron 
	 * */
	for (auto i=0; i< 925+ n1.getDelaySteps();++i)
	{
		n1.updateTest(1); 
		
		if(n1.isSpiking()) 
		{
			n2.receive(i+n1.getDelaySteps(), 0.1);
			
			n1.updateTest(1);  
			EXPECT_EQ(0.0, n1.getMembPot()); 
		}
		
		n2.updateTest(1); 
	}
	EXPECT_NEAR(0.2, n2.getMembPot(), 0.2); 
	
}

TEST (NeuronTest, RecieveSpike) {

	Neuron n;
	double J = 0.1;

	///make the neuron recieve a spike with weight 0.1 and delay 15 steps
	n.receive(0, J);

	///update the neuron one step past the delay
	
	n.updateTest(n.getDelaySteps()+1);
	

	///check if its membrane potential is equal to the spike recieved
	EXPECT_EQ(J, n.getMembPot());
} 

///we run all the tests 

int main(int argc, char** argv) 
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
	
}

