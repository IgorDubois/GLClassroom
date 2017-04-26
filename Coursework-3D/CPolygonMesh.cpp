//
//  CPolygonMesh.cpp
//  Lab8.2
//
//  Created by Hippolyte Dubois on 22/03/17.
//  Copyright © 2017 Hippolyte Dubois. All rights reserved.
//


#include "CPolygonMesh.hpp"

// Print lots of info when reading in model
bool debugPolygons = false;

colour colour_array[] =
{
    {0.0, 0.0, 0.0},
    {1.0, 0.0, 0.0},
    {0.0, 1.0, 0.0},
    {0.0, 0.0, 1.0},
    {1.0, 1.0, 0.0},
    {1.0, 0.0, 1.0},
    {0.0, 1.0, 1.0},
    {0.7, 0.7, 0.7}
};

// model constructor
CPolygonMesh::CPolygonMesh(char dataFile[120]) {
    read_model_data(dataFile);
}

void CPolygonMesh::draw_model(DisplayMode dMode) {
    
    // Choose seed for rand() based on current time (seconds).
    srand(time(NULL));
    switch (dMode) {
            
            // Both VERTEXNORMAL AND FACENORMAL draw the same polygons.
            // The only difference is the normals associated with the vertices.
        case VERTEXNORMAL:
            
            glBegin(GL_TRIANGLES);
            
            for (int i = 0; i < Mesh_NumFaces; i++) {
                
                // Provide colours when lighting is not enabled
                glColor3f(1.F, 1.F, 1.F);
                
                glNormal3fv(vertex_normal_list[ face_list[i][0] ]);
                glVertex3fv(vertex_list[face_list[i][0]]);
                
                glNormal3fv(vertex_normal_list[ face_list[i][1] ]);
                glVertex3fv(vertex_list[face_list[i][1]]);
                
                glNormal3fv(vertex_normal_list[ face_list[i][2] ]);
                glVertex3fv(vertex_list[face_list[i][2]]);
            }
            
            glEnd();
            break; // end VERTEXNORMAL case
            
        case FACENORMAL:
            glBegin(GL_TRIANGLES);
            
            for (int i = 0; i < Mesh_NumFaces; i++) {
                
                // Use face normal for all vertices on this face
                glNormal3fv(face_normal_list[i]);
                
                // Provide colours when lighting is not enabled
                glColor3f(1.F, 1.F, 1.F);

                
                glVertex3fv(vertex_list[face_list[i][0]]);
                glVertex3fv(vertex_list[face_list[i][1]]);
                glVertex3fv(vertex_list[face_list[i][2]]);
            }
            
            glEnd();
            break;  // end FACENORMAL case
            
        case WIREFRAME:
            glBegin(GL_LINES);
            
            for (int i = 0; i < Mesh_NumEdges; i++) {
                glVertex3fv(vertex_list[edge_list[i][0]]);
                glVertex3fv(vertex_list[edge_list[i][1]]);
            }
            
            glEnd();
            
            break; // end VIREFRAME case
    } // End switch dMode
}


void CPolygonMesh::draw_model_textured(DisplayMode dMode) {
    
    for (int i = 0 ; i < 10; i++){
        std::cout << i << " " << vertex_list[i][0] << std::endl;
    }
            
//    glBegin(GL_QUADS);
//    
//    for (int i = 0; i < Mesh_NumFaces; i++) {
//        
//        glTexCoord2f(0, 0);
//        glNormal3fv(vertex_normal_list[ face_list[i][0] ]);
//        glVertex3fv(vertex_list[face_list[i][0]]);
//        
//        glTexCoord2f(1.0, 0.F);
//        glNormal3fv(vertex_normal_list[ face_list[i][1] ]);
//        glVertex3fv(vertex_list[face_list[i][1]]);
//        
//        glTexCoord2f(1.0, 1.0);
//        glNormal3fv(vertex_normal_list[ face_list[i][2] ]);
//        glVertex3fv(vertex_list[face_list[i][2]]);
//        
//    }
//    
//    glEnd();
}



