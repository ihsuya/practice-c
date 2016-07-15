#include "splay_tree.h"

/**
 * This is a top-down implementation of a splay tree.
 */
spltree_node* insert(spltree_node* root, int value) {
  spltree_node* new_node = malloc(sizeof(spltree_node));
  assert(new_node);

  new_node->value = value;

  if (root == NULL) {
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
  }

  root = splay(root, value);

  if (value < root->value) {
    new_node->left = root->left;
    new_node->right = root;
    root->left = NULL;

    return new_node;
  } else if (value > root->value) {
    new_node->left = root;
    new_node->right = root->right;
    root->right = NULL;

    return new_node;
  }

  // new node was already root
  free(new_node);

  return root;
}

spltree_node* splay(spltree_node* x, int value) {
  spltree_node temp, *l, *r, *y;

  if (x == NULL) return x; // is this line needed?

  temp.left = temp.right = NULL;
  l = r = &temp;

  for (;;) {
    if (value < x->value) {
      if (x->left == NULL) break;
      if (value < x->left->value) {  // rotate right
        y = x->left;
        x->left = y->right;
        y->right = x;
        x = y;
        if (x->left == NULL) break;
      }
      r->left = x;              // link right
      r = x;
      x = x->left;
    } else if (value > x->value) {
      if (x->right == NULL) break;
      if (value > x->right->value) {
        y = x->right;           // rotate left
        x->right = y->left;
        y->left = x;
        x = y;
        if (x->right == NULL) break;
      }
      l->right = x;             // link left
      l = x;
      x = x->right;
    } else {
      break;
    }
  }

  l->right = x->left;
  r->left = x->right;
  x->left = temp.right;
  x->right = temp.left;

  return x;
}