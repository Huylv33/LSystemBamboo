//#ifdef __APPLE__
//#include<GLUT/GLUT.h>
//#elseif
#include<gl/glut.h>
//#endif // __APPLE__
#include <iostream>
#include<string>
#include<stack>
using namespace std;
float width = 8.0;
float lengthScale = 0.75;
float leng1 = 0.95;
float leng2 = 5;
float leng3 = 2.5;
float leng4 = 1;
float angle = 23;
void drawLine();
void draw();

struct {
	char f = 'F';
	char k = 'K';
	//string F = "D[++M[+++++X]][--M[-----X]]BD[--M[-----X]]BD[++M[+++++X]]^B";
    string F = "D[++M[+++++X--X]][--C[---X---X++X]]BD[--M[-----X++X]]BD[++M[+++++X]][++C[+++X+++X--X]]^B";

	string G = "[^^[[[+++^X]]^L[++^X]^K[++^X]]]";
	//string F = "F+F--F+F";

}Rules;

string axiom1 = "[F";
string axiom2 = "F";
string str = axiom1;
string strcrown = axiom2;
void Init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
}

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
}

void ReShape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10.0, 10.0, -10.0, 10.0, 10.0, -10.0);
	glMatrixMode(GL_MODELVIEW);
}

void RenderScene()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	draw();

	glFlush();

}
void TurnLeft() {

	glRotatef(angle, 0, 0, 1);

}
void TurnRight() {

	glRotatef(-angle, 0, 0, 1);

}
void TurnRightWithCustomizedAngle() {
	glRotatef(-1, 0, 0, 1);
}
void TurnLeftWithCustomizeAngle() {
    glRotatef(4, 0, 0, 1);
}
void DrawLine(float scale, float length, int colorMode) {
	glLineWidth(width * scale);
	glBegin(GL_LINES);
	if(colorMode == 1)
        glColor3f(0.0, 0.0, 0.0);
    else glColor3f(0.0, 1.0, 0.4);// xanh
	glVertex3f(0,0,0);
	glVertex3f(0,length,0);
	glEnd();
	glTranslatef(0, length, 0);

}
// ve dot cay
void drawDot(){
    float height = 0.05;
    glLineWidth(width);
	glBegin(GL_LINES);
	glColor3f(1, 1, 1);// trang
	glVertex3f(0,0,0);
	glVertex3f(0,height,0);
	glEnd();
	glTranslatef(0, height, 0);
}
void push() {
	glPushMatrix();
}
void pop() {
	glPopMatrix();
}
// ve la cay
void drawLeaf(void) {
  glColor3f(0.1,0.9,0.1);
  int scale = 20;
  glBegin(GL_POLYGON);

  glVertex2d(0.0,0.0);
  glVertex2d(1.0/scale,1.0/scale);
  glVertex2d(0.8/scale,5.0/scale);
  glVertex2d(0,9.0/scale);
  glVertex2d(-0.8/scale,5.0/scale);
  glVertex2d(-1.0/scale,1.0/scale);
  glVertex2d(0.0,0.0);
  glEnd();
}
// sinh than cay
void generateBody() {
	string strCurrent = Rules.F;
	cout << strCurrent;
	str += strCurrent;
}
// sinh  ngon cay

void generateCrown() {
    /*leng1 = lengthScale*leng1;
	leng2 = lengthScale*leng2;
	leng3 = lengthScale*leng3;
	leng4 = lengthScale*leng4;
    */
	string strCurrent = "";

	for (int i = 0; i < strcrown.length(); i++) {
		char current =  strcrown.at(i);
		if (current == Rules.f || current == Rules.k) {
			strCurrent += Rules.G;
		}
		else
			strCurrent += current;
	}
    strcrown += strCurrent;
	str += strCurrent;
	cout <<  strCurrent << " " << strCurrent.length() << "\n";
}
void draw() {
	stack <char> S;

	for (int i = 0; i < str.length(); i++) {
		char current = str.at(i);
		if (current == 'F') {
			// drawLine
			DrawLine(1.0, leng1,0);
			//glTranslated(x, y + 5, z);
		}
		else if (current == 'B') {
			// turn Left
			DrawLine(1.0, leng1,0);
		}
		else if(current == 'L' || current == 'K') {
            DrawLine(0.45, leng1,0);
		}
		else if (current == 'C') {
            DrawLine(0.3, leng1 * 0.75,0);
		}
		else if(current == 'M') {
            DrawLine(0.2, leng1*0.2,0);
		}
		else if (current == 'H') {
            DrawLine(1.0, leng1*0.6,1);
		}
		else if (current == 'X') {
			// turn Left
			drawLeaf();
		}
		else if (current == 'D'){
            drawDot();
		}
		else if (current == '+') {
			// turn Right
			TurnRight();
		}
		else if (current == '-') {
			// turn Left
			TurnLeft();
		}

        else if (current == '*') {;
            TurnLeftWithCustomizeAngle();
        }
        else if (current == '^') {
            // turn Left with customized angle
            TurnRightWithCustomizedAngle();
        }
		else if (current == '[') {
			push();
			S.push(1);
		}
		else if(current == ']') {
			pop();
			S.pop();
		}

	}
}
void generateTree()
{
	int treeNum = 6;
	for(int iter = 0;iter < treeNum;iter++ ){
		for (int i = 0; i < 2; i++) {
		generateBody();
		cout<< "\n";
		}
		int branchNum = 3;
		for(int i = 0;i<branchNum;++i){
	        for (int j = 0; j < 2; j++) {
	            generateCrown();
	            cout<< "\n";
	        }
			/*leng1 = leng1/lengthScale;
			leng2 = leng2/lengthScale;
			leng3 = leng3/lengthScale;
			leng4 = leng4/lengthScale; */
			strcrown = axiom2;
			if(i != branchNum-1) str +="^^L+";
		}
	    cout << str;
	 //   leng1 = leng1*lengthScale*2;
//	    leng2 = leng2*lengthScale;
//        leng3 = leng3*lengthScale;
//        leng4 = leng4*lengthScale;
        string h = "";
      /*  for(int i = 0;i<iter+1;++i)
        {
            h += "H";
        }*/
       // string addString = "][++++" + h + "----^^";
        string addString;
        if (iter % 2 == 0) {
            if (iter != 0) for (int i = 0; i < iter; ++i) h+= "H";
            addString = "][++++" + h + "----^^^^^^^^^^^^^";

        }
        else {
            for (int i = 0; i < iter + 1; ++i) h += "H";
            addString = "][++++" + h + "----^^^^^^";
        }

        if (iter!= treeNum - 1) addString += "B";
	    str += addString ; //tach ve cay lien ke
	}



}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE || GLUT_RGB);

	glutInitWindowSize(1000, 1000);

	glutInitWindowPosition(100, 100);

	glutCreateWindow("BTL");

	Init();
	generateTree();
	//cout << str << "\n\n";
	string temp = str;



	glutReshapeFunc(ReShape);
	glutDisplayFunc(RenderScene);
	glutMainLoop();
	return 0;
}

