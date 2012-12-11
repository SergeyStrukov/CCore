/* enum AtomClass */ 

const char * GetTextDesc(AtomClass ac)
 {
  static const char *const Table[]=
   {
    "no-atom",

    "(",
    ")",
    "*",
    "+",
    "x"
   };

  return Table[ac];
 }

