/* block.ddl */

struct S
 {
  int a ;
  text b = "default" ;
  int[10] c = {1,2,3} ;
 } s1 = { 1 } ;

struct T
 {
  text b ;
  int[10] c ;
 } t1= { "b" , {5,6,7} } ;

S[3] s3={ t1 , {} , null };

S[4] s4={ t1 { .b=".b" } { .a=66 , .a1="???" } { .c={1,2,3} } };

struct E
 {
  type Int = int ;

  const Int def_e = 100 ;

  struct S { Int a; } e={ def_e };

 };

E e = {} ;

E#Int de=E#def_e ;
