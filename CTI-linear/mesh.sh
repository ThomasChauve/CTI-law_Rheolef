#!/bin/bash -x

gmsh -3 twograins_mesh_3d.mshcad -format msh2 -o twograins_mesh_3d.msh
msh2geo twograins_mesh_3d.msh > new_twograins_mesh_3d.geo
# geo new_twograins_mesh_3d.geo
