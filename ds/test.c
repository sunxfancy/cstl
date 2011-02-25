#include <stdio.h>
#include "tree.h"

void printKey(void *in)
{
  int a = (int)in;
  printf("%d", a); 
}

int comp(void *a, void *b)
{
  int ia = (int)a; 
  int ib = (int)b;
  if(ia > ib)
    return 0;
  if(ib > ia)
    return 1;
  return 2;
}

int main()
{
  int a[] = {1,2,3,9,5,6,7,8};
  int ad[] = {10,20,30,90,50,60,70,80};
  int i;

  tree *t = newTree(comp, NULL, NULL, printKey, NULL);
  for(i = 0; i<8; i++)
  {
    
    if(Insert(t, (void *)a[i], (void *)ad[i]))
      printf("Insert failed\n");
  }
    
  Inorder(t); 
  printf("\n");
  int data = (int )Search(t, a[3]);
  if(!data)
    printf("not found\n");
  else
    printf("the data is %d", data);

  //now remove 
  Remove(t, 9);
  printf("\n");
  Inorder(t);
  printf("\n");
  Remove(t, 1);
  Inorder(t);
  printf("\n");
  Remove(t, 5);
  Inorder(t);
  return(0);
}
