/* struct Element_A */ 

struct Element_A : ElementBase
 {
  static ulen NextState(ulen state);

  void A1(ElementContext ctx,Element_M *);

  void A2(ElementContext ctx,Element_A *,ElementAtom *,Element_M *);
 };

/* struct Element_M */ 

struct Element_M : ElementBase
 {
  static ulen NextState(ulen state);

  void M1(ElementContext ctx,Element_P *);

  void M2(ElementContext ctx,Element_P *,ElementAtom *,Element_M *);
 };

/* struct Element_P */ 

struct Element_P : ElementBase
 {
  static ulen NextState(ulen state);

  void P1(ElementContext ctx,ElementAtom *);

  void P2(ElementContext ctx,ElementAtom *,Element_A *,ElementAtom *);
 };

