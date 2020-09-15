#include <glut.h>
#include<math.h>
#include<stdio.h>
static double x1 = 0, rotX = 0.0, rotY = 0.0, rot = 0;
int wire = 0, panaroma = 0, open = 0, walk = 0;
float xpos = 0, ypos = 0, zpos = 0, xrot = 0, yrot = 0, angle = 0.0;

static void SpecialKey(int key, int x, int y)
{

	switch (key) {
	case GLUT_KEY_UP:
		rotX -= 0.1;
		glutPostRedisplay();
		break;
	case GLUT_KEY_DOWN:
		rotX += 0.1;
		glutPostRedisplay();
		break;
	case GLUT_KEY_LEFT:
		rotY -= 0.1;
		glutPostRedisplay();
		break;
	case GLUT_KEY_RIGHT:
		rotY += 0.1;
		glutPostRedisplay();
		break;
	}
}

void flag()
{
	glPushMatrix();
	glTranslated(3, 14, -4.3);
	glScaled(12, 7, 0.5);
	if (wire)
		glutWireCube(0.1);
	else
		glutSolidCube(0.1);
	glPopMatrix();
}

void box()
{
	glPushMatrix();
	glScaled(2, 0.5, 2);
	if (wire)
		glutWireCube(1);
	else
		glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.75, 0.5, 0.75);
	if (wire)
		glutWireCube(0.5);
	else
		glutSolidCube(0.5);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.75, 0.5, 0.75);
	if (wire)
		glutWireCube(0.5);
	else
		glutSolidCube(0.5);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-0.75, 0.5, 0.75);
	if (wire)
		glutWireCube(0.5);
	else
		glutSolidCube(0.5);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.75, 0.5, -0.75);
	if (wire)
		glutWireCube(0.5);
	else
		glutSolidCube(0.5);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-0.75, 0.5, -0.75);
	if (wire)
		glutWireCube(0.5);
	else
		glutSolidCube(0.5);
	glPopMatrix();
}



void renderCylinder(float x1, float y1, float z1, float x2, float y2, float z2, float radius, int subdivisions, GLUquadricObj* quadric)
{

	float vx = x2 - x1;
	float vy = y2 - y1;
	float vz = z2 - z1;

	//handle the degenerate case of z1 == z2 with an approximation
	if (vz == 0)
		vz = .0001;

	float v = sqrt(vx * vx + vy * vy + vz * vz);
	float ax = 57.2957795 * acos(vz / v);
	if (vz < 0.0)
		ax = -ax;
	float rx = -vy * vz;
	float ry = vx * vz;
	glPushMatrix();

	//draw the cylinder body
	glTranslatef(x1, y1, z1);
	glRotatef(ax, rx, ry, 0.0);
	gluQuadricOrientation(quadric, GLU_OUTSIDE);
	gluCylinder(quadric, radius, radius, v, subdivisions, 1);

	//draw the first cap
	gluQuadricOrientation(quadric, GLU_INSIDE);
	gluDisk(quadric, 0.0, radius, subdivisions, 1);
	glTranslatef(0, 0, v);

	//draw the second cap
	gluQuadricOrientation(quadric, GLU_OUTSIDE);
	gluDisk(quadric, 0.0, radius, subdivisions, 1);
	glPopMatrix();

}

void renderCylinder_convenient(float x1, float y1, float z1, float x2, float y2, float z2, float radius, int subdivisions)
{
	//the same quadric can be re-used for drawing many cylinders
	GLUquadricObj* quadric = gluNewQuadric();
	gluQuadricNormals(quadric, GLU_SMOOTH);
	renderCylinder(x1, y1, z1, x2, y2, z2, radius, subdivisions, quadric);
	gluDeleteQuadric(quadric);
}


