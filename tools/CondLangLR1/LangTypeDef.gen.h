/* struct TypeDefCore */

struct TypeDefCore
 {
  // types

  struct S1; // Final#Action
  struct S2; // Final
  struct S3; // State#Transition
  struct S4; // State
  struct S5; // TopRule#Arg
  struct S6; // TopRule
  struct S7; // Rule#Arg
  struct S8; // Rule
  struct S9; // Element
  struct S10; // Kind
  struct S11; // Synt
  struct S12; // Atom
  struct S13; // Lang

  using A1 = DDL::imp_uint32 ; // FinalIndex
  using A2 = DDL::imp_uint32 ; // StateIndex
  using A3 = DDL::imp_uint32 ; // RuleIndex
  using A4 = DDL::imp_uint32 ; // ElementIndex
  using A5 = DDL::imp_uint32 ; // KindIndex
  using A6 = DDL::imp_uint32 ; // SyntIndex
  using A7 = DDL::imp_uint32 ; // AtomIndex


  using XXX8226D906_9897_43AA_B1BE_D60B0A6E31C8 = TypeDefCore ;

  // structures

  struct S1
   {
    S12 * atom;
    S8 * rule;

    struct Ext;
   };

  struct S2
   {
    A1 index;
    PtrLen<S1 > actions;

    using Action = XXX8226D906_9897_43AA_B1BE_D60B0A6E31C8::S1 ;

    struct Ext;
   };

  struct S3
   {
    S9 * element;
    S4 * state;

    struct Ext;
   };

  struct S4
   {
    A2 index;
    S2 * final;
    PtrLen<S3 > transitions;

    using Transition = XXX8226D906_9897_43AA_B1BE_D60B0A6E31C8::S3 ;

    struct Ext;
   };

  struct S5
   {
    S12 * atom;
    S10 * kind;

    struct Ext;
   };

  struct S6
   {
    A3 index;
    StrLen name;
    S8 * bottom;
    S10 * result;
    PtrLen<S5 > args;

    using Arg = XXX8226D906_9897_43AA_B1BE_D60B0A6E31C8::S5 ;

    struct Ext;
   };

  struct S7
   {
    S12 * atom;
    S11 * synt;

    struct Ext;
   };

  struct S8
   {
    A3 index;
    StrLen name;
    S10 * result;
    PtrLen<S7 > args;

    using Arg = XXX8226D906_9897_43AA_B1BE_D60B0A6E31C8::S7 ;

    struct Ext;
   };

  struct S9
   {
    A4 index;
    S12 * atom;
    S10 * kind;

    struct Ext;
   };

  struct S10
   {
    A5 kindex;
    A5 index;
    StrLen name;
    S11 * synt;
    S9 * element;
    PtrLen<S6 * > rules;

    struct Ext;
   };

  struct S11
   {
    A6 index;
    StrLen name;
    PtrLen<S10 > kinds;
    PtrLen<S8 * > rules;

    struct Ext;
   };

  struct S12
   {
    A7 index;
    StrLen name;
    S9 * element;

    struct Ext;
   };

  struct S13
   {
    PtrLen<S12 > atoms;
    PtrLen<S11 > synts;
    PtrLen<S11 * > lang;
    PtrLen<S9 > elements;
    PtrLen<S8 > rules;
    PtrLen<S6 > top_rules;
    PtrLen<S4 > states;
    PtrLen<S2 > finals;

    struct Ext;
   };

  // extra

 };

using XXX212CD757_09B2_4D89_BE20_65C1E4E5A819 = TypeDefCore ;

namespace TypeDef {

    using AtomIndex = XXX212CD757_09B2_4D89_BE20_65C1E4E5A819::A7 ;
    using ElementIndex = XXX212CD757_09B2_4D89_BE20_65C1E4E5A819::A4 ;
    using FinalIndex = XXX212CD757_09B2_4D89_BE20_65C1E4E5A819::A1 ;
    using KindIndex = XXX212CD757_09B2_4D89_BE20_65C1E4E5A819::A5 ;
    using RuleIndex = XXX212CD757_09B2_4D89_BE20_65C1E4E5A819::A3 ;
    using StateIndex = XXX212CD757_09B2_4D89_BE20_65C1E4E5A819::A2 ;
    using SyntIndex = XXX212CD757_09B2_4D89_BE20_65C1E4E5A819::A6 ;
    using Atom = XXX212CD757_09B2_4D89_BE20_65C1E4E5A819::S12 ;
    using Element = XXX212CD757_09B2_4D89_BE20_65C1E4E5A819::S9 ;
    using Final = XXX212CD757_09B2_4D89_BE20_65C1E4E5A819::S2 ;
    using Kind = XXX212CD757_09B2_4D89_BE20_65C1E4E5A819::S10 ;
    using Lang = XXX212CD757_09B2_4D89_BE20_65C1E4E5A819::S13 ;
    using Rule = XXX212CD757_09B2_4D89_BE20_65C1E4E5A819::S8 ;
    using State = XXX212CD757_09B2_4D89_BE20_65C1E4E5A819::S4 ;
    using Synt = XXX212CD757_09B2_4D89_BE20_65C1E4E5A819::S11 ;
    using TopRule = XXX212CD757_09B2_4D89_BE20_65C1E4E5A819::S6 ;

} // namespace TypeDef

