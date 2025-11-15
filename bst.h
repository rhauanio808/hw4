#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed by the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); //TODO -> DONE
    virtual ~BinarySearchTree(); //TODO -> DONE
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO -> DONE
    virtual void remove(const Key& key); //TODO -> DONE
    void clear(); //TODO -> DONE
    bool isBalanced() const; //TODO -> DONE
    void print() const;
    bool empty() const;

    template<typename PPKey, typename PPValue>
    friend void prettyPrintBST(BinarySearchTree<PPKey, PPValue> & tree);
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator  // TODO -> DONE
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value> *current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;
    Value& operator[](const Key& key);
    Value const & operator[](const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const; // TODO
    Node<Key, Value> *getSmallestNode() const;  // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.

    // Provided helper functions
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2) ;

    // Add helper functions here
    // added static successor function
    static Node<Key, Value>* successor(Node<Key, Value>* current); 
    
    // helper functions for isBalanced
    int getHeight(Node<Key, Value>* node) const;
    
    // recursive helper for isBalanced
    bool balanceHelper(Node<Key, Value>* node) const;

    // recursive helper for clear
    void clearSubtree(Node<Key, Value>* node);


protected:
    Node<Key, Value>* root_;
    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr)
     : current_(ptr) // initialize iterator to given pointer
{
    // TODO -> DONE
}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() 
    : current_(NULL) // initialize iterator to NULL
{
    // TODO -> DONE
}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO -> DONE
    return this->current_ == rhs.current_; // true if both point to same node, else false
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO -> DONE
    return this->current_ != rhs.current_; // true if both point to different nodes, else false
}


/**
* Advances the iterator's location using an in-order sequencing
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
    // TODO -> DONE
        // use successor function to get next node using in-order traversal
        // this->current_ now points to successor node
        this->current_ = BinarySearchTree<Key, Value>::successor(this->current_);
        return *this; // return updated iterator
}


/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree() 
    : root_(NULL) // initialize root to NULL
{
    // TODO -> DONE
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    // TODO -> DONE
    clear(); // delete nodes to clear tree and free memory
}

/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
 * @precondition The key exists in the map
 * Returns the value associated with the key
 */
template<class Key, class Value>
Value& BinarySearchTree<Key, Value>::operator[](const Key& key)
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}
template<class Key, class Value>
Value const & BinarySearchTree<Key, Value>::operator[](const Key& key) const
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}

/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
* Recall: If key is already in the tree, you should 
* overwrite the current value with the updated value.
*/
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{
    // TODO -> DONE
        // case 1: tree is empty, insert at root
        if (root_ == NULL) {
            root_ = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, NULL);
            return;
        }

        // case 2: tree is not empty, find correct position to insert
        Node<Key, Value>* curr = root_;
        Node<Key, Value>* parent = NULL;

        // traverse tree to find insertion point
        while (curr != NULL) {
            parent = curr;
            // key exists, overwrite value
            if (keyValuePair.first == curr->getKey()){
                curr->setValue(keyValuePair.second);
                return;
            }
            // go left if key is less than current node
            else if (keyValuePair.first < curr->getKey()) {
                curr = curr->getLeft();
            }
            // go right if key is greater than current node
            else {
                curr = curr->getRight();
            }
        }

        // insert new node as child of parent
        Node<Key, Value>* newNode = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, parent);
        // insert as left child
        if (keyValuePair.first < parent->getKey()) {
            parent->setLeft(newNode);
        }
        // insert as right child
        else {
            parent->setRight(newNode);
        }
}


