// **************************************************************
// *		   
// *  quadtree.h
// *		   
// *  Quadtree class
// *		   
// *  CS 225 Spring 2008
// *		   
// **************************************************************

#ifndef QUADTREE_H
#define QUADTREE_H

#include "png.h"

class Quadtree
{
	public:
	Quadtree();	
	Quadtree(PNG source, int d);
	Quadtree(Quadtree const & other);
	~Quadtree();
	Quadtree const & operator = (Quadtree const & other); 
	void buildTree(PNG const & source, int resolution);
	RGBAPixel getPixel(int x, int y) const;
	PNG decompress() const;
	void clockwiseRotate();
	void prune(int tolerance);
	int pruneSize(int tolerance) const;
	int idealPrune(int numLeaves) const;
	int getSize();
//	bool operator == (Quadtree const & other) const;
	private:

	// A simple class representing a single node of a Quadtree.
	// You may want to add to this class; in particular, it could probably
	// use a constructor or two...
	class QuadtreeNode
	{
		public:
		QuadtreeNode* nwChild;  // pointer to northwest child
		QuadtreeNode* neChild;  // pointer to northeast child
		QuadtreeNode* swChild;  // pointer to southwest child
		QuadtreeNode* seChild;  // pointer to southeast child

		RGBAPixel element;  // the pixel stored as this node's "data"
	};
	int size;
	QuadtreeNode* root;    // pointer to root of quadtree
	void clear();
	void deleter(QuadtreeNode* a);
//	void copy(Quadtree const & other);
	QuadtreeNode * copier(QuadtreeNode * subroot);
	QuadtreeNode* treebuilder (PNG const & source, int resolution, int x, int y);
	RGBAPixel pixelgetter(int region,int x, int y, int xnow, int ynow,QuadtreeNode * subroot) const;
	void  decompressor(PNG & uhh, QuadtreeNode* subroot, int x ,int y,int region) const;
	void rotator (QuadtreeNode * subroot);
	void pruner (int tolerance, QuadtreeNode * subroot);
	bool prunechecker( int tolerance, QuadtreeNode * subroot, QuadtreeNode * beenchecked) const;
	void prunesizer( int tolerance , QuadtreeNode * subroot , int & count) const;
	int dealer (int numLeaves, int lend, int rend) const;
	/**** Functions added for testing/grading                ****/
	/**** Do not remove this line or copy its contents here! ****/
	#include "quadtree_given.h"
};

#endif
