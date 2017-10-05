#pragma once
/**
* implement a container like std::map
*/
#ifndef SJTU_MAP_HPP
#define SJTU_MAP_HPP

// only for std::less<T>
#include <functional>
#include <cstddef>
#include "utility.hpp"
#include "exceptions.hpp"

namespace sjtu {

	template<
		class Key,
		class T,
		class Compare = std::less<Key>
	> class map {
	public:
		typedef pair<const Key, T> value_type;
	private:
		Compare comp;
		struct node {
			//Key num;
			//T data;
			value_type * data;
            node * leftchild;
			node * rightchild;
			node * pre;
			node * next;
			node * father;
			node(const value_type x, node * left, node * right, node * prex, node * nextx,node * fatherx) :data(x), leftchild(left), rightchild(right), pre(prex), next(nextx),father(fatherx) {}
			node(const node & obj) {
				data = obj.data;
				leftchild = obj.leftchild;
				rightchild = obj.rightchild;
				pre = obj.pre;
				next = obj.next;
				father = obj.father;
			}
			node() :leftchild(NULL), rightchild(NULL), pre(NULL), next(NULL),father(NULL) {}
			node & operator = (const node & other) {
				data = other.data;
				leftchild = other.leftchild;
				rightchild = other.rightchild;
				pre = other.pre;
				next = other.next;
				father = other.father;
				return *this;
			}
		};
	public:
		//Compare comp;
		//a < b
		//comp(a,b) 
		/**
		* the internal type of data.
		* it should have a default constructor, a copy constructor.
		* You can use sjtu::map as value_type by typedef.
		*/
		//typedef pair<const Key, T> value_type;
		/**
		* see BidirectionalIterator at CppReference for help.
		*
		* if there is anything wrong throw invalid_iterator.
		*     like it = map.begin(); --it;
		*       or it = map.end(); ++end();
		*/
		class const_iterator;
		class iterator {
		private:
			/**
			* TODO add data members
			*   just add whatever you want.
			*/
			node * itr;
			map * selfmap;
		public:
			iterator() {
				// TODO
				itr = NULL;
				selfmap = NULL;
			}
			iterator(const iterator &other) {
				// TODO
				itr = other.itr;
				selfmap = other.selfmap;
			}
			iterator(const_iterator &other) {
				// TODO
				itr = other.itr;
				selfmap = other.selfmap;
			}
			iterator(node * x, map * y):itr(x),selfmap(y){}
            /**
			* return a new iterator which pointer n-next elements
			*   even if there are not enough elements, just return the answer.
			* as well as operator-
			*/
			/**
			* TODO iter++
			*/
			iterator & operator = (const iterator & other) {
				itr = other.itr;
				selfmap = other.selfmap;
				return *this;
			}
			iterator & operator = (const const_iterator & other) {
				itr = other.itr;
				selfmap = other.selfmap;
				return *this;
			}
			iterator operator + (int x) {
				int i;
				node * tmp = itr;
				for (i = 1;i <= x;++i) {
					if (tmp->next == NULL) throw (invalid_iterator);
					tmp = tmp->next;
				}
				iterator tmpiterator(tmp, selfmap);
				return tmpiterator;
			}
			iterator operator - (int x) {
				int i;
				node * tmp=itr;
				for (i = 1;i <= x;++i) {
					if (tmp->pre == NULL) throw (invalid_iterator);
					tmp = tmp->pre;
				}
				iterator tmpiterator(tmp, selfmap);
				return tmpiterator;
			}
			// iter++
			iterator operator++(int) {
				node * tmp=itr;
				if (itr->next == NULL) throw (invalid_iterator);
				itr = itr->next;
				iterator tmpiterator(tmp, selfmap);
				return tmpiterator;
			}
			/**
			* TODO ++iter
			*/
			iterator & operator++() {
				if (itr->next == NULL) throw (invalid_iterator);
				itr = itr->next;
				return *this;
			}
			/**
			* TODO iter--
			*/
			iterator operator--(int) {
				node * tmp=itr;
				if (itr->pre == NULL) throw (invalid_iterator);
				itr = itr->pre;
				iterator tmpiterator(tmp, selfmap);
				return tmpiterator;
			}
			/**
			* TODO --iter
			*/
			iterator & operator--() {
				if (itr->pre == NULL) throw (invalid_iterator);
				itr = itr->pre;
				return *this;
			}
			/**
			* a operator to check whether two iterators are same (pointing to the same memory).
			*/    // Is the operation * ???
			value_type & operator*() const {     // I am not sure. Can an iterator that is not const go through this operation?
				//value_type p(itr->num, itr->data);
				//return p;
				return *(itr->data);
			}
			bool operator==(const iterator &rhs) const {   //I am not sure if it is necessary to compare "selfmap".
				return (itr == rhs.itr);
			}
			bool operator==(const const_iterator &rhs) const {
				return (itr == rhs.itr);
			}
			/**
			* some other operator for iterator.
			*/
			bool operator!=(const iterator &rhs) const {
				return (itr != rhs.itr);
			}
			bool operator!=(const const_iterator &rhs) const {
				return (itr != rhs.itr);
			}

			/**
			* for the support of it->first.
			* See <http://kelvinh.github.io/blog/2013/11/20/overloading-of-member-access-operator-dash-greater-than-symbol-in-cpp/> for help.
			*/
			value_type* operator->() const noexcept {  // I am not sure.
				return itr->data;
			}
		};
	class const_iterator {
			// it should has similar member method as iterator.
			//  and it should be able to construct from an iterator.
	 private:
			// data members.
			node * itr;
			map * selfmap;
      public:
		  const_iterator() {
			  // TODO
			  itr = NULL;
			  selfmap = NULL;
		  }
		  const_iterator(const iterator &other) {
			  // TODO
			  itr = other.itr;
			  selfmap = other.selfmap;
		  }
		  const_iterator(const_iterator &other) {
			  // TODO
			  itr = other.itr;
			  selfmap = other.selfmap;
		  }
		  const_iterator(node * x, map * y) :itr(x), selfmap(y) {}
		  /**
		  * return a new iterator which pointer n-next elements
		  *   even if there are not enough elements, just return the answer.
		  * as well as operator-
		  */
		  /**
		  * TODO iter++
		  */
		  const_iterator & operator = (const iterator & other) {
			  itr = other.itr;
			  selfmap = other.selfmap;
			  return *this;
		  }
		  const_iterator & operator = (const const_iterator & other) {
			  itr = other.itr;
			  selfmap = other.selfmap;
			  return *this;
		  }
		  const_iterator operator + (int x) {
			  int i;
			  node * tmp = itr;
			  for (i = 1;i <= x;++i) {
				  if (tmp->next == NULL) throw (invalid_iterator);
				  tmp = tmp->next;
			  }
			  const_iterator tmpiterator(tmp, selfmap);
			  return tmpiterator;
		  }
		  const_iterator operator - (int x) {
			  int i;
			  node * tmp = itr;
			  for (i = 1;i <= x;++i) {
				  if (tmp->pre == NULL) throw (invalid_iterator);
				  tmp = tmp->pre;
			  }
			  const_iterator tmpiterator(tmp, selfmap);
			  return tmpiterator;
		  }
		  // iter++
		  const_iterator operator++(int) {
			  node * tmp = itr;
			  if (itr->next == NULL) throw (invalid_iterator);
			  itr = itr->next;
			  const_iterator tmpiterator(tmp, selfmap);
			  return tmpiterator;
		  }
		  /**
		  * TODO ++iter
		  */
		  const_iterator & operator++() {
			  if (itr->next == NULL) throw (invalid_iterator);
			  itr = itr->next;
			  return *this;
		  }
		  /**
		  * TODO iter--
		  */
		  const_iterator operator--(int) {
			  node * tmp = itr;
			  if (itr->pre == NULL) throw (invalid_iterator);
			  itr = itr->pre;
			  const_iterator tmpiterator(tmp, selfmap);
			  return tmpiterator;
		  }
		  /**
		  * TODO --iter
		  */
		  const_iterator & operator--() {
			  if (itr->pre == NULL) throw (invalid_iterator);
			  itr = itr->pre;
			  return *this;
		  }
		  /**
		  * a operator to check whether two iterators are same (pointing to the same memory).
		  */    // Is the operation * ???
		  const value_type & operator*() const {     // I am not sure. Can an iterator that is not const go through this operation?
											   //value_type p(itr->num, itr->data);
											   //return p;
			  return *(itr->data);
		  }
		  bool operator==(const iterator &rhs) const {   //I am not sure if it is necessary to compare "selfmap".
			  return (itr == rhs.itr);
		  }
		  bool operator==(const const_iterator &rhs) const {
			  return (itr == rhs.itr);
		  }
		  /**
		  * some other operator for iterator.
		  */
		  bool operator!=(const iterator &rhs) const {
			  return (itr != rhs.itr);
		  }
		  bool operator!=(const const_iterator &rhs) const {
			  return (itr != rhs.itr);
		  }

		  /**
		  * for the support of it->first.
		  * See <http://kelvinh.github.io/blog/2013/11/20/overloading-of-member-access-operator-dash-greater-than-symbol-in-cpp/> for help.
		  */
		  value_type* operator->() const noexcept {  // I am not sure.
			  return itr->data;
		  }
		};
		private:
			node * root;
			node * head;
			node * rear;
			int size;
		public:
        map() {
			root = NULL;
			head = NULL;
			rear = NULL;
			size = 0;
		}
		map(const map &other) {
			copy(other.root);
			//head = other.head;
			//rear = other.rear;
			//size = other.size;
		}
		/**
		* TODO assignment operator
		*/
		map & operator=(const map &other) {
			copy(root, other.root);
			head = other.head;
			rear = other.rear;
			size = other.size;
			return *this;
		}
		/**
		* TODO Destructors
		*/
		~map() {
			clear();
			size = 0;
		}
		/**
		* TODO
		* access specified element with bounds checking
		* Returns a reference to the mapped value of the element with key equivalent to key.
		* If no such element exists, an exception of type `index_out_of_bound'
		*/
		T & at(const Key &key) {
			return (at(root, key));
		}
		const T & at(const Key &key) const {
			return (at(root, key));
		}
		/**
		* TODO
		* access specified element
		* Returns a reference to the value that is mapped to a key equivalent to key,
		*   performing an insertion if such key does not already exist.
		*/
		T & operator[](const Key &key) {
			return (find(root, key));
		}
		/**
		* behave like at() throw index_out_of_bound if such key does not exist.
		*/
		const T & operator[](const Key &key) const {
			return (find(root, key));
		}
		/**
		* return an iterator to the beginning
		*/
		iterator begin() {
			return iterator(head, *this);
		}
		const_iterator cbegin() const {
			return const_iterator(head, *this);
		}
		/**
		* return an iterator to the end
		* in fact, it returns past-the-end.
		*/
		iterator end() {
			return iterator(rear, *this);
		}
		const_iterator cend() const {
			return const_iterator(rear, *this);
		}
		/**
		* checks whether the container is empty
		* return true if empty, otherwise false.
		*/
		bool empty() const {
			return (size == 0);
		}
		/**
		* returns the number of elements.
		*/
		size_t size() const {
			return size;
		}
		/**
		* clears the contents
		*/
		void clear() {
			clear(root);
		}
		/**
		* insert an element.
		* return a pair, the first of the pair is
		*   the iterator to the new element (or the element that prevented the insertion),
		*   the second one is true if insert successfully, or false.
		*/
		pair<iterator, bool> insert(const value_type &value) {
			insert(value, root);
			size++;
		}
		/**
		* erase the element at pos.
		*
		* throw if pos pointed to a bad element (pos == this->end() || pos points an element out of this)
		*/
		void erase(iterator pos) {

		}
		/**
		* Returns the number of elements with key
		*   that compares equivalent to the specified argument,
		*   which is either 1 or 0
		*     since this container does not allow duplicates.
		* The default method of check the equivalence is !(a < b || b > a)
		*/
		size_t count(const Key &key) const {}
		/**
		* Finds an element with key equivalent to key.
		* key value of the element to search for.
		* Iterator to an element with key equivalent to key.
		*   If no such element is found, past-the-end (see end()) iterator is returned.
		*/
		iterator find(const Key &key) {}
		const_iterator find(const Key &key) const {}

private:
	copy(node * & x, const node * & y) {
		if (y->leftchild == NULL&&y->rightchild == NULL) {
			x->data = y->data;
			x->leftchild = NULL;
			x->rightchild = NULL;
			x->pre = y->pre;
			x->next = y->next;
			x->father = y->father;
		}
		else {
			if (y->leftchild != NULL) copy(x->leftchild, y->leftchild);
			if (y->rightchild != NULL)  copy(x->rightchild, y->rightchild);
			x->data = y->data;
			x->pre = y->pre;
			x->next = y->next;
			x->father = y->father;
		}
	}
	node * copy(const node * other) {
		x = new node(other->data, othercopy(other->leftchild), copy(other->rightchild), NULL, NULL, NULL);
		x->leftchild->father = x;
		x->rightchild->father = x;
		return x;
	}
	void setlist(node * t) const {
		if (t != NULL) {
			setlist(t->leftchild);
			node * tmp = head;
			head->pre = tmp;
			head->next = t;
		}
	}
	void equal(node * & x , const node * other) {
		if (x == NULL) return;
		else {
			x->data = other->data;
			equal(x->leftchild, other->leftchild);
			equal(x->rightchhild, other->rightchild);
			x->leftchild->father = x;
			x->rightchild->father = x;
		}
	}
	copy(node * & x, const node * & y) {
		node * p=
		//insert????
		while ()
	}





	map & operator=(node * & x, const node * & y) {
		if (y->leftchild == NULL&&y->rightchild == NULL) {
			x->data = y->data;
			x->leftchild = NULL;
			x->rightchild = NULL;
			x->pre = y->pre;
			x->next = y->next;
			x->father = y->father;
		}
		else {
			if (y->leftchild != NULL) x->leftchild = y->leftchild;
			if (y->rightchild != NULL) x->rightchild = y->rightchild;
			x->data = y->data;
			x->pre = y->pre;
			x->next = y->next;
		}
		return *this;
	}
	T & at(node * x, const Key & y) {
		if (x == NULL) throw (index_out_of_bound);
		if (x->data->first == y) return x->data->second;
		else {
			if (x->data->first < y) return (at(x->rightchild, y));
			if (x->data->first > y) return (at(x->leftchild, y));
		}
	}
	const T & at(node * x, const Key & y) const {
		if (x == NULL) throw (index_out_of_bound);
		if (x->data->first == y) return x->data->second;
		else {
			if (x->data->first < y) return (at(x->rightchild, y));
			if (x->data->first > y) return (at(x->leftchild, y));
		}
	}
	T & find(node * x, const Key & y) {
		if (x == NULL) throw (index_out_of_bound);
		if ((x->data->first) == y) return x->data->second;
		else {
			if ((x->data->first) < y) return (find(x->rightchild, y));
			if ((x->data->first) > y) return (find(x->leftchild, y));
		}
	}
	void clear(node * x) {
		if (x == NULL) return;
		else {
			if (x->leftchild != NULL) clear(x->leftchild);
			if (x->rightchild != NULL) clear(x->rightchild);
		}
	}
	pair<iterator, bool> insert(const value_type & x, node * & t) {
		if (t == NULL) {
			t = new node(x, NULL, NULL, NULL, NULL);
			iterator tmp(t, *this);   //I am not sure.
			return pair(iterator, true);    
		}
		else {
			if (x->first < t->data->first) {
				return (insert(x, t->leftchild));
			}
			if (!comp(x->first, t->data->first)) {
				return (insert(x, t->rightchild));
			}
			if (x->first == t->data->first) {
				iterator exp(t, *this);
				return pair(iterator, false);
			}
		}
	}




	};

}

#endif