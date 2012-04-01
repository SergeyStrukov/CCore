/* Generator.gen.cpp */ 

#include "Generator.gen.h"

/* lang AMP */ 

namespace AMP {

/* using */ 

using CCore::DimOf;

/* struct GeneratorProp */ 

const NRTIndex GeneratorProp::StartTable[1]=
 {
  NRTIndex(NRTIndexNonTerminal+0),
 };

const NRTIndex GeneratorProp::Rule_A1[3]=
 {
  NRTIndex(14),
  NRTIndex(7),
  NRTIndexEnd
 };

const NRTIndex GeneratorProp::Rule_A2[5]=
 {
  NRTIndex(13),
  NRTIndex(4),
  NRTIndex(14),
  NRTIndex(8),
  NRTIndexEnd
 };

const NRTIndex GeneratorProp::Rule_M1[3]=
 {
  NRTIndex(15),
  NRTIndex(9),
  NRTIndexEnd
 };

const NRTIndex GeneratorProp::Rule_M2[5]=
 {
  NRTIndex(15),
  NRTIndex(3),
  NRTIndex(14),
  NRTIndex(10),
  NRTIndexEnd
 };

const NRTIndex GeneratorProp::Rule_P1[3]=
 {
  NRTIndex(5),
  NRTIndex(11),
  NRTIndexEnd
 };

const NRTIndex GeneratorProp::Rule_P2[5]=
 {
  NRTIndex(1),
  NRTIndex(13),
  NRTIndex(2),
  NRTIndex(12),
  NRTIndexEnd
 };

const NRTIndex *const GeneratorProp::NT_A[3]=
 {
  Rule_A1,
  Rule_A1,
  Rule_A2,
 };

const NRTIndex *const GeneratorProp::NT_M[3]=
 {
  Rule_M1,
  Rule_M1,
  Rule_M2,
 };

const NRTIndex *const GeneratorProp::NT_P[3]=
 {
  Rule_P1,
  Rule_P1,
  Rule_P2,
 };

const GeneratorProp::NTRec GeneratorProp::NTable[3]=
 {
  {NT_A,DimOf(NT_A)},
  {NT_M,DimOf(NT_M)},
  {NT_P,DimOf(NT_P)},
 };

} // namespace AMP

