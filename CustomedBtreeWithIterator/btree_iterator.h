#ifndef BTREE_ITERATOR_H
#define BTREE_ITERATOR_H

#include <iterator>
#include <queue>
using namespace std;
/**
 * You MUST implement the btree iterators as (an) external class(es) in this file.
 * Failure to do so will result in a total mark of 0 for this deliverable.
 **/

// iterator related interface stuff here; would be nice if you called your
// iterator class btree_iterator (and possibly const_btree_iterator)
template<typename T> class btree;
template<typename T> class btree_iterator;
template<typename T> class const_btree_iterator;

template<typename T> class btree_iterator{
public:
    typedef ptrdiff_t                     difference_type;
    typedef std::bidirectional_iterator_tag    iterator_category;
    typedef T                             value_type;
    typedef T*                            pointer;
    typedef T&                            reference;
    friend class btree<T>;
    friend class const_btree_iterator<T>;
    typedef typename btree<T>::TreeNode TreeNode;
    
    reference       operator *() const;
    pointer         operator->() const;
    btree_iterator& operator++();
    btree_iterator& operator--();
    btree_iterator  operator++(int);
    btree_iterator  operator--(int);
    btree_iterator& operator =(const btree_iterator& target);
    bool            operator==(const btree_iterator& target) const;
    bool            operator==(const const_btree_iterator<T>& target) const;
    bool            operator!=(const btree_iterator& target) const;
    bool            operator!=(const const_btree_iterator<T>& target) const;
    
    btree_iterator() : pointee(),element_position(),btree_ptr(){}
    btree_iterator(typename btree<T>::TreeNode *p, const size_t i, const btree<T> *bt) :
    pointee(p),element_position(i), btree_ptr(bt){}
    
    
private:
    typename btree<T>::TreeNode* pointee;
    size_t element_position;
    const btree<T>* btree_ptr;
};
template<typename T> class const_btree_iterator{
public:
    typedef ptrdiff_t                     difference_type;
    typedef std::bidirectional_iterator_tag    iterator_category;
    typedef T                             value_type;
    typedef T*                            pointer;
    typedef T&                            reference;
    friend class btree<T>;
    friend class btree_iterator<T>;
    typedef typename btree<T>::TreeNode TreeNode;
    
    reference       operator *() const;
    pointer         operator->() const;
    const_btree_iterator& operator++();
    const_btree_iterator& operator--();
    const_btree_iterator  operator++(int);
    const_btree_iterator  operator--(int);
    const_btree_iterator& operator =(const const_btree_iterator& target);
    bool            operator==(const btree_iterator<T>& target) const;
    bool            operator==(const const_btree_iterator& target) const;
    bool            operator!=(const btree_iterator<T>& target) const;
    bool            operator!=(const const_btree_iterator& target) const;
    
    const_btree_iterator() : pointee(),element_position(),btree_ptr(){}
    const_btree_iterator(typename btree<T>::TreeNode *p, const size_t i, const btree<T> *bt) :
    pointee(p),element_position(i), btree_ptr(bt){}
    const_btree_iterator(const btree_iterator<T>& target):
    pointee(target.pointee),element_position(target.element_position),btree_ptr(target.btree_ptr){}
    
private:
    typename btree<T>::TreeNode* pointee;
    size_t element_position;
    const btree<T>* btree_ptr;
};

