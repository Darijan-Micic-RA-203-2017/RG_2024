#include "vertices.hpp"

// REFERENCE: https://cplusplus.com/forum/general/131319/#msg707907
// REFERENCE: https://stackoverflow.com/questions/56735173/variable-already-defined-in-obj-what-is-going-on-here

/* Vertices in the normalized device coordinates system (from -1.0F to 1.0F). Since the vertex by itself doesn't have a
surface (the vertex is simply a single point in space), its surrounding vertices need to be used to figure out the
surface of the vertex in question.
A neat trick can be used to calculate the normal vectors for all the cube's vertices by using the cross product.
However, the cube is a simple shape, so the normal vectors can simply be manually added to the vertex data. 36 vertices
are needed to render the cube (6 sides * 2 triangles per side * 3 vertices for each triangle).
*/

float verticesOfGroceries[1152U] = {
	// position           // normal vector     // texture coordinates
	// in the freezing chamber
	-0.05F, -0.2F,  0.3F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, // left fish sticks package
	-0.45F, -0.2F,  0.3F,  0.0F,  0.0F, -1.0F, 1.0F, 0.0F, // - back side
	-0.05F,  0.2F,  0.3F,  0.0F,  0.0F, -1.0F, 0.0F, 1.0F, 
	-0.05F,  0.2F,  0.3F,  0.0F,  0.0F, -1.0F, 0.0F, 1.0F, 
	-0.45F, -0.2F,  0.3F,  0.0F,  0.0F, -1.0F, 1.0F, 0.0F, 
	-0.45F,  0.2F,  0.3F,  0.0F,  0.0F, -1.0F, 1.0F, 1.0F, 
	-0.45F, -0.2F,  0.6F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, // left fish sticks package
	-0.05F, -0.2F,  0.6F,  0.0F,  0.0F,  1.0F, 1.0F, 0.0F, // - front side
	-0.45F,  0.2F,  0.6F,  0.0F,  0.0F,  1.0F, 0.0F, 1.0F, 
	-0.45F,  0.2F,  0.6F,  0.0F,  0.0F,  1.0F, 0.0F, 1.0F, 
	-0.05F, -0.2F,  0.6F,  0.0F,  0.0F,  1.0F, 1.0F, 0.0F, 
	-0.05F,  0.2F,  0.6F,  0.0F,  0.0F,  1.0F, 1.0F, 1.0F, 
	-0.45F, -0.2F,  0.3F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, // left fish sticks package
	-0.45F, -0.2F,  0.6F, -1.0F,  0.0F,  0.0F, 1.0F, 0.0F, // - left side
	-0.45F,  0.2F,  0.3F, -1.0F,  0.0F,  0.0F, 0.0F, 1.0F, 
	-0.45F,  0.2F,  0.3F, -1.0F,  0.0F,  0.0F, 0.0F, 1.0F, 
	-0.45F, -0.2F,  0.6F, -1.0F,  0.0F,  0.0F, 1.0F, 0.0F, 
	-0.45F,  0.2F,  0.6F, -1.0F,  0.0F,  0.0F, 1.0F, 1.0F, 
	-0.05F, -0.2F,  0.6F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, // left fish sticks package
	-0.05F, -0.2F,  0.3F,  1.0F,  0.0F,  0.0F, 1.0F, 0.0F, // - right side
	-0.05F,  0.2F,  0.6F,  1.0F,  0.0F,  0.0F, 0.0F, 1.0F, 
	-0.05F,  0.2F,  0.6F,  1.0F,  0.0F,  0.0F, 0.0F, 1.0F, 
	-0.05F, -0.2F,  0.3F,  1.0F,  0.0F,  0.0F, 1.0F, 0.0F, 
	-0.05F,  0.2F,  0.3F,  1.0F,  0.0F,  0.0F, 1.0F, 1.0F, 
	-0.45F, -0.2F,  0.3F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, // left fish sticks package
	-0.05F, -0.2F,  0.3F,  0.0F, -1.0F,  0.0F, 1.0F, 0.0F, // - bottom side
	-0.45F, -0.2F,  0.6F,  0.0F, -1.0F,  0.0F, 0.0F, 1.0F, 
	-0.45F, -0.2F,  0.6F,  0.0F, -1.0F,  0.0F, 0.0F, 1.0F, 
	-0.05F, -0.2F,  0.3F,  0.0F, -1.0F,  0.0F, 1.0F, 0.0F, 
	-0.05F, -0.2F,  0.6F,  0.0F, -1.0F,  0.0F, 1.0F, 1.0F, 
	-0.45F,  0.2F,  0.6F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, // left fish sticks package
	-0.05F,  0.2F,  0.6F,  0.0F,  1.0F,  0.0F, 1.0F, 0.0F, // - top side
	-0.45F,  0.2F,  0.3F,  0.0F,  1.0F,  0.0F, 0.0F, 1.0F, 
	-0.45F,  0.2F,  0.3F,  0.0F,  1.0F,  0.0F, 0.0F, 1.0F, 
	-0.05F,  0.2F,  0.6F,  0.0F,  1.0F,  0.0F, 1.0F, 0.0F, 
	-0.05F,  0.2F,  0.3F,  0.0F,  1.0F,  0.0F, 1.0F, 1.0F, 
	 0.45F, -0.2F,  0.3F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, // right fish sticks package
	 0.05F, -0.2F,  0.3F,  0.0F,  0.0F, -1.0F, 1.0F, 0.0F, // - back side
	 0.45F,  0.2F,  0.3F,  0.0F,  0.0F, -1.0F, 0.0F, 1.0F, 
	 0.45F,  0.2F,  0.3F,  0.0F,  0.0F, -1.0F, 0.0F, 1.0F, 
	 0.05F, -0.2F,  0.3F,  0.0F,  0.0F, -1.0F, 1.0F, 0.0F, 
	 0.05F,  0.2F,  0.3F,  0.0F,  0.0F, -1.0F, 1.0F, 1.0F, 
	 0.05F, -0.2F,  0.6F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, // right fish sticks package
	 0.45F, -0.2F,  0.6F,  0.0F,  0.0F,  1.0F, 1.0F, 0.0F, // - front side
	 0.05F,  0.2F,  0.6F,  0.0F,  0.0F,  1.0F, 0.0F, 1.0F, 
	 0.05F,  0.2F,  0.6F,  0.0F,  0.0F,  1.0F, 0.0F, 1.0F, 
	 0.45F, -0.2F,  0.6F,  0.0F,  0.0F,  1.0F, 1.0F, 0.0F, 
	 0.45F,  0.2F,  0.6F,  0.0F,  0.0F,  1.0F, 1.0F, 1.0F, 
	 0.05F, -0.2F,  0.3F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, // right fish sticks package
	 0.05F, -0.2F,  0.6F, -1.0F,  0.0F,  0.0F, 1.0F, 0.0F, // - left side
	 0.05F,  0.2F,  0.3F, -1.0F,  0.0F,  0.0F, 0.0F, 1.0F, 
	 0.05F,  0.2F,  0.3F, -1.0F,  0.0F,  0.0F, 0.0F, 1.0F, 
	 0.05F, -0.2F,  0.6F, -1.0F,  0.0F,  0.0F, 1.0F, 0.0F, 
	 0.05F,  0.2F,  0.6F, -1.0F,  0.0F,  0.0F, 1.0F, 1.0F, 
	 0.45F, -0.2F,  0.6F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, // right fish sticks package
	 0.45F, -0.2F,  0.3F,  1.0F,  0.0F,  0.0F, 1.0F, 0.0F, // - right side
	 0.45F,  0.2F,  0.6F,  1.0F,  0.0F,  0.0F, 0.0F, 1.0F, 
	 0.45F,  0.2F,  0.6F,  1.0F,  0.0F,  0.0F, 0.0F, 1.0F, 
	 0.45F, -0.2F,  0.3F,  1.0F,  0.0F,  0.0F, 1.0F, 0.0F, 
	 0.45F,  0.2F,  0.3F,  1.0F,  0.0F,  0.0F, 1.0F, 1.0F, 
	 0.05F, -0.2F,  0.3F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, // right fish sticks package
	 0.45F, -0.2F,  0.3F,  0.0F, -1.0F,  0.0F, 1.0F, 0.0F, // - bottom side
	 0.05F, -0.2F,  0.6F,  0.0F, -1.0F,  0.0F, 0.0F, 1.0F, 
	 0.05F, -0.2F,  0.6F,  0.0F, -1.0F,  0.0F, 0.0F, 1.0F, 
	 0.45F, -0.2F,  0.3F,  0.0F, -1.0F,  0.0F, 1.0F, 0.0F, 
	 0.45F, -0.2F,  0.6F,  0.0F, -1.0F,  0.0F, 1.0F, 1.0F, 
	 0.05F,  0.2F,  0.6F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, // right fish sticks package
	 0.45F,  0.2F,  0.6F,  0.0F,  1.0F,  0.0F, 1.0F, 0.0F, // - top side
	 0.05F,  0.2F,  0.3F,  0.0F,  1.0F,  0.0F, 0.0F, 1.0F, 
	 0.05F,  0.2F,  0.3F,  0.0F,  1.0F,  0.0F, 0.0F, 1.0F, 
	 0.45F,  0.2F,  0.6F,  0.0F,  1.0F,  0.0F, 1.0F, 0.0F, 
	 0.45F,  0.2F,  0.3F,  0.0F,  1.0F,  0.0F, 1.0F, 1.0F, 
	 // in the refrigerating chamber
	-0.05F, -0.7F,  0.3F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, // left milk carton box
	-0.45F, -0.7F,  0.3F,  0.0F,  0.0F, -1.0F, 1.0F, 0.0F, // - back side
	-0.05F, -0.3F,  0.3F,  0.0F,  0.0F, -1.0F, 0.0F, 1.0F, 
	-0.05F, -0.3F,  0.3F,  0.0F,  0.0F, -1.0F, 0.0F, 1.0F, 
	-0.45F, -0.7F,  0.3F,  0.0F,  0.0F, -1.0F, 1.0F, 0.0F, 
	-0.45F, -0.3F,  0.3F,  0.0F,  0.0F, -1.0F, 1.0F, 1.0F, 
	-0.45F, -0.7F,  0.6F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, // left milk carton box
	-0.05F, -0.7F,  0.6F,  0.0F,  0.0F,  1.0F, 1.0F, 0.0F, // - front side
	-0.45F, -0.3F,  0.6F,  0.0F,  0.0F,  1.0F, 0.0F, 1.0F, 
	-0.45F, -0.3F,  0.6F,  0.0F,  0.0F,  1.0F, 0.0F, 1.0F, 
	-0.05F, -0.7F,  0.6F,  0.0F,  0.0F,  1.0F, 1.0F, 0.0F, 
	-0.05F, -0.3F,  0.6F,  0.0F,  0.0F,  1.0F, 1.0F, 1.0F, 
	-0.45F, -0.7F,  0.3F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, // left milk carton box
	-0.45F, -0.7F,  0.6F, -1.0F,  0.0F,  0.0F, 1.0F, 0.0F, // - left side
	-0.45F, -0.3F,  0.3F, -1.0F,  0.0F,  0.0F, 0.0F, 1.0F, 
	-0.45F, -0.3F,  0.3F, -1.0F,  0.0F,  0.0F, 0.0F, 1.0F, 
	-0.45F, -0.7F,  0.6F, -1.0F,  0.0F,  0.0F, 1.0F, 0.0F, 
	-0.45F, -0.3F,  0.6F, -1.0F,  0.0F,  0.0F, 1.0F, 1.0F, 
	-0.05F, -0.7F,  0.6F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, // left milk carton box
	-0.05F, -0.7F,  0.3F,  1.0F,  0.0F,  0.0F, 1.0F, 0.0F, // - right side
	-0.05F, -0.3F,  0.6F,  1.0F,  0.0F,  0.0F, 0.0F, 1.0F, 
	-0.05F, -0.3F,  0.6F,  1.0F,  0.0F,  0.0F, 0.0F, 1.0F, 
	-0.05F, -0.7F,  0.3F,  1.0F,  0.0F,  0.0F, 1.0F, 0.0F, 
	-0.05F, -0.3F,  0.3F,  1.0F,  0.0F,  0.0F, 1.0F, 1.0F, 
	-0.45F, -0.7F,  0.3F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, // left milk carton box
	-0.05F, -0.7F,  0.3F,  0.0F, -1.0F,  0.0F, 1.0F, 0.0F, // - bottom side
	-0.45F, -0.7F,  0.6F,  0.0F, -1.0F,  0.0F, 0.0F, 1.0F, 
	-0.45F, -0.7F,  0.6F,  0.0F, -1.0F,  0.0F, 0.0F, 1.0F, 
	-0.05F, -0.7F,  0.3F,  0.0F, -1.0F,  0.0F, 1.0F, 0.0F, 
	-0.05F, -0.7F,  0.6F,  0.0F, -1.0F,  0.0F, 1.0F, 1.0F, 
	-0.45F, -0.3F,  0.6F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, // left milk carton box
	-0.05F, -0.3F,  0.6F,  0.0F,  1.0F,  0.0F, 1.0F, 0.0F, // - top side
	-0.45F, -0.3F,  0.3F,  0.0F,  1.0F,  0.0F, 0.0F, 1.0F, 
	-0.45F, -0.3F,  0.3F,  0.0F,  1.0F,  0.0F, 0.0F, 1.0F, 
	-0.05F, -0.3F,  0.6F,  0.0F,  1.0F,  0.0F, 1.0F, 0.0F, 
	-0.05F, -0.3F,  0.3F,  0.0F,  1.0F,  0.0F, 1.0F, 1.0F, 
	 0.45F, -0.7F,  0.3F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, // right milk carton box
	 0.05F, -0.7F,  0.3F,  0.0F,  0.0F, -1.0F, 1.0F, 0.0F, // - back side
	 0.45F, -0.3F,  0.3F,  0.0F,  0.0F, -1.0F, 0.0F, 1.0F, 
	 0.45F, -0.3F,  0.3F,  0.0F,  0.0F, -1.0F, 0.0F, 1.0F, 
	 0.05F, -0.7F,  0.3F,  0.0F,  0.0F, -1.0F, 1.0F, 0.0F, 
	 0.05F, -0.3F,  0.3F,  0.0F,  0.0F, -1.0F, 1.0F, 1.0F, 
	 0.05F, -0.7F,  0.6F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, // right milk carton box
	 0.45F, -0.7F,  0.6F,  0.0F,  0.0F,  1.0F, 1.0F, 0.0F, // - front side
	 0.05F, -0.3F,  0.6F,  0.0F,  0.0F,  1.0F, 0.0F, 1.0F, 
	 0.05F, -0.3F,  0.6F,  0.0F,  0.0F,  1.0F, 0.0F, 1.0F, 
	 0.45F, -0.7F,  0.6F,  0.0F,  0.0F,  1.0F, 1.0F, 0.0F, 
	 0.45F, -0.3F,  0.6F,  0.0F,  0.0F,  1.0F, 1.0F, 1.0F, 
	 0.05F, -0.7F,  0.3F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, // right milk carton box
	 0.05F, -0.7F,  0.6F, -1.0F,  0.0F,  0.0F, 1.0F, 0.0F, // - left side
	 0.05F, -0.3F,  0.3F, -1.0F,  0.0F,  0.0F, 0.0F, 1.0F, 
	 0.05F, -0.3F,  0.3F, -1.0F,  0.0F,  0.0F, 0.0F, 1.0F, 
	 0.05F, -0.7F,  0.6F, -1.0F,  0.0F,  0.0F, 1.0F, 0.0F, 
	 0.05F, -0.3F,  0.6F, -1.0F,  0.0F,  0.0F, 1.0F, 1.0F, 
	 0.45F, -0.7F,  0.6F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, // right milk carton box
	 0.45F, -0.7F,  0.3F,  1.0F,  0.0F,  0.0F, 1.0F, 0.0F, // - right side
	 0.45F, -0.3F,  0.6F,  1.0F,  0.0F,  0.0F, 0.0F, 1.0F, 
	 0.45F, -0.3F,  0.6F,  1.0F,  0.0F,  0.0F, 0.0F, 1.0F, 
	 0.45F, -0.7F,  0.3F,  1.0F,  0.0F,  0.0F, 1.0F, 0.0F, 
	 0.45F, -0.3F,  0.3F,  1.0F,  0.0F,  0.0F, 1.0F, 1.0F, 
	 0.05F, -0.7F,  0.3F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, // right milk carton box
	 0.45F, -0.7F,  0.3F,  0.0F, -1.0F,  0.0F, 1.0F, 0.0F, // - bottom side
	 0.05F, -0.7F,  0.6F,  0.0F, -1.0F,  0.0F, 0.0F, 1.0F, 
	 0.05F, -0.7F,  0.6F,  0.0F, -1.0F,  0.0F, 0.0F, 1.0F, 
	 0.45F, -0.7F,  0.3F,  0.0F, -1.0F,  0.0F, 1.0F, 0.0F, 
	 0.45F, -0.7F,  0.6F,  0.0F, -1.0F,  0.0F, 1.0F, 1.0F, 
	 0.05F, -0.3F,  0.6F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, // right milk carton box
	 0.45F, -0.3F,  0.6F,  0.0F,  1.0F,  0.0F, 1.0F, 0.0F, // - top side
	 0.05F, -0.3F,  0.3F,  0.0F,  1.0F,  0.0F, 0.0F, 1.0F, 
	 0.05F, -0.3F,  0.3F,  0.0F,  1.0F,  0.0F, 0.0F, 1.0F, 
	 0.45F, -0.3F,  0.6F,  0.0F,  1.0F,  0.0F, 1.0F, 0.0F, 
	 0.45F, -0.3F,  0.3F,  0.0F,  1.0F,  0.0F, 1.0F, 1.0F
};

