#pragma once

/********************************
*								*
*	My set structure			*
*	Background - RB Tree		*
*								*
********************************/

#define cin std::cin
#define cout std::cout
#define endl std::endl
#define NIL &leaf
#define RED 0
#define BLACK 1
#define dad n->parent
#define grandpa n->parent->parent

/*
	node structure:
	T			data
	int			color
	node *		parent
	node *		left
	node *		right
*/

// Node ctrs
template<typename T>
Set<T>::node::node(unsigned int _color, node * _parent, node * _left, node * _right) : 
	color(_color), parent(_parent), left(_left), right(_right) {
	
}

template<typename T>
Set<T>::node::node(T _data, unsigned int _color, node * _parent, node * _left, node * _right) :
	color(_color), parent(_parent), left(_left), right(_right), data(_data) {

}

// Set ctrs
template<typename T>
Set<T>::Set() : 
	leaf(node(BLACK, NULL, NIL, NIL)), root(NIL), _size(0), first(root), last(root) {

}

template<typename T>
Set<T>::Set(T item) : Set() {
	add(item);
}

// Set dtr
template<typename T>
Set<T>::~Set() {

}

/************************
*  Set private methods	*
************************/

// Tree rotations
template<typename T>
void Set<T>::rotateLeft(node * n) {
	node * y = n->right;

	n->right = y->left;
	if (y->left != NIL) {
		y->left->parent = n;
	}

	if (y != NIL) {
		y->parent = dad;
	}

	if (dad) {
		if (n == dad->left) {
			dad->left = y;
		}
		else {
			dad->right = y;
		}
	}
	else {
		root = y;
	}

	y->left = n;
	if (n != NIL) dad = y;
}

template<typename T>
void Set<T>::rotateRight(node * n) {
	node * y = n->left;

	n->left = y->right;
	if (y->right != NIL) {
		y->right->parent = n;
	}

	if (y != NIL) {
		y->parent = dad;
	}

	if (dad) {
		if (n == dad->right) {
			dad->right = y;
		}
		else {
			dad->left = y;
		}
	}
	else {
		root = y;
	}

	y->right = n;
	if (n != NIL) dad = y;
}

//Tree add fix
template<typename T>
void Set<T>::addFix(node * n) {
	node * uncle;
	while (n != root && dad->color == RED) {
		if (dad == grandpa->left) {
			uncle = grandpa->right;
			if (uncle->color == RED) {
				dad->color = BLACK;
				uncle->color = BLACK;
				grandpa->color = RED;
				n = grandpa;
			}
			else {
				if (n == dad->right) {
					n = dad;
					rotateLeft(n);
				}
				dad->color = BLACK;
				grandpa->color = RED;
				rotateRight(grandpa);
			}
		}
		else {
			uncle = grandpa->left;
			if (uncle->color == RED) {
				dad->color = BLACK;
				uncle->color = BLACK;
				grandpa->color = RED;
				n = grandpa;
			}
			else {
				if (n == dad->left) {
					n = dad;
					rotateRight(n);
				}
				dad->color = BLACK;
				grandpa->color = RED;
				rotateLeft(grandpa);
			}
		}
	}
	root->color = BLACK;
}

// Tree remove fix
template<typename T>
void Set<T>::removeFix(node * n) {
	node *sibling;
	while (n != root && n->color == BLACK) {
		if (n == dad->left) {
			sibling = dad->right;
			if (sibling->color == RED) {
				sibling->color = BLACK;
				dad->color = RED;
				rotateLeft(dad);
				sibling = dad->right;
			}
			if (sibling->left->color == BLACK &&
				sibling->right->color == BLACK) {

				sibling->color = RED;
				n = dad;
			}
			else {
				if (sibling->right->color == BLACK) {
					sibling->left->color = BLACK;
					sibling->color = RED;
					rotateRight(sibling);
					sibling = dad->right;
				}
				sibling->color = dad->color;
				dad->color = BLACK;
				sibling->right->color = BLACK;
				rotateLeft(dad);
				n = root;
			}
		}
		else {
			sibling = dad->left;
			if (sibling->color == RED) {
				sibling->color = BLACK;
				dad->color = RED;
				rotateRight(dad);
				sibling = dad->left;
			}
			if (sibling->right->color == BLACK &&
				sibling->left->color == BLACK) {

				sibling->color = RED;
				n = dad;
			}
			else {
				if (sibling->left->color == BLACK) {
					sibling->right->color = BLACK;
					sibling->color = RED;
					rotateLeft(sibling);
					sibling = dad->left;
				}
				sibling->color = dad->color;
				dad->color = BLACK;
				sibling->left->color = BLACK;
				rotateRight(dad);
				n = root;
			}
		}
	}
	n->color = BLACK;
}

