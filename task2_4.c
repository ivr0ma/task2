#include <stdio.h>
#define n 20

double str2double(char str[])
{
  double ch=0,        /*число*/
         dr=0,        /*дробная часть*/
         d=10,e=0;
  int i=0;
  char flag=0;
  /*printf("s=%s\n",str);*/
  while (str[i] != '\0' && str[i] != 'f' && str[i] != 'F')
    {
      if (str[i] == '.')
        {
          flag=1;
          i++;
          continue;
        }
      if (str[i] == 'e' || str[i] == 'E')
        {
          i++;
          if (str[i] == '+')
            {
              flag=2;
              i++;
            }
          else if (str[i] == '-')
            {
              flag=3;
              i++;
            }
          else
            flag=2;
          continue;
        }
      if (flag == 1)
        {
          dr = dr + (str[i] - '0')/d;
          d *= 10;
        }
      else if (flag == 2 || flag == 3)
        e = e*10 + (str[i] - '0');
      else
        ch = ch*10 + (str[i] - '0');
      i++;
      /*printf("ch=%.10g, dr=%.10g, flag=%d\n", ch, dr, flag);*/
    }
  ch = ch + dr;
  if (flag == 2)
    for (i=0; i < (int) e; i++)
      ch *= 10;
  else
    for (i=0; i < (int) e; i++)
      ch /= 10;
  return ch;
}
/*===================================*/
/*--------------Main-----------------*/
/*===================================*/
int main()
{
  char str[n];
  double d;
  /*scanf("%lf", &d);
  //printf("ch=%.10g\n", d);
  //scanf("%s", str);
  //printf("\nchislo=%.10g\n", str2double(str));*/
  while(scanf("%s", str)==1)
    printf("%.10g\n", str2double(str));
}
