#include "main.h"

#define ANGLE_STEP 1.0

short currentColorSpace;
XYZ* color_XYZ;
NormalizedXYZ* color_normalizedXYZ;
sRGB* color_sRGB;
Munsell* color_munsell;
KodakMinilab* color_kodakMinilab;
float angleX;
float angleY;
float angleZ;
int lastMousePosX;
int lastMousePosY;
int mouseState;
int mouseButton;
Vec3<float>* eye;


int main(int argc, char *argv[]){
	
	initGlut(argc, argv);
	glewInit();
	
	currentColorSpace = def_CIE_XYZ;
	
	std::cout << "Setting up XYZ...\n";
	color_XYZ = new XYZ("1nm-2.csv");
	std::cout << "Setting up normalized XYZ...\n";
	color_normalizedXYZ = new NormalizedXYZ(2, color_XYZ->m_values);
	std::cout << "Setting up sRGB...\n";
	color_sRGB = new sRGB(2);
	std::cout << "Setting up Munsell...\n";
	color_munsell = new Munsell(2, "munsell.csv", 16);
	std::cout << "Setting up Kodak Minilab...\n";
	color_kodakMinilab = new KodakMinilab(2, "Kodak Minilab.csv", 16);
	std::cout << "All done.\n";
	
	
	initAntTweakBar();

	glutMainLoop();

	
}



