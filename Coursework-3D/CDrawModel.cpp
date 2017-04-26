//
//  CDrawModel.cpp
//  Lab8.2
//
//  Created by Hippolyte Dubois on 22/03/17.
//  Copyright © 2017 Hippolyte Dubois. All rights reserved.
//

#include "CDrawModel.hpp"
#include "CPolygonMesh.hpp"
#include <stdlib.h>
#include <unistd.h>

#define RED 0
#define GREEN 1
#define BLUE 2
#define WHITE 3
#define BLACK 4

void lightToggle(int);
void errorCheck(string Place);

#ifdef __APPLE__
CPolygonMesh sphere ("/Users/hippolytedubois/Documents/RGU/CM3056/geosphere.txt");
CPolygonMesh chair  ("/Users/hippolytedubois/Documents/RGU/CM3056/Labs/Coursework-3D/Coursework-3D/models/chair.txt");
CPolygonMesh fan    ("/Users/hippolytedubois/Documents/RGU/CM3056/Labs/Coursework-3D/Coursework-3D/models/fan.txt");
CPolygonMesh floor_ ("/Users/hippolytedubois/Documents/RGU/CM3056/Labs/Coursework-3D/Coursework-3D/models/floor.txt");
CPolygonMesh table  ("/Users/hippolytedubois/Documents/RGU/CM3056/Labs/Coursework-3D/Coursework-3D/models/table.txt");
CPolygonMesh wallfb ("/Users/hippolytedubois/Documents/RGU/CM3056/Labs/Coursework-3D/Coursework-3D/models/wallfb.txt");
CPolygonMesh wallrl ("/Users/hippolytedubois/Documents/RGU/CM3056/Labs/Coursework-3D/Coursework-3D/models/wallrl.txt");
#else
CPolygonMesh sphere ("/Users/hippolytedubois/Documents/RGU/CM3056/geosphere.txt");
CPolygonMesh chair  ("/Users/hippolytedubois/Documents/RGU/CM3056/Labs/Coursework-3D/Coursework-3D/models/chair.txt");
CPolygonMesh fan    ("/Users/hippolytedubois/Documents/RGU/CM3056/Labs/Coursework-3D/Coursework-3D/models/fan.txt");
CPolygonMesh floor_ ("/Users/hippolytedubois/Documents/RGU/CM3056/Labs/Coursework-3D/Coursework-3D/models/floor.txt");
CPolygonMesh table  ("/Users/hippolytedubois/Documents/RGU/CM3056/Labs/Coursework-3D/Coursework-3D/models/table.txt");
CPolygonMesh wallfb ("/Users/hippolytedubois/Documents/RGU/CM3056/Labs/Coursework-3D/Coursework-3D/models/wallfb.txt");
CPolygonMesh wallrl ("/Users/hippolytedubois/Documents/RGU/CM3056/Labs/Coursework-3D/Coursework-3D/models/wallrl.txt");
#endif


float  colours[5][3] =
{	{1.0, 0.0, 0.0},
    {0.0, 1.0, 0.0},
    {0.0, 0.0, 1.0},
    {1.0, 1.0, 1.0},
    {0.0, 0.0, 0.0}
};


void animateObject(void);
void mySphereRow();

float theta = 0.0;
float deltaTheta = 0.04;
bool animateP = false;

unsigned char *imageData;

GLfloat light0_pos[] =	{-20.0, 100.0, 0, 1.0};
GLfloat diffuse0[] =	{1.0, 0.0, 0.0, 1.0};
GLfloat specular0[] =	{1.0, 0.0, 0.0, 1.0};

GLfloat light1_pos[] =	{0.0, 100.0, 0, 1.0};
GLfloat diffuse1[] =	{0.0, 1.0, 0.0, 1.0};
GLfloat specular1[] =	{0.0, 1.0, 0.0, 1.0};

GLfloat light2_pos[] =	{20.0, -50.0, 0, 1.0};
GLfloat diffuse2[] =	{0.0, 0.0, 1.0, 1.0};
GLfloat specular2[] =	{0.0, 0.0, 1.0, 1.0};

GLfloat light3_pos[] =	{80.0, -50.0, 0, 1.0};
GLfloat diffuse3[] =	{0.0, 1.0, 1.0, 1.0};
GLfloat specular3[] =	{1.0, 0.0, 1.0, 1.0};

