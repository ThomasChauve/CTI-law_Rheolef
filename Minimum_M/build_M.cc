// I am writting this file using the exemple 2.1 from Pierre documentation and eshelby exemple from Vero
#include "rheolef.h"
#include <iostream>
#include <valarray>
#include <string>
#include <stdlib.h>
using namespace rheolef;
using namespace std;
#include "BCs.icc" // Is this a file to defined boundary conditions

int main(int argc, char**argv) {
    environment rheolef(argc, argv);
    geo omega (argv[1]); // Mesh grid
    //space Xh (omega, argv[2], "vector");
    space Xh = embankment_space(omega, argv[2]); // Space for uh
    string grad_approx = "P" + itos(Xh.degree()-1) + "d";	// Polyn. degree for grad approx (losing 1 degree wrt to uh polyn
    space Vh (omega, grad_approx, "vector");     // Space for the orientation vector
    space Th (omega, grad_approx, "tensor");     // Space for the stress tensor (Can I use this space for stress, strain tensor and elasticity tensor ? May be not for elasticity tensor that should be a 3x3x3x3 tensor)
    space Sh (omega, grad_approx);     		 // Space for scalar fields
    size_t d = omega.dimension();		 // Finds automatically the dimension of the domain omega and calls it d (should be 3 here)
	
    //Set Input/output directory and files names------------------------------------ 
    string output_dir   = (argc > 3) ? argv[3] : "";
    string test_file    = (argc > 4) ? output_dir + argv[4] : "test";

    //Define orientation tensor M 
    field M(Th, 0.0);  //.... faire le cross-product
    //compute M=cxc Mij=ci.cj . I didn't find this in Notations ?
    M[0,0] = 0; //interpolate(Sh, orient[0]*orient[0]);
    M[0,1] = 1; //interpolate(Sh, orient[0]*orient[1]);
    M[0,2] = 2; //interpolate(Sh, orient[0]*orient[2]);

    M[1,1] = 3; //interpolate(Sh, orient[1]*orient[1]);
    M[1,0] = 4; //interpolate(Sh, orient[1]*orient[0]);
    M[1,2] = 5; //interpolate(Sh, orient[1]*orient[2]);

    M[2,2] = 6; //interpolate(Sh, orient[2]*orient[2]);
    M[2,1] = 7; //interpolate(Sh, orient[2]*orient[1]);
    M[2,0] = 8; //interpolate(Sh, orient[2]*orient[0]);

//Outputs:
dout << catchmark("M") << M;
}