void fort(double rang)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	if (walk)
	{
		glRotatef(xrot, 1.0, 0.0, 0.0);  //rotate our camera on 
		glRotatef(yrot, 0.0, 1.0, 0.0);  //rotate our camera on the 
		glTranslated(-xpos, -ypos, -zpos);
	}
	else
		if (panaroma)
			gluLookAt(0.5, 15, 1, 0, 9, -7, 0, 1, 0);
	if (!walk)
		glTranslatef(0.0f, -5.0f, -48.0f);
	else
	{
		glTranslatef(0, 1, -75);
		glScaled(2, 2, 2.5);
	}
	glRotatef(rang, 0.0f, 1.0f, 0.0f);
	glPushMatrix();
	glTranslated(0, 0, -10);
	glScaled(1, 1, 1.3);

	glColor3f(250 / 255.0, 220 / 255.0, 50 / 255.0);
	//Draw fleft cylinder
	glPushMatrix();
	glTranslatef(-22.5, -3.0, 23);
	renderCylinder_convenient(0, 0, 0, 0, 5, 0, 1.4, 20);
	glPopMatrix();

	//Draw fright cylinder
	glPushMatrix();
	glTranslatef(22.5, -3.0, 23);
	renderCylinder_convenient(0, 0, 0, 0, 5, 0, 1.4, 20);
	glPopMatrix();


	//Draw bleft cylinder
	glPushMatrix();
	glTranslatef(-22.5, -3.0, -8.0);
	renderCylinder_convenient(0, 0, 0, 0, 5, 0, 1.4, 20);
	glPopMatrix();

	//Draw bright cylinder
	glPushMatrix();
	glTranslatef(22.5, -3.0, -8.0);
	renderCylinder_convenient(0, 0, 0, 0, 5, 0, 1.4, 20);
	glPopMatrix();



	// Draw the left Wall 
	glPushMatrix();
	glScaled(0.3, 1.5, 15);
	glTranslatef(0.0, 0.0, -0.5);
	glTranslatef(-75, -1, 1.0);
	if (wire)
		glutWireCube(2);
	else
		glutSolidCube(2);
	glPopMatrix();

	// Draw right wall

	glPushMatrix();
	glScaled(0.3, 1.5, 15);
	glTranslatef(0.0, 0.0, -0.5);
	glTranslatef(75, -1, 1.0);
	if (wire)
		glutWireCube(2);
	else
		glutSolidCube(2);
	glPopMatrix();

	// Draw rear wall

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glScaled(0.3, 1.5, 23);
	glTranslatef(0.0, 0.0, -0.5);
	glTranslatef(26.5, -1.0, 0.5);
	if (wire)
		glutWireCube(2);
	else
		glutSolidCube(2);
	glPopMatrix();
	//Draw bottom

	glColor3f(0 / 255.0, 250 / 255.0, 0 / 255.0);
	glPushMatrix();
	glTranslated(0, -5, 8);
	glScaled(70, 1, 55);
	if (wire)
		glutWireCube(1);
	else
		glutSolidCube(1);
	glPopMatrix();

	//Draw bottom
	glColor3f(200 / 255.0, 180 / 255.0, 50 / 255.0);
	glPushMatrix();
	glTranslated(0, -3.5, 10);
	glScaled(50, 0.5, 39);
	if (wire)
		glutWireCube(1);
	else
		glutSolidCube(1);
	glPopMatrix();

	glColor3f(250 / 255.0, 220 / 255.0, 50 / 255.0);

	//Gate wall 1
	glPushMatrix();
	glScaled(9, 1.5, 0.5);
	glTranslatef(-1.5, -1, 47.0);
	if (wire)
		glutWireCube(2);
	else
		glutSolidCube(2);
	glPopMatrix();
	//Gate wall 2
	glPushMatrix();
	glScaled(9, 1.5, 0.5);
	glTranslatef(1.5, -1, 47.0);
	if (wire)
		glutWireCube(2);
	else
		glutSolidCube(2);
	glPopMatrix();

	//Entrance l
	glPushMatrix();
	glScaled(1.2, 2.6, 0.9);
	glTranslatef(-4.6, -0.2, 26);
	if (wire)
		glutWireCube(2);
	else
		glutSolidCube(2);
	glPopMatrix();
	//Entrance r
	glPushMatrix();
	glScaled(1.2, 2.6, 0.9);
	glTranslatef(4.6, -0.2, 26);
	if (wire)
		glutWireCube(2);
	else
		glutSolidCube(2);
	glPopMatrix();

	//Entrance t
	glPushMatrix();
	glScaled(4.4, 1, 0.9);
	glTranslatef(0, 2, 26);
	if (wire)
		glutWireCube(2);
	else
		glutSolidCube(2);
	glPopMatrix();
	//Entrance t1
	glPushMatrix();
	glScaled(4.4, 1, 0.9);
	glTranslatef(0, 3, 26);
	if (wire)
		glutWireCube(1.5);
	else
		glutSolidCube(1.5);
	glPopMatrix();
	//Entrance t2
	glPushMatrix();
	glScaled(4.4, 1, 0.9);
	glTranslatef(0, 4, 26);
	if (wire)
		glutWireCube(1.0);
	else
		glutSolidCube(1.0);
	glPopMatrix();

	glColor3d(230, 232, 250);

	//Audi 1
	glPushMatrix();
	glTranslated(0, 4.78, 23.5);
	if (wire)
		glutWireTorus(0.08, 0.3, 10, 20);
	else
		glutSolidTorus(0.08, 0.3, 10, 20);
	glPopMatrix();
	//Audi 2
	glPushMatrix();
	glTranslated(0.5, 4.78, 23.5);
	if (wire)
		glutWireTorus(0.08, 0.3, 10, 20);
	else
		glutSolidTorus(0.08, 0.3, 10, 20);
	glPopMatrix();
	//Audi 3
	glPushMatrix();
	glTranslated(-0.5, 4.78, 23.5);
	if (wire)
		glutWireTorus(0.08, 0.3, 10, 20);
	else
		glutSolidTorus(0.08, 0.3, 10, 20);
	glPopMatrix();

	glColor3f(139 / 255.0, 69 / 255.0, 19 / 255.0);

	//Gate1
	glPushMatrix();
	if (open)
		glRotatef(-10, 0, 1, 0);
	glScaled(4.2, 5, 0.5);
	glTranslatef(-0.5, -0.2, 46);
	if (wire)
		glutWireCube(1.0);
	else
		glutSolidCube(1.0);
	glPopMatrix();
	//Gate2
	glPushMatrix();
	if (open)
		glRotatef(10, 0, 1, 0);
	glScaled(4.2, 5, 0.5);
	glTranslatef(0.5, -0.2, 46);
	if (wire)
		glutWireCube(1.0);
	else
		glutSolidCube(1.0);
	glPopMatrix();


	glPopMatrix();

	glTranslated(0.5, -1.5, -6);
	glPopMatrix();

	//Draw the main cube

	//Draw front wall
	glColor3f(200 / 255.0, 150 / 255.0, 150 / 255.0);
	glPushMatrix();
	glTranslated(-7, -1, 17);
	glScaled(18, 8, 0.8);
	if (wire)
		glutWireCube(1.0);
	else
		glutSolidCube(1.0);
	glPopMatrix();

	//Draw sidewall
	glPushMatrix();
	glRotated(-90, 0, 1, 0);
	glTranslated(7, -1, 16);
	glScaled(21, 8, 0.8);
	if (wire)
		glutWireCube(1.0);
	else
		glutSolidCube(1.0);
	glPopMatrix();

	//Draw back wall
	glPushMatrix();
	glTranslated(-9.75, -1, -3.6);
	glScaled(13.25, 8, 0.8);
	if (wire)
		glutWireCube(1.0);
	else
		glutSolidCube(1.0);
	glPopMatrix();

	glColor3f(150 / 255.0, 100 / 255.0, 50 / 255.0);

	//Draw big cylinder
	glPushMatrix();
	glTranslated(-10.3, -2.5, -2.2);
	renderCylinder_convenient(0, 0, 0, 0, 8, 0, 4, 20);
	glPopMatrix();
	glColor3f(255 / 255.0, 0 / 255.0, 0 / 255.0);
	//Draw big cone
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	glTranslated(-10.3, 2, 5);
	if (wire)
		glutWireCone(7, 6, 15, 15);
	else
		glutSolidCone(7, 6, 15, 15);
	glPopMatrix();

	//Draw cube
	glColor3f(200 / 255.0, 150 / 255.0, 150 / 255.0);
	glPushMatrix();
	glTranslated(7.6, -1, 4);
	glScaled(3, 2.5, 7);
	if (wire)
		glutWireCube(4.0);
	else
		glutSolidCube(4.0);
	glPopMatrix();
	glColor3f(238 / 255.0, 44 / 255.0, 44 / 255.0);
	//Draw sphere
	glPushMatrix();

	glTranslated(8, 4, 7);
	if (wire)
		glutWireSphere(5, 25, 25);
	else
		glutSolidSphere(5, 25, 25);
	glPopMatrix();

	glColor3f(200 / 255.0, 150 / 255.0, 150 / 255.0);

	glPushMatrix();
	glTranslatef(0.0, 0.0, -0.5);
	glScaled(1.6, 3, 2);
	if (wire)
		glutWireCube(4);
	else
		glutSolidCube(4);
	glPopMatrix();

	glColor3f(150 / 255.0, 100 / 255.0, 75 / 255.0);

	//Draw fr cylinder
	glPushMatrix();
	glTranslated(.5, 6, 1.0);
	renderCylinder_convenient(0, 0, 0, 0, 4, 0, 0.7, 20);
	glPopMatrix();

	//Draw fl cylinder
	glPushMatrix();
	glTranslated(-9, -2.4, 9.0);
	renderCylinder_convenient(0, 0, 0, 0, 12, 0, 1.3, 20);
	glPopMatrix();

	//Draw br cylinder
	glPushMatrix();
	glTranslated(2.9, -2.4, -5.0);
	renderCylinder_convenient(0, 0, 0, 0, 20, 0, 2, 20);
	glPopMatrix();

	//Draw bm cylinder
	glPushMatrix();
	glTranslated(-1.2, -2.45, -4.1);
	renderCylinder_convenient(0, 0, 0, 0, 16, 0, 1.5, 50);
	glPopMatrix();

	glPushMatrix();
	glTranslated(7, -2.45, -4.1);
	renderCylinder_convenient(0, 0, 0, 0, 13, 0, 1.5, 50);
	glPopMatrix();

	glColor3f(1, 0, 0);

	//Draw cone1
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	glTranslated(-1.2, 4.1, 13);
	if (wire)
		glutWireCone(2.2, 3.5, 15, 15);
	else
		glutSolidCone(2.2, 3.5, 15, 15);
	glPopMatrix();

	//Draw cone2
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	glTranslated(2.8, 4.8, 17);
	if (wire)
		glutWireCone(3, 5, 15, 15);
	else
		glutSolidCone(3, 5, 15, 15);
	glPopMatrix();

	//Draw cone3
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	glTranslated(7, 4.1, 10);
	if (wire)
		glutWireCone(2.2, 3.5, 15, 15);
	else
		glutSolidCone(2.2, 3.5, 15, 15);
	glPopMatrix();

	glScaled(1.8, 1.6, 1.8);
	glTranslated(-5, 6, 5);
	glColor3f(150 / 255.0, 100 / 255.0, 100 / 255.0);
	//Draw box
	box();
	glColor3d(255, 215, 0);
	glPushMatrix();
	glTranslated(5.3, 1, -4.35);
	glRotated(rot, 1, 1, 1);
	if (wire)
		glutWireTorus(0.15, 0.4, 10, 20);
	else
		glutSolidTorus(0.15, 0.4, 10, 20);
	glPopMatrix();

	glPushMatrix();
	glColor3d(230, 232, 250);
	glTranslated(5.3, 1.2, -4.35);
	glRotated(rot, 0, 0, 0);
	if (wire)
		glutWireTorus(0.05, 0.5, 10, 20);
	else
		glutSolidTorus(0.05, 0.5, 5, 20);
	glPopMatrix();
	glColor3f(0.439216, 0.858824, 0.576471);
	glPushMatrix();
	// fLAG post
	glTranslated(6.5, 7.5, -7.7);
	renderCylinder_convenient(0, 0, 0, 0, 3, 0, 0.03, 20);
	glPopMatrix();

	glTranslated(3, -4, -3.35);
	glColor3f(200 / 255.0, 150 / 255.0, 30 / 255.0);
	glPushMatrix();
	glTranslated(-11, 0.4, -9.6);
	box();
	glPopMatrix();

	glPushMatrix();
	glTranslated(14.2, 0.4, 12.75);
	box();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-11, 0.4, 12.75);
	box();
	glPopMatrix();

	glPushMatrix();
	glTranslated(14.2, 0.4, -9.6);
	box();
	glPopMatrix();
	glColor3f(1, 157 / 255, 50);
	flag();
	
	glTranslated(-3.2, -10, 17.5);
	glColor3f(1, 157 / 255, 50);
	flag();
	glPushMatrix();
	// fLAG post
	glColor3f(0, 0, 0);
	glTranslated(3.5, 11, -4.32);
	renderCylinder_convenient(0, 0, 0, 0, 3.5, 0, 0.03, 20);
	glPopMatrix();

	rot += 1;
	glFlush();
	glutSwapBuffers();
}




