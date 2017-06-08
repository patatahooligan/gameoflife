// gameoflife.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "gridwrapper.h"
#include "render.h"

GridWrapper grid_wrapper;

int main(int argc, char** argv)
{
	grid_wrapper.cell(1, 1) = 1;
	render_init(argc, argv);
	glutMainLoop();
    return 0;
}