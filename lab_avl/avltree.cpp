/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
using namespace std;

template <class K, class V>
V AVLTree<K, V>::find(const K & key) const
{
	return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node * subtree, const K & key) const
{
	if (subtree == NULL)
		return V();
	else if (key == subtree->key)
		return subtree->value;
	else
	{
		if (key < subtree->key)
			return find(subtree->left, key);
		else
			return find(subtree->right, key);
	}
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node * & t)
{
	*_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    // your code here
	Node * temp = t->right;
	t->right = temp->left;
	temp->left = t;
	t = temp;
	t->left->height = max(getHeight(t->left->left), getHeight(t->left->right))+1;
	t->height = max(getHeight(t->left), getHeight(t->right))+1;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node * & t)
{
	*_out << __func__ << endl; // Outputs the rotation name (don't remove this)
	// Implemented for you:
	rotateLeft(t->left);
	rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node * & t)
{
	*_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    // your code here
	Node * temp = t->left;
	t->left = temp->right;
	temp->right = t;
	t = temp;
	t->right->height = max ( getHeight(t->right->left),getHeight(t->right->right))+1;
	t->height = max( getHeight(t->left), getHeight(t->right))+1;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node * & t)
{
	*_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    // your code here
	rotateRight(t->right);
	rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
	if (root == NULL) {
	root =  new Node(key, value);
//	root = a;
	root->height = 0;
	}
	else
	 insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node* & subtree, const K & key, const V & value)
{
    // your code here
	if ( subtree == NULL ) {
	subtree = new Node (key,value);
	subtree->height = 0;
	}
	else  if ( key < subtree->key){
	//	if ( subtree->left == NULL) subtree->left = new Node ( key, value);
//		cout<<"nonono"<<endl;
		 insert (subtree->left,key,value);
		if (balancedFactor(subtree)==-2){
			if (balancedFactor (subtree->left) == -1)
				rotateRight(subtree);
			else 
			rotateLeftRight(subtree);
			
			}
	
		subtree->height = max(getHeight(subtree->left), getHeight(subtree->right))+1 ;
	//	subtree->height = getHeight(subtree->left)+1;
	}
	else if (key > subtree->key){
//		cout<<"214132"<<endl;
	//	if ( subtree->right == NULL) subtree->right = new Node ( key, value); 
		insert(subtree->right, key , value);
		if (balancedFactor(subtree) == 2){
			if (balancedFactor (subtree->right) == 1)
				rotateLeft(subtree);
				
			else 
			rotateRightLeft(subtree);
			}
		subtree->height = max(getHeight(subtree->right), getHeight(subtree->left))+1;
//		subtree->height = getHeight(subtree->right)+1;
	}

}

template<class K, class V>
int AVLTree<K,V>::balancedFactor(Node * t){
	return (getHeight(t->right))- (getHeight(t->left));
}

template<class K, class V>
int AVLTree<K,V>::getHeight(Node * t){
	if (t==NULL) return -1;
	else return t->height;
}