void render(){
	
	
	glClearColor(1.0,1.0,1.0,1.0);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();
	gluLookAt(eye->x,eye->y,eye->z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glRotatef(angleX, 1.0, 0.0, 0.0); //rotate on the x axis
    glRotatef(angleY, 0.0, 1.0, 0.0); //rotate on the y axis
    glRotatef(angleZ, 0.0, 0.0, 1.0); //rotate on the z axis

	renderAxis();

	if(currentColorSpace == def_CIE_XYZ)
		glScalef(def_scale_CIE_XYZ, def_scale_CIE_XYZ, def_scale_CIE_XYZ);
	else if(currentColorSpace == def_CIE_Lab)
		glScalef(def_scale_CIE_Lab, def_scale_CIE_Lab, def_scale_CIE_Lab);
	else
		glScalef(def_scale_sRGB, def_scale_sRGB, def_scale_sRGB);
	
	//colorSpace_XYZ->render(currentColorSpace);
	color_kodakMinilab->render(currentColorSpace);
	color_munsell->render(currentColorSpace);
	color_sRGB->render(currentColorSpace);
	color_normalizedXYZ->render(currentColorSpace);
	
	
	glFlush();

	TwDraw();

	//std::cout << currentColorSpace;

	glutSwapBuffers();

}

void renderAxis(){
	glBegin(GL_LINES);
	if(currentColorSpace == def_CIE_XYZ){
		glColor3f(1, 0, 0); glVertex3f(0, 0, 0); glColor3f(1, 0, 0); glVertex3f(1000, 0, 0);
		glColor3f(0, 1, 0); glVertex3f(0, 0, 0); glColor3f(0, 1, 0); glVertex3f(0, 1000, 0);
		glColor3f(0, 0, 1); glVertex3f(0, 0, 0); glColor3f(0, 0, 1); glVertex3f(0, 0, 1000);
	}
	else if(currentColorSpace == def_CIE_Lab){
		glColor3f(1, 0, 0); glVertex3f(0, 0, 0); glColor3f(1, 0, 0); glVertex3f(1000, 0, 0);
		glColor3f(0, 1, 0); glVertex3f(0, 0, 0); glColor3f(0, 1, 0); glVertex3f(0, 1000, 0);
		glColor3f(0, 0, 1); glVertex3f(0, 0, 0); glColor3f(0, 0, 1); glVertex3f(0, 0, 1000);
	}
	else{
		glColor3f(1, 0, 0); glVertex3f(0, 0, 0); glColor3f(1, 0, 0); glVertex3f(1000, 0, 0);
		glColor3f(0, 1, 0); glVertex3f(0, 0, 0); glColor3f(0, 1, 0); glVertex3f(0, 1000, 0);
		glColor3f(0, 0, 1); glVertex3f(0, 0, 0); glColor3f(0, 0, 1); glVertex3f(0, 0, 1000);
	}
	glEnd();

}

void initGlut(int argc, char *argv[]){
	

	angleZ = 0;
	angleX = 0;
	angleY = 0;
	lastMousePosX = 0;
	lastMousePosY = 0;
	mouseState = GLUT_UP;
	mouseButton = GLUT_RIGHT_BUTTON;
	eye = new Vec3<float>(0, 0, 5);


	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(1280,720);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Color - T1");
	
	glClearColor(0.0,0.0,0.0,0.0);
	//gluOrtho2D(0,800,0,600);
	glutDisplayFunc(render);
	glutIdleFunc(render);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(keyboardSpecial);
	glutMotionFunc(mouseActive);
	glutMouseFunc(mouseButtons);
	glutPassiveMotionFunc((GLUTmousemotionfun)TwEventMouseMotionGLUT);
	glutReshapeFunc(reshape);
	
	glEnable(GL_DOUBLEBUFFER);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_ALPHA_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	

}

void initAntTweakBar(){
	
	TwInit(TW_OPENGL, NULL);
	TwWindowSize(1280, 720);

	TwBar *bar;
	bar = TwNewBar("Colors");

	TwDefine(" Colors color='0 128 255' text=dark size='250 400' size='240 650'");

	//TwAddButton(bar, "Nothing", nothing, NULL, "");
	

	
	TwEnumVal colorSpaces[3] = { {def_CIE_XYZ, "CIE XYZ"}, {def_CIE_Lab, "CIE Lab"}, {def_sRGB, "sRGB"} };
	TwType colorSpacesType = TwDefineEnum("ColorSpacesType", colorSpaces, 3);
	TwAddVarRW(bar, "Color space:", colorSpacesType, &(currentColorSpace), "");
	
	
	TwEnumVal render[4] = { {def_render_points, "Points"}, {def_render_wire, "Wire"}, {def_render_shade, "Smooth"}, {def_render_flat, "Flat"}};
	TwType renderTypes = TwDefineEnum("RenderTypes", render, 4);
	
	
	//TwAddVarCB(bar, "Nothing", renderTypes, SetCallback, GetCallback, 0, "");
	
	TwAddVarRW(bar, "Show", TW_TYPE_BOOL8, &(color_normalizedXYZ->m_show), "group = 'Spectral'");
	TwAddVarRW(bar, "Render type", renderTypes, &(color_normalizedXYZ->m_renderType), "group = 'Spectral'");
	TwAddVarRW(bar, "Alpha", TW_TYPE_FLOAT, &(color_normalizedXYZ->m_alpha), "group = 'Spectral'");
	TwAddButton(bar, "Change alpha", changeAlpha, color_normalizedXYZ, "group = 'Spectral'");
	TwAddVarRW(bar, "Normalized", TW_TYPE_BOOL8, &(color_normalizedXYZ->m_normalized), "group = 'Spectral'");
	TwAddVarRW(bar, "Tessellation lvl", TW_TYPE_INT32, &(color_normalizedXYZ->m_tesselationLvl), "group = 'Spectral'");
	TwAddButton(bar, "Change tesselation lvl", tesselate, color_normalizedXYZ, "group = 'Spectral'");
	
	
	TwAddVarRW(bar, " Show", TW_TYPE_BOOL8, &(color_sRGB->m_show), "group = 'sRGB'");
	TwAddVarRW(bar, " Render type", renderTypes, &(color_sRGB->m_renderType), "group = 'sRGB'");
	TwAddVarRW(bar, " Alpha", TW_TYPE_FLOAT, &(color_sRGB->m_alpha), "group = 'sRGB'");
	TwAddButton(bar, " Change alpha", changeAlpha, color_sRGB, "group = 'sRGB'");
	TwAddVarRW(bar, " Normalized", TW_TYPE_BOOL8, &(color_sRGB->m_normalized), "group = 'sRGB'");
	TwAddVarRW(bar, " Tessellation lvl", TW_TYPE_INT32, &(color_sRGB->m_tesselationLvl), "group = 'sRGB'");
	TwAddButton(bar, " Change tesselation lvl", tesselate, color_sRGB, "group = 'sRGB'");

	TwAddVarRW(bar, "  Show", TW_TYPE_BOOL8, &(color_munsell->m_show), "group = 'Munsell'");
	TwAddVarRW(bar, "  Render type", renderTypes, &(color_munsell->m_renderType), "group = 'Munsell'");
	TwAddVarRW(bar, "  Alpha", TW_TYPE_FLOAT, &(color_munsell->m_alpha), "group = 'Munsell'");
	TwAddButton(bar, "  Change alpha", changeAlpha, color_munsell, "group = 'Munsell'");
	TwAddVarRW(bar, "  Normalized", TW_TYPE_BOOL8, &(color_munsell->m_normalized), "group = 'Munsell'");
	//TwAddVarRW(bar, "  Tesselation lvl", TW_TYPE_INT32, &(color_munsell->m_tesselationLvl), "group = 'Munsell'");
	//TwAddButton(bar, "  Change tesselation lvl", tesselate, color_munsell, "group = 'Munsell'");
	TwAddVarRW(bar, "  GBD Matrix Size", TW_TYPE_INT32, &(color_munsell->m_n), "group = 'Munsell'");
	TwAddButton(bar, "  Change size", changeGBDSize, color_munsell, "group = 'Munsell'");
	TwAddVarRW(bar, "  Show all points", TW_TYPE_BOOL8, &(color_munsell->m_showAllPoints), "group = 'Munsell'");

	TwAddVarRW(bar, "   Show", TW_TYPE_BOOL8, &(color_kodakMinilab->m_show), "group = 'Kodak Minilab'");
	TwAddVarRW(bar, "   Render type", renderTypes, &(color_kodakMinilab->m_renderType), "group = 'Kodak Minilab'");
	TwAddVarRW(bar, "   Alpha", TW_TYPE_FLOAT, &(color_kodakMinilab->m_alpha), "group = 'Kodak Minilab'");
	TwAddButton(bar, "   Change alpha", changeAlpha, color_kodakMinilab, "group = 'Kodak Minilab'");
	TwAddVarRW(bar, "   Normalized", TW_TYPE_BOOL8, &(color_kodakMinilab->m_normalized), "group = 'Kodak Minilab'");
	//TwAddVarRW(bar, "   Tesselation lvl", TW_TYPE_INT32, &(color_kodakMinilab->m_tesselationLvl), "group = 'Kodak Minilab'");
	//TwAddButton(bar, "   Change tesselation lvl", tesselate, color_kodakMinilab, "group = 'Kodak Minilab'");
	TwAddVarRW(bar, "   GBD Matrix Size", TW_TYPE_INT32, &(color_kodakMinilab->m_n), "group = 'Kodak Minilab'");
	TwAddButton(bar, "   Change size", changeGBDSize, color_kodakMinilab, "group = 'Kodak Minilab'");
	TwAddVarRW(bar, "   Show all points", TW_TYPE_BOOL8, &(color_kodakMinilab->m_showAllPoints), "group = 'Kodak Minilab'");
	
	
}

void TW_CALL tesselate(void *clientData){
	
	((Color*)clientData)->clear();
	((Color*)clientData)->createGeometries();

}

void TW_CALL changeAlpha(void *clientData){
	
	((Color*)clientData)->changeAlpha(currentColorSpace);

}

void TW_CALL changeGBDSize(void *clientData){
	
	((SegmentMaximaColor*)clientData)->clear();
	((SegmentMaximaColor*)clientData)->changeGBDSize();

}

void reshape(int w, int h){
	
	TwWindowSize(w, h);

	glViewport (0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective (60, (GLfloat)w / (GLfloat)h, 0.1, 1000000.0);
    glMatrixMode (GL_MODELVIEW);

}

void keyboardSpecial(int key, int x, int y){
	
	if( key == GLUT_KEY_LEFT ) angleY+=ANGLE_STEP;
	else if( key == GLUT_KEY_RIGHT ) angleY-=ANGLE_STEP;
	else if( key == GLUT_KEY_UP ) angleX+=ANGLE_STEP;
	else if( key == GLUT_KEY_DOWN ) angleX-=ANGLE_STEP;

}

void keyboard(unsigned char key, int x, int y){
	
	if(!TwEventKeyboardGLUT(key, x, y)){
		
		if( key == '1'){
			currentColorSpace = def_CIE_XYZ;
		}
		else if( key == '2'){
			currentColorSpace = def_CIE_Lab;
		}
		else if( key == '3' ){
			currentColorSpace = def_sRGB;
		}
		else if( key == 'q' ){
			color_kodakMinilab->m_renderType = def_render_points;
			color_munsell->m_renderType = def_render_points;
			color_normalizedXYZ->m_renderType = def_render_points;
			color_sRGB->m_renderType = def_render_points;
		}
		else if( key == 'w' ){
			color_kodakMinilab->m_renderType = def_render_wire;
			color_munsell->m_renderType = def_render_wire;
			color_normalizedXYZ->m_renderType = def_render_wire;
			color_sRGB->m_renderType = def_render_wire;
		}
		else if( key == 'e' ){
			color_kodakMinilab->m_renderType = def_render_flat;
			color_munsell->m_renderType = def_render_flat;
			color_normalizedXYZ->m_renderType = def_render_flat;
			color_sRGB->m_renderType = def_render_flat;
		}
		else if( key == 'r' ){
			color_kodakMinilab->m_renderType = def_render_shade;
			color_munsell->m_renderType = def_render_shade;
			color_normalizedXYZ->m_renderType = def_render_shade;
			color_sRGB->m_renderType = def_render_shade;
		}
		
	}

}

void mouseButtons(int button, int state, int x, int y){
	
	if(!TwEventMouseButtonGLUT(button, state, x, y)){
		mouseState = state;
		mouseButton = button;

		lastMousePosX = x;
		lastMousePosY = y;
	}
}

void mouseActive(int x, int y){
	if(!TwEventMouseMotionGLUT(x, y)){
		if(mouseButton == GLUT_LEFT_BUTTON && mouseState == GLUT_DOWN){
			angleX += (y - lastMousePosY)/5.0f;
			angleY += (x - lastMousePosX)/5.0f;
		}
		else if(mouseButton == GLUT_RIGHT_BUTTON && mouseState == GLUT_DOWN){
			eye->z += (y - lastMousePosY)/50.0;
		}
	}
	

	lastMousePosX = x;
	lastMousePosY = y;

}



