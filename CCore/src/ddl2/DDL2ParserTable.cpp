/* DDL2ParserTable.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.07
//
//  Tag: General
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/ddl2/DDL2Parser.h>

namespace CCore {
namespace DDL2 {

/* class Parser */

static uint16 FinalTable[]=
 {
  381,
  0,
  1,
  2,
  3,
  4,
  5,
  6,
  7,
  8,
  9,
  10,
  11,
  12,
  13,
  14,
  15,
  16,
  17,
  18,
  19,
  20,
  21,
  22,
  23,
  24,
  25,
  26,
  27,
  28,
  29,
  30,
  31,
  32,
  33,
  34,
  34,
  34,
  34,
  35,
  36,
  37,
  38,
  39,
  40,
  40,
  40,
  40,
  40,
  40,
  40,
  40,
  40,
  40,
  40,
  40,
  40,
  40,
  41,
  42,
  43,
  44,
  45,
  46,
  47,
  48,
  49,
  50,
  51,
  52,
  53,
  54,
  55,
  56,
  57,
  57,
  57,
  58,
  58,
  58,
  58,
  58,
  58,
  58,
  58,
  58,
  58,
  58,
  58,
  58,
  58,
  58,
  58,
  58,
  58,
  58,
  58,
  58,
  58,
  58,
  58,
  58,
  58,
  58,
  58,
  58,
  58,
  58,
  58,
  58,
  58,
  58,
  58,
  59,
  59,
  59,
  59,
  59,
  59,
  59,
  59,
  59,
  59,
  59,
  59,
  59,
  59,
  59,
  59,
  59,
  59,
  60,
  60,
  60,
  60,
  61,
  62,
  63,
  64,
  65,
  66,
  67,
  68,
  69,
  70,
  71,
  72,
  73,
  73,
  73,
  73,
  74,
  74,
  75,
  75,
  75,
  75,
  75,
  75,
  75,
  75,
  76,
  77,
  78,
  79,
  80,
  81,
  82,
  83,
  84,
  85,
  86,
  87,
  88,
  89,
  90,
  91,
  92,
  93,
  94,
  95,
  96,
  97,
  98,
  99,
  100,
  101,
  102,
  103,
  104,
  105,
  106,
  107,
  108,
  109,
  110,
  111,
  112,
  113,
  114,
  115,
  116,
  117,
  118,
  119,
  120,
  121,
  122,
  123,
  124,
  125,
  126,
  127,
  128,
  129,
  130,
  131,
  132,
  133,
  134,
  135,
  136,
  137,
  138,
  139,
  140,
  141,
  142,
  143,
  144,
  145,
  146,
  147,
  148,
  149,
  150,
  151,
  152,
  153,
  154,
  155,
  156,
  157,
  158,
  159,
  160,
  161,
  162,
  163,
  164,
  165,
  166,
  167,
  168,
  169,
  170,
  171,
  172,
  173,
  174,
  175,
  176,
  177,
  178,
  179,
  180,
  181,
  182,
  183,
  184,
  185,
  186,
  187,
  188,
  189,
  190,
  191,
  192,
  193,
  194,
  195,
  196,
  197,
  198,
  199,
  200,
  201,
  202,
  203,
  204,
  205,
  206,
  207,
  208,
  209,
  210,
  211,
  211,
  211,
  211,
  211,
  211,
  211,
  211,
  212,
  212,
  212,
  212,
  212,
  212,
  212,
  212,
  213,
  213,
  213,
  213,
  213,
  213,
  213,
  213,
  214,
  215,
  216,
  217,
  218,
  219,
  220,
  221,
  222,
  223,
  224,
  225,
  226,
  227,
  228,
  229,
  230,
  231,
  232,
  233,
  234,
  235,
  236,
  237,
  238,
  239,
  240,
  241,
  241,
  241,
  241,
  242,
  242,
  242,
  242,
  242,
  242,
  242,
  243,
  243,
  243,
  243,
  244,
  244,
  244,
  244,
  245,
  245,
  245,
  245,
  245,
  245,
  245,
  246,
  246,
  246,
  246,
  246,
  246,
  246,
  247,
  248,
  249,
  250,
  251,
  252,
  253,
  254,
  255,
  256,
  257,
  258,
  259,
  260,
  260,
  260,
  260,
  261,
  262,
  263,
  264,
  265,
  266,
  266,
  266,
  266,
  266,
  266,
  266,
  266,
  267,
  267,
  267,
  267,
  267,
  267,
  267,
  267,
  268,
  269,
  270,
  271,
  272,
  273,
  274,
  275,
  276,
  277,
  278,
  279,
  280,
  281,
  282,
  283,
  284,
  285,
  286,
  287,
  288,
  289,
  290,
  291,
  292,
  293,
  294,
  295,
  296,
  297,
  298,
  299,
  300,
  301,
  302,
  303,
  304,
  305,
  306,
  307,
  308,
  309,
  310,
  311,
  312,
  313,
  314,
  315,
  316,
  317,
  318,
  319,
  320,
  321,
  322,
  323,
  324,
  325,
  326,
  327,
  328,
  329,
  330,
  331,
  332,
  333,
  333,
  333,
  334,
  335,
  336,
  337,
  338,
  339,
  339,
  339,
  340,
  341,
  342,
  342,
  342,
  343,
  343,
  343,
  343,
  344,
  345,
  346,
  347,
  347,
  347,
  347,
  348,
  348,
  348,
  348,
  348,
  348,
  348,
  349,
  350,
  351,
  352,
  353,
  354,
  355,
  356,
  357,
  358,
  359,
  359,
  359,
  359,
  359,
  359,
  359,
  359,
  359,
  359,
  359,
  359,
  359,
  359,
  359,
  360,
  360,
  360,
  360,
  360,
  360,
  360,
  360,
  360,
  361,
  361,
  361,
  361,
  362,
  363,
  364,
  365,
  366,
  367,
  368,
  368,
  368,
  368,
  369,
  369,
  369,
  369,
  369,
  369,
  369,
  370,
  370,
  371,
  371,
  371,
  371,
  371,
  371,
  371,
  371,
  371,
  371,
  371,
  371,
  371,
  371,
  371,
  371,
  371,
  371,
  371,
  371,
  371,
  371,
  371,
  371,
  371,
  371,
  371,
  371,
  371,
  371,
  372,
  372,
  372,
  372,
  372,
  372,
  372,
  372,
  372,
  372,
  372,
  372,
  372,
  372,
  372,
  372,
  373,
  373,
  373,
  373,
  373,
  373,
  373,
  373,
  373,
  373,
  373,
  373,
  374,
  375,
  376,
  377,
  378,
  379,
  379,
  379,
  379,
  379,
  379,
  379,
  380,
  380,
  380,
  380,
  380,
  380,
  0,
  382,
  383,
  384,
  385,
  386,
  387,
  388,
  389,
  390,
  391
 };

static uint8 RuleResult[]=
 {
  44,
  44,
  44,
  44,
  44,
  44,
  45,
  46,
  47,
  48,
  49,
  49,
  50,
  50,
  50,
  50,
  51,
  51,
  51,
  51,
  52,
  52,
  52,
  52,
  53,
  53,
  53,
  53,
  53,
  53,
  53,
  53,
  53,
  53,
  53,
  53,
  54,
  54,
  54,
  55,
  55,
  55,
  55,
  55,
  55,
  55,
  56,
  56,
  57,
  58,
  58,
  58,
  58,
  58,
  58,
  65,
  65,
  65,
  65,
  64,
  64,
  64,
  63,
  62,
  62,
  62,
  62,
  61,
  61,
  61,
  60,
  60,
  59,
  59,
  59,
  59,
  59,
  66,
  66,
  67,
  68,
  68,
  69,
  69,
  70,
  70,
  70
 };

