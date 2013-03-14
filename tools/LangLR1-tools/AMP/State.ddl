/* State.ddl */ 

RIndex RIndexLim = 7 ;
TIndex TIndexLim = 6 ;
NIndex NIndexLim = 3 ;
NTIndex NTIndexLim = 9 ; // T , N
StateIndex StateIndexLim = 22 ;
FinalIndex FinalIndexLim = 15 ;

Final[15] FinalTable=
 {
  { 0 ,
   {
    { 0 , RuleTable+0 },
    { 4 , RuleTable+0 }
   }
  },
  { 1 ,
   {
    { 0 , RuleTable+1 },
    { 4 , RuleTable+1 }
   }
  },
  { 2 ,
   {
    { 0 , RuleTable+2 },
    { 4 , RuleTable+2 }
   }
  },
  { 3 ,
   {
    { 0 , RuleTable+3 },
    { 3 , RuleTable+0 },
    { 4 , RuleTable+3 }
   }
  },
  { 4 ,
   {
    { 0 , RuleTable+4 },
    { 4 , RuleTable+4 }
   }
  },
  { 5 ,
   {
    { 0 , RuleTable+5 },
    { 3 , RuleTable+5 },
    { 4 , RuleTable+5 }
   }
  },
  { 6 ,
   {
    { 0 , RuleTable+6 },
    { 3 , RuleTable+6 },
    { 4 , RuleTable+6 }
   }
  },
  { 7 ,
   {
    { 1 , RuleTable+0 },
    { 5 , RuleTable+0 }
   }
  },
  { 8 ,
   {
    { 2 , RuleTable+0 },
    { 4 , RuleTable+0 }
   }
  },
  { 9 ,
   {
    { 2 , RuleTable+1 },
    { 4 , RuleTable+1 }
   }
  },
  { 10 ,
   {
    { 2 , RuleTable+2 },
    { 4 , RuleTable+2 }
   }
  },
  { 11 ,
   {
    { 2 , RuleTable+3 },
    { 3 , RuleTable+0 },
    { 4 , RuleTable+3 }
   }
  },
  { 12 ,
   {
    { 2 , RuleTable+4 },
    { 4 , RuleTable+4 }
   }
  },
  { 13 ,
   {
    { 2 , RuleTable+5 },
    { 3 , RuleTable+5 },
    { 4 , RuleTable+5 }
   }
  },
  { 14 ,
   {
    { 2 , RuleTable+6 },
    { 3 , RuleTable+6 },
    { 4 , RuleTable+6 }
   }
  }
 };

State[22] StateTable=
 {
  { 0 ,
   {
    { 1 , StateTable+1 },
    { 5 , StateTable+2 },
    { 6 , StateTable+3 },
    { 7 , StateTable+4 },
    { 8 , StateTable+16 }
   },
    FinalTable+7
  },
  { 1 ,
   {
    { 1 , StateTable+5 },
    { 5 , StateTable+6 },
    { 6 , StateTable+7 },
    { 7 , StateTable+8 },
    { 8 , StateTable+19 }
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
    { 4 , StateTable+9 }
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
    { 1 , StateTable+5 },
    { 5 , StateTable+6 },
    { 6 , StateTable+10 },
    { 7 , StateTable+8 },
    { 8 , StateTable+19 }
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
    { 2 , StateTable+11 },
    { 4 , StateTable+12 }
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
    { 1 , StateTable+1 },
    { 5 , StateTable+2 },
    { 7 , StateTable+14 },
    { 8 , StateTable+16 }
   },
    FinalTable+7
  },
  { 10 ,
   {
    { 2 , StateTable+17 },
    { 4 , StateTable+12 }
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
    { 1 , StateTable+5 },
    { 5 , StateTable+6 },
    { 7 , StateTable+18 },
    { 8 , StateTable+19 }
   },
    FinalTable+7
  },
  { 13 ,
   {
    { 1 , StateTable+5 },
    { 5 , StateTable+6 },
    { 7 , StateTable+20 },
    { 8 , StateTable+19 }
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
    { 3 , StateTable+21 }
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
    { 3 , StateTable+13 }
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
    { 1 , StateTable+1 },
    { 5 , StateTable+2 },
    { 7 , StateTable+15 },
    { 8 , StateTable+16 }
   },
    FinalTable+7
  }
 };

text[6] TNames=
 {
  "(End)",
  "T(\"(\")",
  "T(\")\")",
  "T(\"*\")",
  "T(\"+\")",
  "T(\"x\")"
 };

Rule[7] RuleTable=
 {
  /* shift, special */ { 0 , "<-" },
  { 1 , "A1" , 0 , { 7 } },
  { 2 , "A2" , 0 , { 6, 4, 7 } },
  { 3 , "M1" , 1 , { 8 } },
  { 4 , "M2" , 1 , { 8, 3, 7 } },
  { 5 , "P1" , 2 , { 5 } },
  { 6 , "P2" , 2 , { 1, 6, 2 } }
 };

NonTerminal[3] NonTerminalTable=
 {
  { 0 , "A" , { RuleTable+1, RuleTable+2 } },
  { 1 , "M" , { RuleTable+3, RuleTable+4 } },
  { 2 , "P" , { RuleTable+5, RuleTable+6 } }
 };

