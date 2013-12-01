/* sample.ddl */

scope Basic 
 {
  include <inc/basic.ddl>
 }

include <inc/basic.ddl>

scope Int
 {
  include <inc/int.ddl>
 } 

scope Text
 {
  include <inc/text.ddl>
 }

scope Scope
 {
  include <inc/scope.ddl>
 }

scope Block
 {
  include <inc/block.ddl>
 }

scope Ptr
 {
  include <inc/ptr.ddl>
 }

scope Temp 
 {
  int Len = 10 ;

  int A = Len ;

  type T = int[Len] ;
 }

/*

type B = A * ;

type A = { { B } * [10] , int } * [] ;

*/

/*

type R = S[] ;

struct T
 {
  R[20] a;
 };

struct S
 {
  T[10] a;
  int[12] b;
 };

*/
