// I am writting this file using the exemple 2.1 from Pierre documentation and eshelby exemple from Vero
#include "rheolef.h"
#include <iostream>
#include <valarray>
#include <string>
#include <stdlib.h>
using namespace rheolef;
using namespace std;
#include "BCs.icc" // Is this a file to defined boundary conditions

//Define x,y coordinates functions
  Float X (const point& x) {
  return x[0];
  }

  Float Y (const point& x) {
  return x[1];
  }

  Float Z (const point& x) {
  return x[2];
  }

  Float Cin (const point& x) { //Generateur de nb aleatoire
  random_device rd;
  mt19937 gen(rd());
  uniform_real_distribution<> dis(1,2);
  return dis(gen);
  }

//Assign orientations per element
  Float orientation (Float y) {
    if (y > 0.5)   return 1.0 ;
    else return 0.0 ;
  }
   

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
	
    // Block the surface
    Xh[d-1].block("bottom");
    if (d == 3) Xh.block("left_bottom_front");
    else        Xh.block("left_bottom");

    //Set Input/output directory and files names------------------------------------ 
    string output_dir   = (argc > 3) ? argv[3] : "";
    string test_file    = (argc > 4) ? output_dir + argv[4] : "test";


    //Define non-dimensional constants
    Float pi = acos(-1.0);
    Float eta12= 1.0;
    Float alpha= 1.0;
    Float beta= 1.0;
    Float incomp = 10e3;
    // physical constant for anisotropy tensor in crystal reference frame

    //Define velocity, deformation rate and stress fields	  
    field uh(Xh, 0.0);
    field varep_h(Xh, 0.0);
    field sigma_h(Th, 0.0);

    //Define Cartesian coordinate fields (for correlation lenghts calculations)
    field x = interpolate (Sh, X);  //x position of an element (center)
    field y = interpolate (Sh, Y);  //y position of an element (center)
    field z = interpolate (Sh, Z);  //y position of an element (center)    
    
    //Define compressing force
    point f(0, 0, 0);
    f[d-1] = -1.0;

    //Define crystal orientation for the two domains
    field orient(Vh);
    //Set domain 1 : y < 0.5 ori1,  Domain 2 : y > 0.5 ori2
    orient[0] = interpolate(Sh, compose(orientation, y));
    orient[1] = 0.0;
    orient[2] = interpolate(Sh, abs(1-compose(orientation, y)));



    //Define orientation tensor M 
    field M(Th, 0.0);  //.... faire le cross-product
    //compute M=cxc Mij=ci.cj . I didn't find this in Notations ?
    M[0,0] = interpolate(Sh, orient[0]*orient[0]);
    M[0,1] = interpolate(Sh, orient[0]*orient[1]);
    M[0,2] = interpolate(Sh, orient[0]*orient[2]);

    M[1,1] = interpolate(Sh, orient[1]*orient[1]);
    M[1,0] = interpolate(Sh, orient[1]*orient[0]);
    M[1,2] = interpolate(Sh, orient[1]*orient[2]);

    M[2,2] = interpolate(Sh, orient[2]*orient[2]);
    M[2,1] = interpolate(Sh, orient[2]*orient[1]);
    M[2,0] = interpolate(Sh, orient[2]*orient[0]);


  //Define trial and test functions 
  trial u(Xh); test v(Xh);                              // For velocity calculation  
  trial lambda(Th); test tau(Th);                       // For stress calculation
  integrate_option iopt;                                // Quadrature type for stress calculation
  iopt.invert = true;
  //form inv_gh = integrate(ddot(lambda,tau), iopt);
  //form mt = integrate(ddot(lambda,tau));

  //Define identity matrix
  tensor I = tensor::eye(d);


  //Define quadrature type for summations and averaging through integrate function
  //quadrature_option_type qopt;
  //qopt.set_family(quadrature_option_type::gauss);
  //qopt.set_order(1);


  //Define boundary conditions
  uh[1]["bottom"] = 0.0;                //y-velocity of bottom bndy = 0
  uh["left_bottom_front"] = 0.0;               //velocity of bottom-left corner = 0
//--------------------------------------------------------------------------------------------
//Solving for the velocity field


  field lh        = integrate (omega["top"],dot(f, v));

  form  a         = integrate ( 2.0*eta12*ddot(D(u), D(v))
			     //+  2.0*eta12*tr(M*D(u))*(2.0*(alpha - beta)*ddot(M,D(v)) - 2.0/3.0*(alpha-1.0)*div(v)) 
			     //+  2.0*eta12*(beta-1.0)*ddot(M*D(u) + D(u)*M, D(v)) 
           + incomp*div(u)*div(v)
           );

  solver_option sopt;
  sopt.iterative=false;

  //solver sa (a.uu(),sopt);
  solver sa (a.uu());
  uh.set_u()      = sa.solve (lh.u() - a.ub()*uh.b());
  varep_h = interpolate(Th, D(uh));	


//Outputs:
  dout << catchmark("u") << uh;
  //dout << catchmark("uh") << varep_h;
}