static int FinalAction(unsigned final,AtomClass ac)
 {
  switch( final )
    {
     case 0 :
       if( 0x1810237FFFD0&(uint64(1)<<ac) ) return 0;
     return -2;

     case 1 :
       if( 0x1810237FFFD0&(uint64(1)<<ac) ) return 1;
     return -2;

     case 2 :
       if( 0x1810237FFFD0&(uint64(1)<<ac) ) return 2;
     return -2;

     case 3 :
       if( 0x1810237FFFD0&(uint64(1)<<ac) ) return 3;
     return -2;

     case 4 :
       if( 0x1810237FFFD0&(uint64(1)<<ac) ) return 4;
     return -2;

     case 5 :
       if( 0x1810237FFFD0&(uint64(1)<<ac) ) return 5;
     return -2;

     case 6 :
       if( 0x1810237FFFD0&(uint64(1)<<ac) ) return 6;
     return -2;

     case 7 :
       if( 0x1810237FFFD0&(uint64(1)<<ac) ) return 7;
     return -2;

     case 8 :
       if( 0x1810247FFFD0&(uint64(1)<<ac) ) return 8;
     return -2;

     case 9 :
       if( 0x1810237FFFD0&(uint64(1)<<ac) ) return 8;
     return -2;

     case 10 :
       if( 0x1810247FFFD0&(uint64(1)<<ac) ) return 9;
     return -2;

     case 11 :
       if( 0x1810237FFFD0&(uint64(1)<<ac) ) return 9;
     return -2;

     case 12 :
       if( 0x121018000000&(uint64(1)<<ac) ) return 10;
     return -2;

     case 13 :
       if( 0x21048000000&(uint64(1)<<ac) ) return 10;
     return -2;

     case 14 :
       if( 0x21008000010&(uint64(1)<<ac) ) return 10;
     return -2;

     case 15 :
       if( 0x121018000000&(uint64(1)<<ac) ) return 11;
     return -2;

     case 16 :
       if( 0x21048000000&(uint64(1)<<ac) ) return 11;
     return -2;

     case 17 :
       if( 0x21008000010&(uint64(1)<<ac) ) return 11;
     return -2;

     case 18 :
       if( 0xBF728000000&(uint64(1)<<ac) ) return 16;
     return -2;

     case 19 :
       if( 0x1AF738000000&(uint64(1)<<ac) ) return 16;
     return -2;

     case 20 :
       if( 0xAF768000000&(uint64(1)<<ac) ) return 16;
     return -2;

     case 21 :
       if( 0xEF728000000&(uint64(1)<<ac) ) return 16;
     return -2;

     case 22 :
       if( 0xBF728000000&(uint64(1)<<ac) ) return 17;
     return -2;

     case 23 :
       if( 0x1AF738000000&(uint64(1)<<ac) ) return 17;
     return -2;

     case 24 :
       if( 0xAF768000000&(uint64(1)<<ac) ) return 17;
     return -2;

     case 25 :
       if( 0xEF728000000&(uint64(1)<<ac) ) return 17;
     return -2;

     case 26 :
       if( 0xBF728000000&(uint64(1)<<ac) ) return 18;
     return -2;

     case 27 :
       if( 0x1AF738000000&(uint64(1)<<ac) ) return 18;
     return -2;

     case 28 :
       if( 0xAF768000000&(uint64(1)<<ac) ) return 18;
     return -2;

     case 29 :
       if( 0xEF728000000&(uint64(1)<<ac) ) return 18;
     return -2;

     case 30 :
       if( 0xBF728000000&(uint64(1)<<ac) ) return 19;
     return -2;

     case 31 :
       if( 0x1AF738000000&(uint64(1)<<ac) ) return 19;
     return -2;

     case 32 :
       if( 0xAF768000000&(uint64(1)<<ac) ) return 19;
     return -2;

     case 33 :
       if( 0xEF728000000&(uint64(1)<<ac) ) return 19;
     return -2;

     case 34 :
       if( 0x1810247FFFD0&(uint64(1)<<ac) ) return 49;
     return -2;

     case 35 :
       if( 0x1810247FFFD0&(uint64(1)<<ac) ) return 50;
     return -2;

     case 36 :
       if( 0x1810247FFFD0&(uint64(1)<<ac) ) return 51;
     return -2;

     case 37 :
       if( 0x1810247FFFD0&(uint64(1)<<ac) ) return 52;
     return -2;

     case 38 :
       if( 0x1810247FFFD0&(uint64(1)<<ac) ) return 53;
     return -2;

     case 39 :
       if( 0x1810247FFFD0&(uint64(1)<<ac) ) return 54;
     return -2;

     case 40 :
       if( 0x1000000000&(uint64(1)<<ac) ) return -1;
     return -2;

     case 41 :
       if( 0x1000000000&(uint64(1)<<ac) ) return -1;
       if( 0xBE728000000&(uint64(1)<<ac) ) return 20;
     return -2;

     case 42 :
       if( 0x1000000000&(uint64(1)<<ac) ) return -1;
       if( 0x1AE738000000&(uint64(1)<<ac) ) return 20;
     return -2;

     case 43 :
       if( 0x1000000000&(uint64(1)<<ac) ) return -1;
       if( 0xAE768000000&(uint64(1)<<ac) ) return 20;
     return -2;

     case 44 :
       if( 0x1000000000&(uint64(1)<<ac) ) return -1;
       if( 0xEE728000000&(uint64(1)<<ac) ) return 20;
     return -2;

     case 45 :
       if( 0x1000000000&(uint64(1)<<ac) ) return -1;
       if( 0xBE728000000&(uint64(1)<<ac) ) return 21;
     return -2;

     case 46 :
       if( 0x1000000000&(uint64(1)<<ac) ) return -1;
       if( 0x1AE738000000&(uint64(1)<<ac) ) return 21;
     return -2;

     case 47 :
       if( 0x1000000000&(uint64(1)<<ac) ) return -1;
       if( 0xAE768000000&(uint64(1)<<ac) ) return 21;
     return -2;

     case 48 :
       if( 0x1000000000&(uint64(1)<<ac) ) return -1;
       if( 0xEE728000000&(uint64(1)<<ac) ) return 21;
     return -2;

     case 49 :
       if( 0x1000000000&(uint64(1)<<ac) ) return -1;
       if( 0xBE728000000&(uint64(1)<<ac) ) return 22;
     return -2;

     case 50 :
       if( 0x1000000000&(uint64(1)<<ac) ) return -1;
       if( 0x1AE738000000&(uint64(1)<<ac) ) return 22;
     return -2;

     case 51 :
       if( 0x1000000000&(uint64(1)<<ac) ) return -1;
       if( 0xAE768000000&(uint64(1)<<ac) ) return 22;
     return -2;

     case 52 :
       if( 0x1000000000&(uint64(1)<<ac) ) return -1;
       if( 0xEE728000000&(uint64(1)<<ac) ) return 22;
     return -2;

     case 53 :
       if( 0x1000000000&(uint64(1)<<ac) ) return -1;
       if( 0xBE728000000&(uint64(1)<<ac) ) return 23;
     return -2;

     case 54 :
       if( 0x1000000000&(uint64(1)<<ac) ) return -1;
       if( 0x1AE738000000&(uint64(1)<<ac) ) return 23;
     return -2;

     case 55 :
       if( 0x1000000000&(uint64(1)<<ac) ) return -1;
       if( 0xAE768000000&(uint64(1)<<ac) ) return 23;
     return -2;

     case 56 :
       if( 0x1000000000&(uint64(1)<<ac) ) return -1;
       if( 0xEE728000000&(uint64(1)<<ac) ) return 23;
     return -2;

     case 57 :
       if( 0xC9E2887FFF6&(uint64(1)<<ac) ) return -1;
     return -2;

     case 58 :
       if( 0x9E2887FFF6&(uint64(1)<<ac) ) return -1;
     return -2;

     case 59 :
       if( 0x89E2887FFF6&(uint64(1)<<ac) ) return -1;
     return -2;

     case 60 :
       if( 0x189E2887FFF6&(uint64(1)<<ac) ) return -1;
     return -2;

     case 61 :
       if( 0x1000000000&(uint64(1)<<ac) ) return -1;
       if( 0x120018000000&(uint64(1)<<ac) ) return 12;
     return -2;

     case 62 :
       if( 0x1000000000&(uint64(1)<<ac) ) return -1;
       if( 0x20048000000&(uint64(1)<<ac) ) return 12;
     return -2;

     case 63 :
       if( 0x1000000000&(uint64(1)<<ac) ) return -1;
       if( 0x20008000010&(uint64(1)<<ac) ) return 12;
     return -2;

     case 64 :
       if( 0x1000000000&(uint64(1)<<ac) ) return -1;
       if( 0x120018000000&(uint64(1)<<ac) ) return 13;
     return -2;

     case 65 :
       if( 0x1000000000&(uint64(1)<<ac) ) return -1;
       if( 0x20048000000&(uint64(1)<<ac) ) return 13;
     return -2;

     case 66 :
       if( 0x1000000000&(uint64(1)<<ac) ) return -1;
       if( 0x20008000010&(uint64(1)<<ac) ) return 13;
     return -2;

     case 67 :
       if( 0x1000000000&(uint64(1)<<ac) ) return -1;
       if( 0x120018000000&(uint64(1)<<ac) ) return 14;
     return -2;

     case 68 :
       if( 0x1000000000&(uint64(1)<<ac) ) return -1;
       if( 0x20048000000&(uint64(1)<<ac) ) return 14;
     return -2;

     case 69 :
       if( 0x1000000000&(uint64(1)<<ac) ) return -1;
       if( 0x20008000010&(uint64(1)<<ac) ) return 14;
     return -2;

     case 70 :
       if( 0x1000000000&(uint64(1)<<ac) ) return -1;
       if( 0x120018000000&(uint64(1)<<ac) ) return 15;
     return -2;

     case 71 :
       if( 0x1000000000&(uint64(1)<<ac) ) return -1;
       if( 0x20048000000&(uint64(1)<<ac) ) return 15;
     return -2;

     case 72 :
       if( 0x1000000000&(uint64(1)<<ac) ) return -1;
       if( 0x20008000010&(uint64(1)<<ac) ) return 15;
     return -2;

     case 73 :
       if( 0x1810247FFFD0&(uint64(1)<<ac) ) return -1;
     return -2;

     case 74 :
       if( 0x1810237FFFD0&(uint64(1)<<ac) ) return -1;
     return -2;

     case 75 :
       if( 0x810203FFFD0&(uint64(1)<<ac) ) return -1;
     return -2;

     case 76 :
       if( 0x1000000010&(uint64(1)<<ac) ) return -1;
     return -2;

     case 77 :
       if( 0xB6728000000&(uint64(1)<<ac) ) return 55;
     return -2;

     case 78 :
       if( 0x1A6738000000&(uint64(1)<<ac) ) return 55;
     return -2;

     case 79 :
       if( 0xA6768000000&(uint64(1)<<ac) ) return 55;
     return -2;

     case 80 :
       if( 0xE6728000000&(uint64(1)<<ac) ) return 55;
     return -2;

     case 81 :
       if( 0xB6728000000&(uint64(1)<<ac) ) return 56;
       if( 0x8000000000&(uint64(1)<<ac) ) return 83;
     return -2;

     case 82 :
       if( 0x1A6738000000&(uint64(1)<<ac) ) return 56;
       if( 0x8000000000&(uint64(1)<<ac) ) return 83;
     return -2;

     case 83 :
       if( 0xA6768000000&(uint64(1)<<ac) ) return 56;
       if( 0x8000000000&(uint64(1)<<ac) ) return 83;
     return -2;

     case 84 :
       if( 0xE6728000000&(uint64(1)<<ac) ) return 56;
       if( 0x8000000000&(uint64(1)<<ac) ) return 83;
     return -2;

     case 85 :
       if( 0xB6728000000&(uint64(1)<<ac) ) return 57;
     return -2;

     case 86 :
       if( 0x1A6738000000&(uint64(1)<<ac) ) return 57;
     return -2;

     case 87 :
       if( 0xA6768000000&(uint64(1)<<ac) ) return 57;
     return -2;

     case 88 :
       if( 0xE6728000000&(uint64(1)<<ac) ) return 57;
     return -2;

     case 89 :
       if( 0xB6728000000&(uint64(1)<<ac) ) return 58;
     return -2;

     case 90 :
       if( 0x1A6738000000&(uint64(1)<<ac) ) return 58;
     return -2;

     case 91 :
       if( 0xA6768000000&(uint64(1)<<ac) ) return 58;
     return -2;

     case 92 :
       if( 0xE6728000000&(uint64(1)<<ac) ) return 58;
     return -2;

     case 93 :
       if( 0xB6728000000&(uint64(1)<<ac) ) return 59;
     return -2;

     case 94 :
       if( 0x1A6738000000&(uint64(1)<<ac) ) return 59;
     return -2;

     case 95 :
       if( 0xA6768000000&(uint64(1)<<ac) ) return 59;
     return -2;

     case 96 :
       if( 0xE6728000000&(uint64(1)<<ac) ) return 59;
     return -2;

     case 97 :
       if( 0xB6728000000&(uint64(1)<<ac) ) return 60;
     return -2;

     case 98 :
       if( 0x1A6738000000&(uint64(1)<<ac) ) return 60;
     return -2;

     case 99 :
       if( 0xA6768000000&(uint64(1)<<ac) ) return 60;
     return -2;

     case 100 :
       if( 0xE6728000000&(uint64(1)<<ac) ) return 60;
     return -2;

     case 101 :
       if( 0xB6728000000&(uint64(1)<<ac) ) return 61;
     return -2;

     case 102 :
       if( 0x1A6738000000&(uint64(1)<<ac) ) return 61;
     return -2;

     case 103 :
       if( 0xA6768000000&(uint64(1)<<ac) ) return 61;
     return -2;

     case 104 :
       if( 0xE6728000000&(uint64(1)<<ac) ) return 61;
     return -2;

     case 105 :
       if( 0x20000000&(uint64(1)<<ac) ) return -1;
       if( 0xB6608000000&(uint64(1)<<ac) ) return 62;
     return -2;

     case 106 :
       if( 0x20000000&(uint64(1)<<ac) ) return -1;
       if( 0x1A6618000000&(uint64(1)<<ac) ) return 62;
     return -2;

     case 107 :
       if( 0x20000000&(uint64(1)<<ac) ) return -1;
       if( 0xA6648000000&(uint64(1)<<ac) ) return 62;
     return -2;

     case 108 :
       if( 0x20000000&(uint64(1)<<ac) ) return -1;
       if( 0xE6608000000&(uint64(1)<<ac) ) return 62;
     return -2;

     case 109 :
       if( 0x20120000000&(uint64(1)<<ac) ) return -1;
       if( 0x96608000000&(uint64(1)<<ac) ) return 63;
     return -2;

     case 110 :
       if( 0x20000000000&(uint64(1)<<ac) ) return -1;
       if( 0x96608000000&(uint64(1)<<ac) ) return 63;
     return -2;

     case 111 :
       if( 0x96608000000&(uint64(1)<<ac) ) return 63;
     return -2;

     case 112 :
       if( 0x20120000000&(uint64(1)<<ac) ) return -1;
       if( 0x186618000000&(uint64(1)<<ac) ) return 63;
     return -2;

     case 113 :
       if( 0x20000000000&(uint64(1)<<ac) ) return -1;
       if( 0x186618000000&(uint64(1)<<ac) ) return 63;
     return -2;

     case 114 :
       if( 0x186618000000&(uint64(1)<<ac) ) return 63;
     return -2;

     case 115 :
       if( 0x20120000000&(uint64(1)<<ac) ) return -1;
       if( 0x86648000000&(uint64(1)<<ac) ) return 63;
     return -2;

     case 116 :
       if( 0x20120000000&(uint64(1)<<ac) ) return -1;
       if( 0xC6608000000&(uint64(1)<<ac) ) return 63;
     return -2;

     case 117 :
       if( 0x20000000000&(uint64(1)<<ac) ) return -1;
       if( 0x86648000000&(uint64(1)<<ac) ) return 63;
     return -2;

     case 118 :
       if( 0x86648000000&(uint64(1)<<ac) ) return 63;
     return -2;

     case 119 :
       if( 0x20000000000&(uint64(1)<<ac) ) return -1;
       if( 0xC6608000000&(uint64(1)<<ac) ) return 63;
     return -2;

     case 120 :
       if( 0xC6608000000&(uint64(1)<<ac) ) return 63;
     return -2;

     case 121 :
       if( 0x20120000000&(uint64(1)<<ac) ) return -1;
       if( 0x96608000000&(uint64(1)<<ac) ) return 64;
     return -2;

     case 122 :
       if( 0x20000000000&(uint64(1)<<ac) ) return -1;
       if( 0x96608000000&(uint64(1)<<ac) ) return 64;
     return -2;

     case 123 :
       if( 0x96608000000&(uint64(1)<<ac) ) return 64;
     return -2;

     case 124 :
       if( 0x20120000000&(uint64(1)<<ac) ) return -1;
       if( 0x186618000000&(uint64(1)<<ac) ) return 64;
     return -2;

     case 125 :
       if( 0x20000000000&(uint64(1)<<ac) ) return -1;
       if( 0x186618000000&(uint64(1)<<ac) ) return 64;
     return -2;

     case 126 :
       if( 0x186618000000&(uint64(1)<<ac) ) return 64;
     return -2;

     case 127 :
       if( 0x20120000000&(uint64(1)<<ac) ) return -1;
       if( 0x86648000000&(uint64(1)<<ac) ) return 64;
     return -2;

     case 128 :
       if( 0x20120000000&(uint64(1)<<ac) ) return -1;
       if( 0xC6608000000&(uint64(1)<<ac) ) return 64;
     return -2;

     case 129 :
       if( 0x20000000000&(uint64(1)<<ac) ) return -1;
       if( 0x86648000000&(uint64(1)<<ac) ) return 64;
     return -2;

     case 130 :
       if( 0x86648000000&(uint64(1)<<ac) ) return 64;
     return -2;

     case 131 :
       if( 0x20000000000&(uint64(1)<<ac) ) return -1;
       if( 0xC6608000000&(uint64(1)<<ac) ) return 64;
     return -2;

     case 132 :
       if( 0xC6608000000&(uint64(1)<<ac) ) return 64;
     return -2;

     case 133 :
       if( 0x20120000000&(uint64(1)<<ac) ) return -1;
       if( 0x96608000000&(uint64(1)<<ac) ) return 65;
     return -2;

     case 134 :
       if( 0x20000000000&(uint64(1)<<ac) ) return -1;
       if( 0x96608000000&(uint64(1)<<ac) ) return 65;
     return -2;

     case 135 :
       if( 0x96608000000&(uint64(1)<<ac) ) return 65;
     return -2;

     case 136 :
       if( 0x20120000000&(uint64(1)<<ac) ) return -1;
       if( 0x186618000000&(uint64(1)<<ac) ) return 65;
     return -2;

     case 137 :
       if( 0x20000000000&(uint64(1)<<ac) ) return -1;
       if( 0x186618000000&(uint64(1)<<ac) ) return 65;
     return -2;

     case 138 :
       if( 0x186618000000&(uint64(1)<<ac) ) return 65;
     return -2;

     case 139 :
       if( 0x20120000000&(uint64(1)<<ac) ) return -1;
       if( 0x86648000000&(uint64(1)<<ac) ) return 65;
     return -2;

     case 140 :
       if( 0x20120000000&(uint64(1)<<ac) ) return -1;
       if( 0xC6608000000&(uint64(1)<<ac) ) return 65;
     return -2;

     case 141 :
       if( 0x20000000000&(uint64(1)<<ac) ) return -1;
       if( 0x86648000000&(uint64(1)<<ac) ) return 65;
     return -2;

     case 142 :
       if( 0x86648000000&(uint64(1)<<ac) ) return 65;
     return -2;

     case 143 :
       if( 0x20000000000&(uint64(1)<<ac) ) return -1;
       if( 0xC6608000000&(uint64(1)<<ac) ) return 65;
     return -2;

     case 144 :
       if( 0xC6608000000&(uint64(1)<<ac) ) return 65;
     return -2;

     case 145 :
       if( 0x20120000000&(uint64(1)<<ac) ) return -1;
       if( 0x96608000000&(uint64(1)<<ac) ) return 66;
     return -2;

     case 146 :
       if( 0x20000000000&(uint64(1)<<ac) ) return -1;
       if( 0x96608000000&(uint64(1)<<ac) ) return 66;
     return -2;

     case 147 :
       if( 0x96608000000&(uint64(1)<<ac) ) return 66;
     return -2;

     case 148 :
       if( 0x20120000000&(uint64(1)<<ac) ) return -1;
       if( 0x186618000000&(uint64(1)<<ac) ) return 66;
     return -2;

     case 149 :
       if( 0x20000000000&(uint64(1)<<ac) ) return -1;
       if( 0x186618000000&(uint64(1)<<ac) ) return 66;
     return -2;

     case 150 :
       if( 0x186618000000&(uint64(1)<<ac) ) return 66;
     return -2;

     case 151 :
       if( 0x20120000000&(uint64(1)<<ac) ) return -1;
       if( 0x86648000000&(uint64(1)<<ac) ) return 66;
     return -2;

     case 152 :
       if( 0x20120000000&(uint64(1)<<ac) ) return -1;
       if( 0xC6608000000&(uint64(1)<<ac) ) return 66;
     return -2;

     case 153 :
       if( 0x20000000000&(uint64(1)<<ac) ) return -1;
       if( 0x86648000000&(uint64(1)<<ac) ) return 66;
     return -2;

     case 154 :
       if( 0x86648000000&(uint64(1)<<ac) ) return 66;
     return -2;

     case 155 :
       if( 0x20000000000&(uint64(1)<<ac) ) return -1;
       if( 0xC6608000000&(uint64(1)<<ac) ) return 66;
     return -2;

     case 156 :
       if( 0xC6608000000&(uint64(1)<<ac) ) return 66;
     return -2;

     case 157 :
       if( 0x20120000000&(uint64(1)<<ac) ) return -1;
       if( 0x96608000000&(uint64(1)<<ac) ) return 67;
     return -2;

     case 158 :
       if( 0x20000000000&(uint64(1)<<ac) ) return -1;
       if( 0x96608000000&(uint64(1)<<ac) ) return 67;
     return -2;

     case 159 :
       if( 0x96608000000&(uint64(1)<<ac) ) return 67;
     return -2;

     case 160 :
       if( 0x20120000000&(uint64(1)<<ac) ) return -1;
       if( 0x186618000000&(uint64(1)<<ac) ) return 67;
     return -2;

     case 161 :
       if( 0x20000000000&(uint64(1)<<ac) ) return -1;
       if( 0x186618000000&(uint64(1)<<ac) ) return 67;
     return -2;

     case 162 :
       if( 0x186618000000&(uint64(1)<<ac) ) return 67;
     return -2;

     case 163 :
       if( 0x20120000000&(uint64(1)<<ac) ) return -1;
       if( 0x86648000000&(uint64(1)<<ac) ) return 67;
     return -2;

     case 164 :
       if( 0x20120000000&(uint64(1)<<ac) ) return -1;
       if( 0xC6608000000&(uint64(1)<<ac) ) return 67;
     return -2;

     case 165 :
       if( 0x20000000000&(uint64(1)<<ac) ) return -1;
       if( 0x86648000000&(uint64(1)<<ac) ) return 67;
     return -2;

     case 166 :
       if( 0x86648000000&(uint64(1)<<ac) ) return 67;
     return -2;

     case 167 :
       if( 0x20000000000&(uint64(1)<<ac) ) return -1;
       if( 0xC6608000000&(uint64(1)<<ac) ) return 67;
     return -2;

     case 168 :
       if( 0xC6608000000&(uint64(1)<<ac) ) return 67;
     return -2;

     case 169 :
       if( 0x20120000000&(uint64(1)<<ac) ) return -1;
       if( 0x96608000000&(uint64(1)<<ac) ) return 68;
     return -2;

     case 170 :
       if( 0x20000000000&(uint64(1)<<ac) ) return -1;
       if( 0x96608000000&(uint64(1)<<ac) ) return 68;
     return -2;

     case 171 :
       if( 0x96608000000&(uint64(1)<<ac) ) return 68;
     return -2;

     case 172 :
       if( 0x20120000000&(uint64(1)<<ac) ) return -1;
       if( 0x186618000000&(uint64(1)<<ac) ) return 68;
     return -2;

     case 173 :
       if( 0x20000000000&(uint64(1)<<ac) ) return -1;
       if( 0x186618000000&(uint64(1)<<ac) ) return 68;
     return -2;

     case 174 :
       if( 0x186618000000&(uint64(1)<<ac) ) return 68;
     return -2;

     case 175 :
       if( 0x20120000000&(uint64(1)<<ac) ) return -1;
       if( 0x86648000000&(uint64(1)<<ac) ) return 68;
     return -2;

     case 176 :
       if( 0x20120000000&(uint64(1)<<ac) ) return -1;
       if( 0xC6608000000&(uint64(1)<<ac) ) return 68;
     return -2;

     case 177 :
       if( 0x20000000000&(uint64(1)<<ac) ) return -1;
       if( 0x86648000000&(uint64(1)<<ac) ) return 68;
     return -2;

     case 178 :
       if( 0x86648000000&(uint64(1)<<ac) ) return 68;
     return -2;

     case 179 :
       if( 0x20000000000&(uint64(1)<<ac) ) return -1;
       if( 0xC6608000000&(uint64(1)<<ac) ) return 68;
     return -2;

     case 180 :
       if( 0xC6608000000&(uint64(1)<<ac) ) return 68;
     return -2;

     case 181 :
       if( 0x20120000000&(uint64(1)<<ac) ) return -1;
       if( 0x96608000000&(uint64(1)<<ac) ) return 69;
     return -2;

     case 182 :
       if( 0x20000000000&(uint64(1)<<ac) ) return -1;
       if( 0x96608000000&(uint64(1)<<ac) ) return 69;
     return -2;

     case 183 :
       if( 0x96608000000&(uint64(1)<<ac) ) return 69;
     return -2;

     case 184 :
       if( 0x20120000000&(uint64(1)<<ac) ) return -1;
       if( 0x186618000000&(uint64(1)<<ac) ) return 69;
     return -2;

     case 185 :
       if( 0x20000000000&(uint64(1)<<ac) ) return -1;
       if( 0x186618000000&(uint64(1)<<ac) ) return 69;
     return -2;

     case 186 :
       if( 0x186618000000&(uint64(1)<<ac) ) return 69;
     return -2;

     case 187 :
       if( 0x20120000000&(uint64(1)<<ac) ) return -1;
       if( 0x86648000000&(uint64(1)<<ac) ) return 69;
     return -2;

     case 188 :
       if( 0x20120000000&(uint64(1)<<ac) ) return -1;
       if( 0xC6608000000&(uint64(1)<<ac) ) return 69;
     return -2;

     case 189 :
       if( 0x20000000000&(uint64(1)<<ac) ) return -1;
       if( 0x86648000000&(uint64(1)<<ac) ) return 69;
     return -2;

     case 190 :
       if( 0x86648000000&(uint64(1)<<ac) ) return 69;
     return -2;

     case 191 :
       if( 0x20000000000&(uint64(1)<<ac) ) return -1;
       if( 0xC6608000000&(uint64(1)<<ac) ) return 69;
     return -2;

     case 192 :
       if( 0xC6608000000&(uint64(1)<<ac) ) return 69;
     return -2;

     case 193 :
       if( 0xB6728000000&(uint64(1)<<ac) ) return 84;
     return -2;

     case 194 :
       if( 0x1A6738000000&(uint64(1)<<ac) ) return 84;
     return -2;

     case 195 :
       if( 0xA6768000000&(uint64(1)<<ac) ) return 84;
     return -2;

     case 196 :
       if( 0xE6728000000&(uint64(1)<<ac) ) return 84;
     return -2;

     case 197 :
       if( 0xB6728000000&(uint64(1)<<ac) ) return 85;
     return -2;

     case 198 :
       if( 0x1A6738000000&(uint64(1)<<ac) ) return 85;
     return -2;

     case 199 :
       if( 0xA6768000000&(uint64(1)<<ac) ) return 85;
     return -2;

     case 200 :
       if( 0xE6728000000&(uint64(1)<<ac) ) return 85;
     return -2;

     case 201 :
       if( 0xB6728000000&(uint64(1)<<ac) ) return 86;
     return -2;

     case 202 :
       if( 0x1A6738000000&(uint64(1)<<ac) ) return 86;
     return -2;

     case 203 :
       if( 0xA6768000000&(uint64(1)<<ac) ) return 86;
     return -2;

     case 204 :
       if( 0xE6728000000&(uint64(1)<<ac) ) return 86;
     return -2;

     case 205 :
       if( 0x26128000000&(uint64(1)<<ac) ) return -1;
       if( 0x90600000000&(uint64(1)<<ac) ) return 70;
     return -2;

     case 206 :
       if( 0x26008000000&(uint64(1)<<ac) ) return -1;
       if( 0x90600000000&(uint64(1)<<ac) ) return 70;
     return -2;

     case 207 :
       if( 0x6008000000&(uint64(1)<<ac) ) return -1;
       if( 0x90600000000&(uint64(1)<<ac) ) return 70;
     return -2;

     case 208 :
       if( 0x26128000000&(uint64(1)<<ac) ) return -1;
       if( 0x90600000000&(uint64(1)<<ac) ) return 71;
     return -2;

     case 209 :
       if( 0x26008000000&(uint64(1)<<ac) ) return -1;
       if( 0x90600000000&(uint64(1)<<ac) ) return 71;
     return -2;

     case 210 :
       if( 0x6008000000&(uint64(1)<<ac) ) return -1;
       if( 0x90600000000&(uint64(1)<<ac) ) return 71;
     return -2;

     case 211 :
       if( 0xB6728000000&(uint64(1)<<ac) ) return -1;
     return -2;

     case 212 :
       if( 0xB6608000000&(uint64(1)<<ac) ) return -1;
     return -2;

     case 213 :
       if( 0x96608000000&(uint64(1)<<ac) ) return -1;
     return -2;

     case 214 :
       if( 0x26128000000&(uint64(1)<<ac) ) return -1;
       if( 0x180610000000&(uint64(1)<<ac) ) return 70;
     return -2;

     case 215 :
       if( 0x26008000000&(uint64(1)<<ac) ) return -1;
       if( 0x180610000000&(uint64(1)<<ac) ) return 70;
     return -2;

     case 216 :
       if( 0x6008000000&(uint64(1)<<ac) ) return -1;
       if( 0x180610000000&(uint64(1)<<ac) ) return 70;
     return -2;

     case 217 :
       if( 0x26128000000&(uint64(1)<<ac) ) return -1;
       if( 0x80640000000&(uint64(1)<<ac) ) return 70;
     return -2;

     case 218 :
       if( 0x26128000000&(uint64(1)<<ac) ) return -1;
       if( 0xC0600000000&(uint64(1)<<ac) ) return 70;
     return -2;

     case 219 :
       if( 0x26008000000&(uint64(1)<<ac) ) return -1;
       if( 0x80640000000&(uint64(1)<<ac) ) return 70;
     return -2;

     case 220 :
       if( 0x6008000000&(uint64(1)<<ac) ) return -1;
       if( 0x80640000000&(uint64(1)<<ac) ) return 70;
     return -2;

     case 221 :
       if( 0x26008000000&(uint64(1)<<ac) ) return -1;
       if( 0xC0600000000&(uint64(1)<<ac) ) return 70;
     return -2;

     case 222 :
       if( 0x6008000000&(uint64(1)<<ac) ) return -1;
       if( 0xC0600000000&(uint64(1)<<ac) ) return 70;
     return -2;

     case 223 :
       if( 0x26128000000&(uint64(1)<<ac) ) return -1;
       if( 0x180610000000&(uint64(1)<<ac) ) return 71;
     return -2;

     case 224 :
       if( 0x26008000000&(uint64(1)<<ac) ) return -1;
       if( 0x180610000000&(uint64(1)<<ac) ) return 71;
     return -2;

     case 225 :
       if( 0x6008000000&(uint64(1)<<ac) ) return -1;
       if( 0x180610000000&(uint64(1)<<ac) ) return 71;
     return -2;

     case 226 :
       if( 0x26128000000&(uint64(1)<<ac) ) return -1;
       if( 0x80640000000&(uint64(1)<<ac) ) return 71;
     return -2;

     case 227 :
       if( 0x26128000000&(uint64(1)<<ac) ) return -1;
       if( 0xC0600000000&(uint64(1)<<ac) ) return 71;
     return -2;

     case 228 :
       if( 0x26008000000&(uint64(1)<<ac) ) return -1;
       if( 0x80640000000&(uint64(1)<<ac) ) return 71;
     return -2;

     case 229 :
       if( 0x6008000000&(uint64(1)<<ac) ) return -1;
       if( 0x80640000000&(uint64(1)<<ac) ) return 71;
     return -2;

     case 230 :
       if( 0x26008000000&(uint64(1)<<ac) ) return -1;
       if( 0xC0600000000&(uint64(1)<<ac) ) return 71;
     return -2;

     case 231 :
       if( 0x6008000000&(uint64(1)<<ac) ) return -1;
       if( 0xC0600000000&(uint64(1)<<ac) ) return 71;
     return -2;

     case 232 :
       if( 0xA6728000000&(uint64(1)<<ac) ) return -1;
       if( 0x100010000000&(uint64(1)<<ac) ) return 77;
     return -2;

     case 233 :
       if( 0xA6608000000&(uint64(1)<<ac) ) return -1;
       if( 0x100010000000&(uint64(1)<<ac) ) return 77;
     return -2;

     case 234 :
       if( 0x86608000000&(uint64(1)<<ac) ) return -1;
       if( 0x100010000000&(uint64(1)<<ac) ) return 77;
     return -2;

     case 235 :
       if( 0xA6728000000&(uint64(1)<<ac) ) return -1;
       if( 0x100010000000&(uint64(1)<<ac) ) return 78;
     return -2;

     case 236 :
       if( 0xA6608000000&(uint64(1)<<ac) ) return -1;
       if( 0x100010000000&(uint64(1)<<ac) ) return 78;
     return -2;

     case 237 :
       if( 0x86608000000&(uint64(1)<<ac) ) return -1;
       if( 0x100010000000&(uint64(1)<<ac) ) return 78;
     return -2;

     case 238 :
       if( 0xA6728000000&(uint64(1)<<ac) ) return -1;
       if( 0x100010000000&(uint64(1)<<ac) ) return 79;
     return -2;

     case 239 :
       if( 0xA6608000000&(uint64(1)<<ac) ) return -1;
       if( 0x100010000000&(uint64(1)<<ac) ) return 79;
     return -2;

     case 240 :
       if( 0x86608000000&(uint64(1)<<ac) ) return -1;
       if( 0x100010000000&(uint64(1)<<ac) ) return 79;
     return -2;

     case 241 :
       if( 0xA6768000000&(uint64(1)<<ac) ) return -1;
     return -2;

     case 242 :
       if( 0xE6728000000&(uint64(1)<<ac) ) return -1;
     return -2;

     case 243 :
       if( 0xA6648000000&(uint64(1)<<ac) ) return -1;
     return -2;

     case 244 :
       if( 0x86648000000&(uint64(1)<<ac) ) return -1;
     return -2;

     case 245 :
       if( 0xE6608000000&(uint64(1)<<ac) ) return -1;
     return -2;

     case 246 :
       if( 0xC6608000000&(uint64(1)<<ac) ) return -1;
     return -2;

     case 247 :
       if( 0x8000000000&(uint64(1)<<ac) ) return 24;
     return -2;

     case 248 :
       if( 0x8000000000&(uint64(1)<<ac) ) return 25;
     return -2;

     case 249 :
       if( 0x8000000000&(uint64(1)<<ac) ) return 26;
     return -2;

     case 250 :
       if( 0x8000000000&(uint64(1)<<ac) ) return 27;
     return -2;

     case 251 :
       if( 0x8000000000&(uint64(1)<<ac) ) return 28;
     return -2;

     case 252 :
       if( 0x8000000000&(uint64(1)<<ac) ) return 29;
     return -2;

     case 253 :
       if( 0x8000000000&(uint64(1)<<ac) ) return 30;
     return -2;

     case 254 :
       if( 0x8000000000&(uint64(1)<<ac) ) return 31;
     return -2;

     case 255 :
       if( 0x8000000000&(uint64(1)<<ac) ) return 32;
     return -2;

     case 256 :
       if( 0x8000000000&(uint64(1)<<ac) ) return 33;
     return -2;

     case 257 :
       if( 0x8000000000&(uint64(1)<<ac) ) return 34;
     return -2;

     case 258 :
       if( 0x8000000000&(uint64(1)<<ac) ) return 35;
     return -2;

     case 259 :
       if( 0x8000000000&(uint64(1)<<ac) ) return 82;
     return -2;

     case 260 :
       if( 0x8000000000&(uint64(1)<<ac) ) return -1;
     return -2;

     case 261 :
       if( 0x90000000000&(uint64(1)<<ac) ) return 72;
     return -2;

     case 262 :
       if( 0x90000000000&(uint64(1)<<ac) ) return 73;
     return -2;

     case 263 :
       if( 0x90000000000&(uint64(1)<<ac) ) return 74;
     return -2;

     case 264 :
       if( 0x90000000000&(uint64(1)<<ac) ) return 75;
     return -2;

     case 265 :
       if( 0x90000000000&(uint64(1)<<ac) ) return 76;
     return -2;

     case 266 :
       if( 0x90600000000&(uint64(1)<<ac) ) return -1;
     return -2;

     case 267 :
       if( 0x90000000000&(uint64(1)<<ac) ) return -1;
     return -2;

     case 268 :
       if( 0x120018000000&(uint64(1)<<ac) ) return 24;
     return -2;

     case 269 :
       if( 0x20048000000&(uint64(1)<<ac) ) return 24;
     return -2;

     case 270 :
       if( 0x20008000010&(uint64(1)<<ac) ) return 24;
     return -2;

     case 271 :
       if( 0x120018000000&(uint64(1)<<ac) ) return 25;
     return -2;

     case 272 :
       if( 0x20048000000&(uint64(1)<<ac) ) return 25;
     return -2;

     case 273 :
       if( 0x20008000010&(uint64(1)<<ac) ) return 25;
     return -2;

     case 274 :
       if( 0x120018000000&(uint64(1)<<ac) ) return 26;
     return -2;

     case 275 :
       if( 0x20048000000&(uint64(1)<<ac) ) return 26;
     return -2;

     case 276 :
       if( 0x20008000010&(uint64(1)<<ac) ) return 26;
     return -2;

     case 277 :
       if( 0x120018000000&(uint64(1)<<ac) ) return 27;
     return -2;

     case 278 :
       if( 0x20048000000&(uint64(1)<<ac) ) return 27;
     return -2;

     case 279 :
       if( 0x20008000010&(uint64(1)<<ac) ) return 27;
     return -2;

     case 280 :
       if( 0x120018000000&(uint64(1)<<ac) ) return 28;
     return -2;

     case 281 :
       if( 0x20048000000&(uint64(1)<<ac) ) return 28;
     return -2;

     case 282 :
       if( 0x20008000010&(uint64(1)<<ac) ) return 28;
     return -2;

     case 283 :
       if( 0x120018000000&(uint64(1)<<ac) ) return 29;
     return -2;

     case 284 :
       if( 0x20048000000&(uint64(1)<<ac) ) return 29;
     return -2;

     case 285 :
       if( 0x20008000010&(uint64(1)<<ac) ) return 29;
     return -2;

     case 286 :
       if( 0x120018000000&(uint64(1)<<ac) ) return 30;
     return -2;

     case 287 :
       if( 0x20048000000&(uint64(1)<<ac) ) return 30;
     return -2;

     case 288 :
       if( 0x20008000010&(uint64(1)<<ac) ) return 30;
     return -2;

     case 289 :
       if( 0x120018000000&(uint64(1)<<ac) ) return 31;
     return -2;

     case 290 :
       if( 0x20048000000&(uint64(1)<<ac) ) return 31;
     return -2;

     case 291 :
       if( 0x20008000010&(uint64(1)<<ac) ) return 31;
     return -2;

     case 292 :
       if( 0x120018000000&(uint64(1)<<ac) ) return 32;
     return -2;

     case 293 :
       if( 0x20048000000&(uint64(1)<<ac) ) return 32;
     return -2;

     case 294 :
       if( 0x20008000010&(uint64(1)<<ac) ) return 32;
     return -2;

     case 295 :
       if( 0x120018000000&(uint64(1)<<ac) ) return 33;
     return -2;

     case 296 :
       if( 0x20048000000&(uint64(1)<<ac) ) return 33;
     return -2;

     case 297 :
       if( 0x20008000010&(uint64(1)<<ac) ) return 33;
     return -2;

     case 298 :
       if( 0x120018000000&(uint64(1)<<ac) ) return 34;
     return -2;

     case 299 :
       if( 0x20048000000&(uint64(1)<<ac) ) return 34;
     return -2;

     case 300 :
       if( 0x20008000010&(uint64(1)<<ac) ) return 34;
     return -2;

     case 301 :
       if( 0x120018000000&(uint64(1)<<ac) ) return 35;
     return -2;

     case 302 :
       if( 0x20048000000&(uint64(1)<<ac) ) return 35;
     return -2;

     case 303 :
       if( 0x20008000010&(uint64(1)<<ac) ) return 35;
     return -2;

     case 304 :
       if( 0x120018000000&(uint64(1)<<ac) ) return 36;
     return -2;

     case 305 :
       if( 0x20048000000&(uint64(1)<<ac) ) return 36;
     return -2;

     case 306 :
       if( 0x20008000010&(uint64(1)<<ac) ) return 36;
     return -2;

     case 307 :
       if( 0x120018000000&(uint64(1)<<ac) ) return 37;
     return -2;

     case 308 :
       if( 0x20048000000&(uint64(1)<<ac) ) return 37;
     return -2;

     case 309 :
       if( 0x20008000010&(uint64(1)<<ac) ) return 37;
     return -2;

     case 310 :
       if( 0x120018000000&(uint64(1)<<ac) ) return 38;
     return -2;

     case 311 :
       if( 0x20048000000&(uint64(1)<<ac) ) return 38;
     return -2;

     case 312 :
       if( 0x20008000010&(uint64(1)<<ac) ) return 38;
     return -2;

     case 313 :
       if( 0x120018000000&(uint64(1)<<ac) ) return 39;
     return -2;

     case 314 :
       if( 0x20048000000&(uint64(1)<<ac) ) return 39;
     return -2;

     case 315 :
       if( 0x20008000010&(uint64(1)<<ac) ) return 39;
     return -2;

     case 316 :
       if( 0x120018000000&(uint64(1)<<ac) ) return 40;
     return -2;

     case 317 :
       if( 0x20048000000&(uint64(1)<<ac) ) return 40;
     return -2;

     case 318 :
       if( 0x20008000010&(uint64(1)<<ac) ) return 40;
     return -2;

     case 319 :
       if( 0x120018000000&(uint64(1)<<ac) ) return 41;
     return -2;

     case 320 :
       if( 0x20048000000&(uint64(1)<<ac) ) return 41;
     return -2;

     case 321 :
       if( 0x20008000010&(uint64(1)<<ac) ) return 41;
     return -2;

     case 322 :
       if( 0x120018000000&(uint64(1)<<ac) ) return 42;
     return -2;

     case 323 :
       if( 0x20048000000&(uint64(1)<<ac) ) return 42;
     return -2;

     case 324 :
       if( 0x20008000010&(uint64(1)<<ac) ) return 42;
     return -2;

     case 325 :
       if( 0x120018000000&(uint64(1)<<ac) ) return 43;
     return -2;

     case 326 :
       if( 0x20048000000&(uint64(1)<<ac) ) return 43;
     return -2;

     case 327 :
       if( 0x20008000010&(uint64(1)<<ac) ) return 43;
     return -2;

     case 328 :
       if( 0x120018000000&(uint64(1)<<ac) ) return 44;
     return -2;

     case 329 :
       if( 0x20048000000&(uint64(1)<<ac) ) return 44;
     return -2;

     case 330 :
       if( 0x20008000010&(uint64(1)<<ac) ) return 44;
     return -2;

     case 331 :
       if( 0x120018000000&(uint64(1)<<ac) ) return 45;
     return -2;

     case 332 :
       if( 0x20048000000&(uint64(1)<<ac) ) return 45;
     return -2;

     case 333 :
       if( 0x40000000&(uint64(1)<<ac) ) return -1;
       if( 0x20008000010&(uint64(1)<<ac) ) return 45;
     return -2;

     case 334 :
       if( 0x20008000010&(uint64(1)<<ac) ) return 45;
     return -2;

     case 335 :
       if( 0x120018000000&(uint64(1)<<ac) ) return 48;
     return -2;

     case 336 :
       if( 0x20048000010&(uint64(1)<<ac) ) return 48;
     return -2;

     case 337 :
       if( 0x20048000000&(uint64(1)<<ac) ) return 48;
     return -2;

     case 338 :
       if( 0x20008000010&(uint64(1)<<ac) ) return 48;
     return -2;

     case 339 :
       if( 0x8000000&(uint64(1)<<ac) ) return -1;
     return -2;

     case 340 :
       if( 0x20008000000&(uint64(1)<<ac) ) return -1;
       if( 0x100010000000&(uint64(1)<<ac) ) return 46;
     return -2;

     case 341 :
       if( 0x20008000000&(uint64(1)<<ac) ) return -1;
       if( 0x100010000000&(uint64(1)<<ac) ) return 47;
     return -2;

     case 342 :
       if( 0x20048000000&(uint64(1)<<ac) ) return -1;
     return -2;

     case 343 :
       if( 0x20008000010&(uint64(1)<<ac) ) return -1;
     return -2;

     case 344 :
       if( 0x80600000000&(uint64(1)<<ac) ) return -1;
       if( 0x100010000000&(uint64(1)<<ac) ) return 77;
     return -2;

     case 345 :
       if( 0x80600000000&(uint64(1)<<ac) ) return -1;
       if( 0x100010000000&(uint64(1)<<ac) ) return 78;
     return -2;

     case 346 :
       if( 0x80600000000&(uint64(1)<<ac) ) return -1;
       if( 0x100010000000&(uint64(1)<<ac) ) return 79;
     return -2;

     case 347 :
       if( 0x80640000000&(uint64(1)<<ac) ) return -1;
     return -2;

     case 348 :
       if( 0xC0600000000&(uint64(1)<<ac) ) return -1;
     return -2;

     case 349 :
       if( 0x180010000000&(uint64(1)<<ac) ) return 72;
     return -2;

     case 350 :
       if( 0x180010000000&(uint64(1)<<ac) ) return 73;
     return -2;

     case 351 :
       if( 0x180010000000&(uint64(1)<<ac) ) return 74;
     return -2;

     case 352 :
       if( 0x180010000000&(uint64(1)<<ac) ) return 75;
     return -2;

     case 353 :
       if( 0x180010000000&(uint64(1)<<ac) ) return 76;
     return -2;

     case 354 :
       if( 0x80000000000&(uint64(1)<<ac) ) return -1;
       if( 0x100010000000&(uint64(1)<<ac) ) return 77;
     return -2;

     case 355 :
       if( 0x80000000000&(uint64(1)<<ac) ) return -1;
       if( 0x100010000000&(uint64(1)<<ac) ) return 78;
     return -2;

     case 356 :
       if( 0x80000000000&(uint64(1)<<ac) ) return -1;
       if( 0x100010000000&(uint64(1)<<ac) ) return 79;
     return -2;

     case 357 :
       if( 0x100010000000&(uint64(1)<<ac) ) return 80;
     return -2;

     case 358 :
       if( 0x100010000000&(uint64(1)<<ac) ) return 81;
     return -2;

     case 359 :
       if( 0x100010000000&(uint64(1)<<ac) ) return -1;
     return -2;

     case 360 :
       if( 0x20000000&(uint64(1)<<ac) ) return -1;
     return -2;

     case 361 :
       if( 0x100020000000&(uint64(1)<<ac) ) return -1;
     return -2;

     case 362 :
       if( 0x80040000000&(uint64(1)<<ac) ) return 72;
     return -2;

     case 363 :
       if( 0x80040000000&(uint64(1)<<ac) ) return 73;
     return -2;

     case 364 :
       if( 0x80040000000&(uint64(1)<<ac) ) return 74;
     return -2;

     case 365 :
       if( 0x80040000000&(uint64(1)<<ac) ) return 75;
     return -2;

     case 366 :
       if( 0x80040000000&(uint64(1)<<ac) ) return 76;
     return -2;

     case 367 :
       if( 0xC0000000&(uint64(1)<<ac) ) return -1;
     return -2;

     case 368 :
       if( 0x80040000000&(uint64(1)<<ac) ) return -1;
     return -2;

     case 369 :
       if( 0x80000000&(uint64(1)<<ac) ) return -1;
     return -2;

     case 370 :
       if( 0x8&(uint64(1)<<ac) ) return -1;
     return -2;

     case 371 :
       if( 0x10&(uint64(1)<<ac) ) return -1;
     return -2;

     case 372 :
       if( 0x30&(uint64(1)<<ac) ) return -1;
     return -2;

     case 373 :
       if( 0x2&(uint64(1)<<ac) ) return -1;
     return -2;

     case 374 :
       if( 0xC0000000000&(uint64(1)<<ac) ) return 72;
     return -2;

     case 375 :
       if( 0xC0000000000&(uint64(1)<<ac) ) return 73;
     return -2;

     case 376 :
       if( 0xC0000000000&(uint64(1)<<ac) ) return 74;
     return -2;

     case 377 :
       if( 0xC0000000000&(uint64(1)<<ac) ) return 75;
     return -2;

     case 378 :
       if( 0xC0000000000&(uint64(1)<<ac) ) return 76;
     return -2;

     case 379 :
       if( 0xC0000000000&(uint64(1)<<ac) ) return -1;
     return -2;

     case 380 :
       if( 0x80000000000&(uint64(1)<<ac) ) return -1;
     return -2;

     case 381 :
       if( 0x810237FFFD1&(uint64(1)<<ac) ) return 0;
     return -2;

     case 382 :
       if( 0x810237FFFD1&(uint64(1)<<ac) ) return 1;
     return -2;

     case 383 :
       if( 0x810237FFFD1&(uint64(1)<<ac) ) return 2;
     return -2;

     case 384 :
       if( 0x810237FFFD1&(uint64(1)<<ac) ) return 3;
     return -2;

     case 385 :
       if( 0x810237FFFD1&(uint64(1)<<ac) ) return 4;
     return -2;

     case 386 :
       if( 0x810237FFFD1&(uint64(1)<<ac) ) return 5;
     return -2;

     case 387 :
       if( 0x810237FFFD1&(uint64(1)<<ac) ) return 6;
     return -2;

     case 388 :
       if( 0x810237FFFD1&(uint64(1)<<ac) ) return 7;
     return -2;

     case 389 :
       if( 0x810237FFFD1&(uint64(1)<<ac) ) return 8;
     return -2;

     case 390 :
       if( 0x810237FFFD1&(uint64(1)<<ac) ) return 9;
     return -2;

     case 391 :
       if( 0x810237FFFD1&(uint64(1)<<ac) ) return -1;
     return -2;

     default: return -2;
    }
 }

