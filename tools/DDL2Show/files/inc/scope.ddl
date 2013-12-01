/* scope.ddl */

struct S
 {
  int i = ?i ;
 };

int i = 0 ;

int j = i ;

S s={};

scope S1
 {
  int i = 1 ;

  scope S2
   {
    int i = 2 ;
   }
 }

scope S1
 {
  int j = i ;

  S s={};

  scope S2
   {
    int j = i ;
   }

  scope S2
   {
    S s={};

    scope S3
     {
      int i = 3 ;

      int j = i ;

      S s={};

      int j0 = .#i ;
      int j1 = ..#i ;
      int j2 = ...#i ;
      int j3 = ....#i ;
      int j4 = ....#S1#S2#i ;
     }
   }
 }

