/* State.ddl */ 

type RIndex = uint ;
type TIndex = uint ;
type NIndex = uint ;
type NTIndex = uint ;
type StateIndex = uint ;

RIndex RIndexLim = 7 ;
TIndex TIndexLim = 6 ;
NIndex NIndexLim = 3 ;
NTIndex NTIndexLim = 9 ; // T , N
StateIndex StateIndexLim = 22 ;

struct State
 {
  StateIndex state;

  struct Transition { NTIndex ntt; State *state; } [] transitions;

  struct Final { TIndex t; Rule *rule; } [] finals;
 };

struct Rule
 {
  RIndex rule;
  text name;
  NIndex result;
  NTIndex[] str;
 };

struct NonTerminal
 {
  NIndex nt;
  text name;
  Rule * [] rules;
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
   {
    { 1 , RuleTable+0 },
    { 5 , RuleTable+0 }
   }
  },
  { 1 ,
   {
    { 1 , StateTable+5 },
    { 5 , StateTable+6 },
    { 6 , StateTable+7 },
    { 7 , StateTable+8 },
    { 8 , StateTable+19 }
   },
   {
    { 1 , RuleTable+0 },
    { 5 , RuleTable+0 }
   }
  },
  { 2 ,
   {
   },
   {
    { 0 , RuleTable+5 },
    { 3 , RuleTable+5 },
    { 4 , RuleTable+5 }
   }
  },
  { 3 ,
   {
    { 4 , StateTable+9 }
   },
   {
    { 0 , RuleTable+0 },
    { 4 , RuleTable+0 }
   }
  },
  { 4 ,
   {
   },
   {
    { 0 , RuleTable+1 },
    { 4 , RuleTable+1 }
   }
  },
  { 5 ,
   {
    { 1 , StateTable+5 },
    { 5 , StateTable+6 },
    { 6 , StateTable+10 },
    { 7 , StateTable+8 },
    { 8 , StateTable+19 }
   },
   {
    { 1 , RuleTable+0 },
    { 5 , RuleTable+0 }
   }
  },
  { 6 ,
   {
   },
   {
    { 2 , RuleTable+5 },
    { 3 , RuleTable+5 },
    { 4 , RuleTable+5 }
   }
  },
  { 7 ,
   {
    { 2 , StateTable+11 },
    { 4 , StateTable+12 }
   },
   {
    { 2 , RuleTable+0 },
    { 4 , RuleTable+0 }
   }
  },
  { 8 ,
   {
   },
   {
    { 2 , RuleTable+1 },
    { 4 , RuleTable+1 }
   }
  },
  { 9 ,
   {
    { 1 , StateTable+1 },
    { 5 , StateTable+2 },
    { 7 , StateTable+14 },
    { 8 , StateTable+16 }
   },
   {
    { 1 , RuleTable+0 },
    { 5 , RuleTable+0 }
   }
  },
  { 10 ,
   {
    { 2 , StateTable+17 },
    { 4 , StateTable+12 }
   },
   {
    { 2 , RuleTable+0 },
    { 4 , RuleTable+0 }
   }
  },
  { 11 ,
   {
   },
   {
    { 0 , RuleTable+6 },
    { 3 , RuleTable+6 },
    { 4 , RuleTable+6 }
   }
  },
  { 12 ,
   {
    { 1 , StateTable+5 },
    { 5 , StateTable+6 },
    { 7 , StateTable+18 },
    { 8 , StateTable+19 }
   },
   {
    { 1 , RuleTable+0 },
    { 5 , RuleTable+0 }
   }
  },
  { 13 ,
   {
    { 1 , StateTable+5 },
    { 5 , StateTable+6 },
    { 7 , StateTable+20 },
    { 8 , StateTable+19 }
   },
   {
    { 1 , RuleTable+0 },
    { 5 , RuleTable+0 }
   }
  },
  { 14 ,
   {
   },
   {
    { 0 , RuleTable+2 },
    { 4 , RuleTable+2 }
   }
  },
  { 15 ,
   {
   },
   {
    { 0 , RuleTable+4 },
    { 4 , RuleTable+4 }
   }
  },
  { 16 ,
   {
    { 3 , StateTable+21 }
   },
   {
    { 0 , RuleTable+3 },
    { 3 , RuleTable+0 },
    { 4 , RuleTable+3 }
   }
  },
  { 17 ,
   {
   },
   {
    { 2 , RuleTable+6 },
    { 3 , RuleTable+6 },
    { 4 , RuleTable+6 }
   }
  },
  { 18 ,
   {
   },
   {
    { 2 , RuleTable+2 },
    { 4 , RuleTable+2 }
   }
  },
  { 19 ,
   {
    { 3 , StateTable+13 }
   },
   {
    { 2 , RuleTable+3 },
    { 3 , RuleTable+0 },
    { 4 , RuleTable+3 }
   }
  },
  { 20 ,
   {
   },
   {
    { 2 , RuleTable+4 },
    { 4 , RuleTable+4 }
   }
  },
  { 21 ,
   {
    { 1 , StateTable+1 },
    { 5 , StateTable+2 },
    { 7 , StateTable+15 },
    { 8 , StateTable+16 }
   },
   {
    { 1 , RuleTable+0 },
    { 5 , RuleTable+0 }
   }
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