GLfloat spot_pos[] =    {80.F, -50.F, 1000.F, 1.F};
GLfloat spot_dir[] =    {0.F, 0.F, -10.F};
GLfloat spot_diffuse[] ={1.0, 1.0, 1.0, 1.F};
GLfloat spot_exponent = 100.F;
GLfloat spot_cutoff =   10.0f;


GLfloat global_ambient[] = {0.01F, 0.01F, 0.05F};

materialStruct redMaterial =
{
    {1.0, .2F, .2F, 1.0},	// Diffuse reflectivity
    {1.0, 1.0, 1.0, 1.0},	// Specular reflectivity
    {1.0, 0.0, 0.0, 1.0},	// Ambient reflectivity
    {0.0, 0.0, 0.0, 1.0},   // Emissive light
    20.0					// Shininess
};

materialStruct reddishMaterial =
{
    {1.0, .5F, .5F, 1.0},	// Diffuse reflectivity
    {1.0, 1.0, 1.0, 1.0},	// Specular reflectivity
    {1.0, .0F, .0F, 1.0},	// Ambient reflectivity
    {0.0, 0.0, 0.0, 1.0},   // Emissive light
    80.0					// Shininess
};

materialStruct greenMaterial =
{
    {0.0, 1.0, 0.0, 1.0},	// Diffuse reflectivity
    {1.0, 1.0, 1.0, 1.0},	// Specular reflectivity
    {0.0, 1.0, 0.0, 1.0},	// Ambient reflectivity
    {0.0, 0.0, 0.0, 1.0},   // Emissive light
    40.0					// Shininess
};

materialStruct blueMaterial =
{
    {0.8F, .8F, 1.0, 1.0},	// Diffuse reflectivity
    {1.0, 1.0, 1.0, 1.0},	// Specular reflectivity
    {0.0, 0.0, 1.0, 1.0},	// Ambient reflectivity
    {0.0, 0.0, 0.0, 1.0},   // Emissive light
    40.0					// Shininess
};

materialStruct whiteMaterial =
{
    {1.0, 1.0, 1.0, 1.0},	// Diffuse reflectivity
    {1.0, 1.0, 1.0, 1.0},	// Specular reflectivity
    {1.0, 1.0, 1.0, 1.0},	// Ambient reflectivity
    {0.0, 0.0, 0.0, 1.0},   // Emissive light
    40.0					// Shininess
};


void CDrawModel::initGL(void) {
    
    textureLoad(texture_file);
    
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
    glClearColor(51.F / 255.F, 51.F / 255.F, 51.F / 255.F, 1.0);
    glEnable(GL_DEPTH);
    
    near = 0.1;
    far = 50000.0;
    height = 1.5;
    
    fov0 = 60;
    fov1 = 45;
    fov2 = 30;
    
    cameraZ = -1.47;
    
    myCreateLights();
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    
    
    
    buildLists();
    
}

//  Use for animations if required
void CDrawModel::myIdle(void) {
    for(int i = 0 ; i < 4 ; i++){
        fan_theta[i] += fan_speed[i];
        //fan_theta[i] = float(int(fan_theta[i]) % 360);
    }
    spot_pos[0] -= 1.F;
    glutPostRedisplay();
}


void CDrawModel::MyReSizeGLScene(int fwidth, int fheight)
{
    // Store window size so it can be accessed in myDrawGLScene()
    wWidth = fwidth;
    wHeight = fheight;
    
    // 	Calculate the aspect ratio of the VIEWPORT
    // 	so that we can set the camera�s aspect ratio to the same value
    aspect_ratio = (double) fwidth / (double) fheight;
    
    glMatrixMode(GL_PROJECTION);					// Select The Projection Stack
    glLoadIdentity();
    
    
    
    /*
     // Print values of parameters
     cout << fixed;		// Use fixed-point notation
     cout.precision(3);	// Number of digits after the decimal point
     
     cout << "fovy = " << fovy << endl;
     cout << "aspect_ratio = " << aspect_ratio << endl;
     cout << "near = " << near << endl;
     cout << "far = " << far << endl;
     */
    
}

