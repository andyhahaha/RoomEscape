#include"../h/ClueAction.h"
#include <opencv2/contrib/contrib.hpp> 
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/legacy/legacy.hpp>
#include <opencv2/objdetect/objdetect.hpp>

/*void ClueHit(int x, int y){
	vector<Clue>::iterator it_clue;


	GLdouble  winX, winY, winZ;
	GLdouble posX, posY, posZ;
	int screenX, screenY;
	int maxX = -10000, minX = 10000, maxY = -10000, minY = 10000;
	int i;
	//glGetIntegerv(GL_VIEWPORT, viewport);
	//glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	//glGetDoublev(GL_PROJECTION_MATRIX, projection);


	for (it_clue = ClueOnScreen.begin(); it_clue != ClueOnScreen.end(); ++it_clue) {
		maxX = -10000;
		minX = 10000;
		maxY = -10000;
		minY = 10000;
		for (i = 0; i < 8; i++){
			posX = it_clue->obj_corner()[i].x;
			posY = it_clue->obj_corner()[i].y;
			posZ = it_clue->obj_corner()[i].z;
			gluProject(posX, posY, posZ, modelview, projection, viewport, &winX, &winY, &winZ);
			screenX = winX;
			screenY = viewport[3] - (float)winY;
			if (maxX < screenX)
				maxX = screenX;
			if (maxY < screenY)
				maxY = screenY;
			if (minX > screenX)
				minX = screenX;
			if (minY > screenY)
				minY = screenY;
		}
		if (minX < 0)
			minX = width + 1;
		if (minY < 0)
			minY = height + 1;
		/*cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		cout << "clue = " << it_clue->clue_name() << endl;
		cout << "maxX = " << maxX << endl;
		cout << "minX = " << minX << endl;
		cout << "maxY = " << maxY << endl;
		cout << "minY = " << minY << endl;


		if (x <= maxX && x >= minX && y <= maxY && y >=minY){

		clueBox.InsertItem(*it_clue);
		cout << "~~~~~~~~~~~~~~~~~~Insert clue = " << it_clue->clue_name() << endl;
		}
	}
}*/