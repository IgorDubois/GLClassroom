//
//  main.cpp
//  Lab8.2
//
//  Created by Hippolyte Dubois on 22/03/17.
//  Copyright © 2017 Hippolyte Dubois. All rights reserved.
//

#ifdef __APPLE__
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#else
#include <gl\glut.h>
#endif

#include	"main.h"
#include	"CDrawModel.hpp"
#include	<iostream>

CDrawModel	mModel;



int main(int argc, char **argv) {
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize( 1000, 600 );
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Hippolyte Dubois 1614197");
    glEnable(GL_DEPTH_TEST);	// enable the depth buffer test
    
    // Setup callbacks
    glutDisplayFunc(DrawGLScene);
    glutReshapeFunc(ReSizeGLScene);
    
    glutKeyboardFunc(KeyResponse);
    //glutSpecialFunc(SpecialKey);
    glutIdleFunc(Idle);
    
    mModel.initGL();
    
    glutMainLoop();
}

void DrawGLScene(void) {
    mModel.myDrawGLScene();
}

GLvoid KeyResponse(unsigned char key, int x, int y) {
    mModel.myKeyResponder(key, x, y);
}

void SpecialKey(unsigned char key, int x, int y) {
    mModel.specialKeyResponder(key, x, y);
}

void Idle(void) {
    mModel.myIdle();
}

GLvoid ReSizeGLScene(GLsizei fwidth, GLsizei fheight) {
    mModel.MyReSizeGLScene(fwidth, fheight);
}

