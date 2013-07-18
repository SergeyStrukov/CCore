/* Generator.gen.h */ 

#ifndef Generator_gen_h
#define Generator_gen_h

#include <CCore/inc/Gadget.h>

#include "Parser.gen.h"

/* lang Cond */ 

namespace Cond {

/* using */ 

using CCore::ulen;

/* types */ 

enum RTIndex
 {
  RTIndexEnd=0,
  RTIndexRule=TIndexLim,
  RTIndexLim=TIndexLim+RIndexLim
 };

inline bool isRule(RTIndex i) { return i>=RTIndexRule; }

inline RTIndex toRTIndex(TIndex i) { return RTIndex(i); }

inline RTIndex toRTIndex(RIndex i) { return RTIndex(TIndexLim+i); }

inline RIndex toRIndex(RTIndex i) { return RIndex(i-RTIndexRule); }

inline TIndex toTIndex(RTIndex i) { return TIndex(i); }

inline const char * GetTextDesc(RTIndex i)
 {
  if( isRule(i) ) return GetTextDesc( toRIndex(i) );

  return GetTextDesc( toTIndex(i) );
 }

enum NRTIndex
 {
  NRTIndexEnd=0,
  NRTIndexRule=RTIndexRule,
  NRTIndexNonTerminal=RTIndexLim,
  NRTIndexLim=NTIndexLim+RIndexLim
 };

inline bool isNonTerminal(NRTIndex i) { return i>=NRTIndexNonTerminal; }

inline RTIndex toRTIndex(NRTIndex i) { return RTIndex(i); }

/* struct GeneratorProp */ 

struct GeneratorProp
 {
  static const NRTIndex StartTable[1];

  static const NRTIndex Rule_CastMUL[3];
  static const NRTIndex Rule_OpOR[5];
  static const NRTIndex Rule_CastUN[3];
  static const NRTIndex Rule_OpAND[5];
  static const NRTIndex Rule_CastPRIM[3];
  static const NRTIndex Rule_OpNOT[4];
  static const NRTIndex Rule_OpEQ[5];
  static const NRTIndex Rule_OpNE[5];
  static const NRTIndex Rule_OpLT[5];
  static const NRTIndex Rule_OpLE[5];
  static const NRTIndex Rule_OpGT[5];
  static const NRTIndex Rule_OpGE[5];
  static const NRTIndex Rule_Brackets[5];

  static const NRTIndex *const NT_COND[3];
  static const NRTIndex *const NT_COND_MUL[3];
  static const NRTIndex *const NT_COND_UN[3];
  static const NRTIndex *const NT_COND_PRIM[8];

  struct NTRec
   {
    const NRTIndex *const *list;
    ulen list_len;
   };

  static const NTRec NTable[4];
 };

} // namespace Cond

#endif

