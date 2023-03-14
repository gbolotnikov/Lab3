#ifndef __LIST_HPP_
#define __LIST_HPP_

#include <memory>

template <class T,  typename _Alloc>
class List;

template<typename TBaseType>
class ListIterator;


template<typename T>
class ListNode {

friend class ListIterator<T>;

template<class U, typename _Alloc>
friend class List;

 private:   
    T _value;
    ListNode<T>* _next; 
public:
    ListNode(T curValue): 
        _value(curValue)
    {

    }    

    T value() const {
        return _value;
    }

    ~ListNode() {
        _value = 0;
        _next = nullptr;
    };
};

template<typename T>
class ListIterator: public std::iterator<std::input_iterator_tag, ListNode<T>>
{
    template<class U, typename _Alloc>
    friend class List;
private:
    ListIterator(ListNode<T>* node):
    	_node(node)
    { }
public:

    ListIterator(const ListIterator &it):
    	_node(it._node)
    { }

    bool operator!=(const ListIterator<T>& other) const {
    	return _node != other._node;
    }

    bool operator==(const ListIterator<T>& other) const {
    	return _node == other._node;
    }

    typename ListIterator<T>::reference operator*() const {
    	return *_node;
    }

    ListIterator& operator++() {
    	_node = _node->_next;
    	return *this;
    }

private:
    ListNode<T>* _node;
};

template <class T,  typename _Alloc = std::allocator<T>>
class List {
private:
    using pointer = ListNode<T>*;
    using allocator_type = _Alloc;
    using AllocType =  typename _Alloc::template
        rebind<ListNode<T>>::other;   
    using iterator = ListIterator<T>;
    using const_iterator = const ListIterator<T>;     

private:   
    AllocType _alloc;  
    pointer _head;
    pointer _end = _head;

private:   
    void destruct(pointer p) {
        if (p != _end) {
            destruct(p->_next);
        } 
        _alloc.destroy(p);
        _alloc.deallocate(p, 1);
    }

    bool empty() {
        return _head == nullptr;
    }

public:
    ~List() {
        destruct(_head);       
    }

   void push_back(T& item) {
        auto p = _alloc.allocate(1);
        _alloc.construct(p, item);
        if (empty()) {
            _end = p;
            _head = p;
        } else {
            _end->_next = p;
            _end = p;
        }
    }

    iterator begin() {
    	return iterator(_head);
    }

    const_iterator begin() const {
    	return const_iterator(_head);
    }

    iterator end() {
    	return iterator(_end->_next);
    }

    const_iterator end() const {
    	return const_iterator(_end->_next);
    }   

};

#endif