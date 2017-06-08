#include "stdafx.h"

#include <bitset>
#include <memory>

#include "gridwrapper.h"



std::bitset<grid_size>::reference GridWrapper::new_cell(size_t x, size_t y) {
	return (*new_grid)[y * grid_width + x];
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
	for (size_t y=0; y<grid_height; ++y) {
		for (size_t x=0; x<grid_width; ++x) {
			// Boundary check
			unsigned char neighbors = 0;
			size_t minj = y-1;
			if (y==0) minj = 0;
			size_t maxj = y+1;
			if (y==grid_height-1) maxj = grid_height-1;
			for (size_t j = minj; j <= maxj; ++j) {
				// Boundary check
				size_t mini = x-1;
				if (x==0) mini = 0;
				size_t maxi = x+1;
				if (x==grid_width-1) maxi = grid_width-1;
				for (size_t i = mini; i <= maxi; ++i) {
					if (i==j) continue;
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

std::bitset<grid_size>::reference GridWrapper::cell(size_t x, size_t y) {
	return (*grid)[y * grid_width + x];
}