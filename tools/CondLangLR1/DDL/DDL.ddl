/* DDL.ddl */

//include <LangTypes.ddl>

Lang lang=
 {
   {
    { 0 , "#" , lang.elements+0 },
    { 1 , "%" , lang.elements+1 },
    { 2 , "&" , lang.elements+2 },
    { 3 , "(" , lang.elements+3 },
    { 4 , ")" , lang.elements+4 },
    { 5 , "*" , lang.elements+5 },
    { 6 , "+" , lang.elements+6 },
    { 7 , "," , lang.elements+7 },
    { 8 , "-" , lang.elements+8 },
    { 9 , "->" , lang.elements+9 },
    { 10 , "." , lang.elements+10 },
    { 11 , "/" , lang.elements+11 },
    { 12 , ";" , lang.elements+12 },
    { 13 , "=" , lang.elements+13 },
    { 14 , "Dots" , lang.elements+14 },
    { 15 , "FileName" , lang.elements+15 },
    { 16 , "Name" , lang.elements+16 },
    { 17 , "Number" , lang.elements+17 },
    { 18 , "String" , lang.elements+18 },
    { 19 , "[" , lang.elements+19 },
    { 20 , "]" , lang.elements+20 },
    { 21 , "const" , lang.elements+21 },
    { 22 , "include" , lang.elements+22 },
    { 23 , "int" , lang.elements+23 },
    { 24 , "ip" , lang.elements+24 },
    { 25 , "null" , lang.elements+25 },
    { 26 , "scope" , lang.elements+26 },
    { 27 , "sint" , lang.elements+27 },
    { 28 , "sint16" , lang.elements+28 },
    { 29 , "sint32" , lang.elements+29 },
    { 30 , "sint64" , lang.elements+30 },
    { 31 , "sint8" , lang.elements+31 },
    { 32 , "struct" , lang.elements+32 },
    { 33 , "text" , lang.elements+33 },
    { 34 , "type" , lang.elements+34 },
    { 35 , "uint" , lang.elements+35 },
    { 36 , "uint16" , lang.elements+36 },
    { 37 , "uint32" , lang.elements+37 },
    { 38 , "uint64" , lang.elements+38 },
    { 39 , "uint8" , lang.elements+39 },
    { 40 , "ulen" , lang.elements+40 },
    { 41 , "{" , lang.elements+41 },
    { 42 , "}" , lang.elements+42 }
   },
   {
    { 0 , "BODY" , { { 0 , 0 , "" , lang.synts+0 , lang.elements+43 ,
                                                                      {
                                                                       lang.top_rules+0,
                                                                       lang.top_rules+1,
                                                                       lang.top_rules+2,
                                                                       lang.top_rules+3,
                                                                       lang.top_rules+4,
                                                                       lang.top_rules+5
                                                                      }
                     }
                   } ,
                   {
                    lang.rules+0,
                    lang.rules+1,
                    lang.rules+2,
                    lang.rules+3,
                    lang.rules+4,
                    lang.rules+5
                   }
    },
    { 1 , "SCOPE" , { { 1 , 0 , "" , lang.synts+1 , lang.elements+44 ,
                                                                       {
                                                                        lang.top_rules+6
                                                                       }
                      }
                    } ,
                    {
                     lang.rules+6
                    }
    },
    { 2 , "INCLUDE" , { { 2 , 0 , "" , lang.synts+2 , lang.elements+45 ,
                                                                         {
                                                                          lang.top_rules+7
                                                                         }
                        }
                      } ,
                      {
                       lang.rules+7
                      }
    },
    { 3 , "TYPE" , { { 3 , 0 , "" , lang.synts+3 , lang.elements+46 ,
                                                                      {
                                                                       lang.top_rules+8
                                                                      }
                     }
                   } ,
                   {
                    lang.rules+8
                   }
    },
    { 4 , "CONST" , { { 4 , 0 , "" , lang.synts+4 , lang.elements+47 ,
                                                                       {
                                                                        lang.top_rules+9,
                                                                        lang.top_rules+10,
                                                                        lang.top_rules+11,
                                                                        lang.top_rules+12,
                                                                        lang.top_rules+13,
                                                                        lang.top_rules+14,
                                                                        lang.top_rules+15
                                                                       }
                      }
                    } ,
                    {
                     lang.rules+9
                    }
    },
    { 5 , "RNAME" , { { 5 , 0 , "" , lang.synts+5 , lang.elements+48 ,
                                                                       {
                                                                        lang.top_rules+16,
                                                                        lang.top_rules+17
                                                                       }
                      }
                    } ,
                    {
                     lang.rules+10,
                     lang.rules+11
                    }
    },
    { 6 , "NAME" , { { 6 , 0 , "" , lang.synts+6 , lang.elements+49 ,
                                                                      {
                                                                       lang.top_rules+18,
                                                                       lang.top_rules+19,
                                                                       lang.top_rules+20,
                                                                       lang.top_rules+21
                                                                      }
                     }
                   } ,
                   {
                    lang.rules+12,
                    lang.rules+13,
                    lang.rules+14,
                    lang.rules+15
                   }
    },
    { 7 , "INAME" , { { 7 , 0 , "" , lang.synts+7 , lang.elements+50 ,
                                                                       {
                                                                        lang.top_rules+22,
                                                                        lang.top_rules+23,
                                                                        lang.top_rules+24,
                                                                        lang.top_rules+25,
                                                                        lang.top_rules+26,
                                                                        lang.top_rules+27,
                                                                        lang.top_rules+28,
                                                                        lang.top_rules+29,
                                                                        lang.top_rules+30,
                                                                        lang.top_rules+31,
                                                                        lang.top_rules+32,
                                                                        lang.top_rules+33
                                                                       }
                      }
                    } ,
                    {
                     lang.rules+16,
                     lang.rules+17,
                     lang.rules+18,
                     lang.rules+19,
                     lang.rules+20,
                     lang.rules+21,
                     lang.rules+22,
                     lang.rules+23,
                     lang.rules+24,
                     lang.rules+25,
                     lang.rules+26,
                     lang.rules+27
                    }
    },
    { 8 , "TNAME" , { { 8 , 0 , "" , lang.synts+8 , lang.elements+51 ,
                                                                       {
                                                                        lang.top_rules+34,
                                                                        lang.top_rules+35,
                                                                        lang.top_rules+36
                                                                       }
                      }
                    } ,
                    {
                     lang.rules+28,
                     lang.rules+29,
                     lang.rules+30
                    }
    },
    { 9 , "TYPEDEF" , { { 9 , 0 , "" , lang.synts+9 , lang.elements+52 ,
                                                                         {
                                                                          lang.top_rules+37,
                                                                          lang.top_rules+38,
                                                                          lang.top_rules+39,
                                                                          lang.top_rules+40,
                                                                          lang.top_rules+41,
                                                                          lang.top_rules+42,
                                                                          lang.top_rules+43,
                                                                          lang.top_rules+44,
                                                                          lang.top_rules+45,
                                                                          lang.top_rules+46,
                                                                          lang.top_rules+47,
                                                                          lang.top_rules+48
                                                                         }
                        }
                      } ,
                      {
                       lang.rules+31,
                       lang.rules+32,
                       lang.rules+33,
                       lang.rules+34,
                       lang.rules+35,
                       lang.rules+36
                      }
    },
    { 10 , "STRUCT" , { { 10 , 0 , "" , lang.synts+10 , lang.elements+53 ,
                                                                           {
                                                                            lang.top_rules+49
                                                                           }
                        }
                      } ,
                      {
                       lang.rules+37
                      }
    },
    { 11 , "SBODY" , { { 11 , 0 , "" , lang.synts+11 , lang.elements+54 ,
                                                                          {
                                                                           lang.top_rules+50,
                                                                           lang.top_rules+51,
                                                                           lang.top_rules+52,
                                                                           lang.top_rules+53,
                                                                           lang.top_rules+54,
                                                                           lang.top_rules+55,
                                                                           lang.top_rules+56,
                                                                           lang.top_rules+57,
                                                                           lang.top_rules+58,
                                                                           lang.top_rules+59,
                                                                           lang.top_rules+60,
                                                                           lang.top_rules+61
                                                                          }
                       }
                     } ,
                     {
                      lang.rules+38,
                      lang.rules+39,
                      lang.rules+40,
                      lang.rules+41,
                      lang.rules+42,
                      lang.rules+43
                     }
    },
    { 12 , "EXPR" ,
                    {
                     { 12 , 0 , "LIST" , lang.synts+12 , lang.elements+55 ,
                                                                            {
                                                                             lang.top_rules+62,
                                                                             lang.top_rules+63,
                                                                             lang.top_rules+64,
                                                                             lang.top_rules+65,
                                                                             lang.top_rules+66,
                                                                             lang.top_rules+67,
                                                                             lang.top_rules+68,
                                                                             lang.top_rules+69,
                                                                             lang.top_rules+70,
                                                                             lang.top_rules+71,
                                                                             lang.top_rules+72,
                                                                             lang.top_rules+73,
                                                                             lang.top_rules+74,
                                                                             lang.top_rules+75,
                                                                             lang.top_rules+76,
                                                                             lang.top_rules+77,
                                                                             lang.top_rules+78
                                                                            }
                     },
                     { 13 , 1 , "ADD" , lang.synts+12 , lang.elements+56 ,
                                                                           {
                                                                            lang.top_rules+79,
                                                                            lang.top_rules+80,
                                                                            lang.top_rules+81,
                                                                            lang.top_rules+82,
                                                                            lang.top_rules+83,
                                                                            lang.top_rules+84,
                                                                            lang.top_rules+85,
                                                                            lang.top_rules+86,
                                                                            lang.top_rules+87,
                                                                            lang.top_rules+88,
                                                                            lang.top_rules+89,
                                                                            lang.top_rules+90,
                                                                            lang.top_rules+91,
                                                                            lang.top_rules+92,
                                                                            lang.top_rules+93,
                                                                            lang.top_rules+94,
                                                                            lang.top_rules+95,
                                                                            lang.top_rules+96,
                                                                            lang.top_rules+97,
                                                                            lang.top_rules+98,
                                                                            lang.top_rules+99,
                                                                            lang.top_rules+100,
                                                                            lang.top_rules+101,
                                                                            lang.top_rules+102,
                                                                            lang.top_rules+103,
                                                                            lang.top_rules+104,
                                                                            lang.top_rules+105,
                                                                            lang.top_rules+106,
                                                                            lang.top_rules+107,
                                                                            lang.top_rules+108,
                                                                            lang.top_rules+109,
                                                                            lang.top_rules+110,
                                                                            lang.top_rules+111,
                                                                            lang.top_rules+112,
                                                                            lang.top_rules+113,
                                                                            lang.top_rules+114,
                                                                            lang.top_rules+115,
                                                                            lang.top_rules+116,
                                                                            lang.top_rules+117,
                                                                            lang.top_rules+118,
                                                                            lang.top_rules+119,
                                                                            lang.top_rules+120,
                                                                            lang.top_rules+121,
                                                                            lang.top_rules+122,
                                                                            lang.top_rules+123,
                                                                            lang.top_rules+124,
                                                                            lang.top_rules+125,
                                                                            lang.top_rules+126,
                                                                            lang.top_rules+127,
                                                                            lang.top_rules+128,
                                                                            lang.top_rules+129,
                                                                            lang.top_rules+130,
                                                                            lang.top_rules+131,
                                                                            lang.top_rules+132,
                                                                            lang.top_rules+133,
                                                                            lang.top_rules+134,
                                                                            lang.top_rules+135,
                                                                            lang.top_rules+136,
                                                                            lang.top_rules+137,
                                                                            lang.top_rules+138
                                                                           }
                     },
                     { 14 , 2 , "MUL" , lang.synts+12 , lang.elements+57 ,
                                                                           {
                                                                            lang.top_rules+139,
                                                                            lang.top_rules+140,
                                                                            lang.top_rules+141,
                                                                            lang.top_rules+142,
                                                                            lang.top_rules+143,
                                                                            lang.top_rules+144,
                                                                            lang.top_rules+145,
                                                                            lang.top_rules+146,
                                                                            lang.top_rules+147,
                                                                            lang.top_rules+148,
                                                                            lang.top_rules+149,
                                                                            lang.top_rules+150,
                                                                            lang.top_rules+151,
                                                                            lang.top_rules+152,
                                                                            lang.top_rules+153,
                                                                            lang.top_rules+154,
                                                                            lang.top_rules+155,
                                                                            lang.top_rules+156,
                                                                            lang.top_rules+157,
                                                                            lang.top_rules+158,
                                                                            lang.top_rules+159,
                                                                            lang.top_rules+160,
                                                                            lang.top_rules+161,
                                                                            lang.top_rules+162,
                                                                            lang.top_rules+163,
                                                                            lang.top_rules+164,
                                                                            lang.top_rules+165,
                                                                            lang.top_rules+166,
                                                                            lang.top_rules+167,
                                                                            lang.top_rules+168,
                                                                            lang.top_rules+169,
                                                                            lang.top_rules+170,
                                                                            lang.top_rules+171,
                                                                            lang.top_rules+172,
                                                                            lang.top_rules+173,
                                                                            lang.top_rules+174,
                                                                            lang.top_rules+175,
                                                                            lang.top_rules+176,
                                                                            lang.top_rules+177,
                                                                            lang.top_rules+178,
                                                                            lang.top_rules+179,
                                                                            lang.top_rules+180,
                                                                            lang.top_rules+181,
                                                                            lang.top_rules+182,
                                                                            lang.top_rules+183,
                                                                            lang.top_rules+184,
                                                                            lang.top_rules+185,
                                                                            lang.top_rules+186,
                                                                            lang.top_rules+187,
                                                                            lang.top_rules+188,
                                                                            lang.top_rules+189,
                                                                            lang.top_rules+190,
                                                                            lang.top_rules+191,
                                                                            lang.top_rules+192,
                                                                            lang.top_rules+193,
                                                                            lang.top_rules+194,
                                                                            lang.top_rules+195,
                                                                            lang.top_rules+196,
                                                                            lang.top_rules+197,
                                                                            lang.top_rules+198
                                                                           }
                     },
                     { 15 , 3 , "UN" , lang.synts+12 , lang.elements+58 ,
                                                                          {
                                                                           lang.top_rules+199,
                                                                           lang.top_rules+200,
                                                                           lang.top_rules+201,
                                                                           lang.top_rules+202,
                                                                           lang.top_rules+203,
                                                                           lang.top_rules+204,
                                                                           lang.top_rules+205,
                                                                           lang.top_rules+206,
                                                                           lang.top_rules+207,
                                                                           lang.top_rules+208,
                                                                           lang.top_rules+209,
                                                                           lang.top_rules+210,
                                                                           lang.top_rules+211,
                                                                           lang.top_rules+212,
                                                                           lang.top_rules+213,
                                                                           lang.top_rules+214
                                                                          }
                     },
                     { 16 , 4 , "NUM" , lang.synts+12 , lang.elements+59 ,
                                                                           {
                                                                            lang.top_rules+215
                                                                           }
                     },
                     { 17 , 5 , "POST" , lang.synts+12 , lang.elements+60 ,
                                                                            {
                                                                             lang.top_rules+216,
                                                                             lang.top_rules+217,
                                                                             lang.top_rules+218,
                                                                             lang.top_rules+219,
                                                                             lang.top_rules+220,
                                                                             lang.top_rules+221,
                                                                             lang.top_rules+222,
                                                                             lang.top_rules+223,
                                                                             lang.top_rules+224,
                                                                             lang.top_rules+225,
                                                                             lang.top_rules+226,
                                                                             lang.top_rules+227,
                                                                             lang.top_rules+228,
                                                                             lang.top_rules+229,
                                                                             lang.top_rules+230,
                                                                             lang.top_rules+231,
                                                                             lang.top_rules+232,
                                                                             lang.top_rules+233,
                                                                             lang.top_rules+234,
                                                                             lang.top_rules+235,
                                                                             lang.top_rules+236,
                                                                             lang.top_rules+237,
                                                                             lang.top_rules+238,
                                                                             lang.top_rules+239,
                                                                             lang.top_rules+240
                                                                            }
                     },
                     { 18 , 6 , "PRIM" , lang.synts+12 , lang.elements+61 ,
                                                                            {
                                                                             lang.top_rules+241,
                                                                             lang.top_rules+242,
                                                                             lang.top_rules+243,
                                                                             lang.top_rules+244,
                                                                             lang.top_rules+245,
                                                                             lang.top_rules+246,
                                                                             lang.top_rules+247,
                                                                             lang.top_rules+248,
                                                                             lang.top_rules+249,
                                                                             lang.top_rules+250,
                                                                             lang.top_rules+251,
                                                                             lang.top_rules+252,
                                                                             lang.top_rules+253,
                                                                             lang.top_rules+254,
                                                                             lang.top_rules+255,
                                                                             lang.top_rules+256
                                                                            }
                     }
                    } ,
                    {
                     lang.rules+44,
                     lang.rules+45,
                     lang.rules+46,
                     lang.rules+47,
                     lang.rules+48,
                     lang.rules+49,
                     lang.rules+50,
                     lang.rules+51,
                     lang.rules+52,
                     lang.rules+53,
                     lang.rules+54,
                     lang.rules+55,
                     lang.rules+56,
                     lang.rules+57,
                     lang.rules+58,
                     lang.rules+59,
                     lang.rules+60,
                     lang.rules+61,
                     lang.rules+62,
                     lang.rules+63,
                     lang.rules+64,
                     lang.rules+65
                    }
    },
    { 13 , "ELIST" , { { 19 , 0 , "" , lang.synts+13 , lang.elements+62 ,
                                                                          {
                                                                           lang.top_rules+257,
                                                                           lang.top_rules+258,
                                                                           lang.top_rules+259,
                                                                           lang.top_rules+260,
                                                                           lang.top_rules+261,
                                                                           lang.top_rules+262,
                                                                           lang.top_rules+263,
                                                                           lang.top_rules+264,
                                                                           lang.top_rules+265,
                                                                           lang.top_rules+266,
                                                                           lang.top_rules+267,
                                                                           lang.top_rules+268,
                                                                           lang.top_rules+269,
                                                                           lang.top_rules+270
                                                                          }
                       }
                     } ,
                     {
                      lang.rules+66,
                      lang.rules+67
                     }
    },
    { 14 , "NEXPR" , { { 20 , 0 , "" , lang.synts+14 , lang.elements+63 ,
                                                                          {
                                                                           lang.top_rules+271,
                                                                           lang.top_rules+272,
                                                                           lang.top_rules+273,
                                                                           lang.top_rules+274,
                                                                           lang.top_rules+275,
                                                                           lang.top_rules+276,
                                                                           lang.top_rules+277
                                                                          }
                       }
                     } ,
                     {
                      lang.rules+68
                     }
    },
    { 15 , "NELIST" , { { 21 , 0 , "" , lang.synts+15 , lang.elements+64 ,
                                                                           {
                                                                            lang.top_rules+278,
                                                                            lang.top_rules+279
                                                                           }
                        }
                      } ,
                      {
                       lang.rules+69,
                       lang.rules+70
                      }
    },
    { 16 , "ITYPE" , { { 22 , 0 , "" , lang.synts+16 , lang.elements+65 ,
                                                                          {
                                                                           lang.top_rules+280,
                                                                           lang.top_rules+281
                                                                          }
                       }
                     } ,
                     {
                      lang.rules+71,
                      lang.rules+72
                     }
    },
    { 17 , "NNLIT" , { { 23 , 0 , "" , lang.synts+17 , lang.elements+66 ,
                                                                          {
                                                                           lang.top_rules+282,
                                                                           lang.top_rules+283,
                                                                           lang.top_rules+284
                                                                          }
                       }
                     } ,
                     {
                      lang.rules+73,
                      lang.rules+74,
                      lang.rules+75
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
    { 5 , lang.atoms+5 },
    { 6 , lang.atoms+6 },
    { 7 , lang.atoms+7 },
    { 8 , lang.atoms+8 },
    { 9 , lang.atoms+9 },
    { 10 , lang.atoms+10 },
    { 11 , lang.atoms+11 },
    { 12 , lang.atoms+12 },
    { 13 , lang.atoms+13 },
    { 14 , lang.atoms+14 },
    { 15 , lang.atoms+15 },
    { 16 , lang.atoms+16 },
    { 17 , lang.atoms+17 },
    { 18 , lang.atoms+18 },
    { 19 , lang.atoms+19 },
    { 20 , lang.atoms+20 },
    { 21 , lang.atoms+21 },
    { 22 , lang.atoms+22 },
    { 23 , lang.atoms+23 },
    { 24 , lang.atoms+24 },
    { 25 , lang.atoms+25 },
    { 26 , lang.atoms+26 },
    { 27 , lang.atoms+27 },
    { 28 , lang.atoms+28 },
    { 29 , lang.atoms+29 },
    { 30 , lang.atoms+30 },
    { 31 , lang.atoms+31 },
    { 32 , lang.atoms+32 },
    { 33 , lang.atoms+33 },
    { 34 , lang.atoms+34 },
    { 35 , lang.atoms+35 },
    { 36 , lang.atoms+36 },
    { 37 , lang.atoms+37 },
    { 38 , lang.atoms+38 },
    { 39 , lang.atoms+39 },
    { 40 , lang.atoms+40 },
    { 41 , lang.atoms+41 },
    { 42 , lang.atoms+42 },
    { 43 , lang.synts[0].kinds+0 },
    { 44 , lang.synts[1].kinds+0 },
    { 45 , lang.synts[2].kinds+0 },
    { 46 , lang.synts[3].kinds+0 },
    { 47 , lang.synts[4].kinds+0 },
    { 48 , lang.synts[5].kinds+0 },
    { 49 , lang.synts[6].kinds+0 },
    { 50 , lang.synts[7].kinds+0 },
    { 51 , lang.synts[8].kinds+0 },
    { 52 , lang.synts[9].kinds+0 },
    { 53 , lang.synts[10].kinds+0 },
    { 54 , lang.synts[11].kinds+0 },
    { 55 , lang.synts[12].kinds+0 },
    { 56 , lang.synts[12].kinds+1 },
    { 57 , lang.synts[12].kinds+2 },
    { 58 , lang.synts[12].kinds+3 },
    { 59 , lang.synts[12].kinds+4 },
    { 60 , lang.synts[12].kinds+5 },
    { 61 , lang.synts[12].kinds+6 },
    { 62 , lang.synts[13].kinds+0 },
    { 63 , lang.synts[14].kinds+0 },
    { 64 , lang.synts[15].kinds+0 },
    { 65 , lang.synts[16].kinds+0 },
    { 66 , lang.synts[17].kinds+0 }
   },
   {
    { 0 , "start" , lang.synts[0].kinds+0 ,
                                            {
                                             
                                            }
    },
    { 1 , "ext_SCOPE" , lang.synts[0].kinds+0 ,
                                                {
                                                 lang.synts+0,
                                                 lang.synts+1
                                                }
    },
    { 2 , "ext_INCLUDE" , lang.synts[0].kinds+0 ,
                                                  {
                                                   lang.synts+0,
                                                   lang.synts+2
                                                  }
    },
    { 3 , "ext_TYPE" , lang.synts[0].kinds+0 ,
                                               {
                                                lang.synts+0,
                                                lang.synts+3
                                               }
    },
    { 4 , "ext_CONST" , lang.synts[0].kinds+0 ,
                                                {
                                                 lang.synts+0,
                                                 lang.synts+4
                                                }
    },
    { 5 , "ext_STRUCT" , lang.synts[0].kinds+0 ,
                                                 {
                                                  lang.synts+0,
                                                  lang.synts+10,
                                                  lang.atoms+12
                                                 }
    },
    { 6 , "build" , lang.synts[1].kinds+0 ,
                                            {
                                             lang.atoms+26,
                                             lang.atoms+16,
                                             lang.atoms+41,
                                             lang.synts+0,
                                             lang.atoms+42
                                            }
    },
    { 7 , "includeFile" , lang.synts[2].kinds+0 ,
                                                  {
                                                   lang.atoms+22,
                                                   lang.atoms+15
                                                  }
    },
    { 8 , "build" , lang.synts[3].kinds+0 ,
                                            {
                                             lang.atoms+34,
                                             lang.atoms+16,
                                             lang.atoms+13,
                                             lang.synts+9,
                                             lang.atoms+12
                                            }
    },
    { 9 , "build" , lang.synts[4].kinds+0 ,
                                            {
                                             lang.synts+9,
                                             lang.atoms+16,
                                             lang.atoms+13,
                                             lang.synts+12,
                                             lang.atoms+12
                                            }
    },
    { 10 , "start" , lang.synts[5].kinds+0 ,
                                             {
                                              lang.atoms+16
                                             }
    },
    { 11 , "ext" , lang.synts[5].kinds+0 ,
                                           {
                                            lang.synts+5,
                                            lang.atoms+0,
                                            lang.atoms+16
                                           }
    },
    { 12 , "rel" , lang.synts[6].kinds+0 ,
                                           {
                                            lang.synts+5
                                           }
    },
    { 13 , "abs" , lang.synts[6].kinds+0 ,
                                           {
                                            lang.atoms+0,
                                            lang.synts+5
                                           }
    },
    { 14 , "dot" , lang.synts[6].kinds+0 ,
                                           {
                                            lang.atoms+10,
                                            lang.atoms+0,
                                            lang.synts+5
                                           }
    },
    { 15 , "dots" , lang.synts[6].kinds+0 ,
                                            {
                                             lang.atoms+14,
                                             lang.atoms+0,
                                             lang.synts+5
                                            }
    },
    { 16 , "intName" , lang.synts[7].kinds+0 ,
                                               {
                                                lang.atoms+23
                                               }
    },
    { 17 , "sintName" , lang.synts[7].kinds+0 ,
                                                {
                                                 lang.atoms+27
                                                }
    },
    { 18 , "uintName" , lang.synts[7].kinds+0 ,
                                                {
                                                 lang.atoms+35
                                                }
    },
    { 19 , "ulenName" , lang.synts[7].kinds+0 ,
                                                {
                                                 lang.atoms+40
                                                }
    },
    { 20 , "sint8Name" , lang.synts[7].kinds+0 ,
                                                 {
                                                  lang.atoms+31
                                                 }
    },
    { 21 , "uint8Name" , lang.synts[7].kinds+0 ,
                                                 {
                                                  lang.atoms+39
                                                 }
    },
    { 22 , "sint16Name" , lang.synts[7].kinds+0 ,
                                                  {
                                                   lang.atoms+28
                                                  }
    },
    { 23 , "uint16Name" , lang.synts[7].kinds+0 ,
                                                  {
                                                   lang.atoms+36
                                                  }
    },
    { 24 , "sint32Name" , lang.synts[7].kinds+0 ,
                                                  {
                                                   lang.atoms+29
                                                  }
    },
    { 25 , "uint32Name" , lang.synts[7].kinds+0 ,
                                                  {
                                                   lang.atoms+37
                                                  }
    },
    { 26 , "sint64Name" , lang.synts[7].kinds+0 ,
                                                  {
                                                   lang.atoms+30
                                                  }
    },
    { 27 , "uint64Name" , lang.synts[7].kinds+0 ,
                                                  {
                                                   lang.atoms+38
                                                  }
    },
    { 28 , "cast" , lang.synts[8].kinds+0 ,
                                            {
                                             lang.synts+7
                                            }
    },
    { 29 , "text" , lang.synts[8].kinds+0 ,
                                            {
                                             lang.atoms+33
                                            }
    },
    { 30 , "ip" , lang.synts[8].kinds+0 ,
                                          {
                                           lang.atoms+24
                                          }
    },
    { 31 , "namedType" , lang.synts[9].kinds+0 ,
                                                 {
                                                  lang.synts+6
                                                 }
    },
    { 32 , "baseType" , lang.synts[9].kinds+0 ,
                                                {
                                                 lang.synts+8
                                                }
    },
    { 33 , "ptrType" , lang.synts[9].kinds+0 ,
                                               {
                                                lang.synts+9,
                                                lang.atoms+5
                                               }
    },
    { 34 , "arrayType" , lang.synts[9].kinds+0 ,
                                                 {
                                                  lang.synts+9,
                                                  lang.atoms+19,
                                                  lang.atoms+20
                                                 }
    },
    { 35 , "arrayLenType" , lang.synts[9].kinds+0 ,
                                                    {
                                                     lang.synts+9,
                                                     lang.atoms+19,
                                                     lang.synts+12,
                                                     lang.atoms+20
                                                    }
    },
    { 36 , "structType" , lang.synts[9].kinds+0 ,
                                                  {
                                                   lang.synts+10
                                                  }
    },
    { 37 , "build" , lang.synts[10].kinds+0 ,
                                              {
                                               lang.atoms+32,
                                               lang.atoms+16,
                                               lang.atoms+41,
                                               lang.synts+11,
                                               lang.atoms+42
                                              }
    },
    { 38 , "start" , lang.synts[11].kinds+0 ,
                                              {
                                               
                                              }
    },
    { 39 , "ext_TYPE" , lang.synts[11].kinds+0 ,
                                                 {
                                                  lang.synts+11,
                                                  lang.synts+3
                                                 }
    },
    { 40 , "ext_CONST" , lang.synts[11].kinds+0 ,
                                                  {
                                                   lang.synts+11,
                                                   lang.atoms+21,
                                                   lang.synts+4
                                                  }
    },
    { 41 , "ext_STRUCT" , lang.synts[11].kinds+0 ,
                                                   {
                                                    lang.synts+11,
                                                    lang.synts+10,
                                                    lang.atoms+12
                                                   }
    },
    { 42 , "ext_field" , lang.synts[11].kinds+0 ,
                                                  {
                                                   lang.synts+11,
                                                   lang.synts+9,
                                                   lang.atoms+16,
                                                   lang.atoms+12
                                                  }
    },
    { 43 , "ext_fieldVal" , lang.synts[11].kinds+0 ,
                                                     {
                                                      lang.synts+11,
                                                      lang.synts+9,
                                                      lang.atoms+16,
                                                      lang.atoms+13,
                                                      lang.synts+12,
                                                      lang.atoms+12
                                                     }
    },
    { 44 , "cast_EXPR" , lang.synts[12].kinds+6 ,
                                                  {
                                                   lang.atoms+3,
                                                   lang.synts+12,
                                                   lang.atoms+4
                                                  }
    },
    { 45 , "cast_NAME" , lang.synts[12].kinds+6 ,
                                                  {
                                                   lang.synts+6
                                                  }
    },
    { 46 , "cast_NNLIT" , lang.synts[12].kinds+6 ,
                                                   {
                                                    lang.synts+17
                                                   }
    },
    { 47 , "opDomain" , lang.synts[12].kinds+6 ,
                                                 {
                                                  lang.synts+16,
                                                  lang.atoms+3,
                                                  lang.synts+12,
                                                  lang.atoms+4
                                                 }
    },
    { 48 , "opInd" , lang.synts[12].kinds+5 ,
                                              {
                                               lang.synts+12,
                                               lang.atoms+19,
                                               lang.synts+12,
                                               lang.atoms+20
                                              }
    },
    { 49 , "opSelect" , lang.synts[12].kinds+5 ,
                                                 {
                                                  lang.synts+12,
                                                  lang.atoms+10,
                                                  lang.atoms+16
                                                 }
    },
    { 50 , "opPtrSelect" , lang.synts[12].kinds+5 ,
                                                    {
                                                     lang.synts+12,
                                                     lang.atoms+9,
                                                     lang.atoms+16
                                                    }
    },
    { 51 , "cast_Number" , lang.synts[12].kinds+4 ,
                                                    {
                                                     lang.atoms+17
                                                    }
    },
    { 52 , "opAst" , lang.synts[12].kinds+3 ,
                                              {
                                               lang.atoms+5,
                                               lang.synts+12
                                              }
    },
    { 53 , "opAmp" , lang.synts[12].kinds+3 ,
                                              {
                                               lang.atoms+2,
                                               lang.synts+12
                                              }
    },
    { 54 , "opPlus" , lang.synts[12].kinds+3 ,
                                               {
                                                lang.atoms+6,
                                                lang.synts+12
                                               }
    },
    { 55 , "opMinus" , lang.synts[12].kinds+3 ,
                                                {
                                                 lang.atoms+8,
                                                 lang.synts+12
                                                }
    },
    { 56 , "opMul" , lang.synts[12].kinds+2 ,
                                              {
                                               lang.synts+12,
                                               lang.atoms+5,
                                               lang.synts+12
                                              }
    },
    { 57 , "opDiv" , lang.synts[12].kinds+2 ,
                                              {
                                               lang.synts+12,
                                               lang.atoms+11,
                                               lang.synts+12
                                              }
    },
    { 58 , "opRem" , lang.synts[12].kinds+2 ,
                                              {
                                               lang.synts+12,
                                               lang.atoms+1,
                                               lang.synts+12
                                              }
    },
    { 59 , "opAdd" , lang.synts[12].kinds+1 ,
                                              {
                                               lang.synts+12,
                                               lang.atoms+6,
                                               lang.synts+12
                                              }
    },
    { 60 , "opSub" , lang.synts[12].kinds+1 ,
                                              {
                                               lang.synts+12,
                                               lang.atoms+8,
                                               lang.synts+12
                                              }
    },
    { 61 , "emptyExprList" , lang.synts[12].kinds+0 ,
                                                      {
                                                       lang.atoms+41,
                                                       lang.atoms+42
                                                      }
    },
    { 62 , "buildExprList" , lang.synts[12].kinds+0 ,
                                                      {
                                                       lang.atoms+41,
                                                       lang.synts+13,
                                                       lang.atoms+42
                                                      }
    },
    { 63 , "buildNamedExprList" , lang.synts[12].kinds+0 ,
                                                           {
                                                            lang.atoms+41,
                                                            lang.synts+15,
                                                            lang.atoms+42
                                                           }
    },
    { 64 , "applyEmpty" , lang.synts[12].kinds+0 ,
                                                   {
                                                    lang.synts+12,
                                                    lang.atoms+41,
                                                    lang.atoms+42
                                                   }
    },
    { 65 , "applyNamedExprList" , lang.synts[12].kinds+0 ,
                                                           {
                                                            lang.synts+12,
                                                            lang.atoms+41,
                                                            lang.synts+15,
                                                            lang.atoms+42
                                                           }
    },
    { 66 , "start" , lang.synts[13].kinds+0 ,
                                              {
                                               lang.synts+12
                                              }
    },
    { 67 , "ext" , lang.synts[13].kinds+0 ,
                                            {
                                             lang.synts+13,
                                             lang.atoms+7,
                                             lang.synts+12
                                            }
    },
    { 68 , "build" , lang.synts[14].kinds+0 ,
                                              {
                                               lang.atoms+10,
                                               lang.atoms+16,
                                               lang.atoms+13,
                                               lang.synts+12
                                              }
    },
    { 69 , "start" , lang.synts[15].kinds+0 ,
                                              {
                                               lang.synts+14
                                              }
    },
    { 70 , "ext" , lang.synts[15].kinds+0 ,
                                            {
                                             lang.synts+15,
                                             lang.atoms+7,
                                             lang.synts+14
                                            }
    },
    { 71 , "type_NAME" , lang.synts[16].kinds+0 ,
                                                  {
                                                   lang.synts+6
                                                  }
    },
    { 72 , "type_INAME" , lang.synts[16].kinds+0 ,
                                                   {
                                                    lang.synts+7
                                                   }
    },
    { 73 , "cast_null" , lang.synts[17].kinds+0 ,
                                                  {
                                                   lang.atoms+25
                                                  }
    },
    { 74 , "cast_String" , lang.synts[17].kinds+0 ,
                                                    {
                                                     lang.atoms+18
                                                    }
    },
    { 75 , "buildIP" , lang.synts[17].kinds+0 ,
                                                {
                                                 lang.atoms+17,
                                                 lang.atoms+10,
                                                 lang.atoms+17,
                                                 lang.atoms+10,
                                                 lang.atoms+17,
                                                 lang.atoms+10,
                                                 lang.atoms+17
                                                }
    }
   },
   {
    { 0 , "start" , lang.rules+0 , lang.synts[0].kinds+0 ,
                                                           {
                                                            
                                                           }
    },
    { 1 , "ext_SCOPE" , lang.rules+1 , lang.synts[0].kinds+0 ,
                                                               {
                                                                lang.synts[0].kinds+0,
                                                                lang.synts[1].kinds+0
                                                               }
    },
    { 2 , "ext_INCLUDE" , lang.rules+2 , lang.synts[0].kinds+0 ,
                                                                 {
                                                                  lang.synts[0].kinds+0,
                                                                  lang.synts[2].kinds+0
                                                                 }
    },
    { 3 , "ext_TYPE" , lang.rules+3 , lang.synts[0].kinds+0 ,
                                                              {
                                                               lang.synts[0].kinds+0,
                                                               lang.synts[3].kinds+0
                                                              }
    },
    { 4 , "ext_CONST" , lang.rules+4 , lang.synts[0].kinds+0 ,
                                                               {
                                                                lang.synts[0].kinds+0,
                                                                lang.synts[4].kinds+0
                                                               }
    },
    { 5 , "ext_STRUCT" , lang.rules+5 , lang.synts[0].kinds+0 ,
                                                                {
                                                                 lang.synts[0].kinds+0,
                                                                 lang.synts[10].kinds+0,
                                                                 lang.atoms+12
                                                                }
    },
    { 6 , "build" , lang.rules+6 , lang.synts[1].kinds+0 ,
                                                           {
                                                            lang.atoms+26,
                                                            lang.atoms+16,
                                                            lang.atoms+41,
                                                            lang.synts[0].kinds+0,
                                                            lang.atoms+42
                                                           }
    },
    { 7 , "includeFile" , lang.rules+7 , lang.synts[2].kinds+0 ,
                                                                 {
                                                                  lang.atoms+22,
                                                                  lang.atoms+15
                                                                 }
    },
    { 8 , "build" , lang.rules+8 , lang.synts[3].kinds+0 ,
                                                           {
                                                            lang.atoms+34,
                                                            lang.atoms+16,
                                                            lang.atoms+13,
                                                            lang.synts[9].kinds+0,
                                                            lang.atoms+12
                                                           }
    },
    { 9 , "build.LIST" , lang.rules+9 , lang.synts[4].kinds+0 ,
                                                                {
                                                                 lang.synts[9].kinds+0,
                                                                 lang.atoms+16,
                                                                 lang.atoms+13,
                                                                 lang.synts[12].kinds+0,
                                                                 lang.atoms+12
                                                                }
    },
    { 10 , "build.ADD" , lang.rules+9 , lang.synts[4].kinds+0 ,
                                                                {
                                                                 lang.synts[9].kinds+0,
                                                                 lang.atoms+16,
                                                                 lang.atoms+13,
                                                                 lang.synts[12].kinds+1,
                                                                 lang.atoms+12
                                                                }
    },
    { 11 , "build.MUL" , lang.rules+9 , lang.synts[4].kinds+0 ,
                                                                {
                                                                 lang.synts[9].kinds+0,
                                                                 lang.atoms+16,
                                                                 lang.atoms+13,
                                                                 lang.synts[12].kinds+2,
                                                                 lang.atoms+12
                                                                }
    },
    { 12 , "build.UN" , lang.rules+9 , lang.synts[4].kinds+0 ,
                                                               {
                                                                lang.synts[9].kinds+0,
                                                                lang.atoms+16,
                                                                lang.atoms+13,
                                                                lang.synts[12].kinds+3,
                                                                lang.atoms+12
                                                               }
    },
    { 13 , "build.NUM" , lang.rules+9 , lang.synts[4].kinds+0 ,
                                                                {
                                                                 lang.synts[9].kinds+0,
                                                                 lang.atoms+16,
                                                                 lang.atoms+13,
                                                                 lang.synts[12].kinds+4,
                                                                 lang.atoms+12
                                                                }
    },
    { 14 , "build.POST" , lang.rules+9 , lang.synts[4].kinds+0 ,
                                                                 {
                                                                  lang.synts[9].kinds+0,
                                                                  lang.atoms+16,
                                                                  lang.atoms+13,
                                                                  lang.synts[12].kinds+5,
                                                                  lang.atoms+12
                                                                 }
    },
    { 15 , "build.PRIM" , lang.rules+9 , lang.synts[4].kinds+0 ,
                                                                 {
                                                                  lang.synts[9].kinds+0,
                                                                  lang.atoms+16,
                                                                  lang.atoms+13,
                                                                  lang.synts[12].kinds+6,
                                                                  lang.atoms+12
                                                                 }
    },
    { 16 , "start" , lang.rules+10 , lang.synts[5].kinds+0 ,
                                                             {
                                                              lang.atoms+16
                                                             }
    },
    { 17 , "ext" , lang.rules+11 , lang.synts[5].kinds+0 ,
                                                           {
                                                            lang.synts[5].kinds+0,
                                                            lang.atoms+0,
                                                            lang.atoms+16
                                                           }
    },
    { 18 , "rel" , lang.rules+12 , lang.synts[6].kinds+0 ,
                                                           {
                                                            lang.synts[5].kinds+0
                                                           }
    },
    { 19 , "abs" , lang.rules+13 , lang.synts[6].kinds+0 ,
                                                           {
                                                            lang.atoms+0,
                                                            lang.synts[5].kinds+0
                                                           }
    },
    { 20 , "dot" , lang.rules+14 , lang.synts[6].kinds+0 ,
                                                           {
                                                            lang.atoms+10,
                                                            lang.atoms+0,
                                                            lang.synts[5].kinds+0
                                                           }
    },
    { 21 , "dots" , lang.rules+15 , lang.synts[6].kinds+0 ,
                                                            {
                                                             lang.atoms+14,
                                                             lang.atoms+0,
                                                             lang.synts[5].kinds+0
                                                            }
    },
    { 22 , "intName" , lang.rules+16 , lang.synts[7].kinds+0 ,
                                                               {
                                                                lang.atoms+23
                                                               }
    },
    { 23 , "sintName" , lang.rules+17 , lang.synts[7].kinds+0 ,
                                                                {
                                                                 lang.atoms+27
                                                                }
    },
    { 24 , "uintName" , lang.rules+18 , lang.synts[7].kinds+0 ,
                                                                {
                                                                 lang.atoms+35
                                                                }
    },
    { 25 , "ulenName" , lang.rules+19 , lang.synts[7].kinds+0 ,
                                                                {
                                                                 lang.atoms+40
                                                                }
    },
    { 26 , "sint8Name" , lang.rules+20 , lang.synts[7].kinds+0 ,
                                                                 {
                                                                  lang.atoms+31
                                                                 }
    },
    { 27 , "uint8Name" , lang.rules+21 , lang.synts[7].kinds+0 ,
                                                                 {
                                                                  lang.atoms+39
                                                                 }
    },
    { 28 , "sint16Name" , lang.rules+22 , lang.synts[7].kinds+0 ,
                                                                  {
                                                                   lang.atoms+28
                                                                  }
    },
    { 29 , "uint16Name" , lang.rules+23 , lang.synts[7].kinds+0 ,
                                                                  {
                                                                   lang.atoms+36
                                                                  }
    },
    { 30 , "sint32Name" , lang.rules+24 , lang.synts[7].kinds+0 ,
                                                                  {
                                                                   lang.atoms+29
                                                                  }
    },
    { 31 , "uint32Name" , lang.rules+25 , lang.synts[7].kinds+0 ,
                                                                  {
                                                                   lang.atoms+37
                                                                  }
    },
    { 32 , "sint64Name" , lang.rules+26 , lang.synts[7].kinds+0 ,
                                                                  {
                                                                   lang.atoms+30
                                                                  }
    },
    { 33 , "uint64Name" , lang.rules+27 , lang.synts[7].kinds+0 ,
                                                                  {
                                                                   lang.atoms+38
                                                                  }
    },
    { 34 , "cast" , lang.rules+28 , lang.synts[8].kinds+0 ,
                                                            {
                                                             lang.synts[7].kinds+0
                                                            }
    },
    { 35 , "text" , lang.rules+29 , lang.synts[8].kinds+0 ,
                                                            {
                                                             lang.atoms+33
                                                            }
    },
    { 36 , "ip" , lang.rules+30 , lang.synts[8].kinds+0 ,
                                                          {
                                                           lang.atoms+24
                                                          }
    },
    { 37 , "namedType" , lang.rules+31 , lang.synts[9].kinds+0 ,
                                                                 {
                                                                  lang.synts[6].kinds+0
                                                                 }
    },
    { 38 , "baseType" , lang.rules+32 , lang.synts[9].kinds+0 ,
                                                                {
                                                                 lang.synts[8].kinds+0
                                                                }
    },
    { 39 , "ptrType" , lang.rules+33 , lang.synts[9].kinds+0 ,
                                                               {
                                                                lang.synts[9].kinds+0,
                                                                lang.atoms+5
                                                               }
    },
    { 40 , "arrayType" , lang.rules+34 , lang.synts[9].kinds+0 ,
                                                                 {
                                                                  lang.synts[9].kinds+0,
                                                                  lang.atoms+19,
                                                                  lang.atoms+20
                                                                 }
    },
    { 41 , "arrayLenType.LIST" , lang.rules+35 , lang.synts[9].kinds+0 ,
                                                                         {
                                                                          lang.synts[9].kinds+0,
                                                                          lang.atoms+19,
                                                                          lang.synts[12].kinds+0,
                                                                          lang.atoms+20
                                                                         }
    },
    { 42 , "arrayLenType.ADD" , lang.rules+35 , lang.synts[9].kinds+0 ,
                                                                        {
                                                                         lang.synts[9].kinds+0,
                                                                         lang.atoms+19,
                                                                         lang.synts[12].kinds+1,
                                                                         lang.atoms+20
                                                                        }
    },
    { 43 , "arrayLenType.MUL" , lang.rules+35 , lang.synts[9].kinds+0 ,
                                                                        {
                                                                         lang.synts[9].kinds+0,
                                                                         lang.atoms+19,
                                                                         lang.synts[12].kinds+2,
                                                                         lang.atoms+20
                                                                        }
    },
    { 44 , "arrayLenType.UN" , lang.rules+35 , lang.synts[9].kinds+0 ,
                                                                       {
                                                                        lang.synts[9].kinds+0,
                                                                        lang.atoms+19,
                                                                        lang.synts[12].kinds+3,
                                                                        lang.atoms+20
                                                                       }
    },
    { 45 , "arrayLenType.NUM" , lang.rules+35 , lang.synts[9].kinds+0 ,
                                                                        {
                                                                         lang.synts[9].kinds+0,
                                                                         lang.atoms+19,
                                                                         lang.synts[12].kinds+4,
                                                                         lang.atoms+20
                                                                        }
    },
    { 46 , "arrayLenType.POST" , lang.rules+35 , lang.synts[9].kinds+0 ,
                                                                         {
                                                                          lang.synts[9].kinds+0,
                                                                          lang.atoms+19,
                                                                          lang.synts[12].kinds+5,
                                                                          lang.atoms+20
                                                                         }
    },
    { 47 , "arrayLenType.PRIM" , lang.rules+35 , lang.synts[9].kinds+0 ,
                                                                         {
                                                                          lang.synts[9].kinds+0,
                                                                          lang.atoms+19,
                                                                          lang.synts[12].kinds+6,
                                                                          lang.atoms+20
                                                                         }
    },
    { 48 , "structType" , lang.rules+36 , lang.synts[9].kinds+0 ,
                                                                  {
                                                                   lang.synts[10].kinds+0
                                                                  }
    },
    { 49 , "build" , lang.rules+37 , lang.synts[10].kinds+0 ,
                                                              {
                                                               lang.atoms+32,
                                                               lang.atoms+16,
                                                               lang.atoms+41,
                                                               lang.synts[11].kinds+0,
                                                               lang.atoms+42
                                                              }
    },
    { 50 , "start" , lang.rules+38 , lang.synts[11].kinds+0 ,
                                                              {
                                                               
                                                              }
    },
    { 51 , "ext_TYPE" , lang.rules+39 , lang.synts[11].kinds+0 ,
                                                                 {
                                                                  lang.synts[11].kinds+0,
                                                                  lang.synts[3].kinds+0
                                                                 }
    },
    { 52 , "ext_CONST" , lang.rules+40 , lang.synts[11].kinds+0 ,
                                                                  {
                                                                   lang.synts[11].kinds+0,
                                                                   lang.atoms+21,
                                                                   lang.synts[4].kinds+0
                                                                  }
    },
    { 53 , "ext_STRUCT" , lang.rules+41 , lang.synts[11].kinds+0 ,
                                                                   {
                                                                    lang.synts[11].kinds+0,
                                                                    lang.synts[10].kinds+0,
                                                                    lang.atoms+12
                                                                   }
    },
    { 54 , "ext_field" , lang.rules+42 , lang.synts[11].kinds+0 ,
                                                                  {
                                                                   lang.synts[11].kinds+0,
                                                                   lang.synts[9].kinds+0,
                                                                   lang.atoms+16,
                                                                   lang.atoms+12
                                                                  }
    },
    { 55 , "ext_fieldVal.LIST" , lang.rules+43 , lang.synts[11].kinds+0 ,
                                                                          {
                                                                           lang.synts[11].kinds+0,
                                                                           lang.synts[9].kinds+0,
                                                                           lang.atoms+16,
                                                                           lang.atoms+13,
                                                                           lang.synts[12].kinds+0,
                                                                           lang.atoms+12
                                                                          }
    },
    { 56 , "ext_fieldVal.ADD" , lang.rules+43 , lang.synts[11].kinds+0 ,
                                                                         {
                                                                          lang.synts[11].kinds+0,
                                                                          lang.synts[9].kinds+0,
                                                                          lang.atoms+16,
                                                                          lang.atoms+13,
                                                                          lang.synts[12].kinds+1,
                                                                          lang.atoms+12
                                                                         }
    },
    { 57 , "ext_fieldVal.MUL" , lang.rules+43 , lang.synts[11].kinds+0 ,
                                                                         {
                                                                          lang.synts[11].kinds+0,
                                                                          lang.synts[9].kinds+0,
                                                                          lang.atoms+16,
                                                                          lang.atoms+13,
                                                                          lang.synts[12].kinds+2,
                                                                          lang.atoms+12
                                                                         }
    },
    { 58 , "ext_fieldVal.UN" , lang.rules+43 , lang.synts[11].kinds+0 ,
                                                                        {
                                                                         lang.synts[11].kinds+0,
                                                                         lang.synts[9].kinds+0,
                                                                         lang.atoms+16,
                                                                         lang.atoms+13,
                                                                         lang.synts[12].kinds+3,
                                                                         lang.atoms+12
                                                                        }
    },
    { 59 , "ext_fieldVal.NUM" , lang.rules+43 , lang.synts[11].kinds+0 ,
                                                                         {
                                                                          lang.synts[11].kinds+0,
                                                                          lang.synts[9].kinds+0,
                                                                          lang.atoms+16,
                                                                          lang.atoms+13,
                                                                          lang.synts[12].kinds+4,
                                                                          lang.atoms+12
                                                                         }
    },
    { 60 , "ext_fieldVal.POST" , lang.rules+43 , lang.synts[11].kinds+0 ,
                                                                          {
                                                                           lang.synts[11].kinds+0,
                                                                           lang.synts[9].kinds+0,
                                                                           lang.atoms+16,
                                                                           lang.atoms+13,
                                                                           lang.synts[12].kinds+5,
                                                                           lang.atoms+12
                                                                          }
    },
    { 61 , "ext_fieldVal.PRIM" , lang.rules+43 , lang.synts[11].kinds+0 ,
                                                                          {
                                                                           lang.synts[11].kinds+0,
                                                                           lang.synts[9].kinds+0,
                                                                           lang.atoms+16,
                                                                           lang.atoms+13,
                                                                           lang.synts[12].kinds+6,
                                                                           lang.atoms+12
                                                                          }
    },
    { 62 , "emptyExprList" , lang.rules+61 , lang.synts[12].kinds+0 ,
                                                                      {
                                                                       lang.atoms+41,
                                                                       lang.atoms+42
                                                                      }
    },
    { 63 , "buildExprList" , lang.rules+62 , lang.synts[12].kinds+0 ,
                                                                      {
                                                                       lang.atoms+41,
                                                                       lang.synts[13].kinds+0,
                                                                       lang.atoms+42
                                                                      }
    },
    { 64 , "buildNamedExprList" , lang.rules+63 , lang.synts[12].kinds+0 ,
                                                                           {
                                                                            lang.atoms+41,
                                                                            lang.synts[15].kinds+0,
                                                                            lang.atoms+42
                                                                           }
    },
    { 65 , "applyEmpty.LIST" , lang.rules+64 , lang.synts[12].kinds+0 ,
                                                                        {
                                                                         lang.synts[12].kinds+0,
                                                                         lang.atoms+41,
                                                                         lang.atoms+42
                                                                        }
    },
    { 66 , "applyEmpty.ADD" , lang.rules+64 , lang.synts[12].kinds+0 ,
                                                                       {
                                                                        lang.synts[12].kinds+1,
                                                                        lang.atoms+41,
                                                                        lang.atoms+42
                                                                       }
    },
    { 67 , "applyEmpty.MUL" , lang.rules+64 , lang.synts[12].kinds+0 ,
                                                                       {
                                                                        lang.synts[12].kinds+2,
                                                                        lang.atoms+41,
                                                                        lang.atoms+42
                                                                       }
    },
    { 68 , "applyEmpty.UN" , lang.rules+64 , lang.synts[12].kinds+0 ,
                                                                      {
                                                                       lang.synts[12].kinds+3,
                                                                       lang.atoms+41,
                                                                       lang.atoms+42
                                                                      }
    },
    { 69 , "applyEmpty.NUM" , lang.rules+64 , lang.synts[12].kinds+0 ,
                                                                       {
                                                                        lang.synts[12].kinds+4,
                                                                        lang.atoms+41,
                                                                        lang.atoms+42
                                                                       }
    },
    { 70 , "applyEmpty.POST" , lang.rules+64 , lang.synts[12].kinds+0 ,
                                                                        {
                                                                         lang.synts[12].kinds+5,
                                                                         lang.atoms+41,
                                                                         lang.atoms+42
                                                                        }
    },
    { 71 , "applyEmpty.PRIM" , lang.rules+64 , lang.synts[12].kinds+0 ,
                                                                        {
                                                                         lang.synts[12].kinds+6,
                                                                         lang.atoms+41,
                                                                         lang.atoms+42
                                                                        }
    },
    { 72 , "applyNamedExprList.LIST" , lang.rules+65 , lang.synts[12].kinds+0 ,
                                                                                {
                                                                                 lang.synts[12].kinds+0,
                                                                                 lang.atoms+41,
                                                                                 lang.synts[15].kinds+0,
                                                                                 lang.atoms+42
                                                                                }
    },
    { 73 , "applyNamedExprList.ADD" , lang.rules+65 , lang.synts[12].kinds+0 ,
                                                                               {
                                                                                lang.synts[12].kinds+1,
                                                                                lang.atoms+41,
                                                                                lang.synts[15].kinds+0,
                                                                                lang.atoms+42
                                                                               }
    },
    { 74 , "applyNamedExprList.MUL" , lang.rules+65 , lang.synts[12].kinds+0 ,
                                                                               {
                                                                                lang.synts[12].kinds+2,
                                                                                lang.atoms+41,
                                                                                lang.synts[15].kinds+0,
                                                                                lang.atoms+42
                                                                               }
    },
    { 75 , "applyNamedExprList.UN" , lang.rules+65 , lang.synts[12].kinds+0 ,
                                                                              {
                                                                               lang.synts[12].kinds+3,
                                                                               lang.atoms+41,
                                                                               lang.synts[15].kinds+0,
                                                                               lang.atoms+42
                                                                              }
    },
    { 76 , "applyNamedExprList.NUM" , lang.rules+65 , lang.synts[12].kinds+0 ,
                                                                               {
                                                                                lang.synts[12].kinds+4,
                                                                                lang.atoms+41,
                                                                                lang.synts[15].kinds+0,
                                                                                lang.atoms+42
                                                                               }
    },
    { 77 , "applyNamedExprList.POST" , lang.rules+65 , lang.synts[12].kinds+0 ,
                                                                                {
                                                                                 lang.synts[12].kinds+5,
                                                                                 lang.atoms+41,
                                                                                 lang.synts[15].kinds+0,
                                                                                 lang.atoms+42
                                                                                }
    },
    { 78 , "applyNamedExprList.PRIM" , lang.rules+65 , lang.synts[12].kinds+0 ,
                                                                                {
                                                                                 lang.synts[12].kinds+6,
                                                                                 lang.atoms+41,
                                                                                 lang.synts[15].kinds+0,
                                                                                 lang.atoms+42
                                                                                }
    },
    { 79 , "opAdd.ADD.MUL" , lang.rules+59 , lang.synts[12].kinds+1 ,
                                                                      {
                                                                       lang.synts[12].kinds+1,
                                                                       lang.atoms+6,
                                                                       lang.synts[12].kinds+2
                                                                      }
    },
    { 80 , "opAdd.MUL.MUL" , lang.rules+59 , lang.synts[12].kinds+1 ,
                                                                      {
                                                                       lang.synts[12].kinds+2,
                                                                       lang.atoms+6,
                                                                       lang.synts[12].kinds+2
                                                                      }
    },
    { 81 , "opAdd.UN.MUL" , lang.rules+59 , lang.synts[12].kinds+1 ,
                                                                     {
                                                                      lang.synts[12].kinds+3,
                                                                      lang.atoms+6,
                                                                      lang.synts[12].kinds+2
                                                                     }
    },
    { 82 , "opAdd.NUM.MUL" , lang.rules+59 , lang.synts[12].kinds+1 ,
                                                                      {
                                                                       lang.synts[12].kinds+4,
                                                                       lang.atoms+6,
                                                                       lang.synts[12].kinds+2
                                                                      }
    },
    { 83 , "opAdd.POST.MUL" , lang.rules+59 , lang.synts[12].kinds+1 ,
                                                                       {
                                                                        lang.synts[12].kinds+5,
                                                                        lang.atoms+6,
                                                                        lang.synts[12].kinds+2
                                                                       }
    },
    { 84 , "opAdd.PRIM.MUL" , lang.rules+59 , lang.synts[12].kinds+1 ,
                                                                       {
                                                                        lang.synts[12].kinds+6,
                                                                        lang.atoms+6,
                                                                        lang.synts[12].kinds+2
                                                                       }
    },
    { 85 , "opAdd.ADD.UN" , lang.rules+59 , lang.synts[12].kinds+1 ,
                                                                     {
                                                                      lang.synts[12].kinds+1,
                                                                      lang.atoms+6,
                                                                      lang.synts[12].kinds+3
                                                                     }
    },
    { 86 , "opAdd.MUL.UN" , lang.rules+59 , lang.synts[12].kinds+1 ,
                                                                     {
                                                                      lang.synts[12].kinds+2,
                                                                      lang.atoms+6,
                                                                      lang.synts[12].kinds+3
                                                                     }
    },
    { 87 , "opAdd.UN.UN" , lang.rules+59 , lang.synts[12].kinds+1 ,
                                                                    {
                                                                     lang.synts[12].kinds+3,
                                                                     lang.atoms+6,
                                                                     lang.synts[12].kinds+3
                                                                    }
    },
    { 88 , "opAdd.NUM.UN" , lang.rules+59 , lang.synts[12].kinds+1 ,
                                                                     {
                                                                      lang.synts[12].kinds+4,
                                                                      lang.atoms+6,
                                                                      lang.synts[12].kinds+3
                                                                     }
    },
    { 89 , "opAdd.POST.UN" , lang.rules+59 , lang.synts[12].kinds+1 ,
                                                                      {
                                                                       lang.synts[12].kinds+5,
                                                                       lang.atoms+6,
                                                                       lang.synts[12].kinds+3
                                                                      }
    },
    { 90 , "opAdd.PRIM.UN" , lang.rules+59 , lang.synts[12].kinds+1 ,
                                                                      {
                                                                       lang.synts[12].kinds+6,
                                                                       lang.atoms+6,
                                                                       lang.synts[12].kinds+3
                                                                      }
    },
    { 91 , "opAdd.ADD.NUM" , lang.rules+59 , lang.synts[12].kinds+1 ,
                                                                      {
                                                                       lang.synts[12].kinds+1,
                                                                       lang.atoms+6,
                                                                       lang.synts[12].kinds+4
                                                                      }
    },
    { 92 , "opAdd.MUL.NUM" , lang.rules+59 , lang.synts[12].kinds+1 ,
                                                                      {
                                                                       lang.synts[12].kinds+2,
                                                                       lang.atoms+6,
                                                                       lang.synts[12].kinds+4
                                                                      }
    },
    { 93 , "opAdd.UN.NUM" , lang.rules+59 , lang.synts[12].kinds+1 ,
                                                                     {
                                                                      lang.synts[12].kinds+3,
                                                                      lang.atoms+6,
                                                                      lang.synts[12].kinds+4
                                                                     }
    },
    { 94 , "opAdd.NUM.NUM" , lang.rules+59 , lang.synts[12].kinds+1 ,
                                                                      {
                                                                       lang.synts[12].kinds+4,
                                                                       lang.atoms+6,
                                                                       lang.synts[12].kinds+4
                                                                      }
    },
    { 95 , "opAdd.POST.NUM" , lang.rules+59 , lang.synts[12].kinds+1 ,
                                                                       {
                                                                        lang.synts[12].kinds+5,
                                                                        lang.atoms+6,
                                                                        lang.synts[12].kinds+4
                                                                       }
    },
    { 96 , "opAdd.PRIM.NUM" , lang.rules+59 , lang.synts[12].kinds+1 ,
                                                                       {
                                                                        lang.synts[12].kinds+6,
                                                                        lang.atoms+6,
                                                                        lang.synts[12].kinds+4
                                                                       }
    },
    { 97 , "opAdd.ADD.POST" , lang.rules+59 , lang.synts[12].kinds+1 ,
                                                                       {
                                                                        lang.synts[12].kinds+1,
                                                                        lang.atoms+6,
                                                                        lang.synts[12].kinds+5
                                                                       }
    },
    { 98 , "opAdd.MUL.POST" , lang.rules+59 , lang.synts[12].kinds+1 ,
                                                                       {
                                                                        lang.synts[12].kinds+2,
                                                                        lang.atoms+6,
                                                                        lang.synts[12].kinds+5
                                                                       }
    },
    { 99 , "opAdd.UN.POST" , lang.rules+59 , lang.synts[12].kinds+1 ,
                                                                      {
                                                                       lang.synts[12].kinds+3,
                                                                       lang.atoms+6,
                                                                       lang.synts[12].kinds+5
                                                                      }
    },
    { 100 , "opAdd.NUM.POST" , lang.rules+59 , lang.synts[12].kinds+1 ,
                                                                        {
                                                                         lang.synts[12].kinds+4,
                                                                         lang.atoms+6,
                                                                         lang.synts[12].kinds+5
                                                                        }
    },
    { 101 , "opAdd.POST.POST" , lang.rules+59 , lang.synts[12].kinds+1 ,
                                                                         {
                                                                          lang.synts[12].kinds+5,
                                                                          lang.atoms+6,
                                                                          lang.synts[12].kinds+5
                                                                         }
    },
    { 102 , "opAdd.PRIM.POST" , lang.rules+59 , lang.synts[12].kinds+1 ,
                                                                         {
                                                                          lang.synts[12].kinds+6,
                                                                          lang.atoms+6,
                                                                          lang.synts[12].kinds+5
                                                                         }
    },
    { 103 , "opAdd.ADD.PRIM" , lang.rules+59 , lang.synts[12].kinds+1 ,
                                                                        {
                                                                         lang.synts[12].kinds+1,
                                                                         lang.atoms+6,
                                                                         lang.synts[12].kinds+6
                                                                        }
    },
    { 104 , "opAdd.MUL.PRIM" , lang.rules+59 , lang.synts[12].kinds+1 ,
                                                                        {
                                                                         lang.synts[12].kinds+2,
                                                                         lang.atoms+6,
                                                                         lang.synts[12].kinds+6
                                                                        }
    },
    { 105 , "opAdd.UN.PRIM" , lang.rules+59 , lang.synts[12].kinds+1 ,
                                                                       {
                                                                        lang.synts[12].kinds+3,
                                                                        lang.atoms+6,
                                                                        lang.synts[12].kinds+6
                                                                       }
    },
    { 106 , "opAdd.NUM.PRIM" , lang.rules+59 , lang.synts[12].kinds+1 ,
                                                                        {
                                                                         lang.synts[12].kinds+4,
                                                                         lang.atoms+6,
                                                                         lang.synts[12].kinds+6
                                                                        }
    },
    { 107 , "opAdd.POST.PRIM" , lang.rules+59 , lang.synts[12].kinds+1 ,
                                                                         {
                                                                          lang.synts[12].kinds+5,
                                                                          lang.atoms+6,
                                                                          lang.synts[12].kinds+6
                                                                         }
    },
    { 108 , "opAdd.PRIM.PRIM" , lang.rules+59 , lang.synts[12].kinds+1 ,
                                                                         {
                                                                          lang.synts[12].kinds+6,
                                                                          lang.atoms+6,
                                                                          lang.synts[12].kinds+6
                                                                         }
    },
    { 109 , "opSub.ADD.MUL" , lang.rules+60 , lang.synts[12].kinds+1 ,
                                                                       {
                                                                        lang.synts[12].kinds+1,
                                                                        lang.atoms+8,
                                                                        lang.synts[12].kinds+2
                                                                       }
    },
    { 110 , "opSub.MUL.MUL" , lang.rules+60 , lang.synts[12].kinds+1 ,
                                                                       {
                                                                        lang.synts[12].kinds+2,
                                                                        lang.atoms+8,
                                                                        lang.synts[12].kinds+2
                                                                       }
    },
    { 111 , "opSub.UN.MUL" , lang.rules+60 , lang.synts[12].kinds+1 ,
                                                                      {
                                                                       lang.synts[12].kinds+3,
                                                                       lang.atoms+8,
                                                                       lang.synts[12].kinds+2
                                                                      }
    },
    { 112 , "opSub.NUM.MUL" , lang.rules+60 , lang.synts[12].kinds+1 ,
                                                                       {
                                                                        lang.synts[12].kinds+4,
                                                                        lang.atoms+8,
                                                                        lang.synts[12].kinds+2
                                                                       }
    },
    { 113 , "opSub.POST.MUL" , lang.rules+60 , lang.synts[12].kinds+1 ,
                                                                        {
                                                                         lang.synts[12].kinds+5,
                                                                         lang.atoms+8,
                                                                         lang.synts[12].kinds+2
                                                                        }
    },
    { 114 , "opSub.PRIM.MUL" , lang.rules+60 , lang.synts[12].kinds+1 ,
                                                                        {
                                                                         lang.synts[12].kinds+6,
                                                                         lang.atoms+8,
                                                                         lang.synts[12].kinds+2
                                                                        }
    },
    { 115 , "opSub.ADD.UN" , lang.rules+60 , lang.synts[12].kinds+1 ,
                                                                      {
                                                                       lang.synts[12].kinds+1,
                                                                       lang.atoms+8,
                                                                       lang.synts[12].kinds+3
                                                                      }
    },
    { 116 , "opSub.MUL.UN" , lang.rules+60 , lang.synts[12].kinds+1 ,
                                                                      {
                                                                       lang.synts[12].kinds+2,
                                                                       lang.atoms+8,
                                                                       lang.synts[12].kinds+3
                                                                      }
    },
    { 117 , "opSub.UN.UN" , lang.rules+60 , lang.synts[12].kinds+1 ,
                                                                     {
                                                                      lang.synts[12].kinds+3,
                                                                      lang.atoms+8,
                                                                      lang.synts[12].kinds+3
                                                                     }
    },
    { 118 , "opSub.NUM.UN" , lang.rules+60 , lang.synts[12].kinds+1 ,
                                                                      {
                                                                       lang.synts[12].kinds+4,
                                                                       lang.atoms+8,
                                                                       lang.synts[12].kinds+3
                                                                      }
    },
    { 119 , "opSub.POST.UN" , lang.rules+60 , lang.synts[12].kinds+1 ,
                                                                       {
                                                                        lang.synts[12].kinds+5,
                                                                        lang.atoms+8,
                                                                        lang.synts[12].kinds+3
                                                                       }
    },
    { 120 , "opSub.PRIM.UN" , lang.rules+60 , lang.synts[12].kinds+1 ,
                                                                       {
                                                                        lang.synts[12].kinds+6,
                                                                        lang.atoms+8,
                                                                        lang.synts[12].kinds+3
                                                                       }
    },
    { 121 , "opSub.ADD.NUM" , lang.rules+60 , lang.synts[12].kinds+1 ,
                                                                       {
                                                                        lang.synts[12].kinds+1,
                                                                        lang.atoms+8,
                                                                        lang.synts[12].kinds+4
                                                                       }
    },
    { 122 , "opSub.MUL.NUM" , lang.rules+60 , lang.synts[12].kinds+1 ,
                                                                       {
                                                                        lang.synts[12].kinds+2,
                                                                        lang.atoms+8,
                                                                        lang.synts[12].kinds+4
                                                                       }
    },
    { 123 , "opSub.UN.NUM" , lang.rules+60 , lang.synts[12].kinds+1 ,
                                                                      {
                                                                       lang.synts[12].kinds+3,
                                                                       lang.atoms+8,
                                                                       lang.synts[12].kinds+4
                                                                      }
    },
    { 124 , "opSub.NUM.NUM" , lang.rules+60 , lang.synts[12].kinds+1 ,
                                                                       {
                                                                        lang.synts[12].kinds+4,
                                                                        lang.atoms+8,
                                                                        lang.synts[12].kinds+4
                                                                       }
    },
    { 125 , "opSub.POST.NUM" , lang.rules+60 , lang.synts[12].kinds+1 ,
                                                                        {
                                                                         lang.synts[12].kinds+5,
                                                                         lang.atoms+8,
                                                                         lang.synts[12].kinds+4
                                                                        }
    },
    { 126 , "opSub.PRIM.NUM" , lang.rules+60 , lang.synts[12].kinds+1 ,
                                                                        {
                                                                         lang.synts[12].kinds+6,
                                                                         lang.atoms+8,
                                                                         lang.synts[12].kinds+4
                                                                        }
    },
    { 127 , "opSub.ADD.POST" , lang.rules+60 , lang.synts[12].kinds+1 ,
                                                                        {
                                                                         lang.synts[12].kinds+1,
                                                                         lang.atoms+8,
                                                                         lang.synts[12].kinds+5
                                                                        }
    },
    { 128 , "opSub.MUL.POST" , lang.rules+60 , lang.synts[12].kinds+1 ,
                                                                        {
                                                                         lang.synts[12].kinds+2,
                                                                         lang.atoms+8,
                                                                         lang.synts[12].kinds+5
                                                                        }
    },
    { 129 , "opSub.UN.POST" , lang.rules+60 , lang.synts[12].kinds+1 ,
                                                                       {
                                                                        lang.synts[12].kinds+3,
                                                                        lang.atoms+8,
                                                                        lang.synts[12].kinds+5
                                                                       }
    },
    { 130 , "opSub.NUM.POST" , lang.rules+60 , lang.synts[12].kinds+1 ,
                                                                        {
                                                                         lang.synts[12].kinds+4,
                                                                         lang.atoms+8,
                                                                         lang.synts[12].kinds+5
                                                                        }
    },
    { 131 , "opSub.POST.POST" , lang.rules+60 , lang.synts[12].kinds+1 ,
                                                                         {
                                                                          lang.synts[12].kinds+5,
                                                                          lang.atoms+8,
                                                                          lang.synts[12].kinds+5
                                                                         }
    },
    { 132 , "opSub.PRIM.POST" , lang.rules+60 , lang.synts[12].kinds+1 ,
                                                                         {
                                                                          lang.synts[12].kinds+6,
                                                                          lang.atoms+8,
                                                                          lang.synts[12].kinds+5
                                                                         }
    },
    { 133 , "opSub.ADD.PRIM" , lang.rules+60 , lang.synts[12].kinds+1 ,
                                                                        {
                                                                         lang.synts[12].kinds+1,
                                                                         lang.atoms+8,
                                                                         lang.synts[12].kinds+6
                                                                        }
    },
    { 134 , "opSub.MUL.PRIM" , lang.rules+60 , lang.synts[12].kinds+1 ,
                                                                        {
                                                                         lang.synts[12].kinds+2,
                                                                         lang.atoms+8,
                                                                         lang.synts[12].kinds+6
                                                                        }
    },
    { 135 , "opSub.UN.PRIM" , lang.rules+60 , lang.synts[12].kinds+1 ,
                                                                       {
                                                                        lang.synts[12].kinds+3,
                                                                        lang.atoms+8,
                                                                        lang.synts[12].kinds+6
                                                                       }
    },
    { 136 , "opSub.NUM.PRIM" , lang.rules+60 , lang.synts[12].kinds+1 ,
                                                                        {
                                                                         lang.synts[12].kinds+4,
                                                                         lang.atoms+8,
                                                                         lang.synts[12].kinds+6
                                                                        }
    },
    { 137 , "opSub.POST.PRIM" , lang.rules+60 , lang.synts[12].kinds+1 ,
                                                                         {
                                                                          lang.synts[12].kinds+5,
                                                                          lang.atoms+8,
                                                                          lang.synts[12].kinds+6
                                                                         }
    },
    { 138 , "opSub.PRIM.PRIM" , lang.rules+60 , lang.synts[12].kinds+1 ,
                                                                         {
                                                                          lang.synts[12].kinds+6,
                                                                          lang.atoms+8,
                                                                          lang.synts[12].kinds+6
                                                                         }
    },
    { 139 , "opMul.MUL.UN" , lang.rules+56 , lang.synts[12].kinds+2 ,
                                                                      {
                                                                       lang.synts[12].kinds+2,
                                                                       lang.atoms+5,
                                                                       lang.synts[12].kinds+3
                                                                      }
    },
    { 140 , "opMul.UN.UN" , lang.rules+56 , lang.synts[12].kinds+2 ,
                                                                     {
                                                                      lang.synts[12].kinds+3,
                                                                      lang.atoms+5,
                                                                      lang.synts[12].kinds+3
                                                                     }
    },
    { 141 , "opMul.NUM.UN" , lang.rules+56 , lang.synts[12].kinds+2 ,
                                                                      {
                                                                       lang.synts[12].kinds+4,
                                                                       lang.atoms+5,
                                                                       lang.synts[12].kinds+3
                                                                      }
    },
    { 142 , "opMul.POST.UN" , lang.rules+56 , lang.synts[12].kinds+2 ,
                                                                       {
                                                                        lang.synts[12].kinds+5,
                                                                        lang.atoms+5,
                                                                        lang.synts[12].kinds+3
                                                                       }
    },
    { 143 , "opMul.PRIM.UN" , lang.rules+56 , lang.synts[12].kinds+2 ,
                                                                       {
                                                                        lang.synts[12].kinds+6,
                                                                        lang.atoms+5,
                                                                        lang.synts[12].kinds+3
                                                                       }
    },
    { 144 , "opMul.MUL.NUM" , lang.rules+56 , lang.synts[12].kinds+2 ,
                                                                       {
                                                                        lang.synts[12].kinds+2,
                                                                        lang.atoms+5,
                                                                        lang.synts[12].kinds+4
                                                                       }
    },
    { 145 , "opMul.UN.NUM" , lang.rules+56 , lang.synts[12].kinds+2 ,
                                                                      {
                                                                       lang.synts[12].kinds+3,
                                                                       lang.atoms+5,
                                                                       lang.synts[12].kinds+4
                                                                      }
    },
    { 146 , "opMul.NUM.NUM" , lang.rules+56 , lang.synts[12].kinds+2 ,
                                                                       {
                                                                        lang.synts[12].kinds+4,
                                                                        lang.atoms+5,
                                                                        lang.synts[12].kinds+4
                                                                       }
    },
    { 147 , "opMul.POST.NUM" , lang.rules+56 , lang.synts[12].kinds+2 ,
                                                                        {
                                                                         lang.synts[12].kinds+5,
                                                                         lang.atoms+5,
                                                                         lang.synts[12].kinds+4
                                                                        }
    },
    { 148 , "opMul.PRIM.NUM" , lang.rules+56 , lang.synts[12].kinds+2 ,
                                                                        {
                                                                         lang.synts[12].kinds+6,
                                                                         lang.atoms+5,
                                                                         lang.synts[12].kinds+4
                                                                        }
    },
    { 149 , "opMul.MUL.POST" , lang.rules+56 , lang.synts[12].kinds+2 ,
                                                                        {
                                                                         lang.synts[12].kinds+2,
                                                                         lang.atoms+5,
                                                                         lang.synts[12].kinds+5
                                                                        }
    },
    { 150 , "opMul.UN.POST" , lang.rules+56 , lang.synts[12].kinds+2 ,
                                                                       {
                                                                        lang.synts[12].kinds+3,
                                                                        lang.atoms+5,
                                                                        lang.synts[12].kinds+5
                                                                       }
    },
    { 151 , "opMul.NUM.POST" , lang.rules+56 , lang.synts[12].kinds+2 ,
                                                                        {
                                                                         lang.synts[12].kinds+4,
                                                                         lang.atoms+5,
                                                                         lang.synts[12].kinds+5
                                                                        }
    },
    { 152 , "opMul.POST.POST" , lang.rules+56 , lang.synts[12].kinds+2 ,
                                                                         {
                                                                          lang.synts[12].kinds+5,
                                                                          lang.atoms+5,
                                                                          lang.synts[12].kinds+5
                                                                         }
    },
    { 153 , "opMul.PRIM.POST" , lang.rules+56 , lang.synts[12].kinds+2 ,
                                                                         {
                                                                          lang.synts[12].kinds+6,
                                                                          lang.atoms+5,
                                                                          lang.synts[12].kinds+5
                                                                         }
    },
    { 154 , "opMul.MUL.PRIM" , lang.rules+56 , lang.synts[12].kinds+2 ,
                                                                        {
                                                                         lang.synts[12].kinds+2,
                                                                         lang.atoms+5,
                                                                         lang.synts[12].kinds+6
                                                                        }
    },
    { 155 , "opMul.UN.PRIM" , lang.rules+56 , lang.synts[12].kinds+2 ,
                                                                       {
                                                                        lang.synts[12].kinds+3,
                                                                        lang.atoms+5,
                                                                        lang.synts[12].kinds+6
                                                                       }
    },
    { 156 , "opMul.NUM.PRIM" , lang.rules+56 , lang.synts[12].kinds+2 ,
                                                                        {
                                                                         lang.synts[12].kinds+4,
                                                                         lang.atoms+5,
                                                                         lang.synts[12].kinds+6
                                                                        }
    },
    { 157 , "opMul.POST.PRIM" , lang.rules+56 , lang.synts[12].kinds+2 ,
                                                                         {
                                                                          lang.synts[12].kinds+5,
                                                                          lang.atoms+5,
                                                                          lang.synts[12].kinds+6
                                                                         }
    },
    { 158 , "opMul.PRIM.PRIM" , lang.rules+56 , lang.synts[12].kinds+2 ,
                                                                         {
                                                                          lang.synts[12].kinds+6,
                                                                          lang.atoms+5,
                                                                          lang.synts[12].kinds+6
                                                                         }
    },
    { 159 , "opDiv.MUL.UN" , lang.rules+57 , lang.synts[12].kinds+2 ,
                                                                      {
                                                                       lang.synts[12].kinds+2,
                                                                       lang.atoms+11,
                                                                       lang.synts[12].kinds+3
                                                                      }
    },
    { 160 , "opDiv.UN.UN" , lang.rules+57 , lang.synts[12].kinds+2 ,
                                                                     {
                                                                      lang.synts[12].kinds+3,
                                                                      lang.atoms+11,
                                                                      lang.synts[12].kinds+3
                                                                     }
    },
    { 161 , "opDiv.NUM.UN" , lang.rules+57 , lang.synts[12].kinds+2 ,
                                                                      {
                                                                       lang.synts[12].kinds+4,
                                                                       lang.atoms+11,
                                                                       lang.synts[12].kinds+3
                                                                      }
    },
    { 162 , "opDiv.POST.UN" , lang.rules+57 , lang.synts[12].kinds+2 ,
                                                                       {
                                                                        lang.synts[12].kinds+5,
                                                                        lang.atoms+11,
                                                                        lang.synts[12].kinds+3
                                                                       }
    },
    { 163 , "opDiv.PRIM.UN" , lang.rules+57 , lang.synts[12].kinds+2 ,
                                                                       {
                                                                        lang.synts[12].kinds+6,
                                                                        lang.atoms+11,
                                                                        lang.synts[12].kinds+3
                                                                       }
    },
    { 164 , "opDiv.MUL.NUM" , lang.rules+57 , lang.synts[12].kinds+2 ,
                                                                       {
                                                                        lang.synts[12].kinds+2,
                                                                        lang.atoms+11,
                                                                        lang.synts[12].kinds+4
                                                                       }
    },
    { 165 , "opDiv.UN.NUM" , lang.rules+57 , lang.synts[12].kinds+2 ,
                                                                      {
                                                                       lang.synts[12].kinds+3,
                                                                       lang.atoms+11,
                                                                       lang.synts[12].kinds+4
                                                                      }
    },
    { 166 , "opDiv.NUM.NUM" , lang.rules+57 , lang.synts[12].kinds+2 ,
                                                                       {
                                                                        lang.synts[12].kinds+4,
                                                                        lang.atoms+11,
                                                                        lang.synts[12].kinds+4
                                                                       }
    },
    { 167 , "opDiv.POST.NUM" , lang.rules+57 , lang.synts[12].kinds+2 ,
                                                                        {
                                                                         lang.synts[12].kinds+5,
                                                                         lang.atoms+11,
                                                                         lang.synts[12].kinds+4
                                                                        }
    },
    { 168 , "opDiv.PRIM.NUM" , lang.rules+57 , lang.synts[12].kinds+2 ,
                                                                        {
                                                                         lang.synts[12].kinds+6,
                                                                         lang.atoms+11,
                                                                         lang.synts[12].kinds+4
                                                                        }
    },
    { 169 , "opDiv.MUL.POST" , lang.rules+57 , lang.synts[12].kinds+2 ,
                                                                        {
                                                                         lang.synts[12].kinds+2,
                                                                         lang.atoms+11,
                                                                         lang.synts[12].kinds+5
                                                                        }
    },
    { 170 , "opDiv.UN.POST" , lang.rules+57 , lang.synts[12].kinds+2 ,
                                                                       {
                                                                        lang.synts[12].kinds+3,
                                                                        lang.atoms+11,
                                                                        lang.synts[12].kinds+5
                                                                       }
    },
    { 171 , "opDiv.NUM.POST" , lang.rules+57 , lang.synts[12].kinds+2 ,
                                                                        {
                                                                         lang.synts[12].kinds+4,
                                                                         lang.atoms+11,
                                                                         lang.synts[12].kinds+5
                                                                        }
    },
    { 172 , "opDiv.POST.POST" , lang.rules+57 , lang.synts[12].kinds+2 ,
                                                                         {
                                                                          lang.synts[12].kinds+5,
                                                                          lang.atoms+11,
                                                                          lang.synts[12].kinds+5
                                                                         }
    },
    { 173 , "opDiv.PRIM.POST" , lang.rules+57 , lang.synts[12].kinds+2 ,
                                                                         {
                                                                          lang.synts[12].kinds+6,
                                                                          lang.atoms+11,
                                                                          lang.synts[12].kinds+5
                                                                         }
    },
    { 174 , "opDiv.MUL.PRIM" , lang.rules+57 , lang.synts[12].kinds+2 ,
                                                                        {
                                                                         lang.synts[12].kinds+2,
                                                                         lang.atoms+11,
                                                                         lang.synts[12].kinds+6
                                                                        }
    },
    { 175 , "opDiv.UN.PRIM" , lang.rules+57 , lang.synts[12].kinds+2 ,
                                                                       {
                                                                        lang.synts[12].kinds+3,
                                                                        lang.atoms+11,
                                                                        lang.synts[12].kinds+6
                                                                       }
    },
    { 176 , "opDiv.NUM.PRIM" , lang.rules+57 , lang.synts[12].kinds+2 ,
                                                                        {
                                                                         lang.synts[12].kinds+4,
                                                                         lang.atoms+11,
                                                                         lang.synts[12].kinds+6
                                                                        }
    },
    { 177 , "opDiv.POST.PRIM" , lang.rules+57 , lang.synts[12].kinds+2 ,
                                                                         {
                                                                          lang.synts[12].kinds+5,
                                                                          lang.atoms+11,
                                                                          lang.synts[12].kinds+6
                                                                         }
    },
    { 178 , "opDiv.PRIM.PRIM" , lang.rules+57 , lang.synts[12].kinds+2 ,
                                                                         {
                                                                          lang.synts[12].kinds+6,
                                                                          lang.atoms+11,
                                                                          lang.synts[12].kinds+6
                                                                         }
    },
    { 179 , "opRem.MUL.UN" , lang.rules+58 , lang.synts[12].kinds+2 ,
                                                                      {
                                                                       lang.synts[12].kinds+2,
                                                                       lang.atoms+1,
                                                                       lang.synts[12].kinds+3
                                                                      }
    },
    { 180 , "opRem.UN.UN" , lang.rules+58 , lang.synts[12].kinds+2 ,
                                                                     {
                                                                      lang.synts[12].kinds+3,
                                                                      lang.atoms+1,
                                                                      lang.synts[12].kinds+3
                                                                     }
    },
    { 181 , "opRem.NUM.UN" , lang.rules+58 , lang.synts[12].kinds+2 ,
                                                                      {
                                                                       lang.synts[12].kinds+4,
                                                                       lang.atoms+1,
                                                                       lang.synts[12].kinds+3
                                                                      }
    },
    { 182 , "opRem.POST.UN" , lang.rules+58 , lang.synts[12].kinds+2 ,
                                                                       {
                                                                        lang.synts[12].kinds+5,
                                                                        lang.atoms+1,
                                                                        lang.synts[12].kinds+3
                                                                       }
    },
    { 183 , "opRem.PRIM.UN" , lang.rules+58 , lang.synts[12].kinds+2 ,
                                                                       {
                                                                        lang.synts[12].kinds+6,
                                                                        lang.atoms+1,
                                                                        lang.synts[12].kinds+3
                                                                       }
    },
    { 184 , "opRem.MUL.NUM" , lang.rules+58 , lang.synts[12].kinds+2 ,
                                                                       {
                                                                        lang.synts[12].kinds+2,
                                                                        lang.atoms+1,
                                                                        lang.synts[12].kinds+4
                                                                       }
    },
    { 185 , "opRem.UN.NUM" , lang.rules+58 , lang.synts[12].kinds+2 ,
                                                                      {
                                                                       lang.synts[12].kinds+3,
                                                                       lang.atoms+1,
                                                                       lang.synts[12].kinds+4
                                                                      }
    },
    { 186 , "opRem.NUM.NUM" , lang.rules+58 , lang.synts[12].kinds+2 ,
                                                                       {
                                                                        lang.synts[12].kinds+4,
                                                                        lang.atoms+1,
                                                                        lang.synts[12].kinds+4
                                                                       }
    },
    { 187 , "opRem.POST.NUM" , lang.rules+58 , lang.synts[12].kinds+2 ,
                                                                        {
                                                                         lang.synts[12].kinds+5,
                                                                         lang.atoms+1,
                                                                         lang.synts[12].kinds+4
                                                                        }
    },
    { 188 , "opRem.PRIM.NUM" , lang.rules+58 , lang.synts[12].kinds+2 ,
                                                                        {
                                                                         lang.synts[12].kinds+6,
                                                                         lang.atoms+1,
                                                                         lang.synts[12].kinds+4
                                                                        }
    },
    { 189 , "opRem.MUL.POST" , lang.rules+58 , lang.synts[12].kinds+2 ,
                                                                        {
                                                                         lang.synts[12].kinds+2,
                                                                         lang.atoms+1,
                                                                         lang.synts[12].kinds+5
                                                                        }
    },
    { 190 , "opRem.UN.POST" , lang.rules+58 , lang.synts[12].kinds+2 ,
                                                                       {
                                                                        lang.synts[12].kinds+3,
                                                                        lang.atoms+1,
                                                                        lang.synts[12].kinds+5
                                                                       }
    },
    { 191 , "opRem.NUM.POST" , lang.rules+58 , lang.synts[12].kinds+2 ,
                                                                        {
                                                                         lang.synts[12].kinds+4,
                                                                         lang.atoms+1,
                                                                         lang.synts[12].kinds+5
                                                                        }
    },
    { 192 , "opRem.POST.POST" , lang.rules+58 , lang.synts[12].kinds+2 ,
                                                                         {
                                                                          lang.synts[12].kinds+5,
                                                                          lang.atoms+1,
                                                                          lang.synts[12].kinds+5
                                                                         }
    },
    { 193 , "opRem.PRIM.POST" , lang.rules+58 , lang.synts[12].kinds+2 ,
                                                                         {
                                                                          lang.synts[12].kinds+6,
                                                                          lang.atoms+1,
                                                                          lang.synts[12].kinds+5
                                                                         }
    },
    { 194 , "opRem.MUL.PRIM" , lang.rules+58 , lang.synts[12].kinds+2 ,
                                                                        {
                                                                         lang.synts[12].kinds+2,
                                                                         lang.atoms+1,
                                                                         lang.synts[12].kinds+6
                                                                        }
    },
    { 195 , "opRem.UN.PRIM" , lang.rules+58 , lang.synts[12].kinds+2 ,
                                                                       {
                                                                        lang.synts[12].kinds+3,
                                                                        lang.atoms+1,
                                                                        lang.synts[12].kinds+6
                                                                       }
    },
    { 196 , "opRem.NUM.PRIM" , lang.rules+58 , lang.synts[12].kinds+2 ,
                                                                        {
                                                                         lang.synts[12].kinds+4,
                                                                         lang.atoms+1,
                                                                         lang.synts[12].kinds+6
                                                                        }
    },
    { 197 , "opRem.POST.PRIM" , lang.rules+58 , lang.synts[12].kinds+2 ,
                                                                         {
                                                                          lang.synts[12].kinds+5,
                                                                          lang.atoms+1,
                                                                          lang.synts[12].kinds+6
                                                                         }
    },
    { 198 , "opRem.PRIM.PRIM" , lang.rules+58 , lang.synts[12].kinds+2 ,
                                                                         {
                                                                          lang.synts[12].kinds+6,
                                                                          lang.atoms+1,
                                                                          lang.synts[12].kinds+6
                                                                         }
    },
    { 199 , "opAst.UN" , lang.rules+52 , lang.synts[12].kinds+3 ,
                                                                  {
                                                                   lang.atoms+5,
                                                                   lang.synts[12].kinds+3
                                                                  }
    },
    { 200 , "opAst.NUM" , lang.rules+52 , lang.synts[12].kinds+3 ,
                                                                   {
                                                                    lang.atoms+5,
                                                                    lang.synts[12].kinds+4
                                                                   }
    },
    { 201 , "opAst.POST" , lang.rules+52 , lang.synts[12].kinds+3 ,
                                                                    {
                                                                     lang.atoms+5,
                                                                     lang.synts[12].kinds+5
                                                                    }
    },
    { 202 , "opAst.PRIM" , lang.rules+52 , lang.synts[12].kinds+3 ,
                                                                    {
                                                                     lang.atoms+5,
                                                                     lang.synts[12].kinds+6
                                                                    }
    },
    { 203 , "opAmp.UN" , lang.rules+53 , lang.synts[12].kinds+3 ,
                                                                  {
                                                                   lang.atoms+2,
                                                                   lang.synts[12].kinds+3
                                                                  }
    },
    { 204 , "opAmp.NUM" , lang.rules+53 , lang.synts[12].kinds+3 ,
                                                                   {
                                                                    lang.atoms+2,
                                                                    lang.synts[12].kinds+4
                                                                   }
    },
    { 205 , "opAmp.POST" , lang.rules+53 , lang.synts[12].kinds+3 ,
                                                                    {
                                                                     lang.atoms+2,
                                                                     lang.synts[12].kinds+5
                                                                    }
    },
    { 206 , "opAmp.PRIM" , lang.rules+53 , lang.synts[12].kinds+3 ,
                                                                    {
                                                                     lang.atoms+2,
                                                                     lang.synts[12].kinds+6
                                                                    }
    },
    { 207 , "opPlus.UN" , lang.rules+54 , lang.synts[12].kinds+3 ,
                                                                   {
                                                                    lang.atoms+6,
                                                                    lang.synts[12].kinds+3
                                                                   }
    },
    { 208 , "opPlus.NUM" , lang.rules+54 , lang.synts[12].kinds+3 ,
                                                                    {
                                                                     lang.atoms+6,
                                                                     lang.synts[12].kinds+4
                                                                    }
    },
    { 209 , "opPlus.POST" , lang.rules+54 , lang.synts[12].kinds+3 ,
                                                                     {
                                                                      lang.atoms+6,
                                                                      lang.synts[12].kinds+5
                                                                     }
    },
    { 210 , "opPlus.PRIM" , lang.rules+54 , lang.synts[12].kinds+3 ,
                                                                     {
                                                                      lang.atoms+6,
                                                                      lang.synts[12].kinds+6
                                                                     }
    },
    { 211 , "opMinus.UN" , lang.rules+55 , lang.synts[12].kinds+3 ,
                                                                    {
                                                                     lang.atoms+8,
                                                                     lang.synts[12].kinds+3
                                                                    }
    },
    { 212 , "opMinus.NUM" , lang.rules+55 , lang.synts[12].kinds+3 ,
                                                                     {
                                                                      lang.atoms+8,
                                                                      lang.synts[12].kinds+4
                                                                     }
    },
    { 213 , "opMinus.POST" , lang.rules+55 , lang.synts[12].kinds+3 ,
                                                                      {
                                                                       lang.atoms+8,
                                                                       lang.synts[12].kinds+5
                                                                      }
    },
    { 214 , "opMinus.PRIM" , lang.rules+55 , lang.synts[12].kinds+3 ,
                                                                      {
                                                                       lang.atoms+8,
                                                                       lang.synts[12].kinds+6
                                                                      }
    },
    { 215 , "cast_Number" , lang.rules+51 , lang.synts[12].kinds+4 ,
                                                                     {
                                                                      lang.atoms+17
                                                                     }
    },
    { 216 , "opInd.NUM.LIST" , lang.rules+48 , lang.synts[12].kinds+5 ,
                                                                        {
                                                                         lang.synts[12].kinds+4,
                                                                         lang.atoms+19,
                                                                         lang.synts[12].kinds+0,
                                                                         lang.atoms+20
                                                                        }
    },
    { 217 , "opInd.POST.LIST" , lang.rules+48 , lang.synts[12].kinds+5 ,
                                                                         {
                                                                          lang.synts[12].kinds+5,
                                                                          lang.atoms+19,
                                                                          lang.synts[12].kinds+0,
                                                                          lang.atoms+20
                                                                         }
    },
    { 218 , "opInd.PRIM.LIST" , lang.rules+48 , lang.synts[12].kinds+5 ,
                                                                         {
                                                                          lang.synts[12].kinds+6,
                                                                          lang.atoms+19,
                                                                          lang.synts[12].kinds+0,
                                                                          lang.atoms+20
                                                                         }
    },
    { 219 , "opInd.NUM.ADD" , lang.rules+48 , lang.synts[12].kinds+5 ,
                                                                       {
                                                                        lang.synts[12].kinds+4,
                                                                        lang.atoms+19,
                                                                        lang.synts[12].kinds+1,
                                                                        lang.atoms+20
                                                                       }
    },
    { 220 , "opInd.POST.ADD" , lang.rules+48 , lang.synts[12].kinds+5 ,
                                                                        {
                                                                         lang.synts[12].kinds+5,
                                                                         lang.atoms+19,
                                                                         lang.synts[12].kinds+1,
                                                                         lang.atoms+20
                                                                        }
    },
    { 221 , "opInd.PRIM.ADD" , lang.rules+48 , lang.synts[12].kinds+5 ,
                                                                        {
                                                                         lang.synts[12].kinds+6,
                                                                         lang.atoms+19,
                                                                         lang.synts[12].kinds+1,
                                                                         lang.atoms+20
                                                                        }
    },
    { 222 , "opInd.NUM.MUL" , lang.rules+48 , lang.synts[12].kinds+5 ,
                                                                       {
                                                                        lang.synts[12].kinds+4,
                                                                        lang.atoms+19,
                                                                        lang.synts[12].kinds+2,
                                                                        lang.atoms+20
                                                                       }
    },
    { 223 , "opInd.POST.MUL" , lang.rules+48 , lang.synts[12].kinds+5 ,
                                                                        {
                                                                         lang.synts[12].kinds+5,
                                                                         lang.atoms+19,
                                                                         lang.synts[12].kinds+2,
                                                                         lang.atoms+20
                                                                        }
    },
    { 224 , "opInd.PRIM.MUL" , lang.rules+48 , lang.synts[12].kinds+5 ,
                                                                        {
                                                                         lang.synts[12].kinds+6,
                                                                         lang.atoms+19,
                                                                         lang.synts[12].kinds+2,
                                                                         lang.atoms+20
                                                                        }
    },
    { 225 , "opInd.NUM.UN" , lang.rules+48 , lang.synts[12].kinds+5 ,
                                                                      {
                                                                       lang.synts[12].kinds+4,
                                                                       lang.atoms+19,
                                                                       lang.synts[12].kinds+3,
                                                                       lang.atoms+20
                                                                      }
    },
    { 226 , "opInd.POST.UN" , lang.rules+48 , lang.synts[12].kinds+5 ,
                                                                       {
                                                                        lang.synts[12].kinds+5,
                                                                        lang.atoms+19,
                                                                        lang.synts[12].kinds+3,
                                                                        lang.atoms+20
                                                                       }
    },
    { 227 , "opInd.PRIM.UN" , lang.rules+48 , lang.synts[12].kinds+5 ,
                                                                       {
                                                                        lang.synts[12].kinds+6,
                                                                        lang.atoms+19,
                                                                        lang.synts[12].kinds+3,
                                                                        lang.atoms+20
                                                                       }
    },
    { 228 , "opInd.NUM.NUM" , lang.rules+48 , lang.synts[12].kinds+5 ,
                                                                       {
                                                                        lang.synts[12].kinds+4,
                                                                        lang.atoms+19,
                                                                        lang.synts[12].kinds+4,
                                                                        lang.atoms+20
                                                                       }
    },
    { 229 , "opInd.POST.NUM" , lang.rules+48 , lang.synts[12].kinds+5 ,
                                                                        {
                                                                         lang.synts[12].kinds+5,
                                                                         lang.atoms+19,
                                                                         lang.synts[12].kinds+4,
                                                                         lang.atoms+20
                                                                        }
    },
    { 230 , "opInd.PRIM.NUM" , lang.rules+48 , lang.synts[12].kinds+5 ,
                                                                        {
                                                                         lang.synts[12].kinds+6,
                                                                         lang.atoms+19,
                                                                         lang.synts[12].kinds+4,
                                                                         lang.atoms+20
                                                                        }
    },
    { 231 , "opInd.NUM.POST" , lang.rules+48 , lang.synts[12].kinds+5 ,
                                                                        {
                                                                         lang.synts[12].kinds+4,
                                                                         lang.atoms+19,
                                                                         lang.synts[12].kinds+5,
                                                                         lang.atoms+20
                                                                        }
    },
    { 232 , "opInd.POST.POST" , lang.rules+48 , lang.synts[12].kinds+5 ,
                                                                         {
                                                                          lang.synts[12].kinds+5,
                                                                          lang.atoms+19,
                                                                          lang.synts[12].kinds+5,
                                                                          lang.atoms+20
                                                                         }
    },
    { 233 , "opInd.PRIM.POST" , lang.rules+48 , lang.synts[12].kinds+5 ,
                                                                         {
                                                                          lang.synts[12].kinds+6,
                                                                          lang.atoms+19,
                                                                          lang.synts[12].kinds+5,
                                                                          lang.atoms+20
                                                                         }
    },
    { 234 , "opInd.NUM.PRIM" , lang.rules+48 , lang.synts[12].kinds+5 ,
                                                                        {
                                                                         lang.synts[12].kinds+4,
                                                                         lang.atoms+19,
                                                                         lang.synts[12].kinds+6,
                                                                         lang.atoms+20
                                                                        }
    },
    { 235 , "opInd.POST.PRIM" , lang.rules+48 , lang.synts[12].kinds+5 ,
                                                                         {
                                                                          lang.synts[12].kinds+5,
                                                                          lang.atoms+19,
                                                                          lang.synts[12].kinds+6,
                                                                          lang.atoms+20
                                                                         }
    },
    { 236 , "opInd.PRIM.PRIM" , lang.rules+48 , lang.synts[12].kinds+5 ,
                                                                         {
                                                                          lang.synts[12].kinds+6,
                                                                          lang.atoms+19,
                                                                          lang.synts[12].kinds+6,
                                                                          lang.atoms+20
                                                                         }
    },
    { 237 , "opSelect.POST" , lang.rules+49 , lang.synts[12].kinds+5 ,
                                                                       {
                                                                        lang.synts[12].kinds+5,
                                                                        lang.atoms+10,
                                                                        lang.atoms+16
                                                                       }
    },
    { 238 , "opSelect.PRIM" , lang.rules+49 , lang.synts[12].kinds+5 ,
                                                                       {
                                                                        lang.synts[12].kinds+6,
                                                                        lang.atoms+10,
                                                                        lang.atoms+16
                                                                       }
    },
    { 239 , "opPtrSelect.POST" , lang.rules+50 , lang.synts[12].kinds+5 ,
                                                                          {
                                                                           lang.synts[12].kinds+5,
                                                                           lang.atoms+9,
                                                                           lang.atoms+16
                                                                          }
    },
    { 240 , "opPtrSelect.PRIM" , lang.rules+50 , lang.synts[12].kinds+5 ,
                                                                          {
                                                                           lang.synts[12].kinds+6,
                                                                           lang.atoms+9,
                                                                           lang.atoms+16
                                                                          }
    },
    { 241 , "cast_EXPR.LIST" , lang.rules+44 , lang.synts[12].kinds+6 ,
                                                                        {
                                                                         lang.atoms+3,
                                                                         lang.synts[12].kinds+0,
                                                                         lang.atoms+4
                                                                        }
    },
    { 242 , "cast_EXPR.ADD" , lang.rules+44 , lang.synts[12].kinds+6 ,
                                                                       {
                                                                        lang.atoms+3,
                                                                        lang.synts[12].kinds+1,
                                                                        lang.atoms+4
                                                                       }
    },
    { 243 , "cast_EXPR.MUL" , lang.rules+44 , lang.synts[12].kinds+6 ,
                                                                       {
                                                                        lang.atoms+3,
                                                                        lang.synts[12].kinds+2,
                                                                        lang.atoms+4
                                                                       }
    },
    { 244 , "cast_EXPR.UN" , lang.rules+44 , lang.synts[12].kinds+6 ,
                                                                      {
                                                                       lang.atoms+3,
                                                                       lang.synts[12].kinds+3,
                                                                       lang.atoms+4
                                                                      }
    },
    { 245 , "cast_EXPR.NUM" , lang.rules+44 , lang.synts[12].kinds+6 ,
                                                                       {
                                                                        lang.atoms+3,
                                                                        lang.synts[12].kinds+4,
                                                                        lang.atoms+4
                                                                       }
    },
    { 246 , "cast_EXPR.POST" , lang.rules+44 , lang.synts[12].kinds+6 ,
                                                                        {
                                                                         lang.atoms+3,
                                                                         lang.synts[12].kinds+5,
                                                                         lang.atoms+4
                                                                        }
    },
    { 247 , "cast_EXPR.PRIM" , lang.rules+44 , lang.synts[12].kinds+6 ,
                                                                        {
                                                                         lang.atoms+3,
                                                                         lang.synts[12].kinds+6,
                                                                         lang.atoms+4
                                                                        }
    },
    { 248 , "cast_NAME" , lang.rules+45 , lang.synts[12].kinds+6 ,
                                                                   {
                                                                    lang.synts[6].kinds+0
                                                                   }
    },
    { 249 , "cast_NNLIT" , lang.rules+46 , lang.synts[12].kinds+6 ,
                                                                    {
                                                                     lang.synts[17].kinds+0
                                                                    }
    },
    { 250 , "opDomain.LIST" , lang.rules+47 , lang.synts[12].kinds+6 ,
                                                                       {
                                                                        lang.synts[16].kinds+0,
                                                                        lang.atoms+3,
                                                                        lang.synts[12].kinds+0,
                                                                        lang.atoms+4
                                                                       }
    },
    { 251 , "opDomain.ADD" , lang.rules+47 , lang.synts[12].kinds+6 ,
                                                                      {
                                                                       lang.synts[16].kinds+0,
                                                                       lang.atoms+3,
                                                                       lang.synts[12].kinds+1,
                                                                       lang.atoms+4
                                                                      }
    },
    { 252 , "opDomain.MUL" , lang.rules+47 , lang.synts[12].kinds+6 ,
                                                                      {
                                                                       lang.synts[16].kinds+0,
                                                                       lang.atoms+3,
                                                                       lang.synts[12].kinds+2,
                                                                       lang.atoms+4
                                                                      }
    },
    { 253 , "opDomain.UN" , lang.rules+47 , lang.synts[12].kinds+6 ,
                                                                     {
                                                                      lang.synts[16].kinds+0,
                                                                      lang.atoms+3,
                                                                      lang.synts[12].kinds+3,
                                                                      lang.atoms+4
                                                                     }
    },
    { 254 , "opDomain.NUM" , lang.rules+47 , lang.synts[12].kinds+6 ,
                                                                      {
                                                                       lang.synts[16].kinds+0,
                                                                       lang.atoms+3,
                                                                       lang.synts[12].kinds+4,
                                                                       lang.atoms+4
                                                                      }
    },
    { 255 , "opDomain.POST" , lang.rules+47 , lang.synts[12].kinds+6 ,
                                                                       {
                                                                        lang.synts[16].kinds+0,
                                                                        lang.atoms+3,
                                                                        lang.synts[12].kinds+5,
                                                                        lang.atoms+4
                                                                       }
    },
    { 256 , "opDomain.PRIM" , lang.rules+47 , lang.synts[12].kinds+6 ,
                                                                       {
                                                                        lang.synts[16].kinds+0,
                                                                        lang.atoms+3,
                                                                        lang.synts[12].kinds+6,
                                                                        lang.atoms+4
                                                                       }
    },
    { 257 , "start.LIST" , lang.rules+66 , lang.synts[13].kinds+0 ,
                                                                    {
                                                                     lang.synts[12].kinds+0
                                                                    }
    },
    { 258 , "start.ADD" , lang.rules+66 , lang.synts[13].kinds+0 ,
                                                                   {
                                                                    lang.synts[12].kinds+1
                                                                   }
    },
    { 259 , "start.MUL" , lang.rules+66 , lang.synts[13].kinds+0 ,
                                                                   {
                                                                    lang.synts[12].kinds+2
                                                                   }
    },
    { 260 , "start.UN" , lang.rules+66 , lang.synts[13].kinds+0 ,
                                                                  {
                                                                   lang.synts[12].kinds+3
                                                                  }
    },
    { 261 , "start.NUM" , lang.rules+66 , lang.synts[13].kinds+0 ,
                                                                   {
                                                                    lang.synts[12].kinds+4
                                                                   }
    },
    { 262 , "start.POST" , lang.rules+66 , lang.synts[13].kinds+0 ,
                                                                    {
                                                                     lang.synts[12].kinds+5
                                                                    }
    },
    { 263 , "start.PRIM" , lang.rules+66 , lang.synts[13].kinds+0 ,
                                                                    {
                                                                     lang.synts[12].kinds+6
                                                                    }
    },
    { 264 , "ext.LIST" , lang.rules+67 , lang.synts[13].kinds+0 ,
                                                                  {
                                                                   lang.synts[13].kinds+0,
                                                                   lang.atoms+7,
                                                                   lang.synts[12].kinds+0
                                                                  }
    },
    { 265 , "ext.ADD" , lang.rules+67 , lang.synts[13].kinds+0 ,
                                                                 {
                                                                  lang.synts[13].kinds+0,
                                                                  lang.atoms+7,
                                                                  lang.synts[12].kinds+1
                                                                 }
    },
    { 266 , "ext.MUL" , lang.rules+67 , lang.synts[13].kinds+0 ,
                                                                 {
                                                                  lang.synts[13].kinds+0,
                                                                  lang.atoms+7,
                                                                  lang.synts[12].kinds+2
                                                                 }
    },
    { 267 , "ext.UN" , lang.rules+67 , lang.synts[13].kinds+0 ,
                                                                {
                                                                 lang.synts[13].kinds+0,
                                                                 lang.atoms+7,
                                                                 lang.synts[12].kinds+3
                                                                }
    },
    { 268 , "ext.NUM" , lang.rules+67 , lang.synts[13].kinds+0 ,
                                                                 {
                                                                  lang.synts[13].kinds+0,
                                                                  lang.atoms+7,
                                                                  lang.synts[12].kinds+4
                                                                 }
    },
    { 269 , "ext.POST" , lang.rules+67 , lang.synts[13].kinds+0 ,
                                                                  {
                                                                   lang.synts[13].kinds+0,
                                                                   lang.atoms+7,
                                                                   lang.synts[12].kinds+5
                                                                  }
    },
    { 270 , "ext.PRIM" , lang.rules+67 , lang.synts[13].kinds+0 ,
                                                                  {
                                                                   lang.synts[13].kinds+0,
                                                                   lang.atoms+7,
                                                                   lang.synts[12].kinds+6
                                                                  }
    },
    { 271 , "build.LIST" , lang.rules+68 , lang.synts[14].kinds+0 ,
                                                                    {
                                                                     lang.atoms+10,
                                                                     lang.atoms+16,
                                                                     lang.atoms+13,
                                                                     lang.synts[12].kinds+0
                                                                    }
    },
    { 272 , "build.ADD" , lang.rules+68 , lang.synts[14].kinds+0 ,
                                                                   {
                                                                    lang.atoms+10,
                                                                    lang.atoms+16,
                                                                    lang.atoms+13,
                                                                    lang.synts[12].kinds+1
                                                                   }
    },
    { 273 , "build.MUL" , lang.rules+68 , lang.synts[14].kinds+0 ,
                                                                   {
                                                                    lang.atoms+10,
                                                                    lang.atoms+16,
                                                                    lang.atoms+13,
                                                                    lang.synts[12].kinds+2
                                                                   }
    },
    { 274 , "build.UN" , lang.rules+68 , lang.synts[14].kinds+0 ,
                                                                  {
                                                                   lang.atoms+10,
                                                                   lang.atoms+16,
                                                                   lang.atoms+13,
                                                                   lang.synts[12].kinds+3
                                                                  }
    },
    { 275 , "build.NUM" , lang.rules+68 , lang.synts[14].kinds+0 ,
                                                                   {
                                                                    lang.atoms+10,
                                                                    lang.atoms+16,
                                                                    lang.atoms+13,
                                                                    lang.synts[12].kinds+4
                                                                   }
    },
    { 276 , "build.POST" , lang.rules+68 , lang.synts[14].kinds+0 ,
                                                                    {
                                                                     lang.atoms+10,
                                                                     lang.atoms+16,
                                                                     lang.atoms+13,
                                                                     lang.synts[12].kinds+5
                                                                    }
    },
    { 277 , "build.PRIM" , lang.rules+68 , lang.synts[14].kinds+0 ,
                                                                    {
                                                                     lang.atoms+10,
                                                                     lang.atoms+16,
                                                                     lang.atoms+13,
                                                                     lang.synts[12].kinds+6
                                                                    }
    },
    { 278 , "start" , lang.rules+69 , lang.synts[15].kinds+0 ,
                                                               {
                                                                lang.synts[14].kinds+0
                                                               }
    },
    { 279 , "ext" , lang.rules+70 , lang.synts[15].kinds+0 ,
                                                             {
                                                              lang.synts[15].kinds+0,
                                                              lang.atoms+7,
                                                              lang.synts[14].kinds+0
                                                             }
    },
    { 280 , "type_NAME" , lang.rules+71 , lang.synts[16].kinds+0 ,
                                                                   {
                                                                    lang.synts[6].kinds+0
                                                                   }
    },
    { 281 , "type_INAME" , lang.rules+72 , lang.synts[16].kinds+0 ,
                                                                    {
                                                                     lang.synts[7].kinds+0
                                                                    }
    },
    { 282 , "cast_null" , lang.rules+73 , lang.synts[17].kinds+0 ,
                                                                   {
                                                                    lang.atoms+25
                                                                   }
    },
    { 283 , "cast_String" , lang.rules+74 , lang.synts[17].kinds+0 ,
                                                                     {
                                                                      lang.atoms+18
                                                                     }
    },
    { 284 , "buildIP" , lang.rules+75 , lang.synts[17].kinds+0 ,
                                                                 {
                                                                  lang.atoms+17,
                                                                  lang.atoms+10,
                                                                  lang.atoms+17,
                                                                  lang.atoms+10,
                                                                  lang.atoms+17,
                                                                  lang.atoms+10,
                                                                  lang.atoms+17
                                                                 }
    }
   },
   {
    { 0 , lang.finals+338 ,
                            {
                             { lang.elements+43 , lang.states+593 }
                            }
    },
    { 1 , lang.finals+0 ,
                          {
                           { lang.elements+43 , lang.states+133 }
                          }
    },
    { 2 , lang.finals+1 ,
                          {
                           
                          }
    },
    { 3 , lang.finals+2 ,
                          {
                           
                          }
    },
    { 4 , lang.finals+3 ,
                          {
                           
                          }
    },
    { 5 , lang.finals+4 ,
                          {
                           
                          }
    },
    { 6 , lang.finals+5 ,
                          {
                           
                          }
    },
    { 7 , lang.finals+6 ,
                          {
                           
                          }
    },
    { 8 , lang.finals+7 ,
                          {
                           
                          }
    },
    { 9 , lang.finals+8 ,
                          {
                           
                          }
    },
    { 10 , lang.finals+9 ,
                           {
                            
                           }
    },
    { 11 , lang.finals+10 ,
                            {
                             
                            }
    },
    { 12 , lang.finals+11 ,
                            {
                             
                            }
    },
    { 13 , lang.finals+12 ,
                            {
                             
                            }
    },
    { 14 , lang.finals+13 ,
                            {
                             
                            }
    },
    { 15 , lang.finals+14 ,
                            {
                             
                            }
    },
    { 16 , lang.finals+15 ,
                            {
                             
                            }
    },
    { 17 , lang.finals+16 ,
                            {
                             
                            }
    },
    { 18 , lang.finals+17 ,
                            {
                             
                            }
    },
    { 19 , lang.finals+18 ,
                            {
                             
                            }
    },
    { 20 , lang.finals+19 ,
                            {
                             
                            }
    },
    { 21 , lang.finals+20 ,
                            {
                             
                            }
    },
    { 22 , lang.finals+21 ,
                            {
                             
                            }
    },
    { 23 , lang.finals+22 ,
                            {
                             
                            }
    },
    { 24 , lang.finals+23 ,
                            {
                             
                            }
    },
    { 25 , lang.finals+24 ,
                            {
                             { lang.elements+54 , lang.states+129 }
                            }
    },
    { 26 , lang.finals+24 ,
                            {
                             { lang.elements+54 , lang.states+130 }
                            }
    },
    { 27 , lang.finals+24 ,
                            {
                             { lang.elements+54 , lang.states+131 }
                            }
    },
    { 28 , lang.finals+25 ,
                            {
                             
                            }
    },
    { 29 , lang.finals+26 ,
                            {
                             
                            }
    },
    { 30 , lang.finals+27 ,
                            {
                             
                            }
    },
    { 31 , lang.finals+28 ,
                            {
                             
                            }
    },
    { 32 , lang.finals+29 ,
                            {
                             
                            }
    },
    { 33 , lang.finals+30 ,
                            {
                             { lang.elements+0 , lang.states+515 }
                            }
    },
    { 34 , lang.finals+30 ,
                            {
                             { lang.elements+0 , lang.states+516 }
                            }
    },
    { 35 , lang.finals+30 ,
                            {
                             { lang.elements+0 , lang.states+518 }
                            }
    },
    { 36 , lang.finals+30 ,
                            {
                             { lang.elements+0 , lang.states+519 }
                            }
    },
    { 37 , lang.finals+30 ,
                            {
                             { lang.elements+0 , lang.states+521 }
                            }
    },
    { 38 , lang.finals+30 ,
                            {
                             { lang.elements+0 , lang.states+522 }
                            }
    },
    { 39 , lang.finals+30 ,
                            {
                             { lang.elements+0 , lang.states+524 }
                            }
    },
    { 40 , lang.finals+30 ,
                            {
                             { lang.elements+0 , lang.states+525 }
                            }
    },
    { 41 , lang.finals+30 ,
                            {
                             { lang.elements+0 , lang.states+527 }
                            }
    },
    { 42 , lang.finals+30 ,
                            {
                             { lang.elements+0 , lang.states+528 }
                            }
    },
    { 43 , lang.finals+30 ,
                            {
                             { lang.elements+0 , lang.states+530 }
                            }
    },
    { 44 , lang.finals+30 ,
                            {
                             { lang.elements+0 , lang.states+531 }
                            }
    },
    { 45 , lang.finals+31 ,
                            {
                             { lang.elements+0 , lang.states+532 }
                            }
    },
    { 46 , lang.finals+32 ,
                            {
                             { lang.elements+0 , lang.states+533 }
                            }
    },
    { 47 , lang.finals+33 ,
                            {
                             { lang.elements+0 , lang.states+534 }
                            }
    },
    { 48 , lang.finals+34 ,
                            {
                             { lang.elements+0 , lang.states+535 }
                            }
    },
    { 49 , lang.finals+35 ,
                            {
                             { lang.elements+0 , lang.states+532 }
                            }
    },
    { 50 , lang.finals+36 ,
                            {
                             { lang.elements+0 , lang.states+533 }
                            }
    },
    { 51 , lang.finals+37 ,
                            {
                             { lang.elements+0 , lang.states+534 }
                            }
    },
    { 52 , lang.finals+38 ,
                            {
                             { lang.elements+0 , lang.states+535 }
                            }
    },
    { 53 , lang.finals+39 ,
                            {
                             { lang.elements+0 , lang.states+532 }
                            }
    },
    { 54 , lang.finals+40 ,
                            {
                             { lang.elements+0 , lang.states+533 }
                            }
    },
    { 55 , lang.finals+41 ,
                            {
                             { lang.elements+0 , lang.states+534 }
                            }
    },
    { 56 , lang.finals+42 ,
                            {
                             { lang.elements+0 , lang.states+535 }
                            }
    },
    { 57 , lang.finals+43 ,
                            {
                             { lang.elements+0 , lang.states+532 }
                            }
    },
    { 58 , lang.finals+44 ,
                            {
                             { lang.elements+0 , lang.states+533 }
                            }
    },
    { 59 , lang.finals+45 ,
                            {
                             { lang.elements+0 , lang.states+534 }
                            }
    },
    { 60 , lang.finals+46 ,
                            {
                             { lang.elements+0 , lang.states+535 }
                            }
    },
    { 61 , lang.finals+47 ,
                            {
                             { lang.elements+0 , lang.states+523 },
                             { lang.elements+2 , lang.states+93 },
                             { lang.elements+3 , lang.states+102 },
                             { lang.elements+5 , lang.states+92 },
                             { lang.elements+6 , lang.states+94 },
                             { lang.elements+8 , lang.states+95 },
                             { lang.elements+10 , lang.states+39 },
                             { lang.elements+14 , lang.states+40 },
                             { lang.elements+16 , lang.states+16 },
                             { lang.elements+17 , lang.states+170 },
                             { lang.elements+18 , lang.states+262 },
                             { lang.elements+20 , lang.states+428 },
                             { lang.elements+23 , lang.states+354 },
                             { lang.elements+25 , lang.states+258 },
                             { lang.elements+27 , lang.states+355 },
                             { lang.elements+28 , lang.states+360 },
                             { lang.elements+29 , lang.states+362 },
                             { lang.elements+30 , lang.states+364 },
                             { lang.elements+31 , lang.states+358 },
                             { lang.elements+35 , lang.states+356 },
                             { lang.elements+36 , lang.states+361 },
                             { lang.elements+37 , lang.states+363 },
                             { lang.elements+38 , lang.states+365 },
                             { lang.elements+39 , lang.states+359 },
                             { lang.elements+40 , lang.states+357 },
                             { lang.elements+41 , lang.states+120 },
                             { lang.elements+48 , lang.states+48 },
                             { lang.elements+49 , lang.states+146 },
                             { lang.elements+50 , lang.states+366 },
                             { lang.elements+55 , lang.states+576 },
                             { lang.elements+56 , lang.states+458 },
                             { lang.elements+57 , lang.states+352 },
                             { lang.elements+58 , lang.states+352 },
                             { lang.elements+59 , lang.states+346 },
                             { lang.elements+60 , lang.states+332 },
                             { lang.elements+61 , lang.states+332 },
                             { lang.elements+65 , lang.states+370 },
                             { lang.elements+66 , lang.states+150 }
                            }
    },
    { 62 , lang.finals+47 ,
                            {
                             { lang.elements+0 , lang.states+523 },
                             { lang.elements+2 , lang.states+93 },
                             { lang.elements+3 , lang.states+102 },
                             { lang.elements+5 , lang.states+92 },
                             { lang.elements+6 , lang.states+94 },
                             { lang.elements+8 , lang.states+95 },
                             { lang.elements+10 , lang.states+39 },
                             { lang.elements+14 , lang.states+40 },
                             { lang.elements+16 , lang.states+16 },
                             { lang.elements+17 , lang.states+170 },
                             { lang.elements+18 , lang.states+262 },
                             { lang.elements+20 , lang.states+429 },
                             { lang.elements+23 , lang.states+354 },
                             { lang.elements+25 , lang.states+258 },
                             { lang.elements+27 , lang.states+355 },
                             { lang.elements+28 , lang.states+360 },
                             { lang.elements+29 , lang.states+362 },
                             { lang.elements+30 , lang.states+364 },
                             { lang.elements+31 , lang.states+358 },
                             { lang.elements+35 , lang.states+356 },
                             { lang.elements+36 , lang.states+361 },
                             { lang.elements+37 , lang.states+363 },
                             { lang.elements+38 , lang.states+365 },
                             { lang.elements+39 , lang.states+359 },
                             { lang.elements+40 , lang.states+357 },
                             { lang.elements+41 , lang.states+120 },
                             { lang.elements+48 , lang.states+48 },
                             { lang.elements+49 , lang.states+146 },
                             { lang.elements+50 , lang.states+366 },
                             { lang.elements+55 , lang.states+577 },
                             { lang.elements+56 , lang.states+459 },
                             { lang.elements+57 , lang.states+353 },
                             { lang.elements+58 , lang.states+353 },
                             { lang.elements+59 , lang.states+347 },
                             { lang.elements+60 , lang.states+333 },
                             { lang.elements+61 , lang.states+333 },
                             { lang.elements+65 , lang.states+370 },
                             { lang.elements+66 , lang.states+150 }
                            }
    },
    { 63 , lang.finals+48 ,
                            {
                             { lang.elements+0 , lang.states+514 },
                             { lang.elements+2 , lang.states+66 },
                             { lang.elements+3 , lang.states+99 },
                             { lang.elements+5 , lang.states+65 },
                             { lang.elements+6 , lang.states+67 },
                             { lang.elements+8 , lang.states+68 },
                             { lang.elements+10 , lang.states+33 },
                             { lang.elements+14 , lang.states+34 },
                             { lang.elements+16 , lang.states+13 },
                             { lang.elements+17 , lang.states+167 },
                             { lang.elements+18 , lang.states+259 },
                             { lang.elements+23 , lang.states+354 },
                             { lang.elements+25 , lang.states+255 },
                             { lang.elements+27 , lang.states+355 },
                             { lang.elements+28 , lang.states+360 },
                             { lang.elements+29 , lang.states+362 },
                             { lang.elements+30 , lang.states+364 },
                             { lang.elements+31 , lang.states+358 },
                             { lang.elements+35 , lang.states+356 },
                             { lang.elements+36 , lang.states+361 },
                             { lang.elements+37 , lang.states+363 },
                             { lang.elements+38 , lang.states+365 },
                             { lang.elements+39 , lang.states+359 },
                             { lang.elements+40 , lang.states+357 },
                             { lang.elements+48 , lang.states+45 },
                             { lang.elements+49 , lang.states+143 },
                             { lang.elements+50 , lang.states+366 },
                             { lang.elements+57 , lang.states+269 },
                             { lang.elements+58 , lang.states+269 },
                             { lang.elements+59 , lang.states+268 },
                             { lang.elements+60 , lang.states+267 },
                             { lang.elements+61 , lang.states+267 },
                             { lang.elements+65 , lang.states+367 },
                             { lang.elements+66 , lang.states+147 }
                            }
    },
    { 64 , lang.finals+48 ,
                            {
                             { lang.elements+0 , lang.states+514 },
                             { lang.elements+2 , lang.states+66 },
                             { lang.elements+3 , lang.states+99 },
                             { lang.elements+5 , lang.states+65 },
                             { lang.elements+6 , lang.states+67 },
                             { lang.elements+8 , lang.states+68 },
                             { lang.elements+10 , lang.states+33 },
                             { lang.elements+14 , lang.states+34 },
                             { lang.elements+16 , lang.states+13 },
                             { lang.elements+17 , lang.states+167 },
                             { lang.elements+18 , lang.states+259 },
                             { lang.elements+23 , lang.states+354 },
                             { lang.elements+25 , lang.states+255 },
                             { lang.elements+27 , lang.states+355 },
                             { lang.elements+28 , lang.states+360 },
                             { lang.elements+29 , lang.states+362 },
                             { lang.elements+30 , lang.states+364 },
                             { lang.elements+31 , lang.states+358 },
                             { lang.elements+35 , lang.states+356 },
                             { lang.elements+36 , lang.states+361 },
                             { lang.elements+37 , lang.states+363 },
                             { lang.elements+38 , lang.states+365 },
                             { lang.elements+39 , lang.states+359 },
                             { lang.elements+40 , lang.states+357 },
                             { lang.elements+48 , lang.states+45 },
                             { lang.elements+49 , lang.states+143 },
                             { lang.elements+50 , lang.states+366 },
                             { lang.elements+57 , lang.states+272 },
                             { lang.elements+58 , lang.states+272 },
                             { lang.elements+59 , lang.states+271 },
                             { lang.elements+60 , lang.states+270 },
                             { lang.elements+61 , lang.states+270 },
                             { lang.elements+65 , lang.states+367 },
                             { lang.elements+66 , lang.states+147 }
                            }
    },
    { 65 , lang.finals+48 ,
                            {
                             { lang.elements+0 , lang.states+514 },
                             { lang.elements+2 , lang.states+66 },
                             { lang.elements+3 , lang.states+99 },
                             { lang.elements+5 , lang.states+65 },
                             { lang.elements+6 , lang.states+67 },
                             { lang.elements+8 , lang.states+68 },
                             { lang.elements+10 , lang.states+33 },
                             { lang.elements+14 , lang.states+34 },
                             { lang.elements+16 , lang.states+13 },
                             { lang.elements+17 , lang.states+167 },
                             { lang.elements+18 , lang.states+259 },
                             { lang.elements+23 , lang.states+354 },
                             { lang.elements+25 , lang.states+255 },
                             { lang.elements+27 , lang.states+355 },
                             { lang.elements+28 , lang.states+360 },
                             { lang.elements+29 , lang.states+362 },
                             { lang.elements+30 , lang.states+364 },
                             { lang.elements+31 , lang.states+358 },
                             { lang.elements+35 , lang.states+356 },
                             { lang.elements+36 , lang.states+361 },
                             { lang.elements+37 , lang.states+363 },
                             { lang.elements+38 , lang.states+365 },
                             { lang.elements+39 , lang.states+359 },
                             { lang.elements+40 , lang.states+357 },
                             { lang.elements+48 , lang.states+45 },
                             { lang.elements+49 , lang.states+143 },
                             { lang.elements+50 , lang.states+366 },
                             { lang.elements+58 , lang.states+173 },
                             { lang.elements+59 , lang.states+172 },
                             { lang.elements+60 , lang.states+171 },
                             { lang.elements+61 , lang.states+171 },
                             { lang.elements+65 , lang.states+367 },
                             { lang.elements+66 , lang.states+147 }
                            }
    },
    { 66 , lang.finals+48 ,
                            {
                             { lang.elements+0 , lang.states+514 },
                             { lang.elements+2 , lang.states+66 },
                             { lang.elements+3 , lang.states+99 },
                             { lang.elements+5 , lang.states+65 },
                             { lang.elements+6 , lang.states+67 },
                             { lang.elements+8 , lang.states+68 },
                             { lang.elements+10 , lang.states+33 },
                             { lang.elements+14 , lang.states+34 },
                             { lang.elements+16 , lang.states+13 },
                             { lang.elements+17 , lang.states+167 },
                             { lang.elements+18 , lang.states+259 },
                             { lang.elements+23 , lang.states+354 },
                             { lang.elements+25 , lang.states+255 },
                             { lang.elements+27 , lang.states+355 },
                             { lang.elements+28 , lang.states+360 },
                             { lang.elements+29 , lang.states+362 },
                             { lang.elements+30 , lang.states+364 },
                             { lang.elements+31 , lang.states+358 },
                             { lang.elements+35 , lang.states+356 },
                             { lang.elements+36 , lang.states+361 },
                             { lang.elements+37 , lang.states+363 },
                             { lang.elements+38 , lang.states+365 },
                             { lang.elements+39 , lang.states+359 },
                             { lang.elements+40 , lang.states+357 },
                             { lang.elements+48 , lang.states+45 },
                             { lang.elements+49 , lang.states+143 },
                             { lang.elements+50 , lang.states+366 },
                             { lang.elements+58 , lang.states+185 },
                             { lang.elements+59 , lang.states+184 },
                             { lang.elements+60 , lang.states+183 },
                             { lang.elements+61 , lang.states+183 },
                             { lang.elements+65 , lang.states+367 },
                             { lang.elements+66 , lang.states+147 }
                            }
    },
    { 67 , lang.finals+48 ,
                            {
                             { lang.elements+0 , lang.states+514 },
                             { lang.elements+2 , lang.states+66 },
                             { lang.elements+3 , lang.states+99 },
                             { lang.elements+5 , lang.states+65 },
                             { lang.elements+6 , lang.states+67 },
                             { lang.elements+8 , lang.states+68 },
                             { lang.elements+10 , lang.states+33 },
                             { lang.elements+14 , lang.states+34 },
                             { lang.elements+16 , lang.states+13 },
                             { lang.elements+17 , lang.states+167 },
                             { lang.elements+18 , lang.states+259 },
                             { lang.elements+23 , lang.states+354 },
                             { lang.elements+25 , lang.states+255 },
                             { lang.elements+27 , lang.states+355 },
                             { lang.elements+28 , lang.states+360 },
                             { lang.elements+29 , lang.states+362 },
                             { lang.elements+30 , lang.states+364 },
                             { lang.elements+31 , lang.states+358 },
                             { lang.elements+35 , lang.states+356 },
                             { lang.elements+36 , lang.states+361 },
                             { lang.elements+37 , lang.states+363 },
                             { lang.elements+38 , lang.states+365 },
                             { lang.elements+39 , lang.states+359 },
                             { lang.elements+40 , lang.states+357 },
                             { lang.elements+48 , lang.states+45 },
                             { lang.elements+49 , lang.states+143 },
                             { lang.elements+50 , lang.states+366 },
                             { lang.elements+58 , lang.states+197 },
                             { lang.elements+59 , lang.states+196 },
                             { lang.elements+60 , lang.states+195 },
                             { lang.elements+61 , lang.states+195 },
                             { lang.elements+65 , lang.states+367 },
                             { lang.elements+66 , lang.states+147 }
                            }
    },
    { 68 , lang.finals+48 ,
                            {
                             { lang.elements+0 , lang.states+514 },
                             { lang.elements+2 , lang.states+66 },
                             { lang.elements+3 , lang.states+99 },
                             { lang.elements+5 , lang.states+65 },
                             { lang.elements+6 , lang.states+67 },
                             { lang.elements+8 , lang.states+68 },
                             { lang.elements+10 , lang.states+33 },
                             { lang.elements+14 , lang.states+34 },
                             { lang.elements+16 , lang.states+13 },
                             { lang.elements+17 , lang.states+167 },
                             { lang.elements+18 , lang.states+259 },
                             { lang.elements+23 , lang.states+354 },
                             { lang.elements+25 , lang.states+255 },
                             { lang.elements+27 , lang.states+355 },
                             { lang.elements+28 , lang.states+360 },
                             { lang.elements+29 , lang.states+362 },
                             { lang.elements+30 , lang.states+364 },
                             { lang.elements+31 , lang.states+358 },
                             { lang.elements+35 , lang.states+356 },
                             { lang.elements+36 , lang.states+361 },
                             { lang.elements+37 , lang.states+363 },
                             { lang.elements+38 , lang.states+365 },
                             { lang.elements+39 , lang.states+359 },
                             { lang.elements+40 , lang.states+357 },
                             { lang.elements+48 , lang.states+45 },
                             { lang.elements+49 , lang.states+143 },
                             { lang.elements+50 , lang.states+366 },
                             { lang.elements+58 , lang.states+209 },
                             { lang.elements+59 , lang.states+208 },
                             { lang.elements+60 , lang.states+207 },
                             { lang.elements+61 , lang.states+207 },
                             { lang.elements+65 , lang.states+367 },
                             { lang.elements+66 , lang.states+147 }
                            }
    },
    { 69 , lang.finals+48 ,
                            {
                             { lang.elements+0 , lang.states+514 },
                             { lang.elements+2 , lang.states+66 },
                             { lang.elements+3 , lang.states+99 },
                             { lang.elements+5 , lang.states+65 },
                             { lang.elements+6 , lang.states+67 },
                             { lang.elements+8 , lang.states+68 },
                             { lang.elements+10 , lang.states+33 },
                             { lang.elements+14 , lang.states+34 },
                             { lang.elements+16 , lang.states+13 },
                             { lang.elements+17 , lang.states+167 },
                             { lang.elements+18 , lang.states+259 },
                             { lang.elements+23 , lang.states+354 },
                             { lang.elements+25 , lang.states+255 },
                             { lang.elements+27 , lang.states+355 },
                             { lang.elements+28 , lang.states+360 },
                             { lang.elements+29 , lang.states+362 },
                             { lang.elements+30 , lang.states+364 },
                             { lang.elements+31 , lang.states+358 },
                             { lang.elements+35 , lang.states+356 },
                             { lang.elements+36 , lang.states+361 },
                             { lang.elements+37 , lang.states+363 },
                             { lang.elements+38 , lang.states+365 },
                             { lang.elements+39 , lang.states+359 },
                             { lang.elements+40 , lang.states+357 },
                             { lang.elements+48 , lang.states+45 },
                             { lang.elements+49 , lang.states+143 },
                             { lang.elements+50 , lang.states+366 },
                             { lang.elements+58 , lang.states+221 },
                             { lang.elements+59 , lang.states+220 },
                             { lang.elements+60 , lang.states+219 },
                             { lang.elements+61 , lang.states+219 },
                             { lang.elements+65 , lang.states+367 },
                             { lang.elements+66 , lang.states+147 }
                            }
    },
    { 70 , lang.finals+48 ,
                            {
                             { lang.elements+0 , lang.states+514 },
                             { lang.elements+2 , lang.states+66 },
                             { lang.elements+3 , lang.states+99 },
                             { lang.elements+5 , lang.states+65 },
                             { lang.elements+6 , lang.states+67 },
                             { lang.elements+8 , lang.states+68 },
                             { lang.elements+10 , lang.states+33 },
                             { lang.elements+14 , lang.states+34 },
                             { lang.elements+16 , lang.states+13 },
                             { lang.elements+17 , lang.states+167 },
                             { lang.elements+18 , lang.states+259 },
                             { lang.elements+23 , lang.states+354 },
                             { lang.elements+25 , lang.states+255 },
                             { lang.elements+27 , lang.states+355 },
                             { lang.elements+28 , lang.states+360 },
                             { lang.elements+29 , lang.states+362 },
                             { lang.elements+30 , lang.states+364 },
                             { lang.elements+31 , lang.states+358 },
                             { lang.elements+35 , lang.states+356 },
                             { lang.elements+36 , lang.states+361 },
                             { lang.elements+37 , lang.states+363 },
                             { lang.elements+38 , lang.states+365 },
                             { lang.elements+39 , lang.states+359 },
                             { lang.elements+40 , lang.states+357 },
                             { lang.elements+48 , lang.states+45 },
                             { lang.elements+49 , lang.states+143 },
                             { lang.elements+50 , lang.states+366 },
                             { lang.elements+58 , lang.states+233 },
                             { lang.elements+59 , lang.states+232 },
                             { lang.elements+60 , lang.states+231 },
                             { lang.elements+61 , lang.states+231 },
                             { lang.elements+65 , lang.states+367 },
                             { lang.elements+66 , lang.states+147 }
                            }
    },
    { 71 , lang.finals+48 ,
                            {
                             { lang.elements+0 , lang.states+514 },
                             { lang.elements+2 , lang.states+66 },
                             { lang.elements+3 , lang.states+99 },
                             { lang.elements+5 , lang.states+65 },
                             { lang.elements+6 , lang.states+67 },
                             { lang.elements+8 , lang.states+68 },
                             { lang.elements+10 , lang.states+33 },
                             { lang.elements+14 , lang.states+34 },
                             { lang.elements+16 , lang.states+13 },
                             { lang.elements+17 , lang.states+167 },
                             { lang.elements+18 , lang.states+259 },
                             { lang.elements+23 , lang.states+354 },
                             { lang.elements+25 , lang.states+255 },
                             { lang.elements+27 , lang.states+355 },
                             { lang.elements+28 , lang.states+360 },
                             { lang.elements+29 , lang.states+362 },
                             { lang.elements+30 , lang.states+364 },
                             { lang.elements+31 , lang.states+358 },
                             { lang.elements+35 , lang.states+356 },
                             { lang.elements+36 , lang.states+361 },
                             { lang.elements+37 , lang.states+363 },
                             { lang.elements+38 , lang.states+365 },
                             { lang.elements+39 , lang.states+359 },
                             { lang.elements+40 , lang.states+357 },
                             { lang.elements+48 , lang.states+45 },
                             { lang.elements+49 , lang.states+143 },
                             { lang.elements+50 , lang.states+366 },
                             { lang.elements+58 , lang.states+245 },
                             { lang.elements+59 , lang.states+244 },
                             { lang.elements+60 , lang.states+243 },
                             { lang.elements+61 , lang.states+243 },
                             { lang.elements+65 , lang.states+367 },
                             { lang.elements+66 , lang.states+147 }
                            }
    },
    { 72 , lang.finals+48 ,
                            {
                             { lang.elements+0 , lang.states+517 },
                             { lang.elements+2 , lang.states+75 },
                             { lang.elements+3 , lang.states+100 },
                             { lang.elements+5 , lang.states+74 },
                             { lang.elements+6 , lang.states+76 },
                             { lang.elements+8 , lang.states+77 },
                             { lang.elements+10 , lang.states+35 },
                             { lang.elements+14 , lang.states+36 },
                             { lang.elements+16 , lang.states+14 },
                             { lang.elements+17 , lang.states+168 },
                             { lang.elements+18 , lang.states+260 },
                             { lang.elements+23 , lang.states+354 },
                             { lang.elements+25 , lang.states+256 },
                             { lang.elements+27 , lang.states+355 },
                             { lang.elements+28 , lang.states+360 },
                             { lang.elements+29 , lang.states+362 },
                             { lang.elements+30 , lang.states+364 },
                             { lang.elements+31 , lang.states+358 },
                             { lang.elements+35 , lang.states+356 },
                             { lang.elements+36 , lang.states+361 },
                             { lang.elements+37 , lang.states+363 },
                             { lang.elements+38 , lang.states+365 },
                             { lang.elements+39 , lang.states+359 },
                             { lang.elements+40 , lang.states+357 },
                             { lang.elements+48 , lang.states+46 },
                             { lang.elements+49 , lang.states+144 },
                             { lang.elements+50 , lang.states+366 },
                             { lang.elements+57 , lang.states+299 },
                             { lang.elements+58 , lang.states+299 },
                             { lang.elements+59 , lang.states+298 },
                             { lang.elements+60 , lang.states+297 },
                             { lang.elements+61 , lang.states+297 },
                             { lang.elements+65 , lang.states+368 },
                             { lang.elements+66 , lang.states+148 }
                            }
    },
    { 73 , lang.finals+48 ,
                            {
                             { lang.elements+0 , lang.states+517 },
                             { lang.elements+2 , lang.states+75 },
                             { lang.elements+3 , lang.states+100 },
                             { lang.elements+5 , lang.states+74 },
                             { lang.elements+6 , lang.states+76 },
                             { lang.elements+8 , lang.states+77 },
                             { lang.elements+10 , lang.states+35 },
                             { lang.elements+14 , lang.states+36 },
                             { lang.elements+16 , lang.states+14 },
                             { lang.elements+17 , lang.states+168 },
                             { lang.elements+18 , lang.states+260 },
                             { lang.elements+23 , lang.states+354 },
                             { lang.elements+25 , lang.states+256 },
                             { lang.elements+27 , lang.states+355 },
                             { lang.elements+28 , lang.states+360 },
                             { lang.elements+29 , lang.states+362 },
                             { lang.elements+30 , lang.states+364 },
                             { lang.elements+31 , lang.states+358 },
                             { lang.elements+35 , lang.states+356 },
                             { lang.elements+36 , lang.states+361 },
                             { lang.elements+37 , lang.states+363 },
                             { lang.elements+38 , lang.states+365 },
                             { lang.elements+39 , lang.states+359 },
                             { lang.elements+40 , lang.states+357 },
                             { lang.elements+48 , lang.states+46 },
                             { lang.elements+49 , lang.states+144 },
                             { lang.elements+50 , lang.states+366 },
                             { lang.elements+57 , lang.states+308 },
                             { lang.elements+58 , lang.states+308 },
                             { lang.elements+59 , lang.states+307 },
                             { lang.elements+60 , lang.states+306 },
                             { lang.elements+61 , lang.states+306 },
                             { lang.elements+65 , lang.states+368 },
                             { lang.elements+66 , lang.states+148 }
                            }
    },
    { 74 , lang.finals+48 ,
                            {
                             { lang.elements+0 , lang.states+517 },
                             { lang.elements+2 , lang.states+75 },
                             { lang.elements+3 , lang.states+100 },
                             { lang.elements+5 , lang.states+74 },
                             { lang.elements+6 , lang.states+76 },
                             { lang.elements+8 , lang.states+77 },
                             { lang.elements+10 , lang.states+35 },
                             { lang.elements+14 , lang.states+36 },
                             { lang.elements+16 , lang.states+14 },
                             { lang.elements+17 , lang.states+168 },
                             { lang.elements+18 , lang.states+260 },
                             { lang.elements+23 , lang.states+354 },
                             { lang.elements+25 , lang.states+256 },
                             { lang.elements+27 , lang.states+355 },
                             { lang.elements+28 , lang.states+360 },
                             { lang.elements+29 , lang.states+362 },
                             { lang.elements+30 , lang.states+364 },
                             { lang.elements+31 , lang.states+358 },
                             { lang.elements+35 , lang.states+356 },
                             { lang.elements+36 , lang.states+361 },
                             { lang.elements+37 , lang.states+363 },
                             { lang.elements+38 , lang.states+365 },
                             { lang.elements+39 , lang.states+359 },
                             { lang.elements+40 , lang.states+357 },
                             { lang.elements+48 , lang.states+46 },
                             { lang.elements+49 , lang.states+144 },
                             { lang.elements+50 , lang.states+366 },
                             { lang.elements+58 , lang.states+176 },
                             { lang.elements+59 , lang.states+175 },
                             { lang.elements+60 , lang.states+174 },
                             { lang.elements+61 , lang.states+174 },
                             { lang.elements+65 , lang.states+368 },
                             { lang.elements+66 , lang.states+148 }
                            }
    },
    { 75 , lang.finals+48 ,
                            {
                             { lang.elements+0 , lang.states+517 },
                             { lang.elements+2 , lang.states+75 },
                             { lang.elements+3 , lang.states+100 },
                             { lang.elements+5 , lang.states+74 },
                             { lang.elements+6 , lang.states+76 },
                             { lang.elements+8 , lang.states+77 },
                             { lang.elements+10 , lang.states+35 },
                             { lang.elements+14 , lang.states+36 },
                             { lang.elements+16 , lang.states+14 },
                             { lang.elements+17 , lang.states+168 },
                             { lang.elements+18 , lang.states+260 },
                             { lang.elements+23 , lang.states+354 },
                             { lang.elements+25 , lang.states+256 },
                             { lang.elements+27 , lang.states+355 },
                             { lang.elements+28 , lang.states+360 },
                             { lang.elements+29 , lang.states+362 },
                             { lang.elements+30 , lang.states+364 },
                             { lang.elements+31 , lang.states+358 },
                             { lang.elements+35 , lang.states+356 },
                             { lang.elements+36 , lang.states+361 },
                             { lang.elements+37 , lang.states+363 },
                             { lang.elements+38 , lang.states+365 },
                             { lang.elements+39 , lang.states+359 },
                             { lang.elements+40 , lang.states+357 },
                             { lang.elements+48 , lang.states+46 },
                             { lang.elements+49 , lang.states+144 },
                             { lang.elements+50 , lang.states+366 },
                             { lang.elements+58 , lang.states+188 },
                             { lang.elements+59 , lang.states+187 },
                             { lang.elements+60 , lang.states+186 },
                             { lang.elements+61 , lang.states+186 },
                             { lang.elements+65 , lang.states+368 },
                             { lang.elements+66 , lang.states+148 }
                            }
    },
    { 76 , lang.finals+48 ,
                            {
                             { lang.elements+0 , lang.states+517 },
                             { lang.elements+2 , lang.states+75 },
                             { lang.elements+3 , lang.states+100 },
                             { lang.elements+5 , lang.states+74 },
                             { lang.elements+6 , lang.states+76 },
                             { lang.elements+8 , lang.states+77 },
                             { lang.elements+10 , lang.states+35 },
                             { lang.elements+14 , lang.states+36 },
                             { lang.elements+16 , lang.states+14 },
                             { lang.elements+17 , lang.states+168 },
                             { lang.elements+18 , lang.states+260 },
                             { lang.elements+23 , lang.states+354 },
                             { lang.elements+25 , lang.states+256 },
                             { lang.elements+27 , lang.states+355 },
                             { lang.elements+28 , lang.states+360 },
                             { lang.elements+29 , lang.states+362 },
                             { lang.elements+30 , lang.states+364 },
                             { lang.elements+31 , lang.states+358 },
                             { lang.elements+35 , lang.states+356 },
                             { lang.elements+36 , lang.states+361 },
                             { lang.elements+37 , lang.states+363 },
                             { lang.elements+38 , lang.states+365 },
                             { lang.elements+39 , lang.states+359 },
                             { lang.elements+40 , lang.states+357 },
                             { lang.elements+48 , lang.states+46 },
                             { lang.elements+49 , lang.states+144 },
                             { lang.elements+50 , lang.states+366 },
                             { lang.elements+58 , lang.states+200 },
                             { lang.elements+59 , lang.states+199 },
                             { lang.elements+60 , lang.states+198 },
                             { lang.elements+61 , lang.states+198 },
                             { lang.elements+65 , lang.states+368 },
                             { lang.elements+66 , lang.states+148 }
                            }
    },
    { 77 , lang.finals+48 ,
                            {
                             { lang.elements+0 , lang.states+517 },
                             { lang.elements+2 , lang.states+75 },
                             { lang.elements+3 , lang.states+100 },
                             { lang.elements+5 , lang.states+74 },
                             { lang.elements+6 , lang.states+76 },
                             { lang.elements+8 , lang.states+77 },
                             { lang.elements+10 , lang.states+35 },
                             { lang.elements+14 , lang.states+36 },
                             { lang.elements+16 , lang.states+14 },
                             { lang.elements+17 , lang.states+168 },
                             { lang.elements+18 , lang.states+260 },
                             { lang.elements+23 , lang.states+354 },
                             { lang.elements+25 , lang.states+256 },
                             { lang.elements+27 , lang.states+355 },
                             { lang.elements+28 , lang.states+360 },
                             { lang.elements+29 , lang.states+362 },
                             { lang.elements+30 , lang.states+364 },
                             { lang.elements+31 , lang.states+358 },
                             { lang.elements+35 , lang.states+356 },
                             { lang.elements+36 , lang.states+361 },
                             { lang.elements+37 , lang.states+363 },
                             { lang.elements+38 , lang.states+365 },
                             { lang.elements+39 , lang.states+359 },
                             { lang.elements+40 , lang.states+357 },
                             { lang.elements+48 , lang.states+46 },
                             { lang.elements+49 , lang.states+144 },
                             { lang.elements+50 , lang.states+366 },
                             { lang.elements+58 , lang.states+212 },
                             { lang.elements+59 , lang.states+211 },
                             { lang.elements+60 , lang.states+210 },
                             { lang.elements+61 , lang.states+210 },
                             { lang.elements+65 , lang.states+368 },
                             { lang.elements+66 , lang.states+148 }
                            }
    },
    { 78 , lang.finals+48 ,
                            {
                             { lang.elements+0 , lang.states+517 },
                             { lang.elements+2 , lang.states+75 },
                             { lang.elements+3 , lang.states+100 },
                             { lang.elements+5 , lang.states+74 },
                             { lang.elements+6 , lang.states+76 },
                             { lang.elements+8 , lang.states+77 },
                             { lang.elements+10 , lang.states+35 },
                             { lang.elements+14 , lang.states+36 },
                             { lang.elements+16 , lang.states+14 },
                             { lang.elements+17 , lang.states+168 },
                             { lang.elements+18 , lang.states+260 },
                             { lang.elements+23 , lang.states+354 },
                             { lang.elements+25 , lang.states+256 },
                             { lang.elements+27 , lang.states+355 },
                             { lang.elements+28 , lang.states+360 },
                             { lang.elements+29 , lang.states+362 },
                             { lang.elements+30 , lang.states+364 },
                             { lang.elements+31 , lang.states+358 },
                             { lang.elements+35 , lang.states+356 },
                             { lang.elements+36 , lang.states+361 },
                             { lang.elements+37 , lang.states+363 },
                             { lang.elements+38 , lang.states+365 },
                             { lang.elements+39 , lang.states+359 },
                             { lang.elements+40 , lang.states+357 },
                             { lang.elements+48 , lang.states+46 },
                             { lang.elements+49 , lang.states+144 },
                             { lang.elements+50 , lang.states+366 },
                             { lang.elements+58 , lang.states+224 },
                             { lang.elements+59 , lang.states+223 },
                             { lang.elements+60 , lang.states+222 },
                             { lang.elements+61 , lang.states+222 },
                             { lang.elements+65 , lang.states+368 },
                             { lang.elements+66 , lang.states+148 }
                            }
    },
    { 79 , lang.finals+48 ,
                            {
                             { lang.elements+0 , lang.states+517 },
                             { lang.elements+2 , lang.states+75 },
                             { lang.elements+3 , lang.states+100 },
                             { lang.elements+5 , lang.states+74 },
                             { lang.elements+6 , lang.states+76 },
                             { lang.elements+8 , lang.states+77 },
                             { lang.elements+10 , lang.states+35 },
                             { lang.elements+14 , lang.states+36 },
                             { lang.elements+16 , lang.states+14 },
                             { lang.elements+17 , lang.states+168 },
                             { lang.elements+18 , lang.states+260 },
                             { lang.elements+23 , lang.states+354 },
                             { lang.elements+25 , lang.states+256 },
                             { lang.elements+27 , lang.states+355 },
                             { lang.elements+28 , lang.states+360 },
                             { lang.elements+29 , lang.states+362 },
                             { lang.elements+30 , lang.states+364 },
                             { lang.elements+31 , lang.states+358 },
                             { lang.elements+35 , lang.states+356 },
                             { lang.elements+36 , lang.states+361 },
                             { lang.elements+37 , lang.states+363 },
                             { lang.elements+38 , lang.states+365 },
                             { lang.elements+39 , lang.states+359 },
                             { lang.elements+40 , lang.states+357 },
                             { lang.elements+48 , lang.states+46 },
                             { lang.elements+49 , lang.states+144 },
                             { lang.elements+50 , lang.states+366 },
                             { lang.elements+58 , lang.states+236 },
                             { lang.elements+59 , lang.states+235 },
                             { lang.elements+60 , lang.states+234 },
                             { lang.elements+61 , lang.states+234 },
                             { lang.elements+65 , lang.states+368 },
                             { lang.elements+66 , lang.states+148 }
                            }
    },
    { 80 , lang.finals+48 ,
                            {
                             { lang.elements+0 , lang.states+517 },
                             { lang.elements+2 , lang.states+75 },
                             { lang.elements+3 , lang.states+100 },
                             { lang.elements+5 , lang.states+74 },
                             { lang.elements+6 , lang.states+76 },
                             { lang.elements+8 , lang.states+77 },
                             { lang.elements+10 , lang.states+35 },
                             { lang.elements+14 , lang.states+36 },
                             { lang.elements+16 , lang.states+14 },
                             { lang.elements+17 , lang.states+168 },
                             { lang.elements+18 , lang.states+260 },
                             { lang.elements+23 , lang.states+354 },
                             { lang.elements+25 , lang.states+256 },
                             { lang.elements+27 , lang.states+355 },
                             { lang.elements+28 , lang.states+360 },
                             { lang.elements+29 , lang.states+362 },
                             { lang.elements+30 , lang.states+364 },
                             { lang.elements+31 , lang.states+358 },
                             { lang.elements+35 , lang.states+356 },
                             { lang.elements+36 , lang.states+361 },
                             { lang.elements+37 , lang.states+363 },
                             { lang.elements+38 , lang.states+365 },
                             { lang.elements+39 , lang.states+359 },
                             { lang.elements+40 , lang.states+357 },
                             { lang.elements+48 , lang.states+46 },
                             { lang.elements+49 , lang.states+144 },
                             { lang.elements+50 , lang.states+366 },
                             { lang.elements+58 , lang.states+248 },
                             { lang.elements+59 , lang.states+247 },
                             { lang.elements+60 , lang.states+246 },
                             { lang.elements+61 , lang.states+246 },
                             { lang.elements+65 , lang.states+368 },
                             { lang.elements+66 , lang.states+148 }
                            }
    },
    { 81 , lang.finals+48 ,
                            {
                             { lang.elements+0 , lang.states+520 },
                             { lang.elements+2 , lang.states+84 },
                             { lang.elements+3 , lang.states+101 },
                             { lang.elements+5 , lang.states+83 },
                             { lang.elements+6 , lang.states+85 },
                             { lang.elements+8 , lang.states+86 },
                             { lang.elements+10 , lang.states+37 },
                             { lang.elements+14 , lang.states+38 },
                             { lang.elements+16 , lang.states+15 },
                             { lang.elements+17 , lang.states+169 },
                             { lang.elements+18 , lang.states+261 },
                             { lang.elements+23 , lang.states+354 },
                             { lang.elements+25 , lang.states+257 },
                             { lang.elements+27 , lang.states+355 },
                             { lang.elements+28 , lang.states+360 },
                             { lang.elements+29 , lang.states+362 },
                             { lang.elements+30 , lang.states+364 },
                             { lang.elements+31 , lang.states+358 },
                             { lang.elements+35 , lang.states+356 },
                             { lang.elements+36 , lang.states+361 },
                             { lang.elements+37 , lang.states+363 },
                             { lang.elements+38 , lang.states+365 },
                             { lang.elements+39 , lang.states+359 },
                             { lang.elements+40 , lang.states+357 },
                             { lang.elements+48 , lang.states+47 },
                             { lang.elements+49 , lang.states+145 },
                             { lang.elements+50 , lang.states+366 },
                             { lang.elements+57 , lang.states+303 },
                             { lang.elements+58 , lang.states+303 },
                             { lang.elements+59 , lang.states+302 },
                             { lang.elements+60 , lang.states+300 },
                             { lang.elements+61 , lang.states+300 },
                             { lang.elements+65 , lang.states+369 },
                             { lang.elements+66 , lang.states+149 }
                            }
    },
    { 82 , lang.finals+48 ,
                            {
                             { lang.elements+0 , lang.states+520 },
                             { lang.elements+2 , lang.states+84 },
                             { lang.elements+3 , lang.states+101 },
                             { lang.elements+5 , lang.states+83 },
                             { lang.elements+6 , lang.states+85 },
                             { lang.elements+8 , lang.states+86 },
                             { lang.elements+10 , lang.states+37 },
                             { lang.elements+14 , lang.states+38 },
                             { lang.elements+16 , lang.states+15 },
                             { lang.elements+17 , lang.states+169 },
                             { lang.elements+18 , lang.states+261 },
                             { lang.elements+23 , lang.states+354 },
                             { lang.elements+25 , lang.states+257 },
                             { lang.elements+27 , lang.states+355 },
                             { lang.elements+28 , lang.states+360 },
                             { lang.elements+29 , lang.states+362 },
                             { lang.elements+30 , lang.states+364 },
                             { lang.elements+31 , lang.states+358 },
                             { lang.elements+35 , lang.states+356 },
                             { lang.elements+36 , lang.states+361 },
                             { lang.elements+37 , lang.states+363 },
                             { lang.elements+38 , lang.states+365 },
                             { lang.elements+39 , lang.states+359 },
                             { lang.elements+40 , lang.states+357 },
                             { lang.elements+48 , lang.states+47 },
                             { lang.elements+49 , lang.states+145 },
                             { lang.elements+50 , lang.states+366 },
                             { lang.elements+57 , lang.states+312 },
                             { lang.elements+58 , lang.states+312 },
                             { lang.elements+59 , lang.states+311 },
                             { lang.elements+60 , lang.states+309 },
                             { lang.elements+61 , lang.states+309 },
                             { lang.elements+65 , lang.states+369 },
                             { lang.elements+66 , lang.states+149 }
                            }
    },
    { 83 , lang.finals+48 ,
                            {
                             { lang.elements+0 , lang.states+520 },
                             { lang.elements+2 , lang.states+84 },
                             { lang.elements+3 , lang.states+101 },
                             { lang.elements+5 , lang.states+83 },
                             { lang.elements+6 , lang.states+85 },
                             { lang.elements+8 , lang.states+86 },
                             { lang.elements+10 , lang.states+37 },
                             { lang.elements+14 , lang.states+38 },
                             { lang.elements+16 , lang.states+15 },
                             { lang.elements+17 , lang.states+169 },
                             { lang.elements+18 , lang.states+261 },
                             { lang.elements+23 , lang.states+354 },
                             { lang.elements+25 , lang.states+257 },
                             { lang.elements+27 , lang.states+355 },
                             { lang.elements+28 , lang.states+360 },
                             { lang.elements+29 , lang.states+362 },
                             { lang.elements+30 , lang.states+364 },
                             { lang.elements+31 , lang.states+358 },
                             { lang.elements+35 , lang.states+356 },
                             { lang.elements+36 , lang.states+361 },
                             { lang.elements+37 , lang.states+363 },
                             { lang.elements+38 , lang.states+365 },
                             { lang.elements+39 , lang.states+359 },
                             { lang.elements+40 , lang.states+357 },
                             { lang.elements+48 , lang.states+47 },
                             { lang.elements+49 , lang.states+145 },
                             { lang.elements+50 , lang.states+366 },
                             { lang.elements+58 , lang.states+180 },
                             { lang.elements+59 , lang.states+179 },
                             { lang.elements+60 , lang.states+177 },
                             { lang.elements+61 , lang.states+177 },
                             { lang.elements+65 , lang.states+369 },
                             { lang.elements+66 , lang.states+149 }
                            }
    },
    { 84 , lang.finals+48 ,
                            {
                             { lang.elements+0 , lang.states+520 },
                             { lang.elements+2 , lang.states+84 },
                             { lang.elements+3 , lang.states+101 },
                             { lang.elements+5 , lang.states+83 },
                             { lang.elements+6 , lang.states+85 },
                             { lang.elements+8 , lang.states+86 },
                             { lang.elements+10 , lang.states+37 },
                             { lang.elements+14 , lang.states+38 },
                             { lang.elements+16 , lang.states+15 },
                             { lang.elements+17 , lang.states+169 },
                             { lang.elements+18 , lang.states+261 },
                             { lang.elements+23 , lang.states+354 },
                             { lang.elements+25 , lang.states+257 },
                             { lang.elements+27 , lang.states+355 },
                             { lang.elements+28 , lang.states+360 },
                             { lang.elements+29 , lang.states+362 },
                             { lang.elements+30 , lang.states+364 },
                             { lang.elements+31 , lang.states+358 },
                             { lang.elements+35 , lang.states+356 },
                             { lang.elements+36 , lang.states+361 },
                             { lang.elements+37 , lang.states+363 },
                             { lang.elements+38 , lang.states+365 },
                             { lang.elements+39 , lang.states+359 },
                             { lang.elements+40 , lang.states+357 },
                             { lang.elements+48 , lang.states+47 },
                             { lang.elements+49 , lang.states+145 },
                             { lang.elements+50 , lang.states+366 },
                             { lang.elements+58 , lang.states+192 },
                             { lang.elements+59 , lang.states+191 },
                             { lang.elements+60 , lang.states+189 },
                             { lang.elements+61 , lang.states+189 },
                             { lang.elements+65 , lang.states+369 },
                             { lang.elements+66 , lang.states+149 }
                            }
    },
    { 85 , lang.finals+48 ,
                            {
                             { lang.elements+0 , lang.states+520 },
                             { lang.elements+2 , lang.states+84 },
                             { lang.elements+3 , lang.states+101 },
                             { lang.elements+5 , lang.states+83 },
                             { lang.elements+6 , lang.states+85 },
                             { lang.elements+8 , lang.states+86 },
                             { lang.elements+10 , lang.states+37 },
                             { lang.elements+14 , lang.states+38 },
                             { lang.elements+16 , lang.states+15 },
                             { lang.elements+17 , lang.states+169 },
                             { lang.elements+18 , lang.states+261 },
                             { lang.elements+23 , lang.states+354 },
                             { lang.elements+25 , lang.states+257 },
                             { lang.elements+27 , lang.states+355 },
                             { lang.elements+28 , lang.states+360 },
                             { lang.elements+29 , lang.states+362 },
                             { lang.elements+30 , lang.states+364 },
                             { lang.elements+31 , lang.states+358 },
                             { lang.elements+35 , lang.states+356 },
                             { lang.elements+36 , lang.states+361 },
                             { lang.elements+37 , lang.states+363 },
                             { lang.elements+38 , lang.states+365 },
                             { lang.elements+39 , lang.states+359 },
                             { lang.elements+40 , lang.states+357 },
                             { lang.elements+48 , lang.states+47 },
                             { lang.elements+49 , lang.states+145 },
                             { lang.elements+50 , lang.states+366 },
                             { lang.elements+58 , lang.states+204 },
                             { lang.elements+59 , lang.states+203 },
                             { lang.elements+60 , lang.states+201 },
                             { lang.elements+61 , lang.states+201 },
                             { lang.elements+65 , lang.states+369 },
                             { lang.elements+66 , lang.states+149 }
                            }
    },
    { 86 , lang.finals+48 ,
                            {
                             { lang.elements+0 , lang.states+520 },
                             { lang.elements+2 , lang.states+84 },
                             { lang.elements+3 , lang.states+101 },
                             { lang.elements+5 , lang.states+83 },
                             { lang.elements+6 , lang.states+85 },
                             { lang.elements+8 , lang.states+86 },
                             { lang.elements+10 , lang.states+37 },
                             { lang.elements+14 , lang.states+38 },
                             { lang.elements+16 , lang.states+15 },
                             { lang.elements+17 , lang.states+169 },
                             { lang.elements+18 , lang.states+261 },
                             { lang.elements+23 , lang.states+354 },
                             { lang.elements+25 , lang.states+257 },
                             { lang.elements+27 , lang.states+355 },
                             { lang.elements+28 , lang.states+360 },
                             { lang.elements+29 , lang.states+362 },
                             { lang.elements+30 , lang.states+364 },
                             { lang.elements+31 , lang.states+358 },
                             { lang.elements+35 , lang.states+356 },
                             { lang.elements+36 , lang.states+361 },
                             { lang.elements+37 , lang.states+363 },
                             { lang.elements+38 , lang.states+365 },
                             { lang.elements+39 , lang.states+359 },
                             { lang.elements+40 , lang.states+357 },
                             { lang.elements+48 , lang.states+47 },
                             { lang.elements+49 , lang.states+145 },
                             { lang.elements+50 , lang.states+366 },
                             { lang.elements+58 , lang.states+216 },
                             { lang.elements+59 , lang.states+215 },
                             { lang.elements+60 , lang.states+213 },
                             { lang.elements+61 , lang.states+213 },
                             { lang.elements+65 , lang.states+369 },
                             { lang.elements+66 , lang.states+149 }
                            }
    },
    { 87 , lang.finals+48 ,
                            {
                             { lang.elements+0 , lang.states+520 },
                             { lang.elements+2 , lang.states+84 },
                             { lang.elements+3 , lang.states+101 },
                             { lang.elements+5 , lang.states+83 },
                             { lang.elements+6 , lang.states+85 },
                             { lang.elements+8 , lang.states+86 },
                             { lang.elements+10 , lang.states+37 },
                             { lang.elements+14 , lang.states+38 },
                             { lang.elements+16 , lang.states+15 },
                             { lang.elements+17 , lang.states+169 },
                             { lang.elements+18 , lang.states+261 },
                             { lang.elements+23 , lang.states+354 },
                             { lang.elements+25 , lang.states+257 },
                             { lang.elements+27 , lang.states+355 },
                             { lang.elements+28 , lang.states+360 },
                             { lang.elements+29 , lang.states+362 },
                             { lang.elements+30 , lang.states+364 },
                             { lang.elements+31 , lang.states+358 },
                             { lang.elements+35 , lang.states+356 },
                             { lang.elements+36 , lang.states+361 },
                             { lang.elements+37 , lang.states+363 },
                             { lang.elements+38 , lang.states+365 },
                             { lang.elements+39 , lang.states+359 },
                             { lang.elements+40 , lang.states+357 },
                             { lang.elements+48 , lang.states+47 },
                             { lang.elements+49 , lang.states+145 },
                             { lang.elements+50 , lang.states+366 },
                             { lang.elements+58 , lang.states+228 },
                             { lang.elements+59 , lang.states+227 },
                             { lang.elements+60 , lang.states+225 },
                             { lang.elements+61 , lang.states+225 },
                             { lang.elements+65 , lang.states+369 },
                             { lang.elements+66 , lang.states+149 }
                            }
    },
    { 88 , lang.finals+48 ,
                            {
                             { lang.elements+0 , lang.states+520 },
                             { lang.elements+2 , lang.states+84 },
                             { lang.elements+3 , lang.states+101 },
                             { lang.elements+5 , lang.states+83 },
                             { lang.elements+6 , lang.states+85 },
                             { lang.elements+8 , lang.states+86 },
                             { lang.elements+10 , lang.states+37 },
                             { lang.elements+14 , lang.states+38 },
                             { lang.elements+16 , lang.states+15 },
                             { lang.elements+17 , lang.states+169 },
                             { lang.elements+18 , lang.states+261 },
                             { lang.elements+23 , lang.states+354 },
                             { lang.elements+25 , lang.states+257 },
                             { lang.elements+27 , lang.states+355 },
                             { lang.elements+28 , lang.states+360 },
                             { lang.elements+29 , lang.states+362 },
                             { lang.elements+30 , lang.states+364 },
                             { lang.elements+31 , lang.states+358 },
                             { lang.elements+35 , lang.states+356 },
                             { lang.elements+36 , lang.states+361 },
                             { lang.elements+37 , lang.states+363 },
                             { lang.elements+38 , lang.states+365 },
                             { lang.elements+39 , lang.states+359 },
                             { lang.elements+40 , lang.states+357 },
                             { lang.elements+48 , lang.states+47 },
                             { lang.elements+49 , lang.states+145 },
                             { lang.elements+50 , lang.states+366 },
                             { lang.elements+58 , lang.states+240 },
                             { lang.elements+59 , lang.states+239 },
                             { lang.elements+60 , lang.states+237 },
                             { lang.elements+61 , lang.states+237 },
                             { lang.elements+65 , lang.states+369 },
                             { lang.elements+66 , lang.states+149 }
                            }
    },
    { 89 , lang.finals+48 ,
                            {
                             { lang.elements+0 , lang.states+520 },
                             { lang.elements+2 , lang.states+84 },
                             { lang.elements+3 , lang.states+101 },
                             { lang.elements+5 , lang.states+83 },
                             { lang.elements+6 , lang.states+85 },
                             { lang.elements+8 , lang.states+86 },
                             { lang.elements+10 , lang.states+37 },
                             { lang.elements+14 , lang.states+38 },
                             { lang.elements+16 , lang.states+15 },
                             { lang.elements+17 , lang.states+169 },
                             { lang.elements+18 , lang.states+261 },
                             { lang.elements+23 , lang.states+354 },
                             { lang.elements+25 , lang.states+257 },
                             { lang.elements+27 , lang.states+355 },
                             { lang.elements+28 , lang.states+360 },
                             { lang.elements+29 , lang.states+362 },
                             { lang.elements+30 , lang.states+364 },
                             { lang.elements+31 , lang.states+358 },
                             { lang.elements+35 , lang.states+356 },
                             { lang.elements+36 , lang.states+361 },
                             { lang.elements+37 , lang.states+363 },
                             { lang.elements+38 , lang.states+365 },
                             { lang.elements+39 , lang.states+359 },
                             { lang.elements+40 , lang.states+357 },
                             { lang.elements+48 , lang.states+47 },
                             { lang.elements+49 , lang.states+145 },
                             { lang.elements+50 , lang.states+366 },
                             { lang.elements+58 , lang.states+252 },
                             { lang.elements+59 , lang.states+251 },
                             { lang.elements+60 , lang.states+249 },
                             { lang.elements+61 , lang.states+249 },
                             { lang.elements+65 , lang.states+369 },
                             { lang.elements+66 , lang.states+149 }
                            }
    },
    { 90 , lang.finals+48 ,
                            {
                             { lang.elements+0 , lang.states+523 },
                             { lang.elements+2 , lang.states+93 },
                             { lang.elements+3 , lang.states+102 },
                             { lang.elements+5 , lang.states+92 },
                             { lang.elements+6 , lang.states+94 },
                             { lang.elements+8 , lang.states+95 },
                             { lang.elements+10 , lang.states+39 },
                             { lang.elements+14 , lang.states+40 },
                             { lang.elements+16 , lang.states+16 },
                             { lang.elements+17 , lang.states+170 },
                             { lang.elements+18 , lang.states+262 },
                             { lang.elements+23 , lang.states+354 },
                             { lang.elements+25 , lang.states+258 },
                             { lang.elements+27 , lang.states+355 },
                             { lang.elements+28 , lang.states+360 },
                             { lang.elements+29 , lang.states+362 },
                             { lang.elements+30 , lang.states+364 },
                             { lang.elements+31 , lang.states+358 },
                             { lang.elements+35 , lang.states+356 },
                             { lang.elements+36 , lang.states+361 },
                             { lang.elements+37 , lang.states+363 },
                             { lang.elements+38 , lang.states+365 },
                             { lang.elements+39 , lang.states+359 },
                             { lang.elements+40 , lang.states+357 },
                             { lang.elements+48 , lang.states+48 },
                             { lang.elements+49 , lang.states+146 },
                             { lang.elements+50 , lang.states+366 },
                             { lang.elements+57 , lang.states+305 },
                             { lang.elements+58 , lang.states+305 },
                             { lang.elements+59 , lang.states+304 },
                             { lang.elements+60 , lang.states+301 },
                             { lang.elements+61 , lang.states+301 },
                             { lang.elements+65 , lang.states+370 },
                             { lang.elements+66 , lang.states+150 }
                            }
    },
    { 91 , lang.finals+48 ,
                            {
                             { lang.elements+0 , lang.states+523 },
                             { lang.elements+2 , lang.states+93 },
                             { lang.elements+3 , lang.states+102 },
                             { lang.elements+5 , lang.states+92 },
                             { lang.elements+6 , lang.states+94 },
                             { lang.elements+8 , lang.states+95 },
                             { lang.elements+10 , lang.states+39 },
                             { lang.elements+14 , lang.states+40 },
                             { lang.elements+16 , lang.states+16 },
                             { lang.elements+17 , lang.states+170 },
                             { lang.elements+18 , lang.states+262 },
                             { lang.elements+23 , lang.states+354 },
                             { lang.elements+25 , lang.states+258 },
                             { lang.elements+27 , lang.states+355 },
                             { lang.elements+28 , lang.states+360 },
                             { lang.elements+29 , lang.states+362 },
                             { lang.elements+30 , lang.states+364 },
                             { lang.elements+31 , lang.states+358 },
                             { lang.elements+35 , lang.states+356 },
                             { lang.elements+36 , lang.states+361 },
                             { lang.elements+37 , lang.states+363 },
                             { lang.elements+38 , lang.states+365 },
                             { lang.elements+39 , lang.states+359 },
                             { lang.elements+40 , lang.states+357 },
                             { lang.elements+48 , lang.states+48 },
                             { lang.elements+49 , lang.states+146 },
                             { lang.elements+50 , lang.states+366 },
                             { lang.elements+57 , lang.states+314 },
                             { lang.elements+58 , lang.states+314 },
                             { lang.elements+59 , lang.states+313 },
                             { lang.elements+60 , lang.states+310 },
                             { lang.elements+61 , lang.states+310 },
                             { lang.elements+65 , lang.states+370 },
                             { lang.elements+66 , lang.states+150 }
                            }
    },
    { 92 , lang.finals+48 ,
                            {
                             { lang.elements+0 , lang.states+523 },
                             { lang.elements+2 , lang.states+93 },
                             { lang.elements+3 , lang.states+102 },
                             { lang.elements+5 , lang.states+92 },
                             { lang.elements+6 , lang.states+94 },
                             { lang.elements+8 , lang.states+95 },
                             { lang.elements+10 , lang.states+39 },
                             { lang.elements+14 , lang.states+40 },
                             { lang.elements+16 , lang.states+16 },
                             { lang.elements+17 , lang.states+170 },
                             { lang.elements+18 , lang.states+262 },
                             { lang.elements+23 , lang.states+354 },
                             { lang.elements+25 , lang.states+258 },
                             { lang.elements+27 , lang.states+355 },
                             { lang.elements+28 , lang.states+360 },
                             { lang.elements+29 , lang.states+362 },
                             { lang.elements+30 , lang.states+364 },
                             { lang.elements+31 , lang.states+358 },
                             { lang.elements+35 , lang.states+356 },
                             { lang.elements+36 , lang.states+361 },
                             { lang.elements+37 , lang.states+363 },
                             { lang.elements+38 , lang.states+365 },
                             { lang.elements+39 , lang.states+359 },
                             { lang.elements+40 , lang.states+357 },
                             { lang.elements+48 , lang.states+48 },
                             { lang.elements+49 , lang.states+146 },
                             { lang.elements+50 , lang.states+366 },
                             { lang.elements+58 , lang.states+182 },
                             { lang.elements+59 , lang.states+181 },
                             { lang.elements+60 , lang.states+178 },
                             { lang.elements+61 , lang.states+178 },
                             { lang.elements+65 , lang.states+370 },
                             { lang.elements+66 , lang.states+150 }
                            }
    },
    { 93 , lang.finals+48 ,
                            {
                             { lang.elements+0 , lang.states+523 },
                             { lang.elements+2 , lang.states+93 },
                             { lang.elements+3 , lang.states+102 },
                             { lang.elements+5 , lang.states+92 },
                             { lang.elements+6 , lang.states+94 },
                             { lang.elements+8 , lang.states+95 },
                             { lang.elements+10 , lang.states+39 },
                             { lang.elements+14 , lang.states+40 },
                             { lang.elements+16 , lang.states+16 },
                             { lang.elements+17 , lang.states+170 },
                             { lang.elements+18 , lang.states+262 },
                             { lang.elements+23 , lang.states+354 },
                             { lang.elements+25 , lang.states+258 },
                             { lang.elements+27 , lang.states+355 },
                             { lang.elements+28 , lang.states+360 },
                             { lang.elements+29 , lang.states+362 },
                             { lang.elements+30 , lang.states+364 },
                             { lang.elements+31 , lang.states+358 },
                             { lang.elements+35 , lang.states+356 },
                             { lang.elements+36 , lang.states+361 },
                             { lang.elements+37 , lang.states+363 },
                             { lang.elements+38 , lang.states+365 },
                             { lang.elements+39 , lang.states+359 },
                             { lang.elements+40 , lang.states+357 },
                             { lang.elements+48 , lang.states+48 },
                             { lang.elements+49 , lang.states+146 },
                             { lang.elements+50 , lang.states+366 },
                             { lang.elements+58 , lang.states+194 },
                             { lang.elements+59 , lang.states+193 },
                             { lang.elements+60 , lang.states+190 },
                             { lang.elements+61 , lang.states+190 },
                             { lang.elements+65 , lang.states+370 },
                             { lang.elements+66 , lang.states+150 }
                            }
    },
    { 94 , lang.finals+48 ,
                            {
                             { lang.elements+0 , lang.states+523 },
                             { lang.elements+2 , lang.states+93 },
                             { lang.elements+3 , lang.states+102 },
                             { lang.elements+5 , lang.states+92 },
                             { lang.elements+6 , lang.states+94 },
                             { lang.elements+8 , lang.states+95 },
                             { lang.elements+10 , lang.states+39 },
                             { lang.elements+14 , lang.states+40 },
                             { lang.elements+16 , lang.states+16 },
                             { lang.elements+17 , lang.states+170 },
                             { lang.elements+18 , lang.states+262 },
                             { lang.elements+23 , lang.states+354 },
                             { lang.elements+25 , lang.states+258 },
                             { lang.elements+27 , lang.states+355 },
                             { lang.elements+28 , lang.states+360 },
                             { lang.elements+29 , lang.states+362 },
                             { lang.elements+30 , lang.states+364 },
                             { lang.elements+31 , lang.states+358 },
                             { lang.elements+35 , lang.states+356 },
                             { lang.elements+36 , lang.states+361 },
                             { lang.elements+37 , lang.states+363 },
                             { lang.elements+38 , lang.states+365 },
                             { lang.elements+39 , lang.states+359 },
                             { lang.elements+40 , lang.states+357 },
                             { lang.elements+48 , lang.states+48 },
                             { lang.elements+49 , lang.states+146 },
                             { lang.elements+50 , lang.states+366 },
                             { lang.elements+58 , lang.states+206 },
                             { lang.elements+59 , lang.states+205 },
                             { lang.elements+60 , lang.states+202 },
                             { lang.elements+61 , lang.states+202 },
                             { lang.elements+65 , lang.states+370 },
                             { lang.elements+66 , lang.states+150 }
                            }
    },
    { 95 , lang.finals+48 ,
                            {
                             { lang.elements+0 , lang.states+523 },
                             { lang.elements+2 , lang.states+93 },
                             { lang.elements+3 , lang.states+102 },
                             { lang.elements+5 , lang.states+92 },
                             { lang.elements+6 , lang.states+94 },
                             { lang.elements+8 , lang.states+95 },
                             { lang.elements+10 , lang.states+39 },
                             { lang.elements+14 , lang.states+40 },
                             { lang.elements+16 , lang.states+16 },
                             { lang.elements+17 , lang.states+170 },
                             { lang.elements+18 , lang.states+262 },
                             { lang.elements+23 , lang.states+354 },
                             { lang.elements+25 , lang.states+258 },
                             { lang.elements+27 , lang.states+355 },
                             { lang.elements+28 , lang.states+360 },
                             { lang.elements+29 , lang.states+362 },
                             { lang.elements+30 , lang.states+364 },
                             { lang.elements+31 , lang.states+358 },
                             { lang.elements+35 , lang.states+356 },
                             { lang.elements+36 , lang.states+361 },
                             { lang.elements+37 , lang.states+363 },
                             { lang.elements+38 , lang.states+365 },
                             { lang.elements+39 , lang.states+359 },
                             { lang.elements+40 , lang.states+357 },
                             { lang.elements+48 , lang.states+48 },
                             { lang.elements+49 , lang.states+146 },
                             { lang.elements+50 , lang.states+366 },
                             { lang.elements+58 , lang.states+218 },
                             { lang.elements+59 , lang.states+217 },
                             { lang.elements+60 , lang.states+214 },
                             { lang.elements+61 , lang.states+214 },
                             { lang.elements+65 , lang.states+370 },
                             { lang.elements+66 , lang.states+150 }
                            }
    },
    { 96 , lang.finals+48 ,
                            {
                             { lang.elements+0 , lang.states+523 },
                             { lang.elements+2 , lang.states+93 },
                             { lang.elements+3 , lang.states+102 },
                             { lang.elements+5 , lang.states+92 },
                             { lang.elements+6 , lang.states+94 },
                             { lang.elements+8 , lang.states+95 },
                             { lang.elements+10 , lang.states+39 },
                             { lang.elements+14 , lang.states+40 },
                             { lang.elements+16 , lang.states+16 },
                             { lang.elements+17 , lang.states+170 },
                             { lang.elements+18 , lang.states+262 },
                             { lang.elements+23 , lang.states+354 },
                             { lang.elements+25 , lang.states+258 },
                             { lang.elements+27 , lang.states+355 },
                             { lang.elements+28 , lang.states+360 },
                             { lang.elements+29 , lang.states+362 },
                             { lang.elements+30 , lang.states+364 },
                             { lang.elements+31 , lang.states+358 },
                             { lang.elements+35 , lang.states+356 },
                             { lang.elements+36 , lang.states+361 },
                             { lang.elements+37 , lang.states+363 },
                             { lang.elements+38 , lang.states+365 },
                             { lang.elements+39 , lang.states+359 },
                             { lang.elements+40 , lang.states+357 },
                             { lang.elements+48 , lang.states+48 },
                             { lang.elements+49 , lang.states+146 },
                             { lang.elements+50 , lang.states+366 },
                             { lang.elements+58 , lang.states+230 },
                             { lang.elements+59 , lang.states+229 },
                             { lang.elements+60 , lang.states+226 },
                             { lang.elements+61 , lang.states+226 },
                             { lang.elements+65 , lang.states+370 },
                             { lang.elements+66 , lang.states+150 }
                            }
    },
    { 97 , lang.finals+48 ,
                            {
                             { lang.elements+0 , lang.states+523 },
                             { lang.elements+2 , lang.states+93 },
                             { lang.elements+3 , lang.states+102 },
                             { lang.elements+5 , lang.states+92 },
                             { lang.elements+6 , lang.states+94 },
                             { lang.elements+8 , lang.states+95 },
                             { lang.elements+10 , lang.states+39 },
                             { lang.elements+14 , lang.states+40 },
                             { lang.elements+16 , lang.states+16 },
                             { lang.elements+17 , lang.states+170 },
                             { lang.elements+18 , lang.states+262 },
                             { lang.elements+23 , lang.states+354 },
                             { lang.elements+25 , lang.states+258 },
                             { lang.elements+27 , lang.states+355 },
                             { lang.elements+28 , lang.states+360 },
                             { lang.elements+29 , lang.states+362 },
                             { lang.elements+30 , lang.states+364 },
                             { lang.elements+31 , lang.states+358 },
                             { lang.elements+35 , lang.states+356 },
                             { lang.elements+36 , lang.states+361 },
                             { lang.elements+37 , lang.states+363 },
                             { lang.elements+38 , lang.states+365 },
                             { lang.elements+39 , lang.states+359 },
                             { lang.elements+40 , lang.states+357 },
                             { lang.elements+48 , lang.states+48 },
                             { lang.elements+49 , lang.states+146 },
                             { lang.elements+50 , lang.states+366 },
                             { lang.elements+58 , lang.states+242 },
                             { lang.elements+59 , lang.states+241 },
                             { lang.elements+60 , lang.states+238 },
                             { lang.elements+61 , lang.states+238 },
                             { lang.elements+65 , lang.states+370 },
                             { lang.elements+66 , lang.states+150 }
                            }
    },
    { 98 , lang.finals+48 ,
                            {
                             { lang.elements+0 , lang.states+523 },
                             { lang.elements+2 , lang.states+93 },
                             { lang.elements+3 , lang.states+102 },
                             { lang.elements+5 , lang.states+92 },
                             { lang.elements+6 , lang.states+94 },
                             { lang.elements+8 , lang.states+95 },
                             { lang.elements+10 , lang.states+39 },
                             { lang.elements+14 , lang.states+40 },
                             { lang.elements+16 , lang.states+16 },
                             { lang.elements+17 , lang.states+170 },
                             { lang.elements+18 , lang.states+262 },
                             { lang.elements+23 , lang.states+354 },
                             { lang.elements+25 , lang.states+258 },
                             { lang.elements+27 , lang.states+355 },
                             { lang.elements+28 , lang.states+360 },
                             { lang.elements+29 , lang.states+362 },
                             { lang.elements+30 , lang.states+364 },
                             { lang.elements+31 , lang.states+358 },
                             { lang.elements+35 , lang.states+356 },
                             { lang.elements+36 , lang.states+361 },
                             { lang.elements+37 , lang.states+363 },
                             { lang.elements+38 , lang.states+365 },
                             { lang.elements+39 , lang.states+359 },
                             { lang.elements+40 , lang.states+357 },
                             { lang.elements+48 , lang.states+48 },
                             { lang.elements+49 , lang.states+146 },
                             { lang.elements+50 , lang.states+366 },
                             { lang.elements+58 , lang.states+254 },
                             { lang.elements+59 , lang.states+253 },
                             { lang.elements+60 , lang.states+250 },
                             { lang.elements+61 , lang.states+250 },
                             { lang.elements+65 , lang.states+370 },
                             { lang.elements+66 , lang.states+150 }
                            }
    },
    { 99 , lang.finals+49 ,
                            {
                             { lang.elements+0 , lang.states+514 },
                             { lang.elements+2 , lang.states+66 },
                             { lang.elements+3 , lang.states+99 },
                             { lang.elements+5 , lang.states+65 },
                             { lang.elements+6 , lang.states+67 },
                             { lang.elements+8 , lang.states+68 },
                             { lang.elements+10 , lang.states+33 },
                             { lang.elements+14 , lang.states+34 },
                             { lang.elements+16 , lang.states+13 },
                             { lang.elements+17 , lang.states+167 },
                             { lang.elements+18 , lang.states+259 },
                             { lang.elements+23 , lang.states+354 },
                             { lang.elements+25 , lang.states+255 },
                             { lang.elements+27 , lang.states+355 },
                             { lang.elements+28 , lang.states+360 },
                             { lang.elements+29 , lang.states+362 },
                             { lang.elements+30 , lang.states+364 },
                             { lang.elements+31 , lang.states+358 },
                             { lang.elements+35 , lang.states+356 },
                             { lang.elements+36 , lang.states+361 },
                             { lang.elements+37 , lang.states+363 },
                             { lang.elements+38 , lang.states+365 },
                             { lang.elements+39 , lang.states+359 },
                             { lang.elements+40 , lang.states+357 },
                             { lang.elements+41 , lang.states+117 },
                             { lang.elements+48 , lang.states+45 },
                             { lang.elements+49 , lang.states+143 },
                             { lang.elements+50 , lang.states+366 },
                             { lang.elements+55 , lang.states+384 },
                             { lang.elements+56 , lang.states+376 },
                             { lang.elements+57 , lang.states+289 },
                             { lang.elements+58 , lang.states+289 },
                             { lang.elements+59 , lang.states+281 },
                             { lang.elements+60 , lang.states+273 },
                             { lang.elements+61 , lang.states+273 },
                             { lang.elements+65 , lang.states+367 },
                             { lang.elements+66 , lang.states+147 }
                            }
    },
    { 100 , lang.finals+49 ,
                             {
                              { lang.elements+0 , lang.states+514 },
                              { lang.elements+2 , lang.states+66 },
                              { lang.elements+3 , lang.states+99 },
                              { lang.elements+5 , lang.states+65 },
                              { lang.elements+6 , lang.states+67 },
                              { lang.elements+8 , lang.states+68 },
                              { lang.elements+10 , lang.states+33 },
                              { lang.elements+14 , lang.states+34 },
                              { lang.elements+16 , lang.states+13 },
                              { lang.elements+17 , lang.states+167 },
                              { lang.elements+18 , lang.states+259 },
                              { lang.elements+23 , lang.states+354 },
                              { lang.elements+25 , lang.states+255 },
                              { lang.elements+27 , lang.states+355 },
                              { lang.elements+28 , lang.states+360 },
                              { lang.elements+29 , lang.states+362 },
                              { lang.elements+30 , lang.states+364 },
                              { lang.elements+31 , lang.states+358 },
                              { lang.elements+35 , lang.states+356 },
                              { lang.elements+36 , lang.states+361 },
                              { lang.elements+37 , lang.states+363 },
                              { lang.elements+38 , lang.states+365 },
                              { lang.elements+39 , lang.states+359 },
                              { lang.elements+40 , lang.states+357 },
                              { lang.elements+41 , lang.states+117 },
                              { lang.elements+48 , lang.states+45 },
                              { lang.elements+49 , lang.states+143 },
                              { lang.elements+50 , lang.states+366 },
                              { lang.elements+55 , lang.states+385 },
                              { lang.elements+56 , lang.states+377 },
                              { lang.elements+57 , lang.states+290 },
                              { lang.elements+58 , lang.states+290 },
                              { lang.elements+59 , lang.states+282 },
                              { lang.elements+60 , lang.states+274 },
                              { lang.elements+61 , lang.states+274 },
                              { lang.elements+65 , lang.states+367 },
                              { lang.elements+66 , lang.states+147 }
                             }
    },
    { 101 , lang.finals+49 ,
                             {
                              { lang.elements+0 , lang.states+514 },
                              { lang.elements+2 , lang.states+66 },
                              { lang.elements+3 , lang.states+99 },
                              { lang.elements+5 , lang.states+65 },
                              { lang.elements+6 , lang.states+67 },
                              { lang.elements+8 , lang.states+68 },
                              { lang.elements+10 , lang.states+33 },
                              { lang.elements+14 , lang.states+34 },
                              { lang.elements+16 , lang.states+13 },
                              { lang.elements+17 , lang.states+167 },
                              { lang.elements+18 , lang.states+259 },
                              { lang.elements+23 , lang.states+354 },
                              { lang.elements+25 , lang.states+255 },
                              { lang.elements+27 , lang.states+355 },
                              { lang.elements+28 , lang.states+360 },
                              { lang.elements+29 , lang.states+362 },
                              { lang.elements+30 , lang.states+364 },
                              { lang.elements+31 , lang.states+358 },
                              { lang.elements+35 , lang.states+356 },
                              { lang.elements+36 , lang.states+361 },
                              { lang.elements+37 , lang.states+363 },
                              { lang.elements+38 , lang.states+365 },
                              { lang.elements+39 , lang.states+359 },
                              { lang.elements+40 , lang.states+357 },
                              { lang.elements+41 , lang.states+117 },
                              { lang.elements+48 , lang.states+45 },
                              { lang.elements+49 , lang.states+143 },
                              { lang.elements+50 , lang.states+366 },
                              { lang.elements+55 , lang.states+386 },
                              { lang.elements+56 , lang.states+378 },
                              { lang.elements+57 , lang.states+291 },
                              { lang.elements+58 , lang.states+291 },
                              { lang.elements+59 , lang.states+283 },
                              { lang.elements+60 , lang.states+275 },
                              { lang.elements+61 , lang.states+275 },
                              { lang.elements+65 , lang.states+367 },
                              { lang.elements+66 , lang.states+147 }
                             }
    },
    { 102 , lang.finals+49 ,
                             {
                              { lang.elements+0 , lang.states+514 },
                              { lang.elements+2 , lang.states+66 },
                              { lang.elements+3 , lang.states+99 },
                              { lang.elements+5 , lang.states+65 },
                              { lang.elements+6 , lang.states+67 },
                              { lang.elements+8 , lang.states+68 },
                              { lang.elements+10 , lang.states+33 },
                              { lang.elements+14 , lang.states+34 },
                              { lang.elements+16 , lang.states+13 },
                              { lang.elements+17 , lang.states+167 },
                              { lang.elements+18 , lang.states+259 },
                              { lang.elements+23 , lang.states+354 },
                              { lang.elements+25 , lang.states+255 },
                              { lang.elements+27 , lang.states+355 },
                              { lang.elements+28 , lang.states+360 },
                              { lang.elements+29 , lang.states+362 },
                              { lang.elements+30 , lang.states+364 },
                              { lang.elements+31 , lang.states+358 },
                              { lang.elements+35 , lang.states+356 },
                              { lang.elements+36 , lang.states+361 },
                              { lang.elements+37 , lang.states+363 },
                              { lang.elements+38 , lang.states+365 },
                              { lang.elements+39 , lang.states+359 },
                              { lang.elements+40 , lang.states+357 },
                              { lang.elements+41 , lang.states+117 },
                              { lang.elements+48 , lang.states+45 },
                              { lang.elements+49 , lang.states+143 },
                              { lang.elements+50 , lang.states+366 },
                              { lang.elements+55 , lang.states+387 },
                              { lang.elements+56 , lang.states+379 },
                              { lang.elements+57 , lang.states+292 },
                              { lang.elements+58 , lang.states+292 },
                              { lang.elements+59 , lang.states+284 },
                              { lang.elements+60 , lang.states+276 },
                              { lang.elements+61 , lang.states+276 },
                              { lang.elements+65 , lang.states+367 },
                              { lang.elements+66 , lang.states+147 }
                             }
    },
    { 103 , lang.finals+49 ,
                             {
                              { lang.elements+0 , lang.states+514 },
                              { lang.elements+2 , lang.states+66 },
                              { lang.elements+3 , lang.states+99 },
                              { lang.elements+5 , lang.states+65 },
                              { lang.elements+6 , lang.states+67 },
                              { lang.elements+8 , lang.states+68 },
                              { lang.elements+10 , lang.states+33 },
                              { lang.elements+14 , lang.states+34 },
                              { lang.elements+16 , lang.states+13 },
                              { lang.elements+17 , lang.states+167 },
                              { lang.elements+18 , lang.states+259 },
                              { lang.elements+23 , lang.states+354 },
                              { lang.elements+25 , lang.states+255 },
                              { lang.elements+27 , lang.states+355 },
                              { lang.elements+28 , lang.states+360 },
                              { lang.elements+29 , lang.states+362 },
                              { lang.elements+30 , lang.states+364 },
                              { lang.elements+31 , lang.states+358 },
                              { lang.elements+35 , lang.states+356 },
                              { lang.elements+36 , lang.states+361 },
                              { lang.elements+37 , lang.states+363 },
                              { lang.elements+38 , lang.states+365 },
                              { lang.elements+39 , lang.states+359 },
                              { lang.elements+40 , lang.states+357 },
                              { lang.elements+41 , lang.states+117 },
                              { lang.elements+48 , lang.states+45 },
                              { lang.elements+49 , lang.states+143 },
                              { lang.elements+50 , lang.states+366 },
                              { lang.elements+55 , lang.states+388 },
                              { lang.elements+56 , lang.states+380 },
                              { lang.elements+57 , lang.states+293 },
                              { lang.elements+58 , lang.states+293 },
                              { lang.elements+59 , lang.states+285 },
                              { lang.elements+60 , lang.states+277 },
                              { lang.elements+61 , lang.states+277 },
                              { lang.elements+65 , lang.states+367 },
                              { lang.elements+66 , lang.states+147 }
                             }
    },
    { 104 , lang.finals+49 ,
                             {
                              { lang.elements+0 , lang.states+514 },
                              { lang.elements+2 , lang.states+66 },
                              { lang.elements+3 , lang.states+99 },
                              { lang.elements+5 , lang.states+65 },
                              { lang.elements+6 , lang.states+67 },
                              { lang.elements+8 , lang.states+68 },
                              { lang.elements+10 , lang.states+33 },
                              { lang.elements+14 , lang.states+34 },
                              { lang.elements+16 , lang.states+13 },
                              { lang.elements+17 , lang.states+167 },
                              { lang.elements+18 , lang.states+259 },
                              { lang.elements+23 , lang.states+354 },
                              { lang.elements+25 , lang.states+255 },
                              { lang.elements+27 , lang.states+355 },
                              { lang.elements+28 , lang.states+360 },
                              { lang.elements+29 , lang.states+362 },
                              { lang.elements+30 , lang.states+364 },
                              { lang.elements+31 , lang.states+358 },
                              { lang.elements+35 , lang.states+356 },
                              { lang.elements+36 , lang.states+361 },
                              { lang.elements+37 , lang.states+363 },
                              { lang.elements+38 , lang.states+365 },
                              { lang.elements+39 , lang.states+359 },
                              { lang.elements+40 , lang.states+357 },
                              { lang.elements+41 , lang.states+117 },
                              { lang.elements+48 , lang.states+45 },
                              { lang.elements+49 , lang.states+143 },
                              { lang.elements+50 , lang.states+366 },
                              { lang.elements+55 , lang.states+389 },
                              { lang.elements+56 , lang.states+381 },
                              { lang.elements+57 , lang.states+294 },
                              { lang.elements+58 , lang.states+294 },
                              { lang.elements+59 , lang.states+286 },
                              { lang.elements+60 , lang.states+278 },
                              { lang.elements+61 , lang.states+278 },
                              { lang.elements+65 , lang.states+367 },
                              { lang.elements+66 , lang.states+147 }
                             }
    },
    { 105 , lang.finals+49 ,
                             {
                              { lang.elements+0 , lang.states+514 },
                              { lang.elements+2 , lang.states+66 },
                              { lang.elements+3 , lang.states+99 },
                              { lang.elements+5 , lang.states+65 },
                              { lang.elements+6 , lang.states+67 },
                              { lang.elements+8 , lang.states+68 },
                              { lang.elements+10 , lang.states+33 },
                              { lang.elements+14 , lang.states+34 },
                              { lang.elements+16 , lang.states+13 },
                              { lang.elements+17 , lang.states+167 },
                              { lang.elements+18 , lang.states+259 },
                              { lang.elements+23 , lang.states+354 },
                              { lang.elements+25 , lang.states+255 },
                              { lang.elements+27 , lang.states+355 },
                              { lang.elements+28 , lang.states+360 },
                              { lang.elements+29 , lang.states+362 },
                              { lang.elements+30 , lang.states+364 },
                              { lang.elements+31 , lang.states+358 },
                              { lang.elements+35 , lang.states+356 },
                              { lang.elements+36 , lang.states+361 },
                              { lang.elements+37 , lang.states+363 },
                              { lang.elements+38 , lang.states+365 },
                              { lang.elements+39 , lang.states+359 },
                              { lang.elements+40 , lang.states+357 },
                              { lang.elements+41 , lang.states+117 },
                              { lang.elements+48 , lang.states+45 },
                              { lang.elements+49 , lang.states+143 },
                              { lang.elements+50 , lang.states+366 },
                              { lang.elements+55 , lang.states+390 },
                              { lang.elements+56 , lang.states+382 },
                              { lang.elements+57 , lang.states+295 },
                              { lang.elements+58 , lang.states+295 },
                              { lang.elements+59 , lang.states+287 },
                              { lang.elements+60 , lang.states+279 },
                              { lang.elements+61 , lang.states+279 },
                              { lang.elements+65 , lang.states+367 },
                              { lang.elements+66 , lang.states+147 }
                             }
    },
    { 106 , lang.finals+49 ,
                             {
                              { lang.elements+0 , lang.states+514 },
                              { lang.elements+2 , lang.states+66 },
                              { lang.elements+3 , lang.states+99 },
                              { lang.elements+5 , lang.states+65 },
                              { lang.elements+6 , lang.states+67 },
                              { lang.elements+8 , lang.states+68 },
                              { lang.elements+10 , lang.states+33 },
                              { lang.elements+14 , lang.states+34 },
                              { lang.elements+16 , lang.states+13 },
                              { lang.elements+17 , lang.states+167 },
                              { lang.elements+18 , lang.states+259 },
                              { lang.elements+23 , lang.states+354 },
                              { lang.elements+25 , lang.states+255 },
                              { lang.elements+27 , lang.states+355 },
                              { lang.elements+28 , lang.states+360 },
                              { lang.elements+29 , lang.states+362 },
                              { lang.elements+30 , lang.states+364 },
                              { lang.elements+31 , lang.states+358 },
                              { lang.elements+35 , lang.states+356 },
                              { lang.elements+36 , lang.states+361 },
                              { lang.elements+37 , lang.states+363 },
                              { lang.elements+38 , lang.states+365 },
                              { lang.elements+39 , lang.states+359 },
                              { lang.elements+40 , lang.states+357 },
                              { lang.elements+41 , lang.states+117 },
                              { lang.elements+48 , lang.states+45 },
                              { lang.elements+49 , lang.states+143 },
                              { lang.elements+50 , lang.states+366 },
                              { lang.elements+55 , lang.states+391 },
                              { lang.elements+56 , lang.states+383 },
                              { lang.elements+57 , lang.states+296 },
                              { lang.elements+58 , lang.states+296 },
                              { lang.elements+59 , lang.states+288 },
                              { lang.elements+60 , lang.states+280 },
                              { lang.elements+61 , lang.states+280 },
                              { lang.elements+65 , lang.states+367 },
                              { lang.elements+66 , lang.states+147 }
                             }
    },
    { 107 , lang.finals+49 ,
                             {
                              { lang.elements+0 , lang.states+517 },
                              { lang.elements+2 , lang.states+75 },
                              { lang.elements+3 , lang.states+100 },
                              { lang.elements+5 , lang.states+74 },
                              { lang.elements+6 , lang.states+76 },
                              { lang.elements+8 , lang.states+77 },
                              { lang.elements+10 , lang.states+35 },
                              { lang.elements+14 , lang.states+36 },
                              { lang.elements+16 , lang.states+14 },
                              { lang.elements+17 , lang.states+168 },
                              { lang.elements+18 , lang.states+260 },
                              { lang.elements+23 , lang.states+354 },
                              { lang.elements+25 , lang.states+256 },
                              { lang.elements+27 , lang.states+355 },
                              { lang.elements+28 , lang.states+360 },
                              { lang.elements+29 , lang.states+362 },
                              { lang.elements+30 , lang.states+364 },
                              { lang.elements+31 , lang.states+358 },
                              { lang.elements+35 , lang.states+356 },
                              { lang.elements+36 , lang.states+361 },
                              { lang.elements+37 , lang.states+363 },
                              { lang.elements+38 , lang.states+365 },
                              { lang.elements+39 , lang.states+359 },
                              { lang.elements+40 , lang.states+357 },
                              { lang.elements+41 , lang.states+118 },
                              { lang.elements+48 , lang.states+46 },
                              { lang.elements+49 , lang.states+144 },
                              { lang.elements+50 , lang.states+366 },
                              { lang.elements+55 , lang.states+466 },
                              { lang.elements+56 , lang.states+448 },
                              { lang.elements+57 , lang.states+320 },
                              { lang.elements+58 , lang.states+320 },
                              { lang.elements+59 , lang.states+319 },
                              { lang.elements+60 , lang.states+318 },
                              { lang.elements+61 , lang.states+318 },
                              { lang.elements+65 , lang.states+368 },
                              { lang.elements+66 , lang.states+148 }
                             }
    },
    { 108 , lang.finals+49 ,
                             {
                              { lang.elements+0 , lang.states+517 },
                              { lang.elements+2 , lang.states+75 },
                              { lang.elements+3 , lang.states+100 },
                              { lang.elements+5 , lang.states+74 },
                              { lang.elements+6 , lang.states+76 },
                              { lang.elements+8 , lang.states+77 },
                              { lang.elements+10 , lang.states+35 },
                              { lang.elements+14 , lang.states+36 },
                              { lang.elements+16 , lang.states+14 },
                              { lang.elements+17 , lang.states+168 },
                              { lang.elements+18 , lang.states+260 },
                              { lang.elements+23 , lang.states+354 },
                              { lang.elements+25 , lang.states+256 },
                              { lang.elements+27 , lang.states+355 },
                              { lang.elements+28 , lang.states+360 },
                              { lang.elements+29 , lang.states+362 },
                              { lang.elements+30 , lang.states+364 },
                              { lang.elements+31 , lang.states+358 },
                              { lang.elements+35 , lang.states+356 },
                              { lang.elements+36 , lang.states+361 },
                              { lang.elements+37 , lang.states+363 },
                              { lang.elements+38 , lang.states+365 },
                              { lang.elements+39 , lang.states+359 },
                              { lang.elements+40 , lang.states+357 },
                              { lang.elements+41 , lang.states+118 },
                              { lang.elements+48 , lang.states+46 },
                              { lang.elements+49 , lang.states+144 },
                              { lang.elements+50 , lang.states+366 },
                              { lang.elements+55 , lang.states+467 },
                              { lang.elements+56 , lang.states+449 },
                              { lang.elements+57 , lang.states+323 },
                              { lang.elements+58 , lang.states+323 },
                              { lang.elements+59 , lang.states+322 },
                              { lang.elements+60 , lang.states+321 },
                              { lang.elements+61 , lang.states+321 },
                              { lang.elements+65 , lang.states+368 },
                              { lang.elements+66 , lang.states+148 }
                             }
    },
    { 109 , lang.finals+49 ,
                             {
                              { lang.elements+0 , lang.states+520 },
                              { lang.elements+2 , lang.states+84 },
                              { lang.elements+3 , lang.states+101 },
                              { lang.elements+5 , lang.states+83 },
                              { lang.elements+6 , lang.states+85 },
                              { lang.elements+8 , lang.states+86 },
                              { lang.elements+10 , lang.states+37 },
                              { lang.elements+14 , lang.states+38 },
                              { lang.elements+16 , lang.states+15 },
                              { lang.elements+17 , lang.states+169 },
                              { lang.elements+18 , lang.states+261 },
                              { lang.elements+23 , lang.states+354 },
                              { lang.elements+25 , lang.states+257 },
                              { lang.elements+27 , lang.states+355 },
                              { lang.elements+28 , lang.states+360 },
                              { lang.elements+29 , lang.states+362 },
                              { lang.elements+30 , lang.states+364 },
                              { lang.elements+31 , lang.states+358 },
                              { lang.elements+35 , lang.states+356 },
                              { lang.elements+36 , lang.states+361 },
                              { lang.elements+37 , lang.states+363 },
                              { lang.elements+38 , lang.states+365 },
                              { lang.elements+39 , lang.states+359 },
                              { lang.elements+40 , lang.states+357 },
                              { lang.elements+41 , lang.states+119 },
                              { lang.elements+48 , lang.states+47 },
                              { lang.elements+49 , lang.states+145 },
                              { lang.elements+50 , lang.states+366 },
                              { lang.elements+55 , lang.states+501 },
                              { lang.elements+56 , lang.states+450 },
                              { lang.elements+57 , lang.states+338 },
                              { lang.elements+58 , lang.states+338 },
                              { lang.elements+59 , lang.states+334 },
                              { lang.elements+60 , lang.states+324 },
                              { lang.elements+61 , lang.states+324 },
                              { lang.elements+65 , lang.states+369 },
                              { lang.elements+66 , lang.states+149 }
                             }
    },
    { 110 , lang.finals+49 ,
                             {
                              { lang.elements+0 , lang.states+520 },
                              { lang.elements+2 , lang.states+84 },
                              { lang.elements+3 , lang.states+101 },
                              { lang.elements+5 , lang.states+83 },
                              { lang.elements+6 , lang.states+85 },
                              { lang.elements+8 , lang.states+86 },
                              { lang.elements+10 , lang.states+37 },
                              { lang.elements+14 , lang.states+38 },
                              { lang.elements+16 , lang.states+15 },
                              { lang.elements+17 , lang.states+169 },
                              { lang.elements+18 , lang.states+261 },
                              { lang.elements+23 , lang.states+354 },
                              { lang.elements+25 , lang.states+257 },
                              { lang.elements+27 , lang.states+355 },
                              { lang.elements+28 , lang.states+360 },
                              { lang.elements+29 , lang.states+362 },
                              { lang.elements+30 , lang.states+364 },
                              { lang.elements+31 , lang.states+358 },
                              { lang.elements+35 , lang.states+356 },
                              { lang.elements+36 , lang.states+361 },
                              { lang.elements+37 , lang.states+363 },
                              { lang.elements+38 , lang.states+365 },
                              { lang.elements+39 , lang.states+359 },
                              { lang.elements+40 , lang.states+357 },
                              { lang.elements+41 , lang.states+119 },
                              { lang.elements+48 , lang.states+47 },
                              { lang.elements+49 , lang.states+145 },
                              { lang.elements+50 , lang.states+366 },
                              { lang.elements+55 , lang.states+502 },
                              { lang.elements+56 , lang.states+451 },
                              { lang.elements+57 , lang.states+339 },
                              { lang.elements+58 , lang.states+339 },
                              { lang.elements+59 , lang.states+335 },
                              { lang.elements+60 , lang.states+325 },
                              { lang.elements+61 , lang.states+325 },
                              { lang.elements+65 , lang.states+369 },
                              { lang.elements+66 , lang.states+149 }
                             }
    },
    { 111 , lang.finals+49 ,
                             {
                              { lang.elements+0 , lang.states+520 },
                              { lang.elements+2 , lang.states+84 },
                              { lang.elements+3 , lang.states+101 },
                              { lang.elements+5 , lang.states+83 },
                              { lang.elements+6 , lang.states+85 },
                              { lang.elements+8 , lang.states+86 },
                              { lang.elements+10 , lang.states+37 },
                              { lang.elements+14 , lang.states+38 },
                              { lang.elements+16 , lang.states+15 },
                              { lang.elements+17 , lang.states+169 },
                              { lang.elements+18 , lang.states+261 },
                              { lang.elements+23 , lang.states+354 },
                              { lang.elements+25 , lang.states+257 },
                              { lang.elements+27 , lang.states+355 },
                              { lang.elements+28 , lang.states+360 },
                              { lang.elements+29 , lang.states+362 },
                              { lang.elements+30 , lang.states+364 },
                              { lang.elements+31 , lang.states+358 },
                              { lang.elements+35 , lang.states+356 },
                              { lang.elements+36 , lang.states+361 },
                              { lang.elements+37 , lang.states+363 },
                              { lang.elements+38 , lang.states+365 },
                              { lang.elements+39 , lang.states+359 },
                              { lang.elements+40 , lang.states+357 },
                              { lang.elements+41 , lang.states+119 },
                              { lang.elements+48 , lang.states+47 },
                              { lang.elements+49 , lang.states+145 },
                              { lang.elements+50 , lang.states+366 },
                              { lang.elements+55 , lang.states+503 },
                              { lang.elements+56 , lang.states+452 },
                              { lang.elements+57 , lang.states+340 },
                              { lang.elements+58 , lang.states+340 },
                              { lang.elements+59 , lang.states+336 },
                              { lang.elements+60 , lang.states+326 },
                              { lang.elements+61 , lang.states+326 },
                              { lang.elements+65 , lang.states+369 },
                              { lang.elements+66 , lang.states+149 }
                             }
    },
    { 112 , lang.finals+49 ,
                             {
                              { lang.elements+0 , lang.states+520 },
                              { lang.elements+2 , lang.states+84 },
                              { lang.elements+3 , lang.states+101 },
                              { lang.elements+5 , lang.states+83 },
                              { lang.elements+6 , lang.states+85 },
                              { lang.elements+8 , lang.states+86 },
                              { lang.elements+10 , lang.states+37 },
                              { lang.elements+14 , lang.states+38 },
                              { lang.elements+16 , lang.states+15 },
                              { lang.elements+17 , lang.states+169 },
                              { lang.elements+18 , lang.states+261 },
                              { lang.elements+23 , lang.states+354 },
                              { lang.elements+25 , lang.states+257 },
                              { lang.elements+27 , lang.states+355 },
                              { lang.elements+28 , lang.states+360 },
                              { lang.elements+29 , lang.states+362 },
                              { lang.elements+30 , lang.states+364 },
                              { lang.elements+31 , lang.states+358 },
                              { lang.elements+35 , lang.states+356 },
                              { lang.elements+36 , lang.states+361 },
                              { lang.elements+37 , lang.states+363 },
                              { lang.elements+38 , lang.states+365 },
                              { lang.elements+39 , lang.states+359 },
                              { lang.elements+40 , lang.states+357 },
                              { lang.elements+41 , lang.states+119 },
                              { lang.elements+48 , lang.states+47 },
                              { lang.elements+49 , lang.states+145 },
                              { lang.elements+50 , lang.states+366 },
                              { lang.elements+55 , lang.states+504 },
                              { lang.elements+56 , lang.states+453 },
                              { lang.elements+57 , lang.states+341 },
                              { lang.elements+58 , lang.states+341 },
                              { lang.elements+59 , lang.states+337 },
                              { lang.elements+60 , lang.states+327 },
                              { lang.elements+61 , lang.states+327 },
                              { lang.elements+65 , lang.states+369 },
                              { lang.elements+66 , lang.states+149 }
                             }
    },
    { 113 , lang.finals+49 ,
                             {
                              { lang.elements+0 , lang.states+523 },
                              { lang.elements+2 , lang.states+93 },
                              { lang.elements+3 , lang.states+102 },
                              { lang.elements+5 , lang.states+92 },
                              { lang.elements+6 , lang.states+94 },
                              { lang.elements+8 , lang.states+95 },
                              { lang.elements+10 , lang.states+39 },
                              { lang.elements+14 , lang.states+40 },
                              { lang.elements+16 , lang.states+16 },
                              { lang.elements+17 , lang.states+170 },
                              { lang.elements+18 , lang.states+262 },
                              { lang.elements+23 , lang.states+354 },
                              { lang.elements+25 , lang.states+258 },
                              { lang.elements+27 , lang.states+355 },
                              { lang.elements+28 , lang.states+360 },
                              { lang.elements+29 , lang.states+362 },
                              { lang.elements+30 , lang.states+364 },
                              { lang.elements+31 , lang.states+358 },
                              { lang.elements+35 , lang.states+356 },
                              { lang.elements+36 , lang.states+361 },
                              { lang.elements+37 , lang.states+363 },
                              { lang.elements+38 , lang.states+365 },
                              { lang.elements+39 , lang.states+359 },
                              { lang.elements+40 , lang.states+357 },
                              { lang.elements+41 , lang.states+120 },
                              { lang.elements+48 , lang.states+48 },
                              { lang.elements+49 , lang.states+146 },
                              { lang.elements+50 , lang.states+366 },
                              { lang.elements+55 , lang.states+572 },
                              { lang.elements+56 , lang.states+454 },
                              { lang.elements+57 , lang.states+348 },
                              { lang.elements+58 , lang.states+348 },
                              { lang.elements+59 , lang.states+342 },
                              { lang.elements+60 , lang.states+328 },
                              { lang.elements+61 , lang.states+328 },
                              { lang.elements+65 , lang.states+370 },
                              { lang.elements+66 , lang.states+150 }
                             }
    },
    { 114 , lang.finals+49 ,
                             {
                              { lang.elements+0 , lang.states+523 },
                              { lang.elements+2 , lang.states+93 },
                              { lang.elements+3 , lang.states+102 },
                              { lang.elements+5 , lang.states+92 },
                              { lang.elements+6 , lang.states+94 },
                              { lang.elements+8 , lang.states+95 },
                              { lang.elements+10 , lang.states+39 },
                              { lang.elements+14 , lang.states+40 },
                              { lang.elements+16 , lang.states+16 },
                              { lang.elements+17 , lang.states+170 },
                              { lang.elements+18 , lang.states+262 },
                              { lang.elements+23 , lang.states+354 },
                              { lang.elements+25 , lang.states+258 },
                              { lang.elements+27 , lang.states+355 },
                              { lang.elements+28 , lang.states+360 },
                              { lang.elements+29 , lang.states+362 },
                              { lang.elements+30 , lang.states+364 },
                              { lang.elements+31 , lang.states+358 },
                              { lang.elements+35 , lang.states+356 },
                              { lang.elements+36 , lang.states+361 },
                              { lang.elements+37 , lang.states+363 },
                              { lang.elements+38 , lang.states+365 },
                              { lang.elements+39 , lang.states+359 },
                              { lang.elements+40 , lang.states+357 },
                              { lang.elements+41 , lang.states+120 },
                              { lang.elements+48 , lang.states+48 },
                              { lang.elements+49 , lang.states+146 },
                              { lang.elements+50 , lang.states+366 },
                              { lang.elements+55 , lang.states+573 },
                              { lang.elements+56 , lang.states+455 },
                              { lang.elements+57 , lang.states+349 },
                              { lang.elements+58 , lang.states+349 },
                              { lang.elements+59 , lang.states+343 },
                              { lang.elements+60 , lang.states+329 },
                              { lang.elements+61 , lang.states+329 },
                              { lang.elements+65 , lang.states+370 },
                              { lang.elements+66 , lang.states+150 }
                             }
    },
    { 115 , lang.finals+49 ,
                             {
                              { lang.elements+0 , lang.states+523 },
                              { lang.elements+2 , lang.states+93 },
                              { lang.elements+3 , lang.states+102 },
                              { lang.elements+5 , lang.states+92 },
                              { lang.elements+6 , lang.states+94 },
                              { lang.elements+8 , lang.states+95 },
                              { lang.elements+10 , lang.states+39 },
                              { lang.elements+14 , lang.states+40 },
                              { lang.elements+16 , lang.states+16 },
                              { lang.elements+17 , lang.states+170 },
                              { lang.elements+18 , lang.states+262 },
                              { lang.elements+23 , lang.states+354 },
                              { lang.elements+25 , lang.states+258 },
                              { lang.elements+27 , lang.states+355 },
                              { lang.elements+28 , lang.states+360 },
                              { lang.elements+29 , lang.states+362 },
                              { lang.elements+30 , lang.states+364 },
                              { lang.elements+31 , lang.states+358 },
                              { lang.elements+35 , lang.states+356 },
                              { lang.elements+36 , lang.states+361 },
                              { lang.elements+37 , lang.states+363 },
                              { lang.elements+38 , lang.states+365 },
                              { lang.elements+39 , lang.states+359 },
                              { lang.elements+40 , lang.states+357 },
                              { lang.elements+41 , lang.states+120 },
                              { lang.elements+48 , lang.states+48 },
                              { lang.elements+49 , lang.states+146 },
                              { lang.elements+50 , lang.states+366 },
                              { lang.elements+55 , lang.states+574 },
                              { lang.elements+56 , lang.states+456 },
                              { lang.elements+57 , lang.states+350 },
                              { lang.elements+58 , lang.states+350 },
                              { lang.elements+59 , lang.states+344 },
                              { lang.elements+60 , lang.states+330 },
                              { lang.elements+61 , lang.states+330 },
                              { lang.elements+65 , lang.states+370 },
                              { lang.elements+66 , lang.states+150 }
                             }
    },
    { 116 , lang.finals+49 ,
                             {
                              { lang.elements+0 , lang.states+523 },
                              { lang.elements+2 , lang.states+93 },
                              { lang.elements+3 , lang.states+102 },
                              { lang.elements+5 , lang.states+92 },
                              { lang.elements+6 , lang.states+94 },
                              { lang.elements+8 , lang.states+95 },
                              { lang.elements+10 , lang.states+39 },
                              { lang.elements+14 , lang.states+40 },
                              { lang.elements+16 , lang.states+16 },
                              { lang.elements+17 , lang.states+170 },
                              { lang.elements+18 , lang.states+262 },
                              { lang.elements+23 , lang.states+354 },
                              { lang.elements+25 , lang.states+258 },
                              { lang.elements+27 , lang.states+355 },
                              { lang.elements+28 , lang.states+360 },
                              { lang.elements+29 , lang.states+362 },
                              { lang.elements+30 , lang.states+364 },
                              { lang.elements+31 , lang.states+358 },
                              { lang.elements+35 , lang.states+356 },
                              { lang.elements+36 , lang.states+361 },
                              { lang.elements+37 , lang.states+363 },
                              { lang.elements+38 , lang.states+365 },
                              { lang.elements+39 , lang.states+359 },
                              { lang.elements+40 , lang.states+357 },
                              { lang.elements+41 , lang.states+120 },
                              { lang.elements+48 , lang.states+48 },
                              { lang.elements+49 , lang.states+146 },
                              { lang.elements+50 , lang.states+366 },
                              { lang.elements+55 , lang.states+575 },
                              { lang.elements+56 , lang.states+457 },
                              { lang.elements+57 , lang.states+351 },
                              { lang.elements+58 , lang.states+351 },
                              { lang.elements+59 , lang.states+345 },
                              { lang.elements+60 , lang.states+331 },
                              { lang.elements+61 , lang.states+331 },
                              { lang.elements+65 , lang.states+370 },
                              { lang.elements+66 , lang.states+150 }
                             }
    },
    { 117 , lang.finals+50 ,
                             {
                              { lang.elements+0 , lang.states+517 },
                              { lang.elements+2 , lang.states+75 },
                              { lang.elements+3 , lang.states+100 },
                              { lang.elements+5 , lang.states+74 },
                              { lang.elements+6 , lang.states+76 },
                              { lang.elements+8 , lang.states+77 },
                              { lang.elements+10 , lang.states+138 },
                              { lang.elements+14 , lang.states+36 },
                              { lang.elements+16 , lang.states+14 },
                              { lang.elements+17 , lang.states+168 },
                              { lang.elements+18 , lang.states+260 },
                              { lang.elements+23 , lang.states+354 },
                              { lang.elements+25 , lang.states+256 },
                              { lang.elements+27 , lang.states+355 },
                              { lang.elements+28 , lang.states+360 },
                              { lang.elements+29 , lang.states+362 },
                              { lang.elements+30 , lang.states+364 },
                              { lang.elements+31 , lang.states+358 },
                              { lang.elements+35 , lang.states+356 },
                              { lang.elements+36 , lang.states+361 },
                              { lang.elements+37 , lang.states+363 },
                              { lang.elements+38 , lang.states+365 },
                              { lang.elements+39 , lang.states+359 },
                              { lang.elements+40 , lang.states+357 },
                              { lang.elements+41 , lang.states+118 },
                              { lang.elements+42 , lang.states+371 },
                              { lang.elements+48 , lang.states+46 },
                              { lang.elements+49 , lang.states+144 },
                              { lang.elements+50 , lang.states+366 },
                              { lang.elements+55 , lang.states+465 },
                              { lang.elements+56 , lang.states+447 },
                              { lang.elements+57 , lang.states+317 },
                              { lang.elements+58 , lang.states+317 },
                              { lang.elements+59 , lang.states+316 },
                              { lang.elements+60 , lang.states+315 },
                              { lang.elements+61 , lang.states+315 },
                              { lang.elements+62 , lang.states+470 },
                              { lang.elements+63 , lang.states+468 },
                              { lang.elements+64 , lang.states+474 },
                              { lang.elements+65 , lang.states+368 },
                              { lang.elements+66 , lang.states+148 }
                             }
    },
    { 118 , lang.finals+50 ,
                             {
                              { lang.elements+0 , lang.states+517 },
                              { lang.elements+2 , lang.states+75 },
                              { lang.elements+3 , lang.states+100 },
                              { lang.elements+5 , lang.states+74 },
                              { lang.elements+6 , lang.states+76 },
                              { lang.elements+8 , lang.states+77 },
                              { lang.elements+10 , lang.states+138 },
                              { lang.elements+14 , lang.states+36 },
                              { lang.elements+16 , lang.states+14 },
                              { lang.elements+17 , lang.states+168 },
                              { lang.elements+18 , lang.states+260 },
                              { lang.elements+23 , lang.states+354 },
                              { lang.elements+25 , lang.states+256 },
                              { lang.elements+27 , lang.states+355 },
                              { lang.elements+28 , lang.states+360 },
                              { lang.elements+29 , lang.states+362 },
                              { lang.elements+30 , lang.states+364 },
                              { lang.elements+31 , lang.states+358 },
                              { lang.elements+35 , lang.states+356 },
                              { lang.elements+36 , lang.states+361 },
                              { lang.elements+37 , lang.states+363 },
                              { lang.elements+38 , lang.states+365 },
                              { lang.elements+39 , lang.states+359 },
                              { lang.elements+40 , lang.states+357 },
                              { lang.elements+41 , lang.states+118 },
                              { lang.elements+42 , lang.states+460 },
                              { lang.elements+48 , lang.states+46 },
                              { lang.elements+49 , lang.states+144 },
                              { lang.elements+50 , lang.states+366 },
                              { lang.elements+55 , lang.states+465 },
                              { lang.elements+56 , lang.states+447 },
                              { lang.elements+57 , lang.states+317 },
                              { lang.elements+58 , lang.states+317 },
                              { lang.elements+59 , lang.states+316 },
                              { lang.elements+60 , lang.states+315 },
                              { lang.elements+61 , lang.states+315 },
                              { lang.elements+62 , lang.states+471 },
                              { lang.elements+63 , lang.states+468 },
                              { lang.elements+64 , lang.states+476 },
                              { lang.elements+65 , lang.states+368 },
                              { lang.elements+66 , lang.states+148 }
                             }
    },
    { 119 , lang.finals+50 ,
                             {
                              { lang.elements+0 , lang.states+517 },
                              { lang.elements+2 , lang.states+75 },
                              { lang.elements+3 , lang.states+100 },
                              { lang.elements+5 , lang.states+74 },
                              { lang.elements+6 , lang.states+76 },
                              { lang.elements+8 , lang.states+77 },
                              { lang.elements+10 , lang.states+138 },
                              { lang.elements+14 , lang.states+36 },
                              { lang.elements+16 , lang.states+14 },
                              { lang.elements+17 , lang.states+168 },
                              { lang.elements+18 , lang.states+260 },
                              { lang.elements+23 , lang.states+354 },
                              { lang.elements+25 , lang.states+256 },
                              { lang.elements+27 , lang.states+355 },
                              { lang.elements+28 , lang.states+360 },
                              { lang.elements+29 , lang.states+362 },
                              { lang.elements+30 , lang.states+364 },
                              { lang.elements+31 , lang.states+358 },
                              { lang.elements+35 , lang.states+356 },
                              { lang.elements+36 , lang.states+361 },
                              { lang.elements+37 , lang.states+363 },
                              { lang.elements+38 , lang.states+365 },
                              { lang.elements+39 , lang.states+359 },
                              { lang.elements+40 , lang.states+357 },
                              { lang.elements+41 , lang.states+118 },
                              { lang.elements+42 , lang.states+495 },
                              { lang.elements+48 , lang.states+46 },
                              { lang.elements+49 , lang.states+144 },
                              { lang.elements+50 , lang.states+366 },
                              { lang.elements+55 , lang.states+465 },
                              { lang.elements+56 , lang.states+447 },
                              { lang.elements+57 , lang.states+317 },
                              { lang.elements+58 , lang.states+317 },
                              { lang.elements+59 , lang.states+316 },
                              { lang.elements+60 , lang.states+315 },
                              { lang.elements+61 , lang.states+315 },
                              { lang.elements+62 , lang.states+472 },
                              { lang.elements+63 , lang.states+468 },
                              { lang.elements+64 , lang.states+478 },
                              { lang.elements+65 , lang.states+368 },
                              { lang.elements+66 , lang.states+148 }
                             }
    },
    { 120 , lang.finals+50 ,
                             {
                              { lang.elements+0 , lang.states+517 },
                              { lang.elements+2 , lang.states+75 },
                              { lang.elements+3 , lang.states+100 },
                              { lang.elements+5 , lang.states+74 },
                              { lang.elements+6 , lang.states+76 },
                              { lang.elements+8 , lang.states+77 },
                              { lang.elements+10 , lang.states+138 },
                              { lang.elements+14 , lang.states+36 },
                              { lang.elements+16 , lang.states+14 },
                              { lang.elements+17 , lang.states+168 },
                              { lang.elements+18 , lang.states+260 },
                              { lang.elements+23 , lang.states+354 },
                              { lang.elements+25 , lang.states+256 },
                              { lang.elements+27 , lang.states+355 },
                              { lang.elements+28 , lang.states+360 },
                              { lang.elements+29 , lang.states+362 },
                              { lang.elements+30 , lang.states+364 },
                              { lang.elements+31 , lang.states+358 },
                              { lang.elements+35 , lang.states+356 },
                              { lang.elements+36 , lang.states+361 },
                              { lang.elements+37 , lang.states+363 },
                              { lang.elements+38 , lang.states+365 },
                              { lang.elements+39 , lang.states+359 },
                              { lang.elements+40 , lang.states+357 },
                              { lang.elements+41 , lang.states+118 },
                              { lang.elements+42 , lang.states+567 },
                              { lang.elements+48 , lang.states+46 },
                              { lang.elements+49 , lang.states+144 },
                              { lang.elements+50 , lang.states+366 },
                              { lang.elements+55 , lang.states+465 },
                              { lang.elements+56 , lang.states+447 },
                              { lang.elements+57 , lang.states+317 },
                              { lang.elements+58 , lang.states+317 },
                              { lang.elements+59 , lang.states+316 },
                              { lang.elements+60 , lang.states+315 },
                              { lang.elements+61 , lang.states+315 },
                              { lang.elements+62 , lang.states+473 },
                              { lang.elements+63 , lang.states+468 },
                              { lang.elements+64 , lang.states+480 },
                              { lang.elements+65 , lang.states+368 },
                              { lang.elements+66 , lang.states+148 }
                             }
    },
    { 121 , lang.finals+51 ,
                             {
                              { lang.elements+0 , lang.states+536 }
                             }
    },
    { 122 , lang.finals+52 ,
                             {
                              { lang.elements+0 , lang.states+537 }
                             }
    },
    { 123 , lang.finals+53 ,
                             {
                              { lang.elements+0 , lang.states+536 }
                             }
    },
    { 124 , lang.finals+54 ,
                             {
                              { lang.elements+0 , lang.states+537 }
                             }
    },
    { 125 , lang.finals+55 ,
                             {
                              { lang.elements+0 , lang.states+536 }
                             }
    },
    { 126 , lang.finals+56 ,
                             {
                              { lang.elements+0 , lang.states+537 }
                             }
    },
    { 127 , lang.finals+57 ,
                             {
                              { lang.elements+0 , lang.states+536 }
                             }
    },
    { 128 , lang.finals+58 ,
                             {
                              { lang.elements+0 , lang.states+537 }
                             }
    },
    { 129 , lang.finals+59 ,
                             {
                              { lang.elements+0 , lang.states+529 },
                              { lang.elements+10 , lang.states+43 },
                              { lang.elements+14 , lang.states+44 },
                              { lang.elements+16 , lang.states+18 },
                              { lang.elements+21 , lang.states+137 },
                              { lang.elements+23 , lang.states+393 },
                              { lang.elements+24 , lang.states+421 },
                              { lang.elements+27 , lang.states+395 },
                              { lang.elements+28 , lang.states+405 },
                              { lang.elements+29 , lang.states+409 },
                              { lang.elements+30 , lang.states+413 },
                              { lang.elements+31 , lang.states+401 },
                              { lang.elements+32 , lang.states+552 },
                              { lang.elements+33 , lang.states+419 },
                              { lang.elements+34 , lang.states+547 },
                              { lang.elements+35 , lang.states+397 },
                              { lang.elements+36 , lang.states+407 },
                              { lang.elements+37 , lang.states+411 },
                              { lang.elements+38 , lang.states+415 },
                              { lang.elements+39 , lang.states+403 },
                              { lang.elements+40 , lang.states+399 },
                              { lang.elements+42 , lang.states+437 },
                              { lang.elements+46 , lang.states+28 },
                              { lang.elements+48 , lang.states+122 },
                              { lang.elements+49 , lang.states+423 },
                              { lang.elements+50 , lang.states+417 },
                              { lang.elements+51 , lang.states+425 },
                              { lang.elements+52 , lang.states+443 },
                              { lang.elements+53 , lang.states+434 }
                             }
    },
    { 130 , lang.finals+59 ,
                             {
                              { lang.elements+0 , lang.states+529 },
                              { lang.elements+10 , lang.states+43 },
                              { lang.elements+14 , lang.states+44 },
                              { lang.elements+16 , lang.states+18 },
                              { lang.elements+21 , lang.states+137 },
                              { lang.elements+23 , lang.states+393 },
                              { lang.elements+24 , lang.states+421 },
                              { lang.elements+27 , lang.states+395 },
                              { lang.elements+28 , lang.states+405 },
                              { lang.elements+29 , lang.states+409 },
                              { lang.elements+30 , lang.states+413 },
                              { lang.elements+31 , lang.states+401 },
                              { lang.elements+32 , lang.states+552 },
                              { lang.elements+33 , lang.states+419 },
                              { lang.elements+34 , lang.states+547 },
                              { lang.elements+35 , lang.states+397 },
                              { lang.elements+36 , lang.states+407 },
                              { lang.elements+37 , lang.states+411 },
                              { lang.elements+38 , lang.states+415 },
                              { lang.elements+39 , lang.states+403 },
                              { lang.elements+40 , lang.states+399 },
                              { lang.elements+42 , lang.states+438 },
                              { lang.elements+46 , lang.states+28 },
                              { lang.elements+48 , lang.states+122 },
                              { lang.elements+49 , lang.states+423 },
                              { lang.elements+50 , lang.states+417 },
                              { lang.elements+51 , lang.states+425 },
                              { lang.elements+52 , lang.states+443 },
                              { lang.elements+53 , lang.states+434 }
                             }
    },
    { 131 , lang.finals+59 ,
                             {
                              { lang.elements+0 , lang.states+529 },
                              { lang.elements+10 , lang.states+43 },
                              { lang.elements+14 , lang.states+44 },
                              { lang.elements+16 , lang.states+18 },
                              { lang.elements+21 , lang.states+137 },
                              { lang.elements+23 , lang.states+393 },
                              { lang.elements+24 , lang.states+421 },
                              { lang.elements+27 , lang.states+395 },
                              { lang.elements+28 , lang.states+405 },
                              { lang.elements+29 , lang.states+409 },
                              { lang.elements+30 , lang.states+413 },
                              { lang.elements+31 , lang.states+401 },
                              { lang.elements+32 , lang.states+552 },
                              { lang.elements+33 , lang.states+419 },
                              { lang.elements+34 , lang.states+547 },
                              { lang.elements+35 , lang.states+397 },
                              { lang.elements+36 , lang.states+407 },
                              { lang.elements+37 , lang.states+411 },
                              { lang.elements+38 , lang.states+415 },
                              { lang.elements+39 , lang.states+403 },
                              { lang.elements+40 , lang.states+399 },
                              { lang.elements+42 , lang.states+439 },
                              { lang.elements+46 , lang.states+28 },
                              { lang.elements+48 , lang.states+122 },
                              { lang.elements+49 , lang.states+423 },
                              { lang.elements+50 , lang.states+417 },
                              { lang.elements+51 , lang.states+425 },
                              { lang.elements+52 , lang.states+443 },
                              { lang.elements+53 , lang.states+434 }
                             }
    },
    { 132 , lang.finals+60 ,
                             {
                              { lang.elements+0 , lang.states+529 },
                              { lang.elements+10 , lang.states+43 },
                              { lang.elements+14 , lang.states+44 },
                              { lang.elements+16 , lang.states+18 },
                              { lang.elements+22 , lang.states+512 },
                              { lang.elements+23 , lang.states+393 },
                              { lang.elements+24 , lang.states+421 },
                              { lang.elements+26 , lang.states+550 },
                              { lang.elements+27 , lang.states+395 },
                              { lang.elements+28 , lang.states+405 },
                              { lang.elements+29 , lang.states+409 },
                              { lang.elements+30 , lang.states+413 },
                              { lang.elements+31 , lang.states+401 },
                              { lang.elements+32 , lang.states+552 },
                              { lang.elements+33 , lang.states+419 },
                              { lang.elements+34 , lang.states+548 },
                              { lang.elements+35 , lang.states+397 },
                              { lang.elements+36 , lang.states+407 },
                              { lang.elements+37 , lang.states+411 },
                              { lang.elements+38 , lang.states+415 },
                              { lang.elements+39 , lang.states+403 },
                              { lang.elements+40 , lang.states+399 },
                              { lang.elements+42 , lang.states+7 },
                              { lang.elements+44 , lang.states+2 },
                              { lang.elements+45 , lang.states+3 },
                              { lang.elements+46 , lang.states+4 },
                              { lang.elements+47 , lang.states+5 },
                              { lang.elements+48 , lang.states+122 },
                              { lang.elements+49 , lang.states+423 },
                              { lang.elements+50 , lang.states+417 },
                              { lang.elements+51 , lang.states+425 },
                              { lang.elements+52 , lang.states+445 },
                              { lang.elements+53 , lang.states+433 }
                             }
    },
    { 133 , lang.finals+60 ,
                             {
                              { lang.elements+0 , lang.states+529 },
                              { lang.elements+10 , lang.states+43 },
                              { lang.elements+14 , lang.states+44 },
                              { lang.elements+16 , lang.states+18 },
                              { lang.elements+22 , lang.states+512 },
                              { lang.elements+23 , lang.states+393 },
                              { lang.elements+24 , lang.states+421 },
                              { lang.elements+26 , lang.states+550 },
                              { lang.elements+27 , lang.states+395 },
                              { lang.elements+28 , lang.states+405 },
                              { lang.elements+29 , lang.states+409 },
                              { lang.elements+30 , lang.states+413 },
                              { lang.elements+31 , lang.states+401 },
                              { lang.elements+32 , lang.states+552 },
                              { lang.elements+33 , lang.states+419 },
                              { lang.elements+34 , lang.states+548 },
                              { lang.elements+35 , lang.states+397 },
                              { lang.elements+36 , lang.states+407 },
                              { lang.elements+37 , lang.states+411 },
                              { lang.elements+38 , lang.states+415 },
                              { lang.elements+39 , lang.states+403 },
                              { lang.elements+40 , lang.states+399 },
                              { lang.elements+42 , lang.states+589 },
                              { lang.elements+44 , lang.states+2 },
                              { lang.elements+45 , lang.states+3 },
                              { lang.elements+46 , lang.states+4 },
                              { lang.elements+47 , lang.states+5 },
                              { lang.elements+48 , lang.states+122 },
                              { lang.elements+49 , lang.states+423 },
                              { lang.elements+50 , lang.states+417 },
                              { lang.elements+51 , lang.states+425 },
                              { lang.elements+52 , lang.states+445 },
                              { lang.elements+53 , lang.states+433 }
                             }
    },
    { 134 , lang.finals+61 ,
                             {
                              { lang.elements+0 , lang.states+526 },
                              { lang.elements+10 , lang.states+41 },
                              { lang.elements+14 , lang.states+42 },
                              { lang.elements+16 , lang.states+17 },
                              { lang.elements+23 , lang.states+392 },
                              { lang.elements+24 , lang.states+420 },
                              { lang.elements+27 , lang.states+394 },
                              { lang.elements+28 , lang.states+404 },
                              { lang.elements+29 , lang.states+408 },
                              { lang.elements+30 , lang.states+412 },
                              { lang.elements+31 , lang.states+400 },
                              { lang.elements+32 , lang.states+553 },
                              { lang.elements+33 , lang.states+418 },
                              { lang.elements+35 , lang.states+396 },
                              { lang.elements+36 , lang.states+406 },
                              { lang.elements+37 , lang.states+410 },
                              { lang.elements+38 , lang.states+414 },
                              { lang.elements+39 , lang.states+402 },
                              { lang.elements+40 , lang.states+398 },
                              { lang.elements+48 , lang.states+121 },
                              { lang.elements+49 , lang.states+422 },
                              { lang.elements+50 , lang.states+416 },
                              { lang.elements+51 , lang.states+424 },
                              { lang.elements+52 , lang.states+440 },
                              { lang.elements+53 , lang.states+432 }
                             }
    },
    { 135 , lang.finals+61 ,
                             {
                              { lang.elements+0 , lang.states+526 },
                              { lang.elements+10 , lang.states+41 },
                              { lang.elements+14 , lang.states+42 },
                              { lang.elements+16 , lang.states+17 },
                              { lang.elements+23 , lang.states+392 },
                              { lang.elements+24 , lang.states+420 },
                              { lang.elements+27 , lang.states+394 },
                              { lang.elements+28 , lang.states+404 },
                              { lang.elements+29 , lang.states+408 },
                              { lang.elements+30 , lang.states+412 },
                              { lang.elements+31 , lang.states+400 },
                              { lang.elements+32 , lang.states+553 },
                              { lang.elements+33 , lang.states+418 },
                              { lang.elements+35 , lang.states+396 },
                              { lang.elements+36 , lang.states+406 },
                              { lang.elements+37 , lang.states+410 },
                              { lang.elements+38 , lang.states+414 },
                              { lang.elements+39 , lang.states+402 },
                              { lang.elements+40 , lang.states+398 },
                              { lang.elements+48 , lang.states+121 },
                              { lang.elements+49 , lang.states+422 },
                              { lang.elements+50 , lang.states+416 },
                              { lang.elements+51 , lang.states+424 },
                              { lang.elements+52 , lang.states+441 },
                              { lang.elements+53 , lang.states+432 }
                             }
    },
    { 136 , lang.finals+61 ,
                             {
                              { lang.elements+0 , lang.states+526 },
                              { lang.elements+10 , lang.states+41 },
                              { lang.elements+14 , lang.states+42 },
                              { lang.elements+16 , lang.states+17 },
                              { lang.elements+23 , lang.states+392 },
                              { lang.elements+24 , lang.states+420 },
                              { lang.elements+27 , lang.states+394 },
                              { lang.elements+28 , lang.states+404 },
                              { lang.elements+29 , lang.states+408 },
                              { lang.elements+30 , lang.states+412 },
                              { lang.elements+31 , lang.states+400 },
                              { lang.elements+32 , lang.states+553 },
                              { lang.elements+33 , lang.states+418 },
                              { lang.elements+35 , lang.states+396 },
                              { lang.elements+36 , lang.states+406 },
                              { lang.elements+37 , lang.states+410 },
                              { lang.elements+38 , lang.states+414 },
                              { lang.elements+39 , lang.states+402 },
                              { lang.elements+40 , lang.states+398 },
                              { lang.elements+48 , lang.states+121 },
                              { lang.elements+49 , lang.states+422 },
                              { lang.elements+50 , lang.states+416 },
                              { lang.elements+51 , lang.states+424 },
                              { lang.elements+52 , lang.states+442 },
                              { lang.elements+53 , lang.states+432 }
                             }
    },
    { 137 , lang.finals+61 ,
                             {
                              { lang.elements+0 , lang.states+529 },
                              { lang.elements+10 , lang.states+43 },
                              { lang.elements+14 , lang.states+44 },
                              { lang.elements+16 , lang.states+18 },
                              { lang.elements+23 , lang.states+393 },
                              { lang.elements+24 , lang.states+421 },
                              { lang.elements+27 , lang.states+395 },
                              { lang.elements+28 , lang.states+405 },
                              { lang.elements+29 , lang.states+409 },
                              { lang.elements+30 , lang.states+413 },
                              { lang.elements+31 , lang.states+401 },
                              { lang.elements+32 , lang.states+554 },
                              { lang.elements+33 , lang.states+419 },
                              { lang.elements+35 , lang.states+397 },
                              { lang.elements+36 , lang.states+407 },
                              { lang.elements+37 , lang.states+411 },
                              { lang.elements+38 , lang.states+415 },
                              { lang.elements+39 , lang.states+403 },
                              { lang.elements+40 , lang.states+399 },
                              { lang.elements+47 , lang.states+29 },
                              { lang.elements+48 , lang.states+122 },
                              { lang.elements+49 , lang.states+423 },
                              { lang.elements+50 , lang.states+417 },
                              { lang.elements+51 , lang.states+425 },
                              { lang.elements+52 , lang.states+444 },
                              { lang.elements+53 , lang.states+436 }
                             }
    },
    { 138 , lang.finals+62 ,
                             {
                              { lang.elements+0 , lang.states+518 },
                              { lang.elements+16 , lang.states+505 }
                             }
    },
    { 139 , lang.finals+63 ,
                             {
                              
                             }
    },
    { 140 , lang.finals+64 ,
                             {
                              
                             }
    },
    { 141 , lang.finals+65 ,
                             {
                              
                             }
    },
    { 142 , lang.finals+66 ,
                             {
                              
                             }
    },
    { 143 , lang.finals+67 ,
                             {
                              
                             }
    },
    { 144 , lang.finals+68 ,
                             {
                              
                             }
    },
    { 145 , lang.finals+69 ,
                             {
                              
                             }
    },
    { 146 , lang.finals+70 ,
                             {
                              
                             }
    },
    { 147 , lang.finals+71 ,
                             {
                              
                             }
    },
    { 148 , lang.finals+72 ,
                             {
                              
                             }
    },
    { 149 , lang.finals+73 ,
                             {
                              
                             }
    },
    { 150 , lang.finals+74 ,
                             {
                              
                             }
    },
    { 151 , lang.finals+75 ,
                             {
                              
                             }
    },
    { 152 , lang.finals+76 ,
                             {
                              
                             }
    },
    { 153 , lang.finals+77 ,
                             {
                              
                             }
    },
    { 154 , lang.finals+78 ,
                             {
                              
                             }
    },
    { 155 , lang.finals+79 ,
                             {
                              
                             }
    },
    { 156 , lang.finals+80 ,
                             {
                              
                             }
    },
    { 157 , lang.finals+81 ,
                             {
                              
                             }
    },
    { 158 , lang.finals+82 ,
                             {
                              
                             }
    },
    { 159 , lang.finals+83 ,
                             {
                              
                             }
    },
    { 160 , lang.finals+84 ,
                             {
                              
                             }
    },
    { 161 , lang.finals+85 ,
                             {
                              
                             }
    },
    { 162 , lang.finals+86 ,
                             {
                              
                             }
    },
    { 163 , lang.finals+87 ,
                             {
                              
                             }
    },
    { 164 , lang.finals+88 ,
                             {
                              
                             }
    },
    { 165 , lang.finals+89 ,
                             {
                              
                             }
    },
    { 166 , lang.finals+90 ,
                             {
                              
                             }
    },
    { 167 , lang.finals+91 ,
                             {
                              { lang.elements+10 , lang.states+563 }
                             }
    },
    { 168 , lang.finals+92 ,
                             {
                              { lang.elements+10 , lang.states+564 }
                             }
    },
    { 169 , lang.finals+93 ,
                             {
                              { lang.elements+10 , lang.states+565 }
                             }
    },
    { 170 , lang.finals+94 ,
                             {
                              { lang.elements+10 , lang.states+566 }
                             }
    },
    { 171 , lang.finals+95 ,
                             {
                              { lang.elements+9 , lang.states+542 },
                              { lang.elements+10 , lang.states+538 },
                              { lang.elements+19 , lang.states+113 }
                             }
    },
    { 172 , lang.finals+96 ,
                             {
                              { lang.elements+19 , lang.states+113 }
                             }
    },
    { 173 , lang.finals+97 ,
                             {
                              
                             }
    },
    { 174 , lang.finals+98 ,
                             {
                              { lang.elements+9 , lang.states+543 },
                              { lang.elements+10 , lang.states+539 },
                              { lang.elements+19 , lang.states+114 }
                             }
    },
    { 175 , lang.finals+99 ,
                             {
                              { lang.elements+19 , lang.states+114 }
                             }
    },
    { 176 , lang.finals+100 ,
                              {
                               
                              }
    },
    { 177 , lang.finals+101 ,
                              {
                               { lang.elements+9 , lang.states+544 },
                               { lang.elements+10 , lang.states+540 },
                               { lang.elements+19 , lang.states+115 }
                              }
    },
    { 178 , lang.finals+102 ,
                              {
                               { lang.elements+9 , lang.states+545 },
                               { lang.elements+10 , lang.states+541 },
                               { lang.elements+19 , lang.states+116 }
                              }
    },
    { 179 , lang.finals+103 ,
                              {
                               { lang.elements+19 , lang.states+115 }
                              }
    },
    { 180 , lang.finals+104 ,
                              {
                               
                              }
    },
    { 181 , lang.finals+105 ,
                              {
                               { lang.elements+19 , lang.states+116 }
                              }
    },
    { 182 , lang.finals+106 ,
                              {
                               
                              }
    },
    { 183 , lang.finals+107 ,
                              {
                               { lang.elements+9 , lang.states+542 },
                               { lang.elements+10 , lang.states+538 },
                               { lang.elements+19 , lang.states+113 }
                              }
    },
    { 184 , lang.finals+108 ,
                              {
                               { lang.elements+19 , lang.states+113 }
                              }
    },
    { 185 , lang.finals+109 ,
                              {
                               
                              }
    },
    { 186 , lang.finals+110 ,
                              {
                               { lang.elements+9 , lang.states+543 },
                               { lang.elements+10 , lang.states+539 },
                               { lang.elements+19 , lang.states+114 }
                              }
    },
    { 187 , lang.finals+111 ,
                              {
                               { lang.elements+19 , lang.states+114 }
                              }
    },
    { 188 , lang.finals+112 ,
                              {
                               
                              }
    },
    { 189 , lang.finals+113 ,
                              {
                               { lang.elements+9 , lang.states+544 },
                               { lang.elements+10 , lang.states+540 },
                               { lang.elements+19 , lang.states+115 }
                              }
    },
    { 190 , lang.finals+114 ,
                              {
                               { lang.elements+9 , lang.states+545 },
                               { lang.elements+10 , lang.states+541 },
                               { lang.elements+19 , lang.states+116 }
                              }
    },
    { 191 , lang.finals+115 ,
                              {
                               { lang.elements+19 , lang.states+115 }
                              }
    },
    { 192 , lang.finals+116 ,
                              {
                               
                              }
    },
    { 193 , lang.finals+117 ,
                              {
                               { lang.elements+19 , lang.states+116 }
                              }
    },
    { 194 , lang.finals+118 ,
                              {
                               
                              }
    },
    { 195 , lang.finals+119 ,
                              {
                               { lang.elements+9 , lang.states+542 },
                               { lang.elements+10 , lang.states+538 },
                               { lang.elements+19 , lang.states+113 }
                              }
    },
    { 196 , lang.finals+120 ,
                              {
                               { lang.elements+19 , lang.states+113 }
                              }
    },
    { 197 , lang.finals+121 ,
                              {
                               
                              }
    },
    { 198 , lang.finals+122 ,
                              {
                               { lang.elements+9 , lang.states+543 },
                               { lang.elements+10 , lang.states+539 },
                               { lang.elements+19 , lang.states+114 }
                              }
    },
    { 199 , lang.finals+123 ,
                              {
                               { lang.elements+19 , lang.states+114 }
                              }
    },
    { 200 , lang.finals+124 ,
                              {
                               
                              }
    },
    { 201 , lang.finals+125 ,
                              {
                               { lang.elements+9 , lang.states+544 },
                               { lang.elements+10 , lang.states+540 },
                               { lang.elements+19 , lang.states+115 }
                              }
    },
    { 202 , lang.finals+126 ,
                              {
                               { lang.elements+9 , lang.states+545 },
                               { lang.elements+10 , lang.states+541 },
                               { lang.elements+19 , lang.states+116 }
                              }
    },
    { 203 , lang.finals+127 ,
                              {
                               { lang.elements+19 , lang.states+115 }
                              }
    },
    { 204 , lang.finals+128 ,
                              {
                               
                              }
    },
    { 205 , lang.finals+129 ,
                              {
                               { lang.elements+19 , lang.states+116 }
                              }
    },
    { 206 , lang.finals+130 ,
                              {
                               
                              }
    },
    { 207 , lang.finals+131 ,
                              {
                               { lang.elements+9 , lang.states+542 },
                               { lang.elements+10 , lang.states+538 },
                               { lang.elements+19 , lang.states+113 }
                              }
    },
    { 208 , lang.finals+132 ,
                              {
                               { lang.elements+19 , lang.states+113 }
                              }
    },
    { 209 , lang.finals+133 ,
                              {
                               
                              }
    },
    { 210 , lang.finals+134 ,
                              {
                               { lang.elements+9 , lang.states+543 },
                               { lang.elements+10 , lang.states+539 },
                               { lang.elements+19 , lang.states+114 }
                              }
    },
    { 211 , lang.finals+135 ,
                              {
                               { lang.elements+19 , lang.states+114 }
                              }
    },
    { 212 , lang.finals+136 ,
                              {
                               
                              }
    },
    { 213 , lang.finals+137 ,
                              {
                               { lang.elements+9 , lang.states+544 },
                               { lang.elements+10 , lang.states+540 },
                               { lang.elements+19 , lang.states+115 }
                              }
    },
    { 214 , lang.finals+138 ,
                              {
                               { lang.elements+9 , lang.states+545 },
                               { lang.elements+10 , lang.states+541 },
                               { lang.elements+19 , lang.states+116 }
                              }
    },
    { 215 , lang.finals+139 ,
                              {
                               { lang.elements+19 , lang.states+115 }
                              }
    },
    { 216 , lang.finals+140 ,
                              {
                               
                              }
    },
    { 217 , lang.finals+141 ,
                              {
                               { lang.elements+19 , lang.states+116 }
                              }
    },
    { 218 , lang.finals+142 ,
                              {
                               
                              }
    },
    { 219 , lang.finals+143 ,
                              {
                               { lang.elements+9 , lang.states+542 },
                               { lang.elements+10 , lang.states+538 },
                               { lang.elements+19 , lang.states+113 }
                              }
    },
    { 220 , lang.finals+144 ,
                              {
                               { lang.elements+19 , lang.states+113 }
                              }
    },
    { 221 , lang.finals+145 ,
                              {
                               
                              }
    },
    { 222 , lang.finals+146 ,
                              {
                               { lang.elements+9 , lang.states+543 },
                               { lang.elements+10 , lang.states+539 },
                               { lang.elements+19 , lang.states+114 }
                              }
    },
    { 223 , lang.finals+147 ,
                              {
                               { lang.elements+19 , lang.states+114 }
                              }
    },
    { 224 , lang.finals+148 ,
                              {
                               
                              }
    },
    { 225 , lang.finals+149 ,
                              {
                               { lang.elements+9 , lang.states+544 },
                               { lang.elements+10 , lang.states+540 },
                               { lang.elements+19 , lang.states+115 }
                              }
    },
    { 226 , lang.finals+150 ,
                              {
                               { lang.elements+9 , lang.states+545 },
                               { lang.elements+10 , lang.states+541 },
                               { lang.elements+19 , lang.states+116 }
                              }
    },
    { 227 , lang.finals+151 ,
                              {
                               { lang.elements+19 , lang.states+115 }
                              }
    },
    { 228 , lang.finals+152 ,
                              {
                               
                              }
    },
    { 229 , lang.finals+153 ,
                              {
                               { lang.elements+19 , lang.states+116 }
                              }
    },
    { 230 , lang.finals+154 ,
                              {
                               
                              }
    },
    { 231 , lang.finals+155 ,
                              {
                               { lang.elements+9 , lang.states+542 },
                               { lang.elements+10 , lang.states+538 },
                               { lang.elements+19 , lang.states+113 }
                              }
    },
    { 232 , lang.finals+156 ,
                              {
                               { lang.elements+19 , lang.states+113 }
                              }
    },
    { 233 , lang.finals+157 ,
                              {
                               
                              }
    },
    { 234 , lang.finals+158 ,
                              {
                               { lang.elements+9 , lang.states+543 },
                               { lang.elements+10 , lang.states+539 },
                               { lang.elements+19 , lang.states+114 }
                              }
    },
    { 235 , lang.finals+159 ,
                              {
                               { lang.elements+19 , lang.states+114 }
                              }
    },
    { 236 , lang.finals+160 ,
                              {
                               
                              }
    },
    { 237 , lang.finals+161 ,
                              {
                               { lang.elements+9 , lang.states+544 },
                               { lang.elements+10 , lang.states+540 },
                               { lang.elements+19 , lang.states+115 }
                              }
    },
    { 238 , lang.finals+162 ,
                              {
                               { lang.elements+9 , lang.states+545 },
                               { lang.elements+10 , lang.states+541 },
                               { lang.elements+19 , lang.states+116 }
                              }
    },
    { 239 , lang.finals+163 ,
                              {
                               { lang.elements+19 , lang.states+115 }
                              }
    },
    { 240 , lang.finals+164 ,
                              {
                               
                              }
    },
    { 241 , lang.finals+165 ,
                              {
                               { lang.elements+19 , lang.states+116 }
                              }
    },
    { 242 , lang.finals+166 ,
                              {
                               
                              }
    },
    { 243 , lang.finals+167 ,
                              {
                               { lang.elements+9 , lang.states+542 },
                               { lang.elements+10 , lang.states+538 },
                               { lang.elements+19 , lang.states+113 }
                              }
    },
    { 244 , lang.finals+168 ,
                              {
                               { lang.elements+19 , lang.states+113 }
                              }
    },
    { 245 , lang.finals+169 ,
                              {
                               
                              }
    },
    { 246 , lang.finals+170 ,
                              {
                               { lang.elements+9 , lang.states+543 },
                               { lang.elements+10 , lang.states+539 },
                               { lang.elements+19 , lang.states+114 }
                              }
    },
    { 247 , lang.finals+171 ,
                              {
                               { lang.elements+19 , lang.states+114 }
                              }
    },
    { 248 , lang.finals+172 ,
                              {
                               
                              }
    },
    { 249 , lang.finals+173 ,
                              {
                               { lang.elements+9 , lang.states+544 },
                               { lang.elements+10 , lang.states+540 },
                               { lang.elements+19 , lang.states+115 }
                              }
    },
    { 250 , lang.finals+174 ,
                              {
                               { lang.elements+9 , lang.states+545 },
                               { lang.elements+10 , lang.states+541 },
                               { lang.elements+19 , lang.states+116 }
                              }
    },
    { 251 , lang.finals+175 ,
                              {
                               { lang.elements+19 , lang.states+115 }
                              }
    },
    { 252 , lang.finals+176 ,
                              {
                               
                              }
    },
    { 253 , lang.finals+177 ,
                              {
                               { lang.elements+19 , lang.states+116 }
                              }
    },
    { 254 , lang.finals+178 ,
                              {
                               
                              }
    },
    { 255 , lang.finals+179 ,
                              {
                               
                              }
    },
    { 256 , lang.finals+180 ,
                              {
                               
                              }
    },
    { 257 , lang.finals+181 ,
                              {
                               
                              }
    },
    { 258 , lang.finals+182 ,
                              {
                               
                              }
    },
    { 259 , lang.finals+183 ,
                              {
                               
                              }
    },
    { 260 , lang.finals+184 ,
                              {
                               
                              }
    },
    { 261 , lang.finals+185 ,
                              {
                               
                              }
    },
    { 262 , lang.finals+186 ,
                              {
                               
                              }
    },
    { 263 , lang.finals+187 ,
                              {
                               
                              }
    },
    { 264 , lang.finals+188 ,
                              {
                               
                              }
    },
    { 265 , lang.finals+189 ,
                              {
                               
                              }
    },
    { 266 , lang.finals+190 ,
                              {
                               
                              }
    },
    { 267 , lang.finals+191 ,
                              {
                               { lang.elements+1 , lang.states+71 },
                               { lang.elements+5 , lang.states+69 },
                               { lang.elements+9 , lang.states+542 },
                               { lang.elements+10 , lang.states+538 },
                               { lang.elements+11 , lang.states+70 },
                               { lang.elements+19 , lang.states+113 }
                              }
    },
    { 268 , lang.finals+192 ,
                              {
                               { lang.elements+1 , lang.states+71 },
                               { lang.elements+5 , lang.states+69 },
                               { lang.elements+11 , lang.states+70 },
                               { lang.elements+19 , lang.states+113 }
                              }
    },
    { 269 , lang.finals+193 ,
                              {
                               { lang.elements+1 , lang.states+71 },
                               { lang.elements+5 , lang.states+69 },
                               { lang.elements+11 , lang.states+70 }
                              }
    },
    { 270 , lang.finals+194 ,
                              {
                               { lang.elements+1 , lang.states+71 },
                               { lang.elements+5 , lang.states+69 },
                               { lang.elements+9 , lang.states+542 },
                               { lang.elements+10 , lang.states+538 },
                               { lang.elements+11 , lang.states+70 },
                               { lang.elements+19 , lang.states+113 }
                              }
    },
    { 271 , lang.finals+195 ,
                              {
                               { lang.elements+1 , lang.states+71 },
                               { lang.elements+5 , lang.states+69 },
                               { lang.elements+11 , lang.states+70 },
                               { lang.elements+19 , lang.states+113 }
                              }
    },
    { 272 , lang.finals+196 ,
                              {
                               { lang.elements+1 , lang.states+71 },
                               { lang.elements+5 , lang.states+69 },
                               { lang.elements+11 , lang.states+70 }
                              }
    },
    { 273 , lang.finals+197 ,
                              {
                               { lang.elements+1 , lang.states+71 },
                               { lang.elements+4 , lang.states+139 },
                               { lang.elements+5 , lang.states+69 },
                               { lang.elements+6 , lang.states+63 },
                               { lang.elements+8 , lang.states+64 },
                               { lang.elements+9 , lang.states+542 },
                               { lang.elements+10 , lang.states+538 },
                               { lang.elements+11 , lang.states+70 },
                               { lang.elements+19 , lang.states+113 },
                               { lang.elements+41 , lang.states+491 }
                              }
    },
    { 274 , lang.finals+197 ,
                              {
                               { lang.elements+1 , lang.states+71 },
                               { lang.elements+4 , lang.states+140 },
                               { lang.elements+5 , lang.states+69 },
                               { lang.elements+6 , lang.states+63 },
                               { lang.elements+8 , lang.states+64 },
                               { lang.elements+9 , lang.states+542 },
                               { lang.elements+10 , lang.states+538 },
                               { lang.elements+11 , lang.states+70 },
                               { lang.elements+19 , lang.states+113 },
                               { lang.elements+41 , lang.states+491 }
                              }
    },
    { 275 , lang.finals+197 ,
                              {
                               { lang.elements+1 , lang.states+71 },
                               { lang.elements+4 , lang.states+141 },
                               { lang.elements+5 , lang.states+69 },
                               { lang.elements+6 , lang.states+63 },
                               { lang.elements+8 , lang.states+64 },
                               { lang.elements+9 , lang.states+542 },
                               { lang.elements+10 , lang.states+538 },
                               { lang.elements+11 , lang.states+70 },
                               { lang.elements+19 , lang.states+113 },
                               { lang.elements+41 , lang.states+491 }
                              }
    },
    { 276 , lang.finals+197 ,
                              {
                               { lang.elements+1 , lang.states+71 },
                               { lang.elements+4 , lang.states+142 },
                               { lang.elements+5 , lang.states+69 },
                               { lang.elements+6 , lang.states+63 },
                               { lang.elements+8 , lang.states+64 },
                               { lang.elements+9 , lang.states+542 },
                               { lang.elements+10 , lang.states+538 },
                               { lang.elements+11 , lang.states+70 },
                               { lang.elements+19 , lang.states+113 },
                               { lang.elements+41 , lang.states+491 }
                              }
    },
    { 277 , lang.finals+197 ,
                              {
                               { lang.elements+1 , lang.states+71 },
                               { lang.elements+4 , lang.states+151 },
                               { lang.elements+5 , lang.states+69 },
                               { lang.elements+6 , lang.states+63 },
                               { lang.elements+8 , lang.states+64 },
                               { lang.elements+9 , lang.states+542 },
                               { lang.elements+10 , lang.states+538 },
                               { lang.elements+11 , lang.states+70 },
                               { lang.elements+19 , lang.states+113 },
                               { lang.elements+41 , lang.states+491 }
                              }
    },
    { 278 , lang.finals+197 ,
                              {
                               { lang.elements+1 , lang.states+71 },
                               { lang.elements+4 , lang.states+152 },
                               { lang.elements+5 , lang.states+69 },
                               { lang.elements+6 , lang.states+63 },
                               { lang.elements+8 , lang.states+64 },
                               { lang.elements+9 , lang.states+542 },
                               { lang.elements+10 , lang.states+538 },
                               { lang.elements+11 , lang.states+70 },
                               { lang.elements+19 , lang.states+113 },
                               { lang.elements+41 , lang.states+491 }
                              }
    },
    { 279 , lang.finals+197 ,
                              {
                               { lang.elements+1 , lang.states+71 },
                               { lang.elements+4 , lang.states+153 },
                               { lang.elements+5 , lang.states+69 },
                               { lang.elements+6 , lang.states+63 },
                               { lang.elements+8 , lang.states+64 },
                               { lang.elements+9 , lang.states+542 },
                               { lang.elements+10 , lang.states+538 },
                               { lang.elements+11 , lang.states+70 },
                               { lang.elements+19 , lang.states+113 },
                               { lang.elements+41 , lang.states+491 }
                              }
    },
    { 280 , lang.finals+197 ,
                              {
                               { lang.elements+1 , lang.states+71 },
                               { lang.elements+4 , lang.states+154 },
                               { lang.elements+5 , lang.states+69 },
                               { lang.elements+6 , lang.states+63 },
                               { lang.elements+8 , lang.states+64 },
                               { lang.elements+9 , lang.states+542 },
                               { lang.elements+10 , lang.states+538 },
                               { lang.elements+11 , lang.states+70 },
                               { lang.elements+19 , lang.states+113 },
                               { lang.elements+41 , lang.states+491 }
                              }
    },
    { 281 , lang.finals+198 ,
                              {
                               { lang.elements+1 , lang.states+71 },
                               { lang.elements+4 , lang.states+139 },
                               { lang.elements+5 , lang.states+69 },
                               { lang.elements+6 , lang.states+63 },
                               { lang.elements+8 , lang.states+64 },
                               { lang.elements+11 , lang.states+70 },
                               { lang.elements+19 , lang.states+113 },
                               { lang.elements+41 , lang.states+491 }
                              }
    },
    { 282 , lang.finals+198 ,
                              {
                               { lang.elements+1 , lang.states+71 },
                               { lang.elements+4 , lang.states+140 },
                               { lang.elements+5 , lang.states+69 },
                               { lang.elements+6 , lang.states+63 },
                               { lang.elements+8 , lang.states+64 },
                               { lang.elements+11 , lang.states+70 },
                               { lang.elements+19 , lang.states+113 },
                               { lang.elements+41 , lang.states+491 }
                              }
    },
    { 283 , lang.finals+198 ,
                              {
                               { lang.elements+1 , lang.states+71 },
                               { lang.elements+4 , lang.states+141 },
                               { lang.elements+5 , lang.states+69 },
                               { lang.elements+6 , lang.states+63 },
                               { lang.elements+8 , lang.states+64 },
                               { lang.elements+11 , lang.states+70 },
                               { lang.elements+19 , lang.states+113 },
                               { lang.elements+41 , lang.states+491 }
                              }
    },
    { 284 , lang.finals+198 ,
                              {
                               { lang.elements+1 , lang.states+71 },
                               { lang.elements+4 , lang.states+142 },
                               { lang.elements+5 , lang.states+69 },
                               { lang.elements+6 , lang.states+63 },
                               { lang.elements+8 , lang.states+64 },
                               { lang.elements+11 , lang.states+70 },
                               { lang.elements+19 , lang.states+113 },
                               { lang.elements+41 , lang.states+491 }
                              }
    },
    { 285 , lang.finals+198 ,
                              {
                               { lang.elements+1 , lang.states+71 },
                               { lang.elements+4 , lang.states+151 },
                               { lang.elements+5 , lang.states+69 },
                               { lang.elements+6 , lang.states+63 },
                               { lang.elements+8 , lang.states+64 },
                               { lang.elements+11 , lang.states+70 },
                               { lang.elements+19 , lang.states+113 },
                               { lang.elements+41 , lang.states+491 }
                              }
    },
    { 286 , lang.finals+198 ,
                              {
                               { lang.elements+1 , lang.states+71 },
                               { lang.elements+4 , lang.states+152 },
                               { lang.elements+5 , lang.states+69 },
                               { lang.elements+6 , lang.states+63 },
                               { lang.elements+8 , lang.states+64 },
                               { lang.elements+11 , lang.states+70 },
                               { lang.elements+19 , lang.states+113 },
                               { lang.elements+41 , lang.states+491 }
                              }
    },
    { 287 , lang.finals+198 ,
                              {
                               { lang.elements+1 , lang.states+71 },
                               { lang.elements+4 , lang.states+153 },
                               { lang.elements+5 , lang.states+69 },
                               { lang.elements+6 , lang.states+63 },
                               { lang.elements+8 , lang.states+64 },
                               { lang.elements+11 , lang.states+70 },
                               { lang.elements+19 , lang.states+113 },
                               { lang.elements+41 , lang.states+491 }
                              }
    },
    { 288 , lang.finals+198 ,
                              {
                               { lang.elements+1 , lang.states+71 },
                               { lang.elements+4 , lang.states+154 },
                               { lang.elements+5 , lang.states+69 },
                               { lang.elements+6 , lang.states+63 },
                               { lang.elements+8 , lang.states+64 },
                               { lang.elements+11 , lang.states+70 },
                               { lang.elements+19 , lang.states+113 },
                               { lang.elements+41 , lang.states+491 }
                              }
    },
    { 289 , lang.finals+199 ,
                              {
                               { lang.elements+1 , lang.states+71 },
                               { lang.elements+4 , lang.states+139 },
                               { lang.elements+5 , lang.states+69 },
                               { lang.elements+6 , lang.states+63 },
                               { lang.elements+8 , lang.states+64 },
                               { lang.elements+11 , lang.states+70 },
                               { lang.elements+41 , lang.states+491 }
                              }
    },
    { 290 , lang.finals+199 ,
                              {
                               { lang.elements+1 , lang.states+71 },
                               { lang.elements+4 , lang.states+140 },
                               { lang.elements+5 , lang.states+69 },
                               { lang.elements+6 , lang.states+63 },
                               { lang.elements+8 , lang.states+64 },
                               { lang.elements+11 , lang.states+70 },
                               { lang.elements+41 , lang.states+491 }
                              }
    },
    { 291 , lang.finals+199 ,
                              {
                               { lang.elements+1 , lang.states+71 },
                               { lang.elements+4 , lang.states+141 },
                               { lang.elements+5 , lang.states+69 },
                               { lang.elements+6 , lang.states+63 },
                               { lang.elements+8 , lang.states+64 },
                               { lang.elements+11 , lang.states+70 },
                               { lang.elements+41 , lang.states+491 }
                              }
    },
    { 292 , lang.finals+199 ,
                              {
                               { lang.elements+1 , lang.states+71 },
                               { lang.elements+4 , lang.states+142 },
                               { lang.elements+5 , lang.states+69 },
                               { lang.elements+6 , lang.states+63 },
                               { lang.elements+8 , lang.states+64 },
                               { lang.elements+11 , lang.states+70 },
                               { lang.elements+41 , lang.states+491 }
                              }
    },
    { 293 , lang.finals+199 ,
                              {
                               { lang.elements+1 , lang.states+71 },
                               { lang.elements+4 , lang.states+151 },
                               { lang.elements+5 , lang.states+69 },
                               { lang.elements+6 , lang.states+63 },
                               { lang.elements+8 , lang.states+64 },
                               { lang.elements+11 , lang.states+70 },
                               { lang.elements+41 , lang.states+491 }
                              }
    },
    { 294 , lang.finals+199 ,
                              {
                               { lang.elements+1 , lang.states+71 },
                               { lang.elements+4 , lang.states+152 },
                               { lang.elements+5 , lang.states+69 },
                               { lang.elements+6 , lang.states+63 },
                               { lang.elements+8 , lang.states+64 },
                               { lang.elements+11 , lang.states+70 },
                               { lang.elements+41 , lang.states+491 }
                              }
    },
    { 295 , lang.finals+199 ,
                              {
                               { lang.elements+1 , lang.states+71 },
                               { lang.elements+4 , lang.states+153 },
                               { lang.elements+5 , lang.states+69 },
                               { lang.elements+6 , lang.states+63 },
                               { lang.elements+8 , lang.states+64 },
                               { lang.elements+11 , lang.states+70 },
                               { lang.elements+41 , lang.states+491 }
                              }
    },
    { 296 , lang.finals+199 ,
                              {
                               { lang.elements+1 , lang.states+71 },
                               { lang.elements+4 , lang.states+154 },
                               { lang.elements+5 , lang.states+69 },
                               { lang.elements+6 , lang.states+63 },
                               { lang.elements+8 , lang.states+64 },
                               { lang.elements+11 , lang.states+70 },
                               { lang.elements+41 , lang.states+491 }
                              }
    },
    { 297 , lang.finals+200 ,
                              {
                               { lang.elements+1 , lang.states+80 },
                               { lang.elements+5 , lang.states+78 },
                               { lang.elements+9 , lang.states+543 },
                               { lang.elements+10 , lang.states+539 },
                               { lang.elements+11 , lang.states+79 },
                               { lang.elements+19 , lang.states+114 }
                              }
    },
    { 298 , lang.finals+201 ,
                              {
                               { lang.elements+1 , lang.states+80 },
                               { lang.elements+5 , lang.states+78 },
                               { lang.elements+11 , lang.states+79 },
                               { lang.elements+19 , lang.states+114 }
                              }
    },
    { 299 , lang.finals+202 ,
                              {
                               { lang.elements+1 , lang.states+80 },
                               { lang.elements+5 , lang.states+78 },
                               { lang.elements+11 , lang.states+79 }
                              }
    },
    { 300 , lang.finals+203 ,
                              {
                               { lang.elements+1 , lang.states+89 },
                               { lang.elements+5 , lang.states+87 },
                               { lang.elements+9 , lang.states+544 },
                               { lang.elements+10 , lang.states+540 },
                               { lang.elements+11 , lang.states+88 },
                               { lang.elements+19 , lang.states+115 }
                              }
    },
    { 301 , lang.finals+204 ,
                              {
                               { lang.elements+1 , lang.states+98 },
                               { lang.elements+5 , lang.states+96 },
                               { lang.elements+9 , lang.states+545 },
                               { lang.elements+10 , lang.states+541 },
                               { lang.elements+11 , lang.states+97 },
                               { lang.elements+19 , lang.states+116 }
                              }
    },
    { 302 , lang.finals+205 ,
                              {
                               { lang.elements+1 , lang.states+89 },
                               { lang.elements+5 , lang.states+87 },
                               { lang.elements+11 , lang.states+88 },
                               { lang.elements+19 , lang.states+115 }
                              }
    },
    { 303 , lang.finals+206 ,
                              {
                               { lang.elements+1 , lang.states+89 },
                               { lang.elements+5 , lang.states+87 },
                               { lang.elements+11 , lang.states+88 }
                              }
    },
    { 304 , lang.finals+207 ,
                              {
                               { lang.elements+1 , lang.states+98 },
                               { lang.elements+5 , lang.states+96 },
                               { lang.elements+11 , lang.states+97 },
                               { lang.elements+19 , lang.states+116 }
                              }
    },
    { 305 , lang.finals+208 ,
                              {
                               { lang.elements+1 , lang.states+98 },
                               { lang.elements+5 , lang.states+96 },
                               { lang.elements+11 , lang.states+97 }
                              }
    },
    { 306 , lang.finals+209 ,
                              {
                               { lang.elements+1 , lang.states+80 },
                               { lang.elements+5 , lang.states+78 },
                               { lang.elements+9 , lang.states+543 },
                               { lang.elements+10 , lang.states+539 },
                               { lang.elements+11 , lang.states+79 },
                               { lang.elements+19 , lang.states+114 }
                              }
    },
    { 307 , lang.finals+210 ,
                              {
                               { lang.elements+1 , lang.states+80 },
                               { lang.elements+5 , lang.states+78 },
                               { lang.elements+11 , lang.states+79 },
                               { lang.elements+19 , lang.states+114 }
                              }
    },
    { 308 , lang.finals+211 ,
                              {
                               { lang.elements+1 , lang.states+80 },
                               { lang.elements+5 , lang.states+78 },
                               { lang.elements+11 , lang.states+79 }
                              }
    },
    { 309 , lang.finals+212 ,
                              {
                               { lang.elements+1 , lang.states+89 },
                               { lang.elements+5 , lang.states+87 },
                               { lang.elements+9 , lang.states+544 },
                               { lang.elements+10 , lang.states+540 },
                               { lang.elements+11 , lang.states+88 },
                               { lang.elements+19 , lang.states+115 }
                              }
    },
    { 310 , lang.finals+213 ,
                              {
                               { lang.elements+1 , lang.states+98 },
                               { lang.elements+5 , lang.states+96 },
                               { lang.elements+9 , lang.states+545 },
                               { lang.elements+10 , lang.states+541 },
                               { lang.elements+11 , lang.states+97 },
                               { lang.elements+19 , lang.states+116 }
                              }
    },
    { 311 , lang.finals+214 ,
                              {
                               { lang.elements+1 , lang.states+89 },
                               { lang.elements+5 , lang.states+87 },
                               { lang.elements+11 , lang.states+88 },
                               { lang.elements+19 , lang.states+115 }
                              }
    },
    { 312 , lang.finals+215 ,
                              {
                               { lang.elements+1 , lang.states+89 },
                               { lang.elements+5 , lang.states+87 },
                               { lang.elements+11 , lang.states+88 }
                              }
    },
    { 313 , lang.finals+216 ,
                              {
                               { lang.elements+1 , lang.states+98 },
                               { lang.elements+5 , lang.states+96 },
                               { lang.elements+11 , lang.states+97 },
                               { lang.elements+19 , lang.states+116 }
                              }
    },
    { 314 , lang.finals+217 ,
                              {
                               { lang.elements+1 , lang.states+98 },
                               { lang.elements+5 , lang.states+96 },
                               { lang.elements+11 , lang.states+97 }
                              }
    },
    { 315 , lang.finals+218 ,
                              {
                               { lang.elements+1 , lang.states+80 },
                               { lang.elements+5 , lang.states+78 },
                               { lang.elements+6 , lang.states+72 },
                               { lang.elements+8 , lang.states+73 },
                               { lang.elements+9 , lang.states+543 },
                               { lang.elements+10 , lang.states+539 },
                               { lang.elements+11 , lang.states+79 },
                               { lang.elements+19 , lang.states+114 },
                               { lang.elements+41 , lang.states+492 }
                              }
    },
    { 316 , lang.finals+219 ,
                              {
                               { lang.elements+1 , lang.states+80 },
                               { lang.elements+5 , lang.states+78 },
                               { lang.elements+6 , lang.states+72 },
                               { lang.elements+8 , lang.states+73 },
                               { lang.elements+11 , lang.states+79 },
                               { lang.elements+19 , lang.states+114 },
                               { lang.elements+41 , lang.states+492 }
                              }
    },
    { 317 , lang.finals+220 ,
                              {
                               { lang.elements+1 , lang.states+80 },
                               { lang.elements+5 , lang.states+78 },
                               { lang.elements+6 , lang.states+72 },
                               { lang.elements+8 , lang.states+73 },
                               { lang.elements+11 , lang.states+79 },
                               { lang.elements+41 , lang.states+492 }
                              }
    },
    { 318 , lang.finals+221 ,
                              {
                               { lang.elements+1 , lang.states+80 },
                               { lang.elements+5 , lang.states+78 },
                               { lang.elements+6 , lang.states+72 },
                               { lang.elements+8 , lang.states+73 },
                               { lang.elements+9 , lang.states+543 },
                               { lang.elements+10 , lang.states+539 },
                               { lang.elements+11 , lang.states+79 },
                               { lang.elements+19 , lang.states+114 },
                               { lang.elements+41 , lang.states+492 }
                              }
    },
    { 319 , lang.finals+222 ,
                              {
                               { lang.elements+1 , lang.states+80 },
                               { lang.elements+5 , lang.states+78 },
                               { lang.elements+6 , lang.states+72 },
                               { lang.elements+8 , lang.states+73 },
                               { lang.elements+11 , lang.states+79 },
                               { lang.elements+19 , lang.states+114 },
                               { lang.elements+41 , lang.states+492 }
                              }
    },
    { 320 , lang.finals+223 ,
                              {
                               { lang.elements+1 , lang.states+80 },
                               { lang.elements+5 , lang.states+78 },
                               { lang.elements+6 , lang.states+72 },
                               { lang.elements+8 , lang.states+73 },
                               { lang.elements+11 , lang.states+79 },
                               { lang.elements+41 , lang.states+492 }
                              }
    },
    { 321 , lang.finals+224 ,
                              {
                               { lang.elements+1 , lang.states+80 },
                               { lang.elements+5 , lang.states+78 },
                               { lang.elements+6 , lang.states+72 },
                               { lang.elements+8 , lang.states+73 },
                               { lang.elements+9 , lang.states+543 },
                               { lang.elements+10 , lang.states+539 },
                               { lang.elements+11 , lang.states+79 },
                               { lang.elements+19 , lang.states+114 },
                               { lang.elements+41 , lang.states+492 }
                              }
    },
    { 322 , lang.finals+225 ,
                              {
                               { lang.elements+1 , lang.states+80 },
                               { lang.elements+5 , lang.states+78 },
                               { lang.elements+6 , lang.states+72 },
                               { lang.elements+8 , lang.states+73 },
                               { lang.elements+11 , lang.states+79 },
                               { lang.elements+19 , lang.states+114 },
                               { lang.elements+41 , lang.states+492 }
                              }
    },
    { 323 , lang.finals+226 ,
                              {
                               { lang.elements+1 , lang.states+80 },
                               { lang.elements+5 , lang.states+78 },
                               { lang.elements+6 , lang.states+72 },
                               { lang.elements+8 , lang.states+73 },
                               { lang.elements+11 , lang.states+79 },
                               { lang.elements+41 , lang.states+492 }
                              }
    },
    { 324 , lang.finals+227 ,
                              {
                               { lang.elements+1 , lang.states+89 },
                               { lang.elements+5 , lang.states+87 },
                               { lang.elements+6 , lang.states+81 },
                               { lang.elements+8 , lang.states+82 },
                               { lang.elements+9 , lang.states+544 },
                               { lang.elements+10 , lang.states+540 },
                               { lang.elements+11 , lang.states+88 },
                               { lang.elements+12 , lang.states+11 },
                               { lang.elements+19 , lang.states+115 },
                               { lang.elements+41 , lang.states+493 }
                              }
    },
    { 325 , lang.finals+227 ,
                              {
                               { lang.elements+1 , lang.states+89 },
                               { lang.elements+5 , lang.states+87 },
                               { lang.elements+6 , lang.states+81 },
                               { lang.elements+8 , lang.states+82 },
                               { lang.elements+9 , lang.states+544 },
                               { lang.elements+10 , lang.states+540 },
                               { lang.elements+11 , lang.states+88 },
                               { lang.elements+12 , lang.states+12 },
                               { lang.elements+19 , lang.states+115 },
                               { lang.elements+41 , lang.states+493 }
                              }
    },
    { 326 , lang.finals+227 ,
                              {
                               { lang.elements+1 , lang.states+89 },
                               { lang.elements+5 , lang.states+87 },
                               { lang.elements+6 , lang.states+81 },
                               { lang.elements+8 , lang.states+82 },
                               { lang.elements+9 , lang.states+544 },
                               { lang.elements+10 , lang.states+540 },
                               { lang.elements+11 , lang.states+88 },
                               { lang.elements+12 , lang.states+32 },
                               { lang.elements+19 , lang.states+115 },
                               { lang.elements+41 , lang.states+493 }
                              }
    },
    { 327 , lang.finals+227 ,
                              {
                               { lang.elements+1 , lang.states+89 },
                               { lang.elements+5 , lang.states+87 },
                               { lang.elements+6 , lang.states+81 },
                               { lang.elements+8 , lang.states+82 },
                               { lang.elements+9 , lang.states+544 },
                               { lang.elements+10 , lang.states+540 },
                               { lang.elements+11 , lang.states+88 },
                               { lang.elements+12 , lang.states+592 },
                               { lang.elements+19 , lang.states+115 },
                               { lang.elements+41 , lang.states+493 }
                              }
    },
    { 328 , lang.finals+228 ,
                              {
                               { lang.elements+1 , lang.states+98 },
                               { lang.elements+5 , lang.states+96 },
                               { lang.elements+6 , lang.states+90 },
                               { lang.elements+8 , lang.states+91 },
                               { lang.elements+9 , lang.states+545 },
                               { lang.elements+10 , lang.states+541 },
                               { lang.elements+11 , lang.states+97 },
                               { lang.elements+19 , lang.states+116 },
                               { lang.elements+20 , lang.states+155 },
                               { lang.elements+41 , lang.states+494 }
                              }
    },
    { 329 , lang.finals+228 ,
                              {
                               { lang.elements+1 , lang.states+98 },
                               { lang.elements+5 , lang.states+96 },
                               { lang.elements+6 , lang.states+90 },
                               { lang.elements+8 , lang.states+91 },
                               { lang.elements+9 , lang.states+545 },
                               { lang.elements+10 , lang.states+541 },
                               { lang.elements+11 , lang.states+97 },
                               { lang.elements+19 , lang.states+116 },
                               { lang.elements+20 , lang.states+156 },
                               { lang.elements+41 , lang.states+494 }
                              }
    },
    { 330 , lang.finals+228 ,
                              {
                               { lang.elements+1 , lang.states+98 },
                               { lang.elements+5 , lang.states+96 },
                               { lang.elements+6 , lang.states+90 },
                               { lang.elements+8 , lang.states+91 },
                               { lang.elements+9 , lang.states+545 },
                               { lang.elements+10 , lang.states+541 },
                               { lang.elements+11 , lang.states+97 },
                               { lang.elements+19 , lang.states+116 },
                               { lang.elements+20 , lang.states+157 },
                               { lang.elements+41 , lang.states+494 }
                              }
    },
    { 331 , lang.finals+228 ,
                              {
                               { lang.elements+1 , lang.states+98 },
                               { lang.elements+5 , lang.states+96 },
                               { lang.elements+6 , lang.states+90 },
                               { lang.elements+8 , lang.states+91 },
                               { lang.elements+9 , lang.states+545 },
                               { lang.elements+10 , lang.states+541 },
                               { lang.elements+11 , lang.states+97 },
                               { lang.elements+19 , lang.states+116 },
                               { lang.elements+20 , lang.states+158 },
                               { lang.elements+41 , lang.states+494 }
                              }
    },
    { 332 , lang.finals+228 ,
                              {
                               { lang.elements+1 , lang.states+98 },
                               { lang.elements+5 , lang.states+96 },
                               { lang.elements+6 , lang.states+90 },
                               { lang.elements+8 , lang.states+91 },
                               { lang.elements+9 , lang.states+545 },
                               { lang.elements+10 , lang.states+541 },
                               { lang.elements+11 , lang.states+97 },
                               { lang.elements+19 , lang.states+116 },
                               { lang.elements+20 , lang.states+430 },
                               { lang.elements+41 , lang.states+494 }
                              }
    },
    { 333 , lang.finals+228 ,
                              {
                               { lang.elements+1 , lang.states+98 },
                               { lang.elements+5 , lang.states+96 },
                               { lang.elements+6 , lang.states+90 },
                               { lang.elements+8 , lang.states+91 },
                               { lang.elements+9 , lang.states+545 },
                               { lang.elements+10 , lang.states+541 },
                               { lang.elements+11 , lang.states+97 },
                               { lang.elements+19 , lang.states+116 },
                               { lang.elements+20 , lang.states+431 },
                               { lang.elements+41 , lang.states+494 }
                              }
    },
    { 334 , lang.finals+229 ,
                              {
                               { lang.elements+1 , lang.states+89 },
                               { lang.elements+5 , lang.states+87 },
                               { lang.elements+6 , lang.states+81 },
                               { lang.elements+8 , lang.states+82 },
                               { lang.elements+11 , lang.states+88 },
                               { lang.elements+12 , lang.states+11 },
                               { lang.elements+19 , lang.states+115 },
                               { lang.elements+41 , lang.states+493 }
                              }
    },
    { 335 , lang.finals+229 ,
                              {
                               { lang.elements+1 , lang.states+89 },
                               { lang.elements+5 , lang.states+87 },
                               { lang.elements+6 , lang.states+81 },
                               { lang.elements+8 , lang.states+82 },
                               { lang.elements+11 , lang.states+88 },
                               { lang.elements+12 , lang.states+12 },
                               { lang.elements+19 , lang.states+115 },
                               { lang.elements+41 , lang.states+493 }
                              }
    },
    { 336 , lang.finals+229 ,
                              {
                               { lang.elements+1 , lang.states+89 },
                               { lang.elements+5 , lang.states+87 },
                               { lang.elements+6 , lang.states+81 },
                               { lang.elements+8 , lang.states+82 },
                               { lang.elements+11 , lang.states+88 },
                               { lang.elements+12 , lang.states+32 },
                               { lang.elements+19 , lang.states+115 },
                               { lang.elements+41 , lang.states+493 }
                              }
    },
    { 337 , lang.finals+229 ,
                              {
                               { lang.elements+1 , lang.states+89 },
                               { lang.elements+5 , lang.states+87 },
                               { lang.elements+6 , lang.states+81 },
                               { lang.elements+8 , lang.states+82 },
                               { lang.elements+11 , lang.states+88 },
                               { lang.elements+12 , lang.states+592 },
                               { lang.elements+19 , lang.states+115 },
                               { lang.elements+41 , lang.states+493 }
                              }
    },
    { 338 , lang.finals+230 ,
                              {
                               { lang.elements+1 , lang.states+89 },
                               { lang.elements+5 , lang.states+87 },
                               { lang.elements+6 , lang.states+81 },
                               { lang.elements+8 , lang.states+82 },
                               { lang.elements+11 , lang.states+88 },
                               { lang.elements+12 , lang.states+11 },
                               { lang.elements+41 , lang.states+493 }
                              }
    },
    { 339 , lang.finals+230 ,
                              {
                               { lang.elements+1 , lang.states+89 },
                               { lang.elements+5 , lang.states+87 },
                               { lang.elements+6 , lang.states+81 },
                               { lang.elements+8 , lang.states+82 },
                               { lang.elements+11 , lang.states+88 },
                               { lang.elements+12 , lang.states+12 },
                               { lang.elements+41 , lang.states+493 }
                              }
    },
    { 340 , lang.finals+230 ,
                              {
                               { lang.elements+1 , lang.states+89 },
                               { lang.elements+5 , lang.states+87 },
                               { lang.elements+6 , lang.states+81 },
                               { lang.elements+8 , lang.states+82 },
                               { lang.elements+11 , lang.states+88 },
                               { lang.elements+12 , lang.states+32 },
                               { lang.elements+41 , lang.states+493 }
                              }
    },
    { 341 , lang.finals+230 ,
                              {
                               { lang.elements+1 , lang.states+89 },
                               { lang.elements+5 , lang.states+87 },
                               { lang.elements+6 , lang.states+81 },
                               { lang.elements+8 , lang.states+82 },
                               { lang.elements+11 , lang.states+88 },
                               { lang.elements+12 , lang.states+592 },
                               { lang.elements+41 , lang.states+493 }
                              }
    },
    { 342 , lang.finals+231 ,
                              {
                               { lang.elements+1 , lang.states+98 },
                               { lang.elements+5 , lang.states+96 },
                               { lang.elements+6 , lang.states+90 },
                               { lang.elements+8 , lang.states+91 },
                               { lang.elements+11 , lang.states+97 },
                               { lang.elements+19 , lang.states+116 },
                               { lang.elements+20 , lang.states+155 },
                               { lang.elements+41 , lang.states+494 }
                              }
    },
    { 343 , lang.finals+231 ,
                              {
                               { lang.elements+1 , lang.states+98 },
                               { lang.elements+5 , lang.states+96 },
                               { lang.elements+6 , lang.states+90 },
                               { lang.elements+8 , lang.states+91 },
                               { lang.elements+11 , lang.states+97 },
                               { lang.elements+19 , lang.states+116 },
                               { lang.elements+20 , lang.states+156 },
                               { lang.elements+41 , lang.states+494 }
                              }
    },
    { 344 , lang.finals+231 ,
                              {
                               { lang.elements+1 , lang.states+98 },
                               { lang.elements+5 , lang.states+96 },
                               { lang.elements+6 , lang.states+90 },
                               { lang.elements+8 , lang.states+91 },
                               { lang.elements+11 , lang.states+97 },
                               { lang.elements+19 , lang.states+116 },
                               { lang.elements+20 , lang.states+157 },
                               { lang.elements+41 , lang.states+494 }
                              }
    },
    { 345 , lang.finals+231 ,
                              {
                               { lang.elements+1 , lang.states+98 },
                               { lang.elements+5 , lang.states+96 },
                               { lang.elements+6 , lang.states+90 },
                               { lang.elements+8 , lang.states+91 },
                               { lang.elements+11 , lang.states+97 },
                               { lang.elements+19 , lang.states+116 },
                               { lang.elements+20 , lang.states+158 },
                               { lang.elements+41 , lang.states+494 }
                              }
    },
    { 346 , lang.finals+231 ,
                              {
                               { lang.elements+1 , lang.states+98 },
                               { lang.elements+5 , lang.states+96 },
                               { lang.elements+6 , lang.states+90 },
                               { lang.elements+8 , lang.states+91 },
                               { lang.elements+11 , lang.states+97 },
                               { lang.elements+19 , lang.states+116 },
                               { lang.elements+20 , lang.states+430 },
                               { lang.elements+41 , lang.states+494 }
                              }
    },
    { 347 , lang.finals+231 ,
                              {
                               { lang.elements+1 , lang.states+98 },
                               { lang.elements+5 , lang.states+96 },
                               { lang.elements+6 , lang.states+90 },
                               { lang.elements+8 , lang.states+91 },
                               { lang.elements+11 , lang.states+97 },
                               { lang.elements+19 , lang.states+116 },
                               { lang.elements+20 , lang.states+431 },
                               { lang.elements+41 , lang.states+494 }
                              }
    },
    { 348 , lang.finals+232 ,
                              {
                               { lang.elements+1 , lang.states+98 },
                               { lang.elements+5 , lang.states+96 },
                               { lang.elements+6 , lang.states+90 },
                               { lang.elements+8 , lang.states+91 },
                               { lang.elements+11 , lang.states+97 },
                               { lang.elements+20 , lang.states+155 },
                               { lang.elements+41 , lang.states+494 }
                              }
    },
    { 349 , lang.finals+232 ,
                              {
                               { lang.elements+1 , lang.states+98 },
                               { lang.elements+5 , lang.states+96 },
                               { lang.elements+6 , lang.states+90 },
                               { lang.elements+8 , lang.states+91 },
                               { lang.elements+11 , lang.states+97 },
                               { lang.elements+20 , lang.states+156 },
                               { lang.elements+41 , lang.states+494 }
                              }
    },
    { 350 , lang.finals+232 ,
                              {
                               { lang.elements+1 , lang.states+98 },
                               { lang.elements+5 , lang.states+96 },
                               { lang.elements+6 , lang.states+90 },
                               { lang.elements+8 , lang.states+91 },
                               { lang.elements+11 , lang.states+97 },
                               { lang.elements+20 , lang.states+157 },
                               { lang.elements+41 , lang.states+494 }
                              }
    },
    { 351 , lang.finals+232 ,
                              {
                               { lang.elements+1 , lang.states+98 },
                               { lang.elements+5 , lang.states+96 },
                               { lang.elements+6 , lang.states+90 },
                               { lang.elements+8 , lang.states+91 },
                               { lang.elements+11 , lang.states+97 },
                               { lang.elements+20 , lang.states+158 },
                               { lang.elements+41 , lang.states+494 }
                              }
    },
    { 352 , lang.finals+232 ,
                              {
                               { lang.elements+1 , lang.states+98 },
                               { lang.elements+5 , lang.states+96 },
                               { lang.elements+6 , lang.states+90 },
                               { lang.elements+8 , lang.states+91 },
                               { lang.elements+11 , lang.states+97 },
                               { lang.elements+20 , lang.states+430 },
                               { lang.elements+41 , lang.states+494 }
                              }
    },
    { 353 , lang.finals+232 ,
                              {
                               { lang.elements+1 , lang.states+98 },
                               { lang.elements+5 , lang.states+96 },
                               { lang.elements+6 , lang.states+90 },
                               { lang.elements+8 , lang.states+91 },
                               { lang.elements+11 , lang.states+97 },
                               { lang.elements+20 , lang.states+431 },
                               { lang.elements+41 , lang.states+494 }
                              }
    },
    { 354 , lang.finals+233 ,
                              {
                               
                              }
    },
    { 355 , lang.finals+234 ,
                              {
                               
                              }
    },
    { 356 , lang.finals+235 ,
                              {
                               
                              }
    },
    { 357 , lang.finals+236 ,
                              {
                               
                              }
    },
    { 358 , lang.finals+237 ,
                              {
                               
                              }
    },
    { 359 , lang.finals+238 ,
                              {
                               
                              }
    },
    { 360 , lang.finals+239 ,
                              {
                               
                              }
    },
    { 361 , lang.finals+240 ,
                              {
                               
                              }
    },
    { 362 , lang.finals+241 ,
                              {
                               
                              }
    },
    { 363 , lang.finals+242 ,
                              {
                               
                              }
    },
    { 364 , lang.finals+243 ,
                              {
                               
                              }
    },
    { 365 , lang.finals+244 ,
                              {
                               
                              }
    },
    { 366 , lang.finals+245 ,
                              {
                               
                              }
    },
    { 367 , lang.finals+246 ,
                              {
                               { lang.elements+3 , lang.states+103 }
                              }
    },
    { 368 , lang.finals+246 ,
                              {
                               { lang.elements+3 , lang.states+104 }
                              }
    },
    { 369 , lang.finals+246 ,
                              {
                               { lang.elements+3 , lang.states+105 }
                              }
    },
    { 370 , lang.finals+246 ,
                              {
                               { lang.elements+3 , lang.states+106 }
                              }
    },
    { 371 , lang.finals+247 ,
                              {
                               
                              }
    },
    { 372 , lang.finals+248 ,
                              {
                               
                              }
    },
    { 373 , lang.finals+249 ,
                              {
                               
                              }
    },
    { 374 , lang.finals+250 ,
                              {
                               
                              }
    },
    { 375 , lang.finals+251 ,
                              {
                               
                              }
    },
    { 376 , lang.finals+252 ,
                              {
                               { lang.elements+4 , lang.states+139 },
                               { lang.elements+6 , lang.states+63 },
                               { lang.elements+8 , lang.states+64 },
                               { lang.elements+41 , lang.states+491 }
                              }
    },
    { 377 , lang.finals+252 ,
                              {
                               { lang.elements+4 , lang.states+140 },
                               { lang.elements+6 , lang.states+63 },
                               { lang.elements+8 , lang.states+64 },
                               { lang.elements+41 , lang.states+491 }
                              }
    },
    { 378 , lang.finals+252 ,
                              {
                               { lang.elements+4 , lang.states+141 },
                               { lang.elements+6 , lang.states+63 },
                               { lang.elements+8 , lang.states+64 },
                               { lang.elements+41 , lang.states+491 }
                              }
    },
    { 379 , lang.finals+252 ,
                              {
                               { lang.elements+4 , lang.states+142 },
                               { lang.elements+6 , lang.states+63 },
                               { lang.elements+8 , lang.states+64 },
                               { lang.elements+41 , lang.states+491 }
                              }
    },
    { 380 , lang.finals+252 ,
                              {
                               { lang.elements+4 , lang.states+151 },
                               { lang.elements+6 , lang.states+63 },
                               { lang.elements+8 , lang.states+64 },
                               { lang.elements+41 , lang.states+491 }
                              }
    },
    { 381 , lang.finals+252 ,
                              {
                               { lang.elements+4 , lang.states+152 },
                               { lang.elements+6 , lang.states+63 },
                               { lang.elements+8 , lang.states+64 },
                               { lang.elements+41 , lang.states+491 }
                              }
    },
    { 382 , lang.finals+252 ,
                              {
                               { lang.elements+4 , lang.states+153 },
                               { lang.elements+6 , lang.states+63 },
                               { lang.elements+8 , lang.states+64 },
                               { lang.elements+41 , lang.states+491 }
                              }
    },
    { 383 , lang.finals+252 ,
                              {
                               { lang.elements+4 , lang.states+154 },
                               { lang.elements+6 , lang.states+63 },
                               { lang.elements+8 , lang.states+64 },
                               { lang.elements+41 , lang.states+491 }
                              }
    },
    { 384 , lang.finals+253 ,
                              {
                               { lang.elements+4 , lang.states+139 },
                               { lang.elements+41 , lang.states+491 }
                              }
    },
    { 385 , lang.finals+253 ,
                              {
                               { lang.elements+4 , lang.states+140 },
                               { lang.elements+41 , lang.states+491 }
                              }
    },
    { 386 , lang.finals+253 ,
                              {
                               { lang.elements+4 , lang.states+141 },
                               { lang.elements+41 , lang.states+491 }
                              }
    },
    { 387 , lang.finals+253 ,
                              {
                               { lang.elements+4 , lang.states+142 },
                               { lang.elements+41 , lang.states+491 }
                              }
    },
    { 388 , lang.finals+253 ,
                              {
                               { lang.elements+4 , lang.states+151 },
                               { lang.elements+41 , lang.states+491 }
                              }
    },
    { 389 , lang.finals+253 ,
                              {
                               { lang.elements+4 , lang.states+152 },
                               { lang.elements+41 , lang.states+491 }
                              }
    },
    { 390 , lang.finals+253 ,
                              {
                               { lang.elements+4 , lang.states+153 },
                               { lang.elements+41 , lang.states+491 }
                              }
    },
    { 391 , lang.finals+253 ,
                              {
                               { lang.elements+4 , lang.states+154 },
                               { lang.elements+41 , lang.states+491 }
                              }
    },
    { 392 , lang.finals+254 ,
                              {
                               
                              }
    },
    { 393 , lang.finals+255 ,
                              {
                               
                              }
    },
    { 394 , lang.finals+256 ,
                              {
                               
                              }
    },
    { 395 , lang.finals+257 ,
                              {
                               
                              }
    },
    { 396 , lang.finals+258 ,
                              {
                               
                              }
    },
    { 397 , lang.finals+259 ,
                              {
                               
                              }
    },
    { 398 , lang.finals+260 ,
                              {
                               
                              }
    },
    { 399 , lang.finals+261 ,
                              {
                               
                              }
    },
    { 400 , lang.finals+262 ,
                              {
                               
                              }
    },
    { 401 , lang.finals+263 ,
                              {
                               
                              }
    },
    { 402 , lang.finals+264 ,
                              {
                               
                              }
    },
    { 403 , lang.finals+265 ,
                              {
                               
                              }
    },
    { 404 , lang.finals+266 ,
                              {
                               
                              }
    },
    { 405 , lang.finals+267 ,
                              {
                               
                              }
    },
    { 406 , lang.finals+268 ,
                              {
                               
                              }
    },
    { 407 , lang.finals+269 ,
                              {
                               
                              }
    },
    { 408 , lang.finals+270 ,
                              {
                               
                              }
    },
    { 409 , lang.finals+271 ,
                              {
                               
                              }
    },
    { 410 , lang.finals+272 ,
                              {
                               
                              }
    },
    { 411 , lang.finals+273 ,
                              {
                               
                              }
    },
    { 412 , lang.finals+274 ,
                              {
                               
                              }
    },
    { 413 , lang.finals+275 ,
                              {
                               
                              }
    },
    { 414 , lang.finals+276 ,
                              {
                               
                              }
    },
    { 415 , lang.finals+277 ,
                              {
                               
                              }
    },
    { 416 , lang.finals+278 ,
                              {
                               
                              }
    },
    { 417 , lang.finals+279 ,
                              {
                               
                              }
    },
    { 418 , lang.finals+280 ,
                              {
                               
                              }
    },
    { 419 , lang.finals+281 ,
                              {
                               
                              }
    },
    { 420 , lang.finals+282 ,
                              {
                               
                              }
    },
    { 421 , lang.finals+283 ,
                              {
                               
                              }
    },
    { 422 , lang.finals+284 ,
                              {
                               
                              }
    },
    { 423 , lang.finals+285 ,
                              {
                               
                              }
    },
    { 424 , lang.finals+286 ,
                              {
                               
                              }
    },
    { 425 , lang.finals+287 ,
                              {
                               
                              }
    },
    { 426 , lang.finals+288 ,
                              {
                               
                              }
    },
    { 427 , lang.finals+289 ,
                              {
                               
                              }
    },
    { 428 , lang.finals+290 ,
                              {
                               
                              }
    },
    { 429 , lang.finals+291 ,
                              {
                               
                              }
    },
    { 430 , lang.finals+292 ,
                              {
                               
                              }
    },
    { 431 , lang.finals+293 ,
                              {
                               
                              }
    },
    { 432 , lang.finals+294 ,
                              {
                               
                              }
    },
    { 433 , lang.finals+295 ,
                              {
                               { lang.elements+12 , lang.states+6 }
                              }
    },
    { 434 , lang.finals+295 ,
                              {
                               { lang.elements+12 , lang.states+30 }
                              }
    },
    { 435 , lang.finals+295 ,
                              {
                               { lang.elements+12 , lang.states+588 }
                              }
    },
    { 436 , lang.finals+296 ,
                              {
                               
                              }
    },
    { 437 , lang.finals+297 ,
                              {
                               
                              }
    },
    { 438 , lang.finals+298 ,
                              {
                               
                              }
    },
    { 439 , lang.finals+299 ,
                              {
                               
                              }
    },
    { 440 , lang.finals+300 ,
                              {
                               { lang.elements+5 , lang.states+426 },
                               { lang.elements+12 , lang.states+9 },
                               { lang.elements+19 , lang.states+61 }
                              }
    },
    { 441 , lang.finals+300 ,
                              {
                               { lang.elements+5 , lang.states+426 },
                               { lang.elements+12 , lang.states+10 },
                               { lang.elements+19 , lang.states+61 }
                              }
    },
    { 442 , lang.finals+300 ,
                              {
                               { lang.elements+5 , lang.states+426 },
                               { lang.elements+12 , lang.states+591 },
                               { lang.elements+19 , lang.states+61 }
                              }
    },
    { 443 , lang.finals+301 ,
                              {
                               { lang.elements+5 , lang.states+427 },
                               { lang.elements+16 , lang.states+500 },
                               { lang.elements+19 , lang.states+62 }
                              }
    },
    { 444 , lang.finals+301 ,
                              {
                               { lang.elements+5 , lang.states+427 },
                               { lang.elements+16 , lang.states+506 },
                               { lang.elements+19 , lang.states+62 }
                              }
    },
    { 445 , lang.finals+301 ,
                              {
                               { lang.elements+5 , lang.states+427 },
                               { lang.elements+16 , lang.states+507 },
                               { lang.elements+19 , lang.states+62 }
                              }
    },
    { 446 , lang.finals+301 ,
                              {
                               { lang.elements+5 , lang.states+427 },
                               { lang.elements+16 , lang.states+508 },
                               { lang.elements+19 , lang.states+62 }
                              }
    },
    { 447 , lang.finals+302 ,
                              {
                               { lang.elements+6 , lang.states+72 },
                               { lang.elements+8 , lang.states+73 },
                               { lang.elements+41 , lang.states+492 }
                              }
    },
    { 448 , lang.finals+303 ,
                              {
                               { lang.elements+6 , lang.states+72 },
                               { lang.elements+8 , lang.states+73 },
                               { lang.elements+41 , lang.states+492 }
                              }
    },
    { 449 , lang.finals+304 ,
                              {
                               { lang.elements+6 , lang.states+72 },
                               { lang.elements+8 , lang.states+73 },
                               { lang.elements+41 , lang.states+492 }
                              }
    },
    { 450 , lang.finals+305 ,
                              {
                               { lang.elements+6 , lang.states+81 },
                               { lang.elements+8 , lang.states+82 },
                               { lang.elements+12 , lang.states+11 },
                               { lang.elements+41 , lang.states+493 }
                              }
    },
    { 451 , lang.finals+305 ,
                              {
                               { lang.elements+6 , lang.states+81 },
                               { lang.elements+8 , lang.states+82 },
                               { lang.elements+12 , lang.states+12 },
                               { lang.elements+41 , lang.states+493 }
                              }
    },
    { 452 , lang.finals+305 ,
                              {
                               { lang.elements+6 , lang.states+81 },
                               { lang.elements+8 , lang.states+82 },
                               { lang.elements+12 , lang.states+32 },
                               { lang.elements+41 , lang.states+493 }
                              }
    },
    { 453 , lang.finals+305 ,
                              {
                               { lang.elements+6 , lang.states+81 },
                               { lang.elements+8 , lang.states+82 },
                               { lang.elements+12 , lang.states+592 },
                               { lang.elements+41 , lang.states+493 }
                              }
    },
    { 454 , lang.finals+306 ,
                              {
                               { lang.elements+6 , lang.states+90 },
                               { lang.elements+8 , lang.states+91 },
                               { lang.elements+20 , lang.states+155 },
                               { lang.elements+41 , lang.states+494 }
                              }
    },
    { 455 , lang.finals+306 ,
                              {
                               { lang.elements+6 , lang.states+90 },
                               { lang.elements+8 , lang.states+91 },
                               { lang.elements+20 , lang.states+156 },
                               { lang.elements+41 , lang.states+494 }
                              }
    },
    { 456 , lang.finals+306 ,
                              {
                               { lang.elements+6 , lang.states+90 },
                               { lang.elements+8 , lang.states+91 },
                               { lang.elements+20 , lang.states+157 },
                               { lang.elements+41 , lang.states+494 }
                              }
    },
    { 457 , lang.finals+306 ,
                              {
                               { lang.elements+6 , lang.states+90 },
                               { lang.elements+8 , lang.states+91 },
                               { lang.elements+20 , lang.states+158 },
                               { lang.elements+41 , lang.states+494 }
                              }
    },
    { 458 , lang.finals+306 ,
                              {
                               { lang.elements+6 , lang.states+90 },
                               { lang.elements+8 , lang.states+91 },
                               { lang.elements+20 , lang.states+430 },
                               { lang.elements+41 , lang.states+494 }
                              }
    },
    { 459 , lang.finals+306 ,
                              {
                               { lang.elements+6 , lang.states+90 },
                               { lang.elements+8 , lang.states+91 },
                               { lang.elements+20 , lang.states+431 },
                               { lang.elements+41 , lang.states+494 }
                              }
    },
    { 460 , lang.finals+307 ,
                              {
                               
                              }
    },
    { 461 , lang.finals+308 ,
                              {
                               
                              }
    },
    { 462 , lang.finals+309 ,
                              {
                               
                              }
    },
    { 463 , lang.finals+310 ,
                              {
                               
                              }
    },
    { 464 , lang.finals+311 ,
                              {
                               
                              }
    },
    { 465 , lang.finals+312 ,
                              {
                               { lang.elements+41 , lang.states+492 }
                              }
    },
    { 466 , lang.finals+313 ,
                              {
                               { lang.elements+41 , lang.states+492 }
                              }
    },
    { 467 , lang.finals+314 ,
                              {
                               { lang.elements+41 , lang.states+492 }
                              }
    },
    { 468 , lang.finals+315 ,
                              {
                               
                              }
    },
    { 469 , lang.finals+316 ,
                              {
                               
                              }
    },
    { 470 , lang.finals+317 ,
                              {
                               { lang.elements+7 , lang.states+107 },
                               { lang.elements+42 , lang.states+372 }
                              }
    },
    { 471 , lang.finals+317 ,
                              {
                               { lang.elements+7 , lang.states+107 },
                               { lang.elements+42 , lang.states+461 }
                              }
    },
    { 472 , lang.finals+317 ,
                              {
                               { lang.elements+7 , lang.states+107 },
                               { lang.elements+42 , lang.states+496 }
                              }
    },
    { 473 , lang.finals+317 ,
                              {
                               { lang.elements+7 , lang.states+107 },
                               { lang.elements+42 , lang.states+568 }
                              }
    },
    { 474 , lang.finals+317 ,
                              {
                               { lang.elements+7 , lang.states+482 },
                               { lang.elements+42 , lang.states+373 }
                              }
    },
    { 475 , lang.finals+317 ,
                              {
                               { lang.elements+7 , lang.states+482 },
                               { lang.elements+42 , lang.states+375 }
                              }
    },
    { 476 , lang.finals+317 ,
                              {
                               { lang.elements+7 , lang.states+482 },
                               { lang.elements+42 , lang.states+462 }
                              }
    },
    { 477 , lang.finals+317 ,
                              {
                               { lang.elements+7 , lang.states+482 },
                               { lang.elements+42 , lang.states+464 }
                              }
    },
    { 478 , lang.finals+317 ,
                              {
                               { lang.elements+7 , lang.states+482 },
                               { lang.elements+42 , lang.states+497 }
                              }
    },
    { 479 , lang.finals+317 ,
                              {
                               { lang.elements+7 , lang.states+482 },
                               { lang.elements+42 , lang.states+499 }
                              }
    },
    { 480 , lang.finals+317 ,
                              {
                               { lang.elements+7 , lang.states+482 },
                               { lang.elements+42 , lang.states+569 }
                              }
    },
    { 481 , lang.finals+317 ,
                              {
                               { lang.elements+7 , lang.states+482 },
                               { lang.elements+42 , lang.states+571 }
                              }
    },
    { 482 , lang.finals+318 ,
                              {
                               { lang.elements+10 , lang.states+546 },
                               { lang.elements+63 , lang.states+469 }
                              }
    },
    { 483 , lang.finals+318 ,
                              {
                               { lang.elements+10 , lang.states+555 }
                              }
    },
    { 484 , lang.finals+318 ,
                              {
                               { lang.elements+10 , lang.states+556 }
                              }
    },
    { 485 , lang.finals+318 ,
                              {
                               { lang.elements+10 , lang.states+557 }
                              }
    },
    { 486 , lang.finals+318 ,
                              {
                               { lang.elements+10 , lang.states+558 }
                              }
    },
    { 487 , lang.finals+318 ,
                              {
                               { lang.elements+10 , lang.states+559 }
                              }
    },
    { 488 , lang.finals+318 ,
                              {
                               { lang.elements+10 , lang.states+560 }
                              }
    },
    { 489 , lang.finals+318 ,
                              {
                               { lang.elements+10 , lang.states+561 }
                              }
    },
    { 490 , lang.finals+318 ,
                              {
                               { lang.elements+10 , lang.states+562 }
                              }
    },
    { 491 , lang.finals+319 ,
                              {
                               { lang.elements+10 , lang.states+546 },
                               { lang.elements+42 , lang.states+374 },
                               { lang.elements+63 , lang.states+468 },
                               { lang.elements+64 , lang.states+475 }
                              }
    },
    { 492 , lang.finals+319 ,
                              {
                               { lang.elements+10 , lang.states+546 },
                               { lang.elements+42 , lang.states+463 },
                               { lang.elements+63 , lang.states+468 },
                               { lang.elements+64 , lang.states+477 }
                              }
    },
    { 493 , lang.finals+319 ,
                              {
                               { lang.elements+10 , lang.states+546 },
                               { lang.elements+42 , lang.states+498 },
                               { lang.elements+63 , lang.states+468 },
                               { lang.elements+64 , lang.states+479 }
                              }
    },
    { 494 , lang.finals+319 ,
                              {
                               { lang.elements+10 , lang.states+546 },
                               { lang.elements+42 , lang.states+570 },
                               { lang.elements+63 , lang.states+468 },
                               { lang.elements+64 , lang.states+481 }
                              }
    },
    { 495 , lang.finals+320 ,
                              {
                               
                              }
    },
    { 496 , lang.finals+321 ,
                              {
                               
                              }
    },
    { 497 , lang.finals+322 ,
                              {
                               
                              }
    },
    { 498 , lang.finals+323 ,
                              {
                               
                              }
    },
    { 499 , lang.finals+324 ,
                              {
                               
                              }
    },
    { 500 , lang.finals+325 ,
                              {
                               { lang.elements+12 , lang.states+31 },
                               { lang.elements+13 , lang.states+111 }
                              }
    },
    { 501 , lang.finals+326 ,
                              {
                               { lang.elements+12 , lang.states+11 },
                               { lang.elements+41 , lang.states+493 }
                              }
    },
    { 502 , lang.finals+326 ,
                              {
                               { lang.elements+12 , lang.states+12 },
                               { lang.elements+41 , lang.states+493 }
                              }
    },
    { 503 , lang.finals+326 ,
                              {
                               { lang.elements+12 , lang.states+32 },
                               { lang.elements+41 , lang.states+493 }
                              }
    },
    { 504 , lang.finals+326 ,
                              {
                               { lang.elements+12 , lang.states+592 },
                               { lang.elements+41 , lang.states+493 }
                              }
    },
    { 505 , lang.finals+327 ,
                              {
                               { lang.elements+13 , lang.states+108 }
                              }
    },
    { 506 , lang.finals+327 ,
                              {
                               { lang.elements+13 , lang.states+109 }
                              }
    },
    { 507 , lang.finals+327 ,
                              {
                               { lang.elements+13 , lang.states+110 }
                              }
    },
    { 508 , lang.finals+327 ,
                              {
                               { lang.elements+13 , lang.states+112 }
                              }
    },
    { 509 , lang.finals+327 ,
                              {
                               { lang.elements+13 , lang.states+134 }
                              }
    },
    { 510 , lang.finals+327 ,
                              {
                               { lang.elements+13 , lang.states+135 }
                              }
    },
    { 511 , lang.finals+327 ,
                              {
                               { lang.elements+13 , lang.states+136 }
                              }
    },
    { 512 , lang.finals+328 ,
                              {
                               { lang.elements+15 , lang.states+8 }
                              }
    },
    { 513 , lang.finals+328 ,
                              {
                               { lang.elements+15 , lang.states+590 }
                              }
    },
    { 514 , lang.finals+329 ,
                              {
                               { lang.elements+16 , lang.states+13 },
                               { lang.elements+48 , lang.states+49 }
                              }
    },
    { 515 , lang.finals+329 ,
                              {
                               { lang.elements+16 , lang.states+13 },
                               { lang.elements+48 , lang.states+53 }
                              }
    },
    { 516 , lang.finals+329 ,
                              {
                               { lang.elements+16 , lang.states+13 },
                               { lang.elements+48 , lang.states+57 }
                              }
    },
    { 517 , lang.finals+329 ,
                              {
                               { lang.elements+16 , lang.states+14 },
                               { lang.elements+48 , lang.states+50 }
                              }
    },
    { 518 , lang.finals+329 ,
                              {
                               { lang.elements+16 , lang.states+14 },
                               { lang.elements+48 , lang.states+54 }
                              }
    },
    { 519 , lang.finals+329 ,
                              {
                               { lang.elements+16 , lang.states+14 },
                               { lang.elements+48 , lang.states+58 }
                              }
    },
    { 520 , lang.finals+329 ,
                              {
                               { lang.elements+16 , lang.states+15 },
                               { lang.elements+48 , lang.states+51 }
                              }
    },
    { 521 , lang.finals+329 ,
                              {
                               { lang.elements+16 , lang.states+15 },
                               { lang.elements+48 , lang.states+55 }
                              }
    },
    { 522 , lang.finals+329 ,
                              {
                               { lang.elements+16 , lang.states+15 },
                               { lang.elements+48 , lang.states+59 }
                              }
    },
    { 523 , lang.finals+329 ,
                              {
                               { lang.elements+16 , lang.states+16 },
                               { lang.elements+48 , lang.states+52 }
                              }
    },
    { 524 , lang.finals+329 ,
                              {
                               { lang.elements+16 , lang.states+16 },
                               { lang.elements+48 , lang.states+56 }
                              }
    },
    { 525 , lang.finals+329 ,
                              {
                               { lang.elements+16 , lang.states+16 },
                               { lang.elements+48 , lang.states+60 }
                              }
    },
    { 526 , lang.finals+329 ,
                              {
                               { lang.elements+16 , lang.states+17 },
                               { lang.elements+48 , lang.states+123 }
                              }
    },
    { 527 , lang.finals+329 ,
                              {
                               { lang.elements+16 , lang.states+17 },
                               { lang.elements+48 , lang.states+125 }
                              }
    },
    { 528 , lang.finals+329 ,
                              {
                               { lang.elements+16 , lang.states+17 },
                               { lang.elements+48 , lang.states+127 }
                              }
    },
    { 529 , lang.finals+329 ,
                              {
                               { lang.elements+16 , lang.states+18 },
                               { lang.elements+48 , lang.states+124 }
                              }
    },
    { 530 , lang.finals+329 ,
                              {
                               { lang.elements+16 , lang.states+18 },
                               { lang.elements+48 , lang.states+126 }
                              }
    },
    { 531 , lang.finals+329 ,
                              {
                               { lang.elements+16 , lang.states+18 },
                               { lang.elements+48 , lang.states+128 }
                              }
    },
    { 532 , lang.finals+329 ,
                              {
                               { lang.elements+16 , lang.states+19 }
                              }
    },
    { 533 , lang.finals+329 ,
                              {
                               { lang.elements+16 , lang.states+20 }
                              }
    },
    { 534 , lang.finals+329 ,
                              {
                               { lang.elements+16 , lang.states+21 }
                              }
    },
    { 535 , lang.finals+329 ,
                              {
                               { lang.elements+16 , lang.states+22 }
                              }
    },
    { 536 , lang.finals+329 ,
                              {
                               { lang.elements+16 , lang.states+23 }
                              }
    },
    { 537 , lang.finals+329 ,
                              {
                               { lang.elements+16 , lang.states+24 }
                              }
    },
    { 538 , lang.finals+329 ,
                              {
                               { lang.elements+16 , lang.states+159 }
                              }
    },
    { 539 , lang.finals+329 ,
                              {
                               { lang.elements+16 , lang.states+160 }
                              }
    },
    { 540 , lang.finals+329 ,
                              {
                               { lang.elements+16 , lang.states+161 }
                              }
    },
    { 541 , lang.finals+329 ,
                              {
                               { lang.elements+16 , lang.states+162 }
                              }
    },
    { 542 , lang.finals+329 ,
                              {
                               { lang.elements+16 , lang.states+163 }
                              }
    },
    { 543 , lang.finals+329 ,
                              {
                               { lang.elements+16 , lang.states+164 }
                              }
    },
    { 544 , lang.finals+329 ,
                              {
                               { lang.elements+16 , lang.states+165 }
                              }
    },
    { 545 , lang.finals+329 ,
                              {
                               { lang.elements+16 , lang.states+166 }
                              }
    },
    { 546 , lang.finals+329 ,
                              {
                               { lang.elements+16 , lang.states+505 }
                              }
    },
    { 547 , lang.finals+329 ,
                              {
                               { lang.elements+16 , lang.states+509 }
                              }
    },
    { 548 , lang.finals+329 ,
                              {
                               { lang.elements+16 , lang.states+510 }
                              }
    },
    { 549 , lang.finals+329 ,
                              {
                               { lang.elements+16 , lang.states+511 }
                              }
    },
    { 550 , lang.finals+329 ,
                              {
                               { lang.elements+16 , lang.states+578 }
                              }
    },
    { 551 , lang.finals+329 ,
                              {
                               { lang.elements+16 , lang.states+579 }
                              }
    },
    { 552 , lang.finals+329 ,
                              {
                               { lang.elements+16 , lang.states+580 }
                              }
    },
    { 553 , lang.finals+329 ,
                              {
                               { lang.elements+16 , lang.states+581 }
                              }
    },
    { 554 , lang.finals+329 ,
                              {
                               { lang.elements+16 , lang.states+582 }
                              }
    },
    { 555 , lang.finals+330 ,
                              {
                               { lang.elements+17 , lang.states+263 }
                              }
    },
    { 556 , lang.finals+330 ,
                              {
                               { lang.elements+17 , lang.states+264 }
                              }
    },
    { 557 , lang.finals+330 ,
                              {
                               { lang.elements+17 , lang.states+265 }
                              }
    },
    { 558 , lang.finals+330 ,
                              {
                               { lang.elements+17 , lang.states+266 }
                              }
    },
    { 559 , lang.finals+330 ,
                              {
                               { lang.elements+17 , lang.states+483 }
                              }
    },
    { 560 , lang.finals+330 ,
                              {
                               { lang.elements+17 , lang.states+484 }
                              }
    },
    { 561 , lang.finals+330 ,
                              {
                               { lang.elements+17 , lang.states+485 }
                              }
    },
    { 562 , lang.finals+330 ,
                              {
                               { lang.elements+17 , lang.states+486 }
                              }
    },
    { 563 , lang.finals+330 ,
                              {
                               { lang.elements+17 , lang.states+487 }
                              }
    },
    { 564 , lang.finals+330 ,
                              {
                               { lang.elements+17 , lang.states+488 }
                              }
    },
    { 565 , lang.finals+330 ,
                              {
                               { lang.elements+17 , lang.states+489 }
                              }
    },
    { 566 , lang.finals+330 ,
                              {
                               { lang.elements+17 , lang.states+490 }
                              }
    },
    { 567 , lang.finals+331 ,
                              {
                               
                              }
    },
    { 568 , lang.finals+332 ,
                              {
                               
                              }
    },
    { 569 , lang.finals+333 ,
                              {
                               
                              }
    },
    { 570 , lang.finals+334 ,
                              {
                               
                              }
    },
    { 571 , lang.finals+335 ,
                              {
                               
                              }
    },
    { 572 , lang.finals+336 ,
                              {
                               { lang.elements+20 , lang.states+155 },
                               { lang.elements+41 , lang.states+494 }
                              }
    },
    { 573 , lang.finals+336 ,
                              {
                               { lang.elements+20 , lang.states+156 },
                               { lang.elements+41 , lang.states+494 }
                              }
    },
    { 574 , lang.finals+336 ,
                              {
                               { lang.elements+20 , lang.states+157 },
                               { lang.elements+41 , lang.states+494 }
                              }
    },
    { 575 , lang.finals+336 ,
                              {
                               { lang.elements+20 , lang.states+158 },
                               { lang.elements+41 , lang.states+494 }
                              }
    },
    { 576 , lang.finals+336 ,
                              {
                               { lang.elements+20 , lang.states+430 },
                               { lang.elements+41 , lang.states+494 }
                              }
    },
    { 577 , lang.finals+336 ,
                              {
                               { lang.elements+20 , lang.states+431 },
                               { lang.elements+41 , lang.states+494 }
                              }
    },
    { 578 , lang.finals+337 ,
                              {
                               { lang.elements+41 , lang.states+583 }
                              }
    },
    { 579 , lang.finals+337 ,
                              {
                               { lang.elements+41 , lang.states+1 }
                              }
    },
    { 580 , lang.finals+337 ,
                              {
                               { lang.elements+41 , lang.states+25 }
                              }
    },
    { 581 , lang.finals+337 ,
                              {
                               { lang.elements+41 , lang.states+26 }
                              }
    },
    { 582 , lang.finals+337 ,
                              {
                               { lang.elements+41 , lang.states+27 }
                              }
    },
    { 583 , lang.finals+0 ,
                            {
                             { lang.elements+43 , lang.states+132 }
                            }
    },
    { 584 , lang.finals+339 ,
                              {
                               
                              }
    },
    { 585 , lang.finals+340 ,
                              {
                               
                              }
    },
    { 586 , lang.finals+341 ,
                              {
                               
                              }
    },
    { 587 , lang.finals+342 ,
                              {
                               
                              }
    },
    { 588 , lang.finals+343 ,
                              {
                               
                              }
    },
    { 589 , lang.finals+344 ,
                              {
                               
                              }
    },
    { 590 , lang.finals+345 ,
                              {
                               
                              }
    },
    { 591 , lang.finals+346 ,
                              {
                               
                              }
    },
    { 592 , lang.finals+347 ,
                              {
                               
                              }
    },
    { 593 , lang.finals+348 ,
                              {
                               { lang.elements+0 , lang.states+529 },
                               { lang.elements+10 , lang.states+43 },
                               { lang.elements+14 , lang.states+44 },
                               { lang.elements+16 , lang.states+18 },
                               { lang.elements+22 , lang.states+513 },
                               { lang.elements+23 , lang.states+393 },
                               { lang.elements+24 , lang.states+421 },
                               { lang.elements+26 , lang.states+551 },
                               { lang.elements+27 , lang.states+395 },
                               { lang.elements+28 , lang.states+405 },
                               { lang.elements+29 , lang.states+409 },
                               { lang.elements+30 , lang.states+413 },
                               { lang.elements+31 , lang.states+401 },
                               { lang.elements+32 , lang.states+552 },
                               { lang.elements+33 , lang.states+419 },
                               { lang.elements+34 , lang.states+549 },
                               { lang.elements+35 , lang.states+397 },
                               { lang.elements+36 , lang.states+407 },
                               { lang.elements+37 , lang.states+411 },
                               { lang.elements+38 , lang.states+415 },
                               { lang.elements+39 , lang.states+403 },
                               { lang.elements+40 , lang.states+399 },
                               { lang.elements+44 , lang.states+584 },
                               { lang.elements+45 , lang.states+585 },
                               { lang.elements+46 , lang.states+586 },
                               { lang.elements+47 , lang.states+587 },
                               { lang.elements+48 , lang.states+122 },
                               { lang.elements+49 , lang.states+423 },
                               { lang.elements+50 , lang.states+417 },
                               { lang.elements+51 , lang.states+425 },
                               { lang.elements+52 , lang.states+446 },
                               { lang.elements+53 , lang.states+435 }
                              }
    }
   },
   {
    { 0 ,
          {
           { lang.atoms+0 , lang.rules+0 },
           { lang.atoms+10 , lang.rules+0 },
           { lang.atoms+14 , lang.rules+0 },
           { lang.atoms+16 , lang.rules+0 },
           { lang.atoms+22 , lang.rules+0 },
           { lang.atoms+23 , lang.rules+0 },
           { lang.atoms+24 , lang.rules+0 },
           { lang.atoms+26 , lang.rules+0 },
           { lang.atoms+27 , lang.rules+0 },
           { lang.atoms+28 , lang.rules+0 },
           { lang.atoms+29 , lang.rules+0 },
           { lang.atoms+30 , lang.rules+0 },
           { lang.atoms+31 , lang.rules+0 },
           { lang.atoms+32 , lang.rules+0 },
           { lang.atoms+33 , lang.rules+0 },
           { lang.atoms+34 , lang.rules+0 },
           { lang.atoms+35 , lang.rules+0 },
           { lang.atoms+36 , lang.rules+0 },
           { lang.atoms+37 , lang.rules+0 },
           { lang.atoms+38 , lang.rules+0 },
           { lang.atoms+39 , lang.rules+0 },
           { lang.atoms+40 , lang.rules+0 },
           { lang.atoms+42 , lang.rules+0 }
          }
    },
    { 1 ,
          {
           { lang.atoms+0 , lang.rules+1 },
           { lang.atoms+10 , lang.rules+1 },
           { lang.atoms+14 , lang.rules+1 },
           { lang.atoms+16 , lang.rules+1 },
           { lang.atoms+22 , lang.rules+1 },
           { lang.atoms+23 , lang.rules+1 },
           { lang.atoms+24 , lang.rules+1 },
           { lang.atoms+26 , lang.rules+1 },
           { lang.atoms+27 , lang.rules+1 },
           { lang.atoms+28 , lang.rules+1 },
           { lang.atoms+29 , lang.rules+1 },
           { lang.atoms+30 , lang.rules+1 },
           { lang.atoms+31 , lang.rules+1 },
           { lang.atoms+32 , lang.rules+1 },
           { lang.atoms+33 , lang.rules+1 },
           { lang.atoms+34 , lang.rules+1 },
           { lang.atoms+35 , lang.rules+1 },
           { lang.atoms+36 , lang.rules+1 },
           { lang.atoms+37 , lang.rules+1 },
           { lang.atoms+38 , lang.rules+1 },
           { lang.atoms+39 , lang.rules+1 },
           { lang.atoms+40 , lang.rules+1 },
           { lang.atoms+42 , lang.rules+1 }
          }
    },
    { 2 ,
          {
           { lang.atoms+0 , lang.rules+2 },
           { lang.atoms+10 , lang.rules+2 },
           { lang.atoms+14 , lang.rules+2 },
           { lang.atoms+16 , lang.rules+2 },
           { lang.atoms+22 , lang.rules+2 },
           { lang.atoms+23 , lang.rules+2 },
           { lang.atoms+24 , lang.rules+2 },
           { lang.atoms+26 , lang.rules+2 },
           { lang.atoms+27 , lang.rules+2 },
           { lang.atoms+28 , lang.rules+2 },
           { lang.atoms+29 , lang.rules+2 },
           { lang.atoms+30 , lang.rules+2 },
           { lang.atoms+31 , lang.rules+2 },
           { lang.atoms+32 , lang.rules+2 },
           { lang.atoms+33 , lang.rules+2 },
           { lang.atoms+34 , lang.rules+2 },
           { lang.atoms+35 , lang.rules+2 },
           { lang.atoms+36 , lang.rules+2 },
           { lang.atoms+37 , lang.rules+2 },
           { lang.atoms+38 , lang.rules+2 },
           { lang.atoms+39 , lang.rules+2 },
           { lang.atoms+40 , lang.rules+2 },
           { lang.atoms+42 , lang.rules+2 }
          }
    },
    { 3 ,
          {
           { lang.atoms+0 , lang.rules+3 },
           { lang.atoms+10 , lang.rules+3 },
           { lang.atoms+14 , lang.rules+3 },
           { lang.atoms+16 , lang.rules+3 },
           { lang.atoms+22 , lang.rules+3 },
           { lang.atoms+23 , lang.rules+3 },
           { lang.atoms+24 , lang.rules+3 },
           { lang.atoms+26 , lang.rules+3 },
           { lang.atoms+27 , lang.rules+3 },
           { lang.atoms+28 , lang.rules+3 },
           { lang.atoms+29 , lang.rules+3 },
           { lang.atoms+30 , lang.rules+3 },
           { lang.atoms+31 , lang.rules+3 },
           { lang.atoms+32 , lang.rules+3 },
           { lang.atoms+33 , lang.rules+3 },
           { lang.atoms+34 , lang.rules+3 },
           { lang.atoms+35 , lang.rules+3 },
           { lang.atoms+36 , lang.rules+3 },
           { lang.atoms+37 , lang.rules+3 },
           { lang.atoms+38 , lang.rules+3 },
           { lang.atoms+39 , lang.rules+3 },
           { lang.atoms+40 , lang.rules+3 },
           { lang.atoms+42 , lang.rules+3 }
          }
    },
    { 4 ,
          {
           { lang.atoms+0 , lang.rules+4 },
           { lang.atoms+10 , lang.rules+4 },
           { lang.atoms+14 , lang.rules+4 },
           { lang.atoms+16 , lang.rules+4 },
           { lang.atoms+22 , lang.rules+4 },
           { lang.atoms+23 , lang.rules+4 },
           { lang.atoms+24 , lang.rules+4 },
           { lang.atoms+26 , lang.rules+4 },
           { lang.atoms+27 , lang.rules+4 },
           { lang.atoms+28 , lang.rules+4 },
           { lang.atoms+29 , lang.rules+4 },
           { lang.atoms+30 , lang.rules+4 },
           { lang.atoms+31 , lang.rules+4 },
           { lang.atoms+32 , lang.rules+4 },
           { lang.atoms+33 , lang.rules+4 },
           { lang.atoms+34 , lang.rules+4 },
           { lang.atoms+35 , lang.rules+4 },
           { lang.atoms+36 , lang.rules+4 },
           { lang.atoms+37 , lang.rules+4 },
           { lang.atoms+38 , lang.rules+4 },
           { lang.atoms+39 , lang.rules+4 },
           { lang.atoms+40 , lang.rules+4 },
           { lang.atoms+42 , lang.rules+4 }
          }
    },
    { 5 ,
          {
           { lang.atoms+0 , lang.rules+5 },
           { lang.atoms+10 , lang.rules+5 },
           { lang.atoms+14 , lang.rules+5 },
           { lang.atoms+16 , lang.rules+5 },
           { lang.atoms+22 , lang.rules+5 },
           { lang.atoms+23 , lang.rules+5 },
           { lang.atoms+24 , lang.rules+5 },
           { lang.atoms+26 , lang.rules+5 },
           { lang.atoms+27 , lang.rules+5 },
           { lang.atoms+28 , lang.rules+5 },
           { lang.atoms+29 , lang.rules+5 },
           { lang.atoms+30 , lang.rules+5 },
           { lang.atoms+31 , lang.rules+5 },
           { lang.atoms+32 , lang.rules+5 },
           { lang.atoms+33 , lang.rules+5 },
           { lang.atoms+34 , lang.rules+5 },
           { lang.atoms+35 , lang.rules+5 },
           { lang.atoms+36 , lang.rules+5 },
           { lang.atoms+37 , lang.rules+5 },
           { lang.atoms+38 , lang.rules+5 },
           { lang.atoms+39 , lang.rules+5 },
           { lang.atoms+40 , lang.rules+5 },
           { lang.atoms+42 , lang.rules+5 }
          }
    },
    { 6 ,
          {
           { lang.atoms+0 , lang.rules+6 },
           { lang.atoms+10 , lang.rules+6 },
           { lang.atoms+14 , lang.rules+6 },
           { lang.atoms+16 , lang.rules+6 },
           { lang.atoms+22 , lang.rules+6 },
           { lang.atoms+23 , lang.rules+6 },
           { lang.atoms+24 , lang.rules+6 },
           { lang.atoms+26 , lang.rules+6 },
           { lang.atoms+27 , lang.rules+6 },
           { lang.atoms+28 , lang.rules+6 },
           { lang.atoms+29 , lang.rules+6 },
           { lang.atoms+30 , lang.rules+6 },
           { lang.atoms+31 , lang.rules+6 },
           { lang.atoms+32 , lang.rules+6 },
           { lang.atoms+33 , lang.rules+6 },
           { lang.atoms+34 , lang.rules+6 },
           { lang.atoms+35 , lang.rules+6 },
           { lang.atoms+36 , lang.rules+6 },
           { lang.atoms+37 , lang.rules+6 },
           { lang.atoms+38 , lang.rules+6 },
           { lang.atoms+39 , lang.rules+6 },
           { lang.atoms+40 , lang.rules+6 },
           { lang.atoms+42 , lang.rules+6 }
          }
    },
    { 7 ,
          {
           { lang.atoms+0 , lang.rules+7 },
           { lang.atoms+10 , lang.rules+7 },
           { lang.atoms+14 , lang.rules+7 },
           { lang.atoms+16 , lang.rules+7 },
           { lang.atoms+22 , lang.rules+7 },
           { lang.atoms+23 , lang.rules+7 },
           { lang.atoms+24 , lang.rules+7 },
           { lang.atoms+26 , lang.rules+7 },
           { lang.atoms+27 , lang.rules+7 },
           { lang.atoms+28 , lang.rules+7 },
           { lang.atoms+29 , lang.rules+7 },
           { lang.atoms+30 , lang.rules+7 },
           { lang.atoms+31 , lang.rules+7 },
           { lang.atoms+32 , lang.rules+7 },
           { lang.atoms+33 , lang.rules+7 },
           { lang.atoms+34 , lang.rules+7 },
           { lang.atoms+35 , lang.rules+7 },
           { lang.atoms+36 , lang.rules+7 },
           { lang.atoms+37 , lang.rules+7 },
           { lang.atoms+38 , lang.rules+7 },
           { lang.atoms+39 , lang.rules+7 },
           { lang.atoms+40 , lang.rules+7 },
           { lang.atoms+42 , lang.rules+7 }
          }
    },
    { 8 ,
          {
           { lang.atoms+0 , lang.rules+8 },
           { lang.atoms+10 , lang.rules+8 },
           { lang.atoms+14 , lang.rules+8 },
           { lang.atoms+16 , lang.rules+8 },
           { lang.atoms+21 , lang.rules+8 },
           { lang.atoms+23 , lang.rules+8 },
           { lang.atoms+24 , lang.rules+8 },
           { lang.atoms+27 , lang.rules+8 },
           { lang.atoms+28 , lang.rules+8 },
           { lang.atoms+29 , lang.rules+8 },
           { lang.atoms+30 , lang.rules+8 },
           { lang.atoms+31 , lang.rules+8 },
           { lang.atoms+32 , lang.rules+8 },
           { lang.atoms+33 , lang.rules+8 },
           { lang.atoms+34 , lang.rules+8 },
           { lang.atoms+35 , lang.rules+8 },
           { lang.atoms+36 , lang.rules+8 },
           { lang.atoms+37 , lang.rules+8 },
           { lang.atoms+38 , lang.rules+8 },
           { lang.atoms+39 , lang.rules+8 },
           { lang.atoms+40 , lang.rules+8 },
           { lang.atoms+42 , lang.rules+8 }
          }
    },
    { 9 ,
          {
           { lang.atoms+0 , lang.rules+8 },
           { lang.atoms+10 , lang.rules+8 },
           { lang.atoms+14 , lang.rules+8 },
           { lang.atoms+16 , lang.rules+8 },
           { lang.atoms+22 , lang.rules+8 },
           { lang.atoms+23 , lang.rules+8 },
           { lang.atoms+24 , lang.rules+8 },
           { lang.atoms+26 , lang.rules+8 },
           { lang.atoms+27 , lang.rules+8 },
           { lang.atoms+28 , lang.rules+8 },
           { lang.atoms+29 , lang.rules+8 },
           { lang.atoms+30 , lang.rules+8 },
           { lang.atoms+31 , lang.rules+8 },
           { lang.atoms+32 , lang.rules+8 },
           { lang.atoms+33 , lang.rules+8 },
           { lang.atoms+34 , lang.rules+8 },
           { lang.atoms+35 , lang.rules+8 },
           { lang.atoms+36 , lang.rules+8 },
           { lang.atoms+37 , lang.rules+8 },
           { lang.atoms+38 , lang.rules+8 },
           { lang.atoms+39 , lang.rules+8 },
           { lang.atoms+40 , lang.rules+8 },
           { lang.atoms+42 , lang.rules+8 }
          }
    },
    { 10 ,
           {
            { lang.atoms+0 , lang.rules+9 },
            { lang.atoms+10 , lang.rules+9 },
            { lang.atoms+14 , lang.rules+9 },
            { lang.atoms+16 , lang.rules+9 },
            { lang.atoms+21 , lang.rules+9 },
            { lang.atoms+23 , lang.rules+9 },
            { lang.atoms+24 , lang.rules+9 },
            { lang.atoms+27 , lang.rules+9 },
            { lang.atoms+28 , lang.rules+9 },
            { lang.atoms+29 , lang.rules+9 },
            { lang.atoms+30 , lang.rules+9 },
            { lang.atoms+31 , lang.rules+9 },
            { lang.atoms+32 , lang.rules+9 },
            { lang.atoms+33 , lang.rules+9 },
            { lang.atoms+34 , lang.rules+9 },
            { lang.atoms+35 , lang.rules+9 },
            { lang.atoms+36 , lang.rules+9 },
            { lang.atoms+37 , lang.rules+9 },
            { lang.atoms+38 , lang.rules+9 },
            { lang.atoms+39 , lang.rules+9 },
            { lang.atoms+40 , lang.rules+9 },
            { lang.atoms+42 , lang.rules+9 }
           }
    },
    { 11 ,
           {
            { lang.atoms+0 , lang.rules+9 },
            { lang.atoms+10 , lang.rules+9 },
            { lang.atoms+14 , lang.rules+9 },
            { lang.atoms+16 , lang.rules+9 },
            { lang.atoms+22 , lang.rules+9 },
            { lang.atoms+23 , lang.rules+9 },
            { lang.atoms+24 , lang.rules+9 },
            { lang.atoms+26 , lang.rules+9 },
            { lang.atoms+27 , lang.rules+9 },
            { lang.atoms+28 , lang.rules+9 },
            { lang.atoms+29 , lang.rules+9 },
            { lang.atoms+30 , lang.rules+9 },
            { lang.atoms+31 , lang.rules+9 },
            { lang.atoms+32 , lang.rules+9 },
            { lang.atoms+33 , lang.rules+9 },
            { lang.atoms+34 , lang.rules+9 },
            { lang.atoms+35 , lang.rules+9 },
            { lang.atoms+36 , lang.rules+9 },
            { lang.atoms+37 , lang.rules+9 },
            { lang.atoms+38 , lang.rules+9 },
            { lang.atoms+39 , lang.rules+9 },
            { lang.atoms+40 , lang.rules+9 },
            { lang.atoms+42 , lang.rules+9 }
           }
    },
    { 12 ,
           {
            { lang.atoms+0 , lang.rules+10 },
            { lang.atoms+1 , lang.rules+10 },
            { lang.atoms+3 , lang.rules+10 },
            { lang.atoms+4 , lang.rules+10 },
            { lang.atoms+5 , lang.rules+10 },
            { lang.atoms+6 , lang.rules+10 },
            { lang.atoms+8 , lang.rules+10 },
            { lang.atoms+9 , lang.rules+10 },
            { lang.atoms+10 , lang.rules+10 },
            { lang.atoms+11 , lang.rules+10 },
            { lang.atoms+19 , lang.rules+10 },
            { lang.atoms+41 , lang.rules+10 }
           }
    },
    { 13 ,
           {
            { lang.atoms+0 , lang.rules+10 },
            { lang.atoms+1 , lang.rules+10 },
            { lang.atoms+3 , lang.rules+10 },
            { lang.atoms+5 , lang.rules+10 },
            { lang.atoms+6 , lang.rules+10 },
            { lang.atoms+7 , lang.rules+10 },
            { lang.atoms+8 , lang.rules+10 },
            { lang.atoms+9 , lang.rules+10 },
            { lang.atoms+10 , lang.rules+10 },
            { lang.atoms+11 , lang.rules+10 },
            { lang.atoms+19 , lang.rules+10 },
            { lang.atoms+41 , lang.rules+10 },
            { lang.atoms+42 , lang.rules+10 }
           }
    },
    { 14 ,
           {
            { lang.atoms+0 , lang.rules+10 },
            { lang.atoms+1 , lang.rules+10 },
            { lang.atoms+3 , lang.rules+10 },
            { lang.atoms+5 , lang.rules+10 },
            { lang.atoms+6 , lang.rules+10 },
            { lang.atoms+8 , lang.rules+10 },
            { lang.atoms+9 , lang.rules+10 },
            { lang.atoms+10 , lang.rules+10 },
            { lang.atoms+11 , lang.rules+10 },
            { lang.atoms+12 , lang.rules+10 },
            { lang.atoms+19 , lang.rules+10 },
            { lang.atoms+41 , lang.rules+10 }
           }
    },
    { 15 ,
           {
            { lang.atoms+0 , lang.rules+10 },
            { lang.atoms+1 , lang.rules+10 },
            { lang.atoms+3 , lang.rules+10 },
            { lang.atoms+5 , lang.rules+10 },
            { lang.atoms+6 , lang.rules+10 },
            { lang.atoms+8 , lang.rules+10 },
            { lang.atoms+9 , lang.rules+10 },
            { lang.atoms+10 , lang.rules+10 },
            { lang.atoms+11 , lang.rules+10 },
            { lang.atoms+19 , lang.rules+10 },
            { lang.atoms+20 , lang.rules+10 },
            { lang.atoms+41 , lang.rules+10 }
           }
    },
    { 16 ,
           {
            { lang.atoms+0 , lang.rules+10 },
            { lang.atoms+5 , lang.rules+10 },
            { lang.atoms+12 , lang.rules+10 },
            { lang.atoms+19 , lang.rules+10 }
           }
    },
    { 17 ,
           {
            { lang.atoms+0 , lang.rules+10 },
            { lang.atoms+5 , lang.rules+10 },
            { lang.atoms+16 , lang.rules+10 },
            { lang.atoms+19 , lang.rules+10 }
           }
    },
    { 18 ,
           {
            { lang.atoms+0 , lang.rules+11 },
            { lang.atoms+1 , lang.rules+11 },
            { lang.atoms+3 , lang.rules+11 },
            { lang.atoms+4 , lang.rules+11 },
            { lang.atoms+5 , lang.rules+11 },
            { lang.atoms+6 , lang.rules+11 },
            { lang.atoms+8 , lang.rules+11 },
            { lang.atoms+9 , lang.rules+11 },
            { lang.atoms+10 , lang.rules+11 },
            { lang.atoms+11 , lang.rules+11 },
            { lang.atoms+19 , lang.rules+11 },
            { lang.atoms+41 , lang.rules+11 }
           }
    },
    { 19 ,
           {
            { lang.atoms+0 , lang.rules+11 },
            { lang.atoms+1 , lang.rules+11 },
            { lang.atoms+3 , lang.rules+11 },
            { lang.atoms+5 , lang.rules+11 },
            { lang.atoms+6 , lang.rules+11 },
            { lang.atoms+7 , lang.rules+11 },
            { lang.atoms+8 , lang.rules+11 },
            { lang.atoms+9 , lang.rules+11 },
            { lang.atoms+10 , lang.rules+11 },
            { lang.atoms+11 , lang.rules+11 },
            { lang.atoms+19 , lang.rules+11 },
            { lang.atoms+41 , lang.rules+11 },
            { lang.atoms+42 , lang.rules+11 }
           }
    },
    { 20 ,
           {
            { lang.atoms+0 , lang.rules+11 },
            { lang.atoms+1 , lang.rules+11 },
            { lang.atoms+3 , lang.rules+11 },
            { lang.atoms+5 , lang.rules+11 },
            { lang.atoms+6 , lang.rules+11 },
            { lang.atoms+8 , lang.rules+11 },
            { lang.atoms+9 , lang.rules+11 },
            { lang.atoms+10 , lang.rules+11 },
            { lang.atoms+11 , lang.rules+11 },
            { lang.atoms+12 , lang.rules+11 },
            { lang.atoms+19 , lang.rules+11 },
            { lang.atoms+41 , lang.rules+11 }
           }
    },
    { 21 ,
           {
            { lang.atoms+0 , lang.rules+11 },
            { lang.atoms+1 , lang.rules+11 },
            { lang.atoms+3 , lang.rules+11 },
            { lang.atoms+5 , lang.rules+11 },
            { lang.atoms+6 , lang.rules+11 },
            { lang.atoms+8 , lang.rules+11 },
            { lang.atoms+9 , lang.rules+11 },
            { lang.atoms+10 , lang.rules+11 },
            { lang.atoms+11 , lang.rules+11 },
            { lang.atoms+19 , lang.rules+11 },
            { lang.atoms+20 , lang.rules+11 },
            { lang.atoms+41 , lang.rules+11 }
           }
    },
    { 22 ,
           {
            { lang.atoms+0 , lang.rules+11 },
            { lang.atoms+5 , lang.rules+11 },
            { lang.atoms+12 , lang.rules+11 },
            { lang.atoms+19 , lang.rules+11 }
           }
    },
    { 23 ,
           {
            { lang.atoms+0 , lang.rules+11 },
            { lang.atoms+5 , lang.rules+11 },
            { lang.atoms+16 , lang.rules+11 },
            { lang.atoms+19 , lang.rules+11 }
           }
    },
    { 24 ,
           {
            { lang.atoms+0 , lang.rules+38 },
            { lang.atoms+10 , lang.rules+38 },
            { lang.atoms+14 , lang.rules+38 },
            { lang.atoms+16 , lang.rules+38 },
            { lang.atoms+21 , lang.rules+38 },
            { lang.atoms+23 , lang.rules+38 },
            { lang.atoms+24 , lang.rules+38 },
            { lang.atoms+27 , lang.rules+38 },
            { lang.atoms+28 , lang.rules+38 },
            { lang.atoms+29 , lang.rules+38 },
            { lang.atoms+30 , lang.rules+38 },
            { lang.atoms+31 , lang.rules+38 },
            { lang.atoms+32 , lang.rules+38 },
            { lang.atoms+33 , lang.rules+38 },
            { lang.atoms+34 , lang.rules+38 },
            { lang.atoms+35 , lang.rules+38 },
            { lang.atoms+36 , lang.rules+38 },
            { lang.atoms+37 , lang.rules+38 },
            { lang.atoms+38 , lang.rules+38 },
            { lang.atoms+39 , lang.rules+38 },
            { lang.atoms+40 , lang.rules+38 },
            { lang.atoms+42 , lang.rules+38 }
           }
    },
    { 25 ,
           {
            { lang.atoms+0 , lang.rules+39 },
            { lang.atoms+10 , lang.rules+39 },
            { lang.atoms+14 , lang.rules+39 },
            { lang.atoms+16 , lang.rules+39 },
            { lang.atoms+21 , lang.rules+39 },
            { lang.atoms+23 , lang.rules+39 },
            { lang.atoms+24 , lang.rules+39 },
            { lang.atoms+27 , lang.rules+39 },
            { lang.atoms+28 , lang.rules+39 },
            { lang.atoms+29 , lang.rules+39 },
            { lang.atoms+30 , lang.rules+39 },
            { lang.atoms+31 , lang.rules+39 },
            { lang.atoms+32 , lang.rules+39 },
            { lang.atoms+33 , lang.rules+39 },
            { lang.atoms+34 , lang.rules+39 },
            { lang.atoms+35 , lang.rules+39 },
            { lang.atoms+36 , lang.rules+39 },
            { lang.atoms+37 , lang.rules+39 },
            { lang.atoms+38 , lang.rules+39 },
            { lang.atoms+39 , lang.rules+39 },
            { lang.atoms+40 , lang.rules+39 },
            { lang.atoms+42 , lang.rules+39 }
           }
    },
    { 26 ,
           {
            { lang.atoms+0 , lang.rules+40 },
            { lang.atoms+10 , lang.rules+40 },
            { lang.atoms+14 , lang.rules+40 },
            { lang.atoms+16 , lang.rules+40 },
            { lang.atoms+21 , lang.rules+40 },
            { lang.atoms+23 , lang.rules+40 },
            { lang.atoms+24 , lang.rules+40 },
            { lang.atoms+27 , lang.rules+40 },
            { lang.atoms+28 , lang.rules+40 },
            { lang.atoms+29 , lang.rules+40 },
            { lang.atoms+30 , lang.rules+40 },
            { lang.atoms+31 , lang.rules+40 },
            { lang.atoms+32 , lang.rules+40 },
            { lang.atoms+33 , lang.rules+40 },
            { lang.atoms+34 , lang.rules+40 },
            { lang.atoms+35 , lang.rules+40 },
            { lang.atoms+36 , lang.rules+40 },
            { lang.atoms+37 , lang.rules+40 },
            { lang.atoms+38 , lang.rules+40 },
            { lang.atoms+39 , lang.rules+40 },
            { lang.atoms+40 , lang.rules+40 },
            { lang.atoms+42 , lang.rules+40 }
           }
    },
    { 27 ,
           {
            { lang.atoms+0 , lang.rules+41 },
            { lang.atoms+10 , lang.rules+41 },
            { lang.atoms+14 , lang.rules+41 },
            { lang.atoms+16 , lang.rules+41 },
            { lang.atoms+21 , lang.rules+41 },
            { lang.atoms+23 , lang.rules+41 },
            { lang.atoms+24 , lang.rules+41 },
            { lang.atoms+27 , lang.rules+41 },
            { lang.atoms+28 , lang.rules+41 },
            { lang.atoms+29 , lang.rules+41 },
            { lang.atoms+30 , lang.rules+41 },
            { lang.atoms+31 , lang.rules+41 },
            { lang.atoms+32 , lang.rules+41 },
            { lang.atoms+33 , lang.rules+41 },
            { lang.atoms+34 , lang.rules+41 },
            { lang.atoms+35 , lang.rules+41 },
            { lang.atoms+36 , lang.rules+41 },
            { lang.atoms+37 , lang.rules+41 },
            { lang.atoms+38 , lang.rules+41 },
            { lang.atoms+39 , lang.rules+41 },
            { lang.atoms+40 , lang.rules+41 },
            { lang.atoms+42 , lang.rules+41 }
           }
    },
    { 28 ,
           {
            { lang.atoms+0 , lang.rules+42 },
            { lang.atoms+10 , lang.rules+42 },
            { lang.atoms+14 , lang.rules+42 },
            { lang.atoms+16 , lang.rules+42 },
            { lang.atoms+21 , lang.rules+42 },
            { lang.atoms+23 , lang.rules+42 },
            { lang.atoms+24 , lang.rules+42 },
            { lang.atoms+27 , lang.rules+42 },
            { lang.atoms+28 , lang.rules+42 },
            { lang.atoms+29 , lang.rules+42 },
            { lang.atoms+30 , lang.rules+42 },
            { lang.atoms+31 , lang.rules+42 },
            { lang.atoms+32 , lang.rules+42 },
            { lang.atoms+33 , lang.rules+42 },
            { lang.atoms+34 , lang.rules+42 },
            { lang.atoms+35 , lang.rules+42 },
            { lang.atoms+36 , lang.rules+42 },
            { lang.atoms+37 , lang.rules+42 },
            { lang.atoms+38 , lang.rules+42 },
            { lang.atoms+39 , lang.rules+42 },
            { lang.atoms+40 , lang.rules+42 },
            { lang.atoms+42 , lang.rules+42 }
           }
    },
    { 29 ,
           {
            { lang.atoms+0 , lang.rules+43 },
            { lang.atoms+10 , lang.rules+43 },
            { lang.atoms+14 , lang.rules+43 },
            { lang.atoms+16 , lang.rules+43 },
            { lang.atoms+21 , lang.rules+43 },
            { lang.atoms+23 , lang.rules+43 },
            { lang.atoms+24 , lang.rules+43 },
            { lang.atoms+27 , lang.rules+43 },
            { lang.atoms+28 , lang.rules+43 },
            { lang.atoms+29 , lang.rules+43 },
            { lang.atoms+30 , lang.rules+43 },
            { lang.atoms+31 , lang.rules+43 },
            { lang.atoms+32 , lang.rules+43 },
            { lang.atoms+33 , lang.rules+43 },
            { lang.atoms+34 , lang.rules+43 },
            { lang.atoms+35 , lang.rules+43 },
            { lang.atoms+36 , lang.rules+43 },
            { lang.atoms+37 , lang.rules+43 },
            { lang.atoms+38 , lang.rules+43 },
            { lang.atoms+39 , lang.rules+43 },
            { lang.atoms+40 , lang.rules+43 },
            { lang.atoms+42 , lang.rules+43 }
           }
    },
    { 30 ,
           {
            { lang.atoms+0 , null }
           }
    },
    { 31 ,
           {
            { lang.atoms+0 , null },
            { lang.atoms+1 , lang.rules+12 },
            { lang.atoms+3 , lang.rules+12 },
            { lang.atoms+4 , lang.rules+12 },
            { lang.atoms+5 , lang.rules+12 },
            { lang.atoms+6 , lang.rules+12 },
            { lang.atoms+8 , lang.rules+12 },
            { lang.atoms+9 , lang.rules+12 },
            { lang.atoms+10 , lang.rules+12 },
            { lang.atoms+11 , lang.rules+12 },
            { lang.atoms+19 , lang.rules+12 },
            { lang.atoms+41 , lang.rules+12 }
           }
    },
    { 32 ,
           {
            { lang.atoms+0 , null },
            { lang.atoms+1 , lang.rules+12 },
            { lang.atoms+3 , lang.rules+12 },
            { lang.atoms+5 , lang.rules+12 },
            { lang.atoms+6 , lang.rules+12 },
            { lang.atoms+7 , lang.rules+12 },
            { lang.atoms+8 , lang.rules+12 },
            { lang.atoms+9 , lang.rules+12 },
            { lang.atoms+10 , lang.rules+12 },
            { lang.atoms+11 , lang.rules+12 },
            { lang.atoms+19 , lang.rules+12 },
            { lang.atoms+41 , lang.rules+12 },
            { lang.atoms+42 , lang.rules+12 }
           }
    },
    { 33 ,
           {
            { lang.atoms+0 , null },
            { lang.atoms+1 , lang.rules+12 },
            { lang.atoms+3 , lang.rules+12 },
            { lang.atoms+5 , lang.rules+12 },
            { lang.atoms+6 , lang.rules+12 },
            { lang.atoms+8 , lang.rules+12 },
            { lang.atoms+9 , lang.rules+12 },
            { lang.atoms+10 , lang.rules+12 },
            { lang.atoms+11 , lang.rules+12 },
            { lang.atoms+12 , lang.rules+12 },
            { lang.atoms+19 , lang.rules+12 },
            { lang.atoms+41 , lang.rules+12 }
           }
    },
    { 34 ,
           {
            { lang.atoms+0 , null },
            { lang.atoms+1 , lang.rules+12 },
            { lang.atoms+3 , lang.rules+12 },
            { lang.atoms+5 , lang.rules+12 },
            { lang.atoms+6 , lang.rules+12 },
            { lang.atoms+8 , lang.rules+12 },
            { lang.atoms+9 , lang.rules+12 },
            { lang.atoms+10 , lang.rules+12 },
            { lang.atoms+11 , lang.rules+12 },
            { lang.atoms+19 , lang.rules+12 },
            { lang.atoms+20 , lang.rules+12 },
            { lang.atoms+41 , lang.rules+12 }
           }
    },
    { 35 ,
           {
            { lang.atoms+0 , null },
            { lang.atoms+1 , lang.rules+13 },
            { lang.atoms+3 , lang.rules+13 },
            { lang.atoms+4 , lang.rules+13 },
            { lang.atoms+5 , lang.rules+13 },
            { lang.atoms+6 , lang.rules+13 },
            { lang.atoms+8 , lang.rules+13 },
            { lang.atoms+9 , lang.rules+13 },
            { lang.atoms+10 , lang.rules+13 },
            { lang.atoms+11 , lang.rules+13 },
            { lang.atoms+19 , lang.rules+13 },
            { lang.atoms+41 , lang.rules+13 }
           }
    },
    { 36 ,
           {
            { lang.atoms+0 , null },
            { lang.atoms+1 , lang.rules+13 },
            { lang.atoms+3 , lang.rules+13 },
            { lang.atoms+5 , lang.rules+13 },
            { lang.atoms+6 , lang.rules+13 },
            { lang.atoms+7 , lang.rules+13 },
            { lang.atoms+8 , lang.rules+13 },
            { lang.atoms+9 , lang.rules+13 },
            { lang.atoms+10 , lang.rules+13 },
            { lang.atoms+11 , lang.rules+13 },
            { lang.atoms+19 , lang.rules+13 },
            { lang.atoms+41 , lang.rules+13 },
            { lang.atoms+42 , lang.rules+13 }
           }
    },
    { 37 ,
           {
            { lang.atoms+0 , null },
            { lang.atoms+1 , lang.rules+13 },
            { lang.atoms+3 , lang.rules+13 },
            { lang.atoms+5 , lang.rules+13 },
            { lang.atoms+6 , lang.rules+13 },
            { lang.atoms+8 , lang.rules+13 },
            { lang.atoms+9 , lang.rules+13 },
            { lang.atoms+10 , lang.rules+13 },
            { lang.atoms+11 , lang.rules+13 },
            { lang.atoms+12 , lang.rules+13 },
            { lang.atoms+19 , lang.rules+13 },
            { lang.atoms+41 , lang.rules+13 }
           }
    },
    { 38 ,
           {
            { lang.atoms+0 , null },
            { lang.atoms+1 , lang.rules+13 },
            { lang.atoms+3 , lang.rules+13 },
            { lang.atoms+5 , lang.rules+13 },
            { lang.atoms+6 , lang.rules+13 },
            { lang.atoms+8 , lang.rules+13 },
            { lang.atoms+9 , lang.rules+13 },
            { lang.atoms+10 , lang.rules+13 },
            { lang.atoms+11 , lang.rules+13 },
            { lang.atoms+19 , lang.rules+13 },
            { lang.atoms+20 , lang.rules+13 },
            { lang.atoms+41 , lang.rules+13 }
           }
    },
    { 39 ,
           {
            { lang.atoms+0 , null },
            { lang.atoms+1 , lang.rules+14 },
            { lang.atoms+3 , lang.rules+14 },
            { lang.atoms+4 , lang.rules+14 },
            { lang.atoms+5 , lang.rules+14 },
            { lang.atoms+6 , lang.rules+14 },
            { lang.atoms+8 , lang.rules+14 },
            { lang.atoms+9 , lang.rules+14 },
            { lang.atoms+10 , lang.rules+14 },
            { lang.atoms+11 , lang.rules+14 },
            { lang.atoms+19 , lang.rules+14 },
            { lang.atoms+41 , lang.rules+14 }
           }
    },
    { 40 ,
           {
            { lang.atoms+0 , null },
            { lang.atoms+1 , lang.rules+14 },
            { lang.atoms+3 , lang.rules+14 },
            { lang.atoms+5 , lang.rules+14 },
            { lang.atoms+6 , lang.rules+14 },
            { lang.atoms+7 , lang.rules+14 },
            { lang.atoms+8 , lang.rules+14 },
            { lang.atoms+9 , lang.rules+14 },
            { lang.atoms+10 , lang.rules+14 },
            { lang.atoms+11 , lang.rules+14 },
            { lang.atoms+19 , lang.rules+14 },
            { lang.atoms+41 , lang.rules+14 },
            { lang.atoms+42 , lang.rules+14 }
           }
    },
    { 41 ,
           {
            { lang.atoms+0 , null },
            { lang.atoms+1 , lang.rules+14 },
            { lang.atoms+3 , lang.rules+14 },
            { lang.atoms+5 , lang.rules+14 },
            { lang.atoms+6 , lang.rules+14 },
            { lang.atoms+8 , lang.rules+14 },
            { lang.atoms+9 , lang.rules+14 },
            { lang.atoms+10 , lang.rules+14 },
            { lang.atoms+11 , lang.rules+14 },
            { lang.atoms+12 , lang.rules+14 },
            { lang.atoms+19 , lang.rules+14 },
            { lang.atoms+41 , lang.rules+14 }
           }
    },
    { 42 ,
           {
            { lang.atoms+0 , null },
            { lang.atoms+1 , lang.rules+14 },
            { lang.atoms+3 , lang.rules+14 },
            { lang.atoms+5 , lang.rules+14 },
            { lang.atoms+6 , lang.rules+14 },
            { lang.atoms+8 , lang.rules+14 },
            { lang.atoms+9 , lang.rules+14 },
            { lang.atoms+10 , lang.rules+14 },
            { lang.atoms+11 , lang.rules+14 },
            { lang.atoms+19 , lang.rules+14 },
            { lang.atoms+20 , lang.rules+14 },
            { lang.atoms+41 , lang.rules+14 }
           }
    },
    { 43 ,
           {
            { lang.atoms+0 , null },
            { lang.atoms+1 , lang.rules+15 },
            { lang.atoms+3 , lang.rules+15 },
            { lang.atoms+4 , lang.rules+15 },
            { lang.atoms+5 , lang.rules+15 },
            { lang.atoms+6 , lang.rules+15 },
            { lang.atoms+8 , lang.rules+15 },
            { lang.atoms+9 , lang.rules+15 },
            { lang.atoms+10 , lang.rules+15 },
            { lang.atoms+11 , lang.rules+15 },
            { lang.atoms+19 , lang.rules+15 },
            { lang.atoms+41 , lang.rules+15 }
           }
    },
    { 44 ,
           {
            { lang.atoms+0 , null },
            { lang.atoms+1 , lang.rules+15 },
            { lang.atoms+3 , lang.rules+15 },
            { lang.atoms+5 , lang.rules+15 },
            { lang.atoms+6 , lang.rules+15 },
            { lang.atoms+7 , lang.rules+15 },
            { lang.atoms+8 , lang.rules+15 },
            { lang.atoms+9 , lang.rules+15 },
            { lang.atoms+10 , lang.rules+15 },
            { lang.atoms+11 , lang.rules+15 },
            { lang.atoms+19 , lang.rules+15 },
            { lang.atoms+41 , lang.rules+15 },
            { lang.atoms+42 , lang.rules+15 }
           }
    },
    { 45 ,
           {
            { lang.atoms+0 , null },
            { lang.atoms+1 , lang.rules+15 },
            { lang.atoms+3 , lang.rules+15 },
            { lang.atoms+5 , lang.rules+15 },
            { lang.atoms+6 , lang.rules+15 },
            { lang.atoms+8 , lang.rules+15 },
            { lang.atoms+9 , lang.rules+15 },
            { lang.atoms+10 , lang.rules+15 },
            { lang.atoms+11 , lang.rules+15 },
            { lang.atoms+12 , lang.rules+15 },
            { lang.atoms+19 , lang.rules+15 },
            { lang.atoms+41 , lang.rules+15 }
           }
    },
    { 46 ,
           {
            { lang.atoms+0 , null },
            { lang.atoms+1 , lang.rules+15 },
            { lang.atoms+3 , lang.rules+15 },
            { lang.atoms+5 , lang.rules+15 },
            { lang.atoms+6 , lang.rules+15 },
            { lang.atoms+8 , lang.rules+15 },
            { lang.atoms+9 , lang.rules+15 },
            { lang.atoms+10 , lang.rules+15 },
            { lang.atoms+11 , lang.rules+15 },
            { lang.atoms+19 , lang.rules+15 },
            { lang.atoms+20 , lang.rules+15 },
            { lang.atoms+41 , lang.rules+15 }
           }
    },
    { 47 ,
           {
            { lang.atoms+0 , null },
            { lang.atoms+2 , null },
            { lang.atoms+3 , null },
            { lang.atoms+5 , null },
            { lang.atoms+6 , null },
            { lang.atoms+8 , null },
            { lang.atoms+10 , null },
            { lang.atoms+14 , null },
            { lang.atoms+16 , null },
            { lang.atoms+17 , null },
            { lang.atoms+18 , null },
            { lang.atoms+20 , null },
            { lang.atoms+23 , null },
            { lang.atoms+25 , null },
            { lang.atoms+27 , null },
            { lang.atoms+28 , null },
            { lang.atoms+29 , null },
            { lang.atoms+30 , null },
            { lang.atoms+31 , null },
            { lang.atoms+35 , null },
            { lang.atoms+36 , null },
            { lang.atoms+37 , null },
            { lang.atoms+38 , null },
            { lang.atoms+39 , null },
            { lang.atoms+40 , null },
            { lang.atoms+41 , null }
           }
    },
    { 48 ,
           {
            { lang.atoms+0 , null },
            { lang.atoms+2 , null },
            { lang.atoms+3 , null },
            { lang.atoms+5 , null },
            { lang.atoms+6 , null },
            { lang.atoms+8 , null },
            { lang.atoms+10 , null },
            { lang.atoms+14 , null },
            { lang.atoms+16 , null },
            { lang.atoms+17 , null },
            { lang.atoms+18 , null },
            { lang.atoms+23 , null },
            { lang.atoms+25 , null },
            { lang.atoms+27 , null },
            { lang.atoms+28 , null },
            { lang.atoms+29 , null },
            { lang.atoms+30 , null },
            { lang.atoms+31 , null },
            { lang.atoms+35 , null },
            { lang.atoms+36 , null },
            { lang.atoms+37 , null },
            { lang.atoms+38 , null },
            { lang.atoms+39 , null },
            { lang.atoms+40 , null }
           }
    },
    { 49 ,
           {
            { lang.atoms+0 , null },
            { lang.atoms+2 , null },
            { lang.atoms+3 , null },
            { lang.atoms+5 , null },
            { lang.atoms+6 , null },
            { lang.atoms+8 , null },
            { lang.atoms+10 , null },
            { lang.atoms+14 , null },
            { lang.atoms+16 , null },
            { lang.atoms+17 , null },
            { lang.atoms+18 , null },
            { lang.atoms+23 , null },
            { lang.atoms+25 , null },
            { lang.atoms+27 , null },
            { lang.atoms+28 , null },
            { lang.atoms+29 , null },
            { lang.atoms+30 , null },
            { lang.atoms+31 , null },
            { lang.atoms+35 , null },
            { lang.atoms+36 , null },
            { lang.atoms+37 , null },
            { lang.atoms+38 , null },
            { lang.atoms+39 , null },
            { lang.atoms+40 , null },
            { lang.atoms+41 , null }
           }
    },
    { 50 ,
           {
            { lang.atoms+0 , null },
            { lang.atoms+2 , null },
            { lang.atoms+3 , null },
            { lang.atoms+5 , null },
            { lang.atoms+6 , null },
            { lang.atoms+8 , null },
            { lang.atoms+10 , null },
            { lang.atoms+14 , null },
            { lang.atoms+16 , null },
            { lang.atoms+17 , null },
            { lang.atoms+18 , null },
            { lang.atoms+23 , null },
            { lang.atoms+25 , null },
            { lang.atoms+27 , null },
            { lang.atoms+28 , null },
            { lang.atoms+29 , null },
            { lang.atoms+30 , null },
            { lang.atoms+31 , null },
            { lang.atoms+35 , null },
            { lang.atoms+36 , null },
            { lang.atoms+37 , null },
            { lang.atoms+38 , null },
            { lang.atoms+39 , null },
            { lang.atoms+40 , null },
            { lang.atoms+41 , null },
            { lang.atoms+42 , null }
           }
    },
    { 51 ,
           {
            { lang.atoms+0 , null },
            { lang.atoms+5 , lang.rules+12 },
            { lang.atoms+12 , lang.rules+12 },
            { lang.atoms+19 , lang.rules+12 }
           }
    },
    { 52 ,
           {
            { lang.atoms+0 , null },
            { lang.atoms+5 , lang.rules+12 },
            { lang.atoms+16 , lang.rules+12 },
            { lang.atoms+19 , lang.rules+12 }
           }
    },
    { 53 ,
           {
            { lang.atoms+0 , null },
            { lang.atoms+5 , lang.rules+13 },
            { lang.atoms+12 , lang.rules+13 },
            { lang.atoms+19 , lang.rules+13 }
           }
    },
    { 54 ,
           {
            { lang.atoms+0 , null },
            { lang.atoms+5 , lang.rules+13 },
            { lang.atoms+16 , lang.rules+13 },
            { lang.atoms+19 , lang.rules+13 }
           }
    },
    { 55 ,
           {
            { lang.atoms+0 , null },
            { lang.atoms+5 , lang.rules+14 },
            { lang.atoms+12 , lang.rules+14 },
            { lang.atoms+19 , lang.rules+14 }
           }
    },
    { 56 ,
           {
            { lang.atoms+0 , null },
            { lang.atoms+5 , lang.rules+14 },
            { lang.atoms+16 , lang.rules+14 },
            { lang.atoms+19 , lang.rules+14 }
           }
    },
    { 57 ,
           {
            { lang.atoms+0 , null },
            { lang.atoms+5 , lang.rules+15 },
            { lang.atoms+12 , lang.rules+15 },
            { lang.atoms+19 , lang.rules+15 }
           }
    },
    { 58 ,
           {
            { lang.atoms+0 , null },
            { lang.atoms+5 , lang.rules+15 },
            { lang.atoms+16 , lang.rules+15 },
            { lang.atoms+19 , lang.rules+15 }
           }
    },
    { 59 ,
           {
            { lang.atoms+0 , null },
            { lang.atoms+10 , null },
            { lang.atoms+14 , null },
            { lang.atoms+16 , null },
            { lang.atoms+21 , null },
            { lang.atoms+23 , null },
            { lang.atoms+24 , null },
            { lang.atoms+27 , null },
            { lang.atoms+28 , null },
            { lang.atoms+29 , null },
            { lang.atoms+30 , null },
            { lang.atoms+31 , null },
            { lang.atoms+32 , null },
            { lang.atoms+33 , null },
            { lang.atoms+34 , null },
            { lang.atoms+35 , null },
            { lang.atoms+36 , null },
            { lang.atoms+37 , null },
            { lang.atoms+38 , null },
            { lang.atoms+39 , null },
            { lang.atoms+40 , null },
            { lang.atoms+42 , null }
           }
    },
    { 60 ,
           {
            { lang.atoms+0 , null },
            { lang.atoms+10 , null },
            { lang.atoms+14 , null },
            { lang.atoms+16 , null },
            { lang.atoms+22 , null },
            { lang.atoms+23 , null },
            { lang.atoms+24 , null },
            { lang.atoms+26 , null },
            { lang.atoms+27 , null },
            { lang.atoms+28 , null },
            { lang.atoms+29 , null },
            { lang.atoms+30 , null },
            { lang.atoms+31 , null },
            { lang.atoms+32 , null },
            { lang.atoms+33 , null },
            { lang.atoms+34 , null },
            { lang.atoms+35 , null },
            { lang.atoms+36 , null },
            { lang.atoms+37 , null },
            { lang.atoms+38 , null },
            { lang.atoms+39 , null },
            { lang.atoms+40 , null },
            { lang.atoms+42 , null }
           }
    },
    { 61 ,
           {
            { lang.atoms+0 , null },
            { lang.atoms+10 , null },
            { lang.atoms+14 , null },
            { lang.atoms+16 , null },
            { lang.atoms+23 , null },
            { lang.atoms+24 , null },
            { lang.atoms+27 , null },
            { lang.atoms+28 , null },
            { lang.atoms+29 , null },
            { lang.atoms+30 , null },
            { lang.atoms+31 , null },
            { lang.atoms+32 , null },
            { lang.atoms+33 , null },
            { lang.atoms+35 , null },
            { lang.atoms+36 , null },
            { lang.atoms+37 , null },
            { lang.atoms+38 , null },
            { lang.atoms+39 , null },
            { lang.atoms+40 , null }
           }
    },
    { 62 ,
           {
            { lang.atoms+0 , null },
            { lang.atoms+16 , null }
           }
    },
    { 63 ,
           {
            { lang.atoms+1 , lang.rules+44 },
            { lang.atoms+4 , lang.rules+44 },
            { lang.atoms+5 , lang.rules+44 },
            { lang.atoms+6 , lang.rules+44 },
            { lang.atoms+8 , lang.rules+44 },
            { lang.atoms+9 , lang.rules+44 },
            { lang.atoms+10 , lang.rules+44 },
            { lang.atoms+11 , lang.rules+44 },
            { lang.atoms+19 , lang.rules+44 },
            { lang.atoms+41 , lang.rules+44 }
           }
    },
    { 64 ,
           {
            { lang.atoms+1 , lang.rules+44 },
            { lang.atoms+5 , lang.rules+44 },
            { lang.atoms+6 , lang.rules+44 },
            { lang.atoms+7 , lang.rules+44 },
            { lang.atoms+8 , lang.rules+44 },
            { lang.atoms+9 , lang.rules+44 },
            { lang.atoms+10 , lang.rules+44 },
            { lang.atoms+11 , lang.rules+44 },
            { lang.atoms+19 , lang.rules+44 },
            { lang.atoms+41 , lang.rules+44 },
            { lang.atoms+42 , lang.rules+44 }
           }
    },
    { 65 ,
           {
            { lang.atoms+1 , lang.rules+44 },
            { lang.atoms+5 , lang.rules+44 },
            { lang.atoms+6 , lang.rules+44 },
            { lang.atoms+8 , lang.rules+44 },
            { lang.atoms+9 , lang.rules+44 },
            { lang.atoms+10 , lang.rules+44 },
            { lang.atoms+11 , lang.rules+44 },
            { lang.atoms+12 , lang.rules+44 },
            { lang.atoms+19 , lang.rules+44 },
            { lang.atoms+41 , lang.rules+44 }
           }
    },
    { 66 ,
           {
            { lang.atoms+1 , lang.rules+44 },
            { lang.atoms+5 , lang.rules+44 },
            { lang.atoms+6 , lang.rules+44 },
            { lang.atoms+8 , lang.rules+44 },
            { lang.atoms+9 , lang.rules+44 },
            { lang.atoms+10 , lang.rules+44 },
            { lang.atoms+11 , lang.rules+44 },
            { lang.atoms+19 , lang.rules+44 },
            { lang.atoms+20 , lang.rules+44 },
            { lang.atoms+41 , lang.rules+44 }
           }
    },
    { 67 ,
           {
            { lang.atoms+1 , lang.rules+45 },
            { lang.atoms+3 , lang.rules+71 },
            { lang.atoms+4 , lang.rules+45 },
            { lang.atoms+5 , lang.rules+45 },
            { lang.atoms+6 , lang.rules+45 },
            { lang.atoms+8 , lang.rules+45 },
            { lang.atoms+9 , lang.rules+45 },
            { lang.atoms+10 , lang.rules+45 },
            { lang.atoms+11 , lang.rules+45 },
            { lang.atoms+19 , lang.rules+45 },
            { lang.atoms+41 , lang.rules+45 }
           }
    },
    { 68 ,
           {
            { lang.atoms+1 , lang.rules+45 },
            { lang.atoms+3 , lang.rules+71 },
            { lang.atoms+5 , lang.rules+45 },
            { lang.atoms+6 , lang.rules+45 },
            { lang.atoms+7 , lang.rules+45 },
            { lang.atoms+8 , lang.rules+45 },
            { lang.atoms+9 , lang.rules+45 },
            { lang.atoms+10 , lang.rules+45 },
            { lang.atoms+11 , lang.rules+45 },
            { lang.atoms+19 , lang.rules+45 },
            { lang.atoms+41 , lang.rules+45 },
            { lang.atoms+42 , lang.rules+45 }
           }
    },
    { 69 ,
           {
            { lang.atoms+1 , lang.rules+45 },
            { lang.atoms+3 , lang.rules+71 },
            { lang.atoms+5 , lang.rules+45 },
            { lang.atoms+6 , lang.rules+45 },
            { lang.atoms+8 , lang.rules+45 },
            { lang.atoms+9 , lang.rules+45 },
            { lang.atoms+10 , lang.rules+45 },
            { lang.atoms+11 , lang.rules+45 },
            { lang.atoms+12 , lang.rules+45 },
            { lang.atoms+19 , lang.rules+45 },
            { lang.atoms+41 , lang.rules+45 }
           }
    },
    { 70 ,
           {
            { lang.atoms+1 , lang.rules+45 },
            { lang.atoms+3 , lang.rules+71 },
            { lang.atoms+5 , lang.rules+45 },
            { lang.atoms+6 , lang.rules+45 },
            { lang.atoms+8 , lang.rules+45 },
            { lang.atoms+9 , lang.rules+45 },
            { lang.atoms+10 , lang.rules+45 },
            { lang.atoms+11 , lang.rules+45 },
            { lang.atoms+19 , lang.rules+45 },
            { lang.atoms+20 , lang.rules+45 },
            { lang.atoms+41 , lang.rules+45 }
           }
    },
    { 71 ,
           {
            { lang.atoms+1 , lang.rules+46 },
            { lang.atoms+4 , lang.rules+46 },
            { lang.atoms+5 , lang.rules+46 },
            { lang.atoms+6 , lang.rules+46 },
            { lang.atoms+8 , lang.rules+46 },
            { lang.atoms+9 , lang.rules+46 },
            { lang.atoms+10 , lang.rules+46 },
            { lang.atoms+11 , lang.rules+46 },
            { lang.atoms+19 , lang.rules+46 },
            { lang.atoms+41 , lang.rules+46 }
           }
    },
    { 72 ,
           {
            { lang.atoms+1 , lang.rules+46 },
            { lang.atoms+5 , lang.rules+46 },
            { lang.atoms+6 , lang.rules+46 },
            { lang.atoms+7 , lang.rules+46 },
            { lang.atoms+8 , lang.rules+46 },
            { lang.atoms+9 , lang.rules+46 },
            { lang.atoms+10 , lang.rules+46 },
            { lang.atoms+11 , lang.rules+46 },
            { lang.atoms+19 , lang.rules+46 },
            { lang.atoms+41 , lang.rules+46 },
            { lang.atoms+42 , lang.rules+46 }
           }
    },
    { 73 ,
           {
            { lang.atoms+1 , lang.rules+46 },
            { lang.atoms+5 , lang.rules+46 },
            { lang.atoms+6 , lang.rules+46 },
            { lang.atoms+8 , lang.rules+46 },
            { lang.atoms+9 , lang.rules+46 },
            { lang.atoms+10 , lang.rules+46 },
            { lang.atoms+11 , lang.rules+46 },
            { lang.atoms+12 , lang.rules+46 },
            { lang.atoms+19 , lang.rules+46 },
            { lang.atoms+41 , lang.rules+46 }
           }
    },
    { 74 ,
           {
            { lang.atoms+1 , lang.rules+46 },
            { lang.atoms+5 , lang.rules+46 },
            { lang.atoms+6 , lang.rules+46 },
            { lang.atoms+8 , lang.rules+46 },
            { lang.atoms+9 , lang.rules+46 },
            { lang.atoms+10 , lang.rules+46 },
            { lang.atoms+11 , lang.rules+46 },
            { lang.atoms+19 , lang.rules+46 },
            { lang.atoms+20 , lang.rules+46 },
            { lang.atoms+41 , lang.rules+46 }
           }
    },
    { 75 ,
           {
            { lang.atoms+1 , lang.rules+47 },
            { lang.atoms+4 , lang.rules+47 },
            { lang.atoms+5 , lang.rules+47 },
            { lang.atoms+6 , lang.rules+47 },
            { lang.atoms+8 , lang.rules+47 },
            { lang.atoms+9 , lang.rules+47 },
            { lang.atoms+10 , lang.rules+47 },
            { lang.atoms+11 , lang.rules+47 },
            { lang.atoms+19 , lang.rules+47 },
            { lang.atoms+41 , lang.rules+47 }
           }
    },
    { 76 ,
           {
            { lang.atoms+1 , lang.rules+47 },
            { lang.atoms+5 , lang.rules+47 },
            { lang.atoms+6 , lang.rules+47 },
            { lang.atoms+7 , lang.rules+47 },
            { lang.atoms+8 , lang.rules+47 },
            { lang.atoms+9 , lang.rules+47 },
            { lang.atoms+10 , lang.rules+47 },
            { lang.atoms+11 , lang.rules+47 },
            { lang.atoms+19 , lang.rules+47 },
            { lang.atoms+41 , lang.rules+47 },
            { lang.atoms+42 , lang.rules+47 }
           }
    },
    { 77 ,
           {
            { lang.atoms+1 , lang.rules+47 },
            { lang.atoms+5 , lang.rules+47 },
            { lang.atoms+6 , lang.rules+47 },
            { lang.atoms+8 , lang.rules+47 },
            { lang.atoms+9 , lang.rules+47 },
            { lang.atoms+10 , lang.rules+47 },
            { lang.atoms+11 , lang.rules+47 },
            { lang.atoms+12 , lang.rules+47 },
            { lang.atoms+19 , lang.rules+47 },
            { lang.atoms+41 , lang.rules+47 }
           }
    },
    { 78 ,
           {
            { lang.atoms+1 , lang.rules+47 },
            { lang.atoms+5 , lang.rules+47 },
            { lang.atoms+6 , lang.rules+47 },
            { lang.atoms+8 , lang.rules+47 },
            { lang.atoms+9 , lang.rules+47 },
            { lang.atoms+10 , lang.rules+47 },
            { lang.atoms+11 , lang.rules+47 },
            { lang.atoms+19 , lang.rules+47 },
            { lang.atoms+20 , lang.rules+47 },
            { lang.atoms+41 , lang.rules+47 }
           }
    },
    { 79 ,
           {
            { lang.atoms+1 , lang.rules+48 },
            { lang.atoms+4 , lang.rules+48 },
            { lang.atoms+5 , lang.rules+48 },
            { lang.atoms+6 , lang.rules+48 },
            { lang.atoms+8 , lang.rules+48 },
            { lang.atoms+9 , lang.rules+48 },
            { lang.atoms+10 , lang.rules+48 },
            { lang.atoms+11 , lang.rules+48 },
            { lang.atoms+19 , lang.rules+48 },
            { lang.atoms+41 , lang.rules+48 }
           }
    },
    { 80 ,
           {
            { lang.atoms+1 , lang.rules+48 },
            { lang.atoms+5 , lang.rules+48 },
            { lang.atoms+6 , lang.rules+48 },
            { lang.atoms+7 , lang.rules+48 },
            { lang.atoms+8 , lang.rules+48 },
            { lang.atoms+9 , lang.rules+48 },
            { lang.atoms+10 , lang.rules+48 },
            { lang.atoms+11 , lang.rules+48 },
            { lang.atoms+19 , lang.rules+48 },
            { lang.atoms+41 , lang.rules+48 },
            { lang.atoms+42 , lang.rules+48 }
           }
    },
    { 81 ,
           {
            { lang.atoms+1 , lang.rules+48 },
            { lang.atoms+5 , lang.rules+48 },
            { lang.atoms+6 , lang.rules+48 },
            { lang.atoms+8 , lang.rules+48 },
            { lang.atoms+9 , lang.rules+48 },
            { lang.atoms+10 , lang.rules+48 },
            { lang.atoms+11 , lang.rules+48 },
            { lang.atoms+12 , lang.rules+48 },
            { lang.atoms+19 , lang.rules+48 },
            { lang.atoms+41 , lang.rules+48 }
           }
    },
    { 82 ,
           {
            { lang.atoms+1 , lang.rules+48 },
            { lang.atoms+5 , lang.rules+48 },
            { lang.atoms+6 , lang.rules+48 },
            { lang.atoms+8 , lang.rules+48 },
            { lang.atoms+9 , lang.rules+48 },
            { lang.atoms+10 , lang.rules+48 },
            { lang.atoms+11 , lang.rules+48 },
            { lang.atoms+19 , lang.rules+48 },
            { lang.atoms+20 , lang.rules+48 },
            { lang.atoms+41 , lang.rules+48 }
           }
    },
    { 83 ,
           {
            { lang.atoms+1 , lang.rules+49 },
            { lang.atoms+4 , lang.rules+49 },
            { lang.atoms+5 , lang.rules+49 },
            { lang.atoms+6 , lang.rules+49 },
            { lang.atoms+8 , lang.rules+49 },
            { lang.atoms+9 , lang.rules+49 },
            { lang.atoms+10 , lang.rules+49 },
            { lang.atoms+11 , lang.rules+49 },
            { lang.atoms+19 , lang.rules+49 },
            { lang.atoms+41 , lang.rules+49 }
           }
    },
    { 84 ,
           {
            { lang.atoms+1 , lang.rules+49 },
            { lang.atoms+5 , lang.rules+49 },
            { lang.atoms+6 , lang.rules+49 },
            { lang.atoms+7 , lang.rules+49 },
            { lang.atoms+8 , lang.rules+49 },
            { lang.atoms+9 , lang.rules+49 },
            { lang.atoms+10 , lang.rules+49 },
            { lang.atoms+11 , lang.rules+49 },
            { lang.atoms+19 , lang.rules+49 },
            { lang.atoms+41 , lang.rules+49 },
            { lang.atoms+42 , lang.rules+49 }
           }
    },
    { 85 ,
           {
            { lang.atoms+1 , lang.rules+49 },
            { lang.atoms+5 , lang.rules+49 },
            { lang.atoms+6 , lang.rules+49 },
            { lang.atoms+8 , lang.rules+49 },
            { lang.atoms+9 , lang.rules+49 },
            { lang.atoms+10 , lang.rules+49 },
            { lang.atoms+11 , lang.rules+49 },
            { lang.atoms+12 , lang.rules+49 },
            { lang.atoms+19 , lang.rules+49 },
            { lang.atoms+41 , lang.rules+49 }
           }
    },
    { 86 ,
           {
            { lang.atoms+1 , lang.rules+49 },
            { lang.atoms+5 , lang.rules+49 },
            { lang.atoms+6 , lang.rules+49 },
            { lang.atoms+8 , lang.rules+49 },
            { lang.atoms+9 , lang.rules+49 },
            { lang.atoms+10 , lang.rules+49 },
            { lang.atoms+11 , lang.rules+49 },
            { lang.atoms+19 , lang.rules+49 },
            { lang.atoms+20 , lang.rules+49 },
            { lang.atoms+41 , lang.rules+49 }
           }
    },
    { 87 ,
           {
            { lang.atoms+1 , lang.rules+50 },
            { lang.atoms+4 , lang.rules+50 },
            { lang.atoms+5 , lang.rules+50 },
            { lang.atoms+6 , lang.rules+50 },
            { lang.atoms+8 , lang.rules+50 },
            { lang.atoms+9 , lang.rules+50 },
            { lang.atoms+10 , lang.rules+50 },
            { lang.atoms+11 , lang.rules+50 },
            { lang.atoms+19 , lang.rules+50 },
            { lang.atoms+41 , lang.rules+50 }
           }
    },
    { 88 ,
           {
            { lang.atoms+1 , lang.rules+50 },
            { lang.atoms+5 , lang.rules+50 },
            { lang.atoms+6 , lang.rules+50 },
            { lang.atoms+7 , lang.rules+50 },
            { lang.atoms+8 , lang.rules+50 },
            { lang.atoms+9 , lang.rules+50 },
            { lang.atoms+10 , lang.rules+50 },
            { lang.atoms+11 , lang.rules+50 },
            { lang.atoms+19 , lang.rules+50 },
            { lang.atoms+41 , lang.rules+50 },
            { lang.atoms+42 , lang.rules+50 }
           }
    },
    { 89 ,
           {
            { lang.atoms+1 , lang.rules+50 },
            { lang.atoms+5 , lang.rules+50 },
            { lang.atoms+6 , lang.rules+50 },
            { lang.atoms+8 , lang.rules+50 },
            { lang.atoms+9 , lang.rules+50 },
            { lang.atoms+10 , lang.rules+50 },
            { lang.atoms+11 , lang.rules+50 },
            { lang.atoms+12 , lang.rules+50 },
            { lang.atoms+19 , lang.rules+50 },
            { lang.atoms+41 , lang.rules+50 }
           }
    },
    { 90 ,
           {
            { lang.atoms+1 , lang.rules+50 },
            { lang.atoms+5 , lang.rules+50 },
            { lang.atoms+6 , lang.rules+50 },
            { lang.atoms+8 , lang.rules+50 },
            { lang.atoms+9 , lang.rules+50 },
            { lang.atoms+10 , lang.rules+50 },
            { lang.atoms+11 , lang.rules+50 },
            { lang.atoms+19 , lang.rules+50 },
            { lang.atoms+20 , lang.rules+50 },
            { lang.atoms+41 , lang.rules+50 }
           }
    },
    { 91 ,
           {
            { lang.atoms+1 , lang.rules+51 },
            { lang.atoms+4 , lang.rules+51 },
            { lang.atoms+5 , lang.rules+51 },
            { lang.atoms+6 , lang.rules+51 },
            { lang.atoms+8 , lang.rules+51 },
            { lang.atoms+10 , null },
            { lang.atoms+11 , lang.rules+51 },
            { lang.atoms+19 , lang.rules+51 },
            { lang.atoms+41 , lang.rules+51 }
           }
    },
    { 92 ,
           {
            { lang.atoms+1 , lang.rules+51 },
            { lang.atoms+5 , lang.rules+51 },
            { lang.atoms+6 , lang.rules+51 },
            { lang.atoms+7 , lang.rules+51 },
            { lang.atoms+8 , lang.rules+51 },
            { lang.atoms+10 , null },
            { lang.atoms+11 , lang.rules+51 },
            { lang.atoms+19 , lang.rules+51 },
            { lang.atoms+41 , lang.rules+51 },
            { lang.atoms+42 , lang.rules+51 }
           }
    },
    { 93 ,
           {
            { lang.atoms+1 , lang.rules+51 },
            { lang.atoms+5 , lang.rules+51 },
            { lang.atoms+6 , lang.rules+51 },
            { lang.atoms+8 , lang.rules+51 },
            { lang.atoms+10 , null },
            { lang.atoms+11 , lang.rules+51 },
            { lang.atoms+12 , lang.rules+51 },
            { lang.atoms+19 , lang.rules+51 },
            { lang.atoms+41 , lang.rules+51 }
           }
    },
    { 94 ,
           {
            { lang.atoms+1 , lang.rules+51 },
            { lang.atoms+5 , lang.rules+51 },
            { lang.atoms+6 , lang.rules+51 },
            { lang.atoms+8 , lang.rules+51 },
            { lang.atoms+10 , null },
            { lang.atoms+11 , lang.rules+51 },
            { lang.atoms+19 , lang.rules+51 },
            { lang.atoms+20 , lang.rules+51 },
            { lang.atoms+41 , lang.rules+51 }
           }
    },
    { 95 ,
           {
            { lang.atoms+1 , lang.rules+52 },
            { lang.atoms+4 , lang.rules+52 },
            { lang.atoms+5 , lang.rules+52 },
            { lang.atoms+6 , lang.rules+52 },
            { lang.atoms+8 , lang.rules+52 },
            { lang.atoms+9 , null },
            { lang.atoms+10 , null },
            { lang.atoms+11 , lang.rules+52 },
            { lang.atoms+19 , null },
            { lang.atoms+41 , lang.rules+52 }
           }
    },
    { 96 ,
           {
            { lang.atoms+1 , lang.rules+52 },
            { lang.atoms+4 , lang.rules+52 },
            { lang.atoms+5 , lang.rules+52 },
            { lang.atoms+6 , lang.rules+52 },
            { lang.atoms+8 , lang.rules+52 },
            { lang.atoms+11 , lang.rules+52 },
            { lang.atoms+19 , null },
            { lang.atoms+41 , lang.rules+52 }
           }
    },
    { 97 ,
           {
            { lang.atoms+1 , lang.rules+52 },
            { lang.atoms+4 , lang.rules+52 },
            { lang.atoms+5 , lang.rules+52 },
            { lang.atoms+6 , lang.rules+52 },
            { lang.atoms+8 , lang.rules+52 },
            { lang.atoms+11 , lang.rules+52 },
            { lang.atoms+41 , lang.rules+52 }
           }
    },
    { 98 ,
           {
            { lang.atoms+1 , lang.rules+52 },
            { lang.atoms+5 , lang.rules+52 },
            { lang.atoms+6 , lang.rules+52 },
            { lang.atoms+7 , lang.rules+52 },
            { lang.atoms+8 , lang.rules+52 },
            { lang.atoms+9 , null },
            { lang.atoms+10 , null },
            { lang.atoms+11 , lang.rules+52 },
            { lang.atoms+19 , null },
            { lang.atoms+41 , lang.rules+52 },
            { lang.atoms+42 , lang.rules+52 }
           }
    },
    { 99 ,
           {
            { lang.atoms+1 , lang.rules+52 },
            { lang.atoms+5 , lang.rules+52 },
            { lang.atoms+6 , lang.rules+52 },
            { lang.atoms+7 , lang.rules+52 },
            { lang.atoms+8 , lang.rules+52 },
            { lang.atoms+11 , lang.rules+52 },
            { lang.atoms+19 , null },
            { lang.atoms+41 , lang.rules+52 },
            { lang.atoms+42 , lang.rules+52 }
           }
    },
    { 100 ,
            {
             { lang.atoms+1 , lang.rules+52 },
             { lang.atoms+5 , lang.rules+52 },
             { lang.atoms+6 , lang.rules+52 },
             { lang.atoms+7 , lang.rules+52 },
             { lang.atoms+8 , lang.rules+52 },
             { lang.atoms+11 , lang.rules+52 },
             { lang.atoms+41 , lang.rules+52 },
             { lang.atoms+42 , lang.rules+52 }
            }
    },
    { 101 ,
            {
             { lang.atoms+1 , lang.rules+52 },
             { lang.atoms+5 , lang.rules+52 },
             { lang.atoms+6 , lang.rules+52 },
             { lang.atoms+8 , lang.rules+52 },
             { lang.atoms+9 , null },
             { lang.atoms+10 , null },
             { lang.atoms+11 , lang.rules+52 },
             { lang.atoms+12 , lang.rules+52 },
             { lang.atoms+19 , null },
             { lang.atoms+41 , lang.rules+52 }
            }
    },
    { 102 ,
            {
             { lang.atoms+1 , lang.rules+52 },
             { lang.atoms+5 , lang.rules+52 },
             { lang.atoms+6 , lang.rules+52 },
             { lang.atoms+8 , lang.rules+52 },
             { lang.atoms+9 , null },
             { lang.atoms+10 , null },
             { lang.atoms+11 , lang.rules+52 },
             { lang.atoms+19 , null },
             { lang.atoms+20 , lang.rules+52 },
             { lang.atoms+41 , lang.rules+52 }
            }
    },
    { 103 ,
            {
             { lang.atoms+1 , lang.rules+52 },
             { lang.atoms+5 , lang.rules+52 },
             { lang.atoms+6 , lang.rules+52 },
             { lang.atoms+8 , lang.rules+52 },
             { lang.atoms+11 , lang.rules+52 },
             { lang.atoms+12 , lang.rules+52 },
             { lang.atoms+19 , null },
             { lang.atoms+41 , lang.rules+52 }
            }
    },
    { 104 ,
            {
             { lang.atoms+1 , lang.rules+52 },
             { lang.atoms+5 , lang.rules+52 },
             { lang.atoms+6 , lang.rules+52 },
             { lang.atoms+8 , lang.rules+52 },
             { lang.atoms+11 , lang.rules+52 },
             { lang.atoms+12 , lang.rules+52 },
             { lang.atoms+41 , lang.rules+52 }
            }
    },
    { 105 ,
            {
             { lang.atoms+1 , lang.rules+52 },
             { lang.atoms+5 , lang.rules+52 },
             { lang.atoms+6 , lang.rules+52 },
             { lang.atoms+8 , lang.rules+52 },
             { lang.atoms+11 , lang.rules+52 },
             { lang.atoms+19 , null },
             { lang.atoms+20 , lang.rules+52 },
             { lang.atoms+41 , lang.rules+52 }
            }
    },
    { 106 ,
            {
             { lang.atoms+1 , lang.rules+52 },
             { lang.atoms+5 , lang.rules+52 },
             { lang.atoms+6 , lang.rules+52 },
             { lang.atoms+8 , lang.rules+52 },
             { lang.atoms+11 , lang.rules+52 },
             { lang.atoms+20 , lang.rules+52 },
             { lang.atoms+41 , lang.rules+52 }
            }
    },
    { 107 ,
            {
             { lang.atoms+1 , lang.rules+53 },
             { lang.atoms+4 , lang.rules+53 },
             { lang.atoms+5 , lang.rules+53 },
             { lang.atoms+6 , lang.rules+53 },
             { lang.atoms+8 , lang.rules+53 },
             { lang.atoms+9 , null },
             { lang.atoms+10 , null },
             { lang.atoms+11 , lang.rules+53 },
             { lang.atoms+19 , null },
             { lang.atoms+41 , lang.rules+53 }
            }
    },
    { 108 ,
            {
             { lang.atoms+1 , lang.rules+53 },
             { lang.atoms+4 , lang.rules+53 },
             { lang.atoms+5 , lang.rules+53 },
             { lang.atoms+6 , lang.rules+53 },
             { lang.atoms+8 , lang.rules+53 },
             { lang.atoms+11 , lang.rules+53 },
             { lang.atoms+19 , null },
             { lang.atoms+41 , lang.rules+53 }
            }
    },
    { 109 ,
            {
             { lang.atoms+1 , lang.rules+53 },
             { lang.atoms+4 , lang.rules+53 },
             { lang.atoms+5 , lang.rules+53 },
             { lang.atoms+6 , lang.rules+53 },
             { lang.atoms+8 , lang.rules+53 },
             { lang.atoms+11 , lang.rules+53 },
             { lang.atoms+41 , lang.rules+53 }
            }
    },
    { 110 ,
            {
             { lang.atoms+1 , lang.rules+53 },
             { lang.atoms+5 , lang.rules+53 },
             { lang.atoms+6 , lang.rules+53 },
             { lang.atoms+7 , lang.rules+53 },
             { lang.atoms+8 , lang.rules+53 },
             { lang.atoms+9 , null },
             { lang.atoms+10 , null },
             { lang.atoms+11 , lang.rules+53 },
             { lang.atoms+19 , null },
             { lang.atoms+41 , lang.rules+53 },
             { lang.atoms+42 , lang.rules+53 }
            }
    },
    { 111 ,
            {
             { lang.atoms+1 , lang.rules+53 },
             { lang.atoms+5 , lang.rules+53 },
             { lang.atoms+6 , lang.rules+53 },
             { lang.atoms+7 , lang.rules+53 },
             { lang.atoms+8 , lang.rules+53 },
             { lang.atoms+11 , lang.rules+53 },
             { lang.atoms+19 , null },
             { lang.atoms+41 , lang.rules+53 },
             { lang.atoms+42 , lang.rules+53 }
            }
    },
    { 112 ,
            {
             { lang.atoms+1 , lang.rules+53 },
             { lang.atoms+5 , lang.rules+53 },
             { lang.atoms+6 , lang.rules+53 },
             { lang.atoms+7 , lang.rules+53 },
             { lang.atoms+8 , lang.rules+53 },
             { lang.atoms+11 , lang.rules+53 },
             { lang.atoms+41 , lang.rules+53 },
             { lang.atoms+42 , lang.rules+53 }
            }
    },
    { 113 ,
            {
             { lang.atoms+1 , lang.rules+53 },
             { lang.atoms+5 , lang.rules+53 },
             { lang.atoms+6 , lang.rules+53 },
             { lang.atoms+8 , lang.rules+53 },
             { lang.atoms+9 , null },
             { lang.atoms+10 , null },
             { lang.atoms+11 , lang.rules+53 },
             { lang.atoms+12 , lang.rules+53 },
             { lang.atoms+19 , null },
             { lang.atoms+41 , lang.rules+53 }
            }
    },
    { 114 ,
            {
             { lang.atoms+1 , lang.rules+53 },
             { lang.atoms+5 , lang.rules+53 },
             { lang.atoms+6 , lang.rules+53 },
             { lang.atoms+8 , lang.rules+53 },
             { lang.atoms+9 , null },
             { lang.atoms+10 , null },
             { lang.atoms+11 , lang.rules+53 },
             { lang.atoms+19 , null },
             { lang.atoms+20 , lang.rules+53 },
             { lang.atoms+41 , lang.rules+53 }
            }
    },
    { 115 ,
            {
             { lang.atoms+1 , lang.rules+53 },
             { lang.atoms+5 , lang.rules+53 },
             { lang.atoms+6 , lang.rules+53 },
             { lang.atoms+8 , lang.rules+53 },
             { lang.atoms+11 , lang.rules+53 },
             { lang.atoms+12 , lang.rules+53 },
             { lang.atoms+19 , null },
             { lang.atoms+41 , lang.rules+53 }
            }
    },
    { 116 ,
            {
             { lang.atoms+1 , lang.rules+53 },
             { lang.atoms+5 , lang.rules+53 },
             { lang.atoms+6 , lang.rules+53 },
             { lang.atoms+8 , lang.rules+53 },
             { lang.atoms+11 , lang.rules+53 },
             { lang.atoms+12 , lang.rules+53 },
             { lang.atoms+41 , lang.rules+53 }
            }
    },
    { 117 ,
            {
             { lang.atoms+1 , lang.rules+53 },
             { lang.atoms+5 , lang.rules+53 },
             { lang.atoms+6 , lang.rules+53 },
             { lang.atoms+8 , lang.rules+53 },
             { lang.atoms+11 , lang.rules+53 },
             { lang.atoms+19 , null },
             { lang.atoms+20 , lang.rules+53 },
             { lang.atoms+41 , lang.rules+53 }
            }
    },
    { 118 ,
            {
             { lang.atoms+1 , lang.rules+53 },
             { lang.atoms+5 , lang.rules+53 },
             { lang.atoms+6 , lang.rules+53 },
             { lang.atoms+8 , lang.rules+53 },
             { lang.atoms+11 , lang.rules+53 },
             { lang.atoms+20 , lang.rules+53 },
             { lang.atoms+41 , lang.rules+53 }
            }
    },
    { 119 ,
            {
             { lang.atoms+1 , lang.rules+54 },
             { lang.atoms+4 , lang.rules+54 },
             { lang.atoms+5 , lang.rules+54 },
             { lang.atoms+6 , lang.rules+54 },
             { lang.atoms+8 , lang.rules+54 },
             { lang.atoms+9 , null },
             { lang.atoms+10 , null },
             { lang.atoms+11 , lang.rules+54 },
             { lang.atoms+19 , null },
             { lang.atoms+41 , lang.rules+54 }
            }
    },
    { 120 ,
            {
             { lang.atoms+1 , lang.rules+54 },
             { lang.atoms+4 , lang.rules+54 },
             { lang.atoms+5 , lang.rules+54 },
             { lang.atoms+6 , lang.rules+54 },
             { lang.atoms+8 , lang.rules+54 },
             { lang.atoms+11 , lang.rules+54 },
             { lang.atoms+19 , null },
             { lang.atoms+41 , lang.rules+54 }
            }
    },
    { 121 ,
            {
             { lang.atoms+1 , lang.rules+54 },
             { lang.atoms+4 , lang.rules+54 },
             { lang.atoms+5 , lang.rules+54 },
             { lang.atoms+6 , lang.rules+54 },
             { lang.atoms+8 , lang.rules+54 },
             { lang.atoms+11 , lang.rules+54 },
             { lang.atoms+41 , lang.rules+54 }
            }
    },
    { 122 ,
            {
             { lang.atoms+1 , lang.rules+54 },
             { lang.atoms+5 , lang.rules+54 },
             { lang.atoms+6 , lang.rules+54 },
             { lang.atoms+7 , lang.rules+54 },
             { lang.atoms+8 , lang.rules+54 },
             { lang.atoms+9 , null },
             { lang.atoms+10 , null },
             { lang.atoms+11 , lang.rules+54 },
             { lang.atoms+19 , null },
             { lang.atoms+41 , lang.rules+54 },
             { lang.atoms+42 , lang.rules+54 }
            }
    },
    { 123 ,
            {
             { lang.atoms+1 , lang.rules+54 },
             { lang.atoms+5 , lang.rules+54 },
             { lang.atoms+6 , lang.rules+54 },
             { lang.atoms+7 , lang.rules+54 },
             { lang.atoms+8 , lang.rules+54 },
             { lang.atoms+11 , lang.rules+54 },
             { lang.atoms+19 , null },
             { lang.atoms+41 , lang.rules+54 },
             { lang.atoms+42 , lang.rules+54 }
            }
    },
    { 124 ,
            {
             { lang.atoms+1 , lang.rules+54 },
             { lang.atoms+5 , lang.rules+54 },
             { lang.atoms+6 , lang.rules+54 },
             { lang.atoms+7 , lang.rules+54 },
             { lang.atoms+8 , lang.rules+54 },
             { lang.atoms+11 , lang.rules+54 },
             { lang.atoms+41 , lang.rules+54 },
             { lang.atoms+42 , lang.rules+54 }
            }
    },
    { 125 ,
            {
             { lang.atoms+1 , lang.rules+54 },
             { lang.atoms+5 , lang.rules+54 },
             { lang.atoms+6 , lang.rules+54 },
             { lang.atoms+8 , lang.rules+54 },
             { lang.atoms+9 , null },
             { lang.atoms+10 , null },
             { lang.atoms+11 , lang.rules+54 },
             { lang.atoms+12 , lang.rules+54 },
             { lang.atoms+19 , null },
             { lang.atoms+41 , lang.rules+54 }
            }
    },
    { 126 ,
            {
             { lang.atoms+1 , lang.rules+54 },
             { lang.atoms+5 , lang.rules+54 },
             { lang.atoms+6 , lang.rules+54 },
             { lang.atoms+8 , lang.rules+54 },
             { lang.atoms+9 , null },
             { lang.atoms+10 , null },
             { lang.atoms+11 , lang.rules+54 },
             { lang.atoms+19 , null },
             { lang.atoms+20 , lang.rules+54 },
             { lang.atoms+41 , lang.rules+54 }
            }
    },
    { 127 ,
            {
             { lang.atoms+1 , lang.rules+54 },
             { lang.atoms+5 , lang.rules+54 },
             { lang.atoms+6 , lang.rules+54 },
             { lang.atoms+8 , lang.rules+54 },
             { lang.atoms+11 , lang.rules+54 },
             { lang.atoms+12 , lang.rules+54 },
             { lang.atoms+19 , null },
             { lang.atoms+41 , lang.rules+54 }
            }
    },
    { 128 ,
            {
             { lang.atoms+1 , lang.rules+54 },
             { lang.atoms+5 , lang.rules+54 },
             { lang.atoms+6 , lang.rules+54 },
             { lang.atoms+8 , lang.rules+54 },
             { lang.atoms+11 , lang.rules+54 },
             { lang.atoms+12 , lang.rules+54 },
             { lang.atoms+41 , lang.rules+54 }
            }
    },
    { 129 ,
            {
             { lang.atoms+1 , lang.rules+54 },
             { lang.atoms+5 , lang.rules+54 },
             { lang.atoms+6 , lang.rules+54 },
             { lang.atoms+8 , lang.rules+54 },
             { lang.atoms+11 , lang.rules+54 },
             { lang.atoms+19 , null },
             { lang.atoms+20 , lang.rules+54 },
             { lang.atoms+41 , lang.rules+54 }
            }
    },
    { 130 ,
            {
             { lang.atoms+1 , lang.rules+54 },
             { lang.atoms+5 , lang.rules+54 },
             { lang.atoms+6 , lang.rules+54 },
             { lang.atoms+8 , lang.rules+54 },
             { lang.atoms+11 , lang.rules+54 },
             { lang.atoms+20 , lang.rules+54 },
             { lang.atoms+41 , lang.rules+54 }
            }
    },
    { 131 ,
            {
             { lang.atoms+1 , lang.rules+55 },
             { lang.atoms+4 , lang.rules+55 },
             { lang.atoms+5 , lang.rules+55 },
             { lang.atoms+6 , lang.rules+55 },
             { lang.atoms+8 , lang.rules+55 },
             { lang.atoms+9 , null },
             { lang.atoms+10 , null },
             { lang.atoms+11 , lang.rules+55 },
             { lang.atoms+19 , null },
             { lang.atoms+41 , lang.rules+55 }
            }
    },
    { 132 ,
            {
             { lang.atoms+1 , lang.rules+55 },
             { lang.atoms+4 , lang.rules+55 },
             { lang.atoms+5 , lang.rules+55 },
             { lang.atoms+6 , lang.rules+55 },
             { lang.atoms+8 , lang.rules+55 },
             { lang.atoms+11 , lang.rules+55 },
             { lang.atoms+19 , null },
             { lang.atoms+41 , lang.rules+55 }
            }
    },
    { 133 ,
            {
             { lang.atoms+1 , lang.rules+55 },
             { lang.atoms+4 , lang.rules+55 },
             { lang.atoms+5 , lang.rules+55 },
             { lang.atoms+6 , lang.rules+55 },
             { lang.atoms+8 , lang.rules+55 },
             { lang.atoms+11 , lang.rules+55 },
             { lang.atoms+41 , lang.rules+55 }
            }
    },
    { 134 ,
            {
             { lang.atoms+1 , lang.rules+55 },
             { lang.atoms+5 , lang.rules+55 },
             { lang.atoms+6 , lang.rules+55 },
             { lang.atoms+7 , lang.rules+55 },
             { lang.atoms+8 , lang.rules+55 },
             { lang.atoms+9 , null },
             { lang.atoms+10 , null },
             { lang.atoms+11 , lang.rules+55 },
             { lang.atoms+19 , null },
             { lang.atoms+41 , lang.rules+55 },
             { lang.atoms+42 , lang.rules+55 }
            }
    },
    { 135 ,
            {
             { lang.atoms+1 , lang.rules+55 },
             { lang.atoms+5 , lang.rules+55 },
             { lang.atoms+6 , lang.rules+55 },
             { lang.atoms+7 , lang.rules+55 },
             { lang.atoms+8 , lang.rules+55 },
             { lang.atoms+11 , lang.rules+55 },
             { lang.atoms+19 , null },
             { lang.atoms+41 , lang.rules+55 },
             { lang.atoms+42 , lang.rules+55 }
            }
    },
    { 136 ,
            {
             { lang.atoms+1 , lang.rules+55 },
             { lang.atoms+5 , lang.rules+55 },
             { lang.atoms+6 , lang.rules+55 },
             { lang.atoms+7 , lang.rules+55 },
             { lang.atoms+8 , lang.rules+55 },
             { lang.atoms+11 , lang.rules+55 },
             { lang.atoms+41 , lang.rules+55 },
             { lang.atoms+42 , lang.rules+55 }
            }
    },
    { 137 ,
            {
             { lang.atoms+1 , lang.rules+55 },
             { lang.atoms+5 , lang.rules+55 },
             { lang.atoms+6 , lang.rules+55 },
             { lang.atoms+8 , lang.rules+55 },
             { lang.atoms+9 , null },
             { lang.atoms+10 , null },
             { lang.atoms+11 , lang.rules+55 },
             { lang.atoms+12 , lang.rules+55 },
             { lang.atoms+19 , null },
             { lang.atoms+41 , lang.rules+55 }
            }
    },
    { 138 ,
            {
             { lang.atoms+1 , lang.rules+55 },
             { lang.atoms+5 , lang.rules+55 },
             { lang.atoms+6 , lang.rules+55 },
             { lang.atoms+8 , lang.rules+55 },
             { lang.atoms+9 , null },
             { lang.atoms+10 , null },
             { lang.atoms+11 , lang.rules+55 },
             { lang.atoms+19 , null },
             { lang.atoms+20 , lang.rules+55 },
             { lang.atoms+41 , lang.rules+55 }
            }
    },
    { 139 ,
            {
             { lang.atoms+1 , lang.rules+55 },
             { lang.atoms+5 , lang.rules+55 },
             { lang.atoms+6 , lang.rules+55 },
             { lang.atoms+8 , lang.rules+55 },
             { lang.atoms+11 , lang.rules+55 },
             { lang.atoms+12 , lang.rules+55 },
             { lang.atoms+19 , null },
             { lang.atoms+41 , lang.rules+55 }
            }
    },
    { 140 ,
            {
             { lang.atoms+1 , lang.rules+55 },
             { lang.atoms+5 , lang.rules+55 },
             { lang.atoms+6 , lang.rules+55 },
             { lang.atoms+8 , lang.rules+55 },
             { lang.atoms+11 , lang.rules+55 },
             { lang.atoms+12 , lang.rules+55 },
             { lang.atoms+41 , lang.rules+55 }
            }
    },
    { 141 ,
            {
             { lang.atoms+1 , lang.rules+55 },
             { lang.atoms+5 , lang.rules+55 },
             { lang.atoms+6 , lang.rules+55 },
             { lang.atoms+8 , lang.rules+55 },
             { lang.atoms+11 , lang.rules+55 },
             { lang.atoms+19 , null },
             { lang.atoms+20 , lang.rules+55 },
             { lang.atoms+41 , lang.rules+55 }
            }
    },
    { 142 ,
            {
             { lang.atoms+1 , lang.rules+55 },
             { lang.atoms+5 , lang.rules+55 },
             { lang.atoms+6 , lang.rules+55 },
             { lang.atoms+8 , lang.rules+55 },
             { lang.atoms+11 , lang.rules+55 },
             { lang.atoms+20 , lang.rules+55 },
             { lang.atoms+41 , lang.rules+55 }
            }
    },
    { 143 ,
            {
             { lang.atoms+1 , lang.rules+56 },
             { lang.atoms+4 , lang.rules+56 },
             { lang.atoms+5 , lang.rules+56 },
             { lang.atoms+6 , lang.rules+56 },
             { lang.atoms+8 , lang.rules+56 },
             { lang.atoms+9 , null },
             { lang.atoms+10 , null },
             { lang.atoms+11 , lang.rules+56 },
             { lang.atoms+19 , null },
             { lang.atoms+41 , lang.rules+56 }
            }
    },
    { 144 ,
            {
             { lang.atoms+1 , lang.rules+56 },
             { lang.atoms+4 , lang.rules+56 },
             { lang.atoms+5 , lang.rules+56 },
             { lang.atoms+6 , lang.rules+56 },
             { lang.atoms+8 , lang.rules+56 },
             { lang.atoms+11 , lang.rules+56 },
             { lang.atoms+19 , null },
             { lang.atoms+41 , lang.rules+56 }
            }
    },
    { 145 ,
            {
             { lang.atoms+1 , lang.rules+56 },
             { lang.atoms+4 , lang.rules+56 },
             { lang.atoms+5 , lang.rules+56 },
             { lang.atoms+6 , lang.rules+56 },
             { lang.atoms+8 , lang.rules+56 },
             { lang.atoms+11 , lang.rules+56 },
             { lang.atoms+41 , lang.rules+56 }
            }
    },
    { 146 ,
            {
             { lang.atoms+1 , lang.rules+56 },
             { lang.atoms+5 , lang.rules+56 },
             { lang.atoms+6 , lang.rules+56 },
             { lang.atoms+7 , lang.rules+56 },
             { lang.atoms+8 , lang.rules+56 },
             { lang.atoms+9 , null },
             { lang.atoms+10 , null },
             { lang.atoms+11 , lang.rules+56 },
             { lang.atoms+19 , null },
             { lang.atoms+41 , lang.rules+56 },
             { lang.atoms+42 , lang.rules+56 }
            }
    },
    { 147 ,
            {
             { lang.atoms+1 , lang.rules+56 },
             { lang.atoms+5 , lang.rules+56 },
             { lang.atoms+6 , lang.rules+56 },
             { lang.atoms+7 , lang.rules+56 },
             { lang.atoms+8 , lang.rules+56 },
             { lang.atoms+11 , lang.rules+56 },
             { lang.atoms+19 , null },
             { lang.atoms+41 , lang.rules+56 },
             { lang.atoms+42 , lang.rules+56 }
            }
    },
    { 148 ,
            {
             { lang.atoms+1 , lang.rules+56 },
             { lang.atoms+5 , lang.rules+56 },
             { lang.atoms+6 , lang.rules+56 },
             { lang.atoms+7 , lang.rules+56 },
             { lang.atoms+8 , lang.rules+56 },
             { lang.atoms+11 , lang.rules+56 },
             { lang.atoms+41 , lang.rules+56 },
             { lang.atoms+42 , lang.rules+56 }
            }
    },
    { 149 ,
            {
             { lang.atoms+1 , lang.rules+56 },
             { lang.atoms+5 , lang.rules+56 },
             { lang.atoms+6 , lang.rules+56 },
             { lang.atoms+8 , lang.rules+56 },
             { lang.atoms+9 , null },
             { lang.atoms+10 , null },
             { lang.atoms+11 , lang.rules+56 },
             { lang.atoms+12 , lang.rules+56 },
             { lang.atoms+19 , null },
             { lang.atoms+41 , lang.rules+56 }
            }
    },
    { 150 ,
            {
             { lang.atoms+1 , lang.rules+56 },
             { lang.atoms+5 , lang.rules+56 },
             { lang.atoms+6 , lang.rules+56 },
             { lang.atoms+8 , lang.rules+56 },
             { lang.atoms+9 , null },
             { lang.atoms+10 , null },
             { lang.atoms+11 , lang.rules+56 },
             { lang.atoms+19 , null },
             { lang.atoms+20 , lang.rules+56 },
             { lang.atoms+41 , lang.rules+56 }
            }
    },
    { 151 ,
            {
             { lang.atoms+1 , lang.rules+56 },
             { lang.atoms+5 , lang.rules+56 },
             { lang.atoms+6 , lang.rules+56 },
             { lang.atoms+8 , lang.rules+56 },
             { lang.atoms+11 , lang.rules+56 },
             { lang.atoms+12 , lang.rules+56 },
             { lang.atoms+19 , null },
             { lang.atoms+41 , lang.rules+56 }
            }
    },
    { 152 ,
            {
             { lang.atoms+1 , lang.rules+56 },
             { lang.atoms+5 , lang.rules+56 },
             { lang.atoms+6 , lang.rules+56 },
             { lang.atoms+8 , lang.rules+56 },
             { lang.atoms+11 , lang.rules+56 },
             { lang.atoms+12 , lang.rules+56 },
             { lang.atoms+41 , lang.rules+56 }
            }
    },
    { 153 ,
            {
             { lang.atoms+1 , lang.rules+56 },
             { lang.atoms+5 , lang.rules+56 },
             { lang.atoms+6 , lang.rules+56 },
             { lang.atoms+8 , lang.rules+56 },
             { lang.atoms+11 , lang.rules+56 },
             { lang.atoms+19 , null },
             { lang.atoms+20 , lang.rules+56 },
             { lang.atoms+41 , lang.rules+56 }
            }
    },
    { 154 ,
            {
             { lang.atoms+1 , lang.rules+56 },
             { lang.atoms+5 , lang.rules+56 },
             { lang.atoms+6 , lang.rules+56 },
             { lang.atoms+8 , lang.rules+56 },
             { lang.atoms+11 , lang.rules+56 },
             { lang.atoms+20 , lang.rules+56 },
             { lang.atoms+41 , lang.rules+56 }
            }
    },
    { 155 ,
            {
             { lang.atoms+1 , lang.rules+57 },
             { lang.atoms+4 , lang.rules+57 },
             { lang.atoms+5 , lang.rules+57 },
             { lang.atoms+6 , lang.rules+57 },
             { lang.atoms+8 , lang.rules+57 },
             { lang.atoms+9 , null },
             { lang.atoms+10 , null },
             { lang.atoms+11 , lang.rules+57 },
             { lang.atoms+19 , null },
             { lang.atoms+41 , lang.rules+57 }
            }
    },
    { 156 ,
            {
             { lang.atoms+1 , lang.rules+57 },
             { lang.atoms+4 , lang.rules+57 },
             { lang.atoms+5 , lang.rules+57 },
             { lang.atoms+6 , lang.rules+57 },
             { lang.atoms+8 , lang.rules+57 },
             { lang.atoms+11 , lang.rules+57 },
             { lang.atoms+19 , null },
             { lang.atoms+41 , lang.rules+57 }
            }
    },
    { 157 ,
            {
             { lang.atoms+1 , lang.rules+57 },
             { lang.atoms+4 , lang.rules+57 },
             { lang.atoms+5 , lang.rules+57 },
             { lang.atoms+6 , lang.rules+57 },
             { lang.atoms+8 , lang.rules+57 },
             { lang.atoms+11 , lang.rules+57 },
             { lang.atoms+41 , lang.rules+57 }
            }
    },
    { 158 ,
            {
             { lang.atoms+1 , lang.rules+57 },
             { lang.atoms+5 , lang.rules+57 },
             { lang.atoms+6 , lang.rules+57 },
             { lang.atoms+7 , lang.rules+57 },
             { lang.atoms+8 , lang.rules+57 },
             { lang.atoms+9 , null },
             { lang.atoms+10 , null },
             { lang.atoms+11 , lang.rules+57 },
             { lang.atoms+19 , null },
             { lang.atoms+41 , lang.rules+57 },
             { lang.atoms+42 , lang.rules+57 }
            }
    },
    { 159 ,
            {
             { lang.atoms+1 , lang.rules+57 },
             { lang.atoms+5 , lang.rules+57 },
             { lang.atoms+6 , lang.rules+57 },
             { lang.atoms+7 , lang.rules+57 },
             { lang.atoms+8 , lang.rules+57 },
             { lang.atoms+11 , lang.rules+57 },
             { lang.atoms+19 , null },
             { lang.atoms+41 , lang.rules+57 },
             { lang.atoms+42 , lang.rules+57 }
            }
    },
    { 160 ,
            {
             { lang.atoms+1 , lang.rules+57 },
             { lang.atoms+5 , lang.rules+57 },
             { lang.atoms+6 , lang.rules+57 },
             { lang.atoms+7 , lang.rules+57 },
             { lang.atoms+8 , lang.rules+57 },
             { lang.atoms+11 , lang.rules+57 },
             { lang.atoms+41 , lang.rules+57 },
             { lang.atoms+42 , lang.rules+57 }
            }
    },
    { 161 ,
            {
             { lang.atoms+1 , lang.rules+57 },
             { lang.atoms+5 , lang.rules+57 },
             { lang.atoms+6 , lang.rules+57 },
             { lang.atoms+8 , lang.rules+57 },
             { lang.atoms+9 , null },
             { lang.atoms+10 , null },
             { lang.atoms+11 , lang.rules+57 },
             { lang.atoms+12 , lang.rules+57 },
             { lang.atoms+19 , null },
             { lang.atoms+41 , lang.rules+57 }
            }
    },
    { 162 ,
            {
             { lang.atoms+1 , lang.rules+57 },
             { lang.atoms+5 , lang.rules+57 },
             { lang.atoms+6 , lang.rules+57 },
             { lang.atoms+8 , lang.rules+57 },
             { lang.atoms+9 , null },
             { lang.atoms+10 , null },
             { lang.atoms+11 , lang.rules+57 },
             { lang.atoms+19 , null },
             { lang.atoms+20 , lang.rules+57 },
             { lang.atoms+41 , lang.rules+57 }
            }
    },
    { 163 ,
            {
             { lang.atoms+1 , lang.rules+57 },
             { lang.atoms+5 , lang.rules+57 },
             { lang.atoms+6 , lang.rules+57 },
             { lang.atoms+8 , lang.rules+57 },
             { lang.atoms+11 , lang.rules+57 },
             { lang.atoms+12 , lang.rules+57 },
             { lang.atoms+19 , null },
             { lang.atoms+41 , lang.rules+57 }
            }
    },
    { 164 ,
            {
             { lang.atoms+1 , lang.rules+57 },
             { lang.atoms+5 , lang.rules+57 },
             { lang.atoms+6 , lang.rules+57 },
             { lang.atoms+8 , lang.rules+57 },
             { lang.atoms+11 , lang.rules+57 },
             { lang.atoms+12 , lang.rules+57 },
             { lang.atoms+41 , lang.rules+57 }
            }
    },
    { 165 ,
            {
             { lang.atoms+1 , lang.rules+57 },
             { lang.atoms+5 , lang.rules+57 },
             { lang.atoms+6 , lang.rules+57 },
             { lang.atoms+8 , lang.rules+57 },
             { lang.atoms+11 , lang.rules+57 },
             { lang.atoms+19 , null },
             { lang.atoms+20 , lang.rules+57 },
             { lang.atoms+41 , lang.rules+57 }
            }
    },
    { 166 ,
            {
             { lang.atoms+1 , lang.rules+57 },
             { lang.atoms+5 , lang.rules+57 },
             { lang.atoms+6 , lang.rules+57 },
             { lang.atoms+8 , lang.rules+57 },
             { lang.atoms+11 , lang.rules+57 },
             { lang.atoms+20 , lang.rules+57 },
             { lang.atoms+41 , lang.rules+57 }
            }
    },
    { 167 ,
            {
             { lang.atoms+1 , lang.rules+58 },
             { lang.atoms+4 , lang.rules+58 },
             { lang.atoms+5 , lang.rules+58 },
             { lang.atoms+6 , lang.rules+58 },
             { lang.atoms+8 , lang.rules+58 },
             { lang.atoms+9 , null },
             { lang.atoms+10 , null },
             { lang.atoms+11 , lang.rules+58 },
             { lang.atoms+19 , null },
             { lang.atoms+41 , lang.rules+58 }
            }
    },
    { 168 ,
            {
             { lang.atoms+1 , lang.rules+58 },
             { lang.atoms+4 , lang.rules+58 },
             { lang.atoms+5 , lang.rules+58 },
             { lang.atoms+6 , lang.rules+58 },
             { lang.atoms+8 , lang.rules+58 },
             { lang.atoms+11 , lang.rules+58 },
             { lang.atoms+19 , null },
             { lang.atoms+41 , lang.rules+58 }
            }
    },
    { 169 ,
            {
             { lang.atoms+1 , lang.rules+58 },
             { lang.atoms+4 , lang.rules+58 },
             { lang.atoms+5 , lang.rules+58 },
             { lang.atoms+6 , lang.rules+58 },
             { lang.atoms+8 , lang.rules+58 },
             { lang.atoms+11 , lang.rules+58 },
             { lang.atoms+41 , lang.rules+58 }
            }
    },
    { 170 ,
            {
             { lang.atoms+1 , lang.rules+58 },
             { lang.atoms+5 , lang.rules+58 },
             { lang.atoms+6 , lang.rules+58 },
             { lang.atoms+7 , lang.rules+58 },
             { lang.atoms+8 , lang.rules+58 },
             { lang.atoms+9 , null },
             { lang.atoms+10 , null },
             { lang.atoms+11 , lang.rules+58 },
             { lang.atoms+19 , null },
             { lang.atoms+41 , lang.rules+58 },
             { lang.atoms+42 , lang.rules+58 }
            }
    },
    { 171 ,
            {
             { lang.atoms+1 , lang.rules+58 },
             { lang.atoms+5 , lang.rules+58 },
             { lang.atoms+6 , lang.rules+58 },
             { lang.atoms+7 , lang.rules+58 },
             { lang.atoms+8 , lang.rules+58 },
             { lang.atoms+11 , lang.rules+58 },
             { lang.atoms+19 , null },
             { lang.atoms+41 , lang.rules+58 },
             { lang.atoms+42 , lang.rules+58 }
            }
    },
    { 172 ,
            {
             { lang.atoms+1 , lang.rules+58 },
             { lang.atoms+5 , lang.rules+58 },
             { lang.atoms+6 , lang.rules+58 },
             { lang.atoms+7 , lang.rules+58 },
             { lang.atoms+8 , lang.rules+58 },
             { lang.atoms+11 , lang.rules+58 },
             { lang.atoms+41 , lang.rules+58 },
             { lang.atoms+42 , lang.rules+58 }
            }
    },
    { 173 ,
            {
             { lang.atoms+1 , lang.rules+58 },
             { lang.atoms+5 , lang.rules+58 },
             { lang.atoms+6 , lang.rules+58 },
             { lang.atoms+8 , lang.rules+58 },
             { lang.atoms+9 , null },
             { lang.atoms+10 , null },
             { lang.atoms+11 , lang.rules+58 },
             { lang.atoms+12 , lang.rules+58 },
             { lang.atoms+19 , null },
             { lang.atoms+41 , lang.rules+58 }
            }
    },
    { 174 ,
            {
             { lang.atoms+1 , lang.rules+58 },
             { lang.atoms+5 , lang.rules+58 },
             { lang.atoms+6 , lang.rules+58 },
             { lang.atoms+8 , lang.rules+58 },
             { lang.atoms+9 , null },
             { lang.atoms+10 , null },
             { lang.atoms+11 , lang.rules+58 },
             { lang.atoms+19 , null },
             { lang.atoms+20 , lang.rules+58 },
             { lang.atoms+41 , lang.rules+58 }
            }
    },
    { 175 ,
            {
             { lang.atoms+1 , lang.rules+58 },
             { lang.atoms+5 , lang.rules+58 },
             { lang.atoms+6 , lang.rules+58 },
             { lang.atoms+8 , lang.rules+58 },
             { lang.atoms+11 , lang.rules+58 },
             { lang.atoms+12 , lang.rules+58 },
             { lang.atoms+19 , null },
             { lang.atoms+41 , lang.rules+58 }
            }
    },
    { 176 ,
            {
             { lang.atoms+1 , lang.rules+58 },
             { lang.atoms+5 , lang.rules+58 },
             { lang.atoms+6 , lang.rules+58 },
             { lang.atoms+8 , lang.rules+58 },
             { lang.atoms+11 , lang.rules+58 },
             { lang.atoms+12 , lang.rules+58 },
             { lang.atoms+41 , lang.rules+58 }
            }
    },
    { 177 ,
            {
             { lang.atoms+1 , lang.rules+58 },
             { lang.atoms+5 , lang.rules+58 },
             { lang.atoms+6 , lang.rules+58 },
             { lang.atoms+8 , lang.rules+58 },
             { lang.atoms+11 , lang.rules+58 },
             { lang.atoms+19 , null },
             { lang.atoms+20 , lang.rules+58 },
             { lang.atoms+41 , lang.rules+58 }
            }
    },
    { 178 ,
            {
             { lang.atoms+1 , lang.rules+58 },
             { lang.atoms+5 , lang.rules+58 },
             { lang.atoms+6 , lang.rules+58 },
             { lang.atoms+8 , lang.rules+58 },
             { lang.atoms+11 , lang.rules+58 },
             { lang.atoms+20 , lang.rules+58 },
             { lang.atoms+41 , lang.rules+58 }
            }
    },
    { 179 ,
            {
             { lang.atoms+1 , lang.rules+73 },
             { lang.atoms+4 , lang.rules+73 },
             { lang.atoms+5 , lang.rules+73 },
             { lang.atoms+6 , lang.rules+73 },
             { lang.atoms+8 , lang.rules+73 },
             { lang.atoms+9 , lang.rules+73 },
             { lang.atoms+10 , lang.rules+73 },
             { lang.atoms+11 , lang.rules+73 },
             { lang.atoms+19 , lang.rules+73 },
             { lang.atoms+41 , lang.rules+73 }
            }
    },
    { 180 ,
            {
             { lang.atoms+1 , lang.rules+73 },
             { lang.atoms+5 , lang.rules+73 },
             { lang.atoms+6 , lang.rules+73 },
             { lang.atoms+7 , lang.rules+73 },
             { lang.atoms+8 , lang.rules+73 },
             { lang.atoms+9 , lang.rules+73 },
             { lang.atoms+10 , lang.rules+73 },
             { lang.atoms+11 , lang.rules+73 },
             { lang.atoms+19 , lang.rules+73 },
             { lang.atoms+41 , lang.rules+73 },
             { lang.atoms+42 , lang.rules+73 }
            }
    },
    { 181 ,
            {
             { lang.atoms+1 , lang.rules+73 },
             { lang.atoms+5 , lang.rules+73 },
             { lang.atoms+6 , lang.rules+73 },
             { lang.atoms+8 , lang.rules+73 },
             { lang.atoms+9 , lang.rules+73 },
             { lang.atoms+10 , lang.rules+73 },
             { lang.atoms+11 , lang.rules+73 },
             { lang.atoms+12 , lang.rules+73 },
             { lang.atoms+19 , lang.rules+73 },
             { lang.atoms+41 , lang.rules+73 }
            }
    },
    { 182 ,
            {
             { lang.atoms+1 , lang.rules+73 },
             { lang.atoms+5 , lang.rules+73 },
             { lang.atoms+6 , lang.rules+73 },
             { lang.atoms+8 , lang.rules+73 },
             { lang.atoms+9 , lang.rules+73 },
             { lang.atoms+10 , lang.rules+73 },
             { lang.atoms+11 , lang.rules+73 },
             { lang.atoms+19 , lang.rules+73 },
             { lang.atoms+20 , lang.rules+73 },
             { lang.atoms+41 , lang.rules+73 }
            }
    },
    { 183 ,
            {
             { lang.atoms+1 , lang.rules+74 },
             { lang.atoms+4 , lang.rules+74 },
             { lang.atoms+5 , lang.rules+74 },
             { lang.atoms+6 , lang.rules+74 },
             { lang.atoms+8 , lang.rules+74 },
             { lang.atoms+9 , lang.rules+74 },
             { lang.atoms+10 , lang.rules+74 },
             { lang.atoms+11 , lang.rules+74 },
             { lang.atoms+19 , lang.rules+74 },
             { lang.atoms+41 , lang.rules+74 }
            }
    },
    { 184 ,
            {
             { lang.atoms+1 , lang.rules+74 },
             { lang.atoms+5 , lang.rules+74 },
             { lang.atoms+6 , lang.rules+74 },
             { lang.atoms+7 , lang.rules+74 },
             { lang.atoms+8 , lang.rules+74 },
             { lang.atoms+9 , lang.rules+74 },
             { lang.atoms+10 , lang.rules+74 },
             { lang.atoms+11 , lang.rules+74 },
             { lang.atoms+19 , lang.rules+74 },
             { lang.atoms+41 , lang.rules+74 },
             { lang.atoms+42 , lang.rules+74 }
            }
    },
    { 185 ,
            {
             { lang.atoms+1 , lang.rules+74 },
             { lang.atoms+5 , lang.rules+74 },
             { lang.atoms+6 , lang.rules+74 },
             { lang.atoms+8 , lang.rules+74 },
             { lang.atoms+9 , lang.rules+74 },
             { lang.atoms+10 , lang.rules+74 },
             { lang.atoms+11 , lang.rules+74 },
             { lang.atoms+12 , lang.rules+74 },
             { lang.atoms+19 , lang.rules+74 },
             { lang.atoms+41 , lang.rules+74 }
            }
    },
    { 186 ,
            {
             { lang.atoms+1 , lang.rules+74 },
             { lang.atoms+5 , lang.rules+74 },
             { lang.atoms+6 , lang.rules+74 },
             { lang.atoms+8 , lang.rules+74 },
             { lang.atoms+9 , lang.rules+74 },
             { lang.atoms+10 , lang.rules+74 },
             { lang.atoms+11 , lang.rules+74 },
             { lang.atoms+19 , lang.rules+74 },
             { lang.atoms+20 , lang.rules+74 },
             { lang.atoms+41 , lang.rules+74 }
            }
    },
    { 187 ,
            {
             { lang.atoms+1 , lang.rules+75 },
             { lang.atoms+4 , lang.rules+75 },
             { lang.atoms+5 , lang.rules+75 },
             { lang.atoms+6 , lang.rules+75 },
             { lang.atoms+8 , lang.rules+75 },
             { lang.atoms+9 , lang.rules+75 },
             { lang.atoms+10 , lang.rules+75 },
             { lang.atoms+11 , lang.rules+75 },
             { lang.atoms+19 , lang.rules+75 },
             { lang.atoms+41 , lang.rules+75 }
            }
    },
    { 188 ,
            {
             { lang.atoms+1 , lang.rules+75 },
             { lang.atoms+5 , lang.rules+75 },
             { lang.atoms+6 , lang.rules+75 },
             { lang.atoms+7 , lang.rules+75 },
             { lang.atoms+8 , lang.rules+75 },
             { lang.atoms+9 , lang.rules+75 },
             { lang.atoms+10 , lang.rules+75 },
             { lang.atoms+11 , lang.rules+75 },
             { lang.atoms+19 , lang.rules+75 },
             { lang.atoms+41 , lang.rules+75 },
             { lang.atoms+42 , lang.rules+75 }
            }
    },
    { 189 ,
            {
             { lang.atoms+1 , lang.rules+75 },
             { lang.atoms+5 , lang.rules+75 },
             { lang.atoms+6 , lang.rules+75 },
             { lang.atoms+8 , lang.rules+75 },
             { lang.atoms+9 , lang.rules+75 },
             { lang.atoms+10 , lang.rules+75 },
             { lang.atoms+11 , lang.rules+75 },
             { lang.atoms+12 , lang.rules+75 },
             { lang.atoms+19 , lang.rules+75 },
             { lang.atoms+41 , lang.rules+75 }
            }
    },
    { 190 ,
            {
             { lang.atoms+1 , lang.rules+75 },
             { lang.atoms+5 , lang.rules+75 },
             { lang.atoms+6 , lang.rules+75 },
             { lang.atoms+8 , lang.rules+75 },
             { lang.atoms+9 , lang.rules+75 },
             { lang.atoms+10 , lang.rules+75 },
             { lang.atoms+11 , lang.rules+75 },
             { lang.atoms+19 , lang.rules+75 },
             { lang.atoms+20 , lang.rules+75 },
             { lang.atoms+41 , lang.rules+75 }
            }
    },
    { 191 ,
            {
             { lang.atoms+1 , null },
             { lang.atoms+4 , lang.rules+59 },
             { lang.atoms+5 , null },
             { lang.atoms+6 , lang.rules+59 },
             { lang.atoms+8 , lang.rules+59 },
             { lang.atoms+9 , null },
             { lang.atoms+10 , null },
             { lang.atoms+11 , null },
             { lang.atoms+19 , null },
             { lang.atoms+41 , lang.rules+59 }
            }
    },
    { 192 ,
            {
             { lang.atoms+1 , null },
             { lang.atoms+4 , lang.rules+59 },
             { lang.atoms+5 , null },
             { lang.atoms+6 , lang.rules+59 },
             { lang.atoms+8 , lang.rules+59 },
             { lang.atoms+11 , null },
             { lang.atoms+19 , null },
             { lang.atoms+41 , lang.rules+59 }
            }
    },
    { 193 ,
            {
             { lang.atoms+1 , null },
             { lang.atoms+4 , lang.rules+59 },
             { lang.atoms+5 , null },
             { lang.atoms+6 , lang.rules+59 },
             { lang.atoms+8 , lang.rules+59 },
             { lang.atoms+11 , null },
             { lang.atoms+41 , lang.rules+59 }
            }
    },
    { 194 ,
            {
             { lang.atoms+1 , null },
             { lang.atoms+4 , lang.rules+60 },
             { lang.atoms+5 , null },
             { lang.atoms+6 , lang.rules+60 },
             { lang.atoms+8 , lang.rules+60 },
             { lang.atoms+9 , null },
             { lang.atoms+10 , null },
             { lang.atoms+11 , null },
             { lang.atoms+19 , null },
             { lang.atoms+41 , lang.rules+60 }
            }
    },
    { 195 ,
            {
             { lang.atoms+1 , null },
             { lang.atoms+4 , lang.rules+60 },
             { lang.atoms+5 , null },
             { lang.atoms+6 , lang.rules+60 },
             { lang.atoms+8 , lang.rules+60 },
             { lang.atoms+11 , null },
             { lang.atoms+19 , null },
             { lang.atoms+41 , lang.rules+60 }
            }
    },
    { 196 ,
            {
             { lang.atoms+1 , null },
             { lang.atoms+4 , lang.rules+60 },
             { lang.atoms+5 , null },
             { lang.atoms+6 , lang.rules+60 },
             { lang.atoms+8 , lang.rules+60 },
             { lang.atoms+11 , null },
             { lang.atoms+41 , lang.rules+60 }
            }
    },
    { 197 ,
            {
             { lang.atoms+1 , null },
             { lang.atoms+4 , null },
             { lang.atoms+5 , null },
             { lang.atoms+6 , null },
             { lang.atoms+8 , null },
             { lang.atoms+9 , null },
             { lang.atoms+10 , null },
             { lang.atoms+11 , null },
             { lang.atoms+19 , null },
             { lang.atoms+41 , null }
            }
    },
    { 198 ,
            {
             { lang.atoms+1 , null },
             { lang.atoms+4 , null },
             { lang.atoms+5 , null },
             { lang.atoms+6 , null },
             { lang.atoms+8 , null },
             { lang.atoms+11 , null },
             { lang.atoms+19 , null },
             { lang.atoms+41 , null }
            }
    },
    { 199 ,
            {
             { lang.atoms+1 , null },
             { lang.atoms+4 , null },
             { lang.atoms+5 , null },
             { lang.atoms+6 , null },
             { lang.atoms+8 , null },
             { lang.atoms+11 , null },
             { lang.atoms+41 , null }
            }
    },
    { 200 ,
            {
             { lang.atoms+1 , null },
             { lang.atoms+5 , null },
             { lang.atoms+6 , lang.rules+59 },
             { lang.atoms+7 , lang.rules+59 },
             { lang.atoms+8 , lang.rules+59 },
             { lang.atoms+9 , null },
             { lang.atoms+10 , null },
             { lang.atoms+11 , null },
             { lang.atoms+19 , null },
             { lang.atoms+41 , lang.rules+59 },
             { lang.atoms+42 , lang.rules+59 }
            }
    },
    { 201 ,
            {
             { lang.atoms+1 , null },
             { lang.atoms+5 , null },
             { lang.atoms+6 , lang.rules+59 },
             { lang.atoms+7 , lang.rules+59 },
             { lang.atoms+8 , lang.rules+59 },
             { lang.atoms+11 , null },
             { lang.atoms+19 , null },
             { lang.atoms+41 , lang.rules+59 },
             { lang.atoms+42 , lang.rules+59 }
            }
    },
    { 202 ,
            {
             { lang.atoms+1 , null },
             { lang.atoms+5 , null },
             { lang.atoms+6 , lang.rules+59 },
             { lang.atoms+7 , lang.rules+59 },
             { lang.atoms+8 , lang.rules+59 },
             { lang.atoms+11 , null },
             { lang.atoms+41 , lang.rules+59 },
             { lang.atoms+42 , lang.rules+59 }
            }
    },
    { 203 ,
            {
             { lang.atoms+1 , null },
             { lang.atoms+5 , null },
             { lang.atoms+6 , lang.rules+59 },
             { lang.atoms+8 , lang.rules+59 },
             { lang.atoms+9 , null },
             { lang.atoms+10 , null },
             { lang.atoms+11 , null },
             { lang.atoms+12 , lang.rules+59 },
             { lang.atoms+19 , null },
             { lang.atoms+41 , lang.rules+59 }
            }
    },
    { 204 ,
            {
             { lang.atoms+1 , null },
             { lang.atoms+5 , null },
             { lang.atoms+6 , lang.rules+59 },
             { lang.atoms+8 , lang.rules+59 },
             { lang.atoms+9 , null },
             { lang.atoms+10 , null },
             { lang.atoms+11 , null },
             { lang.atoms+19 , null },
             { lang.atoms+20 , lang.rules+59 },
             { lang.atoms+41 , lang.rules+59 }
            }
    },
    { 205 ,
            {
             { lang.atoms+1 , null },
             { lang.atoms+5 , null },
             { lang.atoms+6 , lang.rules+59 },
             { lang.atoms+8 , lang.rules+59 },
             { lang.atoms+11 , null },
             { lang.atoms+12 , lang.rules+59 },
             { lang.atoms+19 , null },
             { lang.atoms+41 , lang.rules+59 }
            }
    },
    { 206 ,
            {
             { lang.atoms+1 , null },
             { lang.atoms+5 , null },
             { lang.atoms+6 , lang.rules+59 },
             { lang.atoms+8 , lang.rules+59 },
             { lang.atoms+11 , null },
             { lang.atoms+12 , lang.rules+59 },
             { lang.atoms+41 , lang.rules+59 }
            }
    },
    { 207 ,
            {
             { lang.atoms+1 , null },
             { lang.atoms+5 , null },
             { lang.atoms+6 , lang.rules+59 },
             { lang.atoms+8 , lang.rules+59 },
             { lang.atoms+11 , null },
             { lang.atoms+19 , null },
             { lang.atoms+20 , lang.rules+59 },
             { lang.atoms+41 , lang.rules+59 }
            }
    },
    { 208 ,
            {
             { lang.atoms+1 , null },
             { lang.atoms+5 , null },
             { lang.atoms+6 , lang.rules+59 },
             { lang.atoms+8 , lang.rules+59 },
             { lang.atoms+11 , null },
             { lang.atoms+20 , lang.rules+59 },
             { lang.atoms+41 , lang.rules+59 }
            }
    },
    { 209 ,
            {
             { lang.atoms+1 , null },
             { lang.atoms+5 , null },
             { lang.atoms+6 , lang.rules+60 },
             { lang.atoms+7 , lang.rules+60 },
             { lang.atoms+8 , lang.rules+60 },
             { lang.atoms+9 , null },
             { lang.atoms+10 , null },
             { lang.atoms+11 , null },
             { lang.atoms+19 , null },
             { lang.atoms+41 , lang.rules+60 },
             { lang.atoms+42 , lang.rules+60 }
            }
    },
    { 210 ,
            {
             { lang.atoms+1 , null },
             { lang.atoms+5 , null },
             { lang.atoms+6 , lang.rules+60 },
             { lang.atoms+7 , lang.rules+60 },
             { lang.atoms+8 , lang.rules+60 },
             { lang.atoms+11 , null },
             { lang.atoms+19 , null },
             { lang.atoms+41 , lang.rules+60 },
             { lang.atoms+42 , lang.rules+60 }
            }
    },
    { 211 ,
            {
             { lang.atoms+1 , null },
             { lang.atoms+5 , null },
             { lang.atoms+6 , lang.rules+60 },
             { lang.atoms+7 , lang.rules+60 },
             { lang.atoms+8 , lang.rules+60 },
             { lang.atoms+11 , null },
             { lang.atoms+41 , lang.rules+60 },
             { lang.atoms+42 , lang.rules+60 }
            }
    },
    { 212 ,
            {
             { lang.atoms+1 , null },
             { lang.atoms+5 , null },
             { lang.atoms+6 , lang.rules+60 },
             { lang.atoms+8 , lang.rules+60 },
             { lang.atoms+9 , null },
             { lang.atoms+10 , null },
             { lang.atoms+11 , null },
             { lang.atoms+12 , lang.rules+60 },
             { lang.atoms+19 , null },
             { lang.atoms+41 , lang.rules+60 }
            }
    },
    { 213 ,
            {
             { lang.atoms+1 , null },
             { lang.atoms+5 , null },
             { lang.atoms+6 , lang.rules+60 },
             { lang.atoms+8 , lang.rules+60 },
             { lang.atoms+9 , null },
             { lang.atoms+10 , null },
             { lang.atoms+11 , null },
             { lang.atoms+19 , null },
             { lang.atoms+20 , lang.rules+60 },
             { lang.atoms+41 , lang.rules+60 }
            }
    },
    { 214 ,
            {
             { lang.atoms+1 , null },
             { lang.atoms+5 , null },
             { lang.atoms+6 , lang.rules+60 },
             { lang.atoms+8 , lang.rules+60 },
             { lang.atoms+11 , null },
             { lang.atoms+12 , lang.rules+60 },
             { lang.atoms+19 , null },
             { lang.atoms+41 , lang.rules+60 }
            }
    },
    { 215 ,
            {
             { lang.atoms+1 , null },
             { lang.atoms+5 , null },
             { lang.atoms+6 , lang.rules+60 },
             { lang.atoms+8 , lang.rules+60 },
             { lang.atoms+11 , null },
             { lang.atoms+12 , lang.rules+60 },
             { lang.atoms+41 , lang.rules+60 }
            }
    },
    { 216 ,
            {
             { lang.atoms+1 , null },
             { lang.atoms+5 , null },
             { lang.atoms+6 , lang.rules+60 },
             { lang.atoms+8 , lang.rules+60 },
             { lang.atoms+11 , null },
             { lang.atoms+19 , null },
             { lang.atoms+20 , lang.rules+60 },
             { lang.atoms+41 , lang.rules+60 }
            }
    },
    { 217 ,
            {
             { lang.atoms+1 , null },
             { lang.atoms+5 , null },
             { lang.atoms+6 , lang.rules+60 },
             { lang.atoms+8 , lang.rules+60 },
             { lang.atoms+11 , null },
             { lang.atoms+20 , lang.rules+60 },
             { lang.atoms+41 , lang.rules+60 }
            }
    },
    { 218 ,
            {
             { lang.atoms+1 , null },
             { lang.atoms+5 , null },
             { lang.atoms+6 , null },
             { lang.atoms+7 , lang.rules+66 },
             { lang.atoms+8 , null },
             { lang.atoms+9 , null },
             { lang.atoms+10 , null },
             { lang.atoms+11 , null },
             { lang.atoms+19 , null },
             { lang.atoms+41 , null },
             { lang.atoms+42 , lang.rules+66 }
            }
    },
    { 219 ,
            {
             { lang.atoms+1 , null },
             { lang.atoms+5 , null },
             { lang.atoms+6 , null },
             { lang.atoms+7 , lang.rules+66 },
             { lang.atoms+8 , null },
             { lang.atoms+11 , null },
             { lang.atoms+19 , null },
             { lang.atoms+41 , null },
             { lang.atoms+42 , lang.rules+66 }
            }
    },
    { 220 ,
            {
             { lang.atoms+1 , null },
             { lang.atoms+5 , null },
             { lang.atoms+6 , null },
             { lang.atoms+7 , lang.rules+66 },
             { lang.atoms+8 , null },
             { lang.atoms+11 , null },
             { lang.atoms+41 , null },
             { lang.atoms+42 , lang.rules+66 }
            }
    },
    { 221 ,
            {
             { lang.atoms+1 , null },
             { lang.atoms+5 , null },
             { lang.atoms+6 , null },
             { lang.atoms+7 , lang.rules+67 },
             { lang.atoms+8 , null },
             { lang.atoms+9 , null },
             { lang.atoms+10 , null },
             { lang.atoms+11 , null },
             { lang.atoms+19 , null },
             { lang.atoms+41 , null },
             { lang.atoms+42 , lang.rules+67 }
            }
    },
    { 222 ,
            {
             { lang.atoms+1 , null },
             { lang.atoms+5 , null },
             { lang.atoms+6 , null },
             { lang.atoms+7 , lang.rules+67 },
             { lang.atoms+8 , null },
             { lang.atoms+11 , null },
             { lang.atoms+19 , null },
             { lang.atoms+41 , null },
             { lang.atoms+42 , lang.rules+67 }
            }
    },
    { 223 ,
            {
             { lang.atoms+1 , null },
             { lang.atoms+5 , null },
             { lang.atoms+6 , null },
             { lang.atoms+7 , lang.rules+67 },
             { lang.atoms+8 , null },
             { lang.atoms+11 , null },
             { lang.atoms+41 , null },
             { lang.atoms+42 , lang.rules+67 }
            }
    },
    { 224 ,
            {
             { lang.atoms+1 , null },
             { lang.atoms+5 , null },
             { lang.atoms+6 , null },
             { lang.atoms+7 , lang.rules+68 },
             { lang.atoms+8 , null },
             { lang.atoms+9 , null },
             { lang.atoms+10 , null },
             { lang.atoms+11 , null },
             { lang.atoms+19 , null },
             { lang.atoms+41 , null },
             { lang.atoms+42 , lang.rules+68 }
            }
    },
    { 225 ,
            {
             { lang.atoms+1 , null },
             { lang.atoms+5 , null },
             { lang.atoms+6 , null },
             { lang.atoms+7 , lang.rules+68 },
             { lang.atoms+8 , null },
             { lang.atoms+11 , null },
             { lang.atoms+19 , null },
             { lang.atoms+41 , null },
             { lang.atoms+42 , lang.rules+68 }
            }
    },
    { 226 ,
            {
             { lang.atoms+1 , null },
             { lang.atoms+5 , null },
             { lang.atoms+6 , null },
             { lang.atoms+7 , lang.rules+68 },
             { lang.atoms+8 , null },
             { lang.atoms+11 , null },
             { lang.atoms+41 , null },
             { lang.atoms+42 , lang.rules+68 }
            }
    },
    { 227 ,
            {
             { lang.atoms+1 , null },
             { lang.atoms+5 , null },
             { lang.atoms+6 , null },
             { lang.atoms+8 , null },
             { lang.atoms+9 , null },
             { lang.atoms+10 , null },
             { lang.atoms+11 , null },
             { lang.atoms+12 , null },
             { lang.atoms+19 , null },
             { lang.atoms+41 , null }
            }
    },
    { 228 ,
            {
             { lang.atoms+1 , null },
             { lang.atoms+5 , null },
             { lang.atoms+6 , null },
             { lang.atoms+8 , null },
             { lang.atoms+9 , null },
             { lang.atoms+10 , null },
             { lang.atoms+11 , null },
             { lang.atoms+19 , null },
             { lang.atoms+20 , null },
             { lang.atoms+41 , null }
            }
    },
    { 229 ,
            {
             { lang.atoms+1 , null },
             { lang.atoms+5 , null },
             { lang.atoms+6 , null },
             { lang.atoms+8 , null },
             { lang.atoms+11 , null },
             { lang.atoms+12 , null },
             { lang.atoms+19 , null },
             { lang.atoms+41 , null }
            }
    },
    { 230 ,
            {
             { lang.atoms+1 , null },
             { lang.atoms+5 , null },
             { lang.atoms+6 , null },
             { lang.atoms+8 , null },
             { lang.atoms+11 , null },
             { lang.atoms+12 , null },
             { lang.atoms+41 , null }
            }
    },
    { 231 ,
            {
             { lang.atoms+1 , null },
             { lang.atoms+5 , null },
             { lang.atoms+6 , null },
             { lang.atoms+8 , null },
             { lang.atoms+11 , null },
             { lang.atoms+19 , null },
             { lang.atoms+20 , null },
             { lang.atoms+41 , null }
            }
    },
    { 232 ,
            {
             { lang.atoms+1 , null },
             { lang.atoms+5 , null },
             { lang.atoms+6 , null },
             { lang.atoms+8 , null },
             { lang.atoms+11 , null },
             { lang.atoms+20 , null },
             { lang.atoms+41 , null }
            }
    },
    { 233 ,
            {
             { lang.atoms+3 , lang.rules+16 }
            }
    },
    { 234 ,
            {
             { lang.atoms+3 , lang.rules+17 }
            }
    },
    { 235 ,
            {
             { lang.atoms+3 , lang.rules+18 }
            }
    },
    { 236 ,
            {
             { lang.atoms+3 , lang.rules+19 }
            }
    },
    { 237 ,
            {
             { lang.atoms+3 , lang.rules+20 }
            }
    },
    { 238 ,
            {
             { lang.atoms+3 , lang.rules+21 }
            }
    },
    { 239 ,
            {
             { lang.atoms+3 , lang.rules+22 }
            }
    },
    { 240 ,
            {
             { lang.atoms+3 , lang.rules+23 }
            }
    },
    { 241 ,
            {
             { lang.atoms+3 , lang.rules+24 }
            }
    },
    { 242 ,
            {
             { lang.atoms+3 , lang.rules+25 }
            }
    },
    { 243 ,
            {
             { lang.atoms+3 , lang.rules+26 }
            }
    },
    { 244 ,
            {
             { lang.atoms+3 , lang.rules+27 }
            }
    },
    { 245 ,
            {
             { lang.atoms+3 , lang.rules+72 }
            }
    },
    { 246 ,
            {
             { lang.atoms+3 , null }
            }
    },
    { 247 ,
            {
             { lang.atoms+4 , lang.rules+61 },
             { lang.atoms+41 , lang.rules+61 }
            }
    },
    { 248 ,
            {
             { lang.atoms+4 , lang.rules+62 },
             { lang.atoms+41 , lang.rules+62 }
            }
    },
    { 249 ,
            {
             { lang.atoms+4 , lang.rules+63 },
             { lang.atoms+41 , lang.rules+63 }
            }
    },
    { 250 ,
            {
             { lang.atoms+4 , lang.rules+64 },
             { lang.atoms+41 , lang.rules+64 }
            }
    },
    { 251 ,
            {
             { lang.atoms+4 , lang.rules+65 },
             { lang.atoms+41 , lang.rules+65 }
            }
    },
    { 252 ,
            {
             { lang.atoms+4 , null },
             { lang.atoms+6 , null },
             { lang.atoms+8 , null },
             { lang.atoms+41 , null }
            }
    },
    { 253 ,
            {
             { lang.atoms+4 , null },
             { lang.atoms+41 , null }
            }
    },
    { 254 ,
            {
             { lang.atoms+5 , lang.rules+16 },
             { lang.atoms+12 , lang.rules+16 },
             { lang.atoms+19 , lang.rules+16 }
            }
    },
    { 255 ,
            {
             { lang.atoms+5 , lang.rules+16 },
             { lang.atoms+16 , lang.rules+16 },
             { lang.atoms+19 , lang.rules+16 }
            }
    },
    { 256 ,
            {
             { lang.atoms+5 , lang.rules+17 },
             { lang.atoms+12 , lang.rules+17 },
             { lang.atoms+19 , lang.rules+17 }
            }
    },
    { 257 ,
            {
             { lang.atoms+5 , lang.rules+17 },
             { lang.atoms+16 , lang.rules+17 },
             { lang.atoms+19 , lang.rules+17 }
            }
    },
    { 258 ,
            {
             { lang.atoms+5 , lang.rules+18 },
             { lang.atoms+12 , lang.rules+18 },
             { lang.atoms+19 , lang.rules+18 }
            }
    },
    { 259 ,
            {
             { lang.atoms+5 , lang.rules+18 },
             { lang.atoms+16 , lang.rules+18 },
             { lang.atoms+19 , lang.rules+18 }
            }
    },
    { 260 ,
            {
             { lang.atoms+5 , lang.rules+19 },
             { lang.atoms+12 , lang.rules+19 },
             { lang.atoms+19 , lang.rules+19 }
            }
    },
    { 261 ,
            {
             { lang.atoms+5 , lang.rules+19 },
             { lang.atoms+16 , lang.rules+19 },
             { lang.atoms+19 , lang.rules+19 }
            }
    },
    { 262 ,
            {
             { lang.atoms+5 , lang.rules+20 },
             { lang.atoms+12 , lang.rules+20 },
             { lang.atoms+19 , lang.rules+20 }
            }
    },
    { 263 ,
            {
             { lang.atoms+5 , lang.rules+20 },
             { lang.atoms+16 , lang.rules+20 },
             { lang.atoms+19 , lang.rules+20 }
            }
    },
    { 264 ,
            {
             { lang.atoms+5 , lang.rules+21 },
             { lang.atoms+12 , lang.rules+21 },
             { lang.atoms+19 , lang.rules+21 }
            }
    },
    { 265 ,
            {
             { lang.atoms+5 , lang.rules+21 },
             { lang.atoms+16 , lang.rules+21 },
             { lang.atoms+19 , lang.rules+21 }
            }
    },
    { 266 ,
            {
             { lang.atoms+5 , lang.rules+22 },
             { lang.atoms+12 , lang.rules+22 },
             { lang.atoms+19 , lang.rules+22 }
            }
    },
    { 267 ,
            {
             { lang.atoms+5 , lang.rules+22 },
             { lang.atoms+16 , lang.rules+22 },
             { lang.atoms+19 , lang.rules+22 }
            }
    },
    { 268 ,
            {
             { lang.atoms+5 , lang.rules+23 },
             { lang.atoms+12 , lang.rules+23 },
             { lang.atoms+19 , lang.rules+23 }
            }
    },
    { 269 ,
            {
             { lang.atoms+5 , lang.rules+23 },
             { lang.atoms+16 , lang.rules+23 },
             { lang.atoms+19 , lang.rules+23 }
            }
    },
    { 270 ,
            {
             { lang.atoms+5 , lang.rules+24 },
             { lang.atoms+12 , lang.rules+24 },
             { lang.atoms+19 , lang.rules+24 }
            }
    },
    { 271 ,
            {
             { lang.atoms+5 , lang.rules+24 },
             { lang.atoms+16 , lang.rules+24 },
             { lang.atoms+19 , lang.rules+24 }
            }
    },
    { 272 ,
            {
             { lang.atoms+5 , lang.rules+25 },
             { lang.atoms+12 , lang.rules+25 },
             { lang.atoms+19 , lang.rules+25 }
            }
    },
    { 273 ,
            {
             { lang.atoms+5 , lang.rules+25 },
             { lang.atoms+16 , lang.rules+25 },
             { lang.atoms+19 , lang.rules+25 }
            }
    },
    { 274 ,
            {
             { lang.atoms+5 , lang.rules+26 },
             { lang.atoms+12 , lang.rules+26 },
             { lang.atoms+19 , lang.rules+26 }
            }
    },
    { 275 ,
            {
             { lang.atoms+5 , lang.rules+26 },
             { lang.atoms+16 , lang.rules+26 },
             { lang.atoms+19 , lang.rules+26 }
            }
    },
    { 276 ,
            {
             { lang.atoms+5 , lang.rules+27 },
             { lang.atoms+12 , lang.rules+27 },
             { lang.atoms+19 , lang.rules+27 }
            }
    },
    { 277 ,
            {
             { lang.atoms+5 , lang.rules+27 },
             { lang.atoms+16 , lang.rules+27 },
             { lang.atoms+19 , lang.rules+27 }
            }
    },
    { 278 ,
            {
             { lang.atoms+5 , lang.rules+28 },
             { lang.atoms+12 , lang.rules+28 },
             { lang.atoms+19 , lang.rules+28 }
            }
    },
    { 279 ,
            {
             { lang.atoms+5 , lang.rules+28 },
             { lang.atoms+16 , lang.rules+28 },
             { lang.atoms+19 , lang.rules+28 }
            }
    },
    { 280 ,
            {
             { lang.atoms+5 , lang.rules+29 },
             { lang.atoms+12 , lang.rules+29 },
             { lang.atoms+19 , lang.rules+29 }
            }
    },
    { 281 ,
            {
             { lang.atoms+5 , lang.rules+29 },
             { lang.atoms+16 , lang.rules+29 },
             { lang.atoms+19 , lang.rules+29 }
            }
    },
    { 282 ,
            {
             { lang.atoms+5 , lang.rules+30 },
             { lang.atoms+12 , lang.rules+30 },
             { lang.atoms+19 , lang.rules+30 }
            }
    },
    { 283 ,
            {
             { lang.atoms+5 , lang.rules+30 },
             { lang.atoms+16 , lang.rules+30 },
             { lang.atoms+19 , lang.rules+30 }
            }
    },
    { 284 ,
            {
             { lang.atoms+5 , lang.rules+31 },
             { lang.atoms+12 , lang.rules+31 },
             { lang.atoms+19 , lang.rules+31 }
            }
    },
    { 285 ,
            {
             { lang.atoms+5 , lang.rules+31 },
             { lang.atoms+16 , lang.rules+31 },
             { lang.atoms+19 , lang.rules+31 }
            }
    },
    { 286 ,
            {
             { lang.atoms+5 , lang.rules+32 },
             { lang.atoms+12 , lang.rules+32 },
             { lang.atoms+19 , lang.rules+32 }
            }
    },
    { 287 ,
            {
             { lang.atoms+5 , lang.rules+32 },
             { lang.atoms+16 , lang.rules+32 },
             { lang.atoms+19 , lang.rules+32 }
            }
    },
    { 288 ,
            {
             { lang.atoms+5 , lang.rules+33 },
             { lang.atoms+12 , lang.rules+33 },
             { lang.atoms+19 , lang.rules+33 }
            }
    },
    { 289 ,
            {
             { lang.atoms+5 , lang.rules+33 },
             { lang.atoms+16 , lang.rules+33 },
             { lang.atoms+19 , lang.rules+33 }
            }
    },
    { 290 ,
            {
             { lang.atoms+5 , lang.rules+34 },
             { lang.atoms+12 , lang.rules+34 },
             { lang.atoms+19 , lang.rules+34 }
            }
    },
    { 291 ,
            {
             { lang.atoms+5 , lang.rules+34 },
             { lang.atoms+16 , lang.rules+34 },
             { lang.atoms+19 , lang.rules+34 }
            }
    },
    { 292 ,
            {
             { lang.atoms+5 , lang.rules+35 },
             { lang.atoms+12 , lang.rules+35 },
             { lang.atoms+19 , lang.rules+35 }
            }
    },
    { 293 ,
            {
             { lang.atoms+5 , lang.rules+35 },
             { lang.atoms+16 , lang.rules+35 },
             { lang.atoms+19 , lang.rules+35 }
            }
    },
    { 294 ,
            {
             { lang.atoms+5 , lang.rules+36 },
             { lang.atoms+12 , lang.rules+36 },
             { lang.atoms+19 , lang.rules+36 }
            }
    },
    { 295 ,
            {
             { lang.atoms+5 , lang.rules+36 },
             { lang.atoms+12 , null },
             { lang.atoms+16 , lang.rules+36 },
             { lang.atoms+19 , lang.rules+36 }
            }
    },
    { 296 ,
            {
             { lang.atoms+5 , lang.rules+36 },
             { lang.atoms+16 , lang.rules+36 },
             { lang.atoms+19 , lang.rules+36 }
            }
    },
    { 297 ,
            {
             { lang.atoms+5 , lang.rules+37 },
             { lang.atoms+12 , lang.rules+37 },
             { lang.atoms+16 , lang.rules+37 },
             { lang.atoms+19 , lang.rules+37 }
            }
    },
    { 298 ,
            {
             { lang.atoms+5 , lang.rules+37 },
             { lang.atoms+12 , lang.rules+37 },
             { lang.atoms+19 , lang.rules+37 }
            }
    },
    { 299 ,
            {
             { lang.atoms+5 , lang.rules+37 },
             { lang.atoms+16 , lang.rules+37 },
             { lang.atoms+19 , lang.rules+37 }
            }
    },
    { 300 ,
            {
             { lang.atoms+5 , null },
             { lang.atoms+12 , null },
             { lang.atoms+19 , null }
            }
    },
    { 301 ,
            {
             { lang.atoms+5 , null },
             { lang.atoms+16 , null },
             { lang.atoms+19 , null }
            }
    },
    { 302 ,
            {
             { lang.atoms+6 , null },
             { lang.atoms+7 , lang.rules+66 },
             { lang.atoms+8 , null },
             { lang.atoms+41 , null },
             { lang.atoms+42 , lang.rules+66 }
            }
    },
    { 303 ,
            {
             { lang.atoms+6 , null },
             { lang.atoms+7 , lang.rules+67 },
             { lang.atoms+8 , null },
             { lang.atoms+41 , null },
             { lang.atoms+42 , lang.rules+67 }
            }
    },
    { 304 ,
            {
             { lang.atoms+6 , null },
             { lang.atoms+7 , lang.rules+68 },
             { lang.atoms+8 , null },
             { lang.atoms+41 , null },
             { lang.atoms+42 , lang.rules+68 }
            }
    },
    { 305 ,
            {
             { lang.atoms+6 , null },
             { lang.atoms+8 , null },
             { lang.atoms+12 , null },
             { lang.atoms+41 , null }
            }
    },
    { 306 ,
            {
             { lang.atoms+6 , null },
             { lang.atoms+8 , null },
             { lang.atoms+20 , null },
             { lang.atoms+41 , null }
            }
    },
    { 307 ,
            {
             { lang.atoms+7 , lang.rules+61 },
             { lang.atoms+41 , lang.rules+61 },
             { lang.atoms+42 , lang.rules+61 }
            }
    },
    { 308 ,
            {
             { lang.atoms+7 , lang.rules+62 },
             { lang.atoms+41 , lang.rules+62 },
             { lang.atoms+42 , lang.rules+62 }
            }
    },
    { 309 ,
            {
             { lang.atoms+7 , lang.rules+63 },
             { lang.atoms+41 , lang.rules+63 },
             { lang.atoms+42 , lang.rules+63 }
            }
    },
    { 310 ,
            {
             { lang.atoms+7 , lang.rules+64 },
             { lang.atoms+41 , lang.rules+64 },
             { lang.atoms+42 , lang.rules+64 }
            }
    },
    { 311 ,
            {
             { lang.atoms+7 , lang.rules+65 },
             { lang.atoms+41 , lang.rules+65 },
             { lang.atoms+42 , lang.rules+65 }
            }
    },
    { 312 ,
            {
             { lang.atoms+7 , lang.rules+66 },
             { lang.atoms+41 , null },
             { lang.atoms+42 , lang.rules+66 }
            }
    },
    { 313 ,
            {
             { lang.atoms+7 , lang.rules+67 },
             { lang.atoms+41 , null },
             { lang.atoms+42 , lang.rules+67 }
            }
    },
    { 314 ,
            {
             { lang.atoms+7 , lang.rules+68 },
             { lang.atoms+41 , null },
             { lang.atoms+42 , lang.rules+68 }
            }
    },
    { 315 ,
            {
             { lang.atoms+7 , lang.rules+69 },
             { lang.atoms+42 , lang.rules+69 }
            }
    },
    { 316 ,
            {
             { lang.atoms+7 , lang.rules+70 },
             { lang.atoms+42 , lang.rules+70 }
            }
    },
    { 317 ,
            {
             { lang.atoms+7 , null },
             { lang.atoms+42 , null }
            }
    },
    { 318 ,
            {
             { lang.atoms+10 , null }
            }
    },
    { 319 ,
            {
             { lang.atoms+10 , null },
             { lang.atoms+42 , null }
            }
    },
    { 320 ,
            {
             { lang.atoms+12 , lang.rules+61 },
             { lang.atoms+41 , lang.rules+61 }
            }
    },
    { 321 ,
            {
             { lang.atoms+12 , lang.rules+62 },
             { lang.atoms+41 , lang.rules+62 }
            }
    },
    { 322 ,
            {
             { lang.atoms+12 , lang.rules+63 },
             { lang.atoms+41 , lang.rules+63 }
            }
    },
    { 323 ,
            {
             { lang.atoms+12 , lang.rules+64 },
             { lang.atoms+41 , lang.rules+64 }
            }
    },
    { 324 ,
            {
             { lang.atoms+12 , lang.rules+65 },
             { lang.atoms+41 , lang.rules+65 }
            }
    },
    { 325 ,
            {
             { lang.atoms+12 , null },
             { lang.atoms+13 , null }
            }
    },
    { 326 ,
            {
             { lang.atoms+12 , null },
             { lang.atoms+41 , null }
            }
    },
    { 327 ,
            {
             { lang.atoms+13 , null }
            }
    },
    { 328 ,
            {
             { lang.atoms+15 , null }
            }
    },
    { 329 ,
            {
             { lang.atoms+16 , null }
            }
    },
    { 330 ,
            {
             { lang.atoms+17 , null }
            }
    },
    { 331 ,
            {
             { lang.atoms+20 , lang.rules+61 },
             { lang.atoms+41 , lang.rules+61 }
            }
    },
    { 332 ,
            {
             { lang.atoms+20 , lang.rules+62 },
             { lang.atoms+41 , lang.rules+62 }
            }
    },
    { 333 ,
            {
             { lang.atoms+20 , lang.rules+63 },
             { lang.atoms+41 , lang.rules+63 }
            }
    },
    { 334 ,
            {
             { lang.atoms+20 , lang.rules+64 },
             { lang.atoms+41 , lang.rules+64 }
            }
    },
    { 335 ,
            {
             { lang.atoms+20 , lang.rules+65 },
             { lang.atoms+41 , lang.rules+65 }
            }
    },
    { 336 ,
            {
             { lang.atoms+20 , null },
             { lang.atoms+41 , null }
            }
    },
    { 337 ,
            {
             { lang.atoms+41 , null }
            }
    },
    { 338 ,
            {
             { null , lang.rules+0 },
             { lang.atoms+0 , lang.rules+0 },
             { lang.atoms+10 , lang.rules+0 },
             { lang.atoms+14 , lang.rules+0 },
             { lang.atoms+16 , lang.rules+0 },
             { lang.atoms+22 , lang.rules+0 },
             { lang.atoms+23 , lang.rules+0 },
             { lang.atoms+24 , lang.rules+0 },
             { lang.atoms+26 , lang.rules+0 },
             { lang.atoms+27 , lang.rules+0 },
             { lang.atoms+28 , lang.rules+0 },
             { lang.atoms+29 , lang.rules+0 },
             { lang.atoms+30 , lang.rules+0 },
             { lang.atoms+31 , lang.rules+0 },
             { lang.atoms+32 , lang.rules+0 },
             { lang.atoms+33 , lang.rules+0 },
             { lang.atoms+34 , lang.rules+0 },
             { lang.atoms+35 , lang.rules+0 },
             { lang.atoms+36 , lang.rules+0 },
             { lang.atoms+37 , lang.rules+0 },
             { lang.atoms+38 , lang.rules+0 },
             { lang.atoms+39 , lang.rules+0 },
             { lang.atoms+40 , lang.rules+0 }
            }
    },
    { 339 ,
            {
             { null , lang.rules+1 },
             { lang.atoms+0 , lang.rules+1 },
             { lang.atoms+10 , lang.rules+1 },
             { lang.atoms+14 , lang.rules+1 },
             { lang.atoms+16 , lang.rules+1 },
             { lang.atoms+22 , lang.rules+1 },
             { lang.atoms+23 , lang.rules+1 },
             { lang.atoms+24 , lang.rules+1 },
             { lang.atoms+26 , lang.rules+1 },
             { lang.atoms+27 , lang.rules+1 },
             { lang.atoms+28 , lang.rules+1 },
             { lang.atoms+29 , lang.rules+1 },
             { lang.atoms+30 , lang.rules+1 },
             { lang.atoms+31 , lang.rules+1 },
             { lang.atoms+32 , lang.rules+1 },
             { lang.atoms+33 , lang.rules+1 },
             { lang.atoms+34 , lang.rules+1 },
             { lang.atoms+35 , lang.rules+1 },
             { lang.atoms+36 , lang.rules+1 },
             { lang.atoms+37 , lang.rules+1 },
             { lang.atoms+38 , lang.rules+1 },
             { lang.atoms+39 , lang.rules+1 },
             { lang.atoms+40 , lang.rules+1 }
            }
    },
    { 340 ,
            {
             { null , lang.rules+2 },
             { lang.atoms+0 , lang.rules+2 },
             { lang.atoms+10 , lang.rules+2 },
             { lang.atoms+14 , lang.rules+2 },
             { lang.atoms+16 , lang.rules+2 },
             { lang.atoms+22 , lang.rules+2 },
             { lang.atoms+23 , lang.rules+2 },
             { lang.atoms+24 , lang.rules+2 },
             { lang.atoms+26 , lang.rules+2 },
             { lang.atoms+27 , lang.rules+2 },
             { lang.atoms+28 , lang.rules+2 },
             { lang.atoms+29 , lang.rules+2 },
             { lang.atoms+30 , lang.rules+2 },
             { lang.atoms+31 , lang.rules+2 },
             { lang.atoms+32 , lang.rules+2 },
             { lang.atoms+33 , lang.rules+2 },
             { lang.atoms+34 , lang.rules+2 },
             { lang.atoms+35 , lang.rules+2 },
             { lang.atoms+36 , lang.rules+2 },
             { lang.atoms+37 , lang.rules+2 },
             { lang.atoms+38 , lang.rules+2 },
             { lang.atoms+39 , lang.rules+2 },
             { lang.atoms+40 , lang.rules+2 }
            }
    },
    { 341 ,
            {
             { null , lang.rules+3 },
             { lang.atoms+0 , lang.rules+3 },
             { lang.atoms+10 , lang.rules+3 },
             { lang.atoms+14 , lang.rules+3 },
             { lang.atoms+16 , lang.rules+3 },
             { lang.atoms+22 , lang.rules+3 },
             { lang.atoms+23 , lang.rules+3 },
             { lang.atoms+24 , lang.rules+3 },
             { lang.atoms+26 , lang.rules+3 },
             { lang.atoms+27 , lang.rules+3 },
             { lang.atoms+28 , lang.rules+3 },
             { lang.atoms+29 , lang.rules+3 },
             { lang.atoms+30 , lang.rules+3 },
             { lang.atoms+31 , lang.rules+3 },
             { lang.atoms+32 , lang.rules+3 },
             { lang.atoms+33 , lang.rules+3 },
             { lang.atoms+34 , lang.rules+3 },
             { lang.atoms+35 , lang.rules+3 },
             { lang.atoms+36 , lang.rules+3 },
             { lang.atoms+37 , lang.rules+3 },
             { lang.atoms+38 , lang.rules+3 },
             { lang.atoms+39 , lang.rules+3 },
             { lang.atoms+40 , lang.rules+3 }
            }
    },
    { 342 ,
            {
             { null , lang.rules+4 },
             { lang.atoms+0 , lang.rules+4 },
             { lang.atoms+10 , lang.rules+4 },
             { lang.atoms+14 , lang.rules+4 },
             { lang.atoms+16 , lang.rules+4 },
             { lang.atoms+22 , lang.rules+4 },
             { lang.atoms+23 , lang.rules+4 },
             { lang.atoms+24 , lang.rules+4 },
             { lang.atoms+26 , lang.rules+4 },
             { lang.atoms+27 , lang.rules+4 },
             { lang.atoms+28 , lang.rules+4 },
             { lang.atoms+29 , lang.rules+4 },
             { lang.atoms+30 , lang.rules+4 },
             { lang.atoms+31 , lang.rules+4 },
             { lang.atoms+32 , lang.rules+4 },
             { lang.atoms+33 , lang.rules+4 },
             { lang.atoms+34 , lang.rules+4 },
             { lang.atoms+35 , lang.rules+4 },
             { lang.atoms+36 , lang.rules+4 },
             { lang.atoms+37 , lang.rules+4 },
             { lang.atoms+38 , lang.rules+4 },
             { lang.atoms+39 , lang.rules+4 },
             { lang.atoms+40 , lang.rules+4 }
            }
    },
    { 343 ,
            {
             { null , lang.rules+5 },
             { lang.atoms+0 , lang.rules+5 },
             { lang.atoms+10 , lang.rules+5 },
             { lang.atoms+14 , lang.rules+5 },
             { lang.atoms+16 , lang.rules+5 },
             { lang.atoms+22 , lang.rules+5 },
             { lang.atoms+23 , lang.rules+5 },
             { lang.atoms+24 , lang.rules+5 },
             { lang.atoms+26 , lang.rules+5 },
             { lang.atoms+27 , lang.rules+5 },
             { lang.atoms+28 , lang.rules+5 },
             { lang.atoms+29 , lang.rules+5 },
             { lang.atoms+30 , lang.rules+5 },
             { lang.atoms+31 , lang.rules+5 },
             { lang.atoms+32 , lang.rules+5 },
             { lang.atoms+33 , lang.rules+5 },
             { lang.atoms+34 , lang.rules+5 },
             { lang.atoms+35 , lang.rules+5 },
             { lang.atoms+36 , lang.rules+5 },
             { lang.atoms+37 , lang.rules+5 },
             { lang.atoms+38 , lang.rules+5 },
             { lang.atoms+39 , lang.rules+5 },
             { lang.atoms+40 , lang.rules+5 }
            }
    },
    { 344 ,
            {
             { null , lang.rules+6 },
             { lang.atoms+0 , lang.rules+6 },
             { lang.atoms+10 , lang.rules+6 },
             { lang.atoms+14 , lang.rules+6 },
             { lang.atoms+16 , lang.rules+6 },
             { lang.atoms+22 , lang.rules+6 },
             { lang.atoms+23 , lang.rules+6 },
             { lang.atoms+24 , lang.rules+6 },
             { lang.atoms+26 , lang.rules+6 },
             { lang.atoms+27 , lang.rules+6 },
             { lang.atoms+28 , lang.rules+6 },
             { lang.atoms+29 , lang.rules+6 },
             { lang.atoms+30 , lang.rules+6 },
             { lang.atoms+31 , lang.rules+6 },
             { lang.atoms+32 , lang.rules+6 },
             { lang.atoms+33 , lang.rules+6 },
             { lang.atoms+34 , lang.rules+6 },
             { lang.atoms+35 , lang.rules+6 },
             { lang.atoms+36 , lang.rules+6 },
             { lang.atoms+37 , lang.rules+6 },
             { lang.atoms+38 , lang.rules+6 },
             { lang.atoms+39 , lang.rules+6 },
             { lang.atoms+40 , lang.rules+6 }
            }
    },
    { 345 ,
            {
             { null , lang.rules+7 },
             { lang.atoms+0 , lang.rules+7 },
             { lang.atoms+10 , lang.rules+7 },
             { lang.atoms+14 , lang.rules+7 },
             { lang.atoms+16 , lang.rules+7 },
             { lang.atoms+22 , lang.rules+7 },
             { lang.atoms+23 , lang.rules+7 },
             { lang.atoms+24 , lang.rules+7 },
             { lang.atoms+26 , lang.rules+7 },
             { lang.atoms+27 , lang.rules+7 },
             { lang.atoms+28 , lang.rules+7 },
             { lang.atoms+29 , lang.rules+7 },
             { lang.atoms+30 , lang.rules+7 },
             { lang.atoms+31 , lang.rules+7 },
             { lang.atoms+32 , lang.rules+7 },
             { lang.atoms+33 , lang.rules+7 },
             { lang.atoms+34 , lang.rules+7 },
             { lang.atoms+35 , lang.rules+7 },
             { lang.atoms+36 , lang.rules+7 },
             { lang.atoms+37 , lang.rules+7 },
             { lang.atoms+38 , lang.rules+7 },
             { lang.atoms+39 , lang.rules+7 },
             { lang.atoms+40 , lang.rules+7 }
            }
    },
    { 346 ,
            {
             { null , lang.rules+8 },
             { lang.atoms+0 , lang.rules+8 },
             { lang.atoms+10 , lang.rules+8 },
             { lang.atoms+14 , lang.rules+8 },
             { lang.atoms+16 , lang.rules+8 },
             { lang.atoms+22 , lang.rules+8 },
             { lang.atoms+23 , lang.rules+8 },
             { lang.atoms+24 , lang.rules+8 },
             { lang.atoms+26 , lang.rules+8 },
             { lang.atoms+27 , lang.rules+8 },
             { lang.atoms+28 , lang.rules+8 },
             { lang.atoms+29 , lang.rules+8 },
             { lang.atoms+30 , lang.rules+8 },
             { lang.atoms+31 , lang.rules+8 },
             { lang.atoms+32 , lang.rules+8 },
             { lang.atoms+33 , lang.rules+8 },
             { lang.atoms+34 , lang.rules+8 },
             { lang.atoms+35 , lang.rules+8 },
             { lang.atoms+36 , lang.rules+8 },
             { lang.atoms+37 , lang.rules+8 },
             { lang.atoms+38 , lang.rules+8 },
             { lang.atoms+39 , lang.rules+8 },
             { lang.atoms+40 , lang.rules+8 }
            }
    },
    { 347 ,
            {
             { null , lang.rules+9 },
             { lang.atoms+0 , lang.rules+9 },
             { lang.atoms+10 , lang.rules+9 },
             { lang.atoms+14 , lang.rules+9 },
             { lang.atoms+16 , lang.rules+9 },
             { lang.atoms+22 , lang.rules+9 },
             { lang.atoms+23 , lang.rules+9 },
             { lang.atoms+24 , lang.rules+9 },
             { lang.atoms+26 , lang.rules+9 },
             { lang.atoms+27 , lang.rules+9 },
             { lang.atoms+28 , lang.rules+9 },
             { lang.atoms+29 , lang.rules+9 },
             { lang.atoms+30 , lang.rules+9 },
             { lang.atoms+31 , lang.rules+9 },
             { lang.atoms+32 , lang.rules+9 },
             { lang.atoms+33 , lang.rules+9 },
             { lang.atoms+34 , lang.rules+9 },
             { lang.atoms+35 , lang.rules+9 },
             { lang.atoms+36 , lang.rules+9 },
             { lang.atoms+37 , lang.rules+9 },
             { lang.atoms+38 , lang.rules+9 },
             { lang.atoms+39 , lang.rules+9 },
             { lang.atoms+40 , lang.rules+9 }
            }
    },
    { 348 ,
            {
             { null , null },
             { lang.atoms+0 , null },
             { lang.atoms+10 , null },
             { lang.atoms+14 , null },
             { lang.atoms+16 , null },
             { lang.atoms+22 , null },
             { lang.atoms+23 , null },
             { lang.atoms+24 , null },
             { lang.atoms+26 , null },
             { lang.atoms+27 , null },
             { lang.atoms+28 , null },
             { lang.atoms+29 , null },
             { lang.atoms+30 , null },
             { lang.atoms+31 , null },
             { lang.atoms+32 , null },
             { lang.atoms+33 , null },
             { lang.atoms+34 , null },
             { lang.atoms+35 , null },
             { lang.atoms+36 , null },
             { lang.atoms+37 , null },
             { lang.atoms+38 , null },
             { lang.atoms+39 , null },
             { lang.atoms+40 , null }
            }
    }
   }
 };

