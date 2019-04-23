#include <cmath>
#include "maze.h"
#include "glut.h"
#include "rat.h"
#include "graphics.h"

Rat::Rat() {}

Rat::Rat(double x, double y, double degrees) {
        mX=x;
        mY=y;
        mDegrees = degrees;

}

void Rat::Draw() {
    if (current_view == rat_view) {
        return;
    }else {
        glColor3d(.5,.5,.5);
        glPushMatrix();
        glTranslated(mX,mY,0);
        glRotated(mDegrees,0,0,1);
        DrawTriangle(.2,0,-.2,.2,-.2,-.2);
        DrawCircle(.2,0,.03);
        glPopMatrix();
    }
}

void Rat::RotateLeft() {
        mDegrees+=3;
}

void Rat::RotateRight() {
        mDegrees-=3;
}

double Rat::getX() {
    return mX;
}

double Rat::getY() {
        return mY;
}

double Rat::getDX() {
        return cos(mDegrees*3.14/180) * 0.01;
}

double Rat::getDY() {
        return sin(mDegrees * 3.14/180) * 0.01;
}


void Rat::ScurryForward(Maze& maze) {
        double newX = mX + cos(mDegrees * 3.14/180) * 0.03;
        double newY = mY + sin(mDegrees * 3.14/180) * 0.03;
        if (maze.isSafe(newX,newY,.203)) {
                mX=newX;
                mY=newY;
        } else if (maze.isSafe(mX,newY,.2)) {
                mY=newY;
        } else if (maze.isSafe(newX,mY,.2)) {
                mX=newX;
        }
}
