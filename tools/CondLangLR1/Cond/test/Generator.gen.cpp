/* Generator.gen.cpp */ 

#include "Generator.gen.h"

/* lang Cond */ 

namespace Cond {

/* using */ 

using CCore::DimOf;

/* struct GeneratorProp */ 

const NRTIndex GeneratorProp::StartTable[1]=
 {
  NRTIndex(NRTIndexNonTerminal+0),
 };

const NRTIndex GeneratorProp::Rule_CastMUL[3]=
 {
  NRTIndex(28),
  NRTIndex(14),
  NRTIndexEnd
 };

const NRTIndex GeneratorProp::Rule_OpOR[5]=
 {
  NRTIndex(27),
  NRTIndex(12),
  NRTIndex(28),
  NRTIndex(15),
  NRTIndexEnd
 };

const NRTIndex GeneratorProp::Rule_CastUN[3]=
 {
  NRTIndex(29),
  NRTIndex(16),
  NRTIndexEnd
 };

const NRTIndex GeneratorProp::Rule_OpAND[5]=
 {
  NRTIndex(28),
  NRTIndex(3),
  NRTIndex(29),
  NRTIndex(17),
  NRTIndexEnd
 };

const NRTIndex GeneratorProp::Rule_CastPRIM[3]=
 {
  NRTIndex(30),
  NRTIndex(18),
  NRTIndexEnd
 };

const NRTIndex GeneratorProp::Rule_OpNOT[4]=
 {
  NRTIndex(1),
  NRTIndex(29),
  NRTIndex(19),
  NRTIndexEnd
 };

const NRTIndex GeneratorProp::Rule_OpEQ[5]=
 {
  NRTIndex(11),
  NRTIndex(8),
  NRTIndex(11),
  NRTIndex(20),
  NRTIndexEnd
 };

const NRTIndex GeneratorProp::Rule_OpNE[5]=
 {
  NRTIndex(11),
  NRTIndex(2),
  NRTIndex(11),
  NRTIndex(21),
  NRTIndexEnd
 };

const NRTIndex GeneratorProp::Rule_OpLT[5]=
 {
  NRTIndex(11),
  NRTIndex(6),
  NRTIndex(11),
  NRTIndex(22),
  NRTIndexEnd
 };

const NRTIndex GeneratorProp::Rule_OpLE[5]=
 {
  NRTIndex(11),
  NRTIndex(7),
  NRTIndex(11),
  NRTIndex(23),
  NRTIndexEnd
 };

const NRTIndex GeneratorProp::Rule_OpGT[5]=
 {
  NRTIndex(11),
  NRTIndex(9),
  NRTIndex(11),
  NRTIndex(24),
  NRTIndexEnd
 };

const NRTIndex GeneratorProp::Rule_OpGE[5]=
 {
  NRTIndex(11),
  NRTIndex(10),
  NRTIndex(11),
  NRTIndex(25),
  NRTIndexEnd
 };

const NRTIndex GeneratorProp::Rule_Brackets[5]=
 {
  NRTIndex(4),
  NRTIndex(27),
  NRTIndex(5),
  NRTIndex(26),
  NRTIndexEnd
 };

const NRTIndex *const GeneratorProp::NT_COND[3]=
 {
  Rule_CastMUL,
  Rule_CastMUL,
  Rule_OpOR,
 };

const NRTIndex *const GeneratorProp::NT_COND_MUL[3]=
 {
  Rule_CastUN,
  Rule_CastUN,
  Rule_OpAND,
 };

const NRTIndex *const GeneratorProp::NT_COND_UN[3]=
 {
  Rule_CastPRIM,
  Rule_CastPRIM,
  Rule_OpNOT,
 };

const NRTIndex *const GeneratorProp::NT_COND_PRIM[8]=
 {
  Rule_OpEQ,
  Rule_OpEQ,
  Rule_OpNE,
  Rule_OpLT,
  Rule_OpLE,
  Rule_OpGT,
  Rule_OpGE,
  Rule_Brackets,
 };

const GeneratorProp::NTRec GeneratorProp::NTable[4]=
 {
  {NT_COND,DimOf(NT_COND)},
  {NT_COND_MUL,DimOf(NT_COND_MUL)},
  {NT_COND_UN,DimOf(NT_COND_UN)},
  {NT_COND_PRIM,DimOf(NT_COND_PRIM)},
 };

} // namespace Cond

