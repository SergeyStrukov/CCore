/* scope.ddl */

int i = 0 ;

int j = i ;

scope S1
 {
  int i = 1 ;

  int j = i ;

  scope S2
   {
    int i = 2 ;

    int j = i ;

    scope S3
     {
      int i = 3 ;

      int j = i ;

      int j0 = .#i ;
      int j1 = ..#i ;
      int j2 = ...#i ;
      int j3 = ....#i ;
      int j4 = ....#S1#S2#i ;
     }
   }
 }

