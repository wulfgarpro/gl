#include <GL/freeglut.h>

#include "template.h"

static Template* instance;

Template::~Template() {
    delete instance;
}

void Template::display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);
    glVertex2f (-0.5,-0.5);
    glVertex2f (-0.5, 0.5);
    glVertex2f ( 0.5, 0.5);
    glVertex2f ( 0.5,-0.5);
    glEnd();
    glFlush();
}

void Template::init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(500, 500);
    gluOrtho2D(-1,1,-1,1);
}

void Template::setDrawCallback() {
    instance = this;
}

void Template::drawCallback() {
    instance->display();
}
