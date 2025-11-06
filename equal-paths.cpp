#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)

#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here
   // helper function to find the depth of the first leaf int
    int findDepth(Node* node) {
        // base case: empty tree (root == NULL)
        if (node == nullptr) { return 0;}

        // if it's a leaf node, return depth
        if (node->left == nullptr && node->right == nullptr) { return 1;}

        // // recursive step: recursively find the depth of left and right subtrees
        int L = findDepth(node->left);
        int R = findDepth(node->right);

        // return the larger depth + 1
        if (L > R) {
            return L + 1;
        }
        else {
            return R + 1;
        }
    }
   


bool equalPaths(Node * root)
{
    // Add your code below
    // case 1: empty tree has equal paths
    if (root == nullptr) {
        return true;  
    }

    // recursively check children subtrees must ALSO have equal paths
    if (!equalPaths(root->left)){  return false;}
    if (!equalPaths(root->right)){ return false;}


    int leftDepth  = findDepth(root->left);
    int rightDepth = findDepth(root->right);

    // if only 1 subtree exists, still true (only one path)
    if (root->left == nullptr || root->right == nullptr) {
        return true;
    }

    // both exist (equal depth)
    return leftDepth == rightDepth;
}
