#include "glesDrawing.h"
#include <AR/gsub_es2.h>


void drawCube()
{
	int i;
	const GLfloat cube_vertices[8][3] = {
		/* +z */{ 0.5f, 0.5f, 0.5f }, { 0.5f, -0.5f, 0.5f }, { -0.5f, -0.5f, 0.5f }, { -0.5f, 0.5f, 0.5f },
		/* -z */{ 0.5f, 0.5f, -0.5f }, { 0.5f, -0.5f, -0.5f }, { -0.5f, -0.5f, -0.5f }, { -0.5f, 0.5f, -0.5f } };
	const GLubyte cube_vertex_colors[8][4] = {
		{ 255, 255, 255, 255 }, { 255, 255, 0, 255 }, { 0, 255, 0, 255 }, { 0, 255, 255, 255 },
		{ 255, 0, 255, 255 }, { 255, 0, 0, 255 }, { 0, 0, 0, 255 }, { 0, 0, 255, 255 } };
	const GLubyte cube_vertex_colors_black[8][4] = {
		{ 0, 0, 0, 255 }, { 0, 0, 0, 255 }, { 0, 0, 0, 255 }, { 0, 0, 0, 255 },
		{ 0, 0, 0, 255 }, { 0, 0, 0, 255 }, { 0, 0, 0, 255 }, { 0, 0, 0, 255 } };
	const GLushort cube_faces[6][4] = { /* ccw-winding */
		/* +z */{ 3, 2, 1, 0 }, /* -y */{ 2, 3, 7, 6 }, /* +y */{ 0, 1, 5, 4 },
		/* -x */{ 3, 0, 4, 7 }, /* +x */{ 1, 2, 6, 5 }, /* -z */{ 4, 5, 6, 7 } };

	glVertexAttribPointer(ATTRIBUTE_VERTEX, 3, GL_FLOAT, GL_FALSE, 0, cube_vertices);
	glEnableVertexAttribArray(ATTRIBUTE_VERTEX);
	glVertexAttribPointer(ATTRIBUTE_COLOUR, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, cube_vertex_colors);
	glEnableVertexAttribArray(ATTRIBUTE_COLOUR);

	for (i = 0; i < 6; i++) {
		glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_SHORT, &(cube_faces[i][0]));
	}
	glVertexAttribPointer(ATTRIBUTE_COLOUR, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, cube_vertex_colors_black);
	glEnableVertexAttribArray(ATTRIBUTE_COLOUR);
	for (i = 0; i < 6; i++) {
		glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_SHORT, &(cube_faces[i][0]));
	}
}

void drawGrid()
{
	glLineWidth(1.0f);
	int i, j;
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 8; j++)
		{
			float x0 = i * 1;
			float y0 = j * 1;

			float x1 = x0 + 1;
			float y1 = y0 + 1;

			const GLfloat cube_vertices[8][3] = {
				{ x0, y0, 0.0f }, { x1, y0, 0.0f }, { x1, y1, 0.0f }, { x0, y1, 0.0f }
			};

			const GLubyte cube_vertex_colors[8][4] = {
				{ 192, 192, 192, 255 }, { 192, 192, 192, 255 },
				{ 192, 192, 192, 255 }, { 192, 192, 192, 255 }
			};

			const GLushort cube_faces[4] = {
				0, 1, 2, 3
			};

			glVertexAttribPointer(ATTRIBUTE_VERTEX, 3, GL_FLOAT, GL_FALSE, 0, cube_vertices);
			glEnableVertexAttribArray(ATTRIBUTE_VERTEX);

			glVertexAttribPointer(ATTRIBUTE_COLOUR, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, cube_vertex_colors);
			glEnableVertexAttribArray(ATTRIBUTE_COLOUR);

			glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_SHORT, cube_faces);
		}
	}
}

void drawCoordinate()
{
	int i;
	const GLfloat cube_vertices[6][3] = {
		{ 0.0f, 0.0f, 0.0f }, { 0.5f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.5f, 0.0f },
		{ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.5f }
	};

	const GLubyte cube_vertex_colors[6][4] = {
		{ 255, 255, 255, 255 }, { 255, 0, 0, 255 },
		{ 255, 255, 255, 255 }, { 0, 255, 0, 255 },
		{ 255, 255, 255, 255 }, { 0, 0, 255, 255 }
	};

	const GLushort cube_faces[3][2] = {
		{ 0, 1 }, { 2, 3 }, { 4, 5 }
	};

	glVertexAttribPointer(ATTRIBUTE_VERTEX, 3, GL_FLOAT, GL_FALSE, 0, cube_vertices);
	glEnableVertexAttribArray(ATTRIBUTE_VERTEX);

	glVertexAttribPointer(ATTRIBUTE_COLOUR, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, cube_vertex_colors);
	glEnableVertexAttribArray(ATTRIBUTE_COLOUR);

	glLineWidth(2.0f);
	glDrawElements(GL_LINES, 6, GL_UNSIGNED_SHORT, &(cube_faces[0][0]));
}

void draw4marker(int index)
{
	if (index == 0) {
		drawCoordinate();
		drawGrid();
	}

	if (index == 1) {
		drawCube();
	}
}

