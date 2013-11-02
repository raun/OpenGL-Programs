#include <iostream>
#include <vector>
#ifdef __APPLE__
#include<GLUT/glut.h>
#include<openGL/openGL.h>
#else
#include <GL/glut.h>
#endif

#define UPDATE_TIME 75
#define NO_OF_RECTANGLES 25
using namespace std;
class position{
private:
	float x,y,z;
public:
	position();						
	position(float,float,float);
	void setX(float a);
	void setY(float b);
	void setZ(float c);
	float getX();
	float getY();
	float getZ();
};
position::position(){
	this->x=0;
	this->y=0;
	this->z=0;
}
position::position(float a,float b,float c){
	this->x=a;
	this->y=b;
	this->z=c;
}
void position::setX(float a){
	x=a;
}
void position::setY(float b){
	y=b;
}
void position::setZ(float c){
	z=c;
}
float position::getX(){
	return x;
}
float position::getY(){
	return y;
}
float position::getZ(){
	return z;
}
class Rectangle{
private:
	position p[4];
public:
	Rectangle();
	Rectangle(position a[4]);
	void draw();
	void decrementZ();
	void incrementZ();
};
Rectangle::Rectangle(){
	// Incase the rectangle array is being made the following function would be called and a rectangle of 
	// following demention would be shown
	p[0]=position(0.9,0.0,0.0);
	p[1]=position(0.0,0.9,0.0);
	p[2]=position(-0.9,0.0,0.0);
	p[3]=position(0.0,-0.9,0.0);
}
Rectangle::Rectangle(position a[4]){
	for(int i=0;i<4;++i)
		p[i]=a[i];
}
void Rectangle::draw(){
	for(int i=0;i<3;++i){
		glBegin(GL_LINES);
		glColor3f(1.0,1.0,1.0);
		glVertex3f(p[i].getX(),p[i].getY(),p[i].getZ());
		glVertex3f(p[i+1].getX(),p[i+1].getY(),p[i+1].getZ());
		glEnd();
	}
	glBegin(GL_LINES);
	glColor3f(1.0,1.0,1.0);
	glVertex3f(p[3].getX(),p[3].getY(),p[3].getZ());
	glVertex3f(p[0].getX(),p[0].getY(),p[0].getZ());
	glEnd();
}
void Rectangle::decrementZ(){
	for(int i=0;i<4;++i){
		p[i].setX(p[i].getX()/1.1);
		p[i].setY(p[i].getY()/1.1);
	}
}
void Rectangle::incrementZ(){
	for(int i=0;i<4;++i){
		p[i].setX(p[i].getX()/0.9);
		p[i].setY(p[i].getY()/0.9);
	}
}
std::vector<Rectangle> v;
void intialScene(){
	Rectangle r;
	position a[4];
	a[0]=position(0.9,0.0,0.0);
	a[1]=position(0.0,0.9,0.0);
	a[2]=position(-0.9,0.0,0.0);
	a[3]=position(0.0,-0.9,0.0);
	r=Rectangle(a);
	v.push_back(r);
	for(int i=0;i<NO_OF_RECTANGLES;++i){
		position a0=a[0];
		for(int j=0;j<3;++j){
			a[j].setX((a[j].getX()+a[j+1].getX())/2);
			a[j].setY((a[j].getY()+a[j+1].getY())/2);
		}
		a[3].setX((a[3].getX()+a0.getX())/2);
		a[3].setY((a[3].getY()+a0.getY())/2);
		r=Rectangle(a);
		v.push_back(r);	
	}
}

void display(void)
{
	
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW); 
    glLoadIdentity();
    // Remember to call the function to draw the initial scene
    for(int i=0,n=v.size();i<n;++i)
    	v[i].draw();
    glutSwapBuffers();
}
void mouse(int button,int state,int x,int y){
	switch(button){
		case GLUT_LEFT_BUTTON://cout<<"left mouse pressed";
							for(int i=0,n=v.size();i<n;++i)
								v[i].decrementZ();
							glutIdleFunc(display);
								break;
		case GLUT_RIGHT_BUTTON://cout<<"right mouse pressed";
							for(int i=0,n=v.size();i<n;++i)
								v[i].incrementZ();
							glutIdleFunc(display);
								break;
		default:break;
	}
}
int main(int argc,char **argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGBA);
	glutInitWindowSize(800,800);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Zoomin & Zoomout");
	intialScene();
	glutMouseFunc(mouse);
	glutDisplayFunc(display);
	//glutTimerFunc(UPDATE_TIME, update, 0);
	glutMainLoop();
	return 0;
}