float verticesOfChambers[3600U] = {
	// position              // normal vector     // color
	  0.7F, -0.24F, -0.825F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, 1.0F, 0.25F, // see-through, blue-tinted freezing chamber plastic
	 -0.7F, -0.24F, -0.825F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, 1.0F, 0.25F, // - back side (back side)
	  0.7F,  0.24F, -0.825F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F,  0.24F, -0.825F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.24F, -0.825F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F,  0.24F, -0.825F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.24F, -0.775F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, 1.0F, 0.25F, // see-through, blue-tinted freezing chamber plastic
	  0.7F, -0.24F, -0.775F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, 1.0F, 0.25F, // - front side (back side)
	 -0.7F,  0.24F, -0.775F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F,  0.24F, -0.775F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.24F, -0.775F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F,  0.24F, -0.775F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.24F, -0.825F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // see-through, blue-tinted freezing chamber plastic
	 -0.7F, -0.24F, -0.775F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // - left side (back side)
	 -0.7F,  0.24F, -0.825F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F,  0.24F, -0.825F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.24F, -0.775F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F,  0.24F, -0.775F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.24F, -0.775F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // see-through, blue-tinted freezing chamber plastic
	  0.7F, -0.24F, -0.825F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // - right side (back side)
	  0.7F,  0.24F, -0.775F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F,  0.24F, -0.775F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.24F, -0.825F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F,  0.24F, -0.825F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.24F, -0.825F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // see-through, blue-tinted freezing chamber plastic
	  0.7F, -0.24F, -0.825F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // - bottom side (back side)
	 -0.7F, -0.24F, -0.775F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.24F, -0.775F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.24F, -0.825F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.24F, -0.775F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F,  0.24F, -0.775F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // see-through, blue-tinted freezing chamber plastic
	  0.7F,  0.24F, -0.775F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // - top side (back side)
	 -0.7F,  0.24F, -0.825F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F,  0.24F, -0.825F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F,  0.24F, -0.775F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F,  0.24F, -0.825F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.24F,  0.775F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, 1.0F, 0.25F, // see-through, blue-tinted freezing chamber plastic
	 -0.7F, -0.24F,  0.775F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, 1.0F, 0.25F, // - back side (front side)
	  0.7F,  0.24F,  0.775F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F,  0.24F,  0.775F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.24F,  0.775F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F,  0.24F,  0.775F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.24F,  0.825F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, 1.0F, 0.25F, // see-through, blue-tinted freezing chamber plastic
	  0.7F, -0.24F,  0.825F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, 1.0F, 0.25F, // - front side (front side)
	 -0.7F,  0.24F,  0.825F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F,  0.24F,  0.825F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.24F,  0.825F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F,  0.24F,  0.825F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.24F,  0.775F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // see-through, blue-tinted freezing chamber plastic
	 -0.7F, -0.24F,  0.825F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // - left side (front side)
	 -0.7F,  0.24F,  0.775F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F,  0.24F,  0.775F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.24F,  0.825F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F,  0.24F,  0.825F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.24F,  0.825F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // see-through, blue-tinted freezing chamber plastic
	  0.7F, -0.24F,  0.775F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // - right side (front side)
	  0.7F,  0.24F,  0.825F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F,  0.24F,  0.825F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.24F,  0.775F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F,  0.24F,  0.775F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.24F,  0.775F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // see-through, blue-tinted freezing chamber plastic
	  0.7F, -0.24F,  0.775F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // - bottom side (front side)
	 -0.7F, -0.24F,  0.825F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.24F,  0.825F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.24F,  0.775F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.24F,  0.825F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F,  0.24F,  0.825F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // see-through, blue-tinted freezing chamber plastic
	  0.7F,  0.24F,  0.825F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // - top side (front side)
	 -0.7F,  0.24F,  0.775F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F,  0.24F,  0.775F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F,  0.24F,  0.825F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F,  0.24F,  0.775F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.22F, -0.775F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, 1.0F, 0.25F, // see-through, blue-tinted freezing chamber plastic
	 0.65F, -0.22F, -0.775F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, 1.0F, 0.25F, // - back side (left side)
	  0.7F,  0.22F, -0.775F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F,  0.22F, -0.775F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 0.65F, -0.22F, -0.775F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 0.65F,  0.22F, -0.775F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 0.65F, -0.22F,  0.775F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, 1.0F, 0.25F, // see-through, blue-tinted freezing chamber plastic
	  0.7F, -0.22F,  0.775F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, 1.0F, 0.25F, // - front side (left side)
	 0.65F,  0.22F,  0.775F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 0.65F,  0.22F,  0.775F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.22F,  0.775F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F,  0.22F,  0.775F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.22F,  0.775F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // see-through, blue-tinted freezing chamber plastic
	  0.7F, -0.22F, -0.775F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // - left side (left side)
	  0.7F,  0.22F,  0.775F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F,  0.22F,  0.775F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.22F, -0.775F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F,  0.22F, -0.775F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 0.65F, -0.22F, -0.775F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // see-through, blue-tinted freezing chamber plastic
	 0.65F, -0.22F,  0.775F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // - right side (left side)
	 0.65F,  0.22F, -0.775F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 0.65F,  0.22F, -0.775F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 0.65F, -0.22F,  0.775F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 0.65F,  0.22F,  0.775F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 0.65F, -0.22F, -0.775F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // see-through, blue-tinted freezing chamber plastic
	  0.7F, -0.22F, -0.775F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // - bottom side (left side)
	 0.65F, -0.22F,  0.775F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 0.65F, -0.22F,  0.775F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.22F, -0.775F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.22F,  0.775F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 0.65F,  0.22F,  0.775F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // see-through, blue-tinted freezing chamber plastic
	  0.7F,  0.22F,  0.775F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // - top side (left side)
	 0.65F,  0.22F, -0.775F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 0.65F,  0.22F, -0.775F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F,  0.22F,  0.775F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F,  0.22F, -0.775F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	-0.65F, -0.22F, -0.775F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, 1.0F, 0.25F, // see-through, blue-tinted freezing chamber plastic
	 -0.7F, -0.22F, -0.775F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, 1.0F, 0.25F, // - back side (right side)
	-0.65F,  0.22F, -0.775F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	-0.65F,  0.22F, -0.775F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.22F, -0.775F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F,  0.22F, -0.775F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.22F,  0.775F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, 1.0F, 0.25F, // see-through, blue-tinted freezing chamber plastic
	-0.65F, -0.22F,  0.775F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, 1.0F, 0.25F, // - front side (right side)
	 -0.7F,  0.22F,  0.775F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F,  0.22F,  0.775F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	-0.65F, -0.22F,  0.775F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	-0.65F,  0.22F,  0.775F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	-0.65F, -0.22F,  0.775F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // see-through, blue-tinted freezing chamber plastic
	-0.65F, -0.22F, -0.775F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // - left side (right side)
	-0.65F,  0.22F,  0.775F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	-0.65F,  0.22F,  0.775F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	-0.65F, -0.22F, -0.775F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	-0.65F,  0.22F, -0.775F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.22F, -0.775F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // see-through, blue-tinted freezing chamber plastic
	 -0.7F, -0.22F,  0.775F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // - right side (right side)
	 -0.7F,  0.22F, -0.775F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F,  0.22F, -0.775F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.22F,  0.775F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F,  0.22F,  0.775F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.22F, -0.775F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // see-through, blue-tinted freezing chamber plastic
	-0.65F, -0.22F, -0.775F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // - bottom side (right side)
	 -0.7F, -0.22F,  0.775F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.22F,  0.775F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	-0.65F, -0.22F, -0.775F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	-0.65F, -0.22F,  0.775F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F,  0.22F,  0.775F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // see-through, blue-tinted freezing chamber plastic
	-0.65F,  0.22F,  0.775F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // - top side (right side)
	 -0.7F,  0.22F, -0.775F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F,  0.22F, -0.775F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	-0.65F,  0.22F,  0.775F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	-0.65F,  0.22F, -0.775F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.24F, -0.775F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, 1.0F, 0.25F, // see-through, blue-tinted freezing chamber plastic
	 -0.7F, -0.24F, -0.775F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, 1.0F, 0.25F, // - back side (bottom side)
	  0.7F, -0.22F, -0.775F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.22F, -0.775F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.24F, -0.775F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.22F, -0.775F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.24F,  0.775F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, 1.0F, 0.25F, // see-through, blue-tinted freezing chamber plastic
	  0.7F, -0.24F,  0.775F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, 1.0F, 0.25F, // - front side (bottom side)
	 -0.7F, -0.22F,  0.775F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.22F,  0.775F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.24F,  0.775F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.22F,  0.775F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.24F,  0.775F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // see-through, blue-tinted freezing chamber plastic
	  0.7F, -0.24F, -0.775F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // - left side (bottom side)
	  0.7F, -0.22F,  0.775F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.22F,  0.775F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.24F, -0.775F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.22F, -0.775F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.24F, -0.775F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // see-through, blue-tinted freezing chamber plastic
	 -0.7F, -0.24F,  0.775F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // - right side (bottom side)
	 -0.7F, -0.22F, -0.775F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.22F, -0.775F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.24F,  0.775F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.22F,  0.775F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.24F, -0.775F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // see-through, blue-tinted freezing chamber plastic
	  0.7F, -0.24F, -0.775F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // - bottom side (bottom side)
	 -0.7F, -0.24F,  0.775F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.24F,  0.775F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.24F, -0.775F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.24F,  0.775F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.22F,  0.775F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // see-through, blue-tinted freezing chamber plastic
	  0.7F, -0.22F,  0.775F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // - top side (bottom side)
	 -0.7F, -0.22F, -0.775F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.22F, -0.775F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.22F,  0.775F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.22F, -0.775F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.74F, -0.825F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, 1.0F, 0.25F, // see-through, blue-tinted refrigerating chamber plastic
	 -0.7F, -0.74F, -0.825F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, 1.0F, 0.25F, // - back side (back side)
	  0.7F, -0.26F, -0.825F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.26F, -0.825F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.74F, -0.825F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.26F, -0.825F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.74F, -0.775F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, 1.0F, 0.25F, // see-through, blue-tinted refrigerating chamber plastic
	  0.7F, -0.74F, -0.775F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, 1.0F, 0.25F, // - front side (back side)
	 -0.7F, -0.26F, -0.775F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.26F, -0.775F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.74F, -0.775F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.26F, -0.775F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.74F, -0.825F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // see-through, blue-tinted refrigerating chamber plastic
	 -0.7F, -0.74F, -0.775F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // - left side (back side)
	 -0.7F, -0.26F, -0.825F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.26F, -0.825F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.74F, -0.775F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.26F, -0.775F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.74F, -0.775F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // see-through, blue-tinted refrigerating chamber plastic
	  0.7F, -0.74F, -0.825F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // - right side (back side)
	  0.7F, -0.26F, -0.775F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.26F, -0.775F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.74F, -0.825F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.26F, -0.825F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.74F, -0.825F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // see-through, blue-tinted refrigerating chamber plastic
	  0.7F, -0.74F, -0.825F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // - bottom side (back side)
	 -0.7F, -0.74F, -0.775F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.74F, -0.775F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.74F, -0.825F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.74F, -0.775F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.26F, -0.775F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // see-through, blue-tinted refrigerating chamber plastic
	  0.7F, -0.26F, -0.775F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // - top side (back side)
	 -0.7F, -0.26F, -0.825F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.26F, -0.825F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.26F, -0.775F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.26F, -0.825F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.74F,  0.775F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, 1.0F, 0.25F, // see-through, blue-tinted refrigerating chamber plastic
	 -0.7F, -0.74F,  0.775F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, 1.0F, 0.25F, // - back side (front side)
	  0.7F, -0.26F,  0.775F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.26F,  0.775F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.74F,  0.775F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.26F,  0.775F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.74F,  0.825F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, 1.0F, 0.25F, // see-through, blue-tinted refrigerating chamber plastic
	  0.7F, -0.74F,  0.825F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, 1.0F, 0.25F, // - front side (front side)
	 -0.7F, -0.26F,  0.825F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.26F,  0.825F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.74F,  0.825F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.26F,  0.825F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.74F,  0.775F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // see-through, blue-tinted refrigerating chamber plastic
	 -0.7F, -0.74F,  0.825F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // - left side (front side)
	 -0.7F, -0.26F,  0.775F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.26F,  0.775F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.74F,  0.825F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.26F,  0.825F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.74F,  0.825F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // see-through, blue-tinted refrigerating chamber plastic
	  0.7F, -0.74F,  0.775F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // - right side (front side)
	  0.7F, -0.26F,  0.825F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.26F,  0.825F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.74F,  0.775F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.26F,  0.775F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.74F,  0.775F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // see-through, blue-tinted refrigerating chamber plastic
	  0.7F, -0.74F,  0.775F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // - bottom side (front side)
	 -0.7F, -0.74F,  0.825F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.74F,  0.825F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.74F,  0.775F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.74F,  0.825F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.26F,  0.825F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // see-through, blue-tinted refrigerating chamber plastic
	  0.7F, -0.26F,  0.825F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // - top side (front side)
	 -0.7F, -0.26F,  0.775F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.26F,  0.775F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.26F,  0.825F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.26F,  0.775F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.72F, -0.775F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, 1.0F, 0.25F, // see-through, blue-tinted refrigerating chamber plastic
	 0.65F, -0.72F, -0.775F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, 1.0F, 0.25F, // - back side (left side)
	  0.7F, -0.28F, -0.775F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.28F, -0.775F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 0.65F, -0.72F, -0.775F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 0.65F, -0.28F, -0.775F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 0.65F, -0.72F,  0.775F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, 1.0F, 0.25F, // see-through, blue-tinted refrigerating chamber plastic
	  0.7F, -0.72F,  0.775F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, 1.0F, 0.25F, // - front side (left side)
	 0.65F, -0.28F,  0.775F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 0.65F, -0.28F,  0.775F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.72F,  0.775F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.28F,  0.775F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.72F,  0.775F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // see-through, blue-tinted refrigerating chamber plastic
	  0.7F, -0.72F, -0.775F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // - left side (left side)
	  0.7F, -0.28F,  0.775F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.28F,  0.775F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.72F, -0.775F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.28F, -0.775F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 0.65F, -0.72F, -0.775F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // see-through, blue-tinted refrigerating chamber plastic
	 0.65F, -0.72F,  0.775F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // - right side (left side)
	 0.65F, -0.28F, -0.775F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 0.65F, -0.28F, -0.775F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 0.65F, -0.72F,  0.775F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 0.65F, -0.28F,  0.775F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 0.65F, -0.72F, -0.775F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // see-through, blue-tinted refrigerating chamber plastic
	  0.7F, -0.72F, -0.775F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // - bottom side (left side)
	 0.65F, -0.72F,  0.775F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 0.65F, -0.72F,  0.775F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.72F, -0.775F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.72F,  0.775F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 0.65F, -0.28F,  0.775F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // see-through, blue-tinted refrigerating chamber plastic
	  0.7F, -0.28F,  0.775F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // - top side (left side)
	 0.65F, -0.28F, -0.775F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 0.65F, -0.28F, -0.775F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.28F,  0.775F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.28F, -0.775F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	-0.65F, -0.72F, -0.775F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, 1.0F, 0.25F, // see-through, blue-tinted refrigerating chamber plastic
	 -0.7F, -0.72F, -0.775F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, 1.0F, 0.25F, // - back side (right side)
	-0.65F, -0.28F, -0.775F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	-0.65F, -0.28F, -0.775F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.72F, -0.775F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.28F, -0.775F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.72F,  0.775F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, 1.0F, 0.25F, // see-through, blue-tinted refrigerating chamber plastic
	-0.65F, -0.72F,  0.775F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, 1.0F, 0.25F, // - front side (right side)
	 -0.7F, -0.28F,  0.775F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.28F,  0.775F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	-0.65F, -0.72F,  0.775F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	-0.65F, -0.28F,  0.775F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	-0.65F, -0.72F,  0.775F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // see-through, blue-tinted refrigerating chamber plastic
	-0.65F, -0.72F, -0.775F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // - left side (right side)
	-0.65F, -0.28F,  0.775F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	-0.65F, -0.28F,  0.775F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	-0.65F, -0.72F, -0.775F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	-0.65F, -0.28F, -0.775F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.72F, -0.775F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // see-through, blue-tinted refrigerating chamber plastic
	 -0.7F, -0.72F,  0.775F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // - right side (right side)
	 -0.7F, -0.28F, -0.775F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.28F, -0.775F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.72F,  0.775F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.28F,  0.775F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.72F, -0.775F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // see-through, blue-tinted refrigerating chamber plastic
	-0.65F, -0.72F, -0.775F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // - bottom side (right side)
	 -0.7F, -0.72F,  0.775F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.72F,  0.775F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	-0.65F, -0.72F, -0.775F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	-0.65F, -0.72F,  0.775F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.28F,  0.775F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // see-through, blue-tinted refrigerating chamber plastic
	-0.65F, -0.28F,  0.775F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // - top side (right side)
	 -0.7F, -0.28F, -0.775F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.28F, -0.775F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	-0.65F, -0.28F,  0.775F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	-0.65F, -0.28F, -0.775F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.74F, -0.775F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, 1.0F, 0.25F, // see-through, blue-tinted refrigerating chamber plastic
	 -0.7F, -0.74F, -0.775F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, 1.0F, 0.25F, // - back side (bottom side)
	  0.7F, -0.72F, -0.775F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.72F, -0.775F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.74F, -0.775F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.72F, -0.775F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.74F,  0.775F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, 1.0F, 0.25F, // see-through, blue-tinted refrigerating chamber plastic
	  0.7F, -0.74F,  0.775F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, 1.0F, 0.25F, // - front side (bottom side)
	 -0.7F, -0.72F,  0.775F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.72F,  0.775F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.74F,  0.775F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.72F,  0.775F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.74F,  0.775F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // see-through, blue-tinted refrigerating chamber plastic
	  0.7F, -0.74F, -0.775F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // - left side (bottom side)
	  0.7F, -0.72F,  0.775F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.72F,  0.775F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.74F, -0.775F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.72F, -0.775F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.74F, -0.775F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // see-through, blue-tinted refrigerating chamber plastic
	 -0.7F, -0.74F,  0.775F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // - right side (bottom side)
	 -0.7F, -0.72F, -0.775F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.72F, -0.775F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.74F,  0.775F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.72F,  0.775F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.74F, -0.775F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // see-through, blue-tinted refrigerating chamber plastic
	  0.7F, -0.74F, -0.775F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // - bottom side (bottom side)
	 -0.7F, -0.74F,  0.775F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.74F,  0.775F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.74F, -0.775F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.74F,  0.775F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.72F,  0.775F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // see-through, blue-tinted refrigerating chamber plastic
	  0.7F, -0.72F,  0.775F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // - top side (bottom side)
	 -0.7F, -0.72F, -0.775F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	 -0.7F, -0.72F, -0.775F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.72F,  0.775F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
	  0.7F, -0.72F, -0.775F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F
};

