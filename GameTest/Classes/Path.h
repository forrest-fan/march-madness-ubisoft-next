#ifndef _PATH_H
#define _PATH_H

class Path
{
public:
	Path(float *pathX, float *pathY, int numCoordinates);
	void Draw();
	int GetLength() { return length; }
	float* GetX() { return x; }
	float* GetY() { return y; }
private:
	float *x;
	float *y;
	int length;
};

#endif