#pragma once

#include <bitset>
#include <memory>

const size_t 
	grid_height = 50,
	grid_width = 50,
	grid_size = grid_height * grid_width;

class GridWrapper {
	private:
		std::unique_ptr<std::bitset<grid_size>> grid;
	public:
		GridWrapper();					// Allocate an empty grid
		GridWrapper::~GridWrapper();	// Empty destructor
		void reset();					// Set all grid cells to 0
		void turn();					// Simulate a single turn of game of life

		// TODO: add set() method to alter the state of single grid cells
		//		 add method to render the grid
		//		 rewrite class to support dynamic size
};