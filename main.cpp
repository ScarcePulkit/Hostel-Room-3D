//
//  main.cpp
//  Assignment-2
//
//  Created by Pulkit Agrawal, Rahil Sanghavi
//


#define GL_SILENCE_DEPRECATION
#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using namespace std;

// declaring the global variables
GLboolean redFlag = true, switchOne = false, switchTwo=false, amb1=true, diff1=true, spec1=true, amb2=true, diff2=true, spec2=true, amb3=true, diff3=true, spec3=true;
double windowHeight=800, windowWidth=550;
double eyeX=5.0, eyeY=2.0, eyeZ=15.0, refX = 0, refY=0,refZ=0;
double theta = 90.0, y = 1.36, z = 7.97888;

static GLfloat v_cube[8][3] =
{
    {0.0, 0.0, 0.0}, //0
    {0.0, 0.0, 3.0}, //1
    {3.0, 0.0, 3.0}, //2
    {3.0, 0.0, 0.0}, //3
    {0.0, 3.0, 0.0}, //4
    {0.0, 3.0, 3.0}, //5
    {3.0, 3.0, 3.0}, //6
    {3.0, 3.0, 0.0}  //7
};

static GLubyte quadIndices[6][4] =
{
    {0, 1, 2, 3}, //bottom
    {4, 5, 6, 7}, //top
    {5, 1, 2, 6}, //front
    {0, 4, 7, 3}, // back is clockwise
    {2, 3, 7, 6}, //right
    {1, 5, 4, 0}  //left is clockwise
};

// declaring the axis for the frames
static void getNormal3p
(GLfloat x1, GLfloat y1,GLfloat z1, GLfloat x2, GLfloat y2,GLfloat z2, GLfloat x3, GLfloat y3,GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;
    //up vector
    Ux = x2-x1;
    Uy = y2-y1;
    Uz = z2-z1;

    Vx = x3-x1;
    Vy = y3-y1;
    Vz = z3-z1;

    // normal vector
    Nx = Uy*Vz - Uz*Vy;
    Ny = Uz*Vx - Ux*Vz;
    Nz = Ux*Vy - Uy*Vx;

    glNormal3f(Nx,Ny,Nz);
}

// for drawing a cube
void drawCube()
{
    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        getNormal3p(v_cube[quadIndices[i][0]][0], v_cube[quadIndices[i][0]][1], v_cube[quadIndices[i][0]][2],
                    v_cube[quadIndices[i][1]][0], v_cube[quadIndices[i][1]][1], v_cube[quadIndices[i][1]][2],
                    v_cube[quadIndices[i][2]][0], v_cube[quadIndices[i][2]][1], v_cube[quadIndices[i][2]][2]);
        glVertex3fv(&v_cube[quadIndices[i][0]][0]);
        glVertex3fv(&v_cube[quadIndices[i][1]][0]);
        glVertex3fv(&v_cube[quadIndices[i][2]][0]);
        glVertex3fv(&v_cube[quadIndices[i][3]][0]);
    }
    glEnd();
}

// for drawing a cube
/**
 * @brief Draws a cube with the specified material properties.
 *
 * @param difX The diffuse color component for the X-axis.
 * @param difY The diffuse color component for the Y-axis.
 * @param difZ The diffuse color component for the Z-axis.
 * @param ambX The ambient color component for the X-axis. Default is 0.
 * @param ambY The ambient color component for the Y-axis. Default is 0.
 * @param ambZ The ambient color component for the Z-axis. Default is 0.
 * @param shine The shininess factor of the material. Default is 50.
 */
void drawCube1(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX=0, GLfloat ambY=0, GLfloat ambZ=0, GLfloat shine=50)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {shine};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

    glBegin(GL_QUADS);

    for (GLint i = 0; i <6; i++)
    {
        getNormal3p(v_cube[quadIndices[i][0]][0], v_cube[quadIndices[i][0]][1], v_cube[quadIndices[i][0]][2],
                    v_cube[quadIndices[i][1]][0], v_cube[quadIndices[i][1]][1], v_cube[quadIndices[i][1]][2],
                    v_cube[quadIndices[i][2]][0], v_cube[quadIndices[i][2]][1], v_cube[quadIndices[i][2]][2]);
        glVertex3fv(&v_cube[quadIndices[i][0]][0]);
        glVertex3fv(&v_cube[quadIndices[i][1]][0]);
        glVertex3fv(&v_cube[quadIndices[i][2]][0]);
        glVertex3fv(&v_cube[quadIndices[i][3]][0]);
    }
    glEnd();
}