template<typename T> typename btree_iterator<T>::reference btree_iterator<T>::operator*() const{
    return pointee->element[element_position];
}
template<typename T> typename btree_iterator<T>::pointer btree_iterator<T>::operator->() const{
    return &(operator*());
}
template<typename T> bool
btree_iterator<T>::operator ==(const btree_iterator<T>& target) const {
    if(pointee == target.pointee && element_position == target.element_position && btree_ptr == target.btree_ptr){
        return true;
    }else{
        return false;
    }
}
template<typename T> bool
btree_iterator<T>::operator ==(const const_btree_iterator<T>& target) const {
    if(pointee == target.pointee && element_position == target.element_position && btree_ptr == target.btree_ptr){
        return true;
    }else{
        return false;
    }
}
template<typename T> bool
btree_iterator<T>::operator !=(const btree_iterator<T>& target) const {
    return (! operator== (target));
}
template<typename T> bool
btree_iterator<T>::operator !=(const const_btree_iterator<T>& target) const {
    return (! operator== (target));
}
template<typename T> typename btree_iterator<T>::btree_iterator& btree_iterator<T>::operator++(){
    if(pointee==nullptr){
        pointee = btree_ptr->Headnode;
        element_position = 0;
        return *this;
    }
    else if(pointee->children[element_position+1] != nullptr){
        //pointee = pointee->children[element_position + 1];
        std::queue<std::pair<TreeNode*, size_t>> Q;
        Q.push(std::make_pair(pointee->children[element_position+1],element_position+1));
        while(!Q.empty()){
            std::pair<TreeNode*, size_t> temp = Q.front();
            Q.pop();
            /*
             pointee = Q.front();
             element_position = 0;
             Q.pop();*/
            pointee = temp.first;
            element_position = temp.second;
            if(pointee->current_size == pointee->max_nodes_num && pointee->children[element_position] != nullptr){
                //Q.push(pointee->children[element_position]);
                std::cout<<"1"<<std::endl;
                Q.push(std::make_pair(pointee->children[element_position],0));
            }
        }
    }
    else if(element_position != pointee->current_size - 1){
        ++element_position;
        
    }
    else{
        //const T element_should_be_larger_than_this = pointee->element[element_position];
        /*
         std::queue<TreeNode*> Q;
         Q.push(pointee);*/
        std::queue<std::pair<TreeNode*, size_t>> Q;
        
        while(!Q.empty()){
            std::pair<TreeNode*, size_t> temp = Q.front();
            Q.pop();
            /*
             pointee = Q.front();
             Q.pop();*/
            pointee = temp.first;
            element_position = temp.second;
            if(pointee->parent_node != nullptr){
                pointee = pointee->parent_node;
                if(element_position < pointee->current_size){
                    Q.push(std::make_pair(pointee, element_position));
                }
                /*
                 for(element_position = 0; element_position != pointee->current_size;element_position++){
                 if(pointee->element[element_position] > element_should_be_larger_than_this){
                 return *this;
                 }
                 }*/
                //Q.push(pointee);
            }
            }
    }else{
                pointee = nullptr;
                element_position = 0;
                return *this;
    }
    return *this;
}
template<typename T> typename btree_iterator<T>::btree_iterator& btree_iterator<T>::operator--(){
    if(pointee==nullptr){
        pointee = btree_ptr->Tailnode;
        element_position = pointee->current_size - 1;
        return *this;
    } else if(pointee->children[element_position] != nullptr){
        std::queue<TreeNode*> Q;
        Q.push(pointee->children[element_position]);
        while(!Q.empty()){
            pointee = Q.front();
            Q.pop();
            element_position = pointee->current_size - 1;
            if(pointee->children[element_position+1] != nullptr){
                //std::cout<< "!!"<<std::endl;
                Q.push(pointee->children[element_position+1]);
            }else{
                return *this;
            }
        }
    }
    else if(element_position > 0){
        --element_position;
        return *this;
        
    }
    else{
        const T element_should_be_smaller_than_this = pointee->element[element_position];
        std::queue<TreeNode*> Q;
        Q.push(pointee);
        while(!Q.empty()){
            pointee = Q.front();
            Q.pop();
            if(pointee->parent_node != nullptr){
                pointee = pointee->parent_node;
                for(element_position = pointee->current_size - 1; element_position >= 0;--element_position){
                    if(pointee->element[element_position] < element_should_be_smaller_than_this){
                        return *this;
                    }if(element_position == 0){
                        break;
                    }
                }
                Q.push(pointee);
            }else{
                pointee = nullptr;
                element_position = 0;
                return *this;
            }
        }
    }
    return *this;
}
template<typename T> typename btree_iterator<T>::btree_iterator btree_iterator<T>::operator++(int){
    btree_iterator<T> return_before_operator = *this;
    operator++();
    return return_before_operator;
}
template<typename T> typename btree_iterator<T>::btree_iterator btree_iterator<T>::operator--(int){
    btree_iterator<T> return_before_operator = *this;
    operator--();
    return return_before_operator;
}
template<typename T> typename btree_iterator<T>::btree_iterator& btree_iterator<T>::operator =(const btree_iterator<T>& copy){
    if(this != &copy){
        pointee = copy.pointee;
        element_position = copy.element_position;
        btree_ptr = copy.btree_ptr;
    }
    return *this;
}