void CDrawModel::myDrawGLScene(GLvoid)		// Here's Where We Do All The Drawing
{
    std::cout << "Start of myDrawGLScene" << std::endl;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// clear the drawing area
    glEnable(GL_SCISSOR_TEST);
    
    // LEFT VIEWPORT - PERSPECTIVE //
    glMatrixMode(GL_PROJECTION);					// Select The Projection Stack
    glLoadIdentity();
    glScissor(0, 0, wWidth/2, wHeight);
    glEnable(GL_SCISSOR_TEST);
    glEnable(GL_LIGHTING);
    switch (camPos) {
        case 0:
            fovy = fov0;
            break;
        case 1:
            fovy = fov1;
            break;
        case 2:
            fovy = fov2;
            break;
        case 3:
            fovy = fov1;
            break;
            
        default:
            fovy = 90;
            break;
    }									// Override the calculated value
    gluPerspective(fovy, aspect_ratio/2, near, far);  // perspective view
    glViewport(0, 0, wWidth / 2, wHeight);				// Viewport fills the window
    glClearDepth(1.0);
    glClearColor(0.1, 0.1, 0.1, 1.F);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glTranslatef(-100.F, 0.F, -800.F);
    myDrawModel(displayLists);
    glPopMatrix();
    
    
    // RIGHT VIEWPORT - WIREFRAME //
    glScissor(wWidth/2, 0, wWidth, wHeight);
    glEnable(GL_SCISSOR_TEST);
    glMatrixMode(GL_PROJECTION);					// Select The Projection Stack
    glLoadIdentity();
    glOrtho(-800.0, 800.0, -800.0, 800.0, -1000, 1000);
    glViewport(wWidth/2, 0, wWidth, wHeight);
    glClearDepth(1.0);
    glClearColor(0.1F, 0.1F, 0.3F, 1.F);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
        glTranslatef(-500.F, 0.F, -500.F);
        myDrawModel(displayLists +1);
    glPopMatrix();
    
    glDisable(GL_SCISSOR_TEST);
    
    glutSwapBuffers();				// Needed if we're running an animation
    glFlush();
    
    errorCheck("End of myDrawGLScene");
    std::cout << "End of myDrawGLScene" << std::endl;
}



void CDrawModel::myDrawModel(int list)
{
    
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    if(list == displayLists){
        
        switch (camPos) {
            case 0:
                gluLookAt(280.0, 0, cameraZ,  // Put camera at the origin
                          282.0, 0.0, -2.0,   // Look along the –ve z axi
                          0.0, 0.0, 1.0);   // The x axis is up

                break;
            case 1:
                gluLookAt(375.0, 0, 15,  // Put camera at the origin
                          380.0, -7.0, -2.0,   // Look along the –ve z axi
                          0.F, 0.F, 1.0);   // The x axis is up

                break;
            case 2:
                gluLookAt(280.0, -220, 150,  // Put camera at the origin
                          0.0, -200.0, -2.0,   // Look along the –ve z axi
                          0.0, 0.0, 1.0);   // The x axis is up

                break;
            case 3:
                gluLookAt(280, 0, 15,  // Put camera at the origin
                          282, 0, -2.0,   // Look along the –ve z axi
                          0.F, 0.F, 1.0);   // The x axis is up
                
                break;
                
            default:
                break;
        }
    } else {
        gluLookAt(0.0, 0.0, 0.0,  // Put camera at the origin
                  0.0, 0.0, -50.0,   // Look along the –ve z axi
                  1.0, 0.0, 0.0);   // The x axis is up
    }
    
    glCallList(list);
    
    //Draw the fans
    glPushAttrib(GL_LIGHTING_BIT);
    assignMaterial(&whiteMaterial);
    for(int i = 0 ; i < 2 ; i++){
        for(int j = 0 ; j < 2 ; j++){
            glPushMatrix();
            glRotatef(90, 1, 0, 0);
            glTranslatef(-200 + 400 * i, 200, 300 * j);
            float angle = fan_theta[i + j*2];
            glRotatef(angle, 0, 1, 0);
            fan.draw_model(list==displayLists?FACENORMAL:WIREFRAME);
            glPopMatrix();
        }
    }
    glPopAttrib();
    
    

}

