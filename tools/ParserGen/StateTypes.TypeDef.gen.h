/* struct TypeDefCore */

struct TypeDefCore
 {
  // types

  struct S1; // State#Transition
  struct S2; // State
  struct S3; // Final#Action
  struct S4; // Final
  struct S5; // Rule
  struct S6; // Element

  using A1 = DDL::imp_uint32 ; // StateIndex
  using A2 = DDL::imp_uint32 ; // FinalIndex
  using A3 = DDL::imp_uint32 ; // RuleIndex
  using A4 = DDL::imp_uint32 ; // ElementIndex

  // structures

  struct S1
   {
    S6 * element;
    S2 * state;
   };

  struct S2
   {
    A1 state;
    PtrLen<S1 > transitions;
    S4 * final;

    using Transition = TypeDefCore::S1 ;
   };

  struct S3
   {
    S6 * atom;
    S5 * rule;
   };

  struct S4
   {
    A2 final;
    PtrLen<S3 > actions;

    using Action = TypeDefCore::S3 ;
   };

  struct S5
   {
    A3 rule;
    StrLen name;
    S6 * result;
    PtrLen<S6 * > args;
   };

  struct S6
   {
    A4 element;
    StrLen name;
    PtrLen<S5 * > rules;
    
    static A4 AtomLim;
   };

 };

namespace TypeDef {

  using Element = TypeDefCore::S6 ;

  using State = TypeDefCore::S2 ;

  using StateIndex = TypeDefCore::A1 ;

  using Rule = TypeDefCore::S5 ;

  using Final = TypeDefCore::S4 ;

  using FinalIndex = TypeDefCore::A2 ;

  using RuleIndex = TypeDefCore::A3 ;

  using ElementIndex = TypeDefCore::A4 ;

} // namespace TypeDef

