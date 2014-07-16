/* APRTestData.gen.cpp */

#include <CCore/inc/math/APRTest.h>

namespace CCore {
namespace Math {
namespace APRTest {

static const TestSet::PrimeQ QSet[]=
 {
  { 3u , 0u },
  { 7u , 0u },
  { 11u , 1u },
  { 31u , 1u },
  { 43u , 2u },
  { 71u , 2u },
  { 211u , 2u },
  { 23u , 3u },
  { 67u , 3u },
  { 331u , 3u },
  { 463u , 3u },
  { 2311u , 3u },
  { 79u , 4u },
  { 131u , 4u },
  { 547u , 4u },
  { 859u , 4u },
  { 911u , 4u },
  { 2003u , 4u },
  { 2731u , 4u },
  { 6007u , 4u },
  { 103u , 5u },
  { 239u , 5u },
  { 443u , 5u },
  { 1123u , 5u },
  { 1327u , 5u },
  { 1871u , 5u },
  { 3571u , 5u },
  { 9283u , 5u },
  { 46411u , 5u },
  { 72931u , 5u },
  { 102103u , 5u },
  { 191u , 6u },
  { 419u , 6u },
  { 571u , 6u },
  { 647u , 6u },
  { 1483u , 6u },
  { 2927u , 6u },
  { 4523u , 6u },
  { 6271u , 6u },
  { 7411u , 6u },
  { 8779u , 6u },
  { 13567u , 6u },
  { 17291u , 6u },
  { 21319u , 6u },
  { 35531u , 6u },
  { 38039u , 6u },
  { 43891u , 6u },
  { 51871u , 6u },
  { 58787u , 6u },
  { 106591u , 6u },
  { 461891u , 6u },
  { 1939939u , 6u },
  { 3233231u , 6u },
  { 47u , 7u },
  { 139u , 7u },
  { 599u , 7u },
  { 691u , 7u },
  { 967u , 7u },
  { 2347u , 7u },
  { 2531u , 7u },
  { 3911u , 7u },
  { 4831u , 7u },
  { 7591u , 7u },
  { 8971u , 7u },
  { 10627u , 7u },
  { 11731u , 7u },
  { 28843u , 7u },
  { 62791u , 7u },
  { 91771u , 7u },
  { 111827u , 7u },
  { 138139u , 7u },
  { 336491u , 7u },
  { 355811u , 7u },
  { 520031u , 7u },
  { 782783u , 7u },
  { 903211u , 7u },
  { 1193011u , 7u },
  { 2348347u , 7u },
  { 2624623u , 7u },
  { 2897311u , 7u },
  { 13123111u , 7u },
  { 17160991u , 7u }
 };

static const TestSet::JTable JSet_2[]=
 {
  { 3u , 0u , 0 },
  { 7u , 0u , 0 },
  { 11u , 1u , 0 },
  { 31u , 1u , 0 },
  { 43u , 2u , 0 },
  { 71u , 2u , 0 },
  { 211u , 2u , 0 },
  { 23u , 3u , 0 },
  { 67u , 3u , 0 },
  { 331u , 3u , 0 },
  { 463u , 3u , 0 },
  { 2311u , 3u , 0 },
  { 79u , 4u , 0 },
  { 131u , 4u , 0 },
  { 547u , 4u , 0 },
  { 859u , 4u , 0 },
  { 911u , 4u , 0 },
  { 2003u , 4u , 0 },
  { 2731u , 4u , 0 },
  { 6007u , 4u , 0 },
  { 103u , 5u , 0 },
  { 239u , 5u , 0 },
  { 443u , 5u , 0 },
  { 1123u , 5u , 0 },
  { 1327u , 5u , 0 },
  { 1871u , 5u , 0 },
  { 3571u , 5u , 0 },
  { 9283u , 5u , 0 },
  { 46411u , 5u , 0 },
  { 72931u , 5u , 0 },
  { 102103u , 5u , 0 },
  { 191u , 6u , 0 },
  { 419u , 6u , 0 },
  { 571u , 6u , 0 },
  { 647u , 6u , 0 },
  { 1483u , 6u , 0 },
  { 2927u , 6u , 0 },
  { 4523u , 6u , 0 },
  { 6271u , 6u , 0 },
  { 7411u , 6u , 0 },
  { 8779u , 6u , 0 },
  { 13567u , 6u , 0 },
  { 17291u , 6u , 0 },
  { 21319u , 6u , 0 },
  { 35531u , 6u , 0 },
  { 38039u , 6u , 0 },
  { 43891u , 6u , 0 },
  { 51871u , 6u , 0 },
  { 58787u , 6u , 0 },
  { 106591u , 6u , 0 },
  { 461891u , 6u , 0 },
  { 1939939u , 6u , 0 },
  { 3233231u , 6u , 0 },
  { 47u , 7u , 0 },
  { 139u , 7u , 0 },
  { 599u , 7u , 0 },
  { 691u , 7u , 0 },
  { 967u , 7u , 0 },
  { 2347u , 7u , 0 },
  { 2531u , 7u , 0 },
  { 3911u , 7u , 0 },
  { 4831u , 7u , 0 },
  { 7591u , 7u , 0 },
  { 8971u , 7u , 0 },
  { 10627u , 7u , 0 },
  { 11731u , 7u , 0 },
  { 28843u , 7u , 0 },
  { 62791u , 7u , 0 },
  { 91771u , 7u , 0 },
  { 111827u , 7u , 0 },
  { 138139u , 7u , 0 },
  { 336491u , 7u , 0 },
  { 355811u , 7u , 0 },
  { 520031u , 7u , 0 },
  { 782783u , 7u , 0 },
  { 903211u , 7u , 0 },
  { 1193011u , 7u , 0 },
  { 2348347u , 7u , 0 },
  { 2624623u , 7u , 0 },
  { 2897311u , 7u , 0 },
  { 13123111u , 7u , 0 },
  { 17160991u , 7u , 0 }
 };

static const QType JTable_3_7[]=
 {
  2u, 0u, 3u
 };

static const QType JTable_3_31[]=
 {
  5u, 6u, 0u
 };

static const QType JTable_3_43[]=
 {
  0u, 7u, 1u
 };

static const QType JTable_3_211[]=
 {
  14u, 15u, 0u
 };

static const QType JTable_3_67[]=
 {
  2u, 9u, 0u
 };

static const QType JTable_3_331[]=
 {
  11u, 0u, 21u
 };

static const QType JTable_3_463[]=
 {
  0u, 1u, 22u
 };

static const QType JTable_3_2311[]=
 {
  0u, 34u, 55u
 };

static const QType JTable_3_79[]=
 {
  0u, 7u, 10u
 };

static const QType JTable_3_547[]=
 {
  14u, 27u, 0u
 };

static const QType JTable_3_859[]=
 {
  23u, 0u, 33u
 };

static const QType JTable_3_2731[]=
 {
  0u, 55u, 49u
 };

static const QType JTable_3_6007[]=
 {
  77u, 78u, 0u
 };

static const QType JTable_3_103[]=
 {
  11u, 9u, 0u
 };

static const QType JTable_3_1123[]=
 {
  0u, 1u, 34u
 };

static const QType JTable_3_1327[]=
 {
  23u, 42u, 0u
 };

static const QType JTable_3_3571[]=
 {
  35u, 0u, 69u
 };

static const QType JTable_3_9283[]=
 {
  62u, 111u, 0u
 };

static const QType JTable_3_46411[]=
 {
  155u, 0u, 246u
 };

static const QType JTable_3_72931[]=
 {
  101u, 306u, 0u
 };

static const QType JTable_3_102103[]=
 {
  77u, 0u, 351u
 };

static const QType JTable_3_571[]=
 {
  26u, 0u, 21u
 };

static const QType JTable_3_1483[]=
 {
  38u, 39u, 0u
 };

static const QType JTable_3_6271[]=
 {
  59u, 90u, 0u
 };

static const QType JTable_3_7411[]=
 {
  0u, 19u, 94u
 };

static const QType JTable_3_8779[]=
 {
  0u, 97u, 7u
 };

static const QType JTable_3_13567[]=
 {
  134u, 0u, 57u
 };

static const QType JTable_3_21319[]=
 {
  2u, 147u, 0u
 };

static const QType JTable_3_43891[]=
 {
  209u, 0u, 210u
 };

static const QType JTable_3_51871[]=
 {
  0u, 169u, 259u
 };

static const QType JTable_3_106591[]=
 {
  221u, 375u, 0u
 };

static const QType JTable_3_1939939[]=
 {
  1463u, 0u, 153u
 };

static const QType JTable_3_139[]=
 {
  0u, 13u, 10u
 };

static const QType JTable_3_691[]=
 {
  11u, 0u, 30u
 };

static const QType JTable_3_967[]=
 {
  0u, 34u, 7u
 };

static const QType JTable_3_2347[]=
 {
  53u, 42u, 0u
 };

static const QType JTable_3_4831[]=
 {
  0u, 70u, 1u
 };

static const QType JTable_3_7591[]=
 {
  65u, 0u, 99u
 };

static const QType JTable_3_8971[]=
 {
  26u, 105u, 0u
 };

static const QType JTable_3_10627[]=
 {
  119u, 0u, 57u
 };

static const QType JTable_3_11731[]=
 {
  125u, 0u, 66u
 };

static const QType JTable_3_28843[]=
 {
  191u, 0u, 57u
 };

static const QType JTable_3_62791[]=
 {
  0u, 286u, 181u
 };

static const QType JTable_3_91771[]=
 {
  0u, 349u, 154u
 };

static const QType JTable_3_138139[]=
 {
  365u, 0u, 378u
 };

static const QType JTable_3_903211[]=
 {
  1001u, 0u, 111u
 };

static const QType JTable_3_1193011[]=
 {
  0u, 1261u, 610u
 };

static const QType JTable_3_2348347[]=
 {
  1553u, 42u, 0u
 };

static const QType JTable_3_2624623[]=
 {
  0u, 1483u, 1729u
 };

static const QType JTable_3_2897311[]=
 {
  1715u, 1689u, 0u
 };

static const QType JTable_3_13123111[]=
 {
  1154u, 4059u, 0u
 };

static const QType JTable_3_17160991[]=
 {
  0u, 805u, 4486u
 };

static const TestSet::JTable JSet_3[]=
 {
  { 7u , 0u , JTable_3_7 },
  { 31u , 1u , JTable_3_31 },
  { 43u , 2u , JTable_3_43 },
  { 211u , 2u , JTable_3_211 },
  { 67u , 3u , JTable_3_67 },
  { 331u , 3u , JTable_3_331 },
  { 463u , 3u , JTable_3_463 },
  { 2311u , 3u , JTable_3_2311 },
  { 79u , 4u , JTable_3_79 },
  { 547u , 4u , JTable_3_547 },
  { 859u , 4u , JTable_3_859 },
  { 2731u , 4u , JTable_3_2731 },
  { 6007u , 4u , JTable_3_6007 },
  { 103u , 5u , JTable_3_103 },
  { 1123u , 5u , JTable_3_1123 },
  { 1327u , 5u , JTable_3_1327 },
  { 3571u , 5u , JTable_3_3571 },
  { 9283u , 5u , JTable_3_9283 },
  { 46411u , 5u , JTable_3_46411 },
  { 72931u , 5u , JTable_3_72931 },
  { 102103u , 5u , JTable_3_102103 },
  { 571u , 6u , JTable_3_571 },
  { 1483u , 6u , JTable_3_1483 },
  { 6271u , 6u , JTable_3_6271 },
  { 7411u , 6u , JTable_3_7411 },
  { 8779u , 6u , JTable_3_8779 },
  { 13567u , 6u , JTable_3_13567 },
  { 21319u , 6u , JTable_3_21319 },
  { 43891u , 6u , JTable_3_43891 },
  { 51871u , 6u , JTable_3_51871 },
  { 106591u , 6u , JTable_3_106591 },
  { 1939939u , 6u , JTable_3_1939939 },
  { 139u , 7u , JTable_3_139 },
  { 691u , 7u , JTable_3_691 },
  { 967u , 7u , JTable_3_967 },
  { 2347u , 7u , JTable_3_2347 },
  { 4831u , 7u , JTable_3_4831 },
  { 7591u , 7u , JTable_3_7591 },
  { 8971u , 7u , JTable_3_8971 },
  { 10627u , 7u , JTable_3_10627 },
  { 11731u , 7u , JTable_3_11731 },
  { 28843u , 7u , JTable_3_28843 },
  { 62791u , 7u , JTable_3_62791 },
  { 91771u , 7u , JTable_3_91771 },
  { 138139u , 7u , JTable_3_138139 },
  { 903211u , 7u , JTable_3_903211 },
  { 1193011u , 7u , JTable_3_1193011 },
  { 2348347u , 7u , JTable_3_2348347 },
  { 2624623u , 7u , JTable_3_2624623 },
  { 2897311u , 7u , JTable_3_2897311 },
  { 13123111u , 7u , JTable_3_13123111 },
  { 17160991u , 7u , JTable_3_17160991 }
 };

static const QType JTable_5_11[]=
 {
  2u, 4u, 0u, 1u, 2u,
  2u, 1u, 4u, 2u, 0u,
  2u, 4u, 0u, 1u, 2u
 };

static const QType JTable_5_31[]=
 {
  6u, 0u, 3u, 6u, 4u,
  6u, 6u, 0u, 4u, 3u,
  6u, 0u, 3u, 6u, 4u
 };

static const QType JTable_5_71[]=
 {
  0u, 10u, 4u, 3u, 2u,
  0u, 3u, 10u, 2u, 4u,
  0u, 10u, 4u, 3u, 2u
 };

static const QType JTable_5_211[]=
 {
  9u, 15u, 5u, 0u, 15u,
  9u, 0u, 15u, 15u, 5u,
  9u, 15u, 5u, 0u, 15u
 };

static const QType JTable_5_331[]=
 {
  21u, 3u, 9u, 0u, 11u,
  21u, 0u, 3u, 11u, 9u,
  21u, 3u, 9u, 0u, 11u
 };

static const QType JTable_5_2311[]=
 {
  0u, 45u, 54u, 18u, 32u,
  0u, 18u, 45u, 32u, 54u,
  0u, 45u, 54u, 18u, 32u
 };

static const QType JTable_5_131[]=
 {
  8u, 2u, 0u, 13u, 6u,
  8u, 13u, 2u, 6u, 0u,
  8u, 2u, 0u, 13u, 6u
 };

static const QType JTable_5_911[]=
 {
  35u, 28u, 0u, 22u, 14u,
  35u, 22u, 28u, 14u, 0u,
  35u, 28u, 0u, 22u, 14u
 };

static const QType JTable_5_2731[]=
 {
  0u, 63u, 45u, 27u, 29u,
  0u, 27u, 63u, 29u, 45u,
  0u, 63u, 45u, 27u, 29u
 };

static const QType JTable_5_1871[]=
 {
  49u, 35u, 45u, 0u, 35u,
  49u, 0u, 35u, 35u, 45u,
  49u, 35u, 45u, 0u, 35u
 };

static const QType JTable_5_3571[]=
 {
  69u, 15u, 35u, 0u, 45u,
  69u, 0u, 15u, 45u, 35u,
  69u, 15u, 35u, 0u, 45u
 };

static const QType JTable_5_46411[]=
 {
  0u, 180u, 114u, 258u, 97u,
  0u, 258u, 180u, 97u, 114u,
  0u, 180u, 114u, 258u, 97u
 };

static const QType JTable_5_72931[]=
 {
  324u, 90u, 155u, 0u, 90u,
  324u, 0u, 90u, 90u, 155u,
  324u, 90u, 155u, 0u, 90u
 };

static const QType JTable_5_191[]=
 {
  17u, 9u, 0u, 11u, 7u,
  17u, 11u, 9u, 7u, 0u,
  17u, 9u, 0u, 11u, 7u
 };

static const QType JTable_5_571[]=
 {
  3u, 12u, 0u, 18u, 26u,
  3u, 18u, 12u, 26u, 0u,
  3u, 12u, 0u, 18u, 26u
 };

static const QType JTable_5_6271[]=
 {
  54u, 95u, 0u, 30u, 60u,
  54u, 30u, 95u, 60u, 0u,
  54u, 95u, 0u, 30u, 60u
 };

static const QType JTable_5_7411[]=
 {
  15u, 9u, 7u, 0u, 93u,
  15u, 0u, 9u, 93u, 7u,
  15u, 9u, 7u, 0u, 93u
 };

static const QType JTable_5_17291[]=
 {
  113u, 72u, 0u, 158u, 106u,
  113u, 158u, 72u, 106u, 0u,
  113u, 72u, 0u, 158u, 106u
 };

static const QType JTable_5_35531[]=
 {
  193u, 158u, 212u, 166u, 0u,
  193u, 166u, 158u, 0u, 212u,
  193u, 158u, 212u, 166u, 0u
 };

static const QType JTable_5_43891[]=
 {
  225u, 0u, 174u, 228u, 182u,
  225u, 228u, 0u, 182u, 174u,
  225u, 0u, 174u, 228u, 182u
 };

static const QType JTable_5_51871[]=
 {
  0u, 170u, 104u, 278u, 167u,
  0u, 278u, 170u, 167u, 104u,
  0u, 170u, 104u, 278u, 167u
 };

static const QType JTable_5_106591[]=
 {
  182u, 116u, 374u, 47u, 0u,
  182u, 47u, 116u, 0u, 374u,
  182u, 116u, 374u, 47u, 0u
 };

static const QType JTable_5_461891[]=
 {
  0u, 760u, 199u, 78u, 122u,
  0u, 78u, 760u, 122u, 199u,
  0u, 760u, 199u, 78u, 122u
 };

static const QType JTable_5_3233231[]=
 {
  749u, 1155u, 55u, 0u, 1925u,
  749u, 0u, 1155u, 1925u, 55u,
  749u, 1155u, 55u, 0u, 1925u
 };

static const QType JTable_5_691[]=
 {
  24u, 30u, 0u, 15u, 10u,
  24u, 15u, 30u, 10u, 0u,
  24u, 30u, 0u, 15u, 10u
 };

static const QType JTable_5_2531[]=
 {
  52u, 46u, 54u, 47u, 0u,
  52u, 47u, 46u, 0u, 54u,
  52u, 46u, 54u, 47u, 0u
 };

static const QType JTable_5_3911[]=
 {
  22u, 0u, 2u, 69u, 16u,
  22u, 69u, 0u, 16u, 2u,
  22u, 0u, 2u, 69u, 16u
 };

static const QType JTable_5_4831[]=
 {
  35u, 17u, 83u, 29u, 0u,
  35u, 29u, 17u, 0u, 83u,
  35u, 17u, 83u, 29u, 0u
 };

static const QType JTable_5_7591[]=
 {
  11u, 33u, 99u, 0u, 21u,
  11u, 0u, 33u, 21u, 99u,
  11u, 33u, 99u, 0u, 21u
 };

static const QType JTable_5_8971[]=
 {
  68u, 98u, 2u, 41u, 0u,
  68u, 41u, 98u, 0u, 2u,
  68u, 98u, 2u, 41u, 0u
 };

static const QType JTable_5_11731[]=
 {
  0u, 12u, 3u, 114u, 10u,
  0u, 114u, 12u, 10u, 3u,
  0u, 12u, 3u, 114u, 10u
 };

static const QType JTable_5_62791[]=
 {
  277u, 181u, 259u, 127u, 0u,
  277u, 127u, 181u, 0u, 259u,
  277u, 181u, 259u, 127u, 0u
 };

static const QType JTable_5_91771[]=
 {
  322u, 0u, 162u, 69u, 276u,
  322u, 69u, 0u, 276u, 162u,
  322u, 0u, 162u, 69u, 276u
 };

static const QType JTable_5_336491[]=
 {
  212u, 0u, 577u, 354u, 626u,
  212u, 354u, 0u, 626u, 577u,
  212u, 0u, 577u, 354u, 626u
 };

static const QType JTable_5_355811[]=
 {
  52u, 526u, 294u, 587u, 0u,
  52u, 587u, 526u, 0u, 294u,
  52u, 526u, 294u, 587u, 0u
 };

static const QType JTable_5_520031[]=
 {
  706u, 698u, 804u, 0u, 611u,
  706u, 0u, 698u, 611u, 804u,
  706u, 698u, 804u, 0u, 611u
 };

static const QType JTable_5_903211[]=
 {
  1154u, 0u, 300u, 495u, 570u,
  1154u, 495u, 0u, 570u, 300u,
  1154u, 0u, 300u, 495u, 570u
 };

static const QType JTable_5_1193011[]=
 {
  1072u, 966u, 1194u, 1077u, 0u,
  1072u, 1077u, 966u, 0u, 1194u,
  1072u, 966u, 1194u, 1077u, 0u
 };

static const QType JTable_5_2897311[]=
 {
  657u, 1107u, 2061u, 0u, 659u,
  657u, 0u, 1107u, 659u, 2061u,
  657u, 1107u, 2061u, 0u, 659u
 };

static const QType JTable_5_13123111[]=
 {
  3339u, 630u, 0u, 3690u, 1960u,
  3339u, 3690u, 630u, 1960u, 0u,
  3339u, 630u, 0u, 3690u, 1960u
 };

static const QType JTable_5_17160991[]=
 {
  3194u, 4355u, 3620u, 4610u, 0u,
  3194u, 4610u, 4355u, 0u, 3620u,
  3194u, 4355u, 3620u, 4610u, 0u
 };

static const TestSet::JTable JSet_5[]=
 {
  { 11u , 1u , JTable_5_11 },
  { 31u , 1u , JTable_5_31 },
  { 71u , 2u , JTable_5_71 },
  { 211u , 2u , JTable_5_211 },
  { 331u , 3u , JTable_5_331 },
  { 2311u , 3u , JTable_5_2311 },
  { 131u , 4u , JTable_5_131 },
  { 911u , 4u , JTable_5_911 },
  { 2731u , 4u , JTable_5_2731 },
  { 1871u , 5u , JTable_5_1871 },
  { 3571u , 5u , JTable_5_3571 },
  { 46411u , 5u , JTable_5_46411 },
  { 72931u , 5u , JTable_5_72931 },
  { 191u , 6u , JTable_5_191 },
  { 571u , 6u , JTable_5_571 },
  { 6271u , 6u , JTable_5_6271 },
  { 7411u , 6u , JTable_5_7411 },
  { 17291u , 6u , JTable_5_17291 },
  { 35531u , 6u , JTable_5_35531 },
  { 43891u , 6u , JTable_5_43891 },
  { 51871u , 6u , JTable_5_51871 },
  { 106591u , 6u , JTable_5_106591 },
  { 461891u , 6u , JTable_5_461891 },
  { 3233231u , 6u , JTable_5_3233231 },
  { 691u , 7u , JTable_5_691 },
  { 2531u , 7u , JTable_5_2531 },
  { 3911u , 7u , JTable_5_3911 },
  { 4831u , 7u , JTable_5_4831 },
  { 7591u , 7u , JTable_5_7591 },
  { 8971u , 7u , JTable_5_8971 },
  { 11731u , 7u , JTable_5_11731 },
  { 62791u , 7u , JTable_5_62791 },
  { 91771u , 7u , JTable_5_91771 },
  { 336491u , 7u , JTable_5_336491 },
  { 355811u , 7u , JTable_5_355811 },
  { 520031u , 7u , JTable_5_520031 },
  { 903211u , 7u , JTable_5_903211 },
  { 1193011u , 7u , JTable_5_1193011 },
  { 2897311u , 7u , JTable_5_2897311 },
  { 13123111u , 7u , JTable_5_13123111 },
  { 17160991u , 7u , JTable_5_17160991 }
 };

static const QType JTable_7_43[]=
 {
  3u, 1u, 0u, 3u, 5u, 1u, 7u,
  7u, 2u, 2u, 0u, 2u, 0u, 0u,
  3u, 1u, 3u, 1u, 7u, 5u, 0u,
  7u, 2u, 2u, 0u, 2u, 0u, 0u,
  3u, 1u, 0u, 3u, 5u, 1u, 7u
 };

static const QType JTable_7_71[]=
 {
  6u, 0u, 5u, 6u, 8u, 2u, 0u,
  0u, 7u, 7u, 9u, 7u, 9u, 9u,
  6u, 2u, 6u, 0u, 0u, 8u, 5u,
  0u, 7u, 7u, 9u, 7u, 9u, 9u,
  6u, 0u, 5u, 6u, 8u, 2u, 0u
 };

static const QType JTable_7_211[]=
 {
  0u, 8u, 18u, 6u, 10u, 5u, 8u,
  11u, 10u, 10u, 0u, 10u, 0u, 0u,
  0u, 5u, 6u, 8u, 8u, 10u, 18u,
  11u, 10u, 10u, 0u, 10u, 0u, 0u,
  0u, 8u, 18u, 6u, 10u, 5u, 8u
 };

static const QType JTable_7_463[]=
 {
  10u, 4u, 19u, 22u, 0u, 10u, 4u,
  23u, 0u, 0u, 6u, 0u, 6u, 6u,
  10u, 10u, 22u, 4u, 4u, 0u, 19u,
  23u, 0u, 0u, 6u, 0u, 6u, 6u,
  10u, 4u, 19u, 22u, 0u, 10u, 4u
 };

static const QType JTable_7_2311[]=
 {
  42u, 8u, 6u, 0u, 37u, 38u, 8u,
  49u, 0u, 0u, 2u, 0u, 2u, 2u,
  42u, 38u, 0u, 8u, 8u, 37u, 6u,
  49u, 0u, 0u, 2u, 0u, 2u, 2u,
  42u, 8u, 6u, 0u, 37u, 38u, 8u
 };

static const QType JTable_7_547[]=
 {
  24u, 26u, 0u, 18u, 18u, 15u, 24u,
  0u, 19u, 19u, 25u, 19u, 25u, 25u,
  24u, 15u, 18u, 26u, 24u, 18u, 0u,
  0u, 19u, 19u, 25u, 19u, 25u, 25u,
  24u, 26u, 0u, 18u, 18u, 15u, 24u
 };

static const QType JTable_7_911[]=
 {
  18u, 16u, 0u, 0u, 31u, 10u, 22u,
  3u, 22u, 22u, 0u, 22u, 0u, 0u,
  18u, 10u, 0u, 16u, 22u, 31u, 0u,
  3u, 22u, 22u, 0u, 22u, 0u, 0u,
  18u, 16u, 0u, 0u, 31u, 10u, 22u
 };

static const QType JTable_7_2003[]=
 {
  21u, 2u, 18u, 50u, 8u, 12u, 0u,
  45u, 22u, 22u, 0u, 22u, 0u, 0u,
  21u, 12u, 50u, 2u, 0u, 8u, 18u,
  45u, 22u, 22u, 0u, 22u, 0u, 0u,
  21u, 2u, 18u, 50u, 8u, 12u, 0u
 };

static const QType JTable_7_2731[]=
 {
  15u, 0u, 42u, 18u, 28u, 60u, 18u,
  49u, 30u, 30u, 0u, 30u, 0u, 0u,
  15u, 60u, 18u, 0u, 18u, 28u, 42u,
  49u, 30u, 30u, 0u, 30u, 0u, 0u,
  15u, 0u, 42u, 18u, 28u, 60u, 18u
 };

static const QType JTable_7_6007[]=
 {
  24u, 14u, 0u, 78u, 28u, 50u, 71u,
  71u, 46u, 46u, 0u, 46u, 0u, 0u,
  24u, 50u, 78u, 14u, 71u, 28u, 0u,
  71u, 46u, 46u, 0u, 46u, 0u, 0u,
  24u, 14u, 0u, 78u, 28u, 50u, 71u
 };

static const QType JTable_7_239[]=
 {
  16u, 1u, 10u, 6u, 0u, 10u, 12u,
  0u, 3u, 3u, 13u, 3u, 13u, 13u,
  16u, 10u, 6u, 1u, 12u, 0u, 10u,
  0u, 3u, 3u, 13u, 3u, 13u, 13u,
  16u, 1u, 10u, 6u, 0u, 10u, 12u
 };

static const QType JTable_7_3571[]=
 {
  16u, 46u, 40u, 34u, 0u, 1u, 58u,
  0u, 43u, 43u, 1u, 43u, 1u, 1u,
  16u, 1u, 34u, 46u, 58u, 0u, 40u,
  0u, 43u, 43u, 1u, 43u, 1u, 1u,
  16u, 46u, 40u, 34u, 0u, 1u, 58u
 };

static const QType JTable_7_9283[]=
 {
  18u, 10u, 108u, 28u, 10u, 35u, 0u,
  103u, 0u, 0u, 26u, 0u, 26u, 26u,
  18u, 35u, 28u, 10u, 0u, 10u, 108u,
  103u, 0u, 0u, 26u, 0u, 26u, 26u,
  18u, 10u, 108u, 28u, 10u, 35u, 0u
 };

static const QType JTable_7_46411[]=
 {
  0u, 66u, 258u, 102u, 173u, 108u, 132u,
  59u, 162u, 162u, 0u, 162u, 0u, 0u,
  0u, 108u, 102u, 66u, 132u, 173u, 258u,
  59u, 162u, 162u, 0u, 162u, 0u, 0u,
  0u, 66u, 258u, 102u, 173u, 108u, 132u
 };

static const QType JTable_7_102103[]=
 {
  226u, 78u, 346u, 48u, 0u, 80u, 187u,
  305u, 0u, 0u, 178u, 0u, 178u, 178u,
  226u, 80u, 48u, 78u, 187u, 0u, 346u,
  305u, 0u, 0u, 178u, 0u, 178u, 178u,
  226u, 78u, 346u, 48u, 0u, 80u, 187u
 };

static const QType JTable_7_2927[]=
 {
  14u, 0u, 24u, 14u, 30u, 20u, 65u,
  39u, 0u, 0u, 38u, 0u, 38u, 38u,
  14u, 20u, 14u, 0u, 65u, 30u, 24u,
  39u, 0u, 0u, 38u, 0u, 38u, 38u,
  14u, 0u, 24u, 14u, 30u, 20u, 65u
 };

static const QType JTable_7_4523[]=
 {
  62u, 80u, 42u, 62u, 57u, 0u, 60u,
  0u, 33u, 33u, 67u, 33u, 67u, 67u,
  62u, 0u, 62u, 80u, 60u, 57u, 42u,
  0u, 33u, 33u, 67u, 33u, 67u, 67u,
  62u, 80u, 42u, 62u, 57u, 0u, 60u
 };

static const QType JTable_7_8779[]=
 {
  46u, 114u, 24u, 33u, 54u, 0u, 36u,
  67u, 0u, 0u, 66u, 0u, 66u, 66u,
  46u, 0u, 33u, 114u, 36u, 54u, 24u,
  67u, 0u, 0u, 66u, 0u, 66u, 66u,
  46u, 114u, 24u, 33u, 54u, 0u, 36u
 };

static const QType JTable_7_13567[]=
 {
  98u, 32u, 47u, 86u, 0u, 116u, 110u,
  0u, 119u, 119u, 65u, 119u, 65u, 65u,
  98u, 116u, 86u, 32u, 110u, 0u, 47u,
  0u, 119u, 119u, 65u, 119u, 65u, 65u,
  98u, 32u, 47u, 86u, 0u, 116u, 110u
 };

static const QType JTable_7_17291[]=
 {
  158u, 92u, 74u, 0u, 80u, 69u, 30u,
  27u, 98u, 98u, 0u, 98u, 0u, 0u,
  158u, 69u, 0u, 92u, 30u, 80u, 74u,
  27u, 98u, 98u, 0u, 98u, 0u, 0u,
  158u, 92u, 74u, 0u, 80u, 69u, 30u
 };

static const QType JTable_7_38039[]=
 {
  138u, 159u, 224u, 50u, 144u, 110u, 0u,
  0u, 27u, 27u, 157u, 27u, 157u, 157u,
  138u, 110u, 50u, 159u, 0u, 144u, 224u,
  0u, 27u, 27u, 157u, 27u, 157u, 157u,
  138u, 159u, 224u, 50u, 144u, 110u, 0u
 };

static const QType JTable_7_43891[]=
 {
  30u, 6u, 135u, 12u, 148u, 186u, 0u,
  223u, 42u, 42u, 0u, 42u, 0u, 0u,
  30u, 186u, 12u, 6u, 0u, 148u, 135u,
  223u, 42u, 42u, 0u, 42u, 0u, 0u,
  30u, 6u, 135u, 12u, 148u, 186u, 0u
 };

static const QType JTable_7_51871[]=
 {
  178u, 136u, 266u, 0u, 78u, 148u, 201u,
  49u, 0u, 0u, 170u, 0u, 170u, 170u,
  178u, 148u, 0u, 136u, 201u, 78u, 266u,
  49u, 0u, 0u, 170u, 0u, 170u, 170u,
  178u, 136u, 266u, 0u, 78u, 148u, 201u
 };

static const QType JTable_7_58787[]=
 {
  186u, 66u, 80u, 0u, 206u, 245u, 56u,
  259u, 58u, 58u, 0u, 58u, 0u, 0u,
  186u, 245u, 0u, 66u, 56u, 206u, 80u,
  259u, 58u, 58u, 0u, 58u, 0u, 0u,
  186u, 66u, 80u, 0u, 206u, 245u, 56u
 };

static const QType JTable_7_1939939[]=
 {
  0u, 1624u, 846u, 1146u, 1194u, 1011u, 492u,
  0u, 1037u, 1037u, 71u, 1037u, 71u, 71u,
  0u, 1011u, 1146u, 1624u, 492u, 1194u, 846u,
  0u, 1037u, 1037u, 71u, 1037u, 71u, 71u,
  0u, 1624u, 846u, 1146u, 1194u, 1011u, 492u
 };

static const QType JTable_7_3233231[]=
 {
  1727u, 0u, 342u, 260u, 1530u, 524u, 1202u,
  1869u, 0u, 0u, 170u, 0u, 170u, 170u,
  1727u, 524u, 260u, 0u, 1202u, 1530u, 342u,
  1869u, 0u, 0u, 170u, 0u, 170u, 170u,
  1727u, 0u, 342u, 260u, 1530u, 524u, 1202u
 };

static const QType JTable_7_967[]=
 {
  30u, 21u, 0u, 20u, 0u, 6u, 6u,
  29u, 0u, 0u, 18u, 0u, 18u, 18u,
  30u, 6u, 20u, 21u, 6u, 0u, 0u,
  29u, 0u, 0u, 18u, 0u, 18u, 18u,
  30u, 21u, 0u, 20u, 0u, 6u, 6u
 };

static const QType JTable_7_4831[]=
 {
  28u, 30u, 70u, 34u, 59u, 72u, 0u,
  67u, 0u, 0u, 38u, 0u, 38u, 38u,
  28u, 72u, 34u, 30u, 0u, 59u, 70u,
  67u, 0u, 0u, 38u, 0u, 38u, 38u,
  28u, 30u, 70u, 34u, 59u, 72u, 0u
 };

static const QType JTable_7_10627[]=
 {
  0u, 13u, 15u, 25u, 19u, 113u, 3u,
  109u, 0u, 0u, 38u, 0u, 38u, 38u,
  0u, 113u, 25u, 13u, 3u, 19u, 15u,
  109u, 0u, 0u, 38u, 0u, 38u, 38u,
  0u, 13u, 15u, 25u, 19u, 113u, 3u
 };

static const QType JTable_7_62791[]=
 {
  155u, 270u, 200u, 140u, 46u, 210u, 0u,
  0u, 259u, 259u, 149u, 259u, 149u, 149u,
  155u, 210u, 140u, 270u, 0u, 46u, 200u,
  0u, 259u, 259u, 149u, 259u, 149u, 149u,
  155u, 270u, 200u, 140u, 46u, 210u, 0u
 };

static const QType JTable_7_91771[]=
 {
  178u, 282u, 144u, 0u, 330u, 249u, 300u,
  0u, 311u, 311u, 293u, 311u, 293u, 293u,
  178u, 249u, 0u, 282u, 300u, 330u, 144u,
  0u, 311u, 311u, 293u, 311u, 293u, 293u,
  178u, 282u, 144u, 0u, 330u, 249u, 300u
 };

static const QType JTable_7_138139[]=
 {
  0u, 75u, 130u, 420u, 100u, 250u, 242u,
  397u, 0u, 0u, 110u, 0u, 110u, 110u,
  0u, 250u, 420u, 75u, 242u, 100u, 130u,
  397u, 0u, 0u, 110u, 0u, 110u, 110u,
  0u, 75u, 130u, 420u, 100u, 250u, 242u
 };

static const QType JTable_7_336491[]=
 {
  0u, 177u, 545u, 485u, 483u, 227u, 567u,
  0u, 489u, 489u, 619u, 489u, 619u, 619u,
  0u, 227u, 485u, 177u, 567u, 483u, 545u,
  0u, 489u, 489u, 619u, 489u, 619u, 619u,
  0u, 177u, 545u, 485u, 483u, 227u, 567u
 };

static const QType JTable_7_355811[]=
 {
  250u, 0u, 58u, 636u, 174u, 451u, 376u,
  339u, 442u, 442u, 0u, 442u, 0u, 0u,
  250u, 451u, 636u, 0u, 376u, 174u, 58u,
  339u, 442u, 442u, 0u, 442u, 0u, 0u,
  250u, 0u, 58u, 636u, 174u, 451u, 376u
 };

static const QType JTable_7_520031[]=
 {
  333u, 592u, 430u, 870u, 288u, 0u, 538u,
  0u, 71u, 71u, 561u, 71u, 561u, 561u,
  333u, 0u, 870u, 592u, 538u, 288u, 430u,
  0u, 71u, 71u, 561u, 71u, 561u, 561u,
  333u, 592u, 430u, 870u, 288u, 0u, 538u
 };

static const QType JTable_7_782783[]=
 {
  252u, 806u, 0u, 144u, 201u, 842u, 554u,
  885u, 0u, 0u, 442u, 0u, 442u, 442u,
  252u, 842u, 144u, 806u, 554u, 201u, 0u,
  885u, 0u, 0u, 442u, 0u, 442u, 442u,
  252u, 806u, 0u, 144u, 201u, 842u, 554u
 };

static const QType JTable_7_903211[]=
 {
  1144u, 624u, 462u, 234u, 390u, 351u, 0u,
  553u, 702u, 702u, 0u, 702u, 0u, 0u,
  1144u, 351u, 234u, 624u, 0u, 390u, 462u,
  553u, 702u, 702u, 0u, 702u, 0u, 0u,
  1144u, 624u, 462u, 234u, 390u, 351u, 0u
 };

static const QType JTable_7_1193011[]=
 {
  372u, 0u, 754u, 654u, 372u, 1329u, 522u,
  1021u, 630u, 630u, 0u, 630u, 0u, 0u,
  372u, 1329u, 654u, 0u, 522u, 372u, 754u,
  1021u, 630u, 630u, 0u, 630u, 0u, 0u,
  372u, 0u, 754u, 654u, 372u, 1329u, 522u
 };

static const QType JTable_7_2348347[]=
 {
  1239u, 582u, 1308u, 0u, 310u, 1578u, 1044u,
  0u, 1631u, 1631u, 1325u, 1631u, 1325u, 1325u,
  1239u, 1578u, 0u, 582u, 1044u, 310u, 1308u,
  0u, 1631u, 1631u, 1325u, 1631u, 1325u, 1325u,
  1239u, 582u, 1308u, 0u, 310u, 1578u, 1044u
 };

static const QType JTable_7_2624623[]=
 {
  1452u, 1674u, 1814u, 0u, 1212u, 966u, 861u,
  0u, 727u, 727u, 1585u, 727u, 1585u, 1585u,
  1452u, 966u, 0u, 1674u, 861u, 1212u, 1814u,
  0u, 727u, 727u, 1585u, 727u, 1585u, 1585u,
  1452u, 1674u, 1814u, 0u, 1212u, 966u, 861u
 };

static const QType JTable_7_13123111[]=
 {
  3970u, 102u, 0u, 1328u, 1896u, 2321u, 1190u,
  2291u, 0u, 0u, 2638u, 0u, 2638u, 2638u,
  3970u, 2321u, 1328u, 102u, 1190u, 1896u, 0u,
  2291u, 0u, 0u, 2638u, 0u, 2638u, 2638u,
  3970u, 102u, 0u, 1328u, 1896u, 2321u, 1190u
 };

static const QType JTable_7_17160991[]=
 {
  4938u, 2943u, 4292u, 2958u, 3546u, 0u, 3372u,
  0u, 3301u, 3301u, 523u, 3301u, 523u, 523u,
  4938u, 0u, 2958u, 2943u, 3372u, 3546u, 4292u,
  0u, 3301u, 3301u, 523u, 3301u, 523u, 523u,
  4938u, 2943u, 4292u, 2958u, 3546u, 0u, 3372u
 };

static const TestSet::JTable JSet_7[]=
 {
  { 43u , 2u , JTable_7_43 },
  { 71u , 2u , JTable_7_71 },
  { 211u , 2u , JTable_7_211 },
  { 463u , 3u , JTable_7_463 },
  { 2311u , 3u , JTable_7_2311 },
  { 547u , 4u , JTable_7_547 },
  { 911u , 4u , JTable_7_911 },
  { 2003u , 4u , JTable_7_2003 },
  { 2731u , 4u , JTable_7_2731 },
  { 6007u , 4u , JTable_7_6007 },
  { 239u , 5u , JTable_7_239 },
  { 3571u , 5u , JTable_7_3571 },
  { 9283u , 5u , JTable_7_9283 },
  { 46411u , 5u , JTable_7_46411 },
  { 102103u , 5u , JTable_7_102103 },
  { 2927u , 6u , JTable_7_2927 },
  { 4523u , 6u , JTable_7_4523 },
  { 8779u , 6u , JTable_7_8779 },
  { 13567u , 6u , JTable_7_13567 },
  { 17291u , 6u , JTable_7_17291 },
  { 38039u , 6u , JTable_7_38039 },
  { 43891u , 6u , JTable_7_43891 },
  { 51871u , 6u , JTable_7_51871 },
  { 58787u , 6u , JTable_7_58787 },
  { 1939939u , 6u , JTable_7_1939939 },
  { 3233231u , 6u , JTable_7_3233231 },
  { 967u , 7u , JTable_7_967 },
  { 4831u , 7u , JTable_7_4831 },
  { 10627u , 7u , JTable_7_10627 },
  { 62791u , 7u , JTable_7_62791 },
  { 91771u , 7u , JTable_7_91771 },
  { 138139u , 7u , JTable_7_138139 },
  { 336491u , 7u , JTable_7_336491 },
  { 355811u , 7u , JTable_7_355811 },
  { 520031u , 7u , JTable_7_520031 },
  { 782783u , 7u , JTable_7_782783 },
  { 903211u , 7u , JTable_7_903211 },
  { 1193011u , 7u , JTable_7_1193011 },
  { 2348347u , 7u , JTable_7_2348347 },
  { 2624623u , 7u , JTable_7_2624623 },
  { 13123111u , 7u , JTable_7_13123111 },
  { 17160991u , 7u , JTable_7_17160991 }
 };

static const QType JTable_11_23[]=
 {
  0u, 2u, 4u, 2u, 2u, 4u, 0u, 3u, 2u, 2u, 0u,
  3u, 3u, 2u, 1u, 4u, 2u, 1u, 0u, 0u, 4u, 1u,
  3u, 0u, 2u, 2u, 1u, 0u, 4u, 3u, 4u, 1u, 1u,
  3u, 2u, 4u, 1u, 0u, 1u, 3u, 1u, 2u, 0u, 4u,
  0u, 2u, 3u, 4u, 2u, 2u, 0u, 2u, 0u, 2u, 4u,
  3u, 2u, 4u, 1u, 0u, 1u, 3u, 1u, 2u, 0u, 4u,
  3u, 0u, 2u, 2u, 1u, 0u, 4u, 3u, 4u, 1u, 1u,
  3u, 3u, 2u, 1u, 4u, 2u, 1u, 0u, 0u, 4u, 1u,
  0u, 2u, 4u, 2u, 2u, 4u, 0u, 3u, 2u, 2u, 0u
 };

static const QType JTable_11_67[]=
 {
  6u, 8u, 2u, 4u, 6u, 4u, 6u, 0u, 4u, 1u, 2u,
  5u, 0u, 7u, 7u, 2u, 1u, 3u, 3u, 2u, 2u, 0u,
  5u, 2u, 1u, 7u, 0u, 3u, 2u, 0u, 2u, 3u, 7u,
  5u, 7u, 2u, 3u, 2u, 0u, 0u, 7u, 1u, 3u, 2u,
  6u, 1u, 0u, 4u, 4u, 8u, 2u, 4u, 6u, 6u, 2u,
  5u, 7u, 2u, 3u, 2u, 0u, 0u, 7u, 1u, 3u, 2u,
  5u, 2u, 1u, 7u, 0u, 3u, 2u, 0u, 2u, 3u, 7u,
  5u, 0u, 7u, 7u, 2u, 1u, 3u, 3u, 2u, 2u, 0u,
  6u, 8u, 2u, 4u, 6u, 4u, 6u, 0u, 4u, 1u, 2u
 };

static const QType JTable_11_331[]=
 {
  3u, 10u, 2u, 14u, 2u, 6u, 16u, 8u, 0u, 0u, 4u,
  18u, 20u, 13u, 0u, 14u, 8u, 11u, 13u, 9u, 16u, 9u,
  18u, 9u, 8u, 13u, 9u, 13u, 14u, 20u, 16u, 11u, 0u,
  18u, 13u, 14u, 11u, 9u, 9u, 20u, 0u, 8u, 13u, 16u,
  3u, 0u, 8u, 6u, 14u, 10u, 4u, 0u, 16u, 2u, 2u,
  18u, 13u, 14u, 11u, 9u, 9u, 20u, 0u, 8u, 13u, 16u,
  18u, 9u, 8u, 13u, 9u, 13u, 14u, 20u, 16u, 11u, 0u,
  18u, 20u, 13u, 0u, 14u, 8u, 11u, 13u, 9u, 16u, 9u,
  3u, 10u, 2u, 14u, 2u, 6u, 16u, 8u, 0u, 0u, 4u
 };

static const QType JTable_11_463[]=
 {
  10u, 2u, 6u, 16u, 2u, 20u, 12u, 8u, 0u, 1u, 10u,
  17u, 4u, 14u, 13u, 10u, 9u, 23u, 7u, 6u, 0u, 6u,
  17u, 6u, 9u, 14u, 6u, 7u, 10u, 4u, 0u, 23u, 13u,
  17u, 14u, 10u, 23u, 6u, 6u, 4u, 13u, 9u, 7u, 0u,
  10u, 1u, 8u, 20u, 16u, 2u, 10u, 0u, 12u, 2u, 6u,
  17u, 14u, 10u, 23u, 6u, 6u, 4u, 13u, 9u, 7u, 0u,
  17u, 6u, 9u, 14u, 6u, 7u, 10u, 4u, 0u, 23u, 13u,
  17u, 4u, 14u, 13u, 10u, 9u, 23u, 7u, 6u, 0u, 6u,
  10u, 2u, 6u, 16u, 2u, 20u, 12u, 8u, 0u, 1u, 10u
 };

static const QType JTable_11_2311[]=
 {
  11u, 17u, 0u, 23u, 33u, 19u, 7u, 37u, 35u, 21u, 49u,
  19u, 18u, 18u, 54u, 11u, 25u, 23u, 34u, 31u, 0u, 8u,
  19u, 31u, 25u, 18u, 8u, 34u, 11u, 18u, 0u, 23u, 54u,
  19u, 18u, 11u, 23u, 31u, 8u, 18u, 54u, 25u, 34u, 0u,
  11u, 21u, 37u, 19u, 23u, 17u, 49u, 35u, 7u, 33u, 0u,
  19u, 18u, 11u, 23u, 31u, 8u, 18u, 54u, 25u, 34u, 0u,
  19u, 31u, 25u, 18u, 8u, 34u, 11u, 18u, 0u, 23u, 54u,
  19u, 18u, 18u, 54u, 11u, 25u, 23u, 34u, 31u, 0u, 8u,
  11u, 17u, 0u, 23u, 33u, 19u, 7u, 37u, 35u, 21u, 49u
 };

static const QType JTable_11_859[]=
 {
  22u, 14u, 12u, 28u, 18u, 22u, 0u, 12u, 14u, 5u, 28u,
  14u, 9u, 23u, 0u, 17u, 16u, 12u, 24u, 31u, 13u, 5u,
  14u, 31u, 16u, 23u, 5u, 24u, 17u, 9u, 13u, 12u, 0u,
  14u, 23u, 17u, 12u, 31u, 5u, 9u, 0u, 16u, 24u, 13u,
  22u, 5u, 12u, 22u, 28u, 14u, 28u, 14u, 0u, 18u, 12u,
  14u, 23u, 17u, 12u, 31u, 5u, 9u, 0u, 16u, 24u, 13u,
  14u, 31u, 16u, 23u, 5u, 24u, 17u, 9u, 13u, 12u, 0u,
  14u, 9u, 23u, 0u, 17u, 16u, 12u, 24u, 31u, 13u, 5u,
  22u, 14u, 12u, 28u, 18u, 22u, 0u, 12u, 14u, 5u, 28u
 };

static const QType JTable_11_2003[]=
 {
  26u, 30u, 24u, 8u, 40u, 26u, 2u, 10u, 0u, 36u, 17u,
  28u, 33u, 30u, 34u, 36u, 38u, 26u, 12u, 0u, 50u, 20u,
  28u, 0u, 38u, 30u, 20u, 12u, 36u, 33u, 50u, 26u, 34u,
  28u, 30u, 36u, 26u, 0u, 20u, 33u, 34u, 38u, 12u, 50u,
  26u, 36u, 10u, 26u, 8u, 30u, 17u, 0u, 2u, 40u, 24u,
  28u, 30u, 36u, 26u, 0u, 20u, 33u, 34u, 38u, 12u, 50u,
  28u, 0u, 38u, 30u, 20u, 12u, 36u, 33u, 50u, 26u, 34u,
  28u, 33u, 30u, 34u, 36u, 38u, 26u, 12u, 0u, 50u, 20u,
  26u, 30u, 24u, 8u, 40u, 26u, 2u, 10u, 0u, 36u, 17u
 };

static const QType JTable_11_6007[]=
 {
  62u, 32u, 66u, 76u, 32u, 0u, 54u, 25u, 72u, 46u, 62u,
  28u, 38u, 52u, 22u, 27u, 68u, 70u, 0u, 42u, 0u, 26u,
  28u, 42u, 68u, 52u, 26u, 0u, 27u, 38u, 0u, 70u, 22u,
  28u, 52u, 27u, 70u, 42u, 26u, 38u, 22u, 68u, 0u, 0u,
  62u, 46u, 25u, 0u, 76u, 32u, 62u, 72u, 54u, 32u, 66u,
  28u, 52u, 27u, 70u, 42u, 26u, 38u, 22u, 68u, 0u, 0u,
  28u, 42u, 68u, 52u, 26u, 0u, 27u, 38u, 0u, 70u, 22u,
  28u, 38u, 52u, 22u, 27u, 68u, 70u, 0u, 42u, 0u, 26u,
  62u, 32u, 66u, 76u, 32u, 0u, 54u, 25u, 72u, 46u, 62u
 };

static const QType JTable_11_1123[]=
 {
  14u, 2u, 2u, 28u, 18u, 28u, 0u, 12u, 14u, 1u, 12u,
  8u, 30u, 27u, 0u, 22u, 20u, 30u, 28u, 34u, 20u, 22u,
  8u, 34u, 20u, 27u, 22u, 28u, 22u, 30u, 20u, 30u, 0u,
  8u, 27u, 22u, 30u, 34u, 22u, 30u, 0u, 20u, 28u, 20u,
  14u, 1u, 12u, 28u, 28u, 2u, 12u, 14u, 0u, 18u, 2u,
  8u, 27u, 22u, 30u, 34u, 22u, 30u, 0u, 20u, 28u, 20u,
  8u, 34u, 20u, 27u, 22u, 28u, 22u, 30u, 20u, 30u, 0u,
  8u, 30u, 27u, 0u, 22u, 20u, 30u, 28u, 34u, 20u, 22u,
  14u, 2u, 2u, 28u, 18u, 28u, 0u, 12u, 14u, 1u, 12u
 };

static const QType JTable_11_1871[]=
 {
  36u, 18u, 40u, 4u, 16u, 18u, 22u, 26u, 0u, 22u, 39u,
  0u, 36u, 11u, 36u, 43u, 23u, 15u, 32u, 32u, 20u, 15u,
  0u, 32u, 23u, 11u, 15u, 32u, 43u, 36u, 20u, 15u, 36u,
  0u, 11u, 43u, 15u, 32u, 15u, 36u, 36u, 23u, 32u, 20u,
  36u, 22u, 26u, 18u, 4u, 18u, 39u, 0u, 22u, 16u, 40u,
  0u, 11u, 43u, 15u, 32u, 15u, 36u, 36u, 23u, 32u, 20u,
  0u, 32u, 23u, 11u, 15u, 32u, 43u, 36u, 20u, 15u, 36u,
  0u, 36u, 11u, 36u, 43u, 23u, 15u, 32u, 32u, 20u, 15u,
  36u, 18u, 40u, 4u, 16u, 18u, 22u, 26u, 0u, 22u, 39u
 };

static const QType JTable_11_72931[]=
 {
  282u, 108u, 49u, 206u, 136u, 112u, 0u, 86u, 144u, 230u, 98u,
  262u, 89u, 55u, 129u, 0u, 104u, 212u, 183u, 38u, 207u, 139u,
  262u, 38u, 104u, 55u, 139u, 183u, 0u, 89u, 207u, 212u, 129u,
  262u, 55u, 0u, 212u, 38u, 139u, 89u, 129u, 104u, 183u, 207u,
  282u, 230u, 86u, 112u, 206u, 108u, 98u, 144u, 0u, 136u, 49u,
  262u, 55u, 0u, 212u, 38u, 139u, 89u, 129u, 104u, 183u, 207u,
  262u, 38u, 104u, 55u, 139u, 183u, 0u, 89u, 207u, 212u, 129u,
  262u, 89u, 55u, 129u, 0u, 104u, 212u, 183u, 38u, 207u, 139u,
  282u, 108u, 49u, 206u, 136u, 112u, 0u, 86u, 144u, 230u, 98u
 };

static const QType JTable_11_102103[]=
 {
  296u, 198u, 205u, 112u, 86u, 290u, 112u, 44u, 70u, 126u, 0u,
  58u, 147u, 91u, 133u, 156u, 0u, 356u, 247u, 140u, 65u, 135u,
  58u, 140u, 0u, 91u, 135u, 247u, 156u, 147u, 65u, 356u, 133u,
  58u, 91u, 156u, 356u, 140u, 135u, 147u, 133u, 0u, 247u, 65u,
  296u, 126u, 44u, 290u, 112u, 198u, 0u, 70u, 112u, 86u, 205u,
  58u, 91u, 156u, 356u, 140u, 135u, 147u, 133u, 0u, 247u, 65u,
  58u, 140u, 0u, 91u, 135u, 247u, 156u, 147u, 65u, 356u, 133u,
  58u, 147u, 91u, 133u, 156u, 0u, 356u, 247u, 140u, 65u, 135u,
  296u, 198u, 205u, 112u, 86u, 290u, 112u, 44u, 70u, 126u, 0u
 };

static const QType JTable_11_419[]=
 {
  14u, 10u, 0u, 2u, 0u, 18u, 4u, 12u, 14u, 5u, 8u,
  8u, 10u, 3u, 4u, 22u, 2u, 4u, 0u, 2u, 2u, 8u,
  8u, 2u, 2u, 3u, 8u, 0u, 22u, 10u, 2u, 4u, 4u,
  8u, 3u, 22u, 4u, 2u, 8u, 10u, 4u, 2u, 0u, 2u,
  14u, 5u, 12u, 18u, 2u, 10u, 8u, 14u, 4u, 0u, 0u,
  8u, 3u, 22u, 4u, 2u, 8u, 10u, 4u, 2u, 0u, 2u,
  8u, 2u, 2u, 3u, 8u, 0u, 22u, 10u, 2u, 4u, 4u,
  8u, 10u, 3u, 4u, 22u, 2u, 4u, 0u, 2u, 2u, 8u,
  14u, 10u, 0u, 2u, 0u, 18u, 4u, 12u, 14u, 5u, 8u
 };

static const QType JTable_11_2927[]=
 {
  42u, 0u, 24u, 58u, 26u, 34u, 37u, 48u, 40u, 56u, 30u,
  14u, 48u, 30u, 6u, 0u, 37u, 26u, 48u, 20u, 38u, 40u,
  14u, 20u, 37u, 30u, 40u, 48u, 0u, 48u, 38u, 26u, 6u,
  14u, 30u, 0u, 26u, 20u, 40u, 48u, 6u, 37u, 48u, 38u,
  42u, 56u, 48u, 34u, 58u, 0u, 30u, 40u, 37u, 26u, 24u,
  14u, 30u, 0u, 26u, 20u, 40u, 48u, 6u, 37u, 48u, 38u,
  14u, 20u, 37u, 30u, 40u, 48u, 0u, 48u, 38u, 26u, 6u,
  14u, 48u, 30u, 6u, 0u, 37u, 26u, 48u, 20u, 38u, 40u,
  42u, 0u, 24u, 58u, 26u, 34u, 37u, 48u, 40u, 56u, 30u
 };

static const QType JTable_11_6271[]=
 {
  34u, 84u, 46u, 68u, 50u, 0u, 26u, 64u, 46u, 24u, 63u,
  55u, 38u, 0u, 53u, 86u, 40u, 72u, 37u, 81u, 57u, 52u,
  55u, 81u, 40u, 0u, 52u, 37u, 86u, 38u, 57u, 72u, 53u,
  55u, 0u, 86u, 72u, 81u, 52u, 38u, 53u, 40u, 37u, 57u,
  34u, 24u, 64u, 0u, 68u, 84u, 63u, 46u, 26u, 50u, 46u,
  55u, 0u, 86u, 72u, 81u, 52u, 38u, 53u, 40u, 37u, 57u,
  55u, 81u, 40u, 0u, 52u, 37u, 86u, 38u, 57u, 72u, 53u,
  55u, 38u, 0u, 53u, 86u, 40u, 72u, 37u, 81u, 57u, 52u,
  34u, 84u, 46u, 68u, 50u, 0u, 26u, 64u, 46u, 24u, 63u
 };

static const QType JTable_11_8779[]=
 {
  42u, 78u, 74u, 0u, 92u, 64u, 62u, 26u, 21u, 28u, 40u,
  32u, 69u, 24u, 34u, 49u, 42u, 35u, 101u, 61u, 80u, 0u,
  32u, 61u, 42u, 24u, 0u, 101u, 49u, 69u, 80u, 35u, 34u,
  32u, 24u, 49u, 35u, 61u, 0u, 69u, 34u, 42u, 101u, 80u,
  42u, 28u, 26u, 64u, 0u, 78u, 40u, 21u, 62u, 92u, 74u,
  32u, 24u, 49u, 35u, 61u, 0u, 69u, 34u, 42u, 101u, 80u,
  32u, 61u, 42u, 24u, 0u, 101u, 49u, 69u, 80u, 35u, 34u,
  32u, 69u, 24u, 34u, 49u, 42u, 35u, 101u, 61u, 80u, 0u,
  42u, 78u, 74u, 0u, 92u, 64u, 62u, 26u, 21u, 28u, 40u
 };

static const QType JTable_11_21319[]=
 {
  106u, 78u, 62u, 92u, 136u, 128u, 0u, 104u, 15u, 42u, 94u,
  93u, 0u, 65u, 87u, 8u, 85u, 8u, 68u, 42u, 97u, 139u,
  93u, 42u, 85u, 65u, 139u, 68u, 8u, 0u, 97u, 8u, 87u,
  93u, 65u, 8u, 8u, 42u, 139u, 0u, 87u, 85u, 68u, 97u,
  106u, 42u, 104u, 128u, 92u, 78u, 94u, 15u, 0u, 136u, 62u,
  93u, 65u, 8u, 8u, 42u, 139u, 0u, 87u, 85u, 68u, 97u,
  93u, 42u, 85u, 65u, 139u, 68u, 8u, 0u, 97u, 8u, 87u,
  93u, 0u, 65u, 87u, 8u, 85u, 8u, 68u, 42u, 97u, 139u,
  106u, 78u, 62u, 92u, 136u, 128u, 0u, 104u, 15u, 42u, 94u
 };

static const QType JTable_11_35531[]=
 {
  8u, 22u, 103u, 0u, 174u, 104u, 2u, 20u, 18u, 80u, 18u,
  0u, 47u, 29u, 85u, 64u, 36u, 32u, 213u, 38u, 39u, 21u,
  0u, 38u, 36u, 29u, 21u, 213u, 64u, 47u, 39u, 32u, 85u,
  0u, 29u, 64u, 32u, 38u, 21u, 47u, 85u, 36u, 213u, 39u,
  8u, 80u, 20u, 104u, 0u, 22u, 18u, 18u, 2u, 174u, 103u,
  0u, 29u, 64u, 32u, 38u, 21u, 47u, 85u, 36u, 213u, 39u,
  0u, 38u, 36u, 29u, 21u, 213u, 64u, 47u, 39u, 32u, 85u,
  0u, 47u, 29u, 85u, 64u, 36u, 32u, 213u, 38u, 39u, 21u,
  8u, 22u, 103u, 0u, 174u, 104u, 2u, 20u, 18u, 80u, 18u
 };

static const QType JTable_11_38039[]=
 {
  151u, 44u, 162u, 68u, 118u, 6u, 0u, 128u, 162u, 80u, 114u,
  144u, 190u, 113u, 90u, 148u, 0u, 169u, 207u, 177u, 104u, 175u,
  144u, 177u, 0u, 113u, 175u, 207u, 148u, 190u, 104u, 169u, 90u,
  144u, 113u, 148u, 169u, 177u, 175u, 190u, 90u, 0u, 207u, 104u,
  151u, 80u, 128u, 6u, 68u, 44u, 114u, 162u, 0u, 118u, 162u,
  144u, 113u, 148u, 169u, 177u, 175u, 190u, 90u, 0u, 207u, 104u,
  144u, 177u, 0u, 113u, 175u, 207u, 148u, 190u, 104u, 169u, 90u,
  144u, 190u, 113u, 90u, 148u, 0u, 169u, 207u, 177u, 104u, 175u,
  151u, 44u, 162u, 68u, 118u, 6u, 0u, 128u, 162u, 80u, 114u
 };

static const QType JTable_11_43891[]=
 {
  178u, 152u, 126u, 184u, 208u, 185u, 94u, 206u, 0u, 102u, 192u,
  163u, 198u, 194u, 0u, 209u, 200u, 235u, 219u, 182u, 205u, 163u,
  163u, 182u, 200u, 194u, 163u, 219u, 209u, 198u, 205u, 235u, 0u,
  163u, 194u, 209u, 235u, 182u, 163u, 198u, 0u, 200u, 219u, 205u,
  178u, 102u, 206u, 185u, 184u, 152u, 192u, 0u, 94u, 208u, 126u,
  163u, 194u, 209u, 235u, 182u, 163u, 198u, 0u, 200u, 219u, 205u,
  163u, 182u, 200u, 194u, 163u, 219u, 209u, 198u, 205u, 235u, 0u,
  163u, 198u, 194u, 0u, 209u, 200u, 235u, 219u, 182u, 205u, 163u,
  178u, 152u, 126u, 184u, 208u, 185u, 94u, 206u, 0u, 102u, 192u
 };

static const QType JTable_11_106591[]=
 {
  0u, 91u, 5u, 267u, 109u, 241u, 239u, 43u, 53u, 207u, 141u,
  192u, 227u, 240u, 305u, 143u, 325u, 0u, 56u, 238u, 241u, 166u,
  192u, 238u, 325u, 240u, 166u, 56u, 143u, 227u, 241u, 0u, 305u,
  192u, 240u, 143u, 0u, 238u, 166u, 227u, 305u, 325u, 56u, 241u,
  0u, 207u, 43u, 241u, 267u, 91u, 141u, 53u, 239u, 109u, 5u,
  192u, 240u, 143u, 0u, 238u, 166u, 227u, 305u, 325u, 56u, 241u,
  192u, 238u, 325u, 240u, 166u, 56u, 143u, 227u, 241u, 0u, 305u,
  192u, 227u, 240u, 305u, 143u, 325u, 0u, 56u, 238u, 241u, 166u,
  0u, 91u, 5u, 267u, 109u, 241u, 239u, 43u, 53u, 207u, 141u
 };

static const QType JTable_11_461891[]=
 {
  401u, 440u, 498u, 744u, 298u, 266u, 140u, 364u, 590u, 0u, 438u,
  524u, 735u, 0u, 253u, 223u, 549u, 432u, 388u, 398u, 637u, 370u,
  524u, 398u, 549u, 0u, 370u, 388u, 223u, 735u, 637u, 432u, 253u,
  524u, 0u, 223u, 432u, 398u, 370u, 735u, 253u, 549u, 388u, 637u,
  401u, 0u, 364u, 266u, 744u, 440u, 438u, 590u, 140u, 298u, 498u,
  524u, 0u, 223u, 432u, 398u, 370u, 735u, 253u, 549u, 388u, 637u,
  524u, 398u, 549u, 0u, 370u, 388u, 223u, 735u, 637u, 432u, 253u,
  524u, 735u, 0u, 253u, 223u, 549u, 432u, 388u, 398u, 637u, 370u,
  401u, 440u, 498u, 744u, 298u, 266u, 140u, 364u, 590u, 0u, 438u
 };

static const QType JTable_11_1939939[]=
 {
  424u, 814u, 1168u, 864u, 830u, 622u, 200u, 570u, 0u, 1493u, 846u,
  0u, 851u, 1425u, 1002u, 929u, 304u, 938u, 852u, 577u, 193u, 991u,
  0u, 577u, 304u, 1425u, 991u, 852u, 929u, 851u, 193u, 938u, 1002u,
  0u, 1425u, 929u, 938u, 577u, 991u, 851u, 1002u, 304u, 852u, 193u,
  424u, 1493u, 570u, 622u, 864u, 814u, 846u, 0u, 200u, 830u, 1168u,
  0u, 1425u, 929u, 938u, 577u, 991u, 851u, 1002u, 304u, 852u, 193u,
  0u, 577u, 304u, 1425u, 991u, 852u, 929u, 851u, 193u, 938u, 1002u,
  0u, 851u, 1425u, 1002u, 929u, 304u, 938u, 852u, 577u, 193u, 991u,
  424u, 814u, 1168u, 864u, 830u, 622u, 200u, 570u, 0u, 1493u, 846u
 };

static const QType JTable_11_3233231[]=
 {
  1138u, 1396u, 1602u, 1348u, 0u, 500u, 1640u, 571u, 1646u, 1010u, 1402u,
  1266u, 1574u, 944u, 996u, 1361u, 1658u, 1834u, 0u, 1228u, 570u, 624u,
  1266u, 1228u, 1658u, 944u, 624u, 0u, 1361u, 1574u, 570u, 1834u, 996u,
  1266u, 944u, 1361u, 1834u, 1228u, 624u, 1574u, 996u, 1658u, 0u, 570u,
  1138u, 1010u, 571u, 500u, 1348u, 1396u, 1402u, 1646u, 1640u, 0u, 1602u,
  1266u, 944u, 1361u, 1834u, 1228u, 624u, 1574u, 996u, 1658u, 0u, 570u,
  1266u, 1228u, 1658u, 944u, 624u, 0u, 1361u, 1574u, 570u, 1834u, 996u,
  1266u, 1574u, 944u, 996u, 1361u, 1658u, 1834u, 0u, 1228u, 570u, 624u,
  1138u, 1396u, 1602u, 1348u, 0u, 500u, 1640u, 571u, 1646u, 1010u, 1402u
 };

static const QType JTable_11_2531[]=
 {
  18u, 50u, 26u, 14u, 0u, 24u, 28u, 40u, 8u, 39u, 38u,
  44u, 21u, 39u, 16u, 13u, 16u, 0u, 22u, 45u, 31u, 5u,
  44u, 45u, 16u, 39u, 5u, 22u, 13u, 21u, 31u, 0u, 16u,
  44u, 39u, 13u, 0u, 45u, 5u, 21u, 16u, 16u, 22u, 31u,
  18u, 39u, 40u, 24u, 14u, 50u, 38u, 8u, 28u, 0u, 26u,
  44u, 39u, 13u, 0u, 45u, 5u, 21u, 16u, 16u, 22u, 31u,
  44u, 45u, 16u, 39u, 5u, 22u, 13u, 21u, 31u, 0u, 16u,
  44u, 21u, 39u, 16u, 13u, 16u, 0u, 22u, 45u, 31u, 5u,
  18u, 50u, 26u, 14u, 0u, 24u, 28u, 40u, 8u, 39u, 38u
 };

static const QType JTable_11_7591[]=
 {
  72u, 52u, 46u, 0u, 66u, 80u, 70u, 56u, 98u, 30u, 67u,
  76u, 52u, 95u, 50u, 79u, 65u, 73u, 84u, 0u, 38u, 69u,
  76u, 0u, 65u, 95u, 69u, 84u, 79u, 52u, 38u, 73u, 50u,
  76u, 95u, 79u, 73u, 0u, 69u, 52u, 50u, 65u, 84u, 38u,
  72u, 30u, 56u, 80u, 0u, 52u, 67u, 98u, 70u, 66u, 46u,
  76u, 95u, 79u, 73u, 0u, 69u, 52u, 50u, 65u, 84u, 38u,
  76u, 0u, 65u, 95u, 69u, 84u, 79u, 52u, 38u, 73u, 50u,
  76u, 52u, 95u, 50u, 79u, 65u, 73u, 84u, 0u, 38u, 69u,
  72u, 52u, 46u, 0u, 66u, 80u, 70u, 56u, 98u, 30u, 67u
 };

static const QType JTable_11_10627[]=
 {
  48u, 62u, 108u, 30u, 94u, 32u, 0u, 34u, 76u, 46u, 41u,
  10u, 25u, 72u, 94u, 18u, 62u, 32u, 86u, 40u, 0u, 44u,
  10u, 40u, 62u, 72u, 44u, 86u, 18u, 25u, 0u, 32u, 94u,
  10u, 72u, 18u, 32u, 40u, 44u, 25u, 94u, 62u, 86u, 0u,
  48u, 46u, 34u, 32u, 30u, 62u, 41u, 76u, 0u, 94u, 108u,
  10u, 72u, 18u, 32u, 40u, 44u, 25u, 94u, 62u, 86u, 0u,
  10u, 40u, 62u, 72u, 44u, 86u, 18u, 25u, 0u, 32u, 94u,
  10u, 25u, 72u, 94u, 18u, 62u, 32u, 86u, 40u, 0u, 44u,
  48u, 62u, 108u, 30u, 94u, 32u, 0u, 34u, 76u, 46u, 41u
 };

static const QType JTable_11_28843[]=
 {
  78u, 42u, 126u, 48u, 106u, 84u, 132u, 180u, 0u, 39u, 66u,
  90u, 21u, 114u, 72u, 189u, 54u, 0u, 58u, 63u, 27u, 81u,
  90u, 63u, 54u, 114u, 81u, 58u, 189u, 21u, 27u, 0u, 72u,
  90u, 114u, 189u, 0u, 63u, 81u, 21u, 72u, 54u, 58u, 27u,
  78u, 39u, 180u, 84u, 48u, 42u, 66u, 0u, 132u, 106u, 126u,
  90u, 114u, 189u, 0u, 63u, 81u, 21u, 72u, 54u, 58u, 27u,
  90u, 63u, 54u, 114u, 81u, 58u, 189u, 21u, 27u, 0u, 72u,
  90u, 21u, 114u, 72u, 189u, 54u, 0u, 58u, 63u, 27u, 81u,
  78u, 42u, 126u, 48u, 106u, 84u, 132u, 180u, 0u, 39u, 66u
 };

static const QType JTable_11_111827[]=
 {
  166u, 290u, 188u, 72u, 178u, 202u, 0u, 244u, 20u, 47u, 22u,
  10u, 188u, 201u, 210u, 88u, 196u, 90u, 0u, 274u, 8u, 10u,
  10u, 274u, 196u, 201u, 10u, 0u, 88u, 188u, 8u, 90u, 210u,
  10u, 201u, 88u, 90u, 274u, 10u, 188u, 210u, 196u, 0u, 8u,
  166u, 47u, 244u, 202u, 72u, 290u, 22u, 20u, 0u, 178u, 188u,
  10u, 201u, 88u, 90u, 274u, 10u, 188u, 210u, 196u, 0u, 8u,
  10u, 274u, 196u, 201u, 10u, 0u, 88u, 188u, 8u, 90u, 210u,
  10u, 188u, 201u, 210u, 88u, 196u, 90u, 0u, 274u, 8u, 10u,
  166u, 290u, 188u, 72u, 178u, 202u, 0u, 244u, 20u, 47u, 22u
 };

static const QType JTable_11_138139[]=
 {
  278u, 308u, 334u, 159u, 324u, 146u, 0u, 340u, 282u, 376u, 202u,
  298u, 144u, 130u, 108u, 170u, 0u, 378u, 346u, 155u, 224u, 136u,
  298u, 155u, 0u, 130u, 136u, 346u, 170u, 144u, 224u, 378u, 108u,
  298u, 130u, 170u, 378u, 155u, 136u, 144u, 108u, 0u, 346u, 224u,
  278u, 376u, 340u, 146u, 159u, 308u, 202u, 282u, 0u, 324u, 334u,
  298u, 130u, 170u, 378u, 155u, 136u, 144u, 108u, 0u, 346u, 224u,
  298u, 155u, 0u, 130u, 136u, 346u, 170u, 144u, 224u, 378u, 108u,
  298u, 144u, 130u, 108u, 170u, 0u, 378u, 346u, 155u, 224u, 136u,
  278u, 308u, 334u, 159u, 324u, 146u, 0u, 340u, 282u, 376u, 202u
 };

static const QType JTable_11_336491[]=
 {
  140u, 404u, 231u, 230u, 70u, 0u, 632u, 336u, 342u, 342u, 374u,
  502u, 283u, 243u, 615u, 162u, 262u, 0u, 365u, 526u, 357u, 391u,
  502u, 526u, 262u, 243u, 391u, 365u, 162u, 283u, 357u, 0u, 615u,
  502u, 243u, 162u, 0u, 526u, 391u, 283u, 615u, 262u, 365u, 357u,
  140u, 342u, 336u, 0u, 230u, 404u, 374u, 342u, 632u, 70u, 231u,
  502u, 243u, 162u, 0u, 526u, 391u, 283u, 615u, 262u, 365u, 357u,
  502u, 526u, 262u, 243u, 391u, 365u, 162u, 283u, 357u, 0u, 615u,
  502u, 283u, 243u, 615u, 162u, 262u, 0u, 365u, 526u, 357u, 391u,
  140u, 404u, 231u, 230u, 70u, 0u, 632u, 336u, 342u, 342u, 374u
 };

static const QType JTable_11_782783[]=
 {
  622u, 550u, 0u, 268u, 696u, 532u, 164u, 681u, 394u, 942u, 518u,
  178u, 0u, 537u, 524u, 490u, 621u, 784u, 53u, 777u, 571u, 480u,
  178u, 777u, 621u, 537u, 480u, 53u, 490u, 0u, 571u, 784u, 524u,
  178u, 537u, 490u, 784u, 777u, 480u, 0u, 524u, 621u, 53u, 571u,
  622u, 942u, 681u, 532u, 268u, 550u, 518u, 394u, 164u, 696u, 0u,
  178u, 537u, 490u, 784u, 777u, 480u, 0u, 524u, 621u, 53u, 571u,
  178u, 777u, 621u, 537u, 480u, 53u, 490u, 0u, 571u, 784u, 524u,
  178u, 0u, 537u, 524u, 490u, 621u, 784u, 53u, 777u, 571u, 480u,
  622u, 550u, 0u, 268u, 696u, 532u, 164u, 681u, 394u, 942u, 518u
 };

static const QType JTable_11_903211[]=
 {
  0u, 716u, 460u, 834u, 92u, 482u, 806u, 358u, 282u, 349u, 108u,
  431u, 0u, 526u, 575u, 326u, 1143u, 557u, 537u, 178u, 496u, 598u,
  431u, 178u, 1143u, 526u, 598u, 537u, 326u, 0u, 496u, 557u, 575u,
  431u, 526u, 326u, 557u, 178u, 598u, 0u, 575u, 1143u, 537u, 496u,
  0u, 349u, 358u, 482u, 834u, 716u, 108u, 282u, 806u, 92u, 460u,
  431u, 526u, 326u, 557u, 178u, 598u, 0u, 575u, 1143u, 537u, 496u,
  431u, 178u, 1143u, 526u, 598u, 537u, 326u, 0u, 496u, 557u, 575u,
  431u, 0u, 526u, 575u, 326u, 1143u, 557u, 537u, 178u, 496u, 598u,
  0u, 716u, 460u, 834u, 92u, 482u, 806u, 358u, 282u, 349u, 108u
 };

static const QType JTable_11_2348347[]=
 {
  758u, 812u, 190u, 450u, 2u, 1138u, 1183u, 0u, 1048u, 924u, 1172u,
  57u, 269u, 1131u, 642u, 919u, 1454u, 0u, 763u, 646u, 928u, 230u,
  57u, 646u, 1454u, 1131u, 230u, 763u, 919u, 269u, 928u, 0u, 642u,
  57u, 1131u, 919u, 0u, 646u, 230u, 269u, 642u, 1454u, 763u, 928u,
  758u, 924u, 0u, 1138u, 450u, 812u, 1172u, 1048u, 1183u, 2u, 190u,
  57u, 1131u, 919u, 0u, 646u, 230u, 269u, 642u, 1454u, 763u, 928u,
  57u, 646u, 1454u, 1131u, 230u, 763u, 919u, 269u, 928u, 0u, 642u,
  57u, 269u, 1131u, 642u, 919u, 1454u, 0u, 763u, 646u, 928u, 230u,
  758u, 812u, 190u, 450u, 2u, 1138u, 1183u, 0u, 1048u, 924u, 1172u
 };

static const QType JTable_11_2624623[]=
 {
  1142u, 908u, 1706u, 924u, 934u, 0u, 522u, 1621u, 500u, 1078u, 1092u,
  913u, 1105u, 1412u, 255u, 682u, 0u, 1409u, 1286u, 696u, 860u, 1501u,
  913u, 696u, 0u, 1412u, 1501u, 1286u, 682u, 1105u, 860u, 1409u, 255u,
  913u, 1412u, 682u, 1409u, 696u, 1501u, 1105u, 255u, 0u, 1286u, 860u,
  1142u, 1078u, 1621u, 0u, 924u, 908u, 1092u, 500u, 522u, 934u, 1706u,
  913u, 1412u, 682u, 1409u, 696u, 1501u, 1105u, 255u, 0u, 1286u, 860u,
  913u, 696u, 0u, 1412u, 1501u, 1286u, 682u, 1105u, 860u, 1409u, 255u,
  913u, 1105u, 1412u, 255u, 682u, 0u, 1409u, 1286u, 696u, 860u, 1501u,
  1142u, 908u, 1706u, 924u, 934u, 0u, 522u, 1621u, 500u, 1078u, 1092u
 };

static const QType JTable_11_13123111[]=
 {
  3382u, 454u, 2520u, 2334u, 2962u, 1403u, 0u, 584u, 2238u, 1304u, 1232u,
  465u, 1694u, 2788u, 0u, 2463u, 2452u, 3091u, 1079u, 494u, 447u, 2021u,
  465u, 494u, 2452u, 2788u, 2021u, 1079u, 2463u, 1694u, 447u, 3091u, 0u,
  465u, 2788u, 2463u, 3091u, 494u, 2021u, 1694u, 0u, 2452u, 1079u, 447u,
  3382u, 1304u, 584u, 1403u, 2334u, 454u, 1232u, 2238u, 0u, 2962u, 2520u,
  465u, 2788u, 2463u, 3091u, 494u, 2021u, 1694u, 0u, 2452u, 1079u, 447u,
  465u, 494u, 2452u, 2788u, 2021u, 1079u, 2463u, 1694u, 447u, 3091u, 0u,
  465u, 1694u, 2788u, 0u, 2463u, 2452u, 3091u, 1079u, 494u, 447u, 2021u,
  3382u, 454u, 2520u, 2334u, 2962u, 1403u, 0u, 584u, 2238u, 1304u, 1232u
 };

static const QType JTable_11_17160991[]=
 {
  2468u, 2982u, 1468u, 1266u, 0u, 4750u, 2666u, 2662u, 3633u, 2192u, 2048u,
  2762u, 2830u, 1090u, 823u, 4424u, 792u, 1384u, 0u, 788u, 1646u, 1566u,
  2762u, 788u, 792u, 1090u, 1566u, 0u, 4424u, 2830u, 1646u, 1384u, 823u,
  2762u, 1090u, 4424u, 1384u, 788u, 1566u, 2830u, 823u, 792u, 0u, 1646u,
  2468u, 2192u, 2662u, 4750u, 1266u, 2982u, 2048u, 3633u, 2666u, 0u, 1468u,
  2762u, 1090u, 4424u, 1384u, 788u, 1566u, 2830u, 823u, 792u, 0u, 1646u,
  2762u, 788u, 792u, 1090u, 1566u, 0u, 4424u, 2830u, 1646u, 1384u, 823u,
  2762u, 2830u, 1090u, 823u, 4424u, 792u, 1384u, 0u, 788u, 1646u, 1566u,
  2468u, 2982u, 1468u, 1266u, 0u, 4750u, 2666u, 2662u, 3633u, 2192u, 2048u
 };

static const TestSet::JTable JSet_11[]=
 {
  { 23u , 3u , JTable_11_23 },
  { 67u , 3u , JTable_11_67 },
  { 331u , 3u , JTable_11_331 },
  { 463u , 3u , JTable_11_463 },
  { 2311u , 3u , JTable_11_2311 },
  { 859u , 4u , JTable_11_859 },
  { 2003u , 4u , JTable_11_2003 },
  { 6007u , 4u , JTable_11_6007 },
  { 1123u , 5u , JTable_11_1123 },
  { 1871u , 5u , JTable_11_1871 },
  { 72931u , 5u , JTable_11_72931 },
  { 102103u , 5u , JTable_11_102103 },
  { 419u , 6u , JTable_11_419 },
  { 2927u , 6u , JTable_11_2927 },
  { 6271u , 6u , JTable_11_6271 },
  { 8779u , 6u , JTable_11_8779 },
  { 21319u , 6u , JTable_11_21319 },
  { 35531u , 6u , JTable_11_35531 },
  { 38039u , 6u , JTable_11_38039 },
  { 43891u , 6u , JTable_11_43891 },
  { 106591u , 6u , JTable_11_106591 },
  { 461891u , 6u , JTable_11_461891 },
  { 1939939u , 6u , JTable_11_1939939 },
  { 3233231u , 6u , JTable_11_3233231 },
  { 2531u , 7u , JTable_11_2531 },
  { 7591u , 7u , JTable_11_7591 },
  { 10627u , 7u , JTable_11_10627 },
  { 28843u , 7u , JTable_11_28843 },
  { 111827u , 7u , JTable_11_111827 },
  { 138139u , 7u , JTable_11_138139 },
  { 336491u , 7u , JTable_11_336491 },
  { 782783u , 7u , JTable_11_782783 },
  { 903211u , 7u , JTable_11_903211 },
  { 2348347u , 7u , JTable_11_2348347 },
  { 2624623u , 7u , JTable_11_2624623 },
  { 13123111u , 7u , JTable_11_13123111 },
  { 17160991u , 7u , JTable_11_17160991 }
 };

static const QType JTable_13_79[]=
 {
  6u, 4u, 2u, 8u, 4u, 3u, 6u, 6u, 0u, 2u, 0u, 6u, 4u,
  6u, 5u, 6u, 3u, 3u, 9u, 1u, 5u, 5u, 4u, 0u, 1u, 3u,
  5u, 0u, 1u, 0u, 6u, 1u, 1u, 4u, 4u, 0u, 6u, 4u, 6u,
  6u, 0u, 5u, 3u, 5u, 1u, 5u, 9u, 6u, 3u, 4u, 1u, 3u,
  6u, 6u, 3u, 1u, 5u, 0u, 3u, 5u, 3u, 9u, 5u, 4u, 1u,
  6u, 6u, 2u, 6u, 3u, 8u, 4u, 4u, 0u, 0u, 6u, 4u, 2u,
  6u, 6u, 3u, 1u, 5u, 0u, 3u, 5u, 3u, 9u, 5u, 4u, 1u,
  6u, 0u, 5u, 3u, 5u, 1u, 5u, 9u, 6u, 3u, 4u, 1u, 3u,
  5u, 0u, 1u, 0u, 6u, 1u, 1u, 4u, 4u, 0u, 6u, 4u, 6u,
  6u, 5u, 6u, 3u, 3u, 9u, 1u, 5u, 5u, 4u, 0u, 1u, 3u,
  6u, 4u, 2u, 8u, 4u, 3u, 6u, 6u, 0u, 2u, 0u, 6u, 4u
 };

static const QType JTable_13_131[]=
 {
  6u, 8u, 6u, 6u, 8u, 10u, 8u, 12u, 10u, 12u, 0u, 7u, 10u,
  5u, 10u, 0u, 9u, 7u, 6u, 5u, 8u, 9u, 9u, 5u, 3u, 1u,
  5u, 8u, 1u, 8u, 2u, 1u, 1u, 0u, 0u, 8u, 2u, 0u, 2u,
  5u, 5u, 8u, 7u, 10u, 3u, 9u, 6u, 0u, 1u, 9u, 5u, 9u,
  5u, 0u, 7u, 5u, 9u, 5u, 1u, 10u, 9u, 6u, 8u, 9u, 3u,
  6u, 7u, 12u, 12u, 10u, 6u, 8u, 10u, 0u, 10u, 8u, 8u, 6u,
  5u, 0u, 7u, 5u, 9u, 5u, 1u, 10u, 9u, 6u, 8u, 9u, 3u,
  5u, 5u, 8u, 7u, 10u, 3u, 9u, 6u, 0u, 1u, 9u, 5u, 9u,
  5u, 8u, 1u, 8u, 2u, 1u, 1u, 0u, 0u, 8u, 2u, 0u, 2u,
  5u, 10u, 0u, 9u, 7u, 6u, 5u, 8u, 9u, 9u, 5u, 3u, 1u,
  6u, 8u, 6u, 6u, 8u, 10u, 8u, 12u, 10u, 12u, 0u, 7u, 10u
 };

static const QType JTable_13_547[]=
 {
  24u, 16u, 18u, 16u, 10u, 0u, 14u, 16u, 18u, 6u, 14u, 21u, 8u,
  12u, 20u, 18u, 2u, 15u, 0u, 7u, 11u, 6u, 16u, 16u, 15u, 4u,
  19u, 3u, 12u, 3u, 0u, 12u, 12u, 0u, 0u, 3u, 0u, 0u, 0u,
  12u, 16u, 11u, 15u, 20u, 15u, 6u, 0u, 18u, 4u, 16u, 7u, 2u,
  12u, 18u, 15u, 7u, 6u, 16u, 4u, 20u, 2u, 0u, 11u, 16u, 15u,
  24u, 21u, 6u, 16u, 0u, 16u, 16u, 8u, 14u, 18u, 14u, 10u, 18u,
  12u, 18u, 15u, 7u, 6u, 16u, 4u, 20u, 2u, 0u, 11u, 16u, 15u,
  12u, 16u, 11u, 15u, 20u, 15u, 6u, 0u, 18u, 4u, 16u, 7u, 2u,
  19u, 3u, 12u, 3u, 0u, 12u, 12u, 0u, 0u, 3u, 0u, 0u, 0u,
  12u, 20u, 18u, 2u, 15u, 0u, 7u, 11u, 6u, 16u, 16u, 15u, 4u,
  24u, 16u, 18u, 16u, 10u, 0u, 14u, 16u, 18u, 6u, 14u, 21u, 8u
 };

static const QType JTable_13_859[]=
 {
  30u, 16u, 12u, 8u, 14u, 4u, 2u, 6u, 18u, 4u, 6u, 9u, 0u,
  6u, 5u, 19u, 11u, 5u, 3u, 7u, 0u, 15u, 12u, 9u, 31u, 6u,
  11u, 0u, 22u, 0u, 6u, 22u, 22u, 7u, 7u, 0u, 6u, 7u, 6u,
  6u, 9u, 0u, 5u, 5u, 31u, 15u, 3u, 19u, 6u, 12u, 7u, 11u,
  6u, 19u, 5u, 7u, 15u, 9u, 6u, 5u, 11u, 3u, 0u, 12u, 31u,
  30u, 9u, 4u, 6u, 4u, 8u, 16u, 0u, 6u, 18u, 2u, 14u, 12u,
  6u, 19u, 5u, 7u, 15u, 9u, 6u, 5u, 11u, 3u, 0u, 12u, 31u,
  6u, 9u, 0u, 5u, 5u, 31u, 15u, 3u, 19u, 6u, 12u, 7u, 11u,
  11u, 0u, 22u, 0u, 6u, 22u, 22u, 7u, 7u, 0u, 6u, 7u, 6u,
  6u, 5u, 19u, 11u, 5u, 3u, 7u, 0u, 15u, 12u, 9u, 31u, 6u,
  30u, 16u, 12u, 8u, 14u, 4u, 2u, 6u, 18u, 4u, 6u, 9u, 0u
 };

static const QType JTable_13_911[]=
 {
  20u, 15u, 18u, 8u, 0u, 16u, 24u, 16u, 22u, 18u, 30u, 2u, 18u,
  29u, 3u, 11u, 6u, 4u, 3u, 0u, 19u, 9u, 19u, 9u, 3u, 14u,
  27u, 0u, 4u, 0u, 15u, 4u, 4u, 2u, 2u, 0u, 15u, 2u, 15u,
  29u, 9u, 19u, 4u, 3u, 3u, 9u, 3u, 11u, 14u, 19u, 0u, 6u,
  29u, 11u, 4u, 0u, 9u, 9u, 14u, 3u, 6u, 3u, 19u, 19u, 3u,
  20u, 2u, 18u, 16u, 16u, 8u, 15u, 18u, 30u, 22u, 24u, 0u, 18u,
  29u, 11u, 4u, 0u, 9u, 9u, 14u, 3u, 6u, 3u, 19u, 19u, 3u,
  29u, 9u, 19u, 4u, 3u, 3u, 9u, 3u, 11u, 14u, 19u, 0u, 6u,
  27u, 0u, 4u, 0u, 15u, 4u, 4u, 2u, 2u, 0u, 15u, 2u, 15u,
  29u, 3u, 11u, 6u, 4u, 3u, 0u, 19u, 9u, 19u, 9u, 3u, 14u,
  20u, 15u, 18u, 8u, 0u, 16u, 24u, 16u, 22u, 18u, 30u, 2u, 18u
 };

static const QType JTable_13_2003[]=
 {
  26u, 8u, 18u, 4u, 43u, 26u, 20u, 34u, 32u, 0u, 14u, 12u, 22u,
  28u, 14u, 2u, 0u, 46u, 20u, 22u, 32u, 18u, 32u, 20u, 30u, 21u,
  0u, 33u, 11u, 33u, 27u, 11u, 11u, 37u, 37u, 33u, 27u, 37u, 27u,
  28u, 20u, 32u, 46u, 14u, 30u, 18u, 20u, 2u, 21u, 32u, 22u, 0u,
  28u, 2u, 46u, 22u, 18u, 20u, 21u, 14u, 0u, 20u, 32u, 32u, 30u,
  26u, 12u, 0u, 34u, 26u, 4u, 8u, 22u, 14u, 32u, 20u, 43u, 18u,
  28u, 2u, 46u, 22u, 18u, 20u, 21u, 14u, 0u, 20u, 32u, 32u, 30u,
  28u, 20u, 32u, 46u, 14u, 30u, 18u, 20u, 2u, 21u, 32u, 22u, 0u,
  0u, 33u, 11u, 33u, 27u, 11u, 11u, 37u, 37u, 33u, 27u, 37u, 27u,
  28u, 14u, 2u, 0u, 46u, 20u, 22u, 32u, 18u, 32u, 20u, 30u, 21u,
  26u, 8u, 18u, 4u, 43u, 26u, 20u, 34u, 32u, 0u, 14u, 12u, 22u
 };

static const QType JTable_13_2731[]=
 {
  24u, 10u, 34u, 46u, 52u, 24u, 36u, 46u, 0u, 32u, 21u, 34u, 30u,
  30u, 56u, 30u, 46u, 51u, 36u, 28u, 46u, 28u, 46u, 42u, 0u, 28u,
  0u, 35u, 13u, 35u, 17u, 13u, 13u, 43u, 43u, 35u, 17u, 43u, 17u,
  30u, 42u, 46u, 51u, 56u, 0u, 28u, 36u, 30u, 28u, 46u, 28u, 46u,
  30u, 30u, 51u, 28u, 28u, 42u, 28u, 56u, 46u, 36u, 46u, 46u, 0u,
  24u, 34u, 32u, 46u, 24u, 46u, 10u, 30u, 21u, 0u, 36u, 52u, 34u,
  30u, 30u, 51u, 28u, 28u, 42u, 28u, 56u, 46u, 36u, 46u, 46u, 0u,
  30u, 42u, 46u, 51u, 56u, 0u, 28u, 36u, 30u, 28u, 46u, 28u, 46u,
  0u, 35u, 13u, 35u, 17u, 13u, 13u, 43u, 43u, 35u, 17u, 43u, 17u,
  30u, 56u, 30u, 46u, 51u, 36u, 28u, 46u, 28u, 46u, 42u, 0u, 28u,
  24u, 10u, 34u, 46u, 52u, 24u, 36u, 46u, 0u, 32u, 21u, 34u, 30u
 };

static const QType JTable_13_6007[]=
 {
  44u, 22u, 40u, 12u, 66u, 14u, 24u, 62u, 44u, 2u, 11u, 0u, 22u,
  61u, 61u, 34u, 37u, 8u, 31u, 11u, 41u, 27u, 45u, 73u, 0u, 38u,
  25u, 18u, 45u, 18u, 0u, 45u, 45u, 54u, 54u, 18u, 0u, 54u, 0u,
  61u, 73u, 41u, 8u, 61u, 0u, 27u, 31u, 34u, 38u, 45u, 11u, 37u,
  61u, 34u, 8u, 11u, 27u, 73u, 38u, 61u, 37u, 31u, 41u, 45u, 0u,
  44u, 0u, 2u, 62u, 14u, 12u, 22u, 22u, 11u, 44u, 24u, 66u, 40u,
  61u, 34u, 8u, 11u, 27u, 73u, 38u, 61u, 37u, 31u, 41u, 45u, 0u,
  61u, 73u, 41u, 8u, 61u, 0u, 27u, 31u, 34u, 38u, 45u, 11u, 37u,
  25u, 18u, 45u, 18u, 0u, 45u, 45u, 54u, 54u, 18u, 0u, 54u, 0u,
  61u, 61u, 34u, 37u, 8u, 31u, 11u, 41u, 27u, 45u, 73u, 0u, 38u,
  44u, 22u, 40u, 12u, 66u, 14u, 24u, 62u, 44u, 2u, 11u, 0u, 22u
 };

static const QType JTable_13_443[]=
 {
  4u, 18u, 18u, 6u, 20u, 6u, 12u, 8u, 8u, 10u, 10u, 9u, 0u,
  13u, 13u, 15u, 6u, 19u, 3u, 9u, 18u, 8u, 3u, 0u, 11u, 11u,
  0u, 13u, 21u, 13u, 20u, 21u, 21u, 15u, 15u, 13u, 20u, 15u, 20u,
  13u, 0u, 18u, 19u, 13u, 11u, 8u, 3u, 15u, 11u, 3u, 9u, 6u,
  13u, 15u, 19u, 9u, 8u, 0u, 11u, 13u, 6u, 3u, 18u, 3u, 11u,
  4u, 9u, 10u, 8u, 6u, 6u, 18u, 0u, 10u, 8u, 12u, 20u, 18u,
  13u, 15u, 19u, 9u, 8u, 0u, 11u, 13u, 6u, 3u, 18u, 3u, 11u,
  13u, 0u, 18u, 19u, 13u, 11u, 8u, 3u, 15u, 11u, 3u, 9u, 6u,
  0u, 13u, 21u, 13u, 20u, 21u, 21u, 15u, 15u, 13u, 20u, 15u, 20u,
  13u, 13u, 15u, 6u, 19u, 3u, 9u, 18u, 8u, 3u, 0u, 11u, 11u,
  4u, 18u, 18u, 6u, 20u, 6u, 12u, 8u, 8u, 10u, 10u, 9u, 0u
 };

static const QType JTable_13_1327[]=
 {
  32u, 28u, 22u, 10u, 26u, 8u, 0u, 34u, 19u, 24u, 10u, 22u, 24u,
  6u, 20u, 0u, 18u, 14u, 28u, 28u, 18u, 18u, 0u, 28u, 23u, 6u,
  0u, 17u, 25u, 17u, 35u, 25u, 25u, 31u, 31u, 17u, 35u, 31u, 35u,
  6u, 28u, 18u, 14u, 20u, 23u, 18u, 28u, 0u, 6u, 0u, 28u, 18u,
  6u, 0u, 14u, 28u, 18u, 28u, 6u, 20u, 18u, 28u, 18u, 0u, 23u,
  32u, 22u, 24u, 34u, 8u, 10u, 28u, 24u, 10u, 19u, 0u, 26u, 22u,
  6u, 0u, 14u, 28u, 18u, 28u, 6u, 20u, 18u, 28u, 18u, 0u, 23u,
  6u, 28u, 18u, 14u, 20u, 23u, 18u, 28u, 0u, 6u, 0u, 28u, 18u,
  0u, 17u, 25u, 17u, 35u, 25u, 25u, 31u, 31u, 17u, 35u, 31u, 35u,
  6u, 20u, 0u, 18u, 14u, 28u, 28u, 18u, 18u, 0u, 28u, 23u, 6u,
  32u, 28u, 22u, 10u, 26u, 8u, 0u, 34u, 19u, 24u, 10u, 22u, 24u
 };

static const QType JTable_13_9283[]=
 {
  62u, 78u, 110u, 64u, 46u, 56u, 78u, 0u, 72u, 60u, 46u, 57u, 24u,
  56u, 58u, 74u, 92u, 78u, 68u, 50u, 35u, 68u, 106u, 0u, 54u, 40u,
  17u, 58u, 54u, 58u, 64u, 54u, 54u, 0u, 0u, 58u, 64u, 0u, 64u,
  56u, 0u, 35u, 78u, 58u, 54u, 68u, 68u, 74u, 40u, 106u, 50u, 92u,
  56u, 74u, 78u, 50u, 68u, 0u, 40u, 58u, 92u, 68u, 35u, 106u, 54u,
  62u, 57u, 60u, 0u, 56u, 64u, 78u, 24u, 46u, 72u, 78u, 46u, 110u,
  56u, 74u, 78u, 50u, 68u, 0u, 40u, 58u, 92u, 68u, 35u, 106u, 54u,
  56u, 0u, 35u, 78u, 58u, 54u, 68u, 68u, 74u, 40u, 106u, 50u, 92u,
  17u, 58u, 54u, 58u, 64u, 54u, 54u, 0u, 0u, 58u, 64u, 0u, 64u,
  56u, 58u, 74u, 92u, 78u, 68u, 50u, 35u, 68u, 106u, 0u, 54u, 40u,
  62u, 78u, 110u, 64u, 46u, 56u, 78u, 0u, 72u, 60u, 46u, 57u, 24u
 };

static const QType JTable_13_46411[]=
 {
  174u, 148u, 38u, 40u, 30u, 0u, 165u, 46u, 124u, 90u, 152u, 74u, 36u,
  108u, 127u, 149u, 194u, 127u, 118u, 133u, 227u, 201u, 143u, 121u, 223u, 0u,
  37u, 0u, 165u, 0u, 84u, 165u, 165u, 72u, 72u, 0u, 84u, 72u, 84u,
  108u, 121u, 227u, 127u, 127u, 223u, 201u, 118u, 149u, 0u, 143u, 133u, 194u,
  108u, 149u, 127u, 133u, 201u, 121u, 0u, 127u, 194u, 118u, 227u, 143u, 223u,
  174u, 74u, 90u, 46u, 0u, 40u, 148u, 36u, 152u, 124u, 165u, 30u, 38u,
  108u, 149u, 127u, 133u, 201u, 121u, 0u, 127u, 194u, 118u, 227u, 143u, 223u,
  108u, 121u, 227u, 127u, 127u, 223u, 201u, 118u, 149u, 0u, 143u, 133u, 194u,
  37u, 0u, 165u, 0u, 84u, 165u, 165u, 72u, 72u, 0u, 84u, 72u, 84u,
  108u, 127u, 149u, 194u, 127u, 118u, 133u, 227u, 201u, 143u, 121u, 223u, 0u,
  174u, 148u, 38u, 40u, 30u, 0u, 165u, 46u, 124u, 90u, 152u, 74u, 36u
 };

static const QType JTable_13_72931[]=
 {
  228u, 156u, 176u, 67u, 146u, 206u, 158u, 298u, 140u, 176u, 190u, 86u, 0u,
  58u, 154u, 240u, 98u, 240u, 213u, 128u, 90u, 234u, 195u, 167u, 0u, 145u,
  175u, 8u, 168u, 8u, 47u, 168u, 168u, 0u, 0u, 8u, 47u, 0u, 47u,
  58u, 167u, 90u, 240u, 154u, 0u, 234u, 213u, 240u, 145u, 195u, 128u, 98u,
  58u, 240u, 240u, 128u, 234u, 167u, 145u, 154u, 98u, 213u, 90u, 195u, 0u,
  228u, 86u, 176u, 298u, 206u, 67u, 156u, 0u, 190u, 140u, 158u, 146u, 176u,
  58u, 240u, 240u, 128u, 234u, 167u, 145u, 154u, 98u, 213u, 90u, 195u, 0u,
  58u, 167u, 90u, 240u, 154u, 0u, 234u, 213u, 240u, 145u, 195u, 128u, 98u,
  175u, 8u, 168u, 8u, 47u, 168u, 168u, 0u, 0u, 8u, 47u, 0u, 47u,
  58u, 154u, 240u, 98u, 240u, 213u, 128u, 90u, 234u, 195u, 167u, 0u, 145u,
  228u, 156u, 176u, 67u, 146u, 206u, 158u, 298u, 140u, 176u, 190u, 86u, 0u
 };

static const QType JTable_13_102103[]=
 {
  182u, 260u, 218u, 108u, 284u, 94u, 66u, 0u, 191u, 254u, 88u, 232u, 102u,
  122u, 162u, 213u, 196u, 188u, 132u, 182u, 8u, 203u, 0u, 157u, 343u, 212u,
  103u, 171u, 234u, 171u, 0u, 234u, 234u, 180u, 180u, 171u, 0u, 180u, 0u,
  122u, 157u, 8u, 188u, 162u, 343u, 203u, 132u, 213u, 212u, 0u, 182u, 196u,
  122u, 213u, 188u, 182u, 203u, 157u, 212u, 162u, 196u, 132u, 8u, 0u, 343u,
  182u, 232u, 254u, 0u, 94u, 108u, 260u, 102u, 88u, 191u, 66u, 284u, 218u,
  122u, 213u, 188u, 182u, 203u, 157u, 212u, 162u, 196u, 132u, 8u, 0u, 343u,
  122u, 157u, 8u, 188u, 162u, 343u, 203u, 132u, 213u, 212u, 0u, 182u, 196u,
  103u, 171u, 234u, 171u, 0u, 234u, 234u, 180u, 180u, 171u, 0u, 180u, 0u,
  122u, 162u, 213u, 196u, 188u, 132u, 182u, 8u, 203u, 0u, 157u, 343u, 212u,
  182u, 260u, 218u, 108u, 284u, 94u, 66u, 0u, 191u, 254u, 88u, 232u, 102u
 };

static const QType JTable_13_1483[]=
 {
  30u, 4u, 0u, 12u, 24u, 14u, 30u, 10u, 14u, 36u, 14u, 25u, 20u,
  23u, 40u, 20u, 0u, 26u, 28u, 30u, 35u, 30u, 21u, 42u, 22u, 33u,
  0u, 1u, 1u, 1u, 25u, 1u, 1u, 16u, 16u, 1u, 25u, 16u, 25u,
  23u, 42u, 35u, 26u, 40u, 22u, 30u, 28u, 20u, 33u, 21u, 30u, 0u,
  23u, 20u, 26u, 30u, 30u, 42u, 33u, 40u, 0u, 28u, 35u, 21u, 22u,
  30u, 25u, 36u, 10u, 14u, 12u, 4u, 20u, 14u, 14u, 30u, 24u, 0u,
  23u, 20u, 26u, 30u, 30u, 42u, 33u, 40u, 0u, 28u, 35u, 21u, 22u,
  23u, 42u, 35u, 26u, 40u, 22u, 30u, 28u, 20u, 33u, 21u, 30u, 0u,
  0u, 1u, 1u, 1u, 25u, 1u, 1u, 16u, 16u, 1u, 25u, 16u, 25u,
  23u, 40u, 20u, 0u, 26u, 28u, 30u, 35u, 30u, 21u, 42u, 22u, 33u,
  30u, 4u, 0u, 12u, 24u, 14u, 30u, 10u, 14u, 36u, 14u, 25u, 20u
 };

static const QType JTable_13_7411[]=
 {
  14u, 74u, 42u, 34u, 68u, 26u, 28u, 32u, 68u, 28u, 0u, 3u, 50u,
  0u, 9u, 31u, 68u, 32u, 13u, 50u, 59u, 10u, 72u, 26u, 44u, 14u,
  80u, 43u, 0u, 43u, 7u, 0u, 0u, 27u, 27u, 43u, 7u, 27u, 7u,
  0u, 26u, 59u, 32u, 9u, 44u, 10u, 13u, 31u, 14u, 72u, 50u, 68u,
  0u, 31u, 32u, 50u, 10u, 26u, 14u, 9u, 68u, 13u, 59u, 72u, 44u,
  14u, 3u, 28u, 32u, 26u, 34u, 74u, 50u, 0u, 68u, 28u, 68u, 42u,
  0u, 31u, 32u, 50u, 10u, 26u, 14u, 9u, 68u, 13u, 59u, 72u, 44u,
  0u, 26u, 59u, 32u, 9u, 44u, 10u, 13u, 31u, 14u, 72u, 50u, 68u,
  80u, 43u, 0u, 43u, 7u, 0u, 0u, 27u, 27u, 43u, 7u, 27u, 7u,
  0u, 9u, 31u, 68u, 32u, 13u, 50u, 59u, 10u, 72u, 26u, 44u, 14u,
  14u, 74u, 42u, 34u, 68u, 26u, 28u, 32u, 68u, 28u, 0u, 3u, 50u
 };

static const QType JTable_13_17291[]=
 {
  52u, 0u, 30u, 88u, 122u, 66u, 48u, 70u, 86u, 9u, 104u, 24u, 54u,
  57u, 103u, 130u, 0u, 82u, 61u, 74u, 58u, 116u, 132u, 112u, 67u, 86u,
  0u, 112u, 93u, 112u, 65u, 93u, 93u, 33u, 33u, 112u, 65u, 33u, 65u,
  57u, 112u, 58u, 82u, 103u, 67u, 116u, 61u, 130u, 86u, 132u, 74u, 0u,
  57u, 130u, 82u, 74u, 116u, 112u, 86u, 103u, 0u, 61u, 58u, 132u, 67u,
  52u, 24u, 9u, 70u, 66u, 88u, 0u, 54u, 104u, 86u, 48u, 122u, 30u,
  57u, 130u, 82u, 74u, 116u, 112u, 86u, 103u, 0u, 61u, 58u, 132u, 67u,
  57u, 112u, 58u, 82u, 103u, 67u, 116u, 61u, 130u, 86u, 132u, 74u, 0u,
  0u, 112u, 93u, 112u, 65u, 93u, 93u, 33u, 33u, 112u, 65u, 33u, 65u,
  57u, 103u, 130u, 0u, 82u, 61u, 74u, 58u, 116u, 132u, 112u, 67u, 86u,
  52u, 0u, 30u, 88u, 122u, 66u, 48u, 70u, 86u, 9u, 104u, 24u, 54u
 };

static const QType JTable_13_38039[]=
 {
  66u, 0u, 18u, 78u, 58u, 191u, 60u, 72u, 80u, 130u, 124u, 22u, 140u,
  171u, 64u, 56u, 41u, 119u, 107u, 0u, 7u, 55u, 55u, 117u, 149u, 20u,
  40u, 0u, 139u, 0u, 71u, 139u, 139u, 19u, 19u, 0u, 71u, 19u, 71u,
  171u, 117u, 7u, 119u, 64u, 149u, 55u, 107u, 56u, 20u, 55u, 0u, 41u,
  171u, 56u, 119u, 0u, 55u, 117u, 20u, 64u, 41u, 107u, 7u, 55u, 149u,
  66u, 22u, 130u, 72u, 191u, 78u, 0u, 140u, 124u, 80u, 60u, 58u, 18u,
  171u, 56u, 119u, 0u, 55u, 117u, 20u, 64u, 41u, 107u, 7u, 55u, 149u,
  171u, 117u, 7u, 119u, 64u, 149u, 55u, 107u, 56u, 20u, 55u, 0u, 41u,
  40u, 0u, 139u, 0u, 71u, 139u, 139u, 19u, 19u, 0u, 71u, 19u, 71u,
  171u, 64u, 56u, 41u, 119u, 107u, 0u, 7u, 55u, 55u, 117u, 149u, 20u,
  66u, 0u, 18u, 78u, 58u, 191u, 60u, 72u, 80u, 130u, 124u, 22u, 140u
 };

static const QType JTable_13_51871[]=
 {
  46u, 180u, 7u, 34u, 68u, 62u, 66u, 176u, 64u, 186u, 102u, 48u, 0u,
  180u, 88u, 183u, 87u, 0u, 195u, 160u, 209u, 75u, 167u, 167u, 181u, 205u,
  73u, 156u, 33u, 156u, 120u, 33u, 33u, 0u, 0u, 156u, 120u, 0u, 120u,
  180u, 167u, 209u, 0u, 88u, 181u, 75u, 195u, 183u, 205u, 167u, 160u, 87u,
  180u, 183u, 0u, 160u, 75u, 167u, 205u, 88u, 87u, 195u, 209u, 167u, 181u,
  46u, 48u, 186u, 176u, 62u, 34u, 180u, 0u, 102u, 64u, 66u, 68u, 7u,
  180u, 183u, 0u, 160u, 75u, 167u, 205u, 88u, 87u, 195u, 209u, 167u, 181u,
  180u, 167u, 209u, 0u, 88u, 181u, 75u, 195u, 183u, 205u, 167u, 160u, 87u,
  73u, 156u, 33u, 156u, 120u, 33u, 33u, 0u, 0u, 156u, 120u, 0u, 120u,
  180u, 88u, 183u, 87u, 0u, 195u, 160u, 209u, 75u, 167u, 167u, 181u, 205u,
  46u, 180u, 7u, 34u, 68u, 62u, 66u, 176u, 64u, 186u, 102u, 48u, 0u
 };

static const QType JTable_13_58787[]=
 {
  202u, 124u, 232u, 176u, 230u, 0u, 110u, 198u, 106u, 136u, 96u, 67u, 142u,
  64u, 7u, 127u, 82u, 148u, 53u, 34u, 133u, 242u, 24u, 98u, 66u, 0u,
  253u, 0u, 13u, 0u, 68u, 13u, 13u, 64u, 64u, 0u, 68u, 64u, 68u,
  64u, 98u, 133u, 148u, 7u, 66u, 242u, 53u, 127u, 0u, 24u, 34u, 82u,
  64u, 127u, 148u, 34u, 242u, 98u, 0u, 7u, 82u, 53u, 133u, 24u, 66u,
  202u, 67u, 136u, 198u, 0u, 176u, 124u, 142u, 96u, 106u, 110u, 230u, 232u,
  64u, 127u, 148u, 34u, 242u, 98u, 0u, 7u, 82u, 53u, 133u, 24u, 66u,
  64u, 98u, 133u, 148u, 7u, 66u, 242u, 53u, 127u, 0u, 24u, 34u, 82u,
  253u, 0u, 13u, 0u, 68u, 13u, 13u, 64u, 64u, 0u, 68u, 64u, 68u,
  64u, 7u, 127u, 82u, 148u, 53u, 34u, 133u, 242u, 24u, 98u, 66u, 0u,
  202u, 124u, 232u, 176u, 230u, 0u, 110u, 198u, 106u, 136u, 96u, 67u, 142u
 };

static const QType JTable_13_461891[]=
 {
  826u, 468u, 326u, 336u, 290u, 344u, 0u, 450u, 322u, 285u, 268u, 252u, 174u,
  310u, 83u, 392u, 474u, 18u, 308u, 0u, 296u, 565u, 515u, 218u, 520u, 317u,
  237u, 0u, 509u, 0u, 120u, 509u, 509u, 232u, 232u, 0u, 120u, 232u, 120u,
  310u, 218u, 296u, 18u, 83u, 520u, 565u, 308u, 392u, 317u, 515u, 0u, 474u,
  310u, 392u, 18u, 0u, 565u, 218u, 317u, 83u, 474u, 308u, 296u, 515u, 520u,
  826u, 252u, 285u, 450u, 344u, 336u, 468u, 174u, 268u, 322u, 0u, 290u, 326u,
  310u, 392u, 18u, 0u, 565u, 218u, 317u, 83u, 474u, 308u, 296u, 515u, 520u,
  310u, 218u, 296u, 18u, 83u, 520u, 565u, 308u, 392u, 317u, 515u, 0u, 474u,
  237u, 0u, 509u, 0u, 120u, 509u, 509u, 232u, 232u, 0u, 120u, 232u, 120u,
  310u, 83u, 392u, 474u, 18u, 308u, 0u, 296u, 565u, 515u, 218u, 520u, 317u,
  826u, 468u, 326u, 336u, 290u, 344u, 0u, 450u, 322u, 285u, 268u, 252u, 174u
 };

static const QType JTable_13_1939939[]=
 {
  1138u, 1106u, 938u, 1226u, 1198u, 968u, 1592u, 1324u, 1448u, 0u, 942u, 1125u, 800u,
  1266u, 860u, 606u, 700u, 1060u, 1102u, 1194u, 617u, 324u, 312u, 674u, 1086u, 0u,
  541u, 956u, 42u, 956u, 338u, 42u, 42u, 0u, 0u, 956u, 338u, 0u, 338u,
  1266u, 674u, 617u, 1060u, 860u, 1086u, 324u, 1102u, 606u, 0u, 312u, 1194u, 700u,
  1266u, 606u, 1060u, 1194u, 324u, 674u, 0u, 860u, 700u, 1102u, 617u, 312u, 1086u,
  1138u, 1125u, 0u, 1324u, 968u, 1226u, 1106u, 800u, 942u, 1448u, 1592u, 1198u, 938u,
  1266u, 606u, 1060u, 1194u, 324u, 674u, 0u, 860u, 700u, 1102u, 617u, 312u, 1086u,
  1266u, 674u, 617u, 1060u, 860u, 1086u, 324u, 1102u, 606u, 0u, 312u, 1194u, 700u,
  541u, 956u, 42u, 956u, 338u, 42u, 42u, 0u, 0u, 956u, 338u, 0u, 338u,
  1266u, 860u, 606u, 700u, 1060u, 1102u, 1194u, 617u, 324u, 312u, 674u, 1086u, 0u,
  1138u, 1106u, 938u, 1226u, 1198u, 968u, 1592u, 1324u, 1448u, 0u, 942u, 1125u, 800u
 };

static const QType JTable_13_3233231[]=
 {
  831u, 775u, 723u, 1019u, 1579u, 651u, 709u, 1049u, 1853u, 1305u, 321u, 1261u, 0u,
  552u, 551u, 43u, 1407u, 545u, 387u, 0u, 1133u, 1197u, 945u, 898u, 1522u, 257u,
  1192u, 1157u, 529u, 1157u, 0u, 529u, 529u, 109u, 109u, 1157u, 0u, 109u, 0u,
  552u, 898u, 1133u, 545u, 551u, 1522u, 1197u, 387u, 43u, 257u, 945u, 0u, 1407u,
  552u, 43u, 545u, 0u, 1197u, 898u, 257u, 551u, 1407u, 387u, 1133u, 945u, 1522u,
  831u, 1261u, 1305u, 1049u, 651u, 1019u, 775u, 0u, 321u, 1853u, 709u, 1579u, 723u,
  552u, 43u, 545u, 0u, 1197u, 898u, 257u, 551u, 1407u, 387u, 1133u, 945u, 1522u,
  552u, 898u, 1133u, 545u, 551u, 1522u, 1197u, 387u, 43u, 257u, 945u, 0u, 1407u,
  1192u, 1157u, 529u, 1157u, 0u, 529u, 529u, 109u, 109u, 1157u, 0u, 109u, 0u,
  552u, 551u, 43u, 1407u, 545u, 387u, 0u, 1133u, 1197u, 945u, 898u, 1522u, 257u,
  831u, 775u, 723u, 1019u, 1579u, 651u, 709u, 1049u, 1853u, 1305u, 321u, 1261u, 0u
 };

static const QType JTable_13_599[]=
 {
  10u, 4u, 14u, 8u, 6u, 0u, 6u, 16u, 12u, 25u, 2u, 10u, 16u,
  22u, 16u, 5u, 11u, 11u, 14u, 1u, 17u, 3u, 5u, 9u, 0u, 15u,
  25u, 1u, 0u, 1u, 4u, 0u, 0u, 8u, 8u, 1u, 4u, 8u, 4u,
  22u, 9u, 17u, 11u, 16u, 0u, 3u, 14u, 5u, 15u, 5u, 1u, 11u,
  22u, 5u, 11u, 1u, 3u, 9u, 15u, 16u, 11u, 14u, 17u, 5u, 0u,
  10u, 10u, 25u, 16u, 0u, 8u, 4u, 16u, 2u, 12u, 6u, 6u, 14u,
  22u, 5u, 11u, 1u, 3u, 9u, 15u, 16u, 11u, 14u, 17u, 5u, 0u,
  22u, 9u, 17u, 11u, 16u, 0u, 3u, 14u, 5u, 15u, 5u, 1u, 11u,
  25u, 1u, 0u, 1u, 4u, 0u, 0u, 8u, 8u, 1u, 4u, 8u, 4u,
  22u, 16u, 5u, 11u, 11u, 14u, 1u, 17u, 3u, 5u, 9u, 0u, 15u,
  10u, 4u, 14u, 8u, 6u, 0u, 6u, 16u, 12u, 25u, 2u, 10u, 16u
 };

static const QType JTable_13_8971[]=
 {
  0u, 94u, 74u, 32u, 54u, 24u, 70u, 40u, 56u, 18u, 24u, 33u, 26u,
  17u, 41u, 31u, 49u, 0u, 47u, 46u, 2u, 47u, 5u, 49u, 84u, 75u,
  32u, 0u, 57u, 0u, 45u, 57u, 57u, 69u, 69u, 0u, 45u, 69u, 45u,
  17u, 49u, 2u, 0u, 41u, 84u, 47u, 47u, 31u, 75u, 5u, 46u, 49u,
  17u, 31u, 0u, 46u, 47u, 49u, 75u, 41u, 49u, 47u, 2u, 5u, 84u,
  0u, 33u, 18u, 40u, 24u, 32u, 94u, 26u, 24u, 56u, 70u, 54u, 74u,
  17u, 31u, 0u, 46u, 47u, 49u, 75u, 41u, 49u, 47u, 2u, 5u, 84u,
  17u, 49u, 2u, 0u, 41u, 84u, 47u, 47u, 31u, 75u, 5u, 46u, 49u,
  32u, 0u, 57u, 0u, 45u, 57u, 57u, 69u, 69u, 0u, 45u, 69u, 45u,
  17u, 41u, 31u, 49u, 0u, 47u, 46u, 2u, 47u, 5u, 49u, 84u, 75u,
  0u, 94u, 74u, 32u, 54u, 24u, 70u, 40u, 56u, 18u, 24u, 33u, 26u
 };

static const QType JTable_13_62791[]=
 {
  232u, 193u, 206u, 176u, 84u, 0u, 202u, 98u, 140u, 128u, 202u, 182u, 54u,
  149u, 114u, 117u, 243u, 80u, 232u, 160u, 39u, 0u, 146u, 128u, 136u, 54u,
  119u, 75u, 30u, 75u, 180u, 30u, 30u, 0u, 0u, 75u, 180u, 0u, 180u,
  149u, 128u, 39u, 80u, 114u, 136u, 0u, 232u, 117u, 54u, 146u, 160u, 243u,
  149u, 117u, 80u, 160u, 0u, 128u, 54u, 114u, 243u, 232u, 39u, 146u, 136u,
  232u, 182u, 128u, 98u, 0u, 176u, 193u, 54u, 202u, 140u, 202u, 84u, 206u,
  149u, 117u, 80u, 160u, 0u, 128u, 54u, 114u, 243u, 232u, 39u, 146u, 136u,
  149u, 128u, 39u, 80u, 114u, 136u, 0u, 232u, 117u, 54u, 146u, 160u, 243u,
  119u, 75u, 30u, 75u, 180u, 30u, 30u, 0u, 0u, 75u, 180u, 0u, 180u,
  149u, 114u, 117u, 243u, 80u, 232u, 160u, 39u, 0u, 146u, 128u, 136u, 54u,
  232u, 193u, 206u, 176u, 84u, 0u, 202u, 98u, 140u, 128u, 202u, 182u, 54u
 };

static const QType JTable_13_111827[]=
 {
  0u, 266u, 216u, 178u, 196u, 162u, 144u, 370u, 132u, 230u, 160u, 191u, 42u,
  107u, 102u, 136u, 138u, 0u, 70u, 176u, 337u, 102u, 257u, 84u, 126u, 275u,
  112u, 223u, 83u, 223u, 211u, 83u, 83u, 0u, 0u, 223u, 211u, 0u, 211u,
  107u, 84u, 337u, 0u, 102u, 126u, 102u, 70u, 136u, 275u, 257u, 176u, 138u,
  107u, 136u, 0u, 176u, 102u, 84u, 275u, 102u, 138u, 70u, 337u, 257u, 126u,
  0u, 191u, 230u, 370u, 162u, 178u, 266u, 42u, 160u, 132u, 144u, 196u, 216u,
  107u, 136u, 0u, 176u, 102u, 84u, 275u, 102u, 138u, 70u, 337u, 257u, 126u,
  107u, 84u, 337u, 0u, 102u, 126u, 102u, 70u, 136u, 275u, 257u, 176u, 138u,
  112u, 223u, 83u, 223u, 211u, 83u, 83u, 0u, 0u, 223u, 211u, 0u, 211u,
  107u, 102u, 136u, 138u, 0u, 70u, 176u, 337u, 102u, 257u, 84u, 126u, 275u,
  0u, 266u, 216u, 178u, 196u, 162u, 144u, 370u, 132u, 230u, 160u, 191u, 42u
 };

static const QType JTable_13_138139[]=
 {
  88u, 314u, 166u, 204u, 43u, 326u, 264u, 172u, 126u, 60u, 0u, 242u, 126u,
  240u, 0u, 210u, 142u, 132u, 254u, 133u, 165u, 124u, 386u, 325u, 138u, 77u,
  145u, 0u, 189u, 0u, 66u, 189u, 189u, 264u, 264u, 0u, 66u, 264u, 66u,
  240u, 325u, 165u, 132u, 0u, 138u, 124u, 254u, 210u, 77u, 386u, 133u, 142u,
  240u, 210u, 132u, 133u, 124u, 325u, 77u, 0u, 142u, 254u, 165u, 386u, 138u,
  88u, 242u, 60u, 172u, 326u, 204u, 314u, 126u, 0u, 126u, 264u, 43u, 166u,
  240u, 210u, 132u, 133u, 124u, 325u, 77u, 0u, 142u, 254u, 165u, 386u, 138u,
  240u, 325u, 165u, 132u, 0u, 138u, 124u, 254u, 210u, 77u, 386u, 133u, 142u,
  145u, 0u, 189u, 0u, 66u, 189u, 189u, 264u, 264u, 0u, 66u, 264u, 66u,
  240u, 0u, 210u, 142u, 132u, 254u, 133u, 165u, 124u, 386u, 325u, 138u, 77u,
  88u, 314u, 166u, 204u, 43u, 326u, 264u, 172u, 126u, 60u, 0u, 242u, 126u
 };

static const QType JTable_13_355811[]=
 {
  166u, 126u, 14u, 192u, 308u, 526u, 366u, 0u, 536u, 172u, 214u, 225u, 300u,
  341u, 114u, 0u, 5u, 467u, 220u, 303u, 414u, 341u, 139u, 387u, 25u, 363u,
  0u, 447u, 160u, 447u, 363u, 160u, 160u, 503u, 503u, 447u, 363u, 503u, 363u,
  341u, 387u, 414u, 467u, 114u, 25u, 341u, 220u, 0u, 363u, 139u, 303u, 5u,
  341u, 0u, 467u, 303u, 341u, 387u, 363u, 114u, 5u, 220u, 414u, 139u, 25u,
  166u, 225u, 172u, 0u, 526u, 192u, 126u, 300u, 214u, 536u, 366u, 308u, 14u,
  341u, 0u, 467u, 303u, 341u, 387u, 363u, 114u, 5u, 220u, 414u, 139u, 25u,
  341u, 387u, 414u, 467u, 114u, 25u, 341u, 220u, 0u, 363u, 139u, 303u, 5u,
  0u, 447u, 160u, 447u, 363u, 160u, 160u, 503u, 503u, 447u, 363u, 503u, 363u,
  341u, 114u, 0u, 5u, 467u, 220u, 303u, 414u, 341u, 139u, 387u, 25u, 363u,
  166u, 126u, 14u, 192u, 308u, 526u, 366u, 0u, 536u, 172u, 214u, 225u, 300u
 };

static const QType JTable_13_782783[]=
 {
  548u, 634u, 366u, 0u, 670u, 454u, 670u, 695u, 220u, 640u, 652u, 978u, 440u,
  600u, 84u, 452u, 264u, 0u, 807u, 808u, 523u, 339u, 524u, 404u, 568u, 255u,
  805u, 401u, 10u, 401u, 0u, 10u, 10u, 148u, 148u, 401u, 0u, 148u, 0u,
  600u, 404u, 523u, 0u, 84u, 568u, 339u, 807u, 452u, 255u, 524u, 808u, 264u,
  600u, 452u, 0u, 808u, 339u, 404u, 255u, 84u, 264u, 807u, 523u, 524u, 568u,
  548u, 978u, 640u, 695u, 454u, 0u, 634u, 440u, 652u, 220u, 670u, 670u, 366u,
  600u, 452u, 0u, 808u, 339u, 404u, 255u, 84u, 264u, 807u, 523u, 524u, 568u,
  600u, 404u, 523u, 0u, 84u, 568u, 339u, 807u, 452u, 255u, 524u, 808u, 264u,
  805u, 401u, 10u, 401u, 0u, 10u, 10u, 148u, 148u, 401u, 0u, 148u, 0u,
  600u, 84u, 452u, 264u, 0u, 807u, 808u, 523u, 339u, 524u, 404u, 568u, 255u,
  548u, 634u, 366u, 0u, 670u, 454u, 670u, 695u, 220u, 640u, 652u, 978u, 440u
 };

static const QType JTable_13_1193011[]=
 {
  389u, 733u, 359u, 87u, 603u, 805u, 73u, 897u, 407u, 503u, 51u, 0u, 201u,
  1089u, 209u, 555u, 703u, 976u, 559u, 0u, 624u, 205u, 401u, 659u, 712u, 613u,
  68u, 0u, 801u, 0u, 495u, 801u, 801u, 423u, 423u, 0u, 495u, 423u, 495u,
  1089u, 659u, 624u, 976u, 209u, 712u, 205u, 559u, 555u, 613u, 401u, 0u, 703u,
  1089u, 555u, 976u, 0u, 205u, 659u, 613u, 209u, 703u, 559u, 624u, 401u, 712u,
  389u, 0u, 503u, 897u, 805u, 87u, 733u, 201u, 51u, 407u, 73u, 603u, 359u,
  1089u, 555u, 976u, 0u, 205u, 659u, 613u, 209u, 703u, 559u, 624u, 401u, 712u,
  1089u, 659u, 624u, 976u, 209u, 712u, 205u, 559u, 555u, 613u, 401u, 0u, 703u,
  68u, 0u, 801u, 0u, 495u, 801u, 801u, 423u, 423u, 0u, 495u, 423u, 495u,
  1089u, 209u, 555u, 703u, 976u, 559u, 0u, 624u, 205u, 401u, 659u, 712u, 613u,
  389u, 733u, 359u, 87u, 603u, 805u, 73u, 897u, 407u, 503u, 51u, 0u, 201u
 };

static const QType JTable_13_2348347[]=
 {
  502u, 780u, 810u, 96u, 472u, 1057u, 734u, 366u, 1488u, 314u, 648u, 0u, 38u,
  1002u, 1046u, 675u, 1353u, 242u, 931u, 1534u, 630u, 426u, 0u, 868u, 533u, 834u,
  0u, 389u, 1309u, 389u, 1076u, 1309u, 1309u, 727u, 727u, 389u, 1076u, 727u, 1076u,
  1002u, 868u, 630u, 242u, 1046u, 533u, 426u, 931u, 675u, 834u, 0u, 1534u, 1353u,
  1002u, 675u, 242u, 1534u, 426u, 868u, 834u, 1046u, 1353u, 931u, 630u, 0u, 533u,
  502u, 0u, 314u, 366u, 1057u, 96u, 780u, 38u, 648u, 1488u, 734u, 472u, 810u,
  1002u, 675u, 242u, 1534u, 426u, 868u, 834u, 1046u, 1353u, 931u, 630u, 0u, 533u,
  1002u, 868u, 630u, 242u, 1046u, 533u, 426u, 931u, 675u, 834u, 0u, 1534u, 1353u,
  0u, 389u, 1309u, 389u, 1076u, 1309u, 1309u, 727u, 727u, 389u, 1076u, 727u, 1076u,
  1002u, 1046u, 675u, 1353u, 242u, 931u, 1534u, 630u, 426u, 0u, 868u, 533u, 834u,
  502u, 780u, 810u, 96u, 472u, 1057u, 734u, 366u, 1488u, 314u, 648u, 0u, 38u
 };

static const QType JTable_13_2624623[]=
 {
  670u, 956u, 812u, 359u, 654u, 810u, 1452u, 1278u, 1084u, 534u, 244u, 1442u, 0u,
  1127u, 0u, 860u, 1307u, 743u, 563u, 811u, 253u, 1321u, 786u, 1439u, 1042u, 1473u,
  605u, 0u, 534u, 0u, 1074u, 534u, 534u, 1089u, 1089u, 0u, 1074u, 1089u, 1074u,
  1127u, 1439u, 253u, 743u, 0u, 1042u, 1321u, 563u, 860u, 1473u, 786u, 811u, 1307u,
  1127u, 860u, 743u, 811u, 1321u, 1439u, 1473u, 0u, 1307u, 563u, 253u, 786u, 1042u,
  670u, 1442u, 534u, 1278u, 810u, 359u, 956u, 0u, 244u, 1084u, 1452u, 654u, 812u,
  1127u, 860u, 743u, 811u, 1321u, 1439u, 1473u, 0u, 1307u, 563u, 253u, 786u, 1042u,
  1127u, 1439u, 253u, 743u, 0u, 1042u, 1321u, 563u, 860u, 1473u, 786u, 811u, 1307u,
  605u, 0u, 534u, 0u, 1074u, 534u, 534u, 1089u, 1089u, 0u, 1074u, 1089u, 1074u,
  1127u, 0u, 860u, 1307u, 743u, 563u, 811u, 253u, 1321u, 786u, 1439u, 1042u, 1473u,
  670u, 956u, 812u, 359u, 654u, 810u, 1452u, 1278u, 1084u, 534u, 244u, 1442u, 0u
 };

static const QType JTable_13_2897311[]=
 {
  374u, 1559u, 0u, 160u, 1112u, 1246u, 934u, 1278u, 828u, 764u, 588u, 254u, 782u,
  1626u, 1572u, 726u, 1009u, 816u, 1018u, 1540u, 572u, 752u, 0u, 1298u, 622u, 642u,
  0u, 1235u, 953u, 1235u, 173u, 953u, 953u, 347u, 347u, 1235u, 173u, 347u, 173u,
  1626u, 1298u, 572u, 816u, 1572u, 622u, 752u, 1018u, 726u, 642u, 0u, 1540u, 1009u,
  1626u, 726u, 816u, 1540u, 752u, 1298u, 642u, 1572u, 1009u, 1018u, 572u, 0u, 622u,
  374u, 254u, 764u, 1278u, 1246u, 160u, 1559u, 782u, 588u, 828u, 934u, 1112u, 0u,
  1626u, 726u, 816u, 1540u, 752u, 1298u, 642u, 1572u, 1009u, 1018u, 572u, 0u, 622u,
  1626u, 1298u, 572u, 816u, 1572u, 622u, 752u, 1018u, 726u, 642u, 0u, 1540u, 1009u,
  0u, 1235u, 953u, 1235u, 173u, 953u, 953u, 347u, 347u, 1235u, 173u, 347u, 173u,
  1626u, 1572u, 726u, 1009u, 816u, 1018u, 1540u, 572u, 752u, 0u, 1298u, 622u, 642u,
  374u, 1559u, 0u, 160u, 1112u, 1246u, 934u, 1278u, 828u, 764u, 588u, 254u, 782u
 };

static const QType JTable_13_13123111[]=
 {
  3102u, 18u, 1540u, 1130u, 2282u, 1288u, 1677u, 3346u, 1812u, 1332u, 818u, 0u, 972u,
  372u, 1524u, 2490u, 1506u, 1724u, 2937u, 1002u, 2500u, 0u, 490u, 338u, 2258u, 2644u,
  497u, 2454u, 1882u, 2454u, 0u, 1882u, 1882u, 568u, 568u, 2454u, 0u, 568u, 0u,
  372u, 338u, 2500u, 1724u, 1524u, 2258u, 0u, 2937u, 2490u, 2644u, 490u, 1002u, 1506u,
  372u, 2490u, 1724u, 1002u, 0u, 338u, 2644u, 1524u, 1506u, 2937u, 2500u, 490u, 2258u,
  3102u, 0u, 1332u, 3346u, 1288u, 1130u, 18u, 972u, 818u, 1812u, 1677u, 2282u, 1540u,
  372u, 2490u, 1724u, 1002u, 0u, 338u, 2644u, 1524u, 1506u, 2937u, 2500u, 490u, 2258u,
  372u, 338u, 2500u, 1724u, 1524u, 2258u, 0u, 2937u, 2490u, 2644u, 490u, 1002u, 1506u,
  497u, 2454u, 1882u, 2454u, 0u, 1882u, 1882u, 568u, 568u, 2454u, 0u, 568u, 0u,
  372u, 1524u, 2490u, 1506u, 1724u, 2937u, 1002u, 2500u, 0u, 490u, 338u, 2258u, 2644u,
  3102u, 18u, 1540u, 1130u, 2282u, 1288u, 1677u, 3346u, 1812u, 1332u, 818u, 0u, 972u
 };

static const TestSet::JTable JSet_13[]=
 {
  { 79u , 4u , JTable_13_79 },
  { 131u , 4u , JTable_13_131 },
  { 547u , 4u , JTable_13_547 },
  { 859u , 4u , JTable_13_859 },
  { 911u , 4u , JTable_13_911 },
  { 2003u , 4u , JTable_13_2003 },
  { 2731u , 4u , JTable_13_2731 },
  { 6007u , 4u , JTable_13_6007 },
  { 443u , 5u , JTable_13_443 },
  { 1327u , 5u , JTable_13_1327 },
  { 9283u , 5u , JTable_13_9283 },
  { 46411u , 5u , JTable_13_46411 },
  { 72931u , 5u , JTable_13_72931 },
  { 102103u , 5u , JTable_13_102103 },
  { 1483u , 6u , JTable_13_1483 },
  { 7411u , 6u , JTable_13_7411 },
  { 17291u , 6u , JTable_13_17291 },
  { 38039u , 6u , JTable_13_38039 },
  { 51871u , 6u , JTable_13_51871 },
  { 58787u , 6u , JTable_13_58787 },
  { 461891u , 6u , JTable_13_461891 },
  { 1939939u , 6u , JTable_13_1939939 },
  { 3233231u , 6u , JTable_13_3233231 },
  { 599u , 7u , JTable_13_599 },
  { 8971u , 7u , JTable_13_8971 },
  { 62791u , 7u , JTable_13_62791 },
  { 111827u , 7u , JTable_13_111827 },
  { 138139u , 7u , JTable_13_138139 },
  { 355811u , 7u , JTable_13_355811 },
  { 782783u , 7u , JTable_13_782783 },
  { 1193011u , 7u , JTable_13_1193011 },
  { 2348347u , 7u , JTable_13_2348347 },
  { 2624623u , 7u , JTable_13_2624623 },
  { 2897311u , 7u , JTable_13_2897311 },
  { 13123111u , 7u , JTable_13_13123111 }
 };

static const QType JTable_17_103[]=
 {
  8u, 8u, 6u, 6u, 8u, 10u, 4u, 2u, 8u, 0u, 6u, 6u, 8u, 6u, 5u, 4u, 6u,
  7u, 6u, 0u, 7u, 5u, 6u, 1u, 0u, 1u, 4u, 4u, 6u, 3u, 5u, 5u, 6u, 1u,
  4u, 3u, 0u, 3u, 0u, 2u, 3u, 9u, 0u, 4u, 7u, 4u, 4u, 0u, 1u, 3u, 3u,
  4u, 0u, 4u, 2u, 3u, 1u, 7u, 3u, 0u, 3u, 4u, 9u, 3u, 3u, 4u, 0u, 0u,
  7u, 5u, 6u, 1u, 6u, 0u, 1u, 5u, 4u, 0u, 5u, 6u, 6u, 3u, 4u, 1u, 7u,
  4u, 3u, 3u, 4u, 4u, 3u, 3u, 0u, 9u, 7u, 0u, 3u, 0u, 2u, 0u, 4u, 1u,
  7u, 0u, 5u, 1u, 1u, 4u, 3u, 5u, 1u, 6u, 7u, 6u, 0u, 4u, 6u, 5u, 6u,
  8u, 4u, 6u, 6u, 0u, 2u, 10u, 6u, 8u, 6u, 5u, 8u, 6u, 8u, 4u, 8u, 6u,
  7u, 0u, 5u, 1u, 1u, 4u, 3u, 5u, 1u, 6u, 7u, 6u, 0u, 4u, 6u, 5u, 6u,
  4u, 3u, 3u, 4u, 4u, 3u, 3u, 0u, 9u, 7u, 0u, 3u, 0u, 2u, 0u, 4u, 1u,
  7u, 5u, 6u, 1u, 6u, 0u, 1u, 5u, 4u, 0u, 5u, 6u, 6u, 3u, 4u, 1u, 7u,
  4u, 0u, 4u, 2u, 3u, 1u, 7u, 3u, 0u, 3u, 4u, 9u, 3u, 3u, 4u, 0u, 0u,
  4u, 3u, 0u, 3u, 0u, 2u, 3u, 9u, 0u, 4u, 7u, 4u, 4u, 0u, 1u, 3u, 3u,
  7u, 6u, 0u, 7u, 5u, 6u, 1u, 0u, 1u, 4u, 4u, 6u, 3u, 5u, 5u, 6u, 1u,
  8u, 8u, 6u, 6u, 8u, 10u, 4u, 2u, 8u, 0u, 6u, 6u, 8u, 6u, 5u, 4u, 6u
 };

static const QType JTable_17_239[]=
 {
  6u, 0u, 6u, 4u, 11u, 6u, 4u, 2u, 0u, 2u, 0u, 2u, 10u, 0u, 0u, 10u, 4u,
  4u, 4u, 2u, 5u, 4u, 0u, 5u, 3u, 8u, 6u, 1u, 8u, 3u, 4u, 5u, 17u, 5u,
  4u, 5u, 8u, 1u, 13u, 4u, 0u, 3u, 7u, 4u, 7u, 5u, 7u, 10u, 14u, 4u, 5u,
  4u, 10u, 4u, 4u, 5u, 14u, 7u, 0u, 8u, 4u, 5u, 3u, 1u, 5u, 7u, 7u, 13u,
  4u, 5u, 8u, 8u, 0u, 2u, 5u, 4u, 1u, 3u, 4u, 4u, 17u, 3u, 6u, 5u, 5u,
  4u, 1u, 0u, 4u, 7u, 4u, 5u, 13u, 3u, 7u, 10u, 5u, 8u, 4u, 7u, 5u, 14u,
  4u, 2u, 4u, 5u, 8u, 1u, 3u, 5u, 5u, 4u, 5u, 0u, 3u, 6u, 8u, 4u, 17u,
  6u, 10u, 0u, 2u, 2u, 2u, 6u, 4u, 0u, 4u, 0u, 10u, 0u, 0u, 4u, 11u, 6u,
  4u, 2u, 4u, 5u, 8u, 1u, 3u, 5u, 5u, 4u, 5u, 0u, 3u, 6u, 8u, 4u, 17u,
  4u, 1u, 0u, 4u, 7u, 4u, 5u, 13u, 3u, 7u, 10u, 5u, 8u, 4u, 7u, 5u, 14u,
  4u, 5u, 8u, 8u, 0u, 2u, 5u, 4u, 1u, 3u, 4u, 4u, 17u, 3u, 6u, 5u, 5u,
  4u, 10u, 4u, 4u, 5u, 14u, 7u, 0u, 8u, 4u, 5u, 3u, 1u, 5u, 7u, 7u, 13u,
  4u, 5u, 8u, 1u, 13u, 4u, 0u, 3u, 7u, 4u, 7u, 5u, 7u, 10u, 14u, 4u, 5u,
  4u, 4u, 2u, 5u, 4u, 0u, 5u, 3u, 8u, 6u, 1u, 8u, 3u, 4u, 5u, 17u, 5u,
  6u, 0u, 6u, 4u, 11u, 6u, 4u, 2u, 0u, 2u, 0u, 2u, 10u, 0u, 0u, 10u, 4u
 };

static const QType JTable_17_443[]=
 {
  5u, 15u, 9u, 17u, 11u, 7u, 11u, 13u, 5u, 1u, 11u, 11u, 9u, 11u, 1u, 0u, 15u,
  12u, 11u, 7u, 12u, 7u, 1u, 8u, 19u, 2u, 10u, 2u, 10u, 7u, 0u, 3u, 1u, 6u,
  0u, 10u, 16u, 2u, 11u, 2u, 11u, 11u, 10u, 11u, 3u, 4u, 0u, 3u, 3u, 14u, 7u,
  0u, 3u, 11u, 2u, 10u, 3u, 3u, 11u, 16u, 14u, 4u, 11u, 2u, 7u, 0u, 10u, 11u,
  12u, 3u, 10u, 2u, 1u, 7u, 6u, 0u, 2u, 19u, 7u, 11u, 1u, 7u, 10u, 8u, 12u,
  0u, 2u, 11u, 11u, 0u, 14u, 10u, 11u, 11u, 3u, 3u, 7u, 16u, 2u, 10u, 4u, 3u,
  12u, 7u, 7u, 8u, 2u, 2u, 7u, 3u, 6u, 11u, 12u, 1u, 19u, 10u, 10u, 0u, 1u,
  5u, 0u, 11u, 11u, 1u, 13u, 7u, 17u, 15u, 15u, 1u, 9u, 11u, 5u, 11u, 11u, 9u,
  12u, 7u, 7u, 8u, 2u, 2u, 7u, 3u, 6u, 11u, 12u, 1u, 19u, 10u, 10u, 0u, 1u,
  0u, 2u, 11u, 11u, 0u, 14u, 10u, 11u, 11u, 3u, 3u, 7u, 16u, 2u, 10u, 4u, 3u,
  12u, 3u, 10u, 2u, 1u, 7u, 6u, 0u, 2u, 19u, 7u, 11u, 1u, 7u, 10u, 8u, 12u,
  0u, 3u, 11u, 2u, 10u, 3u, 3u, 11u, 16u, 14u, 4u, 11u, 2u, 7u, 0u, 10u, 11u,
  0u, 10u, 16u, 2u, 11u, 2u, 11u, 11u, 10u, 11u, 3u, 4u, 0u, 3u, 3u, 14u, 7u,
  12u, 11u, 7u, 12u, 7u, 1u, 8u, 19u, 2u, 10u, 2u, 10u, 7u, 0u, 3u, 1u, 6u,
  5u, 15u, 9u, 17u, 11u, 7u, 11u, 13u, 5u, 1u, 11u, 11u, 9u, 11u, 1u, 0u, 15u
 };

static const QType JTable_17_1123[]=
 {
  10u, 22u, 14u, 30u, 18u, 2u, 8u, 14u, 12u, 8u, 0u, 20u, 8u, 12u, 6u, 19u, 0u,
  6u, 18u, 8u, 7u, 13u, 6u, 4u, 21u, 12u, 23u, 29u, 6u, 11u, 0u, 23u, 11u, 5u,
  23u, 24u, 24u, 19u, 0u, 25u, 19u, 26u, 16u, 11u, 29u, 17u, 24u, 20u, 16u, 25u, 38u,
  23u, 20u, 11u, 25u, 24u, 16u, 29u, 19u, 24u, 25u, 17u, 26u, 19u, 38u, 24u, 16u, 0u,
  6u, 23u, 6u, 12u, 6u, 8u, 5u, 0u, 29u, 21u, 13u, 18u, 11u, 11u, 23u, 4u, 7u,
  23u, 19u, 19u, 11u, 24u, 25u, 24u, 0u, 26u, 29u, 20u, 38u, 24u, 25u, 16u, 17u, 16u,
  6u, 8u, 13u, 4u, 12u, 29u, 11u, 23u, 5u, 18u, 7u, 6u, 21u, 23u, 6u, 0u, 11u,
  10u, 19u, 12u, 20u, 8u, 14u, 2u, 30u, 22u, 0u, 6u, 8u, 0u, 12u, 8u, 18u, 14u,
  6u, 8u, 13u, 4u, 12u, 29u, 11u, 23u, 5u, 18u, 7u, 6u, 21u, 23u, 6u, 0u, 11u,
  23u, 19u, 19u, 11u, 24u, 25u, 24u, 0u, 26u, 29u, 20u, 38u, 24u, 25u, 16u, 17u, 16u,
  6u, 23u, 6u, 12u, 6u, 8u, 5u, 0u, 29u, 21u, 13u, 18u, 11u, 11u, 23u, 4u, 7u,
  23u, 20u, 11u, 25u, 24u, 16u, 29u, 19u, 24u, 25u, 17u, 26u, 19u, 38u, 24u, 16u, 0u,
  23u, 24u, 24u, 19u, 0u, 25u, 19u, 26u, 16u, 11u, 29u, 17u, 24u, 20u, 16u, 25u, 38u,
  6u, 18u, 8u, 7u, 13u, 6u, 4u, 21u, 12u, 23u, 29u, 6u, 11u, 0u, 23u, 11u, 5u,
  10u, 22u, 14u, 30u, 18u, 2u, 8u, 14u, 12u, 8u, 0u, 20u, 8u, 12u, 6u, 19u, 0u
 };

static const QType JTable_17_1327[]=
 {
  6u, 0u, 14u, 22u, 8u, 2u, 8u, 8u, 6u, 16u, 24u, 24u, 14u, 3u, 28u, 2u, 18u,
  19u, 24u, 29u, 24u, 15u, 13u, 0u, 32u, 20u, 11u, 26u, 31u, 23u, 30u, 18u, 30u, 11u,
  19u, 23u, 28u, 25u, 26u, 19u, 29u, 36u, 12u, 0u, 27u, 7u, 26u, 19u, 26u, 20u, 14u,
  19u, 19u, 0u, 19u, 23u, 26u, 27u, 29u, 28u, 20u, 7u, 36u, 25u, 14u, 26u, 12u, 26u,
  19u, 18u, 31u, 20u, 13u, 29u, 11u, 30u, 26u, 32u, 15u, 24u, 30u, 23u, 11u, 0u, 24u,
  19u, 25u, 29u, 0u, 26u, 20u, 23u, 26u, 36u, 27u, 19u, 14u, 28u, 19u, 12u, 7u, 26u,
  19u, 29u, 15u, 0u, 20u, 26u, 23u, 18u, 11u, 24u, 24u, 13u, 32u, 11u, 31u, 30u, 30u,
  6u, 2u, 3u, 24u, 16u, 8u, 2u, 22u, 0u, 18u, 28u, 14u, 24u, 6u, 8u, 8u, 14u,
  19u, 29u, 15u, 0u, 20u, 26u, 23u, 18u, 11u, 24u, 24u, 13u, 32u, 11u, 31u, 30u, 30u,
  19u, 25u, 29u, 0u, 26u, 20u, 23u, 26u, 36u, 27u, 19u, 14u, 28u, 19u, 12u, 7u, 26u,
  19u, 18u, 31u, 20u, 13u, 29u, 11u, 30u, 26u, 32u, 15u, 24u, 30u, 23u, 11u, 0u, 24u,
  19u, 19u, 0u, 19u, 23u, 26u, 27u, 29u, 28u, 20u, 7u, 36u, 25u, 14u, 26u, 12u, 26u,
  19u, 23u, 28u, 25u, 26u, 19u, 29u, 36u, 12u, 0u, 27u, 7u, 26u, 19u, 26u, 20u, 14u,
  19u, 24u, 29u, 24u, 15u, 13u, 0u, 32u, 20u, 11u, 26u, 31u, 23u, 30u, 18u, 30u, 11u,
  6u, 0u, 14u, 22u, 8u, 2u, 8u, 8u, 6u, 16u, 24u, 24u, 14u, 3u, 28u, 2u, 18u
 };

static const QType JTable_17_1871[]=
 {
  30u, 16u, 36u, 28u, 22u, 0u, 18u, 20u, 6u, 28u, 26u, 28u, 22u, 22u, 38u, 28u, 5u,
  10u, 30u, 7u, 32u, 0u, 5u, 23u, 25u, 25u, 14u, 19u, 14u, 3u, 1u, 18u, 10u, 1u,
  33u, 14u, 0u, 17u, 10u, 13u, 16u, 18u, 28u, 4u, 13u, 7u, 32u, 23u, 37u, 14u, 9u,
  33u, 23u, 4u, 13u, 14u, 37u, 13u, 16u, 0u, 14u, 7u, 18u, 17u, 9u, 32u, 28u, 10u,
  10u, 18u, 14u, 25u, 5u, 7u, 1u, 1u, 19u, 25u, 0u, 30u, 10u, 3u, 14u, 23u, 32u,
  33u, 17u, 16u, 4u, 32u, 14u, 14u, 10u, 18u, 13u, 23u, 9u, 0u, 13u, 28u, 7u, 37u,
  10u, 7u, 0u, 23u, 25u, 19u, 3u, 18u, 1u, 30u, 32u, 5u, 25u, 14u, 14u, 1u, 10u,
  30u, 28u, 22u, 28u, 28u, 20u, 0u, 28u, 16u, 5u, 38u, 22u, 26u, 6u, 18u, 22u, 36u,
  10u, 7u, 0u, 23u, 25u, 19u, 3u, 18u, 1u, 30u, 32u, 5u, 25u, 14u, 14u, 1u, 10u,
  33u, 17u, 16u, 4u, 32u, 14u, 14u, 10u, 18u, 13u, 23u, 9u, 0u, 13u, 28u, 7u, 37u,
  10u, 18u, 14u, 25u, 5u, 7u, 1u, 1u, 19u, 25u, 0u, 30u, 10u, 3u, 14u, 23u, 32u,
  33u, 23u, 4u, 13u, 14u, 37u, 13u, 16u, 0u, 14u, 7u, 18u, 17u, 9u, 32u, 28u, 10u,
  33u, 14u, 0u, 17u, 10u, 13u, 16u, 18u, 28u, 4u, 13u, 7u, 32u, 23u, 37u, 14u, 9u,
  10u, 30u, 7u, 32u, 0u, 5u, 23u, 25u, 25u, 14u, 19u, 14u, 3u, 1u, 18u, 10u, 1u,
  30u, 16u, 36u, 28u, 22u, 0u, 18u, 20u, 6u, 28u, 26u, 28u, 22u, 22u, 38u, 28u, 5u
 };

static const QType JTable_17_3571[]=
 {
  38u, 34u, 54u, 0u, 48u, 42u, 28u, 38u, 52u, 58u, 58u, 40u, 32u, 36u, 54u, 57u, 44u,
  8u, 11u, 46u, 0u, 30u, 0u, 0u, 34u, 42u, 26u, 20u, 32u, 32u, 18u, 10u, 16u, 14u,
  36u, 62u, 32u, 30u, 28u, 42u, 24u, 36u, 26u, 20u, 41u, 54u, 0u, 26u, 26u, 44u, 50u,
  36u, 26u, 20u, 42u, 62u, 26u, 41u, 24u, 32u, 44u, 54u, 36u, 30u, 50u, 0u, 26u, 28u,
  8u, 10u, 32u, 42u, 0u, 46u, 14u, 18u, 20u, 34u, 30u, 11u, 16u, 32u, 26u, 0u, 0u,
  36u, 30u, 24u, 20u, 0u, 44u, 62u, 28u, 36u, 41u, 26u, 50u, 32u, 42u, 26u, 54u, 26u,
  8u, 46u, 30u, 0u, 42u, 20u, 32u, 10u, 14u, 11u, 0u, 0u, 34u, 26u, 32u, 18u, 16u,
  38u, 57u, 36u, 40u, 58u, 38u, 42u, 0u, 34u, 44u, 54u, 32u, 58u, 52u, 28u, 48u, 54u,
  8u, 46u, 30u, 0u, 42u, 20u, 32u, 10u, 14u, 11u, 0u, 0u, 34u, 26u, 32u, 18u, 16u,
  36u, 30u, 24u, 20u, 0u, 44u, 62u, 28u, 36u, 41u, 26u, 50u, 32u, 42u, 26u, 54u, 26u,
  8u, 10u, 32u, 42u, 0u, 46u, 14u, 18u, 20u, 34u, 30u, 11u, 16u, 32u, 26u, 0u, 0u,
  36u, 26u, 20u, 42u, 62u, 26u, 41u, 24u, 32u, 44u, 54u, 36u, 30u, 50u, 0u, 26u, 28u,
  36u, 62u, 32u, 30u, 28u, 42u, 24u, 36u, 26u, 20u, 41u, 54u, 0u, 26u, 26u, 44u, 50u,
  8u, 11u, 46u, 0u, 30u, 0u, 0u, 34u, 42u, 26u, 20u, 32u, 32u, 18u, 10u, 16u, 14u,
  38u, 34u, 54u, 0u, 48u, 42u, 28u, 38u, 52u, 58u, 58u, 40u, 32u, 36u, 54u, 57u, 44u
 };

static const QType JTable_17_9283[]=
 {
  34u, 12u, 30u, 28u, 52u, 14u, 0u, 6u, 20u, 6u, 18u, 100u, 14u, 36u, 26u, 35u, 44u,
  57u, 35u, 61u, 34u, 30u, 46u, 49u, 0u, 11u, 26u, 52u, 61u, 80u, 21u, 33u, 84u, 16u,
  7u, 54u, 26u, 29u, 80u, 69u, 44u, 78u, 16u, 57u, 43u, 43u, 0u, 26u, 63u, 53u, 42u,
  7u, 26u, 57u, 69u, 54u, 63u, 43u, 44u, 26u, 53u, 43u, 78u, 29u, 42u, 0u, 16u, 80u,
  57u, 33u, 61u, 11u, 46u, 61u, 16u, 21u, 52u, 0u, 30u, 35u, 84u, 80u, 26u, 49u, 34u,
  7u, 29u, 44u, 57u, 0u, 53u, 54u, 80u, 78u, 43u, 26u, 42u, 26u, 69u, 16u, 43u, 63u,
  57u, 61u, 30u, 49u, 11u, 52u, 80u, 33u, 16u, 35u, 34u, 46u, 0u, 26u, 61u, 21u, 84u,
  34u, 35u, 36u, 100u, 6u, 6u, 14u, 28u, 12u, 44u, 26u, 14u, 18u, 20u, 0u, 52u, 30u,
  57u, 61u, 30u, 49u, 11u, 52u, 80u, 33u, 16u, 35u, 34u, 46u, 0u, 26u, 61u, 21u, 84u,
  7u, 29u, 44u, 57u, 0u, 53u, 54u, 80u, 78u, 43u, 26u, 42u, 26u, 69u, 16u, 43u, 63u,
  57u, 33u, 61u, 11u, 46u, 61u, 16u, 21u, 52u, 0u, 30u, 35u, 84u, 80u, 26u, 49u, 34u,
  7u, 26u, 57u, 69u, 54u, 63u, 43u, 44u, 26u, 53u, 43u, 78u, 29u, 42u, 0u, 16u, 80u,
  7u, 54u, 26u, 29u, 80u, 69u, 44u, 78u, 16u, 57u, 43u, 43u, 0u, 26u, 63u, 53u, 42u,
  57u, 35u, 61u, 34u, 30u, 46u, 49u, 0u, 11u, 26u, 52u, 61u, 80u, 21u, 33u, 84u, 16u,
  34u, 12u, 30u, 28u, 52u, 14u, 0u, 6u, 20u, 6u, 18u, 100u, 14u, 36u, 26u, 35u, 44u
 };

static const QType JTable_17_46411[]=
 {
  60u, 66u, 0u, 110u, 82u, 66u, 168u, 80u, 152u, 122u, 136u, 54u, 136u, 40u, 3u, 126u, 162u,
  166u, 128u, 158u, 172u, 206u, 168u, 162u, 108u, 190u, 154u, 101u, 0u, 184u, 166u, 124u, 238u, 124u,
  48u, 154u, 100u, 186u, 74u, 78u, 152u, 142u, 76u, 180u, 128u, 58u, 0u, 90u, 52u, 153u, 130u,
  48u, 90u, 180u, 78u, 154u, 52u, 128u, 152u, 100u, 153u, 58u, 142u, 186u, 130u, 0u, 76u, 74u,
  166u, 124u, 0u, 190u, 168u, 158u, 124u, 166u, 101u, 108u, 206u, 128u, 238u, 184u, 154u, 162u, 172u,
  48u, 186u, 152u, 180u, 0u, 153u, 154u, 74u, 142u, 128u, 90u, 130u, 100u, 78u, 76u, 58u, 52u,
  166u, 158u, 206u, 162u, 190u, 101u, 184u, 124u, 124u, 128u, 172u, 168u, 108u, 154u, 0u, 166u, 238u,
  60u, 126u, 40u, 54u, 122u, 80u, 66u, 110u, 66u, 162u, 3u, 136u, 136u, 152u, 168u, 82u, 0u,
  166u, 158u, 206u, 162u, 190u, 101u, 184u, 124u, 124u, 128u, 172u, 168u, 108u, 154u, 0u, 166u, 238u,
  48u, 186u, 152u, 180u, 0u, 153u, 154u, 74u, 142u, 128u, 90u, 130u, 100u, 78u, 76u, 58u, 52u,
  166u, 124u, 0u, 190u, 168u, 158u, 124u, 166u, 101u, 108u, 206u, 128u, 238u, 184u, 154u, 162u, 172u,
  48u, 90u, 180u, 78u, 154u, 52u, 128u, 152u, 100u, 153u, 58u, 142u, 186u, 130u, 0u, 76u, 74u,
  48u, 154u, 100u, 186u, 74u, 78u, 152u, 142u, 76u, 180u, 128u, 58u, 0u, 90u, 52u, 153u, 130u,
  166u, 128u, 158u, 172u, 206u, 168u, 162u, 108u, 190u, 154u, 101u, 0u, 184u, 166u, 124u, 238u, 124u,
  60u, 66u, 0u, 110u, 82u, 66u, 168u, 80u, 152u, 122u, 136u, 54u, 136u, 40u, 3u, 126u, 162u
 };

static const QType JTable_17_72931[]=
 {
  0u, 150u, 148u, 72u, 22u, 86u, 34u, 184u, 80u, 232u, 118u, 90u, 132u, 18u, 92u, 133u, 6u,
  141u, 37u, 147u, 195u, 208u, 0u, 116u, 129u, 11u, 170u, 128u, 213u, 148u, 146u, 194u, 200u, 111u,
  204u, 197u, 255u, 0u, 114u, 145u, 131u, 83u, 172u, 178u, 186u, 140u, 230u, 183u, 167u, 65u, 235u,
  204u, 183u, 178u, 145u, 197u, 167u, 186u, 131u, 255u, 65u, 140u, 83u, 0u, 235u, 230u, 172u, 114u,
  141u, 194u, 213u, 11u, 0u, 147u, 111u, 146u, 128u, 129u, 208u, 37u, 200u, 148u, 170u, 116u, 195u,
  204u, 0u, 131u, 178u, 230u, 65u, 197u, 114u, 83u, 186u, 183u, 235u, 255u, 145u, 172u, 140u, 167u,
  141u, 147u, 208u, 116u, 11u, 128u, 148u, 194u, 111u, 37u, 195u, 0u, 129u, 170u, 213u, 146u, 200u,
  0u, 133u, 18u, 90u, 232u, 184u, 86u, 72u, 150u, 6u, 92u, 132u, 118u, 80u, 34u, 22u, 148u,
  141u, 147u, 208u, 116u, 11u, 128u, 148u, 194u, 111u, 37u, 195u, 0u, 129u, 170u, 213u, 146u, 200u,
  204u, 0u, 131u, 178u, 230u, 65u, 197u, 114u, 83u, 186u, 183u, 235u, 255u, 145u, 172u, 140u, 167u,
  141u, 194u, 213u, 11u, 0u, 147u, 111u, 146u, 128u, 129u, 208u, 37u, 200u, 148u, 170u, 116u, 195u,
  204u, 183u, 178u, 145u, 197u, 167u, 186u, 131u, 255u, 65u, 140u, 83u, 0u, 235u, 230u, 172u, 114u,
  204u, 197u, 255u, 0u, 114u, 145u, 131u, 83u, 172u, 178u, 186u, 140u, 230u, 183u, 167u, 65u, 235u,
  141u, 37u, 147u, 195u, 208u, 0u, 116u, 129u, 11u, 170u, 128u, 213u, 148u, 146u, 194u, 200u, 111u,
  0u, 150u, 148u, 72u, 22u, 86u, 34u, 184u, 80u, 232u, 118u, 90u, 132u, 18u, 92u, 133u, 6u
 };

static const QType JTable_17_102103[]=
 {
  72u, 374u, 159u, 188u, 178u, 122u, 108u, 218u, 168u, 178u, 184u, 118u, 0u, 154u, 156u, 94u, 112u,
  0u, 172u, 0u, 124u, 197u, 47u, 70u, 131u, 115u, 50u, 233u, 263u, 178u, 84u, 67u, 78u, 179u,
  157u, 162u, 102u, 15u, 63u, 125u, 119u, 6u, 217u, 188u, 109u, 201u, 220u, 98u, 129u, 0u, 264u,
  157u, 98u, 188u, 125u, 162u, 129u, 109u, 119u, 102u, 0u, 201u, 6u, 15u, 264u, 220u, 217u, 63u,
  0u, 67u, 263u, 115u, 47u, 0u, 179u, 84u, 233u, 131u, 197u, 172u, 78u, 178u, 50u, 70u, 124u,
  157u, 15u, 119u, 188u, 220u, 0u, 162u, 63u, 6u, 109u, 98u, 264u, 102u, 125u, 217u, 201u, 129u,
  0u, 0u, 197u, 70u, 115u, 233u, 178u, 67u, 179u, 172u, 124u, 47u, 131u, 50u, 263u, 84u, 78u,
  72u, 94u, 154u, 118u, 178u, 218u, 122u, 188u, 374u, 112u, 156u, 0u, 184u, 168u, 108u, 178u, 159u,
  0u, 0u, 197u, 70u, 115u, 233u, 178u, 67u, 179u, 172u, 124u, 47u, 131u, 50u, 263u, 84u, 78u,
  157u, 15u, 119u, 188u, 220u, 0u, 162u, 63u, 6u, 109u, 98u, 264u, 102u, 125u, 217u, 201u, 129u,
  0u, 67u, 263u, 115u, 47u, 0u, 179u, 84u, 233u, 131u, 197u, 172u, 78u, 178u, 50u, 70u, 124u,
  157u, 98u, 188u, 125u, 162u, 129u, 109u, 119u, 102u, 0u, 201u, 6u, 15u, 264u, 220u, 217u, 63u,
  157u, 162u, 102u, 15u, 63u, 125u, 119u, 6u, 217u, 188u, 109u, 201u, 220u, 98u, 129u, 0u, 264u,
  0u, 172u, 0u, 124u, 197u, 47u, 70u, 131u, 115u, 50u, 233u, 263u, 178u, 84u, 67u, 78u, 179u,
  72u, 374u, 159u, 188u, 178u, 122u, 108u, 218u, 168u, 178u, 184u, 118u, 0u, 154u, 156u, 94u, 112u
 };

static const QType JTable_17_647[]=
 {
  16u, 6u, 18u, 10u, 20u, 22u, 22u, 13u, 12u, 12u, 10u, 16u, 12u, 0u, 18u, 22u, 8u,
  18u, 9u, 15u, 2u, 12u, 1u, 13u, 12u, 5u, 9u, 4u, 1u, 16u, 6u, 0u, 10u, 19u,
  13u, 13u, 12u, 18u, 11u, 0u, 15u, 3u, 7u, 9u, 24u, 11u, 14u, 10u, 5u, 20u, 18u,
  13u, 10u, 9u, 0u, 13u, 5u, 24u, 15u, 12u, 20u, 11u, 3u, 18u, 18u, 14u, 7u, 11u,
  18u, 0u, 1u, 5u, 1u, 15u, 19u, 6u, 4u, 12u, 12u, 9u, 10u, 16u, 9u, 13u, 2u,
  13u, 18u, 15u, 9u, 14u, 20u, 13u, 11u, 3u, 24u, 10u, 18u, 12u, 0u, 7u, 11u, 5u,
  18u, 15u, 12u, 13u, 5u, 4u, 16u, 0u, 19u, 9u, 2u, 1u, 12u, 9u, 1u, 6u, 10u,
  16u, 22u, 0u, 16u, 12u, 13u, 22u, 10u, 6u, 8u, 18u, 12u, 10u, 12u, 22u, 20u, 18u,
  18u, 15u, 12u, 13u, 5u, 4u, 16u, 0u, 19u, 9u, 2u, 1u, 12u, 9u, 1u, 6u, 10u,
  13u, 18u, 15u, 9u, 14u, 20u, 13u, 11u, 3u, 24u, 10u, 18u, 12u, 0u, 7u, 11u, 5u,
  18u, 0u, 1u, 5u, 1u, 15u, 19u, 6u, 4u, 12u, 12u, 9u, 10u, 16u, 9u, 13u, 2u,
  13u, 10u, 9u, 0u, 13u, 5u, 24u, 15u, 12u, 20u, 11u, 3u, 18u, 18u, 14u, 7u, 11u,
  13u, 13u, 12u, 18u, 11u, 0u, 15u, 3u, 7u, 9u, 24u, 11u, 14u, 10u, 5u, 20u, 18u,
  18u, 9u, 15u, 2u, 12u, 1u, 13u, 12u, 5u, 9u, 4u, 1u, 16u, 6u, 0u, 10u, 19u,
  16u, 6u, 18u, 10u, 20u, 22u, 22u, 13u, 12u, 12u, 10u, 16u, 12u, 0u, 18u, 22u, 8u
 };

static const QType JTable_17_4523[]=
 {
  25u, 58u, 52u, 22u, 16u, 44u, 24u, 14u, 16u, 30u, 0u, 50u, 14u, 22u, 28u, 6u, 20u,
  41u, 52u, 31u, 36u, 50u, 43u, 41u, 24u, 39u, 39u, 0u, 57u, 29u, 40u, 24u, 12u, 2u,
  39u, 34u, 64u, 22u, 36u, 35u, 23u, 28u, 5u, 31u, 42u, 31u, 35u, 10u, 0u, 57u, 34u,
  39u, 10u, 31u, 35u, 34u, 0u, 42u, 23u, 64u, 57u, 31u, 28u, 22u, 34u, 35u, 5u, 36u,
  41u, 24u, 57u, 39u, 43u, 31u, 2u, 40u, 0u, 24u, 50u, 52u, 12u, 29u, 39u, 41u, 36u,
  39u, 22u, 23u, 31u, 35u, 57u, 34u, 36u, 28u, 42u, 10u, 34u, 64u, 35u, 5u, 31u, 0u,
  41u, 31u, 50u, 41u, 39u, 0u, 29u, 24u, 2u, 52u, 36u, 43u, 24u, 39u, 57u, 40u, 12u,
  25u, 6u, 22u, 50u, 30u, 14u, 44u, 22u, 58u, 20u, 28u, 14u, 0u, 16u, 24u, 16u, 52u,
  41u, 31u, 50u, 41u, 39u, 0u, 29u, 24u, 2u, 52u, 36u, 43u, 24u, 39u, 57u, 40u, 12u,
  39u, 22u, 23u, 31u, 35u, 57u, 34u, 36u, 28u, 42u, 10u, 34u, 64u, 35u, 5u, 31u, 0u,
  41u, 24u, 57u, 39u, 43u, 31u, 2u, 40u, 0u, 24u, 50u, 52u, 12u, 29u, 39u, 41u, 36u,
  39u, 10u, 31u, 35u, 34u, 0u, 42u, 23u, 64u, 57u, 31u, 28u, 22u, 34u, 35u, 5u, 36u,
  39u, 34u, 64u, 22u, 36u, 35u, 23u, 28u, 5u, 31u, 42u, 31u, 35u, 10u, 0u, 57u, 34u,
  41u, 52u, 31u, 36u, 50u, 43u, 41u, 24u, 39u, 39u, 0u, 57u, 29u, 40u, 24u, 12u, 2u,
  25u, 58u, 52u, 22u, 16u, 44u, 24u, 14u, 16u, 30u, 0u, 50u, 14u, 22u, 28u, 6u, 20u
 };

static const QType JTable_17_13567[]=
 {
  44u, 54u, 90u, 74u, 38u, 68u, 60u, 68u, 66u, 79u, 8u, 102u, 66u, 50u, 12u, 0u, 72u,
  25u, 84u, 40u, 64u, 3u, 32u, 70u, 54u, 67u, 12u, 9u, 0u, 61u, 1u, 21u, 73u, 46u,
  28u, 63u, 38u, 81u, 7u, 85u, 58u, 29u, 61u, 89u, 70u, 81u, 34u, 0u, 20u, 72u, 33u,
  28u, 0u, 89u, 85u, 63u, 20u, 70u, 58u, 38u, 72u, 81u, 29u, 81u, 33u, 34u, 61u, 7u,
  25u, 21u, 0u, 67u, 32u, 40u, 46u, 1u, 9u, 54u, 3u, 84u, 73u, 61u, 12u, 70u, 64u,
  28u, 81u, 58u, 89u, 34u, 72u, 63u, 7u, 29u, 70u, 0u, 33u, 38u, 85u, 61u, 81u, 20u,
  25u, 40u, 3u, 70u, 67u, 9u, 61u, 21u, 46u, 84u, 64u, 32u, 54u, 12u, 0u, 1u, 73u,
  44u, 0u, 50u, 102u, 79u, 68u, 68u, 74u, 54u, 72u, 12u, 66u, 8u, 66u, 60u, 38u, 90u,
  25u, 40u, 3u, 70u, 67u, 9u, 61u, 21u, 46u, 84u, 64u, 32u, 54u, 12u, 0u, 1u, 73u,
  28u, 81u, 58u, 89u, 34u, 72u, 63u, 7u, 29u, 70u, 0u, 33u, 38u, 85u, 61u, 81u, 20u,
  25u, 21u, 0u, 67u, 32u, 40u, 46u, 1u, 9u, 54u, 3u, 84u, 73u, 61u, 12u, 70u, 64u,
  28u, 0u, 89u, 85u, 63u, 20u, 70u, 58u, 38u, 72u, 81u, 29u, 81u, 33u, 34u, 61u, 7u,
  28u, 63u, 38u, 81u, 7u, 85u, 58u, 29u, 61u, 89u, 70u, 81u, 34u, 0u, 20u, 72u, 33u,
  25u, 84u, 40u, 64u, 3u, 32u, 70u, 54u, 67u, 12u, 9u, 0u, 61u, 1u, 21u, 73u, 46u,
  44u, 54u, 90u, 74u, 38u, 68u, 60u, 68u, 66u, 79u, 8u, 102u, 66u, 50u, 12u, 0u, 72u
 };

static const QType JTable_17_21319[]=
 {
  46u, 96u, 118u, 116u, 114u, 112u, 94u, 86u, 0u, 82u, 119u, 96u, 74u, 104u, 124u, 86u, 164u,
  66u, 10u, 7u, 0u, 91u, 7u, 62u, 100u, 6u, 47u, 25u, 66u, 81u, 110u, 37u, 33u, 50u,
  76u, 145u, 22u, 87u, 61u, 54u, 0u, 76u, 63u, 53u, 74u, 71u, 114u, 120u, 64u, 63u, 29u,
  76u, 120u, 53u, 54u, 145u, 64u, 74u, 0u, 22u, 63u, 71u, 76u, 87u, 29u, 114u, 63u, 61u,
  66u, 37u, 66u, 6u, 7u, 7u, 50u, 110u, 25u, 100u, 91u, 10u, 33u, 81u, 47u, 62u, 0u,
  76u, 87u, 0u, 53u, 114u, 63u, 145u, 61u, 76u, 74u, 120u, 29u, 22u, 54u, 63u, 71u, 64u,
  66u, 7u, 91u, 62u, 6u, 25u, 81u, 37u, 50u, 10u, 0u, 7u, 100u, 47u, 66u, 110u, 33u,
  46u, 86u, 104u, 96u, 82u, 86u, 112u, 116u, 96u, 164u, 124u, 74u, 119u, 0u, 94u, 114u, 118u,
  66u, 7u, 91u, 62u, 6u, 25u, 81u, 37u, 50u, 10u, 0u, 7u, 100u, 47u, 66u, 110u, 33u,
  76u, 87u, 0u, 53u, 114u, 63u, 145u, 61u, 76u, 74u, 120u, 29u, 22u, 54u, 63u, 71u, 64u,
  66u, 37u, 66u, 6u, 7u, 7u, 50u, 110u, 25u, 100u, 91u, 10u, 33u, 81u, 47u, 62u, 0u,
  76u, 120u, 53u, 54u, 145u, 64u, 74u, 0u, 22u, 63u, 71u, 76u, 87u, 29u, 114u, 63u, 61u,
  76u, 145u, 22u, 87u, 61u, 54u, 0u, 76u, 63u, 53u, 74u, 71u, 114u, 120u, 64u, 63u, 29u,
  66u, 10u, 7u, 0u, 91u, 7u, 62u, 100u, 6u, 47u, 25u, 66u, 81u, 110u, 37u, 33u, 50u,
  46u, 96u, 118u, 116u, 114u, 112u, 94u, 86u, 0u, 82u, 119u, 96u, 74u, 104u, 124u, 86u, 164u
 };

static const QType JTable_17_35531[]=
 {
  80u, 134u, 180u, 82u, 0u, 106u, 44u, 122u, 0u, 68u, 96u, 60u, 95u, 74u, 42u, 62u, 114u,
  30u, 87u, 2u, 68u, 39u, 50u, 0u, 75u, 181u, 98u, 37u, 92u, 9u, 63u, 83u, 3u, 68u,
  60u, 41u, 42u, 64u, 59u, 39u, 123u, 27u, 154u, 61u, 0u, 79u, 155u, 134u, 66u, 113u, 40u,
  60u, 134u, 61u, 39u, 41u, 66u, 0u, 123u, 42u, 113u, 79u, 27u, 64u, 40u, 155u, 154u, 59u,
  30u, 83u, 92u, 181u, 50u, 2u, 68u, 63u, 37u, 75u, 39u, 87u, 3u, 9u, 98u, 0u, 68u,
  60u, 64u, 123u, 61u, 155u, 113u, 41u, 59u, 27u, 0u, 134u, 40u, 42u, 39u, 154u, 79u, 66u,
  30u, 2u, 39u, 0u, 181u, 37u, 9u, 83u, 68u, 87u, 68u, 50u, 75u, 98u, 92u, 63u, 3u,
  80u, 62u, 74u, 60u, 68u, 122u, 106u, 82u, 134u, 114u, 42u, 95u, 96u, 0u, 44u, 0u, 180u,
  30u, 2u, 39u, 0u, 181u, 37u, 9u, 83u, 68u, 87u, 68u, 50u, 75u, 98u, 92u, 63u, 3u,
  60u, 64u, 123u, 61u, 155u, 113u, 41u, 59u, 27u, 0u, 134u, 40u, 42u, 39u, 154u, 79u, 66u,
  30u, 83u, 92u, 181u, 50u, 2u, 68u, 63u, 37u, 75u, 39u, 87u, 3u, 9u, 98u, 0u, 68u,
  60u, 134u, 61u, 39u, 41u, 66u, 0u, 123u, 42u, 113u, 79u, 27u, 64u, 40u, 155u, 154u, 59u,
  60u, 41u, 42u, 64u, 59u, 39u, 123u, 27u, 154u, 61u, 0u, 79u, 155u, 134u, 66u, 113u, 40u,
  30u, 87u, 2u, 68u, 39u, 50u, 0u, 75u, 181u, 98u, 37u, 92u, 9u, 63u, 83u, 3u, 68u,
  80u, 134u, 180u, 82u, 0u, 106u, 44u, 122u, 0u, 68u, 96u, 60u, 95u, 74u, 42u, 62u, 114u
 };

static const QType JTable_17_58787[]=
 {
  213u, 169u, 165u, 193u, 247u, 109u, 199u, 169u, 195u, 153u, 123u, 175u, 223u, 119u, 191u, 0u, 93u,
  94u, 69u, 174u, 183u, 183u, 57u, 151u, 0u, 154u, 118u, 4u, 116u, 170u, 144u, 153u, 163u, 157u,
  178u, 0u, 44u, 172u, 82u, 177u, 121u, 131u, 161u, 170u, 163u, 96u, 199u, 117u, 199u, 126u, 226u,
  178u, 117u, 170u, 177u, 0u, 199u, 163u, 121u, 44u, 126u, 96u, 131u, 172u, 226u, 199u, 161u, 82u,
  94u, 153u, 116u, 154u, 57u, 174u, 157u, 144u, 4u, 0u, 183u, 69u, 163u, 170u, 118u, 151u, 183u,
  178u, 172u, 121u, 170u, 199u, 126u, 0u, 82u, 131u, 163u, 117u, 226u, 44u, 177u, 161u, 96u, 199u,
  94u, 174u, 183u, 151u, 154u, 4u, 170u, 153u, 157u, 69u, 183u, 57u, 0u, 118u, 116u, 144u, 163u,
  213u, 0u, 119u, 175u, 153u, 169u, 109u, 193u, 169u, 93u, 191u, 223u, 123u, 195u, 199u, 247u, 165u,
  94u, 174u, 183u, 151u, 154u, 4u, 170u, 153u, 157u, 69u, 183u, 57u, 0u, 118u, 116u, 144u, 163u,
  178u, 172u, 121u, 170u, 199u, 126u, 0u, 82u, 131u, 163u, 117u, 226u, 44u, 177u, 161u, 96u, 199u,
  94u, 153u, 116u, 154u, 57u, 174u, 157u, 144u, 4u, 0u, 183u, 69u, 163u, 170u, 118u, 151u, 183u,
  178u, 117u, 170u, 177u, 0u, 199u, 163u, 121u, 44u, 126u, 96u, 131u, 172u, 226u, 199u, 161u, 82u,
  178u, 0u, 44u, 172u, 82u, 177u, 121u, 131u, 161u, 170u, 163u, 96u, 199u, 117u, 199u, 126u, 226u,
  94u, 69u, 174u, 183u, 183u, 57u, 151u, 0u, 154u, 118u, 4u, 116u, 170u, 144u, 153u, 163u, 157u,
  213u, 169u, 165u, 193u, 247u, 109u, 199u, 169u, 195u, 153u, 123u, 175u, 223u, 119u, 191u, 0u, 93u
 };

static const QType JTable_17_106591[]=
 {
  20u, 92u, 8u, 147u, 270u, 162u, 226u, 0u, 194u, 164u, 48u, 48u, 174u, 62u, 78u, 132u, 146u,
  118u, 60u, 169u, 229u, 67u, 279u, 42u, 61u, 26u, 163u, 211u, 73u, 0u, 108u, 78u, 24u, 76u,
  146u, 143u, 240u, 31u, 78u, 56u, 120u, 124u, 125u, 147u, 99u, 337u, 131u, 131u, 213u, 88u, 0u,
  146u, 131u, 147u, 56u, 143u, 213u, 99u, 120u, 240u, 88u, 337u, 124u, 31u, 0u, 131u, 125u, 78u,
  118u, 78u, 73u, 26u, 279u, 169u, 76u, 108u, 211u, 61u, 67u, 60u, 24u, 0u, 163u, 42u, 229u,
  146u, 31u, 120u, 147u, 131u, 88u, 143u, 78u, 124u, 99u, 131u, 0u, 240u, 56u, 125u, 337u, 213u,
  118u, 169u, 67u, 42u, 26u, 211u, 0u, 78u, 76u, 60u, 229u, 279u, 61u, 163u, 73u, 108u, 24u,
  20u, 132u, 62u, 48u, 164u, 0u, 162u, 147u, 92u, 146u, 78u, 174u, 48u, 194u, 226u, 270u, 8u,
  118u, 169u, 67u, 42u, 26u, 211u, 0u, 78u, 76u, 60u, 229u, 279u, 61u, 163u, 73u, 108u, 24u,
  146u, 31u, 120u, 147u, 131u, 88u, 143u, 78u, 124u, 99u, 131u, 0u, 240u, 56u, 125u, 337u, 213u,
  118u, 78u, 73u, 26u, 279u, 169u, 76u, 108u, 211u, 61u, 67u, 60u, 24u, 0u, 163u, 42u, 229u,
  146u, 131u, 147u, 56u, 143u, 213u, 99u, 120u, 240u, 88u, 337u, 124u, 31u, 0u, 131u, 125u, 78u,
  146u, 143u, 240u, 31u, 78u, 56u, 120u, 124u, 125u, 147u, 99u, 337u, 131u, 131u, 213u, 88u, 0u,
  118u, 60u, 169u, 229u, 67u, 279u, 42u, 61u, 26u, 163u, 211u, 73u, 0u, 108u, 78u, 24u, 76u,
  20u, 92u, 8u, 147u, 270u, 162u, 226u, 0u, 194u, 164u, 48u, 48u, 174u, 62u, 78u, 132u, 146u
 };

static const QType JTable_17_461891[]=
 {
  430u, 0u, 314u, 424u, 582u, 534u, 236u, 304u, 628u, 190u, 205u, 276u, 262u, 242u, 362u, 428u, 124u,
  211u, 358u, 402u, 137u, 35u, 436u, 174u, 59u, 22u, 331u, 0u, 399u, 405u, 379u, 446u, 46u, 256u,
  212u, 268u, 674u, 323u, 0u, 173u, 92u, 387u, 167u, 318u, 28u, 269u, 135u, 208u, 193u, 159u, 473u,
  212u, 208u, 318u, 173u, 268u, 193u, 28u, 92u, 674u, 159u, 269u, 387u, 323u, 473u, 135u, 167u, 0u,
  211u, 446u, 399u, 22u, 436u, 402u, 256u, 379u, 0u, 59u, 35u, 358u, 46u, 405u, 331u, 174u, 137u,
  212u, 323u, 92u, 318u, 135u, 159u, 268u, 0u, 387u, 28u, 208u, 473u, 674u, 173u, 167u, 269u, 193u,
  211u, 402u, 35u, 174u, 22u, 0u, 405u, 446u, 256u, 358u, 137u, 436u, 59u, 331u, 399u, 379u, 46u,
  430u, 428u, 242u, 276u, 190u, 304u, 534u, 424u, 0u, 124u, 362u, 262u, 205u, 628u, 236u, 582u, 314u,
  211u, 402u, 35u, 174u, 22u, 0u, 405u, 446u, 256u, 358u, 137u, 436u, 59u, 331u, 399u, 379u, 46u,
  212u, 323u, 92u, 318u, 135u, 159u, 268u, 0u, 387u, 28u, 208u, 473u, 674u, 173u, 167u, 269u, 193u,
  211u, 446u, 399u, 22u, 436u, 402u, 256u, 379u, 0u, 59u, 35u, 358u, 46u, 405u, 331u, 174u, 137u,
  212u, 208u, 318u, 173u, 268u, 193u, 28u, 92u, 674u, 159u, 269u, 387u, 323u, 473u, 135u, 167u, 0u,
  212u, 268u, 674u, 323u, 0u, 173u, 92u, 387u, 167u, 318u, 28u, 269u, 135u, 208u, 193u, 159u, 473u,
  211u, 358u, 402u, 137u, 35u, 436u, 174u, 59u, 22u, 331u, 0u, 399u, 405u, 379u, 446u, 46u, 256u,
  430u, 0u, 314u, 424u, 582u, 534u, 236u, 304u, 628u, 190u, 205u, 276u, 262u, 242u, 362u, 428u, 124u
 };

static const QType JTable_17_1939939[]=
 {
  558u, 1072u, 1270u, 1366u, 970u, 660u, 548u, 934u, 906u, 944u, 508u, 712u, 1274u, 0u, 960u, 773u, 654u,
  257u, 281u, 180u, 766u, 167u, 225u, 238u, 791u, 26u, 740u, 1334u, 424u, 613u, 0u, 289u, 481u, 480u,
  331u, 233u, 285u, 161u, 542u, 97u, 820u, 190u, 339u, 151u, 460u, 358u, 543u, 652u, 0u, 1133u, 1150u,
  331u, 652u, 151u, 97u, 233u, 0u, 460u, 820u, 285u, 1133u, 358u, 190u, 161u, 1150u, 543u, 339u, 542u,
  257u, 289u, 424u, 26u, 225u, 180u, 480u, 0u, 1334u, 791u, 167u, 281u, 481u, 613u, 740u, 238u, 766u,
  331u, 161u, 820u, 151u, 543u, 1133u, 233u, 542u, 190u, 460u, 652u, 1150u, 285u, 97u, 339u, 358u, 0u,
  257u, 180u, 167u, 238u, 26u, 1334u, 613u, 289u, 480u, 281u, 766u, 225u, 791u, 740u, 424u, 0u, 481u,
  558u, 773u, 0u, 712u, 944u, 934u, 660u, 1366u, 1072u, 654u, 960u, 1274u, 508u, 906u, 548u, 970u, 1270u,
  257u, 180u, 167u, 238u, 26u, 1334u, 613u, 289u, 480u, 281u, 766u, 225u, 791u, 740u, 424u, 0u, 481u,
  331u, 161u, 820u, 151u, 543u, 1133u, 233u, 542u, 190u, 460u, 652u, 1150u, 285u, 97u, 339u, 358u, 0u,
  257u, 289u, 424u, 26u, 225u, 180u, 480u, 0u, 1334u, 791u, 167u, 281u, 481u, 613u, 740u, 238u, 766u,
  331u, 652u, 151u, 97u, 233u, 0u, 460u, 820u, 285u, 1133u, 358u, 190u, 161u, 1150u, 543u, 339u, 542u,
  331u, 233u, 285u, 161u, 542u, 97u, 820u, 190u, 339u, 151u, 460u, 358u, 543u, 652u, 0u, 1133u, 1150u,
  257u, 281u, 180u, 766u, 167u, 225u, 238u, 791u, 26u, 740u, 1334u, 424u, 613u, 0u, 289u, 481u, 480u,
  558u, 1072u, 1270u, 1366u, 970u, 660u, 548u, 934u, 906u, 944u, 508u, 712u, 1274u, 0u, 960u, 773u, 654u
 };

static const QType JTable_17_3233231[]=
 {
  662u, 1314u, 354u, 64u, 649u, 1070u, 1100u, 1148u, 884u, 1158u, 254u, 256u, 1086u, 0u, 1034u, 304u, 392u,
  1099u, 649u, 691u, 175u, 1394u, 830u, 0u, 810u, 1066u, 370u, 824u, 301u, 867u, 267u, 1076u, 1075u, 1578u,
  827u, 1395u, 966u, 1544u, 1718u, 906u, 398u, 1338u, 1140u, 1663u, 761u, 1009u, 1247u, 0u, 933u, 908u, 1113u,
  827u, 0u, 1663u, 906u, 1395u, 933u, 761u, 398u, 966u, 908u, 1009u, 1338u, 1544u, 1113u, 1247u, 1140u, 1718u,
  1099u, 1076u, 301u, 1066u, 830u, 691u, 1578u, 267u, 824u, 810u, 1394u, 649u, 1075u, 867u, 370u, 0u, 175u,
  827u, 1544u, 398u, 1663u, 1247u, 908u, 1395u, 1718u, 1338u, 761u, 0u, 1113u, 966u, 906u, 1140u, 1009u, 933u,
  1099u, 691u, 1394u, 0u, 1066u, 824u, 867u, 1076u, 1578u, 649u, 175u, 830u, 810u, 370u, 301u, 267u, 1075u,
  662u, 304u, 0u, 256u, 1158u, 1148u, 1070u, 64u, 1314u, 392u, 1034u, 1086u, 254u, 884u, 1100u, 649u, 354u,
  1099u, 691u, 1394u, 0u, 1066u, 824u, 867u, 1076u, 1578u, 649u, 175u, 830u, 810u, 370u, 301u, 267u, 1075u,
  827u, 1544u, 398u, 1663u, 1247u, 908u, 1395u, 1718u, 1338u, 761u, 0u, 1113u, 966u, 906u, 1140u, 1009u, 933u,
  1099u, 1076u, 301u, 1066u, 830u, 691u, 1578u, 267u, 824u, 810u, 1394u, 649u, 1075u, 867u, 370u, 0u, 175u,
  827u, 0u, 1663u, 906u, 1395u, 933u, 761u, 398u, 966u, 908u, 1009u, 1338u, 1544u, 1113u, 1247u, 1140u, 1718u,
  827u, 1395u, 966u, 1544u, 1718u, 906u, 398u, 1338u, 1140u, 1663u, 761u, 1009u, 1247u, 0u, 933u, 908u, 1113u,
  1099u, 649u, 691u, 175u, 1394u, 830u, 0u, 810u, 1066u, 370u, 824u, 301u, 867u, 267u, 1076u, 1075u, 1578u,
  662u, 1314u, 354u, 64u, 649u, 1070u, 1100u, 1148u, 884u, 1158u, 254u, 256u, 1086u, 0u, 1034u, 304u, 392u
 };

static const QType JTable_17_2347[]=
 {
  0u, 0u, 4u, 30u, 16u, 2u, 0u, 16u, 11u, 22u, 10u, 40u, 10u, 4u, 26u, 2u, 10u,
  28u, 24u, 24u, 33u, 27u, 6u, 31u, 24u, 32u, 16u, 3u, 29u, 0u, 17u, 32u, 45u, 19u,
  17u, 30u, 31u, 0u, 10u, 5u, 17u, 3u, 18u, 0u, 19u, 40u, 19u, 6u, 28u, 7u, 21u,
  17u, 6u, 0u, 5u, 30u, 28u, 19u, 17u, 31u, 7u, 40u, 3u, 0u, 21u, 19u, 18u, 10u,
  28u, 32u, 29u, 32u, 6u, 24u, 19u, 17u, 3u, 24u, 27u, 24u, 45u, 0u, 16u, 31u, 33u,
  17u, 0u, 17u, 0u, 19u, 7u, 30u, 10u, 3u, 19u, 6u, 21u, 31u, 5u, 18u, 40u, 28u,
  28u, 24u, 27u, 31u, 32u, 3u, 0u, 32u, 19u, 24u, 33u, 6u, 24u, 16u, 29u, 17u, 45u,
  0u, 2u, 4u, 40u, 22u, 16u, 2u, 30u, 0u, 10u, 26u, 10u, 10u, 11u, 0u, 16u, 4u,
  28u, 24u, 27u, 31u, 32u, 3u, 0u, 32u, 19u, 24u, 33u, 6u, 24u, 16u, 29u, 17u, 45u,
  17u, 0u, 17u, 0u, 19u, 7u, 30u, 10u, 3u, 19u, 6u, 21u, 31u, 5u, 18u, 40u, 28u,
  28u, 32u, 29u, 32u, 6u, 24u, 19u, 17u, 3u, 24u, 27u, 24u, 45u, 0u, 16u, 31u, 33u,
  17u, 6u, 0u, 5u, 30u, 28u, 19u, 17u, 31u, 7u, 40u, 3u, 0u, 21u, 19u, 18u, 10u,
  17u, 30u, 31u, 0u, 10u, 5u, 17u, 3u, 18u, 0u, 19u, 40u, 19u, 6u, 28u, 7u, 21u,
  28u, 24u, 24u, 33u, 27u, 6u, 31u, 24u, 32u, 16u, 3u, 29u, 0u, 17u, 32u, 45u, 19u,
  0u, 0u, 4u, 30u, 16u, 2u, 0u, 16u, 11u, 22u, 10u, 40u, 10u, 4u, 26u, 2u, 10u
 };

static const QType JTable_17_3911[]=
 {
  12u, 50u, 26u, 44u, 10u, 16u, 20u, 6u, 24u, 2u, 16u, 26u, 1u, 12u, 38u, 0u, 2u,
  24u, 53u, 43u, 3u, 7u, 30u, 23u, 32u, 6u, 31u, 22u, 0u, 27u, 21u, 26u, 12u, 47u,
  27u, 27u, 12u, 29u, 40u, 18u, 59u, 49u, 36u, 0u, 27u, 32u, 32u, 27u, 14u, 41u, 5u,
  27u, 27u, 0u, 18u, 27u, 14u, 27u, 59u, 12u, 41u, 32u, 49u, 29u, 5u, 32u, 36u, 40u,
  24u, 26u, 0u, 6u, 30u, 43u, 47u, 21u, 22u, 32u, 7u, 53u, 12u, 27u, 31u, 23u, 3u,
  27u, 29u, 59u, 0u, 32u, 41u, 27u, 40u, 49u, 27u, 27u, 5u, 12u, 18u, 36u, 32u, 14u,
  24u, 43u, 7u, 23u, 6u, 22u, 27u, 26u, 47u, 53u, 3u, 30u, 32u, 31u, 0u, 21u, 12u,
  12u, 0u, 12u, 26u, 2u, 6u, 16u, 44u, 50u, 2u, 38u, 1u, 16u, 24u, 20u, 10u, 26u,
  24u, 43u, 7u, 23u, 6u, 22u, 27u, 26u, 47u, 53u, 3u, 30u, 32u, 31u, 0u, 21u, 12u,
  27u, 29u, 59u, 0u, 32u, 41u, 27u, 40u, 49u, 27u, 27u, 5u, 12u, 18u, 36u, 32u, 14u,
  24u, 26u, 0u, 6u, 30u, 43u, 47u, 21u, 22u, 32u, 7u, 53u, 12u, 27u, 31u, 23u, 3u,
  27u, 27u, 0u, 18u, 27u, 14u, 27u, 59u, 12u, 41u, 32u, 49u, 29u, 5u, 32u, 36u, 40u,
  27u, 27u, 12u, 29u, 40u, 18u, 59u, 49u, 36u, 0u, 27u, 32u, 32u, 27u, 14u, 41u, 5u,
  24u, 53u, 43u, 3u, 7u, 30u, 23u, 32u, 6u, 31u, 22u, 0u, 27u, 21u, 26u, 12u, 47u,
  12u, 50u, 26u, 44u, 10u, 16u, 20u, 6u, 24u, 2u, 16u, 26u, 1u, 12u, 38u, 0u, 2u
 };

static const QType JTable_17_11731[]=
 {
  46u, 8u, 23u, 106u, 32u, 34u, 50u, 80u, 50u, 52u, 36u, 58u, 66u, 80u, 42u, 52u, 0u,
  0u, 44u, 9u, 109u, 57u, 19u, 38u, 71u, 53u, 40u, 80u, 49u, 65u, 59u, 46u, 48u, 28u,
  53u, 28u, 28u, 16u, 12u, 71u, 97u, 47u, 39u, 77u, 40u, 72u, 0u, 67u, 37u, 22u, 58u,
  53u, 67u, 77u, 71u, 28u, 37u, 40u, 97u, 28u, 22u, 72u, 47u, 16u, 58u, 0u, 39u, 12u,
  0u, 46u, 49u, 53u, 19u, 9u, 28u, 59u, 80u, 71u, 57u, 44u, 48u, 65u, 40u, 38u, 109u,
  53u, 16u, 97u, 77u, 0u, 22u, 28u, 12u, 47u, 40u, 67u, 58u, 28u, 71u, 39u, 72u, 37u,
  0u, 9u, 57u, 38u, 53u, 80u, 65u, 46u, 28u, 44u, 109u, 19u, 71u, 40u, 49u, 59u, 48u,
  46u, 52u, 80u, 58u, 52u, 80u, 34u, 106u, 8u, 0u, 42u, 66u, 36u, 50u, 50u, 32u, 23u,
  0u, 9u, 57u, 38u, 53u, 80u, 65u, 46u, 28u, 44u, 109u, 19u, 71u, 40u, 49u, 59u, 48u,
  53u, 16u, 97u, 77u, 0u, 22u, 28u, 12u, 47u, 40u, 67u, 58u, 28u, 71u, 39u, 72u, 37u,
  0u, 46u, 49u, 53u, 19u, 9u, 28u, 59u, 80u, 71u, 57u, 44u, 48u, 65u, 40u, 38u, 109u,
  53u, 67u, 77u, 71u, 28u, 37u, 40u, 97u, 28u, 22u, 72u, 47u, 16u, 58u, 0u, 39u, 12u,
  53u, 28u, 28u, 16u, 12u, 71u, 97u, 47u, 39u, 77u, 40u, 72u, 0u, 67u, 37u, 22u, 58u,
  0u, 44u, 9u, 109u, 57u, 19u, 38u, 71u, 53u, 40u, 80u, 49u, 65u, 59u, 46u, 48u, 28u,
  46u, 8u, 23u, 106u, 32u, 34u, 50u, 80u, 50u, 52u, 36u, 58u, 66u, 80u, 42u, 52u, 0u
 };

static const QType JTable_17_111827[]=
 {
  100u, 158u, 344u, 0u, 128u, 58u, 58u, 52u, 176u, 166u, 158u, 154u, 64u, 98u, 216u, 199u, 182u,
  220u, 197u, 310u, 320u, 0u, 172u, 134u, 224u, 220u, 242u, 304u, 266u, 134u, 320u, 226u, 258u, 226u,
  146u, 30u, 132u, 204u, 258u, 88u, 44u, 106u, 38u, 0u, 235u, 6u, 152u, 48u, 10u, 58u, 144u,
  146u, 48u, 0u, 88u, 30u, 10u, 235u, 44u, 132u, 58u, 6u, 106u, 204u, 144u, 152u, 38u, 258u,
  220u, 226u, 266u, 220u, 172u, 310u, 226u, 320u, 304u, 224u, 0u, 197u, 258u, 134u, 242u, 134u, 320u,
  146u, 204u, 44u, 0u, 152u, 58u, 30u, 258u, 106u, 235u, 48u, 144u, 132u, 88u, 38u, 6u, 10u,
  220u, 310u, 0u, 134u, 220u, 304u, 134u, 226u, 226u, 197u, 320u, 172u, 224u, 242u, 266u, 320u, 258u,
  100u, 199u, 98u, 154u, 166u, 52u, 58u, 0u, 158u, 182u, 216u, 64u, 158u, 176u, 58u, 128u, 344u,
  220u, 310u, 0u, 134u, 220u, 304u, 134u, 226u, 226u, 197u, 320u, 172u, 224u, 242u, 266u, 320u, 258u,
  146u, 204u, 44u, 0u, 152u, 58u, 30u, 258u, 106u, 235u, 48u, 144u, 132u, 88u, 38u, 6u, 10u,
  220u, 226u, 266u, 220u, 172u, 310u, 226u, 320u, 304u, 224u, 0u, 197u, 258u, 134u, 242u, 134u, 320u,
  146u, 48u, 0u, 88u, 30u, 10u, 235u, 44u, 132u, 58u, 6u, 106u, 204u, 144u, 152u, 38u, 258u,
  146u, 30u, 132u, 204u, 258u, 88u, 44u, 106u, 38u, 0u, 235u, 6u, 152u, 48u, 10u, 58u, 144u,
  220u, 197u, 310u, 320u, 0u, 172u, 134u, 224u, 220u, 242u, 304u, 266u, 134u, 320u, 226u, 258u, 226u,
  100u, 158u, 344u, 0u, 128u, 58u, 58u, 52u, 176u, 166u, 158u, 154u, 64u, 98u, 216u, 199u, 182u
 };

static const QType JTable_17_355811[]=
 {
  306u, 250u, 330u, 312u, 302u, 380u, 274u, 376u, 138u, 348u, 282u, 672u, 152u, 0u, 280u, 131u, 158u,
  344u, 255u, 166u, 280u, 482u, 0u, 430u, 306u, 312u, 282u, 276u, 434u, 512u, 280u, 250u, 0u, 150u,
  246u, 230u, 336u, 344u, 512u, 432u, 18u, 92u, 306u, 122u, 203u, 280u, 216u, 370u, 0u, 446u, 266u,
  246u, 370u, 122u, 432u, 230u, 0u, 203u, 18u, 336u, 446u, 280u, 92u, 344u, 266u, 216u, 306u, 512u,
  344u, 250u, 434u, 312u, 0u, 166u, 150u, 280u, 276u, 306u, 482u, 255u, 0u, 512u, 282u, 430u, 280u,
  246u, 344u, 18u, 122u, 216u, 446u, 230u, 512u, 92u, 203u, 370u, 266u, 336u, 432u, 306u, 280u, 0u,
  344u, 166u, 482u, 430u, 312u, 276u, 512u, 250u, 150u, 255u, 280u, 0u, 306u, 282u, 434u, 280u, 0u,
  306u, 131u, 0u, 672u, 348u, 376u, 380u, 312u, 250u, 158u, 280u, 152u, 282u, 138u, 274u, 302u, 330u,
  344u, 166u, 482u, 430u, 312u, 276u, 512u, 250u, 150u, 255u, 280u, 0u, 306u, 282u, 434u, 280u, 0u,
  246u, 344u, 18u, 122u, 216u, 446u, 230u, 512u, 92u, 203u, 370u, 266u, 336u, 432u, 306u, 280u, 0u,
  344u, 250u, 434u, 312u, 0u, 166u, 150u, 280u, 276u, 306u, 482u, 255u, 0u, 512u, 282u, 430u, 280u,
  246u, 370u, 122u, 432u, 230u, 0u, 203u, 18u, 336u, 446u, 280u, 92u, 344u, 266u, 216u, 306u, 512u,
  246u, 230u, 336u, 344u, 512u, 432u, 18u, 92u, 306u, 122u, 203u, 280u, 216u, 370u, 0u, 446u, 266u,
  344u, 255u, 166u, 280u, 482u, 0u, 430u, 306u, 312u, 282u, 276u, 434u, 512u, 280u, 250u, 0u, 150u,
  306u, 250u, 330u, 312u, 302u, 380u, 274u, 376u, 138u, 348u, 282u, 672u, 152u, 0u, 280u, 131u, 158u
 };

static const QType JTable_17_520031[]=
 {
  0u, 446u, 424u, 358u, 325u, 480u, 214u, 4u, 146u, 88u, 242u, 538u, 164u, 74u, 344u, 236u, 506u,
  254u, 218u, 503u, 536u, 515u, 252u, 359u, 405u, 491u, 417u, 546u, 535u, 510u, 0u, 642u, 323u, 106u,
  413u, 442u, 585u, 332u, 422u, 444u, 666u, 345u, 0u, 265u, 500u, 241u, 767u, 353u, 514u, 517u, 503u,
  413u, 353u, 265u, 444u, 442u, 514u, 500u, 666u, 585u, 517u, 241u, 345u, 332u, 503u, 767u, 0u, 422u,
  254u, 642u, 535u, 491u, 252u, 503u, 106u, 0u, 546u, 405u, 515u, 218u, 323u, 510u, 417u, 359u, 536u,
  413u, 332u, 666u, 265u, 767u, 517u, 442u, 422u, 345u, 500u, 353u, 503u, 585u, 444u, 0u, 241u, 514u,
  254u, 503u, 515u, 359u, 491u, 546u, 510u, 642u, 106u, 218u, 536u, 252u, 405u, 417u, 535u, 0u, 323u,
  0u, 236u, 74u, 538u, 88u, 4u, 480u, 358u, 446u, 506u, 344u, 164u, 242u, 146u, 214u, 325u, 424u,
  254u, 503u, 515u, 359u, 491u, 546u, 510u, 642u, 106u, 218u, 536u, 252u, 405u, 417u, 535u, 0u, 323u,
  413u, 332u, 666u, 265u, 767u, 517u, 442u, 422u, 345u, 500u, 353u, 503u, 585u, 444u, 0u, 241u, 514u,
  254u, 642u, 535u, 491u, 252u, 503u, 106u, 0u, 546u, 405u, 515u, 218u, 323u, 510u, 417u, 359u, 536u,
  413u, 353u, 265u, 444u, 442u, 514u, 500u, 666u, 585u, 517u, 241u, 345u, 332u, 503u, 767u, 0u, 422u,
  413u, 442u, 585u, 332u, 422u, 444u, 666u, 345u, 0u, 265u, 500u, 241u, 767u, 353u, 514u, 517u, 503u,
  254u, 218u, 503u, 536u, 515u, 252u, 359u, 405u, 491u, 417u, 546u, 535u, 510u, 0u, 642u, 323u, 106u,
  0u, 446u, 424u, 358u, 325u, 480u, 214u, 4u, 146u, 88u, 242u, 538u, 164u, 74u, 344u, 236u, 506u
 };

static const QType JTable_17_782783[]=
 {
  256u, 444u, 574u, 484u, 380u, 785u, 438u, 422u, 356u, 734u, 538u, 944u, 542u, 0u, 558u, 320u, 418u,
  491u, 53u, 271u, 512u, 176u, 237u, 864u, 481u, 288u, 0u, 197u, 181u, 301u, 290u, 104u, 399u, 50u,
  239u, 110u, 466u, 13u, 437u, 143u, 360u, 356u, 145u, 800u, 593u, 50u, 0u, 245u, 125u, 247u, 226u,
  239u, 245u, 800u, 143u, 110u, 125u, 593u, 360u, 466u, 247u, 50u, 356u, 13u, 226u, 0u, 145u, 437u,
  491u, 104u, 181u, 288u, 237u, 271u, 50u, 290u, 197u, 481u, 176u, 53u, 399u, 301u, 0u, 864u, 512u,
  239u, 13u, 360u, 800u, 0u, 247u, 110u, 437u, 356u, 593u, 245u, 226u, 466u, 143u, 145u, 50u, 125u,
  491u, 271u, 176u, 864u, 288u, 197u, 301u, 104u, 50u, 53u, 512u, 237u, 481u, 0u, 181u, 290u, 399u,
  256u, 320u, 0u, 944u, 734u, 422u, 785u, 484u, 444u, 418u, 558u, 542u, 538u, 356u, 438u, 380u, 574u,
  491u, 271u, 176u, 864u, 288u, 197u, 301u, 104u, 50u, 53u, 512u, 237u, 481u, 0u, 181u, 290u, 399u,
  239u, 13u, 360u, 800u, 0u, 247u, 110u, 437u, 356u, 593u, 245u, 226u, 466u, 143u, 145u, 50u, 125u,
  491u, 104u, 181u, 288u, 237u, 271u, 50u, 290u, 197u, 481u, 176u, 53u, 399u, 301u, 0u, 864u, 512u,
  239u, 245u, 800u, 143u, 110u, 125u, 593u, 360u, 466u, 247u, 50u, 356u, 13u, 226u, 0u, 145u, 437u,
  239u, 110u, 466u, 13u, 437u, 143u, 360u, 356u, 145u, 800u, 593u, 50u, 0u, 245u, 125u, 247u, 226u,
  491u, 53u, 271u, 512u, 176u, 237u, 864u, 481u, 288u, 0u, 197u, 181u, 301u, 290u, 104u, 399u, 50u,
  256u, 444u, 574u, 484u, 380u, 785u, 438u, 422u, 356u, 734u, 538u, 944u, 542u, 0u, 558u, 320u, 418u
 };

static const QType JTable_17_903211[]=
 {
  585u, 221u, 541u, 129u, 459u, 229u, 627u, 573u, 771u, 661u, 403u, 319u, 75u, 691u, 555u, 0u, 385u,
  227u, 686u, 165u, 74u, 212u, 273u, 451u, 23u, 324u, 425u, 392u, 744u, 563u, 87u, 573u, 0u, 152u,
  740u, 0u, 375u, 112u, 431u, 159u, 607u, 620u, 506u, 159u, 328u, 657u, 524u, 550u, 647u, 249u, 713u,
  740u, 550u, 159u, 159u, 0u, 647u, 328u, 607u, 375u, 249u, 657u, 620u, 112u, 713u, 524u, 506u, 431u,
  227u, 573u, 744u, 324u, 273u, 165u, 152u, 87u, 392u, 23u, 212u, 686u, 0u, 563u, 425u, 451u, 74u,
  740u, 112u, 607u, 159u, 524u, 249u, 0u, 431u, 620u, 328u, 550u, 713u, 375u, 159u, 506u, 657u, 647u,
  227u, 165u, 212u, 451u, 324u, 392u, 563u, 573u, 152u, 686u, 74u, 273u, 23u, 425u, 744u, 87u, 0u,
  585u, 0u, 691u, 319u, 661u, 573u, 229u, 129u, 221u, 385u, 555u, 75u, 403u, 771u, 627u, 459u, 541u,
  227u, 165u, 212u, 451u, 324u, 392u, 563u, 573u, 152u, 686u, 74u, 273u, 23u, 425u, 744u, 87u, 0u,
  740u, 112u, 607u, 159u, 524u, 249u, 0u, 431u, 620u, 328u, 550u, 713u, 375u, 159u, 506u, 657u, 647u,
  227u, 573u, 744u, 324u, 273u, 165u, 152u, 87u, 392u, 23u, 212u, 686u, 0u, 563u, 425u, 451u, 74u,
  740u, 550u, 159u, 159u, 0u, 647u, 328u, 607u, 375u, 249u, 657u, 620u, 112u, 713u, 524u, 506u, 431u,
  740u, 0u, 375u, 112u, 431u, 159u, 607u, 620u, 506u, 159u, 328u, 657u, 524u, 550u, 647u, 249u, 713u,
  227u, 686u, 165u, 74u, 212u, 273u, 451u, 23u, 324u, 425u, 392u, 744u, 563u, 87u, 573u, 0u, 152u,
  585u, 221u, 541u, 129u, 459u, 229u, 627u, 573u, 771u, 661u, 403u, 319u, 75u, 691u, 555u, 0u, 385u
 };

static const QType JTable_17_2348347[]=
 {
  958u, 722u, 222u, 1250u, 850u, 476u, 602u, 540u, 1048u, 0u, 220u, 40u, 842u, 650u, 1119u, 724u, 344u,
  773u, 1189u, 823u, 657u, 0u, 545u, 1308u, 566u, 421u, 769u, 54u, 586u, 275u, 550u, 114u, 1057u, 546u,
  0u, 905u, 271u, 460u, 401u, 1128u, 620u, 526u, 1242u, 619u, 298u, 857u, 599u, 1118u, 1201u, 295u, 390u,
  0u, 1118u, 619u, 1128u, 905u, 1201u, 298u, 620u, 271u, 295u, 857u, 526u, 460u, 390u, 599u, 1242u, 401u,
  773u, 114u, 586u, 421u, 545u, 823u, 546u, 550u, 54u, 566u, 0u, 1189u, 1057u, 275u, 769u, 1308u, 657u,
  0u, 460u, 620u, 619u, 599u, 295u, 905u, 401u, 526u, 298u, 1118u, 390u, 271u, 1128u, 1242u, 857u, 1201u,
  773u, 823u, 0u, 1308u, 421u, 54u, 275u, 114u, 546u, 1189u, 657u, 545u, 566u, 769u, 586u, 550u, 1057u,
  958u, 724u, 650u, 40u, 0u, 540u, 476u, 1250u, 722u, 344u, 1119u, 842u, 220u, 1048u, 602u, 850u, 222u,
  773u, 823u, 0u, 1308u, 421u, 54u, 275u, 114u, 546u, 1189u, 657u, 545u, 566u, 769u, 586u, 550u, 1057u,
  0u, 460u, 620u, 619u, 599u, 295u, 905u, 401u, 526u, 298u, 1118u, 390u, 271u, 1128u, 1242u, 857u, 1201u,
  773u, 114u, 586u, 421u, 545u, 823u, 546u, 550u, 54u, 566u, 0u, 1189u, 1057u, 275u, 769u, 1308u, 657u,
  0u, 1118u, 619u, 1128u, 905u, 1201u, 298u, 620u, 271u, 295u, 857u, 526u, 460u, 390u, 599u, 1242u, 401u,
  0u, 905u, 271u, 460u, 401u, 1128u, 620u, 526u, 1242u, 619u, 298u, 857u, 599u, 1118u, 1201u, 295u, 390u,
  773u, 1189u, 823u, 657u, 0u, 545u, 1308u, 566u, 421u, 769u, 54u, 586u, 275u, 550u, 114u, 1057u, 546u,
  958u, 722u, 222u, 1250u, 850u, 476u, 602u, 540u, 1048u, 0u, 220u, 40u, 842u, 650u, 1119u, 724u, 344u
 };

static const QType JTable_17_2897311[]=
 {
  1038u, 744u, 674u, 442u, 486u, 880u, 176u, 746u, 113u, 1028u, 1086u, 446u, 0u, 660u, 1260u, 442u, 1508u,
  1226u, 522u, 711u, 359u, 1270u, 258u, 771u, 1320u, 278u, 0u, 602u, 791u, 1427u, 905u, 925u, 1131u, 712u,
  815u, 1160u, 337u, 1369u, 1056u, 582u, 455u, 1065u, 749u, 0u, 702u, 0u, 1178u, 1330u, 1005u, 769u, 755u,
  815u, 1330u, 0u, 582u, 1160u, 1005u, 702u, 455u, 337u, 769u, 0u, 1065u, 1369u, 755u, 1178u, 749u, 1056u,
  1226u, 925u, 791u, 278u, 258u, 711u, 712u, 905u, 602u, 1320u, 1270u, 522u, 1131u, 1427u, 0u, 771u, 359u,
  815u, 1369u, 455u, 0u, 1178u, 769u, 1160u, 1056u, 1065u, 702u, 1330u, 755u, 337u, 582u, 749u, 0u, 1005u,
  1226u, 711u, 1270u, 771u, 278u, 602u, 1427u, 925u, 712u, 522u, 359u, 258u, 1320u, 0u, 791u, 905u, 1131u,
  1038u, 442u, 660u, 446u, 1028u, 746u, 880u, 442u, 744u, 1508u, 1260u, 0u, 1086u, 113u, 176u, 486u, 674u,
  1226u, 711u, 1270u, 771u, 278u, 602u, 1427u, 925u, 712u, 522u, 359u, 258u, 1320u, 0u, 791u, 905u, 1131u,
  815u, 1369u, 455u, 0u, 1178u, 769u, 1160u, 1056u, 1065u, 702u, 1330u, 755u, 337u, 582u, 749u, 0u, 1005u,
  1226u, 925u, 791u, 278u, 258u, 711u, 712u, 905u, 602u, 1320u, 1270u, 522u, 1131u, 1427u, 0u, 771u, 359u,
  815u, 1330u, 0u, 582u, 1160u, 1005u, 702u, 455u, 337u, 769u, 0u, 1065u, 1369u, 755u, 1178u, 749u, 1056u,
  815u, 1160u, 337u, 1369u, 1056u, 582u, 455u, 1065u, 749u, 0u, 702u, 0u, 1178u, 1330u, 1005u, 769u, 755u,
  1226u, 522u, 711u, 359u, 1270u, 258u, 771u, 1320u, 278u, 0u, 602u, 791u, 1427u, 905u, 925u, 1131u, 712u,
  1038u, 744u, 674u, 442u, 486u, 880u, 176u, 746u, 113u, 1028u, 1086u, 446u, 0u, 660u, 1260u, 442u, 1508u
 };

static const QType JTable_17_17160991[]=
 {
  2550u, 1686u, 1868u, 1214u, 150u, 284u, 1856u, 1449u, 2370u, 686u, 0u, 920u, 2550u, 1268u, 604u, 3808u, 1114u,
  2836u, 2552u, 3016u, 1763u, 2675u, 3661u, 2155u, 1883u, 4018u, 1870u, 3602u, 1862u, 3585u, 2028u, 0u, 1315u, 2675u,
  836u, 0u, 2257u, 3691u, 1357u, 1230u, 1692u, 2781u, 935u, 3148u, 559u, 2027u, 2517u, 1549u, 1670u, 576u, 816u,
  836u, 1549u, 3148u, 1230u, 0u, 1670u, 559u, 1692u, 2257u, 576u, 2027u, 2781u, 3691u, 816u, 2517u, 935u, 1357u,
  2836u, 0u, 1862u, 4018u, 3661u, 3016u, 2675u, 2028u, 3602u, 1883u, 2675u, 2552u, 1315u, 3585u, 1870u, 2155u, 1763u,
  836u, 3691u, 1692u, 3148u, 2517u, 576u, 0u, 1357u, 2781u, 559u, 1549u, 816u, 2257u, 1230u, 935u, 2027u, 1670u,
  2836u, 3016u, 2675u, 2155u, 4018u, 3602u, 3585u, 0u, 2675u, 2552u, 1763u, 3661u, 1883u, 1870u, 1862u, 2028u, 1315u,
  2550u, 3808u, 1268u, 920u, 686u, 1449u, 284u, 1214u, 1686u, 1114u, 604u, 2550u, 0u, 2370u, 1856u, 150u, 1868u,
  2836u, 3016u, 2675u, 2155u, 4018u, 3602u, 3585u, 0u, 2675u, 2552u, 1763u, 3661u, 1883u, 1870u, 1862u, 2028u, 1315u,
  836u, 3691u, 1692u, 3148u, 2517u, 576u, 0u, 1357u, 2781u, 559u, 1549u, 816u, 2257u, 1230u, 935u, 2027u, 1670u,
  2836u, 0u, 1862u, 4018u, 3661u, 3016u, 2675u, 2028u, 3602u, 1883u, 2675u, 2552u, 1315u, 3585u, 1870u, 2155u, 1763u,
  836u, 1549u, 3148u, 1230u, 0u, 1670u, 559u, 1692u, 2257u, 576u, 2027u, 2781u, 3691u, 816u, 2517u, 935u, 1357u,
  836u, 0u, 2257u, 3691u, 1357u, 1230u, 1692u, 2781u, 935u, 3148u, 559u, 2027u, 2517u, 1549u, 1670u, 576u, 816u,
  2836u, 2552u, 3016u, 1763u, 2675u, 3661u, 2155u, 1883u, 4018u, 1870u, 3602u, 1862u, 3585u, 2028u, 0u, 1315u, 2675u,
  2550u, 1686u, 1868u, 1214u, 150u, 284u, 1856u, 1449u, 2370u, 686u, 0u, 920u, 2550u, 1268u, 604u, 3808u, 1114u
 };

static const TestSet::JTable JSet_17[]=
 {
  { 103u , 5u , JTable_17_103 },
  { 239u , 5u , JTable_17_239 },
  { 443u , 5u , JTable_17_443 },
  { 1123u , 5u , JTable_17_1123 },
  { 1327u , 5u , JTable_17_1327 },
  { 1871u , 5u , JTable_17_1871 },
  { 3571u , 5u , JTable_17_3571 },
  { 9283u , 5u , JTable_17_9283 },
  { 46411u , 5u , JTable_17_46411 },
  { 72931u , 5u , JTable_17_72931 },
  { 102103u , 5u , JTable_17_102103 },
  { 647u , 6u , JTable_17_647 },
  { 4523u , 6u , JTable_17_4523 },
  { 13567u , 6u , JTable_17_13567 },
  { 21319u , 6u , JTable_17_21319 },
  { 35531u , 6u , JTable_17_35531 },
  { 58787u , 6u , JTable_17_58787 },
  { 106591u , 6u , JTable_17_106591 },
  { 461891u , 6u , JTable_17_461891 },
  { 1939939u , 6u , JTable_17_1939939 },
  { 3233231u , 6u , JTable_17_3233231 },
  { 2347u , 7u , JTable_17_2347 },
  { 3911u , 7u , JTable_17_3911 },
  { 11731u , 7u , JTable_17_11731 },
  { 111827u , 7u , JTable_17_111827 },
  { 355811u , 7u , JTable_17_355811 },
  { 520031u , 7u , JTable_17_520031 },
  { 782783u , 7u , JTable_17_782783 },
  { 903211u , 7u , JTable_17_903211 },
  { 2348347u , 7u , JTable_17_2348347 },
  { 2897311u , 7u , JTable_17_2897311 },
  { 17160991u , 7u , JTable_17_17160991 }
 };

static const QType JTable_19_191[]=
 {
  6u, 10u, 14u, 10u, 8u, 8u, 6u, 9u, 12u, 6u, 6u, 12u, 8u, 4u, 8u, 6u, 10u, 0u, 8u,
  2u, 4u, 6u, 3u, 3u, 9u, 12u, 9u, 7u, 4u, 5u, 10u, 5u, 3u, 10u, 0u, 8u, 6u, 7u,
  10u, 6u, 6u, 5u, 8u, 2u, 6u, 8u, 9u, 1u, 6u, 5u, 2u, 7u, 7u, 0u, 7u, 5u, 13u,
  10u, 0u, 5u, 8u, 5u, 13u, 7u, 6u, 6u, 6u, 5u, 7u, 1u, 2u, 6u, 7u, 2u, 9u, 8u,
  10u, 5u, 6u, 1u, 2u, 0u, 13u, 6u, 2u, 9u, 5u, 7u, 5u, 6u, 8u, 8u, 6u, 7u, 7u,
  2u, 8u, 3u, 5u, 9u, 3u, 4u, 6u, 10u, 10u, 7u, 9u, 6u, 7u, 0u, 5u, 4u, 12u, 3u,
  4u, 9u, 2u, 2u, 0u, 5u, 0u, 9u, 8u, 0u, 6u, 9u, 8u, 6u, 2u, 6u, 5u, 5u, 8u,
  2u, 6u, 3u, 12u, 7u, 5u, 5u, 10u, 8u, 7u, 4u, 3u, 9u, 9u, 4u, 10u, 3u, 0u, 6u,
  6u, 0u, 6u, 4u, 12u, 6u, 9u, 8u, 10u, 10u, 8u, 10u, 8u, 8u, 6u, 12u, 6u, 8u, 14u,
  2u, 6u, 3u, 12u, 7u, 5u, 5u, 10u, 8u, 7u, 4u, 3u, 9u, 9u, 4u, 10u, 3u, 0u, 6u,
  4u, 9u, 2u, 2u, 0u, 5u, 0u, 9u, 8u, 0u, 6u, 9u, 8u, 6u, 2u, 6u, 5u, 5u, 8u,
  2u, 8u, 3u, 5u, 9u, 3u, 4u, 6u, 10u, 10u, 7u, 9u, 6u, 7u, 0u, 5u, 4u, 12u, 3u,
  10u, 5u, 6u, 1u, 2u, 0u, 13u, 6u, 2u, 9u, 5u, 7u, 5u, 6u, 8u, 8u, 6u, 7u, 7u,
  10u, 0u, 5u, 8u, 5u, 13u, 7u, 6u, 6u, 6u, 5u, 7u, 1u, 2u, 6u, 7u, 2u, 9u, 8u,
  10u, 6u, 6u, 5u, 8u, 2u, 6u, 8u, 9u, 1u, 6u, 5u, 2u, 7u, 7u, 0u, 7u, 5u, 13u,
  2u, 4u, 6u, 3u, 3u, 9u, 12u, 9u, 7u, 4u, 5u, 10u, 5u, 3u, 10u, 0u, 8u, 6u, 7u,
  6u, 10u, 14u, 10u, 8u, 8u, 6u, 9u, 12u, 6u, 6u, 12u, 8u, 4u, 8u, 6u, 10u, 0u, 8u
 };

static const QType JTable_19_419[]=
 {
  12u, 12u, 6u, 12u, 10u, 14u, 12u, 10u, 8u, 18u, 8u, 4u, 14u, 16u, 10u, 14u, 2u, 7u, 0u,
  11u, 15u, 9u, 9u, 9u, 0u, 2u, 19u, 7u, 11u, 5u, 13u, 11u, 10u, 15u, 7u, 8u, 12u, 16u,
  7u, 18u, 10u, 10u, 8u, 14u, 2u, 13u, 5u, 0u, 6u, 6u, 14u, 16u, 5u, 7u, 9u, 12u, 8u,
  7u, 7u, 6u, 13u, 10u, 8u, 5u, 6u, 2u, 10u, 12u, 16u, 0u, 14u, 18u, 9u, 14u, 5u, 8u,
  7u, 10u, 2u, 0u, 14u, 7u, 8u, 10u, 14u, 5u, 6u, 5u, 12u, 18u, 8u, 13u, 6u, 16u, 9u,
  11u, 8u, 10u, 5u, 19u, 9u, 15u, 12u, 15u, 13u, 7u, 0u, 9u, 16u, 7u, 11u, 11u, 2u, 9u,
  0u, 17u, 12u, 12u, 11u, 5u, 11u, 17u, 6u, 11u, 12u, 17u, 6u, 12u, 12u, 12u, 5u, 5u, 6u,
  11u, 9u, 9u, 2u, 7u, 5u, 11u, 15u, 8u, 16u, 15u, 9u, 0u, 19u, 11u, 13u, 10u, 7u, 12u,
  12u, 7u, 14u, 16u, 4u, 18u, 10u, 14u, 12u, 12u, 0u, 2u, 10u, 14u, 8u, 8u, 12u, 10u, 6u,
  11u, 9u, 9u, 2u, 7u, 5u, 11u, 15u, 8u, 16u, 15u, 9u, 0u, 19u, 11u, 13u, 10u, 7u, 12u,
  0u, 17u, 12u, 12u, 11u, 5u, 11u, 17u, 6u, 11u, 12u, 17u, 6u, 12u, 12u, 12u, 5u, 5u, 6u,
  11u, 8u, 10u, 5u, 19u, 9u, 15u, 12u, 15u, 13u, 7u, 0u, 9u, 16u, 7u, 11u, 11u, 2u, 9u,
  7u, 10u, 2u, 0u, 14u, 7u, 8u, 10u, 14u, 5u, 6u, 5u, 12u, 18u, 8u, 13u, 6u, 16u, 9u,
  7u, 7u, 6u, 13u, 10u, 8u, 5u, 6u, 2u, 10u, 12u, 16u, 0u, 14u, 18u, 9u, 14u, 5u, 8u,
  7u, 18u, 10u, 10u, 8u, 14u, 2u, 13u, 5u, 0u, 6u, 6u, 14u, 16u, 5u, 7u, 9u, 12u, 8u,
  11u, 15u, 9u, 9u, 9u, 0u, 2u, 19u, 7u, 11u, 5u, 13u, 11u, 10u, 15u, 7u, 8u, 12u, 16u,
  12u, 12u, 6u, 12u, 10u, 14u, 12u, 10u, 8u, 18u, 8u, 4u, 14u, 16u, 10u, 14u, 2u, 7u, 0u
 };

static const QType JTable_19_571[]=
 {
  10u, 12u, 14u, 16u, 10u, 0u, 12u, 6u, 18u, 10u, 16u, 14u, 9u, 24u, 18u, 8u, 8u, 16u, 6u,
  14u, 5u, 15u, 0u, 12u, 11u, 13u, 13u, 15u, 6u, 9u, 6u, 1u, 4u, 14u, 6u, 4u, 3u, 19u,
  5u, 12u, 8u, 10u, 2u, 9u, 0u, 5u, 12u, 9u, 17u, 17u, 7u, 6u, 8u, 19u, 9u, 0u, 15u,
  5u, 19u, 17u, 5u, 10u, 15u, 8u, 17u, 0u, 8u, 0u, 6u, 9u, 9u, 12u, 9u, 7u, 12u, 2u,
  5u, 10u, 0u, 9u, 7u, 19u, 15u, 8u, 9u, 12u, 17u, 8u, 0u, 12u, 2u, 5u, 17u, 6u, 9u,
  14u, 4u, 4u, 9u, 13u, 12u, 5u, 3u, 14u, 6u, 15u, 11u, 15u, 19u, 6u, 1u, 6u, 13u, 0u,
  11u, 16u, 8u, 8u, 6u, 2u, 6u, 16u, 2u, 6u, 0u, 16u, 2u, 0u, 8u, 0u, 2u, 2u, 2u,
  14u, 15u, 12u, 13u, 15u, 9u, 1u, 14u, 4u, 19u, 5u, 0u, 11u, 13u, 6u, 6u, 4u, 6u, 3u,
  10u, 16u, 8u, 24u, 14u, 10u, 6u, 0u, 16u, 12u, 6u, 8u, 18u, 9u, 16u, 18u, 12u, 10u, 14u,
  14u, 15u, 12u, 13u, 15u, 9u, 1u, 14u, 4u, 19u, 5u, 0u, 11u, 13u, 6u, 6u, 4u, 6u, 3u,
  11u, 16u, 8u, 8u, 6u, 2u, 6u, 16u, 2u, 6u, 0u, 16u, 2u, 0u, 8u, 0u, 2u, 2u, 2u,
  14u, 4u, 4u, 9u, 13u, 12u, 5u, 3u, 14u, 6u, 15u, 11u, 15u, 19u, 6u, 1u, 6u, 13u, 0u,
  5u, 10u, 0u, 9u, 7u, 19u, 15u, 8u, 9u, 12u, 17u, 8u, 0u, 12u, 2u, 5u, 17u, 6u, 9u,
  5u, 19u, 17u, 5u, 10u, 15u, 8u, 17u, 0u, 8u, 0u, 6u, 9u, 9u, 12u, 9u, 7u, 12u, 2u,
  5u, 12u, 8u, 10u, 2u, 9u, 0u, 5u, 12u, 9u, 17u, 17u, 7u, 6u, 8u, 19u, 9u, 0u, 15u,
  14u, 5u, 15u, 0u, 12u, 11u, 13u, 13u, 15u, 6u, 9u, 6u, 1u, 4u, 14u, 6u, 4u, 3u, 19u,
  10u, 12u, 14u, 16u, 10u, 0u, 12u, 6u, 18u, 10u, 16u, 14u, 9u, 24u, 18u, 8u, 8u, 16u, 6u
 };

static const QType JTable_19_647[]=
 {
  10u, 10u, 20u, 18u, 8u, 20u, 10u, 15u, 24u, 22u, 14u, 8u, 10u, 16u, 0u, 16u, 12u, 18u, 14u,
  4u, 3u, 13u, 2u, 20u, 13u, 0u, 9u, 5u, 15u, 14u, 11u, 13u, 16u, 8u, 3u, 3u, 14u, 4u,
  12u, 0u, 19u, 7u, 9u, 10u, 4u, 3u, 9u, 8u, 20u, 17u, 12u, 4u, 18u, 15u, 10u, 3u, 9u,
  12u, 15u, 17u, 3u, 7u, 9u, 18u, 20u, 4u, 19u, 3u, 4u, 8u, 10u, 0u, 10u, 12u, 9u, 9u,
  12u, 7u, 4u, 8u, 12u, 15u, 9u, 19u, 10u, 9u, 17u, 18u, 3u, 0u, 9u, 3u, 20u, 4u, 10u,
  4u, 3u, 16u, 14u, 9u, 20u, 3u, 14u, 8u, 11u, 5u, 13u, 13u, 4u, 3u, 13u, 15u, 0u, 2u,
  10u, 12u, 12u, 12u, 17u, 17u, 17u, 12u, 0u, 17u, 8u, 12u, 0u, 8u, 12u, 8u, 17u, 17u, 0u,
  4u, 13u, 20u, 0u, 5u, 14u, 13u, 8u, 3u, 4u, 3u, 2u, 13u, 9u, 15u, 11u, 16u, 3u, 14u,
  10u, 18u, 16u, 16u, 8u, 22u, 15u, 20u, 18u, 10u, 14u, 12u, 0u, 10u, 14u, 24u, 10u, 8u, 20u,
  4u, 13u, 20u, 0u, 5u, 14u, 13u, 8u, 3u, 4u, 3u, 2u, 13u, 9u, 15u, 11u, 16u, 3u, 14u,
  10u, 12u, 12u, 12u, 17u, 17u, 17u, 12u, 0u, 17u, 8u, 12u, 0u, 8u, 12u, 8u, 17u, 17u, 0u,
  4u, 3u, 16u, 14u, 9u, 20u, 3u, 14u, 8u, 11u, 5u, 13u, 13u, 4u, 3u, 13u, 15u, 0u, 2u,
  12u, 7u, 4u, 8u, 12u, 15u, 9u, 19u, 10u, 9u, 17u, 18u, 3u, 0u, 9u, 3u, 20u, 4u, 10u,
  12u, 15u, 17u, 3u, 7u, 9u, 18u, 20u, 4u, 19u, 3u, 4u, 8u, 10u, 0u, 10u, 12u, 9u, 9u,
  12u, 0u, 19u, 7u, 9u, 10u, 4u, 3u, 9u, 8u, 20u, 17u, 12u, 4u, 18u, 15u, 10u, 3u, 9u,
  4u, 3u, 13u, 2u, 20u, 13u, 0u, 9u, 5u, 15u, 14u, 11u, 13u, 16u, 8u, 3u, 3u, 14u, 4u,
  10u, 10u, 20u, 18u, 8u, 20u, 10u, 15u, 24u, 22u, 14u, 8u, 10u, 16u, 0u, 16u, 12u, 18u, 14u
 };

static const QType JTable_19_1483[]=
 {
  14u, 4u, 22u, 18u, 24u, 14u, 26u, 2u, 0u, 4u, 24u, 14u, 0u, 16u, 2u, 16u, 12u, 1u, 14u,
  29u, 25u, 22u, 25u, 20u, 29u, 36u, 18u, 7u, 10u, 18u, 17u, 21u, 25u, 15u, 14u, 16u, 32u, 0u,
  25u, 23u, 29u, 20u, 26u, 23u, 32u, 20u, 25u, 26u, 35u, 32u, 29u, 23u, 12u, 0u, 40u, 18u, 17u,
  25u, 0u, 32u, 20u, 20u, 17u, 12u, 35u, 32u, 29u, 18u, 23u, 26u, 23u, 23u, 40u, 29u, 25u, 26u,
  25u, 20u, 32u, 26u, 29u, 0u, 17u, 29u, 23u, 25u, 32u, 12u, 18u, 23u, 26u, 20u, 35u, 23u, 40u,
  29u, 16u, 25u, 18u, 18u, 20u, 25u, 32u, 15u, 17u, 7u, 29u, 22u, 0u, 14u, 21u, 10u, 36u, 25u,
  22u, 27u, 14u, 14u, 15u, 24u, 15u, 27u, 20u, 15u, 0u, 27u, 20u, 0u, 14u, 0u, 24u, 24u, 20u,
  29u, 22u, 20u, 36u, 7u, 18u, 21u, 15u, 16u, 0u, 25u, 25u, 29u, 18u, 10u, 17u, 25u, 14u, 32u,
  14u, 1u, 16u, 16u, 14u, 4u, 2u, 14u, 18u, 4u, 14u, 12u, 2u, 0u, 24u, 0u, 26u, 24u, 22u,
  29u, 22u, 20u, 36u, 7u, 18u, 21u, 15u, 16u, 0u, 25u, 25u, 29u, 18u, 10u, 17u, 25u, 14u, 32u,
  22u, 27u, 14u, 14u, 15u, 24u, 15u, 27u, 20u, 15u, 0u, 27u, 20u, 0u, 14u, 0u, 24u, 24u, 20u,
  29u, 16u, 25u, 18u, 18u, 20u, 25u, 32u, 15u, 17u, 7u, 29u, 22u, 0u, 14u, 21u, 10u, 36u, 25u,
  25u, 20u, 32u, 26u, 29u, 0u, 17u, 29u, 23u, 25u, 32u, 12u, 18u, 23u, 26u, 20u, 35u, 23u, 40u,
  25u, 0u, 32u, 20u, 20u, 17u, 12u, 35u, 32u, 29u, 18u, 23u, 26u, 23u, 23u, 40u, 29u, 25u, 26u,
  25u, 23u, 29u, 20u, 26u, 23u, 32u, 20u, 25u, 26u, 35u, 32u, 29u, 23u, 12u, 0u, 40u, 18u, 17u,
  29u, 25u, 22u, 25u, 20u, 29u, 36u, 18u, 7u, 10u, 18u, 17u, 21u, 25u, 15u, 14u, 16u, 32u, 0u,
  14u, 4u, 22u, 18u, 24u, 14u, 26u, 2u, 0u, 4u, 24u, 14u, 0u, 16u, 2u, 16u, 12u, 1u, 14u
 };

static const QType JTable_19_2927[]=
 {
  14u, 18u, 10u, 36u, 46u, 8u, 32u, 12u, 30u, 14u, 34u, 38u, 22u, 23u, 28u, 0u, 4u, 24u, 24u,
  35u, 0u, 32u, 28u, 13u, 17u, 11u, 42u, 16u, 30u, 25u, 26u, 37u, 43u, 21u, 22u, 3u, 8u, 27u,
  31u, 24u, 24u, 5u, 26u, 25u, 12u, 46u, 16u, 15u, 0u, 15u, 13u, 31u, 0u, 6u, 36u, 29u, 25u,
  31u, 6u, 15u, 46u, 5u, 25u, 0u, 0u, 12u, 24u, 29u, 31u, 15u, 25u, 24u, 36u, 13u, 16u, 26u,
  31u, 5u, 12u, 15u, 13u, 6u, 25u, 24u, 25u, 16u, 15u, 0u, 29u, 24u, 26u, 46u, 0u, 31u, 36u,
  35u, 3u, 43u, 25u, 42u, 13u, 0u, 8u, 21u, 26u, 16u, 17u, 32u, 27u, 22u, 37u, 30u, 11u, 28u,
  0u, 4u, 31u, 31u, 38u, 16u, 38u, 4u, 20u, 38u, 11u, 4u, 20u, 11u, 31u, 11u, 16u, 16u, 20u,
  35u, 32u, 13u, 11u, 16u, 25u, 37u, 21u, 3u, 27u, 0u, 28u, 17u, 42u, 30u, 26u, 43u, 22u, 8u,
  14u, 24u, 0u, 23u, 38u, 14u, 12u, 8u, 36u, 18u, 24u, 4u, 28u, 22u, 34u, 30u, 32u, 46u, 10u,
  35u, 32u, 13u, 11u, 16u, 25u, 37u, 21u, 3u, 27u, 0u, 28u, 17u, 42u, 30u, 26u, 43u, 22u, 8u,
  0u, 4u, 31u, 31u, 38u, 16u, 38u, 4u, 20u, 38u, 11u, 4u, 20u, 11u, 31u, 11u, 16u, 16u, 20u,
  35u, 3u, 43u, 25u, 42u, 13u, 0u, 8u, 21u, 26u, 16u, 17u, 32u, 27u, 22u, 37u, 30u, 11u, 28u,
  31u, 5u, 12u, 15u, 13u, 6u, 25u, 24u, 25u, 16u, 15u, 0u, 29u, 24u, 26u, 46u, 0u, 31u, 36u,
  31u, 6u, 15u, 46u, 5u, 25u, 0u, 0u, 12u, 24u, 29u, 31u, 15u, 25u, 24u, 36u, 13u, 16u, 26u,
  31u, 24u, 24u, 5u, 26u, 25u, 12u, 46u, 16u, 15u, 0u, 15u, 13u, 31u, 0u, 6u, 36u, 29u, 25u,
  35u, 0u, 32u, 28u, 13u, 17u, 11u, 42u, 16u, 30u, 25u, 26u, 37u, 43u, 21u, 22u, 3u, 8u, 27u,
  14u, 18u, 10u, 36u, 46u, 8u, 32u, 12u, 30u, 14u, 34u, 38u, 22u, 23u, 28u, 0u, 4u, 24u, 24u
 };

static const QType JTable_19_4523[]=
 {
  0u, 60u, 34u, 40u, 14u, 36u, 34u, 32u, 42u, 42u, 22u, 36u, 66u, 42u, 31u, 48u, 24u, 22u, 20u,
  27u, 7u, 38u, 29u, 27u, 30u, 34u, 38u, 24u, 18u, 26u, 51u, 39u, 42u, 44u, 0u, 3u, 49u, 5u,
  57u, 31u, 32u, 35u, 31u, 59u, 65u, 25u, 42u, 24u, 38u, 29u, 57u, 40u, 30u, 34u, 34u, 20u, 0u,
  57u, 34u, 29u, 25u, 35u, 0u, 30u, 38u, 65u, 32u, 20u, 40u, 24u, 59u, 31u, 34u, 57u, 42u, 31u,
  57u, 35u, 65u, 24u, 57u, 34u, 0u, 32u, 59u, 42u, 29u, 30u, 20u, 31u, 31u, 25u, 38u, 40u, 34u,
  27u, 3u, 42u, 26u, 38u, 27u, 7u, 49u, 44u, 51u, 24u, 30u, 38u, 5u, 0u, 39u, 18u, 34u, 29u,
  6u, 0u, 4u, 4u, 32u, 24u, 32u, 0u, 15u, 32u, 43u, 0u, 15u, 43u, 4u, 43u, 24u, 24u, 15u,
  27u, 38u, 27u, 34u, 24u, 26u, 39u, 44u, 3u, 5u, 7u, 29u, 30u, 38u, 18u, 51u, 42u, 0u, 49u,
  0u, 22u, 48u, 42u, 36u, 42u, 32u, 36u, 40u, 60u, 20u, 24u, 31u, 66u, 22u, 42u, 34u, 14u, 34u,
  27u, 38u, 27u, 34u, 24u, 26u, 39u, 44u, 3u, 5u, 7u, 29u, 30u, 38u, 18u, 51u, 42u, 0u, 49u,
  6u, 0u, 4u, 4u, 32u, 24u, 32u, 0u, 15u, 32u, 43u, 0u, 15u, 43u, 4u, 43u, 24u, 24u, 15u,
  27u, 3u, 42u, 26u, 38u, 27u, 7u, 49u, 44u, 51u, 24u, 30u, 38u, 5u, 0u, 39u, 18u, 34u, 29u,
  57u, 35u, 65u, 24u, 57u, 34u, 0u, 32u, 59u, 42u, 29u, 30u, 20u, 31u, 31u, 25u, 38u, 40u, 34u,
  57u, 34u, 29u, 25u, 35u, 0u, 30u, 38u, 65u, 32u, 20u, 40u, 24u, 59u, 31u, 34u, 57u, 42u, 31u,
  57u, 31u, 32u, 35u, 31u, 59u, 65u, 25u, 42u, 24u, 38u, 29u, 57u, 40u, 30u, 34u, 34u, 20u, 0u,
  27u, 7u, 38u, 29u, 27u, 30u, 34u, 38u, 24u, 18u, 26u, 51u, 39u, 42u, 44u, 0u, 3u, 49u, 5u,
  0u, 60u, 34u, 40u, 14u, 36u, 34u, 32u, 42u, 42u, 22u, 36u, 66u, 42u, 31u, 48u, 24u, 22u, 20u
 };

static const QType JTable_19_6271[]=
 {
  24u, 0u, 40u, 22u, 56u, 44u, 38u, 4u, 64u, 45u, 14u, 14u, 12u, 30u, 22u, 36u, 42u, 2u, 22u,
  0u, 15u, 25u, 26u, 53u, 21u, 51u, 33u, 38u, 59u, 28u, 22u, 68u, 27u, 25u, 34u, 71u, 34u, 34u,
  47u, 28u, 0u, 36u, 66u, 19u, 60u, 16u, 55u, 59u, 45u, 30u, 23u, 14u, 12u, 41u, 37u, 29u, 28u,
  47u, 41u, 30u, 16u, 36u, 28u, 12u, 45u, 60u, 0u, 29u, 14u, 59u, 19u, 28u, 37u, 23u, 55u, 66u,
  47u, 36u, 60u, 59u, 23u, 41u, 28u, 0u, 19u, 55u, 30u, 12u, 29u, 28u, 66u, 16u, 45u, 14u, 37u,
  0u, 71u, 27u, 28u, 33u, 53u, 15u, 34u, 25u, 22u, 38u, 21u, 25u, 34u, 34u, 68u, 59u, 51u, 26u,
  58u, 36u, 0u, 0u, 36u, 6u, 36u, 36u, 5u, 36u, 5u, 36u, 5u, 5u, 0u, 5u, 6u, 6u, 5u,
  0u, 25u, 53u, 51u, 38u, 28u, 68u, 25u, 71u, 34u, 15u, 26u, 21u, 33u, 59u, 22u, 27u, 34u, 34u,
  24u, 2u, 36u, 30u, 14u, 45u, 4u, 44u, 22u, 0u, 22u, 42u, 22u, 12u, 14u, 64u, 38u, 56u, 40u,
  0u, 25u, 53u, 51u, 38u, 28u, 68u, 25u, 71u, 34u, 15u, 26u, 21u, 33u, 59u, 22u, 27u, 34u, 34u,
  58u, 36u, 0u, 0u, 36u, 6u, 36u, 36u, 5u, 36u, 5u, 36u, 5u, 5u, 0u, 5u, 6u, 6u, 5u,
  0u, 71u, 27u, 28u, 33u, 53u, 15u, 34u, 25u, 22u, 38u, 21u, 25u, 34u, 34u, 68u, 59u, 51u, 26u,
  47u, 36u, 60u, 59u, 23u, 41u, 28u, 0u, 19u, 55u, 30u, 12u, 29u, 28u, 66u, 16u, 45u, 14u, 37u,
  47u, 41u, 30u, 16u, 36u, 28u, 12u, 45u, 60u, 0u, 29u, 14u, 59u, 19u, 28u, 37u, 23u, 55u, 66u,
  47u, 28u, 0u, 36u, 66u, 19u, 60u, 16u, 55u, 59u, 45u, 30u, 23u, 14u, 12u, 41u, 37u, 29u, 28u,
  0u, 15u, 25u, 26u, 53u, 21u, 51u, 33u, 38u, 59u, 28u, 22u, 68u, 27u, 25u, 34u, 71u, 34u, 34u,
  24u, 0u, 40u, 22u, 56u, 44u, 38u, 4u, 64u, 45u, 14u, 14u, 12u, 30u, 22u, 36u, 42u, 2u, 22u
 };

static const QType JTable_19_7411[]=
 {
  53u, 81u, 43u, 61u, 61u, 71u, 65u, 55u, 29u, 39u, 37u, 55u, 63u, 53u, 23u, 71u, 39u, 0u, 69u,
  64u, 40u, 4u, 32u, 27u, 0u, 50u, 25u, 30u, 13u, 55u, 72u, 33u, 30u, 17u, 46u, 38u, 62u, 26u,
  40u, 45u, 22u, 47u, 19u, 28u, 53u, 78u, 0u, 19u, 38u, 40u, 52u, 60u, 54u, 68u, 30u, 62u, 23u,
  40u, 68u, 40u, 78u, 47u, 23u, 54u, 38u, 53u, 22u, 62u, 60u, 19u, 28u, 45u, 30u, 52u, 0u, 19u,
  40u, 47u, 53u, 19u, 52u, 68u, 23u, 22u, 28u, 0u, 40u, 54u, 62u, 45u, 19u, 78u, 38u, 60u, 30u,
  64u, 38u, 30u, 55u, 25u, 27u, 40u, 62u, 17u, 72u, 30u, 0u, 4u, 26u, 46u, 33u, 13u, 50u, 32u,
  0u, 58u, 3u, 3u, 26u, 42u, 26u, 58u, 51u, 26u, 35u, 58u, 51u, 35u, 3u, 35u, 42u, 42u, 51u,
  64u, 4u, 27u, 50u, 30u, 55u, 33u, 17u, 38u, 26u, 40u, 32u, 0u, 25u, 13u, 72u, 30u, 46u, 62u,
  53u, 0u, 71u, 53u, 55u, 39u, 55u, 71u, 61u, 81u, 69u, 39u, 23u, 63u, 37u, 29u, 65u, 61u, 43u,
  64u, 4u, 27u, 50u, 30u, 55u, 33u, 17u, 38u, 26u, 40u, 32u, 0u, 25u, 13u, 72u, 30u, 46u, 62u,
  0u, 58u, 3u, 3u, 26u, 42u, 26u, 58u, 51u, 26u, 35u, 58u, 51u, 35u, 3u, 35u, 42u, 42u, 51u,
  64u, 38u, 30u, 55u, 25u, 27u, 40u, 62u, 17u, 72u, 30u, 0u, 4u, 26u, 46u, 33u, 13u, 50u, 32u,
  40u, 47u, 53u, 19u, 52u, 68u, 23u, 22u, 28u, 0u, 40u, 54u, 62u, 45u, 19u, 78u, 38u, 60u, 30u,
  40u, 68u, 40u, 78u, 47u, 23u, 54u, 38u, 53u, 22u, 62u, 60u, 19u, 28u, 45u, 30u, 52u, 0u, 19u,
  40u, 45u, 22u, 47u, 19u, 28u, 53u, 78u, 0u, 19u, 38u, 40u, 52u, 60u, 54u, 68u, 30u, 62u, 23u,
  64u, 40u, 4u, 32u, 27u, 0u, 50u, 25u, 30u, 13u, 55u, 72u, 33u, 30u, 17u, 46u, 38u, 62u, 26u,
  53u, 81u, 43u, 61u, 61u, 71u, 65u, 55u, 29u, 39u, 37u, 55u, 63u, 53u, 23u, 71u, 39u, 0u, 69u
 };

static const QType JTable_19_8779[]=
 {
  54u, 86u, 62u, 74u, 46u, 48u, 81u, 54u, 60u, 52u, 80u, 56u, 0u, 42u, 70u, 44u, 102u, 60u, 68u,
  28u, 70u, 46u, 67u, 26u, 33u, 12u, 72u, 52u, 39u, 22u, 58u, 51u, 5u, 34u, 40u, 0u, 36u, 11u,
  59u, 26u, 44u, 36u, 0u, 39u, 27u, 52u, 62u, 75u, 26u, 70u, 48u, 11u, 34u, 67u, 54u, 42u, 6u,
  59u, 67u, 70u, 52u, 36u, 6u, 34u, 26u, 27u, 44u, 42u, 11u, 75u, 39u, 26u, 54u, 48u, 62u, 0u,
  59u, 36u, 27u, 75u, 48u, 67u, 6u, 44u, 39u, 62u, 70u, 34u, 42u, 26u, 0u, 52u, 26u, 11u, 54u,
  28u, 0u, 5u, 22u, 72u, 26u, 70u, 36u, 34u, 58u, 52u, 33u, 46u, 11u, 40u, 51u, 39u, 12u, 67u,
  0u, 75u, 58u, 58u, 71u, 55u, 71u, 75u, 30u, 71u, 78u, 75u, 30u, 78u, 58u, 78u, 55u, 55u, 30u,
  28u, 46u, 26u, 12u, 52u, 22u, 51u, 34u, 0u, 11u, 70u, 67u, 33u, 72u, 39u, 58u, 5u, 40u, 36u,
  54u, 60u, 44u, 42u, 56u, 52u, 54u, 48u, 74u, 86u, 68u, 102u, 70u, 0u, 80u, 60u, 81u, 46u, 62u,
  28u, 46u, 26u, 12u, 52u, 22u, 51u, 34u, 0u, 11u, 70u, 67u, 33u, 72u, 39u, 58u, 5u, 40u, 36u,
  0u, 75u, 58u, 58u, 71u, 55u, 71u, 75u, 30u, 71u, 78u, 75u, 30u, 78u, 58u, 78u, 55u, 55u, 30u,
  28u, 0u, 5u, 22u, 72u, 26u, 70u, 36u, 34u, 58u, 52u, 33u, 46u, 11u, 40u, 51u, 39u, 12u, 67u,
  59u, 36u, 27u, 75u, 48u, 67u, 6u, 44u, 39u, 62u, 70u, 34u, 42u, 26u, 0u, 52u, 26u, 11u, 54u,
  59u, 67u, 70u, 52u, 36u, 6u, 34u, 26u, 27u, 44u, 42u, 11u, 75u, 39u, 26u, 54u, 48u, 62u, 0u,
  59u, 26u, 44u, 36u, 0u, 39u, 27u, 52u, 62u, 75u, 26u, 70u, 48u, 11u, 34u, 67u, 54u, 42u, 6u,
  28u, 70u, 46u, 67u, 26u, 33u, 12u, 72u, 52u, 39u, 22u, 58u, 51u, 5u, 34u, 40u, 0u, 36u, 11u,
  54u, 86u, 62u, 74u, 46u, 48u, 81u, 54u, 60u, 52u, 80u, 56u, 0u, 42u, 70u, 44u, 102u, 60u, 68u
 };

static const QType JTable_19_13567[]=
 {
  0u, 90u, 16u, 56u, 54u, 68u, 106u, 90u, 72u, 54u, 54u, 60u, 64u, 68u, 53u, 18u, 58u, 94u, 64u,
  40u, 27u, 41u, 47u, 70u, 21u, 6u, 39u, 75u, 0u, 76u, 8u, 3u, 17u, 31u, 54u, 30u, 76u, 79u,
  46u, 73u, 29u, 77u, 48u, 99u, 38u, 0u, 22u, 33u, 11u, 71u, 48u, 12u, 24u, 77u, 33u, 54u, 21u,
  46u, 77u, 71u, 0u, 77u, 21u, 24u, 11u, 38u, 29u, 54u, 12u, 33u, 99u, 73u, 33u, 48u, 22u, 48u,
  46u, 77u, 38u, 33u, 48u, 77u, 21u, 29u, 99u, 22u, 71u, 24u, 54u, 73u, 48u, 0u, 11u, 12u, 33u,
  40u, 30u, 17u, 76u, 39u, 70u, 27u, 76u, 31u, 8u, 75u, 21u, 41u, 79u, 54u, 3u, 0u, 6u, 47u,
  0u, 4u, 23u, 23u, 82u, 26u, 82u, 4u, 14u, 82u, 47u, 4u, 14u, 47u, 23u, 47u, 26u, 26u, 14u,
  40u, 41u, 70u, 6u, 75u, 76u, 3u, 31u, 30u, 79u, 27u, 47u, 21u, 39u, 0u, 8u, 17u, 54u, 76u,
  0u, 94u, 18u, 68u, 60u, 54u, 90u, 68u, 56u, 90u, 64u, 58u, 53u, 64u, 54u, 72u, 106u, 54u, 16u,
  40u, 41u, 70u, 6u, 75u, 76u, 3u, 31u, 30u, 79u, 27u, 47u, 21u, 39u, 0u, 8u, 17u, 54u, 76u,
  0u, 4u, 23u, 23u, 82u, 26u, 82u, 4u, 14u, 82u, 47u, 4u, 14u, 47u, 23u, 47u, 26u, 26u, 14u,
  40u, 30u, 17u, 76u, 39u, 70u, 27u, 76u, 31u, 8u, 75u, 21u, 41u, 79u, 54u, 3u, 0u, 6u, 47u,
  46u, 77u, 38u, 33u, 48u, 77u, 21u, 29u, 99u, 22u, 71u, 24u, 54u, 73u, 48u, 0u, 11u, 12u, 33u,
  46u, 77u, 71u, 0u, 77u, 21u, 24u, 11u, 38u, 29u, 54u, 12u, 33u, 99u, 73u, 33u, 48u, 22u, 48u,
  46u, 73u, 29u, 77u, 48u, 99u, 38u, 0u, 22u, 33u, 11u, 71u, 48u, 12u, 24u, 77u, 33u, 54u, 21u,
  40u, 27u, 41u, 47u, 70u, 21u, 6u, 39u, 75u, 0u, 76u, 8u, 3u, 17u, 31u, 54u, 30u, 76u, 79u,
  0u, 90u, 16u, 56u, 54u, 68u, 106u, 90u, 72u, 54u, 54u, 60u, 64u, 68u, 53u, 18u, 58u, 94u, 64u
 };

static const QType JTable_19_17291[]=
 {
  72u, 0u, 38u, 56u, 84u, 50u, 130u, 71u, 48u, 88u, 54u, 22u, 68u, 50u, 78u, 4u, 46u, 76u, 66u,
  97u, 80u, 60u, 63u, 97u, 62u, 52u, 59u, 30u, 112u, 0u, 59u, 90u, 69u, 17u, 38u, 26u, 37u, 91u,
  81u, 53u, 28u, 108u, 32u, 59u, 67u, 24u, 0u, 61u, 38u, 47u, 75u, 105u, 70u, 67u, 5u, 86u, 76u,
  81u, 67u, 47u, 24u, 108u, 76u, 70u, 38u, 67u, 28u, 86u, 105u, 61u, 59u, 53u, 5u, 75u, 0u, 32u,
  81u, 108u, 67u, 61u, 75u, 67u, 76u, 28u, 59u, 0u, 47u, 70u, 86u, 53u, 32u, 24u, 38u, 105u, 5u,
  97u, 26u, 69u, 0u, 59u, 97u, 80u, 37u, 17u, 59u, 30u, 62u, 60u, 91u, 38u, 90u, 112u, 52u, 63u,
  114u, 0u, 5u, 5u, 12u, 34u, 12u, 0u, 62u, 12u, 45u, 0u, 62u, 45u, 5u, 45u, 34u, 34u, 62u,
  97u, 60u, 97u, 52u, 30u, 0u, 90u, 17u, 26u, 91u, 80u, 63u, 62u, 59u, 112u, 59u, 69u, 38u, 37u,
  72u, 76u, 4u, 50u, 22u, 88u, 71u, 50u, 56u, 0u, 66u, 46u, 78u, 68u, 54u, 48u, 130u, 84u, 38u,
  97u, 60u, 97u, 52u, 30u, 0u, 90u, 17u, 26u, 91u, 80u, 63u, 62u, 59u, 112u, 59u, 69u, 38u, 37u,
  114u, 0u, 5u, 5u, 12u, 34u, 12u, 0u, 62u, 12u, 45u, 0u, 62u, 45u, 5u, 45u, 34u, 34u, 62u,
  97u, 26u, 69u, 0u, 59u, 97u, 80u, 37u, 17u, 59u, 30u, 62u, 60u, 91u, 38u, 90u, 112u, 52u, 63u,
  81u, 108u, 67u, 61u, 75u, 67u, 76u, 28u, 59u, 0u, 47u, 70u, 86u, 53u, 32u, 24u, 38u, 105u, 5u,
  81u, 67u, 47u, 24u, 108u, 76u, 70u, 38u, 67u, 28u, 86u, 105u, 61u, 59u, 53u, 5u, 75u, 0u, 32u,
  81u, 53u, 28u, 108u, 32u, 59u, 67u, 24u, 0u, 61u, 38u, 47u, 75u, 105u, 70u, 67u, 5u, 86u, 76u,
  97u, 80u, 60u, 63u, 97u, 62u, 52u, 59u, 30u, 112u, 0u, 59u, 90u, 69u, 17u, 38u, 26u, 37u, 91u,
  72u, 0u, 38u, 56u, 84u, 50u, 130u, 71u, 48u, 88u, 54u, 22u, 68u, 50u, 78u, 4u, 46u, 76u, 66u
 };

static const QType JTable_19_21319[]=
 {
  54u, 76u, 58u, 0u, 20u, 74u, 48u, 76u, 38u, 28u, 148u, 71u, 90u, 34u, 88u, 50u, 42u, 84u, 98u,
  74u, 13u, 33u, 23u, 83u, 42u, 67u, 109u, 0u, 50u, 36u, 75u, 116u, 67u, 31u, 102u, 92u, 76u, 31u,
  68u, 38u, 49u, 86u, 111u, 41u, 63u, 24u, 76u, 49u, 58u, 0u, 56u, 40u, 55u, 156u, 53u, 63u, 91u,
  68u, 156u, 0u, 24u, 86u, 91u, 55u, 58u, 63u, 49u, 63u, 40u, 49u, 41u, 38u, 53u, 56u, 76u, 111u,
  68u, 86u, 63u, 49u, 56u, 156u, 91u, 49u, 41u, 76u, 0u, 55u, 63u, 38u, 111u, 24u, 58u, 40u, 53u,
  74u, 92u, 67u, 36u, 109u, 83u, 13u, 76u, 31u, 75u, 0u, 42u, 33u, 31u, 102u, 116u, 50u, 67u, 23u,
  0u, 103u, 128u, 128u, 91u, 64u, 91u, 103u, 70u, 91u, 44u, 103u, 70u, 44u, 128u, 44u, 64u, 64u, 70u,
  74u, 33u, 83u, 67u, 0u, 36u, 116u, 31u, 92u, 31u, 13u, 23u, 42u, 109u, 50u, 75u, 67u, 102u, 76u,
  54u, 84u, 50u, 34u, 71u, 28u, 76u, 74u, 0u, 76u, 98u, 42u, 88u, 90u, 148u, 38u, 48u, 20u, 58u,
  74u, 33u, 83u, 67u, 0u, 36u, 116u, 31u, 92u, 31u, 13u, 23u, 42u, 109u, 50u, 75u, 67u, 102u, 76u,
  0u, 103u, 128u, 128u, 91u, 64u, 91u, 103u, 70u, 91u, 44u, 103u, 70u, 44u, 128u, 44u, 64u, 64u, 70u,
  74u, 92u, 67u, 36u, 109u, 83u, 13u, 76u, 31u, 75u, 0u, 42u, 33u, 31u, 102u, 116u, 50u, 67u, 23u,
  68u, 86u, 63u, 49u, 56u, 156u, 91u, 49u, 41u, 76u, 0u, 55u, 63u, 38u, 111u, 24u, 58u, 40u, 53u,
  68u, 156u, 0u, 24u, 86u, 91u, 55u, 58u, 63u, 49u, 63u, 40u, 49u, 41u, 38u, 53u, 56u, 76u, 111u,
  68u, 38u, 49u, 86u, 111u, 41u, 63u, 24u, 76u, 49u, 58u, 0u, 56u, 40u, 55u, 156u, 53u, 63u, 91u,
  74u, 13u, 33u, 23u, 83u, 42u, 67u, 109u, 0u, 50u, 36u, 75u, 116u, 67u, 31u, 102u, 92u, 76u, 31u,
  54u, 76u, 58u, 0u, 20u, 74u, 48u, 76u, 38u, 28u, 148u, 71u, 90u, 34u, 88u, 50u, 42u, 84u, 98u
 };

static const QType JTable_19_35531[]=
 {
  84u, 190u, 88u, 96u, 54u, 74u, 32u, 86u, 32u, 108u, 124u, 38u, 50u, 77u, 0u, 120u, 106u, 110u, 50u,
  187u, 106u, 171u, 99u, 95u, 89u, 126u, 70u, 85u, 80u, 0u, 165u, 157u, 124u, 88u, 110u, 132u, 85u, 82u,
  186u, 105u, 94u, 173u, 70u, 118u, 78u, 84u, 67u, 153u, 100u, 126u, 69u, 0u, 74u, 149u, 85u, 111u, 95u,
  186u, 149u, 126u, 84u, 173u, 95u, 74u, 100u, 78u, 94u, 111u, 0u, 153u, 118u, 105u, 85u, 69u, 67u, 70u,
  186u, 173u, 78u, 153u, 69u, 149u, 95u, 94u, 118u, 67u, 126u, 74u, 111u, 105u, 70u, 84u, 100u, 0u, 85u,
  187u, 132u, 124u, 0u, 70u, 95u, 106u, 85u, 88u, 165u, 85u, 89u, 171u, 82u, 110u, 157u, 80u, 126u, 99u,
  107u, 118u, 78u, 78u, 70u, 12u, 70u, 118u, 0u, 70u, 28u, 118u, 0u, 28u, 78u, 28u, 12u, 12u, 0u,
  187u, 171u, 95u, 126u, 85u, 0u, 157u, 88u, 132u, 82u, 106u, 99u, 89u, 70u, 80u, 165u, 124u, 110u, 85u,
  84u, 110u, 120u, 77u, 38u, 108u, 86u, 74u, 96u, 190u, 50u, 106u, 0u, 50u, 124u, 32u, 32u, 54u, 88u,
  187u, 171u, 95u, 126u, 85u, 0u, 157u, 88u, 132u, 82u, 106u, 99u, 89u, 70u, 80u, 165u, 124u, 110u, 85u,
  107u, 118u, 78u, 78u, 70u, 12u, 70u, 118u, 0u, 70u, 28u, 118u, 0u, 28u, 78u, 28u, 12u, 12u, 0u,
  187u, 132u, 124u, 0u, 70u, 95u, 106u, 85u, 88u, 165u, 85u, 89u, 171u, 82u, 110u, 157u, 80u, 126u, 99u,
  186u, 173u, 78u, 153u, 69u, 149u, 95u, 94u, 118u, 67u, 126u, 74u, 111u, 105u, 70u, 84u, 100u, 0u, 85u,
  186u, 149u, 126u, 84u, 173u, 95u, 74u, 100u, 78u, 94u, 111u, 0u, 153u, 118u, 105u, 85u, 69u, 67u, 70u,
  186u, 105u, 94u, 173u, 70u, 118u, 78u, 84u, 67u, 153u, 100u, 126u, 69u, 0u, 74u, 149u, 85u, 111u, 95u,
  187u, 106u, 171u, 99u, 95u, 89u, 126u, 70u, 85u, 80u, 0u, 165u, 157u, 124u, 88u, 110u, 132u, 85u, 82u,
  84u, 190u, 88u, 96u, 54u, 74u, 32u, 86u, 32u, 108u, 124u, 38u, 50u, 77u, 0u, 120u, 106u, 110u, 50u
 };

static const QType JTable_19_38039[]=
 {
  150u, 52u, 66u, 162u, 0u, 94u, 60u, 36u, 24u, 74u, 54u, 82u, 96u, 138u, 96u, 60u, 14u, 104u, 119u,
  187u, 70u, 70u, 37u, 162u, 73u, 32u, 88u, 10u, 97u, 90u, 55u, 79u, 55u, 0u, 58u, 50u, 65u, 89u,
  145u, 143u, 75u, 64u, 0u, 164u, 69u, 34u, 97u, 97u, 63u, 58u, 55u, 122u, 31u, 97u, 72u, 72u, 156u,
  145u, 97u, 58u, 34u, 64u, 156u, 31u, 63u, 69u, 75u, 72u, 122u, 97u, 164u, 143u, 72u, 55u, 97u, 0u,
  145u, 64u, 69u, 97u, 55u, 97u, 156u, 75u, 164u, 97u, 58u, 31u, 72u, 143u, 0u, 34u, 63u, 122u, 72u,
  187u, 50u, 55u, 90u, 88u, 162u, 70u, 65u, 0u, 55u, 10u, 73u, 70u, 89u, 58u, 79u, 97u, 32u, 37u,
  144u, 44u, 0u, 0u, 51u, 111u, 51u, 44u, 52u, 51u, 118u, 44u, 52u, 118u, 0u, 118u, 111u, 111u, 52u,
  187u, 70u, 162u, 32u, 10u, 90u, 79u, 0u, 50u, 89u, 70u, 37u, 73u, 88u, 97u, 55u, 55u, 58u, 65u,
  150u, 104u, 60u, 138u, 82u, 74u, 36u, 94u, 162u, 52u, 119u, 14u, 96u, 96u, 54u, 24u, 60u, 0u, 66u,
  187u, 70u, 162u, 32u, 10u, 90u, 79u, 0u, 50u, 89u, 70u, 37u, 73u, 88u, 97u, 55u, 55u, 58u, 65u,
  144u, 44u, 0u, 0u, 51u, 111u, 51u, 44u, 52u, 51u, 118u, 44u, 52u, 118u, 0u, 118u, 111u, 111u, 52u,
  187u, 50u, 55u, 90u, 88u, 162u, 70u, 65u, 0u, 55u, 10u, 73u, 70u, 89u, 58u, 79u, 97u, 32u, 37u,
  145u, 64u, 69u, 97u, 55u, 97u, 156u, 75u, 164u, 97u, 58u, 31u, 72u, 143u, 0u, 34u, 63u, 122u, 72u,
  145u, 97u, 58u, 34u, 64u, 156u, 31u, 63u, 69u, 75u, 72u, 122u, 97u, 164u, 143u, 72u, 55u, 97u, 0u,
  145u, 143u, 75u, 64u, 0u, 164u, 69u, 34u, 97u, 97u, 63u, 58u, 55u, 122u, 31u, 97u, 72u, 72u, 156u,
  187u, 70u, 70u, 37u, 162u, 73u, 32u, 88u, 10u, 97u, 90u, 55u, 79u, 55u, 0u, 58u, 50u, 65u, 89u,
  150u, 52u, 66u, 162u, 0u, 94u, 60u, 36u, 24u, 74u, 54u, 82u, 96u, 138u, 96u, 60u, 14u, 104u, 119u
 };

static const QType JTable_19_43891[]=
 {
  36u, 174u, 138u, 202u, 82u, 114u, 96u, 72u, 112u, 164u, 76u, 50u, 104u, 114u, 110u, 101u, 0u, 92u, 138u,
  99u, 170u, 98u, 153u, 125u, 32u, 94u, 116u, 7u, 147u, 102u, 84u, 19u, 82u, 93u, 105u, 51u, 0u, 113u,
  39u, 123u, 21u, 0u, 154u, 81u, 133u, 30u, 84u, 87u, 134u, 30u, 12u, 29u, 12u, 51u, 55u, 122u, 56u,
  39u, 51u, 30u, 30u, 0u, 56u, 12u, 134u, 133u, 21u, 122u, 29u, 87u, 81u, 123u, 55u, 12u, 84u, 154u,
  39u, 0u, 133u, 87u, 12u, 51u, 56u, 21u, 81u, 84u, 30u, 12u, 122u, 123u, 154u, 30u, 134u, 29u, 55u,
  99u, 51u, 82u, 102u, 116u, 125u, 170u, 0u, 93u, 84u, 7u, 32u, 98u, 113u, 105u, 19u, 147u, 94u, 153u,
  35u, 55u, 43u, 43u, 0u, 144u, 0u, 55u, 49u, 0u, 1u, 55u, 49u, 1u, 43u, 1u, 144u, 144u, 49u,
  99u, 98u, 125u, 94u, 7u, 102u, 19u, 93u, 51u, 113u, 170u, 153u, 32u, 116u, 147u, 84u, 82u, 105u, 0u,
  36u, 92u, 101u, 114u, 50u, 164u, 72u, 114u, 202u, 174u, 138u, 0u, 110u, 104u, 76u, 112u, 96u, 82u, 138u,
  99u, 98u, 125u, 94u, 7u, 102u, 19u, 93u, 51u, 113u, 170u, 153u, 32u, 116u, 147u, 84u, 82u, 105u, 0u,
  35u, 55u, 43u, 43u, 0u, 144u, 0u, 55u, 49u, 0u, 1u, 55u, 49u, 1u, 43u, 1u, 144u, 144u, 49u,
  99u, 51u, 82u, 102u, 116u, 125u, 170u, 0u, 93u, 84u, 7u, 32u, 98u, 113u, 105u, 19u, 147u, 94u, 153u,
  39u, 0u, 133u, 87u, 12u, 51u, 56u, 21u, 81u, 84u, 30u, 12u, 122u, 123u, 154u, 30u, 134u, 29u, 55u,
  39u, 51u, 30u, 30u, 0u, 56u, 12u, 134u, 133u, 21u, 122u, 29u, 87u, 81u, 123u, 55u, 12u, 84u, 154u,
  39u, 123u, 21u, 0u, 154u, 81u, 133u, 30u, 84u, 87u, 134u, 30u, 12u, 29u, 12u, 51u, 55u, 122u, 56u,
  99u, 170u, 98u, 153u, 125u, 32u, 94u, 116u, 7u, 147u, 102u, 84u, 19u, 82u, 93u, 105u, 51u, 0u, 113u,
  36u, 174u, 138u, 202u, 82u, 114u, 96u, 72u, 112u, 164u, 76u, 50u, 104u, 114u, 110u, 101u, 0u, 92u, 138u
 };

static const QType JTable_19_51871[]=
 {
  100u, 0u, 112u, 152u, 50u, 22u, 102u, 110u, 100u, 14u, 136u, 64u, 88u, 108u, 162u, 122u, 162u, 138u, 5u,
  23u, 40u, 131u, 33u, 124u, 137u, 125u, 67u, 0u, 142u, 110u, 159u, 72u, 128u, 126u, 204u, 97u, 109u, 148u,
  59u, 38u, 142u, 0u, 118u, 179u, 88u, 132u, 120u, 33u, 107u, 119u, 196u, 145u, 85u, 106u, 107u, 162u, 39u,
  59u, 106u, 119u, 132u, 0u, 39u, 85u, 107u, 88u, 142u, 162u, 145u, 33u, 179u, 38u, 107u, 196u, 120u, 118u,
  59u, 0u, 88u, 33u, 196u, 106u, 39u, 142u, 179u, 120u, 119u, 85u, 162u, 38u, 118u, 132u, 107u, 145u, 107u,
  23u, 97u, 128u, 110u, 67u, 124u, 40u, 109u, 126u, 159u, 0u, 137u, 131u, 148u, 204u, 72u, 142u, 125u, 33u,
  10u, 0u, 51u, 51u, 122u, 80u, 122u, 0u, 75u, 122u, 156u, 0u, 75u, 156u, 51u, 156u, 80u, 80u, 75u,
  23u, 131u, 124u, 125u, 0u, 110u, 72u, 126u, 97u, 148u, 40u, 33u, 137u, 67u, 142u, 159u, 128u, 204u, 109u,
  100u, 138u, 122u, 108u, 64u, 14u, 110u, 22u, 152u, 0u, 5u, 162u, 162u, 88u, 136u, 100u, 102u, 50u, 112u,
  23u, 131u, 124u, 125u, 0u, 110u, 72u, 126u, 97u, 148u, 40u, 33u, 137u, 67u, 142u, 159u, 128u, 204u, 109u,
  10u, 0u, 51u, 51u, 122u, 80u, 122u, 0u, 75u, 122u, 156u, 0u, 75u, 156u, 51u, 156u, 80u, 80u, 75u,
  23u, 97u, 128u, 110u, 67u, 124u, 40u, 109u, 126u, 159u, 0u, 137u, 131u, 148u, 204u, 72u, 142u, 125u, 33u,
  59u, 0u, 88u, 33u, 196u, 106u, 39u, 142u, 179u, 120u, 119u, 85u, 162u, 38u, 118u, 132u, 107u, 145u, 107u,
  59u, 106u, 119u, 132u, 0u, 39u, 85u, 107u, 88u, 142u, 162u, 145u, 33u, 179u, 38u, 107u, 196u, 120u, 118u,
  59u, 38u, 142u, 0u, 118u, 179u, 88u, 132u, 120u, 33u, 107u, 119u, 196u, 145u, 85u, 106u, 107u, 162u, 39u,
  23u, 40u, 131u, 33u, 124u, 137u, 125u, 67u, 0u, 142u, 110u, 159u, 72u, 128u, 126u, 204u, 97u, 109u, 148u,
  100u, 0u, 112u, 152u, 50u, 22u, 102u, 110u, 100u, 14u, 136u, 64u, 88u, 108u, 162u, 122u, 162u, 138u, 5u
 };

static const QType JTable_19_58787[]=
 {
  0u, 124u, 36u, 172u, 124u, 66u, 48u, 16u, 114u, 174u, 92u, 66u, 202u, 146u, 86u, 150u, 118u, 57u, 108u,
  209u, 44u, 75u, 176u, 66u, 0u, 57u, 35u, 141u, 112u, 202u, 74u, 87u, 97u, 156u, 117u, 98u, 123u, 87u,
  184u, 122u, 131u, 47u, 129u, 68u, 142u, 134u, 87u, 61u, 49u, 224u, 61u, 0u, 78u, 34u, 41u, 116u, 77u,
  184u, 34u, 224u, 134u, 47u, 77u, 78u, 49u, 142u, 131u, 116u, 0u, 61u, 68u, 122u, 41u, 61u, 87u, 129u,
  184u, 47u, 142u, 61u, 61u, 34u, 77u, 131u, 68u, 87u, 224u, 78u, 116u, 122u, 129u, 134u, 49u, 0u, 41u,
  209u, 98u, 97u, 202u, 35u, 66u, 44u, 123u, 156u, 74u, 141u, 0u, 75u, 87u, 117u, 87u, 112u, 57u, 176u,
  0u, 26u, 66u, 66u, 105u, 141u, 105u, 26u, 172u, 105u, 142u, 26u, 172u, 142u, 66u, 142u, 141u, 141u, 172u,
  209u, 75u, 66u, 57u, 141u, 202u, 87u, 156u, 98u, 87u, 44u, 176u, 0u, 35u, 112u, 74u, 97u, 117u, 123u,
  0u, 57u, 150u, 146u, 66u, 174u, 16u, 66u, 172u, 124u, 108u, 118u, 86u, 202u, 92u, 114u, 48u, 124u, 36u,
  209u, 75u, 66u, 57u, 141u, 202u, 87u, 156u, 98u, 87u, 44u, 176u, 0u, 35u, 112u, 74u, 97u, 117u, 123u,
  0u, 26u, 66u, 66u, 105u, 141u, 105u, 26u, 172u, 105u, 142u, 26u, 172u, 142u, 66u, 142u, 141u, 141u, 172u,
  209u, 98u, 97u, 202u, 35u, 66u, 44u, 123u, 156u, 74u, 141u, 0u, 75u, 87u, 117u, 87u, 112u, 57u, 176u,
  184u, 47u, 142u, 61u, 61u, 34u, 77u, 131u, 68u, 87u, 224u, 78u, 116u, 122u, 129u, 134u, 49u, 0u, 41u,
  184u, 34u, 224u, 134u, 47u, 77u, 78u, 49u, 142u, 131u, 116u, 0u, 61u, 68u, 122u, 41u, 61u, 87u, 129u,
  184u, 122u, 131u, 47u, 129u, 68u, 142u, 134u, 87u, 61u, 49u, 224u, 61u, 0u, 78u, 34u, 41u, 116u, 77u,
  209u, 44u, 75u, 176u, 66u, 0u, 57u, 35u, 141u, 112u, 202u, 74u, 87u, 97u, 156u, 117u, 98u, 123u, 87u,
  0u, 124u, 36u, 172u, 124u, 66u, 48u, 16u, 114u, 174u, 92u, 66u, 202u, 146u, 86u, 150u, 118u, 57u, 108u
 };

static const QType JTable_19_106591[]=
 {
  163u, 242u, 102u, 120u, 196u, 164u, 310u, 82u, 86u, 110u, 200u, 84u, 216u, 188u, 74u, 118u, 46u, 120u, 0u,
  0u, 198u, 190u, 277u, 89u, 173u, 172u, 94u, 238u, 51u, 57u, 64u, 63u, 140u, 233u, 91u, 141u, 194u, 137u,
  291u, 0u, 61u, 96u, 194u, 138u, 43u, 160u, 193u, 150u, 270u, 233u, 109u, 129u, 136u, 78u, 108u, 175u, 95u,
  291u, 78u, 233u, 160u, 96u, 95u, 136u, 270u, 43u, 61u, 175u, 129u, 150u, 138u, 0u, 108u, 109u, 193u, 194u,
  291u, 96u, 43u, 150u, 109u, 78u, 95u, 61u, 138u, 193u, 233u, 136u, 175u, 0u, 194u, 160u, 270u, 129u, 108u,
  0u, 141u, 140u, 57u, 94u, 89u, 198u, 194u, 233u, 64u, 238u, 173u, 190u, 137u, 91u, 63u, 51u, 172u, 277u,
  65u, 53u, 217u, 217u, 0u, 76u, 0u, 53u, 173u, 0u, 143u, 53u, 173u, 143u, 217u, 143u, 76u, 76u, 173u,
  0u, 190u, 89u, 172u, 238u, 57u, 63u, 233u, 141u, 137u, 198u, 277u, 173u, 94u, 51u, 64u, 140u, 91u, 194u,
  163u, 120u, 118u, 188u, 84u, 110u, 82u, 164u, 120u, 242u, 0u, 46u, 74u, 216u, 200u, 86u, 310u, 196u, 102u,
  0u, 190u, 89u, 172u, 238u, 57u, 63u, 233u, 141u, 137u, 198u, 277u, 173u, 94u, 51u, 64u, 140u, 91u, 194u,
  65u, 53u, 217u, 217u, 0u, 76u, 0u, 53u, 173u, 0u, 143u, 53u, 173u, 143u, 217u, 143u, 76u, 76u, 173u,
  0u, 141u, 140u, 57u, 94u, 89u, 198u, 194u, 233u, 64u, 238u, 173u, 190u, 137u, 91u, 63u, 51u, 172u, 277u,
  291u, 96u, 43u, 150u, 109u, 78u, 95u, 61u, 138u, 193u, 233u, 136u, 175u, 0u, 194u, 160u, 270u, 129u, 108u,
  291u, 78u, 233u, 160u, 96u, 95u, 136u, 270u, 43u, 61u, 175u, 129u, 150u, 138u, 0u, 108u, 109u, 193u, 194u,
  291u, 0u, 61u, 96u, 194u, 138u, 43u, 160u, 193u, 150u, 270u, 233u, 109u, 129u, 136u, 78u, 108u, 175u, 95u,
  0u, 198u, 190u, 277u, 89u, 173u, 172u, 94u, 238u, 51u, 57u, 64u, 63u, 140u, 233u, 91u, 141u, 194u, 137u,
  163u, 242u, 102u, 120u, 196u, 164u, 310u, 82u, 86u, 110u, 200u, 84u, 216u, 188u, 74u, 118u, 46u, 120u, 0u
 };

static const QType JTable_19_461891[]=
 {
  438u, 608u, 454u, 356u, 444u, 396u, 430u, 66u, 408u, 321u, 182u, 312u, 344u, 566u, 466u, 342u, 0u, 566u, 368u,
  397u, 569u, 482u, 573u, 250u, 0u, 572u, 426u, 399u, 266u, 476u, 169u, 405u, 171u, 218u, 429u, 254u, 314u, 431u,
  368u, 475u, 483u, 469u, 415u, 264u, 73u, 532u, 192u, 520u, 371u, 215u, 146u, 279u, 452u, 228u, 0u, 445u, 323u,
  368u, 228u, 215u, 532u, 469u, 323u, 452u, 371u, 73u, 483u, 445u, 279u, 520u, 264u, 475u, 0u, 146u, 192u, 415u,
  368u, 469u, 73u, 520u, 146u, 228u, 323u, 483u, 264u, 192u, 215u, 452u, 445u, 475u, 415u, 532u, 371u, 279u, 0u,
  397u, 254u, 171u, 476u, 426u, 250u, 569u, 314u, 218u, 169u, 399u, 0u, 482u, 431u, 429u, 405u, 266u, 572u, 573u,
  346u, 233u, 390u, 390u, 497u, 354u, 497u, 233u, 0u, 497u, 266u, 233u, 0u, 266u, 390u, 266u, 354u, 354u, 0u,
  397u, 482u, 250u, 572u, 399u, 476u, 405u, 218u, 254u, 431u, 569u, 573u, 0u, 426u, 266u, 169u, 171u, 429u, 314u,
  438u, 566u, 342u, 566u, 312u, 321u, 66u, 396u, 356u, 608u, 368u, 0u, 466u, 344u, 182u, 408u, 430u, 444u, 454u,
  397u, 482u, 250u, 572u, 399u, 476u, 405u, 218u, 254u, 431u, 569u, 573u, 0u, 426u, 266u, 169u, 171u, 429u, 314u,
  346u, 233u, 390u, 390u, 497u, 354u, 497u, 233u, 0u, 497u, 266u, 233u, 0u, 266u, 390u, 266u, 354u, 354u, 0u,
  397u, 254u, 171u, 476u, 426u, 250u, 569u, 314u, 218u, 169u, 399u, 0u, 482u, 431u, 429u, 405u, 266u, 572u, 573u,
  368u, 469u, 73u, 520u, 146u, 228u, 323u, 483u, 264u, 192u, 215u, 452u, 445u, 475u, 415u, 532u, 371u, 279u, 0u,
  368u, 228u, 215u, 532u, 469u, 323u, 452u, 371u, 73u, 483u, 445u, 279u, 520u, 264u, 475u, 0u, 146u, 192u, 415u,
  368u, 475u, 483u, 469u, 415u, 264u, 73u, 532u, 192u, 520u, 371u, 215u, 146u, 279u, 452u, 228u, 0u, 445u, 323u,
  397u, 569u, 482u, 573u, 250u, 0u, 572u, 426u, 399u, 266u, 476u, 169u, 405u, 171u, 218u, 429u, 254u, 314u, 431u,
  438u, 608u, 454u, 356u, 444u, 396u, 430u, 66u, 408u, 321u, 182u, 312u, 344u, 566u, 466u, 342u, 0u, 566u, 368u
 };

static const QType JTable_19_1939939[]=
 {
  706u, 0u, 1236u, 558u, 680u, 560u, 544u, 910u, 900u, 486u, 874u, 798u, 912u, 318u, 826u, 1176u, 1174u, 1073u, 1088u,
  227u, 967u, 1025u, 814u, 727u, 805u, 161u, 130u, 724u, 644u, 617u, 486u, 0u, 781u, 826u, 133u, 602u, 282u, 897u,
  713u, 930u, 1158u, 935u, 752u, 1194u, 1122u, 1095u, 1237u, 1243u, 1046u, 1529u, 1215u, 833u, 1167u, 0u, 1078u, 1233u, 1260u,
  713u, 0u, 1529u, 1095u, 935u, 1260u, 1167u, 1046u, 1122u, 1158u, 1233u, 833u, 1243u, 1194u, 930u, 1078u, 1215u, 1237u, 752u,
  713u, 935u, 1122u, 1243u, 1215u, 0u, 1260u, 1158u, 1194u, 1237u, 1529u, 1167u, 1233u, 930u, 752u, 1095u, 1046u, 833u, 1078u,
  227u, 602u, 781u, 617u, 130u, 727u, 967u, 282u, 826u, 486u, 724u, 805u, 1025u, 897u, 133u, 0u, 644u, 161u, 814u,
  787u, 572u, 717u, 717u, 965u, 0u, 965u, 572u, 897u, 965u, 513u, 572u, 897u, 513u, 717u, 513u, 0u, 0u, 897u,
  227u, 1025u, 727u, 161u, 724u, 617u, 0u, 826u, 602u, 897u, 967u, 814u, 805u, 130u, 644u, 486u, 781u, 133u, 282u,
  706u, 1073u, 1176u, 318u, 798u, 486u, 910u, 560u, 558u, 0u, 1088u, 1174u, 826u, 912u, 874u, 900u, 544u, 680u, 1236u,
  227u, 1025u, 727u, 161u, 724u, 617u, 0u, 826u, 602u, 897u, 967u, 814u, 805u, 130u, 644u, 486u, 781u, 133u, 282u,
  787u, 572u, 717u, 717u, 965u, 0u, 965u, 572u, 897u, 965u, 513u, 572u, 897u, 513u, 717u, 513u, 0u, 0u, 897u,
  227u, 602u, 781u, 617u, 130u, 727u, 967u, 282u, 826u, 486u, 724u, 805u, 1025u, 897u, 133u, 0u, 644u, 161u, 814u,
  713u, 935u, 1122u, 1243u, 1215u, 0u, 1260u, 1158u, 1194u, 1237u, 1529u, 1167u, 1233u, 930u, 752u, 1095u, 1046u, 833u, 1078u,
  713u, 0u, 1529u, 1095u, 935u, 1260u, 1167u, 1046u, 1122u, 1158u, 1233u, 833u, 1243u, 1194u, 930u, 1078u, 1215u, 1237u, 752u,
  713u, 930u, 1158u, 935u, 752u, 1194u, 1122u, 1095u, 1237u, 1243u, 1046u, 1529u, 1215u, 833u, 1167u, 0u, 1078u, 1233u, 1260u,
  227u, 967u, 1025u, 814u, 727u, 805u, 161u, 130u, 724u, 644u, 617u, 486u, 0u, 781u, 826u, 133u, 602u, 282u, 897u,
  706u, 0u, 1236u, 558u, 680u, 560u, 544u, 910u, 900u, 486u, 874u, 798u, 912u, 318u, 826u, 1176u, 1174u, 1073u, 1088u
 };

static const QType JTable_19_3233231[]=
 {
  1450u, 1666u, 528u, 902u, 1010u, 670u, 354u, 999u, 700u, 664u, 820u, 720u, 422u, 1276u, 520u, 802u, 834u, 0u, 1432u,
  973u, 720u, 669u, 1461u, 1123u, 985u, 990u, 1245u, 1608u, 1520u, 1663u, 1584u, 0u, 1509u, 970u, 895u, 930u, 1409u, 1196u,
  1398u, 379u, 958u, 1235u, 1340u, 847u, 0u, 1491u, 722u, 969u, 1479u, 1596u, 1361u, 1525u, 788u, 931u, 1052u, 1220u, 1000u,
  1398u, 931u, 1596u, 1491u, 1235u, 1000u, 788u, 1479u, 0u, 958u, 1220u, 1525u, 969u, 847u, 379u, 1052u, 1361u, 722u, 1340u,
  1398u, 1235u, 0u, 969u, 1361u, 931u, 1000u, 958u, 847u, 722u, 1596u, 788u, 1220u, 379u, 1340u, 1491u, 1479u, 1525u, 1052u,
  973u, 930u, 1509u, 1663u, 1245u, 1123u, 720u, 1409u, 970u, 1584u, 1608u, 985u, 669u, 1196u, 895u, 0u, 1520u, 990u, 1461u,
  817u, 553u, 204u, 204u, 157u, 1223u, 157u, 553u, 0u, 157u, 301u, 553u, 0u, 301u, 204u, 301u, 1223u, 1223u, 0u,
  973u, 669u, 1123u, 990u, 1608u, 1663u, 0u, 970u, 930u, 1196u, 720u, 1461u, 985u, 1245u, 1520u, 1584u, 1509u, 895u, 1409u,
  1450u, 0u, 802u, 1276u, 720u, 664u, 999u, 670u, 902u, 1666u, 1432u, 834u, 520u, 422u, 820u, 700u, 354u, 1010u, 528u,
  973u, 669u, 1123u, 990u, 1608u, 1663u, 0u, 970u, 930u, 1196u, 720u, 1461u, 985u, 1245u, 1520u, 1584u, 1509u, 895u, 1409u,
  817u, 553u, 204u, 204u, 157u, 1223u, 157u, 553u, 0u, 157u, 301u, 553u, 0u, 301u, 204u, 301u, 1223u, 1223u, 0u,
  973u, 930u, 1509u, 1663u, 1245u, 1123u, 720u, 1409u, 970u, 1584u, 1608u, 985u, 669u, 1196u, 895u, 0u, 1520u, 990u, 1461u,
  1398u, 1235u, 0u, 969u, 1361u, 931u, 1000u, 958u, 847u, 722u, 1596u, 788u, 1220u, 379u, 1340u, 1491u, 1479u, 1525u, 1052u,
  1398u, 931u, 1596u, 1491u, 1235u, 1000u, 788u, 1479u, 0u, 958u, 1220u, 1525u, 969u, 847u, 379u, 1052u, 1361u, 722u, 1340u,
  1398u, 379u, 958u, 1235u, 1340u, 847u, 0u, 1491u, 722u, 969u, 1479u, 1596u, 1361u, 1525u, 788u, 931u, 1052u, 1220u, 1000u,
  973u, 720u, 669u, 1461u, 1123u, 985u, 990u, 1245u, 1608u, 1520u, 1663u, 1584u, 0u, 1509u, 970u, 895u, 930u, 1409u, 1196u,
  1450u, 1666u, 528u, 902u, 1010u, 670u, 354u, 999u, 700u, 664u, 820u, 720u, 422u, 1276u, 520u, 802u, 834u, 0u, 1432u
 };

static const QType JTable_19_28843[]=
 {
  40u, 54u, 52u, 34u, 56u, 70u, 34u, 28u, 150u, 12u, 60u, 62u, 116u, 70u, 0u, 10u, 6u, 7u, 88u,
  52u, 0u, 78u, 32u, 18u, 87u, 111u, 71u, 66u, 50u, 93u, 127u, 79u, 23u, 107u, 65u, 138u, 60u, 129u,
  87u, 55u, 69u, 61u, 94u, 14u, 47u, 57u, 45u, 36u, 124u, 72u, 60u, 110u, 77u, 0u, 98u, 71u, 171u,
  87u, 0u, 72u, 57u, 61u, 171u, 77u, 124u, 47u, 69u, 71u, 110u, 36u, 14u, 55u, 98u, 60u, 45u, 94u,
  87u, 61u, 47u, 36u, 60u, 0u, 171u, 69u, 14u, 45u, 72u, 77u, 71u, 55u, 94u, 57u, 124u, 110u, 98u,
  52u, 138u, 23u, 93u, 71u, 18u, 0u, 60u, 107u, 127u, 66u, 87u, 78u, 129u, 65u, 79u, 50u, 111u, 32u,
  19u, 20u, 17u, 17u, 0u, 93u, 0u, 20u, 101u, 0u, 41u, 20u, 101u, 41u, 17u, 41u, 93u, 93u, 101u,
  52u, 78u, 18u, 111u, 66u, 93u, 79u, 107u, 138u, 129u, 0u, 32u, 87u, 71u, 50u, 127u, 23u, 65u, 60u,
  40u, 7u, 10u, 70u, 62u, 12u, 28u, 70u, 34u, 54u, 88u, 6u, 0u, 116u, 60u, 150u, 34u, 56u, 52u,
  52u, 78u, 18u, 111u, 66u, 93u, 79u, 107u, 138u, 129u, 0u, 32u, 87u, 71u, 50u, 127u, 23u, 65u, 60u,
  19u, 20u, 17u, 17u, 0u, 93u, 0u, 20u, 101u, 0u, 41u, 20u, 101u, 41u, 17u, 41u, 93u, 93u, 101u,
  52u, 138u, 23u, 93u, 71u, 18u, 0u, 60u, 107u, 127u, 66u, 87u, 78u, 129u, 65u, 79u, 50u, 111u, 32u,
  87u, 61u, 47u, 36u, 60u, 0u, 171u, 69u, 14u, 45u, 72u, 77u, 71u, 55u, 94u, 57u, 124u, 110u, 98u,
  87u, 0u, 72u, 57u, 61u, 171u, 77u, 124u, 47u, 69u, 71u, 110u, 36u, 14u, 55u, 98u, 60u, 45u, 94u,
  87u, 55u, 69u, 61u, 94u, 14u, 47u, 57u, 45u, 36u, 124u, 72u, 60u, 110u, 77u, 0u, 98u, 71u, 171u,
  52u, 0u, 78u, 32u, 18u, 87u, 111u, 71u, 66u, 50u, 93u, 127u, 79u, 23u, 107u, 65u, 138u, 60u, 129u,
  40u, 54u, 52u, 34u, 56u, 70u, 34u, 28u, 150u, 12u, 60u, 62u, 116u, 70u, 0u, 10u, 6u, 7u, 88u
 };

static const QType JTable_19_91771[]=
 {
  158u, 126u, 4u, 218u, 94u, 8u, 82u, 136u, 154u, 148u, 178u, 44u, 192u, 82u, 176u, 68u, 0u, 11u, 58u,
  16u, 273u, 98u, 66u, 97u, 75u, 0u, 41u, 115u, 75u, 230u, 116u, 182u, 62u, 89u, 156u, 161u, 147u, 71u,
  131u, 97u, 35u, 73u, 148u, 104u, 0u, 99u, 186u, 58u, 69u, 189u, 86u, 99u, 126u, 24u, 234u, 139u, 268u,
  131u, 24u, 189u, 99u, 73u, 268u, 126u, 69u, 0u, 35u, 139u, 99u, 58u, 104u, 97u, 234u, 86u, 186u, 148u,
  131u, 73u, 0u, 58u, 86u, 24u, 268u, 35u, 104u, 186u, 189u, 126u, 139u, 97u, 148u, 99u, 69u, 99u, 234u,
  16u, 161u, 62u, 230u, 41u, 97u, 273u, 147u, 89u, 116u, 115u, 75u, 98u, 71u, 156u, 182u, 75u, 0u, 66u,
  146u, 146u, 209u, 209u, 52u, 152u, 52u, 146u, 0u, 52u, 133u, 146u, 0u, 133u, 209u, 133u, 152u, 152u, 0u,
  16u, 98u, 97u, 0u, 115u, 230u, 182u, 89u, 161u, 71u, 273u, 66u, 75u, 41u, 75u, 116u, 62u, 156u, 147u,
  158u, 11u, 68u, 82u, 44u, 148u, 136u, 8u, 218u, 126u, 58u, 0u, 176u, 192u, 178u, 154u, 82u, 94u, 4u,
  16u, 98u, 97u, 0u, 115u, 230u, 182u, 89u, 161u, 71u, 273u, 66u, 75u, 41u, 75u, 116u, 62u, 156u, 147u,
  146u, 146u, 209u, 209u, 52u, 152u, 52u, 146u, 0u, 52u, 133u, 146u, 0u, 133u, 209u, 133u, 152u, 152u, 0u,
  16u, 161u, 62u, 230u, 41u, 97u, 273u, 147u, 89u, 116u, 115u, 75u, 98u, 71u, 156u, 182u, 75u, 0u, 66u,
  131u, 73u, 0u, 58u, 86u, 24u, 268u, 35u, 104u, 186u, 189u, 126u, 139u, 97u, 148u, 99u, 69u, 99u, 234u,
  131u, 24u, 189u, 99u, 73u, 268u, 126u, 69u, 0u, 35u, 139u, 99u, 58u, 104u, 97u, 234u, 86u, 186u, 148u,
  131u, 97u, 35u, 73u, 148u, 104u, 0u, 99u, 186u, 58u, 69u, 189u, 86u, 99u, 126u, 24u, 234u, 139u, 268u,
  16u, 273u, 98u, 66u, 97u, 75u, 0u, 41u, 115u, 75u, 230u, 116u, 182u, 62u, 89u, 156u, 161u, 147u, 71u,
  158u, 126u, 4u, 218u, 94u, 8u, 82u, 136u, 154u, 148u, 178u, 44u, 192u, 82u, 176u, 68u, 0u, 11u, 58u
 };

static const QType JTable_19_336491[]=
 {
  210u, 354u, 378u, 322u, 214u, 230u, 156u, 232u, 104u, 252u, 368u, 520u, 0u, 446u, 478u, 329u, 400u, 176u, 226u,
  151u, 98u, 291u, 328u, 298u, 59u, 266u, 152u, 586u, 222u, 184u, 342u, 70u, 0u, 191u, 112u, 201u, 212u, 321u,
  133u, 197u, 236u, 75u, 53u, 70u, 467u, 0u, 88u, 255u, 80u, 75u, 198u, 181u, 463u, 275u, 339u, 91u, 143u,
  133u, 275u, 75u, 0u, 75u, 143u, 463u, 80u, 467u, 236u, 91u, 181u, 255u, 70u, 197u, 339u, 198u, 88u, 53u,
  133u, 75u, 467u, 255u, 198u, 275u, 143u, 236u, 70u, 88u, 75u, 463u, 91u, 197u, 53u, 0u, 80u, 181u, 339u,
  151u, 201u, 0u, 184u, 152u, 298u, 98u, 212u, 191u, 342u, 586u, 59u, 291u, 321u, 112u, 70u, 222u, 266u, 328u,
  223u, 0u, 211u, 211u, 180u, 270u, 180u, 0u, 91u, 180u, 421u, 0u, 91u, 421u, 211u, 421u, 270u, 270u, 91u,
  151u, 291u, 298u, 266u, 586u, 184u, 70u, 191u, 201u, 321u, 98u, 328u, 59u, 152u, 222u, 342u, 0u, 112u, 212u,
  210u, 176u, 329u, 446u, 520u, 252u, 232u, 230u, 322u, 354u, 226u, 400u, 478u, 0u, 368u, 104u, 156u, 214u, 378u,
  151u, 291u, 298u, 266u, 586u, 184u, 70u, 191u, 201u, 321u, 98u, 328u, 59u, 152u, 222u, 342u, 0u, 112u, 212u,
  223u, 0u, 211u, 211u, 180u, 270u, 180u, 0u, 91u, 180u, 421u, 0u, 91u, 421u, 211u, 421u, 270u, 270u, 91u,
  151u, 201u, 0u, 184u, 152u, 298u, 98u, 212u, 191u, 342u, 586u, 59u, 291u, 321u, 112u, 70u, 222u, 266u, 328u,
  133u, 75u, 467u, 255u, 198u, 275u, 143u, 236u, 70u, 88u, 75u, 463u, 91u, 197u, 53u, 0u, 80u, 181u, 339u,
  133u, 275u, 75u, 0u, 75u, 143u, 463u, 80u, 467u, 236u, 91u, 181u, 255u, 70u, 197u, 339u, 198u, 88u, 53u,
  133u, 197u, 236u, 75u, 53u, 70u, 467u, 0u, 88u, 255u, 80u, 75u, 198u, 181u, 463u, 275u, 339u, 91u, 143u,
  151u, 98u, 291u, 328u, 298u, 59u, 266u, 152u, 586u, 222u, 184u, 342u, 70u, 0u, 191u, 112u, 201u, 212u, 321u,
  210u, 354u, 378u, 322u, 214u, 230u, 156u, 232u, 104u, 252u, 368u, 520u, 0u, 446u, 478u, 329u, 400u, 176u, 226u
 };

static const QType JTable_19_520031[]=
 {
  582u, 32u, 226u, 0u, 370u, 116u, 207u, 542u, 464u, 402u, 284u, 130u, 436u, 490u, 246u, 310u, 380u, 204u, 316u,
  175u, 782u, 250u, 472u, 430u, 498u, 428u, 525u, 501u, 296u, 402u, 340u, 536u, 298u, 501u, 437u, 355u, 278u, 0u,
  516u, 540u, 285u, 407u, 493u, 0u, 580u, 214u, 170u, 104u, 281u, 447u, 494u, 192u, 130u, 254u, 358u, 244u, 389u,
  516u, 254u, 447u, 214u, 407u, 389u, 130u, 281u, 580u, 285u, 244u, 192u, 104u, 0u, 540u, 358u, 494u, 170u, 493u,
  516u, 407u, 580u, 104u, 494u, 254u, 389u, 285u, 0u, 170u, 447u, 130u, 244u, 540u, 493u, 214u, 281u, 192u, 358u,
  175u, 355u, 298u, 402u, 525u, 430u, 782u, 278u, 501u, 340u, 501u, 498u, 250u, 0u, 437u, 536u, 296u, 428u, 472u,
  0u, 318u, 255u, 255u, 496u, 256u, 496u, 318u, 51u, 496u, 473u, 318u, 51u, 473u, 255u, 473u, 256u, 256u, 51u,
  175u, 250u, 430u, 428u, 501u, 402u, 536u, 501u, 355u, 0u, 782u, 472u, 498u, 525u, 296u, 340u, 298u, 437u, 278u,
  582u, 204u, 310u, 490u, 130u, 402u, 542u, 116u, 0u, 32u, 316u, 380u, 246u, 436u, 284u, 464u, 207u, 370u, 226u,
  175u, 250u, 430u, 428u, 501u, 402u, 536u, 501u, 355u, 0u, 782u, 472u, 498u, 525u, 296u, 340u, 298u, 437u, 278u,
  0u, 318u, 255u, 255u, 496u, 256u, 496u, 318u, 51u, 496u, 473u, 318u, 51u, 473u, 255u, 473u, 256u, 256u, 51u,
  175u, 355u, 298u, 402u, 525u, 430u, 782u, 278u, 501u, 340u, 501u, 498u, 250u, 0u, 437u, 536u, 296u, 428u, 472u,
  516u, 407u, 580u, 104u, 494u, 254u, 389u, 285u, 0u, 170u, 447u, 130u, 244u, 540u, 493u, 214u, 281u, 192u, 358u,
  516u, 254u, 447u, 214u, 407u, 389u, 130u, 281u, 580u, 285u, 244u, 192u, 104u, 0u, 540u, 358u, 494u, 170u, 493u,
  516u, 540u, 285u, 407u, 493u, 0u, 580u, 214u, 170u, 104u, 281u, 447u, 494u, 192u, 130u, 254u, 358u, 244u, 389u,
  175u, 782u, 250u, 472u, 430u, 498u, 428u, 525u, 501u, 296u, 402u, 340u, 536u, 298u, 501u, 437u, 355u, 278u, 0u,
  582u, 32u, 226u, 0u, 370u, 116u, 207u, 542u, 464u, 402u, 284u, 130u, 436u, 490u, 246u, 310u, 380u, 204u, 316u
 };

static const QType JTable_19_1193011[]=
 {
  462u, 988u, 422u, 270u, 304u, 376u, 356u, 714u, 448u, 526u, 2u, 358u, 216u, 0u, 534u, 148u, 786u, 493u, 196u,
  792u, 957u, 812u, 631u, 0u, 1077u, 545u, 382u, 558u, 506u, 648u, 927u, 803u, 795u, 371u, 656u, 710u, 861u, 850u,
  812u, 818u, 682u, 719u, 777u, 805u, 497u, 0u, 794u, 677u, 632u, 759u, 390u, 713u, 473u, 432u, 331u, 1197u, 670u,
  812u, 432u, 759u, 0u, 719u, 670u, 473u, 632u, 497u, 682u, 1197u, 713u, 677u, 805u, 818u, 331u, 390u, 794u, 777u,
  812u, 719u, 497u, 677u, 390u, 432u, 670u, 682u, 805u, 794u, 759u, 473u, 1197u, 818u, 777u, 0u, 632u, 713u, 331u,
  792u, 710u, 795u, 648u, 382u, 0u, 957u, 861u, 371u, 927u, 558u, 1077u, 812u, 850u, 656u, 803u, 506u, 545u, 631u,
  0u, 914u, 570u, 570u, 846u, 910u, 846u, 914u, 521u, 846u, 957u, 914u, 521u, 957u, 570u, 957u, 910u, 910u, 521u,
  792u, 812u, 0u, 545u, 558u, 648u, 803u, 371u, 710u, 850u, 957u, 631u, 1077u, 382u, 506u, 927u, 795u, 656u, 861u,
  462u, 493u, 148u, 0u, 358u, 526u, 714u, 376u, 270u, 988u, 196u, 786u, 534u, 216u, 2u, 448u, 356u, 304u, 422u,
  792u, 812u, 0u, 545u, 558u, 648u, 803u, 371u, 710u, 850u, 957u, 631u, 1077u, 382u, 506u, 927u, 795u, 656u, 861u,
  0u, 914u, 570u, 570u, 846u, 910u, 846u, 914u, 521u, 846u, 957u, 914u, 521u, 957u, 570u, 957u, 910u, 910u, 521u,
  792u, 710u, 795u, 648u, 382u, 0u, 957u, 861u, 371u, 927u, 558u, 1077u, 812u, 850u, 656u, 803u, 506u, 545u, 631u,
  812u, 719u, 497u, 677u, 390u, 432u, 670u, 682u, 805u, 794u, 759u, 473u, 1197u, 818u, 777u, 0u, 632u, 713u, 331u,
  812u, 432u, 759u, 0u, 719u, 670u, 473u, 632u, 497u, 682u, 1197u, 713u, 677u, 805u, 818u, 331u, 390u, 794u, 777u,
  812u, 818u, 682u, 719u, 777u, 805u, 497u, 0u, 794u, 677u, 632u, 759u, 390u, 713u, 473u, 432u, 331u, 1197u, 670u,
  792u, 957u, 812u, 631u, 0u, 1077u, 545u, 382u, 558u, 506u, 648u, 927u, 803u, 795u, 371u, 656u, 710u, 861u, 850u,
  462u, 988u, 422u, 270u, 304u, 376u, 356u, 714u, 448u, 526u, 2u, 358u, 216u, 0u, 534u, 148u, 786u, 493u, 196u
 };

static const QType JTable_19_2624623[]=
 {
  1054u, 1092u, 940u, 346u, 1344u, 922u, 1279u, 824u, 402u, 848u, 562u, 246u, 648u, 806u, 1248u, 440u, 486u, 762u, 0u,
  927u, 89u, 1469u, 1022u, 925u, 752u, 544u, 1010u, 1391u, 759u, 1024u, 815u, 898u, 0u, 516u, 551u, 897u, 726u, 1169u,
  470u, 85u, 670u, 364u, 853u, 679u, 1427u, 916u, 339u, 384u, 740u, 1005u, 489u, 481u, 900u, 61u, 748u, 1054u, 0u,
  470u, 61u, 1005u, 916u, 364u, 0u, 900u, 740u, 1427u, 670u, 1054u, 481u, 384u, 679u, 85u, 748u, 489u, 339u, 853u,
  470u, 364u, 1427u, 384u, 489u, 61u, 0u, 670u, 679u, 339u, 1005u, 900u, 1054u, 85u, 853u, 916u, 740u, 481u, 748u,
  927u, 897u, 0u, 1024u, 1010u, 925u, 89u, 726u, 516u, 815u, 1391u, 752u, 1469u, 1169u, 551u, 898u, 759u, 544u, 1022u,
  1003u, 189u, 555u, 555u, 959u, 923u, 959u, 189u, 0u, 959u, 396u, 189u, 0u, 396u, 555u, 396u, 923u, 923u, 0u,
  927u, 1469u, 925u, 544u, 1391u, 1024u, 898u, 516u, 897u, 1169u, 89u, 1022u, 752u, 1010u, 759u, 815u, 0u, 551u, 726u,
  1054u, 762u, 440u, 806u, 246u, 848u, 824u, 922u, 346u, 1092u, 0u, 486u, 1248u, 648u, 562u, 402u, 1279u, 1344u, 940u,
  927u, 1469u, 925u, 544u, 1391u, 1024u, 898u, 516u, 897u, 1169u, 89u, 1022u, 752u, 1010u, 759u, 815u, 0u, 551u, 726u,
  1003u, 189u, 555u, 555u, 959u, 923u, 959u, 189u, 0u, 959u, 396u, 189u, 0u, 396u, 555u, 396u, 923u, 923u, 0u,
  927u, 897u, 0u, 1024u, 1010u, 925u, 89u, 726u, 516u, 815u, 1391u, 752u, 1469u, 1169u, 551u, 898u, 759u, 544u, 1022u,
  470u, 364u, 1427u, 384u, 489u, 61u, 0u, 670u, 679u, 339u, 1005u, 900u, 1054u, 85u, 853u, 916u, 740u, 481u, 748u,
  470u, 61u, 1005u, 916u, 364u, 0u, 900u, 740u, 1427u, 670u, 1054u, 481u, 384u, 679u, 85u, 748u, 489u, 339u, 853u,
  470u, 85u, 670u, 364u, 853u, 679u, 1427u, 916u, 339u, 384u, 740u, 1005u, 489u, 481u, 900u, 61u, 748u, 1054u, 0u,
  927u, 89u, 1469u, 1022u, 925u, 752u, 544u, 1010u, 1391u, 759u, 1024u, 815u, 898u, 0u, 516u, 551u, 897u, 726u, 1169u,
  1054u, 1092u, 940u, 346u, 1344u, 922u, 1279u, 824u, 402u, 848u, 562u, 246u, 648u, 806u, 1248u, 440u, 486u, 762u, 0u
 };

static const QType JTable_19_2897311[]=
 {
  146u, 526u, 1101u, 1012u, 0u, 558u, 580u, 838u, 110u, 378u, 392u, 162u, 532u, 770u, 476u, 1628u, 504u, 838u, 620u,
  1110u, 1568u, 800u, 748u, 310u, 1172u, 208u, 482u, 810u, 696u, 326u, 670u, 690u, 0u, 1020u, 374u, 451u, 348u, 262u,
  802u, 56u, 1096u, 0u, 550u, 1016u, 970u, 846u, 1180u, 549u, 262u, 408u, 1056u, 350u, 60u, 78u, 894u, 570u, 732u,
  802u, 78u, 408u, 846u, 0u, 732u, 60u, 262u, 970u, 1096u, 570u, 350u, 549u, 1016u, 56u, 894u, 1056u, 1180u, 550u,
  802u, 0u, 970u, 549u, 1056u, 78u, 732u, 1096u, 1016u, 1180u, 408u, 60u, 570u, 56u, 550u, 846u, 262u, 350u, 894u,
  1110u, 451u, 0u, 326u, 482u, 310u, 1568u, 348u, 1020u, 670u, 810u, 1172u, 800u, 262u, 374u, 690u, 696u, 208u, 748u,
  1363u, 778u, 640u, 640u, 722u, 10u, 722u, 778u, 0u, 722u, 296u, 778u, 0u, 296u, 640u, 296u, 10u, 10u, 0u,
  1110u, 800u, 310u, 208u, 810u, 326u, 690u, 1020u, 451u, 262u, 1568u, 748u, 1172u, 482u, 696u, 670u, 0u, 374u, 348u,
  146u, 838u, 1628u, 770u, 162u, 378u, 838u, 558u, 1012u, 526u, 620u, 504u, 476u, 532u, 392u, 110u, 580u, 0u, 1101u,
  1110u, 800u, 310u, 208u, 810u, 326u, 690u, 1020u, 451u, 262u, 1568u, 748u, 1172u, 482u, 696u, 670u, 0u, 374u, 348u,
  1363u, 778u, 640u, 640u, 722u, 10u, 722u, 778u, 0u, 722u, 296u, 778u, 0u, 296u, 640u, 296u, 10u, 10u, 0u,
  1110u, 451u, 0u, 326u, 482u, 310u, 1568u, 348u, 1020u, 670u, 810u, 1172u, 800u, 262u, 374u, 690u, 696u, 208u, 748u,
  802u, 0u, 970u, 549u, 1056u, 78u, 732u, 1096u, 1016u, 1180u, 408u, 60u, 570u, 56u, 550u, 846u, 262u, 350u, 894u,
  802u, 78u, 408u, 846u, 0u, 732u, 60u, 262u, 970u, 1096u, 570u, 350u, 549u, 1016u, 56u, 894u, 1056u, 1180u, 550u,
  802u, 56u, 1096u, 0u, 550u, 1016u, 970u, 846u, 1180u, 549u, 262u, 408u, 1056u, 350u, 60u, 78u, 894u, 570u, 732u,
  1110u, 1568u, 800u, 748u, 310u, 1172u, 208u, 482u, 810u, 696u, 326u, 670u, 690u, 0u, 1020u, 374u, 451u, 348u, 262u,
  146u, 526u, 1101u, 1012u, 0u, 558u, 580u, 838u, 110u, 378u, 392u, 162u, 532u, 770u, 476u, 1628u, 504u, 838u, 620u
 };

static const QType JTable_19_13123111[]=
 {
  2154u, 2028u, 1744u, 1143u, 2174u, 2554u, 1192u, 3652u, 94u, 0u, 918u, 1748u, 1360u, 1278u, 1626u, 2304u, 1342u, 1676u, 1374u,
  1051u, 2793u, 2220u, 1929u, 1085u, 2584u, 2070u, 2583u, 2760u, 1507u, 2525u, 1569u, 0u, 931u, 1942u, 2674u, 1486u, 866u, 3087u,
  2904u, 2327u, 796u, 1079u, 1915u, 1248u, 2656u, 2075u, 2564u, 1132u, 2534u, 2711u, 1061u, 1331u, 1719u, 370u, 1975u, 0u, 1826u,
  2904u, 370u, 2711u, 2075u, 1079u, 1826u, 1719u, 2534u, 2656u, 796u, 0u, 1331u, 1132u, 1248u, 2327u, 1975u, 1061u, 2564u, 1915u,
  2904u, 1079u, 2656u, 1132u, 1061u, 370u, 1826u, 796u, 1248u, 2564u, 2711u, 1719u, 0u, 2327u, 1915u, 2075u, 2534u, 1331u, 1975u,
  1051u, 1486u, 931u, 2525u, 2583u, 1085u, 2793u, 866u, 1942u, 1569u, 2760u, 2584u, 2220u, 3087u, 2674u, 0u, 1507u, 2070u, 1929u,
  0u, 1612u, 1268u, 1268u, 1659u, 471u, 1659u, 1612u, 130u, 1659u, 2466u, 1612u, 130u, 2466u, 1268u, 2466u, 471u, 471u, 130u,
  1051u, 2220u, 1085u, 2070u, 2760u, 2525u, 0u, 1942u, 1486u, 3087u, 2793u, 1929u, 2584u, 2583u, 1507u, 1569u, 931u, 2674u, 866u,
  2154u, 1676u, 2304u, 1278u, 1748u, 0u, 3652u, 2554u, 1143u, 2028u, 1374u, 1342u, 1626u, 1360u, 918u, 94u, 1192u, 2174u, 1744u,
  1051u, 2220u, 1085u, 2070u, 2760u, 2525u, 0u, 1942u, 1486u, 3087u, 2793u, 1929u, 2584u, 2583u, 1507u, 1569u, 931u, 2674u, 866u,
  0u, 1612u, 1268u, 1268u, 1659u, 471u, 1659u, 1612u, 130u, 1659u, 2466u, 1612u, 130u, 2466u, 1268u, 2466u, 471u, 471u, 130u,
  1051u, 1486u, 931u, 2525u, 2583u, 1085u, 2793u, 866u, 1942u, 1569u, 2760u, 2584u, 2220u, 3087u, 2674u, 0u, 1507u, 2070u, 1929u,
  2904u, 1079u, 2656u, 1132u, 1061u, 370u, 1826u, 796u, 1248u, 2564u, 2711u, 1719u, 0u, 2327u, 1915u, 2075u, 2534u, 1331u, 1975u,
  2904u, 370u, 2711u, 2075u, 1079u, 1826u, 1719u, 2534u, 2656u, 796u, 0u, 1331u, 1132u, 1248u, 2327u, 1975u, 1061u, 2564u, 1915u,
  2904u, 2327u, 796u, 1079u, 1915u, 1248u, 2656u, 2075u, 2564u, 1132u, 2534u, 2711u, 1061u, 1331u, 1719u, 370u, 1975u, 0u, 1826u,
  1051u, 2793u, 2220u, 1929u, 1085u, 2584u, 2070u, 2583u, 2760u, 1507u, 2525u, 1569u, 0u, 931u, 1942u, 2674u, 1486u, 866u, 3087u,
  2154u, 2028u, 1744u, 1143u, 2174u, 2554u, 1192u, 3652u, 94u, 0u, 918u, 1748u, 1360u, 1278u, 1626u, 2304u, 1342u, 1676u, 1374u
 };

static const QType JTable_19_17160991[]=
 {
  1524u, 2240u, 1810u, 114u, 3620u, 1650u, 1336u, 2352u, 2838u, 2766u, 2428u, 0u, 678u, 1078u, 1801u, 1040u, 2556u, 886u, 1506u,
  2961u, 3127u, 2484u, 3986u, 3691u, 3181u, 4050u, 3219u, 1795u, 2871u, 0u, 3711u, 3748u, 2760u, 1829u, 3027u, 3550u, 2684u, 3204u,
  3098u, 2427u, 3435u, 2358u, 1948u, 2929u, 3201u, 419u, 0u, 3012u, 1159u, 3569u, 2234u, 2375u, 1774u, 1934u, 2710u, 2593u, 2030u,
  3098u, 1934u, 3569u, 419u, 2358u, 2030u, 1774u, 1159u, 3201u, 3435u, 2593u, 2375u, 3012u, 2929u, 2427u, 2710u, 2234u, 0u, 1948u,
  3098u, 2358u, 3201u, 3012u, 2234u, 1934u, 2030u, 3435u, 2929u, 0u, 3569u, 1774u, 2593u, 2427u, 1948u, 419u, 1159u, 2375u, 2710u,
  2961u, 3550u, 2760u, 0u, 3219u, 3691u, 3127u, 2684u, 1829u, 3711u, 1795u, 3181u, 2484u, 3204u, 3027u, 3748u, 2871u, 4050u, 3986u,
  0u, 1272u, 2469u, 2469u, 286u, 738u, 286u, 1272u, 2534u, 286u, 2245u, 1272u, 2534u, 2245u, 2469u, 2245u, 738u, 738u, 2534u,
  2961u, 2484u, 3691u, 4050u, 1795u, 0u, 3748u, 1829u, 3550u, 3204u, 3127u, 3986u, 3181u, 3219u, 2871u, 3711u, 2760u, 3027u, 2684u,
  1524u, 886u, 1040u, 1078u, 0u, 2766u, 2352u, 1650u, 114u, 2240u, 1506u, 2556u, 1801u, 678u, 2428u, 2838u, 1336u, 3620u, 1810u,
  2961u, 2484u, 3691u, 4050u, 1795u, 0u, 3748u, 1829u, 3550u, 3204u, 3127u, 3986u, 3181u, 3219u, 2871u, 3711u, 2760u, 3027u, 2684u,
  0u, 1272u, 2469u, 2469u, 286u, 738u, 286u, 1272u, 2534u, 286u, 2245u, 1272u, 2534u, 2245u, 2469u, 2245u, 738u, 738u, 2534u,
  2961u, 3550u, 2760u, 0u, 3219u, 3691u, 3127u, 2684u, 1829u, 3711u, 1795u, 3181u, 2484u, 3204u, 3027u, 3748u, 2871u, 4050u, 3986u,
  3098u, 2358u, 3201u, 3012u, 2234u, 1934u, 2030u, 3435u, 2929u, 0u, 3569u, 1774u, 2593u, 2427u, 1948u, 419u, 1159u, 2375u, 2710u,
  3098u, 1934u, 3569u, 419u, 2358u, 2030u, 1774u, 1159u, 3201u, 3435u, 2593u, 2375u, 3012u, 2929u, 2427u, 2710u, 2234u, 0u, 1948u,
  3098u, 2427u, 3435u, 2358u, 1948u, 2929u, 3201u, 419u, 0u, 3012u, 1159u, 3569u, 2234u, 2375u, 1774u, 1934u, 2710u, 2593u, 2030u,
  2961u, 3127u, 2484u, 3986u, 3691u, 3181u, 4050u, 3219u, 1795u, 2871u, 0u, 3711u, 3748u, 2760u, 1829u, 3027u, 3550u, 2684u, 3204u,
  1524u, 2240u, 1810u, 114u, 3620u, 1650u, 1336u, 2352u, 2838u, 2766u, 2428u, 0u, 678u, 1078u, 1801u, 1040u, 2556u, 886u, 1506u
 };

static const TestSet::JTable JSet_19[]=
 {
  { 191u , 6u , JTable_19_191 },
  { 419u , 6u , JTable_19_419 },
  { 571u , 6u , JTable_19_571 },
  { 647u , 6u , JTable_19_647 },
  { 1483u , 6u , JTable_19_1483 },
  { 2927u , 6u , JTable_19_2927 },
  { 4523u , 6u , JTable_19_4523 },
  { 6271u , 6u , JTable_19_6271 },
  { 7411u , 6u , JTable_19_7411 },
  { 8779u , 6u , JTable_19_8779 },
  { 13567u , 6u , JTable_19_13567 },
  { 17291u , 6u , JTable_19_17291 },
  { 21319u , 6u , JTable_19_21319 },
  { 35531u , 6u , JTable_19_35531 },
  { 38039u , 6u , JTable_19_38039 },
  { 43891u , 6u , JTable_19_43891 },
  { 51871u , 6u , JTable_19_51871 },
  { 58787u , 6u , JTable_19_58787 },
  { 106591u , 6u , JTable_19_106591 },
  { 461891u , 6u , JTable_19_461891 },
  { 1939939u , 6u , JTable_19_1939939 },
  { 3233231u , 6u , JTable_19_3233231 },
  { 28843u , 7u , JTable_19_28843 },
  { 91771u , 7u , JTable_19_91771 },
  { 336491u , 7u , JTable_19_336491 },
  { 520031u , 7u , JTable_19_520031 },
  { 1193011u , 7u , JTable_19_1193011 },
  { 2624623u , 7u , JTable_19_2624623 },
  { 2897311u , 7u , JTable_19_2897311 },
  { 13123111u , 7u , JTable_19_13123111 },
  { 17160991u , 7u , JTable_19_17160991 }
 };

static const QType JTable_23_47[]=
 {
  0u, 4u, 4u, 2u, 0u, 2u, 0u, 2u, 2u, 0u, 3u, 2u, 0u, 4u, 2u, 4u, 2u, 4u, 2u, 2u, 2u, 2u, 0u,
  3u, 1u, 1u, 3u, 4u, 0u, 1u, 2u, 2u, 3u, 6u, 1u, 4u, 1u, 1u, 2u, 1u, 2u, 1u, 2u, 0u, 1u, 3u,
  2u, 1u, 2u, 0u, 1u, 3u, 1u, 1u, 3u, 3u, 2u, 2u, 3u, 2u, 3u, 0u, 1u, 3u, 6u, 1u, 4u, 1u, 0u,
  2u, 5u, 2u, 4u, 1u, 3u, 1u, 3u, 2u, 1u, 2u, 0u, 0u, 1u, 3u, 3u, 1u, 1u, 5u, 2u, 0u, 2u, 1u,
  2u, 1u, 0u, 2u, 1u, 0u, 0u, 6u, 3u, 2u, 1u, 2u, 1u, 3u, 2u, 3u, 3u, 1u, 4u, 1u, 3u, 3u, 1u,
  2u, 1u, 2u, 0u, 1u, 0u, 5u, 3u, 1u, 1u, 1u, 2u, 2u, 1u, 2u, 3u, 5u, 1u, 4u, 3u, 0u, 3u, 2u,
  3u, 0u, 2u, 1u, 1u, 2u, 0u, 1u, 3u, 2u, 1u, 1u, 6u, 2u, 4u, 1u, 1u, 1u, 2u, 4u, 3u, 1u, 3u,
  2u, 0u, 1u, 3u, 3u, 0u, 6u, 1u, 1u, 1u, 1u, 2u, 2u, 1u, 1u, 0u, 2u, 3u, 3u, 2u, 3u, 3u, 4u,
  2u, 5u, 1u, 2u, 4u, 2u, 1u, 0u, 1u, 5u, 2u, 3u, 1u, 1u, 1u, 1u, 0u, 3u, 2u, 0u, 3u, 2u, 3u,
  3u, 1u, 4u, 1u, 2u, 6u, 4u, 1u, 1u, 1u, 0u, 3u, 1u, 3u, 0u, 2u, 3u, 1u, 1u, 2u, 2u, 2u, 1u,
  0u, 2u, 2u, 4u, 4u, 4u, 2u, 0u, 2u, 2u, 2u, 4u, 0u, 2u, 2u, 2u, 2u, 0u, 3u, 2u, 0u, 0u, 4u,
  3u, 1u, 4u, 1u, 2u, 6u, 4u, 1u, 1u, 1u, 0u, 3u, 1u, 3u, 0u, 2u, 3u, 1u, 1u, 2u, 2u, 2u, 1u,
  2u, 5u, 1u, 2u, 4u, 2u, 1u, 0u, 1u, 5u, 2u, 3u, 1u, 1u, 1u, 1u, 0u, 3u, 2u, 0u, 3u, 2u, 3u,
  2u, 0u, 1u, 3u, 3u, 0u, 6u, 1u, 1u, 1u, 1u, 2u, 2u, 1u, 1u, 0u, 2u, 3u, 3u, 2u, 3u, 3u, 4u,
  3u, 0u, 2u, 1u, 1u, 2u, 0u, 1u, 3u, 2u, 1u, 1u, 6u, 2u, 4u, 1u, 1u, 1u, 2u, 4u, 3u, 1u, 3u,
  2u, 1u, 2u, 0u, 1u, 0u, 5u, 3u, 1u, 1u, 1u, 2u, 2u, 1u, 2u, 3u, 5u, 1u, 4u, 3u, 0u, 3u, 2u,
  2u, 1u, 0u, 2u, 1u, 0u, 0u, 6u, 3u, 2u, 1u, 2u, 1u, 3u, 2u, 3u, 3u, 1u, 4u, 1u, 3u, 3u, 1u,
  2u, 5u, 2u, 4u, 1u, 3u, 1u, 3u, 2u, 1u, 2u, 0u, 0u, 1u, 3u, 3u, 1u, 1u, 5u, 2u, 0u, 2u, 1u,
  2u, 1u, 2u, 0u, 1u, 3u, 1u, 1u, 3u, 3u, 2u, 2u, 3u, 2u, 3u, 0u, 1u, 3u, 6u, 1u, 4u, 1u, 0u,
  3u, 1u, 1u, 3u, 4u, 0u, 1u, 2u, 2u, 3u, 6u, 1u, 4u, 1u, 1u, 2u, 1u, 2u, 1u, 2u, 0u, 1u, 3u,
  0u, 4u, 4u, 2u, 0u, 2u, 0u, 2u, 2u, 0u, 3u, 2u, 0u, 4u, 2u, 4u, 2u, 4u, 2u, 2u, 2u, 2u, 0u
 };

static const QType JTable_23_139[]=
 {
  8u, 2u, 4u, 0u, 4u, 4u, 6u, 10u, 4u, 4u, 6u, 2u, 4u, 4u, 2u, 6u, 6u, 2u, 4u, 6u, 2u, 1u, 0u,
  8u, 4u, 3u, 6u, 7u, 5u, 6u, 6u, 0u, 8u, 6u, 9u, 5u, 3u, 4u, 7u, 5u, 6u, 7u, 8u, 12u, 4u, 8u,
  9u, 6u, 2u, 7u, 8u, 8u, 0u, 5u, 3u, 5u, 9u, 5u, 4u, 6u, 1u, 4u, 3u, 3u, 3u, 7u, 5u, 7u, 4u,
  4u, 11u, 6u, 4u, 4u, 7u, 7u, 3u, 8u, 4u, 6u, 1u, 5u, 8u, 6u, 6u, 3u, 0u, 6u, 2u, 3u, 5u, 5u,
  9u, 7u, 4u, 5u, 5u, 7u, 4u, 3u, 1u, 9u, 0u, 2u, 7u, 3u, 6u, 5u, 8u, 6u, 5u, 3u, 4u, 3u, 8u,
  4u, 4u, 8u, 5u, 3u, 3u, 11u, 7u, 4u, 8u, 0u, 5u, 6u, 7u, 6u, 6u, 6u, 5u, 4u, 3u, 1u, 6u, 2u,
  8u, 12u, 6u, 4u, 9u, 0u, 5u, 3u, 8u, 8u, 5u, 3u, 6u, 6u, 7u, 4u, 4u, 7u, 7u, 5u, 8u, 6u, 6u,
  9u, 7u, 0u, 5u, 4u, 4u, 3u, 7u, 6u, 8u, 5u, 9u, 6u, 3u, 7u, 4u, 2u, 8u, 3u, 5u, 1u, 3u, 5u,
  4u, 6u, 8u, 8u, 4u, 5u, 3u, 1u, 7u, 11u, 2u, 6u, 4u, 4u, 5u, 0u, 5u, 3u, 6u, 3u, 6u, 6u, 7u,
  8u, 3u, 7u, 6u, 0u, 6u, 5u, 4u, 5u, 7u, 12u, 8u, 4u, 6u, 5u, 6u, 8u, 9u, 3u, 7u, 6u, 8u, 4u,
  8u, 1u, 6u, 2u, 6u, 4u, 2u, 4u, 10u, 4u, 0u, 2u, 0u, 2u, 4u, 6u, 2u, 4u, 6u, 4u, 6u, 4u, 4u,
  8u, 3u, 7u, 6u, 0u, 6u, 5u, 4u, 5u, 7u, 12u, 8u, 4u, 6u, 5u, 6u, 8u, 9u, 3u, 7u, 6u, 8u, 4u,
  4u, 6u, 8u, 8u, 4u, 5u, 3u, 1u, 7u, 11u, 2u, 6u, 4u, 4u, 5u, 0u, 5u, 3u, 6u, 3u, 6u, 6u, 7u,
  9u, 7u, 0u, 5u, 4u, 4u, 3u, 7u, 6u, 8u, 5u, 9u, 6u, 3u, 7u, 4u, 2u, 8u, 3u, 5u, 1u, 3u, 5u,
  8u, 12u, 6u, 4u, 9u, 0u, 5u, 3u, 8u, 8u, 5u, 3u, 6u, 6u, 7u, 4u, 4u, 7u, 7u, 5u, 8u, 6u, 6u,
  4u, 4u, 8u, 5u, 3u, 3u, 11u, 7u, 4u, 8u, 0u, 5u, 6u, 7u, 6u, 6u, 6u, 5u, 4u, 3u, 1u, 6u, 2u,
  9u, 7u, 4u, 5u, 5u, 7u, 4u, 3u, 1u, 9u, 0u, 2u, 7u, 3u, 6u, 5u, 8u, 6u, 5u, 3u, 4u, 3u, 8u,
  4u, 11u, 6u, 4u, 4u, 7u, 7u, 3u, 8u, 4u, 6u, 1u, 5u, 8u, 6u, 6u, 3u, 0u, 6u, 2u, 3u, 5u, 5u,
  9u, 6u, 2u, 7u, 8u, 8u, 0u, 5u, 3u, 5u, 9u, 5u, 4u, 6u, 1u, 4u, 3u, 3u, 3u, 7u, 5u, 7u, 4u,
  8u, 4u, 3u, 6u, 7u, 5u, 6u, 6u, 0u, 8u, 6u, 9u, 5u, 3u, 4u, 7u, 5u, 6u, 7u, 8u, 12u, 4u, 8u,
  8u, 2u, 4u, 0u, 4u, 4u, 6u, 10u, 4u, 4u, 6u, 2u, 4u, 4u, 2u, 6u, 6u, 2u, 4u, 6u, 2u, 1u, 0u
 };

static const QType JTable_23_599[]=
 {
  0u, 10u, 10u, 14u, 10u, 9u, 8u, 20u, 0u, 8u, 14u, 4u, 4u, 2u, 10u, 2u, 6u, 4u, 8u, 16u, 12u, 6u, 6u,
  13u, 11u, 14u, 4u, 7u, 12u, 16u, 10u, 12u, 17u, 4u, 5u, 8u, 9u, 12u, 0u, 15u, 14u, 16u, 11u, 12u, 7u, 23u,
  8u, 0u, 19u, 8u, 9u, 6u, 5u, 8u, 6u, 4u, 10u, 9u, 10u, 4u, 9u, 13u, 21u, 11u, 14u, 5u, 6u, 4u, 17u,
  8u, 12u, 0u, 12u, 3u, 9u, 6u, 0u, 9u, 19u, 7u, 14u, 19u, 10u, 4u, 6u, 9u, 16u, 8u, 11u, 5u, 7u, 12u,
  8u, 5u, 13u, 9u, 8u, 8u, 17u, 14u, 9u, 10u, 5u, 19u, 4u, 11u, 4u, 4u, 6u, 0u, 6u, 21u, 10u, 6u, 9u,
  8u, 3u, 9u, 19u, 9u, 5u, 12u, 9u, 19u, 10u, 16u, 7u, 0u, 6u, 7u, 4u, 8u, 12u, 12u, 0u, 14u, 6u, 11u,
  13u, 12u, 14u, 12u, 5u, 12u, 12u, 14u, 23u, 11u, 15u, 9u, 4u, 10u, 7u, 11u, 7u, 16u, 0u, 8u, 17u, 16u, 4u,
  8u, 8u, 5u, 4u, 10u, 13u, 14u, 4u, 0u, 9u, 8u, 10u, 4u, 21u, 5u, 17u, 19u, 6u, 6u, 9u, 9u, 11u, 6u,
  8u, 8u, 10u, 9u, 12u, 7u, 9u, 14u, 6u, 12u, 11u, 4u, 19u, 3u, 12u, 16u, 19u, 0u, 0u, 5u, 6u, 7u, 9u,
  13u, 14u, 7u, 16u, 12u, 4u, 8u, 12u, 15u, 16u, 12u, 23u, 11u, 4u, 12u, 10u, 17u, 5u, 9u, 0u, 14u, 11u, 7u,
  0u, 6u, 16u, 4u, 2u, 2u, 4u, 8u, 20u, 9u, 14u, 10u, 6u, 12u, 8u, 6u, 10u, 4u, 14u, 0u, 8u, 10u, 10u,
  13u, 14u, 7u, 16u, 12u, 4u, 8u, 12u, 15u, 16u, 12u, 23u, 11u, 4u, 12u, 10u, 17u, 5u, 9u, 0u, 14u, 11u, 7u,
  8u, 8u, 10u, 9u, 12u, 7u, 9u, 14u, 6u, 12u, 11u, 4u, 19u, 3u, 12u, 16u, 19u, 0u, 0u, 5u, 6u, 7u, 9u,
  8u, 8u, 5u, 4u, 10u, 13u, 14u, 4u, 0u, 9u, 8u, 10u, 4u, 21u, 5u, 17u, 19u, 6u, 6u, 9u, 9u, 11u, 6u,
  13u, 12u, 14u, 12u, 5u, 12u, 12u, 14u, 23u, 11u, 15u, 9u, 4u, 10u, 7u, 11u, 7u, 16u, 0u, 8u, 17u, 16u, 4u,
  8u, 3u, 9u, 19u, 9u, 5u, 12u, 9u, 19u, 10u, 16u, 7u, 0u, 6u, 7u, 4u, 8u, 12u, 12u, 0u, 14u, 6u, 11u,
  8u, 5u, 13u, 9u, 8u, 8u, 17u, 14u, 9u, 10u, 5u, 19u, 4u, 11u, 4u, 4u, 6u, 0u, 6u, 21u, 10u, 6u, 9u,
  8u, 12u, 0u, 12u, 3u, 9u, 6u, 0u, 9u, 19u, 7u, 14u, 19u, 10u, 4u, 6u, 9u, 16u, 8u, 11u, 5u, 7u, 12u,
  8u, 0u, 19u, 8u, 9u, 6u, 5u, 8u, 6u, 4u, 10u, 9u, 10u, 4u, 9u, 13u, 21u, 11u, 14u, 5u, 6u, 4u, 17u,
  13u, 11u, 14u, 4u, 7u, 12u, 16u, 10u, 12u, 17u, 4u, 5u, 8u, 9u, 12u, 0u, 15u, 14u, 16u, 11u, 12u, 7u, 23u,
  0u, 10u, 10u, 14u, 10u, 9u, 8u, 20u, 0u, 8u, 14u, 4u, 4u, 2u, 10u, 2u, 6u, 4u, 8u, 16u, 12u, 6u, 6u
 };

static const QType JTable_23_691[]=
 {
  18u, 16u, 26u, 24u, 14u, 16u, 22u, 8u, 16u, 14u, 20u, 14u, 0u, 18u, 13u, 20u, 18u, 20u, 10u, 16u, 18u, 14u, 12u,
  7u, 2u, 5u, 3u, 10u, 3u, 5u, 7u, 10u, 9u, 15u, 3u, 14u, 12u, 14u, 14u, 3u, 1u, 0u, 20u, 4u, 7u, 15u,
  21u, 9u, 4u, 6u, 7u, 3u, 7u, 9u, 2u, 10u, 12u, 7u, 4u, 16u, 10u, 5u, 12u, 12u, 11u, 6u, 0u, 22u, 11u,
  0u, 10u, 4u, 7u, 5u, 4u, 12u, 5u, 13u, 16u, 9u, 18u, 11u, 4u, 9u, 4u, 8u, 19u, 17u, 0u, 8u, 8u, 15u,
  21u, 6u, 5u, 7u, 9u, 6u, 11u, 11u, 10u, 12u, 7u, 4u, 22u, 12u, 16u, 10u, 3u, 9u, 0u, 12u, 4u, 2u, 7u,
  0u, 5u, 13u, 11u, 8u, 8u, 10u, 4u, 16u, 4u, 19u, 8u, 4u, 12u, 9u, 9u, 17u, 15u, 7u, 5u, 18u, 4u, 0u,
  7u, 4u, 1u, 14u, 3u, 10u, 3u, 5u, 15u, 20u, 3u, 12u, 15u, 7u, 10u, 2u, 7u, 0u, 14u, 14u, 9u, 5u, 3u,
  21u, 6u, 7u, 10u, 4u, 5u, 11u, 22u, 9u, 7u, 9u, 12u, 16u, 12u, 6u, 11u, 4u, 3u, 2u, 7u, 10u, 12u, 0u,
  0u, 17u, 4u, 13u, 7u, 8u, 8u, 18u, 12u, 10u, 0u, 9u, 16u, 5u, 15u, 19u, 11u, 5u, 4u, 8u, 4u, 9u, 4u,
  7u, 5u, 10u, 5u, 10u, 15u, 14u, 14u, 3u, 0u, 4u, 15u, 2u, 3u, 3u, 7u, 9u, 3u, 12u, 14u, 1u, 20u, 7u,
  18u, 14u, 16u, 20u, 20u, 18u, 14u, 14u, 8u, 16u, 24u, 16u, 12u, 18u, 10u, 18u, 13u, 0u, 20u, 16u, 22u, 14u, 26u,
  7u, 5u, 10u, 5u, 10u, 15u, 14u, 14u, 3u, 0u, 4u, 15u, 2u, 3u, 3u, 7u, 9u, 3u, 12u, 14u, 1u, 20u, 7u,
  0u, 17u, 4u, 13u, 7u, 8u, 8u, 18u, 12u, 10u, 0u, 9u, 16u, 5u, 15u, 19u, 11u, 5u, 4u, 8u, 4u, 9u, 4u,
  21u, 6u, 7u, 10u, 4u, 5u, 11u, 22u, 9u, 7u, 9u, 12u, 16u, 12u, 6u, 11u, 4u, 3u, 2u, 7u, 10u, 12u, 0u,
  7u, 4u, 1u, 14u, 3u, 10u, 3u, 5u, 15u, 20u, 3u, 12u, 15u, 7u, 10u, 2u, 7u, 0u, 14u, 14u, 9u, 5u, 3u,
  0u, 5u, 13u, 11u, 8u, 8u, 10u, 4u, 16u, 4u, 19u, 8u, 4u, 12u, 9u, 9u, 17u, 15u, 7u, 5u, 18u, 4u, 0u,
  21u, 6u, 5u, 7u, 9u, 6u, 11u, 11u, 10u, 12u, 7u, 4u, 22u, 12u, 16u, 10u, 3u, 9u, 0u, 12u, 4u, 2u, 7u,
  0u, 10u, 4u, 7u, 5u, 4u, 12u, 5u, 13u, 16u, 9u, 18u, 11u, 4u, 9u, 4u, 8u, 19u, 17u, 0u, 8u, 8u, 15u,
  21u, 9u, 4u, 6u, 7u, 3u, 7u, 9u, 2u, 10u, 12u, 7u, 4u, 16u, 10u, 5u, 12u, 12u, 11u, 6u, 0u, 22u, 11u,
  7u, 2u, 5u, 3u, 10u, 3u, 5u, 7u, 10u, 9u, 15u, 3u, 14u, 12u, 14u, 14u, 3u, 1u, 0u, 20u, 4u, 7u, 15u,
  18u, 16u, 26u, 24u, 14u, 16u, 22u, 8u, 16u, 14u, 20u, 14u, 0u, 18u, 13u, 20u, 18u, 20u, 10u, 16u, 18u, 14u, 12u
 };

static const QType JTable_23_967[]=
 {
  10u, 16u, 22u, 8u, 10u, 2u, 12u, 8u, 4u, 18u, 14u, 13u, 0u, 24u, 18u, 14u, 22u, 12u, 8u, 18u, 8u, 10u, 4u,
  20u, 26u, 11u, 17u, 26u, 15u, 7u, 24u, 7u, 14u, 0u, 13u, 19u, 25u, 20u, 9u, 16u, 14u, 15u, 19u, 15u, 20u, 15u,
  12u, 18u, 13u, 0u, 21u, 15u, 16u, 9u, 7u, 14u, 4u, 7u, 6u, 5u, 7u, 29u, 12u, 18u, 9u, 8u, 17u, 17u, 11u,
  9u, 7u, 21u, 19u, 8u, 18u, 12u, 9u, 11u, 13u, 8u, 3u, 5u, 11u, 4u, 17u, 11u, 24u, 0u, 4u, 7u, 9u, 22u,
  12u, 8u, 29u, 7u, 9u, 0u, 11u, 9u, 7u, 4u, 16u, 13u, 17u, 18u, 5u, 14u, 15u, 18u, 17u, 12u, 6u, 7u, 21u,
  9u, 8u, 11u, 5u, 11u, 7u, 7u, 18u, 13u, 11u, 24u, 9u, 21u, 12u, 8u, 4u, 0u, 22u, 19u, 9u, 3u, 17u, 4u,
  20u, 15u, 14u, 20u, 13u, 7u, 15u, 11u, 15u, 19u, 16u, 25u, 0u, 24u, 26u, 26u, 20u, 15u, 9u, 19u, 14u, 7u, 17u,
  12u, 0u, 16u, 14u, 6u, 29u, 9u, 17u, 18u, 21u, 9u, 4u, 5u, 12u, 8u, 11u, 13u, 15u, 7u, 7u, 7u, 18u, 17u,
  9u, 0u, 11u, 11u, 19u, 9u, 11u, 3u, 12u, 7u, 4u, 4u, 13u, 8u, 22u, 24u, 5u, 9u, 21u, 7u, 17u, 8u, 18u,
  20u, 11u, 26u, 7u, 7u, 0u, 19u, 20u, 16u, 15u, 15u, 15u, 26u, 17u, 15u, 24u, 14u, 13u, 25u, 9u, 14u, 19u, 20u,
  10u, 10u, 18u, 12u, 14u, 24u, 13u, 18u, 8u, 2u, 8u, 16u, 4u, 8u, 8u, 22u, 18u, 0u, 14u, 4u, 12u, 10u, 22u,
  20u, 11u, 26u, 7u, 7u, 0u, 19u, 20u, 16u, 15u, 15u, 15u, 26u, 17u, 15u, 24u, 14u, 13u, 25u, 9u, 14u, 19u, 20u,
  9u, 0u, 11u, 11u, 19u, 9u, 11u, 3u, 12u, 7u, 4u, 4u, 13u, 8u, 22u, 24u, 5u, 9u, 21u, 7u, 17u, 8u, 18u,
  12u, 0u, 16u, 14u, 6u, 29u, 9u, 17u, 18u, 21u, 9u, 4u, 5u, 12u, 8u, 11u, 13u, 15u, 7u, 7u, 7u, 18u, 17u,
  20u, 15u, 14u, 20u, 13u, 7u, 15u, 11u, 15u, 19u, 16u, 25u, 0u, 24u, 26u, 26u, 20u, 15u, 9u, 19u, 14u, 7u, 17u,
  9u, 8u, 11u, 5u, 11u, 7u, 7u, 18u, 13u, 11u, 24u, 9u, 21u, 12u, 8u, 4u, 0u, 22u, 19u, 9u, 3u, 17u, 4u,
  12u, 8u, 29u, 7u, 9u, 0u, 11u, 9u, 7u, 4u, 16u, 13u, 17u, 18u, 5u, 14u, 15u, 18u, 17u, 12u, 6u, 7u, 21u,
  9u, 7u, 21u, 19u, 8u, 18u, 12u, 9u, 11u, 13u, 8u, 3u, 5u, 11u, 4u, 17u, 11u, 24u, 0u, 4u, 7u, 9u, 22u,
  12u, 18u, 13u, 0u, 21u, 15u, 16u, 9u, 7u, 14u, 4u, 7u, 6u, 5u, 7u, 29u, 12u, 18u, 9u, 8u, 17u, 17u, 11u,
  20u, 26u, 11u, 17u, 26u, 15u, 7u, 24u, 7u, 14u, 0u, 13u, 19u, 25u, 20u, 9u, 16u, 14u, 15u, 19u, 15u, 20u, 15u,
  10u, 16u, 22u, 8u, 10u, 2u, 12u, 8u, 4u, 18u, 14u, 13u, 0u, 24u, 18u, 14u, 22u, 12u, 8u, 18u, 8u, 10u, 4u
 };

static const QType JTable_23_2347[]=
 {
  20u, 18u, 2u, 28u, 34u, 16u, 22u, 24u, 8u, 22u, 2u, 14u, 0u, 8u, 38u, 18u, 15u, 8u, 28u, 18u, 30u, 20u, 20u,
  46u, 16u, 26u, 27u, 7u, 4u, 30u, 21u, 13u, 0u, 12u, 23u, 18u, 16u, 29u, 11u, 29u, 20u, 18u, 10u, 15u, 27u, 18u,
  13u, 7u, 19u, 33u, 0u, 22u, 31u, 11u, 19u, 28u, 32u, 30u, 33u, 17u, 36u, 17u, 27u, 6u, 18u, 21u, 29u, 36u, 20u,
  35u, 6u, 20u, 3u, 11u, 0u, 11u, 14u, 31u, 12u, 14u, 29u, 22u, 14u, 14u, 25u, 6u, 30u, 33u, 6u, 14u, 15u, 25u,
  13u, 21u, 17u, 30u, 11u, 33u, 20u, 18u, 36u, 32u, 31u, 19u, 36u, 6u, 17u, 28u, 22u, 7u, 29u, 27u, 33u, 19u, 0u,
  35u, 11u, 31u, 22u, 6u, 14u, 6u, 0u, 12u, 14u, 30u, 15u, 20u, 11u, 14u, 14u, 33u, 25u, 3u, 14u, 29u, 25u, 6u,
  46u, 15u, 20u, 29u, 23u, 13u, 4u, 26u, 18u, 10u, 29u, 16u, 12u, 21u, 7u, 16u, 27u, 18u, 11u, 18u, 0u, 30u, 27u,
  13u, 33u, 31u, 28u, 33u, 17u, 18u, 36u, 7u, 0u, 11u, 32u, 17u, 27u, 21u, 20u, 19u, 22u, 19u, 30u, 36u, 6u, 29u,
  35u, 33u, 14u, 31u, 3u, 15u, 6u, 29u, 11u, 6u, 6u, 14u, 12u, 11u, 25u, 30u, 22u, 14u, 20u, 14u, 25u, 14u, 0u,
  46u, 26u, 7u, 30u, 13u, 12u, 18u, 29u, 29u, 18u, 15u, 18u, 16u, 27u, 4u, 21u, 0u, 23u, 16u, 11u, 20u, 10u, 27u,
  20u, 20u, 18u, 8u, 18u, 8u, 14u, 22u, 24u, 16u, 28u, 18u, 20u, 30u, 28u, 15u, 38u, 0u, 2u, 8u, 22u, 34u, 2u,
  46u, 26u, 7u, 30u, 13u, 12u, 18u, 29u, 29u, 18u, 15u, 18u, 16u, 27u, 4u, 21u, 0u, 23u, 16u, 11u, 20u, 10u, 27u,
  35u, 33u, 14u, 31u, 3u, 15u, 6u, 29u, 11u, 6u, 6u, 14u, 12u, 11u, 25u, 30u, 22u, 14u, 20u, 14u, 25u, 14u, 0u,
  13u, 33u, 31u, 28u, 33u, 17u, 18u, 36u, 7u, 0u, 11u, 32u, 17u, 27u, 21u, 20u, 19u, 22u, 19u, 30u, 36u, 6u, 29u,
  46u, 15u, 20u, 29u, 23u, 13u, 4u, 26u, 18u, 10u, 29u, 16u, 12u, 21u, 7u, 16u, 27u, 18u, 11u, 18u, 0u, 30u, 27u,
  35u, 11u, 31u, 22u, 6u, 14u, 6u, 0u, 12u, 14u, 30u, 15u, 20u, 11u, 14u, 14u, 33u, 25u, 3u, 14u, 29u, 25u, 6u,
  13u, 21u, 17u, 30u, 11u, 33u, 20u, 18u, 36u, 32u, 31u, 19u, 36u, 6u, 17u, 28u, 22u, 7u, 29u, 27u, 33u, 19u, 0u,
  35u, 6u, 20u, 3u, 11u, 0u, 11u, 14u, 31u, 12u, 14u, 29u, 22u, 14u, 14u, 25u, 6u, 30u, 33u, 6u, 14u, 15u, 25u,
  13u, 7u, 19u, 33u, 0u, 22u, 31u, 11u, 19u, 28u, 32u, 30u, 33u, 17u, 36u, 17u, 27u, 6u, 18u, 21u, 29u, 36u, 20u,
  46u, 16u, 26u, 27u, 7u, 4u, 30u, 21u, 13u, 0u, 12u, 23u, 18u, 16u, 29u, 11u, 29u, 20u, 18u, 10u, 15u, 27u, 18u,
  20u, 18u, 2u, 28u, 34u, 16u, 22u, 24u, 8u, 22u, 2u, 14u, 0u, 8u, 38u, 18u, 15u, 8u, 28u, 18u, 30u, 20u, 20u
 };

static const QType JTable_23_2531[]=
 {
  22u, 40u, 26u, 36u, 20u, 26u, 14u, 34u, 32u, 24u, 34u, 6u, 32u, 32u, 32u, 18u, 18u, 28u, 34u, 0u, 12u, 21u, 10u,
  0u, 8u, 23u, 0u, 6u, 28u, 7u, 19u, 21u, 11u, 36u, 13u, 20u, 13u, 34u, 7u, 9u, 13u, 20u, 23u, 32u, 21u, 3u,
  36u, 42u, 20u, 25u, 20u, 17u, 30u, 37u, 22u, 42u, 20u, 12u, 21u, 33u, 21u, 0u, 39u, 25u, 40u, 24u, 25u, 34u, 35u,
  35u, 14u, 11u, 18u, 23u, 29u, 20u, 19u, 35u, 0u, 34u, 33u, 22u, 35u, 35u, 24u, 11u, 25u, 15u, 16u, 0u, 24u, 27u,
  36u, 24u, 0u, 12u, 37u, 25u, 35u, 40u, 21u, 20u, 30u, 20u, 34u, 25u, 33u, 42u, 17u, 42u, 25u, 39u, 21u, 22u, 20u,
  35u, 23u, 35u, 22u, 11u, 0u, 14u, 29u, 0u, 35u, 25u, 24u, 11u, 20u, 34u, 35u, 15u, 27u, 18u, 19u, 33u, 24u, 16u,
  0u, 32u, 13u, 34u, 13u, 21u, 28u, 23u, 3u, 23u, 9u, 13u, 36u, 19u, 6u, 8u, 21u, 20u, 7u, 20u, 11u, 7u, 0u,
  36u, 25u, 30u, 42u, 21u, 0u, 40u, 34u, 42u, 20u, 37u, 20u, 33u, 39u, 24u, 35u, 20u, 17u, 22u, 12u, 21u, 25u, 25u,
  35u, 15u, 35u, 35u, 18u, 24u, 11u, 33u, 20u, 14u, 16u, 35u, 0u, 23u, 27u, 25u, 22u, 19u, 11u, 0u, 24u, 34u, 29u,
  0u, 23u, 6u, 7u, 21u, 36u, 20u, 34u, 9u, 20u, 32u, 3u, 8u, 0u, 28u, 19u, 11u, 13u, 13u, 7u, 13u, 23u, 21u,
  22u, 21u, 0u, 28u, 18u, 32u, 6u, 24u, 34u, 26u, 36u, 40u, 10u, 12u, 34u, 18u, 32u, 32u, 34u, 32u, 14u, 20u, 26u,
  0u, 23u, 6u, 7u, 21u, 36u, 20u, 34u, 9u, 20u, 32u, 3u, 8u, 0u, 28u, 19u, 11u, 13u, 13u, 7u, 13u, 23u, 21u,
  35u, 15u, 35u, 35u, 18u, 24u, 11u, 33u, 20u, 14u, 16u, 35u, 0u, 23u, 27u, 25u, 22u, 19u, 11u, 0u, 24u, 34u, 29u,
  36u, 25u, 30u, 42u, 21u, 0u, 40u, 34u, 42u, 20u, 37u, 20u, 33u, 39u, 24u, 35u, 20u, 17u, 22u, 12u, 21u, 25u, 25u,
  0u, 32u, 13u, 34u, 13u, 21u, 28u, 23u, 3u, 23u, 9u, 13u, 36u, 19u, 6u, 8u, 21u, 20u, 7u, 20u, 11u, 7u, 0u,
  35u, 23u, 35u, 22u, 11u, 0u, 14u, 29u, 0u, 35u, 25u, 24u, 11u, 20u, 34u, 35u, 15u, 27u, 18u, 19u, 33u, 24u, 16u,
  36u, 24u, 0u, 12u, 37u, 25u, 35u, 40u, 21u, 20u, 30u, 20u, 34u, 25u, 33u, 42u, 17u, 42u, 25u, 39u, 21u, 22u, 20u,
  35u, 14u, 11u, 18u, 23u, 29u, 20u, 19u, 35u, 0u, 34u, 33u, 22u, 35u, 35u, 24u, 11u, 25u, 15u, 16u, 0u, 24u, 27u,
  36u, 42u, 20u, 25u, 20u, 17u, 30u, 37u, 22u, 42u, 20u, 12u, 21u, 33u, 21u, 0u, 39u, 25u, 40u, 24u, 25u, 34u, 35u,
  0u, 8u, 23u, 0u, 6u, 28u, 7u, 19u, 21u, 11u, 36u, 13u, 20u, 13u, 34u, 7u, 9u, 13u, 20u, 23u, 32u, 21u, 3u,
  22u, 40u, 26u, 36u, 20u, 26u, 14u, 34u, 32u, 24u, 34u, 6u, 32u, 32u, 32u, 18u, 18u, 28u, 34u, 0u, 12u, 21u, 10u
 };

static const QType JTable_23_3911[]=
 {
  30u, 26u, 46u, 44u, 18u, 42u, 26u, 14u, 32u, 56u, 24u, 24u, 14u, 48u, 28u, 32u, 26u, 22u, 32u, 13u, 30u, 0u, 16u,
  19u, 38u, 22u, 0u, 17u, 9u, 9u, 41u, 7u, 50u, 28u, 25u, 17u, 30u, 34u, 36u, 27u, 22u, 13u, 13u, 43u, 36u, 15u,
  6u, 9u, 23u, 18u, 14u, 16u, 42u, 0u, 21u, 5u, 13u, 38u, 16u, 1u, 16u, 6u, 20u, 13u, 24u, 19u, 31u, 35u, 50u,
  14u, 49u, 39u, 15u, 29u, 11u, 11u, 19u, 19u, 20u, 33u, 25u, 14u, 22u, 20u, 34u, 27u, 47u, 0u, 20u, 19u, 50u, 37u,
  6u, 19u, 6u, 38u, 0u, 18u, 50u, 24u, 16u, 13u, 42u, 23u, 35u, 13u, 1u, 5u, 16u, 9u, 31u, 20u, 16u, 21u, 14u,
  14u, 29u, 19u, 14u, 27u, 19u, 49u, 11u, 20u, 22u, 47u, 50u, 39u, 11u, 33u, 20u, 0u, 37u, 15u, 19u, 25u, 34u, 20u,
  19u, 43u, 22u, 34u, 25u, 7u, 9u, 22u, 15u, 13u, 27u, 30u, 28u, 41u, 17u, 38u, 36u, 13u, 36u, 17u, 50u, 9u, 0u,
  6u, 18u, 42u, 5u, 16u, 6u, 24u, 35u, 9u, 14u, 0u, 13u, 1u, 20u, 19u, 50u, 23u, 16u, 21u, 38u, 16u, 13u, 31u,
  14u, 0u, 22u, 19u, 15u, 50u, 27u, 25u, 11u, 49u, 20u, 20u, 20u, 29u, 37u, 47u, 14u, 19u, 39u, 19u, 34u, 33u, 11u,
  19u, 22u, 17u, 9u, 7u, 28u, 17u, 34u, 27u, 13u, 43u, 15u, 38u, 0u, 9u, 41u, 50u, 25u, 30u, 36u, 22u, 13u, 36u,
  30u, 0u, 13u, 22u, 32u, 48u, 24u, 56u, 14u, 42u, 44u, 26u, 16u, 30u, 32u, 26u, 28u, 14u, 24u, 32u, 26u, 18u, 46u,
  19u, 22u, 17u, 9u, 7u, 28u, 17u, 34u, 27u, 13u, 43u, 15u, 38u, 0u, 9u, 41u, 50u, 25u, 30u, 36u, 22u, 13u, 36u,
  14u, 0u, 22u, 19u, 15u, 50u, 27u, 25u, 11u, 49u, 20u, 20u, 20u, 29u, 37u, 47u, 14u, 19u, 39u, 19u, 34u, 33u, 11u,
  6u, 18u, 42u, 5u, 16u, 6u, 24u, 35u, 9u, 14u, 0u, 13u, 1u, 20u, 19u, 50u, 23u, 16u, 21u, 38u, 16u, 13u, 31u,
  19u, 43u, 22u, 34u, 25u, 7u, 9u, 22u, 15u, 13u, 27u, 30u, 28u, 41u, 17u, 38u, 36u, 13u, 36u, 17u, 50u, 9u, 0u,
  14u, 29u, 19u, 14u, 27u, 19u, 49u, 11u, 20u, 22u, 47u, 50u, 39u, 11u, 33u, 20u, 0u, 37u, 15u, 19u, 25u, 34u, 20u,
  6u, 19u, 6u, 38u, 0u, 18u, 50u, 24u, 16u, 13u, 42u, 23u, 35u, 13u, 1u, 5u, 16u, 9u, 31u, 20u, 16u, 21u, 14u,
  14u, 49u, 39u, 15u, 29u, 11u, 11u, 19u, 19u, 20u, 33u, 25u, 14u, 22u, 20u, 34u, 27u, 47u, 0u, 20u, 19u, 50u, 37u,
  6u, 9u, 23u, 18u, 14u, 16u, 42u, 0u, 21u, 5u, 13u, 38u, 16u, 1u, 16u, 6u, 20u, 13u, 24u, 19u, 31u, 35u, 50u,
  19u, 38u, 22u, 0u, 17u, 9u, 9u, 41u, 7u, 50u, 28u, 25u, 17u, 30u, 34u, 36u, 27u, 22u, 13u, 13u, 43u, 36u, 15u,
  30u, 26u, 46u, 44u, 18u, 42u, 26u, 14u, 32u, 56u, 24u, 24u, 14u, 48u, 28u, 32u, 26u, 22u, 32u, 13u, 30u, 0u, 16u
 };

static const QType JTable_23_4831[]=
 {
  36u, 16u, 40u, 32u, 40u, 11u, 26u, 22u, 26u, 14u, 38u, 6u, 12u, 58u, 30u, 6u, 18u, 0u, 32u, 16u, 36u, 42u, 40u,
  0u, 43u, 20u, 30u, 21u, 48u, 36u, 43u, 27u, 18u, 41u, 50u, 14u, 34u, 35u, 23u, 16u, 35u, 40u, 52u, 6u, 25u, 9u,
  29u, 11u, 16u, 8u, 0u, 33u, 18u, 13u, 25u, 28u, 14u, 45u, 38u, 22u, 15u, 46u, 37u, 7u, 16u, 0u, 50u, 19u, 38u,
  23u, 15u, 9u, 42u, 12u, 21u, 32u, 36u, 34u, 49u, 46u, 0u, 34u, 31u, 39u, 41u, 32u, 54u, 34u, 16u, 49u, 34u, 52u,
  29u, 0u, 46u, 45u, 13u, 8u, 38u, 16u, 15u, 14u, 18u, 16u, 19u, 7u, 22u, 28u, 33u, 11u, 50u, 37u, 38u, 25u, 0u,
  23u, 12u, 34u, 34u, 32u, 49u, 15u, 21u, 49u, 31u, 54u, 34u, 9u, 32u, 46u, 39u, 34u, 52u, 42u, 36u, 0u, 41u, 16u,
  0u, 6u, 35u, 35u, 50u, 27u, 48u, 20u, 9u, 52u, 16u, 34u, 41u, 43u, 21u, 43u, 25u, 40u, 23u, 14u, 18u, 36u, 30u,
  29u, 8u, 18u, 28u, 38u, 46u, 16u, 19u, 11u, 0u, 13u, 14u, 22u, 37u, 0u, 38u, 16u, 33u, 25u, 45u, 15u, 7u, 50u,
  23u, 34u, 31u, 34u, 42u, 34u, 32u, 0u, 32u, 15u, 16u, 39u, 49u, 12u, 52u, 54u, 34u, 36u, 9u, 49u, 41u, 46u, 21u,
  0u, 20u, 21u, 36u, 27u, 41u, 14u, 35u, 16u, 40u, 6u, 9u, 43u, 30u, 48u, 43u, 18u, 50u, 34u, 23u, 35u, 52u, 25u,
  36u, 42u, 16u, 0u, 6u, 58u, 6u, 14u, 22u, 11u, 32u, 16u, 40u, 36u, 32u, 18u, 30u, 12u, 38u, 26u, 26u, 40u, 40u,
  0u, 20u, 21u, 36u, 27u, 41u, 14u, 35u, 16u, 40u, 6u, 9u, 43u, 30u, 48u, 43u, 18u, 50u, 34u, 23u, 35u, 52u, 25u,
  23u, 34u, 31u, 34u, 42u, 34u, 32u, 0u, 32u, 15u, 16u, 39u, 49u, 12u, 52u, 54u, 34u, 36u, 9u, 49u, 41u, 46u, 21u,
  29u, 8u, 18u, 28u, 38u, 46u, 16u, 19u, 11u, 0u, 13u, 14u, 22u, 37u, 0u, 38u, 16u, 33u, 25u, 45u, 15u, 7u, 50u,
  0u, 6u, 35u, 35u, 50u, 27u, 48u, 20u, 9u, 52u, 16u, 34u, 41u, 43u, 21u, 43u, 25u, 40u, 23u, 14u, 18u, 36u, 30u,
  23u, 12u, 34u, 34u, 32u, 49u, 15u, 21u, 49u, 31u, 54u, 34u, 9u, 32u, 46u, 39u, 34u, 52u, 42u, 36u, 0u, 41u, 16u,
  29u, 0u, 46u, 45u, 13u, 8u, 38u, 16u, 15u, 14u, 18u, 16u, 19u, 7u, 22u, 28u, 33u, 11u, 50u, 37u, 38u, 25u, 0u,
  23u, 15u, 9u, 42u, 12u, 21u, 32u, 36u, 34u, 49u, 46u, 0u, 34u, 31u, 39u, 41u, 32u, 54u, 34u, 16u, 49u, 34u, 52u,
  29u, 11u, 16u, 8u, 0u, 33u, 18u, 13u, 25u, 28u, 14u, 45u, 38u, 22u, 15u, 46u, 37u, 7u, 16u, 0u, 50u, 19u, 38u,
  0u, 43u, 20u, 30u, 21u, 48u, 36u, 43u, 27u, 18u, 41u, 50u, 14u, 34u, 35u, 23u, 16u, 35u, 40u, 52u, 6u, 25u, 9u,
  36u, 16u, 40u, 32u, 40u, 11u, 26u, 22u, 26u, 14u, 38u, 6u, 12u, 58u, 30u, 6u, 18u, 0u, 32u, 16u, 36u, 42u, 40u
 };

static const QType JTable_23_7591[]=
 {
  40u, 38u, 26u, 46u, 14u, 44u, 58u, 20u, 40u, 22u, 16u, 76u, 49u, 46u, 2u, 32u, 18u, 14u, 0u, 46u, 32u, 20u, 36u,
  42u, 42u, 11u, 58u, 60u, 60u, 32u, 19u, 21u, 43u, 0u, 27u, 35u, 17u, 47u, 65u, 23u, 26u, 27u, 59u, 18u, 57u, 38u,
  48u, 26u, 16u, 37u, 38u, 0u, 70u, 47u, 63u, 51u, 25u, 24u, 23u, 27u, 51u, 12u, 17u, 22u, 36u, 33u, 38u, 2u, 52u,
  39u, 42u, 5u, 72u, 28u, 33u, 38u, 47u, 62u, 51u, 35u, 58u, 56u, 66u, 39u, 42u, 31u, 37u, 0u, 37u, 63u, 61u, 23u,
  48u, 33u, 12u, 24u, 47u, 37u, 52u, 36u, 51u, 25u, 70u, 16u, 2u, 22u, 27u, 51u, 0u, 26u, 38u, 17u, 23u, 63u, 38u,
  39u, 28u, 62u, 56u, 31u, 63u, 42u, 33u, 51u, 66u, 37u, 61u, 5u, 38u, 35u, 39u, 0u, 23u, 72u, 47u, 58u, 42u, 37u,
  42u, 18u, 26u, 47u, 27u, 21u, 60u, 11u, 38u, 59u, 23u, 17u, 0u, 19u, 60u, 42u, 57u, 27u, 65u, 35u, 43u, 32u, 58u,
  48u, 37u, 70u, 51u, 23u, 12u, 36u, 2u, 26u, 38u, 47u, 25u, 27u, 17u, 33u, 52u, 16u, 0u, 63u, 24u, 51u, 22u, 38u,
  39u, 0u, 66u, 62u, 72u, 61u, 31u, 58u, 38u, 42u, 37u, 39u, 51u, 28u, 23u, 37u, 56u, 47u, 5u, 63u, 42u, 35u, 33u,
  42u, 11u, 60u, 32u, 21u, 0u, 35u, 47u, 23u, 27u, 18u, 38u, 42u, 58u, 60u, 19u, 43u, 27u, 17u, 65u, 26u, 59u, 57u,
  40u, 20u, 46u, 14u, 32u, 46u, 76u, 22u, 20u, 44u, 46u, 38u, 36u, 32u, 0u, 18u, 2u, 49u, 16u, 40u, 58u, 14u, 26u,
  42u, 11u, 60u, 32u, 21u, 0u, 35u, 47u, 23u, 27u, 18u, 38u, 42u, 58u, 60u, 19u, 43u, 27u, 17u, 65u, 26u, 59u, 57u,
  39u, 0u, 66u, 62u, 72u, 61u, 31u, 58u, 38u, 42u, 37u, 39u, 51u, 28u, 23u, 37u, 56u, 47u, 5u, 63u, 42u, 35u, 33u,
  48u, 37u, 70u, 51u, 23u, 12u, 36u, 2u, 26u, 38u, 47u, 25u, 27u, 17u, 33u, 52u, 16u, 0u, 63u, 24u, 51u, 22u, 38u,
  42u, 18u, 26u, 47u, 27u, 21u, 60u, 11u, 38u, 59u, 23u, 17u, 0u, 19u, 60u, 42u, 57u, 27u, 65u, 35u, 43u, 32u, 58u,
  39u, 28u, 62u, 56u, 31u, 63u, 42u, 33u, 51u, 66u, 37u, 61u, 5u, 38u, 35u, 39u, 0u, 23u, 72u, 47u, 58u, 42u, 37u,
  48u, 33u, 12u, 24u, 47u, 37u, 52u, 36u, 51u, 25u, 70u, 16u, 2u, 22u, 27u, 51u, 0u, 26u, 38u, 17u, 23u, 63u, 38u,
  39u, 42u, 5u, 72u, 28u, 33u, 38u, 47u, 62u, 51u, 35u, 58u, 56u, 66u, 39u, 42u, 31u, 37u, 0u, 37u, 63u, 61u, 23u,
  48u, 26u, 16u, 37u, 38u, 0u, 70u, 47u, 63u, 51u, 25u, 24u, 23u, 27u, 51u, 12u, 17u, 22u, 36u, 33u, 38u, 2u, 52u,
  42u, 42u, 11u, 58u, 60u, 60u, 32u, 19u, 21u, 43u, 0u, 27u, 35u, 17u, 47u, 65u, 23u, 26u, 27u, 59u, 18u, 57u, 38u,
  40u, 38u, 26u, 46u, 14u, 44u, 58u, 20u, 40u, 22u, 16u, 76u, 49u, 46u, 2u, 32u, 18u, 14u, 0u, 46u, 32u, 20u, 36u
 };

static const QType JTable_23_8971[]=
 {
  28u, 32u, 34u, 26u, 44u, 46u, 2u, 38u, 54u, 38u, 36u, 28u, 0u, 32u, 40u, 78u, 60u, 20u, 82u, 38u, 42u, 19u, 56u,
  0u, 54u, 26u, 54u, 36u, 50u, 60u, 41u, 24u, 50u, 49u, 63u, 17u, 3u, 34u, 40u, 23u, 81u, 22u, 17u, 34u, 27u, 22u,
  28u, 54u, 15u, 59u, 24u, 38u, 46u, 72u, 31u, 19u, 0u, 47u, 35u, 5u, 63u, 39u, 21u, 43u, 39u, 66u, 65u, 56u, 31u,
  29u, 32u, 69u, 52u, 20u, 41u, 3u, 29u, 39u, 87u, 19u, 24u, 42u, 15u, 30u, 0u, 33u, 34u, 21u, 24u, 47u, 33u, 58u,
  28u, 66u, 39u, 47u, 72u, 59u, 31u, 39u, 63u, 0u, 46u, 15u, 56u, 43u, 5u, 19u, 38u, 54u, 65u, 21u, 35u, 31u, 24u,
  29u, 20u, 39u, 42u, 33u, 47u, 32u, 41u, 87u, 15u, 34u, 33u, 69u, 3u, 19u, 30u, 21u, 58u, 52u, 29u, 24u, 0u, 24u,
  0u, 34u, 81u, 34u, 63u, 24u, 50u, 26u, 22u, 17u, 23u, 3u, 49u, 41u, 36u, 54u, 27u, 22u, 40u, 17u, 50u, 60u, 54u,
  28u, 59u, 46u, 19u, 35u, 39u, 39u, 56u, 54u, 24u, 72u, 0u, 5u, 21u, 66u, 31u, 15u, 38u, 31u, 47u, 63u, 43u, 65u,
  29u, 21u, 15u, 39u, 52u, 33u, 33u, 24u, 3u, 32u, 24u, 30u, 87u, 20u, 58u, 34u, 42u, 29u, 69u, 47u, 0u, 19u, 41u,
  0u, 26u, 36u, 60u, 24u, 49u, 17u, 34u, 23u, 22u, 34u, 22u, 54u, 54u, 50u, 41u, 50u, 63u, 3u, 40u, 81u, 17u, 27u,
  28u, 19u, 38u, 20u, 78u, 32u, 28u, 38u, 38u, 46u, 26u, 32u, 56u, 42u, 82u, 60u, 40u, 0u, 36u, 54u, 2u, 44u, 34u,
  0u, 26u, 36u, 60u, 24u, 49u, 17u, 34u, 23u, 22u, 34u, 22u, 54u, 54u, 50u, 41u, 50u, 63u, 3u, 40u, 81u, 17u, 27u,
  29u, 21u, 15u, 39u, 52u, 33u, 33u, 24u, 3u, 32u, 24u, 30u, 87u, 20u, 58u, 34u, 42u, 29u, 69u, 47u, 0u, 19u, 41u,
  28u, 59u, 46u, 19u, 35u, 39u, 39u, 56u, 54u, 24u, 72u, 0u, 5u, 21u, 66u, 31u, 15u, 38u, 31u, 47u, 63u, 43u, 65u,
  0u, 34u, 81u, 34u, 63u, 24u, 50u, 26u, 22u, 17u, 23u, 3u, 49u, 41u, 36u, 54u, 27u, 22u, 40u, 17u, 50u, 60u, 54u,
  29u, 20u, 39u, 42u, 33u, 47u, 32u, 41u, 87u, 15u, 34u, 33u, 69u, 3u, 19u, 30u, 21u, 58u, 52u, 29u, 24u, 0u, 24u,
  28u, 66u, 39u, 47u, 72u, 59u, 31u, 39u, 63u, 0u, 46u, 15u, 56u, 43u, 5u, 19u, 38u, 54u, 65u, 21u, 35u, 31u, 24u,
  29u, 32u, 69u, 52u, 20u, 41u, 3u, 29u, 39u, 87u, 19u, 24u, 42u, 15u, 30u, 0u, 33u, 34u, 21u, 24u, 47u, 33u, 58u,
  28u, 54u, 15u, 59u, 24u, 38u, 46u, 72u, 31u, 19u, 0u, 47u, 35u, 5u, 63u, 39u, 21u, 43u, 39u, 66u, 65u, 56u, 31u,
  0u, 54u, 26u, 54u, 36u, 50u, 60u, 41u, 24u, 50u, 49u, 63u, 17u, 3u, 34u, 40u, 23u, 81u, 22u, 17u, 34u, 27u, 22u,
  28u, 32u, 34u, 26u, 44u, 46u, 2u, 38u, 54u, 38u, 36u, 28u, 0u, 32u, 40u, 78u, 60u, 20u, 82u, 38u, 42u, 19u, 56u
 };

static const QType JTable_23_10627[]=
 {
  4u, 10u, 12u, 76u, 14u, 46u, 14u, 22u, 12u, 4u, 38u, 58u, 35u, 36u, 44u, 58u, 18u, 60u, 32u, 0u, 32u, 54u, 10u,
  60u, 9u, 38u, 16u, 8u, 34u, 47u, 29u, 27u, 70u, 71u, 10u, 63u, 40u, 24u, 20u, 21u, 52u, 69u, 46u, 21u, 29u, 0u,
  9u, 14u, 37u, 10u, 83u, 24u, 24u, 30u, 55u, 21u, 25u, 25u, 22u, 25u, 63u, 48u, 26u, 5u, 18u, 5u, 0u, 9u, 65u,
  47u, 60u, 48u, 19u, 57u, 33u, 60u, 56u, 66u, 47u, 53u, 0u, 42u, 20u, 13u, 46u, 31u, 35u, 33u, 89u, 17u, 2u, 45u,
  9u, 5u, 48u, 25u, 30u, 10u, 65u, 18u, 63u, 25u, 24u, 37u, 9u, 5u, 25u, 21u, 24u, 14u, 0u, 26u, 22u, 55u, 83u,
  47u, 57u, 66u, 42u, 31u, 17u, 60u, 33u, 47u, 20u, 35u, 2u, 48u, 60u, 53u, 13u, 33u, 45u, 19u, 56u, 0u, 46u, 89u,
  60u, 21u, 52u, 24u, 10u, 27u, 34u, 38u, 0u, 46u, 21u, 40u, 71u, 29u, 8u, 9u, 29u, 69u, 20u, 63u, 70u, 47u, 16u,
  9u, 10u, 24u, 21u, 22u, 48u, 18u, 9u, 14u, 83u, 30u, 25u, 25u, 26u, 5u, 65u, 37u, 24u, 55u, 25u, 63u, 5u, 0u,
  47u, 33u, 20u, 66u, 19u, 2u, 31u, 0u, 60u, 60u, 89u, 13u, 47u, 57u, 45u, 35u, 42u, 56u, 48u, 17u, 46u, 53u, 33u,
  60u, 38u, 8u, 47u, 27u, 71u, 63u, 24u, 21u, 69u, 21u, 0u, 9u, 16u, 34u, 29u, 70u, 10u, 40u, 20u, 52u, 46u, 29u,
  4u, 54u, 0u, 60u, 58u, 36u, 58u, 4u, 22u, 46u, 76u, 10u, 10u, 32u, 32u, 18u, 44u, 35u, 38u, 12u, 14u, 14u, 12u,
  60u, 38u, 8u, 47u, 27u, 71u, 63u, 24u, 21u, 69u, 21u, 0u, 9u, 16u, 34u, 29u, 70u, 10u, 40u, 20u, 52u, 46u, 29u,
  47u, 33u, 20u, 66u, 19u, 2u, 31u, 0u, 60u, 60u, 89u, 13u, 47u, 57u, 45u, 35u, 42u, 56u, 48u, 17u, 46u, 53u, 33u,
  9u, 10u, 24u, 21u, 22u, 48u, 18u, 9u, 14u, 83u, 30u, 25u, 25u, 26u, 5u, 65u, 37u, 24u, 55u, 25u, 63u, 5u, 0u,
  60u, 21u, 52u, 24u, 10u, 27u, 34u, 38u, 0u, 46u, 21u, 40u, 71u, 29u, 8u, 9u, 29u, 69u, 20u, 63u, 70u, 47u, 16u,
  47u, 57u, 66u, 42u, 31u, 17u, 60u, 33u, 47u, 20u, 35u, 2u, 48u, 60u, 53u, 13u, 33u, 45u, 19u, 56u, 0u, 46u, 89u,
  9u, 5u, 48u, 25u, 30u, 10u, 65u, 18u, 63u, 25u, 24u, 37u, 9u, 5u, 25u, 21u, 24u, 14u, 0u, 26u, 22u, 55u, 83u,
  47u, 60u, 48u, 19u, 57u, 33u, 60u, 56u, 66u, 47u, 53u, 0u, 42u, 20u, 13u, 46u, 31u, 35u, 33u, 89u, 17u, 2u, 45u,
  9u, 14u, 37u, 10u, 83u, 24u, 24u, 30u, 55u, 21u, 25u, 25u, 22u, 25u, 63u, 48u, 26u, 5u, 18u, 5u, 0u, 9u, 65u,
  60u, 9u, 38u, 16u, 8u, 34u, 47u, 29u, 27u, 70u, 71u, 10u, 63u, 40u, 24u, 20u, 21u, 52u, 69u, 46u, 21u, 29u, 0u,
  4u, 10u, 12u, 76u, 14u, 46u, 14u, 22u, 12u, 4u, 38u, 58u, 35u, 36u, 44u, 58u, 18u, 60u, 32u, 0u, 32u, 54u, 10u
 };

static const QType JTable_23_11731[]=
 {
  48u, 30u, 0u, 58u, 28u, 70u, 88u, 34u, 58u, 87u, 64u, 40u, 18u, 68u, 66u, 60u, 42u, 68u, 14u, 60u, 50u, 64u, 34u,
  56u, 36u, 74u, 74u, 60u, 75u, 120u, 68u, 45u, 46u, 70u, 63u, 61u, 49u, 73u, 79u, 58u, 88u, 0u, 60u, 39u, 52u, 79u,
  68u, 48u, 46u, 64u, 52u, 47u, 54u, 25u, 0u, 82u, 98u, 40u, 91u, 31u, 77u, 43u, 51u, 58u, 78u, 71u, 60u, 66u, 83u,
  36u, 50u, 53u, 43u, 10u, 74u, 48u, 45u, 57u, 87u, 38u, 74u, 67u, 46u, 30u, 39u, 35u, 10u, 74u, 43u, 81u, 40u, 0u,
  68u, 71u, 43u, 40u, 25u, 64u, 83u, 78u, 77u, 98u, 54u, 46u, 66u, 58u, 31u, 82u, 47u, 48u, 60u, 51u, 91u, 0u, 52u,
  36u, 10u, 57u, 67u, 35u, 81u, 50u, 74u, 87u, 46u, 10u, 40u, 53u, 48u, 38u, 30u, 74u, 0u, 43u, 45u, 74u, 39u, 43u,
  56u, 39u, 88u, 73u, 63u, 45u, 75u, 74u, 79u, 60u, 58u, 49u, 70u, 68u, 60u, 36u, 52u, 0u, 79u, 61u, 46u, 120u, 74u,
  68u, 64u, 54u, 82u, 91u, 43u, 78u, 66u, 48u, 52u, 25u, 98u, 31u, 51u, 71u, 83u, 46u, 47u, 0u, 40u, 77u, 58u, 60u,
  36u, 74u, 46u, 57u, 43u, 40u, 35u, 74u, 48u, 50u, 43u, 30u, 87u, 10u, 0u, 10u, 67u, 45u, 53u, 81u, 39u, 38u, 74u,
  56u, 74u, 60u, 120u, 45u, 70u, 61u, 73u, 58u, 0u, 39u, 79u, 36u, 74u, 75u, 68u, 46u, 63u, 49u, 79u, 88u, 60u, 52u,
  48u, 64u, 60u, 68u, 60u, 68u, 40u, 87u, 34u, 70u, 58u, 30u, 34u, 50u, 14u, 42u, 66u, 18u, 64u, 58u, 88u, 28u, 0u,
  56u, 74u, 60u, 120u, 45u, 70u, 61u, 73u, 58u, 0u, 39u, 79u, 36u, 74u, 75u, 68u, 46u, 63u, 49u, 79u, 88u, 60u, 52u,
  36u, 74u, 46u, 57u, 43u, 40u, 35u, 74u, 48u, 50u, 43u, 30u, 87u, 10u, 0u, 10u, 67u, 45u, 53u, 81u, 39u, 38u, 74u,
  68u, 64u, 54u, 82u, 91u, 43u, 78u, 66u, 48u, 52u, 25u, 98u, 31u, 51u, 71u, 83u, 46u, 47u, 0u, 40u, 77u, 58u, 60u,
  56u, 39u, 88u, 73u, 63u, 45u, 75u, 74u, 79u, 60u, 58u, 49u, 70u, 68u, 60u, 36u, 52u, 0u, 79u, 61u, 46u, 120u, 74u,
  36u, 10u, 57u, 67u, 35u, 81u, 50u, 74u, 87u, 46u, 10u, 40u, 53u, 48u, 38u, 30u, 74u, 0u, 43u, 45u, 74u, 39u, 43u,
  68u, 71u, 43u, 40u, 25u, 64u, 83u, 78u, 77u, 98u, 54u, 46u, 66u, 58u, 31u, 82u, 47u, 48u, 60u, 51u, 91u, 0u, 52u,
  36u, 50u, 53u, 43u, 10u, 74u, 48u, 45u, 57u, 87u, 38u, 74u, 67u, 46u, 30u, 39u, 35u, 10u, 74u, 43u, 81u, 40u, 0u,
  68u, 48u, 46u, 64u, 52u, 47u, 54u, 25u, 0u, 82u, 98u, 40u, 91u, 31u, 77u, 43u, 51u, 58u, 78u, 71u, 60u, 66u, 83u,
  56u, 36u, 74u, 74u, 60u, 75u, 120u, 68u, 45u, 46u, 70u, 63u, 61u, 49u, 73u, 79u, 58u, 88u, 0u, 60u, 39u, 52u, 79u,
  48u, 30u, 0u, 58u, 28u, 70u, 88u, 34u, 58u, 87u, 64u, 40u, 18u, 68u, 66u, 60u, 42u, 68u, 14u, 60u, 50u, 64u, 34u
 };

static const QType JTable_23_28843[]=
 {
  122u, 142u, 66u, 58u, 98u, 24u, 64u, 76u, 64u, 58u, 84u, 94u, 74u, 22u, 62u, 8u, 64u, 0u, 100u, 88u, 68u, 71u, 10u,
  128u, 0u, 14u, 73u, 5u, 50u, 110u, 83u, 88u, 48u, 74u, 19u, 71u, 96u, 83u, 84u, 36u, 113u, 98u, 97u, 41u, 72u, 57u,
  39u, 82u, 72u, 151u, 42u, 95u, 147u, 80u, 90u, 64u, 137u, 56u, 80u, 83u, 97u, 62u, 62u, 80u, 97u, 74u, 123u, 49u, 0u,
  19u, 0u, 86u, 118u, 61u, 75u, 124u, 86u, 40u, 70u, 38u, 45u, 56u, 22u, 123u, 22u, 99u, 32u, 13u, 42u, 71u, 62u, 75u,
  39u, 74u, 62u, 56u, 80u, 151u, 0u, 97u, 97u, 137u, 147u, 72u, 49u, 80u, 83u, 64u, 95u, 82u, 123u, 62u, 80u, 90u, 42u,
  19u, 61u, 40u, 56u, 99u, 71u, 0u, 75u, 70u, 22u, 32u, 62u, 86u, 124u, 38u, 123u, 13u, 75u, 118u, 86u, 45u, 22u, 42u,
  128u, 41u, 113u, 83u, 19u, 88u, 50u, 14u, 57u, 97u, 36u, 96u, 74u, 83u, 5u, 0u, 72u, 98u, 84u, 71u, 48u, 110u, 73u,
  39u, 151u, 147u, 64u, 80u, 62u, 97u, 49u, 82u, 42u, 80u, 137u, 83u, 62u, 74u, 0u, 72u, 95u, 90u, 56u, 97u, 80u, 123u,
  19u, 13u, 22u, 40u, 118u, 62u, 99u, 45u, 124u, 0u, 42u, 123u, 70u, 61u, 75u, 32u, 56u, 86u, 86u, 71u, 22u, 38u, 75u,
  128u, 14u, 5u, 110u, 88u, 74u, 71u, 83u, 36u, 98u, 41u, 57u, 0u, 73u, 50u, 83u, 48u, 19u, 96u, 84u, 113u, 97u, 72u,
  122u, 71u, 88u, 0u, 8u, 22u, 94u, 58u, 76u, 24u, 58u, 142u, 10u, 68u, 100u, 64u, 62u, 74u, 84u, 64u, 64u, 98u, 66u,
  128u, 14u, 5u, 110u, 88u, 74u, 71u, 83u, 36u, 98u, 41u, 57u, 0u, 73u, 50u, 83u, 48u, 19u, 96u, 84u, 113u, 97u, 72u,
  19u, 13u, 22u, 40u, 118u, 62u, 99u, 45u, 124u, 0u, 42u, 123u, 70u, 61u, 75u, 32u, 56u, 86u, 86u, 71u, 22u, 38u, 75u,
  39u, 151u, 147u, 64u, 80u, 62u, 97u, 49u, 82u, 42u, 80u, 137u, 83u, 62u, 74u, 0u, 72u, 95u, 90u, 56u, 97u, 80u, 123u,
  128u, 41u, 113u, 83u, 19u, 88u, 50u, 14u, 57u, 97u, 36u, 96u, 74u, 83u, 5u, 0u, 72u, 98u, 84u, 71u, 48u, 110u, 73u,
  19u, 61u, 40u, 56u, 99u, 71u, 0u, 75u, 70u, 22u, 32u, 62u, 86u, 124u, 38u, 123u, 13u, 75u, 118u, 86u, 45u, 22u, 42u,
  39u, 74u, 62u, 56u, 80u, 151u, 0u, 97u, 97u, 137u, 147u, 72u, 49u, 80u, 83u, 64u, 95u, 82u, 123u, 62u, 80u, 90u, 42u,
  19u, 0u, 86u, 118u, 61u, 75u, 124u, 86u, 40u, 70u, 38u, 45u, 56u, 22u, 123u, 22u, 99u, 32u, 13u, 42u, 71u, 62u, 75u,
  39u, 82u, 72u, 151u, 42u, 95u, 147u, 80u, 90u, 64u, 137u, 56u, 80u, 83u, 97u, 62u, 62u, 80u, 97u, 74u, 123u, 49u, 0u,
  128u, 0u, 14u, 73u, 5u, 50u, 110u, 83u, 88u, 48u, 74u, 19u, 71u, 96u, 83u, 84u, 36u, 113u, 98u, 97u, 41u, 72u, 57u,
  122u, 142u, 66u, 58u, 98u, 24u, 64u, 76u, 64u, 58u, 84u, 94u, 74u, 22u, 62u, 8u, 64u, 0u, 100u, 88u, 68u, 71u, 10u
 };

static const QType JTable_23_62791[]=
 {
  40u, 80u, 120u, 38u, 20u, 122u, 38u, 180u, 20u, 18u, 32u, 114u, 94u, 14u, 50u, 52u, 0u, 40u, 73u, 182u, 82u, 114u, 132u,
  53u, 0u, 170u, 56u, 151u, 161u, 216u, 117u, 71u, 55u, 177u, 94u, 84u, 145u, 30u, 93u, 135u, 111u, 58u, 72u, 131u, 85u, 103u,
  107u, 113u, 0u, 47u, 171u, 148u, 160u, 186u, 45u, 139u, 79u, 147u, 70u, 154u, 115u, 121u, 197u, 62u, 87u, 136u, 82u, 23u, 117u,
  159u, 78u, 78u, 48u, 51u, 88u, 51u, 124u, 47u, 157u, 22u, 25u, 159u, 105u, 108u, 183u, 59u, 63u, 61u, 104u, 5u, 0u, 18u,
  107u, 136u, 121u, 147u, 186u, 47u, 117u, 87u, 115u, 79u, 160u, 0u, 23u, 62u, 154u, 139u, 148u, 113u, 82u, 197u, 70u, 45u, 171u,
  159u, 51u, 47u, 159u, 59u, 5u, 78u, 88u, 157u, 105u, 63u, 0u, 78u, 51u, 22u, 108u, 61u, 18u, 48u, 124u, 25u, 183u, 104u,
  53u, 131u, 111u, 30u, 94u, 71u, 161u, 170u, 103u, 72u, 135u, 145u, 177u, 117u, 151u, 0u, 85u, 58u, 93u, 84u, 55u, 216u, 56u,
  107u, 47u, 160u, 139u, 70u, 121u, 87u, 23u, 113u, 171u, 186u, 79u, 154u, 197u, 136u, 117u, 0u, 148u, 45u, 147u, 115u, 62u, 82u,
  159u, 61u, 105u, 47u, 48u, 0u, 59u, 25u, 51u, 78u, 104u, 108u, 157u, 51u, 18u, 63u, 159u, 124u, 78u, 5u, 183u, 22u, 88u,
  53u, 170u, 151u, 216u, 71u, 177u, 84u, 30u, 135u, 58u, 131u, 103u, 0u, 56u, 161u, 117u, 55u, 94u, 145u, 93u, 111u, 72u, 85u,
  40u, 114u, 182u, 40u, 52u, 14u, 114u, 18u, 180u, 122u, 38u, 80u, 132u, 82u, 73u, 0u, 50u, 94u, 32u, 20u, 38u, 20u, 120u,
  53u, 170u, 151u, 216u, 71u, 177u, 84u, 30u, 135u, 58u, 131u, 103u, 0u, 56u, 161u, 117u, 55u, 94u, 145u, 93u, 111u, 72u, 85u,
  159u, 61u, 105u, 47u, 48u, 0u, 59u, 25u, 51u, 78u, 104u, 108u, 157u, 51u, 18u, 63u, 159u, 124u, 78u, 5u, 183u, 22u, 88u,
  107u, 47u, 160u, 139u, 70u, 121u, 87u, 23u, 113u, 171u, 186u, 79u, 154u, 197u, 136u, 117u, 0u, 148u, 45u, 147u, 115u, 62u, 82u,
  53u, 131u, 111u, 30u, 94u, 71u, 161u, 170u, 103u, 72u, 135u, 145u, 177u, 117u, 151u, 0u, 85u, 58u, 93u, 84u, 55u, 216u, 56u,
  159u, 51u, 47u, 159u, 59u, 5u, 78u, 88u, 157u, 105u, 63u, 0u, 78u, 51u, 22u, 108u, 61u, 18u, 48u, 124u, 25u, 183u, 104u,
  107u, 136u, 121u, 147u, 186u, 47u, 117u, 87u, 115u, 79u, 160u, 0u, 23u, 62u, 154u, 139u, 148u, 113u, 82u, 197u, 70u, 45u, 171u,
  159u, 78u, 78u, 48u, 51u, 88u, 51u, 124u, 47u, 157u, 22u, 25u, 159u, 105u, 108u, 183u, 59u, 63u, 61u, 104u, 5u, 0u, 18u,
  107u, 113u, 0u, 47u, 171u, 148u, 160u, 186u, 45u, 139u, 79u, 147u, 70u, 154u, 115u, 121u, 197u, 62u, 87u, 136u, 82u, 23u, 117u,
  53u, 0u, 170u, 56u, 151u, 161u, 216u, 117u, 71u, 55u, 177u, 94u, 84u, 145u, 30u, 93u, 135u, 111u, 58u, 72u, 131u, 85u, 103u,
  40u, 80u, 120u, 38u, 20u, 122u, 38u, 180u, 20u, 18u, 32u, 114u, 94u, 14u, 50u, 52u, 0u, 40u, 73u, 182u, 82u, 114u, 132u
 };

static const QType JTable_23_91771[]=
 {
  44u, 58u, 152u, 136u, 198u, 166u, 114u, 136u, 120u, 184u, 214u, 134u, 118u, 168u, 68u, 248u, 114u, 230u, 188u, 158u, 0u, 65u, 206u,
  27u, 28u, 0u, 25u, 109u, 106u, 107u, 67u, 166u, 67u, 104u, 37u, 181u, 38u, 132u, 118u, 87u, 225u, 59u, 6u, 197u, 165u, 110u,
  96u, 0u, 175u, 101u, 137u, 120u, 96u, 29u, 288u, 195u, 48u, 96u, 47u, 74u, 38u, 51u, 159u, 78u, 109u, 76u, 78u, 99u, 40u,
  151u, 147u, 91u, 82u, 139u, 244u, 78u, 146u, 216u, 61u, 24u, 155u, 119u, 222u, 111u, 163u, 49u, 131u, 97u, 27u, 90u, 0u, 147u,
  96u, 76u, 51u, 96u, 29u, 101u, 40u, 109u, 38u, 48u, 96u, 175u, 99u, 78u, 74u, 195u, 120u, 0u, 78u, 159u, 47u, 288u, 137u,
  151u, 139u, 216u, 119u, 49u, 90u, 147u, 244u, 61u, 222u, 131u, 0u, 91u, 78u, 24u, 111u, 97u, 147u, 82u, 146u, 155u, 163u, 27u,
  27u, 197u, 225u, 132u, 37u, 166u, 106u, 0u, 110u, 6u, 87u, 38u, 104u, 67u, 109u, 28u, 165u, 59u, 118u, 181u, 67u, 107u, 25u,
  96u, 101u, 96u, 195u, 47u, 51u, 109u, 99u, 0u, 137u, 29u, 48u, 74u, 159u, 76u, 40u, 175u, 120u, 288u, 96u, 38u, 78u, 78u,
  151u, 97u, 222u, 216u, 82u, 0u, 49u, 155u, 78u, 147u, 27u, 111u, 61u, 139u, 147u, 131u, 119u, 146u, 91u, 90u, 163u, 24u, 244u,
  27u, 0u, 109u, 107u, 166u, 104u, 181u, 132u, 87u, 59u, 197u, 110u, 28u, 25u, 106u, 67u, 67u, 37u, 38u, 118u, 225u, 6u, 165u,
  44u, 65u, 158u, 230u, 248u, 168u, 134u, 184u, 136u, 166u, 136u, 58u, 206u, 0u, 188u, 114u, 68u, 118u, 214u, 120u, 114u, 198u, 152u,
  27u, 0u, 109u, 107u, 166u, 104u, 181u, 132u, 87u, 59u, 197u, 110u, 28u, 25u, 106u, 67u, 67u, 37u, 38u, 118u, 225u, 6u, 165u,
  151u, 97u, 222u, 216u, 82u, 0u, 49u, 155u, 78u, 147u, 27u, 111u, 61u, 139u, 147u, 131u, 119u, 146u, 91u, 90u, 163u, 24u, 244u,
  96u, 101u, 96u, 195u, 47u, 51u, 109u, 99u, 0u, 137u, 29u, 48u, 74u, 159u, 76u, 40u, 175u, 120u, 288u, 96u, 38u, 78u, 78u,
  27u, 197u, 225u, 132u, 37u, 166u, 106u, 0u, 110u, 6u, 87u, 38u, 104u, 67u, 109u, 28u, 165u, 59u, 118u, 181u, 67u, 107u, 25u,
  151u, 139u, 216u, 119u, 49u, 90u, 147u, 244u, 61u, 222u, 131u, 0u, 91u, 78u, 24u, 111u, 97u, 147u, 82u, 146u, 155u, 163u, 27u,
  96u, 76u, 51u, 96u, 29u, 101u, 40u, 109u, 38u, 48u, 96u, 175u, 99u, 78u, 74u, 195u, 120u, 0u, 78u, 159u, 47u, 288u, 137u,
  151u, 147u, 91u, 82u, 139u, 244u, 78u, 146u, 216u, 61u, 24u, 155u, 119u, 222u, 111u, 163u, 49u, 131u, 97u, 27u, 90u, 0u, 147u,
  96u, 0u, 175u, 101u, 137u, 120u, 96u, 29u, 288u, 195u, 48u, 96u, 47u, 74u, 38u, 51u, 159u, 78u, 109u, 76u, 78u, 99u, 40u,
  27u, 28u, 0u, 25u, 109u, 106u, 107u, 67u, 166u, 67u, 104u, 37u, 181u, 38u, 132u, 118u, 87u, 225u, 59u, 6u, 197u, 165u, 110u,
  44u, 58u, 152u, 136u, 198u, 166u, 114u, 136u, 120u, 184u, 214u, 134u, 118u, 168u, 68u, 248u, 114u, 230u, 188u, 158u, 0u, 65u, 206u
 };

static const QType JTable_23_111827[]=
 {
  196u, 272u, 180u, 110u, 264u, 94u, 144u, 238u, 212u, 0u, 90u, 134u, 212u, 174u, 176u, 222u, 204u, 290u, 114u, 214u, 92u, 189u, 226u,
  85u, 189u, 213u, 175u, 174u, 49u, 151u, 108u, 114u, 85u, 140u, 63u, 212u, 141u, 157u, 183u, 112u, 329u, 116u, 165u, 244u, 152u, 0u,
  86u, 63u, 158u, 188u, 34u, 71u, 154u, 143u, 88u, 139u, 33u, 226u, 212u, 153u, 128u, 86u, 0u, 24u, 117u, 103u, 1u, 226u, 27u,
  46u, 119u, 49u, 145u, 238u, 84u, 90u, 153u, 159u, 20u, 0u, 103u, 62u, 94u, 118u, 146u, 228u, 15u, 198u, 73u, 199u, 223u, 128u,
  86u, 103u, 86u, 226u, 143u, 188u, 27u, 117u, 128u, 33u, 154u, 158u, 226u, 24u, 153u, 139u, 71u, 63u, 1u, 0u, 212u, 88u, 34u,
  46u, 238u, 159u, 62u, 228u, 199u, 119u, 84u, 20u, 94u, 15u, 223u, 49u, 90u, 0u, 118u, 198u, 128u, 145u, 153u, 103u, 146u, 73u,
  85u, 244u, 329u, 157u, 63u, 114u, 49u, 213u, 0u, 165u, 112u, 141u, 140u, 108u, 174u, 189u, 152u, 116u, 183u, 212u, 85u, 151u, 175u,
  86u, 188u, 154u, 139u, 212u, 86u, 117u, 226u, 63u, 34u, 143u, 33u, 153u, 0u, 103u, 27u, 158u, 71u, 88u, 226u, 128u, 24u, 1u,
  46u, 198u, 94u, 159u, 145u, 223u, 228u, 103u, 90u, 119u, 73u, 118u, 20u, 238u, 128u, 15u, 62u, 153u, 49u, 199u, 146u, 0u, 84u,
  85u, 213u, 174u, 151u, 114u, 140u, 212u, 157u, 112u, 116u, 244u, 0u, 189u, 175u, 49u, 108u, 85u, 63u, 141u, 183u, 329u, 165u, 152u,
  196u, 189u, 214u, 290u, 222u, 174u, 134u, 0u, 238u, 94u, 110u, 272u, 226u, 92u, 114u, 204u, 176u, 212u, 90u, 212u, 144u, 264u, 180u,
  85u, 213u, 174u, 151u, 114u, 140u, 212u, 157u, 112u, 116u, 244u, 0u, 189u, 175u, 49u, 108u, 85u, 63u, 141u, 183u, 329u, 165u, 152u,
  46u, 198u, 94u, 159u, 145u, 223u, 228u, 103u, 90u, 119u, 73u, 118u, 20u, 238u, 128u, 15u, 62u, 153u, 49u, 199u, 146u, 0u, 84u,
  86u, 188u, 154u, 139u, 212u, 86u, 117u, 226u, 63u, 34u, 143u, 33u, 153u, 0u, 103u, 27u, 158u, 71u, 88u, 226u, 128u, 24u, 1u,
  85u, 244u, 329u, 157u, 63u, 114u, 49u, 213u, 0u, 165u, 112u, 141u, 140u, 108u, 174u, 189u, 152u, 116u, 183u, 212u, 85u, 151u, 175u,
  46u, 238u, 159u, 62u, 228u, 199u, 119u, 84u, 20u, 94u, 15u, 223u, 49u, 90u, 0u, 118u, 198u, 128u, 145u, 153u, 103u, 146u, 73u,
  86u, 103u, 86u, 226u, 143u, 188u, 27u, 117u, 128u, 33u, 154u, 158u, 226u, 24u, 153u, 139u, 71u, 63u, 1u, 0u, 212u, 88u, 34u,
  46u, 119u, 49u, 145u, 238u, 84u, 90u, 153u, 159u, 20u, 0u, 103u, 62u, 94u, 118u, 146u, 228u, 15u, 198u, 73u, 199u, 223u, 128u,
  86u, 63u, 158u, 188u, 34u, 71u, 154u, 143u, 88u, 139u, 33u, 226u, 212u, 153u, 128u, 86u, 0u, 24u, 117u, 103u, 1u, 226u, 27u,
  85u, 189u, 213u, 175u, 174u, 49u, 151u, 108u, 114u, 85u, 140u, 63u, 212u, 141u, 157u, 183u, 112u, 329u, 116u, 165u, 244u, 152u, 0u,
  196u, 272u, 180u, 110u, 264u, 94u, 144u, 238u, 212u, 0u, 90u, 134u, 212u, 174u, 176u, 222u, 204u, 290u, 114u, 214u, 92u, 189u, 226u
 };

static const QType JTable_23_138139[]=
 {
  158u, 76u, 138u, 96u, 97u, 218u, 280u, 182u, 0u, 122u, 28u, 130u, 46u, 8u, 182u, 90u, 164u, 80u, 150u, 156u, 160u, 14u, 276u,
  170u, 254u, 178u, 163u, 296u, 196u, 130u, 219u, 159u, 213u, 295u, 170u, 262u, 321u, 217u, 219u, 92u, 152u, 0u, 325u, 206u, 136u, 111u,
  157u, 227u, 158u, 124u, 294u, 186u, 55u, 293u, 211u, 166u, 65u, 59u, 3u, 208u, 157u, 187u, 128u, 139u, 121u, 127u, 196u, 0u, 188u,
  224u, 93u, 152u, 301u, 232u, 147u, 224u, 218u, 305u, 243u, 130u, 92u, 104u, 167u, 0u, 344u, 160u, 163u, 181u, 146u, 134u, 193u, 209u,
  157u, 127u, 187u, 59u, 293u, 124u, 188u, 121u, 157u, 65u, 55u, 158u, 0u, 139u, 208u, 166u, 186u, 227u, 196u, 128u, 3u, 211u, 294u,
  224u, 232u, 305u, 104u, 160u, 134u, 93u, 147u, 243u, 167u, 163u, 193u, 152u, 224u, 130u, 0u, 181u, 209u, 301u, 218u, 92u, 344u, 146u,
  170u, 206u, 152u, 217u, 170u, 159u, 196u, 178u, 111u, 325u, 92u, 321u, 295u, 219u, 296u, 254u, 136u, 0u, 219u, 262u, 213u, 130u, 163u,
  157u, 124u, 55u, 166u, 3u, 187u, 121u, 0u, 227u, 294u, 293u, 65u, 208u, 128u, 127u, 188u, 158u, 186u, 211u, 59u, 157u, 139u, 196u,
  224u, 181u, 167u, 305u, 301u, 193u, 160u, 92u, 224u, 93u, 146u, 0u, 243u, 232u, 209u, 163u, 104u, 218u, 152u, 134u, 344u, 130u, 147u,
  170u, 178u, 296u, 130u, 159u, 295u, 262u, 217u, 92u, 0u, 206u, 111u, 254u, 163u, 196u, 219u, 213u, 170u, 321u, 219u, 152u, 325u, 136u,
  158u, 14u, 156u, 80u, 90u, 8u, 130u, 122u, 182u, 218u, 96u, 76u, 276u, 160u, 150u, 164u, 182u, 46u, 28u, 0u, 280u, 97u, 138u,
  170u, 178u, 296u, 130u, 159u, 295u, 262u, 217u, 92u, 0u, 206u, 111u, 254u, 163u, 196u, 219u, 213u, 170u, 321u, 219u, 152u, 325u, 136u,
  224u, 181u, 167u, 305u, 301u, 193u, 160u, 92u, 224u, 93u, 146u, 0u, 243u, 232u, 209u, 163u, 104u, 218u, 152u, 134u, 344u, 130u, 147u,
  157u, 124u, 55u, 166u, 3u, 187u, 121u, 0u, 227u, 294u, 293u, 65u, 208u, 128u, 127u, 188u, 158u, 186u, 211u, 59u, 157u, 139u, 196u,
  170u, 206u, 152u, 217u, 170u, 159u, 196u, 178u, 111u, 325u, 92u, 321u, 295u, 219u, 296u, 254u, 136u, 0u, 219u, 262u, 213u, 130u, 163u,
  224u, 232u, 305u, 104u, 160u, 134u, 93u, 147u, 243u, 167u, 163u, 193u, 152u, 224u, 130u, 0u, 181u, 209u, 301u, 218u, 92u, 344u, 146u,
  157u, 127u, 187u, 59u, 293u, 124u, 188u, 121u, 157u, 65u, 55u, 158u, 0u, 139u, 208u, 166u, 186u, 227u, 196u, 128u, 3u, 211u, 294u,
  224u, 93u, 152u, 301u, 232u, 147u, 224u, 218u, 305u, 243u, 130u, 92u, 104u, 167u, 0u, 344u, 160u, 163u, 181u, 146u, 134u, 193u, 209u,
  157u, 227u, 158u, 124u, 294u, 186u, 55u, 293u, 211u, 166u, 65u, 59u, 3u, 208u, 157u, 187u, 128u, 139u, 121u, 127u, 196u, 0u, 188u,
  170u, 254u, 178u, 163u, 296u, 196u, 130u, 219u, 159u, 213u, 295u, 170u, 262u, 321u, 217u, 219u, 92u, 152u, 0u, 325u, 206u, 136u, 111u,
  158u, 76u, 138u, 96u, 97u, 218u, 280u, 182u, 0u, 122u, 28u, 130u, 46u, 8u, 182u, 90u, 164u, 80u, 150u, 156u, 160u, 14u, 276u
 };

static const QType JTable_23_336491[]=
 {
  450u, 88u, 178u, 0u, 208u, 146u, 156u, 134u, 238u, 76u, 338u, 404u, 68u, 230u, 322u, 436u, 140u, 235u, 138u, 134u, 308u, 192u, 302u,
  304u, 457u, 411u, 416u, 186u, 202u, 188u, 157u, 337u, 422u, 0u, 200u, 231u, 429u, 167u, 376u, 306u, 235u, 394u, 90u, 291u, 375u, 288u,
  193u, 151u, 335u, 0u, 214u, 275u, 403u, 334u, 60u, 321u, 281u, 92u, 339u, 329u, 354u, 238u, 242u, 251u, 359u, 561u, 226u, 348u, 211u,
  102u, 37u, 316u, 329u, 152u, 275u, 183u, 324u, 128u, 451u, 129u, 131u, 126u, 158u, 261u, 130u, 368u, 343u, 20u, 0u, 164u, 75u, 236u,
  193u, 561u, 238u, 92u, 334u, 0u, 211u, 359u, 354u, 281u, 403u, 335u, 348u, 251u, 329u, 321u, 275u, 151u, 226u, 242u, 339u, 60u, 214u,
  102u, 152u, 128u, 126u, 368u, 164u, 37u, 275u, 451u, 158u, 343u, 75u, 316u, 183u, 129u, 261u, 20u, 236u, 329u, 324u, 131u, 130u, 0u,
  304u, 291u, 235u, 167u, 200u, 337u, 202u, 411u, 288u, 90u, 306u, 429u, 0u, 157u, 186u, 457u, 375u, 394u, 376u, 231u, 422u, 188u, 416u,
  193u, 0u, 403u, 321u, 339u, 238u, 359u, 348u, 151u, 214u, 334u, 281u, 329u, 242u, 561u, 211u, 335u, 275u, 60u, 92u, 354u, 251u, 226u,
  102u, 20u, 158u, 128u, 329u, 75u, 368u, 131u, 183u, 37u, 0u, 261u, 451u, 152u, 236u, 343u, 126u, 324u, 316u, 164u, 130u, 129u, 275u,
  304u, 411u, 186u, 188u, 337u, 0u, 231u, 167u, 306u, 394u, 291u, 288u, 457u, 416u, 202u, 157u, 422u, 200u, 429u, 376u, 235u, 90u, 375u,
  450u, 192u, 134u, 235u, 436u, 230u, 404u, 76u, 134u, 146u, 0u, 88u, 302u, 308u, 138u, 140u, 322u, 68u, 338u, 238u, 156u, 208u, 178u,
  304u, 411u, 186u, 188u, 337u, 0u, 231u, 167u, 306u, 394u, 291u, 288u, 457u, 416u, 202u, 157u, 422u, 200u, 429u, 376u, 235u, 90u, 375u,
  102u, 20u, 158u, 128u, 329u, 75u, 368u, 131u, 183u, 37u, 0u, 261u, 451u, 152u, 236u, 343u, 126u, 324u, 316u, 164u, 130u, 129u, 275u,
  193u, 0u, 403u, 321u, 339u, 238u, 359u, 348u, 151u, 214u, 334u, 281u, 329u, 242u, 561u, 211u, 335u, 275u, 60u, 92u, 354u, 251u, 226u,
  304u, 291u, 235u, 167u, 200u, 337u, 202u, 411u, 288u, 90u, 306u, 429u, 0u, 157u, 186u, 457u, 375u, 394u, 376u, 231u, 422u, 188u, 416u,
  102u, 152u, 128u, 126u, 368u, 164u, 37u, 275u, 451u, 158u, 343u, 75u, 316u, 183u, 129u, 261u, 20u, 236u, 329u, 324u, 131u, 130u, 0u,
  193u, 561u, 238u, 92u, 334u, 0u, 211u, 359u, 354u, 281u, 403u, 335u, 348u, 251u, 329u, 321u, 275u, 151u, 226u, 242u, 339u, 60u, 214u,
  102u, 37u, 316u, 329u, 152u, 275u, 183u, 324u, 128u, 451u, 129u, 131u, 126u, 158u, 261u, 130u, 368u, 343u, 20u, 0u, 164u, 75u, 236u,
  193u, 151u, 335u, 0u, 214u, 275u, 403u, 334u, 60u, 321u, 281u, 92u, 339u, 329u, 354u, 238u, 242u, 251u, 359u, 561u, 226u, 348u, 211u,
  304u, 457u, 411u, 416u, 186u, 202u, 188u, 157u, 337u, 422u, 0u, 200u, 231u, 429u, 167u, 376u, 306u, 235u, 394u, 90u, 291u, 375u, 288u,
  450u, 88u, 178u, 0u, 208u, 146u, 156u, 134u, 238u, 76u, 338u, 404u, 68u, 230u, 322u, 436u, 140u, 235u, 138u, 134u, 308u, 192u, 302u
 };

static const QType JTable_23_355811[]=
 {
  0u, 94u, 64u, 140u, 256u, 248u, 250u, 194u, 240u, 54u, 396u, 234u, 24u, 220u, 402u, 278u, 166u, 170u, 180u, 406u, 104u, 395u, 38u,
  408u, 180u, 313u, 305u, 420u, 253u, 0u, 224u, 103u, 428u, 293u, 434u, 347u, 242u, 405u, 490u, 84u, 283u, 438u, 322u, 325u, 392u, 279u,
  167u, 206u, 246u, 367u, 180u, 55u, 352u, 249u, 292u, 339u, 14u, 424u, 229u, 282u, 229u, 475u, 154u, 0u, 75u, 116u, 141u, 280u, 256u,
  332u, 409u, 0u, 373u, 210u, 17u, 373u, 449u, 304u, 375u, 288u, 395u, 323u, 428u, 258u, 269u, 196u, 328u, 268u, 183u, 123u, 193u, 437u,
  167u, 116u, 475u, 424u, 249u, 367u, 256u, 75u, 229u, 14u, 352u, 246u, 280u, 0u, 282u, 339u, 55u, 206u, 141u, 154u, 229u, 292u, 180u,
  332u, 210u, 304u, 323u, 196u, 123u, 409u, 17u, 375u, 428u, 328u, 193u, 0u, 373u, 288u, 258u, 268u, 437u, 373u, 449u, 395u, 269u, 183u,
  408u, 325u, 283u, 405u, 434u, 103u, 253u, 313u, 279u, 322u, 84u, 242u, 293u, 224u, 420u, 180u, 392u, 438u, 490u, 347u, 428u, 0u, 305u,
  167u, 367u, 352u, 339u, 229u, 475u, 75u, 280u, 206u, 180u, 249u, 14u, 282u, 154u, 116u, 256u, 246u, 55u, 292u, 424u, 229u, 0u, 141u,
  332u, 268u, 428u, 304u, 373u, 193u, 196u, 395u, 373u, 409u, 183u, 258u, 375u, 210u, 437u, 328u, 323u, 449u, 0u, 123u, 269u, 288u, 17u,
  408u, 313u, 420u, 0u, 103u, 293u, 347u, 405u, 84u, 438u, 325u, 279u, 180u, 305u, 253u, 224u, 428u, 434u, 242u, 490u, 283u, 322u, 392u,
  0u, 395u, 406u, 170u, 278u, 220u, 234u, 54u, 194u, 248u, 140u, 94u, 38u, 104u, 180u, 166u, 402u, 24u, 396u, 240u, 250u, 256u, 64u,
  408u, 313u, 420u, 0u, 103u, 293u, 347u, 405u, 84u, 438u, 325u, 279u, 180u, 305u, 253u, 224u, 428u, 434u, 242u, 490u, 283u, 322u, 392u,
  332u, 268u, 428u, 304u, 373u, 193u, 196u, 395u, 373u, 409u, 183u, 258u, 375u, 210u, 437u, 328u, 323u, 449u, 0u, 123u, 269u, 288u, 17u,
  167u, 367u, 352u, 339u, 229u, 475u, 75u, 280u, 206u, 180u, 249u, 14u, 282u, 154u, 116u, 256u, 246u, 55u, 292u, 424u, 229u, 0u, 141u,
  408u, 325u, 283u, 405u, 434u, 103u, 253u, 313u, 279u, 322u, 84u, 242u, 293u, 224u, 420u, 180u, 392u, 438u, 490u, 347u, 428u, 0u, 305u,
  332u, 210u, 304u, 323u, 196u, 123u, 409u, 17u, 375u, 428u, 328u, 193u, 0u, 373u, 288u, 258u, 268u, 437u, 373u, 449u, 395u, 269u, 183u,
  167u, 116u, 475u, 424u, 249u, 367u, 256u, 75u, 229u, 14u, 352u, 246u, 280u, 0u, 282u, 339u, 55u, 206u, 141u, 154u, 229u, 292u, 180u,
  332u, 409u, 0u, 373u, 210u, 17u, 373u, 449u, 304u, 375u, 288u, 395u, 323u, 428u, 258u, 269u, 196u, 328u, 268u, 183u, 123u, 193u, 437u,
  167u, 206u, 246u, 367u, 180u, 55u, 352u, 249u, 292u, 339u, 14u, 424u, 229u, 282u, 229u, 475u, 154u, 0u, 75u, 116u, 141u, 280u, 256u,
  408u, 180u, 313u, 305u, 420u, 253u, 0u, 224u, 103u, 428u, 293u, 434u, 347u, 242u, 405u, 490u, 84u, 283u, 438u, 322u, 325u, 392u, 279u,
  0u, 94u, 64u, 140u, 256u, 248u, 250u, 194u, 240u, 54u, 396u, 234u, 24u, 220u, 402u, 278u, 166u, 170u, 180u, 406u, 104u, 395u, 38u
 };

static const QType JTable_23_520031[]=
 {
  326u, 486u, 270u, 328u, 280u, 0u, 398u, 166u, 214u, 456u, 540u, 358u, 350u, 444u, 500u, 308u, 26u, 534u, 338u, 552u, 360u, 368u, 171u,
  104u, 508u, 292u, 479u, 167u, 0u, 143u, 195u, 476u, 260u, 363u, 323u, 552u, 264u, 291u, 464u, 519u, 103u, 329u, 407u, 187u, 325u, 309u,
  488u, 338u, 346u, 286u, 342u, 399u, 488u, 107u, 179u, 0u, 372u, 223u, 137u, 612u, 418u, 99u, 354u, 226u, 421u, 219u, 355u, 214u, 506u,
  100u, 155u, 466u, 318u, 335u, 444u, 257u, 350u, 356u, 473u, 447u, 224u, 425u, 0u, 178u, 69u, 546u, 247u, 80u, 395u, 436u, 207u, 276u,
  488u, 219u, 99u, 223u, 107u, 286u, 506u, 421u, 418u, 372u, 488u, 346u, 214u, 226u, 612u, 0u, 399u, 338u, 355u, 354u, 137u, 179u, 342u,
  100u, 335u, 356u, 425u, 546u, 436u, 155u, 444u, 473u, 0u, 247u, 207u, 466u, 257u, 447u, 178u, 80u, 276u, 318u, 350u, 224u, 69u, 395u,
  104u, 187u, 103u, 291u, 323u, 476u, 0u, 292u, 309u, 407u, 519u, 264u, 363u, 195u, 167u, 508u, 325u, 329u, 464u, 552u, 260u, 143u, 479u,
  488u, 286u, 488u, 0u, 137u, 99u, 421u, 214u, 338u, 342u, 107u, 372u, 612u, 354u, 219u, 506u, 346u, 399u, 179u, 223u, 418u, 226u, 355u,
  100u, 80u, 0u, 356u, 318u, 207u, 546u, 224u, 257u, 155u, 395u, 178u, 473u, 335u, 276u, 247u, 425u, 350u, 466u, 436u, 69u, 447u, 444u,
  104u, 292u, 167u, 143u, 476u, 363u, 552u, 291u, 519u, 329u, 187u, 309u, 508u, 479u, 0u, 195u, 260u, 323u, 264u, 464u, 103u, 407u, 325u,
  326u, 368u, 552u, 534u, 308u, 444u, 358u, 456u, 166u, 0u, 328u, 486u, 171u, 360u, 338u, 26u, 500u, 350u, 540u, 214u, 398u, 280u, 270u,
  104u, 292u, 167u, 143u, 476u, 363u, 552u, 291u, 519u, 329u, 187u, 309u, 508u, 479u, 0u, 195u, 260u, 323u, 264u, 464u, 103u, 407u, 325u,
  100u, 80u, 0u, 356u, 318u, 207u, 546u, 224u, 257u, 155u, 395u, 178u, 473u, 335u, 276u, 247u, 425u, 350u, 466u, 436u, 69u, 447u, 444u,
  488u, 286u, 488u, 0u, 137u, 99u, 421u, 214u, 338u, 342u, 107u, 372u, 612u, 354u, 219u, 506u, 346u, 399u, 179u, 223u, 418u, 226u, 355u,
  104u, 187u, 103u, 291u, 323u, 476u, 0u, 292u, 309u, 407u, 519u, 264u, 363u, 195u, 167u, 508u, 325u, 329u, 464u, 552u, 260u, 143u, 479u,
  100u, 335u, 356u, 425u, 546u, 436u, 155u, 444u, 473u, 0u, 247u, 207u, 466u, 257u, 447u, 178u, 80u, 276u, 318u, 350u, 224u, 69u, 395u,
  488u, 219u, 99u, 223u, 107u, 286u, 506u, 421u, 418u, 372u, 488u, 346u, 214u, 226u, 612u, 0u, 399u, 338u, 355u, 354u, 137u, 179u, 342u,
  100u, 155u, 466u, 318u, 335u, 444u, 257u, 350u, 356u, 473u, 447u, 224u, 425u, 0u, 178u, 69u, 546u, 247u, 80u, 395u, 436u, 207u, 276u,
  488u, 338u, 346u, 286u, 342u, 399u, 488u, 107u, 179u, 0u, 372u, 223u, 137u, 612u, 418u, 99u, 354u, 226u, 421u, 219u, 355u, 214u, 506u,
  104u, 508u, 292u, 479u, 167u, 0u, 143u, 195u, 476u, 260u, 363u, 323u, 552u, 264u, 291u, 464u, 519u, 103u, 329u, 407u, 187u, 325u, 309u,
  326u, 486u, 270u, 328u, 280u, 0u, 398u, 166u, 214u, 456u, 540u, 358u, 350u, 444u, 500u, 308u, 26u, 534u, 338u, 552u, 360u, 368u, 171u
 };

static const QType JTable_23_782783[]=
 {
  305u, 365u, 183u, 243u, 217u, 237u, 319u, 331u, 357u, 417u, 427u, 427u, 341u, 461u, 129u, 355u, 529u, 0u, 855u, 641u, 431u, 47u, 271u,
  545u, 384u, 505u, 286u, 374u, 545u, 654u, 663u, 533u, 56u, 492u, 410u, 297u, 0u, 490u, 541u, 191u, 676u, 220u, 346u, 255u, 240u, 335u,
  180u, 121u, 639u, 598u, 437u, 356u, 288u, 233u, 448u, 163u, 263u, 419u, 28u, 0u, 435u, 93u, 382u, 437u, 291u, 285u, 112u, 596u, 95u,
  185u, 257u, 240u, 0u, 541u, 124u, 175u, 366u, 509u, 78u, 235u, 414u, 503u, 417u, 254u, 301u, 29u, 487u, 473u, 723u, 296u, 372u, 541u,
  180u, 285u, 93u, 419u, 233u, 598u, 95u, 291u, 435u, 263u, 288u, 639u, 596u, 437u, 0u, 163u, 356u, 121u, 112u, 382u, 28u, 448u, 437u,
  185u, 541u, 509u, 503u, 29u, 296u, 257u, 124u, 78u, 417u, 487u, 372u, 240u, 175u, 235u, 254u, 473u, 541u, 0u, 366u, 414u, 301u, 723u,
  545u, 255u, 676u, 490u, 410u, 533u, 545u, 505u, 335u, 346u, 191u, 0u, 492u, 663u, 374u, 384u, 240u, 220u, 541u, 297u, 56u, 654u, 286u,
  180u, 598u, 288u, 163u, 28u, 93u, 291u, 596u, 121u, 437u, 233u, 263u, 0u, 382u, 285u, 95u, 639u, 356u, 448u, 419u, 435u, 437u, 112u,
  185u, 473u, 417u, 509u, 0u, 372u, 29u, 414u, 175u, 257u, 723u, 254u, 78u, 541u, 541u, 487u, 503u, 366u, 240u, 296u, 301u, 235u, 124u,
  545u, 505u, 374u, 654u, 533u, 492u, 297u, 490u, 191u, 220u, 255u, 335u, 384u, 286u, 545u, 663u, 56u, 410u, 0u, 541u, 676u, 346u, 240u,
  305u, 47u, 641u, 0u, 355u, 461u, 427u, 417u, 331u, 237u, 243u, 365u, 271u, 431u, 855u, 529u, 129u, 341u, 427u, 357u, 319u, 217u, 183u,
  545u, 505u, 374u, 654u, 533u, 492u, 297u, 490u, 191u, 220u, 255u, 335u, 384u, 286u, 545u, 663u, 56u, 410u, 0u, 541u, 676u, 346u, 240u,
  185u, 473u, 417u, 509u, 0u, 372u, 29u, 414u, 175u, 257u, 723u, 254u, 78u, 541u, 541u, 487u, 503u, 366u, 240u, 296u, 301u, 235u, 124u,
  180u, 598u, 288u, 163u, 28u, 93u, 291u, 596u, 121u, 437u, 233u, 263u, 0u, 382u, 285u, 95u, 639u, 356u, 448u, 419u, 435u, 437u, 112u,
  545u, 255u, 676u, 490u, 410u, 533u, 545u, 505u, 335u, 346u, 191u, 0u, 492u, 663u, 374u, 384u, 240u, 220u, 541u, 297u, 56u, 654u, 286u,
  185u, 541u, 509u, 503u, 29u, 296u, 257u, 124u, 78u, 417u, 487u, 372u, 240u, 175u, 235u, 254u, 473u, 541u, 0u, 366u, 414u, 301u, 723u,
  180u, 285u, 93u, 419u, 233u, 598u, 95u, 291u, 435u, 263u, 288u, 639u, 596u, 437u, 0u, 163u, 356u, 121u, 112u, 382u, 28u, 448u, 437u,
  185u, 257u, 240u, 0u, 541u, 124u, 175u, 366u, 509u, 78u, 235u, 414u, 503u, 417u, 254u, 301u, 29u, 487u, 473u, 723u, 296u, 372u, 541u,
  180u, 121u, 639u, 598u, 437u, 356u, 288u, 233u, 448u, 163u, 263u, 419u, 28u, 0u, 435u, 93u, 382u, 437u, 291u, 285u, 112u, 596u, 95u,
  545u, 384u, 505u, 286u, 374u, 545u, 654u, 663u, 533u, 56u, 492u, 410u, 297u, 0u, 490u, 541u, 191u, 676u, 220u, 346u, 255u, 240u, 335u,
  305u, 365u, 183u, 243u, 217u, 237u, 319u, 331u, 357u, 417u, 427u, 427u, 341u, 461u, 129u, 355u, 529u, 0u, 855u, 641u, 431u, 47u, 271u
 };

static const QType JTable_23_903211[]=
 {
  318u, 276u, 550u, 302u, 192u, 266u, 454u, 530u, 274u, 104u, 430u, 360u, 756u, 396u, 748u, 546u, 0u, 452u, 246u, 176u, 338u, 559u, 52u,
  513u, 394u, 0u, 408u, 543u, 826u, 170u, 583u, 320u, 115u, 476u, 540u, 395u, 643u, 576u, 735u, 478u, 466u, 605u, 533u, 150u, 530u, 396u,
  294u, 426u, 241u, 742u, 509u, 61u, 152u, 392u, 213u, 106u, 231u, 352u, 284u, 417u, 392u, 280u, 0u, 235u, 180u, 428u, 158u, 849u, 279u,
  713u, 85u, 0u, 361u, 58u, 405u, 153u, 87u, 650u, 434u, 478u, 278u, 522u, 295u, 477u, 315u, 667u, 217u, 254u, 340u, 289u, 322u, 557u,
  294u, 428u, 280u, 352u, 392u, 742u, 279u, 180u, 392u, 231u, 152u, 241u, 849u, 235u, 417u, 106u, 61u, 426u, 158u, 0u, 284u, 213u, 509u,
  713u, 58u, 650u, 522u, 667u, 289u, 85u, 405u, 434u, 295u, 217u, 322u, 0u, 153u, 478u, 477u, 254u, 557u, 361u, 87u, 278u, 315u, 340u,
  513u, 150u, 466u, 576u, 540u, 320u, 826u, 0u, 396u, 533u, 478u, 643u, 476u, 583u, 543u, 394u, 530u, 605u, 735u, 395u, 115u, 170u, 408u,
  294u, 742u, 152u, 106u, 284u, 280u, 180u, 849u, 426u, 509u, 392u, 231u, 417u, 0u, 428u, 279u, 241u, 61u, 213u, 352u, 392u, 235u, 158u,
  713u, 254u, 295u, 650u, 361u, 322u, 667u, 278u, 153u, 85u, 340u, 477u, 434u, 58u, 557u, 217u, 522u, 87u, 0u, 289u, 315u, 478u, 405u,
  513u, 0u, 543u, 170u, 320u, 476u, 395u, 576u, 478u, 605u, 150u, 396u, 394u, 408u, 826u, 583u, 115u, 540u, 643u, 735u, 466u, 533u, 530u,
  318u, 559u, 176u, 452u, 546u, 396u, 360u, 104u, 530u, 266u, 302u, 276u, 52u, 338u, 246u, 0u, 748u, 756u, 430u, 274u, 454u, 192u, 550u,
  513u, 0u, 543u, 170u, 320u, 476u, 395u, 576u, 478u, 605u, 150u, 396u, 394u, 408u, 826u, 583u, 115u, 540u, 643u, 735u, 466u, 533u, 530u,
  713u, 254u, 295u, 650u, 361u, 322u, 667u, 278u, 153u, 85u, 340u, 477u, 434u, 58u, 557u, 217u, 522u, 87u, 0u, 289u, 315u, 478u, 405u,
  294u, 742u, 152u, 106u, 284u, 280u, 180u, 849u, 426u, 509u, 392u, 231u, 417u, 0u, 428u, 279u, 241u, 61u, 213u, 352u, 392u, 235u, 158u,
  513u, 150u, 466u, 576u, 540u, 320u, 826u, 0u, 396u, 533u, 478u, 643u, 476u, 583u, 543u, 394u, 530u, 605u, 735u, 395u, 115u, 170u, 408u,
  713u, 58u, 650u, 522u, 667u, 289u, 85u, 405u, 434u, 295u, 217u, 322u, 0u, 153u, 478u, 477u, 254u, 557u, 361u, 87u, 278u, 315u, 340u,
  294u, 428u, 280u, 352u, 392u, 742u, 279u, 180u, 392u, 231u, 152u, 241u, 849u, 235u, 417u, 106u, 61u, 426u, 158u, 0u, 284u, 213u, 509u,
  713u, 85u, 0u, 361u, 58u, 405u, 153u, 87u, 650u, 434u, 478u, 278u, 522u, 295u, 477u, 315u, 667u, 217u, 254u, 340u, 289u, 322u, 557u,
  294u, 426u, 241u, 742u, 509u, 61u, 152u, 392u, 213u, 106u, 231u, 352u, 284u, 417u, 392u, 280u, 0u, 235u, 180u, 428u, 158u, 849u, 279u,
  513u, 394u, 0u, 408u, 543u, 826u, 170u, 583u, 320u, 115u, 476u, 540u, 395u, 643u, 576u, 735u, 478u, 466u, 605u, 533u, 150u, 530u, 396u,
  318u, 276u, 550u, 302u, 192u, 266u, 454u, 530u, 274u, 104u, 430u, 360u, 756u, 396u, 748u, 546u, 0u, 452u, 246u, 176u, 338u, 559u, 52u
 };

static const QType JTable_23_1193011[]=
 {
  618u, 430u, 462u, 520u, 550u, 582u, 130u, 142u, 66u, 166u, 700u, 0u, 468u, 84u, 148u, 512u, 806u, 128u, 436u, 532u, 340u, 221u, 238u,
  530u, 524u, 733u, 642u, 468u, 396u, 313u, 862u, 0u, 496u, 436u, 273u, 52u, 235u, 513u, 748u, 351u, 433u, 299u, 10u, 451u, 616u, 209u,
  467u, 303u, 602u, 701u, 579u, 558u, 311u, 516u, 370u, 880u, 804u, 357u, 266u, 368u, 196u, 425u, 356u, 0u, 977u, 428u, 527u, 466u, 743u,
  976u, 591u, 392u, 641u, 347u, 798u, 199u, 687u, 574u, 297u, 0u, 332u, 490u, 362u, 590u, 771u, 281u, 732u, 743u, 444u, 300u, 422u, 461u,
  467u, 428u, 425u, 357u, 516u, 701u, 743u, 977u, 196u, 804u, 311u, 602u, 466u, 0u, 368u, 880u, 558u, 303u, 527u, 356u, 266u, 370u, 579u,
  976u, 347u, 574u, 490u, 281u, 300u, 591u, 798u, 297u, 362u, 732u, 422u, 392u, 199u, 0u, 590u, 743u, 461u, 641u, 687u, 332u, 771u, 444u,
  530u, 451u, 433u, 513u, 273u, 0u, 396u, 733u, 209u, 10u, 351u, 235u, 436u, 862u, 468u, 524u, 616u, 299u, 748u, 52u, 496u, 313u, 642u,
  467u, 701u, 311u, 880u, 266u, 425u, 977u, 466u, 303u, 579u, 516u, 804u, 368u, 356u, 428u, 743u, 602u, 558u, 370u, 357u, 196u, 0u, 527u,
  976u, 743u, 362u, 574u, 641u, 422u, 281u, 332u, 199u, 591u, 444u, 590u, 297u, 347u, 461u, 732u, 490u, 687u, 392u, 300u, 771u, 0u, 798u,
  530u, 733u, 468u, 313u, 0u, 436u, 52u, 513u, 351u, 299u, 451u, 209u, 524u, 642u, 396u, 862u, 496u, 273u, 235u, 748u, 433u, 10u, 616u,
  618u, 221u, 532u, 128u, 512u, 84u, 0u, 166u, 142u, 582u, 520u, 430u, 238u, 340u, 436u, 806u, 148u, 468u, 700u, 66u, 130u, 550u, 462u,
  530u, 733u, 468u, 313u, 0u, 436u, 52u, 513u, 351u, 299u, 451u, 209u, 524u, 642u, 396u, 862u, 496u, 273u, 235u, 748u, 433u, 10u, 616u,
  976u, 743u, 362u, 574u, 641u, 422u, 281u, 332u, 199u, 591u, 444u, 590u, 297u, 347u, 461u, 732u, 490u, 687u, 392u, 300u, 771u, 0u, 798u,
  467u, 701u, 311u, 880u, 266u, 425u, 977u, 466u, 303u, 579u, 516u, 804u, 368u, 356u, 428u, 743u, 602u, 558u, 370u, 357u, 196u, 0u, 527u,
  530u, 451u, 433u, 513u, 273u, 0u, 396u, 733u, 209u, 10u, 351u, 235u, 436u, 862u, 468u, 524u, 616u, 299u, 748u, 52u, 496u, 313u, 642u,
  976u, 347u, 574u, 490u, 281u, 300u, 591u, 798u, 297u, 362u, 732u, 422u, 392u, 199u, 0u, 590u, 743u, 461u, 641u, 687u, 332u, 771u, 444u,
  467u, 428u, 425u, 357u, 516u, 701u, 743u, 977u, 196u, 804u, 311u, 602u, 466u, 0u, 368u, 880u, 558u, 303u, 527u, 356u, 266u, 370u, 579u,
  976u, 591u, 392u, 641u, 347u, 798u, 199u, 687u, 574u, 297u, 0u, 332u, 490u, 362u, 590u, 771u, 281u, 732u, 743u, 444u, 300u, 422u, 461u,
  467u, 303u, 602u, 701u, 579u, 558u, 311u, 516u, 370u, 880u, 804u, 357u, 266u, 368u, 196u, 425u, 356u, 0u, 977u, 428u, 527u, 466u, 743u,
  530u, 524u, 733u, 642u, 468u, 396u, 313u, 862u, 0u, 496u, 436u, 273u, 52u, 235u, 513u, 748u, 351u, 433u, 299u, 10u, 451u, 616u, 209u,
  618u, 430u, 462u, 520u, 550u, 582u, 130u, 142u, 66u, 166u, 700u, 0u, 468u, 84u, 148u, 512u, 806u, 128u, 436u, 532u, 340u, 221u, 238u
 };

static const QType JTable_23_2348347[]=
 {
  614u, 534u, 650u, 518u, 261u, 620u, 748u, 624u, 48u, 864u, 914u, 1006u, 594u, 1408u, 370u, 532u, 330u, 0u, 1030u, 720u, 340u, 440u, 450u,
  795u, 494u, 435u, 41u, 632u, 408u, 147u, 669u, 530u, 102u, 136u, 641u, 668u, 866u, 0u, 55u, 467u, 418u, 772u, 623u, 628u, 1289u, 154u,
  368u, 915u, 754u, 794u, 898u, 905u, 623u, 504u, 938u, 391u, 943u, 550u, 1431u, 632u, 983u, 1390u, 631u, 636u, 874u, 759u, 1153u, 660u, 0u,
  180u, 1036u, 830u, 415u, 1138u, 643u, 674u, 934u, 750u, 236u, 864u, 623u, 1366u, 614u, 545u, 610u, 694u, 1087u, 457u, 755u, 449u, 509u, 0u,
  368u, 759u, 1390u, 550u, 504u, 794u, 0u, 874u, 983u, 943u, 623u, 754u, 660u, 636u, 632u, 391u, 905u, 915u, 1153u, 631u, 1431u, 938u, 898u,
  180u, 1138u, 750u, 1366u, 694u, 449u, 1036u, 643u, 236u, 614u, 1087u, 509u, 830u, 674u, 864u, 545u, 457u, 0u, 415u, 934u, 623u, 610u, 755u,
  795u, 628u, 418u, 0u, 641u, 530u, 408u, 435u, 154u, 623u, 467u, 866u, 136u, 669u, 632u, 494u, 1289u, 772u, 55u, 668u, 102u, 147u, 41u,
  368u, 794u, 623u, 391u, 1431u, 1390u, 874u, 660u, 915u, 898u, 504u, 943u, 632u, 631u, 759u, 0u, 754u, 905u, 938u, 550u, 983u, 636u, 1153u,
  180u, 457u, 614u, 750u, 415u, 509u, 694u, 623u, 674u, 1036u, 755u, 545u, 236u, 1138u, 0u, 1087u, 1366u, 934u, 830u, 449u, 610u, 864u, 643u,
  795u, 435u, 632u, 147u, 530u, 136u, 668u, 0u, 467u, 772u, 628u, 154u, 494u, 41u, 408u, 669u, 102u, 641u, 866u, 55u, 418u, 623u, 1289u,
  614u, 440u, 720u, 0u, 532u, 1408u, 1006u, 864u, 624u, 620u, 518u, 534u, 450u, 340u, 1030u, 330u, 370u, 594u, 914u, 48u, 748u, 261u, 650u,
  795u, 435u, 632u, 147u, 530u, 136u, 668u, 0u, 467u, 772u, 628u, 154u, 494u, 41u, 408u, 669u, 102u, 641u, 866u, 55u, 418u, 623u, 1289u,
  180u, 457u, 614u, 750u, 415u, 509u, 694u, 623u, 674u, 1036u, 755u, 545u, 236u, 1138u, 0u, 1087u, 1366u, 934u, 830u, 449u, 610u, 864u, 643u,
  368u, 794u, 623u, 391u, 1431u, 1390u, 874u, 660u, 915u, 898u, 504u, 943u, 632u, 631u, 759u, 0u, 754u, 905u, 938u, 550u, 983u, 636u, 1153u,
  795u, 628u, 418u, 0u, 641u, 530u, 408u, 435u, 154u, 623u, 467u, 866u, 136u, 669u, 632u, 494u, 1289u, 772u, 55u, 668u, 102u, 147u, 41u,
  180u, 1138u, 750u, 1366u, 694u, 449u, 1036u, 643u, 236u, 614u, 1087u, 509u, 830u, 674u, 864u, 545u, 457u, 0u, 415u, 934u, 623u, 610u, 755u,
  368u, 759u, 1390u, 550u, 504u, 794u, 0u, 874u, 983u, 943u, 623u, 754u, 660u, 636u, 632u, 391u, 905u, 915u, 1153u, 631u, 1431u, 938u, 898u,
  180u, 1036u, 830u, 415u, 1138u, 643u, 674u, 934u, 750u, 236u, 864u, 623u, 1366u, 614u, 545u, 610u, 694u, 1087u, 457u, 755u, 449u, 509u, 0u,
  368u, 915u, 754u, 794u, 898u, 905u, 623u, 504u, 938u, 391u, 943u, 550u, 1431u, 632u, 983u, 1390u, 631u, 636u, 874u, 759u, 1153u, 660u, 0u,
  795u, 494u, 435u, 41u, 632u, 408u, 147u, 669u, 530u, 102u, 136u, 641u, 668u, 866u, 0u, 55u, 467u, 418u, 772u, 623u, 628u, 1289u, 154u,
  614u, 534u, 650u, 518u, 261u, 620u, 748u, 624u, 48u, 864u, 914u, 1006u, 594u, 1408u, 370u, 532u, 330u, 0u, 1030u, 720u, 340u, 440u, 450u
 };

static const QType JTable_23_2624623[]=
 {
  1506u, 808u, 0u, 444u, 750u, 790u, 1026u, 380u, 1272u, 228u, 782u, 682u, 305u, 504u, 780u, 690u, 838u, 1066u, 652u, 1056u, 920u, 774u, 858u,
  529u, 184u, 320u, 436u, 793u, 1129u, 0u, 967u, 974u, 521u, 200u, 313u, 274u, 46u, 378u, 710u, 198u, 715u, 70u, 699u, 310u, 722u, 1057u,
  644u, 878u, 357u, 344u, 237u, 238u, 537u, 316u, 1207u, 719u, 268u, 612u, 1428u, 137u, 649u, 212u, 498u, 697u, 268u, 233u, 0u, 482u, 446u,
  203u, 808u, 290u, 300u, 582u, 371u, 473u, 788u, 565u, 625u, 755u, 392u, 721u, 321u, 931u, 41u, 923u, 1136u, 1394u, 581u, 0u, 818u, 505u,
  644u, 233u, 212u, 612u, 316u, 344u, 446u, 268u, 649u, 268u, 537u, 357u, 482u, 697u, 137u, 719u, 238u, 878u, 0u, 498u, 1428u, 1207u, 237u,
  203u, 582u, 565u, 721u, 923u, 0u, 808u, 371u, 625u, 321u, 1136u, 818u, 290u, 473u, 755u, 931u, 1394u, 505u, 300u, 788u, 392u, 41u, 581u,
  529u, 310u, 715u, 378u, 313u, 974u, 1129u, 320u, 1057u, 699u, 198u, 46u, 200u, 967u, 793u, 184u, 722u, 70u, 710u, 274u, 521u, 0u, 436u,
  644u, 344u, 537u, 719u, 1428u, 212u, 268u, 482u, 878u, 237u, 316u, 268u, 137u, 498u, 233u, 446u, 357u, 238u, 1207u, 612u, 649u, 697u, 0u,
  203u, 1394u, 321u, 565u, 300u, 818u, 923u, 392u, 473u, 808u, 581u, 931u, 625u, 582u, 505u, 1136u, 721u, 788u, 290u, 0u, 41u, 755u, 371u,
  529u, 320u, 793u, 0u, 974u, 200u, 274u, 378u, 198u, 70u, 310u, 1057u, 184u, 436u, 1129u, 967u, 521u, 313u, 46u, 710u, 715u, 699u, 722u,
  1506u, 774u, 1056u, 1066u, 690u, 504u, 682u, 228u, 380u, 790u, 444u, 808u, 858u, 920u, 652u, 838u, 780u, 305u, 782u, 1272u, 1026u, 750u, 0u,
  529u, 320u, 793u, 0u, 974u, 200u, 274u, 378u, 198u, 70u, 310u, 1057u, 184u, 436u, 1129u, 967u, 521u, 313u, 46u, 710u, 715u, 699u, 722u,
  203u, 1394u, 321u, 565u, 300u, 818u, 923u, 392u, 473u, 808u, 581u, 931u, 625u, 582u, 505u, 1136u, 721u, 788u, 290u, 0u, 41u, 755u, 371u,
  644u, 344u, 537u, 719u, 1428u, 212u, 268u, 482u, 878u, 237u, 316u, 268u, 137u, 498u, 233u, 446u, 357u, 238u, 1207u, 612u, 649u, 697u, 0u,
  529u, 310u, 715u, 378u, 313u, 974u, 1129u, 320u, 1057u, 699u, 198u, 46u, 200u, 967u, 793u, 184u, 722u, 70u, 710u, 274u, 521u, 0u, 436u,
  203u, 582u, 565u, 721u, 923u, 0u, 808u, 371u, 625u, 321u, 1136u, 818u, 290u, 473u, 755u, 931u, 1394u, 505u, 300u, 788u, 392u, 41u, 581u,
  644u, 233u, 212u, 612u, 316u, 344u, 446u, 268u, 649u, 268u, 537u, 357u, 482u, 697u, 137u, 719u, 238u, 878u, 0u, 498u, 1428u, 1207u, 237u,
  203u, 808u, 290u, 300u, 582u, 371u, 473u, 788u, 565u, 625u, 755u, 392u, 721u, 321u, 931u, 41u, 923u, 1136u, 1394u, 581u, 0u, 818u, 505u,
  644u, 878u, 357u, 344u, 237u, 238u, 537u, 316u, 1207u, 719u, 268u, 612u, 1428u, 137u, 649u, 212u, 498u, 697u, 268u, 233u, 0u, 482u, 446u,
  529u, 184u, 320u, 436u, 793u, 1129u, 0u, 967u, 974u, 521u, 200u, 313u, 274u, 46u, 378u, 710u, 198u, 715u, 70u, 699u, 310u, 722u, 1057u,
  1506u, 808u, 0u, 444u, 750u, 790u, 1026u, 380u, 1272u, 228u, 782u, 682u, 305u, 504u, 780u, 690u, 838u, 1066u, 652u, 1056u, 920u, 774u, 858u
 };

static const QType JTable_23_2897311[]=
 {
  168u, 666u, 662u, 0u, 392u, 658u, 654u, 386u, 418u, 446u, 1300u, 1314u, 750u, 342u, 771u, 320u, 408u, 868u, 470u, 1108u, 52u, 1016u, 492u,
  340u, 908u, 46u, 1410u, 671u, 648u, 900u, 1239u, 1257u, 889u, 800u, 1051u, 893u, 1074u, 1021u, 623u, 0u, 632u, 1080u, 723u, 771u, 1226u, 772u,
  1429u, 698u, 1234u, 1388u, 671u, 555u, 714u, 449u, 1095u, 568u, 701u, 805u, 1291u, 838u, 248u, 935u, 0u, 978u, 1058u, 1078u, 618u, 668u, 1047u,
  860u, 1252u, 1348u, 1169u, 1134u, 507u, 1158u, 1373u, 0u, 758u, 1061u, 1168u, 834u, 1089u, 378u, 1013u, 399u, 811u, 839u, 818u, 830u, 297u, 798u,
  1429u, 1078u, 935u, 805u, 449u, 1388u, 1047u, 1058u, 248u, 701u, 714u, 1234u, 668u, 978u, 838u, 568u, 555u, 698u, 618u, 0u, 1291u, 1095u, 671u,
  860u, 1134u, 0u, 834u, 399u, 830u, 1252u, 507u, 758u, 1089u, 811u, 297u, 1348u, 1158u, 1061u, 378u, 839u, 798u, 1169u, 1373u, 1168u, 1013u, 818u,
  340u, 771u, 632u, 1021u, 1051u, 1257u, 648u, 46u, 772u, 723u, 0u, 1074u, 800u, 1239u, 671u, 908u, 1226u, 1080u, 623u, 893u, 889u, 900u, 1410u,
  1429u, 1388u, 714u, 568u, 1291u, 935u, 1058u, 668u, 698u, 671u, 449u, 701u, 838u, 0u, 1078u, 1047u, 1234u, 555u, 1095u, 805u, 248u, 978u, 618u,
  860u, 839u, 1089u, 0u, 1169u, 297u, 399u, 1168u, 1158u, 1252u, 818u, 378u, 758u, 1134u, 798u, 811u, 834u, 1373u, 1348u, 830u, 1013u, 1061u, 507u,
  340u, 46u, 671u, 900u, 1257u, 800u, 893u, 1021u, 0u, 1080u, 771u, 772u, 908u, 1410u, 648u, 1239u, 889u, 1051u, 1074u, 623u, 632u, 723u, 1226u,
  168u, 1016u, 1108u, 868u, 320u, 342u, 1314u, 446u, 386u, 658u, 0u, 666u, 492u, 52u, 470u, 408u, 771u, 750u, 1300u, 418u, 654u, 392u, 662u,
  340u, 46u, 671u, 900u, 1257u, 800u, 893u, 1021u, 0u, 1080u, 771u, 772u, 908u, 1410u, 648u, 1239u, 889u, 1051u, 1074u, 623u, 632u, 723u, 1226u,
  860u, 839u, 1089u, 0u, 1169u, 297u, 399u, 1168u, 1158u, 1252u, 818u, 378u, 758u, 1134u, 798u, 811u, 834u, 1373u, 1348u, 830u, 1013u, 1061u, 507u,
  1429u, 1388u, 714u, 568u, 1291u, 935u, 1058u, 668u, 698u, 671u, 449u, 701u, 838u, 0u, 1078u, 1047u, 1234u, 555u, 1095u, 805u, 248u, 978u, 618u,
  340u, 771u, 632u, 1021u, 1051u, 1257u, 648u, 46u, 772u, 723u, 0u, 1074u, 800u, 1239u, 671u, 908u, 1226u, 1080u, 623u, 893u, 889u, 900u, 1410u,
  860u, 1134u, 0u, 834u, 399u, 830u, 1252u, 507u, 758u, 1089u, 811u, 297u, 1348u, 1158u, 1061u, 378u, 839u, 798u, 1169u, 1373u, 1168u, 1013u, 818u,
  1429u, 1078u, 935u, 805u, 449u, 1388u, 1047u, 1058u, 248u, 701u, 714u, 1234u, 668u, 978u, 838u, 568u, 555u, 698u, 618u, 0u, 1291u, 1095u, 671u,
  860u, 1252u, 1348u, 1169u, 1134u, 507u, 1158u, 1373u, 0u, 758u, 1061u, 1168u, 834u, 1089u, 378u, 1013u, 399u, 811u, 839u, 818u, 830u, 297u, 798u,
  1429u, 698u, 1234u, 1388u, 671u, 555u, 714u, 449u, 1095u, 568u, 701u, 805u, 1291u, 838u, 248u, 935u, 0u, 978u, 1058u, 1078u, 618u, 668u, 1047u,
  340u, 908u, 46u, 1410u, 671u, 648u, 900u, 1239u, 1257u, 889u, 800u, 1051u, 893u, 1074u, 1021u, 623u, 0u, 632u, 1080u, 723u, 771u, 1226u, 772u,
  168u, 666u, 662u, 0u, 392u, 658u, 654u, 386u, 418u, 446u, 1300u, 1314u, 750u, 342u, 771u, 320u, 408u, 868u, 470u, 1108u, 52u, 1016u, 492u
 };

static const QType JTable_23_13123111[]=
 {
  1182u, 1986u, 1534u, 2530u, 1015u, 2296u, 1488u, 1716u, 2016u, 2080u, 1484u, 2506u, 1766u, 140u, 1530u, 0u, 834u, 2584u, 2218u, 1756u, 744u, 1850u, 2970u,
  744u, 659u, 818u, 634u, 2915u, 1765u, 1974u, 1674u, 873u, 1273u, 2221u, 1828u, 1351u, 1863u, 2787u, 0u, 2222u, 1995u, 2539u, 1552u, 655u, 1674u, 1311u,
  1416u, 849u, 1352u, 2268u, 954u, 2333u, 2117u, 442u, 88u, 1755u, 1813u, 2266u, 1105u, 1266u, 2215u, 28u, 1941u, 716u, 1606u, 999u, 399u, 0u, 1120u,
  1771u, 2251u, 449u, 2948u, 1833u, 1634u, 2185u, 2007u, 1803u, 571u, 1277u, 2808u, 1933u, 1079u, 2186u, 1295u, 1607u, 1648u, 0u, 560u, 1620u, 1378u, 2715u,
  1416u, 999u, 28u, 2266u, 442u, 2268u, 1120u, 1606u, 2215u, 1813u, 2117u, 1352u, 0u, 716u, 1266u, 1755u, 2333u, 849u, 399u, 1941u, 1105u, 88u, 954u,
  1771u, 1833u, 1803u, 1933u, 1607u, 1620u, 2251u, 1634u, 571u, 1079u, 1648u, 1378u, 449u, 2185u, 1277u, 2186u, 0u, 2715u, 2948u, 2007u, 2808u, 1295u, 560u,
  744u, 655u, 1995u, 2787u, 1828u, 873u, 1765u, 818u, 1311u, 1552u, 2222u, 1863u, 2221u, 1674u, 2915u, 659u, 1674u, 2539u, 0u, 1351u, 1273u, 1974u, 634u,
  1416u, 2268u, 2117u, 1755u, 1105u, 28u, 1606u, 0u, 849u, 954u, 442u, 1813u, 1266u, 1941u, 999u, 1120u, 1352u, 2333u, 88u, 2266u, 2215u, 716u, 399u,
  1771u, 0u, 1079u, 1803u, 2948u, 1378u, 1607u, 2808u, 2185u, 2251u, 560u, 2186u, 571u, 1833u, 2715u, 1648u, 1933u, 2007u, 449u, 1620u, 1295u, 1277u, 1634u,
  744u, 818u, 2915u, 1974u, 873u, 2221u, 1351u, 2787u, 2222u, 2539u, 655u, 1311u, 659u, 634u, 1765u, 1674u, 1273u, 1828u, 1863u, 0u, 1995u, 1552u, 1674u,
  1182u, 1850u, 1756u, 2584u, 0u, 140u, 2506u, 2080u, 1716u, 2296u, 2530u, 1986u, 2970u, 744u, 2218u, 834u, 1530u, 1766u, 1484u, 2016u, 1488u, 1015u, 1534u,
  744u, 818u, 2915u, 1974u, 873u, 2221u, 1351u, 2787u, 2222u, 2539u, 655u, 1311u, 659u, 634u, 1765u, 1674u, 1273u, 1828u, 1863u, 0u, 1995u, 1552u, 1674u,
  1771u, 0u, 1079u, 1803u, 2948u, 1378u, 1607u, 2808u, 2185u, 2251u, 560u, 2186u, 571u, 1833u, 2715u, 1648u, 1933u, 2007u, 449u, 1620u, 1295u, 1277u, 1634u,
  1416u, 2268u, 2117u, 1755u, 1105u, 28u, 1606u, 0u, 849u, 954u, 442u, 1813u, 1266u, 1941u, 999u, 1120u, 1352u, 2333u, 88u, 2266u, 2215u, 716u, 399u,
  744u, 655u, 1995u, 2787u, 1828u, 873u, 1765u, 818u, 1311u, 1552u, 2222u, 1863u, 2221u, 1674u, 2915u, 659u, 1674u, 2539u, 0u, 1351u, 1273u, 1974u, 634u,
  1771u, 1833u, 1803u, 1933u, 1607u, 1620u, 2251u, 1634u, 571u, 1079u, 1648u, 1378u, 449u, 2185u, 1277u, 2186u, 0u, 2715u, 2948u, 2007u, 2808u, 1295u, 560u,
  1416u, 999u, 28u, 2266u, 442u, 2268u, 1120u, 1606u, 2215u, 1813u, 2117u, 1352u, 0u, 716u, 1266u, 1755u, 2333u, 849u, 399u, 1941u, 1105u, 88u, 954u,
  1771u, 2251u, 449u, 2948u, 1833u, 1634u, 2185u, 2007u, 1803u, 571u, 1277u, 2808u, 1933u, 1079u, 2186u, 1295u, 1607u, 1648u, 0u, 560u, 1620u, 1378u, 2715u,
  1416u, 849u, 1352u, 2268u, 954u, 2333u, 2117u, 442u, 88u, 1755u, 1813u, 2266u, 1105u, 1266u, 2215u, 28u, 1941u, 716u, 1606u, 999u, 399u, 0u, 1120u,
  744u, 659u, 818u, 634u, 2915u, 1765u, 1974u, 1674u, 873u, 1273u, 2221u, 1828u, 1351u, 1863u, 2787u, 0u, 2222u, 1995u, 2539u, 1552u, 655u, 1674u, 1311u,
  1182u, 1986u, 1534u, 2530u, 1015u, 2296u, 1488u, 1716u, 2016u, 2080u, 1484u, 2506u, 1766u, 140u, 1530u, 0u, 834u, 2584u, 2218u, 1756u, 744u, 1850u, 2970u
 };

static const QType JTable_23_17160991[]=
 {
  1072u, 804u, 2348u, 2084u, 2095u, 2230u, 2658u, 1110u, 302u, 906u, 1810u, 980u, 1466u, 1902u, 1074u, 726u, 2772u, 444u, 0u, 1316u, 306u, 3092u, 840u,
  2403u, 3288u, 2820u, 2723u, 1262u, 1801u, 0u, 2981u, 2430u, 2415u, 2119u, 1168u, 2186u, 2723u, 2427u, 1597u, 2574u, 3407u, 591u, 2237u, 3288u, 2364u, 3129u,
  2682u, 1708u, 485u, 1605u, 174u, 3001u, 0u, 509u, 2430u, 2959u, 1368u, 2194u, 2193u, 1743u, 2006u, 2230u, 2023u, 1837u, 1417u, 448u, 795u, 1969u, 1667u,
  2343u, 2421u, 2295u, 161u, 3243u, 1708u, 2338u, 3399u, 1354u, 1684u, 1873u, 2844u, 1768u, 1052u, 2506u, 2962u, 2381u, 1796u, 1777u, 1762u, 0u, 1262u, 1046u,
  2682u, 448u, 2230u, 2194u, 509u, 1605u, 1667u, 1417u, 2006u, 1368u, 0u, 485u, 1969u, 1837u, 1743u, 2959u, 3001u, 1708u, 795u, 2023u, 2193u, 2430u, 174u,
  2343u, 3243u, 1354u, 1768u, 2381u, 0u, 2421u, 1708u, 1684u, 1052u, 1796u, 1262u, 2295u, 2338u, 1873u, 2506u, 1777u, 1046u, 161u, 3399u, 2844u, 2962u, 1762u,
  2403u, 3288u, 3407u, 2427u, 1168u, 2430u, 1801u, 2820u, 3129u, 2237u, 2574u, 2723u, 2119u, 2981u, 1262u, 3288u, 2364u, 591u, 1597u, 2186u, 2415u, 0u, 2723u,
  2682u, 1605u, 0u, 2959u, 2193u, 2230u, 1417u, 1969u, 1708u, 174u, 509u, 1368u, 1743u, 2023u, 448u, 1667u, 485u, 3001u, 2430u, 2194u, 2006u, 1837u, 795u,
  2343u, 1777u, 1052u, 1354u, 161u, 1262u, 2381u, 2844u, 2338u, 2421u, 1762u, 2506u, 1684u, 3243u, 1046u, 1796u, 1768u, 3399u, 2295u, 0u, 2962u, 1873u, 1708u,
  2403u, 2820u, 1262u, 0u, 2430u, 2119u, 2186u, 2427u, 2574u, 591u, 3288u, 3129u, 3288u, 2723u, 1801u, 2981u, 2415u, 1168u, 2723u, 1597u, 3407u, 2237u, 2364u,
  1072u, 3092u, 1316u, 444u, 726u, 1902u, 980u, 906u, 1110u, 2230u, 2084u, 804u, 840u, 306u, 0u, 2772u, 1074u, 1466u, 1810u, 302u, 2658u, 2095u, 2348u,
  2403u, 2820u, 1262u, 0u, 2430u, 2119u, 2186u, 2427u, 2574u, 591u, 3288u, 3129u, 3288u, 2723u, 1801u, 2981u, 2415u, 1168u, 2723u, 1597u, 3407u, 2237u, 2364u,
  2343u, 1777u, 1052u, 1354u, 161u, 1262u, 2381u, 2844u, 2338u, 2421u, 1762u, 2506u, 1684u, 3243u, 1046u, 1796u, 1768u, 3399u, 2295u, 0u, 2962u, 1873u, 1708u,
  2682u, 1605u, 0u, 2959u, 2193u, 2230u, 1417u, 1969u, 1708u, 174u, 509u, 1368u, 1743u, 2023u, 448u, 1667u, 485u, 3001u, 2430u, 2194u, 2006u, 1837u, 795u,
  2403u, 3288u, 3407u, 2427u, 1168u, 2430u, 1801u, 2820u, 3129u, 2237u, 2574u, 2723u, 2119u, 2981u, 1262u, 3288u, 2364u, 591u, 1597u, 2186u, 2415u, 0u, 2723u,
  2343u, 3243u, 1354u, 1768u, 2381u, 0u, 2421u, 1708u, 1684u, 1052u, 1796u, 1262u, 2295u, 2338u, 1873u, 2506u, 1777u, 1046u, 161u, 3399u, 2844u, 2962u, 1762u,
  2682u, 448u, 2230u, 2194u, 509u, 1605u, 1667u, 1417u, 2006u, 1368u, 0u, 485u, 1969u, 1837u, 1743u, 2959u, 3001u, 1708u, 795u, 2023u, 2193u, 2430u, 174u,
  2343u, 2421u, 2295u, 161u, 3243u, 1708u, 2338u, 3399u, 1354u, 1684u, 1873u, 2844u, 1768u, 1052u, 2506u, 2962u, 2381u, 1796u, 1777u, 1762u, 0u, 1262u, 1046u,
  2682u, 1708u, 485u, 1605u, 174u, 3001u, 0u, 509u, 2430u, 2959u, 1368u, 2194u, 2193u, 1743u, 2006u, 2230u, 2023u, 1837u, 1417u, 448u, 795u, 1969u, 1667u,
  2403u, 3288u, 2820u, 2723u, 1262u, 1801u, 0u, 2981u, 2430u, 2415u, 2119u, 1168u, 2186u, 2723u, 2427u, 1597u, 2574u, 3407u, 591u, 2237u, 3288u, 2364u, 3129u,
  1072u, 804u, 2348u, 2084u, 2095u, 2230u, 2658u, 1110u, 302u, 906u, 1810u, 980u, 1466u, 1902u, 1074u, 726u, 2772u, 444u, 0u, 1316u, 306u, 3092u, 840u
 };

static const TestSet::JTable JSet_23[]=
 {
  { 47u , 7u , JTable_23_47 },
  { 139u , 7u , JTable_23_139 },
  { 599u , 7u , JTable_23_599 },
  { 691u , 7u , JTable_23_691 },
  { 967u , 7u , JTable_23_967 },
  { 2347u , 7u , JTable_23_2347 },
  { 2531u , 7u , JTable_23_2531 },
  { 3911u , 7u , JTable_23_3911 },
  { 4831u , 7u , JTable_23_4831 },
  { 7591u , 7u , JTable_23_7591 },
  { 8971u , 7u , JTable_23_8971 },
  { 10627u , 7u , JTable_23_10627 },
  { 11731u , 7u , JTable_23_11731 },
  { 28843u , 7u , JTable_23_28843 },
  { 62791u , 7u , JTable_23_62791 },
  { 91771u , 7u , JTable_23_91771 },
  { 111827u , 7u , JTable_23_111827 },
  { 138139u , 7u , JTable_23_138139 },
  { 336491u , 7u , JTable_23_336491 },
  { 355811u , 7u , JTable_23_355811 },
  { 520031u , 7u , JTable_23_520031 },
  { 782783u , 7u , JTable_23_782783 },
  { 903211u , 7u , JTable_23_903211 },
  { 1193011u , 7u , JTable_23_1193011 },
  { 2348347u , 7u , JTable_23_2348347 },
  { 2624623u , 7u , JTable_23_2624623 },
  { 2897311u , 7u , JTable_23_2897311 },
  { 13123111u , 7u , JTable_23_13123111 },
  { 17160991u , 7u , JTable_23_17160991 }
 };

static const TestSet PSet[]=
 {
  { 2u , Range(JSet_2) },
  { 3u , Range(JSet_3) },
  { 5u , Range(JSet_5) },
  { 7u , Range(JSet_7) },
  { 11u , Range(JSet_11) },
  { 13u , Range(JSet_13) },
  { 17u , Range(JSet_17) },
  { 19u , Range(JSet_19) },
  { 23u , Range(JSet_23) }
 };

/* class TestData */

TestData::TestData()
 {
  pset=PSet;
  qset=Range(QSet);
 }

} // namespace APRTest
} // namespace Math
} // namespace CCore

