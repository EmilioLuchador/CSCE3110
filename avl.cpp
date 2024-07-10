#include <stdio.h>
#include <iostream>
#include "avl.hpp"
using namespace std;

#define IS_ROOT 0
#define IS_LEFT 1
#define IS_RIGHT 2

//computing the height of node t or -1 if nullptr
int height( AvlNode * & t )
{
    return t == nullptr ? -1 : t->height;
}


/**
 * Internal method to find the largest item in a subtree t
 * Return node containing the largest item
 */ 
AvlNode * findMin( AvlNode * & k1)
{
  if( k1 == nullptr)
    return nullptr;
  if( k1->left == nullptr)
    return k1;
  return findMin( k1->left );
} 

/*
 * Rotate binary tree node with left child
 * For AVL trees, this is a single rotation for case 1.
 * Update heights, then set new root 
*/
void rotateWithLeftChild(AvlNode * & k2)
{
  AvlNode *k1 = k2->left;
  k2->left = k1->right;
  k1->right=k2;
  k2->height = max( height( k2->left ), height( k2->right ) ) + 1; 
  k1->height = max( height( k1->left ), k2-> height) + 1;
  k2=k1; 
}

void rotateWithRightChild(AvlNode * & k2)//symmetric just flip left to right
{
  AvlNode *k1 = k2->right;
  k2->right = k1->left;
  k1->left=k2;
  k2->height = max( height( k2->right ), height( k2->left ) ) + 1; 
  k1->height = max( height( k1->right ), k2->height) + 1;
  k2=k1; 
}

void doubleWithLeftChild( AvlNode * & k3 )
{
  rotateWithRightChild( k3->left );
  rotateWithLeftChild( k3 );
}

void doubleWithRightChild( AvlNode * & k3 )
{
  rotateWithLeftChild( k3->right );
  rotateWithRightChild( k3 );

}

static const int ALLOWED_IMBALANCE =1;

//Assume t is balanced or within one of being balanced
void balance( AvlNode * & root)
{
  if (root == nullptr)
    return;

  if( height(root->left) - height(root->right) > ALLOWED_IMBALANCE)
    if( height(root->left->left) >= height(root->left->right) )
      rotateWithLeftChild( root );
    else
      doubleWithLeftChild( root );

  else
  if(height( root->right ) - height( root->left ) > ALLOWED_IMBALANCE)
    if( height( root->right->right ) >= height( root->right->left ) )
      rotateWithRightChild( root );
      else 
        doubleWithRightChild( root );

  root->height = max( height( root->left), height( root->right ) ) +1;
}

/**
 * Internal method to insert into a subtree.
 * x is the item to insert.
 * t is the node that roots the subtree.
 * Set the new root of the subtree.
 */
void insert( const int & info, AvlNode * & root )
{
 // std::cout << "As of now, I am implementing a dummy insert" << endl;
 // std::cout << "Code for inserting " << info << " goes here" << endl;

// if there are no roots
  if (root == NULL) {
    root = new AvlNode (info, NULL, NULL);// root of the entire tree at the beginning
    
  } else { 
  //LL, LR, RL, RR
  if ( info < root->element )
    {
    insert( info, root->left );
    }
    // and off numbers to the right [CHANGE THIS]
  else if (root->element < info )
    {
    insert( info, root->right );
    }
  }

  balance( root );
}


/**
 * Internal method to remove from a subtree.
 * info is the item to remove.
 * root is the node that roots the subtree.
 * Set the new root of the subtree.
 */
void remove( const int & info, AvlNode * & root ) {
  //std::cout << "Code for deleting " << info << " goes here" << endl;
  if( root == nullptr )
    return; //item not found, do nothing

  if( info < root->element )
    remove( info, root->left );
  else if( root->element < info )
    remove( info, root->right );
  else if( root->left != nullptr && root->right != nullptr )//two children
  {
    root->element = findMin( root->right )->element;
    remove (root->element, root->right );
  }
  else
  {
    AvlNode *oldNode = root;
    root = ( root->left != nullptr ) ? root->left : root->right;
    delete oldNode;
  }

  balance( root ); 
}

/*
 * You will probably neesd auxiliary mathods to 
 *  - find the minimum of tree
 *  - rotate (single and double, in both directions
 *  - balance am AVL  tree
 */

/*
 * Print methods, do not change
 */
void print(AvlNode *root, int level, int type) {
  if (root == NULL) {
    return;
  }
  if (type == IS_ROOT) {
    std::cout << root -> element << "\n";
  } else {
    for (int i = 1; i < level; i++) {
      std::cout << "| ";
    }
    if (type == IS_LEFT) {
      std::cout << "|l_" << root -> element << "\n";
    } else {
      std::cout << "|r_" << root -> element << "\n";
    }
  }
  if (root -> left != NULL) {
    print(root -> left, level + 1, IS_LEFT);
  }
  if (root -> right != NULL) {
    print(root -> right, level + 1, IS_RIGHT);
  }
}
void print(AvlNode *root) {
  print(root, 0, IS_ROOT);
}
/*
 * END Print methods, do not change
 */


/* 
 * Main method, do not change
 */
int main(int argc, const char * argv[]) {
  AvlNode *root = NULL;
  std::string filename = argv[1];
  freopen(filename.c_str(), "r", stdin);
  std::string input;
  int data;
  while(std::cin >> input){
    if (input == "insert"){
      std::cin>>data;
      insert(data, root);
    } else if(input == "delete"){
      std::cin>>data;
      remove(data, root);
    } else if(input == "print"){
      print(root);
      std::cout << "\n";
    } else{
      std::cout<<"Data not consistent in file";
      break;
    }
  }
  return 0;
}
/*
 * END main method
 */
