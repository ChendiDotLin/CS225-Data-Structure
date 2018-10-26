/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 *
 * @author Chase Geigle
 * @date (created) Fall 2011
 * @date (modified) Spring 2012, Fall 2012
 *
 * @author Jack Toole
 * @date (modified) Fall 2011
 */

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
#include <iostream>
using namespace std;
template <class T>
List<T>::~List()
{
 clear();   /// @todo Graded in MP3.1
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear()
{
    /// @todo Graded in MP3.1
	if (empty()) return;
	ListNode * thisguy = head;
	ListNode * nextguy = NULL;
	while (length >1 ){
		nextguy = (*thisguy).next;
		delete thisguy;
		thisguy = nextguy;
		nextguy = NULL;
		length--;
		}
	delete thisguy; 
	delete nextguy;
	thisguy = NULL;
	nextguy = NULL;
	head = NULL;
	tail = NULL;
	length=0;

}



/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const & ndata)
{
    /// @todo Graded in MP3.1
	if (empty()) {
		head = new ListNode(ndata);
		tail = head;
		length =1;
	}
	else {
	ListNode * temp = new ListNode(ndata);
	(*temp).next = head;
	(*head).prev = temp;
	head = temp;
	length ++;
	}	
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack( const T & ndata )
{
    /// @todo Graded in MP3.1
	if (empty()){
	head = new ListNode(ndata);
	tail = head;
	length = 1;
	}
	else {
	ListNode *temp = new ListNode (ndata);
	(*temp).prev = tail;
	(*tail).next = temp;
	tail = temp;
	length++;		
	}
}


/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse()
{
    reverse(head, tail);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */																	
template <class T>
void List<T>::reverse( ListNode * & startPoint, ListNode * & endPoint )
{
    /// @todo Graded in MP3.1
//not head tail
if (empty()) return;
if (startPoint == endPoint){cout<<"heh"<<endl; return;}
//	cout<<"o"<<endl;
	ListNode * curr = (*startPoint).next;
	ListNode * temp = (*startPoint).prev;
	(*startPoint).prev = (*startPoint).next;
//	cout<<"0"<<endl;
	if ((*endPoint).next!=NULL)(*startPoint).next = (*endPoint).next;
	else (*startPoint).next =NULL;
//	cout<<"0"<<endl;
	while (curr!=endPoint &&curr!=NULL){
	//	cout<<"@@"<<endl;
		ListNode * temp1 = (*curr).prev;
		(*curr).prev = (*curr).next;
		(*curr).next = temp1;
		curr = (*curr).prev;
	}

//	ListNode * temp = (*endPoint).prev;
	ListNode * tempfornext = (*endPoint).next;
	(*endPoint).next = (*endPoint).prev;
//	cout<<"yujn"<<endl;
	(*endPoint).prev = temp;
	if (startPoint == head && endPoint != tail)
	{
//		cout<<"here!"<<endl; 
		(*tempfornext).prev = startPoint;
		head = endPoint;
		}
	else if (startPoint != head && endPoint == tail) 
	{	
//		cout<<"there"<<endl;
		(*temp).next = endPoint;
//		cout<<"wocao"<<endl;
		tail = startPoint;
		}
	else if (startPoint == head && endPoint == tail) {
		ListNode * temp = head;
		head = endPoint;
		tail = temp;
//		cout<<"fefe"<<endl;
	}
	else {
		 (*temp).next = endPoint;
		 (*tempfornext).prev = startPoint;
	}
	}	      
/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth( int n )
{

//int times = length/n;
//cout<<times<<endl;
if (empty()) return;
int remain = length -n;
//cout<<remain<<endl;
if (remain <=0) {reverse(); 
	return;}
ListNode * startpoint = head;
ListNode * thispoint = head;
	while (remain >0)
	{
//	{cout<<times<<endl;
	for (int i = 0;i<n-1 ; i++){
		//cout<<"!"<<endl;
		thispoint = (*thispoint).next;
		}
//	cout<<"reverse problem"<<endl;
	ListNode * temps = startpoint;
	ListNode * tempt = thispoint;
	startpoint = (*thispoint).next;
	thispoint = (*thispoint).next;

	reverse (temps, tempt);
	remain = remain -n;		
//	cout<<remain<<endl;
	if (remain <=0) {
//		cout<<"finally"<<endl;
		reverse(startpoint,tail);
		return;	
	}
}
}	    /// @todo Graded in MP3.1



/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall()
{
    /// @todo Graded in MP3.1
	if (head == tail ) return;
	ListNode * curr = (*head).next;
	while  (curr != tail && curr != NULL )
	{
	ListNode * temp = (*curr).next;
	(*curr).prev->next = temp;
	(*temp).prev = (*curr).prev;
	(*curr).prev = tail;
	(*tail).next = curr;
	(*curr).next = NULL;
	tail = curr;
	curr = (*temp).next;
	}



}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint)
{
    if (splitPoint > length)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode * secondHead = split(head, splitPoint);

    int oldLength = length;
    if (secondHead == head)
    {
        // current list is going to be empty
        head = NULL;
        tail = NULL;
        length = 0;
    }
    else
    {
        // set up current list
        tail = head;
        while (tail->next != NULL)
            tail = tail->next;
        length = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head = secondHead;
    ret.tail = secondHead;
    if (ret.tail != NULL)
    {
        while (ret.tail->next != NULL)
            ret.tail = ret.tail->next;
    }
    ret.length = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint)
{
    /// @todo Graded in MP3.2
	ListNode * tnode = start;
	for (int i = 0; i< splitPoint-1; i++){
		tnode = (*tnode).next;
	}
	ListNode * newstart = (*tnode).next;
	//splitpoint too large?
	(*newstart).prev = NULL;
	(*tnode).next = NULL;	
	return newstart;	 

 // change me!
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T> & otherList)
{
    // set up the current list
    head = merge(head, otherList.head);
    tail = head;
	cout<<"ehh"<<endl;
    // make sure there is a node in the new list
    if(tail != NULL)
    {
        while (tail->next != NULL){
	cout<<"aaa"<<endl;    
        tail = tail->next;}
    }
    length = length + otherList.length;

    // empty out the parameter list
    otherList.head = NULL;
    otherList.tail = NULL;
    otherList.length = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <class T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode * second)
{
    /// @todo Graded in MP3.2
	ListNode * fstart = first;
        ListNode * sstart = second;
	ListNode * who = NULL;
	while (fstart!=NULL && sstart!=NULL){
		ListNode * superf = (*fstart).next;
		ListNode * supers = (*sstart).next;
	//	cout<<"0"<<endl;
		if (fstart->data < sstart->data) 			 
		{	(*fstart).prev = who;
			if (who!=NULL) (*who).next = fstart;
			(*fstart).next = sstart;
			(*sstart).prev = fstart;
			who = fstart;
			fstart = superf;
		}
		else {
			(*sstart).prev = who;
			if (who!=NULL)
			(*who).next = sstart;
		        (*sstart).next = fstart;
                        (*fstart).prev = sstart;
                        who = sstart ;
 			sstart = supers;
			}
	//	cout<<"1"<<endl;
	//	fstart = superf;
	//	sstart = supers;
	}
	//	cout<<"getout"<<endl;
/*	while (fstart == NULL && sstart !=NULL){
		ListNode * lol = (*sstart).next;
		
		(*sstart).prev = who;
		who = (*sstart).next;
		sstart = lol;
		}
	while (sstart == NULL && fstart!=NULL){
		ListNode * lol = (*fstart).next;
                (*who).next = fstart;
                (*fstart).prev = who;
                who = (*fstart).next;
                fstart = lol;	*/
		if (first->data<second->data) head = first;
		else head = second;
  return head; // change me!
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort()
{
    if (empty())
        return;
    head = mergesort(head, length);
    tail = head;
    while (tail->next != NULL)
        tail = tail->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode * List<T>::mergesort(ListNode * start, int chainLength)
{
    /// @todo Graded in MP3.2
//	ListNode * ss = split(chainLength/2).head;;
//	chainLength = chainLength/2;
	if (chainLength <= 1)//>1 else return 
	{	return start;
		cout<<"1"<<endl;	}
		ListNode * ss = split(start,chainLength/2);
	       //chainLength = chainLength/2;
		cout<<"2"<<endl;
		start = mergesort (start, chainLength/2);
		cout<<"3"<<endl;
		ss = mergesort (ss,chainLength - chainLength/2);
		cout<<"4"<<endl;
		return merge (start,ss);
	
//	return start; // change me!
}