float verticesOfRefrigerator[1800U] = {
	// position                // normal vector     // color
	  -0.9F,   -0.9F,   -1.2F,  0.0F,  0.0F, -1.0F,  0.9F,  0.9F,  0.9F, 1.0F, // refrigerator (back side)
	   0.9F,   -0.9F,   -1.2F,  0.0F,  0.0F, -1.0F,  0.9F,  0.9F,  0.9F, 1.0F, // - back side
	  -0.9F,    0.9F,   -1.2F,  0.0F,  0.0F, -1.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	  -0.9F,    0.9F,   -1.2F,  0.0F,  0.0F, -1.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	   0.9F,   -0.9F,   -1.2F,  0.0F,  0.0F, -1.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	   0.9F,    0.9F,   -1.2F,  0.0F,  0.0F, -1.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	  -0.9F,   -0.9F,   -1.1F,  0.0F,  0.0F,  1.0F,  0.9F,  0.9F,  0.9F, 1.0F, // refrigerator (back side)
	   0.9F,   -0.9F,   -1.1F,  0.0F,  0.0F,  1.0F,  0.9F,  0.9F,  0.9F, 1.0F, // - front side
	  -0.9F,    0.9F,   -1.1F,  0.0F,  0.0F,  1.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	  -0.9F,    0.9F,   -1.1F,  0.0F,  0.0F,  1.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	   0.9F,   -0.9F,   -1.1F,  0.0F,  0.0F,  1.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	   0.9F,    0.9F,   -1.1F,  0.0F,  0.0F,  1.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	  -0.9F,   -0.9F,   -1.2F, -1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, // refrigerator (back side)
	  -0.9F,   -0.9F,   -1.1F, -1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, // - left side
	  -0.9F,    0.9F,   -1.2F, -1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	  -0.9F,    0.9F,   -1.2F, -1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	  -0.9F,   -0.9F,   -1.1F, -1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	  -0.9F,    0.9F,   -1.1F, -1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	   0.9F,   -0.9F,   -1.1F,  1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, // refrigerator (back side)
	   0.9F,   -0.9F,   -1.2F,  1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, // - right side
	   0.9F,    0.9F,   -1.1F,  1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	   0.9F,    0.9F,   -1.1F,  1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	   0.9F,   -0.9F,   -1.2F,  1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	   0.9F,    0.9F,   -1.2F,  1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	  -0.9F,   -0.9F,   -1.2F,  0.0F, -1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, // refrigerator (back side)
	   0.9F,   -0.9F,   -1.2F,  0.0F, -1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, // - bottom side
	  -0.9F,   -0.9F,   -1.1F,  0.0F, -1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	  -0.9F,   -0.9F,   -1.1F,  0.0F, -1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	   0.9F,   -0.9F,   -1.2F,  0.0F, -1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	   0.9F,   -0.9F,   -1.1F,  0.0F, -1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	  -0.9F,    0.9F,   -1.1F,  0.0F,  1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, // refrigerator (back side)
	   0.9F,    0.9F,   -1.1F,  0.0F,  1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, // - top side
	  -0.9F,    0.9F,   -1.2F,  0.0F,  1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	  -0.9F,    0.9F,   -1.2F,  0.0F,  1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	   0.9F,    0.9F,   -1.1F,  0.0F,  1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	   0.9F,    0.9F,   -1.2F,  0.0F,  1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	  -0.9F,   -0.9F,   -1.1F,  0.0F,  0.0F, -1.0F,  0.9F,  0.9F,  0.9F, 1.0F, // refrigerator (left side)
	  -0.8F,   -0.9F,   -1.1F,  0.0F,  0.0F, -1.0F,  0.9F,  0.9F,  0.9F, 1.0F, // - back side
	  -0.9F,    0.9F,   -1.1F,  0.0F,  0.0F, -1.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	  -0.9F,    0.9F,   -1.1F,  0.0F,  0.0F, -1.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	  -0.8F,   -0.9F,   -1.1F,  0.0F,  0.0F, -1.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	  -0.8F,    0.9F,   -1.1F,  0.0F,  0.0F, -1.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	  -0.9F,   -0.9F,    0.9F,  0.0F,  0.0F,  1.0F,  0.9F,  0.9F,  0.9F, 1.0F, // refrigerator (left side)
	  -0.8F,   -0.9F,    0.9F,  0.0F,  0.0F,  1.0F,  0.9F,  0.9F,  0.9F, 1.0F, // - front side
	  -0.9F,    0.9F,    0.9F,  0.0F,  0.0F,  1.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	  -0.9F,    0.9F,    0.9F,  0.0F,  0.0F,  1.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	  -0.8F,   -0.9F,    0.9F,  0.0F,  0.0F,  1.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	  -0.8F,    0.9F,    0.9F,  0.0F,  0.0F,  1.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	  -0.9F,   -0.9F,   -1.1F, -1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, // refrigerator (left side)
	  -0.9F,   -0.9F,    0.9F, -1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, // - left side
	  -0.9F,    0.9F,   -1.1F, -1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	  -0.9F,    0.9F,   -1.1F, -1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	  -0.9F,   -0.9F,    0.9F, -1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	  -0.9F,    0.9F,    0.9F, -1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	  -0.8F,   -0.9F,    0.9F,  1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, // refrigerator (left side)
	  -0.8F,   -0.9F,   -1.1F,  1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, // - right side
	  -0.8F,    0.9F,    0.9F,  1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	  -0.8F,    0.9F,    0.9F,  1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	  -0.8F,   -0.9F,   -1.1F,  1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	  -0.8F,    0.9F,   -1.1F,  1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	  -0.9F,   -0.9F,   -1.1F,  0.0F, -1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, // refrigerator (left side)
	  -0.8F,   -0.9F,   -1.1F,  0.0F, -1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, // - bottom side
	  -0.9F,   -0.9F,    0.9F,  0.0F, -1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	  -0.9F,   -0.9F,    0.9F,  0.0F, -1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	  -0.8F,   -0.9F,   -1.1F,  0.0F, -1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	  -0.8F,   -0.9F,    0.9F,  0.0F, -1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	  -0.9F,    0.9F,    0.9F,  0.0F,  1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, // refrigerator (left side)
	  -0.8F,    0.9F,    0.9F,  0.0F,  1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, // - top side
	  -0.9F,    0.9F,   -1.1F,  0.0F,  1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	  -0.9F,    0.9F,   -1.1F,  0.0F,  1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	  -0.8F,    0.9F,    0.9F,  0.0F,  1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	  -0.8F,    0.9F,   -1.1F,  0.0F,  1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	   0.8F,   -0.9F,   -1.1F,  0.0F,  0.0F, -1.0F,  0.9F,  0.9F,  0.9F, 1.0F, // refrigerator (right side)
	   0.9F,   -0.9F,   -1.1F,  0.0F,  0.0F, -1.0F,  0.9F,  0.9F,  0.9F, 1.0F, // - back side
	   0.8F,    0.9F,   -1.1F,  0.0F,  0.0F, -1.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	   0.8F,    0.9F,   -1.1F,  0.0F,  0.0F, -1.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	   0.9F,   -0.9F,   -1.1F,  0.0F,  0.0F, -1.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	   0.9F,    0.9F,   -1.1F,  0.0F,  0.0F, -1.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	   0.8F,   -0.9F,    0.9F,  0.0F,  0.0F,  1.0F,  0.9F,  0.9F,  0.9F, 1.0F, // refrigerator (right side)
	   0.9F,   -0.9F,    0.9F,  0.0F,  0.0F,  1.0F,  0.9F,  0.9F,  0.9F, 1.0F, // - front side
	   0.8F,    0.9F,    0.9F,  0.0F,  0.0F,  1.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	   0.8F,    0.9F,    0.9F,  0.0F,  0.0F,  1.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	   0.9F,   -0.9F,    0.9F,  0.0F,  0.0F,  1.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	   0.9F,    0.9F,    0.9F,  0.0F,  0.0F,  1.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	   0.8F,   -0.9F,   -1.1F, -1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, // refrigerator (right side)
	   0.8F,   -0.9F,    0.9F, -1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, // - left side
	   0.8F,    0.9F,   -1.1F, -1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	   0.8F,    0.9F,   -1.1F, -1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	   0.8F,   -0.9F,    0.9F, -1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	   0.8F,    0.9F,    0.9F, -1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	   0.9F,   -0.9F,    0.9F,  1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, // refrigerator (right side)
	   0.9F,   -0.9F,   -1.1F,  1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, // - right side
	   0.9F,    0.9F,    0.9F,  1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	   0.9F,    0.9F,    0.9F,  1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	   0.9F,   -0.9F,   -1.1F,  1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	   0.9F,    0.9F,   -1.1F,  1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	   0.8F,   -0.9F,   -1.1F,  0.0F, -1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, // refrigerator (right side)
	   0.9F,   -0.9F,   -1.1F,  0.0F, -1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, // - bottom side
	   0.8F,   -0.9F,    0.9F,  0.0F, -1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	   0.8F,   -0.9F,    0.9F,  0.0F, -1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	   0.9F,   -0.9F,   -1.1F,  0.0F, -1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	   0.9F,   -0.9F,    0.9F,  0.0F, -1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	   0.8F,    0.9F,    0.9F,  0.0F,  1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, // refrigerator (right side)
	   0.9F,    0.9F,    0.9F,  0.0F,  1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, // - top side
	   0.8F,    0.9F,   -1.1F,  0.0F,  1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	   0.8F,    0.9F,   -1.1F,  0.0F,  1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	   0.9F,    0.9F,    0.9F,  0.0F,  1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	   0.9F,    0.9F,   -1.1F,  0.0F,  1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	  -0.8F,   -0.9F,   -1.1F,  0.0F,  0.0F, -1.0F,  0.9F,  0.9F,  0.9F, 1.0F, // refrigerator (bottom side)
	   0.8F,   -0.9F,   -1.1F,  0.0F,  0.0F, -1.0F,  0.9F,  0.9F,  0.9F, 1.0F, // - back side
	  -0.8F,   -0.8F,   -1.1F,  0.0F,  0.0F, -1.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	  -0.8F,   -0.8F,   -1.1F,  0.0F,  0.0F, -1.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	   0.8F,   -0.9F,   -1.1F,  0.0F,  0.0F, -1.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	   0.8F,   -0.8F,   -1.1F,  0.0F,  0.0F, -1.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	  -0.8F,   -0.9F,    0.9F,  0.0F,  0.0F,  1.0F,  0.9F,  0.9F,  0.9F, 1.0F, // refrigerator (bottom side)
	   0.8F,   -0.9F,    0.9F,  0.0F,  0.0F,  1.0F,  0.9F,  0.9F,  0.9F, 1.0F, // - front side
	  -0.8F,   -0.8F,    0.9F,  0.0F,  0.0F,  1.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	  -0.8F,   -0.8F,    0.9F,  0.0F,  0.0F,  1.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	   0.8F,   -0.9F,    0.9F,  0.0F,  0.0F,  1.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	   0.8F,   -0.8F,    0.9F,  0.0F,  0.0F,  1.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	  -0.8F,   -0.9F,   -1.1F, -1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, // refrigerator (bottom side)
	  -0.8F,   -0.9F,    0.9F, -1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, // - left side
	  -0.8F,   -0.8F,   -1.1F, -1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	  -0.8F,   -0.8F,   -1.1F, -1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	  -0.8F,   -0.9F,    0.9F, -1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	  -0.8F,   -0.8F,    0.9F, -1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	   0.8F,   -0.9F,    0.9F,  1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, // refrigerator (bottom side)
	   0.8F,   -0.9F,   -1.1F,  1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, // - right side
	   0.8F,   -0.8F,    0.9F,  1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	   0.8F,   -0.8F,    0.9F,  1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	   0.8F,   -0.9F,   -1.1F,  1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	   0.8F,   -0.8F,   -1.1F,  1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	  -0.8F,   -0.9F,   -1.1F,  0.0F, -1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, // refrigerator (bottom side)
	   0.8F,   -0.9F,   -1.1F,  0.0F, -1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, // - bottom side
	  -0.8F,   -0.9F,    0.9F,  0.0F, -1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	  -0.8F,   -0.9F,    0.9F,  0.0F, -1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	   0.8F,   -0.9F,   -1.1F,  0.0F, -1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	   0.8F,   -0.9F,    0.9F,  0.0F, -1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	  -0.8F,   -0.8F,    0.9F,  0.0F,  1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, // refrigerator (bottom side)
	   0.8F,   -0.8F,    0.9F,  0.0F,  1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, // - top side
	  -0.8F,   -0.8F,   -1.1F,  0.0F,  1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	  -0.8F,   -0.8F,   -1.1F,  0.0F,  1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	   0.8F,   -0.8F,    0.9F,  0.0F,  1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	   0.8F,   -0.8F,   -1.1F,  0.0F,  1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	  -0.8F,    0.8F,   -1.1F,  0.0F,  0.0F, -1.0F,  0.9F,  0.9F,  0.9F, 1.0F, // refrigerator (top side)
	   0.8F,    0.8F,   -1.1F,  0.0F,  0.0F, -1.0F,  0.9F,  0.9F,  0.9F, 1.0F, // - back side
	  -0.8F,    0.9F,   -1.1F,  0.0F,  0.0F, -1.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	  -0.8F,    0.9F,   -1.1F,  0.0F,  0.0F, -1.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	   0.8F,    0.8F,   -1.1F,  0.0F,  0.0F, -1.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	   0.8F,    0.9F,   -1.1F,  0.0F,  0.0F, -1.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	  -0.8F,    0.8F,    0.9F,  0.0F,  0.0F,  1.0F,  0.9F,  0.9F,  0.9F, 1.0F, // refrigerator (top side)
	   0.8F,    0.8F,    0.9F,  0.0F,  0.0F,  1.0F,  0.9F,  0.9F,  0.9F, 1.0F, // - front side
	  -0.8F,    0.9F,    0.9F,  0.0F,  0.0F,  1.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	  -0.8F,    0.9F,    0.9F,  0.0F,  0.0F,  1.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	   0.8F,    0.8F,    0.9F,  0.0F,  0.0F,  1.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	   0.8F,    0.9F,    0.9F,  0.0F,  0.0F,  1.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	  -0.8F,    0.8F,   -1.1F, -1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, // refrigerator (top side)
	  -0.8F,    0.8F,    0.9F, -1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, // - left side
	  -0.8F,    0.9F,   -1.1F, -1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	  -0.8F,    0.9F,   -1.1F, -1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	  -0.8F,    0.8F,    0.9F, -1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	  -0.8F,    0.9F,    0.9F, -1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	   0.8F,    0.8F,    0.9F,  1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, // refrigerator (top side)
	   0.8F,    0.8F,   -1.1F,  1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, // - right side
	   0.8F,    0.9F,    0.9F,  1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	   0.8F,    0.9F,    0.9F,  1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	   0.8F,    0.8F,   -1.1F,  1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	   0.8F,    0.9F,   -1.1F,  1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	  -0.8F,    0.8F,   -1.1F,  0.0F, -1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, // refrigerator (top side)
	   0.8F,    0.8F,   -1.1F,  0.0F, -1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, // - bottom side
	  -0.8F,    0.8F,    0.9F,  0.0F, -1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	  -0.8F,    0.8F,    0.9F,  0.0F, -1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	   0.8F,    0.8F,   -1.1F,  0.0F, -1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	   0.8F,    0.8F,    0.9F,  0.0F, -1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	  -0.8F,    0.9F,    0.9F,  0.0F,  1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, // refrigerator (top side)
	   0.8F,    0.9F,    0.9F,  0.0F,  1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, // - top side
	  -0.8F,    0.9F,   -1.1F,  0.0F,  1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	  -0.8F,    0.9F,   -1.1F,  0.0F,  1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	   0.8F,    0.9F,    0.9F,  0.0F,  1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F, 
	   0.8F,    0.9F,   -1.1F,  0.0F,  1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 1.0F
};

