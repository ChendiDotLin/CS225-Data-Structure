// **************************************************************
// *		   
// *  quadtree.cpp
// *		   
// *  Quadtree class
// *		   
// *  CS 225 Spring 2008
// *		   
// **************************************************************

#include "quadtree.h"
using namespace std;


//getSize
int Quadtree::getSize(){
return this->size;
}

//default constructor
Quadtree::Quadtree()
{
	root = NULL;
	size = 0;	
}

//a constructor using PNG
Quadtree::Quadtree(PNG source, int d )
{
	
	root =treebuilder(source,d,0,0);
	size = d;
}
//a helper function of copy, which is also a helper function
Quadtree::QuadtreeNode * Quadtree::copier(QuadtreeNode * otherroot)
{
	if (otherroot !=NULL){
		QuadtreeNode * subroot  = new QuadtreeNode;
		subroot->element = otherroot->element;
		subroot->nwChild = copier(otherroot->nwChild);
		subroot->neChild = copier(otherroot->neChild);
		subroot->swChild = copier(otherroot->swChild); 
		subroot->seChild = copier(otherroot->seChild);
		return subroot;
		}
	return NULL;
}
//a helper function of copy constructor
//void Quadtree::copy(Quadtree const & other){
//	copier(other.root);
//}

//copy constructor
Quadtree::Quadtree(Quadtree const & other){
	root = copier(other.root);
//	root = other.root;
	size = other.size;
//	cout<<"done"<<endl;
}

//a helper function of destructor
void Quadtree::deleter(QuadtreeNode* subroot){
//	subroot->element = NULL;
	if (subroot==NULL)return;
	deleter(subroot->nwChild);
	deleter(subroot->neChild);
	deleter(subroot->swChild);
	deleter(subroot->seChild);
//	subroot->element = NULL;
	subroot->nwChild = NULL;
	subroot->neChild = NULL;
	subroot->swChild = NULL;
	subroot->seChild = NULL;
	delete subroot;
	subroot = NULL;
	return;
}

//void Quadtree::clear(){
//	deleter(root);

//destructor
Quadtree::~Quadtree()
{
	deleter(root);
	root = NULL;
	size = 0;
}

//operator =
Quadtree const & Quadtree::operator = (Quadtree const & other){
	if (this != &other){
		deleter(this->root);
		this->root = copier(other.root);
		this->size = other.size;
	}
	return *this;
}
//thats how we build a tree~~~~~


void Quadtree::buildTree(PNG const & source, int resolution){
	deleter(root);
	root = treebuilder(source,resolution,0,0);
	size = resolution;
}

//please help me build the tree!!

Quadtree::QuadtreeNode*  Quadtree::treebuilder(PNG const & source, int resolution, int x, int y){
	if (resolution!=1){
		QuadtreeNode * subroot = new QuadtreeNode ();
	//	subroot->element = *source(x,y);
		subroot->nwChild = treebuilder(source, resolution/2,x , y);
		subroot->neChild = treebuilder(source, resolution/2, x+resolution/2, y);
		subroot->swChild = treebuilder(source, resolution/2, x, y+resolution/2);
		subroot->seChild = treebuilder(source, resolution/2, x+resolution/2, y+resolution/2);
		subroot->element.red =( (subroot->nwChild->element.red)+(subroot->neChild->element.red)+(subroot->swChild->element.red)+(subroot->seChild->element.red))/4;
		subroot->element.green = ( (subroot->nwChild->element.green)+(subroot->neChild->element.green)+(subroot->swChild->element.green)+(subroot->seChild->element.green))/4;

		subroot->element.blue = ( (subroot->nwChild->element.blue)+(subroot->neChild->element.blue)+(subroot->swChild->element.blue)+(subroot->seChild->element.blue))/4;


		return subroot;

		}
//value only stored in leave nodes

	if (resolution ==1){
		QuadtreeNode * subroot = new QuadtreeNode();
		subroot->element = *source(x,y);
		subroot->nwChild = NULL;
		subroot->neChild = NULL;
		subroot->swChild = NULL;
		subroot->seChild = NULL;
		return subroot;
		}
	else return NULL;
}