static GLfloat v_trapezoid[8][3] =
{
    {0.0, 0.0, 0.0}, //0
    {0.0, 0.0, 3.0}, //1
    {3.0, 0.0, 3.0}, //2
    {3.0, 0.0, 0.0}, //3
    {0.5, 3.0, 0.5}, //4
    {0.5, 3.0, 2.5}, //5
    {2.5, 3.0, 2.5}, //6
    {2.5, 3.0, 0.5}  //7
};

static GLubyte TquadIndices[6][4] =
{
    {0, 1, 2, 3}, //bottom
    {4, 5, 6, 7}, //top
    {5, 1, 2, 6}, //front
    {0, 4, 7, 3}, // back is clockwise
    {2, 3, 7, 6}, //right
    {1, 5, 4, 0}  //left is clockwise
};

//Drawing pyramid *************************
static GLfloat v_pyramid[5][3] =
{
    {0.0, 0.0, 0.0},
    {0.0, 0.0, 2.0},
    {2.0, 0.0, 2.0},
    {2.0, 0.0, 0.0},
    {1.0, 4.0, 1.0}
};

static GLubyte p_Indices[4][3] =
{
    {4, 1, 2},
    {4, 2, 3},
    {4, 3, 0},
    {4, 0, 1}
};

static GLubyte PquadIndices[1][4] =
{
    {0, 3, 2, 1}
};

/**
 * @brief Draws a pyramid with the specified diffuse and ambient lighting properties.
 *
 * @param difX The X component of the diffuse lighting color.
 * @param difY The Y component of the diffuse lighting color.
 * @param difZ The Z component of the diffuse lighting color.
 * @param ambX The X component of the ambient lighting color.
 * @param ambY The Y component of the ambient lighting color.
 * @param ambZ The Z component of the ambient lighting color.
 * @param shine The shininess factor of the pyramid.
 */
void drawpyramid(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX, GLfloat ambY, GLfloat ambZ, GLfloat shine)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {shine};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    glBegin(GL_TRIANGLES);
    for (GLint i = 0; i <4; i++)
    {
        getNormal3p(v_pyramid[p_Indices[i][0]][0], v_pyramid[p_Indices[i][0]][1], v_pyramid[p_Indices[i][0]][2],
                    v_pyramid[p_Indices[i][1]][0], v_pyramid[p_Indices[i][1]][1], v_pyramid[p_Indices[i][1]][2],
                    v_pyramid[p_Indices[i][2]][0], v_pyramid[p_Indices[i][2]][1], v_pyramid[p_Indices[i][2]][2]);
        glVertex3fv(&v_pyramid[p_Indices[i][0]][0]);
        glVertex3fv(&v_pyramid[p_Indices[i][1]][0]);
        glVertex3fv(&v_pyramid[p_Indices[i][2]][0]);
    }
    glEnd();

    glBegin(GL_QUADS);
    for (GLint i = 0; i <1; i++)
    {
        getNormal3p(v_pyramid[PquadIndices[i][0]][0], v_pyramid[PquadIndices[i][0]][1], v_pyramid[PquadIndices[i][0]][2],
                    v_pyramid[PquadIndices[i][1]][0], v_pyramid[PquadIndices[i][1]][1], v_pyramid[PquadIndices[i][1]][2],
                    v_pyramid[PquadIndices[i][2]][0], v_pyramid[PquadIndices[i][2]][1], v_pyramid[PquadIndices[i][2]][2]);
        glVertex3fv(&v_pyramid[PquadIndices[i][0]][0]);
        glVertex3fv(&v_pyramid[PquadIndices[i][1]][0]);
        glVertex3fv(&v_pyramid[PquadIndices[i][2]][0]);
        glVertex3fv(&v_pyramid[PquadIndices[i][3]][0]);
    }
    glEnd();

}

/**
 * @brief Draws a polygon with the specified diffuse and ambient colors and shininess.
 *
 * @param difX The X component of the diffuse color.
 * @param difY The Y component of the diffuse color.
 * @param difZ The Z component of the diffuse color.
 * @param ambX The X component of the ambient color.
 * @param ambY The Y component of the ambient color.
 * @param ambZ The Z component of the ambient color.
 * @param shine The shininess of the polygon.
 */
void polygon(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX, GLfloat ambY, GLfloat ambZ, GLfloat shine)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {shine};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    glBegin(GL_POLYGON);
    glVertex2f(0,0);
    glVertex2f(6,0);
    glVertex2f(5.8,1);
    glVertex2f(5.2,2);
    glVertex2f(5, 2.2);
    glVertex2f(4, 2.8);
    glVertex2f(3,3);
    glVertex2f(2, 2.8);
    glVertex2f(1, 2.2);
    glVertex2f(0.8, 2);
    glVertex2f(0.2,1);
    //glVertex2f(0,0);

    glEnd();
}

