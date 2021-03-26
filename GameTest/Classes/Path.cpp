#include "stdafx.h"
#include "stdlib.h"
#include "math.h"
#include "..\\App\\app.h"
#include ".\\Path.h"
#include "..\\Constants.h"

Path::Path(float *pathX, float *pathY, int numCoordinates) {
	x = pathX;
	y = pathY;
	length = numCoordinates;
}

void Path::Draw() {
	float prevX = *x;
	float prevY = *y;
	for (int i = 1; i < length - 1; i++) {
		App::DrawLine(prevX, prevY, *(x + i), *(y + i));
		prevX = *(x + i);
		prevY = *(y + i);
	}
	App::DrawLine(prevX, prevY, *(x + length - 1), *(y + length - 1)); // Draw last line outside for loop bc for causes outofbounds
}