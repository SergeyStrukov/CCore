/* StateTypes.ddl */

type RIndex = uint ;
type TIndex = uint ;
type NIndex = uint ;
type NTIndex = uint ;
type StateIndex = uint ;
type FinalIndex = uint ;

struct Final
 {
  FinalIndex final;

  struct Action { TIndex t; Rule *rule; } [] actions;
 };

struct State
 {
  StateIndex state;

  struct Transition { NTIndex ntt; State *state; } [] transitions;

  Final *final;
 };

struct Rule
 {
  RIndex rule;
  text name;
  NIndex result;
  NTIndex[] str;
 };

struct NonTerminal
 {
  NIndex nt;
  text name;
  Rule * [] rules;
 };