float verticesOfRefrigeratorDoors[4560U] = {
	// position                // normal vector     // color
	  -0.9F,   -0.9F,    0.9F,  0.0F,  0.0F, -1.0F,  0.9F,  0.9F,  0.9F, 0.5F, // refrigerator (front side)
	   0.9F,   -0.9F,    0.9F,  0.0F,  0.0F, -1.0F,  0.9F,  0.9F,  0.9F, 0.5F, // - back side
	  -0.9F,    0.9F,    0.9F,  0.0F,  0.0F, -1.0F,  0.9F,  0.9F,  0.9F, 0.5F, 
	  -0.9F,    0.9F,    0.9F,  0.0F,  0.0F, -1.0F,  0.9F,  0.9F,  0.9F, 0.5F, 
	   0.9F,   -0.9F,    0.9F,  0.0F,  0.0F, -1.0F,  0.9F,  0.9F,  0.9F, 0.5F, 
	   0.9F,    0.9F,    0.9F,  0.0F,  0.0F, -1.0F,  0.9F,  0.9F,  0.9F, 0.5F, 
	  -0.9F,   -0.9F,    1.0F,  0.0F,  0.0F,  1.0F,  0.9F,  0.9F,  0.9F, 0.5F, // refrigerator (front side)
	   0.9F,   -0.9F,    1.0F,  0.0F,  0.0F,  1.0F,  0.9F,  0.9F,  0.9F, 0.5F, // - front side
	  -0.9F,    0.9F,    1.0F,  0.0F,  0.0F,  1.0F,  0.9F,  0.9F,  0.9F, 0.5F, 
	  -0.9F,    0.9F,    1.0F,  0.0F,  0.0F,  1.0F,  0.9F,  0.9F,  0.9F, 0.5F, 
	   0.9F,   -0.9F,    1.0F,  0.0F,  0.0F,  1.0F,  0.9F,  0.9F,  0.9F, 0.5F, 
	   0.9F,    0.9F,    1.0F,  0.0F,  0.0F,  1.0F,  0.9F,  0.9F,  0.9F, 0.5F, 
	  -0.9F,   -0.9F,    0.9F, -1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 0.5F, // refrigerator (front side)
	  -0.9F,   -0.9F,    1.0F, -1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 0.5F, // - left side
	  -0.9F,    0.9F,    0.9F, -1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 0.5F, 
	  -0.9F,    0.9F,    0.9F, -1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 0.5F, 
	  -0.9F,   -0.9F,    1.0F, -1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 0.5F, 
	  -0.9F,    0.9F,    1.0F, -1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 0.5F, 
	   0.9F,   -0.9F,    1.0F,  1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 0.5F, // refrigerator (front side)
	   0.9F,   -0.9F,    0.9F,  1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 0.5F, // - right side
	   0.9F,    0.9F,    1.0F,  1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 0.5F, 
	   0.9F,    0.9F,    1.0F,  1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 0.5F, 
	   0.9F,   -0.9F,    0.9F,  1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 0.5F, 
	   0.9F,    0.9F,    0.9F,  1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 0.5F, 
	  -0.9F,   -0.9F,    0.9F,  0.0F, -1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 0.5F, // refrigerator (front side)
	   0.9F,   -0.9F,    0.9F,  0.0F, -1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 0.5F, // - bottom side
	  -0.9F,   -0.9F,    1.0F,  0.0F, -1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 0.5F, 
	  -0.9F,   -0.9F,    1.0F,  0.0F, -1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 0.5F, 
	   0.9F,   -0.9F,    0.9F,  0.0F, -1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 0.5F, 
	   0.9F,   -0.9F,    1.0F,  0.0F, -1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 0.5F, 
	  -0.9F,    0.9F,    1.0F,  0.0F,  1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 0.5F, // refrigerator (front side)
	   0.9F,    0.9F,    1.0F,  0.0F,  1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 0.5F, // - top side
	  -0.9F,    0.9F,    0.9F,  0.0F,  1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 0.5F, 
	  -0.9F,    0.9F,    0.9F,  0.0F,  1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 0.5F, 
	   0.9F,    0.9F,    1.0F,  0.0F,  1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 0.5F, 
	   0.9F,    0.9F,    0.9F,  0.0F,  1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 0.5F, 
	-0.775F,  0.625F,  1.005F,  0.0F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 1.0F, // digital clock widget
	-0.475F,  0.625F,  1.005F,  0.0F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 1.0F, // - back side
	-0.775F,  0.775F,  1.005F,  0.0F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
	-0.775F,  0.775F,  1.005F,  0.0F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
	-0.475F,  0.625F,  1.005F,  0.0F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
	-0.475F,  0.775F,  1.005F,  0.0F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
	-0.775F,  0.625F,  1.025F,  0.0F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 1.0F, // digital clock widget
	-0.475F,  0.625F,  1.025F,  0.0F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 1.0F, // - front side
	-0.775F,  0.775F,  1.025F,  0.0F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
	-0.775F,  0.775F,  1.025F,  0.0F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
	-0.475F,  0.625F,  1.025F,  0.0F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
	-0.475F,  0.775F,  1.025F,  0.0F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
	-0.775F,  0.625F,  1.005F, -1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, // digital clock widget
	-0.775F,  0.625F,  1.025F, -1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, // - left side
	-0.775F,  0.775F,  1.005F, -1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
	-0.775F,  0.775F,  1.005F, -1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
	-0.775F,  0.625F,  1.025F, -1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
	-0.775F,  0.775F,  1.025F, -1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
	-0.475F,  0.625F,  1.025F,  1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, // digital clock widget
	-0.475F,  0.625F,  1.005F,  1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, // - right side
	-0.475F,  0.775F,  1.025F,  1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
	-0.475F,  0.775F,  1.025F,  1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
	-0.475F,  0.625F,  1.005F,  1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
	-0.475F,  0.775F,  1.005F,  1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
	-0.775F,  0.625F,  1.005F,  1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, // digital clock widget
	-0.475F,  0.625F,  1.005F,  1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, // - bottom side
	-0.775F,  0.625F,  1.025F,  1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
	-0.775F,  0.625F,  1.025F,  1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
	-0.475F,  0.625F,  1.005F,  1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
	-0.775F,  0.625F,  1.025F,  1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
	-0.775F,  0.775F,  1.025F,  1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, // digital clock widget
	-0.475F,  0.775F,  1.025F,  1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, // - top side
	-0.775F,  0.775F,  1.005F,  1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
	-0.775F,  0.775F,  1.005F,  1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
	-0.475F,  0.775F,  1.025F,  1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
	-0.475F,  0.775F,  1.005F,  1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
	-0.775F,   0.45F,  1.005F,  0.0F,  0.0F, -1.0F, 0.75F, 0.75F, 0.75F, 1.0F, // see-through mode activation button
	-0.475F,   0.45F,  1.005F,  0.0F,  0.0F, -1.0F, 0.75F, 0.75F, 0.75F, 1.0F, // - back side
	-0.775F,   0.55F,  1.005F,  0.0F,  0.0F, -1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	-0.775F,   0.55F,  1.005F,  0.0F,  0.0F, -1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	-0.475F,   0.45F,  1.005F,  0.0F,  0.0F, -1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	-0.475F,   0.55F,  1.005F,  0.0F,  0.0F, -1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	-0.775F,   0.45F,  1.025F,  0.0F,  0.0F,  1.0F, 0.75F, 0.75F, 0.75F, 1.0F, // see-through mode activation button
	-0.475F,   0.45F,  1.025F,  0.0F,  0.0F,  1.0F, 0.75F, 0.75F, 0.75F, 1.0F, // - front side
	-0.775F,   0.55F,  1.025F,  0.0F,  0.0F,  1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	-0.775F,   0.55F,  1.025F,  0.0F,  0.0F,  1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	-0.475F,   0.45F,  1.025F,  0.0F,  0.0F,  1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	-0.475F,   0.55F,  1.025F,  0.0F,  0.0F,  1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	-0.775F,   0.45F,  1.005F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // see-through mode activation button
	-0.775F,   0.45F,  1.025F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // - left side
	-0.775F,   0.55F,  1.005F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	-0.775F,   0.55F,  1.005F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	-0.775F,   0.45F,  1.025F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	-0.775F,   0.55F,  1.025F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	-0.475F,   0.45F,  1.025F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // see-through mode activation button
	-0.475F,   0.45F,  1.005F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // - right side
	-0.475F,   0.55F,  1.025F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	-0.475F,   0.55F,  1.025F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	-0.475F,   0.45F,  1.005F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	-0.475F,   0.55F,  1.005F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	-0.475F,   0.45F,  1.005F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // see-through mode activation button
	-0.775F,   0.45F,  1.005F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // - bottom side
	-0.475F,   0.45F,  1.025F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	-0.475F,   0.45F,  1.025F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	-0.775F,   0.45F,  1.005F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	-0.775F,   0.45F,  1.025F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	-0.775F,   0.55F,  1.025F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // see-through mode activation button
	-0.475F,   0.55F,  1.025F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // - top side
	-0.775F,   0.55F,  1.005F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	-0.775F,   0.55F,  1.005F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	-0.475F,   0.55F,  1.025F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	-0.475F,   0.55F,  1.005F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	-0.725F,   0.47F,  1.027F,  0.0F,  0.0F,  1.0F,  1.0F,  1.0F,  1.0F, 1.0F, // rectangle symbol on the see-through mode activation button
	-0.525F,   0.47F,  1.027F,  0.0F,  0.0F,  1.0F,  1.0F,  1.0F,  1.0F, 1.0F, 
	-0.725F,   0.53F,  1.027F,  0.0F,  0.0F,  1.0F,  1.0F,  1.0F,  1.0F, 1.0F, 
	-0.725F,   0.53F,  1.027F,  0.0F,  0.0F,  1.0F,  1.0F,  1.0F,  1.0F, 1.0F, 
	-0.525F,   0.47F,  1.027F,  0.0F,  0.0F,  1.0F,  1.0F,  1.0F,  1.0F, 1.0F, 
	-0.525F,   0.53F,  1.027F,  0.0F,  0.0F,  1.0F,  1.0F,  1.0F,  1.0F, 1.0F, 
	   0.1F,   0.65F,  1.005F,  0.0F,  0.0F, -1.0F, 0.75F, 0.75F, 0.75F, 1.0F, // "-" button, left of freezing chamber temperature widget
	   0.2F,   0.65F,  1.005F,  0.0F,  0.0F, -1.0F, 0.75F, 0.75F, 0.75F, 1.0F, // - back side
	   0.1F,   0.75F,  1.005F,  0.0F,  0.0F, -1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	   0.1F,   0.75F,  1.005F,  0.0F,  0.0F, -1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	   0.2F,   0.65F,  1.005F,  0.0F,  0.0F, -1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	   0.2F,   0.75F,  1.005F,  0.0F,  0.0F, -1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	   0.1F,   0.65F,  1.025F,  0.0F,  0.0F,  1.0F, 0.75F, 0.75F, 0.75F, 1.0F, // "-" button, left of freezing chamber temperature widget
	   0.2F,   0.65F,  1.025F,  0.0F,  0.0F,  1.0F, 0.75F, 0.75F, 0.75F, 1.0F, // - front side
	   0.1F,   0.75F,  1.025F,  0.0F,  0.0F,  1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	   0.1F,   0.75F,  1.025F,  0.0F,  0.0F,  1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	   0.2F,   0.65F,  1.025F,  0.0F,  0.0F,  1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	   0.2F,   0.75F,  1.025F,  0.0F,  0.0F,  1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	   0.1F,   0.65F,  1.005F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // "-" button, left of freezing chamber temperature widget
	   0.1F,   0.65F,  1.025F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // - left side
	   0.1F,   0.75F,  1.005F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	   0.1F,   0.75F,  1.005F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	   0.1F,   0.65F,  1.025F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	   0.1F,   0.75F,  1.025F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	   0.2F,   0.65F,  1.025F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // "-" button, left of freezing chamber temperature widget
	   0.2F,   0.65F,  1.005F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // - right side
	   0.2F,   0.75F,  1.025F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	   0.2F,   0.75F,  1.025F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	   0.2F,   0.65F,  1.005F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	   0.2F,   0.75F,  1.005F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	   0.1F,   0.65F,  1.005F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // "-" button, left of freezing chamber temperature widget
	   0.2F,   0.65F,  1.005F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // - bottom side
	   0.1F,   0.65F,  1.025F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	   0.1F,   0.65F,  1.025F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	   0.2F,   0.65F,  1.005F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	   0.2F,   0.65F,  1.025F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	   0.1F,   0.75F,  1.025F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // "-" button, left of freezing chamber temperature widget
	   0.2F,   0.75F,  1.025F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // - top side
	   0.1F,   0.75F,  1.005F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	   0.1F,   0.75F,  1.005F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	   0.2F,   0.75F,  1.025F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	   0.2F,   0.75F,  1.005F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	  0.12F,    0.7F,  1.027F,  0.0F,  0.0F,  1.0F,  1.0F,  1.0F,  1.0F, 1.0F, // line representing the "-" sign itself
	  0.18F,    0.7F,  1.027F,  0.0F,  0.0F,  1.0F,  1.0F,  1.0F,  1.0F, 1.0F, 
	 0.225F,  0.625F,  1.005F,  0.0F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 1.0F, // freezing chamber temperature widget
	 0.625F,  0.625F,  1.005F,  0.0F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 1.0F, // - back side
	 0.225F,  0.775F,  1.005F,  0.0F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
	 0.225F,  0.775F,  1.005F,  0.0F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
	 0.625F,  0.625F,  1.005F,  0.0F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
	 0.625F,  0.775F,  1.005F,  0.0F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
	 0.225F,  0.625F,  1.025F,  0.0F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 1.0F, // freezing chamber temperature widget
	 0.625F,  0.625F,  1.025F,  0.0F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 1.0F, // - front side
	 0.225F,  0.775F,  1.025F,  0.0F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
	 0.225F,  0.775F,  1.025F,  0.0F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
	 0.625F,  0.625F,  1.025F,  0.0F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
	 0.625F,  0.775F,  1.025F,  0.0F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
	 0.225F,  0.625F,  1.005F, -1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, // freezing chamber temperature widget
	 0.225F,  0.625F,  1.025F, -1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, // - left side
	 0.225F,  0.775F,  1.005F, -1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
	 0.225F,  0.775F,  1.005F, -1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
	 0.225F,  0.625F,  1.025F, -1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
	 0.225F,  0.775F,  1.025F, -1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
	 0.625F,  0.625F,  1.025F,  1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, // freezing chamber temperature widget
	 0.625F,  0.625F,  1.005F,  1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, // - right side
	 0.625F,  0.775F,  1.025F,  1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
	 0.625F,  0.775F,  1.025F,  1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
	 0.625F,  0.625F,  1.005F,  1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
	 0.625F,  0.775F,  1.005F,  1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
	 0.225F,  0.625F,  1.005F,  0.0F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, // freezing chamber temperature widget
	 0.625F,  0.625F,  1.005F,  0.0F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, // - bottom side
	 0.225F,  0.625F,  1.025F,  0.0F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
	 0.225F,  0.625F,  1.025F,  0.0F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
	 0.625F,  0.625F,  1.005F,  0.0F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
	 0.625F,  0.625F,  1.025F,  0.0F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
	 0.225F,  0.775F,  1.025F,  0.0F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, // freezing chamber temperature widget
	 0.625F,  0.775F,  1.025F,  0.0F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, // - top side
	 0.225F,  0.775F,  1.005F,  0.0F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
	 0.225F,  0.775F,  1.005F,  0.0F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
	 0.625F,  0.775F,  1.025F,  0.0F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
	 0.625F,  0.775F,  1.005F,  0.0F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
	  0.65F,   0.65F,  1.005F,  0.0F,  0.0F, -1.0F, 0.75F, 0.75F, 0.75F, 1.0F, // "+" button, right of freezing chamber temperature widget
	  0.75F,   0.65F,  1.005F,  0.0F,  0.0F, -1.0F, 0.75F, 0.75F, 0.75F, 1.0F, // - back side
	  0.65F,   0.75F,  1.005F,  0.0F,  0.0F, -1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	  0.65F,   0.75F,  1.005F,  0.0F,  0.0F, -1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	  0.75F,   0.65F,  1.005F,  0.0F,  0.0F, -1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	  0.75F,   0.75F,  1.005F,  0.0F,  0.0F, -1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	  0.65F,   0.65F,  1.025F,  0.0F,  0.0F,  1.0F, 0.75F, 0.75F, 0.75F, 1.0F, // "+" button, right of freezing chamber temperature widget
	  0.75F,   0.65F,  1.025F,  0.0F,  0.0F,  1.0F, 0.75F, 0.75F, 0.75F, 1.0F, // - front side
	  0.65F,   0.75F,  1.025F,  0.0F,  0.0F,  1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	  0.65F,   0.75F,  1.025F,  0.0F,  0.0F,  1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	  0.75F,   0.65F,  1.025F,  0.0F,  0.0F,  1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	  0.75F,   0.75F,  1.025F,  0.0F,  0.0F,  1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	  0.65F,   0.65F,  1.005F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // "+" button, right of freezing chamber temperature widget
	  0.65F,   0.65F,  1.025F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // - left side
	  0.65F,   0.75F,  1.005F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	  0.65F,   0.75F,  1.005F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	  0.65F,   0.65F,  1.025F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	  0.65F,   0.75F,  1.025F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	  0.75F,   0.65F,  1.025F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // "+" button, right of freezing chamber temperature widget
	  0.75F,   0.65F,  1.005F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // - right side
	  0.75F,   0.75F,  1.025F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	  0.75F,   0.75F,  1.025F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	  0.75F,   0.65F,  1.005F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	  0.75F,   0.75F,  1.005F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	  0.65F,   0.65F,  1.005F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // "+" button, right of freezing chamber temperature widget
	  0.75F,   0.65F,  1.005F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // - bottom side
	  0.65F,   0.65F,  1.025F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	  0.65F,   0.65F,  1.025F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	  0.75F,   0.65F,  1.005F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	  0.75F,   0.65F,  1.025F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	  0.65F,   0.75F,  1.025F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // "+" button, right of freezing chamber temperature widget
	  0.75F,   0.75F,  1.025F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // - top side
	  0.65F,   0.75F,  1.005F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	  0.65F,   0.75F,  1.005F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	  0.75F,   0.75F,  1.025F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	  0.75F,   0.75F,  1.005F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	  0.67F,    0.7F,  1.027F,  0.0F,  0.0F,  1.0F,  1.0F,  1.0F,  1.0F, 1.0F, // lines representing the "+" sign itself
	  0.73F,    0.7F,  1.027F,  0.0F,  0.0F,  1.0F,  1.0F,  1.0F,  1.0F, 1.0F, 
	   0.7F,   0.67F,  1.027F,  0.0F,  0.0F,  1.0F,  1.0F,  1.0F,  1.0F, 1.0F, 
	   0.7F,   0.73F,  1.027F,  0.0F,  0.0F,  1.0F,  1.0F,  1.0F,  1.0F, 1.0F, 
	   0.1F,   0.45F,  1.005F,  0.0F,  0.0F, -1.0F, 0.75F, 0.75F, 0.75F, 1.0F, // "-" button, left of refrigerating chamber temperature widget
	   0.2F,   0.45F,  1.005F,  0.0F,  0.0F, -1.0F, 0.75F, 0.75F, 0.75F, 1.0F, // - back side
	   0.1F,   0.55F,  1.005F,  0.0F,  0.0F, -1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	   0.1F,   0.55F,  1.005F,  0.0F,  0.0F, -1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	   0.2F,   0.45F,  1.005F,  0.0F,  0.0F, -1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	   0.2F,   0.55F,  1.005F,  0.0F,  0.0F, -1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	   0.1F,   0.45F,  1.025F,  0.0F,  0.0F,  1.0F, 0.75F, 0.75F, 0.75F, 1.0F, // "-" button, left of refrigerating chamber temperature widget
	   0.2F,   0.45F,  1.025F,  0.0F,  0.0F,  1.0F, 0.75F, 0.75F, 0.75F, 1.0F, // - front side
	   0.1F,   0.55F,  1.025F,  0.0F,  0.0F,  1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	   0.1F,   0.55F,  1.025F,  0.0F,  0.0F,  1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	   0.2F,   0.45F,  1.025F,  0.0F,  0.0F,  1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	   0.2F,   0.55F,  1.025F,  0.0F,  0.0F,  1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	   0.1F,   0.45F,  1.005F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // "-" button, left of refrigerating chamber temperature widget
	   0.1F,   0.45F,  1.025F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // - left side
	   0.1F,   0.55F,  1.005F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	   0.1F,   0.55F,  1.005F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	   0.1F,   0.45F,  1.025F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	   0.1F,   0.55F,  1.025F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	   0.2F,   0.45F,  1.025F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // "-" button, left of refrigerating chamber temperature widget
	   0.2F,   0.45F,  1.005F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // - right side
	   0.2F,   0.55F,  1.025F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	   0.2F,   0.55F,  1.025F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	   0.2F,   0.45F,  1.005F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	   0.2F,   0.55F,  1.005F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	   0.1F,   0.45F,  1.005F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // "-" button, left of refrigerating chamber temperature widget
	   0.2F,   0.45F,  1.005F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // - bottom side
	   0.1F,   0.45F,  1.025F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	   0.1F,   0.45F,  1.025F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	   0.2F,   0.45F,  1.005F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	   0.2F,   0.45F,  1.025F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	   0.1F,   0.55F,  1.025F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // "-" button, left of refrigerating chamber temperature widget
	   0.2F,   0.55F,  1.025F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // - top side
	   0.1F,   0.55F,  1.005F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	   0.1F,   0.55F,  1.005F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	   0.2F,   0.55F,  1.025F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	   0.2F,   0.55F,  1.005F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	  0.12F,    0.5F,  1.027F,  0.0F,  0.0F,  1.0F,  1.0F,  1.0F,  1.0F, 1.0F, // line representing the "-" sign itself
	  0.18F,    0.5F,  1.027F,  0.0F,  0.0F,  1.0F,  1.0F,  1.0F,  1.0F, 1.0F, 
	 0.225F,  0.425F,  1.005F,  0.0F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 1.0F, // refrigerating chamber temperature widget
	 0.625F,  0.425F,  1.005F,  0.0F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 1.0F, // - back side
	 0.225F,  0.575F,  1.005F,  0.0F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
	 0.225F,  0.575F,  1.005F,  0.0F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
	 0.625F,  0.425F,  1.005F,  0.0F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
	 0.625F,  0.575F,  1.005F,  0.0F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
	 0.225F,  0.425F,  1.025F,  0.0F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 1.0F, // refrigerating chamber temperature widget
	 0.625F,  0.425F,  1.025F,  0.0F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 1.0F, // - front side
	 0.225F,  0.575F,  1.025F,  0.0F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
	 0.225F,  0.575F,  1.025F,  0.0F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
	 0.625F,  0.425F,  1.025F,  0.0F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
	 0.625F,  0.575F,  1.025F,  0.0F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
	 0.225F,  0.425F,  1.005F, -1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, // refrigerating chamber temperature widget
	 0.225F,  0.425F,  1.025F, -1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, // - left side
	 0.225F,  0.575F,  1.005F, -1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
	 0.225F,  0.575F,  1.005F, -1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
	 0.225F,  0.425F,  1.025F, -1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
	 0.225F,  0.575F,  1.025F, -1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
	 0.625F,  0.425F,  1.025F,  1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, // refrigerating chamber temperature widget
	 0.625F,  0.425F,  1.005F,  1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, // - right side
	 0.625F,  0.575F,  1.025F,  1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
	 0.625F,  0.575F,  1.025F,  1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
	 0.625F,  0.425F,  1.005F,  1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
	 0.625F,  0.575F,  1.005F,  1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
	 0.225F,  0.425F,  1.005F,  0.0F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, // refrigerating chamber temperature widget
	 0.625F,  0.425F,  1.005F,  0.0F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, // - bottom side
	 0.225F,  0.425F,  1.025F,  0.0F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
	 0.225F,  0.425F,  1.025F,  0.0F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
	 0.625F,  0.425F,  1.005F,  0.0F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
	 0.625F,  0.425F,  1.025F,  0.0F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
	 0.225F,  0.575F,  1.025F,  0.0F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, // refrigerating chamber temperature widget
	 0.625F,  0.575F,  1.025F,  0.0F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, // - top side
	 0.225F,  0.575F,  1.005F,  0.0F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
	 0.225F,  0.575F,  1.005F,  0.0F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
	 0.625F,  0.575F,  1.025F,  0.0F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
	 0.625F,  0.575F,  1.005F,  0.0F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
	  0.65F,   0.45F,  1.005F,  0.0F,  0.0F, -1.0F, 0.75F, 0.75F, 0.75F, 1.0F, // "+" button, right of refrigerating chamber temperature widget
	  0.75F,   0.45F,  1.005F,  0.0F,  0.0F, -1.0F, 0.75F, 0.75F, 0.75F, 1.0F, // - back side
	  0.65F,   0.55F,  1.005F,  0.0F,  0.0F, -1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	  0.65F,   0.55F,  1.005F,  0.0F,  0.0F, -1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	  0.75F,   0.45F,  1.005F,  0.0F,  0.0F, -1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	  0.75F,   0.55F,  1.005F,  0.0F,  0.0F, -1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	  0.65F,   0.45F,  1.025F,  0.0F,  0.0F,  1.0F, 0.75F, 0.75F, 0.75F, 1.0F, // "+" button, right of refrigerating chamber temperature widget
	  0.75F,   0.45F,  1.025F,  0.0F,  0.0F,  1.0F, 0.75F, 0.75F, 0.75F, 1.0F, // - front side
	  0.65F,   0.55F,  1.025F,  0.0F,  0.0F,  1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	  0.65F,   0.55F,  1.025F,  0.0F,  0.0F,  1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	  0.75F,   0.45F,  1.025F,  0.0F,  0.0F,  1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	  0.75F,   0.55F,  1.025F,  0.0F,  0.0F,  1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	  0.65F,   0.45F,  1.005F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // "+" button, right of refrigerating chamber temperature widget
	  0.65F,   0.45F,  1.025F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // - left side
	  0.65F,   0.55F,  1.005F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	  0.65F,   0.55F,  1.005F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	  0.65F,   0.45F,  1.025F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	  0.65F,   0.55F,  1.025F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	  0.75F,   0.45F,  1.025F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // "+" button, right of refrigerating chamber temperature widget
	  0.75F,   0.45F,  1.005F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // - right side
	  0.75F,   0.55F,  1.025F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	  0.75F,   0.55F,  1.025F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	  0.75F,   0.45F,  1.005F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	  0.75F,   0.55F,  1.005F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	  0.65F,   0.45F,  1.005F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // "+" button, right of refrigerating chamber temperature widget
	  0.75F,   0.45F,  1.005F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // - bottom side
	  0.65F,   0.45F,  1.025F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	  0.65F,   0.45F,  1.025F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	  0.75F,   0.45F,  1.005F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	  0.75F,   0.45F,  1.025F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	  0.65F,   0.55F,  1.025F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // "+" button, right of refrigerating chamber temperature widget
	  0.75F,   0.55F,  1.025F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // - top side
	  0.65F,   0.55F,  1.005F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	  0.65F,   0.55F,  1.005F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	  0.75F,   0.55F,  1.025F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	  0.75F,   0.55F,  1.005F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	  0.67F,    0.5F,  1.027F,  0.0F,  0.0F,  1.0F,  1.0F,  1.0F,  1.0F, 1.0F, // lines representing the "+" sign itself
	  0.73F,    0.5F,  1.027F,  0.0F,  0.0F,  1.0F,  1.0F,  1.0F,  1.0F, 1.0F, 
	   0.7F,   0.47F,  1.027F,  0.0F,  0.0F,  1.0F,  1.0F,  1.0F,  1.0F, 1.0F, 
	   0.7F,   0.53F,  1.027F,  0.0F,  0.0F,  1.0F,  1.0F,  1.0F,  1.0F, 1.0F, 
	   0.1F,  0.325F,  1.005F,  0.0F,  0.0F, -1.0F, 0.75F, 0.75F, 0.75F, 1.0F, // "-" button, left of point light intensity widget
	   0.2F,  0.325F,  1.005F,  0.0F,  0.0F, -1.0F, 0.75F, 0.75F, 0.75F, 1.0F, // - back side
	   0.1F,  0.375F,  1.005F,  0.0F,  0.0F, -1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	   0.1F,  0.375F,  1.005F,  0.0F,  0.0F, -1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	   0.2F,  0.325F,  1.005F,  0.0F,  0.0F, -1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	   0.2F,  0.375F,  1.005F,  0.0F,  0.0F, -1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	   0.1F,  0.325F,  1.025F,  0.0F,  0.0F,  1.0F, 0.75F, 0.75F, 0.75F, 1.0F, // "-" button, left of point light intensity widget
	   0.2F,  0.325F,  1.025F,  0.0F,  0.0F,  1.0F, 0.75F, 0.75F, 0.75F, 1.0F, // - front side
	   0.1F,  0.375F,  1.025F,  0.0F,  0.0F,  1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	   0.1F,  0.375F,  1.025F,  0.0F,  0.0F,  1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	   0.2F,  0.325F,  1.025F,  0.0F,  0.0F,  1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	   0.2F,  0.375F,  1.025F,  0.0F,  0.0F,  1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	   0.1F,  0.325F,  1.005F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // "-" button, left of point light intensity widget
	   0.1F,  0.325F,  1.025F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // - left side
	   0.1F,  0.375F,  1.005F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	   0.1F,  0.375F,  1.005F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	   0.1F,  0.325F,  1.025F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	   0.1F,  0.375F,  1.025F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	   0.2F,  0.325F,  1.025F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // "-" button, left of point light intensity widget
	   0.2F,  0.325F,  1.005F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // - right side
	   0.2F,  0.375F,  1.025F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	   0.2F,  0.375F,  1.025F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	   0.2F,  0.325F,  1.005F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	   0.2F,  0.375F,  1.005F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	   0.1F,  0.325F,  1.005F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // "-" button, left of point light intensity widget
	   0.2F,  0.325F,  1.005F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // - bottom side
	   0.1F,  0.325F,  1.025F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	   0.1F,  0.325F,  1.025F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	   0.2F,  0.325F,  1.005F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	   0.2F,  0.325F,  1.025F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	   0.1F,  0.375F,  1.025F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // "-" button, left of point light intensity widget
	   0.2F,  0.375F,  1.025F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // - top side
	   0.1F,  0.375F,  1.005F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	   0.1F,  0.375F,  1.005F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	   0.2F,  0.375F,  1.025F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	   0.2F,  0.375F,  1.005F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	  0.12F,   0.35F,  1.027F,  0.0F,  0.0F,  1.0F,  1.0F,  1.0F,  1.0F, 1.0F, // line representing the "-" sign itself
	  0.18F,   0.35F,  1.027F,  0.0F,  0.0F,  1.0F,  1.0F,  1.0F,  1.0F, 1.0F, 
	 0.325F,    0.3F,  1.005F,  0.0F,  0.0F, -1.0F,  0.0F,  0.0F,  1.0F, 1.0F, // point light intensity widget
	 0.525F,    0.3F,  1.005F,  0.0F,  0.0F, -1.0F,  0.0F,  0.0F,  1.0F, 1.0F, // back side
	 0.325F,    0.4F,  1.005F,  0.0F,  0.0F, -1.0F,  0.0F,  0.0F,  1.0F, 1.0F, 
	 0.325F,    0.4F,  1.005F,  0.0F,  0.0F, -1.0F,  0.0F,  0.0F,  1.0F, 1.0F, 
	 0.525F,    0.3F,  1.005F,  0.0F,  0.0F, -1.0F,  0.0F,  0.0F,  1.0F, 1.0F, 
	 0.525F,    0.4F,  1.005F,  0.0F,  0.0F, -1.0F,  0.0F,  0.0F,  1.0F, 1.0F, 
	 0.325F,    0.3F,  1.025F,  0.0F,  0.0F,  1.0F,  0.0F,  0.0F,  1.0F, 1.0F, // point light intensity widget
	 0.525F,    0.3F,  1.025F,  0.0F,  0.0F,  1.0F,  0.0F,  0.0F,  1.0F, 1.0F, // - front side
	 0.325F,    0.4F,  1.025F,  0.0F,  0.0F,  1.0F,  0.0F,  0.0F,  1.0F, 1.0F, 
	 0.325F,    0.4F,  1.025F,  0.0F,  0.0F,  1.0F,  0.0F,  0.0F,  1.0F, 1.0F, 
	 0.525F,    0.3F,  1.025F,  0.0F,  0.0F,  1.0F,  0.0F,  0.0F,  1.0F, 1.0F, 
	 0.525F,    0.4F,  1.025F,  0.0F,  0.0F,  1.0F,  0.0F,  0.0F,  1.0F, 1.0F, 
	 0.325F,    0.3F,  1.005F, -1.0F,  0.0F,  0.0F,  0.0F,  0.0F,  1.0F, 1.0F, // point light intensity widget
	 0.325F,    0.3F,  1.025F, -1.0F,  0.0F,  0.0F,  0.0F,  0.0F,  1.0F, 1.0F, // - left side
	 0.325F,    0.4F,  1.005F, -1.0F,  0.0F,  0.0F,  0.0F,  0.0F,  1.0F, 1.0F, 
	 0.325F,    0.4F,  1.005F, -1.0F,  0.0F,  0.0F,  0.0F,  0.0F,  1.0F, 1.0F, 
	 0.325F,    0.3F,  1.025F, -1.0F,  0.0F,  0.0F,  0.0F,  0.0F,  1.0F, 1.0F, 
	 0.325F,    0.4F,  1.025F, -1.0F,  0.0F,  0.0F,  0.0F,  0.0F,  1.0F, 1.0F, 
	 0.525F,    0.3F,  1.025F,  1.0F,  0.0F,  0.0F,  0.0F,  0.0F,  1.0F, 1.0F, // point light intensity widget
	 0.525F,    0.3F,  1.005F,  1.0F,  0.0F,  0.0F,  0.0F,  0.0F,  1.0F, 1.0F, // - right side
	 0.525F,    0.4F,  1.025F,  1.0F,  0.0F,  0.0F,  0.0F,  0.0F,  1.0F, 1.0F, 
	 0.525F,    0.4F,  1.025F,  1.0F,  0.0F,  0.0F,  0.0F,  0.0F,  1.0F, 1.0F, 
	 0.525F,    0.3F,  1.005F,  1.0F,  0.0F,  0.0F,  0.0F,  0.0F,  1.0F, 1.0F, 
	 0.525F,    0.4F,  1.005F,  1.0F,  0.0F,  0.0F,  0.0F,  0.0F,  1.0F, 1.0F, 
	 0.525F,    0.3F,  1.005F,  0.0F, -1.0F,  0.0F,  0.0F,  0.0F,  1.0F, 1.0F, // point light intensity widget
	 0.325F,    0.3F,  1.005F,  0.0F, -1.0F,  0.0F,  0.0F,  0.0F,  1.0F, 1.0F, // - bottom side
	 0.525F,    0.3F,  1.025F,  0.0F, -1.0F,  0.0F,  0.0F,  0.0F,  1.0F, 1.0F, 
	 0.525F,    0.3F,  1.025F,  0.0F, -1.0F,  0.0F,  0.0F,  0.0F,  1.0F, 1.0F, 
	 0.325F,    0.3F,  1.005F,  0.0F, -1.0F,  0.0F,  0.0F,  0.0F,  1.0F, 1.0F, 
	 0.325F,    0.3F,  1.025F,  0.0F, -1.0F,  0.0F,  0.0F,  0.0F,  1.0F, 1.0F, 
	 0.325F,    0.4F,  1.025F,  0.0F,  1.0F,  0.0F,  0.0F,  0.0F,  1.0F, 1.0F, // point light intensity widget
	 0.525F,    0.4F,  1.025F,  0.0F,  1.0F,  0.0F,  0.0F,  0.0F,  1.0F, 1.0F, // - top side
	 0.325F,    0.4F,  1.005F,  0.0F,  1.0F,  0.0F,  0.0F,  0.0F,  1.0F, 1.0F, 
	 0.325F,    0.4F,  1.005F,  0.0F,  1.0F,  0.0F,  0.0F,  0.0F,  1.0F, 1.0F, 
	 0.525F,    0.4F,  1.025F,  0.0F,  1.0F,  0.0F,  0.0F,  0.0F,  1.0F, 1.0F, 
	 0.525F,    0.4F,  1.005F,  0.0F,  1.0F,  0.0F,  0.0F,  0.0F,  1.0F, 1.0F, 
	  0.65F,  0.325F,  1.005F,  0.0F,  0.0F, -1.0F, 0.75F, 0.75F, 0.75F, 1.0F, // "+" button, right of point light intensity widget
	  0.75F,  0.325F,  1.005F,  0.0F,  0.0F, -1.0F, 0.75F, 0.75F, 0.75F, 1.0F, // - back side
	  0.65F,  0.375F,  1.005F,  0.0F,  0.0F, -1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	  0.65F,  0.375F,  1.005F,  0.0F,  0.0F, -1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	  0.75F,  0.325F,  1.005F,  0.0F,  0.0F, -1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	  0.75F,  0.375F,  1.005F,  0.0F,  0.0F, -1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	  0.65F,  0.325F,  1.025F,  0.0F,  0.0F,  1.0F, 0.75F, 0.75F, 0.75F, 1.0F, // "+" button, right of point light intensity widget
	  0.75F,  0.325F,  1.025F,  0.0F,  0.0F,  1.0F, 0.75F, 0.75F, 0.75F, 1.0F, // - front side
	  0.65F,  0.375F,  1.025F,  0.0F,  0.0F,  1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	  0.65F,  0.375F,  1.025F,  0.0F,  0.0F,  1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	  0.75F,  0.325F,  1.025F,  0.0F,  0.0F,  1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	  0.75F,  0.375F,  1.025F,  0.0F,  0.0F,  1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	  0.65F,  0.325F,  1.005F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // "+" button, right of point light intensity widget
	  0.65F,  0.325F,  1.025F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // - left side
	  0.65F,  0.375F,  1.005F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	  0.65F,  0.375F,  1.005F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	  0.65F,  0.325F,  1.025F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	  0.65F,  0.375F,  1.025F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	  0.75F,  0.325F,  1.025F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // "+" button, right of point light intensity widget
	  0.75F,  0.325F,  1.005F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // - right side
	  0.75F,  0.375F,  1.025F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	  0.75F,  0.375F,  1.025F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	  0.75F,  0.325F,  1.005F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	  0.75F,  0.375F,  1.005F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	  0.65F,  0.325F,  1.005F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // "+" button, right of point light intensity widget
	  0.75F,  0.325F,  1.005F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // - bottom side
	  0.65F,  0.325F,  1.025F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	  0.65F,  0.325F,  1.025F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	  0.75F,  0.325F,  1.005F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	  0.75F,  0.325F,  1.025F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	  0.65F,  0.375F,  1.025F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // "+" button, right of point light intensity widget
	  0.75F,  0.375F,  1.025F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // - top side
	  0.65F,  0.375F,  1.005F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	  0.65F,  0.375F,  1.005F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	  0.75F,  0.375F,  1.025F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	  0.75F,  0.375F,  1.005F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
	  0.67F,   0.35F,  1.027F,  0.0F,  0.0F,  1.0F,  1.0F,  1.0F,  1.0F, 1.0F, // lines representing the "+" sign itself
	  0.73F,   0.35F,  1.027F,  0.0F,  0.0F,  1.0F,  1.0F,  1.0F,  1.0F, 1.0F, 
	   0.7F,  0.335F,  1.027F,  0.0F,  0.0F,  1.0F,  1.0F,  1.0F,  1.0F, 1.0F, 
	   0.7F,  0.365F,  1.027F,  0.0F,  0.0F,  1.0F,  1.0F,  1.0F,  1.0F, 1.0F
};

