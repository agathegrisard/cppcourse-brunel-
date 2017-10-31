#include "gtest/gtest.h"
#include <cassert>
#include "neuron.hpp"

/*TEST(NeuronTest, Membrane) 
{
	Neuron neuron;
	
	neuron.setExtCurrent(1.0);
	neuron.update(1);													/// test one update 
	
	EXPECT_EQ(20.0 * (1.0 - std::exp(-0.1 / 20.0)), neuron.getMembPot());
}
*/
TEST (NeuronTest, refractory) 
{ 
	Neuron neuron;  
	
	ASSERT_FALSE (neuron.isRefractory(1.0));					/// neuron should not be refractory after initiation1.0
}


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

TEST (NeuronTest, PositiveInput) 
{
	Neuron n; 
	n.setExtCurrent(1.0); 
	
	n.update(1); 
	EXPET_EQ(20.0 * (1.0 - std::exp(-0.1 / 20.0)), n.getMembPot());
	
	n.update(1000); 
	EXPECT_EQ(0, n.getNumSpikes()); 
	EXPECT_GT(1E-3, std::fabs(19.999 - n.getMembPot())); 
	
	n.setExtCurrent(0.0); 
	n.update(2000); 
	EXPECT_NEAR(0,n.getMembPot(), 1e-3); 
	
}


TEST (TwoNeurons,WithPSpike) 
{
	Neuron n1, n2; 
	
	n1.setExtCurrent(1.01); 
	n2.setExtCurrent(1.0); 
	
	for (auto i=0; i<1869+ n2.getDelaySteps(); ++i) 
	{
		if (n1.isSpiking())
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

TEST (TwoNeurons,NoSpike) 
{ 
	Neuron n1, n2; 
	
	n1.setExtCurrent(1.01); 
	
	for (auto i=0; i< 925+ n1.getDelaySteps();++i)
	{
		n1.update(1); 
		
		if(n1.isSpiking()) 
		{
			n2.receive(i+n1.getDelaySteps(), 0.1); 
			EXPECT_EQ(0.0, n1.getMembPot()); 
		}
		
		n2.update(1); 
	}
	EXPECT_EQ(0.1, n2.getMembPot()); 
	
}





int main(int argc, char** argv) 
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
	
}
