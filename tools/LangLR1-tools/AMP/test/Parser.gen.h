/* Parser.gen.h */ 

#ifndef Parser_gen_h
#define Parser_gen_h

/* lang AMP */ 

namespace AMP {

/* types */ 

enum RIndex { RIndexShift=0, RIndexLim=7 };

const char * GetTextDesc(RIndex);

enum RuleLength { RuleLengthZero=0, RuleLengthMax=3 };

enum TIndex { TIndexEnd=0, TIndexLim=6 };

const char * GetTextDesc(TIndex);

enum NTIndex { NTIndexEnd=0, NTIndexLim=9 };

const char * GetTextDesc(NTIndex);

enum StateIndex { StateIndexBegin=0, StateIndexLim=22 };

/* struct RuleProp */ 

struct RuleProp
 {
  RIndex rule;
  RuleLength length;
  NTIndex result;
  NTIndex args[RuleLengthMax];

  static const RuleProp Table[RIndexLim-1];
  static const RuleProp ShiftTable[TIndexLim];
 };

/* struct State */ 

struct State
 {
  RIndex finals[TIndexLim];
  StateIndex transitions[NTIndexLim];

  static const State * GetBegin() { return Table; }

  const RuleProp * final(TIndex i) const
   {
    if( RIndex r=finals[i] )
      {
       if( r==1 )
         return RuleProp::ShiftTable+i;
       else
         return RuleProp::Table+r-2;
      }

    return 0;
   }

  const State * transition(NTIndex i) const
   {
    if( StateIndex t=transitions[i] ) return Table+t-1;

    return 0;
   }

  static const State Table[StateIndexLim];
 };

} // namespace AMP

#endif