void draw_model(const Modeling* model)
{
	DataType type = model->type;

	if (type == DT_POINT) {
		const MPoint* pPoint = (MPoint*)model;

		int dlt = 10;
		const GLfloat points[6][3] = {
			{ pPoint->x - dlt, pPoint->y, pPoint->z }, { pPoint->x + dlt, pPoint->y, pPoint->z },
			{ pPoint->x, pPoint->y - dlt, pPoint->z }, { pPoint->x, pPoint->y + dlt, pPoint->z },
			{ pPoint->x, pPoint->y, pPoint->z - dlt }, { pPoint->x, pPoint->y, pPoint->z + dlt }
		};
		const GLubyte point_colors[6][4] = { 
			{ 255, 0, 0, 255 }, { 255, 0, 0, 255 },
			{ 255, 0, 0, 255 }, { 255, 0, 0, 255 },
			{ 255, 0, 0, 255 }, { 255, 0, 0, 255 }
		};
		const GLushort point_index[3][2] = { { 0, 1 }, { 2, 3 }, {4, 5} };

		glVertexAttribPointer(ATTRIBUTE_VERTEX, 3, GL_FLOAT, GL_FALSE, 0, points);
		glEnableVertexAttribArray(ATTRIBUTE_VERTEX);

		glVertexAttribPointer(ATTRIBUTE_COLOUR, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, point_colors);
		glEnableVertexAttribArray(ATTRIBUTE_COLOUR);

		glLineWidth(2.0f);
		glDrawElements(GL_LINES, 6, GL_UNSIGNED_SHORT, &(point_index[0][0]));
	}

	if (type == DT_POLYLINE) {
		const MPolyline* pPoly = (MPolyline*)model;

		vector<GLfloat> points;
		vector<GLubyte> point_colors;
		vector<GLushort> point_index;

		for (size_t i = 0; i < pPoly->points.size(); i++) {
			points.push_back(pPoly->points[i].x);
			points.push_back(pPoly->points[i].y);
			points.push_back(pPoly->points[i].z);

			point_colors.push_back(255);
			point_colors.push_back(0);
			point_colors.push_back(0);
			point_colors.push_back(255);

			point_index.push_back(i);
		}

		glVertexAttribPointer(ATTRIBUTE_VERTEX, 3, GL_FLOAT, GL_FALSE, 0, &points[0]);
		glEnableVertexAttribArray(ATTRIBUTE_VERTEX);

		glVertexAttribPointer(ATTRIBUTE_COLOUR, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, &point_colors[0]);
		glEnableVertexAttribArray(ATTRIBUTE_COLOUR);

		glLineWidth(2.0f);
		glDrawElements(GL_LINE_LOOP, pPoly->points.size(), GL_UNSIGNED_SHORT, &point_index[0]);
	}

	if (type == DT_PATH) {
		const MPath* pPath = (MPath*)model;

		vector<GLfloat> points;
		vector<GLubyte> point_colors;
		vector<GLushort> point_index;

		for (size_t i = 0; i < pPath->points.size(); i++) {
			points.push_back(pPath->points[i].x);
			points.push_back(pPath->points[i].y);
			points.push_back(pPath->points[i].z);

			point_colors.push_back(255);
			point_colors.push_back(0);
			point_colors.push_back(0);
			point_colors.push_back(255);

			point_index.push_back(i);
		}

		glVertexAttribPointer(ATTRIBUTE_VERTEX, 3, GL_FLOAT, GL_FALSE, 0, &points[0]);
		glEnableVertexAttribArray(ATTRIBUTE_VERTEX);

		glVertexAttribPointer(ATTRIBUTE_COLOUR, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, &point_colors[0]);
		glEnableVertexAttribArray(ATTRIBUTE_COLOUR);

		glLineWidth(2.0f);
		glDrawElements(GL_LINE_STRIP, pPath->points.size(), GL_UNSIGNED_SHORT, &point_index[0]);
	}

	if (type == DT_MODEL3D) {
		const Model3D* pModel = (Model3D*)model;

		if (pModel->points.size() > 0) {
			vector<GLubyte> point_colors;
			for (size_t i = 0; i < pModel->points.size() / 3; i++) {
				point_colors.push_back(255);
				point_colors.push_back(0);
				point_colors.push_back(0);
				point_colors.push_back(255);
			}

			glVertexAttribPointer(ATTRIBUTE_VERTEX, 3, GL_FLOAT, GL_FALSE, 0, &(pModel->points[0]));
			glEnableVertexAttribArray(ATTRIBUTE_VERTEX);

			if (pModel->normals.size() > 0) {
				glVertexAttribPointer(ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, &(pModel->normals[0]));
				glEnableVertexAttribArray(ATTRIBUTE_NORMAL);
			}

			glVertexAttribPointer(ATTRIBUTE_COLOUR, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, &point_colors[0]);
			glEnableVertexAttribArray(ATTRIBUTE_COLOUR);

			if (pModel->edges.size() > 0)
				glDrawElements(GL_LINES, pModel->edges.size(), GL_UNSIGNED_INT, &(pModel->edges[0]));

			if (pModel->triangles.size() > 0)
				glDrawElements(GL_TRIANGLES, pModel->triangles.size(), GL_UNSIGNED_INT, &(pModel->triangles[0]));
		}
	}
}

void draw_models(int index, const vector<Modeling*>& models)
{
	if (index == 0) {
		for (size_t i = 0; i < models.size(); i++) {
			const Modeling* pModeling = models[i];
			draw_model(pModeling);
		}
	}
}
