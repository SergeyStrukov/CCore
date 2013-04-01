/* State.ddl */ 

ElementIndex AtomIndexLim = 6 ;
ElementIndex NonAtomIndexLim = 3 ;
ElementIndex ElementIndexLim = 9 ; // atoms , non-atoms

RuleIndex RuleIndexLim = 7 ;
FinalIndex FinalIndexLim = 15 ;
StateIndex StateIndexLim = 22 ;

Element[9] ElementTable=
 {
  // atoms

  { 0 , "(End)" },
  { 1 , "T(\"(\")" },
  { 2 , "T(\")\")" },
  { 3 , "T(\"*\")" },
  { 4 , "T(\"+\")" },
  { 5 , "T(\"x\")" },

  // non-atoms

  { 6 , "A" , { RuleTable+1, RuleTable+2 } },
  { 7 , "M" , { RuleTable+3, RuleTable+4 } },
  { 8 , "P" , { RuleTable+5, RuleTable+6 } }
 };

Rule[7] RuleTable=
 {
  /* shift, special */ { 0 , "<-" },
  { 1 , "A1" , ElementTable+6 , { ElementTable+7 } },
  { 2 , "A2" , ElementTable+6 , { ElementTable+6, ElementTable+4, ElementTable+7 } },
  { 3 , "M1" , ElementTable+7 , { ElementTable+8 } },
  { 4 , "M2" , ElementTable+7 , { ElementTable+8, ElementTable+3, ElementTable+7 } },
  { 5 , "P1" , ElementTable+8 , { ElementTable+5 } },
  { 6 , "P2" , ElementTable+8 , { ElementTable+1, ElementTable+6, ElementTable+2 } }
 };

Final[15] FinalTable=
 {
  { 0 ,
   {
    { ElementTable+0 , RuleTable+0 },
    { ElementTable+4 , RuleTable+0 }
   }
  },
  { 1 ,
   {
    { ElementTable+0 , RuleTable+1 },
    { ElementTable+4 , RuleTable+1 }
   }
  },
  { 2 ,
   {
    { ElementTable+0 , RuleTable+2 },
    { ElementTable+4 , RuleTable+2 }
   }
  },
  { 3 ,
   {
    { ElementTable+0 , RuleTable+3 },
    { ElementTable+3 , RuleTable+0 },
    { ElementTable+4 , RuleTable+3 }
   }
  },
  { 4 ,
   {
    { ElementTable+0 , RuleTable+4 },
    { ElementTable+4 , RuleTable+4 }
   }
  },
  { 5 ,
   {
    { ElementTable+0 , RuleTable+5 },
    { ElementTable+3 , RuleTable+5 },
    { ElementTable+4 , RuleTable+5 }
   }
  },
  { 6 ,
   {
    { ElementTable+0 , RuleTable+6 },
    { ElementTable+3 , RuleTable+6 },
    { ElementTable+4 , RuleTable+6 }
   }
  },
  { 7 ,
   {
    { ElementTable+1 , RuleTable+0 },
    { ElementTable+5 , RuleTable+0 }
   }
  },
  { 8 ,
   {
    { ElementTable+2 , RuleTable+0 },
    { ElementTable+4 , RuleTable+0 }
   }
  },
  { 9 ,
   {
    { ElementTable+2 , RuleTable+1 },
    { ElementTable+4 , RuleTable+1 }
   }
  },
  { 10 ,
   {
    { ElementTable+2 , RuleTable+2 },
    { ElementTable+4 , RuleTable+2 }
   }
  },
  { 11 ,
   {
    { ElementTable+2 , RuleTable+3 },
    { ElementTable+3 , RuleTable+0 },
    { ElementTable+4 , RuleTable+3 }
   }
  },
  { 12 ,
   {
    { ElementTable+2 , RuleTable+4 },
    { ElementTable+4 , RuleTable+4 }
   }
  },
  { 13 ,
   {
    { ElementTable+2 , RuleTable+5 },
    { ElementTable+3 , RuleTable+5 },
    { ElementTable+4 , RuleTable+5 }
   }
  },
  { 14 ,
   {
    { ElementTable+2 , RuleTable+6 },
    { ElementTable+3 , RuleTable+6 },
    { ElementTable+4 , RuleTable+6 }
   }
  }
 };

State[22] StateTable=
 {
  { 0 ,
   {
    { ElementTable+1 , StateTable+1 },
    { ElementTable+5 , StateTable+2 },
    { ElementTable+6 , StateTable+3 },
    { ElementTable+7 , StateTable+4 },
    { ElementTable+8 , StateTable+16 }
   },
    FinalTable+7
  },
  { 1 ,
   {
    { ElementTable+1 , StateTable+5 },
    { ElementTable+5 , StateTable+6 },
    { ElementTable+6 , StateTable+7 },
    { ElementTable+7 , StateTable+8 },
    { ElementTable+8 , StateTable+19 }
   },
    FinalTable+7
  },
  { 2 ,
   {
   },
    FinalTable+5
  },
  { 3 ,
   {
    { ElementTable+4 , StateTable+9 }
   },
    FinalTable+0
  },
  { 4 ,
   {
   },
    FinalTable+1
  },
  { 5 ,
   {
    { ElementTable+1 , StateTable+5 },
    { ElementTable+5 , StateTable+6 },
    { ElementTable+6 , StateTable+10 },
    { ElementTable+7 , StateTable+8 },
    { ElementTable+8 , StateTable+19 }
   },
    FinalTable+7
  },
  { 6 ,
   {
   },
    FinalTable+13
  },
  { 7 ,
   {
    { ElementTable+2 , StateTable+11 },
    { ElementTable+4 , StateTable+12 }
   },
    FinalTable+8
  },
  { 8 ,
   {
   },
    FinalTable+9
  },
  { 9 ,
   {
    { ElementTable+1 , StateTable+1 },
    { ElementTable+5 , StateTable+2 },
    { ElementTable+7 , StateTable+14 },
    { ElementTable+8 , StateTable+16 }
   },
    FinalTable+7
  },
  { 10 ,
   {
    { ElementTable+2 , StateTable+17 },
    { ElementTable+4 , StateTable+12 }
   },
    FinalTable+8
  },
  { 11 ,
   {
   },
    FinalTable+6
  },
  { 12 ,
   {
    { ElementTable+1 , StateTable+5 },
    { ElementTable+5 , StateTable+6 },
    { ElementTable+7 , StateTable+18 },
    { ElementTable+8 , StateTable+19 }
   },
    FinalTable+7
  },
  { 13 ,
   {
    { ElementTable+1 , StateTable+5 },
    { ElementTable+5 , StateTable+6 },
    { ElementTable+7 , StateTable+20 },
    { ElementTable+8 , StateTable+19 }
   },
    FinalTable+7
  },
  { 14 ,
   {
   },
    FinalTable+2
  },
  { 15 ,
   {
   },
    FinalTable+4
  },
  { 16 ,
   {
    { ElementTable+3 , StateTable+21 }
   },
    FinalTable+3
  },
  { 17 ,
   {
   },
    FinalTable+14
  },
  { 18 ,
   {
   },
    FinalTable+10
  },
  { 19 ,
   {
    { ElementTable+3 , StateTable+13 }
   },
    FinalTable+11
  },
  { 20 ,
   {
   },
    FinalTable+12
  },
  { 21 ,
   {
    { ElementTable+1 , StateTable+1 },
    { ElementTable+5 , StateTable+2 },
    { ElementTable+7 , StateTable+15 },
    { ElementTable+8 , StateTable+16 }
   },
    FinalTable+7
  }
 };

