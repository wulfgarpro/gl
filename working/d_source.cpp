#include <GL/freeglut.h>
#include <iostream>

#include "template.h"

using namespace std;

class TUCdSource : public Template {
    public: 
        void display() override {
            glClear(GL_COLOR_BUFFER_BIT);
            glBegin(GL_LINE_LOOP);
            glVertex2f (-0.2,-0.2);
            glVertex2f (-0.2, 0.2);
            glVertex2f ( 0.2, 0.2);
            glVertex2f ( 0.2,-0.2);
            glEnd();
            glBegin(GL_LINE_LOOP);
            glVertex2f (-0.2,-0.6);
            glVertex2f (-0.2,-0.2);
            glVertex2f ( 0.2,-0.2);
            glVertex2f ( 0.2,-0.6);
            glEnd();
            glBegin(GL_LINES);
            glVertex2f (-0.2,-0.2);
            glVertex2f (0.2,-0.6);
            glVertex2f (-0.2,-0.6);
            glVertex2f (0.2,-0.2);
            glEnd();
            glFlush();
        }
};

int main(int argc, char** argv) {
    TUCdSource* t = new TUCdSource();
    t->setDrawCallback();

    glutInit(&argc, argv);
    glutCreateWindow("My Window");
    glutDisplayFunc(Template::drawCallback);

    t->init();

    glutMainLoop();

    delete t;
    return 0;
}
