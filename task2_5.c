#include <stdio.h>
#include <stdlib.h>

typedef struct Word *Wlink;  /*указатель на слово*/
typedef struct Word          /*структура слово из двух полей*/
               {
                 char buk;   /*буква*/
                 Wlink next; /*ссылка на след. элемент*/
               } word;
typedef Wlink Wlist;         /*список слов задается указателем на слово*/

typedef struct Node *link;   /*указатель на дин. структуру*/
typedef struct Node          /*структура node из двух полей*/
               {
                 Wlist elem; /*указатель на слово*/
                 link next;  /*ссылка на след. элемент*/
               } node;
typedef link list;           /*список элементов задается указателем на звено*/

/*===================================*/
/*-----------Печать слова------------*/
/*===================================*/
void PrintW(Wlist lb)
  {
    for (;lb;lb=lb->next)
      printf("%c", lb->buk);
  }

/*===================================*/
/*-----------Печать списка-----------*/
/*===================================*/
void Print(list lw)
  {
    if (lw)
      {
        PrintW(lw->elem);
        lw=lw->next;
      }
    for (;lw;lw=lw->next)
      {
        printf(" ");
        PrintW(lw->elem);
      }
    printf("\n");
  }

/*===================================*/
/*-----Создание слова из массива-----*/
/*===================================*/
void CreateWord(char *s, Wlist *lb)
  {
    Wlist p, nach;
    *lb=NULL;
    if (*s=='\0')
      return ;
    p=malloc(sizeof(word));
    nach=p;
    p->buk=*s++;
    while(*s != '\0')
      {
        p->next=malloc(sizeof(word));
        p=p->next;
        p->buk=*s++;
      }
    p->next=NULL;
    *lb=nach;
  }

/*===================================*/
/*----------Создание списка----------*/
/*===================================*/
list Create()
  {
    list p,nach=NULL;
    char str[80];
    if (scanf("%s", str)==1)
      {
        p=malloc(sizeof(node));
        nach=p;
        CreateWord(str, &(p->elem));
      }
    else
      return NULL;
    while(scanf("%s", str)==1)
      {
        /*printf("s=%s\n",str);*/
        p->next=malloc(sizeof(node));
        p=p->next;
        CreateWord(str, &(p->elem));
      }
    p->next=NULL;
    return nach;
  }

/*====================================*/
/*--Находим указатель на посл. слово--*/
/*====================================*/
Wlist LastWord(list p)
  {
    if (p)
      for (;p->next;p=p->next)
        ;
    else
      return NULL;
    return p->elem;
  }

/*====================================*/
/*-------Проверка равенства слов------*/
/*====================================*/
int RavWW(Wlist a, Wlist b)
  {
    for (;a->buk == b->buk; a=a->next, b=b->next)
      if (a->next==NULL && b->next==NULL)
        return 1;
      else if (a->next==NULL || b->next==NULL)
        return 0;
    return 0;
  }

/*====================================*/
/*--------Удаление цепочки букв-------*/
/*====================================*/
void DelB(Wlist p)
  {
    Wlink q;
    while (p != NULL)
      {
        q=p;
        p=p->next;
        free(q);
      }
    return ;
  }

/*====================================*/
/*--------Удаление всего списка-------*/
/*====================================*/
void DelAll(list p)
  {
    link q;
    while (p != NULL)
      {
        q=p;
        p=p->next;
        DelB(q->elem);
        free(q);
      }
    return ;
  }

/*====================================*/
/*-----Удаление узлов со словом w-----*/
/*====================================*/
int DelWord(list *p, Wlist w)
  {
    int c=0;
    list q;
    if ( *p )
    {
      if ((*p)->next==NULL)
        return 0;
      else
        while ((*p)->next) /*p=&(*p)->next*/
          if (RavWW((*p)->elem, w))
            {
              DelB((*p)->elem);
              q=(*p);
              *p=q->next;
              free(q);
              c++;
            }
          else
            p=&(*p)->next;
    }
    return c;
  }

/*===================================*/
/*--------------Main-----------------*/
/*===================================*/
int main()
{
  list ListWord=NULL;
  /*char ss[20];*/
  ListWord=Create();
  /*Print(ListWord);
  //printf("word=");
  //PrintW(LastWord(ListWord));
  //printf("\nk=%d\n", DelWord(&ListWord, LastWord(ListWord)));*/
  DelWord(&ListWord, LastWord(ListWord));
  Print(ListWord);
  DelAll(ListWord);
  /*printf("\nrav=%d\n",RavWW(ListWord->elem, LastWord(ListWord)));
  //while (scanf("%s", ss)==1)
  //  printf("%s_", ss);*/
}