/**
 * @brief Draws a polygonal line in 3D space.
 *
 * This function takes the differences in X, Y, and Z coordinates, as well as the ambient color and shine factor,
 * and draws a polygonal line in 3D space.
 *
 * @param difX The difference in X coordinates.
 * @param difY The difference in Y coordinates.
 * @param difZ The difference in Z coordinates.
 * @param ambX The ambient color component for X.
 * @param ambY The ambient color component for Y.
 * @param ambZ The ambient color component for Z.
 * @param shine The shine factor for the polygonal line.
 */
void polygonLine(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX, GLfloat ambY, GLfloat ambZ, GLfloat shine)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {shine};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glBegin(GL_LINE_STRIP);
    //glVertex2f(0,0);
    glVertex2f(6,0);
    glVertex2f(5.8,1);
    glVertex2f(5.2,2);
    glVertex2f(5, 2.2);
    glVertex2f(4, 2.8);
    glVertex2f(3,3);
    glVertex2f(2, 2.8);
    glVertex2f(1, 2.2);
    glVertex2f(0.8, 2);
    glVertex2f(0.2,1);
    glVertex2f(0,0);

    glEnd();
}

/**
 * @brief Draws a sphere with the specified diffuse and ambient colors.
 *
 * @param difX The X component of the diffuse color.
 * @param difY The Y component of the diffuse color.
 * @param difZ The Z component of the diffuse color.
 * @param ambX The X component of the ambient color.
 * @param ambY The Y component of the ambient color.
 * @param ambZ The Z component of the ambient color.
 * @param shine The shininess of the sphere (default value is 90).
 */
void drawSphere(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX, GLfloat ambY, GLfloat ambZ, GLfloat shine=90)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {shine};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    glutSolidSphere (3.0, 20, 16);
}

/**
 * @brief Represents a cupboard.
 *
 * This function represents a cupboard and performs some operations related to it.
 *
 * @param None
 * @return None
 */
void cupboard()
{
    //Cupboard/Almari ************************************************************

        //cupboard
    glPushMatrix();
    glTranslatef(0,-0.2,4.4);
    glScalef(0.85, 1.3, 0.5);
    drawCube1(0.5,0.2,0.2,  0.25, 0.1, 0.1 );
    glPopMatrix();

    //cupboard's middle vertical stripline
    glPushMatrix();
    glTranslatef(1.23,-0.2,5.9);
    glScalef(0.01, 1.4, 0.0001);
    drawCube1(0.2,0.1,0.1,  0.1, 0.05, 0.05);
    glPopMatrix();

    //cupboard's handle right
    glPushMatrix();
    glTranslatef(1.40,1.3,5.9);
    glScalef(0.02, 0.18, 0.01);
    drawCube1(0.2,0.1,0.1,  0.1, 0.05, 0.05);
    glPopMatrix();

    //cupboard's handle left
    glPushMatrix();
    glTranslatef(1.05,1.5,5.9);
    glScalef(0.02, 0.18, 0.01);
    drawCube1(0.2,0.1,0.1,  0.1, 0.05, 0.05);
    glPopMatrix();
}

// the upper shelf
/**
 * @brief Draws a cupboard/almari in the scene.
 *
 * This function draws a cupboard/almari using OpenGL transformations and the drawCube1 function.
 * It consists of a main body, a middle vertical stripline, and two handles.
 *
 * @note This function assumes that the drawCube1 function is defined and implemented elsewhere.
 *
 * @see drawCube1
 */
void cupboard2()
{
    //Cupboard/Almari ************************************************************

        //cupboard
    glPushMatrix();
    glTranslatef(0,3.7,4.4);
    glScalef(0.85, 0.45, 0.5);
    drawCube1(0.5,0.2,0.2,  0.25, 0.1, 0.1 );
    glPopMatrix();

    //cupboard's middle vertical stripline
    glPushMatrix();
    glTranslatef(1.23,3.7,5.9);
    glScalef(0.01, 0.45, 0.0001);
    drawCube1(0.2,0.1,0.1,  0.1, 0.05, 0.05);
    glPopMatrix();

    //cupboard's handle right
    glPushMatrix();
    glTranslatef(1.40,4,5.9);
    glScalef(0.02, 0.18, 0.01);
    drawCube1(0.2,0.1,0.1,  0.1, 0.05, 0.05);
    glPopMatrix();

    //cupboard's handle left
    glPushMatrix();
    glTranslatef(1.05,4,5.9);
    glScalef(0.02, 0.18, 0.01);
    drawCube1(0.2,0.1,0.1,  0.1, 0.05, 0.05);
    glPopMatrix();
}

