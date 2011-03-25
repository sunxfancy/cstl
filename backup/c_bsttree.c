#include <stdlib.h>
#include "c_priv_bsttree.h"
int traverseInorder(BSTtreeNode *root, f_printKey printKey)
{
  if(root->left)
    traverseInorder(root->left, printKey);
  if(!root->removed)
  printKey(root->key);
  if(root->right)
    traverseInorder(root->right, printKey);
  return(0);
}
int BSTInorder(BSTtree *tree)
{
  return(traverseInorder(tree->root, tree->printKey)); 
}

int genericComp(void *one, void *two)
{
  if(one > two)
    return 0;
  if(one< two)
    return 1;
  return 2;
}

BSTtreeNode *BSTtreeFind(BSTtree *tree, void *key)
{
  BSTtreeNode *curr=tree->root;
  int compRv;
  while(curr)
  {
    compRv = tree->comparator(curr->key, key);
    switch(compRv)
    {
      case 0:
        curr=curr->left;
        break;
      case 1:
        curr=curr->right;
        break;
      case 2:
        return curr;
    }
  }
  return NULL;
}

BSTtree *NewBSTtree(f_comparator f_comp, f_deleteKey f_delK, f_deleteData f_delD, f_printKey f_printK, f_printData f_printD)
{
  BSTtree *tree = malloc(sizeof(BSTtree));
  if(!tree)
    goto exit;
  tree->root = NULL;
  if(f_comp == NULL)
    tree->comparator = genericComp;
  else
    tree->comparator = f_comp;
  tree->deleteKey = f_delK;
  tree->deleteData = f_delD;
  tree->printKey = f_printK;
  tree->printData = f_printD;
  
exit:
  return (tree);
}

BSTtreeNode * getNewBSTtreeNode(void *ikey, void *idata)
{
  BSTtreeNode *node = malloc(sizeof(BSTtreeNode));
  if(!node)
    goto exit;
  node->left = NULL;
  node->right = NULL;
  node->parent = NULL;
  node->key = ikey;
  node->data = idata; 
  node->removed = 0;
exit:
  return node;
}

int BSTInsert(BSTtree *tree, BSTtreeNode *newNode, f_comparator comparator)
{
  BSTtreeNode *curr = tree->root;
  int compVal = -1;
  //RBtreeNode *prev = NULL;
  if(!curr)
  {
    tree->root = newNode;
    return (0);
  }
  while(curr)
  {
    compVal = comparator(curr->key, newNode->key);  //returns 0 if curr->key is greater, 1 if newNode->key is greater, 2 if both are equal;
    switch(compVal)
    {
      case 0: 
        if(!curr->left)
        {
          curr->left = newNode;
          newNode->parent = curr;
          return(0);
        }
        else
          curr = curr->left;
        break;
      case 1:
        if(!curr->right)
        {
          curr->right = newNode;
          newNode->parent = curr;
          return(0);
        }
        else
          curr = curr->right;
        break;
      case 2:
        return(1); //equal
    }
  } 
  return(1);
}

int isLeftChild(BSTtreeNode *node)
{
  if(node->parent)
    if(node->parent->left == node)
      return 1;
  return 0;
}

int BSTtreeInsert(BSTtree *tree, void *key, void *data)
{
  BSTtreeNode *newNode = getNewBSTtreeNode(key, data);
  BSTtreeNode *curr = newNode;
  if(!newNode)
    return 1;
  if(BSTInsert(tree, newNode, tree->comparator))
    return 1;
  return (0);
}

BSTtreeNode *findLeftMostNode(BSTtreeNode *node)
{
  BSTtreeNode *tmp = node;
  while(tmp->left)
  {
    tmp=tmp->left;
  }
  return tmp;
}

BSTtreeNode *findRightMostNode(BSTtreeNode *node)
{
  BSTtreeNode *tmp = node;
  while(tmp->right)
  {
    tmp=tmp->right;
  }
  return tmp;
}
int BSTtreeRemove(BSTtree *tree, void *key)
{
  BSTtreeNode *node, *tmp, *tmp2, *tmp3;
  node = BSTtreeFind(tree, key);
  if(!node->right && !node->left)
  {
    if(node == tree->root)
      tree->root = NULL;
    free(node);
    return(0);
  }
  if(node->right && !node->left)
  {
    if(node == tree->root)
    {
      node->right->parent = NULL;
      tree->root=node->right;
      free(node);
      return(0);
    }
    if(isLeftChild(node))
    {
      node->parent->left = node->right;
      node->right->parent = node->parent;
      free(node);  
      return(0);
    }
    else
    {
      node->parent->right = node->right;
      node->right->parent = node->parent;
      free(node);
      return(0);
    }
  } 
  if(node->left && !node->right)
  {
    if(node == tree->root)
    {
      node->left->parent = NULL;
      tree->root=node->left;
      free(node);
      return(0);
    }
    if(isLeftChild(node))
    {
      node->parent->left = node->left;
      node->left->parent = node->parent;
      free(node); 
      return(0);
    }
    else
    {
      node->parent->right = node->left;
      node->left->parent = node->parent;
      free(node);
      return(0);
    }
  } // node the slightly complex case
  if(!node || node->removed)
    return 1;
  node->removed = 1;  //:( :( :(
  return (0);
}

BSTtreeNode *getGrandpa(BSTtreeNode *node)
{
  if(node->parent)
    return(node->parent->parent);
}

BSTtreeNode *getUncle(BSTtreeNode *node)
{
  if(node->parent)
  {
    if(node->parent->parent)
    {
      if(node->parent->parent->left == node->parent)
        return node->parent->parent->right;
      else
        return node->parent->parent->left;
    }
  }  
}

BSTtreeNode *getParent(BSTtreeNode *node)
{
  return(node->parent); 
}

