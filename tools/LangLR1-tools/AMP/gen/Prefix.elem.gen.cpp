/* elem_...() */ 

Element_A * Parser::elem_A1(Element_M *arg1)
 {
  Element_A *elem=ctx.create<Element_A>();

  elem->A1(ctx,arg1);

  return elem;
 }

Element_A * Parser::elem_A2(Element_A *arg1,ElementAtom *arg2,Element_M *arg3)
 {
  Element_A *elem=ctx.create<Element_A>();

  elem->A2(ctx,arg1,arg2,arg3);

  return elem;
 }

Element_M * Parser::elem_M1(Element_P *arg1)
 {
  Element_M *elem=ctx.create<Element_M>();

  elem->M1(ctx,arg1);

  return elem;
 }

Element_M * Parser::elem_M2(Element_P *arg1,ElementAtom *arg2,Element_M *arg3)
 {
  Element_M *elem=ctx.create<Element_M>();

  elem->M2(ctx,arg1,arg2,arg3);

  return elem;
 }

Element_P * Parser::elem_P1(ElementAtom *arg1)
 {
  Element_P *elem=ctx.create<Element_P>();

  elem->P1(ctx,arg1);

  return elem;
 }

Element_P * Parser::elem_P2(ElementAtom *arg1,Element_A *arg2,ElementAtom *arg3)
 {
  Element_P *elem=ctx.create<Element_P>();

  elem->P2(ctx,arg1,arg2,arg3);

  return elem;
 }

