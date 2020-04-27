#include <GL/glut.h>
#include <GL/gl.h>
#include <iostream>
#include <string>
#include "Bezier.h"

#define min(a,b) a>b?a:b
#define EUCLIDEAN_DIST 51
#define WIDTH 500
#define HEIGHT 500
float tRate = 0.025;

int squareDist(glm::vec2 pos1, glm::vec2 pos2);
int nearbyIndex(glm::vec2 point);
void handleMouseClick(int click, int buttonStatus, int x, int y);
void handleMouse(int x, int y);
void resize(int w, int h);

bool move;
int movement;

//! Bezier Curve object.
Bezier curve(tRate);


/**
 * Draws the Bezier curve. 
 * Serves as the display function for glut.
 */
void drawBezier()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 1, 0);
    glBegin(GL_LINE_STRIP);
    for( auto p: curve.controls)
    {
        glVertex2f(p.x, p.y);
    }
    glEnd();
    glColor3f(1, 0, 1);
    glBegin(GL_LINE_STRIP);
    for( auto p: curve.curve)
    {
        glVertex2f(p.x, p.y);
    }
    glEnd();
    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Assignment 3 - IS F311");
    glClearColor(0.8, 0.8, 0.8, 0.8);
    gluOrtho2D(0, WIDTH, 0, HEIGHT);
    glutMotionFunc(handleMouse);
    glutMouseFunc(handleMouseClick);
    glutDisplayFunc(drawBezier);
    glutReshapeFunc(resize);
    glutMainLoop();

    return 0;
}

/**
 * Window resize handler
 */
void resize(int w, int h)
{
    glutReshapeWindow(WIDTH, HEIGHT);
}
/**
 * Helper function: Squared Euclidean distance between two points
 * @param pos1 first point
 * @param pos2 second point
 * @return squared distance
 */
int squareDist(glm::vec2 pos1, glm::vec2 pos2)
{
    return (pos1.x - pos2.x)*(pos1.x - pos2.x) + 
                (pos1.y - pos2.y)*(pos1.y - pos2.y);
}

/**
 * Method to find the index in Control Points of the nearest point within a radius
 * @param point point from which distance is measured.
 * @return index in controls.
 */
int nearbyIndex(glm::vec2 point)
{
    int mn = EUCLIDEAN_DIST+1;
    int id = -1;
    for(int i=0; i< curve.controls.size(); i++)
    {
        int curr = squareDist(point, curve.controls[i]);
        if(mn > curr)
        {
            mn = curr;
            id = i;
        }
    }
    return id;
}


/**
 * Handler function to add/delete/drag points. 
 * @param click button being clicked
 * @param buttonStatus status of the button (pressed/released)
 * @param pos position of the cursor
 */
void handleMouseClick(int click, int buttonStatus, int x, int y)
{
     // drag using left button
    if(click == GLUT_LEFT_BUTTON && buttonStatus == GLUT_DOWN)
    {
        movement = nearbyIndex(glm::vec2(x, HEIGHT-y));
        if(movement != -1) move = true;
    }
    else if(click == GLUT_LEFT_BUTTON && buttonStatus == GLUT_UP)
    {
        move = false;
        curve.movePoint(movement, glm::vec2(x, HEIGHT - y));
    }
    
    // Add a point by middle clicking
    else if(click == GLUT_MIDDLE_BUTTON && buttonStatus == GLUT_DOWN)
    {
        curve.newPoint(glm::vec2(x, HEIGHT - y));
    }
    
    //Delete with right click
    else if(click == GLUT_RIGHT_BUTTON && buttonStatus == GLUT_DOWN)
    {
        curve.deletePoint(nearbyIndex(glm::vec2(x, HEIGHT - y)));
    }
    glutPostRedisplay();
}

/**
 * Handler function for mouse movements. Drags points when pressed.
 * @param pos position of the cursor
 */
void handleMouse(int x, int y)
{
    if(move)
    {
        curve.movePoint(movement, glm::vec2(x, HEIGHT-y));
        glutPostRedisplay();
    }
}