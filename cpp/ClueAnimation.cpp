#include "D:\RoomEscape\h\gameRun.h"

void drawPageNumber(char *bookpage);

/* typeCode: When hit the clue that is on the safe1 (number 1~9 , "clear" and "OK")
*  
*  clue - the clue that user hit
*  code - the current code number
*  
*  Return 0 means the code is not right.
*  Return 1 means the code is right.
*/

int typeCode(Clue clue, char *code)
{
	if (!clue.clue_name().compare("OK"))
	{
		if (code[0] == '8' && code[1] == '7' && code[2] == '8' && code[3] == '7')
			return 1;
	}
	else if (!clue.clue_name().compare("clear"))
	{
		code[0] = '0';
		code[1] = '0';
		code[2] = '0';
		code[3] = '0';
	}
	else	//hit the number 1~9
	{
		/* Find the first place that the number is not 0. */
		int current_code = 0;
		for (; code[current_code] != '0'; current_code++);	
		if (current_code >= 4)	return 0;

		code[current_code] = clue.clue_name()[0];
	}

	drawCode(code);
	cout << "code0 = " << code[0] << endl << "code1 = " << code[1] << endl << "code2 = " << code[2] << endl << "code3 = " << code[3] << endl;
	return 0;
}


void drawCode(char *code)
{
	int space;
	space = (int)ceil(4.0 / 1080.0*width);
	cout << "space = " << space << endl;

	char spacechar = ' ';

	//draw code
	glColor3f(0, 0, 0);
	glMatrixMode(GL_PROJECTION);					// change the current matrix to PROJECTION
	double matrix[16];								// 16 doubles in stack memory
	glGetDoublev(GL_PROJECTION_MATRIX, matrix);		// get the values from PROJECTION matrix to local variable
	glLoadIdentity();								// reset PROJECTION matrix to identity matrix
	glOrtho(0, width, 0, height, -5, 5);			// orthographic perspective
	glMatrixMode(GL_MODELVIEW);						// change current matrix to MODELVIEW matrix again
	glLoadIdentity();								// reset it to identity matrix
	glPushMatrix();									// push current state of MODELVIEW matrix to stack
	glLoadIdentity();								// reset it again. (may not be required, but it my convention)
	glRasterPos2i(width*0.445, height*0.705);		// raster position in 2D

	for (int i = 0; i<3; i ++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (int)code[i]); // generation of characters in our text with 9 by 15 GLU font

		for (int j = 0; j < space; j++)
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (int)spacechar);
		}
	}
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (int)code[3]);


	// Make sure that the polygon mode is set so we draw the polygons filled
	// (save the state first so we can restore it).

	GLint polygonMode[2];
	glGetIntegerv(GL_POLYGON_MODE, polygonMode);
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_FILL);

	// Set up the virtual camera, projecting using simple ortho so we can draw the background image.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 1.0, 0.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	// Clear the depth buffer so the texture forms the background.
	glClear(GL_DEPTH_BUFFER_BIT);

	// Restore the polygon mode state.
	glPolygonMode(GL_FRONT, polygonMode[0]);
	glPolygonMode(GL_BACK, polygonMode[1]);
}




int bookInside(Clue clue, char *bookpage)
{
	if (!clue.clue_name().compare("OK"))
	{
		if (bookpage[0] == '7' && bookpage[1] == '2' && bookpage[2] == '3')
			return 1;
		else
			return -1;
	}
	else if (!clue.clue_name().compare("clear"))
	{
		bookpage[0] = 0;
		bookpage[1] = 0;
		bookpage[2] = 0;
	}
	else	//hit the number 1~9
	{
		/* Find the first place that the number is not 0. */
		int current_num = 0;
		for (; bookpage[current_num] != '0'; current_num++);
		if (current_num >= 3)	return 0;

		bookpage[current_num] = clue.clue_name()[0];
	}

	drawPageNumber(bookpage);

	return 0;
}



void drawPageNumber(char *bookpage)
{
	int space;
	space = (int)ceil(4.0 / 1080.0*width);
	cout << "space = " << space << endl;

	char spacechar = ' ';

	//draw code
	glColor3f(0, 0, 0);
	glMatrixMode(GL_PROJECTION);					// change the current matrix to PROJECTION
	double matrix[16];								// 16 doubles in stack memory
	glGetDoublev(GL_PROJECTION_MATRIX, matrix);		// get the values from PROJECTION matrix to local variable
	glLoadIdentity();								// reset PROJECTION matrix to identity matrix
	glOrtho(0, width, 0, height, -5, 5);			// orthographic perspective
	glMatrixMode(GL_MODELVIEW);						// change current matrix to MODELVIEW matrix again
	glLoadIdentity();								// reset it to identity matrix
	glPushMatrix();									// push current state of MODELVIEW matrix to stack
	glLoadIdentity();								// reset it again. (may not be required, but it my convention)
	glRasterPos2i(width*0.44, height*0.73);		// raster position in 2D

	for (int i = 0; i<3; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (int)bookpage[i]); // generation of characters in our text with 9 by 15 GLU font

		for (int j = 0; j < space; j++)
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (int)spacechar);
		}
	}
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (int)bookpage[3]);


	// Make sure that the polygon mode is set so we draw the polygons filled
	// (save the state first so we can restore it).

	GLint polygonMode[2];
	glGetIntegerv(GL_POLYGON_MODE, polygonMode);
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_FILL);

	// Set up the virtual camera, projecting using simple ortho so we can draw the background image.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 1.0, 0.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	// Clear the depth buffer so the texture forms the background.
	glClear(GL_DEPTH_BUFFER_BIT);

	// Restore the polygon mode state.
	glPolygonMode(GL_FRONT, polygonMode[0]);
	glPolygonMode(GL_BACK, polygonMode[1]);
}