// horizontal and vertical walls
/**
 * @brief Function to perform mid-wall operation.
 *
 * This function performs the mid-wall operation.
 * It is used for a specific purpose in the program.
 *
 * @return void
 */
void midWall(){
    // vertical wall
    glPushMatrix();
    glTranslatef(2.45,-1,0);
    glScalef(0.17, 2, 2);
    drawCube1(1, 0.8, 0.7,  0.5, 0.4, 0.35);
    glPopMatrix();

    // horizontal wall
    glPushMatrix();
    glTranslatef(-0.75,3.6,0);
    glScalef(2.5, 0.075, 2);
    drawCube1(1, 0.8, 0.7,  0.5, 0.4, 0.35);
    glPopMatrix();

    // below window
    glPushMatrix();
    glTranslatef(2.8,1.1,0);
    glScalef(1.3, 0.075, 2);
    drawCube1(1, 0.8, 0.7,  0.5, 0.4, 0.35);
    glPopMatrix();

    // slab
    glPushMatrix();
    glTranslatef(2.8,0.5,0);
    glScalef(1.3, 0.025, 1.7);
    drawCube1(1, 0.8, 0.7,  0.5, 0.4, 0.35);
    glPopMatrix();
}

// whiteboard
/**
 * @brief Function to initialize the whiteboard.
 *
 * This function initializes the whiteboard for drawing.
 * It sets up the necessary variables and data structures.
 */
void whiteboard(){
    glPushMatrix();
    glTranslatef(5.97,2,6.5);
    glScalef(0.02,0.5,0.8);
    drawCube1(0.627, 0.322, 0.176, 1,1,1);
    glPopMatrix();
}

/**
 * @brief This function represents a room.
 *
 * It is responsible for defining the behavior and properties of a room.
 *
 */
void room()
{
    // right wall
    //glColor3f(1, 0.8, 0.5);
    glPushMatrix();
    glTranslatef(-1.5,-1,.5);
    glScalef(5, 2, 0.1);
    drawCube1(1, 0.8, 0.7,  0.5, 0.4, 0.35);
    glPopMatrix();

    // left wall
    glPushMatrix();
    glTranslatef(-3.2,-1,0);
    glScalef(1, 2, 5);
    drawCube1(1, 0.8, 0.7,  0.5, 0.4, 0.35);
    glPopMatrix();

    // the right wall
    glPushMatrix();
    glTranslatef(6,-1,0);
    glScalef(0.2, 2, 5);
    drawCube1(1, 0.8, 0.7,  0.5, 0.4, 0.35);
    glPopMatrix();

    //ceiling
     glPushMatrix();
     glTranslatef(-2,5.1,0);
     glScalef(5, 0.1, 7);
     drawCube1(1.0, 0.9, 0.8,  0.5,0.45,0.4);
     glPopMatrix();

    // floor
    glPushMatrix();
    glScalef(5, 0.1, 7);
    glTranslatef(-1,-5,0);
    drawCube1(0.5, 0.1, 0.0,  0.25,0.05,0);
    glPopMatrix();
}

// bed
/**
 * Draws a bed with a bed body, blanket, and blanket side.
 */
void bed()
{
    //bed body
    glPushMatrix();
    glTranslatef(0,0,0.75);
    glScalef(1, 0.2, 1.75); //1, 0.2, 0.9
    glTranslatef(0,-0.5,5.2);
    drawCube1(0.824, 0.706, 0.549,   0.412,0.353,0.2745);
    glPopMatrix();

    //blanket
    glPushMatrix();
    glTranslatef(0,0,0.75);
    glTranslatef(0,0.45,8.5);
    glRotatef(0, 90,0,1);
    glScalef(1, 0.05, 0.95);
    drawCube1(0.627, 0.322, 0.176,  0.3135,0.161,0.088);
    glPopMatrix();

    //blanket side left part
    glPushMatrix();
    glTranslatef(0,0,0.75);
    glTranslatef(2.8,-0.3,11.36);
    glRotatef(90,0,90,1);
    glScalef(0.90, 0.30, 0.10);
    drawCube1(0.627, 0.322, 0.176, 0.3135,0.161,0.088);
    glPopMatrix();
}

