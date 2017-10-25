#include <iostream>
#include <fstream>
#include <cassert>
#include "neuron.hpp"


using namespace std; 

int main(int argc, char** argv)
{
   //ofstream spike ("potential.dat");
    Neuron n1, n2;
   
    int i_start=1000;           										///time when the step current starts
    int i_stop=4000;           											///time when the step current ends
    int t_stop=5000;            										///total simulation time
    double I_ext=1.01;                									///amplitude of the current
   
  if(argc>1)            												///send an error
    {
        I_ext=atof(argv[1]);
    }
   
   
   for(int t=0; t<=t_stop; ++t)
    {
        if((t>=i_start) and (t<=i_stop))
        {
            n1.setExtCurrent(I_ext);
        }
        else
        {
            n1.setExtCurrent(0.0);
        }
       
        n1.update();
        n2.update();
       
        if (n1.isSpiking()) {
           cout << "Spikes at : " << n1.convert_ms(n1.getLastSpike()) << endl;
        }
       
       
    }
    return 0;
}



