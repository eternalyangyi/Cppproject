/**
 * The btree is a linked structure which operates much like
 * a binary search tree, save the fact that multiple client
 * elements are stored in a single node.  Whereas a single element
 * would partition the tree into two ordered subtrees, a node
 * that stores m client elements partition the tree
 * into m + 1 sorted subtrees.
 */

#ifndef BTREE_H
#define BTREE_H

#include <iostream>
#include <cstddef>
#include <utility>
#include <queue>

// we better include the iterator
#include "btree_iterator.h"
using namespace std;
// we do this to avoid compiler errors about non-template friends
// what do we do, remember? :)
template<typename T> class btree;
template<typename T> std::ostream &operator<<(std::ostream& os, const btree<T>& tree);
template <typename T>
class btree {
public:
    
    /** Hmm, need some iterator typedefs here... friends? **/
    typedef btree_iterator<T> iterator;
    typedef const_btree_iterator<T> const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
    friend class btree_iterator<T> ;
    friend class const_btree_iterator<T> ;
    /**
     * Constructs an empty btree.  Note that
     * the elements stored in your btree must
     * have a well-defined copy constructor and destructor.
     * The elements must also know how to order themselves
     * relative to each other by implementing operator<
     * and operator==. (These are already implemented on
     * behalf of all built-ins: ints, doubles, strings, etc.)
     *
     * @param maxNodeElems the maximum number of elements
     *        that can be stored in each B-Tree node
     */
    btree(size_t maxNodeElems = 40):
    Rootnode(nullptr),
    Headnode(nullptr),
    Tailnode(nullptr),
    max_nodes_limit(maxNodeElems){}
    
    /**
     * The copy constructor and  assignment operator.
     * They allow us to pass around B-Trees by value.
     * Although these operations are likely to be expensive
     * they make for an interesting programming exercise.
     * Implement these operations using value semantics and
     * make sure they do not leak memory.
     */
    
    /**
     * Copy constructor
     * Creates a new B-Tree as a copy of original.
     *
     * @param original a const lvalue reference to a B-Tree object
     */
    btree(const btree<T>& original) :
    Rootnode(nullptr),Headnode(nullptr),Tailnode(nullptr),max_nodes_limit(original.max_nodes_limit) {
        if(original.Rootnode != nullptr){
        std::queue<TreeNode*> Q;
        Q.push(original.Rootnode);
        while(!Q.empty()){
            TreeNode* current = Q.front();
            Q.pop();
            for(size_t i = 0; i != current->current_size; i++){
                insert(current->element[i]);
            }if(current->current_size == max_nodes_limit){
                for(size_t j = 0; j != current->current_size + 1; j++){
                    if(current->children[j] != nullptr){
                        Q.push(current->children[j]);
                    }
                }
            }
        }
        }
        
    }
    
    /**
     * Move constructor
     * Creates a new B-Tree by "stealing" from original.
     *
     * @param original an rvalue reference to a B-Tree object
     */
    btree(btree<T>&& original):
    Rootnode{std::move(original.Rootnode)},
    Headnode{std::move(original.Headnode)},
    Tailnode{std::move(original.Tailnode)},
    max_nodes_limit{std::move(original.max_nodes_limit)}
    {
        original.Rootnode = nullptr;
        original.Headnode = nullptr;
        original.Tailnode = nullptr;
    }
    
    
    /**
     * Copy assignment
     * Replaces the contents of this object with a copy of rhs.
     *
     * @param rhs a const lvalue reference to a B-Tree object
     */
    btree<T>& operator=(const btree<T>& rhs){
        if(rhs.Rootnode != nullptr){
        if(this != &rhs){
            delete Rootnode;
            Rootnode = nullptr;
            Headnode = nullptr;
            Tailnode = nullptr;
            max_nodes_limit = rhs.max_nodes_limit;
            std::queue<TreeNode*> Q;
            Q.push(rhs.Rootnode);
            while(!Q.empty()){
                TreeNode* current = Q.front();
                Q.pop();
                for(size_t i = 0; i != current->current_size; i++){
                    insert(current->element[i]);
                }if(current->current_size == max_nodes_limit){
                    for(size_t j = 0; j != current->current_size + 1; j++){
                        if(current->children[j] != nullptr){
                            Q.push(current->children[j]);
                        }
                    }
                }
            }
        }
        }
        return *this;
    }
    
    /**
     * Move assignment
     * Replaces the contents of this object with the "stolen"
     * contents of original.
     *
     * @param rhs a const reference to a B-Tree object
     */
    btree<T>& operator=(btree<T>&& rhs){
        if(this != &rhs){
            delete Rootnode;
            Rootnode = nullptr;
            Headnode = nullptr;
            Tailnode = nullptr;
            max_nodes_limit = rhs.max_nodes_limit;
            Rootnode = std::move(rhs.Rootnode);
            Headnode = std::move(rhs.Headnode);
            Tailnode = std::move(rhs.Tailnode);
            rhs.Rootnode = nullptr;
            rhs.Headnode = nullptr;
            rhs.Tailnode = nullptr;
        }
        return *this;
        
    }
    
