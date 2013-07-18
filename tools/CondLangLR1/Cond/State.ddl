/* State.ddl */ 

ElementIndex AtomIndexLim = 13 ;
ElementIndex NonAtomIndexLim = 4 ;
ElementIndex ElementIndexLim = 17 ; // atoms , non-atoms

RuleIndex RuleIndexLim = 14 ;
FinalIndex FinalIndexLim = 31 ;
StateIndex StateIndexLim = 52 ;

Element[17] ElementTable=
 {
  // atoms

  { 0 , "(End)" },
  { 1 , "T(\"!\")" },
  { 2 , "T(\"!=\")" },
  { 3 , "T(\"&\")" },
  { 4 , "T(\"(\")" },
  { 5 , "T(\")\")" },
  { 6 , "T(\"<\")" },
  { 7 , "T(\"<=\")" },
  { 8 , "T(\"==\")" },
  { 9 , "T(\">\")" },
  { 10 , "T(\">=\")" },
  { 11 , "T(\"Name\")" },
  { 12 , "T(\"|\")" },

  // non-atoms

  { 13 , "COND" , { RuleTable+1, RuleTable+2 } },
  { 14 , "COND_MUL" , { RuleTable+3, RuleTable+4 } },
  { 15 , "COND_UN" , { RuleTable+5, RuleTable+6 } },
  { 16 , "COND_PRIM" , { RuleTable+7, RuleTable+8, RuleTable+9, RuleTable+10, RuleTable+11, RuleTable+12, RuleTable+13 } }
 };

Rule[14] RuleTable=
 {
  /* shift, special */ { 0 , "<-" },
  { 1 , "CastMUL" , ElementTable+13 , { ElementTable+14 } },
  { 2 , "OpOR" , ElementTable+13 , { ElementTable+13, ElementTable+12, ElementTable+14 } },
  { 3 , "CastUN" , ElementTable+14 , { ElementTable+15 } },
  { 4 , "OpAND" , ElementTable+14 , { ElementTable+14, ElementTable+3, ElementTable+15 } },
  { 5 , "CastPRIM" , ElementTable+15 , { ElementTable+16 } },
  { 6 , "OpNOT" , ElementTable+15 , { ElementTable+1, ElementTable+15 } },
  { 7 , "OpEQ" , ElementTable+16 , { ElementTable+11, ElementTable+8, ElementTable+11 } },
  { 8 , "OpNE" , ElementTable+16 , { ElementTable+11, ElementTable+2, ElementTable+11 } },
  { 9 , "OpLT" , ElementTable+16 , { ElementTable+11, ElementTable+6, ElementTable+11 } },
  { 10 , "OpLE" , ElementTable+16 , { ElementTable+11, ElementTable+7, ElementTable+11 } },
  { 11 , "OpGT" , ElementTable+16 , { ElementTable+11, ElementTable+9, ElementTable+11 } },
  { 12 , "OpGE" , ElementTable+16 , { ElementTable+11, ElementTable+10, ElementTable+11 } },
  { 13 , "Brackets" , ElementTable+16 , { ElementTable+4, ElementTable+13, ElementTable+5 } }
 };

