/* Generator.gen.h */ 

#ifndef Generator_gen_h
#define Generator_gen_h

#include <CCore/inc/Gadget.h>

#include "Parser.gen.h"

/* lang AMP */ 

namespace AMP {

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

  static const NRTIndex Rule_A1[3];
  static const NRTIndex Rule_A2[5];
  static const NRTIndex Rule_M1[3];
  static const NRTIndex Rule_M2[5];
  static const NRTIndex Rule_P1[3];
  static const NRTIndex Rule_P2[5];

  static const NRTIndex *const NT_A[3];
  static const NRTIndex *const NT_M[3];
  static const NRTIndex *const NT_P[3];

  struct NTRec
   {
    const NRTIndex *const *list;
    ulen list_len;
   };

  static const NTRec NTable[3];
 };

} // namespace AMP

#endif

