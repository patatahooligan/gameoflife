#include "stdafx.h"

#include <bitset>
#include <memory>

#include "gridwrapper.h"

bool wrap = true;

std::bitset<grid_size>::reference GridWrapper::new_cell(int x, int y) {
	if (!wrap)
		return (*new_grid)[y * grid_width + x];
	else
		return (*new_grid)[((y+grid_height)%grid_height) * grid_width + ((x+grid_width)%grid_width)];
}

GridWrapper::GridWrapper() :
	// Default constructor for bitset sets all bits to zero
	grid(new std::bitset<grid_size>) {}

GridWrapper::~GridWrapper() {
}

void GridWrapper::reset() {
	// IMPORTANT : a->b is short for (*a).b when dealing with pointers.
	//			   grid.reset() would reset the pointer!	(unique_ptr::reset())
	//			   We need grid->reset() to reset the grid. (bitset::reset())
	//			   They're unrelated, but happen to have the same name.
	grid->reset();
}

void GridWrapper::turn() {
	// Create a new bitset to hold the next state
	new_grid.reset(new std::bitset<grid_size>);

	// Iterate over all cells in the grid
	for (int y=0; y<grid_height; ++y) {
		for (int x=0; x<grid_width; ++x) {
			// Boundary check
			unsigned char neighbors = 0;
			int minj = y-1;
			if (y==0 && !wrap) minj = 0;
			int maxj = y+1;
			if (y==grid_height-1 && !wrap) maxj = grid_height-1;
			for (int j = minj; j <= maxj; ++j) {
				// Boundary check
				int mini = x-1;
				if (x==0 && !wrap) mini = 0;
				int maxi = x+1;
				if (x==grid_width-1 && !wrap) maxi = grid_width-1;
				for (int i = mini; i <= maxi; ++i) {
					if (i==x && j==y) continue;
					neighbors += cell(i, j);
				}
			}
			if (neighbors < 2 || neighbors > 3)
				new_cell(x, y) = 0;
			else if (neighbors == 3)
				new_cell(x, y) = 1;
			else
				new_cell(x, y) = cell(x, y);
		}
	}

	// Make grid point to the new state
	grid = std::move(new_grid);
}

std::bitset<grid_size>::reference GridWrapper::cell(int x, int y) {
	if (!wrap)
		return (*grid)[y * grid_width + x];
	else
		return (*grid)[((y+grid_height)%grid_height) * grid_width + ((x+grid_width)%grid_width)];
}