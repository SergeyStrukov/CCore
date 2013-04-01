/* ShiftState.ddl */

include <State.ddl>

StateIndex ShiftStateIndexLim = 7 ;

ShiftState[7] ShiftStateTable=
 {
  { 0 ,
   {
    { ElementTable+1 , ShiftStateTable+6 },
    { ElementTable+5 , ShiftStateTable+5 },
    { ElementTable+6 , ShiftStateTable+1 },
    { ElementTable+7 , ShiftStateTable+5 },
    { ElementTable+8 , ShiftStateTable+4 }
   },
   {
    StateTable+0
   },
   {
    FinalTable+7
   },
   {
    ElementTable+1,
    ElementTable+5
   }
  },
  { 1 ,
   {
    { ElementTable+4 , ShiftStateTable+2 }
   },
   {
    StateTable+3
   },
   {
    FinalTable+0
   },
   {
    ElementTable+0,
    ElementTable+4
   }
  },
  { 2 ,
   {
    { ElementTable+1 , ShiftStateTable+6 },
    { ElementTable+5 , ShiftStateTable+5 },
    { ElementTable+7 , ShiftStateTable+5 },
    { ElementTable+8 , ShiftStateTable+4 }
   },
   {
    StateTable+9,
    StateTable+12,
    StateTable+13,
    StateTable+21
   },
   {
    FinalTable+7
   },
   {
    ElementTable+1,
    ElementTable+5
   }
  },
  { 3 ,
   {
    { ElementTable+2 , ShiftStateTable+5 },
    { ElementTable+4 , ShiftStateTable+2 }
   },
   {
    StateTable+7,
    StateTable+10
   },
   {
    FinalTable+8
   },
   {
    ElementTable+2,
    ElementTable+4
   }
  },
  { 4 ,
   {
    { ElementTable+3 , ShiftStateTable+2 }
   },
   {
    StateTable+16,
    StateTable+19
   },
   {
    FinalTable+3,
    FinalTable+11
   },
   {
    ElementTable+3
   }
  },
  { 5 ,
   {
   },
   {
    StateTable+2,
    StateTable+4,
    StateTable+6,
    StateTable+8,
    StateTable+11,
    StateTable+14,
    StateTable+15,
    StateTable+17,
    StateTable+18,
    StateTable+20
   },
   {
    FinalTable+1,
    FinalTable+2,
    FinalTable+4,
    FinalTable+5,
    FinalTable+6,
    FinalTable+9,
    FinalTable+10,
    FinalTable+12,
    FinalTable+13,
    FinalTable+14
   },
   {
   }
  },
  { 6 ,
   {
    { ElementTable+1 , ShiftStateTable+6 },
    { ElementTable+5 , ShiftStateTable+5 },
    { ElementTable+6 , ShiftStateTable+3 },
    { ElementTable+7 , ShiftStateTable+5 },
    { ElementTable+8 , ShiftStateTable+4 }
   },
   {
    StateTable+1,
    StateTable+5
   },
   {
    FinalTable+7
   },
   {
    ElementTable+1,
    ElementTable+5
   }
  }
 };

