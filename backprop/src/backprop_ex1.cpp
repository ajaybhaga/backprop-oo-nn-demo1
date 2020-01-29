

// Backpropgation Example program

#include <cstdio>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ncurses.h>
#include <cassert>
#include "../../lib/backprop.h"
#include "../../lib/common.h"

int main()
{
	std::srand(1);
/*
	Pattern *data[250];
	std::ifstream infile("data/lin2var.train");
	if (infile.fail()) 
	{
		std::cout << "Could not open pattern file...\n";
		return 1;
	}
	fori(250)
		data[i] = new Pattern(2, 1, infile);
	infile.close();
*/

	// Create XOR Training Set
	Pattern *data[4];
	                    // sizes, id, input, output
	data[0] = new Pattern(2, 1, 1, 0.0, 0.0, 0.0);
    data[1] = new Pattern(2, 1, 2, 0.0, 1.0, 1.0);
    data[2] = new Pattern(2, 1, 3, 1.0, 0.0, 1.0);
    data[3] = new Pattern(2, 1, 4, 1.0, 1.0, 0.0);


    // Create Backpropagation Network
    std::cout << "Creating Backpropagation Network:\n";
    Base_Node *Node[6];
    Base_Link *Link[9];

    Node[0] = new Input_Node;
    Node[1] = new Input_Node;

    Node[2] = new BP_Middle_Node(0.45, 0.9);
    Node[3] = new BP_Middle_Node(0.45, 0.9);
    Node[4] = new BP_Middle_Node(0.45, 0.9);

    Node[5] = new BP_Output_Node(0.45, 0.9);

    // Create links for network
    fori(9)
        Link[i] = new BP_Link();

    // Connect network
    int curr = 0;
    for (int i = 2; i <= 4; i++) {
        for (int j = 0; j <= 1; j++) {
            Connect(Node[j], Node[i], Link[curr++]);
        }
    }

    for (int j = 2; j <= 4; j++) {
        Connect(Node[j], Node[5], Link[curr++]);
    }

    // Train backpropagation network
	long iteration = 0;
	int good = 0;

	double tolerance = 0.5;
	double total_error;

	// Train until all patterns are correct
	while (good < 4) {

	    good = 0;
	    total_error = 0.0;

	    fori(4) {
            // Set input node values
            Node[0]->Set_Value(data[i]->In(0));
            Node[1]->Set_Value(data[i]->In(1));

            // Forward pass
            for (int j = 2; j <= 5; j++) {
                Node[j]->Run();
            }

            // Set error values
            Node[5]->Set_Error(data[i]->Out(0));

            // Backward pass
            for (int j = 5; j >= 2; j--) {
                Node[j]->Learn();
            }

            if (fabs(Node[5]->Get_Value() - data[i]->Out(0)) < tolerance) {
                good++;
            }

            total_error += fabs(Node[5]->Get_Error());

        }

        if (iteration % 1000 == 0) {
            cout << iteration << ". " << good << "/4" << " Error: " << std::setprecision(15) << total_error << endl;
            iteration++;
        }
	}


	//std::cout << "ADALINE Performance: " << correct << "/" << total << " correct.\n";

	return 0;
}