void CDrawModel::buildLists(){
    displayLists = glGenLists(2);
    
    // LEFT SIDE LIST
    glNewList(displayLists, GL_COMPILE);
    glPushAttrib(GL_ENABLE_BIT);
    //glEnable(GL_LIGHTING);
    constructRoom(FACENORMAL);
    glPopAttrib();
    glEndList();
    
    // RIGHT SIDE LIST
    glNewList(displayLists + 1, GL_COMPILE);
    glPushAttrib(GL_ENABLE_BIT);
    glDisable(GL_LIGHTING);
    constructRoom(WIREFRAME);
    glPopAttrib();
    glEndList();
}

void CDrawModel::constructRoom(DisplayMode mode){
    
    glPushMatrix();
    glTranslatef(0, 0, -100);
    glRotatef(90, 1, 0, 0);
    
    //Draw 8 chairs, tables, and fans
    glPushAttrib(GL_LIGHTING_BIT);
    
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 2; j++){
            glPushMatrix();
            
            glTranslatef(-250.F + 220.F * i - 70.F * j, .0F, 20.F + 150.F * j);
            float angle = j==0?-60.F:15.F*i;
            glRotatef(angle, 0, 1, 0);
            if(mode != WIREFRAME)
                assignMaterial(&reddishMaterial);
            chair.draw_model(mode);
            
            glPushMatrix();
            
            glRotatef(90, 0, 1, 0);
            glScalef(1, 1.7, 1);
            glTranslatef(-170.F, 0.F, 20.F);
            if(mode != WIREFRAME)
                assignMaterial(&redMaterial);
            table.draw_model(mode);
            
            glPopMatrix();
            
            glPopMatrix();
        }
    }
    std::cout << ";" << std::endl;
    glPopAttrib();
    //end of chair, table, and fan
    
    
    //draw the walls and floor
    glPushMatrix();
    glTranslatef(0, 100, -100);
    
    //scale the room
    glScalef(2, 1, 1);
    
    
    //start of floor
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    if(mode != WIREFRAME)
        assignMaterial(&blueMaterial);
    glPushMatrix();
    if(use_texture) {
        //glTranslatef(0, -150, 0);
        if(mode != WIREFRAME){
            
            
            //Enable texturing
            glEnable(GL_TEXTURE_2D);
            // Assign names for 1 texture
            glGenTextures(1, myTextures);
            // Select the first texture
            glBindTexture(GL_TEXTURE_2D, myTextures[0]);
            // The following commands all apply to the first texture
            // Assign texture image
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 512, 512, 0,
                         GL_RGB, GL_UNSIGNED_BYTE, checker_texture);
            
            glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
            glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
            glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
            glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
            
            glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
            
            GLfloat planes[] = {1, 0.0, 0.0, 0.0};
            GLfloat planet[] = {0.0, 0.0, 1, 0.0};
            
            glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
            glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
            
            glTexGenfv(GL_S, GL_OBJECT_PLANE, planes);
            glTexGenfv(GL_T, GL_OBJECT_PLANE, planet);
            
            glEnable(GL_TEXTURE_GEN_S);
            glEnable(GL_TEXTURE_GEN_T);
            
            
            glBindTexture(GL_TEXTURE_2D, myTextures[0]);
            //floor_.draw_model(mode);
            glBegin(GL_QUADS);
            
            glTexCoord2f(0, 0);
            glVertex3f(100.F, 0.F, 100.F);
            
            glTexCoord2f(0, 512);
            glVertex3f(-100.F, 0.F, 100.F);
            
            glTexCoord2f(512, 0);
            glVertex3f(-100.F, 0.F, -100.F);
            
            glTexCoord2f(512, 512);
            glVertex3f(100.F, 0.F, -100.F);
            
            glEnd();
            errorCheck("TEXTURE DISPLAY");
            //glutSolidCube(100);
            
        } else {
            glutSolidCube(100);
            glBegin(GL_QUADS);
            
            glTexCoord2f(0, 0);
            glVertex3f(100.F, 100.F, 1.F);
            
            glTexCoord2f(0, 1);
            glVertex3f(-100.F, 100.F, 1.F);
            
            glTexCoord2f(1, 0);
            glVertex3f(-100.F, -100.F, 1.F);
            
            glTexCoord2f(1, 1);
            glVertex3f(100.F, -100.F, 1.F);
            
            glEnd();
            
        }
    } else {
        glTranslatef(-270, -150, -50);
        glScalef(0.1, 1, 0.1);
        for(int i = 0 ; i < 10 ; i++){
            glTranslatef(500, 0, 0);
            glPushMatrix();
            for(int j = 0 ; j < 10 ; j++){
                glTranslatef(0, 0, 500);
                if((i + j) % 2 == 0){
                    if(mode != WIREFRAME)
                        assignMaterial(&blueMaterial);
                } else {
                    if(mode != WIREFRAME)
                        assignMaterial(&whiteMaterial);
                }
                floor_.draw_model(mode);
            }
            glPopMatrix();
        }
    }
    glPopMatrix();
    glPopAttrib();
    //end of floor
    if(mode != WIREFRAME)
        assignMaterial(&whiteMaterial);
    //left and right walls
    wallfb.draw_model(mode);
    
    glPushMatrix();
    glTranslatef(.0F, .0F, 500.F);
    wallfb.draw_model(mode);
    glPopMatrix();
    //end of left and right walls
    
    //top and bottom walls
    glPushMatrix();
    glTranslatef(250, 0, 0);
    wallrl.draw_model(mode);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-250.F, .0F, 0.F);
    wallrl.draw_model(mode);
    glPopMatrix();
    //end of top and bottom walls
    
    glPopMatrix();
    //end of walls and floor
    
    glPopMatrix();
}