/**
* A remove method to remove a specific key from a Binary Search Tree.
* Recall: The writeup specifies that if a node has 2 children you
* should swap with the predecessor and then remove.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
    // TODO -> DONE
        // find the node to remove with specific key
        Node<Key, Value>* rNode = internalFind(key);
    
        //base case: key not found - no removal
        if (rNode == NULL) {return;}  

        // case 1: node has 2 children
        if (rNode->getLeft() != NULL && rNode->getRight() != NULL) {
            // find predecessor (right most node in left subtree) and swap nodes 
            Node<Key, Value>* pred = predecessor(rNode);
            this->nodeSwap(rNode, pred); 
        }

        // case 2: 0 or 1 child 
        Node<Key, Value>* child = NULL;

        // check if left child exists
        if (rNode->getLeft() != NULL) {child = rNode->getLeft();}

        // check if right child exists
        else if (rNode->getRight() != NULL) {child = rNode->getRight();}

        Node<Key, Value>* parent = rNode->getParent();

        // if target is not the root - fix child pointer
        if (parent != NULL)
        {
            if (parent->getLeft() == rNode)
                parent->setLeft(child);
            else
                parent->setRight(child);
        }
        else
        {
            // remove root node
            root_ = child;
        }

        // if child exists - fix parent pointer
        if (child != NULL)
            child->setParent(parent);

        delete rNode; // remove node
}



template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* curr)
{
    // TODO -> DONE
        // base case: if current is NULL, return NULL
        if (curr == NULL) { return nullptr; }

        // case 1: if left child exists, go down left once, then all the way right
        if (curr->getLeft() != NULL) {
            Node<Key, Value>* temp = curr->getLeft();
            while (temp->getRight() != NULL) {
                temp = temp->getRight();
            }
            return temp;
        }
        // case 2: no left child, go up until we find a parent that is a right child
        Node<Key, Value>* parent = curr->getParent();
        while (parent != NULL && curr == parent->getLeft()) {
            curr = parent;
            parent = parent->getParent();
        }
        return parent;
}

// added a helper function to find successor of a given node
template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::successor(Node<Key, Value>* curr)
{
    // TODO -> DONE
        // base case: if current is NULL, return NULL
        if (curr == NULL) { return nullptr; }

        // case 1: if right child exists - go down right -> then all the way left
        if (curr->getRight() != NULL) {
            Node<Key, Value>* temp = curr->getRight();
            while (temp->getLeft() != NULL) {
                temp = temp->getLeft();
            }
            return temp;
        }
        
        // case 2: no right child - go up until a left child parent is found
        Node<Key, Value>* parent = curr->getParent();
        while (parent != NULL && curr == parent->getRight()) {
            curr = parent;
            parent = parent->getParent();
        }
        return parent;

 }

/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
    // TODO -> DONE
        // tree is empty
        if (root_ == NULL) { return;}

        // use post-order traversal to delete nodes
        clearSubtree(root_);

        root_ = NULL;  // reset tree
}

// helper function to recursively clear subtree rooted at given node (post-order traversal)
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clearSubtree(Node<Key, Value>* curr) {
    // base case: empty subtree
    if (curr == NULL) { return; }
    
    // recursively clear left and right subtrees
    clearSubtree(curr->getLeft());
    clearSubtree(curr->getRight());
    
    delete curr; // delete current node
}


/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
    // TODO -> DONE: runtime O(h)
        // start at root
        Node<Key, Value>* curr = root_;
        
        // tree is empty
        if (curr == NULL) { return NULL; }

        // go down left until no more left child
        while (curr->getLeft() != NULL) {
            curr = curr->getLeft();
        }

        return curr; // return smallest (leftmost) node
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
    // TODO -> DONE: runtime O(h)
    Node<Key, Value>* curr = root_;
    // traverse tree to find key
    while (curr != NULL) {
        // key found
        if (key == curr->getKey()) {
            return curr; 
        }
        // go left if less than current key
        else if (key < curr->getKey()) {
            curr = curr->getLeft(); 
        }
        // go right if greater than current key
        else {
            curr = curr->getRight();
        }
    }
    return NULL; // key not found
}

/**
 * Return true iff the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
    // TODO -> DONE
        // base case: empty tree is balanced
        if (root_ == nullptr) { return true; }

        return balanceHelper(root_);
}

// helper function to recursively get height of subtree rooted at given node
template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::getHeight(Node<Key, Value>* node) const {
    // base case: empty subtree
    if (node == NULL) { return 0; }

    // get heights of left and right subtrees
    int leftH = getHeight(node->getLeft());
    int rightH = getHeight(node->getRight());

    // return max height of subtree
    int tallerH = 0;
    if (leftH > rightH) {
        tallerH = leftH;
    }
    else {
        tallerH = rightH;
    }

    return tallerH + 1; // add 1 for current node
}

// helper function to check if subtree rooted at given node is balanced
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::balanceHelper(Node<Key, Value>* node) const {
    
    // base case: empty subtree is balanced
    if (node == NULL) { return true; }
    
    // get heights of left and right subtrees
    int leftH = getHeight(node->getLeft());
    int rightH = getHeight(node->getRight());
    
    // compute absolute value and check height difference
    int diff = leftH - rightH;
    if (diff < 0) { diff = -diff; } // absolute value

    if (diff > 1) { return false; } 

    
    // recursively check left and right subtrees
    bool lBalance = balanceHelper(node->getLeft()); 
    bool rBalance = balanceHelper(node->getRight());

    return lBalance && rBalance;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }

}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif