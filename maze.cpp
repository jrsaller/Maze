#include <vector>
#include <cstdlib>
#include <iostream>
#include "maze.h"
#include "glut.h"
#include "graphics.h"
Cell::Cell()
{
	l = t = r = b = true;
        visited = false;
        red =0;
        green=0;
        blue = 0;
}

double Cell::getRed() {
        return red;
}

double Cell::getGreen() {
        return green;
}

double Cell::getBlue() {
        return blue;
}

void Cell::setRed(double value) {
        red = value;
}

void Cell::setGreen(double value) {
        green = value;

}

void Cell::setBlue(double value) {
        blue = value;
}

void Cell::Draw(int i, int j)
{
    if (current_view == top_view) {
	if (l)
		DrawLine(i, j, i, j + 1);
	if (t)
		DrawLine(i, j + 1, i + 1, j + 1);
	if (r)
		DrawLine(i + 1, j + 1, i + 1, j);
	if (b)
		DrawLine(i + 1, j, i, j);
    } else {
        //glColor3d(red,green,blue);
        //glColor3d(0.2,0.2,0.2);
        unsigned char r;
        unsigned char g;
        unsigned char b;
        if (l) {
                r = (i * 54872 + j * 32498) % 256;
                g = (i * 37302 + j * 27103) %256;
                b = (i * 28403 + j * 10858) % 256;
                glColor3ub(r,g,b);
                glBegin(GL_QUADS);
                glVertex3d(i,j,0);
                glVertex3d(i,j+1,0);
                glVertex3d(i,j+1,1);
                glVertex3d(i,j,1);
                glEnd();
        }
        if (t) {
                r = (i * 78903 + j * 28740) % 256 + 35;
                g = (i * 58403 + j * 12349) %256 + 35;
                b = (i * 48303 + j * 12902) % 256 + 35;
                glColor3ub(r,g,b);
                glBegin(GL_QUADS);
                glVertex3d(i,j+1,0);
                glVertex3d(i+1,j+1,0);
                glVertex3d(i+1,j+1,1);
                glVertex3d(i,j+1,1);
                glEnd();
                //DrawQuad(i,j+1,i+1,j+1);
        }
        if (r && i==WIDTH-1) {
                r = (i * 76982 + j * 22455) % 256;
                g = (i * 49303 + j * 48303) %256;
                b = (i * 29302 + j * 28430) % 256;
                glColor3ub(r,g,b);
                glBegin(GL_QUADS);
                glVertex3d(i+1,j+1,0);
                glVertex3d(i+1,j,0);
                glVertex3d(i+1,j,1);
                glVertex3d(i+1,j+1,1);
                glEnd();
                //DrawQuad(i+1,j+1,i+1,j);
        }
        if (b && j==0) {
                r = (i * 12389 + j * 38202) % 256;
                g = (i * 34348 + j * 23498) %256;
                b = (i * 34583 + j * 34298) % 256;
                glColor3ub(r,g,b);
                glBegin(GL_QUADS);
                glVertex3d(i+1,j,0);
                glVertex3d(i,j,0);
                glVertex3d(i,j,1);
                glVertex3d(i+1,j,1);
                glEnd();
                //DrawQuad(i+1,j,i,j);
        //glPolygonOffset(-25,0.1);
        }
    }
}



Maze::Maze()
{
}

void Maze::Draw()
{
        for(int i=0; i<WIDTH; i++) {
	        for(int j=0; j<HEIGHT; j++){
		        mCells[i][j].Draw(i, j);
                }
        }
}

void Maze::KnockOutWalls()
{       
        srand(time(0));
        mCells[0][0].b = false;
        KnockOutWallsR(0,0);

        //mCells[0][2].l = false;
        int exit_col = rand() % WIDTH;
        //mCells[HEIGHT][WIDTH].t = false;
        mCells[exit_col][HEIGHT-1].t = false;
}

bool Maze::KnockOutWallsR(int i , int j) {
        mCells[i][j].visited = true;
        while (true) {
                enum DIRECTIONS{N,S,E,W};
                std::vector<DIRECTIONS> dirs;
                if (j+1 < HEIGHT and !mCells[i][j+1].visited) {
                        dirs.push_back(N);
                }
                if (j-1 >= 0 and !mCells[i][j-1].visited) {
                        dirs.push_back(S);
                }
                if (i+1 < WIDTH and !mCells[i+1][j].visited) {
                        dirs.push_back(E);
                }
                if (i-1 >= 0 and !mCells[i-1][j].visited) {
                        dirs.push_back(W);
                }

                if (dirs.size() == 0) {
                    return true;
                }

                int r = rand() % dirs.size();
                if (dirs[r] == N) {
                        mCells[i][j].t = false;
                        mCells[i][j+1].b = false;
                        KnockOutWallsR(i,j+1);
                }
                if (dirs[r] == S) {
                        mCells[i][j].b = false;
                        mCells[i][j-1].t = false;
                        KnockOutWallsR(i,j-1);
                }
                if (dirs[r] == E) {
                        mCells[i][j].r = false;
                        mCells[i+1][j].l = false;
                        KnockOutWallsR(i+1,j);
                }
                if (dirs[r] == W) {
                        mCells[i][j].l = false;
                        mCells[i-1][j].r = false;
                        KnockOutWallsR(i-1,j);
                }
        }


}

bool Maze::isSafe(double x, double y, double radius) {
        int i = (int)x;
        int j = (int)y;
        x=x-i;
        y=y-j;
        if (mCells[i][j].r && x+radius > 1.0) {
                return false;
        }else if (mCells[i][j].l && x-radius < 0.0) {
                return false;
        }else if (mCells[i][j].t && y+radius > 1.0) {
                return false;
        }else if (mCells[i][j].b && y-radius < 0.0) {
                return false;
        }

        if (x+radius > 1.0 && y-radius < 0.0) {
                return false;
        }else if (x+radius > 1.0 && y+radius >1.0) {
                return false;
        } else if (x-radius < 0.0 && y-radius < 0.00) {
                return false;
        } else if (x-radius < 0.0 && y+radius > 1.0) {
                return false;
        }

        return true;
}
