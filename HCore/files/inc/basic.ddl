/* basic.ddl */

sint8 s8 = 1 ;
uint8 u8 = 2 ;

sint16 s16 = 3 ;
uint16 u16 = 4 ;

sint32 s32 = 5 ;
uint32 u32 = 6 ;

sint64 s64 = 7 ;
uint64 u64 = 8 ;

int i = 9 ;
sint s = 10 ;
uint u = 11 ;

text t = "text" ;
ip a = 192.168.1.10 ;

text *ptr_t=&t ;

text at_ptr_t = *ptr_t ;

int[10] array_len_i = {1,2,3,4,5,6,7,8,9} ;

int[] array_i = {1,2,3,4,5} ;

struct Struct
{
 int fi = 1 ;
 uint fu = 2 ;
 text ft = "default" ;
};

type List = Struct[] ;

List list={ {-1,-2,"neg"},{3,4,"pos"},{},null };