void baggage()
{
    //baggage *************************************
      glPushMatrix();
      glTranslatef(0,0.25,0);
      //side drawer
      glPushMatrix();
      glTranslatef(5,3.6,3); //0.5,-0.1,9
      glScalef(0.3, 0.2, 1);
      drawCube1(0.2,0.1,0.1,  0.1,0.05,0.05);
      glPopMatrix();

      // wheel1
      glPushMatrix();
      glTranslatef(5.05,4.1,6.01);
      glScalef(0.02, 0.02, 0.01);
      drawSphere(0.2,0.1,0.1,  0.1, 0.05, 0.05,  10);
      glPopMatrix();

      // wheel2
      glPushMatrix();
      glTranslatef(5.05,3.65,6.01);
      glScalef(0.02, 0.02, 0.01);
      drawSphere(0.2,0.1,0.1,  0.1, 0.05, 0.05,  10);
      glPopMatrix();

      // wheel3
      glPushMatrix();
      glTranslatef(5.82,3.65,6.01);
      glScalef(0.02, 0.02, 0.01);
      drawSphere(0.2,0.1,0.1,  0.1, 0.05, 0.05,  10);
      glPopMatrix();

      // wheel4
      glPushMatrix();
      glTranslatef(5.82,4.1,6.01);
      glScalef(0.02, 0.02, 0.01);
      drawSphere(0.2,0.1,0.1,  0.1, 0.05, 0.05,  10);
      glPopMatrix();
      glPopMatrix();
}

// window shield
/**
 * @brief Renders a window with various stripes.
 *
 * This function is responsible for rendering a window with multiple stripes using OpenGL.
 * It uses the drawCube1 function to draw the stripes.
 *
 * @note This function assumes that the necessary OpenGL context has been set up before calling it.
 */
void window()
{
        // window
        glPushMatrix();
        glTranslatef(0,0.45,0);

        //window main mirror
        glPushMatrix();
        glTranslatef(3,0.9,5.8);
        glScalef(0.98, 0.75, 0.0001);
        drawCube1(0.690, 0.878, 0.902,  0.345,0.439,0.451, 10);
        glPopMatrix();

        // left stripe
        glColor3f(0.2,0.1,0.1);
        glPushMatrix();
        glTranslatef(3,0.9,5.85);
        glScalef(0.019, 0.75, 0.0001);
        drawCube1(0.2,0.1,0.1,  0.1,0.05,0.05);
        glPopMatrix();

        //lower stripe
        glColor3f(1,0.1,0.1);
        glPushMatrix();
        glTranslatef(3,0.9,5.85);
        glScalef(1, 0.019, 0.0001);
        drawCube1(0.2,0.1,0.1,  0.1,0.05,0.05);
        glPopMatrix();

        //upper stripe
        glColor3f(1,0.1,0.1);
        glPushMatrix();
        glTranslatef(3,3.1,5.85);
        glScalef(1, 0.019, 0.0001);
        drawCube1(0.2,0.1,0.1,  0.1,0.05,0.05);
        glPopMatrix();

        // right stripe
        glColor3f(0.2,0.1,0.1);
        glPushMatrix();
        glTranslatef(5.89,0.9,5.85);
        glScalef(0.019, 0.75, 0.0001);
        drawCube1(0.2,0.1,0.1,  0.1,0.05,0.05);
        glPopMatrix();

        // middle stripe
        glColor3f(0.2,0.1,0.1);
        glPushMatrix();
        glTranslatef(4.5,0.9,5.85);
        glScalef(0.019, 0.75, 0.0001);
        drawCube1(0.2,0.1,0.1,  0.1,0.05,0.05);
        glPopMatrix();
        glPopMatrix();
}

/**
 * @brief This function represents a study table.
 *
 * It performs the necessary operations to simulate a study table.
 *
 * @return void
 */
void studyTable(){
    //dressing table upper body
    glPushMatrix();
    glTranslatef(0,0,1);
    glPushMatrix();
    glTranslatef(4.9,0.9,5.3);
    glScalef(0.35, 0.02, 0.8);
    drawCube1(0.545, 0.271, 0.075,  0.2725,0.1355,0.0375);
    glPopMatrix();

    // table legs
    // back
    glPushMatrix();
    glTranslatef(4.99,-0.25,5.5);
    glScalef(0.3, 0.4, 0.015);
    drawCube1(0.545, 0.271, 0.075,  0.2725,0.1355,0.0375);
    glPopMatrix();

    // front
    glPushMatrix();
    glTranslatef(4.99,-0.25,7.5);
    glScalef(0.3, 0.4, 0.015);
    drawCube1(0.545, 0.271, 0.075,  0.2725,0.1355,0.0375);
    glPopMatrix();
    glPopMatrix();
}

// chair
/**
 * @brief This function represents a chair.
 *
 * It defines the behavior and properties of a chair.
 */
