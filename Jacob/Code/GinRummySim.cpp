#include "GinRummy.h"
using namespace SimModels;

int main() {


	// Construct new conversation
	try
	{
		GinRummy simulator;
			
		// Output state of the simulator
		simulator.Insert();

		// Initialize simulator
		simulator.Initialize(); 
	
		// Output state of the simulator
		simulator.Insert();
	
		// begin simulator
		simulator.Simulate();

		// Output state of the simulator
		simulator.Insert();


		// Output simulator postsimulation report
		simulator.WrapUp(); 
	}
	catch ( AppError e )
	{
		
		cout << "\nSimulation Error Detected!\n------------\n";
		cout << "Description : " << e.getMsg()    << "\n";
		cout << "Origin      : " << e.getOrigin() << "\n\n";
	}
	
    return 0;

}//main

