#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
        // compute height of an AVL subtree
        int getHeight(AVLNode<Key,Value>* node) const;

        // rotations
        void rotateL(AVLNode<Key,Value>* node);
        void rotateR(AVLNode<Key,Value>* node);

        // rebalance going up from a given node to root
        void balance(AVLNode<Key,Value>* node);


};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // TODO -> DONE
    // base case: empty tree - new root
    if(this->root_ == NULL) {
        AVLNode<Key,Value>* newRoot = new AVLNode<Key,Value>(new_item.first, new_item.second, NULL);
        this->root_ = newRoot;
        return;
    }

    // standard BST insert with AVLNode
    Node<Key,Value>* curr = this->root_;
    Node<Key,Value>* parent = NULL;

    while(curr != NULL) {
        parent = curr;
        // key already exists - overwrite value (no structural change)
        if(new_item.first == curr->getKey()) {
            curr->setValue(new_item.second);
            return;
        }
        // new key is smaller - go left
        else if(new_item.first < curr->getKey()) {
            curr = curr->getLeft();
        }
        // new key is larger - go right
        else {
            curr = curr->getRight();
        }
    }

    // convert parent to AVLNode
    AVLNode<Key,Value>* avlP = static_cast<AVLNode<Key,Value>*>(parent);
    // create new AVLNode
    AVLNode<Key,Value>* newN = new AVLNode<Key,Value>(new_item.first, new_item.second, avlP);

    // insert new node as left or right child
    if(new_item.first < parent->getKey()) {
        parent->setLeft(newN);
    }
    else {
        parent->setRight(newN);
    }

    // rebalance from parent to root
    balance(avlP);
}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    // TODO -> DONE
    // standard BST remove
    Node<Key, Value>* rNode = this->internalFind(key);

    // convert to AVLNode
    AVLNode<Key,Value>* avlR = static_cast<AVLNode<Key,Value>*>(rNode);

    //base case: key not found, no removal
    if (rNode == NULL) {return;}

    // case 1: node has 2 children
    if(rNode->getLeft() != NULL && rNode->getRight() != NULL) {
        // find predecessor
        AVLNode<Key,Value>* pred = static_cast<AVLNode<Key,Value>*>(BinarySearchTree<Key,Value>::predecessor(rNode));
        // swap nodes
        nodeSwap(avlR, pred);
    }

    // case 2: 0 or 1 child 
    // create avl parent and child pointers
    AVLNode<Key,Value>* parent =
        static_cast<AVLNode<Key,Value>*>(rNode->getParent());
    
    AVLNode<Key,Value>* child = NULL;
        if(rNode->getLeft() != NULL) {
            child = static_cast<AVLNode<Key,Value>*>(rNode->getLeft());
        }
        else {
            child = static_cast<AVLNode<Key,Value>*>(rNode->getRight());
        }

    // if child exists - update parent 
    if(child != NULL) {
        child->setParent(parent);
    }

    // reconnect parent to child
    if(parent == NULL) {
        this->root_ = child;
    }
    else {
        // determine if left or right child is removed
        if(parent->getLeft() == rNode) {
            parent->setLeft(child);
        }
        else {
            parent->setRight(child);
        }
    }

    delete rNode;

    // AVL remove
    // rebalance from parent of removed node and up
    if(parent != NULL) {
        balance(parent);
    }

}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}

// helper functions:
// helper - height of an AVL subtree 
template<class Key, class Value>
int AVLTree<Key, Value>::getHeight(AVLNode<Key,Value>* curr) const
{
    // base case
    if(curr == NULL) return 0;

    // recursively get height
    int leftH = getHeight(curr->getLeft());
    int rightH = getHeight(curr->getRight());
    return std::max(leftH, rightH) + 1;
}

// helper - single left rotation
    // before rotation:
        //     x 
        //       y 
        //         z
    // after rotation:
        //     y
        //  x     z
template<class Key, class Value>
void AVLTree<Key, Value>::rotateL(AVLNode<Key,Value>* x) {
    
    // y = x's right child of x — take x's place after rotation
    AVLNode<Key,Value>* y = x->getRight();

    // move y up to x’s parent
    y->setParent(x->getParent());   // y now takes x's parent

    // if x was the root - y = new root
    if(x->getParent() == NULL) {
        this->root_ = y;
    }
    // update x's parent to point to y instead of x
    else if(x->getParent()->getLeft() == x) {
        x->getParent()->setLeft(y);
    }
    else {
        x->getParent()->setRight(y);
    }

    // move x to become y's left child
    x->setParent(y);

    // y's previous left subtree becomes x's right subtree
    x->setRight(y->getLeft());

    // if subtree exists, update parent 
    if(x->getRight() != NULL) {
        x->getRight()->setParent(x);
    }

    // finish rotation by making x left child of y
    y->setLeft(x);
}

// helper - single right rotation
    // before rotation:
        //     z 
        //   y 
        //  x
    // after rotation:
        //      y
        //  x      z
template<class Key, class Value>
void AVLTree<Key, Value>::rotateR(AVLNode<Key,Value>* z) {
    // MOVE Y UP
    // y = left child of z —  will take z's place after rotation
    AVLNode<Key,Value>* y = z->getLeft();

    // move y up to become z’s parent  
    y->setParent(z->getParent());   

    // if z was the root, y becomes the new root
    if(z->getParent() == NULL) {
        this->root_ = y;
    }
    // update z's parent to point to y instead of z
    else if(z->getParent()->getLeft() == z) {
        z->getParent()->setLeft(y);
    }
    else {
        z->getParent()->setRight(y);
    }

    // MOVE Z DOWN
    z->setParent(y);

    // y's previous right subtree becomes z's left subtree
    z->setLeft(y->getRight());

    // if subtree exists - update parent 
    if(z->getLeft() != NULL) {
        z->getLeft()->setParent(z);
    }

    // make z the right child of y
    y->setRight(z);

    // update balances using subtree heights
        // balance = height(left subtree) - height(right subtree)
    z->setBalance( getHeight(z->getLeft()) - getHeight(z->getRight()) );
    y->setBalance( getHeight(y->getLeft()) - getHeight(y->getRight()) );

}

// helper - balance starting from a given node and moving up toward the root.
    // recompute each node's balance from subtree heights 
    // perform single or double rotations.
template<class Key, class Value>
void AVLTree<Key, Value>::balance(AVLNode<Key,Value>* curr)
{
    while(curr != NULL) {
        int bFact = getHeight(curr->getLeft()) - getHeight(curr->getRight());
        curr->setBalance(bFact);

        // left-heavy
        if(bFact == 2) {
            AVLNode<Key,Value>* L = curr->getLeft();
            int factL = getHeight(L->getLeft()) - getHeight(L->getRight());

            // case 1: left-right
            if(factL < 0) {
                rotateL(L);
            }
            // case 2: left-left = right
            rotateR(curr);
        }
        // right-heavy
        else if(bFact == -2) {
            AVLNode<Key,Value>* R = curr->getRight();
            int factR = getHeight(R->getLeft()) - getHeight(R->getRight());

            // case 3: right-left 
            if(factR > 0) {
                rotateR(R);
            }
            // case 4: right-right = left
            rotateL(curr);
        }

        curr = curr->getParent();
    }
}

#endif