float verticesOfLightSourceInsideRefrigerator[108U] = {
	// position
	  -0.7F, 0.5F, -1.095F, // - back side
	   0.7F, 0.5F, -1.095F, 
	  -0.7F, 0.7F, -1.095F, 
	  -0.7F, 0.7F, -1.095F, 
	   0.7F, 0.5F, -1.095F, 
	   0.7F, 0.7F, -1.095F, 
	  -0.7F, 0.5F, -0.995F, // - front side
	   0.7F, 0.5F, -0.995F, 
	  -0.7F, 0.7F, -0.995F, 
	  -0.7F, 0.7F, -0.995F, 
	   0.7F, 0.5F, -0.995F, 
	   0.7F, 0.7F, -0.995F, 
	  -0.7F, 0.5F, -1.095F, // - left side
	  -0.7F, 0.5F, -0.995F, 
	  -0.7F, 0.7F, -1.095F, 
	  -0.7F, 0.7F, -1.095F, 
	  -0.7F, 0.5F, -0.995F, 
	  -0.7F, 0.7F, -0.995F, 
	   0.7F, 0.5F, -0.995F, // - right side
	   0.7F, 0.5F, -1.095F, 
	   0.7F, 0.7F, -0.995F, 
	   0.7F, 0.7F, -0.995F, 
	   0.7F, 0.5F, -1.095F, 
	   0.7F, 0.7F, -1.095F, 
	  -0.7F, 0.5F, -1.095F, // - bottom side
	   0.7F, 0.5F, -1.095F, 
	  -0.7F, 0.5F, -0.995F, 
	  -0.7F, 0.5F, -0.995F, 
	   0.7F, 0.5F, -1.095F, 
	   0.7F, 0.5F, -0.995F, 
	  -0.7F, 0.7F, -0.995F, // - top side
	   0.7F, 0.7F, -0.995F, 
	  -0.7F, 0.7F, -1.095F, 
	  -0.7F, 0.7F, -1.095F, 
	   0.7F, 0.7F, -0.995F, 
	   0.7F, 0.7F, -1.095F
};
