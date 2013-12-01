/* int.ddl */

int i = 101111b + (+456)*(-789)/12 - 0ABCDEFh%113 ;

sint8 s8 = 101111b + (+456)*(-789)/12 - 0ABCDEFh%113 ;
uint8 u8 = 101111b + (+456)*(-789)/12 - 0ABCDEFh%113 ;

sint16 s16 = 101111b + (+456)*(-789)/12 - 0ABCDEFh%113 ;
uint16 u16 = 101111b + (+456)*(-789)/12 - 0ABCDEFh%113 ;

sint32 s32 = 101111b + (+456)*(-789)/12 - 0ABCDEFh%113 ;
uint32 u32 = 101111b + (+456)*(-789)/12 - 0ABCDEFh%113 ;

sint64 s64 = 101111b + (+456)*(-789)/12 - 0ABCDEFh%113 ;
uint64 u64 = 101111b + (+456)*(-789)/12 - 0ABCDEFh%113 ;

int[] a = {} ;

int diff1 = &a[10] - &a[0] ;
int diff2 = &a[0] - &a[10] ;

type small = sint8 ;

int diff3 = small( (a+1000) - a ) ;

