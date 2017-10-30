#include "gtest/gtest.h"
#include <cassert>
#include "neuron.hpp"

TEST(NeuronTest, Membrane) 
{
	Neuron neuron;
	
	neuron.setExtCurrent(1.0);
	neuron.update(1);													/// test one update 
	
	EXPECT_EQ(20.0 * (1.0 - std::exp(-0.1 / 20.0)), neuron.getMembPot());
}

TEST (NeuronTest, refractory) 
{ 
	Neuron neuron; 
	
	ASSERT_FALSE (neuron.isRefractory(1.0));					/// neuron should not be refractory after initiation1.0
}

/*TEST (NeuronTest, spike_right_time) 
{
	Neuron neuron; 
	
	neuron.setExtCurrent(1.01); 
	
	while (! neuron.isSpiking()) //recopier main ??????
	{neuron.update(); }
	
	EXPECT_EQ(1923,	neuron.getLastSpike()); 
}*/

TEST (NeuronTest, SpikeTimes)
{ 
	Neuron n;
	n.setExtCurrent(1.01); 
	
	
	n.update (924); 
	EXPECT_EQ(0, n.getNumSpikes());
	n.update (1); 
	EXPECT_EQ(1, n.getNumSpikes()); 
	EXPECT_EQ(0.0, n.getMembPot());  
	
	n.update (943); 
	EXPECT_EQ(1, n.getNumSpikes()); 
	n.update(1); 
	EXPECT_EQ(2, n.getNumSpikes()); 
	
}

TEST (TwoNeurons,WithPSpike) 
{
	Neuron n1, n2; 
	
	n1.setExtCurrent(1.01); 
	n2.setExtCurrent(1.0); 
	
	for (auto i=0; i<1869+ n2.getDelaySteps(); ++i) 
	{
		if (n1.update(1))
		{ 
			n2.receive(i+ n2.getDelaySteps(), 0.1)
			EXPECT_EQ(0.0, n1.getMembPot()); 
		}
		n2.update(1); 
	}
	
	EXPECT_EQ(0,n2.getNumSpikes()); 
	n2.update(1); 
	EXPECT_EQ(0,n2.getMembPot()); 
	EXPECT_EQ (1, n2.getNumSpikes()); 
	
}
	
int main(int argc, char** argv) 
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
	
}
