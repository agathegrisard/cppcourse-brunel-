#include "gtest/gtest.h"
#include <cassert>
#include "neuron.hpp"

TEST(NeuronTest, Membrane) 
{
	Neuron neuron;
	
	neuron.setExtCurrent(1.0);
	neuron.update();													/// test one update 
	
	EXPECT_EQ(20.0 * (1.0 - std::exp(-0.1 / 20.0)), neuron.getMembPot());
}

TEST (NeuronTest, refractory) 
{ 
	Neuron neuron; 
	
	ASSERT_FALSE (neuron.isRefractory(1.0));					/// neuron should not be refractory after initiation1.0
}

TEST (NeuronTest, spike_right_time) 
{
	Neuron neuron; 
	
	neuron.setExtCurrent(1.01); 
	
	while (! neuron.isSpiking()) //recopier main ??????
	{neuron.update(); }
	
	EXPECT_EQ(1923,	neuron.getLastSpike()); 
}
	
int mainn(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
	
}
