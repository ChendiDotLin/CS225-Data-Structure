/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

/**
 * @return The height of the binary tree. Recall that the height of a binary tree
 *  is just the length of the longest path from the root to a leaf, and that the
 *  height of an empty tree is -1.
 */
using namespace std;
template <typename T>
int BinaryTree<T>::height() const
{
	// Call recursive helper function on root
	return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node * subRoot) const
{
	// Base case
	if (subRoot == NULL)
        return -1;
	
	// Recursive definition
	return 1 + max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that node
 *  itself, and everything to the right of a node will be printed out after that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
	// Call recursive helper function on the root
	printLeftToRight(root);

	// Finish the line
	cout << endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node * subRoot) const
{
	// Base case - null node
	if (subRoot == NULL)
		return;

	// Print left subtree
	printLeftToRight(subRoot->left);

	// Print this node
	cout << subRoot->elem << ' ';

	// Print right subtree
	printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
template <typename T>
void BinaryTree<T>::mirror()
{
	// your code here
	mirror(root);
}

template <typename T>
void BinaryTree<T>::mirror(Node * subroot)
{

  if (subroot!=NULL){
                Node * temp = subroot->left;
                subroot->left = subroot->right;
                subroot->right = temp;
                mirror(subroot->left);
                mirror(subroot->right);
}
}
/**
 * @return True if an in-order traversal of the tree would produce a nondecreasing list
 *  output values, and false otherwise. This is also the criterion for a binary tree to be
 *  a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrdered() const
{
    // your code here
	std::vector<T> haha ;
	haha =  isOrdered(root,haha);
	bool order = true;
	//for (unsigned long i = 0; i < haha.size(); i++)
//	{
//	cout<<haha.at(i)<<endl;
//}
	while (!haha.empty()){
	T max = haha.back();
	haha.pop_back();
	if (!haha.empty()) order = order && (max > haha.back());
	}
	
	return order;
}
/*template <typename T>
bool BinaryTree<T>::isOrdered() const
{
return isOrdered(root);
	

	}*/
/*template <typename T>
bool BinaryTree<T>::isOrdered(const Node * point) const
{
	if (point == NULL || (point->left==NULL && point->right==NULL)) return true;
	bool a = true;
	bool left = true;
	bool right = true;
//	cout<<"here"<<endl;
	if (point->left!=NULL && point->right!=NULL ){
		if (point->left->elem< point->elem && point->elem < point->right->elem) a = true;
		else a = false;
	}
//	cout<<"there"<<endl;
	else if ( point->left!=NULL){
		if (point->left->elem< point->elem) a = true;
		else a = false;
	}
	else {
		if (point->elem <point->right->elem) a = true;
		else a = false;
	}
	left = isOrdered(point->left);
	right = isOrdered(point->right);
	return a&&left&&right;
}*/
template <typename T>
std::vector<T> BinaryTree<T>::isOrdered(const Node * subroot, std::vector<T>& myvec)const
{
//	bool order= true;
	if (subroot!=NULL){
		isOrdered(subroot->left, myvec);
		myvec.push_back(subroot->elem);
		isOrdered(subroot->right,myvec);
//		order = subroot->left->elem < subroot->elem;		
	}
	return myvec;
}
/**
 * Prints out all the possible paths from the root of the tree to any leaf node.
 * That is, all sequences starting at the root node and continuing downwards, ending at a
 *  leaf node. Paths ending in a left node should be printed before paths ending in a node
 *  further to the right.
 */
template <typename T>
void BinaryTree<T>::printPaths() const
{
   // your code here
	std::vector<T> haha;
	printPaths(root,haha);
}

template <typename T>
void BinaryTree<T>::printPaths(Node * subroot, std::vector<T> myvec) const
{
	if (subroot==NULL) {
		cout<<"Path: ";
		for (unsigned long i= 0 ; i < myvec.size()-1; i++)
			cout<<myvec.at(i)<<" ";
			cout<<myvec.at(myvec.size()-1)<<endl;
	return;
	}
	myvec.push_back(subroot->elem);
	if (subroot->left!=NULL && subroot->right!=NULL){
	printPaths(subroot->left,myvec);
	printPaths(subroot->right,myvec);
	}
	else if (subroot->left!=NULL)
	printPaths(subroot->left,myvec);
	else printPaths(subroot->right,myvec);
}	
/**
 * Each node in a tree has a distance from the root node - the depth of that node,
 *  or the number of edges along the path from that node to the root. This function returns
 *  the sum of the distances of all nodes to the root node (the sum of the depths of all
 *  the nodes). Your solution should take O(n) time, where n is the number of nodes in the tree.
 * @return The sum of the distances of all nodes to the root
 */
template <typename T>
int BinaryTree<T>::sumDistances() const
{
    // your code here
    	int result = 0; int i = 0;
	return sumDistances(root,i,result);
}

template <typename T>
int BinaryTree<T>::sumDistances(Node * subroot, int i,int& result )const
{	if (subroot ==NULL) return 0;
//	result = result+i;
	sumDistances(subroot->left,i+1,result);
	sumDistances(subroot->right,i+1,result);
	result = result+i;
	return result;
	}
