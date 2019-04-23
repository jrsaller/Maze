#pragma once
const int WIDTH = 6;
const int HEIGHT = 6;
const double MARGIN = .5;

struct Cell
{
	bool l, t, r, b,visited;
        double red,green,blue;
	Cell();
        double getRed();
        double getGreen();
        double getBlue();
        void setRed(double value);
        void setGreen(double value);
        void setBlue(double value);
	void Draw(int i, int j);
};

class Maze
{
public:
	Maze();
	void Draw();
	void KnockOutWalls();
        bool KnockOutWallsR(int i , int j);
        bool isSafe(double x,double y,double radius);
private:
	Cell mCells[WIDTH][HEIGHT];
};