//getPixel
//not quite sure about how can a node is not specified
RGBAPixel Quadtree::getPixel(int x, int y ) const{
		
		if ( x>size || y>size||root==NULL){
		RGBAPixel a ;
		return a;}
		else return pixelgetter(size/2,x,y,0,0,root);
	
}

//helper function of getPixel
RGBAPixel Quadtree::pixelgetter(int region, int x, int y, int xnow, int ynow, QuadtreeNode* subroot)const{	
//value only stored in leave nodes
	//	if (subroot->nwChild==NULL && subroot->neChild ==NULL && subroot->swChild==NULL && subroot->seChild ==NULL) {
		if (subroot->nwChild == NULL){
		RGBAPixel a = subroot->element;
//		cout<<xnow<<","<<ynow<<endl;
		return a;}
//		cout<<"1"<<endl;
		if (x<xnow+region && y<ynow+region) return pixelgetter(region/2,x,y,xnow,ynow,subroot->nwChild);
		if (x<xnow+region && y >=ynow+region) return pixelgetter(region/2,x,y,xnow,ynow+region,subroot->swChild);	
		if (x>=xnow+region && y<ynow+region) return pixelgetter(region/2,x,y,xnow+region,ynow,subroot->neChild);
		else return pixelgetter(region/2,x,y,xnow+region,ynow+region,subroot->seChild);
	}


	


//decompress
PNG Quadtree::decompress()const{

PNG uhh;
if(root==NULL){
return uhh;
}
//cout<<"0"<<endl;
uhh.resize(size,size);
//cout<<"2"<<endl;
//return
 decompressor(uhh,root,0,0,size);
//cout<<"ssss"<<endl;
return uhh;
}

//helper function of decompress
//pay attention!! return PNG by value will result in time out!!!
void  Quadtree::decompressor(PNG & a,QuadtreeNode * subroot,int x, int y,int region)const{
//	cout<<"q"<<endl;
	if (subroot==NULL )return ;
//	cout<<"Q"<<endl;
//	if (subroot->nwChild==NULL&&subroot->neChild ==NULL && subroot->swChild ==NULL && subroot->seChild ==NULL){
	if (subroot->nwChild ==NULL){
//		cout<<"haha"<<endl;
		for (int i = x; i < x+region ; i++){
			for (int j = y ; j < y +region ; j++){ 
		*a(i,j) = subroot->element;
		}
	}
//		cout<<"!"<<endl;
}
	//	cout<<"lalalaa"<<endl;
	else{
//		cout<<"lala"<<endl;
		decompressor(a,subroot->nwChild,x,y,region/2);
//		cout<<"1"<<endl;
		decompressor(a,subroot->neChild,x+region/2,y,region/2);
//		cout<<"2"<<endl;
		decompressor(a,subroot->swChild,x,y+region/2,region/2);
//		cout<<"3"<<endl;
		decompressor(a,subroot->seChild,x+region/2,y+region/2,region/2);
//		cout<<"4"<<endl;
	}	
	//return a;
	return;
}		

void Quadtree::clockwiseRotate()
{	
	if (root == NULL ) return;
	rotator(root);	
//	cout<<"dadada"<<endl;
}
void Quadtree:: rotator ( Quadtree::QuadtreeNode * subroot){
	if (subroot->nwChild ==NULL && subroot->neChild == NULL && subroot->swChild ==NULL && subroot->seChild ==NULL)
	return;
	rotator (subroot->nwChild);
	rotator (subroot->neChild);
	rotator (subroot->swChild);
	rotator (subroot->seChild);
	QuadtreeNode * temp = subroot->nwChild;
	subroot->nwChild = subroot->swChild;
	subroot->swChild = subroot->seChild;
	subroot->seChild = subroot->neChild;
	subroot->neChild = temp;
}