Final[31] FinalTable=
 {
  { 0 ,
   {
    { ElementTable+0 , RuleTable+0 },
    { ElementTable+12 , RuleTable+0 }
   }
  },
  { 1 ,
   {
    { ElementTable+0 , RuleTable+1 },
    { ElementTable+3 , RuleTable+0 },
    { ElementTable+12 , RuleTable+1 }
   }
  },
  { 2 ,
   {
    { ElementTable+0 , RuleTable+2 },
    { ElementTable+3 , RuleTable+0 },
    { ElementTable+12 , RuleTable+2 }
   }
  },
  { 3 ,
   {
    { ElementTable+0 , RuleTable+3 },
    { ElementTable+3 , RuleTable+3 },
    { ElementTable+12 , RuleTable+3 }
   }
  },
  { 4 ,
   {
    { ElementTable+0 , RuleTable+4 },
    { ElementTable+3 , RuleTable+4 },
    { ElementTable+12 , RuleTable+4 }
   }
  },
  { 5 ,
   {
    { ElementTable+0 , RuleTable+5 },
    { ElementTable+3 , RuleTable+5 },
    { ElementTable+12 , RuleTable+5 }
   }
  },
  { 6 ,
   {
    { ElementTable+0 , RuleTable+6 },
    { ElementTable+3 , RuleTable+6 },
    { ElementTable+12 , RuleTable+6 }
   }
  },
  { 7 ,
   {
    { ElementTable+0 , RuleTable+7 },
    { ElementTable+3 , RuleTable+7 },
    { ElementTable+12 , RuleTable+7 }
   }
  },
  { 8 ,
   {
    { ElementTable+0 , RuleTable+8 },
    { ElementTable+3 , RuleTable+8 },
    { ElementTable+12 , RuleTable+8 }
   }
  },
  { 9 ,
   {
    { ElementTable+0 , RuleTable+9 },
    { ElementTable+3 , RuleTable+9 },
    { ElementTable+12 , RuleTable+9 }
   }
  },
  { 10 ,
   {
    { ElementTable+0 , RuleTable+10 },
    { ElementTable+3 , RuleTable+10 },
    { ElementTable+12 , RuleTable+10 }
   }
  },
  { 11 ,
   {
    { ElementTable+0 , RuleTable+11 },
    { ElementTable+3 , RuleTable+11 },
    { ElementTable+12 , RuleTable+11 }
   }
  },
  { 12 ,
   {
    { ElementTable+0 , RuleTable+12 },
    { ElementTable+3 , RuleTable+12 },
    { ElementTable+12 , RuleTable+12 }
   }
  },
  { 13 ,
   {
    { ElementTable+0 , RuleTable+13 },
    { ElementTable+3 , RuleTable+13 },
    { ElementTable+12 , RuleTable+13 }
   }
  },
  { 14 ,
   {
    { ElementTable+1 , RuleTable+0 },
    { ElementTable+4 , RuleTable+0 },
    { ElementTable+11 , RuleTable+0 }
   }
  },
  { 15 ,
   {
    { ElementTable+2 , RuleTable+0 },
    { ElementTable+6 , RuleTable+0 },
    { ElementTable+7 , RuleTable+0 },
    { ElementTable+8 , RuleTable+0 },
    { ElementTable+9 , RuleTable+0 },
    { ElementTable+10 , RuleTable+0 }
   }
  },
  { 16 ,
   {
    { ElementTable+3 , RuleTable+0 },
    { ElementTable+5 , RuleTable+1 },
    { ElementTable+12 , RuleTable+1 }
   }
  },
  { 17 ,
   {
    { ElementTable+3 , RuleTable+0 },
    { ElementTable+5 , RuleTable+2 },
    { ElementTable+12 , RuleTable+2 }
   }
  },
  { 18 ,
   {
    { ElementTable+3 , RuleTable+3 },
    { ElementTable+5 , RuleTable+3 },
    { ElementTable+12 , RuleTable+3 }
   }
  },
  { 19 ,
   {
    { ElementTable+3 , RuleTable+4 },
    { ElementTable+5 , RuleTable+4 },
    { ElementTable+12 , RuleTable+4 }
   }
  },
  { 20 ,
   {
    { ElementTable+3 , RuleTable+5 },
    { ElementTable+5 , RuleTable+5 },
    { ElementTable+12 , RuleTable+5 }
   }
  },
  { 21 ,
   {
    { ElementTable+3 , RuleTable+6 },
    { ElementTable+5 , RuleTable+6 },
    { ElementTable+12 , RuleTable+6 }
   }
  },
  { 22 ,
   {
    { ElementTable+3 , RuleTable+7 },
    { ElementTable+5 , RuleTable+7 },
    { ElementTable+12 , RuleTable+7 }
   }
  },
  { 23 ,
   {
    { ElementTable+3 , RuleTable+8 },
    { ElementTable+5 , RuleTable+8 },
    { ElementTable+12 , RuleTable+8 }
   }
  },
  { 24 ,
   {
    { ElementTable+3 , RuleTable+9 },
    { ElementTable+5 , RuleTable+9 },
    { ElementTable+12 , RuleTable+9 }
   }
  },
  { 25 ,
   {
    { ElementTable+3 , RuleTable+10 },
    { ElementTable+5 , RuleTable+10 },
    { ElementTable+12 , RuleTable+10 }
   }
  },
  { 26 ,
   {
    { ElementTable+3 , RuleTable+11 },
    { ElementTable+5 , RuleTable+11 },
    { ElementTable+12 , RuleTable+11 }
   }
  },
  { 27 ,
   {
    { ElementTable+3 , RuleTable+12 },
    { ElementTable+5 , RuleTable+12 },
    { ElementTable+12 , RuleTable+12 }
   }
  },
  { 28 ,
   {
    { ElementTable+3 , RuleTable+13 },
    { ElementTable+5 , RuleTable+13 },
    { ElementTable+12 , RuleTable+13 }
   }
  },
  { 29 ,
   {
    { ElementTable+5 , RuleTable+0 },
    { ElementTable+12 , RuleTable+0 }
   }
  },
  { 30 ,
   {
    { ElementTable+11 , RuleTable+0 }
   }
  }
 };

