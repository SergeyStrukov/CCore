/* do_...() */ 

void Parser::do_A1()
 {
  Element_M *arg1=pop();

  Element_A *elem=elem_A1(arg1);

  ulen new_state=Element_A::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_A2()
 {
  Element_M *arg3=pop();
  ElementAtom *arg2=pop();
  Element_A *arg1=pop();

  Element_A *elem=elem_A2(arg1,arg2,arg3);

  ulen new_state=Element_A::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_M1()
 {
  Element_P *arg1=pop();

  Element_M *elem=elem_M1(arg1);

  ulen new_state=Element_M::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_M2()
 {
  Element_M *arg3=pop();
  ElementAtom *arg2=pop();
  Element_P *arg1=pop();

  Element_M *elem=elem_M2(arg1,arg2,arg3);

  ulen new_state=Element_M::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_P1()
 {
  ElementAtom *arg1=pop();

  Element_P *elem=elem_P1(arg1);

  ulen new_state=Element_P::NextState(stack->state);

  push(elem,new_state);
 }

void Parser::do_P2()
 {
  ElementAtom *arg3=pop();
  Element_A *arg2=pop();
  ElementAtom *arg1=pop();

  Element_P *elem=elem_P2(arg1,arg2,arg3);

  ulen new_state=Element_P::NextState(stack->state);

  push(elem,new_state);
 }

