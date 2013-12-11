/* AMP.ddl */

//include <LangTypes.ddl>

Lang lang=
 {
   {
    { 0 , "(" , lang.elements+0 },
    { 1 , ")" , lang.elements+1 },
    { 2 , "*" , lang.elements+2 },
    { 3 , "+" , lang.elements+3 },
    { 4 , "x" , lang.elements+4 }
   },
   {
    { 0 , "EXPR" ,
                   {
                    { 0 , 0 , "A" , lang.synts+0 , lang.elements+5 ,
                                                                     {
                                                                      lang.top_rules+0,
                                                                      lang.top_rules+1,
                                                                      lang.top_rules+2,
                                                                      lang.top_rules+3,
                                                                      lang.top_rules+4,
                                                                      lang.top_rules+5
                                                                     }
                    },
                    { 1 , 1 , "M" , lang.synts+0 , lang.elements+6 ,
                                                                     {
                                                                      lang.top_rules+6,
                                                                      lang.top_rules+7
                                                                     }
                    },
                    { 2 , 2 , "P" , lang.synts+0 , lang.elements+7 ,
                                                                     {
                                                                      lang.top_rules+8,
                                                                      lang.top_rules+9,
                                                                      lang.top_rules+10,
                                                                      lang.top_rules+11
                                                                     }
                    }
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
    lang.synts+0
   },
   {
    { 0 , lang.atoms+0 },
    { 1 , lang.atoms+1 },
    { 2 , lang.atoms+2 },
    { 3 , lang.atoms+3 },
    { 4 , lang.atoms+4 },
    { 5 , lang.synts[0].kinds+0 },
    { 6 , lang.synts[0].kinds+1 },
    { 7 , lang.synts[0].kinds+2 }
   },
   {
    { 0 , "opVar" , lang.synts[0].kinds+2 ,
                                            {
                                             lang.atoms+4
                                            }
    },
    { 1 , "opBra" , lang.synts[0].kinds+2 ,
                                            {
                                             lang.atoms+0,
                                             lang.synts+0,
                                             lang.atoms+1
                                            }
    },
    { 2 , "opAdd" , lang.synts[0].kinds+0 ,
                                            {
                                             lang.synts+0,
                                             lang.atoms+3,
                                             lang.synts+0
                                            }
    },
    { 3 , "opMul" , lang.synts[0].kinds+1 ,
                                            {
                                             lang.synts+0,
                                             lang.atoms+2,
                                             lang.synts+0
                                            }
    }
   },
   {
    { 0 , "opAdd.A.M" , lang.rules+2 , lang.synts[0].kinds+0 ,
                                                               {
                                                                lang.synts[0].kinds+0,
                                                                lang.atoms+3,
                                                                lang.synts[0].kinds+1
                                                               }
    },
    { 1 , "opAdd.M.M" , lang.rules+2 , lang.synts[0].kinds+0 ,
                                                               {
                                                                lang.synts[0].kinds+1,
                                                                lang.atoms+3,
                                                                lang.synts[0].kinds+1
                                                               }
    },
    { 2 , "opAdd.P.M" , lang.rules+2 , lang.synts[0].kinds+0 ,
                                                               {
                                                                lang.synts[0].kinds+2,
                                                                lang.atoms+3,
                                                                lang.synts[0].kinds+1
                                                               }
    },
    { 3 , "opAdd.A.P" , lang.rules+2 , lang.synts[0].kinds+0 ,
                                                               {
                                                                lang.synts[0].kinds+0,
                                                                lang.atoms+3,
                                                                lang.synts[0].kinds+2
                                                               }
    },
    { 4 , "opAdd.M.P" , lang.rules+2 , lang.synts[0].kinds+0 ,
                                                               {
                                                                lang.synts[0].kinds+1,
                                                                lang.atoms+3,
                                                                lang.synts[0].kinds+2
                                                               }
    },
    { 5 , "opAdd.P.P" , lang.rules+2 , lang.synts[0].kinds+0 ,
                                                               {
                                                                lang.synts[0].kinds+2,
                                                                lang.atoms+3,
                                                                lang.synts[0].kinds+2
                                                               }
    },
    { 6 , "opMul.P.M" , lang.rules+3 , lang.synts[0].kinds+1 ,
                                                               {
                                                                lang.synts[0].kinds+2,
                                                                lang.atoms+2,
                                                                lang.synts[0].kinds+1
                                                               }
    },
    { 7 , "opMul.P.P" , lang.rules+3 , lang.synts[0].kinds+1 ,
                                                               {
                                                                lang.synts[0].kinds+2,
                                                                lang.atoms+2,
                                                                lang.synts[0].kinds+2
                                                               }
    },
    { 8 , "opVar" , lang.rules+0 , lang.synts[0].kinds+2 ,
                                                           {
                                                            lang.atoms+4
                                                           }
    },
    { 9 , "opBra.A" , lang.rules+1 , lang.synts[0].kinds+2 ,
                                                             {
                                                              lang.atoms+0,
                                                              lang.synts[0].kinds+0,
                                                              lang.atoms+1
                                                             }
    },
    { 10 , "opBra.M" , lang.rules+1 , lang.synts[0].kinds+2 ,
                                                              {
                                                               lang.atoms+0,
                                                               lang.synts[0].kinds+1,
                                                               lang.atoms+1
                                                              }
    },
    { 11 , "opBra.P" , lang.rules+1 , lang.synts[0].kinds+2 ,
                                                              {
                                                               lang.atoms+0,
                                                               lang.synts[0].kinds+2,
                                                               lang.atoms+1
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
           { lang.atoms+1 , lang.rules+0 },
           { lang.atoms+2 , lang.rules+0 },
           { lang.atoms+3 , lang.rules+0 }
          }
    },
    { 2 ,
          {
           { lang.atoms+1 , lang.rules+1 },
           { lang.atoms+2 , lang.rules+1 },
           { lang.atoms+3 , lang.rules+1 }
          }
    },
    { 3 ,
          {
           { lang.atoms+1 , lang.rules+2 },
           { lang.atoms+2 , null },
           { lang.atoms+3 , lang.rules+2 }
          }
    },
    { 4 ,
          {
           { lang.atoms+1 , lang.rules+2 },
           { lang.atoms+3 , lang.rules+2 }
          }
    },
    { 5 ,
          {
           { lang.atoms+1 , lang.rules+3 },
           { lang.atoms+2 , null },
           { lang.atoms+3 , lang.rules+3 }
          }
    },
    { 6 ,
          {
           { lang.atoms+1 , lang.rules+3 },
           { lang.atoms+3 , lang.rules+3 }
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
           { null , lang.rules+0 },
           { lang.atoms+2 , lang.rules+0 },
           { lang.atoms+3 , lang.rules+0 }
          }
    },
    { 10 ,
           {
            { null , lang.rules+1 },
            { lang.atoms+2 , lang.rules+1 },
            { lang.atoms+3 , lang.rules+1 }
           }
    },
    { 11 ,
           {
            { null , lang.rules+2 },
            { lang.atoms+2 , null },
            { lang.atoms+3 , lang.rules+2 }
           }
    },
    { 12 ,
           {
            { null , lang.rules+2 },
            { lang.atoms+3 , lang.rules+2 }
           }
    },
    { 13 ,
           {
            { null , lang.rules+3 },
            { lang.atoms+2 , null },
            { lang.atoms+3 , lang.rules+3 }
           }
    },
    { 14 ,
           {
            { null , lang.rules+3 },
            { lang.atoms+3 , lang.rules+3 }
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