void chair(){
    // seat
    glPushMatrix();
    glTranslatef(0.25,0,0);
    glPushMatrix();
    glTranslatef(3.9,0.5,7.3);
    glScalef(0.25, 0.02, 0.25);
    drawCube1(0.545, 0.271, 0.075,  0.2725,0.1355,0.0375);
    glPopMatrix();

    // backseat
    glPushMatrix();
    glTranslatef(3.9,0.5,7.3);
    glScalef(0.02, 0.3, 0.25);
    drawCube1(0.545, 0.271, 0.075,  0.2725,0.1355,0.0375);
    glPopMatrix();

    // legs
    glPushMatrix();
    glTranslatef(3.9,-0.25,7.3);
    glScalef(0.015, 0.27, 0.015);
    drawCube1(0.545, 0.271, 0.075,  0.2725,0.1355,0.0375);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4.6,-0.25,7.3);
    glScalef(0.015, 0.27, 0.015);
    drawCube1(0.545, 0.271, 0.075,  0.2725,0.1355,0.0375);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3.9,-0.25,8);
    glScalef(0.015, 0.27, 0.015);
    drawCube1(0.545, 0.271, 0.075,  0.2725,0.1355,0.0375);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4.6,-0.25,8);
    glScalef(0.015, 0.27, 0.015);
    drawCube1(0.545, 0.271, 0.075,  0.2725,0.1355,0.0375);
    glPopMatrix();
    glPopMatrix();
}

// flaps for fan
void flap(){
    glPushMatrix();
    //glTranslatef(0,0,0.5);
    // tip1
    glPushMatrix();
    glTranslatef(3.25,4.75,7);
    glScalef(0.05,0.005,0.020);
    drawCube1(0.5,0.2,0,  0.25,0.1,0,  20);
    glPopMatrix();

    // flap1
    glPushMatrix();
    glTranslatef(3.35,4.75,6.9);
    glScalef(0.3,0.005,0.09);
    drawCube1(0.5,0.2,0,  0.25,0.1,0,  20);
    glPopMatrix();
    glPopMatrix();

    //tip2
    glPushMatrix();
    glTranslatef(2.80,4.75,6.88);
    glRotatef(135,0,1,0);
    glScalef(0.05,0.005,0.020);
    drawCube1(0.5,0.2,0,  0.25,0.1,0,  20);
    glPopMatrix();

    // flap2
    glPushMatrix();
    glTranslatef(2.63,4.75,6.86);
    glRotatef(135,0,1,0);
    glScalef(0.3,0.005,0.1);
    drawCube1(0.5,0.2,0,  0.25,0.1,0,  20);
    glPopMatrix();

    //tip3
    glPushMatrix();
    glTranslatef(2.80,4.75,7.1);
    glRotatef(-135,0,1,0);
    glScalef(0.05,0.005,0.020);
    drawCube1(0.5,0.2,0,  0.25,0.1,0,  20);
    glPopMatrix();

    // flap3
    glPushMatrix();
    glTranslatef(2.8,4.75,7.3);
    glRotatef(-135,0,1,0);
    glScalef(0.3,0.005,0.1);
    drawCube1(0.5,0.2,0,  0.25,0.1,0,  20);
    glPopMatrix();
}

void sphericalObject()
{
    glPushMatrix();
    glTranslatef(3, 4.79, 7);
    glRotatef(180,1,0,0);
    glTranslatef(-5, -0.2, -10);
    //table top part
    glPushMatrix();
    glTranslatef(5, 0.2, 10);
    glScalef(0.1, 0.02, 0.1);
    drawSphere(0.5,0.2,0,  0.25,0.1,0,  20);
    glPopMatrix();

    //table leg
    glColor3f(0.2,0.1,0.1); //0.2,0.1,0.1
    glPushMatrix();
    glTranslatef(4.98,-0.1,10);
    glScalef(0.02, 0.1, 0.02);
    drawCube1(0.2,0.1,0.1,  0.1,0.05,0.05);
    glPopMatrix();

    //base
    glPushMatrix();
    glTranslatef(5, -0.1, 10);
    glScalef(0.05, 0.01, 0.05);
    drawSphere(0.5,0.2,0,  0.25,0.1,0,  20);
    glPopMatrix();
    glPopMatrix();
}


/**
 * @brief Function to control light bulb 1.
 *
 * This function is responsible for controlling the behavior of light bulb 1.
 * It performs the necessary operations to turn the light bulb on or off.
 *
 * @param None
 * @return None
 */