void lightToggle(int num){
    switch (num) {
        case 1:
            if (glIsEnabled(GL_LIGHT0)) {
                glDisable(GL_LIGHT0);
                std::cout << "Light 0 false" << std::endl;
            } else {
                glEnable(GL_LIGHT0);
                std::cout << "Light 0 true" << std::endl;
            }
            
            break;
        case 2:
            if (glIsEnabled(GL_LIGHT1)){
                glDisable(GL_LIGHT1);
                std::cout << "Light 1 false" << std::endl;
            } else {
                glEnable(GL_LIGHT1);
                std::cout << "Light 1 true" << std::endl;
            }
            break;
        case 3:
            if (glIsEnabled(GL_LIGHT2)){
                glDisable(GL_LIGHT2);
                std::cout << "Light 2 false" << std::endl;
            } else {
                glEnable(GL_LIGHT2);
                std::cout << "Light 2 true" << std::endl;
            }
            break;
        case 4:
            if (glIsEnabled(GL_LIGHT3)){
                glDisable(GL_LIGHT3);
                std::cout << "Light 3 false" << std::endl;
            } else {
                glEnable(GL_LIGHT3);
                std::cout << "Light 3 true" << std::endl;
            }
            break;
    }
    glutPostRedisplay();
}


void CDrawModel::addLightMarkers(void) {
    
    glColor3fv(colours[BLACK]);
    glPushMatrix();
    glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
    glTranslatef(light0_pos[0], light0_pos[1], light0_pos[2]);
    glutSolidIcosahedron();
    glPopMatrix();
    
    glPushMatrix();
    glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);
    glTranslatef(light1_pos[0], light1_pos[1], light1_pos[2]);
    glutSolidIcosahedron();
    glPopMatrix();
    
    glPushMatrix();
    glLightfv(GL_LIGHT2, GL_POSITION, light2_pos);
    glTranslatef(light2_pos[0], light2_pos[1], light2_pos[2]);
    glutSolidIcosahedron();
    glPopMatrix();
    glPopMatrix();
    
}
void CDrawModel::assignMaterial( materialStruct *material ) {
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material -> diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material -> specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material -> ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, material -> emission);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material -> shininess);
}

void CDrawModel::myCreateLights(void) {
    
    glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular0);
    
    glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular1);
    
    glLightfv(GL_LIGHT2, GL_POSITION, light2_pos);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse2);
    glLightfv(GL_LIGHT2, GL_SPECULAR, specular2);
    
    glLightfv(GL_LIGHT3, GL_POSITION, light3_pos);
    glLightfv(GL_LIGHT3, GL_DIFFUSE, diffuse3);
    glLightfv(GL_LIGHT3, GL_SPECULAR, specular3);
    
    glLightfv(GL_LIGHT4, GL_AMBIENT, global_ambient);
    
    glLightf(GL_LIGHT5,GL_SPOT_CUTOFF, spot_cutoff);
    glLightfv(GL_LIGHT5, GL_POSITION, spot_pos);
    glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION, spot_dir);
    glLightfv(GL_LIGHT5, GL_DIFFUSE, spot_diffuse);
    glLightf(GL_LIGHT5,GL_SPOT_EXPONENT, spot_exponent);
    
}