#undef dad
#undef grandpa

// Tree node addition
template<typename T>
typename Set<T>::node * Set<T>::add(node * n) {
	node * cur = root;
	node * dad = NULL;
	while (cur != NIL) {
		if (cur->data < n->data) {
			dad = cur;
			cur = cur->right;
		}
		else if (cur->data > n->data) {
			dad = cur;
			cur = cur->left;
		}
		else {
			return NIL;
		}
	}
	n->parent = dad;
	if (dad) {
		if (dad->data > n->data) {
			dad->left = n;
		}
		else {
			dad->right = n;
		}
	}
	else {
		root = n;
		first = root;
		last = root;
	}
	addFix(n);
	// Fixing min/max values
	while(first->left != NIL) first = first->left;
	while (last->right != NIL) last = last->right;
	
	return n;
}

// Tree node removing 
template<typename T>
typename Set<T>::node * Set<T>::extractNode(node * n) {
	if (n == NIL) return n;
	if (n == last && last->parent != NULL) last = last->parent;
	if (n == first && first->parent != NULL) first = first->parent;
	node * tmp;
	node * x;
	node * y;

	// check if there is only one child
	if (n->left == NIL || n->right == NIL) {
		y = n;
	}
	else {
		y = n->right;
		while (y->left != NIL) y = y->left;
	}
	// y - node || inorder successor
	if (y->left != NIL) {
		x = y->left;
	}
	else {
		x = y->right;
	}
	x->parent = y->parent;
	//check on root and change ref in parent
	if (y->parent) {
		if (y == y->parent->left) {
			y->parent->left = x;
		}
		else {
			y->parent->right = x;
		}
	}
	else {
		root = x;
	}
	// if 
	if (y != n) {
		n->data = y->data;
	}

	tmp = y;
	if (y->color == BLACK) {
		removeFix(x);
	}

	delete y;
	//y = NULL;

	(first == tmp) && (first = root);
	(last == tmp) && (last = root);
	while (first->left != NIL) {
		first = first->left;
	}
	while (last->right != NIL) {
		last = last->right;
	}

	return tmp;
}

// Tree node getting
template<typename T>
typename Set<T>::node * Set<T>::getNode(T item) {
	node * cur = root;
	while (cur != NIL) {
		if (cur->data > item) {
			cur = cur->left;
		}
		else if (cur->data < item) {
			cur = cur->right;
		}
		else {
			return cur;
		}
	}
	return NIL;
}

/************************
*  Set public methods	*
************************/

// Set getting mininum item
template <typename T>
T Set<T>::min() {
	return first->data;
}

// Set getting maximum item
template <typename T>
T Set<T>::max() {
	return last->data;
}

// Set item addition
template<typename T>
bool Set<T>::add(T item) {
	node * n = new node( item, RED, NULL, NIL, NIL);
	return add(n) == NIL ? false : ++_size;
}

// Set item finding
template<typename T>
bool Set<T>::find(T item) {
	node * cur = root;
	while (cur != NIL) {
		if (cur->data > item) {
			cur = cur->left;
		}
		else if (cur->data < item) {
			cur = cur->right;
		}
		else {
			return true;
		}
	}
	return false;
}

// Set item removing
template<typename T>
bool Set<T>::remove(T item) {
	if (root == NIL) return false;
	node * n = getNode(item);
	if (extractNode(n) == NIL) return false;
	--(_size);
	return true;
}

// Set all item (key == item) removing
template<typename T>
void Set<T>::removeAll(T item) {
	while (remove(item));
}

// Set clearing
template<typename T>
bool Set<T>::clear() {

	while (root != NIL) { 
		extractNode(root); 
	}

	_size = 0;
	return true;
}