void lightBulb1()
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
    GLfloat mat_ambient_color[] = { 0.8, 0.8, 0.2, 1.0 };
    GLfloat mat_diffuse[] = { 1.000, 0.843, 0.000, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat high_shininess[] = { 100.0 };
    GLfloat mat_emission[] = {1.000, 1,1, 0.0};

    glPushMatrix();
    glTranslatef (6, 4.5, 10);
    glScalef(0.1, 0.1, 1.5);
    glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    if(switchOne == true){
        glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
    }else{
        glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    }
    //glColor3f(0,0,0);
    //glutSolidSphere(1.0, 16, 16);
    glutSolidCube(1);
    glPopMatrix();
}

/**
 * @brief Function to control the second light bulb.
 *
 * This function is responsible for controlling the second light bulb.
 * It performs the necessary operations to turn the light bulb on or off.
 *
 * @return void
 */
void lightBulb2()
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
    GLfloat mat_ambient_color[] = { 0.8, 0.8, 0.2, 1.0 };
    GLfloat mat_diffuse[] = { 1.000, 0.843, 0.000, 1.0 };
    GLfloat high_shininess[] = { 100.0 };
    GLfloat mat_emission[] = {1,1,1, 1.0};

    glPushMatrix();
    glTranslatef (0,5,8);
    glScalef(0.1, 0.15, 0.1);
    glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    if(switchTwo == true){
        glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
    }else{
        glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    }
    glutSolidSphere(1.0, 16, 16);
    glPopMatrix();
}

/**
 * @brief Function to handle light one.
 *
 * This function is responsible for handling light one in the program.
 * It performs the necessary operations related to light one.
 */
void lightOne()
{
    glPushMatrix();
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {0.5, 0.5, 0.5, 1.0};
    GLfloat light_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 5.0, 5.0, 8.0, 1.0 }; //5 5 10

    //glEnable( GL_LIGHT0);

    if(amb1 == true){glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient);}
    else{glLightfv( GL_LIGHT0, GL_AMBIENT, no_light);}

    if(diff1 == true){glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse);}
    else{glLightfv( GL_LIGHT0, GL_DIFFUSE, no_light);}

    if(spec1 == true){glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular);}
    else{glLightfv( GL_LIGHT0, GL_SPECULAR, no_light);}

    glLightfv( GL_LIGHT0, GL_POSITION, light_position);
    glPopMatrix();
}

void lightTwo()
{
    glPushMatrix();
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {0.5, 0.5, 0.5, 1.0};
    GLfloat light_diffuse[]  = { 1.0, 1.0, 0.9, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 0.0, 5.0, 8.0, 1.0 };

    //glEnable( GL_LIGHT1);

    if(amb2 == true){glLightfv( GL_LIGHT1, GL_AMBIENT, light_ambient);}
    else{glLightfv( GL_LIGHT1, GL_AMBIENT, no_light);}

    if(diff2 == true){glLightfv( GL_LIGHT1, GL_DIFFUSE, light_diffuse);}
    else{glLightfv( GL_LIGHT1, GL_DIFFUSE, no_light);}

    if(spec2 == true){glLightfv( GL_LIGHT1, GL_SPECULAR, light_specular);}
    else{glLightfv( GL_LIGHT1, GL_SPECULAR, no_light);}

    glLightfv( GL_LIGHT1, GL_POSITION, light_position);
    glPopMatrix();
}

// for displaying different objects
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective(60,1,1,100);

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt(eyeX,eyeY,eyeZ,  refX,refY,refZ,  0,1,0); //7,2,15, 0,0,0, 0,1,0

    glEnable(GL_LIGHTING);
    // calling different functions
    lightOne();
    lightTwo();
    midWall();
    room();
    bed();
    baggage();
    studyTable();
    chair();
    cupboard();
    cupboard2();
    window();
    whiteboard();
    sphericalObject();
    flap();
    lightBulb1();
    lightBulb2();
    glDisable(GL_LIGHTING);
    glFlush();
    glutSwapBuffers();
}