template<typename T> typename const_btree_iterator<T>::reference const_btree_iterator<T>::operator*() const{
    return pointee->element[element_position];
}
template<typename T> typename const_btree_iterator<T>::pointer const_btree_iterator<T>::operator->() const{
    return &(operator*());
}
template<typename T> bool
const_btree_iterator<T>::operator ==(const btree_iterator<T>& target) const {
    if(pointee == target.pointee && element_position == target.element_position && btree_ptr == target.btree_ptr){
        return true;
    }else{
        return false;
    }
}
template<typename T> bool
const_btree_iterator<T>::operator ==(const const_btree_iterator<T>& target) const {
    if(pointee == target.pointee && element_position == target.element_position && btree_ptr == target.btree_ptr){
        return true;
    }else{
        return false;
    }
}
template<typename T> bool
const_btree_iterator<T>::operator !=(const btree_iterator<T>& target) const {
    return (! operator== (target));
}
template<typename T> bool
const_btree_iterator<T>::operator !=(const const_btree_iterator<T>& target) const {
    return (! operator== (target));
}
template<typename T> typename const_btree_iterator<T>::const_btree_iterator& const_btree_iterator<T>::operator++(){
    if(pointee==nullptr){
        pointee = btree_ptr->Headnode;
        element_position = 0;
        return *this;
    }
    else if(pointee->children[element_position+1] != nullptr){
        //pointee = pointee->children[element_position + 1];
        std::queue<TreeNode*> Q;
        Q.push(pointee->children[element_position+1]);
        while(!Q.empty()){
            pointee = Q.front();
            element_position = 0;
            Q.pop();
            if(pointee->children[element_position] != nullptr){
                Q.push(pointee->children[element_position]);
            }else{
                return *this;
            }
        }
    }
    else if(element_position != pointee->current_size - 1){
        ++element_position;
        return *this;
        
    }
    else{
        const T element_should_be_larger_than_this = pointee->element[element_position];
        std::queue<TreeNode*> Q;
        Q.push(pointee);
        while(!Q.empty()){
            pointee = Q.front();
            Q.pop();
            if(pointee->parent_node != nullptr){
                pointee = pointee->parent_node;
                for(element_position = 0; element_position != pointee->current_size;element_position++){
                    if(pointee->element[element_position] > element_should_be_larger_than_this){
                        return *this;
                    }
                }
                Q.push(pointee);
            }else{
                pointee = nullptr;
                element_position = 0;
                return *this;
            }
        }
    }
    return *this;
}
template<typename T> typename const_btree_iterator<T>::const_btree_iterator& const_btree_iterator<T>::operator--(){
    if(pointee==nullptr){
        pointee = btree_ptr->Tailnode;
        element_position = pointee->current_size - 1;
        return *this;
    } else if(pointee->children[element_position] != nullptr){
        std::queue<TreeNode*> Q;
        Q.push(pointee->children[element_position]);
        while(!Q.empty()){
            pointee = Q.front();
            Q.pop();
            element_position = pointee->current_size - 1;
            if(pointee->children[element_position+1] != nullptr){
                //std::cout<< "!!"<<std::endl;
                Q.push(pointee->children[element_position+1]);
            }else{
                return *this;
            }
        }
    }
    else if(element_position > 0){
        --element_position;
        return *this;
        
    }
    else{
        const T element_should_be_smaller_than_this = pointee->element[element_position];
        std::queue<TreeNode*> Q;
        Q.push(pointee);
        while(!Q.empty()){
            pointee = Q.front();
            Q.pop();
            if(pointee->parent_node != nullptr){
                pointee = pointee->parent_node;
                for(element_position = pointee->current_size - 1; element_position >= 0;--element_position){
                    if(pointee->element[element_position] < element_should_be_smaller_than_this){
                        return *this;
                    }if(element_position == 0){
                        break;
                    }
                }
                Q.push(pointee);
            }else{
                pointee = nullptr;
                element_position = 0;
                return *this;
            }
        }
    }
    return *this;
}
template<typename T> typename const_btree_iterator<T>::const_btree_iterator const_btree_iterator<T>::operator++(int){
    const_btree_iterator<T> return_before_operator = *this;
    operator++();
    return return_before_operator;
}
template<typename T> typename const_btree_iterator<T>::const_btree_iterator const_btree_iterator<T>::operator--(int){
    const_btree_iterator<T> return_before_operator = *this;
    operator--();
    return return_before_operator;
}
template<typename T> typename const_btree_iterator<T>::const_btree_iterator& const_btree_iterator<T>::operator =(const const_btree_iterator<T>& copy){
    if(this != &copy){
        pointee = copy.pointee;
        element_position = copy.element_position;
        btree_ptr = copy.btree_ptr;
    }
    return *this;
}
#endif