// Set getting size
template<typename T>
unsigned int Set<T>::size() {
	return _size;
}

// Return iterator on the first set item
template<typename T>
typename Set<T>::iterator Set<T>::begin() {
	node * crit = new node(BLACK, last, NIL, NIL);
	if (root == NIL) return iterator(crit, NIL, crit);
	return iterator(first, NIL, crit);
}

// Return iterator on the elem after last ( "crit" )
template<typename T>
typename Set<T>::iterator Set<T>::end() {
	node * crit = new node(BLACK, last, NIL, NIL);
	return iterator(crit, NIL, crit);
}

/**************************************
*        USE ITERATOR CAREFULLY		  *
*	WHILE ITERATING DON"T MODIFY SET  *
*  IT MAY CAUSE OF DIFFERENT PROBLEM  *
***************************************
*			Iterator methods	      *
**************************************/

// Iterator ctr
template<typename T>
Set<T>::iterator::iterator(node * _n, node * _leaf, node * _crit) : 
	current(_n), leaf(_leaf), crit(_crit) {

}

// Iterator operators
template<typename T>
T Set<T>::iterator::operator*() {
	if (current == crit || current == NULL) throw 1;
	return this->current->data;
}

template<typename T>
typename Set<T>::iterator& Set<T>::iterator::operator++() {
	if (current == crit) throw 1;
	if (current->right != this->leaf) {
		current = current->right;
		while (current->left != this->leaf) {
			current = current->left;
		}
		return *this;
	}
	else {
		if (current == crit->parent) {
			current = crit;
			return *this;
		}
		while (current->parent->right == current) {
			current = current->parent;
		}
		current = current->parent;
		return *this;
	}
}

template<typename T>
typename Set<T>::iterator Set<T>::iterator::operator++(int) {
	iterator t = *this;
	++(*this);
	return t;
}

template<typename T>
typename Set<T>::iterator& Set<T>::iterator::operator--() {
	if (current == crit) {
		current = crit->parent;
		return *this;
	}
	if (current->left != this->leaf) {
		current = current->left;
		while (current->right != this->leaf) {
			current = current->right;
		}
		return *this;
	}
	else {
		while (current->parent && current->parent->left == current) {
			current = current->parent;
		}
		current = current->parent;
		return *this;
	}
}

template<typename T>
typename Set<T>::iterator Set<T>::iterator::operator--(int) {
	iterator t = *this;
	--(*this);
	return t;
}

template<typename T>
bool Set<T>::iterator::operator==(iterator & const left) {
	return (current == left.current || (current == crit && left.current == left.crit));
}

template<typename T>
bool Set<T>::iterator::operator!=(iterator & const left) {
	return !(*this == left);
}

/****************************
*  Set operators overload	*
****************************/

template<typename T>
bool Set<T>::operator==(Set<T> & const _Set) {
	if (this->_size != _Set._size) return false;
	auto s0 = this->begin();
	auto e0 = this->end();

	auto s1 = _Set.begin();
	auto e1 = _Set.end();

	while (s0 != e0) {
		if (*(s0++) != *(s1++)) return false;
	}
	return true;
}

template<typename T>
bool Set<T>::operator<( Set<T> & const _Set) {
	return this->_size < _Set._size;
}

template<typename T>
bool Set<T>::operator>( Set<T> & const _Set) {
	return this->_size > _Set._size;
}

template<typename T>
bool Set<T>::operator>=(Set<T> & const _Set) {
	return this->_size >= _Set._size;
}

template<typename T>
bool Set<T>::operator<=(Set<T> & const _Set) {
	return this->_size <= _Set._size;
}

template<typename T>
std::ostream& operator<< (std::ostream& out, Set<T> & const _Set) {
	auto a = _Set.begin();
	auto b = _Set.end();
	while (a != b) {
		out << *(a++) << (a == b ? "" : " ");
	}
	return out;
}

template<typename T>
std::istream& operator>> (std::istream& input, Set<T> & const _Set) {
	T temp;
	input >> temp;
	_Set.add(temp);
	return input;
}


#undef cin 
#undef cout 
#undef endl 
#undef NIL 
#undef RED 
#undef BLACK 