void myKeyboardFunc( unsigned char key, int x, int y )
{
    switch ( key )
    {
        case 'w': // move eye point upwards along Y axis
            eyeY+=1.0;
            break;
        case 's': // move eye point downwards along Y axis
            eyeY-=1.0;
            break;
        case 'a': // move eye point left along X axis
            eyeX-=1.0;
            break;
        case 'd': // move eye point right along X axis
            eyeX+=1.0;
            break;
        case 'o':  //zoom out
            eyeZ+=1;
            break;
        case 'i': //zoom in
            eyeZ-=1;
            break;
        case 'r': //back to default eye point and ref point
                eyeX=5.0, eyeY=2.0, eyeZ=15.0, refX = 0, refY=0,refZ=0;
            break;
        case 'u': // move ref point upwards along Y axis
            refY+=1.0;
            break;
        case 'j': // move ref point downwards along Y axis
            refY-=1.0;
            break;
        case 'h': // move ref point left along X axis
            refX-=1.0;
            break;
        case 'k': // move eye point right along X axis
            refX+=1.0;
            break;
        case 'n':  //move ref point away from screen/ along z axis
            refZ+=1;
            break;
        case 'm': //move ref point towards screen/ along z axis
            refZ-=1;
            break;
        case '1': //to turn on and off light one
            if(switchOne == false)
            {
                switchOne = true; amb1=true; diff1=true; spec1=true;
                glEnable( GL_LIGHT0); break;
            }
            else if(switchOne == true)
            {
                switchOne = false; amb1=false; diff1=false; spec1=false; glDisable( GL_LIGHT0); break;
            }
        case '2': //to turn on and off light two
            if(switchTwo == false)
            {
                switchTwo = true; amb2=true; diff2=true; spec2=true;
                glEnable( GL_LIGHT1); break;
            }
            else if(switchTwo == true)
            {
                switchTwo = false; amb2=false; diff2=false; spec2=false;
                glDisable( GL_LIGHT1); break;
            }
    }

    glutPostRedisplay();
}


void animate()
{
    if(redFlag == true)
    {
        theta+=2;
        z-=0.02; //0.016667;
        if(theta >= 196 && theta <= 210)
        {
            y = 1.44;
        }
        else if(theta >= 180 && theta <= 194)
        {
            y = 1.42;
        }
        else if(theta >= 180 && theta <= 194)
        {
            y = 1.4;
        }
        else if(theta >= 164 && theta <= 178)
        {
            y = 1.42;
        }

        if(theta == 210)
        {
            redFlag = false;
        }
    }
    else if(redFlag == false)
    {
        theta-=2;
        z+=0.02;//0.016667;

        if(theta >= 196 && theta <= 210)
        {
            y = 1.44;
        }
        else if(theta >= 180 && theta <= 194)
        {
            y = 1.42;
        }
        else if(theta >= 180 && theta <= 194)
        {
            y = 1.4;
        }
        else if(theta >= 164 && theta <= 178)
        {
            y = 1.42;
        }

        if(theta == 150)
        {
            redFlag = true;
        }
    }

    glutPostRedisplay();

}

void fullScreen(int w, int h)
{
    //Prevent a divide by zero, when window is too short;you cant make a window of zero width.
    if (h == 0)
        h = 1;
    float ratio = (GLfloat)w / (GLfloat)h;         //Calculate aspect ratio of the window

    //Set the perspective coordinate system
    glMatrixMode(GL_PROJECTION);                   //Use the Projection Matrix
    glLoadIdentity();                              //Reset Matrix

    glViewport(0, 0, w, h);                        //Set the viewport to be the entire window
    gluPerspective(60, ratio, 1, 500);             //Set the correct perspective.
    //glFrustum(-2.5,2.5,-2.5,2.5, ratio, 200);
    glMatrixMode(GL_MODELVIEW);                    //Get Back to the Modelview
}


int main (int argc, char **argv)
{
    glutInit(&argc, argv);

    cout<<"Here are the keys to move Eye:"<<endl;
    cout<<"w: Up"<<endl;
    cout<<"s: Down"<<endl;
    cout<<"a: Left"<<endl;
    cout<<"d: Right"<<endl;
    cout<<"i: Zoom in"<<endl;
    cout<<"o: Zoom out"<<endl;
    cout<<"      "<<endl;
    cout<<"To move Camera point:"<< endl;
    cout<<"u: up"<<endl;
    cout<<"j: down"<<endl;
    cout<<"h: left"<<endl;
    cout<<"k: right"<<endl;
    cout<<"      "<<endl;
    cout<<"Press r to move to default position"<<endl;
    cout<<"      "<<endl;
    cout<<"For lighting:      "<<endl;
    cout<<"Light source 1 [the light on the right on the screen      "<<endl;
    cout<<"1: to turn on/off light one     "<<endl;
    cout<<"2: to turn on/off light two     "<<endl;


    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(100,100);
    glutInitWindowSize(windowHeight, windowWidth);
    glutCreateWindow("Hostel Room");

    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );
    glEnable(GL_NORMALIZE);

    glutReshapeFunc(fullScreen);
    glutDisplayFunc(display);

    glutKeyboardFunc(myKeyboardFunc);
    glutIdleFunc(animate);
    glutMainLoop();

    return 0;
}
