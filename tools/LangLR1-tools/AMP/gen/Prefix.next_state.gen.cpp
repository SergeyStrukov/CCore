/* Element_...::NextState() */ 

/* Element_A::NextState() */ 

ulen Element_A::NextState(ulen state)
 {
  static const StateTableType Table[]=
   {
     3, 7, 0, 0, 0,10, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0, 0
   };

  return Table[state];
 }

/* Element_M::NextState() */ 

ulen Element_M::NextState(ulen state)
 {
  static const StateTableType Table[]=
   {
     4, 8, 0, 0, 0, 8, 0, 0, 0,14,
     0, 0,18,20, 0, 0, 0, 0, 0, 0,
     0,15
   };

  return Table[state];
 }

/* Element_P::NextState() */ 

ulen Element_P::NextState(ulen state)
 {
  static const StateTableType Table[]=
   {
    16,19, 0, 0, 0,19, 0, 0, 0,16,
     0, 0,19,19, 0, 0, 0, 0, 0, 0,
     0,16
   };

  return Table[state];
 }

