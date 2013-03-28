/* struct TypeDefCore */

struct TypeDefCore
 {
  // types

  struct S1; // ShiftState#Transition
  struct S2; // ShiftState
  struct S3; // State#Transition
  struct S4; // State
  struct S5; // Final#Action
  struct S6; // Final
  struct S7; // Rule
  struct S8; // Element

  using A1 = DDL::imp_uint32 ; // StateIndex
  using A2 = DDL::imp_uint32 ; // FinalIndex
  using A3 = DDL::imp_uint32 ; // RuleIndex
  using A4 = DDL::imp_uint32 ; // ElementIndex


  using XXX8226D906_9897_43AA_B1BE_D60B0A6E31C8 = TypeDefCore ;

  // structures

  struct S1
   {
    S8 * element;
    S2 * state;
   };

  struct S2
   {
    A1 state;
    PtrLen<S1 > transitions;
    PtrLen<S4 * > states;
    PtrLen<S6 * > finals;
    PtrLen<S8 * > shift;

    using Transition = XXX8226D906_9897_43AA_B1BE_D60B0A6E31C8::S1 ;
   };

  struct S3
   {
    S8 * element;
    S4 * state;
   };

  struct S4
   {
    A1 state;
    PtrLen<S3 > transitions;
    S6 * final;

    using Transition = XXX8226D906_9897_43AA_B1BE_D60B0A6E31C8::S3 ;
   };

  struct S5
   {
    S8 * atom;
    S7 * rule;
   };

  struct S6
   {
    A2 final;
    PtrLen<S5 > actions;

    using Action = XXX8226D906_9897_43AA_B1BE_D60B0A6E31C8::S5 ;
   };

  struct S7
   {
    A3 rule;
    StrLen name;
    S8 * result;
    PtrLen<S8 * > args;
   };

  struct S8
   {
    A4 element;
    StrLen name;
    PtrLen<S7 * > rules;
   };

  // extra

 };

using XXX212CD757_09B2_4D89_BE20_65C1E4E5A819 = TypeDefCore ;

namespace TypeDef {

    using ElementIndex = XXX212CD757_09B2_4D89_BE20_65C1E4E5A819::A4 ;
    using FinalIndex = XXX212CD757_09B2_4D89_BE20_65C1E4E5A819::A2 ;
    using RuleIndex = XXX212CD757_09B2_4D89_BE20_65C1E4E5A819::A3 ;
    using StateIndex = XXX212CD757_09B2_4D89_BE20_65C1E4E5A819::A1 ;
    using Element = XXX212CD757_09B2_4D89_BE20_65C1E4E5A819::S8 ;
    using Final = XXX212CD757_09B2_4D89_BE20_65C1E4E5A819::S6 ;
    using Rule = XXX212CD757_09B2_4D89_BE20_65C1E4E5A819::S7 ;
    using ShiftState = XXX212CD757_09B2_4D89_BE20_65C1E4E5A819::S2 ;
    using State = XXX212CD757_09B2_4D89_BE20_65C1E4E5A819::S4 ;

} // namespace TypeDef

