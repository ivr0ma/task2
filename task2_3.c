#include <stdio.h>
#include <time.h>

/*===================================*/
/*--------Итеративная функция--------*/
/*===================================*/
int FibI(int i)
{
  int i0=0,i1=1,c=2,f;
  for (;c<=i;c++)
  {
    f=i0+i1;
    i0=i1;
    i1=f;
  }
  if (i==0)
    return 0;
  else if (i==1)
    return 1;
  else
    return f;
}

/*===================================*/
/*--------Рекурсивная функция--------*/
/*===================================*/
int FibR(int i)
{
  if (i==0)
    return 0;
  else if (i==1)
    return 1;
  else
    return FibR(i-2)+FibR(i-1);
}

/*===================================*/
/*--------------Main-----------------*/
/*===================================*/
int main()
{
  int a, f, fr;
  double t;
  clock_t t_begin;
  clock_t t_end;

  while (scanf("%d", &a) == 1)
    {
      t_begin = clock();
      printf("%d\n", FibI(a));
      t_end = clock();
      t = t_end - t_begin;
      fprintf(stderr, "nonrec=%.10g\n", t);

      t_begin = clock();
      printf("%d\n", FibR(a));
      t_end = clock();
      t = t_end - t_begin;
      fprintf(stderr, "rec=%.10g\n", t);
    }
}