    /**
     * Puts a breadth-first traversal of the B-Tree onto the output
     * stream os. Elements must, in turn, support the output operator.
     * Elements are separated by space. Should not output any newlines.
     *
     * @param os a reference to a C++ output stream
     * @param tree a const reference to a B-Tree object
     * @return a reference to os
     */
    
    friend std::ostream& operator<< <T>  (std::ostream& os, const btree<T>& tree);
    
    
    /**
     * The following can go here
     * -- begin()
     * -- end()
     * -- rbegin()
     * -- rend()
     * -- cbegin()
     * -- cend()
     * -- crbegin()
     * -- crend()
     */
    iterator begin()  const{
        return iterator(Headnode,0,this);
    }
    iterator end()  const{
        return iterator(NULL,0,this);
    }
    reverse_iterator rbegin() const{
        return reverse_iterator(end());
    }
    reverse_iterator rend() const{
        return reverse_iterator(begin());
    }
    const_iterator cbegin()  const{
        return const_iterator(begin());
    }
    const_iterator cend()  const{
        return const_iterator(end());
    }
    const_reverse_iterator crbegin() const{
        return const_reverse_iterator(end());
    }
    const_reverse_iterator crend() const{
        return const_reverse_iterator(begin());
    }
    
    /**
     * Returns an iterator to the matching element, or whatever
     * the non-const end() returns if the element could
     * not be found.
     *
     * @param elem the client element we are trying to match.  The elem,
     *        if an instance of a true class, relies on the operator< and
     *        and operator== methods to compare elem to elements already
     *        in the btree.  You must ensure that your class implements
     *        these things, else code making use of btree<T>::find will
     *        not compile.
     * @return an iterator to the matching element, or whatever the
     *         non-const end() returns if no such match was ever found.
     */
    iterator find(const T& elem){
        TreeNode* current_node;
        std::queue<std::pair<TreeNode*, size_t>> Q;
        Q.push(std::make_pair(Rootnode,0));
        while(!Q.empty()){
            std::pair<TreeNode*, size_t> temp = Q.front();
            Q.pop();
            current_node = temp.first;
            size_t position;
            for(position = temp.second; position != current_node->current_size; position++){
                if(current_node->element[position] == elem){
                    return iterator(current_node,position,this);
                }
                if(current_node->element[position] > elem){
                    if(current_node->children == nullptr){
                        return end();
                    }else{
                        if(current_node->children[position] == nullptr){
                            return end();
                        }
                        Q.push(std::make_pair(current_node->children[position],0));
                        break;
                    }
                }
            }
            if(position == current_node->current_size ){
                
                if(current_node->children[position] != nullptr){
                    Q.push(std::make_pair(current_node->children[position],0));
                }else{
                    return end();
                }
            }
        }
        return end();
    }
    
    /**
     * Identical in functionality to the non-const version of find,
     * save the fact that what's pointed to by the returned iterator
     * is deemed as const and immutable.
     *
     * @param elem the client element we are trying to match.
     * @return an iterator to the matching element, or whatever the
     *         const end() returns if no such match was ever found.
     */
    const_iterator find(const T& elem) const{
        TreeNode* current_node;
        std::queue<std::pair<TreeNode*, size_t>> Q;
        Q.push(std::make_pair(Rootnode,0));
        while(!Q.empty()){
            std::pair<TreeNode*, size_t> temp = Q.front();
            Q.pop();
            current_node = temp.first;
            size_t position;
            for(position = temp.second; position != current_node->current_size; position++){
                if(current_node->element[position] == elem){
                    return iterator(current_node,position,this);
                }
                if(current_node->element[position] > elem){
                    if(current_node->children == nullptr){
                        return cend();
                    }else{
                        if(current_node->children[position] == nullptr){
                            return cend();
                        }
                        Q.push(std::make_pair(current_node->children[position],0));
                        break;
                    }
                }
            }
            if(position == current_node->current_size){
                if(current_node->children[position] != nullptr){
                    Q.push(std::make_pair(current_node->children[position],0));
                }else{
                    return cend();
                }
            }
        }
        return cend();
    }
    /**
     * Operation which inserts the specified element
     * into the btree if a matching element isn't already
     * present.  In the event where the element truly needs
     * to be inserted, the size of the btree is effectively
     * increases by one, and the pair that gets returned contains
     * an iterator to the inserted element and true in its first and
     * second fields.
     *
     * If a matching element already exists in the btree, nothing
     * is added at all, and the size of the btree stays the same.  The
     * returned pair still returns an iterator to the matching element, but
     * the second field of the returned pair will store false.  This
     * second value can be checked to after an insertion to decide whether
     * or not the btree got bigger.
     *
     * The insert method makes use of T's copy constructor,
     * and if these things aren't available,
     * then the call to btree<T>::insert will not compile.  The implementation
     * also makes use of the class's operator== and operator< as well.
     *
     * @param elem the element to be inserted.
     * @return a pair whose first field is an iterator positioned at
     *         the matching element in the btree, and whose second field
     *         stores true if and only if the element needed to be added
     *         because no matching element was there prior to the insert call.
     */
    std::pair<iterator, bool> insert(const T& elem){
        bool if_update_head = false;
        bool if_update_tail = false;
        TreeNode** current_node = &Rootnode;
        TreeNode* parent_node = nullptr;
        TreeNode* temp = *current_node;
        std::queue<TreeNode*> Q;
        Q.push(temp);
        while(!Q.empty()){
            temp = Q.front();
            Q.pop();
            if(temp == nullptr){
                *current_node = new TreeNode(elem,parent_node,max_nodes_limit);
                if(*current_node == Rootnode){
                    std::cout<<elem<<std::endl;
                    Headnode = *current_node;
                    Tailnode = *current_node;
                }else if(if_update_head == true){
                    Headnode = *current_node;
                    if_update_head = false;
                }else if(if_update_tail == true){
                    Tailnode = *current_node;
                    if_update_tail = false;
                }
                return std::make_pair(iterator(*current_node,0,this),true);
            }
            else{
                size_t position;
                for(position = 0; position != temp->current_size; position++){
                    if(temp->element[position] == elem){
                        return std::make_pair(iterator(temp,position,this),false);
                    }
                    else if(temp->element[position] > elem){
                        if(temp->current_size != max_nodes_limit){
                            for(size_t i = temp->current_size; i > position; --i){
                                temp->element[i] = temp->element[i-1];
                            }
                            temp->element[position] = elem;
                            break;
                        }else{
                            current_node = &(temp->children[position]);
                            break;
                        }
                    }
                }
                if(temp->current_size !=max_nodes_limit){
                    if(temp->current_size == position){
                        temp->element[position] = elem;
                    }
                    ++temp->current_size;
                    return std::make_pair(iterator(temp,position,this),true);
                }else{
                    parent_node = temp;
                    if(position == 0&& temp == Headnode){
                        if_update_head = true;
                    }else if(position == max_nodes_limit){
                        current_node = &(temp->children[position]);
                        if(temp == Tailnode){
                            if_update_tail = true;
                        }
                    }
                    Q.push(*current_node);
                }
            }
        }
        return std::make_pair(iterator(NULL,0,this),true);
    }
    
