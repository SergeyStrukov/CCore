/* ptr.ddl */

struct R
 {
  int a;
  R *ptr;
 };

R[] list={ {1,list+1}, {2,list+4}, {3,list}, {4,list+5}, {5,list+6}, {6,list+2}, {7,list+3} };

int[] ind={ list[0].ptr->a, list[1].ptr->a, list[2].ptr->a, list[3].ptr->a, list[4].ptr->a, list[5].ptr->a, list[6].ptr->a };

int d1=list[0].ptr-list[1].ptr;

R *ptr=list+9+(list[0].ptr-list[1].ptr);

int b=ptr->a;
