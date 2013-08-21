/* AMP.ddl */

include <../LangTypes.ddl>

Lang lang=
 {
   {
    { 0 , "(" },
    { 1 , ")" },
    { 2 , "*" },
    { 3 , "+" },
    { 4 , "x" }
   },
   {
    { 0 , "EXPR" ,
                   {
                    { 0 , "A" , lang.synts+0 },
                    { 1 , "M" , lang.synts+0 },
                    { 2 , "P" , lang.synts+0 }
                   } ,
                   {
                    lang.rules+0,
                    lang.rules+1,
                    lang.rules+2,
                    lang.rules+3
                   }
    }
   },
   {
    { 0 , lang.atoms+0 , null },
    { 1 , lang.atoms+1 , null },
    { 2 , lang.atoms+2 , null },
    { 3 , lang.atoms+3 , null },
    { 4 , lang.atoms+4 , null },
    { 5 , null , lang.synts[0].kinds+0 },
    { 6 , null , lang.synts[0].kinds+1 },
    { 7 , null , lang.synts[0].kinds+2 }
   },
   {
    { 0 , "opVar" , lang.synts[0].kinds+2 ,
                                            {
                                             { lang.atoms+4 , null }
                                            }
    },
    { 1 , "opBra" , lang.synts[0].kinds+2 ,
                                            {
                                             { lang.atoms+0 , null },
                                             { null , lang.synts+0 },
                                             { lang.atoms+1 , null }
                                            }
    },
    { 2 , "opAdd" , lang.synts[0].kinds+0 ,
                                            {
                                             { null , lang.synts+0 },
                                             { lang.atoms+3 , null },
                                             { null , lang.synts+0 }
                                            }
    },
    { 3 , "opMul" , lang.synts[0].kinds+1 ,
                                            {
                                             { null , lang.synts+0 },
                                             { lang.atoms+2 , null },
                                             { null , lang.synts+0 }
                                            }
    }
   },
   {
    { 0 , lang.finals+0 ,
                          {
                           { lang.elements+0 , lang.states+1 },
                           { lang.elements+4 , lang.states+17 },
                           { lang.elements+5 , lang.states+24 },
                           { lang.elements+6 , lang.states+24 },
                           { lang.elements+7 , lang.states+23 }
                          }
    },
    { 1 , lang.finals+0 ,
                          {
                           { lang.elements+0 , lang.states+4 },
                           { lang.elements+4 , lang.states+7 },
                           { lang.elements+5 , lang.states+16 },
                           { lang.elements+6 , lang.states+16 },
                           { lang.elements+7 , lang.states+14 }
                          }
    },
    { 2 , lang.finals+0 ,
                          {
                           { lang.elements+0 , lang.states+4 },
                           { lang.elements+4 , lang.states+7 },
                           { lang.elements+6 , lang.states+10 },
                           { lang.elements+7 , lang.states+9 }
                          }
    },
    { 3 , lang.finals+0 ,
                          {
                           { lang.elements+0 , lang.states+4 },
                           { lang.elements+4 , lang.states+7 },
                           { lang.elements+6 , lang.states+12 },
                           { lang.elements+7 , lang.states+11 }
                          }
    },
    { 4 , lang.finals+0 ,
                          {
                           { lang.elements+0 , lang.states+4 },
                           { lang.elements+4 , lang.states+7 },
                           { lang.elements+5 , lang.states+15 },
                           { lang.elements+6 , lang.states+15 },
                           { lang.elements+7 , lang.states+13 }
                          }
    },
    { 5 , lang.finals+0 ,
                          {
                           { lang.elements+0 , lang.states+1 },
                           { lang.elements+4 , lang.states+17 },
                           { lang.elements+6 , lang.states+20 },
                           { lang.elements+7 , lang.states+19 }
                          }
    },
    { 6 , lang.finals+0 ,
                          {
                           { lang.elements+0 , lang.states+1 },
                           { lang.elements+4 , lang.states+17 },
                           { lang.elements+6 , lang.states+22 },
                           { lang.elements+7 , lang.states+21 }
                          }
    },
    { 7 , lang.finals+1 ,
                          {
                           
                          }
    },
    { 8 , lang.finals+2 ,
                          {
                           
                          }
    },
    { 9 , lang.finals+3 ,
                          {
                           { lang.elements+2 , lang.states+3 }
                          }
    },
    { 10 , lang.finals+4 ,
                           {
                            
                           }
    },
    { 11 , lang.finals+5 ,
                           {
                            { lang.elements+2 , lang.states+3 }
                           }
    },
    { 12 , lang.finals+6 ,
                           {
                            
                           }
    },
    { 13 , lang.finals+7 ,
                           {
                            { lang.elements+1 , lang.states+8 },
                            { lang.elements+2 , lang.states+3 },
                            { lang.elements+3 , lang.states+2 }
                           }
    },
    { 14 , lang.finals+7 ,
                           {
                            { lang.elements+1 , lang.states+18 },
                            { lang.elements+2 , lang.states+3 },
                            { lang.elements+3 , lang.states+2 }
                           }
    },
    { 15 , lang.finals+8 ,
                           {
                            { lang.elements+1 , lang.states+8 },
                            { lang.elements+3 , lang.states+2 }
                           }
    },
    { 16 , lang.finals+8 ,
                           {
                            { lang.elements+1 , lang.states+18 },
                            { lang.elements+3 , lang.states+2 }
                           }
    },
    { 17 , lang.finals+9 ,
                           {
                            
                           }
    },
    { 18 , lang.finals+10 ,
                            {
                             
                            }
    },
    { 19 , lang.finals+11 ,
                            {
                             { lang.elements+2 , lang.states+6 }
                            }
    },
    { 20 , lang.finals+12 ,
                            {
                             
                            }
    },
    { 21 , lang.finals+13 ,
                            {
                             { lang.elements+2 , lang.states+6 }
                            }
    },
    { 22 , lang.finals+14 ,
                            {
                             
                            }
    },
    { 23 , lang.finals+15 ,
                            {
                             { lang.elements+2 , lang.states+6 },
                             { lang.elements+3 , lang.states+5 }
                            }
    },
    { 24 , lang.finals+16 ,
                            {
                             { lang.elements+3 , lang.states+5 }
                            }
    }
   },
   {
    { 0 ,
          {
           { lang.atoms+0 , null },
           { lang.atoms+4 , null }
          }
    },
    { 1 ,
          {
           { lang.atoms+1 , lang.rules+5 },
           { lang.atoms+2 , lang.rules+5 },
           { lang.atoms+3 , lang.rules+5 }
          }
    },
    { 2 ,
          {
           { lang.atoms+1 , lang.rules+6 },
           { lang.atoms+2 , lang.rules+6 },
           { lang.atoms+3 , lang.rules+6 }
          }
    },
    { 3 ,
          {
           { lang.atoms+1 , lang.rules+7 },
           { lang.atoms+2 , null },
           { lang.atoms+3 , lang.rules+7 }
          }
    },
    { 4 ,
          {
           { lang.atoms+1 , lang.rules+7 },
           { lang.atoms+3 , lang.rules+7 }
          }
    },
    { 5 ,
          {
           { lang.atoms+1 , lang.rules+8 },
           { lang.atoms+2 , null },
           { lang.atoms+3 , lang.rules+8 }
          }
    },
    { 6 ,
          {
           { lang.atoms+1 , lang.rules+8 },
           { lang.atoms+3 , lang.rules+8 }
          }
    },
    { 7 ,
          {
           { lang.atoms+1 , null },
           { lang.atoms+2 , null },
           { lang.atoms+3 , null }
          }
    },
    { 8 ,
          {
           { lang.atoms+1 , null },
           { lang.atoms+3 , null }
          }
    },
    { 9 ,
          {
           { null , lang.rules+5 },
           { lang.atoms+2 , lang.rules+5 },
           { lang.atoms+3 , lang.rules+5 }
          }
    },
    { 10 ,
           {
            { null , lang.rules+6 },
            { lang.atoms+2 , lang.rules+6 },
            { lang.atoms+3 , lang.rules+6 }
           }
    },
    { 11 ,
           {
            { null , lang.rules+7 },
            { lang.atoms+2 , null },
            { lang.atoms+3 , lang.rules+7 }
           }
    },
    { 12 ,
           {
            { null , lang.rules+7 },
            { lang.atoms+3 , lang.rules+7 }
           }
    },
    { 13 ,
           {
            { null , lang.rules+8 },
            { lang.atoms+2 , null },
            { lang.atoms+3 , lang.rules+8 }
           }
    },
    { 14 ,
           {
            { null , lang.rules+8 },
            { lang.atoms+3 , lang.rules+8 }
           }
    },
    { 15 ,
           {
            { null , null },
            { lang.atoms+2 , null },
            { lang.atoms+3 , null }
           }
    },
    { 16 ,
           {
            { null , null },
            { lang.atoms+3 , null }
           }
    }
   }
 };