State[52] StateTable=
 {
  { 0 ,
   {
    { ElementTable+1 , StateTable+7 },
    { ElementTable+4 , StateTable+1 },
    { ElementTable+11 , StateTable+2 },
    { ElementTable+13 , StateTable+3 },
    { ElementTable+14 , StateTable+4 },
    { ElementTable+15 , StateTable+5 },
    { ElementTable+16 , StateTable+6 }
   },
    FinalTable+14
  },
  { 1 ,
   {
    { ElementTable+1 , StateTable+9 },
    { ElementTable+4 , StateTable+10 },
    { ElementTable+11 , StateTable+11 },
    { ElementTable+13 , StateTable+12 },
    { ElementTable+14 , StateTable+13 },
    { ElementTable+15 , StateTable+14 },
    { ElementTable+16 , StateTable+15 }
   },
    FinalTable+14
  },
  { 2 ,
   {
    { ElementTable+2 , StateTable+16 },
    { ElementTable+6 , StateTable+17 },
    { ElementTable+7 , StateTable+18 },
    { ElementTable+8 , StateTable+19 },
    { ElementTable+9 , StateTable+20 },
    { ElementTable+10 , StateTable+21 }
   },
    FinalTable+15
  },
  { 3 ,
   {
    { ElementTable+12 , StateTable+22 }
   },
    FinalTable+0
  },
  { 4 ,
   {
    { ElementTable+3 , StateTable+50 }
   },
    FinalTable+1
  },
  { 5 ,
   {
   },
    FinalTable+3
  },
  { 6 ,
   {
   },
    FinalTable+5
  },
  { 7 ,
   {
    { ElementTable+1 , StateTable+7 },
    { ElementTable+4 , StateTable+1 },
    { ElementTable+11 , StateTable+2 },
    { ElementTable+15 , StateTable+8 },
    { ElementTable+16 , StateTable+6 }
   },
    FinalTable+14
  },
  { 8 ,
   {
   },
    FinalTable+6
  },
  { 9 ,
   {
    { ElementTable+1 , StateTable+9 },
    { ElementTable+4 , StateTable+10 },
    { ElementTable+11 , StateTable+11 },
    { ElementTable+15 , StateTable+23 },
    { ElementTable+16 , StateTable+15 }
   },
    FinalTable+14
  },
  { 10 ,
   {
    { ElementTable+1 , StateTable+9 },
    { ElementTable+4 , StateTable+10 },
    { ElementTable+11 , StateTable+11 },
    { ElementTable+13 , StateTable+24 },
    { ElementTable+14 , StateTable+13 },
    { ElementTable+15 , StateTable+14 },
    { ElementTable+16 , StateTable+15 }
   },
    FinalTable+14
  },
  { 11 ,
   {
    { ElementTable+2 , StateTable+25 },
    { ElementTable+6 , StateTable+26 },
    { ElementTable+7 , StateTable+27 },
    { ElementTable+8 , StateTable+28 },
    { ElementTable+9 , StateTable+29 },
    { ElementTable+10 , StateTable+30 }
   },
    FinalTable+15
  },
  { 12 ,
   {
    { ElementTable+5 , StateTable+31 },
    { ElementTable+12 , StateTable+32 }
   },
    FinalTable+29
  },
  { 13 ,
   {
    { ElementTable+3 , StateTable+51 }
   },
    FinalTable+16
  },
  { 14 ,
   {
   },
    FinalTable+18
  },
  { 15 ,
   {
   },
    FinalTable+20
  },
  { 16 ,
   {
    { ElementTable+11 , StateTable+33 }
   },
    FinalTable+30
  },
  { 17 ,
   {
    { ElementTable+11 , StateTable+34 }
   },
    FinalTable+30
  },
  { 18 ,
   {
    { ElementTable+11 , StateTable+35 }
   },
    FinalTable+30
  },
  { 19 ,
   {
    { ElementTable+11 , StateTable+36 }
   },
    FinalTable+30
  },
  { 20 ,
   {
    { ElementTable+11 , StateTable+37 }
   },
    FinalTable+30
  },
  { 21 ,
   {
    { ElementTable+11 , StateTable+38 }
   },
    FinalTable+30
  },
  { 22 ,
   {
    { ElementTable+1 , StateTable+7 },
    { ElementTable+4 , StateTable+1 },
    { ElementTable+11 , StateTable+2 },
    { ElementTable+14 , StateTable+39 },
    { ElementTable+15 , StateTable+5 },
    { ElementTable+16 , StateTable+6 }
   },
    FinalTable+14
  },
  { 23 ,
   {
   },
    FinalTable+21
  },
  { 24 ,
   {
    { ElementTable+5 , StateTable+41 },
    { ElementTable+12 , StateTable+32 }
   },
    FinalTable+29
  },
  { 25 ,
   {
    { ElementTable+11 , StateTable+42 }
   },
    FinalTable+30
  },
  { 26 ,
   {
    { ElementTable+11 , StateTable+43 }
   },
    FinalTable+30
  },
  { 27 ,
   {
    { ElementTable+11 , StateTable+44 }
   },
    FinalTable+30
  },
  { 28 ,
   {
    { ElementTable+11 , StateTable+45 }
   },
    FinalTable+30
  },
  { 29 ,
   {
    { ElementTable+11 , StateTable+46 }
   },
    FinalTable+30
  },
  { 30 ,
   {
    { ElementTable+11 , StateTable+47 }
   },
    FinalTable+30
  },
  { 31 ,
   {
   },
    FinalTable+13
  },
  { 32 ,
   {
    { ElementTable+1 , StateTable+9 },
    { ElementTable+4 , StateTable+10 },
    { ElementTable+11 , StateTable+11 },
    { ElementTable+14 , StateTable+48 },
    { ElementTable+15 , StateTable+14 },
    { ElementTable+16 , StateTable+15 }
   },
    FinalTable+14
  },
  { 33 ,
   {
   },
    FinalTable+8
  },
  { 34 ,
   {
   },
    FinalTable+9
  },
  { 35 ,
   {
   },
    FinalTable+10
  },
  { 36 ,
   {
   },
    FinalTable+7
  },
  { 37 ,
   {
   },
    FinalTable+11
  },
  { 38 ,
   {
   },
    FinalTable+12
  },
  { 39 ,
   {
    { ElementTable+3 , StateTable+50 }
   },
    FinalTable+2
  },
  { 40 ,
   {
   },
    FinalTable+4
  },
  { 41 ,
   {
   },
    FinalTable+28
  },
  { 42 ,
   {
   },
    FinalTable+23
  },
  { 43 ,
   {
   },
    FinalTable+24
  },
  { 44 ,
   {
   },
    FinalTable+25
  },
  { 45 ,
   {
   },
    FinalTable+22
  },
  { 46 ,
   {
   },
    FinalTable+26
  },
  { 47 ,
   {
   },
    FinalTable+27
  },
  { 48 ,
   {
    { ElementTable+3 , StateTable+51 }
   },
    FinalTable+17
  },
  { 49 ,
   {
   },
    FinalTable+19
  },
  { 50 ,
   {
    { ElementTable+1 , StateTable+7 },
    { ElementTable+4 , StateTable+1 },
    { ElementTable+11 , StateTable+2 },
    { ElementTable+15 , StateTable+40 },
    { ElementTable+16 , StateTable+6 }
   },
    FinalTable+14
  },
  { 51 ,
   {
    { ElementTable+1 , StateTable+9 },
    { ElementTable+4 , StateTable+10 },
    { ElementTable+11 , StateTable+11 },
    { ElementTable+15 , StateTable+49 },
    { ElementTable+16 , StateTable+15 }
   },
    FinalTable+14
  }
 };

