/* struct TypeDefCore */

struct TypeDefCore
 {
  // types

  struct S1; // NonTerminal
  struct S2; // Rule
  struct S3; // State#Transition
  struct S4; // State
  struct S5; // Final#Action
  struct S6; // Final

  using A1 = DDL::imp_uint32 ; // FinalIndex
  using A2 = DDL::imp_uint32 ; // StateIndex
  using A3 = DDL::imp_uint32 ; // NTIndex
  using A4 = DDL::imp_uint32 ; // NIndex
  using A5 = DDL::imp_uint32 ; // TIndex
  using A6 = DDL::imp_uint32 ; // RIndex

  // structures

  struct S1
   {
    A4 nt;
    StrLen name;
    PtrLen<S2 * > rules;
   };

  struct S2
   {
    A6 rule;
    StrLen name;
    A4 result;
    PtrLen<A3 > str;
   };

  struct S3
   {
    A3 ntt;
    S4 * state;
   };

  struct S4
   {
    A2 state;
    PtrLen<S3 > transitions;
    S6 * final;
   };

  struct S5
   {
    A5 t;
    S2 * rule;
   };

  struct S6
   {
    A1 final;
    PtrLen<S5 > actions;
   };

 };

namespace TypeDef {

  using NonTerminal = TypeDefCore::S1 ;

  using Rule = TypeDefCore::S2 ;

  using FinalIndex = TypeDefCore::A1 ;

  using State = TypeDefCore::S4 ;

  using StateIndex = TypeDefCore::A2 ;

  using Final = TypeDefCore::S6 ;

  using NTIndex = TypeDefCore::A3 ;

  using NIndex = TypeDefCore::A4 ;

  using TIndex = TypeDefCore::A5 ;

  using RIndex = TypeDefCore::A6 ;

  namespace Final {

    using Action = TypeDefCore::S5 ;

  } // namespace Final

  namespace State {

    using Transition = TypeDefCore::S3 ;

  } // namespace State


} // namespace TypeDef
