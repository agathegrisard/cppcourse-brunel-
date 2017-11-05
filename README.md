# neuron

this project simulates the interaction sof a network of neurons. 
We used the simulation from the document "Dynamics of Sparsely Connected Networks of Excitatory and Inhibitory Spiking Neurons" written by Brunel. 

In this case, we set different constants that we can modify to change our setting. It will give another background for the neurons. 

Here, we set that we had 125000 neurons interacting with each other: 10000 of them are excitatories and 2500 are inhibitories. 
We have a grid which tells the number of connections between two specific neurons. Depending on the number of connections and the type of the neurons (excitatory or inhibitory), if one of them spikes the other will receive a certain current: the constant value is Jexc=0.1 if the neuron sending is excitatory and Jinh=-0.5 in the other case. However, we can change this value if we want to get another graph at the end. 

In the class Neuron, there is afunction that update the membrane potential each time step. In the class network, we will call this method for each neuron of the vector of neurons. It will therefore send a current to the other neurons he is connected to.

There are two simulations possible: one which represents the interaction between only two neurons, run2neurons(time). It takes the time in parameter to tell how many steps the program has to turn. The second simulation is for all the neurons composing the network: run(time). It also takes the time in parameter. 

These two functions are called in the main after having created the network. We give them in parameter the time it needs to run. 

In the terminal, to make the program run, we have to go to the correct file. Then, we write: cmake .. to set the Cmake. We type make when the configuring is done. Finally, when writing "./neuron", it will run the simulation. We can get the values of the spikes in the file "sim.gdf" for the all network and "spikes.gdf" for two neurons. 
From Jupyter, we can obtain the graph with the number of spikes in function of the time. 

There is also a file neuron_unittest where I test small part of my code. By writing ./neuron_unittest, you can run all the tests and see if they fail. 