void  CDrawModel::myKeyResponder(unsigned char key, int x, int y) {
    //std::cout << key << std::endl;
    if(key == 27) {								// The ESC key
        glutDestroyWindow(glutGetWindow());		// kill the window
        exit(0);
    } else {
        if (key == 'd'){ // ambient lighting
            if (glIsEnabled(GL_LIGHT4)){
                glDisable(GL_LIGHT4);
                std::cout << "Ambient false" << std::endl;
            } else {
                glEnable(GL_LIGHT4);
                std::cout << "Ambient true" << std::endl;
            }
        }
        if (key == 's'){ // ambient lighting
            if (glIsEnabled(GL_LIGHT5)){
                glDisable(GL_LIGHT5);
                std::cout << "Spot false" << std::endl;
            } else {
                glEnable(GL_LIGHT5);
                std::cout << "Spot true" << std::endl;
            }
        }
        if (key == 'l') // Local viewpoint
            glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
        if (key == '+')
            camPos = (camPos + 1) % nCamPos;
        if (key == 'z'){
            switch (camPos) {
                case 0:
                    fov0 -= 0.3;
                    break;
                    
                case 1:
                    fov1 -= 0.3;
                    break;
                    
                case 2:
                    fov2 -= 0.3;
                    break;
                    
                case 3:
                    fov1 -= 0.3;
                    break;
                    
                default:
                    break;
            }
        }
        if (key == 'Z'){
            switch (camPos) {
                case 0:
                    fov0 += 0.3;
                    break;
                    
                case 1:
                    fov1 += 0.3;
                    break;
                    
                case 2:
                    fov2 += 0.3;
                    break;
                    
                case 3:
                    fov1 += 0.3;
                    break;
                    
                default:
                    break;
            }
        }
        int i = key - 48;
        if(i > 0 && i < 5){
            lightToggle(i);
        }
    }
    glutPostRedisplay();
}

void CDrawModel::specialKeyResponder(unsigned char k, int x, int y){
    switch(k)
    {
        case GLUT_KEY_UP:
            cameraZ += 0.1;
            break;
        case GLUT_KEY_DOWN:
            cameraZ -= 0.1;
            break;
        case GLUT_KEY_LEFT:
            cameraY += 0.1;
            break;
        case GLUT_KEY_RIGHT:
            cameraY -= 0.1;
            break;
    }
    
    glutPostRedisplay();
}

void errorCheck(string Place) {
    GLenum errCode;
    const GLubyte *errString;
    if ((errCode = glGetError()) != GL_NO_ERROR) {
        errString = gluErrorString(errCode);
        //cerr << "OpenGL Error (" << Place << ") " << errString << endl;
    }
}


bool CDrawModel::textureLoad(char *filename){
    FILE *fp;
    long image_size;
    textureRelease();
    
    fp = fopen(filename, "rb");
    
    if (fp == NULL) {
        cerr << "Can't open " << filename << " for reading."<< endl;
        return (false);
    }
    
    fread (&file_header, sizeof(BITMAPFILEHEADER), 1, fp);
    fread (&info_header,sizeof(BITMAPINFOHEADER), 1, fp);
    if (info_header.biBitCount != 24){
        memset (&file_header, 0, sizeof(BITMAPFILEHEADER));
        memset (&info_header, 0, sizeof(BITMAPINFOHEADER));
        fclose (fp);
        return (false);
    }
    image_size = info_header.biWidth * info_header.biHeight * 3;
    imageData = new unsigned char[image_size+1];
    fread (imageData, image_size, 1, fp);
    fclose (fp);
    errorCheck("TEXTURE LOAD");
    return (true);
}

void CDrawModel::textureRelease(void)
{
    if (imageData != NULL){
        delete [] imageData;
        imageData = NULL;
        memset (&file_header, 0, sizeof(file_header));
        memset (&info_header, 0, sizeof(info_header));
    }
}
