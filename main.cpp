#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#define  COL 1800.0
#define ROW 1000.0
#define fps 30


double col=COL,row=ROW;

void display_callback();
void reshape_callback(int w,int h);
void timer_callback(int);


struct ant{
	int x;
	int y;
	float cr;
	float cg;
	float cb;
	int dir;
};

ant ants[1000];

void init(){
	//glutFullScreen();
	glClearColor(1.0,1.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	srand(time(NULL));
	for(ant &act: ants){
		act.x = rand()%(int)col;
		act.y = rand()%(int)row;
		act.dir = rand()%(int)4;
		act.cr = (rand()%100)/100.0;
		act.cg = (rand()%100)/100.0;
		act.cb = (rand()%100)/100.0;
	}

}
int main(int argc,char **argv) {
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(col,row);
	glutCreateWindow("langtons ant");
	//glutFullScreen();
	glutDisplayFunc(display_callback);
	glutReshapeFunc(reshape_callback);
	glutTimerFunc(0,timer_callback,0);
	init();
	glutMainLoop();
	return 0;
}


void display_callback(){
	//glClear(GL_COLOR_BUFFER_BIT);
	for(ant &act: ants){
		float pixel[3];
			glReadPixels(act.x,act.y,1,1,GL_RGB,GL_FLOAT,&pixel);
			if(pixel[0]==1.0 && pixel[1]==1.0 && pixel[2]==1.0){
				glBegin(GL_POINTS);
				glColor3f(act.cr,act.cg,act.cb);
				glVertex2i(act.x,act.y);
				glEnd();
				act.dir++;
			} else{
				glBegin(GL_POINTS);
				glColor3f(1.0,1.0,1.0);
				glVertex2i(act.x,act.y);
				glEnd();
				act.dir--;
			}
			act.dir = (act.dir+4)%4;
			switch(act.dir){
			case 0:
				act.x++;
				break;
			case 1:
				act.y++;
				break;
			case 2:
				act.x--;
				break;
			case 3:
				act.y--;
				break;
			}
			act.x = ((int)act.x+(int)col)%(int)col;
			act.y = (act.y+(int)row)%(int)row;
	}
	//drawpoints();
	glutSwapBuffers();
	//glutPostRedisplay();
}



void reshape_callback(int w,int h){
	glViewport(0,0,(GLsizei)w,(GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	col = w;
	row = h;
	glOrtho(0.0,col,00,row,-1.0,1.0);
	glMatrixMode(GL_MODELVIEW);
}

void timer_callback(int){
	glutPostRedisplay();
	glutTimerFunc(1000/fps,timer_callback,0);
}





