#include "stdafx.h"

#include <bitset>
#include <memory>

#include "gridwrapper.h"

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
	std::unique_ptr<std::bitset<grid_size>> new_grid(new std::bitset<grid_size>);

	// Iterate over all cells in the grid
	for (size_t y=0; y<grid_height; y++) {
		for (size_t x=0; x<grid_width; x++) {
			// TODO: add code that determines next state of cell here
			// syntax for current cell : (*grid)[y * grid_width + x]
		}
	}

	// Make grid point to the new state
	grid.swap(new_grid);
}