    /**
     * Disposes of all internal resources, which includes
     * the disposal of any client objects previously
     * inserted using the insert operation.
     * Check that your implementation does not leak memory!
     */
    ~btree(){
        if(Rootnode != nullptr){
            delete Rootnode;
        }
        Headnode = nullptr;
        Tailnode = nullptr;
    }
    
private:
    // The details of your implementation go here
    struct TreeNode{
        TreeNode(const T& elem, TreeNode *parent, size_t max_nodes) :
        max_nodes_num(max_nodes),
        element(new T[max_nodes] ),
        parent_node(parent),
        children(new TreeNode*[max_nodes + 1]()),
        current_size(1)
        {   element[0] = elem;
        };
        TreeNode(TreeNode *parent, size_t max_nodes = 40) :
        max_nodes_num(max_nodes),
        element(new T[max_nodes] ),
        parent_node(parent),
        children(new TreeNode*[max_nodes + 1]()),
        current_size(0){};
        TreeNode& operator= (const TreeNode& copy){
            if(this != copy){
                delete this;
                max_nodes_num = copy.max_nodes_num;
                element = new T[max_nodes_num];
                parent_node = copy.parent_node;
                for(auto i = 0; i != max_nodes_num;i++){
                    TreeNode temp(*copy.children[i]);
                    children[i] = &temp;
                }
            }return *this;
        };
        
        ~TreeNode(){
            for(size_t i = 0; i != max_nodes_num + 1; i++){
                if(children[i] != nullptr){
                    delete children[i];
                }
            }
            delete[] element;
            delete[] children;
            max_nodes_num = 0;
            parent_node = nullptr;
            current_size = 0;
            
        };
        size_t max_nodes_num;
        T *element;
        TreeNode *parent_node;
        TreeNode **children;
        size_t current_size;
        
    };
    TreeNode *Rootnode;
    TreeNode *Headnode;
    TreeNode *Tailnode;
    size_t max_nodes_limit;
};
template <typename T> std::ostream& operator<< (std::ostream& os, const btree<T>& tree) {
    if(tree.Rootnode != nullptr){
        std::queue<typename btree<T>::TreeNode*> Q;
        Q.push(tree.Rootnode);
        typename btree<T>::TreeNode* current_node;
        while(!Q.empty()){
            current_node = Q.front();
            Q.pop();
            size_t i;
            for(i = 0 ; i != current_node->current_size; i++){
                if( i > 0){
                    os<<" ";
                } if(current_node->current_size == 1 && tree.Rootnode != current_node){
                    os<<" ";
                }
                os << current_node->element[i];
                if(current_node->children[i] != nullptr){
                    Q.push(current_node->children[i]);
                }
            }
            if(current_node->children[current_node->current_size] != nullptr){
                Q.push(current_node->children[current_node->current_size]);
            }
        }
    }
    return os;
}

#endif


