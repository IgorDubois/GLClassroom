//
//  main.h
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

void DrawGLScene(GLvoid);
void Idle(GLvoid);

void ReSizeGLScene(GLsizei fwidth, GLsizei fheight);

GLvoid KeyResponse(unsigned char key, int x, int y);
void SpecialKey(unsigned char key, int x, int y);


