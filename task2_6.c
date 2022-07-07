#include <stdio.h>
#include <stdlib.h>

typedef unsigned elemtype;
typedef struct Node *link;        /*указатель на дин. структуру*/
typedef struct Node               /*структура node из двух полей*/
               {
                 elemtype elem;   /*указатель на слово*/
                 link left;       /*ссылка на левое поддерево*/
                 link right;      /*ссылка на правое поддерево*/
               } node;
typedef link tree;                /*список элементов задается указателем на звено*/

/*===================================*/
/*--------Удаляем все дерево---------*/
/*===================================*/
void DelAll(tree t)
{
  if (t==NULL)
    return;
  DelAll(t->left);
  DelAll(t->right);
  free(t);
}

/*===================================*/
/*------Добавляет 1 новый узел-------*/
/*===================================*/
void AddNode(tree *p, elemtype a)
  {
    if (*p==NULL)                 /*если пусто, просто создаем элемент*/
      {
        *p=malloc(sizeof(node));
        (*p)->elem=a;
        (*p)->left=NULL;
        (*p)->right=NULL;
      }
    if (a>(*p)->elem)             /*перемещение по узлам дерева (бинарного)*/
      AddNode(&(*p)->right, a);
    if (a<(*p)->elem)
      AddNode(&(*p)->left, a);
  }

/*===================================*/
/*-------Поиск узла с меткой а-------*/
/*===================================*/
int FindNode(tree p, elemtype a)     /*1 - элемент есть, 0 - элемента нет*/
  {
    if (p==NULL)
      return 0;
    if (p->elem == a)
      return 1;
    if (a>p->elem)                   /*если элемент больше, поиск в правом поддереве*/
      return FindNode(p->right, a);
    else                             /*иначе поиск в левом поддереве*/
      return FindNode(p->left, a);
  }

/*===================================*/
/*----------Печать дерева------------*/
/*===================================*/
void PrintTree(tree p)
  {
    if (p==NULL)
      return ;
    PrintTree(p->left);
    printf("%u ", p->elem);
    PrintTree(p->right);
  }

/*====================================*/
/*----Поиск максимального элемента----*/
/*====================================*/
int MaxNode(tree t)                                       /*передаем значение элемента*/
  {
    int res=t->elem;
    int m;
    /*if (t->left != NULL && (m=MaxNode(t->left)) > res)*/    /*максимум в левом поддереве*/
      /*res=m;*/
    if (t->right != NULL && (m=MaxNode(t->right)) > res)  /*максимум в правом поддереве*/
      res=m;
    return res;
  }

/*===================================*/
/*---------Удаление 1 узла-----------*/
/*===================================*/
void DelNode(tree *p, elemtype a)
  {
    tree q;                                         /*для удаления элементов*/
    int m;                                          /*максимум*/
    if (*p==NULL)
      return ;
    if ((*p)->elem==a)
      {
        if ((*p)->left==NULL && (*p)->right==NULL)  /*если лист, удаляем элемент*/
          {
            q=*p;
            *p=NULL;
            free(q);
            return ;
          }
        else if ((*p)->left==NULL)                  /*если только правое поддерево, удаляем со связью*/
          {
            q=*p;
            *p=q->right;
            free(q);
            return ;
          }
        else if ((*p)->right==NULL)                 /*если только левое поддерево, удаляем со связью*/
          {
            q=*p;
            *p=q->left;
            free(q);
            return ;
          }
        else                                        /*полноценный узел, т.е. со всеми связями*/
          {
            (*p)->elem=m=MaxNode((*p)->left);       /*меняем его значение на максимум из левого поддерева*/
            DelNode(&(*p)->left, m);                /*удаляем этот максимальный элемент из левого поддерева*/
            return ;
          }
      }
    if (a>(*p)->elem)                               /*перемещение по узлам лерева*/
      DelNode(&(*p)->right, a);
    if (a<(*p)->elem)
      DelNode(&(*p)->left, a);
  }

/*===================================*/
/*--------------Main-----------------*/
/*===================================*/
int main()
{
  unsigned a;                            /*неотр. целое число*/
  char zn;                               /*знак +, - или ?*/
  tree BinTree=NULL;
  while (scanf("%c", &zn)==1)
    {
      if (zn!='+' && zn!='-' && zn!='?')
        continue ;
      scanf("%u", &a);
      /*printf("el=%c", zn);
      printf("%d\n", a);*/
      if (zn == '+')
        AddNode(&BinTree, a);
      else if (zn == '?')
        {
          printf("%u ", a);
          if (FindNode(BinTree, a))
            printf("yes\n");
          else
            printf("no\n");
        }
      else
        DelNode(&BinTree, a);
      /*printf("TreeSym=");
      PrintTree(BinTree);
      printf("\n");*/
    }
  DelAll(BinTree);
}
