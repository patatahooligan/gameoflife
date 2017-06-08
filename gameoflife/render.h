#pragma once

#include "stdafx.h"

void render_init(int argc, char** argv);

void render();

void idle();

void mouse(int button, int state, int x, int y);

void keyboard(unsigned char key, int x, int y);