class Rat {
        public:
                Rat();
                Rat(double x, double y, double degrees);
                void ScurryForward(Maze& maze);
                void RotateLeft();
                void RotateRight();
                void Draw();
                double getX();
                double getY();
                double getDX();
                double getDY();
        private:
                double mX,mY,mDegrees;


};
