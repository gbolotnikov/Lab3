#ifndef __LIST_HPP_
#define __LIST_HPP_

#include <memory>
#include <type_traits>

template <class T,  typename _Alloc>
class List;

template<typename TBaseType>
class ListIterator;

template<typename TBaseType>
class ListConstIterator;

template<typename T>
class ListNode {

friend class ListIterator<T>;
friend class ListConstIterator<T>;

template<class U, typename _Alloc>
friend class List;

 private:   
    T _value;
    ListNode<T>* _next; 
public:
    ListNode(T curValue): 
        _value(curValue),
        _next(nullptr)
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

    T& operator*() {
    	return _node->_value;
    }

    ListIterator& operator++() {
    	_node = _node->_next;
    	return *this;
    }

private:
    ListNode<T>* _node;
};

template<typename T>
class ListConstIterator: public std::iterator<std::input_iterator_tag, ListNode<T>>
{
    template<class U, typename _Alloc>
    friend class List;
private:
    ListConstIterator(ListNode<T>* node):
    	_node(node)
    { }
    
public:

    ListConstIterator(const ListConstIterator &it):
    	_node(it._node)
    { }

    bool operator!=(const ListConstIterator<T>& other) const {
    	return _node != other._node;
    }

    bool operator==(const ListConstIterator<T>& other) const {
    	return _node == other._node;
    }

    const T& operator*() {
    	return _node->_value;
    }

    ListConstIterator& operator++() {
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
    using const_pointer = ListNode<const T>*;
    using allocator_type = _Alloc;
    using AllocType =  typename _Alloc::template
        rebind<ListNode<T>>::other;   
    using iterator = ListIterator<T>;
    using const_iterator = ListConstIterator<T>;     

private:   
    AllocType _alloc;  
    pointer _head = nullptr;
    pointer _end = nullptr;

private:   
    void destruct(pointer curr, pointer last) {
        while(curr != last) {
            auto temp = curr;
            curr = curr->_next;
            _alloc.destroy(temp);
            _alloc.deallocate(temp, 1);
        }
    }

    bool empty() {
        return _head == nullptr;
    }

public:
    ~List() {
        destruct(_head, nullptr);       
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
    	return iterator(nullptr);
    }

    const_iterator end() const {;
    	return const_iterator(nullptr);
    }   

};

#endif