void rotater()
{
	x1 += 0.05;
	fort(x1);
}

void init()
{
	glClearColor(0.690196078, 0.87843137, 0.90196078, 1.0);
	glViewport(0, 0, 1050, 680);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, (GLfloat)1050 / (GLfloat)680, 0.2f, 200.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearDepth(2.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
}

void Display()
{

	GLfloat mat_ambient[] = { 0.7f,0.7f,0.7f,1.0f };
	GLfloat mat_diffuse[] = { 0.5f,0.5f,.5f,1.0f };
	GLfloat mat_specular[] = { 1.0f,1.0f,1.0f,1.0f };
	GLfloat mat_shininess[] = { 100.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	GLfloat lightIntensity[] = { 0.3f,0.3f,0.3f,1.0f };
	GLfloat light_position[] = { 2.0f,5.0f,6.0f,0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);
	glFlush();
	glutSwapBuffers();
	fort(x1);

}

void keyboard(unsigned char key, int x, int y) {
	if (key == '+')//going up
	{
		xrot += 1;
		if (xrot > 360) xrot -= 360;
	}

	if (key == '-')//going down
	{
		xrot -= 1;
		if (xrot < -360) xrot += 360;
	}

	if (key == '8')//going front
	{
		float xrotrad, yrotrad;
		yrotrad = (yrot / 180 * 3.141592654f);
		xrotrad = (xrot / 180 * 3.141592654f);
		xpos += float(sin(yrotrad));
		zpos -= float(cos(yrotrad));
		ypos -= float(sin(xrotrad));
	}

	if (key == '2')//going back
	{
		float xrotrad, yrotrad;
		yrotrad = (yrot / 180 * 3.141592654f);
		xrotrad = (xrot / 180 * 3.141592654f);
		xpos -= float(sin(yrotrad));
		zpos += float(cos(yrotrad));
		ypos += float(sin(xrotrad));
	}

	if (key == '6')//going right
	{
		yrot += 1;
		if (yrot > 360) yrot -= 360;
	}

	if (key == '4')//going left
	{
		yrot -= 1;
		if (yrot < -360)yrot += 360;
	}
	if (key == 27)
		exit(0);
	if (key == '5')open = !open;
	Display();
}

void menu(int id)
{
	switch (id)
	{
	case 1:glutIdleFunc(rotater);
		break;
	case 2:panaroma = 0;
		break;
	case 3:panaroma = 1;
		break;
	case 4:wire = 1;
		break;
	case 5:wire = 0;
		break;
	case 6: walk = !walk;
		break;
	case 7: exit(0);
		break;
	}
	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}


int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	printf("\n\n\t\t\t\tGLOBAL ACADEMY OF TECHNOLOGY\n\n\t\t\tDEPARTMENT OF COMPUTER SCIENCE AND ENGINEERING\n");
	printf("\n\n\t\t\t\t CG MINI PROJECT ON   \" CASTLE\"\n\n"); printf("\n\n\n\n\n\n\n\n\n\t\t\t\t NAME: YUVARAJ P \n ");
	printf("\t\t\t	 USN: 1GA17CS181 \n");
	printf("\n\t\t\t\t UNDER THE GUIDANCE OF:\n\t\t\t Mrs. BHAGYASHREE R HANJI, Assistant Professor \n");
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(950, 700);
	glutInitWindowPosition(50, 0);
	glutCreateWindow("Castle");
	glutDisplayFunc(Display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(SpecialKey);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glutCreateMenu(menu);
	glutAddMenuEntry("Rotate", 1);
	glutAddMenuEntry("Normal view", 2);
	glutAddMenuEntry("Bird Eye view", 3);
	glutAddMenuEntry("Wired structure", 4);
	glutAddMenuEntry("Solid Structure", 5);
	glutAddMenuEntry("Walk Mode", 6);
	glutAddMenuEntry("Exit", 7);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	init();
	glutMainLoop();
	return 0;
}
