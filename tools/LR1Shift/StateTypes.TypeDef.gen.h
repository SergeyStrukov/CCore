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


  using XXX8226D906_9897_43AA_B1BE_D60B0A6E31C8 = TypeDefCore ;

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

    using Transition = XXX8226D906_9897_43AA_B1BE_D60B0A6E31C8::S1 ;
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

    using Action = XXX8226D906_9897_43AA_B1BE_D60B0A6E31C8::S3 ;
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
    
    static A4 ElementLim;
    static A4 AtomLim;
   };

  // extra

 };

using XXX212CD757_09B2_4D89_BE20_65C1E4E5A819 = TypeDefCore ;

namespace TypeDef {

    using ElementIndex = XXX212CD757_09B2_4D89_BE20_65C1E4E5A819::A4 ;
    using FinalIndex = XXX212CD757_09B2_4D89_BE20_65C1E4E5A819::A2 ;
    using RuleIndex = XXX212CD757_09B2_4D89_BE20_65C1E4E5A819::A3 ;
    using StateIndex = XXX212CD757_09B2_4D89_BE20_65C1E4E5A819::A1 ;
    using Element = XXX212CD757_09B2_4D89_BE20_65C1E4E5A819::S6 ;
    using Final = XXX212CD757_09B2_4D89_BE20_65C1E4E5A819::S4 ;
    using Rule = XXX212CD757_09B2_4D89_BE20_65C1E4E5A819::S5 ;
    using State = XXX212CD757_09B2_4D89_BE20_65C1E4E5A819::S2 ;

} // namespace TypeDef

