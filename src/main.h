#ifndef Main_H
#define Main_H

#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <AntTweakBar.h>


#include "NormalizedXYZ.h"
#include "XYZ.h"
#include "sRGB.h"
#include "Wavelength.h"
#include "Munsell.h"
#include "Defines.h"
#include "KodakMinilab.h"

void render();
void initGlut(int argc, char *argv[]);
void initAntTweakBar();
void renderAxis();
int main(int argc, char *argv[]);
void reshape(int w, int h);
void keyboardSpecial(int key, int x, int y);
void mouseButtons(int button, int state, int x, int y);
void mouseActive(int x, int y);
void readFileSpectrum(char* fileName);
void keyboard(unsigned char key, int x, int y);
void TW_CALL setColorSpace(const void *value, void *clientData);
void TW_CALL getColorSpace(void *value, void *clientData);
void TW_CALL tesselate(void *clientData);
void TW_CALL changeAlpha(void *clientData);
void TW_CALL changeGBDSize(void *clientData);

#endif