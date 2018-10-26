/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <cmath>
template<int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim> & first, const Point<Dim> & second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
	if (first[curDim] < second[curDim]){
		//cout<<"1"<<endl;
		return true;
}
	else if (first[curDim] > second[curDim]){
//		cout<<"2"<<endl;
 	   	return false;
	}
	else {
//		cout<<"3"<<endl;
		if (first < second) return true;
		else return false;
	}
	  
}


template<int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim> & target, const Point<Dim> & currentBest, const Point<Dim> & potential) const
{
    /**
     * @todo Implement this function!
     */
	int distc = 0;
	int distp = 0;
	for (int i = 0; i <Dim ; i++){
		distc += pow ((target[i] - currentBest[i]),2);
		distp += pow ((target[i] - potential[i]) , 2);
	}
	if (distp < distc) return true;	 
   	else if ( distp > distc) return false;
	else {
		if (potential < currentBest) return true;
		else return false;
	}

}

//constructor
template<int Dim>
KDTree<Dim>::KDTree(const vector< Point<Dim> > & newPoints)
{
    /**
     * @todo Implement this function!
     */
	points = newPoints;
	//cout<<point.size()<<endl;
//	cout<<newPoints.size()<<endl;
//	cout<<"a"<<endl;
	treebuilder(points,0, 0, points.size()-1);
}

//helper function
template<int Dim>
void KDTree<Dim>::treebuilder( vector< Point<Dim> > & points, int dim, int left, int right)
{
	if (points.empty()) return;
	if (left==right){
		return;
	}
	int mid = (left + right)/2;
	qselect(dim, points,left,right,mid);
//	cout<<"o"<<endl;
	if (left <= mid-1)
	treebuilder (points , (dim+1)%Dim,left,mid-1);
	if (mid+1 <= right)
	treebuilder(points,(dim+1)%Dim, mid+1, right);		

}
template<int Dim>
void KDTree<Dim>::swap(Point<Dim>& a , Point<Dim> &b )
{
 Point<Dim> temp = a;
 a = b;
 b = temp;
}

template<int Dim>
int KDTree<Dim>::partition(int dimension, vector< Point<Dim> > & list, int left, int right, int pivotIndex)
{
//	cout<<"v"<<endl;
//	cout<<list.size()<<endl;
	Point<Dim> value = list[pivotIndex];
//	cout<<"i"<<endl;
	swap(list[pivotIndex],list[right]);
//	cout<<"u"<<endl;
	int storeIndex = left;
	for (int i = left ; i <right; i ++)
	{
		if (list[i][dimension] < value[dimension])
		{
		swap(list[storeIndex],list[i]);
		storeIndex++;
		}
		else if (list[i][dimension] == value[dimension]&& list[i] < value)
		{
		swap(list[storeIndex],list[i]);
		storeIndex++;	 
		}
	}
	swap(list[right],list[storeIndex]);
	return storeIndex;
}

//quick selection
template<int Dim>
Point<Dim>  KDTree<Dim>::qselect(int dimension, vector< Point<Dim> > & list, int left, int right, int n)
{
	if (left == right) 
		return list[left];
	int pivotIndex = (left+right)/2;
//	cout<<"e"<<endl;
//	cout<<list.size()<<endl;
	pivotIndex = partition (dimension,list,left, right,pivotIndex);
	if (n == pivotIndex)
		return list[n];
	else if (n<pivotIndex)
		return qselect(dimension,list,left,pivotIndex-1, n );
	else 
		return qselect(dimension,list, pivotIndex+1, right, n);
}



template<int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim> & query) const
{
    /**
     * @todo Implement this function!
     */
 	Point<Dim>ehh = points[(points.size()-1)/2];
	return finder(query, ehh, 0, points.size()-1,0);
	//return finder(query,points[0],0,points.size()-1,0);	
}

template<int Dim>
Point<Dim> KDTree<Dim>::finder(const Point<Dim> & target, Point<Dim>  haha, int left, int right, int dim)const
{

	bool lorr = true;
	if (left==right){
		if(shouldReplace(target,haha,points[left]))
			haha = points[left];
//	haha.print();
	return haha;
		}
	int mid = (left+right)/2;
	if(target == points[mid]) {
		haha = points[mid];
		return haha;
	}
	if (smallerDimVal(target, points[mid], dim) && left <= mid-1){
		haha = finder(target,haha, left, mid-1, (dim+1)%Dim);
		lorr = true;	
	}
	else if (!smallerDimVal(target, points[mid], dim)&& mid+1 <= right){
		haha = finder(target, haha, mid+1, right, (dim+1)%Dim);
		lorr  = false;
		}
//	cout<<radius(target,haha)<<endl;
	if (radius(target,haha) == 0) return haha;
//	if(shouldReplace(target,haha,points[mid]))
  //                      haha = points[mid];
	if(radius(target,haha) < distance(target,points[mid],dim))
		return haha;
	else{
	//	haha.print();
		if(shouldReplace(target,haha,points[mid]))
			haha = points[mid];
		if (lorr && mid+1 <= right){
		haha = finder(target,haha,mid+1,right,(dim+1)%Dim);
//		haha.print();
		}
		else if (!lorr && left <= mid-1)
		haha = finder(target, haha, left, mid-1,(dim+1)%Dim);	

	}
//	haha.print();
	return haha;
}

template<int Dim>
int KDTree<Dim>::radius(const Point<Dim> & first, const Point<Dim> & second) const
{
	int a= 0;
	for (int i = 0; i < Dim; i++)
		a += pow((first[i]-second[i]),2);
	return a;
}

template<int Dim>
int KDTree<Dim>::distance(const Point<Dim> & first, const Point<Dim> & second, int dim) const
{
	return pow((first[dim]-second[dim]),2);
}