// Read in a model
void CPolygonMesh::read_model_data(char datafile[])	{
    
    string separator;
    
    ostringstream errorString;
    
    ifstream inDatastream(datafile, ios::in);
    
    if (! inDatastream) {
        errorString << "Can't open file " << datafile << " for reading.";
        exit(1);
    }
    
    cout << "Reading from file: " << datafile << endl;
    
    readUntil(&inDatastream, "*MESH_NUMVERTEX");
    inDatastream >> Mesh_NumVertex;
    cout << "There are " << Mesh_NumVertex << " vertices" << endl;
    
    readUntil(&inDatastream, "*MESH_NUMFACES");
    inDatastream >> Mesh_NumFaces;
    cout << "There are " << Mesh_NumFaces << " faces" << endl;
    
    try {
        // Allocate memory for Polygon Mesh data structures
        vertex_list = new point[Mesh_NumVertex];
        face_list = new point_triplet[Mesh_NumFaces];
        edge_list = new point_pair[3 * Mesh_NumFaces];
        
        valid_normal_flag = new bool[Mesh_NumVertex];
        // Each face has one normal, which require 3 coordinates
        face_normal_list = new point[Mesh_NumFaces];
        // Each vertex has one normal, which require 3 coordinates
        vertex_normal_list = new point[Mesh_NumVertex];
    }
    catch (bad_alloc &memoryAllocationException) {
        cerr << "Exception occurred: "
        << memoryAllocationException.what() << endl;
        exit(1);
    }
    
    readUntil(&inDatastream, "*MESH_VERTEX_LIST");
    
    inDatastream >> separator; // Read the "{"
    
    for (int vertex = 0; vertex < Mesh_NumVertex; vertex++) {
        int vertex_number;
        readUntil(&inDatastream, "*MESH_VERTEX");
        
        inDatastream >> vertex_number;
        inDatastream	>>	vertex_list[vertex_number][0]
        >>	vertex_list[vertex_number][1]
        >>	vertex_list[vertex_number][2];
        if(debugPolygons)
        cout << "Vertex: " << vertex_number  << "("
        <<	vertex_list[vertex_number][0] << ", "
        <<	vertex_list[vertex_number][1] << ", "
        <<	vertex_list[vertex_number][2] << ")" << endl;
    }  // end of loop through vertices
    
    
    int edge_number = 0;
    for (int face = 0; face < Mesh_NumFaces; face++) {	// read in faces and edges
        int face_number;
        
        readUntil(&inDatastream, "*MESH_FACE");
        
        inDatastream >> face_number;
        
        inDatastream >> separator >> separator; // ":  A:"
        inDatastream	>> face_list[face_number][0]	>> separator  // "B: "
        >> face_list[face_number][1]	>> separator  // "C: "
        >> face_list[face_number][2];
        if(debugPolygons)
        cout << "Face: " << face_number  << "("
        <<	face_list[face_number][0] << ", "
        <<	face_list[face_number][1] << ", "
        <<	face_list[face_number][2] << ")" << endl;
        
        
        // first edge, first point
        edge_list[edge_number][0]   = face_list[face_number][0];
        // first edge, 2nd point
        edge_list[edge_number][1]   = face_list[face_number][1];
        
        edge_number++;	// move to next edge
        
        // second edge, first point
        edge_list[edge_number][0]   = face_list[face_number][1];
        // second edge, 2nd point
        edge_list[edge_number][1]   = face_list[face_number][2];
        
        edge_number++;	// move to next edge
        
        // third edge, first point
        edge_list[edge_number][0]   = face_list[face_number][2];
        // third edge, 2nd point
        edge_list[edge_number][1]   = face_list[face_number][0];
        
        edge_number++;
    } // End of loop through Mesh_NumFaces
    
    Mesh_NumEdges = edge_number;
    cout << "Number of edges: " << Mesh_NumEdges << endl;
    
    readUntil(&inDatastream, "*MESH_NORMALS");
    
    
    // Initially we haven't read in normals for any of the vertices, so they're undefined.
    for (int vertex = 0; vertex < Mesh_NumVertex; vertex++) {
        valid_normal_flag[vertex] = false;
    }
    
    // Each face has a normal at each vertex, so the data in the 3dsMAX file is very redundant.
    // We assume that any given vertex has the SAME vertex normal
    // in each of its faces.
    for (int face = 0; face < Mesh_NumFaces; face++) {
        int face_normal_number; // Number of face (not number of the normal) PROBABLY = loop var
								// but we'll use value from the file just in case
        
        readUntil(&inDatastream, "*MESH_FACENORMAL");
        
        inDatastream >> face_normal_number;  // Index of the face whose normals we're about to read
        
        inDatastream	>> face_normal_list[face_normal_number][0]
        >> face_normal_list[face_normal_number][1]
        >> face_normal_list[face_normal_number][2];
        
        if (debugPolygons) {
            cout	<< "Face: " << face_normal_number << " N( "
            << face_normal_list[face_normal_number][0] << ", "
            << face_normal_list[face_normal_number][1] << ", "
            << face_normal_list[face_normal_number][2] << " )" << endl;
        }
        
        
        // Each face has three corners
        for (int cornerNo = 0; cornerNo < 3; cornerNo++) {
            point vertexNormal;
            int vertex_index;
            readUntil(&inDatastream, "*MESH_VERTEXNORMAL");
            
            inDatastream >> vertex_index;  // The index of the vertex whose normal we're reading
            
            // Store normal data separately, in case we want to check it
            // before storing it in vertex_normal_list.
            inDatastream	>> vertexNormal[0]
            >> vertexNormal[1]
            >> vertexNormal[2];
            
            // Now store the normal in vertex_normal_list.
            // If we've encountered this vertex before as part of another face
            // then the normal will already be present in vertex_normal_list.
            // At the moment we just overwrite the old value (which hopefully was the same
            // as the new value).
            vertex_normal_list[vertex_index][0] = vertexNormal[0];
            vertex_normal_list[vertex_index][1] = vertexNormal[1];
            vertex_normal_list[vertex_index][2] = vertexNormal[2];
            
            // Note that the list now contains a normal for this vertex
            valid_normal_flag[vertex_index] = true;
            
            if (debugPolygons) {
                cout	<< "Vertex: " << vertex_index << " N( "
                << vertex_normal_list[vertex_index][0] << ", "
                << vertex_normal_list[vertex_index][1] << ", "
                << vertex_normal_list[vertex_index][2] << " )" << endl;
            }
            
        } // End of loop through 3 vertices
        
    } // End of normal-reading loop through faces
    
    // Check that every vertex has a vertex normal
    for (int vertex = 0; vertex < Mesh_NumVertex; vertex++) {
        if (! valid_normal_flag[vertex])
            cerr << "Vertex " << vertex << ": No normal defined!" << endl;
    }
}



void CPolygonMesh::readUntil(ifstream *inStream, char *target) {
    string word;
    *inStream >> word;
    while (word.compare(target)){
        *inStream >> word;
    }
    if(debugPolygons)
        cout << "Found " << target << endl;
}
