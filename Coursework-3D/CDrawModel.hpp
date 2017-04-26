//
//  CDrawModel.hpp
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

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <fstream>

#include "CPolygonMesh.hpp"

#undef near
#undef far

using namespace std;

#define PI      3.14159
#define SIZE    512
#define NUMOBJECTS 2

// Structure to hold all the properties of a material
struct materialStruct {
    GLfloat diffuse[4];
    GLfloat specular[4];
    GLfloat ambient[4];
    GLfloat emission[4];
    GLfloat shininess;
};


class CDrawModel
{
private:
    double fovy;			// field of view in y direction
    double aspect_ratio;	// aspect ratio of our viewport
    double near;			// near, far clip planes for camera
    double far;
    double height;			// height of camera view at near clip plane
    
    int wWidth, wHeight;
    
    int dragging;
    float fan_theta[4];
    float fan_speed[4] = {2.F, 1.5F, -.75F, 10.F};
    
    float cameraY = 0.F;
    float cameraZ = 1.F;
    
    int camPos = 0;
    int nCamPos = 4;
    
    float fov0, fov1, fov2;
    
    void myCreateLights(void);
    void assignMaterial( materialStruct *material );
    void addLightMarkers(void);
    
    // DISPLAY LIST
    GLuint displayLists;
    void buildLists(void);
    void constructRoom(DisplayMode mode);
    void drawFloor();
    void processHits(GLint hits, GLuint buffer[]);
    
    //TEXTURES
    BITMAPFILEHEADER file_header;
    BITMAPINFOHEADER info_header;
    GLubyte checker_texture[512][512][3];
    GLuint myTextures[5];
    bool textureLoad(char *filename);
    void textureRelease(void);
    char* texture_file = "/Users/hippolytedubois/Documents/RGU/CM3056/Labs/Coursework-3D/checker_texture.PNG";
    bool use_texture = false;
    
public:
    void initGL(void);
    void MyReSizeGLScene(int fwidth, int fheight);
    void myDrawGLScene(GLvoid);
    void myDrawModel(int list);
    void myIdle(GLvoid);
    void myKeyResponder(unsigned char key, int x, int y);
    void specialKeyResponder(unsigned char k, int x, int y);
    
    void mySphereRow();
    
};