void Quadtree::prune(int tolerance){
	if (root == NULL) return;
	pruner (tolerance, root);

}

bool Quadtree::prunechecker(int tolerance, QuadtreeNode * subroot, QuadtreeNode * beenchecked) const{
	if (subroot->nwChild == NULL){
		int diff = (subroot->element.red - beenchecked->element.red)*(subroot->element.red - beenchecked->element.red)+(subroot->element.green - beenchecked->element.green)*(subroot->element.green - beenchecked->element.green) + (subroot->element.blue - beenchecked->element.blue)*(subroot->element.blue - beenchecked->element.blue);
	//	cout<<diff<<endl;
		return diff <= tolerance;
	}
	return prunechecker(tolerance, subroot->nwChild, beenchecked) && prunechecker(tolerance, subroot->neChild, beenchecked) && prunechecker(tolerance, subroot->swChild, beenchecked) && prunechecker( tolerance, subroot->seChild, beenchecked);
	}

void Quadtree::pruner(int tolerance, QuadtreeNode * subroot){
	if (subroot->nwChild ==NULL)
		 return;

	if (prunechecker(tolerance, subroot, subroot)){
		deleter(subroot->nwChild);
		deleter(subroot->neChild);
		deleter(subroot->swChild);
		deleter(subroot->seChild);	
		subroot->nwChild =NULL;
		subroot->neChild = NULL;
		subroot->swChild = NULL;
		subroot->seChild = NULL;

		return;
	}
//	cout<<"4"<<endl;
	pruner(tolerance, subroot->nwChild);
//	cout<<"1"<<endl;
        pruner(tolerance, subroot->neChild);
  //      cout<<"2"<<endl;
	pruner(tolerance, subroot->swChild);
        pruner(tolerance, subroot->seChild);	
//	deleter (subroot);
	}


int Quadtree::pruneSize(int tolerance) const
{
	if (root==NULL ) return 0;
	int result = 0;
//	bool a = true;
	prunesizer(tolerance, root, result);
	return result;
}

void Quadtree::prunesizer(int tolerance, QuadtreeNode * subroot, int &  count) const{
        if (subroot->nwChild ==NULL) {
		count++;
		return;
	}
	if (prunechecker(tolerance, subroot, subroot)){
		count++;
		return;
	}
        prunesizer(tolerance, subroot->nwChild, count);
        prunesizer(tolerance, subroot->neChild, count);
        prunesizer(tolerance, subroot->swChild, count);
        prunesizer(tolerance, subroot->seChild, count);

}

int Quadtree::idealPrune(int numLeaves) const{
	if (root ==NULL ) return 0;
	if (pruneSize(0) <= numLeaves) return 0;
	return dealer (numLeaves, 0 ,200000);
}


/*int Quadtree::dealer (int numLeaves, int mid ,  int tol) const{
//	if (pruneSize(tol) == numLeaves) {
//		while(pruneSize(tol) == numLeaves)
//			tol--;
//		return tol + 1 ;
//	}
	if (mid == 1){
		if (pruneSize(tol) > numLeaves)
		 return tol+1 ;
	//	if( pruneSize(tol) <  numLeaves)
	//	return tol - 1;
		 return tol;
	}
	if (pruneSize(tol) > numLeaves)
		 return dealer(numLeaves, mid/2 , tol+mid/2);
	else return dealer(numLeaves, mid/2, tol-mid/2);
}*/

int Quadtree::dealer(int numLeaves, int lend, int rend) const {
	if ( lend == rend-1){
		if (pruneSize(lend) <= numLeaves) 
			return lend;
		else
		 	return rend;
}
	int mid = (lend + rend) /2;
	if ( pruneSize(mid) <= numLeaves)
		 return dealer(numLeaves, lend , mid);
	else return dealer ( numLeaves, mid, rend);
	}
