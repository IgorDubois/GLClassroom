//
//  CPolygonMesh.hpp
//  Lab8.2
//
//  Created by Hippolyte Dubois on 22/03/17.
//  Copyright © 2017 Hippolyte Dubois. All rights reserved.
//

#pragma once

#ifdef __APPLE__
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#else
#include <gl\glut.h>
#endif

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <exception>
#include <new> // bad_alloc class is defined here

#include "Point.hpp"
using namespace std;


#undef near
#undef far

enum DisplayMode {	VERTEXNORMAL = 1,
    FACENORMAL,
    WIREFRAME
};

typedef float colour[3];  // RGB colour

class CPolygonMesh {
private:
    int				Mesh_NumFaces;		// number of faces in polygon mesh model
    point			*vertex_list;		// list of vertex coordinates
    point_triplet	*face_list;			// list of faces defined in terms of vertices
    
    point			*face_normal_list;
    point			*vertex_normal_list;
    bool			*valid_normal_flag;
    
    int				Mesh_NumVertex;		// number of vertices in polygon mesh model
    int				Mesh_NumEdges;		// number of edges
    point_pair		*edge_list;			// list of edges, each defined by a pair of points
    
    
    void			read_model_data(char buffer[120]);	// read in model values from file
    void			readUntil(ifstream *inStream, char *target);
    
public:
    CPolygonMesh(char dataFile[120]);
    
    GLenum          mode = GL_TRIANGLES;
    void draw_model(DisplayMode);
    void draw_model_textured(DisplayMode);
    
};

