#pragma once
#include <iostream>
/********************************
*								*
*	My set class declaration	*
*	Background - RB Tree		*
*								*
*********************************/


template<typename T>
class Set {

private:
	struct node
	{
		T data;
		// 0 - red
		// 1 - black
		unsigned int color : 1;
		
		node * parent;
		node * left;
		node * right;

		node(unsigned int _color, node * _parent, node * _left, node * _right);
		node(T _data, unsigned int _color, node * _parent, node * _left, node * _right);
	};

	class iterator {
	private:
		node * leaf;
		node * current;
		node * crit;
	public:
		iterator(node* _n, node * _leaf, node * _crit);
		T operator*();
		iterator& operator++();
		iterator  operator++(int);
		iterator& operator--();
		iterator  operator--(int);
		bool operator==(iterator & const left);
		bool operator!=(iterator & const left);
	};

	unsigned int _size;
	node * root;
	node   leaf;
	node * first;
	node * last;

	void rotateLeft(node * n);
	void rotateRight(node * n);
	void addFix(node * n);
	void removeFix(node * n);

	virtual node *  add(node * n);
	node *			getNode(T v);
	node *			extractNode(node * n);

	friend iterator;
public:
	Set();
	Set(T item);
	~Set();

	bool		 find(T item);
	virtual bool add(T v);
	bool		 remove(T v);
	void		 removeAll(T v);
	bool		 clear();
	unsigned int size();
	T			 min();
	T			 max();
	iterator	 begin();
	iterator	 end();

	template<typename U>
	friend std::ostream& operator<< (std::ostream& out, const Set<U> & _Set);
	template<typename U>
	friend std::istream& operator>> (std::istream& out, const Set<U> & _Set);
	bool operator< ( Set<T> & const _Set);
	bool operator==( Set<T> & const _Set);
	bool operator<=( Set<T> & const _Set);
	bool operator> ( Set<T> & const _Set);
	bool operator>=( Set<T> & const _Set);
};

#include "set.ipp"

template<typename T>
class multiSet : public Set<T> {
private:
	struct node : Set<T>::node
	{
		unsigned int count;
	};
};