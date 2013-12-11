/* struct TypeDefCore */

struct TypeDefCore
 {
  // types

  struct S1; // #Final#Action
  struct S2; // #Final
  struct S3; // #State#Transition
  struct S4; // #State
  struct S5; // #TopRule
  struct S6; // #Rule
  struct S7; // #Element
  struct S8; // #Kind
  struct S9; // #Synt
  struct S10; // #Atom
  struct S11; // #Lang

  using A1 = DDL2::MapPolyPtr< S10 , S8 > ; // #TopRule#Arg
  using A2 = DDL2::MapPolyPtr< S10 , S9 > ; // #Rule#Arg
  using A3 = uint32 ; // #FinalIndex
  using A4 = uint32 ; // #StateIndex
  using A5 = uint32 ; // #RuleIndex
  using A6 = uint32 ; // #ElementIndex
  using A7 = uint32 ; // #KindIndex
  using A8 = uint32 ; // #SyntIndex
  using A9 = uint32 ; // #AtomIndex


  using XXX8226D906_9898_43AA_B1BE_D60B0A6E31C8 = TypeDefCore ;

  // structures

  struct S1
   {
    DDL2::MapPtr< S10 > atom;
    DDL2::MapPtr< S6 > rule;

    struct Ext;
   };

  struct S2
   {
    A3 index;
    DDL2::MapRange< S1 > actions;

    using Action = XXX8226D906_9898_43AA_B1BE_D60B0A6E31C8::S1 ;

    struct Ext;
   };

  struct S3
   {
    DDL2::MapPtr< S7 > element;
    DDL2::MapPtr< S4 > state;

    struct Ext;
   };

  struct S4
   {
    A4 index;
    DDL2::MapPtr< S2 > final;
    DDL2::MapRange< S3 > transitions;

    using Transition = XXX8226D906_9898_43AA_B1BE_D60B0A6E31C8::S3 ;

    struct Ext;
   };

  struct S5
   {
    A5 index;
    DDL2::MapText name;
    DDL2::MapPtr< S6 > bottom;
    DDL2::MapPtr< S8 > result;
    DDL2::MapRange< A1 > args;

    using Arg = XXX8226D906_9898_43AA_B1BE_D60B0A6E31C8::A1 ;

    struct Ext;
   };

  struct S6
   {
    A5 index;
    DDL2::MapText name;
    DDL2::MapPtr< S8 > result;
    DDL2::MapRange< A2 > args;

    using Arg = XXX8226D906_9898_43AA_B1BE_D60B0A6E31C8::A2 ;

    struct Ext;
   };

  struct S7
   {
    A6 index;
    DDL2::MapPolyPtr< S10 , S8 > elem;

    struct Ext;
   };

  struct S8
   {
    A7 kindex;
    A7 index;
    DDL2::MapText name;
    DDL2::MapPtr< S9 > synt;
    DDL2::MapPtr< S7 > element;
    DDL2::MapRange< DDL2::MapPtr< S5 > > rules;

    struct Ext;
   };

  struct S9
   {
    A8 index;
    DDL2::MapText name;
    DDL2::MapRange< S8 > kinds;
    DDL2::MapRange< DDL2::MapPtr< S6 > > rules;

    struct Ext;
   };

  struct S10
   {
    A9 index;
    DDL2::MapText name;
    DDL2::MapPtr< S7 > element;

    struct Ext;
   };

  struct S11
   {
    DDL2::MapRange< S10 > atoms;
    DDL2::MapRange< S9 > synts;
    DDL2::MapRange< DDL2::MapPtr< S9 > > lang;
    DDL2::MapRange< S7 > elements;
    DDL2::MapRange< S6 > rules;
    DDL2::MapRange< S5 > top_rules;
    DDL2::MapRange< S4 > states;
    DDL2::MapRange< S2 > finals;

    struct Ext;
   };

  // extra

 };

using XXX212CD757_09B3_4D89_BE20_65C1E4E5A819 = TypeDefCore ;

namespace TypeDef {

    using StateIndex = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::A4 ;
    using KindIndex = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::A7 ;
    using RuleIndex = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::A5 ;
    using SyntIndex = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::A8 ;
    using AtomIndex = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::A9 ;
    using ElementIndex = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::A6 ;
    using FinalIndex = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::A3 ;
    using Atom = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S10 ;
    using Kind = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S8 ;
    using Lang = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S11 ;
    using Rule = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S6 ;
    using Synt = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S9 ;
    using Element = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S7 ;
    using TopRule = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S5 ;
    using Final = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S2 ;
    using State = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S4 ;

} // namespace TypeDef