Parser::Action::Action(unsigned state,AtomClass ac)
 {
  unsigned final=FinalTable[state];

  int rule=FinalAction(final,ac);

  this->rule=rule;

  if( rule<0 )
    element=0;
  else
    element=RuleResult[rule];
 }

unsigned Parser::Transition(unsigned state,unsigned element)
 {
  switch( state )
    {
     case 0 :
       switch( element )
         {
          case 44 : return 660;
          default: return 0;
         }

     case 1 :
       switch( element )
         {
          case 44 : return 152;
          default: return 0;
         }

     case 2 :
       switch( element )
         {
          default: return 0;
         }

     case 3 :
       switch( element )
         {
          default: return 0;
         }

     case 4 :
       switch( element )
         {
          default: return 0;
         }

     case 5 :
       switch( element )
         {
          default: return 0;
         }

     case 6 :
       switch( element )
         {
          default: return 0;
         }

     case 7 :
       switch( element )
         {
          default: return 0;
         }

     case 8 :
       switch( element )
         {
          default: return 0;
         }

     case 9 :
       switch( element )
         {
          default: return 0;
         }

     case 10 :
       switch( element )
         {
          default: return 0;
         }

     case 11 :
       switch( element )
         {
          default: return 0;
         }

     case 12 :
       switch( element )
         {
          default: return 0;
         }

     case 13 :
       switch( element )
         {
          default: return 0;
         }

     case 14 :
       switch( element )
         {
          default: return 0;
         }

     case 15 :
       switch( element )
         {
          default: return 0;
         }

     case 16 :
       switch( element )
         {
          default: return 0;
         }

     case 17 :
       switch( element )
         {
          default: return 0;
         }

     case 18 :
       switch( element )
         {
          default: return 0;
         }

     case 19 :
       switch( element )
         {
          default: return 0;
         }

     case 20 :
       switch( element )
         {
          default: return 0;
         }

     case 21 :
       switch( element )
         {
          default: return 0;
         }

     case 22 :
       switch( element )
         {
          default: return 0;
         }

     case 23 :
       switch( element )
         {
          default: return 0;
         }

     case 24 :
       switch( element )
         {
          default: return 0;
         }

     case 25 :
       switch( element )
         {
          default: return 0;
         }

     case 26 :
       switch( element )
         {
          default: return 0;
         }

     case 27 :
       switch( element )
         {
          default: return 0;
         }

     case 28 :
       switch( element )
         {
          default: return 0;
         }

     case 29 :
       switch( element )
         {
          default: return 0;
         }

     case 30 :
       switch( element )
         {
          default: return 0;
         }

     case 31 :
       switch( element )
         {
          default: return 0;
         }

     case 32 :
       switch( element )
         {
          default: return 0;
         }

     case 33 :
       switch( element )
         {
          default: return 0;
         }

     case 34 :
       switch( element )
         {
          default: return 0;
         }

     case 35 :
       switch( element )
         {
          case 58 : return 147;
          default: return 0;
         }

     case 36 :
       switch( element )
         {
          case 58 : return 148;
          default: return 0;
         }

     case 37 :
       switch( element )
         {
          case 58 : return 149;
          default: return 0;
         }

     case 38 :
       switch( element )
         {
          case 58 : return 150;
          default: return 0;
         }

     case 39 :
       switch( element )
         {
          default: return 0;
         }

     case 40 :
       switch( element )
         {
          default: return 0;
         }

     case 41 :
       switch( element )
         {
          default: return 0;
         }

     case 42 :
       switch( element )
         {
          default: return 0;
         }

     case 43 :
       switch( element )
         {
          default: return 0;
         }

     case 44 :
       switch( element )
         {
          case 35 : return 575;
          default: return 0;
         }

     case 45 :
       switch( element )
         {
          case 35 : return 576;
          default: return 0;
         }

     case 46 :
       switch( element )
         {
          case 35 : return 578;
          default: return 0;
         }

     case 47 :
       switch( element )
         {
          case 35 : return 579;
          default: return 0;
         }

     case 48 :
       switch( element )
         {
          case 35 : return 581;
          default: return 0;
         }

     case 49 :
       switch( element )
         {
          case 35 : return 582;
          default: return 0;
         }

     case 50 :
       switch( element )
         {
          case 35 : return 605;
          default: return 0;
         }

     case 51 :
       switch( element )
         {
          case 35 : return 606;
          default: return 0;
         }

     case 52 :
       switch( element )
         {
          case 35 : return 608;
          default: return 0;
         }

     case 53 :
       switch( element )
         {
          case 35 : return 609;
          default: return 0;
         }

     case 54 :
       switch( element )
         {
          case 35 : return 611;
          default: return 0;
         }

     case 55 :
       switch( element )
         {
          case 35 : return 612;
          default: return 0;
         }

     case 56 :
       switch( element )
         {
          case 35 : return 614;
          default: return 0;
         }

     case 57 :
       switch( element )
         {
          case 35 : return 615;
          default: return 0;
         }

     case 58 :
       switch( element )
         {
          case 35 : return 616;
          default: return 0;
         }

     case 59 :
       switch( element )
         {
          case 35 : return 617;
          default: return 0;
         }

     case 60 :
       switch( element )
         {
          case 35 : return 618;
          default: return 0;
         }

     case 61 :
       switch( element )
         {
          case 35 : return 619;
          default: return 0;
         }

     case 62 :
       switch( element )
         {
          case 35 : return 616;
          default: return 0;
         }

     case 63 :
       switch( element )
         {
          case 35 : return 617;
          default: return 0;
         }

     case 64 :
       switch( element )
         {
          case 35 : return 618;
          default: return 0;
         }

     case 65 :
       switch( element )
         {
          case 35 : return 619;
          default: return 0;
         }

     case 66 :
       switch( element )
         {
          case 35 : return 616;
          default: return 0;
         }

     case 67 :
       switch( element )
         {
          case 35 : return 617;
          default: return 0;
         }

     case 68 :
       switch( element )
         {
          case 35 : return 618;
          default: return 0;
         }

     case 69 :
       switch( element )
         {
          case 35 : return 619;
          default: return 0;
         }

     case 70 :
       switch( element )
         {
          case 35 : return 616;
          default: return 0;
         }

     case 71 :
       switch( element )
         {
          case 35 : return 617;
          default: return 0;
         }

     case 72 :
       switch( element )
         {
          case 35 : return 618;
          default: return 0;
         }

     case 73 :
       switch( element )
         {
          case 35 : return 619;
          default: return 0;
         }

     case 74 :
       switch( element )
         {
          case 35 : return 613;
          case 34 : return 107;
          case 38 : return 116;
          case 26 : return 106;
          case 32 : return 108;
          case 33 : return 109;
          case 28 : return 56;
          case 5 : return 57;
          case 3 : return 22;
          case 0 : return 193;
          case 4 : return 26;
          case 1 : return 285;
          case 41 : return 475;
          case 6 : return 380;
          case 22 : return 281;
          case 7 : return 381;
          case 11 : return 386;
          case 12 : return 388;
          case 13 : return 390;
          case 10 : return 384;
          case 8 : return 382;
          case 15 : return 387;
          case 16 : return 389;
          case 17 : return 391;
          case 14 : return 385;
          case 9 : return 383;
          case 42 : return 134;
          case 51 : return 61;
          case 52 : return 169;
          case 53 : return 392;
          case 59 : return 641;
          case 60 : return 514;
          case 61 : return 377;
          case 62 : return 377;
          case 63 : return 370;
          case 64 : return 355;
          case 65 : return 355;
          case 69 : return 396;
          case 70 : return 173;
          default: return 0;
         }

     case 75 :
       switch( element )
         {
          case 35 : return 613;
          case 34 : return 107;
          case 38 : return 116;
          case 26 : return 106;
          case 32 : return 108;
          case 33 : return 109;
          case 28 : return 56;
          case 5 : return 57;
          case 3 : return 22;
          case 0 : return 193;
          case 4 : return 26;
          case 1 : return 285;
          case 41 : return 476;
          case 6 : return 380;
          case 22 : return 281;
          case 7 : return 381;
          case 11 : return 386;
          case 12 : return 388;
          case 13 : return 390;
          case 10 : return 384;
          case 8 : return 382;
          case 15 : return 387;
          case 16 : return 389;
          case 17 : return 391;
          case 14 : return 385;
          case 9 : return 383;
          case 42 : return 134;
          case 51 : return 61;
          case 52 : return 169;
          case 53 : return 392;
          case 59 : return 642;
          case 60 : return 515;
          case 61 : return 378;
          case 62 : return 378;
          case 63 : return 371;
          case 64 : return 356;
          case 65 : return 356;
          case 69 : return 396;
          case 70 : return 173;
          default: return 0;
         }

     case 76 :
       switch( element )
         {
          case 35 : return 613;
          case 34 : return 107;
          case 38 : return 116;
          case 26 : return 106;
          case 32 : return 108;
          case 33 : return 109;
          case 28 : return 56;
          case 5 : return 57;
          case 3 : return 22;
          case 0 : return 193;
          case 4 : return 26;
          case 1 : return 285;
          case 41 : return 477;
          case 6 : return 380;
          case 22 : return 281;
          case 7 : return 381;
          case 11 : return 386;
          case 12 : return 388;
          case 13 : return 390;
          case 10 : return 384;
          case 8 : return 382;
          case 15 : return 387;
          case 16 : return 389;
          case 17 : return 391;
          case 14 : return 385;
          case 9 : return 383;
          case 42 : return 134;
          case 51 : return 61;
          case 52 : return 169;
          case 53 : return 392;
          case 59 : return 643;
          case 60 : return 516;
          case 61 : return 379;
          case 62 : return 379;
          case 63 : return 372;
          case 64 : return 357;
          case 65 : return 357;
          case 69 : return 396;
          case 70 : return 173;
          default: return 0;
         }

     case 77 :
       switch( element )
         {
          case 35 : return 604;
          case 34 : return 80;
          case 38 : return 113;
          case 26 : return 79;
          case 32 : return 81;
          case 33 : return 82;
          case 28 : return 50;
          case 5 : return 51;
          case 3 : return 19;
          case 0 : return 190;
          case 4 : return 23;
          case 1 : return 282;
          case 6 : return 380;
          case 22 : return 278;
          case 7 : return 381;
          case 11 : return 386;
          case 12 : return 388;
          case 13 : return 390;
          case 10 : return 384;
          case 8 : return 382;
          case 15 : return 387;
          case 16 : return 389;
          case 17 : return 391;
          case 14 : return 385;
          case 9 : return 383;
          case 51 : return 58;
          case 52 : return 166;
          case 53 : return 392;
          case 61 : return 292;
          case 62 : return 292;
          case 63 : return 291;
          case 64 : return 290;
          case 65 : return 290;
          case 69 : return 393;
          case 70 : return 170;
          default: return 0;
         }

     case 78 :
       switch( element )
         {
          case 35 : return 604;
          case 34 : return 80;
          case 38 : return 113;
          case 26 : return 79;
          case 32 : return 81;
          case 33 : return 82;
          case 28 : return 50;
          case 5 : return 51;
          case 3 : return 19;
          case 0 : return 190;
          case 4 : return 23;
          case 1 : return 282;
          case 6 : return 380;
          case 22 : return 278;
          case 7 : return 381;
          case 11 : return 386;
          case 12 : return 388;
          case 13 : return 390;
          case 10 : return 384;
          case 8 : return 382;
          case 15 : return 387;
          case 16 : return 389;
          case 17 : return 391;
          case 14 : return 385;
          case 9 : return 383;
          case 51 : return 58;
          case 52 : return 166;
          case 53 : return 392;
          case 61 : return 295;
          case 62 : return 295;
          case 63 : return 294;
          case 64 : return 293;
          case 65 : return 293;
          case 69 : return 393;
          case 70 : return 170;
          default: return 0;
         }

     case 79 :
       switch( element )
         {
          case 35 : return 604;
          case 34 : return 80;
          case 38 : return 113;
          case 26 : return 79;
          case 32 : return 81;
          case 33 : return 82;
          case 28 : return 50;
          case 5 : return 51;
          case 3 : return 19;
          case 0 : return 190;
          case 4 : return 23;
          case 1 : return 282;
          case 6 : return 380;
          case 22 : return 278;
          case 7 : return 381;
          case 11 : return 386;
          case 12 : return 388;
          case 13 : return 390;
          case 10 : return 384;
          case 8 : return 382;
          case 15 : return 387;
          case 16 : return 389;
          case 17 : return 391;
          case 14 : return 385;
          case 9 : return 383;
          case 51 : return 58;
          case 52 : return 166;
          case 53 : return 392;
          case 62 : return 196;
          case 63 : return 195;
          case 64 : return 194;
          case 65 : return 194;
          case 69 : return 393;
          case 70 : return 170;
          default: return 0;
         }

     case 80 :
       switch( element )
         {
          case 35 : return 604;
          case 34 : return 80;
          case 38 : return 113;
          case 26 : return 79;
          case 32 : return 81;
          case 33 : return 82;
          case 28 : return 50;
          case 5 : return 51;
          case 3 : return 19;
          case 0 : return 190;
          case 4 : return 23;
          case 1 : return 282;
          case 6 : return 380;
          case 22 : return 278;
          case 7 : return 381;
          case 11 : return 386;
          case 12 : return 388;
          case 13 : return 390;
          case 10 : return 384;
          case 8 : return 382;
          case 15 : return 387;
          case 16 : return 389;
          case 17 : return 391;
          case 14 : return 385;
          case 9 : return 383;
          case 51 : return 58;
          case 52 : return 166;
          case 53 : return 392;
          case 62 : return 208;
          case 63 : return 207;
          case 64 : return 206;
          case 65 : return 206;
          case 69 : return 393;
          case 70 : return 170;
          default: return 0;
         }

     case 81 :
       switch( element )
         {
          case 35 : return 604;
          case 34 : return 80;
          case 38 : return 113;
          case 26 : return 79;
          case 32 : return 81;
          case 33 : return 82;
          case 28 : return 50;
          case 5 : return 51;
          case 3 : return 19;
          case 0 : return 190;
          case 4 : return 23;
          case 1 : return 282;
          case 6 : return 380;
          case 22 : return 278;
          case 7 : return 381;
          case 11 : return 386;
          case 12 : return 388;
          case 13 : return 390;
          case 10 : return 384;
          case 8 : return 382;
          case 15 : return 387;
          case 16 : return 389;
          case 17 : return 391;
          case 14 : return 385;
          case 9 : return 383;
          case 51 : return 58;
          case 52 : return 166;
          case 53 : return 392;
          case 62 : return 220;
          case 63 : return 219;
          case 64 : return 218;
          case 65 : return 218;
          case 69 : return 393;
          case 70 : return 170;
          default: return 0;
         }

     case 82 :
       switch( element )
         {
          case 35 : return 604;
          case 34 : return 80;
          case 38 : return 113;
          case 26 : return 79;
          case 32 : return 81;
          case 33 : return 82;
          case 28 : return 50;
          case 5 : return 51;
          case 3 : return 19;
          case 0 : return 190;
          case 4 : return 23;
          case 1 : return 282;
          case 6 : return 380;
          case 22 : return 278;
          case 7 : return 381;
          case 11 : return 386;
          case 12 : return 388;
          case 13 : return 390;
          case 10 : return 384;
          case 8 : return 382;
          case 15 : return 387;
          case 16 : return 389;
          case 17 : return 391;
          case 14 : return 385;
          case 9 : return 383;
          case 51 : return 58;
          case 52 : return 166;
          case 53 : return 392;
          case 62 : return 232;
          case 63 : return 231;
          case 64 : return 230;
          case 65 : return 230;
          case 69 : return 393;
          case 70 : return 170;
          default: return 0;
         }

     case 83 :
       switch( element )
         {
          case 35 : return 604;
          case 34 : return 80;
          case 38 : return 113;
          case 26 : return 79;
          case 32 : return 81;
          case 33 : return 82;
          case 28 : return 50;
          case 5 : return 51;
          case 3 : return 19;
          case 0 : return 190;
          case 4 : return 23;
          case 1 : return 282;
          case 6 : return 380;
          case 22 : return 278;
          case 7 : return 381;
          case 11 : return 386;
          case 12 : return 388;
          case 13 : return 390;
          case 10 : return 384;
          case 8 : return 382;
          case 15 : return 387;
          case 16 : return 389;
          case 17 : return 391;
          case 14 : return 385;
          case 9 : return 383;
          case 51 : return 58;
          case 52 : return 166;
          case 53 : return 392;
          case 62 : return 244;
          case 63 : return 243;
          case 64 : return 242;
          case 65 : return 242;
          case 69 : return 393;
          case 70 : return 170;
          default: return 0;
         }

     case 84 :
       switch( element )
         {
          case 35 : return 604;
          case 34 : return 80;
          case 38 : return 113;
          case 26 : return 79;
          case 32 : return 81;
          case 33 : return 82;
          case 28 : return 50;
          case 5 : return 51;
          case 3 : return 19;
          case 0 : return 190;
          case 4 : return 23;
          case 1 : return 282;
          case 6 : return 380;
          case 22 : return 278;
          case 7 : return 381;
          case 11 : return 386;
          case 12 : return 388;
          case 13 : return 390;
          case 10 : return 384;
          case 8 : return 382;
          case 15 : return 387;
          case 16 : return 389;
          case 17 : return 391;
          case 14 : return 385;
          case 9 : return 383;
          case 51 : return 58;
          case 52 : return 166;
          case 53 : return 392;
          case 62 : return 256;
          case 63 : return 255;
          case 64 : return 254;
          case 65 : return 254;
          case 69 : return 393;
          case 70 : return 170;
          default: return 0;
         }

     case 85 :
       switch( element )
         {
          case 35 : return 604;
          case 34 : return 80;
          case 38 : return 113;
          case 26 : return 79;
          case 32 : return 81;
          case 33 : return 82;
          case 28 : return 50;
          case 5 : return 51;
          case 3 : return 19;
          case 0 : return 190;
          case 4 : return 23;
          case 1 : return 282;
          case 6 : return 380;
          case 22 : return 278;
          case 7 : return 381;
          case 11 : return 386;
          case 12 : return 388;
          case 13 : return 390;
          case 10 : return 384;
          case 8 : return 382;
          case 15 : return 387;
          case 16 : return 389;
          case 17 : return 391;
          case 14 : return 385;
          case 9 : return 383;
          case 51 : return 58;
          case 52 : return 166;
          case 53 : return 392;
          case 62 : return 268;
          case 63 : return 267;
          case 64 : return 266;
          case 65 : return 266;
          case 69 : return 393;
          case 70 : return 170;
          default: return 0;
         }

     case 86 :
       switch( element )
         {
          case 35 : return 607;
          case 34 : return 89;
          case 38 : return 114;
          case 26 : return 88;
          case 32 : return 90;
          case 33 : return 91;
          case 28 : return 52;
          case 5 : return 53;
          case 3 : return 20;
          case 0 : return 191;
          case 4 : return 24;
          case 1 : return 283;
          case 6 : return 380;
          case 22 : return 279;
          case 7 : return 381;
          case 11 : return 386;
          case 12 : return 388;
          case 13 : return 390;
          case 10 : return 384;
          case 8 : return 382;
          case 15 : return 387;
          case 16 : return 389;
          case 17 : return 391;
          case 14 : return 385;
          case 9 : return 383;
          case 51 : return 59;
          case 52 : return 167;
          case 53 : return 392;
          case 61 : return 322;
          case 62 : return 322;
          case 63 : return 321;
          case 64 : return 320;
          case 65 : return 320;
          case 69 : return 394;
          case 70 : return 171;
          default: return 0;
         }

     case 87 :
       switch( element )
         {
          case 35 : return 607;
          case 34 : return 89;
          case 38 : return 114;
          case 26 : return 88;
          case 32 : return 90;
          case 33 : return 91;
          case 28 : return 52;
          case 5 : return 53;
          case 3 : return 20;
          case 0 : return 191;
          case 4 : return 24;
          case 1 : return 283;
          case 6 : return 380;
          case 22 : return 279;
          case 7 : return 381;
          case 11 : return 386;
          case 12 : return 388;
          case 13 : return 390;
          case 10 : return 384;
          case 8 : return 382;
          case 15 : return 387;
          case 16 : return 389;
          case 17 : return 391;
          case 14 : return 385;
          case 9 : return 383;
          case 51 : return 59;
          case 52 : return 167;
          case 53 : return 392;
          case 61 : return 331;
          case 62 : return 331;
          case 63 : return 330;
          case 64 : return 329;
          case 65 : return 329;
          case 69 : return 394;
          case 70 : return 171;
          default: return 0;
         }

     case 88 :
       switch( element )
         {
          case 35 : return 607;
          case 34 : return 89;
          case 38 : return 114;
          case 26 : return 88;
          case 32 : return 90;
          case 33 : return 91;
          case 28 : return 52;
          case 5 : return 53;
          case 3 : return 20;
          case 0 : return 191;
          case 4 : return 24;
          case 1 : return 283;
          case 6 : return 380;
          case 22 : return 279;
          case 7 : return 381;
          case 11 : return 386;
          case 12 : return 388;
          case 13 : return 390;
          case 10 : return 384;
          case 8 : return 382;
          case 15 : return 387;
          case 16 : return 389;
          case 17 : return 391;
          case 14 : return 385;
          case 9 : return 383;
          case 51 : return 59;
          case 52 : return 167;
          case 53 : return 392;
          case 62 : return 199;
          case 63 : return 198;
          case 64 : return 197;
          case 65 : return 197;
          case 69 : return 394;
          case 70 : return 171;
          default: return 0;
         }

     case 89 :
       switch( element )
         {
          case 35 : return 607;
          case 34 : return 89;
          case 38 : return 114;
          case 26 : return 88;
          case 32 : return 90;
          case 33 : return 91;
          case 28 : return 52;
          case 5 : return 53;
          case 3 : return 20;
          case 0 : return 191;
          case 4 : return 24;
          case 1 : return 283;
          case 6 : return 380;
          case 22 : return 279;
          case 7 : return 381;
          case 11 : return 386;
          case 12 : return 388;
          case 13 : return 390;
          case 10 : return 384;
          case 8 : return 382;
          case 15 : return 387;
          case 16 : return 389;
          case 17 : return 391;
          case 14 : return 385;
          case 9 : return 383;
          case 51 : return 59;
          case 52 : return 167;
          case 53 : return 392;
          case 62 : return 211;
          case 63 : return 210;
          case 64 : return 209;
          case 65 : return 209;
          case 69 : return 394;
          case 70 : return 171;
          default: return 0;
         }

     case 90 :
       switch( element )
         {
          case 35 : return 607;
          case 34 : return 89;
          case 38 : return 114;
          case 26 : return 88;
          case 32 : return 90;
          case 33 : return 91;
          case 28 : return 52;
          case 5 : return 53;
          case 3 : return 20;
          case 0 : return 191;
          case 4 : return 24;
          case 1 : return 283;
          case 6 : return 380;
          case 22 : return 279;
          case 7 : return 381;
          case 11 : return 386;
          case 12 : return 388;
          case 13 : return 390;
          case 10 : return 384;
          case 8 : return 382;
          case 15 : return 387;
          case 16 : return 389;
          case 17 : return 391;
          case 14 : return 385;
          case 9 : return 383;
          case 51 : return 59;
          case 52 : return 167;
          case 53 : return 392;
          case 62 : return 223;
          case 63 : return 222;
          case 64 : return 221;
          case 65 : return 221;
          case 69 : return 394;
          case 70 : return 171;
          default: return 0;
         }

     case 91 :
       switch( element )
         {
          case 35 : return 607;
          case 34 : return 89;
          case 38 : return 114;
          case 26 : return 88;
          case 32 : return 90;
          case 33 : return 91;
          case 28 : return 52;
          case 5 : return 53;
          case 3 : return 20;
          case 0 : return 191;
          case 4 : return 24;
          case 1 : return 283;
          case 6 : return 380;
          case 22 : return 279;
          case 7 : return 381;
          case 11 : return 386;
          case 12 : return 388;
          case 13 : return 390;
          case 10 : return 384;
          case 8 : return 382;
          case 15 : return 387;
          case 16 : return 389;
          case 17 : return 391;
          case 14 : return 385;
          case 9 : return 383;
          case 51 : return 59;
          case 52 : return 167;
          case 53 : return 392;
          case 62 : return 235;
          case 63 : return 234;
          case 64 : return 233;
          case 65 : return 233;
          case 69 : return 394;
          case 70 : return 171;
          default: return 0;
         }

     case 92 :
       switch( element )
         {
          case 35 : return 607;
          case 34 : return 89;
          case 38 : return 114;
          case 26 : return 88;
          case 32 : return 90;
          case 33 : return 91;
          case 28 : return 52;
          case 5 : return 53;
          case 3 : return 20;
          case 0 : return 191;
          case 4 : return 24;
          case 1 : return 283;
          case 6 : return 380;
          case 22 : return 279;
          case 7 : return 381;
          case 11 : return 386;
          case 12 : return 388;
          case 13 : return 390;
          case 10 : return 384;
          case 8 : return 382;
          case 15 : return 387;
          case 16 : return 389;
          case 17 : return 391;
          case 14 : return 385;
          case 9 : return 383;
          case 51 : return 59;
          case 52 : return 167;
          case 53 : return 392;
          case 62 : return 247;
          case 63 : return 246;
          case 64 : return 245;
          case 65 : return 245;
          case 69 : return 394;
          case 70 : return 171;
          default: return 0;
         }

     case 93 :
       switch( element )
         {
          case 35 : return 607;
          case 34 : return 89;
          case 38 : return 114;
          case 26 : return 88;
          case 32 : return 90;
          case 33 : return 91;
          case 28 : return 52;
          case 5 : return 53;
          case 3 : return 20;
          case 0 : return 191;
          case 4 : return 24;
          case 1 : return 283;
          case 6 : return 380;
          case 22 : return 279;
          case 7 : return 381;
          case 11 : return 386;
          case 12 : return 388;
          case 13 : return 390;
          case 10 : return 384;
          case 8 : return 382;
          case 15 : return 387;
          case 16 : return 389;
          case 17 : return 391;
          case 14 : return 385;
          case 9 : return 383;
          case 51 : return 59;
          case 52 : return 167;
          case 53 : return 392;
          case 62 : return 259;
          case 63 : return 258;
          case 64 : return 257;
          case 65 : return 257;
          case 69 : return 394;
          case 70 : return 171;
          default: return 0;
         }

     case 94 :
       switch( element )
         {
          case 35 : return 607;
          case 34 : return 89;
          case 38 : return 114;
          case 26 : return 88;
          case 32 : return 90;
          case 33 : return 91;
          case 28 : return 52;
          case 5 : return 53;
          case 3 : return 20;
          case 0 : return 191;
          case 4 : return 24;
          case 1 : return 283;
          case 6 : return 380;
          case 22 : return 279;
          case 7 : return 381;
          case 11 : return 386;
          case 12 : return 388;
          case 13 : return 390;
          case 10 : return 384;
          case 8 : return 382;
          case 15 : return 387;
          case 16 : return 389;
          case 17 : return 391;
          case 14 : return 385;
          case 9 : return 383;
          case 51 : return 59;
          case 52 : return 167;
          case 53 : return 392;
          case 62 : return 271;
          case 63 : return 270;
          case 64 : return 269;
          case 65 : return 269;
          case 69 : return 394;
          case 70 : return 171;
          default: return 0;
         }

     case 95 :
       switch( element )
         {
          case 35 : return 610;
          case 34 : return 98;
          case 38 : return 115;
          case 26 : return 97;
          case 32 : return 99;
          case 33 : return 100;
          case 28 : return 54;
          case 5 : return 55;
          case 3 : return 21;
          case 0 : return 192;
          case 4 : return 25;
          case 1 : return 284;
          case 6 : return 380;
          case 22 : return 280;
          case 7 : return 381;
          case 11 : return 386;
          case 12 : return 388;
          case 13 : return 390;
          case 10 : return 384;
          case 8 : return 382;
          case 15 : return 387;
          case 16 : return 389;
          case 17 : return 391;
          case 14 : return 385;
          case 9 : return 383;
          case 51 : return 60;
          case 52 : return 168;
          case 53 : return 392;
          case 61 : return 326;
          case 62 : return 326;
          case 63 : return 325;
          case 64 : return 323;
          case 65 : return 323;
          case 69 : return 395;
          case 70 : return 172;
          default: return 0;
         }

     case 96 :
       switch( element )
         {
          case 35 : return 610;
          case 34 : return 98;
          case 38 : return 115;
          case 26 : return 97;
          case 32 : return 99;
          case 33 : return 100;
          case 28 : return 54;
          case 5 : return 55;
          case 3 : return 21;
          case 0 : return 192;
          case 4 : return 25;
          case 1 : return 284;
          case 6 : return 380;
          case 22 : return 280;
          case 7 : return 381;
          case 11 : return 386;
          case 12 : return 388;
          case 13 : return 390;
          case 10 : return 384;
          case 8 : return 382;
          case 15 : return 387;
          case 16 : return 389;
          case 17 : return 391;
          case 14 : return 385;
          case 9 : return 383;
          case 51 : return 60;
          case 52 : return 168;
          case 53 : return 392;
          case 61 : return 335;
          case 62 : return 335;
          case 63 : return 334;
          case 64 : return 332;
          case 65 : return 332;
          case 69 : return 395;
          case 70 : return 172;
          default: return 0;
         }

     case 97 :
       switch( element )
         {
          case 35 : return 610;
          case 34 : return 98;
          case 38 : return 115;
          case 26 : return 97;
          case 32 : return 99;
          case 33 : return 100;
          case 28 : return 54;
          case 5 : return 55;
          case 3 : return 21;
          case 0 : return 192;
          case 4 : return 25;
          case 1 : return 284;
          case 6 : return 380;
          case 22 : return 280;
          case 7 : return 381;
          case 11 : return 386;
          case 12 : return 388;
          case 13 : return 390;
          case 10 : return 384;
          case 8 : return 382;
          case 15 : return 387;
          case 16 : return 389;
          case 17 : return 391;
          case 14 : return 385;
          case 9 : return 383;
          case 51 : return 60;
          case 52 : return 168;
          case 53 : return 392;
          case 62 : return 203;
          case 63 : return 202;
          case 64 : return 200;
          case 65 : return 200;
          case 69 : return 395;
          case 70 : return 172;
          default: return 0;
         }

     case 98 :
       switch( element )
         {
          case 35 : return 610;
          case 34 : return 98;
          case 38 : return 115;
          case 26 : return 97;
          case 32 : return 99;
          case 33 : return 100;
          case 28 : return 54;
          case 5 : return 55;
          case 3 : return 21;
          case 0 : return 192;
          case 4 : return 25;
          case 1 : return 284;
          case 6 : return 380;
          case 22 : return 280;
          case 7 : return 381;
          case 11 : return 386;
          case 12 : return 388;
          case 13 : return 390;
          case 10 : return 384;
          case 8 : return 382;
          case 15 : return 387;
          case 16 : return 389;
          case 17 : return 391;
          case 14 : return 385;
          case 9 : return 383;
          case 51 : return 60;
          case 52 : return 168;
          case 53 : return 392;
          case 62 : return 215;
          case 63 : return 214;
          case 64 : return 212;
          case 65 : return 212;
          case 69 : return 395;
          case 70 : return 172;
          default: return 0;
         }

     case 99 :
       switch( element )
         {
          case 35 : return 610;
          case 34 : return 98;
          case 38 : return 115;
          case 26 : return 97;
          case 32 : return 99;
          case 33 : return 100;
          case 28 : return 54;
          case 5 : return 55;
          case 3 : return 21;
          case 0 : return 192;
          case 4 : return 25;
          case 1 : return 284;
          case 6 : return 380;
          case 22 : return 280;
          case 7 : return 381;
          case 11 : return 386;
          case 12 : return 388;
          case 13 : return 390;
          case 10 : return 384;
          case 8 : return 382;
          case 15 : return 387;
          case 16 : return 389;
          case 17 : return 391;
          case 14 : return 385;
          case 9 : return 383;
          case 51 : return 60;
          case 52 : return 168;
          case 53 : return 392;
          case 62 : return 227;
          case 63 : return 226;
          case 64 : return 224;
          case 65 : return 224;
          case 69 : return 395;
          case 70 : return 172;
          default: return 0;
         }

     case 100 :
       switch( element )
         {
          case 35 : return 610;
          case 34 : return 98;
          case 38 : return 115;
          case 26 : return 97;
          case 32 : return 99;
          case 33 : return 100;
          case 28 : return 54;
          case 5 : return 55;
          case 3 : return 21;
          case 0 : return 192;
          case 4 : return 25;
          case 1 : return 284;
          case 6 : return 380;
          case 22 : return 280;
          case 7 : return 381;
          case 11 : return 386;
          case 12 : return 388;
          case 13 : return 390;
          case 10 : return 384;
          case 8 : return 382;
          case 15 : return 387;
          case 16 : return 389;
          case 17 : return 391;
          case 14 : return 385;
          case 9 : return 383;
          case 51 : return 60;
          case 52 : return 168;
          case 53 : return 392;
          case 62 : return 239;
          case 63 : return 238;
          case 64 : return 236;
          case 65 : return 236;
          case 69 : return 395;
          case 70 : return 172;
          default: return 0;
         }

     case 101 :
       switch( element )
         {
          case 35 : return 610;
          case 34 : return 98;
          case 38 : return 115;
          case 26 : return 97;
          case 32 : return 99;
          case 33 : return 100;
          case 28 : return 54;
          case 5 : return 55;
          case 3 : return 21;
          case 0 : return 192;
          case 4 : return 25;
          case 1 : return 284;
          case 6 : return 380;
          case 22 : return 280;
          case 7 : return 381;
          case 11 : return 386;
          case 12 : return 388;
          case 13 : return 390;
          case 10 : return 384;
          case 8 : return 382;
          case 15 : return 387;
          case 16 : return 389;
          case 17 : return 391;
          case 14 : return 385;
          case 9 : return 383;
          case 51 : return 60;
          case 52 : return 168;
          case 53 : return 392;
          case 62 : return 251;
          case 63 : return 250;
          case 64 : return 248;
          case 65 : return 248;
          case 69 : return 395;
          case 70 : return 172;
          default: return 0;
         }

     case 102 :
       switch( element )
         {
          case 35 : return 610;
          case 34 : return 98;
          case 38 : return 115;
          case 26 : return 97;
          case 32 : return 99;
          case 33 : return 100;
          case 28 : return 54;
          case 5 : return 55;
          case 3 : return 21;
          case 0 : return 192;
          case 4 : return 25;
          case 1 : return 284;
          case 6 : return 380;
          case 22 : return 280;
          case 7 : return 381;
          case 11 : return 386;
          case 12 : return 388;
          case 13 : return 390;
          case 10 : return 384;
          case 8 : return 382;
          case 15 : return 387;
          case 16 : return 389;
          case 17 : return 391;
          case 14 : return 385;
          case 9 : return 383;
          case 51 : return 60;
          case 52 : return 168;
          case 53 : return 392;
          case 62 : return 263;
          case 63 : return 262;
          case 64 : return 260;
          case 65 : return 260;
          case 69 : return 395;
          case 70 : return 172;
          default: return 0;
         }

     case 103 :
       switch( element )
         {
          case 35 : return 610;
          case 34 : return 98;
          case 38 : return 115;
          case 26 : return 97;
          case 32 : return 99;
          case 33 : return 100;
          case 28 : return 54;
          case 5 : return 55;
          case 3 : return 21;
          case 0 : return 192;
          case 4 : return 25;
          case 1 : return 284;
          case 6 : return 380;
          case 22 : return 280;
          case 7 : return 381;
          case 11 : return 386;
          case 12 : return 388;
          case 13 : return 390;
          case 10 : return 384;
          case 8 : return 382;
          case 15 : return 387;
          case 16 : return 389;
          case 17 : return 391;
          case 14 : return 385;
          case 9 : return 383;
          case 51 : return 60;
          case 52 : return 168;
          case 53 : return 392;
          case 62 : return 275;
          case 63 : return 274;
          case 64 : return 272;
          case 65 : return 272;
          case 69 : return 395;
          case 70 : return 172;
          default: return 0;
         }

     case 104 :
       switch( element )
         {
          case 35 : return 613;
          case 34 : return 107;
          case 38 : return 116;
          case 26 : return 106;
          case 32 : return 108;
          case 33 : return 109;
          case 28 : return 56;
          case 5 : return 57;
          case 3 : return 22;
          case 0 : return 193;
          case 4 : return 26;
          case 1 : return 285;
          case 6 : return 380;
          case 22 : return 281;
          case 7 : return 381;
          case 11 : return 386;
          case 12 : return 388;
          case 13 : return 390;
          case 10 : return 384;
          case 8 : return 382;
          case 15 : return 387;
          case 16 : return 389;
          case 17 : return 391;
          case 14 : return 385;
          case 9 : return 383;
          case 51 : return 61;
          case 52 : return 169;
          case 53 : return 392;
          case 61 : return 328;
          case 62 : return 328;
          case 63 : return 327;
          case 64 : return 324;
          case 65 : return 324;
          case 69 : return 396;
          case 70 : return 173;
          default: return 0;
         }

     case 105 :
       switch( element )
         {
          case 35 : return 613;
          case 34 : return 107;
          case 38 : return 116;
          case 26 : return 106;
          case 32 : return 108;
          case 33 : return 109;
          case 28 : return 56;
          case 5 : return 57;
          case 3 : return 22;
          case 0 : return 193;
          case 4 : return 26;
          case 1 : return 285;
          case 6 : return 380;
          case 22 : return 281;
          case 7 : return 381;
          case 11 : return 386;
          case 12 : return 388;
          case 13 : return 390;
          case 10 : return 384;
          case 8 : return 382;
          case 15 : return 387;
          case 16 : return 389;
          case 17 : return 391;
          case 14 : return 385;
          case 9 : return 383;
          case 51 : return 61;
          case 52 : return 169;
          case 53 : return 392;
          case 61 : return 337;
          case 62 : return 337;
          case 63 : return 336;
          case 64 : return 333;
          case 65 : return 333;
          case 69 : return 396;
          case 70 : return 173;
          default: return 0;
         }

     case 106 :
       switch( element )
         {
          case 35 : return 613;
          case 34 : return 107;
          case 38 : return 116;
          case 26 : return 106;
          case 32 : return 108;
          case 33 : return 109;
          case 28 : return 56;
          case 5 : return 57;
          case 3 : return 22;
          case 0 : return 193;
          case 4 : return 26;
          case 1 : return 285;
          case 6 : return 380;
          case 22 : return 281;
          case 7 : return 381;
          case 11 : return 386;
          case 12 : return 388;
          case 13 : return 390;
          case 10 : return 384;
          case 8 : return 382;
          case 15 : return 387;
          case 16 : return 389;
          case 17 : return 391;
          case 14 : return 385;
          case 9 : return 383;
          case 51 : return 61;
          case 52 : return 169;
          case 53 : return 392;
          case 62 : return 205;
          case 63 : return 204;
          case 64 : return 201;
          case 65 : return 201;
          case 69 : return 396;
          case 70 : return 173;
          default: return 0;
         }

     case 107 :
       switch( element )
         {
          case 35 : return 613;
          case 34 : return 107;
          case 38 : return 116;
          case 26 : return 106;
          case 32 : return 108;
          case 33 : return 109;
          case 28 : return 56;
          case 5 : return 57;
          case 3 : return 22;
          case 0 : return 193;
          case 4 : return 26;
          case 1 : return 285;
          case 6 : return 380;
          case 22 : return 281;
          case 7 : return 381;
          case 11 : return 386;
          case 12 : return 388;
          case 13 : return 390;
          case 10 : return 384;
          case 8 : return 382;
          case 15 : return 387;
          case 16 : return 389;
          case 17 : return 391;
          case 14 : return 385;
          case 9 : return 383;
          case 51 : return 61;
          case 52 : return 169;
          case 53 : return 392;
          case 62 : return 217;
          case 63 : return 216;
          case 64 : return 213;
          case 65 : return 213;
          case 69 : return 396;
          case 70 : return 173;
          default: return 0;
         }

     case 108 :
       switch( element )
         {
          case 35 : return 613;
          case 34 : return 107;
          case 38 : return 116;
          case 26 : return 106;
          case 32 : return 108;
          case 33 : return 109;
          case 28 : return 56;
          case 5 : return 57;
          case 3 : return 22;
          case 0 : return 193;
          case 4 : return 26;
          case 1 : return 285;
          case 6 : return 380;
          case 22 : return 281;
          case 7 : return 381;
          case 11 : return 386;
          case 12 : return 388;
          case 13 : return 390;
          case 10 : return 384;
          case 8 : return 382;
          case 15 : return 387;
          case 16 : return 389;
          case 17 : return 391;
          case 14 : return 385;
          case 9 : return 383;
          case 51 : return 61;
          case 52 : return 169;
          case 53 : return 392;
          case 62 : return 229;
          case 63 : return 228;
          case 64 : return 225;
          case 65 : return 225;
          case 69 : return 396;
          case 70 : return 173;
          default: return 0;
         }

     case 109 :
       switch( element )
         {
          case 35 : return 613;
          case 34 : return 107;
          case 38 : return 116;
          case 26 : return 106;
          case 32 : return 108;
          case 33 : return 109;
          case 28 : return 56;
          case 5 : return 57;
          case 3 : return 22;
          case 0 : return 193;
          case 4 : return 26;
          case 1 : return 285;
          case 6 : return 380;
          case 22 : return 281;
          case 7 : return 381;
          case 11 : return 386;
          case 12 : return 388;
          case 13 : return 390;
          case 10 : return 384;
          case 8 : return 382;
          case 15 : return 387;
          case 16 : return 389;
          case 17 : return 391;
          case 14 : return 385;
          case 9 : return 383;
          case 51 : return 61;
          case 52 : return 169;
          case 53 : return 392;
          case 62 : return 241;
          case 63 : return 240;
          case 64 : return 237;
          case 65 : return 237;
          case 69 : return 396;
          case 70 : return 173;
          default: return 0;
         }

     case 110 :
       switch( element )
         {
          case 35 : return 613;
          case 34 : return 107;
          case 38 : return 116;
          case 26 : return 106;
          case 32 : return 108;
          case 33 : return 109;
          case 28 : return 56;
          case 5 : return 57;
          case 3 : return 22;
          case 0 : return 193;
          case 4 : return 26;
          case 1 : return 285;
          case 6 : return 380;
          case 22 : return 281;
          case 7 : return 381;
          case 11 : return 386;
          case 12 : return 388;
          case 13 : return 390;
          case 10 : return 384;
          case 8 : return 382;
          case 15 : return 387;
          case 16 : return 389;
          case 17 : return 391;
          case 14 : return 385;
          case 9 : return 383;
          case 51 : return 61;
          case 52 : return 169;
          case 53 : return 392;
          case 62 : return 253;
          case 63 : return 252;
          case 64 : return 249;
          case 65 : return 249;
          case 69 : return 396;
          case 70 : return 173;
          default: return 0;
         }

     case 111 :
       switch( element )
         {
          case 35 : return 613;
          case 34 : return 107;
          case 38 : return 116;
          case 26 : return 106;
          case 32 : return 108;
          case 33 : return 109;
          case 28 : return 56;
          case 5 : return 57;
          case 3 : return 22;
          case 0 : return 193;
          case 4 : return 26;
          case 1 : return 285;
          case 6 : return 380;
          case 22 : return 281;
          case 7 : return 381;
          case 11 : return 386;
          case 12 : return 388;
          case 13 : return 390;
          case 10 : return 384;
          case 8 : return 382;
          case 15 : return 387;
          case 16 : return 389;
          case 17 : return 391;
          case 14 : return 385;
          case 9 : return 383;
          case 51 : return 61;
          case 52 : return 169;
          case 53 : return 392;
          case 62 : return 265;
          case 63 : return 264;
          case 64 : return 261;
          case 65 : return 261;
          case 69 : return 396;
          case 70 : return 173;
          default: return 0;
         }

     case 112 :
       switch( element )
         {
          case 35 : return 613;
          case 34 : return 107;
          case 38 : return 116;
          case 26 : return 106;
          case 32 : return 108;
          case 33 : return 109;
          case 28 : return 56;
          case 5 : return 57;
          case 3 : return 22;
          case 0 : return 193;
          case 4 : return 26;
          case 1 : return 285;
          case 6 : return 380;
          case 22 : return 281;
          case 7 : return 381;
          case 11 : return 386;
          case 12 : return 388;
          case 13 : return 390;
          case 10 : return 384;
          case 8 : return 382;
          case 15 : return 387;
          case 16 : return 389;
          case 17 : return 391;
          case 14 : return 385;
          case 9 : return 383;
          case 51 : return 61;
          case 52 : return 169;
          case 53 : return 392;
          case 62 : return 277;
          case 63 : return 276;
          case 64 : return 273;
          case 65 : return 273;
          case 69 : return 396;
          case 70 : return 173;
          default: return 0;
         }

     case 113 :
       switch( element )
         {
          case 35 : return 604;
          case 34 : return 80;
          case 38 : return 113;
          case 26 : return 79;
          case 32 : return 81;
          case 33 : return 82;
          case 28 : return 50;
          case 5 : return 51;
          case 3 : return 19;
          case 0 : return 190;
          case 4 : return 23;
          case 1 : return 282;
          case 6 : return 380;
          case 22 : return 278;
          case 7 : return 381;
          case 11 : return 386;
          case 12 : return 388;
          case 13 : return 390;
          case 10 : return 384;
          case 8 : return 382;
          case 15 : return 387;
          case 16 : return 389;
          case 17 : return 391;
          case 14 : return 385;
          case 9 : return 383;
          case 42 : return 131;
          case 51 : return 58;
          case 52 : return 166;
          case 53 : return 392;
          case 59 : return 410;
          case 60 : return 402;
          case 61 : return 312;
          case 62 : return 312;
          case 63 : return 304;
          case 64 : return 296;
          case 65 : return 296;
          case 69 : return 393;
          case 70 : return 170;
          default: return 0;
         }

     case 114 :
       switch( element )
         {
          case 35 : return 604;
          case 34 : return 80;
          case 38 : return 113;
          case 26 : return 79;
          case 32 : return 81;
          case 33 : return 82;
          case 28 : return 50;
          case 5 : return 51;
          case 3 : return 19;
          case 0 : return 190;
          case 4 : return 23;
          case 1 : return 282;
          case 6 : return 380;
          case 22 : return 278;
          case 7 : return 381;
          case 11 : return 386;
          case 12 : return 388;
          case 13 : return 390;
          case 10 : return 384;
          case 8 : return 382;
          case 15 : return 387;
          case 16 : return 389;
          case 17 : return 391;
          case 14 : return 385;
          case 9 : return 383;
          case 42 : return 131;
          case 51 : return 58;
          case 52 : return 166;
          case 53 : return 392;
          case 59 : return 411;
          case 60 : return 403;
          case 61 : return 313;
          case 62 : return 313;
          case 63 : return 305;
          case 64 : return 297;
          case 65 : return 297;
          case 69 : return 393;
          case 70 : return 170;
          default: return 0;
         }

     case 115 :
       switch( element )
         {
          case 35 : return 604;
          case 34 : return 80;
          case 38 : return 113;
          case 26 : return 79;
          case 32 : return 81;
          case 33 : return 82;
          case 28 : return 50;
          case 5 : return 51;
          case 3 : return 19;
          case 0 : return 190;
          case 4 : return 23;
          case 1 : return 282;
          case 6 : return 380;
          case 22 : return 278;
          case 7 : return 381;
          case 11 : return 386;
          case 12 : return 388;
          case 13 : return 390;
          case 10 : return 384;
          case 8 : return 382;
          case 15 : return 387;
          case 16 : return 389;
          case 17 : return 391;
          case 14 : return 385;
          case 9 : return 383;
          case 42 : return 131;
          case 51 : return 58;
          case 52 : return 166;
          case 53 : return 392;
          case 59 : return 412;
          case 60 : return 404;
          case 61 : return 314;
          case 62 : return 314;
          case 63 : return 306;
          case 64 : return 298;
          case 65 : return 298;
          case 69 : return 393;
          case 70 : return 170;
          default: return 0;
         }

     case 116 :
       switch( element )
         {
          case 35 : return 604;
          case 34 : return 80;
          case 38 : return 113;
          case 26 : return 79;
          case 32 : return 81;
          case 33 : return 82;
          case 28 : return 50;
          case 5 : return 51;
          case 3 : return 19;
          case 0 : return 190;
          case 4 : return 23;
          case 1 : return 282;
          case 6 : return 380;
          case 22 : return 278;
          case 7 : return 381;
          case 11 : return 386;
          case 12 : return 388;
          case 13 : return 390;
          case 10 : return 384;
          case 8 : return 382;
          case 15 : return 387;
          case 16 : return 389;
          case 17 : return 391;
          case 14 : return 385;
          case 9 : return 383;
          case 42 : return 131;
          case 51 : return 58;
          case 52 : return 166;
          case 53 : return 392;
          case 59 : return 413;
          case 60 : return 405;
          case 61 : return 315;
          case 62 : return 315;
          case 63 : return 307;
          case 64 : return 299;
          case 65 : return 299;
          case 69 : return 393;
          case 70 : return 170;
          default: return 0;
         }

     case 117 :
       switch( element )
         {
          case 35 : return 604;
          case 34 : return 80;
          case 38 : return 113;
          case 26 : return 79;
          case 32 : return 81;
          case 33 : return 82;
          case 28 : return 50;
          case 5 : return 51;
          case 3 : return 19;
          case 0 : return 190;
          case 4 : return 23;
          case 1 : return 282;
          case 6 : return 380;
          case 22 : return 278;
          case 7 : return 381;
          case 11 : return 386;
          case 12 : return 388;
          case 13 : return 390;
          case 10 : return 384;
          case 8 : return 382;
          case 15 : return 387;
          case 16 : return 389;
          case 17 : return 391;
          case 14 : return 385;
          case 9 : return 383;
          case 42 : return 131;
          case 51 : return 58;
          case 52 : return 166;
          case 53 : return 392;
          case 59 : return 414;
          case 60 : return 406;
          case 61 : return 316;
          case 62 : return 316;
          case 63 : return 308;
          case 64 : return 300;
          case 65 : return 300;
          case 69 : return 393;
          case 70 : return 170;
          default: return 0;
         }

     case 118 :
       switch( element )
         {
          case 35 : return 604;
          case 34 : return 80;
          case 38 : return 113;
          case 26 : return 79;
          case 32 : return 81;
          case 33 : return 82;
          case 28 : return 50;
          case 5 : return 51;
          case 3 : return 19;
          case 0 : return 190;
          case 4 : return 23;
          case 1 : return 282;
          case 6 : return 380;
          case 22 : return 278;
          case 7 : return 381;
          case 11 : return 386;
          case 12 : return 388;
          case 13 : return 390;
          case 10 : return 384;
          case 8 : return 382;
          case 15 : return 387;
          case 16 : return 389;
          case 17 : return 391;
          case 14 : return 385;
          case 9 : return 383;
          case 42 : return 131;
          case 51 : return 58;
          case 52 : return 166;
          case 53 : return 392;
          case 59 : return 415;
          case 60 : return 407;
          case 61 : return 317;
          case 62 : return 317;
          case 63 : return 309;
          case 64 : return 301;
          case 65 : return 301;
          case 69 : return 393;
          case 70 : return 170;
          default: return 0;
         }

     case 119 :
       switch( element )
         {
          case 35 : return 604;
          case 34 : return 80;
          case 38 : return 113;
          case 26 : return 79;
          case 32 : return 81;
          case 33 : return 82;
          case 28 : return 50;
          case 5 : return 51;
          case 3 : return 19;
          case 0 : return 190;
          case 4 : return 23;
          case 1 : return 282;
          case 6 : return 380;
          case 22 : return 278;
          case 7 : return 381;
          case 11 : return 386;
          case 12 : return 388;
          case 13 : return 390;
          case 10 : return 384;
          case 8 : return 382;
          case 15 : return 387;
          case 16 : return 389;
          case 17 : return 391;
          case 14 : return 385;
          case 9 : return 383;
          case 42 : return 131;
          case 51 : return 58;
          case 52 : return 166;
          case 53 : return 392;
          case 59 : return 416;
          case 60 : return 408;
          case 61 : return 318;
          case 62 : return 318;
          case 63 : return 310;
          case 64 : return 302;
          case 65 : return 302;
          case 69 : return 393;
          case 70 : return 170;
          default: return 0;
         }

     case 120 :
       switch( element )
         {
          case 35 : return 604;
          case 34 : return 80;
          case 38 : return 113;
          case 26 : return 79;
          case 32 : return 81;
          case 33 : return 82;
          case 28 : return 50;
          case 5 : return 51;
          case 3 : return 19;
          case 0 : return 190;
          case 4 : return 23;
          case 1 : return 282;
          case 6 : return 380;
          case 22 : return 278;
          case 7 : return 381;
          case 11 : return 386;
          case 12 : return 388;
          case 13 : return 390;
          case 10 : return 384;
          case 8 : return 382;
          case 15 : return 387;
          case 16 : return 389;
          case 17 : return 391;
          case 14 : return 385;
          case 9 : return 383;
          case 42 : return 131;
          case 51 : return 58;
          case 52 : return 166;
          case 53 : return 392;
          case 59 : return 417;
          case 60 : return 409;
          case 61 : return 319;
          case 62 : return 319;
          case 63 : return 311;
          case 64 : return 303;
          case 65 : return 303;
          case 69 : return 393;
          case 70 : return 170;
          default: return 0;
         }

     case 121 :
       switch( element )
         {
          case 35 : return 607;
          case 34 : return 89;
          case 38 : return 114;
          case 26 : return 88;
          case 32 : return 90;
          case 33 : return 91;
          case 28 : return 52;
          case 5 : return 53;
          case 3 : return 20;
          case 0 : return 191;
          case 4 : return 24;
          case 1 : return 283;
          case 6 : return 380;
          case 22 : return 279;
          case 7 : return 381;
          case 11 : return 386;
          case 12 : return 388;
          case 13 : return 390;
          case 10 : return 384;
          case 8 : return 382;
          case 15 : return 387;
          case 16 : return 389;
          case 17 : return 391;
          case 14 : return 385;
          case 9 : return 383;
          case 42 : return 132;
          case 51 : return 59;
          case 52 : return 167;
          case 53 : return 392;
          case 59 : return 523;
          case 60 : return 504;
          case 61 : return 343;
          case 62 : return 343;
          case 63 : return 342;
          case 64 : return 341;
          case 65 : return 341;
          case 69 : return 394;
          case 70 : return 171;
          default: return 0;
         }

     case 122 :
       switch( element )
         {
          case 35 : return 607;
          case 34 : return 89;
          case 38 : return 114;
          case 26 : return 88;
          case 32 : return 90;
          case 33 : return 91;
          case 28 : return 52;
          case 5 : return 53;
          case 3 : return 20;
          case 0 : return 191;
          case 4 : return 24;
          case 1 : return 283;
          case 6 : return 380;
          case 22 : return 279;
          case 7 : return 381;
          case 11 : return 386;
          case 12 : return 388;
          case 13 : return 390;
          case 10 : return 384;
          case 8 : return 382;
          case 15 : return 387;
          case 16 : return 389;
          case 17 : return 391;
          case 14 : return 385;
          case 9 : return 383;
          case 42 : return 132;
          case 51 : return 59;
          case 52 : return 167;
          case 53 : return 392;
          case 59 : return 524;
          case 60 : return 505;
          case 61 : return 346;
          case 62 : return 346;
          case 63 : return 345;
          case 64 : return 344;
          case 65 : return 344;
          case 69 : return 394;
          case 70 : return 171;
          default: return 0;
         }

     case 123 :
       switch( element )
         {
          case 35 : return 610;
          case 34 : return 98;
          case 38 : return 115;
          case 26 : return 97;
          case 32 : return 99;
          case 33 : return 100;
          case 28 : return 54;
          case 5 : return 55;
          case 3 : return 21;
          case 0 : return 192;
          case 4 : return 25;
          case 1 : return 284;
          case 6 : return 380;
          case 22 : return 280;
          case 7 : return 381;
          case 11 : return 386;
          case 12 : return 388;
          case 13 : return 390;
          case 10 : return 384;
          case 8 : return 382;
          case 15 : return 387;
          case 16 : return 389;
          case 17 : return 391;
          case 14 : return 385;
          case 9 : return 383;
          case 42 : return 133;
          case 51 : return 60;
          case 52 : return 168;
          case 53 : return 392;
          case 59 : return 561;
          case 60 : return 506;
          case 61 : return 362;
          case 62 : return 362;
          case 63 : return 358;
          case 64 : return 347;
          case 65 : return 347;
          case 69 : return 395;
          case 70 : return 172;
          default: return 0;
         }

     case 124 :
       switch( element )
         {
          case 35 : return 610;
          case 34 : return 98;
          case 38 : return 115;
          case 26 : return 97;
          case 32 : return 99;
          case 33 : return 100;
          case 28 : return 54;
          case 5 : return 55;
          case 3 : return 21;
          case 0 : return 192;
          case 4 : return 25;
          case 1 : return 284;
          case 6 : return 380;
          case 22 : return 280;
          case 7 : return 381;
          case 11 : return 386;
          case 12 : return 388;
          case 13 : return 390;
          case 10 : return 384;
          case 8 : return 382;
          case 15 : return 387;
          case 16 : return 389;
          case 17 : return 391;
          case 14 : return 385;
          case 9 : return 383;
          case 42 : return 133;
          case 51 : return 60;
          case 52 : return 168;
          case 53 : return 392;
          case 59 : return 562;
          case 60 : return 507;
          case 61 : return 363;
          case 62 : return 363;
          case 63 : return 359;
          case 64 : return 348;
          case 65 : return 348;
          case 69 : return 395;
          case 70 : return 172;
          default: return 0;
         }

     case 125 :
       switch( element )
         {
          case 35 : return 610;
          case 34 : return 98;
          case 38 : return 115;
          case 26 : return 97;
          case 32 : return 99;
          case 33 : return 100;
          case 28 : return 54;
          case 5 : return 55;
          case 3 : return 21;
          case 0 : return 192;
          case 4 : return 25;
          case 1 : return 284;
          case 6 : return 380;
          case 22 : return 280;
          case 7 : return 381;
          case 11 : return 386;
          case 12 : return 388;
          case 13 : return 390;
          case 10 : return 384;
          case 8 : return 382;
          case 15 : return 387;
          case 16 : return 389;
          case 17 : return 391;
          case 14 : return 385;
          case 9 : return 383;
          case 42 : return 133;
          case 51 : return 60;
          case 52 : return 168;
          case 53 : return 392;
          case 59 : return 563;
          case 60 : return 508;
          case 61 : return 364;
          case 62 : return 364;
          case 63 : return 360;
          case 64 : return 349;
          case 65 : return 349;
          case 69 : return 395;
          case 70 : return 172;
          default: return 0;
         }

     case 126 :
       switch( element )
         {
          case 35 : return 610;
          case 34 : return 98;
          case 38 : return 115;
          case 26 : return 97;
          case 32 : return 99;
          case 33 : return 100;
          case 28 : return 54;
          case 5 : return 55;
          case 3 : return 21;
          case 0 : return 192;
          case 4 : return 25;
          case 1 : return 284;
          case 6 : return 380;
          case 22 : return 280;
          case 7 : return 381;
          case 11 : return 386;
          case 12 : return 388;
          case 13 : return 390;
          case 10 : return 384;
          case 8 : return 382;
          case 15 : return 387;
          case 16 : return 389;
          case 17 : return 391;
          case 14 : return 385;
          case 9 : return 383;
          case 42 : return 133;
          case 51 : return 60;
          case 52 : return 168;
          case 53 : return 392;
          case 59 : return 564;
          case 60 : return 509;
          case 61 : return 365;
          case 62 : return 365;
          case 63 : return 361;
          case 64 : return 350;
          case 65 : return 350;
          case 69 : return 395;
          case 70 : return 172;
          default: return 0;
         }

     case 127 :
       switch( element )
         {
          case 35 : return 613;
          case 34 : return 107;
          case 38 : return 116;
          case 26 : return 106;
          case 32 : return 108;
          case 33 : return 109;
          case 28 : return 56;
          case 5 : return 57;
          case 3 : return 22;
          case 0 : return 193;
          case 4 : return 26;
          case 1 : return 285;
          case 6 : return 380;
          case 22 : return 281;
          case 7 : return 381;
          case 11 : return 386;
          case 12 : return 388;
          case 13 : return 390;
          case 10 : return 384;
          case 8 : return 382;
          case 15 : return 387;
          case 16 : return 389;
          case 17 : return 391;
          case 14 : return 385;
          case 9 : return 383;
          case 42 : return 134;
          case 51 : return 61;
          case 52 : return 169;
          case 53 : return 392;
          case 59 : return 637;
          case 60 : return 510;
          case 61 : return 373;
          case 62 : return 373;
          case 63 : return 366;
          case 64 : return 351;
          case 65 : return 351;
          case 69 : return 396;
          case 70 : return 173;
          default: return 0;
         }

     case 128 :
       switch( element )
         {
          case 35 : return 613;
          case 34 : return 107;
          case 38 : return 116;
          case 26 : return 106;
          case 32 : return 108;
          case 33 : return 109;
          case 28 : return 56;
          case 5 : return 57;
          case 3 : return 22;
          case 0 : return 193;
          case 4 : return 26;
          case 1 : return 285;
          case 6 : return 380;
          case 22 : return 281;
          case 7 : return 381;
          case 11 : return 386;
          case 12 : return 388;
          case 13 : return 390;
          case 10 : return 384;
          case 8 : return 382;
          case 15 : return 387;
          case 16 : return 389;
          case 17 : return 391;
          case 14 : return 385;
          case 9 : return 383;
          case 42 : return 134;
          case 51 : return 61;
          case 52 : return 169;
          case 53 : return 392;
          case 59 : return 638;
          case 60 : return 511;
          case 61 : return 374;
          case 62 : return 374;
          case 63 : return 367;
          case 64 : return 352;
          case 65 : return 352;
          case 69 : return 396;
          case 70 : return 173;
          default: return 0;
         }

     case 129 :
       switch( element )
         {
          case 35 : return 613;
          case 34 : return 107;
          case 38 : return 116;
          case 26 : return 106;
          case 32 : return 108;
          case 33 : return 109;
          case 28 : return 56;
          case 5 : return 57;
          case 3 : return 22;
          case 0 : return 193;
          case 4 : return 26;
          case 1 : return 285;
          case 6 : return 380;
          case 22 : return 281;
          case 7 : return 381;
          case 11 : return 386;
          case 12 : return 388;
          case 13 : return 390;
          case 10 : return 384;
          case 8 : return 382;
          case 15 : return 387;
          case 16 : return 389;
          case 17 : return 391;
          case 14 : return 385;
          case 9 : return 383;
          case 42 : return 134;
          case 51 : return 61;
          case 52 : return 169;
          case 53 : return 392;
          case 59 : return 639;
          case 60 : return 512;
          case 61 : return 375;
          case 62 : return 375;
          case 63 : return 368;
          case 64 : return 353;
          case 65 : return 353;
          case 69 : return 396;
          case 70 : return 173;
          default: return 0;
         }

     case 130 :
       switch( element )
         {
          case 35 : return 613;
          case 34 : return 107;
          case 38 : return 116;
          case 26 : return 106;
          case 32 : return 108;
          case 33 : return 109;
          case 28 : return 56;
          case 5 : return 57;
          case 3 : return 22;
          case 0 : return 193;
          case 4 : return 26;
          case 1 : return 285;
          case 6 : return 380;
          case 22 : return 281;
          case 7 : return 381;
          case 11 : return 386;
          case 12 : return 388;
          case 13 : return 390;
          case 10 : return 384;
          case 8 : return 382;
          case 15 : return 387;
          case 16 : return 389;
          case 17 : return 391;
          case 14 : return 385;
          case 9 : return 383;
          case 42 : return 134;
          case 51 : return 61;
          case 52 : return 169;
          case 53 : return 392;
          case 59 : return 640;
          case 60 : return 513;
          case 61 : return 376;
          case 62 : return 376;
          case 63 : return 369;
          case 64 : return 354;
          case 65 : return 354;
          case 69 : return 396;
          case 70 : return 173;
          default: return 0;
         }

     case 131 :
       switch( element )
         {
          case 35 : return 607;
          case 34 : return 89;
          case 38 : return 114;
          case 26 : return 88;
          case 32 : return 90;
          case 33 : return 91;
          case 28 : return 161;
          case 5 : return 53;
          case 3 : return 20;
          case 0 : return 191;
          case 4 : return 24;
          case 1 : return 283;
          case 6 : return 380;
          case 22 : return 279;
          case 7 : return 381;
          case 11 : return 386;
          case 12 : return 388;
          case 13 : return 390;
          case 10 : return 384;
          case 8 : return 382;
          case 15 : return 387;
          case 16 : return 389;
          case 17 : return 391;
          case 14 : return 385;
          case 9 : return 383;
          case 42 : return 132;
          case 43 : return 397;
          case 51 : return 59;
          case 52 : return 167;
          case 53 : return 392;
          case 59 : return 522;
          case 60 : return 503;
          case 61 : return 340;
          case 62 : return 340;
          case 63 : return 339;
          case 64 : return 338;
          case 65 : return 338;
          case 66 : return 527;
          case 67 : return 525;
          case 68 : return 534;
          case 69 : return 394;
          case 70 : return 171;
          default: return 0;
         }

     case 132 :
       switch( element )
         {
          case 35 : return 607;
          case 34 : return 89;
          case 38 : return 114;
          case 26 : return 88;
          case 32 : return 90;
          case 33 : return 91;
          case 28 : return 161;
          case 5 : return 53;
          case 3 : return 20;
          case 0 : return 191;
          case 4 : return 24;
          case 1 : return 283;
          case 6 : return 380;
          case 22 : return 279;
          case 7 : return 381;
          case 11 : return 386;
          case 12 : return 388;
          case 13 : return 390;
          case 10 : return 384;
          case 8 : return 382;
          case 15 : return 387;
          case 16 : return 389;
          case 17 : return 391;
          case 14 : return 385;
          case 9 : return 383;
          case 42 : return 132;
          case 43 : return 517;
          case 51 : return 59;
          case 52 : return 167;
          case 53 : return 392;
          case 59 : return 522;
          case 60 : return 503;
          case 61 : return 340;
          case 62 : return 340;
          case 63 : return 339;
          case 64 : return 338;
          case 65 : return 338;
          case 66 : return 528;
          case 67 : return 525;
          case 68 : return 536;
          case 69 : return 394;
          case 70 : return 171;
          default: return 0;
         }

     case 133 :
       switch( element )
         {
          case 35 : return 607;
          case 34 : return 89;
          case 38 : return 114;
          case 26 : return 88;
          case 32 : return 90;
          case 33 : return 91;
          case 28 : return 161;
          case 5 : return 53;
          case 3 : return 20;
          case 0 : return 191;
          case 4 : return 24;
          case 1 : return 283;
          case 6 : return 380;
          case 22 : return 279;
          case 7 : return 381;
          case 11 : return 386;
          case 12 : return 388;
          case 13 : return 390;
          case 10 : return 384;
          case 8 : return 382;
          case 15 : return 387;
          case 16 : return 389;
          case 17 : return 391;
          case 14 : return 385;
          case 9 : return 383;
          case 42 : return 132;
          case 43 : return 555;
          case 51 : return 59;
          case 52 : return 167;
          case 53 : return 392;
          case 59 : return 522;
          case 60 : return 503;
          case 61 : return 340;
          case 62 : return 340;
          case 63 : return 339;
          case 64 : return 338;
          case 65 : return 338;
          case 66 : return 529;
          case 67 : return 525;
          case 68 : return 538;
          case 69 : return 394;
          case 70 : return 171;
          default: return 0;
         }

     case 134 :
       switch( element )
         {
          case 35 : return 607;
          case 34 : return 89;
          case 38 : return 114;
          case 26 : return 88;
          case 32 : return 90;
          case 33 : return 91;
          case 28 : return 161;
          case 5 : return 53;
          case 3 : return 20;
          case 0 : return 191;
          case 4 : return 24;
          case 1 : return 283;
          case 6 : return 380;
          case 22 : return 279;
          case 7 : return 381;
          case 11 : return 386;
          case 12 : return 388;
          case 13 : return 390;
          case 10 : return 384;
          case 8 : return 382;
          case 15 : return 387;
          case 16 : return 389;
          case 17 : return 391;
          case 14 : return 385;
          case 9 : return 383;
          case 42 : return 132;
          case 43 : return 632;
          case 51 : return 59;
          case 52 : return 167;
          case 53 : return 392;
          case 59 : return 522;
          case 60 : return 503;
          case 61 : return 340;
          case 62 : return 340;
          case 63 : return 339;
          case 64 : return 338;
          case 65 : return 338;
          case 66 : return 530;
          case 67 : return 525;
          case 68 : return 540;
          case 69 : return 394;
          case 70 : return 171;
          default: return 0;
         }

     case 135 :
       switch( element )
         {
          case 35 : return 583;
          default: return 0;
         }

     case 136 :
       switch( element )
         {
          case 35 : return 584;
          default: return 0;
         }

     case 137 :
       switch( element )
         {
          case 35 : return 585;
          default: return 0;
         }

     case 138 :
       switch( element )
         {
          case 35 : return 583;
          default: return 0;
         }

     case 139 :
       switch( element )
         {
          case 35 : return 584;
          default: return 0;
         }

     case 140 :
       switch( element )
         {
          case 35 : return 585;
          default: return 0;
         }

     case 141 :
       switch( element )
         {
          case 35 : return 583;
          default: return 0;
         }

     case 142 :
       switch( element )
         {
          case 35 : return 584;
          default: return 0;
         }

     case 143 :
       switch( element )
         {
          case 35 : return 585;
          default: return 0;
         }

     case 144 :
       switch( element )
         {
          case 35 : return 583;
          default: return 0;
         }

     case 145 :
       switch( element )
         {
          case 35 : return 584;
          default: return 0;
         }

     case 146 :
       switch( element )
         {
          case 35 : return 585;
          default: return 0;
         }

     case 147 :
       switch( element )
         {
          case 35 : return 580;
          case 28 : return 48;
          case 5 : return 49;
          case 3 : return 15;
          case 25 : return 160;
          case 6 : return 420;
          case 19 : return 462;
          case 7 : return 423;
          case 11 : return 438;
          case 12 : return 444;
          case 13 : return 450;
          case 10 : return 432;
          case 20 : return 601;
          case 18 : return 459;
          case 21 : return 595;
          case 8 : return 426;
          case 15 : return 441;
          case 16 : return 447;
          case 17 : return 453;
          case 14 : return 435;
          case 9 : return 429;
          case 42 : return 155;
          case 43 : return 487;
          case 47 : return 39;
          case 49 : return 137;
          case 50 : return 465;
          case 53 : return 456;
          case 54 : return 468;
          case 55 : return 499;
          case 57 : return 484;
          default: return 0;
         }

     case 148 :
       switch( element )
         {
          case 35 : return 580;
          case 28 : return 48;
          case 5 : return 49;
          case 3 : return 15;
          case 25 : return 160;
          case 6 : return 420;
          case 19 : return 462;
          case 7 : return 423;
          case 11 : return 438;
          case 12 : return 444;
          case 13 : return 450;
          case 10 : return 432;
          case 20 : return 601;
          case 18 : return 459;
          case 21 : return 595;
          case 8 : return 426;
          case 15 : return 441;
          case 16 : return 447;
          case 17 : return 453;
          case 14 : return 435;
          case 9 : return 429;
          case 42 : return 155;
          case 43 : return 488;
          case 47 : return 39;
          case 49 : return 137;
          case 50 : return 465;
          case 53 : return 456;
          case 54 : return 468;
          case 55 : return 499;
          case 57 : return 484;
          default: return 0;
         }

     case 149 :
       switch( element )
         {
          case 35 : return 580;
          case 28 : return 48;
          case 5 : return 49;
          case 3 : return 15;
          case 25 : return 160;
          case 6 : return 420;
          case 19 : return 462;
          case 7 : return 423;
          case 11 : return 438;
          case 12 : return 444;
          case 13 : return 450;
          case 10 : return 432;
          case 20 : return 601;
          case 18 : return 459;
          case 21 : return 595;
          case 8 : return 426;
          case 15 : return 441;
          case 16 : return 447;
          case 17 : return 453;
          case 14 : return 435;
          case 9 : return 429;
          case 42 : return 155;
          case 43 : return 489;
          case 47 : return 39;
          case 49 : return 137;
          case 50 : return 465;
          case 53 : return 456;
          case 54 : return 468;
          case 55 : return 499;
          case 57 : return 484;
          default: return 0;
         }

     case 150 :
       switch( element )
         {
          case 35 : return 580;
          case 28 : return 48;
          case 5 : return 49;
          case 3 : return 15;
          case 25 : return 160;
          case 6 : return 420;
          case 19 : return 462;
          case 7 : return 423;
          case 11 : return 438;
          case 12 : return 444;
          case 13 : return 450;
          case 10 : return 432;
          case 20 : return 601;
          case 18 : return 459;
          case 21 : return 595;
          case 8 : return 426;
          case 15 : return 441;
          case 16 : return 447;
          case 17 : return 453;
          case 14 : return 435;
          case 9 : return 429;
          case 42 : return 155;
          case 43 : return 490;
          case 47 : return 39;
          case 49 : return 137;
          case 50 : return 465;
          case 53 : return 456;
          case 54 : return 468;
          case 55 : return 499;
          case 57 : return 484;
          default: return 0;
         }

     case 151 :
       switch( element )
         {
          case 35 : return 580;
          case 28 : return 48;
          case 5 : return 49;
          case 3 : return 15;
          case 24 : return 572;
          case 6 : return 420;
          case 19 : return 462;
          case 23 : return 598;
          case 7 : return 423;
          case 11 : return 438;
          case 12 : return 444;
          case 13 : return 450;
          case 10 : return 432;
          case 20 : return 601;
          case 18 : return 459;
          case 21 : return 596;
          case 8 : return 426;
          case 15 : return 441;
          case 16 : return 447;
          case 17 : return 453;
          case 14 : return 435;
          case 9 : return 429;
          case 42 : return 155;
          case 43 : return 7;
          case 45 : return 2;
          case 46 : return 3;
          case 47 : return 4;
          case 48 : return 5;
          case 49 : return 137;
          case 50 : return 465;
          case 53 : return 456;
          case 54 : return 468;
          case 55 : return 501;
          case 57 : return 483;
          default: return 0;
         }

     case 152 :
       switch( element )
         {
          case 35 : return 580;
          case 28 : return 48;
          case 5 : return 49;
          case 3 : return 15;
          case 24 : return 572;
          case 6 : return 420;
          case 19 : return 462;
          case 23 : return 598;
          case 7 : return 423;
          case 11 : return 438;
          case 12 : return 444;
          case 13 : return 450;
          case 10 : return 432;
          case 20 : return 601;
          case 18 : return 459;
          case 21 : return 596;
          case 8 : return 426;
          case 15 : return 441;
          case 16 : return 447;
          case 17 : return 453;
          case 14 : return 435;
          case 9 : return 429;
          case 42 : return 155;
          case 43 : return 656;
          case 45 : return 2;
          case 46 : return 3;
          case 47 : return 4;
          case 48 : return 5;
          case 49 : return 137;
          case 50 : return 465;
          case 53 : return 456;
          case 54 : return 468;
          case 55 : return 501;
          case 57 : return 483;
          default: return 0;
         }

     case 153 :
       switch( element )
         {
          case 35 : return 574;
          case 28 : return 44;
          case 5 : return 45;
          case 3 : return 13;
          case 6 : return 418;
          case 19 : return 460;
          case 7 : return 421;
          case 11 : return 436;
          case 12 : return 442;
          case 13 : return 448;
          case 10 : return 430;
          case 20 : return 600;
          case 18 : return 457;
          case 8 : return 424;
          case 15 : return 439;
          case 16 : return 445;
          case 17 : return 451;
          case 14 : return 433;
          case 9 : return 427;
          case 42 : return 153;
          case 49 : return 135;
          case 50 : return 463;
          case 53 : return 454;
          case 54 : return 466;
          case 55 : return 494;
          case 56 : return 531;
          case 57 : return 481;
          default: return 0;
         }

     case 154 :
       switch( element )
         {
          case 35 : return 574;
          case 28 : return 44;
          case 5 : return 45;
          case 3 : return 13;
          case 6 : return 418;
          case 19 : return 460;
          case 7 : return 421;
          case 11 : return 436;
          case 12 : return 442;
          case 13 : return 448;
          case 10 : return 430;
          case 20 : return 600;
          case 18 : return 457;
          case 8 : return 424;
          case 15 : return 439;
          case 16 : return 445;
          case 17 : return 451;
          case 14 : return 433;
          case 9 : return 427;
          case 42 : return 153;
          case 49 : return 135;
          case 50 : return 463;
          case 53 : return 454;
          case 54 : return 466;
          case 55 : return 494;
          case 56 : return 532;
          case 57 : return 481;
          default: return 0;
         }

     case 155 :
       switch( element )
         {
          case 35 : return 574;
          case 28 : return 44;
          case 5 : return 45;
          case 3 : return 13;
          case 6 : return 418;
          case 19 : return 460;
          case 7 : return 421;
          case 11 : return 436;
          case 12 : return 442;
          case 13 : return 448;
          case 10 : return 430;
          case 20 : return 600;
          case 18 : return 457;
          case 8 : return 424;
          case 15 : return 439;
          case 16 : return 445;
          case 17 : return 451;
          case 14 : return 433;
          case 9 : return 427;
          case 42 : return 153;
          case 49 : return 135;
          case 50 : return 463;
          case 53 : return 454;
          case 54 : return 466;
          case 55 : return 494;
          case 56 : return 533;
          case 57 : return 481;
          default: return 0;
         }

     case 156 :
       switch( element )
         {
          case 35 : return 574;
          case 28 : return 44;
          case 5 : return 45;
          case 3 : return 13;
          case 6 : return 418;
          case 19 : return 460;
          case 7 : return 421;
          case 11 : return 436;
          case 12 : return 442;
          case 13 : return 448;
          case 10 : return 430;
          case 20 : return 600;
          case 18 : return 457;
          case 8 : return 424;
          case 15 : return 439;
          case 16 : return 445;
          case 17 : return 451;
          case 14 : return 433;
          case 9 : return 427;
          case 42 : return 153;
          case 49 : return 135;
          case 50 : return 463;
          case 53 : return 454;
          case 54 : return 466;
          case 55 : return 495;
          case 57 : return 481;
          default: return 0;
         }

     case 157 :
       switch( element )
         {
          case 35 : return 577;
          case 28 : return 46;
          case 5 : return 47;
          case 3 : return 14;
          case 6 : return 419;
          case 19 : return 461;
          case 7 : return 422;
          case 11 : return 437;
          case 12 : return 443;
          case 13 : return 449;
          case 10 : return 431;
          case 20 : return 602;
          case 18 : return 458;
          case 8 : return 425;
          case 15 : return 440;
          case 16 : return 446;
          case 17 : return 452;
          case 14 : return 434;
          case 9 : return 428;
          case 42 : return 154;
          case 49 : return 136;
          case 50 : return 464;
          case 53 : return 455;
          case 54 : return 467;
          case 55 : return 496;
          case 57 : return 482;
          default: return 0;
         }

     case 158 :
       switch( element )
         {
          case 35 : return 577;
          case 28 : return 46;
          case 5 : return 47;
          case 3 : return 14;
          case 6 : return 419;
          case 19 : return 461;
          case 7 : return 422;
          case 11 : return 437;
          case 12 : return 443;
          case 13 : return 449;
          case 10 : return 431;
          case 20 : return 602;
          case 18 : return 458;
          case 8 : return 425;
          case 15 : return 440;
          case 16 : return 446;
          case 17 : return 452;
          case 14 : return 434;
          case 9 : return 428;
          case 42 : return 154;
          case 49 : return 136;
          case 50 : return 464;
          case 53 : return 455;
          case 54 : return 467;
          case 55 : return 497;
          case 57 : return 482;
          default: return 0;
         }

     case 159 :
       switch( element )
         {
          case 35 : return 577;
          case 28 : return 46;
          case 5 : return 47;
          case 3 : return 14;
          case 6 : return 419;
          case 19 : return 461;
          case 7 : return 422;
          case 11 : return 437;
          case 12 : return 443;
          case 13 : return 449;
          case 10 : return 431;
          case 20 : return 602;
          case 18 : return 458;
          case 8 : return 425;
          case 15 : return 440;
          case 16 : return 446;
          case 17 : return 452;
          case 14 : return 434;
          case 9 : return 428;
          case 42 : return 154;
          case 49 : return 136;
          case 50 : return 464;
          case 53 : return 455;
          case 54 : return 467;
          case 55 : return 498;
          case 57 : return 482;
          default: return 0;
         }

     case 160 :
       switch( element )
         {
          case 35 : return 580;
          case 28 : return 48;
          case 5 : return 49;
          case 3 : return 15;
          case 6 : return 420;
          case 19 : return 462;
          case 7 : return 423;
          case 11 : return 438;
          case 12 : return 444;
          case 13 : return 450;
          case 10 : return 432;
          case 20 : return 603;
          case 18 : return 459;
          case 8 : return 426;
          case 15 : return 441;
          case 16 : return 447;
          case 17 : return 453;
          case 14 : return 435;
          case 9 : return 429;
          case 42 : return 155;
          case 48 : return 40;
          case 49 : return 137;
          case 50 : return 465;
          case 53 : return 456;
          case 54 : return 468;
          case 55 : return 500;
          case 57 : return 486;
          default: return 0;
         }

     case 161 :
       switch( element )
         {
          case 35 : return 608;
          case 3 : return 565;
          default: return 0;
         }

     case 162 :
       switch( element )
         {
          default: return 0;
         }

     case 163 :
       switch( element )
         {
          default: return 0;
         }

     case 164 :
       switch( element )
         {
          default: return 0;
         }

     case 165 :
       switch( element )
         {
          default: return 0;
         }

     case 166 :
       switch( element )
         {
          default: return 0;
         }

     case 167 :
       switch( element )
         {
          default: return 0;
         }

     case 168 :
       switch( element )
         {
          default: return 0;
         }

     case 169 :
       switch( element )
         {
          default: return 0;
         }

     case 170 :
       switch( element )
         {
          default: return 0;
         }

     case 171 :
       switch( element )
         {
          default: return 0;
         }

     case 172 :
       switch( element )
         {
          default: return 0;
         }

     case 173 :
       switch( element )
         {
          default: return 0;
         }

     case 174 :
       switch( element )
         {
          default: return 0;
         }

     case 175 :
       switch( element )
         {
          default: return 0;
         }

     case 176 :
       switch( element )
         {
          default: return 0;
         }

     case 177 :
       switch( element )
         {
          default: return 0;
         }

     case 178 :
       switch( element )
         {
          default: return 0;
         }

     case 179 :
       switch( element )
         {
          default: return 0;
         }

     case 180 :
       switch( element )
         {
          default: return 0;
         }

     case 181 :
       switch( element )
         {
          default: return 0;
         }

     case 182 :
       switch( element )
         {
          default: return 0;
         }

     case 183 :
       switch( element )
         {
          default: return 0;
         }

     case 184 :
       switch( element )
         {
          default: return 0;
         }

     case 185 :
       switch( element )
         {
          default: return 0;
         }

     case 186 :
       switch( element )
         {
          default: return 0;
         }

     case 187 :
       switch( element )
         {
          default: return 0;
         }

     case 188 :
       switch( element )
         {
          default: return 0;
         }

     case 189 :
       switch( element )
         {
          default: return 0;
         }

     case 190 :
       switch( element )
         {
          case 28 : return 628;
          default: return 0;
         }

     case 191 :
       switch( element )
         {
          case 28 : return 629;
          default: return 0;
         }

     case 192 :
       switch( element )
         {
          case 28 : return 630;
          default: return 0;
         }

     case 193 :
       switch( element )
         {
          case 28 : return 631;
          default: return 0;
         }

     case 194 :
       switch( element )
         {
          case 31 : return 590;
          case 28 : return 586;
          case 40 : return 127;
          default: return 0;
         }

     case 195 :
       switch( element )
         {
          case 40 : return 127;
          default: return 0;
         }

     case 196 :
       switch( element )
         {
          default: return 0;
         }

     case 197 :
       switch( element )
         {
          case 31 : return 591;
          case 28 : return 587;
          case 40 : return 128;
          default: return 0;
         }

     case 198 :
       switch( element )
         {
          case 40 : return 128;
          default: return 0;
         }

     case 199 :
       switch( element )
         {
          default: return 0;
         }

     case 200 :
       switch( element )
         {
          case 31 : return 592;
          case 28 : return 588;
          case 40 : return 129;
          default: return 0;
         }

     case 201 :
       switch( element )
         {
          case 31 : return 593;
          case 28 : return 589;
          case 40 : return 130;
          default: return 0;
         }

     case 202 :
       switch( element )
         {
          case 40 : return 129;
          default: return 0;
         }

     case 203 :
       switch( element )
         {
          default: return 0;
         }

     case 204 :
       switch( element )
         {
          case 40 : return 130;
          default: return 0;
         }

     case 205 :
       switch( element )
         {
          default: return 0;
         }

     case 206 :
       switch( element )
         {
          case 31 : return 590;
          case 28 : return 586;
          case 40 : return 127;
          default: return 0;
         }

     case 207 :
       switch( element )
         {
          case 40 : return 127;
          default: return 0;
         }

     case 208 :
       switch( element )
         {
          default: return 0;
         }

     case 209 :
       switch( element )
         {
          case 31 : return 591;
          case 28 : return 587;
          case 40 : return 128;
          default: return 0;
         }

     case 210 :
       switch( element )
         {
          case 40 : return 128;
          default: return 0;
         }

     case 211 :
       switch( element )
         {
          default: return 0;
         }

     case 212 :
       switch( element )
         {
          case 31 : return 592;
          case 28 : return 588;
          case 40 : return 129;
          default: return 0;
         }

     case 213 :
       switch( element )
         {
          case 31 : return 593;
          case 28 : return 589;
          case 40 : return 130;
          default: return 0;
         }

     case 214 :
       switch( element )
         {
          case 40 : return 129;
          default: return 0;
         }

     case 215 :
       switch( element )
         {
          default: return 0;
         }

     case 216 :
       switch( element )
         {
          case 40 : return 130;
          default: return 0;
         }

     case 217 :
       switch( element )
         {
          default: return 0;
         }

     case 218 :
       switch( element )
         {
          case 31 : return 590;
          case 28 : return 586;
          case 40 : return 127;
          default: return 0;
         }

     case 219 :
       switch( element )
         {
          case 40 : return 127;
          default: return 0;
         }

     case 220 :
       switch( element )
         {
          default: return 0;
         }

     case 221 :
       switch( element )
         {
          case 31 : return 591;
          case 28 : return 587;
          case 40 : return 128;
          default: return 0;
         }

     case 222 :
       switch( element )
         {
          case 40 : return 128;
          default: return 0;
         }

     case 223 :
       switch( element )
         {
          default: return 0;
         }

     case 224 :
       switch( element )
         {
          case 31 : return 592;
          case 28 : return 588;
          case 40 : return 129;
          default: return 0;
         }

     case 225 :
       switch( element )
         {
          case 31 : return 593;
          case 28 : return 589;
          case 40 : return 130;
          default: return 0;
         }

     case 226 :
       switch( element )
         {
          case 40 : return 129;
          default: return 0;
         }

     case 227 :
       switch( element )
         {
          default: return 0;
         }

     case 228 :
       switch( element )
         {
          case 40 : return 130;
          default: return 0;
         }

     case 229 :
       switch( element )
         {
          default: return 0;
         }

     case 230 :
       switch( element )
         {
          case 31 : return 590;
          case 28 : return 586;
          case 40 : return 127;
          default: return 0;
         }

     case 231 :
       switch( element )
         {
          case 40 : return 127;
          default: return 0;
         }

     case 232 :
       switch( element )
         {
          default: return 0;
         }

     case 233 :
       switch( element )
         {
          case 31 : return 591;
          case 28 : return 587;
          case 40 : return 128;
          default: return 0;
         }

     case 234 :
       switch( element )
         {
          case 40 : return 128;
          default: return 0;
         }

     case 235 :
       switch( element )
         {
          default: return 0;
         }

     case 236 :
       switch( element )
         {
          case 31 : return 592;
          case 28 : return 588;
          case 40 : return 129;
          default: return 0;
         }

     case 237 :
       switch( element )
         {
          case 31 : return 593;
          case 28 : return 589;
          case 40 : return 130;
          default: return 0;
         }

     case 238 :
       switch( element )
         {
          case 40 : return 129;
          default: return 0;
         }

     case 239 :
       switch( element )
         {
          default: return 0;
         }

     case 240 :
       switch( element )
         {
          case 40 : return 130;
          default: return 0;
         }

     case 241 :
       switch( element )
         {
          default: return 0;
         }

     case 242 :
       switch( element )
         {
          case 31 : return 590;
          case 28 : return 586;
          case 40 : return 127;
          default: return 0;
         }

     case 243 :
       switch( element )
         {
          case 40 : return 127;
          default: return 0;
         }

     case 244 :
       switch( element )
         {
          default: return 0;
         }

     case 245 :
       switch( element )
         {
          case 31 : return 591;
          case 28 : return 587;
          case 40 : return 128;
          default: return 0;
         }

     case 246 :
       switch( element )
         {
          case 40 : return 128;
          default: return 0;
         }

     case 247 :
       switch( element )
         {
          default: return 0;
         }

     case 248 :
       switch( element )
         {
          case 31 : return 592;
          case 28 : return 588;
          case 40 : return 129;
          default: return 0;
         }

     case 249 :
       switch( element )
         {
          case 31 : return 593;
          case 28 : return 589;
          case 40 : return 130;
          default: return 0;
         }

     case 250 :
       switch( element )
         {
          case 40 : return 129;
          default: return 0;
         }

     case 251 :
       switch( element )
         {
          default: return 0;
         }

     case 252 :
       switch( element )
         {
          case 40 : return 130;
          default: return 0;
         }

     case 253 :
       switch( element )
         {
          default: return 0;
         }

     case 254 :
       switch( element )
         {
          case 31 : return 590;
          case 28 : return 586;
          case 40 : return 127;
          default: return 0;
         }

     case 255 :
       switch( element )
         {
          case 40 : return 127;
          default: return 0;
         }

     case 256 :
       switch( element )
         {
          default: return 0;
         }

     case 257 :
       switch( element )
         {
          case 31 : return 591;
          case 28 : return 587;
          case 40 : return 128;
          default: return 0;
         }

     case 258 :
       switch( element )
         {
          case 40 : return 128;
          default: return 0;
         }

     case 259 :
       switch( element )
         {
          default: return 0;
         }

     case 260 :
       switch( element )
         {
          case 31 : return 592;
          case 28 : return 588;
          case 40 : return 129;
          default: return 0;
         }

     case 261 :
       switch( element )
         {
          case 31 : return 593;
          case 28 : return 589;
          case 40 : return 130;
          default: return 0;
         }

     case 262 :
       switch( element )
         {
          case 40 : return 129;
          default: return 0;
         }

     case 263 :
       switch( element )
         {
          default: return 0;
         }

     case 264 :
       switch( element )
         {
          case 40 : return 130;
          default: return 0;
         }

     case 265 :
       switch( element )
         {
          default: return 0;
         }

     case 266 :
       switch( element )
         {
          case 31 : return 590;
          case 28 : return 586;
          case 40 : return 127;
          default: return 0;
         }

     case 267 :
       switch( element )
         {
          case 40 : return 127;
          default: return 0;
         }

     case 268 :
       switch( element )
         {
          default: return 0;
         }

     case 269 :
       switch( element )
         {
          case 31 : return 591;
          case 28 : return 587;
          case 40 : return 128;
          default: return 0;
         }

     case 270 :
       switch( element )
         {
          case 40 : return 128;
          default: return 0;
         }

     case 271 :
       switch( element )
         {
          default: return 0;
         }

     case 272 :
       switch( element )
         {
          case 31 : return 592;
          case 28 : return 588;
          case 40 : return 129;
          default: return 0;
         }

     case 273 :
       switch( element )
         {
          case 31 : return 593;
          case 28 : return 589;
          case 40 : return 130;
          default: return 0;
         }

     case 274 :
       switch( element )
         {
          case 40 : return 129;
          default: return 0;
         }

     case 275 :
       switch( element )
         {
          default: return 0;
         }

     case 276 :
       switch( element )
         {
          case 40 : return 130;
          default: return 0;
         }

     case 277 :
       switch( element )
         {
          default: return 0;
         }

     case 278 :
       switch( element )
         {
          default: return 0;
         }

     case 279 :
       switch( element )
         {
          default: return 0;
         }

     case 280 :
       switch( element )
         {
          default: return 0;
         }

     case 281 :
       switch( element )
         {
          default: return 0;
         }

     case 282 :
       switch( element )
         {
          default: return 0;
         }

     case 283 :
       switch( element )
         {
          default: return 0;
         }

     case 284 :
       switch( element )
         {
          default: return 0;
         }

     case 285 :
       switch( element )
         {
          default: return 0;
         }

     case 286 :
       switch( element )
         {
          default: return 0;
         }

     case 287 :
       switch( element )
         {
          default: return 0;
         }

     case 288 :
       switch( element )
         {
          default: return 0;
         }

     case 289 :
       switch( element )
         {
          default: return 0;
         }

     case 290 :
       switch( element )
         {
          case 37 : return 85;
          case 26 : return 83;
          case 31 : return 590;
          case 28 : return 586;
          case 36 : return 84;
          case 40 : return 127;
          default: return 0;
         }

     case 291 :
       switch( element )
         {
          case 37 : return 85;
          case 26 : return 83;
          case 36 : return 84;
          case 40 : return 127;
          default: return 0;
         }

     case 292 :
       switch( element )
         {
          case 37 : return 85;
          case 26 : return 83;
          case 36 : return 84;
          default: return 0;
         }

     case 293 :
       switch( element )
         {
          case 37 : return 85;
          case 26 : return 83;
          case 31 : return 590;
          case 28 : return 586;
          case 36 : return 84;
          case 40 : return 127;
          default: return 0;
         }

     case 294 :
       switch( element )
         {
          case 37 : return 85;
          case 26 : return 83;
          case 36 : return 84;
          case 40 : return 127;
          default: return 0;
         }

     case 295 :
       switch( element )
         {
          case 37 : return 85;
          case 26 : return 83;
          case 36 : return 84;
          default: return 0;
         }

     case 296 :
       switch( element )
         {
          case 37 : return 85;
          case 39 : return 162;
          case 26 : return 83;
          case 32 : return 77;
          case 33 : return 78;
          case 31 : return 590;
          case 28 : return 586;
          case 36 : return 84;
          case 40 : return 127;
          case 42 : return 551;
          default: return 0;
         }

     case 297 :
       switch( element )
         {
          case 37 : return 85;
          case 39 : return 163;
          case 26 : return 83;
          case 32 : return 77;
          case 33 : return 78;
          case 31 : return 590;
          case 28 : return 586;
          case 36 : return 84;
          case 40 : return 127;
          case 42 : return 551;
          default: return 0;
         }

     case 298 :
       switch( element )
         {
          case 37 : return 85;
          case 39 : return 164;
          case 26 : return 83;
          case 32 : return 77;
          case 33 : return 78;
          case 31 : return 590;
          case 28 : return 586;
          case 36 : return 84;
          case 40 : return 127;
          case 42 : return 551;
          default: return 0;
         }

     case 299 :
       switch( element )
         {
          case 37 : return 85;
          case 39 : return 165;
          case 26 : return 83;
          case 32 : return 77;
          case 33 : return 78;
          case 31 : return 590;
          case 28 : return 586;
          case 36 : return 84;
          case 40 : return 127;
          case 42 : return 551;
          default: return 0;
         }

     case 300 :
       switch( element )
         {
          case 37 : return 85;
          case 39 : return 174;
          case 26 : return 83;
          case 32 : return 77;
          case 33 : return 78;
          case 31 : return 590;
          case 28 : return 586;
          case 36 : return 84;
          case 40 : return 127;
          case 42 : return 551;
          default: return 0;
         }

     case 301 :
       switch( element )
         {
          case 37 : return 85;
          case 39 : return 175;
          case 26 : return 83;
          case 32 : return 77;
          case 33 : return 78;
          case 31 : return 590;
          case 28 : return 586;
          case 36 : return 84;
          case 40 : return 127;
          case 42 : return 551;
          default: return 0;
         }

     case 302 :
       switch( element )
         {
          case 37 : return 85;
          case 39 : return 176;
          case 26 : return 83;
          case 32 : return 77;
          case 33 : return 78;
          case 31 : return 590;
          case 28 : return 586;
          case 36 : return 84;
          case 40 : return 127;
          case 42 : return 551;
          default: return 0;
         }

     case 303 :
       switch( element )
         {
          case 37 : return 85;
          case 39 : return 177;
          case 26 : return 83;
          case 32 : return 77;
          case 33 : return 78;
          case 31 : return 590;
          case 28 : return 586;
          case 36 : return 84;
          case 40 : return 127;
          case 42 : return 551;
          default: return 0;
         }

     case 304 :
       switch( element )
         {
          case 37 : return 85;
          case 39 : return 162;
          case 26 : return 83;
          case 32 : return 77;
          case 33 : return 78;
          case 36 : return 84;
          case 40 : return 127;
          case 42 : return 551;
          default: return 0;
         }

     case 305 :
       switch( element )
         {
          case 37 : return 85;
          case 39 : return 163;
          case 26 : return 83;
          case 32 : return 77;
          case 33 : return 78;
          case 36 : return 84;
          case 40 : return 127;
          case 42 : return 551;
          default: return 0;
         }

     case 306 :
       switch( element )
         {
          case 37 : return 85;
          case 39 : return 164;
          case 26 : return 83;
          case 32 : return 77;
          case 33 : return 78;
          case 36 : return 84;
          case 40 : return 127;
          case 42 : return 551;
          default: return 0;
         }

     case 307 :
       switch( element )
         {
          case 37 : return 85;
          case 39 : return 165;
          case 26 : return 83;
          case 32 : return 77;
          case 33 : return 78;
          case 36 : return 84;
          case 40 : return 127;
          case 42 : return 551;
          default: return 0;
         }

     case 308 :
       switch( element )
         {
          case 37 : return 85;
          case 39 : return 174;
          case 26 : return 83;
          case 32 : return 77;
          case 33 : return 78;
          case 36 : return 84;
          case 40 : return 127;
          case 42 : return 551;
          default: return 0;
         }

     case 309 :
       switch( element )
         {
          case 37 : return 85;
          case 39 : return 175;
          case 26 : return 83;
          case 32 : return 77;
          case 33 : return 78;
          case 36 : return 84;
          case 40 : return 127;
          case 42 : return 551;
          default: return 0;
         }

     case 310 :
       switch( element )
         {
          case 37 : return 85;
          case 39 : return 176;
          case 26 : return 83;
          case 32 : return 77;
          case 33 : return 78;
          case 36 : return 84;
          case 40 : return 127;
          case 42 : return 551;
          default: return 0;
         }

     case 311 :
       switch( element )
         {
          case 37 : return 85;
          case 39 : return 177;
          case 26 : return 83;
          case 32 : return 77;
          case 33 : return 78;
          case 36 : return 84;
          case 40 : return 127;
          case 42 : return 551;
          default: return 0;
         }

     case 312 :
       switch( element )
         {
          case 37 : return 85;
          case 39 : return 162;
          case 26 : return 83;
          case 32 : return 77;
          case 33 : return 78;
          case 36 : return 84;
          case 42 : return 551;
          default: return 0;
         }

     case 313 :
       switch( element )
         {
          case 37 : return 85;
          case 39 : return 163;
          case 26 : return 83;
          case 32 : return 77;
          case 33 : return 78;
          case 36 : return 84;
          case 42 : return 551;
          default: return 0;
         }

     case 314 :
       switch( element )
         {
          case 37 : return 85;
          case 39 : return 164;
          case 26 : return 83;
          case 32 : return 77;
          case 33 : return 78;
          case 36 : return 84;
          case 42 : return 551;
          default: return 0;
         }

     case 315 :
       switch( element )
         {
          case 37 : return 85;
          case 39 : return 165;
          case 26 : return 83;
          case 32 : return 77;
          case 33 : return 78;
          case 36 : return 84;
          case 42 : return 551;
          default: return 0;
         }

     case 316 :
       switch( element )
         {
          case 37 : return 85;
          case 39 : return 174;
          case 26 : return 83;
          case 32 : return 77;
          case 33 : return 78;
          case 36 : return 84;
          case 42 : return 551;
          default: return 0;
         }

     case 317 :
       switch( element )
         {
          case 37 : return 85;
          case 39 : return 175;
          case 26 : return 83;
          case 32 : return 77;
          case 33 : return 78;
          case 36 : return 84;
          case 42 : return 551;
          default: return 0;
         }

     case 318 :
       switch( element )
         {
          case 37 : return 85;
          case 39 : return 176;
          case 26 : return 83;
          case 32 : return 77;
          case 33 : return 78;
          case 36 : return 84;
          case 42 : return 551;
          default: return 0;
         }

     case 319 :
       switch( element )
         {
          case 37 : return 85;
          case 39 : return 177;
          case 26 : return 83;
          case 32 : return 77;
          case 33 : return 78;
          case 36 : return 84;
          case 42 : return 551;
          default: return 0;
         }

     case 320 :
       switch( element )
         {
          case 37 : return 94;
          case 26 : return 92;
          case 31 : return 591;
          case 28 : return 587;
          case 36 : return 93;
          case 40 : return 128;
          default: return 0;
         }

     case 321 :
       switch( element )
         {
          case 37 : return 94;
          case 26 : return 92;
          case 36 : return 93;
          case 40 : return 128;
          default: return 0;
         }

     case 322 :
       switch( element )
         {
          case 37 : return 94;
          case 26 : return 92;
          case 36 : return 93;
          default: return 0;
         }

     case 323 :
       switch( element )
         {
          case 37 : return 103;
          case 26 : return 101;
          case 31 : return 592;
          case 28 : return 588;
          case 36 : return 102;
          case 40 : return 129;
          default: return 0;
         }

     case 324 :
       switch( element )
         {
          case 37 : return 112;
          case 26 : return 110;
          case 31 : return 593;
          case 28 : return 589;
          case 36 : return 111;
          case 40 : return 130;
          default: return 0;
         }

     case 325 :
       switch( element )
         {
          case 37 : return 103;
          case 26 : return 101;
          case 36 : return 102;
          case 40 : return 129;
          default: return 0;
         }

     case 326 :
       switch( element )
         {
          case 37 : return 103;
          case 26 : return 101;
          case 36 : return 102;
          default: return 0;
         }

     case 327 :
       switch( element )
         {
          case 37 : return 112;
          case 26 : return 110;
          case 36 : return 111;
          case 40 : return 130;
          default: return 0;
         }

     case 328 :
       switch( element )
         {
          case 37 : return 112;
          case 26 : return 110;
          case 36 : return 111;
          default: return 0;
         }

     case 329 :
       switch( element )
         {
          case 37 : return 94;
          case 26 : return 92;
          case 31 : return 591;
          case 28 : return 587;
          case 36 : return 93;
          case 40 : return 128;
          default: return 0;
         }

     case 330 :
       switch( element )
         {
          case 37 : return 94;
          case 26 : return 92;
          case 36 : return 93;
          case 40 : return 128;
          default: return 0;
         }

     case 331 :
       switch( element )
         {
          case 37 : return 94;
          case 26 : return 92;
          case 36 : return 93;
          default: return 0;
         }

     case 332 :
       switch( element )
         {
          case 37 : return 103;
          case 26 : return 101;
          case 31 : return 592;
          case 28 : return 588;
          case 36 : return 102;
          case 40 : return 129;
          default: return 0;
         }

     case 333 :
       switch( element )
         {
          case 37 : return 112;
          case 26 : return 110;
          case 31 : return 593;
          case 28 : return 589;
          case 36 : return 111;
          case 40 : return 130;
          default: return 0;
         }

     case 334 :
       switch( element )
         {
          case 37 : return 103;
          case 26 : return 101;
          case 36 : return 102;
          case 40 : return 129;
          default: return 0;
         }

     case 335 :
       switch( element )
         {
          case 37 : return 103;
          case 26 : return 101;
          case 36 : return 102;
          default: return 0;
         }

     case 336 :
       switch( element )
         {
          case 37 : return 112;
          case 26 : return 110;
          case 36 : return 111;
          case 40 : return 130;
          default: return 0;
         }

     case 337 :
       switch( element )
         {
          case 37 : return 112;
          case 26 : return 110;
          case 36 : return 111;
          default: return 0;
         }

     case 338 :
       switch( element )
         {
          case 37 : return 94;
          case 26 : return 92;
          case 32 : return 86;
          case 33 : return 87;
          case 31 : return 591;
          case 28 : return 587;
          case 36 : return 93;
          case 40 : return 128;
          case 42 : return 552;
          default: return 0;
         }

     case 339 :
       switch( element )
         {
          case 37 : return 94;
          case 26 : return 92;
          case 32 : return 86;
          case 33 : return 87;
          case 36 : return 93;
          case 40 : return 128;
          case 42 : return 552;
          default: return 0;
         }

     case 340 :
       switch( element )
         {
          case 37 : return 94;
          case 26 : return 92;
          case 32 : return 86;
          case 33 : return 87;
          case 36 : return 93;
          case 42 : return 552;
          default: return 0;
         }

     case 341 :
       switch( element )
         {
          case 37 : return 94;
          case 26 : return 92;
          case 32 : return 86;
          case 33 : return 87;
          case 31 : return 591;
          case 28 : return 587;
          case 36 : return 93;
          case 40 : return 128;
          case 42 : return 552;
          default: return 0;
         }

     case 342 :
       switch( element )
         {
          case 37 : return 94;
          case 26 : return 92;
          case 32 : return 86;
          case 33 : return 87;
          case 36 : return 93;
          case 40 : return 128;
          case 42 : return 552;
          default: return 0;
         }

     case 343 :
       switch( element )
         {
          case 37 : return 94;
          case 26 : return 92;
          case 32 : return 86;
          case 33 : return 87;
          case 36 : return 93;
          case 42 : return 552;
          default: return 0;
         }

     case 344 :
       switch( element )
         {
          case 37 : return 94;
          case 26 : return 92;
          case 32 : return 86;
          case 33 : return 87;
          case 31 : return 591;
          case 28 : return 587;
          case 36 : return 93;
          case 40 : return 128;
          case 42 : return 552;
          default: return 0;
         }

     case 345 :
       switch( element )
         {
          case 37 : return 94;
          case 26 : return 92;
          case 32 : return 86;
          case 33 : return 87;
          case 36 : return 93;
          case 40 : return 128;
          case 42 : return 552;
          default: return 0;
         }

     case 346 :
       switch( element )
         {
          case 37 : return 94;
          case 26 : return 92;
          case 32 : return 86;
          case 33 : return 87;
          case 36 : return 93;
          case 42 : return 552;
          default: return 0;
         }

     case 347 :
       switch( element )
         {
          case 37 : return 103;
          case 26 : return 101;
          case 32 : return 95;
          case 33 : return 96;
          case 31 : return 592;
          case 28 : return 588;
          case 36 : return 102;
          case 29 : return 11;
          case 40 : return 129;
          case 42 : return 553;
          default: return 0;
         }

     case 348 :
       switch( element )
         {
          case 37 : return 103;
          case 26 : return 101;
          case 32 : return 95;
          case 33 : return 96;
          case 31 : return 592;
          case 28 : return 588;
          case 36 : return 102;
          case 29 : return 12;
          case 40 : return 129;
          case 42 : return 553;
          default: return 0;
         }

     case 349 :
       switch( element )
         {
          case 37 : return 103;
          case 26 : return 101;
          case 32 : return 95;
          case 33 : return 96;
          case 31 : return 592;
          case 28 : return 588;
          case 36 : return 102;
          case 29 : return 43;
          case 40 : return 129;
          case 42 : return 553;
          default: return 0;
         }

     case 350 :
       switch( element )
         {
          case 37 : return 103;
          case 26 : return 101;
          case 32 : return 95;
          case 33 : return 96;
          case 31 : return 592;
          case 28 : return 588;
          case 36 : return 102;
          case 29 : return 659;
          case 40 : return 129;
          case 42 : return 553;
          default: return 0;
         }

     case 351 :
       switch( element )
         {
          case 37 : return 112;
          case 26 : return 110;
          case 32 : return 104;
          case 33 : return 105;
          case 31 : return 593;
          case 28 : return 589;
          case 36 : return 111;
          case 40 : return 130;
          case 41 : return 186;
          case 42 : return 554;
          default: return 0;
         }

     case 352 :
       switch( element )
         {
          case 37 : return 112;
          case 26 : return 110;
          case 32 : return 104;
          case 33 : return 105;
          case 31 : return 593;
          case 28 : return 589;
          case 36 : return 111;
          case 40 : return 130;
          case 41 : return 187;
          case 42 : return 554;
          default: return 0;
         }

     case 353 :
       switch( element )
         {
          case 37 : return 112;
          case 26 : return 110;
          case 32 : return 104;
          case 33 : return 105;
          case 31 : return 593;
          case 28 : return 589;
          case 36 : return 111;
          case 40 : return 130;
          case 41 : return 188;
          case 42 : return 554;
          default: return 0;
         }

     case 354 :
       switch( element )
         {
          case 37 : return 112;
          case 26 : return 110;
          case 32 : return 104;
          case 33 : return 105;
          case 31 : return 593;
          case 28 : return 589;
          case 36 : return 111;
          case 40 : return 130;
          case 41 : return 189;
          case 42 : return 554;
          default: return 0;
         }

     case 355 :
       switch( element )
         {
          case 37 : return 112;
          case 26 : return 110;
          case 32 : return 104;
          case 33 : return 105;
          case 31 : return 593;
          case 28 : return 589;
          case 36 : return 111;
          case 40 : return 130;
          case 41 : return 478;
          case 42 : return 554;
          default: return 0;
         }

     case 356 :
       switch( element )
         {
          case 37 : return 112;
          case 26 : return 110;
          case 32 : return 104;
          case 33 : return 105;
          case 31 : return 593;
          case 28 : return 589;
          case 36 : return 111;
          case 40 : return 130;
          case 41 : return 479;
          case 42 : return 554;
          default: return 0;
         }

     case 357 :
       switch( element )
         {
          case 37 : return 112;
          case 26 : return 110;
          case 32 : return 104;
          case 33 : return 105;
          case 31 : return 593;
          case 28 : return 589;
          case 36 : return 111;
          case 40 : return 130;
          case 41 : return 480;
          case 42 : return 554;
          default: return 0;
         }

     case 358 :
       switch( element )
         {
          case 37 : return 103;
          case 26 : return 101;
          case 32 : return 95;
          case 33 : return 96;
          case 36 : return 102;
          case 29 : return 11;
          case 40 : return 129;
          case 42 : return 553;
          default: return 0;
         }

     case 359 :
       switch( element )
         {
          case 37 : return 103;
          case 26 : return 101;
          case 32 : return 95;
          case 33 : return 96;
          case 36 : return 102;
          case 29 : return 12;
          case 40 : return 129;
          case 42 : return 553;
          default: return 0;
         }

     case 360 :
       switch( element )
         {
          case 37 : return 103;
          case 26 : return 101;
          case 32 : return 95;
          case 33 : return 96;
          case 36 : return 102;
          case 29 : return 43;
          case 40 : return 129;
          case 42 : return 553;
          default: return 0;
         }

     case 361 :
       switch( element )
         {
          case 37 : return 103;
          case 26 : return 101;
          case 32 : return 95;
          case 33 : return 96;
          case 36 : return 102;
          case 29 : return 659;
          case 40 : return 129;
          case 42 : return 553;
          default: return 0;
         }

     case 362 :
       switch( element )
         {
          case 37 : return 103;
          case 26 : return 101;
          case 32 : return 95;
          case 33 : return 96;
          case 36 : return 102;
          case 29 : return 11;
          case 42 : return 553;
          default: return 0;
         }

     case 363 :
       switch( element )
         {
          case 37 : return 103;
          case 26 : return 101;
          case 32 : return 95;
          case 33 : return 96;
          case 36 : return 102;
          case 29 : return 12;
          case 42 : return 553;
          default: return 0;
         }

     case 364 :
       switch( element )
         {
          case 37 : return 103;
          case 26 : return 101;
          case 32 : return 95;
          case 33 : return 96;
          case 36 : return 102;
          case 29 : return 43;
          case 42 : return 553;
          default: return 0;
         }

     case 365 :
       switch( element )
         {
          case 37 : return 103;
          case 26 : return 101;
          case 32 : return 95;
          case 33 : return 96;
          case 36 : return 102;
          case 29 : return 659;
          case 42 : return 553;
          default: return 0;
         }

     case 366 :
       switch( element )
         {
          case 37 : return 112;
          case 26 : return 110;
          case 32 : return 104;
          case 33 : return 105;
          case 36 : return 111;
          case 40 : return 130;
          case 41 : return 186;
          case 42 : return 554;
          default: return 0;
         }

     case 367 :
       switch( element )
         {
          case 37 : return 112;
          case 26 : return 110;
          case 32 : return 104;
          case 33 : return 105;
          case 36 : return 111;
          case 40 : return 130;
          case 41 : return 187;
          case 42 : return 554;
          default: return 0;
         }

     case 368 :
       switch( element )
         {
          case 37 : return 112;
          case 26 : return 110;
          case 32 : return 104;
          case 33 : return 105;
          case 36 : return 111;
          case 40 : return 130;
          case 41 : return 188;
          case 42 : return 554;
          default: return 0;
         }

     case 369 :
       switch( element )
         {
          case 37 : return 112;
          case 26 : return 110;
          case 32 : return 104;
          case 33 : return 105;
          case 36 : return 111;
          case 40 : return 130;
          case 41 : return 189;
          case 42 : return 554;
          default: return 0;
         }

     case 370 :
       switch( element )
         {
          case 37 : return 112;
          case 26 : return 110;
          case 32 : return 104;
          case 33 : return 105;
          case 36 : return 111;
          case 40 : return 130;
          case 41 : return 478;
          case 42 : return 554;
          default: return 0;
         }

     case 371 :
       switch( element )
         {
          case 37 : return 112;
          case 26 : return 110;
          case 32 : return 104;
          case 33 : return 105;
          case 36 : return 111;
          case 40 : return 130;
          case 41 : return 479;
          case 42 : return 554;
          default: return 0;
         }

     case 372 :
       switch( element )
         {
          case 37 : return 112;
          case 26 : return 110;
          case 32 : return 104;
          case 33 : return 105;
          case 36 : return 111;
          case 40 : return 130;
          case 41 : return 480;
          case 42 : return 554;
          default: return 0;
         }

     case 373 :
       switch( element )
         {
          case 37 : return 112;
          case 26 : return 110;
          case 32 : return 104;
          case 33 : return 105;
          case 36 : return 111;
          case 41 : return 186;
          case 42 : return 554;
          default: return 0;
         }

     case 374 :
       switch( element )
         {
          case 37 : return 112;
          case 26 : return 110;
          case 32 : return 104;
          case 33 : return 105;
          case 36 : return 111;
          case 41 : return 187;
          case 42 : return 554;
          default: return 0;
         }

     case 375 :
       switch( element )
         {
          case 37 : return 112;
          case 26 : return 110;
          case 32 : return 104;
          case 33 : return 105;
          case 36 : return 111;
          case 41 : return 188;
          case 42 : return 554;
          default: return 0;
         }

     case 376 :
       switch( element )
         {
          case 37 : return 112;
          case 26 : return 110;
          case 32 : return 104;
          case 33 : return 105;
          case 36 : return 111;
          case 41 : return 189;
          case 42 : return 554;
          default: return 0;
         }

     case 377 :
       switch( element )
         {
          case 37 : return 112;
          case 26 : return 110;
          case 32 : return 104;
          case 33 : return 105;
          case 36 : return 111;
          case 41 : return 478;
          case 42 : return 554;
          default: return 0;
         }

     case 378 :
       switch( element )
         {
          case 37 : return 112;
          case 26 : return 110;
          case 32 : return 104;
          case 33 : return 105;
          case 36 : return 111;
          case 41 : return 479;
          case 42 : return 554;
          default: return 0;
         }

     case 379 :
       switch( element )
         {
          case 37 : return 112;
          case 26 : return 110;
          case 32 : return 104;
          case 33 : return 105;
          case 36 : return 111;
          case 41 : return 480;
          case 42 : return 554;
          default: return 0;
         }

     case 380 :
       switch( element )
         {
          default: return 0;
         }

     case 381 :
       switch( element )
         {
          default: return 0;
         }

     case 382 :
       switch( element )
         {
          default: return 0;
         }

     case 383 :
       switch( element )
         {
          default: return 0;
         }

     case 384 :
       switch( element )
         {
          default: return 0;
         }

     case 385 :
       switch( element )
         {
          default: return 0;
         }

     case 386 :
       switch( element )
         {
          default: return 0;
         }

     case 387 :
       switch( element )
         {
          default: return 0;
         }

     case 388 :
       switch( element )
         {
          default: return 0;
         }

     case 389 :
       switch( element )
         {
          default: return 0;
         }

     case 390 :
       switch( element )
         {
          default: return 0;
         }

     case 391 :
       switch( element )
         {
          default: return 0;
         }

     case 392 :
       switch( element )
         {
          default: return 0;
         }

     case 393 :
       switch( element )
         {
          case 38 : return 117;
          default: return 0;
         }

     case 394 :
       switch( element )
         {
          case 38 : return 118;
          default: return 0;
         }

     case 395 :
       switch( element )
         {
          case 38 : return 119;
          default: return 0;
         }

     case 396 :
       switch( element )
         {
          case 38 : return 120;
          default: return 0;
         }

     case 397 :
       switch( element )
         {
          default: return 0;
         }

     case 398 :
       switch( element )
         {
          default: return 0;
         }

     case 399 :
       switch( element )
         {
          default: return 0;
         }

     case 400 :
       switch( element )
         {
          default: return 0;
         }

     case 401 :
       switch( element )
         {
          default: return 0;
         }

     case 402 :
       switch( element )
         {
          case 39 : return 162;
          case 32 : return 77;
          case 33 : return 78;
          case 42 : return 551;
          default: return 0;
         }

     case 403 :
       switch( element )
         {
          case 39 : return 163;
          case 32 : return 77;
          case 33 : return 78;
          case 42 : return 551;
          default: return 0;
         }

     case 404 :
       switch( element )
         {
          case 39 : return 164;
          case 32 : return 77;
          case 33 : return 78;
          case 42 : return 551;
          default: return 0;
         }

     case 405 :
       switch( element )
         {
          case 39 : return 165;
          case 32 : return 77;
          case 33 : return 78;
          case 42 : return 551;
          default: return 0;
         }

     case 406 :
       switch( element )
         {
          case 39 : return 174;
          case 32 : return 77;
          case 33 : return 78;
          case 42 : return 551;
          default: return 0;
         }

     case 407 :
       switch( element )
         {
          case 39 : return 175;
          case 32 : return 77;
          case 33 : return 78;
          case 42 : return 551;
          default: return 0;
         }

     case 408 :
       switch( element )
         {
          case 39 : return 176;
          case 32 : return 77;
          case 33 : return 78;
          case 42 : return 551;
          default: return 0;
         }

     case 409 :
       switch( element )
         {
          case 39 : return 177;
          case 32 : return 77;
          case 33 : return 78;
          case 42 : return 551;
          default: return 0;
         }

     case 410 :
       switch( element )
         {
          case 39 : return 162;
          case 42 : return 551;
          default: return 0;
         }

     case 411 :
       switch( element )
         {
          case 39 : return 163;
          case 42 : return 551;
          default: return 0;
         }

     case 412 :
       switch( element )
         {
          case 39 : return 164;
          case 42 : return 551;
          default: return 0;
         }

     case 413 :
       switch( element )
         {
          case 39 : return 165;
          case 42 : return 551;
          default: return 0;
         }

     case 414 :
       switch( element )
         {
          case 39 : return 174;
          case 42 : return 551;
          default: return 0;
         }

     case 415 :
       switch( element )
         {
          case 39 : return 175;
          case 42 : return 551;
          default: return 0;
         }

     case 416 :
       switch( element )
         {
          case 39 : return 176;
          case 42 : return 551;
          default: return 0;
         }

     case 417 :
       switch( element )
         {
          case 39 : return 177;
          case 42 : return 551;
          default: return 0;
         }

     case 418 :
       switch( element )
         {
          default: return 0;
         }

     case 419 :
       switch( element )
         {
          default: return 0;
         }

     case 420 :
       switch( element )
         {
          default: return 0;
         }

     case 421 :
       switch( element )
         {
          default: return 0;
         }

     case 422 :
       switch( element )
         {
          default: return 0;
         }

     case 423 :
       switch( element )
         {
          default: return 0;
         }

     case 424 :
       switch( element )
         {
          default: return 0;
         }

     case 425 :
       switch( element )
         {
          default: return 0;
         }

     case 426 :
       switch( element )
         {
          default: return 0;
         }

     case 427 :
       switch( element )
         {
          default: return 0;
         }

     case 428 :
       switch( element )
         {
          default: return 0;
         }

     case 429 :
       switch( element )
         {
          default: return 0;
         }

     case 430 :
       switch( element )
         {
          default: return 0;
         }

     case 431 :
       switch( element )
         {
          default: return 0;
         }

     case 432 :
       switch( element )
         {
          default: return 0;
         }

     case 433 :
       switch( element )
         {
          default: return 0;
         }

     case 434 :
       switch( element )
         {
          default: return 0;
         }

     case 435 :
       switch( element )
         {
          default: return 0;
         }

     case 436 :
       switch( element )
         {
          default: return 0;
         }

     case 437 :
       switch( element )
         {
          default: return 0;
         }

     case 438 :
       switch( element )
         {
          default: return 0;
         }

     case 439 :
       switch( element )
         {
          default: return 0;
         }

     case 440 :
       switch( element )
         {
          default: return 0;
         }

     case 441 :
       switch( element )
         {
          default: return 0;
         }

     case 442 :
       switch( element )
         {
          default: return 0;
         }

     case 443 :
       switch( element )
         {
          default: return 0;
         }

     case 444 :
       switch( element )
         {
          default: return 0;
         }

     case 445 :
       switch( element )
         {
          default: return 0;
         }

     case 446 :
       switch( element )
         {
          default: return 0;
         }

     case 447 :
       switch( element )
         {
          default: return 0;
         }

     case 448 :
       switch( element )
         {
          default: return 0;
         }

     case 449 :
       switch( element )
         {
          default: return 0;
         }

     case 450 :
       switch( element )
         {
          default: return 0;
         }

     case 451 :
       switch( element )
         {
          default: return 0;
         }

     case 452 :
       switch( element )
         {
          default: return 0;
         }

     case 453 :
       switch( element )
         {
          default: return 0;
         }

     case 454 :
       switch( element )
         {
          default: return 0;
         }

     case 455 :
       switch( element )
         {
          default: return 0;
         }

     case 456 :
       switch( element )
         {
          default: return 0;
         }

     case 457 :
       switch( element )
         {
          default: return 0;
         }

     case 458 :
       switch( element )
         {
          default: return 0;
         }

     case 459 :
       switch( element )
         {
          default: return 0;
         }

     case 460 :
       switch( element )
         {
          default: return 0;
         }

     case 461 :
       switch( element )
         {
          default: return 0;
         }

     case 462 :
       switch( element )
         {
          default: return 0;
         }

     case 463 :
       switch( element )
         {
          default: return 0;
         }

     case 464 :
       switch( element )
         {
          default: return 0;
         }

     case 465 :
       switch( element )
         {
          default: return 0;
         }

     case 466 :
       switch( element )
         {
          default: return 0;
         }

     case 467 :
       switch( element )
         {
          default: return 0;
         }

     case 468 :
       switch( element )
         {
          default: return 0;
         }

     case 469 :
       switch( element )
         {
          default: return 0;
         }

     case 470 :
       switch( element )
         {
          default: return 0;
         }

     case 471 :
       switch( element )
         {
          default: return 0;
         }

     case 472 :
       switch( element )
         {
          default: return 0;
         }

     case 473 :
       switch( element )
         {
          default: return 0;
         }

     case 474 :
       switch( element )
         {
          default: return 0;
         }

     case 475 :
       switch( element )
         {
          default: return 0;
         }

     case 476 :
       switch( element )
         {
          default: return 0;
         }

     case 477 :
       switch( element )
         {
          default: return 0;
         }

     case 478 :
       switch( element )
         {
          default: return 0;
         }

     case 479 :
       switch( element )
         {
          default: return 0;
         }

     case 480 :
       switch( element )
         {
          default: return 0;
         }

     case 481 :
       switch( element )
         {
          default: return 0;
         }

     case 482 :
       switch( element )
         {
          default: return 0;
         }

     case 483 :
       switch( element )
         {
          case 29 : return 6;
          default: return 0;
         }

     case 484 :
       switch( element )
         {
          case 29 : return 41;
          default: return 0;
         }

     case 485 :
       switch( element )
         {
          case 29 : return 655;
          default: return 0;
         }

     case 486 :
       switch( element )
         {
          default: return 0;
         }

     case 487 :
       switch( element )
         {
          default: return 0;
         }

     case 488 :
       switch( element )
         {
          default: return 0;
         }

     case 489 :
       switch( element )
         {
          default: return 0;
         }

     case 490 :
       switch( element )
         {
          default: return 0;
         }

     case 491 :
       switch( element )
         {
          case 26 : return 472;
          default: return 0;
         }

     case 492 :
       switch( element )
         {
          case 26 : return 473;
          default: return 0;
         }

     case 493 :
       switch( element )
         {
          case 26 : return 474;
          default: return 0;
         }

     case 494 :
       switch( element )
         {
          case 26 : return 469;
          case 40 : return 74;
          default: return 0;
         }

     case 495 :
       switch( element )
         {
          case 26 : return 469;
          case 40 : return 74;
          default: return 0;
         }

     case 496 :
       switch( element )
         {
          case 26 : return 470;
          case 29 : return 9;
          case 40 : return 75;
          default: return 0;
         }

     case 497 :
       switch( element )
         {
          case 26 : return 470;
          case 29 : return 10;
          case 40 : return 75;
          default: return 0;
         }

     case 498 :
       switch( element )
         {
          case 26 : return 470;
          case 29 : return 658;
          case 40 : return 75;
          default: return 0;
         }

     case 499 :
       switch( element )
         {
          case 26 : return 471;
          case 3 : return 560;
          case 40 : return 76;
          default: return 0;
         }

     case 500 :
       switch( element )
         {
          case 26 : return 471;
          case 3 : return 566;
          case 40 : return 76;
          default: return 0;
         }

     case 501 :
       switch( element )
         {
          case 26 : return 471;
          case 3 : return 567;
          case 40 : return 76;
          default: return 0;
         }

     case 502 :
       switch( element )
         {
          case 26 : return 471;
          case 3 : return 568;
          case 40 : return 76;
          default: return 0;
         }

     case 503 :
       switch( element )
         {
          case 32 : return 86;
          case 33 : return 87;
          case 42 : return 552;
          default: return 0;
         }

     case 504 :
       switch( element )
         {
          case 32 : return 86;
          case 33 : return 87;
          case 42 : return 552;
          default: return 0;
         }

     case 505 :
       switch( element )
         {
          case 32 : return 86;
          case 33 : return 87;
          case 42 : return 552;
          default: return 0;
         }

     case 506 :
       switch( element )
         {
          case 32 : return 95;
          case 33 : return 96;
          case 29 : return 11;
          case 42 : return 553;
          default: return 0;
         }

     case 507 :
       switch( element )
         {
          case 32 : return 95;
          case 33 : return 96;
          case 29 : return 12;
          case 42 : return 553;
          default: return 0;
         }

     case 508 :
       switch( element )
         {
          case 32 : return 95;
          case 33 : return 96;
          case 29 : return 43;
          case 42 : return 553;
          default: return 0;
         }

     case 509 :
       switch( element )
         {
          case 32 : return 95;
          case 33 : return 96;
          case 29 : return 659;
          case 42 : return 553;
          default: return 0;
         }

     case 510 :
       switch( element )
         {
          case 32 : return 104;
          case 33 : return 105;
          case 41 : return 186;
          case 42 : return 554;
          default: return 0;
         }

     case 511 :
       switch( element )
         {
          case 32 : return 104;
          case 33 : return 105;
          case 41 : return 187;
          case 42 : return 554;
          default: return 0;
         }

     case 512 :
       switch( element )
         {
          case 32 : return 104;
          case 33 : return 105;
          case 41 : return 188;
          case 42 : return 554;
          default: return 0;
         }

     case 513 :
       switch( element )
         {
          case 32 : return 104;
          case 33 : return 105;
          case 41 : return 189;
          case 42 : return 554;
          default: return 0;
         }

     case 514 :
       switch( element )
         {
          case 32 : return 104;
          case 33 : return 105;
          case 41 : return 478;
          case 42 : return 554;
          default: return 0;
         }

     case 515 :
       switch( element )
         {
          case 32 : return 104;
          case 33 : return 105;
          case 41 : return 479;
          case 42 : return 554;
          default: return 0;
         }

     case 516 :
       switch( element )
         {
          case 32 : return 104;
          case 33 : return 105;
          case 41 : return 480;
          case 42 : return 554;
          default: return 0;
         }

     case 517 :
       switch( element )
         {
          default: return 0;
         }

     case 518 :
       switch( element )
         {
          default: return 0;
         }

     case 519 :
       switch( element )
         {
          default: return 0;
         }

     case 520 :
       switch( element )
         {
          default: return 0;
         }

     case 521 :
       switch( element )
         {
          default: return 0;
         }

     case 522 :
       switch( element )
         {
          case 42 : return 552;
          default: return 0;
         }

     case 523 :
       switch( element )
         {
          case 42 : return 552;
          default: return 0;
         }

     case 524 :
       switch( element )
         {
          case 42 : return 552;
          default: return 0;
         }

     case 525 :
       switch( element )
         {
          default: return 0;
         }

     case 526 :
       switch( element )
         {
          default: return 0;
         }

     case 527 :
       switch( element )
         {
          case 27 : return 121;
          case 43 : return 398;
          default: return 0;
         }

     case 528 :
       switch( element )
         {
          case 27 : return 121;
          case 43 : return 518;
          default: return 0;
         }

     case 529 :
       switch( element )
         {
          case 27 : return 121;
          case 43 : return 556;
          default: return 0;
         }

     case 530 :
       switch( element )
         {
          case 27 : return 121;
          case 43 : return 633;
          default: return 0;
         }

     case 531 :
       switch( element )
         {
          case 27 : return 156;
          case 43 : return 491;
          default: return 0;
         }

     case 532 :
       switch( element )
         {
          case 27 : return 156;
          case 43 : return 492;
          default: return 0;
         }

     case 533 :
       switch( element )
         {
          case 27 : return 156;
          case 43 : return 493;
          default: return 0;
         }

     case 534 :
       switch( element )
         {
          case 27 : return 542;
          case 43 : return 399;
          default: return 0;
         }

     case 535 :
       switch( element )
         {
          case 27 : return 542;
          case 43 : return 401;
          default: return 0;
         }

     case 536 :
       switch( element )
         {
          case 27 : return 542;
          case 43 : return 519;
          default: return 0;
         }

     case 537 :
       switch( element )
         {
          case 27 : return 542;
          case 43 : return 521;
          default: return 0;
         }

     case 538 :
       switch( element )
         {
          case 27 : return 542;
          case 43 : return 557;
          default: return 0;
         }

     case 539 :
       switch( element )
         {
          case 27 : return 542;
          case 43 : return 559;
          default: return 0;
         }

     case 540 :
       switch( element )
         {
          case 27 : return 542;
          case 43 : return 634;
          default: return 0;
         }

     case 541 :
       switch( element )
         {
          case 27 : return 542;
          case 43 : return 636;
          default: return 0;
         }

     case 542 :
       switch( element )
         {
          case 28 : return 594;
          case 67 : return 526;
          default: return 0;
         }

     case 543 :
       switch( element )
         {
          case 28 : return 620;
          default: return 0;
         }

     case 544 :
       switch( element )
         {
          case 28 : return 621;
          default: return 0;
         }

     case 545 :
       switch( element )
         {
          case 28 : return 622;
          default: return 0;
         }

     case 546 :
       switch( element )
         {
          case 28 : return 623;
          default: return 0;
         }

     case 547 :
       switch( element )
         {
          case 28 : return 624;
          default: return 0;
         }

     case 548 :
       switch( element )
         {
          case 28 : return 625;
          default: return 0;
         }

     case 549 :
       switch( element )
         {
          case 28 : return 626;
          default: return 0;
         }

     case 550 :
       switch( element )
         {
          case 28 : return 627;
          default: return 0;
         }

     case 551 :
       switch( element )
         {
          case 28 : return 594;
          case 43 : return 400;
          case 67 : return 525;
          case 68 : return 535;
          default: return 0;
         }

     case 552 :
       switch( element )
         {
          case 28 : return 594;
          case 43 : return 520;
          case 67 : return 525;
          case 68 : return 537;
          default: return 0;
         }

     case 553 :
       switch( element )
         {
          case 28 : return 594;
          case 43 : return 558;
          case 67 : return 525;
          case 68 : return 539;
          default: return 0;
         }

     case 554 :
       switch( element )
         {
          case 28 : return 594;
          case 43 : return 635;
          case 67 : return 525;
          case 68 : return 541;
          default: return 0;
         }

     case 555 :
       switch( element )
         {
          default: return 0;
         }

     case 556 :
       switch( element )
         {
          default: return 0;
         }

     case 557 :
       switch( element )
         {
          default: return 0;
         }

     case 558 :
       switch( element )
         {
          default: return 0;
         }

     case 559 :
       switch( element )
         {
          default: return 0;
         }

     case 560 :
       switch( element )
         {
          case 29 : return 42;
          case 30 : return 125;
          default: return 0;
         }

     case 561 :
       switch( element )
         {
          case 29 : return 11;
          case 42 : return 553;
          default: return 0;
         }

     case 562 :
       switch( element )
         {
          case 29 : return 12;
          case 42 : return 553;
          default: return 0;
         }

     case 563 :
       switch( element )
         {
          case 29 : return 43;
          case 42 : return 553;
          default: return 0;
         }

     case 564 :
       switch( element )
         {
          case 29 : return 659;
          case 42 : return 553;
          default: return 0;
         }

     case 565 :
       switch( element )
         {
          case 30 : return 122;
          default: return 0;
         }

     case 566 :
       switch( element )
         {
          case 30 : return 123;
          default: return 0;
         }

     case 567 :
       switch( element )
         {
          case 30 : return 124;
          default: return 0;
         }

     case 568 :
       switch( element )
         {
          case 30 : return 126;
          default: return 0;
         }

     case 569 :
       switch( element )
         {
          case 30 : return 157;
          default: return 0;
         }

     case 570 :
       switch( element )
         {
          case 30 : return 158;
          default: return 0;
         }

     case 571 :
       switch( element )
         {
          case 30 : return 159;
          default: return 0;
         }

     case 572 :
       switch( element )
         {
          case 2 : return 8;
          default: return 0;
         }

     case 573 :
       switch( element )
         {
          case 2 : return 657;
          default: return 0;
         }

     case 574 :
       switch( element )
         {
          case 3 : return 13;
          case 49 : return 138;
          default: return 0;
         }

     case 575 :
       switch( element )
         {
          case 3 : return 13;
          case 49 : return 141;
          default: return 0;
         }

     case 576 :
       switch( element )
         {
          case 3 : return 13;
          case 49 : return 144;
          default: return 0;
         }

     case 577 :
       switch( element )
         {
          case 3 : return 14;
          case 49 : return 139;
          default: return 0;
         }

     case 578 :
       switch( element )
         {
          case 3 : return 14;
          case 49 : return 142;
          default: return 0;
         }

     case 579 :
       switch( element )
         {
          case 3 : return 14;
          case 49 : return 145;
          default: return 0;
         }

     case 580 :
       switch( element )
         {
          case 3 : return 15;
          case 49 : return 140;
          default: return 0;
         }

     case 581 :
       switch( element )
         {
          case 3 : return 15;
          case 49 : return 143;
          default: return 0;
         }

     case 582 :
       switch( element )
         {
          case 3 : return 15;
          case 49 : return 146;
          default: return 0;
         }

     case 583 :
       switch( element )
         {
          case 3 : return 16;
          default: return 0;
         }

     case 584 :
       switch( element )
         {
          case 3 : return 17;
          default: return 0;
         }

     case 585 :
       switch( element )
         {
          case 3 : return 18;
          default: return 0;
         }

     case 586 :
       switch( element )
         {
          case 3 : return 178;
          default: return 0;
         }

     case 587 :
       switch( element )
         {
          case 3 : return 179;
          default: return 0;
         }

     case 588 :
       switch( element )
         {
          case 3 : return 180;
          default: return 0;
         }

     case 589 :
       switch( element )
         {
          case 3 : return 181;
          default: return 0;
         }

     case 590 :
       switch( element )
         {
          case 3 : return 182;
          default: return 0;
         }

     case 591 :
       switch( element )
         {
          case 3 : return 183;
          default: return 0;
         }

     case 592 :
       switch( element )
         {
          case 3 : return 184;
          default: return 0;
         }

     case 593 :
       switch( element )
         {
          case 3 : return 185;
          default: return 0;
         }

     case 594 :
       switch( element )
         {
          case 3 : return 565;
          default: return 0;
         }

     case 595 :
       switch( element )
         {
          case 3 : return 569;
          default: return 0;
         }

     case 596 :
       switch( element )
         {
          case 3 : return 570;
          default: return 0;
         }

     case 597 :
       switch( element )
         {
          case 3 : return 571;
          default: return 0;
         }

     case 598 :
       switch( element )
         {
          case 3 : return 644;
          default: return 0;
         }

     case 599 :
       switch( element )
         {
          case 3 : return 645;
          default: return 0;
         }

     case 600 :
       switch( element )
         {
          case 3 : return 646;
          default: return 0;
         }

     case 601 :
       switch( element )
         {
          case 3 : return 647;
          default: return 0;
         }

     case 602 :
       switch( element )
         {
          case 3 : return 648;
          default: return 0;
         }

     case 603 :
       switch( element )
         {
          case 3 : return 649;
          default: return 0;
         }

     case 604 :
       switch( element )
         {
          case 3 : return 19;
          case 4 : return 23;
          case 51 : return 62;
          default: return 0;
         }

     case 605 :
       switch( element )
         {
          case 3 : return 19;
          case 4 : return 23;
          case 51 : return 66;
          default: return 0;
         }

     case 606 :
       switch( element )
         {
          case 3 : return 19;
          case 4 : return 23;
          case 51 : return 70;
          default: return 0;
         }

     case 607 :
       switch( element )
         {
          case 3 : return 20;
          case 4 : return 24;
          case 51 : return 63;
          default: return 0;
         }

     case 608 :
       switch( element )
         {
          case 3 : return 20;
          case 4 : return 24;
          case 51 : return 67;
          default: return 0;
         }

     case 609 :
       switch( element )
         {
          case 3 : return 20;
          case 4 : return 24;
          case 51 : return 71;
          default: return 0;
         }

     case 610 :
       switch( element )
         {
          case 3 : return 21;
          case 4 : return 25;
          case 51 : return 64;
          default: return 0;
         }

     case 611 :
       switch( element )
         {
          case 3 : return 21;
          case 4 : return 25;
          case 51 : return 68;
          default: return 0;
         }

     case 612 :
       switch( element )
         {
          case 3 : return 21;
          case 4 : return 25;
          case 51 : return 72;
          default: return 0;
         }

     case 613 :
       switch( element )
         {
          case 3 : return 22;
          case 4 : return 26;
          case 51 : return 65;
          default: return 0;
         }

     case 614 :
       switch( element )
         {
          case 3 : return 22;
          case 4 : return 26;
          case 51 : return 69;
          default: return 0;
         }

     case 615 :
       switch( element )
         {
          case 3 : return 22;
          case 4 : return 26;
          case 51 : return 73;
          default: return 0;
         }

     case 616 :
       switch( element )
         {
          case 3 : return 27;
          case 4 : return 31;
          default: return 0;
         }

     case 617 :
       switch( element )
         {
          case 3 : return 28;
          case 4 : return 32;
          default: return 0;
         }

     case 618 :
       switch( element )
         {
          case 3 : return 29;
          case 4 : return 33;
          default: return 0;
         }

     case 619 :
       switch( element )
         {
          case 3 : return 30;
          case 4 : return 34;
          default: return 0;
         }

     case 620 :
       switch( element )
         {
          case 0 : return 286;
          default: return 0;
         }

     case 621 :
       switch( element )
         {
          case 0 : return 287;
          default: return 0;
         }

     case 622 :
       switch( element )
         {
          case 0 : return 288;
          default: return 0;
         }

     case 623 :
       switch( element )
         {
          case 0 : return 289;
          default: return 0;
         }

     case 624 :
       switch( element )
         {
          case 0 : return 543;
          default: return 0;
         }

     case 625 :
       switch( element )
         {
          case 0 : return 544;
          default: return 0;
         }

     case 626 :
       switch( element )
         {
          case 0 : return 545;
          default: return 0;
         }

     case 627 :
       switch( element )
         {
          case 0 : return 546;
          default: return 0;
         }

     case 628 :
       switch( element )
         {
          case 0 : return 547;
          default: return 0;
         }

     case 629 :
       switch( element )
         {
          case 0 : return 548;
          default: return 0;
         }

     case 630 :
       switch( element )
         {
          case 0 : return 549;
          default: return 0;
         }

     case 631 :
       switch( element )
         {
          case 0 : return 550;
          default: return 0;
         }

     case 632 :
       switch( element )
         {
          default: return 0;
         }

     case 633 :
       switch( element )
         {
          default: return 0;
         }

     case 634 :
       switch( element )
         {
          default: return 0;
         }

     case 635 :
       switch( element )
         {
          default: return 0;
         }

     case 636 :
       switch( element )
         {
          default: return 0;
         }

     case 637 :
       switch( element )
         {
          case 41 : return 186;
          case 42 : return 554;
          default: return 0;
         }

     case 638 :
       switch( element )
         {
          case 41 : return 187;
          case 42 : return 554;
          default: return 0;
         }

     case 639 :
       switch( element )
         {
          case 41 : return 188;
          case 42 : return 554;
          default: return 0;
         }

     case 640 :
       switch( element )
         {
          case 41 : return 189;
          case 42 : return 554;
          default: return 0;
         }

     case 641 :
       switch( element )
         {
          case 41 : return 478;
          case 42 : return 554;
          default: return 0;
         }

     case 642 :
       switch( element )
         {
          case 41 : return 479;
          case 42 : return 554;
          default: return 0;
         }

     case 643 :
       switch( element )
         {
          case 41 : return 480;
          case 42 : return 554;
          default: return 0;
         }

     case 644 :
       switch( element )
         {
          case 42 : return 650;
          default: return 0;
         }

     case 645 :
       switch( element )
         {
          case 42 : return 1;
          default: return 0;
         }

     case 646 :
       switch( element )
         {
          case 42 : return 35;
          default: return 0;
         }

     case 647 :
       switch( element )
         {
          case 42 : return 36;
          default: return 0;
         }

     case 648 :
       switch( element )
         {
          case 42 : return 37;
          default: return 0;
         }

     case 649 :
       switch( element )
         {
          case 42 : return 38;
          default: return 0;
         }

     case 650 :
       switch( element )
         {
          case 44 : return 151;
          default: return 0;
         }

     case 651 :
       switch( element )
         {
          default: return 0;
         }

     case 652 :
       switch( element )
         {
          default: return 0;
         }

     case 653 :
       switch( element )
         {
          default: return 0;
         }

     case 654 :
       switch( element )
         {
          default: return 0;
         }

     case 655 :
       switch( element )
         {
          default: return 0;
         }

     case 656 :
       switch( element )
         {
          default: return 0;
         }

     case 657 :
       switch( element )
         {
          default: return 0;
         }

     case 658 :
       switch( element )
         {
          default: return 0;
         }

     case 659 :
       switch( element )
         {
          default: return 0;
         }

     case 660 :
       switch( element )
         {
          case 35 : return 580;
          case 28 : return 48;
          case 5 : return 49;
          case 3 : return 15;
          case 24 : return 573;
          case 6 : return 420;
          case 19 : return 462;
          case 23 : return 599;
          case 7 : return 423;
          case 11 : return 438;
          case 12 : return 444;
          case 13 : return 450;
          case 10 : return 432;
          case 20 : return 601;
          case 18 : return 459;
          case 21 : return 597;
          case 8 : return 426;
          case 15 : return 441;
          case 16 : return 447;
          case 17 : return 453;
          case 14 : return 435;
          case 9 : return 429;
          case 42 : return 155;
          case 45 : return 651;
          case 46 : return 652;
          case 47 : return 653;
          case 48 : return 654;
          case 49 : return 137;
          case 50 : return 465;
          case 53 : return 456;
          case 54 : return 468;
          case 55 : return 502;
          case 57 : return 485;
          default: return 0;
         }

     default: return 0;
    }
 }

} // namespace DDL2
} // namespace CCore

