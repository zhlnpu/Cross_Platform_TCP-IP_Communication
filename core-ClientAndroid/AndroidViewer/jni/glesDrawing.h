#pragma once

#include "listenling.h"

// Indices of of GL ES program attributes.
enum {
	ATTRIBUTE_VERTEX,
	ATTRIBUTE_NORMAL,
	ATTRIBUTE_COLOUR,
	ATTRIBUTE_COUNT
};

void drawGrid();
void drawCube();
void drawCoordinate();

void draw_model(const Modeling* model);

void draw4marker(int index);
void draw_models(int index, const vector<Modeling*>& models);
