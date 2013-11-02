#include <iostream>
#include <vector>
using namespace std;

#ifdef __APPLE__
#include<GLUT/glut.h>
#include<openGL/openGL.h>
#else
#include <GL/glut.h>
#endif

#define UPDATE_TIME 30
class point{
	float x,y;
public:
	point();
	point(float,float);
	void setX(float);
	void setY(float);
	float getX();
	float getY();
	point operator +(point);
	point operator -(point);
};
point::point(){
	x=0;y=0;
}
point::point(float a,float b){
	x=a;
	y=b;
}
void point::setX(float a){
	x=a;
}
void point::setY(float a){
	y=a;
}
float point::getX(){
	return x;
}
float point::getY(){
	return y;
}
point point::operator +(point p){
	point temp;
	temp.x=this->x+p.x;
	temp.y=this->y+p.y;
	return temp;
}
point point::operator -(point p){
	point temp;
	temp.x=this->x-p.x;
	temp.y=this->y-p.y;
	return temp;
}
vector<point> v;
class Ball{
private:
	point location;
	float radius;
	float red,green,blue;
public:
	Ball();
	Ball(point,float);
	void setLocation(point);
	void setRadius(float);
	void setColor(float,float,float);
	point getLocation();
	float getR();
	float getRed();
	float getGreen();
	float getBlue();
}b;
int count=0;
Ball::Ball(){
	location=point(0,0);
	radius=0.2;
	red=0.0;
	blue=1.0;
	green=0.0;
}
Ball::Ball(point p,float r){
	location = p;
	radius =r;
	red=0.0;
	blue=0.0;
	green=1.0;
}
void Ball::setLocation(point p){
	location=p;
}
void Ball::setRadius(float r){
	radius=r;
}
void Ball::setColor(float r,float g,float b){
	red=r;
	green=g;
	blue=b;
}
point Ball::getLocation(){
	return location;
}
float Ball::getR(){
	return radius;
}
float Ball::getRed(){
	return red;
}
float Ball::getBlue(){
	return blue;
}
float Ball::getGreen(){
	return green;
}
void update(int value){
	if(count<v.size()){
		b.setLocation(v[count++]);
	}
	glutPostRedisplay();
	glutTimerFunc(UPDATE_TIME, update, value);
}
void drawBall(){
	glColor3f(b.getRed(),b.getGreen(),b.getBlue());
    point loc=b.getLocation();
    glTranslatef(loc.getX(), loc.getY(),0.0);
    glutSolidSphere(b.getR(),100, 100);
}
void display(void){
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW); 
    glLoadIdentity();	
    drawBall();
    glutSwapBuffers();
}
void mouse(int x,int y){

	float rel_x,rel_y;
	rel_x=float((x-300)/310.0);
	rel_y=float((300-y)/310.0);
	point temp(rel_x,rel_y);
	v.push_back(temp);
}
int main(int argc,char **argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGBA);
	glutInitWindowSize(600,600);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Semester Assignment!!!");
	glClearColor(1.0,1.0,1.0,0.0);
	glutPassiveMotionFunc(mouse);
	glutDisplayFunc(display);
	glutTimerFunc(UPDATE_TIME, update, 0);
	glutMainLoop();
	return 0;
}