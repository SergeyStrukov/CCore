/* ARMCmd.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: ARMGo 0.50
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2012 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef ARMGo_inc_ARMCmd_h
#define ARMGo_inc_ARMCmd_h

#include <CCore/inc/Sort.h>
#include <CCore/inc/Array.h>

#include <inc/ARMState.h>

namespace ARMCore {

/* consts */ 

enum OpCode : Word
 {
  Op_AND,
  Op_EOR,
  Op_SUB,
  Op_RSB,
  
  Op_ADD,
  Op_ADC,
  Op_SBC,
  Op_RSC,
  
  Op_TST, // Rd = 0, S = 1
  Op_TEQ, // Rd = 0, S = 1
  Op_CMP, // Rd = 0, S = 1
  Op_CMN, // Rd = 0, S = 1
  
  Op_ORR,
  Op_MOV, // Rn = 0
  Op_BIC,
  Op_MVN  // Rn = 0
 }; 

/* classes */

struct Result;
struct ResultC;
struct ResultCV;
struct ResultQ;
struct ResultD;

struct DoAND;
struct DoEOR;
struct DoORR;
struct DoBIC;

struct DoADD;
struct DoSUB;

struct DoADC;
struct DoSBC;

struct DoMOV;
struct DoMVN;

struct DoCLZ;

struct DoQADD;
struct DoQSUB;
struct DoQDouble;
struct DoQDADD;
struct DoQDSUB;

struct DoMUL;
struct DoMLA;

struct DoSMULL;
struct DoUMULL;

struct DoSMLAL;
struct DoUMLAL;

struct DoSMULxy;
struct DoSMULWy;

struct DoSMLAxy;
struct DoSMLAWy;
struct DoSMLALxy;

struct PrintReg;
struct PrintSRMask;

struct CmdBaseRn;
struct CmdBaseRd;

struct CmdBaseRdNoS;
struct CmdBaseRm;

struct CmdBase_binary;
struct CmdBase_flags;
struct CmdBase_unary;

template <class Base> struct Cmd0Base;
template <class Base> struct Cmd1Base;

struct CmdBaseQ;

struct CmdBaseM;
struct CmdBaseMUL;
struct CmdBaseMLA;
struct CmdBaseML;

struct CmdBaseMnoS;
struct CmdBaseMULy;
struct CmdBaseMLAy;

struct CmdMemBase;
struct Cmd2MemBase;
struct Cmd3MemBase;

struct CmdExtMemBase;

struct CmdMultipleMemBase;

struct Cmd0_AND;
struct Cmd1_AND;

struct Cmd0_EOR;
struct Cmd1_EOR;

struct Cmd0_ORR;
struct Cmd1_ORR;

struct Cmd0_BIC;
struct Cmd1_BIC;

struct Cmd0_ADD;
struct Cmd1_ADD;

struct Cmd0_SUB;
struct Cmd1_SUB;

struct Cmd0_RSB;
struct Cmd1_RSB;

struct Cmd0_ADC;
struct Cmd1_ADC;

struct Cmd0_SBC;
struct Cmd1_SBC;

struct Cmd0_RSC;
struct Cmd1_RSC;

struct Cmd0_TST;
struct Cmd1_TST;

struct Cmd0_TEQ;
struct Cmd1_TEQ;

struct Cmd0_CMP;
struct Cmd1_CMP;

struct Cmd0_CMN;
struct Cmd1_CMN;

struct Cmd0_MOV;
struct Cmd1_MOV;

struct Cmd0_MVN;
struct Cmd1_MVN;

struct Cmd0_CLZ;

struct Cmd0_QADD;
struct Cmd0_QSUB;
struct Cmd0_QDADD;
struct Cmd0_QDSUB;

struct Cmd0_MUL;
struct Cmd0_MLA;

struct Cmd0_SMULL;
struct Cmd0_UMULL;

struct Cmd0_SMLAL;
struct Cmd0_UMLAL;

struct Cmd0_SMULxy;
struct Cmd0_SMULWy;

struct Cmd0_SMLAxy;
struct Cmd0_SMLAWy;
struct Cmd0_SMLALxy;

struct Cmd0_BLX;
struct Cmd0_BX;

struct Cmd5_B;

struct Cmd0_BKPT;

struct Cmd7_SWI;

struct Cmd0_MRS;

struct Cmd0_MSR;
struct Cmd1_MSR;

struct Cmd2_LDR;
struct Cmd3_LDR;
struct Cmd2_LDRB;
struct Cmd3_LDRB;

struct Cmd2_STR;
struct Cmd3_STR;
struct Cmd2_STRB;
struct Cmd3_STRB;

struct Cmd2_PLD;
struct Cmd3_PLD;

struct Cmd0_SWP;
struct Cmd0_SWPB;

struct Cmd0_LDRH;
struct Cmd0_LDRSH;
struct Cmd0_LDRSB;

struct Cmd0_STRH;

struct Cmd0_LDRD;
struct Cmd0_STRD;

struct Cmd4_LDM;
struct Cmd4_STM;

/* struct Result */

struct Result
 {
  Word val;
 };

/* struct ResultC */

struct ResultC
 {
  Word val;
  bool bitC;
 };

/* struct ResultCV */

struct ResultCV
 {
  Word val;
  bool bitC;
  bool bitV;
 };

/* struct ResultQ */

struct ResultQ
 {
  Word val;
  bool bitQ;
  
  void saturate(Word c,bool bit32,bool Q=false)
   {
    bool sc=c&Bit(31);
    
    if( bit32==sc )
      {
       val  = c ;
       bitQ = Q ;
      }
    else
      {
       val  = (bit32?Bit(31):Field(31)) ;
       bitQ = true ;
      }
   }
  
  void set(const ResultQ &obj) { *this=obj; }
 };

/* struct ResultD */

struct ResultD
 {
  Word hi;
  Word lo;
  
  void set(DWord c)
   {
    hi=Word(c>>32);
    lo=Word(c    );
   }
 };

/* struct DoAND */

struct DoAND : ResultC
 {
  DoAND(Word a,ExtWord b)
   {
    val  = a & b ;
    bitC = b.bitC ;
   }
 };

/* struct DoEOR */

struct DoEOR : ResultC
 {
  DoEOR(Word a,ExtWord b)
   {
    val  = a ^ b ;
    bitC = b.bitC ;
   }
 };

/* struct DoORR */

struct DoORR : ResultC
 {
  DoORR(Word a,ExtWord b)
   {
    val  = a | b ;
    bitC = b.bitC ;
   }
 };

/* struct DoBIC */

struct DoBIC : ResultC
 {
  DoBIC(Word a,ExtWord b)
   {
    val  = a & ~b ;
    bitC = b.bitC ;
   }
 };

/* struct DoADD */

struct DoADD : ResultCV
 {
  DoADD(Word a,Word b)
   {
    Word c=a+b;
    
    val  = c ;
    bitC = (c<a) ;
    bitV = SOverflow(a,b,c) ;
   }
 };

/* struct DoSUB */

struct DoSUB : ResultCV
 {
  DoSUB(Word a,Word b)
   {
    Word c=a-b;
    
    val  = c ;
    bitC = (a>=b) ;
    bitV = SOverflow(c,b,a) ;
   }
 };

/* struct DoADC */

struct DoADC : ResultCV
 {
  DoADC(Word a,Word b,bool carry)
   {
    Word c=a+b+carry;
    
    val  = c ;
    bitC = (carry?(c<=a):(c<a)) ;
    bitV = SOverflow(a,b,c) ;
   }
 };

/* struct DoSBC */

struct DoSBC : ResultCV
 {
  DoSBC(Word a,Word b,bool borrow)
   {
    Word c=a-b-borrow;
    
    val  = c ;
    bitC = (borrow?(a>b):(a>=b)) ;
    bitV = SOverflow(c,b,a) ;
   }
 };

/* struct DoMOV */

struct DoMOV : ResultC
 {
  explicit DoMOV(ExtWord b)
   {
    val  = b ;
    bitC = b.bitC ;
   }
 };

/* struct DoMVN */

struct DoMVN : ResultC
 {
  explicit DoMVN(ExtWord b)
   {
    val  = ~b ;
    bitC = b.bitC ;
   }
 };

/* struct DoCLZ */

struct DoCLZ : Result
 {
  explicit DoCLZ(Word a)
   {
    val = (a?31-Quick::ScanMSBit(a):32) ;
   }
 };

/* struct DoQADD */

struct DoQADD : ResultQ
 {
  DoQADD(Word a,Word b,bool Q=false)
   {
    bool sa=a&Bit(31);
    bool sb=b&Bit(31);
    
    Word c=a+b;
    
    saturate(c,sa^sb^(c<a),Q);
   }
  
  DoQADD(Word a,ResultQ b) : DoQADD(a,b.val,b.bitQ) {}
 };

/* struct DoQSUB */

struct DoQSUB : ResultQ
 {
  DoQSUB(Word a,Word b,bool Q=false)
   {
    bool sa=a&Bit(31);
    bool sb=b&Bit(31);
    
    Word c=a-b;
    
    saturate(c,sa^sb^(a<b),Q);
   }
  
  DoQSUB(Word a,ResultQ b) : DoQSUB(a,b.val,b.bitQ) {}
 };

/* struct DoQDouble */

struct DoQDouble : ResultQ
 {
  explicit DoQDouble(Word a)
   {
    saturate(a<<1,a&Bit(31));
   }
 };

/* struct DoQDADD */

struct DoQDADD : ResultQ
 {
  DoQDADD(Word a,Word b)
   {
    set(DoQADD(a,DoQDouble(b)));
   }
 };

/* struct DoQDSUB */

struct DoQDSUB : ResultQ
 {
  DoQDSUB(Word a,Word b)
   {
    set(DoQSUB(a,DoQDouble(b)));
   }
 };

/* struct DoMUL */

struct DoMUL : Result
 {
  DoMUL(Word a,Word b)
   {
    val = a*b ;
   }
 };

/* struct DoMLA */

struct DoMLA : Result
 {
  DoMLA(Word a,Word b,Word c)
   {
    val = a*b+c ;
   }
 };

/* struct DoSMULL */

struct DoSMULL : ResultD
 {
  DoSMULL(Word a,Word b)
   {
    set( SDWord(SWord(a))*SWord(b) );
   }
 };

/* struct DoUMULL */

struct DoUMULL : ResultD
 {
  DoUMULL(Word a,Word b)
   {
    set( DWord(a)*b );
   }
 };

/* struct DoSMLAL */

struct DoSMLAL : ResultD
 {
  DoSMLAL(Word a,Word b,Word hi_,Word lo_)
   {
    set( SDWord(SWord(a))*SWord(b)+MakeDWord(hi_,lo_) );
   }
 };

/* struct DoUMLAL */

struct DoUMLAL : ResultD
 {
  DoUMLAL(Word a,Word b,Word hi_,Word lo_)
   {
    set( DWord(a)*b+MakeDWord(hi_,lo_) );
   }
 };

/* struct DoSMULxy */

struct DoSMULxy : Result
 {
  DoSMULxy(Word a_,Word b_,Word bit_x,Word bit_y)
   {
    SHalf a = SHalf( bit_x?(a_>>16):a_ );
    SHalf b = SHalf( bit_y?(b_>>16):b_ );
    
    val = SWord(a) * b ;
   }
 };

/* struct DoSMULWy */

struct DoSMULWy : Result
 {
  DoSMULWy(Word a,Word b_,Word bit_y)
   {
    SHalf b = SHalf( bit_y?(b_>>16):b_ );
    
    val = Word( (SDWord(SWord(a))*b)>>16 ) ;
   }
 };

/* struct DoSMLAxy */

struct DoSMLAxy : ResultQ
 {
  DoSMLAxy(Word a_,Word b_,Word c,Word bit_x,Word bit_y)
   {
    SHalf a = SHalf( bit_x?(a_>>16):a_ );
    SHalf b = SHalf( bit_y?(b_>>16):b_ );
    
    Word prod = SWord(a) * b ;
    
    val  = prod + c ;
    bitQ = SOverflow(prod,c,val) ;
   }
 };

/* struct DoSMLAWy */

struct DoSMLAWy : ResultQ
 {
  DoSMLAWy(Word a,Word b_,Word c,Word bit_y)
   {
    SHalf b = SHalf( bit_y?(b_>>16):b_ );
    
    Word prod = Word( (SDWord(SWord(a))*b)>>16 ) ;
    
    val  = prod + c ;
    bitQ = SOverflow(prod,c,val) ;
   }
 };

/* struct DoSMLALxy */

struct DoSMLALxy : ResultD
 {
  DoSMLALxy(Word a_,Word b_,Word hi_,Word lo_,Word bit_x,Word bit_y)
   {
    SHalf a = SHalf( bit_x?(a_>>16):a_ );
    SHalf b = SHalf( bit_y?(b_>>16):b_ );
    
    set( SDWord(SWord(a)*b)+MakeDWord(hi_,lo_) );
   }
 };

/* struct PrintReg */

struct PrintReg
 {
  Word R;
  
  explicit PrintReg(Word R_) : R(R_) {}
  
  template <class P>
  void print(P &out) const
   {
    switch( R )
      {
       case 15 : Putobj(out,"PC(R15)"); break;
       case 14 : Putobj(out,"LR(R14)"); break;
       case 13 : Putobj(out,"SP(R13)"); break;
       case 12 : Putobj(out,"IP(R12)"); break;
       case 11 : Putobj(out,"FP(R11)"); break;
       
       default: Printf(out,"R#;",R);
      }
   }
 };

/* struct PrintSRMask */

struct PrintSRMask
 {
  Word mask;
  
  explicit PrintSRMask(Word mask_) : mask(mask_) {}
  
  template <class P>
  void print(P &out) const
   {
    if( mask!=15 )
      {
       if( mask )
         {
          Putch(out,'_');
         
          if( mask&Bit(3) ) Putch(out,'f');
          if( mask&Bit(2) ) Putch(out,'s');
          if( mask&Bit(1) ) Putch(out,'x');
          if( mask&Bit(0) ) Putch(out,'c');
         }
       else
         {
          Putobj(out,"_none");
         }
      }
   }
 };

/* struct CmdBaseRn */

struct CmdBaseRn
 {
  Word Rn;
  
  explicit CmdBaseRn(Word cmd)
   {
    Rn=(cmd>>16)&15;
   }
  
  Word getArg1(const ARMState &state) const
   {
    return state.getReg(Rn);
   }
 };

/* struct CmdBaseRd */

struct CmdBaseRd
 {
  Word Rd;
  Word bitS;
  
  explicit CmdBaseRd(Word cmd) 
   {
    Rd=(cmd>>12)&15;
    bitS=cmd&Bit(20);
   }
  
  template <class Log>
  void setPC(ARMState &state,Word val,Log &log) const
   {
    state.setPC(val,log);
    
    if( bitS ) state.popCPSR(log);
   }
  
  template <class Log>
  void setReg(ARMState &state,Result res,Log &log) const
   {
    if( Rd==15 )
      {
       setPC(state,res.val,log);
      }
    else
      {
       if( bitS ) 
         {
          BitsNZ bits(res.val);
          
          log.trace("#; = #9.h; #;",PrintReg(Rd),res.val,bits);
         
          state.setFlags(bits);
         }
       else
         {
          log.trace("#; = #9.h;",PrintReg(Rd),res.val);
         }
      
       state.R[Rd]=res.val;
      
       state.nextPC();
      }
   }
  
  template <class Log>
  void setReg(ARMState &state,ResultC res,Log &log) const
   {
    if( Rd==15 )
      {
       setPC(state,res.val,log);
      }
    else
      {
       if( bitS ) 
         {
          BitsNZ bits(res.val);
          
          log.trace("#; = #9.h; #; C = #;",PrintReg(Rd),res.val,bits,(unsigned)res.bitC);
         
          state.setFlags(bits,res.bitC);
         }
       else
         {
          log.trace("#; = #9.h;",PrintReg(Rd),res.val);
         }
      
       state.R[Rd]=res.val;
      
       state.nextPC();
      }
   }
  
  template <class Log>
  void setReg(ARMState &state,ResultCV res,Log &log) const
   {
    if( Rd==15 )
      {
       setPC(state,res.val,log);
      }
    else
      {
       if( bitS ) 
         {
          BitsNZ bits(res.val);
          
          log.trace("#; = #9.h; #; C = #; V = #;",PrintReg(Rd),res.val,bits,(unsigned)res.bitC,(unsigned)res.bitV);
        
          state.setFlags(bits,res.bitC,res.bitV);
         }
       else
         {
          log.trace("#; = #9.h;",PrintReg(Rd),res.val);
         }
      
       state.R[Rd]=res.val;
      
       state.nextPC();
      }
   }
 };

/* struct CmdBaseRdNoS */

struct CmdBaseRdNoS
 {
  Word Rd;
  
  explicit CmdBaseRdNoS(Word cmd) 
   {
    Rd=(cmd>>12)&15;
   }
  
  template <class Log>
  void setReg(ARMState &state,Result res,Log &log) const
   {
    state.R[Rd]=res.val;
      
    log.trace("#; = #9.h;",PrintReg(Rd),res.val);
      
    state.nextPC();
   }
  
  template <class Log>
  void setReg(ARMState &state,ResultQ res,Log &log) const
   {
    log.trace("#; = #9.h;#;",PrintReg(Rd),res.val,(res.bitQ?" Q = 1":""));
      
    state.R[Rd]=res.val;
      
    if( res.bitQ ) state.CPSR|=SR_Q;
    
    state.nextPC();
   }
 };

/* struct CmdBaseRm */

struct CmdBaseRm
 {
  Word Rm;
  
  explicit CmdBaseRm(Word cmd)
   {
    Rm=cmd&15;
   }
  
  Word getArg2(const ARMState &state) const
   {
    return state.getReg(Rm);
   }
 };

/* struct CmdBase_binary */

struct CmdBase_binary : CmdBaseRn , CmdBaseRd
 {
  explicit CmdBase_binary(Word cmd) : CmdBaseRn(cmd),CmdBaseRd(cmd) {}
  
  bool badRx() const { return Rd==15 || Rn==15 ; }
  
  template <class P>
  void printBase(P &out) const
   {
    if( bitS ) Putch(out,'S');
    
    Printf(out," #;, #;",PrintReg(Rd),PrintReg(Rn));
   }
 };

/* struct CmdBase_flags */

struct CmdBase_flags : CmdBaseRn
 {
  explicit CmdBase_flags(Word cmd) : CmdBaseRn(cmd) {}
  
  bool badRx() const { return Rn==15 ; }
  
  template <class Log>
  void setFlags(ARMState &state,ResultC res,Log &log) const
   {
    BitsNZ bits(res.val);
    
    log.trace("#; C = #;",bits,(unsigned)res.bitC);
    
    state.setFlags(bits,res.bitC);
      
    state.nextPC();
   }
  
  template <class Log>
  void setFlags(ARMState &state,ResultCV res,Log &log) const
   {
    BitsNZ bits(res.val);
    
    log.trace("#; C = #; V = #;",bits,(unsigned)res.bitC,(unsigned)res.bitV);
    
    state.setFlags(bits,res.bitC,res.bitV);
      
    state.nextPC();
   }
  
  template <class P>
  void printBase(P &out) const
   {
    Printf(out," #;",PrintReg(Rn));
   }
 };

/* struct CmdBase_unary */

struct CmdBase_unary : CmdBaseRd
 {
  explicit CmdBase_unary(Word cmd) : CmdBaseRd(cmd) {} 
  
  bool badRx() const { return Rd==15 ; }
  
  template <class P>
  void printBase(P &out) const
   {
    if( bitS ) Putch(out,'S');
    
    Printf(out," #;",PrintReg(Rd));
   }
 };

/* struct Cmd0Base<Base> */

template <class Base>
struct Cmd0Base : Base
 {
  Word Rm;
  Word shift_type;
  Word reg_shift;
  
  union
   {
    Word imm_shift;
    Word Rs;
   };
  
  explicit Cmd0Base(Word cmd) 
   : Base(cmd)
   {
    Rm=cmd&15;
    
    shift_type=(cmd>>5)&3;
    reg_shift=cmd&Bit(4);
    
    if( reg_shift )
      {
       Rs=(cmd>>8)&15;
      }
    else
      {
       imm_shift=(cmd>>7)&31;
      }
   }
  
  bool badArgs() const 
   { 
    if( reg_shift )
      {
       if( this->badRx() || Rm==15 || Rs==15 ) return true;
      }
     
    return false; 
   }
  
  ExtWord getArg2(const ARMState &state) const
   {
    Word val=state.getReg(Rm);
    
    Word shift;
    
    if( reg_shift )
      {
       shift=state.getReg(Rs)&Field(8);
      }
    else
      {
       shift=imm_shift;
      }
    
    switch( shift_type )
      {
       case 0 : // LSL
        {
         if( shift==0 )
           {
            return ExtWord(val,state.CPSR&SR_C);
           }
         else if( shift<32 )
           {
            return ExtWord(val<<shift,val&Bit(32-shift));
           }
         else if( shift==32 )
           {
            return ExtWord(0,val&Bit(0));
           }
         else
           {
            return Null;
           }
        }
       break;
       
       case 1 : // LSR
        {
         if( !reg_shift && shift==0 ) shift=32;
         
         if( shift==0 )
           {
            return ExtWord(val,state.CPSR&SR_C);
           }
         else if( shift<32 )
           {
            return ExtWord(val>>shift,val&Bit(shift-1));
           }
         else if( shift==32 )
           {
            return ExtWord(0,val&Bit(31));
           }
         else
           {
            return Null;
           }
        }
       break;
       
       case 2 : // ASR
        {
         if( !reg_shift && shift==0 ) shift=32;
         
         if( shift==0 )
           {
            return ExtWord(val,state.CPSR&SR_C);
           }
         else if( shift<32 )
           {
            return ExtWord(SWord(val)>>shift,val&Bit(shift-1));
           }
         else
           {
            if( val&Bit(31) )
              {
               return ExtWord(Word(-1),true);
              }
            else
              {
               return Null;
              }
           }
        }
       break;
       
       case 3 : // ROR
        {
         if( reg_shift )
           {
            if( shift==0 ) return ExtWord(val,state.CPSR&SR_C);
            
            shift&=31;
            
            if( shift )
              {
               return ExtWord(RotR(val,shift),val&Bit(shift-1));
              }
            else
              {
               return ExtWord(val,val&Bit(31));
              }
           }
         else
           {
            if( shift )
              {
               return ExtWord(RotR(val,shift),val&Bit(shift-1));
              }
            else // RRX
              {
               return ExtWord(RotRBit(val,state.CPSR&SR_C),val&Bit(0));
              }
           }
        }
       break; 
      }
    
    return Null;
   }
  
  struct PrintArgs
   {
    const Cmd0Base &obj;
    
    explicit PrintArgs(const Cmd0Base &obj_) : obj(obj_) {}
    
    template <class P>
    void print(P &out) const
     {
      obj.printBase(out);
      
      Printf(out,", #;",PrintReg(obj.Rm));
      
      switch( obj.shift_type )
        {
         case 0 :
          {
           if( obj.reg_shift )
             {
              Printf(out,", LSL #;",PrintReg(obj.Rs));
             }
           else
             {
              if( obj.imm_shift ) 
                Printf(out,", LSL ###;",obj.imm_shift);
             }
          }
         break;
         
         case 1 :
          {
           if( obj.reg_shift )
             {
              Printf(out,", LSR #;",PrintReg(obj.Rs));
             }
           else
             {
              if( obj.imm_shift ) 
                Printf(out,", LSR ###;",obj.imm_shift);
              else
                Printf(out,", LSR ##32");
             }
          }
         break;
         
         case 2 :
          {
           if( obj.reg_shift )
             {
              Printf(out,", ASR #;",PrintReg(obj.Rs));
             }
           else
             {
              if( obj.imm_shift ) 
                Printf(out,", ASR ###;",obj.imm_shift);
              else
                Printf(out,", ASR ##32");
             }
          }
         break;
         
         case 3 :
          {
           if( obj.reg_shift )
             {
              Printf(out,", ROR #;",PrintReg(obj.Rs));
             }
           else
             {
              if( obj.imm_shift ) 
                Printf(out,", ROR ###;",obj.imm_shift);
              else
                Printf(out,", RRX");
             }
          }
         break; 
        }
     }
   };
  
  PrintArgs printArgs() const { return PrintArgs(*this); }
 };

/* struct Cmd1Base<Base> */

template <class Base>
struct Cmd1Base : Base
 {
  Word imm;
  Word rot;
  
  explicit Cmd1Base(Word cmd) 
   : Base(cmd)
   {
    imm=cmd&Field(8);
    rot=((cmd>>8)&15)*2;
    
    if( rot )
      {
       imm=RotR(imm,rot);
      }
   }
  
  ExtWord getArg2(const ARMState &state) const
   {
    if( rot )
      {
       return ExtWord(imm,imm&Bit(31));
      }
    else
      {
       return ExtWord(imm,state.CPSR&SR_C);
      }
   }
  
  struct PrintArgs
   {
    const Cmd1Base &obj;
    
    explicit PrintArgs(const Cmd1Base &obj_) : obj(obj_) {}
    
    template <class P>
    void print(P &out) const
     {
      obj.printBase(out);
      
      Printf(out,", ###.h;",obj.imm);
     }
   };
      
  PrintArgs printArgs() const { return PrintArgs(*this); }
 };

/* types */

typedef Cmd0Base<CmdBase_binary> Cmd0Base_binary;
typedef Cmd1Base<CmdBase_binary> Cmd1Base_binary;

typedef Cmd0Base<CmdBase_flags> Cmd0Base_flags;
typedef Cmd1Base<CmdBase_flags> Cmd1Base_flags;

typedef Cmd0Base<CmdBase_unary> Cmd0Base_unary;
typedef Cmd1Base<CmdBase_unary> Cmd1Base_unary;

/* struct CmdBaseQ */

struct CmdBaseQ : CmdBaseRdNoS , CmdBaseRn , CmdBaseRm 
 {
  explicit CmdBaseQ(Word cmd) : CmdBaseRdNoS(cmd), CmdBaseRn(cmd), CmdBaseRm(cmd) {}
  
  bool badArgs() const { return Rd==15 || Rn==15 || Rm==15 ; }
  
  struct PrintArgs
   {
    const CmdBaseQ &obj;
    
    explicit PrintArgs(const CmdBaseQ &obj_) : obj(obj_) {}
    
    template <class P>
    void print(P &out) const
     {
      Printf(out," #;, #;, #;",PrintReg(obj.Rd),PrintReg(obj.Rm),PrintReg(obj.Rn));
     }
   };
  
  PrintArgs printArgs() const { return PrintArgs(*this); }
 };

/* struct CmdBaseM */

struct CmdBaseM
 {
  Word Rd;
  Word bitS;
  
  Word Rm;
  Word Rs;
  
  explicit CmdBaseM(Word cmd)
   {
    Rd=(cmd>>16)&15;
    bitS=cmd&Bit(20);
    
    Rm=cmd&15;
    Rs=(cmd>>8)&15;
   }
  
  Word getArg1(const ARMState &state) const
   {
    return state.getReg(Rm);
   }
  
  Word getArg2(const ARMState &state) const
   {
    return state.getReg(Rs);
   }
  
  template <class Log>
  void setReg(ARMState &state,Result res,Log &log) const
   {
    if( bitS ) 
      {
       BitsNZ bits(res.val);
         
       log.trace("#; = #9.h; #;",PrintReg(Rd),res.val,bits);
      
       state.setFlags(bits);
      }
    else
      {
       log.trace("#; = #9.h;",PrintReg(Rd),res.val);
      }
   
    state.R[Rd]=res.val;
   
    state.nextPC();
   }
 };

/* struct CmdBaseMUL */

struct CmdBaseMUL : CmdBaseM
 {
  explicit CmdBaseMUL(Word cmd) : CmdBaseM(cmd) {}
  
  bool badArgs() const { return Rd==15 || Rm==15 || Rs==15 ; }
  
  struct PrintArgs
   {
    const CmdBaseMUL &obj;
    
    explicit PrintArgs(const CmdBaseMUL &obj_) : obj(obj_) {}
    
    template <class P>
    void print(P &out) const
     {
      if( obj.bitS ) Putch(out,'S');
      
      Printf(out," #;, #;, #;",PrintReg(obj.Rd),PrintReg(obj.Rm),PrintReg(obj.Rs));
     }
   };
  
  PrintArgs printArgs() const { return PrintArgs(*this); }
 };

/* struct CmdBaseMLA */

struct CmdBaseMLA : CmdBaseM
 {
  Word Rn;
  
  explicit CmdBaseMLA(Word cmd) 
   : CmdBaseM(cmd) 
   {
    Rn=(cmd>>12)&15;
   }
  
  Word getArg3(const ARMState &state) const
   {
    return state.getReg(Rn);
   }
  
  bool badArgs() const { return Rd==15 || Rm==15 || Rs==15 || Rn==15 ; }
  
  struct PrintArgs
   {
    const CmdBaseMLA &obj;
    
    explicit PrintArgs(const CmdBaseMLA &obj_) : obj(obj_) {}
    
    template <class P>
    void print(P &out) const
     {
      if( obj.bitS ) Putch(out,'S');
      
      Printf(out," #;, #;, #;, #;",PrintReg(obj.Rd),PrintReg(obj.Rm),PrintReg(obj.Rs),PrintReg(obj.Rn));
     }
   };
  
  PrintArgs printArgs() const { return PrintArgs(*this); }
 };

/* struct CmdBaseML */

struct CmdBaseML : CmdBaseM
 {
  Word Rn;
  
  explicit CmdBaseML(Word cmd) 
   : CmdBaseM(cmd) 
   {
    Rn=(cmd>>12)&15;
   }
  
  bool badArgs() const { return Rd==15 || Rm==15 || Rs==15 || Rn==15 || Rd==Rn ; }
  
  Word getLo(const ARMState &state) const
   {
    return state.getReg(Rn);
   }
  
  Word getHi(const ARMState &state) const
   {
    return state.getReg(Rd);
   }
  
  template <class Log>
  void setReg(ARMState &state,ResultD res,Log &log) const
   {
    if( bitS ) 
      {
       BitsNZ bits(res.hi,res.lo);
       
       log.trace("#; = #9.h; #; = #9.h; #;",PrintReg(Rn),res.lo,PrintReg(Rd),res.hi,bits);
      
       state.setFlags(bits);
      }
    else
      {
       log.trace("#; = #9.h; #; = #9.h;",PrintReg(Rn),res.lo,PrintReg(Rd),res.hi);
      }
   
    state.R[Rn]=res.lo;
    state.R[Rd]=res.hi;
   
    state.nextPC();
   }
  
  struct PrintArgs
   {
    const CmdBaseML &obj;
    
    explicit PrintArgs(const CmdBaseML &obj_) : obj(obj_) {}
    
    template <class P>
    void print(P &out) const
     {
      if( obj.bitS ) Putch(out,'S');
      
      Printf(out," #;, #;, #;, #;",PrintReg(obj.Rn),PrintReg(obj.Rd),PrintReg(obj.Rm),PrintReg(obj.Rs));
     }
   };
  
  PrintArgs printArgs() const { return PrintArgs(*this); }
 };

/* struct CmdBaseMnoS */

struct CmdBaseMnoS
 {
  Word Rd;
  
  Word Rm;
  Word Rs;
  
  explicit CmdBaseMnoS(Word cmd)
   {
    Rd=(cmd>>16)&15;
    
    Rm=cmd&15;
    Rs=(cmd>>8)&15;
   }
  
  Word getArg1(const ARMState &state) const
   {
    return state.getReg(Rm);
   }
  
  Word getArg2(const ARMState &state) const
   {
    return state.getReg(Rs);
   }
  
  template <class Log>
  void setReg(ARMState &state,Result res,Log &log) const
   {
    log.trace("#; = #9.h;",PrintReg(Rd),res.val);
  
    state.R[Rd]=res.val;
   
    state.nextPC();
   }
 };

/* struct CmdBaseMULy */

struct CmdBaseMULy : CmdBaseMnoS
 {
  explicit CmdBaseMULy(Word cmd) : CmdBaseMnoS(cmd) {}
  
  bool badArgs() const { return Rd==15 || Rm==15 || Rs==15 ; }
  
  struct PrintArgs
   {
    const CmdBaseMULy &obj;
    
    explicit PrintArgs(const CmdBaseMULy &obj_) : obj(obj_) {}
    
    template <class P>
    void print(P &out) const
     {
      Printf(out," #;, #;, #;",PrintReg(obj.Rd),PrintReg(obj.Rm),PrintReg(obj.Rs));
     }
   };
  
  PrintArgs printArgs() const { return PrintArgs(*this); }
 };

/* struct CmdBaseMLAy */

struct CmdBaseMLAy : CmdBaseMnoS
 {
  Word Rn;
  
  explicit CmdBaseMLAy(Word cmd) 
   : CmdBaseMnoS(cmd) 
   {
    Rn=(cmd>>12)&15;
   }
  
  bool badArgs() const { return Rd==15 || Rm==15 || Rs==15 || Rn==15 ; }
  
  Word getArg3(const ARMState &state) const
   {
    return state.getReg(Rn);
   }
  
  template <class Log>
  void setReg(ARMState &state,ResultQ res,Log &log) const
   {
    log.trace("#; = #9.h;#;",PrintReg(Rd),res.val,(res.bitQ?" Q = 1":""));
  
    state.R[Rd]=res.val;
    
    if( res.bitQ ) state.CPSR|=SR_Q;
   
    state.nextPC();
   }
  
  struct PrintArgs
   {
    const CmdBaseMLAy &obj;
    
    explicit PrintArgs(const CmdBaseMLAy &obj_) : obj(obj_) {}
    
    template <class P>
    void print(P &out) const
     {
      Printf(out," #;, #;, #;, #;",PrintReg(obj.Rd),PrintReg(obj.Rm),PrintReg(obj.Rs),PrintReg(obj.Rn));
     }
   };
  
  PrintArgs printArgs() const { return PrintArgs(*this); }
 };

/* struct CmdMemBase */

struct CmdMemBase
 {
  Word Rd;
  Word Rn;
  Word bitU;
  Word bitP;
  Word bitW;
  
  explicit CmdMemBase(Word cmd)
   {
    Rd=(cmd>>12)&15;
    Rn=(cmd>>16)&15;
    bitU=cmd&Bit(23);
    bitP=cmd&Bit(24);
    bitW=cmd&Bit(21);
   }
  
  bool badWriteBack() const { return Rn==Rd && ( !bitP || bitW ) ; }
  
  template <class Log>
  void writeBack(ARMState &state,Word val,Log &log) const
   {
    log.trace("#; = #9.h;",PrintReg(Rn),val);
   
    state.R[Rn]=val;
   }
  
  template <class Log>
  void setReg_noPC(ARMState &state,Word val,Log &log) const
   {
    log.trace("#; = #9.h;",PrintReg(Rd),val);
      
    state.R[Rd]=val;
       
    state.nextPC();
   }
  
  template <class Log>
  void setReg_noPC(ARMState &state,Word val0,Word val1,Log &log) const
   {
    log.trace("#; = #9.h;",PrintReg(Rd),val0);
    log.trace("#; = #9.h;",PrintReg(Rd+1),val1);
      
    state.R[Rd  ]=val0;
    state.R[Rd+1]=val1;
       
    state.nextPC();
   }
  
  template <class Log>
  void setReg(ARMState &state,Word val,Log &log) const
   {
    if( Rd==15 )
      {
       state.setPC_T(val,log);
      }
    else
      {
       setReg_noPC(state,val,log);
      }
   }
 };

/* struct Cmd2MemBase */

struct Cmd2MemBase : CmdMemBase
 {
  Word offset;
  
  explicit Cmd2MemBase(Word cmd) 
   : CmdMemBase(cmd)
   {
    offset=cmd&Field(12);
   }
  
  bool badArgs() const { return Rn==15 && ( !bitP || bitW ) ; }
  
  struct PrintArgs
   {
    const Cmd2MemBase &obj;
    
    explicit PrintArgs(const Cmd2MemBase &obj_) : obj(obj_) {}
    
    template <class P>
    void print(P &out) const
     {
      if( obj.bitP )
        {
         Printf(out," #;, [#; #; #4.h;]",PrintReg(obj.Rd),PrintReg(obj.Rn),(obj.bitU?"+":"-"),obj.offset);
        
         if( obj.bitW ) Putch(out,'!');
        }
      else
        {
         if( obj.bitW ) Putch(out,'T');
         
         Printf(out," #;, [#;], #; #4.h;",PrintReg(obj.Rd),PrintReg(obj.Rn),(obj.bitU?"+":"-"),obj.offset);
        }
     }
   };
  
  PrintArgs printArgs() const { return PrintArgs(*this); }
 };

/* struct Cmd3MemBase */

struct Cmd3MemBase : CmdMemBase
 {
  Word Rm;
  Word shift_type;
  Word shift;
  
  explicit Cmd3MemBase(Word cmd) 
   : CmdMemBase(cmd)
   {
    Rm=cmd&15;
    shift_type=(cmd>>5)&3;
    shift=(cmd>>7)&31;
   }
  
  bool badArgs() const { return Rm==15 || ( Rn==15 && ( !bitP || bitW ) ) ; }
  
  Word getOffset(ARMState &state) const
   {
    Word val=state.getReg(Rm);
    
    switch( shift_type )
      {
       case 0 : // LSL
        {
         return val<<shift; 
        }
        
       case 1 : // LSR
        {
         if( shift )
           {
            return val>>shift;
           }
         else
           {
            return 0;
           }
        }
        
       case 2 : // ASR
        {
         if( shift )
           {
            return SWord(val)>>shift;
           }
         else
           {
            return (val&Bit(31))?Word(-1):Word(0);
           }
        }
        
       case 3 : // ROR
        {
         if( shift )
           {
            return RotR(val,shift);
           }
         else // RRX
           {
            return RotRBit(val,state.CPSR&SR_C);
           }
        }
      }
    
    return 0;
   }
  
  struct PrintOffset
   {
    const Cmd3MemBase &obj;
    
    explicit PrintOffset(const Cmd3MemBase &obj_) : obj(obj_) {}
    
    template <class P>
    void print(P &out) const
     {
      switch( obj.shift_type )
        {
         case 0 :
          {
           if( obj.shift )
             Printf(out,"#; LSL ###;",PrintReg(obj.Rm),obj.shift);
           else
             Printf(out,"#;",PrintReg(obj.Rm));
          }
         break;
         
         case 1 :
          {
           if( obj.shift )
             Printf(out,"#; LSR ###;",PrintReg(obj.Rm),obj.shift);
           else
             Printf(out,"#; LSR #32",PrintReg(obj.Rm));
          }
         break;
         
         case 2 :
          {
           if( obj.shift )
             Printf(out,"#; ASR ###;",PrintReg(obj.Rm),obj.shift);
           else
             Printf(out,"#; ASR #32",PrintReg(obj.Rm));
          }
         break;
         
         case 3 :
          {
           if( obj.shift )
             Printf(out,"#; ROR ###;",PrintReg(obj.Rm),obj.shift);
           else
             Printf(out,"#; RRX",PrintReg(obj.Rm));
          }
         break;
        }
     }
   };
  
  struct PrintArgs
   {
    const Cmd3MemBase &obj;
    
    explicit PrintArgs(const Cmd3MemBase &obj_) : obj(obj_) {}
    
    template <class P>
    void print(P &out) const
     {
      if( obj.bitP )
        {
         Printf(out," #;, [#; #; #;]",PrintReg(obj.Rd),PrintReg(obj.Rn),(obj.bitU?"+":"-"),PrintOffset(obj));
        
         if( obj.bitW ) Putch(out,'!');
        }
      else
        {
         if( obj.bitW ) Putch(out,'T');
         
         Printf(out," #;, [#;], #; #;",PrintReg(obj.Rd),PrintReg(obj.Rn),(obj.bitU?"+":"-"),PrintOffset(obj));
        }
     }
   };
  
  PrintArgs printArgs() const { return PrintArgs(*this); }
 };

/* struct CmdExtMemBase */

struct CmdExtMemBase : CmdMemBase
 {
  Word bitI;
  
  union
   {
    Word Rm;
    Word imm_offset;
   };
  
  explicit CmdExtMemBase(Word cmd)
   : CmdMemBase(cmd)
   {
    bitI=cmd&Bit(22);
    
    if( bitI )
      {
       imm_offset=(cmd&Field(4))|((cmd>>4)&Field(4,4));
      }
    else
      {
       Rm=cmd&15;
      }
   }
  
  bool badArgs() const { return Rd==15 || ( !bitI && Rm==15 ) || ( Rn==15 && ( !bitP || bitW ) ) ; }
  
  Word getOffset(ARMState &state) const
   {
    if( bitI )
      return imm_offset;
    else
      return state.getReg(Rm);
   }
  
  struct PrintOffset
   {
    const CmdExtMemBase &obj;
    
    explicit PrintOffset(const CmdExtMemBase &obj_) : obj(obj_) {}
    
    template <class P>
    void print(P &out) const
     {
      if( obj.bitI )
        Printf(out,"#3.h;",obj.imm_offset);
      else
        Printf(out,"#;",PrintReg(obj.Rm));
     }
   };
  
  struct PrintArgs
   {
    const CmdExtMemBase &obj;
    
    explicit PrintArgs(const CmdExtMemBase &obj_) : obj(obj_) {}
    
    template <class P>
    void print(P &out) const
     {
      if( obj.bitP )
        {
         Printf(out," #;, [#; #; #;]",PrintReg(obj.Rd),PrintReg(obj.Rn),(obj.bitU?"+":"-"),PrintOffset(obj));
        
         if( obj.bitW ) Putch(out,'!');
        }
      else
        {
         Printf(out," #;, [#;], #; #;",PrintReg(obj.Rd),PrintReg(obj.Rn),(obj.bitU?"+":"-"),PrintOffset(obj));
        }
     }
   };
  
  PrintArgs printArgs() const { return PrintArgs(*this); }
 };

/* struct CmdMultipleMemBase */

struct CmdMultipleMemBase
 {
  Word Rn;
  
  Word bitP;
  Word bitU;
  Word bitW;
  Word bitS;
  
  Word list[16];
  Word len;
  
  explicit CmdMultipleMemBase(Word cmd)
   : list{}
   {
    Rn=(cmd>>16)&15;
    
    bitP=cmd&Bit(24);
    bitU=cmd&Bit(23);
    bitW=cmd&Bit(21);
    bitS=cmd&Bit(22);
    
    len=0;
    
    for(unsigned i=0; i<16 ;i++)
      if( cmd&Bit(i) )
        {
         list[len++]=i;
        }
   }
   
  struct PrintArgs
   {
    const CmdMultipleMemBase &obj;
    
    explicit PrintArgs(const CmdMultipleMemBase &obj_) : obj(obj_) {}
    
    template <class P>
    void print(P &out) const
     {
      if( obj.bitU )
        {
         if( obj.bitP )
           {
            Putobj(out,"IB");
           }
         else
           {
            Putobj(out,"IA");
           }
        }
      else
        {
         if( obj.bitP )
           {
            Putobj(out,"DB");
           }
         else
           {
            Putobj(out,"DA");
           }
        }
      
      Printf(out," #;",PrintReg(obj.Rn));
      
      if( obj.bitW ) Putch(out,'!');
      
      Putobj(out,", {");
      
      auto r=Range(obj.list,obj.len);
      
      if( +r )
        {
         Printf(out," #;",PrintReg(*r));
         
         for(++r; +r ;++r) Printf(out,", #;",PrintReg(*r));
         
         Putobj(out," }");
        }
      else
        {
         Putch(out,'}');
        }
     }
   };
  
  PrintArgs printArgs() const { return PrintArgs(*this); }
 };

/* struct Cmd0_AND */

struct Cmd0_AND : Cmd0Base_binary
 {
  explicit Cmd0_AND(Word cmd) : Cmd0Base_binary(cmd) {}
  
  template <class Log>
  void execute(ARMState &state,Log &log) const
   {
    log.trace(state.PC(),"AND#;",printArgs());
    
    if( badArgs() ) 
      {
       log.trace("Bad PC usage");
      
       return state.cmdUndefined(log);
      } 
    
    setReg(state,DoAND(getArg1(state),getArg2(state)),log);
   }
 };
 
/* struct Cmd1_AND */

struct Cmd1_AND : Cmd1Base_binary
 {
  explicit Cmd1_AND(Word cmd) : Cmd1Base_binary(cmd) {}
  
  template <class Log>
  void execute(ARMState &state,Log &log) const
   {
    log.trace(state.PC(),"AND#;",printArgs());
    
    setReg(state,DoAND(getArg1(state),getArg2(state)),log);
   }
 };

/* struct Cmd0_EOR */

struct Cmd0_EOR : Cmd0Base_binary
 {
  explicit Cmd0_EOR(Word cmd) : Cmd0Base_binary(cmd) {}
  
  template <class Log>
  void execute(ARMState &state,Log &log) const
   {
    log.trace(state.PC(),"EOR#;",printArgs());
    
    if( badArgs() ) 
      {
       log.trace("Bad PC usage");
      
       return state.cmdUndefined(log);
      } 
    
    setReg(state,DoEOR(getArg1(state),getArg2(state)),log);
   }
 };

/* struct Cmd1_EOR */

struct Cmd1_EOR : Cmd1Base_binary
 {
  explicit Cmd1_EOR(Word cmd) : Cmd1Base_binary(cmd) {}
  
  template <class Log>
  void execute(ARMState &state,Log &log) const
   {
    log.trace(state.PC(),"EOR#;",printArgs());
    
    setReg(state,DoEOR(getArg1(state),getArg2(state)),log);
   }
 };

/* struct Cmd0_ORR */

struct Cmd0_ORR : Cmd0Base_binary
 {
  explicit Cmd0_ORR(Word cmd) : Cmd0Base_binary(cmd) {}
  
  template <class Log>
  void execute(ARMState &state,Log &log) const
   {
    log.trace(state.PC(),"ORR#;",printArgs());
    
    if( badArgs() ) 
      {
       log.trace("Bad PC usage");
      
       return state.cmdUndefined(log);
      } 
    
    setReg(state,DoORR(getArg1(state),getArg2(state)),log);
   }
 };

/* struct Cmd1_ORR */

struct Cmd1_ORR : Cmd1Base_binary
 {
  explicit Cmd1_ORR(Word cmd) : Cmd1Base_binary(cmd) {}
  
  template <class Log>
  void execute(ARMState &state,Log &log) const
   {
    log.trace(state.PC(),"ORR#;",printArgs());
    
    setReg(state,DoORR(getArg1(state),getArg2(state)),log);
   }
 };

/* struct Cmd0_BIC */

struct Cmd0_BIC : Cmd0Base_binary
 {
  explicit Cmd0_BIC(Word cmd) : Cmd0Base_binary(cmd) {}
  
  template <class Log>
  void execute(ARMState &state,Log &log) const
   {
    log.trace(state.PC(),"BIC#;",printArgs());
    
    if( badArgs() ) 
      {
       log.trace("Bad PC usage");
      
       return state.cmdUndefined(log);
      } 
    
    setReg(state,DoBIC(getArg1(state),getArg2(state)),log);
   }
 };

/* struct Cmd1_BIC */

struct Cmd1_BIC : Cmd1Base_binary
 {
  explicit Cmd1_BIC(Word cmd) : Cmd1Base_binary(cmd) {}
  
  template <class Log>
  void execute(ARMState &state,Log &log) const
   {
    log.trace(state.PC(),"BIC#;",printArgs());
    
    setReg(state,DoBIC(getArg1(state),getArg2(state)),log);
   }
 };

/* struct Cmd0_ADD */

struct Cmd0_ADD : Cmd0Base_binary
 {
  explicit Cmd0_ADD(Word cmd) : Cmd0Base_binary(cmd) {}
  
  template <class Log>
  void execute(ARMState &state,Log &log) const
   {
    log.trace(state.PC(),"ADD#;",printArgs());
    
    if( badArgs() ) 
      {
       log.trace("Bad PC usage");
      
       return state.cmdUndefined(log);
      } 
    
    setReg(state,DoADD(getArg1(state),getArg2(state)),log);
   }
 };

/* struct Cmd1_ADD */

struct Cmd1_ADD : Cmd1Base_binary
 {
  explicit Cmd1_ADD(Word cmd) : Cmd1Base_binary(cmd) {}
  
  template <class Log>
  void execute(ARMState &state,Log &log) const
   {
    log.trace(state.PC(),"ADD#;",printArgs());
    
    setReg(state,DoADD(getArg1(state),getArg2(state)),log);
   }
 };

/* struct Cmd0_SUB */

struct Cmd0_SUB : Cmd0Base_binary
 {
  explicit Cmd0_SUB(Word cmd) : Cmd0Base_binary(cmd) {}
  
  template <class Log>
  void execute(ARMState &state,Log &log) const
   {
    log.trace(state.PC(),"SUB#;",printArgs());
    
    if( badArgs() ) 
      {
       log.trace("Bad PC usage");
      
       return state.cmdUndefined(log);
      } 
    
    setReg(state,DoSUB(getArg1(state),getArg2(state)),log);
   }
 };

/* struct Cmd1_SUB */

struct Cmd1_SUB : Cmd1Base_binary
 {
  explicit Cmd1_SUB(Word cmd) : Cmd1Base_binary(cmd) {}
  
  template <class Log>
  void execute(ARMState &state,Log &log) const
   {
    log.trace(state.PC(),"SUB#;",printArgs());
    
    setReg(state,DoSUB(getArg1(state),getArg2(state)),log);
   }
 };

/* struct Cmd0_RSB */

struct Cmd0_RSB : Cmd0Base_binary
 {
  explicit Cmd0_RSB(Word cmd) : Cmd0Base_binary(cmd) {}
  
  template <class Log>
  void execute(ARMState &state,Log &log) const
   {
    log.trace(state.PC(),"RSB#;",printArgs());
    
    if( badArgs() ) 
      {
       log.trace("Bad PC usage");
      
       return state.cmdUndefined(log);
      } 
    
    setReg(state,DoSUB(getArg2(state),getArg1(state)),log);
   }
 };

/* struct Cmd1_RSB */

struct Cmd1_RSB : Cmd1Base_binary
 {
  explicit Cmd1_RSB(Word cmd) : Cmd1Base_binary(cmd) {}
  
  template <class Log>
  void execute(ARMState &state,Log &log) const
   {
    log.trace(state.PC(),"RSB#;",printArgs());
    
    setReg(state,DoSUB(getArg2(state),getArg1(state)),log);
   }
 };

/* struct Cmd0_ADC */

struct Cmd0_ADC : Cmd0Base_binary
 {
  explicit Cmd0_ADC(Word cmd) : Cmd0Base_binary(cmd) {}
  
  template <class Log>
  void execute(ARMState &state,Log &log) const
   {
    log.trace(state.PC(),"ADC#;",printArgs());
    
    if( badArgs() ) 
      {
       log.trace("Bad PC usage");
      
       return state.cmdUndefined(log);
      } 
    
    setReg(state,DoADC(getArg1(state),getArg2(state),state.CPSR&SR_C),log);
   }
 };

/* struct Cmd1_ADC */

struct Cmd1_ADC : Cmd1Base_binary
 {
  explicit Cmd1_ADC(Word cmd) : Cmd1Base_binary(cmd) {}
  
  template <class Log>
  void execute(ARMState &state,Log &log) const
   {
    log.trace(state.PC(),"ADC#;",printArgs());
    
    setReg(state,DoADC(getArg1(state),getArg2(state),state.CPSR&SR_C),log);
   }
 };

/* struct Cmd0_SBC */

struct Cmd0_SBC : Cmd0Base_binary
 {
  explicit Cmd0_SBC(Word cmd) : Cmd0Base_binary(cmd) {}
  
  template <class Log>
  void execute(ARMState &state,Log &log) const
   {
    log.trace(state.PC(),"SBC#;",printArgs());
    
    if( badArgs() ) 
      {
       log.trace("Bad PC usage");
      
       return state.cmdUndefined(log);
      } 
    
    setReg(state,DoSBC(getArg1(state),getArg2(state),!(state.CPSR&SR_C)),log);
   }
 };

/* struct Cmd1_SBC */

struct Cmd1_SBC : Cmd1Base_binary
 {
  explicit Cmd1_SBC(Word cmd) : Cmd1Base_binary(cmd) {}
  
  template <class Log>
  void execute(ARMState &state,Log &log) const
   {
    log.trace(state.PC(),"SBC#;",printArgs());
    
    setReg(state,DoSBC(getArg1(state),getArg2(state),!(state.CPSR&SR_C)),log);
   }
 };

/* struct Cmd0_RSC */

struct Cmd0_RSC : Cmd0Base_binary
 {
  explicit Cmd0_RSC(Word cmd) : Cmd0Base_binary(cmd) {}
  
  template <class Log>
  void execute(ARMState &state,Log &log) const
   {
    log.trace(state.PC(),"RSC#;",printArgs());
    
    if( badArgs() ) 
      {
       log.trace("Bad PC usage");
      
       return state.cmdUndefined(log);
      } 
    
    setReg(state,DoSBC(getArg2(state),getArg1(state),!(state.CPSR&SR_C)),log);
   }
 };

/* struct Cmd1_RSC */

struct Cmd1_RSC : Cmd1Base_binary
 {
  explicit Cmd1_RSC(Word cmd) : Cmd1Base_binary(cmd) {}
  
  template <class Log>
  void execute(ARMState &state,Log &log) const
   {
    log.trace(state.PC(),"RSC#;",printArgs());
    
    setReg(state,DoSBC(getArg2(state),getArg1(state),!(state.CPSR&SR_C)),log);
   }
 };

/* struct Cmd0_TST */

struct Cmd0_TST : Cmd0Base_flags
 {
  explicit Cmd0_TST(Word cmd) : Cmd0Base_flags(cmd) {}
  
  template <class Log>
  void execute(ARMState &state,Log &log) const
   {
    log.trace(state.PC(),"TST#;",printArgs());
    
    if( badArgs() ) 
      {
       log.trace("Bad PC usage");
      
       return state.cmdUndefined(log);
      } 
    
    setFlags(state,DoAND(getArg1(state),getArg2(state)),log);
   }
 };

/* struct Cmd1_TST */

struct Cmd1_TST : Cmd1Base_flags
 {
  explicit Cmd1_TST(Word cmd) : Cmd1Base_flags(cmd) {}
  
  template <class Log>
  void execute(ARMState &state,Log &log) const
   {
    log.trace(state.PC(),"TST#;",printArgs());
    
    setFlags(state,DoAND(getArg1(state),getArg2(state)),log);
   }
 };

/* struct Cmd0_TEQ */

struct Cmd0_TEQ : Cmd0Base_flags
 {
  explicit Cmd0_TEQ(Word cmd) : Cmd0Base_flags(cmd) {}
  
  template <class Log>
  void execute(ARMState &state,Log &log) const
   {
    log.trace(state.PC(),"TEQ#;",printArgs());
    
    if( badArgs() ) 
      {
       log.trace("Bad PC usage");
      
       return state.cmdUndefined(log);
      } 
    
    setFlags(state,DoEOR(getArg1(state),getArg2(state)),log);
   }
 };

/* struct Cmd1_TEQ */
 
struct Cmd1_TEQ : Cmd1Base_flags
 {
  explicit Cmd1_TEQ(Word cmd) : Cmd1Base_flags(cmd) {}
  
  template <class Log>
  void execute(ARMState &state,Log &log) const
   {
    log.trace(state.PC(),"TEQ#;",printArgs());
    
    setFlags(state,DoEOR(getArg1(state),getArg2(state)),log);
   }
 };

/* struct Cmd0_CMP */

struct Cmd0_CMP : Cmd0Base_flags
 {
  explicit Cmd0_CMP(Word cmd) : Cmd0Base_flags(cmd) {}
  
  template <class Log>
  void execute(ARMState &state,Log &log) const
   {
    log.trace(state.PC(),"CMP#;",printArgs());
    
    if( badArgs() ) 
      {
       log.trace("Bad PC usage");
      
       return state.cmdUndefined(log);
      } 
    
    setFlags(state,DoSUB(getArg1(state),getArg2(state)),log);
   }
 };

/* struct Cmd1_CMP */

struct Cmd1_CMP : Cmd1Base_flags
 {
  explicit Cmd1_CMP(Word cmd) : Cmd1Base_flags(cmd) {}
  
  template <class Log>
  void execute(ARMState &state,Log &log) const
   {
    log.trace(state.PC(),"CMP#;",printArgs());
    
    setFlags(state,DoSUB(getArg1(state),getArg2(state)),log);
   }
 };

/* struct Cmd0_CMN */

struct Cmd0_CMN : Cmd0Base_flags
 {
  explicit Cmd0_CMN(Word cmd) : Cmd0Base_flags(cmd) {}
  
  template <class Log>
  void execute(ARMState &state,Log &log) const
   {
    log.trace(state.PC(),"CMN#;",printArgs());
    
    if( badArgs() ) 
      {
       log.trace("Bad PC usage");
      
       return state.cmdUndefined(log);
      } 
    
    setFlags(state,DoADD(getArg1(state),getArg2(state)),log);
   }
 };

/* struct Cmd1_CMN */

struct Cmd1_CMN : Cmd1Base_flags
 {
  explicit Cmd1_CMN(Word cmd) : Cmd1Base_flags(cmd) {}
  
  template <class Log>
  void execute(ARMState &state,Log &log) const
   {
    log.trace(state.PC(),"CMN#;",printArgs());
    
    setFlags(state,DoADD(getArg1(state),getArg2(state)),log);
   }
 };

/* struct Cmd0_MOV */

struct Cmd0_MOV : Cmd0Base_unary
 {
  explicit Cmd0_MOV(Word cmd) : Cmd0Base_unary(cmd) {}
  
  template <class Log>
  void execute(ARMState &state,Log &log) const
   {
    log.trace(state.PC(),"MOV#;",printArgs());
    
    if( badArgs() ) 
      {
       log.trace("Bad PC usage");
      
       return state.cmdUndefined(log);
      } 
    
    setReg(state,DoMOV(getArg2(state)),log);
   }
 };

/* struct Cmd1_MOV */

struct Cmd1_MOV : Cmd1Base_unary
 {
  explicit Cmd1_MOV(Word cmd) : Cmd1Base_unary(cmd) {}
  
  template <class Log>
  void execute(ARMState &state,Log &log) const
   {
    log.trace(state.PC(),"MOV#;",printArgs());
    
    setReg(state,DoMOV(getArg2(state)),log);
   }
 };

/* struct Cmd0_MVN */

struct Cmd0_MVN : Cmd0Base_unary
 {
  explicit Cmd0_MVN(Word cmd) : Cmd0Base_unary(cmd) {}
  
  template <class Log>
  void execute(ARMState &state,Log &log) const
   {
    log.trace(state.PC(),"MVN#;",printArgs());
    
    if( badArgs() ) 
      {
       log.trace("Bad PC usage");
      
       return state.cmdUndefined(log);
      } 
    
    setReg(state,DoMVN(getArg2(state)),log);
   }
 };

/* struct Cmd1_MVN */

struct Cmd1_MVN : Cmd1Base_unary
 {
  explicit Cmd1_MVN(Word cmd) : Cmd1Base_unary(cmd) {}
  
  template <class Log>
  void execute(ARMState &state,Log &log) const
   {
    log.trace(state.PC(),"MVN#;",printArgs());
    
    setReg(state,DoMVN(getArg2(state)),log);
   }
 };

/* struct Cmd0_CLZ */

struct Cmd0_CLZ : CmdBaseRdNoS , CmdBaseRm
 {
  explicit Cmd0_CLZ(Word cmd) : CmdBaseRdNoS(cmd) , CmdBaseRm(cmd) {}
  
  bool badArgs() const { return Rd==15 || Rm==15 ; }
  
  struct PrintArgs
   {
    const Cmd0_CLZ &obj;
    
    explicit PrintArgs(const Cmd0_CLZ &obj_) : obj(obj_) {}
    
    template <class P>
    void print(P &out) const
     {
      Printf(out," #;, #;",PrintReg(obj.Rd),PrintReg(obj.Rm));
     }
   };
  
  PrintArgs printArgs() const { return PrintArgs(*this); }
  
  template <class Log>
  void execute(ARMState &state,Log &log) const
   {
    log.trace(state.PC(),"CLZ#;",printArgs());
    
    if( badArgs() ) 
      {
       log.trace("Bad PC usage");
      
       return state.cmdUndefined(log);
      }
    
    setReg(state,DoCLZ(getArg2(state)),log);
   }
 };

/* struct Cmd0_QADD */

struct Cmd0_QADD : CmdBaseQ
 {
  explicit Cmd0_QADD(Word cmd) : CmdBaseQ(cmd) {}
  
  template <class Log>
  void execute(ARMState &state,Log &log) const
   {
    log.trace(state.PC(),"QADD#;",printArgs());
    
    if( badArgs() ) 
      {
       log.trace("Bad PC usage");
      
       return state.cmdUndefined(log);
      }
    
    setReg(state,DoQADD(getArg2(state),getArg1(state)),log);
   }
 };

/* struct Cmd0_QSUB */

struct Cmd0_QSUB : CmdBaseQ
 {
  explicit Cmd0_QSUB(Word cmd) : CmdBaseQ(cmd) {}
  
  template <class Log>
  void execute(ARMState &state,Log &log) const
   {
    log.trace(state.PC(),"QSUB#;",printArgs());
    
    if( badArgs() ) 
      {
       log.trace("Bad PC usage");
      
       return state.cmdUndefined(log);
      }
    
    setReg(state,DoQSUB(getArg2(state),getArg1(state)),log);
   }
 };

/* struct Cmd0_QDADD */

struct Cmd0_QDADD : CmdBaseQ
 {
  explicit Cmd0_QDADD(Word cmd) : CmdBaseQ(cmd) {}
  
  template <class Log>
  void execute(ARMState &state,Log &log) const
   {
    log.trace(state.PC(),"QDADD#;",printArgs());
    
    if( badArgs() ) 
      {
       log.trace("Bad PC usage");
      
       return state.cmdUndefined(log);
      }
    
    setReg(state,DoQDADD(getArg2(state),getArg1(state)),log);
   }
 };

/* struct Cmd0_QDSUB */

struct Cmd0_QDSUB : CmdBaseQ
 {
  explicit Cmd0_QDSUB(Word cmd) : CmdBaseQ(cmd) {}
  
  template <class Log>
  void execute(ARMState &state,Log &log) const
   {
    log.trace(state.PC(),"QDSUB#;",printArgs());
    
    if( badArgs() ) 
      {
       log.trace("Bad PC usage");
      
       return state.cmdUndefined(log);
      }
    
    setReg(state,DoQDSUB(getArg2(state),getArg1(state)),log);
   }
 };

/* struct Cmd0_MUL */

struct Cmd0_MUL : CmdBaseMUL
 {
  explicit Cmd0_MUL(Word cmd) : CmdBaseMUL(cmd) {}
  
  template <class Log>
  void execute(ARMState &state,Log &log) const
   {
    log.trace(state.PC(),"MUL#;",printArgs());
    
    if( badArgs() )
      {
       log.trace("Bad PC usage");
     
       return state.cmdUndefined(log);
      }
    
    setReg(state,DoMUL(getArg1(state),getArg2(state)),log);
   }
 };

/* struct Cmd0_MLA */

struct Cmd0_MLA : CmdBaseMLA
 {
  explicit Cmd0_MLA(Word cmd) : CmdBaseMLA(cmd) {}
  
  template <class Log>
  void execute(ARMState &state,Log &log) const
   {
    log.trace(state.PC(),"MLA#;",printArgs());
    
    if( badArgs() )
      {
       log.trace("Bad PC usage");
     
       return state.cmdUndefined(log);
      }
    
    setReg(state,DoMLA(getArg1(state),getArg2(state),getArg3(state)),log);
   }
 };

/* struct Cmd0_SMULL */

struct Cmd0_SMULL : CmdBaseML
 {
  explicit Cmd0_SMULL(Word cmd) : CmdBaseML(cmd) {} 
  
  template <class Log>
  void execute(ARMState &state,Log &log) const
   {
    log.trace(state.PC(),"SMULL#;",printArgs());
    
    if( badArgs() )
      {
       log.trace("Bad register usage");
     
       return state.cmdUndefined(log);
      }
    
    setReg(state,DoSMULL(getArg1(state),getArg2(state)),log);
   }
 };

/* struct Cmd0_UMULL */

struct Cmd0_UMULL : CmdBaseML
 {
  explicit Cmd0_UMULL(Word cmd) : CmdBaseML(cmd) {} 
  
  template <class Log>
  void execute(ARMState &state,Log &log) const
   {
    log.trace(state.PC(),"UMULL#;",printArgs());
    
    if( badArgs() )
      {
       log.trace("Bad resgister usage");
     
       return state.cmdUndefined(log);
      }
    
    setReg(state,DoUMULL(getArg1(state),getArg2(state)),log);
   }
 };

/* struct Cmd0_SMLAL */

struct Cmd0_SMLAL : CmdBaseML
 {
  explicit Cmd0_SMLAL(Word cmd) : CmdBaseML(cmd) {} 
  
  template <class Log>
  void execute(ARMState &state,Log &log) const
   {
    log.trace(state.PC(),"SMLAL#;",printArgs());
    
    if( badArgs() )
      {
       log.trace("Bad resgister usage");
     
       return state.cmdUndefined(log);
      }
    
    setReg(state,DoSMLAL(getArg1(state),getArg2(state),getHi(state),getLo(state)),log);
   }
 };

/* struct Cmd0_UMLAL */

struct Cmd0_UMLAL : CmdBaseML
 {
  explicit Cmd0_UMLAL(Word cmd) : CmdBaseML(cmd) {} 
  
  template <class Log>
  void execute(ARMState &state,Log &log) const
   {
    log.trace(state.PC(),"UMLAL#;",printArgs());
    
    if( badArgs() )
      {
       log.trace("Bad resgister usage");
     
       return state.cmdUndefined(log);
      }
    
    setReg(state,DoUMLAL(getArg1(state),getArg2(state),getHi(state),getLo(state)),log);
   }
 };

/* struct Cmd0_SMULxy */

struct Cmd0_SMULxy : CmdBaseMULy
 {
  Word bit_x;
  Word bit_y;
  
  explicit Cmd0_SMULxy(Word cmd) 
   : CmdBaseMULy(cmd) 
   {
    bit_x=cmd&Bit(5);
    bit_y=cmd&Bit(6);
   } 
  
  template <class Log>
  void execute(ARMState &state,Log &log) const
   {
    log.trace(state.PC(),"SMUL#;#;#;",(bit_x?"T":"B"),(bit_y?"T":"B"),printArgs());
    
    if( badArgs() )
      {
       log.trace("Bad PC usage");
     
       return state.cmdUndefined(log);
      }
    
    setReg(state,DoSMULxy(getArg1(state),getArg2(state),bit_x,bit_y),log);
   }
 };

/* struct Cmd0_SMULWy */

struct Cmd0_SMULWy : CmdBaseMULy
 {
  Word bit_y;
  
  explicit Cmd0_SMULWy(Word cmd) 
   : CmdBaseMULy(cmd) 
   {
    bit_y=cmd&Bit(6);
   }
  
  template <class Log>
  void execute(ARMState &state,Log &log) const
   {
    log.trace(state.PC(),"SMULW#;#;",(bit_y?"T":"B"),printArgs());
    
    if( badArgs() )
      {
       log.trace("Bad PC usage");
     
       return state.cmdUndefined(log);
      }
    
    setReg(state,DoSMULWy(getArg1(state),getArg2(state),bit_y),log);
   }
 };

/* struct Cmd0_SMLAxy */

struct Cmd0_SMLAxy : CmdBaseMLAy
 {
  Word bit_x;
  Word bit_y;
  
  explicit Cmd0_SMLAxy(Word cmd) 
   : CmdBaseMLAy(cmd) 
   {
    bit_x=cmd&Bit(5);
    bit_y=cmd&Bit(6);
   } 
  
  template <class Log>
  void execute(ARMState &state,Log &log) const
   {
    log.trace(state.PC(),"SMLA#;#;#;",(bit_x?"T":"B"),(bit_y?"T":"B"),printArgs());
    
    if( badArgs() )
      {
       log.trace("Bad PC usage");
     
       return state.cmdUndefined(log);
      }
    
    setReg(state,DoSMLAxy(getArg1(state),getArg2(state),getArg3(state),bit_x,bit_y),log);
   }
 };

/* struct Cmd0_SMLAWy */

struct Cmd0_SMLAWy : CmdBaseMLAy
 {
  Word bit_y;
  
  explicit Cmd0_SMLAWy(Word cmd) 
   : CmdBaseMLAy(cmd) 
   {
    bit_y=cmd&Bit(6);
   }
  
  template <class Log>
  void execute(ARMState &state,Log &log) const
   {
    log.trace(state.PC(),"SMLAW#;#;",(bit_y?"T":"B"),printArgs());
    
    if( badArgs() )
      {
       log.trace("Bad PC usage");
     
       return state.cmdUndefined(log);
      }
    
    setReg(state,DoSMLAWy(getArg1(state),getArg2(state),getArg3(state),bit_y),log);
   }
 };

/* struct Cmd0_SMLALxy */

struct Cmd0_SMLALxy : CmdBaseMLAy
 {
  Word bit_x;
  Word bit_y;
  
  explicit Cmd0_SMLALxy(Word cmd) 
   : CmdBaseMLAy(cmd) 
   {
    bit_x=cmd&Bit(5);
    bit_y=cmd&Bit(6);
   }
  
  bool badArgs() const { return Rd==15 || Rm==15 || Rs==15 || Rn==15 || Rn==Rd ; }
  
  Word getLo(const ARMState &state) const
   {
    return state.getReg(Rn);
   }
  
  Word getHi(const ARMState &state) const
   {
    return state.getReg(Rd);
   }
  
  template <class Log>
  void setReg(ARMState &state,ResultD res,Log &log) const
   {
    log.trace("#; = #9.h; #; = #9.h;",PrintReg(Rn),res.lo,PrintReg(Rd),res.hi);
  
    state.R[Rn]=res.lo;
    state.R[Rd]=res.hi;
   
    state.nextPC();
   }
  
  struct PrintArgs
   {
    const Cmd0_SMLALxy &obj;
    
    explicit PrintArgs(const Cmd0_SMLALxy &obj_) : obj(obj_) {}
    
    template <class P>
    void print(P &out) const
     {
      Printf(out," #;, #;, #;, #;",PrintReg(obj.Rn),PrintReg(obj.Rd),PrintReg(obj.Rm),PrintReg(obj.Rs));
     }
   };
  
  PrintArgs printArgs() const { return PrintArgs(*this); }
  
  template <class Log>
  void execute(ARMState &state,Log &log) const
   {
    log.trace(state.PC(),"SMLAL#;#;#;",(bit_x?"T":"B"),(bit_y?"T":"B"),printArgs());
    
    if( badArgs() )
      {
       log.trace("Bad register usage");
     
       return state.cmdUndefined(log);
      }
    
    setReg(state,DoSMLALxy(getArg1(state),getArg2(state),getHi(state),getLo(state),bit_x,bit_y),log);
   }
 };

/* struct Cmd0_BLX */

struct Cmd0_BLX
 {
  Word Rm;
  
  explicit Cmd0_BLX(Word cmd) 
   {
    Rm=cmd&15;
   }
  
  Word getArg(const ARMState &state) const
   {
    return state.getReg(Rm);
   }
  
  template <class Log>
  void execute(ARMState &state,Log &log) const
   {
    log.trace(state.PC(),"BLX #;",PrintReg(Rm));
    
    if( Rm==15 )
      {
       log.trace("Bad PC usage");
     
       return state.cmdUndefined(log);
      }
    
    Word dst=getArg(state);
    
    state.setPCLR_T(dst,log);
   }
 };

/* struct Cmd0_BX */

struct Cmd0_BX
 {
  Word Rm;
  
  explicit Cmd0_BX(Word cmd) 
   {
    Rm=cmd&15;
   }
  
  Word getArg(const ARMState &state) const
   {
    return state.getReg(Rm);
   }
  
  template <class Log>
  void execute(ARMState &state,Log &log) const
   {
    log.trace(state.PC(),"BX #;",PrintReg(Rm));
    
    Word dst=getArg(state);
    
    state.setPC_T(dst,log);
   }
 };

/* struct Cmd5_B */

struct Cmd5_B
 {
  Word off;
  Word bitL;
  
  explicit Cmd5_B(Word cmd)
   {
    Word imm=cmd&Field(24);
    
    if( imm&Bit(23) ) imm|=Field(6,24);
    
    off=(imm<<2)+8;
    bitL=cmd&Bit(24);
   }
  
  template <class Log>
  void execute(ARMState &state,Log &log) const
   {
    Word PC=state.PC();
    
    if( bitL ) 
      {
       log.trace(PC,"BL +#9.h;",off);
       log.trace("PC = #9.h; LR = #9.h;",PC+off,PC+4);
       
       state.LR()=PC+4;
      }
    else
      {
       log.trace(PC,"B +#9.h;",off);
       log.trace("PC = #9.h;",PC+off);
      }
    
    state.PC()=PC+off;
   }
 };

/* struct Cmd0_BKPT */

struct Cmd0_BKPT
 {
  Word num;
  
  explicit Cmd0_BKPT(Word cmd)
   {
    num=(cmd&15)|((cmd>>4)&Field(12,4));
   }
  
  template <class Log>
  void execute(ARMState &state,Log &log) const
   {
    log.trace(state.PC(),"BKPT #5.h;",num);
    
    state.toPrefetchAbort(log);
   }
 };

/* struct Cmd7_SWI */

struct Cmd7_SWI
 {
  Word num;
  
  explicit Cmd7_SWI(Word cmd)
   {
    num=cmd&Field(24);
   }
  
  template <class Log>
  void execute(ARMState &state,Log &log) const
   {
    log.trace(state.PC(),"SWI #7.h;",num);
    
    state.toSVC(log);
   }
 };

/* struct Cmd0_MRS */

struct Cmd0_MRS
 {
  Word Rd;
  Word bitR;
  
  explicit Cmd0_MRS(Word cmd)
   {
    Rd=(cmd>>12)&15;
    bitR=cmd&Bit(22);
   }
  
  template <class Log>
  void execute(ARMState &state,Log &log) const
   {
    log.trace(state.PC(),"MRS #;, #;",PrintReg(Rd),(bitR?"SPSR":"CPSR"));
    
    if( Rd==15 )
      {
       log.trace("Bad PC usage");
       
       return state.cmdUndefined(log);
      }
    
    Word val;
    
    if( bitR )
      {
       Word cur_mode=state.CPSR&SR_M;
      
       if( cur_mode==SR_M_usr || cur_mode==SR_M_sys )
         {
          log.trace("No SPSR register");
          
          return state.cmdUndefined(log);
         }

       val=state.SPSR;
      }
    else
      {
       val=state.CPSR;
      }
    
    log.trace("#; = #9.h;",PrintReg(Rd),val);
   
    state.R[Rd]=val;
    
    state.nextPC();
   }
 };

/* struct Cmd0_MSR */

struct Cmd0_MSR
 {
  Word bitR;
  Word mask;
  Word Rm;
  
  explicit Cmd0_MSR(Word cmd)
   {
    bitR=cmd&Bit(22);
    mask=(cmd>>16)&15;
    Rm=cmd&15;
   }
  
  template <class Log>
  void execute(ARMState &state,Log &log) const
   {
    log.trace(state.PC(),"MSR #;#;, #;",(bitR?"SPSR":"CPSR"),PrintSRMask(mask),PrintReg(Rm));
    
    Word val=state.getReg(Rm);
    
    if( bitR )
      state.setSPSR(mask,val,log);
    else
      state.setCPSR(mask,val,log);
   }
 };

/* struct Cmd1_MSR */

struct Cmd1_MSR
 {
  Word bitR;
  Word mask;
  Word imm;
  
  explicit Cmd1_MSR(Word cmd)
   {
    bitR=cmd&Bit(22);
    mask=(cmd>>16)&15;
    
    imm=cmd&Field(8);
    
    Word rot=((cmd>>8)&15)*2;
    
    if( rot )
      {
       imm=RotR(imm,rot);
      }
   }
  
  template <class Log>
  void execute(ARMState &state,Log &log) const
   {
    log.trace(state.PC(),"MSR #;#;, ###9.h;",(bitR?"SPSR":"CPSR"),PrintSRMask(mask),imm);
    
    if( bitR )
      state.setSPSR(mask,imm,log);
    else
      state.setCPSR(mask,imm,log);
   }
 };

/* struct Cmd2_LDR */

struct Cmd2_LDR : Cmd2MemBase
 {
  explicit Cmd2_LDR(Word cmd) : Cmd2MemBase(cmd) {}
  
  template <class Memory,class Log>
  void execute(ARMState &state,Memory &mem,Log &log) const
   {
    log.trace(state.PC(),"LDR#;",printArgs());
    
    if( badArgs() )
      {
       log.trace("Bad PC usage");
      
       return state.cmdUndefined(log);
      }
    
    if( badWriteBack() )
      {
       log.trace("Rd write-back");
      
       return state.cmdUndefined(log);
      }
    
    Word address=state.getReg(Rn);
    Word sum=bitU?(address+offset):(address-offset);
    
    MemUnit data;
    
    if( bitP )
      {
       log.trace("address = #9.h;",sum);
       
       data=mem.getD(sum);
       
       if( !data )
         {
          return state.dataAbort(sum,data.tag,log);
         }
       
       if( bitW ) writeBack(state,sum,log);
      }
    else
      {
       log.trace("address = #9.h;",address);
      
       data=(bitW?mem.getD_usr(address):mem.getD(address));
       
       if( !data )
         {
          return state.dataAbort(address,data.tag,log);
         }
      
       writeBack(state,sum,log);
      }
    
    setReg(state,data.value,log);
   }
 };

/* struct Cmd3_LDR */

struct Cmd3_LDR : Cmd3MemBase
 {
  explicit Cmd3_LDR(Word cmd) : Cmd3MemBase(cmd) {}
  
  template <class Memory,class Log>
  void execute(ARMState &state,Memory &mem,Log &log) const
   {
    log.trace(state.PC(),"LDR#;",printArgs());
    
    if( badArgs() )
      {
       log.trace("Bad PC usage");
      
       return state.cmdUndefined(log);
      }
    
    if( badWriteBack() )
      {
       log.trace("Rd write-back");
      
       return state.cmdUndefined(log);
      }
    
    Word address=state.getReg(Rn);
    Word offset=getOffset(state);
    Word sum=bitU?(address+offset):(address-offset);
    
    MemUnit data;
    
    if( bitP )
      {
       log.trace("address = #9.h;",sum);
       
       data=mem.getD(sum);
       
       if( !data )
         {
          return state.dataAbort(sum,data.tag,log);
         }
       
       if( bitW ) writeBack(state,sum,log);
      }
    else
      {
       log.trace("address = #9.h;",address);
      
       data=(bitW?mem.getD_usr(address):mem.getD(address));
       
       if( !data )
         {
          return state.dataAbort(address,data.tag,log);
         }
      
       writeBack(state,sum,log);
      }
    
    setReg(state,data.value,log);
   }
 };

/* struct Cmd2_LDRB */

struct Cmd2_LDRB : Cmd2MemBase
 {
  explicit Cmd2_LDRB(Word cmd) : Cmd2MemBase(cmd) {}
  
  template <class Memory,class Log>
  void execute(ARMState &state,Memory &mem,Log &log) const
   {
    log.trace(state.PC(),"LDRB#;",printArgs());
    
    if( Rd==15 || badArgs() )
      {
       log.trace("Bad PC usage");
      
       return state.cmdUndefined(log);
      }
    
    if( badWriteBack() )
      {
       log.trace("Rd write-back");
      
       return state.cmdUndefined(log);
      }
    
    Word address=state.getReg(Rn);
    Word sum=bitU?(address+offset):(address-offset);
    
    MemUnit data;
    
    if( bitP )
      {
       log.trace("address = #9.h;",sum);
      
       data=mem.getB(sum);
       
       if( !data )
         {
          return state.dataAbort(sum,data.tag,log);
         }
       
       if( bitW ) writeBack(state,sum,log);
      }
    else
      {
       log.trace("address = #9.h;",address);
     
       data=(bitW?mem.getB_usr(address):mem.getB(address));
       
       if( !data )
         {
          return state.dataAbort(address,data.tag,log);
         }
      
       writeBack(state,sum,log);
      }
    
    setReg_noPC(state,data.value,log);
   }
 };

/* struct Cmd3_LDRB */

struct Cmd3_LDRB : Cmd3MemBase
 {
  explicit Cmd3_LDRB(Word cmd) : Cmd3MemBase(cmd) {}
  
  template <class Memory,class Log>
  void execute(ARMState &state,Memory &mem,Log &log) const
   {
    log.trace(state.PC(),"LDRB#;",printArgs());
    
    if( Rd==15 || badArgs() )
      {
       log.trace("Bad PC usage");
      
       return state.cmdUndefined(log);
      }
    
    if( badWriteBack() )
      {
       log.trace("Rd write-back");
      
       return state.cmdUndefined(log);
      }
    
    Word address=state.getReg(Rn);
    Word offset=getOffset(state);
    Word sum=bitU?(address+offset):(address-offset);
    
    MemUnit data;
    
    if( bitP )
      {
       log.trace("address = #9.h;",sum);
      
       data=mem.getB(sum);
       
       if( !data )
         {
          return state.dataAbort(sum,data.tag,log);
         }
       
       if( bitW ) writeBack(state,sum,log);
      }
    else
      {
       log.trace("address = #9.h;",address);
     
       data=(bitW?mem.getB_usr(address):mem.getB(address));
       
       if( !data )
         {
          return state.dataAbort(address,data.tag,log);
         }
      
       writeBack(state,sum,log);
      }
    
    setReg_noPC(state,data.value,log);
   }
 };

/* struct Cmd2_STR */

struct Cmd2_STR : Cmd2MemBase
 {
  explicit Cmd2_STR(Word cmd) : Cmd2MemBase(cmd) {}
  
  template <class Memory,class Log>
  void execute(ARMState &state,Memory &mem,Log &log) const
   {
    log.trace(state.PC(),"STR#;",printArgs());
    
    if( badArgs() )
      {
       log.trace("Bad PC usage");
      
       return state.cmdUndefined(log);
      }
    
    if( badWriteBack() )
      {
       log.trace("Rd write-back");
      
       return state.cmdUndefined(log);
      }
    
    Word val=state.getReg(Rd);
    Word address=state.getReg(Rn);
    Word sum=bitU?(address+offset):(address-offset);
    
    if( bitP )
      {
       log.trace("address = #9.h; val = #9.h;",sum,val);
       
       NegMemTag result=mem.putD(sum,val);
       
       if( !result )
         {
          return state.dataAbort(sum,result.tag,log);
         }
       
       if( bitW ) writeBack(state,sum,log);
      }
    else
      {
       log.trace("address = #9.h; val = #9.h;",address,val);
      
       NegMemTag result=(bitW?mem.putD_usr(address,val):mem.putD(address,val));
       
       if( !result )
         {
          return state.dataAbort(address,result.tag,log);
         }
      
       writeBack(state,sum,log);
      }
    
    state.nextPC();
   }
 };

/* struct Cmd3_STR */

struct Cmd3_STR : Cmd3MemBase
 {
  explicit Cmd3_STR(Word cmd) : Cmd3MemBase(cmd) {}
  
  template <class Memory,class Log>
  void execute(ARMState &state,Memory &mem,Log &log) const
   {
    log.trace(state.PC(),"STR#;",printArgs());
    
    if( badArgs() )
      {
       log.trace("Bad PC usage");
      
       return state.cmdUndefined(log);
      }
    
    if( badWriteBack() )
      {
       log.trace("Rd write-back");
      
       return state.cmdUndefined(log);
      }
    
    Word val=state.getReg(Rd);
    Word address=state.getReg(Rn);
    Word offset=getOffset(state);
    Word sum=bitU?(address+offset):(address-offset);
    
    if( bitP )
      {
       log.trace("address = #9.h; val = #9.h;",sum,val);
       
       NegMemTag result=mem.putD(sum,val);
       
       if( !result )
         {
          return state.dataAbort(sum,result.tag,log);
         }
       
       if( bitW ) writeBack(state,sum,log);
      }
    else
      {
       log.trace("address = #9.h; val = #9.h;",address,val);
      
       NegMemTag result=(bitW?mem.putD_usr(address,val):mem.putD(address,val));
       
       if( !result )
         {
          return state.dataAbort(address,result.tag,log);
         }
      
       writeBack(state,sum,log);
      }
    
    state.nextPC();
   }
 };

/* struct Cmd2_STRB */

struct Cmd2_STRB : Cmd2MemBase
 {
  explicit Cmd2_STRB(Word cmd) : Cmd2MemBase(cmd) {}
  
  template <class Memory,class Log>
  void execute(ARMState &state,Memory &mem,Log &log) const
   {
    log.trace(state.PC(),"STRB#;",printArgs());
    
    if( badArgs() )
      {
       log.trace("Bad PC usage");
      
       return state.cmdUndefined(log);
      }
    
    if( badWriteBack() )
      {
       log.trace("Rd write-back");
      
       return state.cmdUndefined(log);
      }
    
    Byte val=Byte(state.getReg(Rd));
    Word address=state.getReg(Rn);
    Word sum=bitU?(address+offset):(address-offset);
    
    if( bitP )
      {
       log.trace("address = #9.h; val = #3.h;",sum,val);
       
       NegMemTag result=mem.putB(sum,val);
       
       if( !result )
         {
          return state.dataAbort(sum,result.tag,log);
         }
       
       if( bitW ) writeBack(state,sum,log);
      }
    else
      {
       log.trace("address = #9.h; val = #3.h;",address,val);
      
       NegMemTag result=(bitW?mem.putB_usr(address,val):mem.putB(address,val));
       
       if( !result )
         {
          return state.dataAbort(address,result.tag,log);
         }
      
       writeBack(state,sum,log);
      }
    
    state.nextPC();
   }
 };

/* struct Cmd3_STRB */

struct Cmd3_STRB : Cmd3MemBase
 {
  explicit Cmd3_STRB(Word cmd) : Cmd3MemBase(cmd) {}
  
  template <class Memory,class Log>
  void execute(ARMState &state,Memory &mem,Log &log) const
   {
    log.trace(state.PC(),"STRB#;",printArgs());
    
    if( badArgs() )
      {
       log.trace("Bad PC usage");
      
       return state.cmdUndefined(log);
      }
    
    if( badWriteBack() )
      {
       log.trace("Rd write-back");
      
       return state.cmdUndefined(log);
      }
    
    Byte val=Byte(state.getReg(Rd));
    Word address=state.getReg(Rn);
    Word offset=getOffset(state);
    Word sum=bitU?(address+offset):(address-offset);
    
    if( bitP )
      {
       log.trace("address = #9.h; val = #3.h;",sum,val);
       
       NegMemTag result=mem.putB(sum,val);
       
       if( !result )
         {
          return state.dataAbort(sum,result.tag,log);
         }
       
       if( bitW ) writeBack(state,sum,log);
      }
    else
      {
       log.trace("address = #9.h; val = #3.h;",address,val);
      
       NegMemTag result=(bitW?mem.putB_usr(address,val):mem.putB(address,val));
       
       if( !result )
         {
          return state.dataAbort(address,result.tag,log);
         }
      
       writeBack(state,sum,log);
      }
    
    state.nextPC();
   }
 };

/* struct Cmd2_PLD */

struct Cmd2_PLD : Cmd2MemBase
 {
  explicit Cmd2_PLD(Word cmd) : Cmd2MemBase(cmd) {}
  
  template <class Memory,class Log>
  void execute(ARMState &state,Memory &mem,Log &log) const
   {
    log.trace(state.PC(),"PLD#;",printArgs());
    
    if( badArgs() )
      {
       log.trace("Bad PC usage");
      
       return state.cmdUndefined(log);
      }
    
    Word address=state.getReg(Rn);
    Word sum=bitU?(address+offset):(address-offset);
    
    log.trace("address = #9.h;",sum);
       
    mem.preload(sum);
       
    state.nextPC();
   }
 };

/* struct Cmd3_PLD */

struct Cmd3_PLD : Cmd3MemBase
 {
  explicit Cmd3_PLD(Word cmd) : Cmd3MemBase(cmd) {}
  
  template <class Memory,class Log>
  void execute(ARMState &state,Memory &mem,Log &log) const
   {
    log.trace(state.PC(),"PLD#;",printArgs());
    
    if( badArgs() )
      {
       log.trace("Bad PC usage");
      
       return state.cmdUndefined(log);
      }
    
    Word address=state.getReg(Rn);
    Word offset=getOffset(state);
    Word sum=bitU?(address+offset):(address-offset);
    
    log.trace("address = #9.h;",sum);
       
    mem.preload(sum);
       
    state.nextPC();
   }
 };

/* struct Cmd0_SWP */

struct Cmd0_SWP
 {
  Word Rm;
  Word Rd;
  Word Rn;
  
  explicit Cmd0_SWP(Word cmd)
   {
    Rm=cmd&15;
    Rd=(cmd>>12)&15;
    Rn=(cmd>>16)&15;
   }
  
  bool badArgs() const { return Rm==15 || Rd==15 || Rn==15 || (Rn==Rd) || (Rn==Rm) ; }
  
  template <class Memory,class Log>
  void execute(ARMState &state,Memory &mem,Log &log) const
   {
    log.trace(state.PC(),"SWP #;, #;, [#;]",PrintReg(Rd),PrintReg(Rm),PrintReg(Rn));
    
    if( badArgs() )
      {
       log.trace("Bad register usage");
      
       return state.cmdUndefined(log);
      }
    
    Word address=state.getReg(Rn);
    Word val=state.getReg(Rm);

    MemUnit data=mem.swapD(address,val);
    
    if( !data  )
      {
       return state.dataAbort(address,data.tag,log);
      }
    
    log.trace("address = #9.h; val = #9.h;",address,val);
    log.trace("#; = #9.h;",PrintReg(Rd),data.value);
    
    state.R[Rd]=data.value;
    
    state.nextPC();
   }
 };

/* struct Cmd0_SWPB */

struct Cmd0_SWPB
 {
  Word Rm;
  Word Rd;
  Word Rn;
  
  explicit Cmd0_SWPB(Word cmd)
   {
    Rm=cmd&15;
    Rd=(cmd>>12)&15;
    Rn=(cmd>>16)&15;
   }
  
  bool badArgs() const { return Rm==15 || Rd==15 || Rn==15 || (Rn==Rd) || (Rn==Rm) ; }
  
  template <class Memory,class Log>
  void execute(ARMState &state,Memory &mem,Log &log) const
   {
    log.trace(state.PC(),"SWPB #;, #;, [#;]",PrintReg(Rd),PrintReg(Rm),PrintReg(Rn));
    
    if( badArgs() )
      {
       log.trace("Bad register usage");
      
       return state.cmdUndefined(log);
      }
    
    Word address=state.getReg(Rn);
    Byte val=Byte(state.getReg(Rm));

    MemUnit data=mem.swapB(address,val);
    
    if( !data  )
      {
       return state.dataAbort(address,data.tag,log);
      }
    
    log.trace("address = #9.h; val = #3.h;",address,val);
    log.trace("#; = #9.h;",PrintReg(Rd),data.value);
    
    state.R[Rd]=data.value;
    
    state.nextPC();
   }
 };

/* struct Cmd0_LDRH */

struct Cmd0_LDRH : CmdExtMemBase
 {
  explicit Cmd0_LDRH(Word cmd) : CmdExtMemBase(cmd) {}
  
  template <class Memory,class Log>
  void execute(ARMState &state,Memory &mem,Log &log) const
   {
    log.trace(state.PC(),"LDRH#;",printArgs());
    
    if( badArgs() )
      {
       log.trace("Bad PC usage");
      
       return state.cmdUndefined(log);
      }
    
    if( badWriteBack() )
      {
       log.trace("Rd write-back");
      
       return state.cmdUndefined(log);
      }
    
    Word address=state.getReg(Rn);
    Word offset=getOffset(state);
    Word sum=bitU?(address+offset):(address-offset);
    
    MemUnit data;
    
    if( bitP )
      {
       log.trace("address = #9.h;",sum);
      
       data=mem.getH(sum);
       
       if( !data )
         {
          return state.dataAbort(sum,data.tag,log);
         }
       
       if( bitW ) writeBack(state,sum,log);
      }
    else
      {
       log.trace("address = #9.h;",address);
     
       data=mem.getH(address);
      
       if( !data )
         {
          return state.dataAbort(address,data.tag,log);
         }
       
       writeBack(state,sum,log);
      }
    
    setReg_noPC(state,data.value,log);
   }
 };

/* struct Cmd0_LDRSH */

struct Cmd0_LDRSH : CmdExtMemBase
 {
  explicit Cmd0_LDRSH(Word cmd) : CmdExtMemBase(cmd) {}
  
  template <class Memory,class Log>
  void execute(ARMState &state,Memory &mem,Log &log) const
   {
    log.trace(state.PC(),"LDRSH#;",printArgs());
    
    if( badArgs() )
      {
       log.trace("Bad PC usage");
      
       return state.cmdUndefined(log);
      }
    
    if( badWriteBack() )
      {
       log.trace("Rd write-back");
      
       return state.cmdUndefined(log);
      }
    
    Word address=state.getReg(Rn);
    Word offset=getOffset(state);
    Word sum=bitU?(address+offset):(address-offset);
    
    MemUnit data;
    
    if( bitP )
      {
       log.trace("address = #9.h;",sum);
      
       data=mem.getH(sum);
       
       if( !data )
         {
          return state.dataAbort(sum,data.tag,log);
         }
       
       if( bitW ) writeBack(state,sum,log);
      }
    else
      {
       log.trace("address = #9.h;",address);
     
       data=mem.getH(address);
      
       if( !data )
         {
          return state.dataAbort(address,data.tag,log);
         }
       
       writeBack(state,sum,log);
      }
    
    setReg_noPC(state,SHExt(data.value),log);
   }
 };

/* struct Cmd0_LDRSB */

struct Cmd0_LDRSB : CmdExtMemBase
 {
  explicit Cmd0_LDRSB(Word cmd) : CmdExtMemBase(cmd) {}
  
  template <class Memory,class Log>
  void execute(ARMState &state,Memory &mem,Log &log) const
   {
    log.trace(state.PC(),"LDRSB#;",printArgs());
    
    if( badArgs() )
      {
       log.trace("Bad PC usage");
      
       return state.cmdUndefined(log);
      }
    
    if( badWriteBack() )
      {
       log.trace("Rd write-back");
      
       return state.cmdUndefined(log);
      }
    
    Word address=state.getReg(Rn);
    Word offset=getOffset(state);
    Word sum=bitU?(address+offset):(address-offset);
    
    MemUnit data;
    
    if( bitP )
      {
       log.trace("address = #9.h;",sum);
      
       data=mem.getB(sum);
       
       if( !data )
         {
          return state.dataAbort(sum,data.tag,log);
         }
       
       if( bitW ) writeBack(state,sum,log);
      }
    else
      {
       log.trace("address = #9.h;",address);
     
       data=mem.getB(address);
      
       if( !data )
         {
          return state.dataAbort(address,data.tag,log);
         }
       
       writeBack(state,sum,log);
      }
    
    setReg_noPC(state,SBExt(data.value),log);
   }
 };

/* struct Cmd0_STRH */

struct Cmd0_STRH : CmdExtMemBase
 {
  explicit Cmd0_STRH(Word cmd) : CmdExtMemBase(cmd) {}
  
  template <class Memory,class Log>
  void execute(ARMState &state,Memory &mem,Log &log) const
   {
    log.trace(state.PC(),"STRH#;",printArgs());
    
    if( badArgs() )
      {
       log.trace("Bad PC usage");
      
       return state.cmdUndefined(log);
      }
    
    if( badWriteBack() )
      {
       log.trace("Rd write-back");
      
       return state.cmdUndefined(log);
      }
    
    Half val=Half(state.getReg(Rd));
    Word address=state.getReg(Rn);
    Word offset=getOffset(state);
    Word sum=bitU?(address+offset):(address-offset);
    
    if( bitP )
      {
       log.trace("address = #9.h; val = #5.h;",sum,val);
       
       NegMemTag result=mem.putH(sum,val);
       
       if( !result )
         {
          return state.dataAbort(sum,result.tag,log);
         }
       
       if( bitW ) writeBack(state,sum,log);
      }
    else
      {
       log.trace("address = #9.h; val = #5.h;",address,val);
      
       NegMemTag result=mem.putH(address,val);
       
       if( !result )
         {
          return state.dataAbort(address,result.tag,log);
         }
      
       writeBack(state,sum,log);
      }
    
    state.nextPC();
   }
 };

/* struct Cmd0_LDRD */

struct Cmd0_LDRD : CmdExtMemBase
 {
  explicit Cmd0_LDRD(Word cmd) : CmdExtMemBase(cmd) {}
  
  bool badArgs() const { return Rd==14 || ( !bitI && Rm==15 ) || ( Rn==15 && ( !bitP || bitW ) ) ; }
  
  bool badWriteBack() const { return ( Rn==Rd || Rn==Rd+1 ) && ( !bitP || bitW ) ; }
  
  bool badRegs() const { return (Rd&1) || ( !bitI && ( Rm==Rd || Rm==Rd+1 ) ) ; }
  
  template <class Memory,class Log>
  void execute(ARMState &state,Memory &mem,Log &log) const
   {
    log.trace(state.PC(),"LDRD#;",printArgs());
    
    if( badArgs() )
      {
       log.trace("Bad PC usage");
      
       return state.cmdUndefined(log);
      }
    
    if( badWriteBack() )
      {
       log.trace("Rd write-back");
      
       return state.cmdUndefined(log);
      }
    
    if( badRegs() )
      {
       log.trace("Bad register usage");
     
       return state.cmdUndefined(log);
      }
    
    Word address=state.getReg(Rn);
    Word offset=getOffset(state);
    Word sum=bitU?(address+offset):(address-offset);
    
    MemUnit data0;
    MemUnit data1;
    
    if( bitP )
      {
       log.trace("address = #9.h;",sum);
      
       data0=mem.getD(sum);
       data1=mem.getD(sum+4);
       
       if( !data0 )
         {
          return state.dataAbort(sum,data0.tag,log);
         }
       
       if( !data1 )
         {
          return state.dataAbort(sum+4,data1.tag,log);
         }
       
       if( bitW ) writeBack(state,sum,log);
      }
    else
      {
       log.trace("address = #9.h;",address);
     
       data0=mem.getD(address);
       data1=mem.getD(address+4);
      
       if( !data0 )
         {
          return state.dataAbort(address,data0.tag,log);
         }
       
       if( !data1 )
         {
          return state.dataAbort(address+4,data1.tag,log);
         }
       
       writeBack(state,sum,log);
      }
    
    setReg_noPC(state,data0.value,data1.value,log);
   }
 };

/* struct Cmd0_STRD */

struct Cmd0_STRD : CmdExtMemBase
 {
  explicit Cmd0_STRD(Word cmd) : CmdExtMemBase(cmd) {}
  
  bool badArgs() const { return Rd==14 || ( !bitI && Rm==15 ) || ( Rn==15 && ( !bitP || bitW ) ) ; }
  
  bool badWriteBack() const { return ( Rn==Rd || Rn==Rd+1 ) && ( !bitP || bitW ) ; }
  
  bool badRegs() const { return (Rd&1) ; }
  
  template <class Memory,class Log>
  void execute(ARMState &state,Memory &mem,Log &log) const
   {
    log.trace(state.PC(),"STRD#;",printArgs());
    
    if( badArgs() )
      {
       log.trace("Bad PC usage");
      
       return state.cmdUndefined(log);
      }
    
    if( badWriteBack() )
      {
       log.trace("Rd write-back");
      
       return state.cmdUndefined(log);
      }
    
    if( badRegs() )
      {
       log.trace("Bad register usage");
     
       return state.cmdUndefined(log);
      }
    
    Word val0=state.getReg(Rd);
    Word val1=state.getReg(Rd+1);
    Word address=state.getReg(Rn);
    Word offset=getOffset(state);
    Word sum=bitU?(address+offset):(address-offset);
    
    if( bitP )
      {
       log.trace("address = #9.h; val0 = #9.h; val1 = #9.h;",sum,val0,val1);
      
       NegMemTag result0=mem.putD(sum  ,val0);
       NegMemTag result1=mem.putD(sum+4,val1);
       
       if( !result0 )
         {
          return state.dataAbort(sum,result0.tag,log);
         }
       
       if( !result1 )
         {
          return state.dataAbort(sum+4,result1.tag,log);
         }
       
       if( bitW ) writeBack(state,sum,log);
      }
    else
      {
       log.trace("address = #9.h; val0 = #9.h; val1 = #9.h;",address,val0,val1);
     
       NegMemTag result0=mem.putD(address  ,val0);
       NegMemTag result1=mem.putD(address+4,val1);
       
       if( !result0 )
         {
          return state.dataAbort(address,result0.tag,log);
         }
       
       if( !result1 )
         {
          return state.dataAbort(address+4,result1.tag,log);
         }
       
       writeBack(state,sum,log);
      }
    
    state.nextPC();
   }
 };

/* struct Cmd4_LDM */

struct Cmd4_LDM : CmdMultipleMemBase
 {
  Word setRn;
  Word setPC;
  
  explicit Cmd4_LDM(Word cmd) 
   : CmdMultipleMemBase(cmd) 
   {
    setRn=cmd&Bit(Rn);
    setPC=cmd&Bit(15);
   }
  
  template <class Memory,class Log>
  void execute(ARMState &state,Memory &mem,Log &log) const
   {
    if( bitS )
      {
       log.trace("Not implemented");
      
       return state.cmdUndefined(log);
      }
    else
      {
       log.trace(state.PC(),"LDM#;",printArgs());
      
       if( Rn==15 )
         {
          log.trace("Bad PC usage");
          
          return state.cmdUndefined(log);
         }
       
       if( len==0 )
         {
          log.trace("Empty list");
          
          return state.cmdUndefined(log);
         }
       
       if( bitW && setRn )
         {
          log.trace("Bad Rn usage");
         
          return state.cmdUndefined(log);
         }
       
       Word address=state.R[Rn];
       Word delta=4*len;
       
       if( bitU )
         {
          if( bitP )
            {
             address+=4;
            }
         }
       else
         {
          if( bitP )
            {
             address-=delta;
            }
          else
            {
             address-=delta-4;
            }
         }
       
       log.trace("address = #9.h;",address);
       
       Word newRn=0;
       Word newPC=0;
       
       for(Word reg : Range(list,len) )
         {
          MemUnit data=mem.getD(address);
          
          if( !data )
            {
             return state.dataAbort(address,data.tag,log);
            }
          
          if( reg==Rn )
            {
             newRn=data.value;
            }
          else if( reg==15 )
            {
             newPC=data.value;
            }
          else
            {
             log.trace("#; = #9.h;",PrintReg(reg),data.value);
            
             state.R[reg]=data.value;
            }
          
          address+=4;
         }
       
       if( bitW )
         {
          Word val=bitU?(state.R[Rn]+delta):(state.R[Rn]-delta);
         
          log.trace("#; = #9.h;",PrintReg(Rn),val);
          
          state.R[Rn]=val;
         }
       
       if( setRn ) 
         {
          log.trace("#; = #9.h;",PrintReg(Rn),newRn);
          
          state.R[Rn]=newRn;
         }
       
       if( setPC )
         {
          state.setPC_T(newPC,log);
         }
       else
         {
          state.nextPC();
         }
      }
   }
 };

/* struct Cmd4_STM */

struct Cmd4_STM : CmdMultipleMemBase
 {
  explicit Cmd4_STM(Word cmd) 
   : CmdMultipleMemBase(cmd) 
   {
   }
  
  template <class Memory,class Log>
  void execute(ARMState &state,Memory &mem,Log &log) const
   {
    if( bitS )
      {
       log.trace("Not implemented");
     
       return state.cmdUndefined(log);
      }
    else
      {
       log.trace(state.PC(),"STM#;",printArgs());
      
       if( Rn==15 )
         {
          log.trace("Bad PC usage");
          
          return state.cmdUndefined(log);
         }
       
       if( len==0 )
         {
          log.trace("Empty list");
          
          return state.cmdUndefined(log);
         }
       
       Word address=state.R[Rn];
       Word delta=4*len;
       
       if( bitU )
         {
          if( bitP )
            {
             address+=4;
            }
         }
       else
         {
          if( bitP )
            {
             address-=delta;
            }
          else
            {
             address-=delta-4;
            }
         }
       
       log.trace("address = #9.h;",address);
       
       for(Word reg : Range(list,len) )
         {
          Word val=state.getReg(reg);
          
          NegMemTag result=mem.putD(address,val);
         
          if( !result )
            {
             return state.dataAbort(address,result.tag,log);
            }
          
          log.trace("#9.h;",val);
            
          address+=4;
         }
       
       if( bitW )
         {
          Word val=bitU?(state.R[Rn]+delta):(state.R[Rn]-delta);
         
          log.trace("#; = #9.h;",PrintReg(Rn),val);
          
          state.R[Rn]=val;
         }
       
       state.nextPC();
      }
   }
 };

/* namespace ARMv5TE_nonT */

namespace ARMv5TE_nonT {

/* consts */

enum CmdType
 {
  // undefined
 
  CmdUndefined,
  
  // key 0
 
  Cmd0AND,
  Cmd0EOR,
  Cmd0SUB,
  Cmd0RSB,
  
  Cmd0ADD,
  Cmd0ADC,
  Cmd0SBC,
  Cmd0RSC,
  
  Cmd0TST,
  Cmd0TEQ,
  Cmd0CMP,
  Cmd0CMN,
  
  Cmd0ORR,
  Cmd0MOV,
  Cmd0BIC,
  Cmd0MVN,
  
  Cmd0MSR,
  Cmd0MRS,
  
  Cmd0BLX,
  Cmd0BX,
  Cmd0CLZ,
  Cmd0BKPT,
  
  Cmd0QADD,
  Cmd0QSUB,
  Cmd0QDADD,
  Cmd0QDSUB,
  
  Cmd0SMLAxy,
  Cmd0SMULWy,
  Cmd0SMLAWy,
  Cmd0SMLALxy,
  Cmd0SMULxy,
  
  Cmd0LDRH,
  Cmd0STRH,
  Cmd0LDRSB,
  Cmd0LDRD,
  Cmd0LDRSH,
  Cmd0STRD,
  
  Cmd0MUL,
  Cmd0MLA,
  Cmd0UMULL,
  Cmd0UMLAL,
  Cmd0SMULL,
  Cmd0SMLAL,
  
  Cmd0SWP,
  Cmd0SWPB,
  
  // key 1
  
  Cmd1AND,
  Cmd1EOR,
  Cmd1SUB,
  Cmd1RSB,
  
  Cmd1ADD,
  Cmd1ADC,
  Cmd1SBC,
  Cmd1RSC,
  
  Cmd1TST,
  Cmd1TEQ,
  Cmd1CMP,
  Cmd1CMN,
  
  Cmd1ORR,
  Cmd1MOV,
  Cmd1BIC,
  Cmd1MVN,
  
  Cmd1MSR,

  // key 2
  
  Cmd2STR,
  Cmd2LDR,
  Cmd2STRB,
  Cmd2LDRB,
  
  Cmd2PLD,
  
  // key 3
  
  Cmd3STR,
  Cmd3LDR,
  Cmd3STRB,
  Cmd3LDRB,
  
  Cmd3PLD,
  
  // key 4
  
  Cmd4LDM,
  Cmd4STM,
  
  // key 5
  
  Cmd5B,
  
  // key 6
  
  Cmd6LDC,
  Cmd6STC,
  
  Cmd6MRRC,
  Cmd6MCRR,
  
  // key 7
  
  Cmd7SWI,
  
  Cmd7MRC,
  Cmd7MCR,
  Cmd7CDP,
  
  // special
  
  CmdIRQ,
  CmdFIQ,
  CmdSKIP,
  
  CmdLim
 };

const char * GetTextDesc(CmdType type);

/* Decode() */

CmdType Decode(Word cmd);
 
/* classes */

struct CoProc;

template <class Memory> struct ExtMem;

class Stat;

struct Cmd6_LDC;
struct Cmd6_STC;

struct Cmd6_MRRC;
struct Cmd6_MCRR;

struct Cmd7_MRC;
struct Cmd7_MCR;
struct Cmd7_CDP;

template <class Memory,class Log> struct CmdAll;

struct ARMState_Copr;

template <class T> class Cache;

template <class Memory,class Log> struct CPUCore;

/* struct CoProc */

struct CoProc
 {
  // CP15
  
  Word regID;
  Word regControl;
  Word regTTBase;
  Word regDomainAC;
  Word regPID;
  
  Word regCacheType;
  Word regAuxControl;
  
  // methods
  
  void reset(bool hi_vector);
  
  ExtWord get(Word cp_num,Word opcode1,Word opcode2,Word CRn,Word CRm);
  
  bool /* bitC */ put(Word cp_num,Word opcode1,Word opcode2,Word CRn,Word CRm,Word val);
  
  bool /* bitC */ get2(Word cp_num,Word opcode,Word CRm,Word &a1,Word &a2);
  
  bool /* bitC */ put2(Word cp_num,Word opcode,Word CRm,Word a1,Word a2);
  
  bool /* bitC */ exec(Word cp_num,Word opcode1,Word opcode2,Word CRd,Word CRn,Word CRm);
 };

CoProc GetCopr(ARMState &state);

/* struct ExtMem<Memory> */

template <class Memory> 
struct ExtMem
 {
  Memory &mem;
  
  explicit ExtMem(Memory &mem_) : mem(mem_) {}
  
  // data access
  
  MemUnit getD(Word address) { return mem.getD(address); }
  
  MemUnit getD_usr(Word address) { return mem.getD(address); }
  
  MemUnit getH(Word address) { return mem.getH(address); }
  
  MemUnit getB(Word address) { return mem.getB(address); }
  
  MemUnit getB_usr(Word address) { return mem.getB(address); }
  
  NegMemTag putD(Word address,Word value) { return mem.putD(address,value); }
  
  NegMemTag putD_usr(Word address,Word value) { return mem.putD(address,value); }
  
  NegMemTag putH(Word address,Half value) { return mem.putH(address,value); }
  
  NegMemTag putB(Word address,Byte value) { return mem.putB(address,value); }
  
  NegMemTag putB_usr(Word address,Byte value) { return mem.putB(address,value); }
  
  // extra
  
  MemUnit swapD(Word address,Word value) 
   { 
    MemUnit ret=mem.getD(address);
    
    if( !ret ) return ret;
    
    NegMemTag result=mem.putD(address,value);
    
    if( !result ) return result.tag;
     
    return ret; 
   }
  
  MemUnit swapB(Word address,Byte value) 
   { 
    MemUnit ret=mem.getB(address);
    
    if( !ret ) return ret;
    
    NegMemTag result=mem.putB(address,value);
    
    if( !result ) return result.tag;
     
    return ret; 
   }
  
  void preload(Word address) { Used(address); }
 };

/* class Stat */

class Stat : NoCopy , public PrintOptAdapter<CmdType>
 {
   struct Rec
    {
     CmdType type;
     uint64 count;
     
     void set(CmdType type_,uint64 count_) 
      {
       type=type_;
       count=count_;
      }
     
     bool operator < (const Rec &obj) const { return count>obj.count; }
    };
   
   uint64 stat[CmdLim];
  
  public:
  
   Stat() { reset(); }
   
   void reset() 
    {
     Range(stat).set_null();
    }
   
   void count(CmdType type) { stat[type]++; }
   
   template <class P,class Opt>
   void print(P &out,const Opt &opt) const
    {
     Rec temp[CmdLim];
     
     for(unsigned i=0; i<CmdLim ;i++) temp[i].set(CmdType(i),stat[i]);
     
     Sort(Range(temp));
     
     for(const Rec &rec : temp )
       if( rec.count )
         {
          Printf(out,"#; = #;\n",BindOpt(opt,rec.type),rec.count);
         }
    }
 };

/* struct Cmd6_LDC */

struct Cmd6_LDC
 {
  explicit Cmd6_LDC(Word cmd)
   {
    Used(cmd);
   }
  
  template <class Memory,class Log>
  void execute(ARMState &state,Memory &mem,Log &log) const
   {
    Used(mem);
    
    log.trace(state.PC(),"LDC");
    
    log.trace("Not implemented");
    
    state.cmdUndefined(log);
   }
 };

/* struct Cmd6_STC */

struct Cmd6_STC
 {
  explicit Cmd6_STC(Word cmd)
   {
    Used(cmd);
   }
  
  template <class Memory,class Log>
  void execute(ARMState &state,Memory &mem,Log &log) const
   {
    Used(mem);
    
    log.trace(state.PC(),"STC");
    
    log.trace("Not implemented");
    
    state.cmdUndefined(log);
   }
 };

/* struct Cmd6_MRRC */

struct Cmd6_MRRC
 {
  Word cp_num;
  Word opcode;
  Word Rd;
  Word Rn;
  Word CRm;
  
  explicit Cmd6_MRRC(Word cmd)
   {
    cp_num=(cmd>>8)&15;
    opcode=(cmd>>4)&15;
    Rd=(cmd>>12)&15;
    Rn=(cmd>>16)&15;
    CRm=cmd&15;
   }
  
  template <class Log>
  void execute(ARMState &state,Log &log) const
   {
    log.trace(state.PC(),"MRRC #;, #;, #;, #;, #;",cp_num,opcode,PrintReg(Rd),PrintReg(Rn),CRm);
    
    if( Rd==15 || Rn==15 )
      {
       log.trace("Bad PC usage");
       
       return state.cmdUndefined(log);
      }
    
    Word a1;
    Word a2;
    
    bool bitC=GetCopr(state).get2(cp_num,opcode,CRm,a1,a2);
    
    if( bitC )
      {
       log.trace("Invalid command");
      
       return state.cmdUndefined(log);
      }
    
    log.trace("#; = #9.h; #; = #9.h;",PrintReg(Rd),a1,PrintReg(Rn),a2);
    
    state.R[Rd]=a1;
    state.R[Rn]=a2;
    
    state.nextPC();
   }
 };

/* struct Cmd6_MCRR */

struct Cmd6_MCRR
 {
  Word cp_num;
  Word opcode;
  Word Rd;
  Word Rn;
  Word CRm;
  
  explicit Cmd6_MCRR(Word cmd)
   {
    cp_num=(cmd>>8)&15;
    opcode=(cmd>>4)&15;
    Rd=(cmd>>12)&15;
    Rn=(cmd>>16)&15;
    CRm=cmd&15;
   }
  
  template <class Log>
  void execute(ARMState &state,Log &log) const
   {
    log.trace(state.PC(),"MCRR #;, #;, #;, #;, #;",cp_num,opcode,PrintReg(Rd),PrintReg(Rn),CRm);
    
    if( Rd==15 || Rn==15 )
      {
       log.trace("Bad PC usage");
       
       return state.cmdUndefined(log);
      }
    
    Word a1=state.R[Rd];
    Word a2=state.R[Rn];
    
    log.trace("a1 = #9.h; a2 = #9.h;",a1,a2);
    
    bool bitC=GetCopr(state).put2(cp_num,opcode,CRm,a1,a2);
    
    if( bitC )
      {
       log.trace("Invalid command");
       
       return state.cmdUndefined(log);
      }
    
    state.nextPC();
   }
 };

/* struct Cmd7_MRC */

struct Cmd7_MRC
 {
  Word cp_num;
  Word opcode1;
  Word opcode2;
  Word Rd;
  Word CRn;
  Word CRm;
  
  explicit Cmd7_MRC(Word cmd)
   {
    cp_num=(cmd>>8)&15;
    opcode1=(cmd>>21)&7;
    opcode2=(cmd>>5)&7;
    Rd=(cmd>>12)&15;
    CRn=(cmd>>16)&15;
    CRm=cmd&15;
   }
  
  template <class Log>
  void execute(ARMState &state,Log &log) const
   {
    log.trace(state.PC(),"MRC #;, #;, #;, #;, #;, #;",cp_num,opcode1,PrintReg(Rd),CRn,CRm,opcode2);
    
    ExtWord a=GetCopr(state).get(cp_num,opcode1,opcode2,CRn,CRm);
    
    if( a.bitC )
      {
       log.trace("Invalid command");
       
       return state.cmdUndefined(log);
      }
    
    if( Rd==15 )
      {
       Word val=Combine(Word(SR_cond),a,state.CPSR);
       
       log.trace("CPSR = #9.h;",val);
       
       state.CPSR=val;
      }
    else
      {
       log.trace("#; = #9.h;",PrintReg(Rd),Word(a));
      
       state.R[Rd]=a;
      }
       
    state.nextPC();
   }
 };

/* struct Cmd7_MCR */

struct Cmd7_MCR
 {
  Word cp_num;
  Word opcode1;
  Word opcode2;
  Word Rd;
  Word CRn;
  Word CRm;
  
  explicit Cmd7_MCR(Word cmd)
   {
    cp_num=(cmd>>8)&15;
    opcode1=(cmd>>21)&7;
    opcode2=(cmd>>5)&7;
    Rd=(cmd>>12)&15;
    CRn=(cmd>>16)&15;
    CRm=cmd&15;
   }
  
  template <class Log>
  void execute(ARMState &state,Log &log) const
   {
    log.trace(state.PC(),"MCR #;, #;, #;, #;, #;, #;",cp_num,opcode1,PrintReg(Rd),CRn,CRm,opcode2);
    
    if( Rd==15 )
      {
       log.trace("Bad PC usage");
       
       return state.cmdUndefined(log);
      }
    
    Word a=state.R[Rd];
    
    log.trace("#9.h;",a);
    
    bool bitC=GetCopr(state).put(cp_num,opcode1,opcode2,CRn,CRm,a);
    
    if( bitC )
      {
       log.trace("Invalid command");
       
       return state.cmdUndefined(log);
      }
    
    state.nextPC();
   }
 };

/* struct Cmd7_CDP */

struct Cmd7_CDP
 {
  Word cp_num;
  Word opcode1;
  Word opcode2;
  Word CRd;
  Word CRn;
  Word CRm;
  
  explicit Cmd7_CDP(Word cmd)
   {
    cp_num=(cmd>>8)&15;
    opcode1=(cmd>>20)&15;
    opcode2=(cmd>>5)&7;
    CRd=(cmd>>12)&15;
    CRn=(cmd>>16)&15;
    CRm=cmd&15;
   }
  
  template <class Log>
  void execute(ARMState &state,Log &log) const
   {
    log.trace(state.PC(),"CDP #;, #;, #;, #;, #;, #;",cp_num,opcode1,CRd,CRn,CRm,opcode2);
    
    bool bitC=GetCopr(state).exec(cp_num,opcode1,opcode2,CRd,CRn,CRm);
    
    if( bitC )
      {
       log.trace("Invalid command");
       
       return state.cmdUndefined(log);
      }
    
    state.nextPC();
   }
 };

/* struct CmdAll<Memory,Log> */

template <class Memory,class Log> 
struct CmdAll
 {
  CmdType type;
  Word cond;
  
  typedef CmdType (CmdAll::* ExecType)(ARMState &state,Memory &mem,Log &log);
  
  ExecType exec_method;
  
  static const ulen BufLen = 96 ;
  
  InitStorage<BufLen> buf;
  
  template <ulen Len>
  Place<void> getPlace()
   {
    static_assert( Len<=BufLen ,"Too small BufLen");
    
    return buf.getPlace();
   }
  
  CmdType execUndefined(ARMState &state,Memory &,Log &log)
   {
    Word cmd=*static_cast<Word *>(buf.getMem());
      
    state.cmdUndefined(cmd,log);
    
    return CmdUndefined;
   }
  
  template <class T>
  CmdType execCmd(ARMState &state,Memory &,Log &log)
   {
    if( state.pass(cond,log) )
      {
       static_cast<T *>(buf.getMem())->execute(state,log);
       
       return type;
      }
    else
      {
       log.trace(state.PC(),"SKIP");
    
       state.nextPC();
      
       return CmdSKIP;
      }
   }
  
  template <class T>
  CmdType execMemCmd(ARMState &state,Memory &mem,Log &log)
   {
    if( state.pass(cond,log) )
      {
       ExtMem<Memory> ext(mem);
      
       static_cast<T *>(buf.getMem())->execute(state,ext,log);
       
       return type;
      }
    else
      {
       log.trace(state.PC(),"SKIP");
    
       state.nextPC();
      
       return CmdSKIP;
      }
   }
  
  template <class T>
  void setCmd(Word cmd)
   {
    new(getPlace<sizeof (T)>()) T(cmd);
    
    exec_method=&CmdAll::execCmd<T>;
   }
  
  template <class T>
  void setMemCmd(Word cmd)
   {
    new(getPlace<sizeof (T)>()) T(cmd);
    
    exec_method=&CmdAll::execMemCmd<T>;
   }

  CmdAll() { type=CmdLim; }
  
  void init(Word cmd)
   {
    type=Decode(cmd);
    cond=cmd>>28;
    
    switch( type )
      {
       default:
       case CmdUndefined :
        {
         new(getPlace<sizeof (Word)>()) Word(cmd);
         
         exec_method=&CmdAll::execUndefined;
        }
       break;
       
       // key 0
     
       case Cmd0AND : setCmd<Cmd0_AND>(cmd); break;
       case Cmd0EOR : setCmd<Cmd0_EOR>(cmd); break;
       case Cmd0SUB : setCmd<Cmd0_SUB>(cmd); break;
       case Cmd0RSB : setCmd<Cmd0_RSB>(cmd); break;
       
       case Cmd0ADD : setCmd<Cmd0_ADD>(cmd); break;
       case Cmd0ADC : setCmd<Cmd0_ADC>(cmd); break;
       case Cmd0SBC : setCmd<Cmd0_SBC>(cmd); break;
       case Cmd0RSC : setCmd<Cmd0_RSC>(cmd); break;
       
       case Cmd0TST : setCmd<Cmd0_TST>(cmd); break;
       case Cmd0TEQ : setCmd<Cmd0_TEQ>(cmd); break;
       case Cmd0CMP : setCmd<Cmd0_CMP>(cmd); break;
       case Cmd0CMN : setCmd<Cmd0_CMN>(cmd); break;
       
       case Cmd0ORR : setCmd<Cmd0_ORR>(cmd); break;
       case Cmd0MOV : setCmd<Cmd0_MOV>(cmd); break;
       case Cmd0BIC : setCmd<Cmd0_BIC>(cmd); break;
       case Cmd0MVN : setCmd<Cmd0_MVN>(cmd); break;
       
       case Cmd0MSR : setCmd<Cmd0_MSR>(cmd); break;
       case Cmd0MRS : setCmd<Cmd0_MRS>(cmd); break;
       
       case Cmd0BLX  : setCmd<Cmd0_BLX>(cmd); break;
       case Cmd0BX   : setCmd<Cmd0_BX>(cmd); break;
       case Cmd0CLZ  : setCmd<Cmd0_CLZ>(cmd); break;
       case Cmd0BKPT : setCmd<Cmd0_BKPT>(cmd); break;
       
       case Cmd0QADD  : setCmd<Cmd0_QADD>(cmd); break;
       case Cmd0QSUB  : setCmd<Cmd0_QSUB>(cmd); break;
       case Cmd0QDADD : setCmd<Cmd0_QDADD>(cmd); break;
       case Cmd0QDSUB : setCmd<Cmd0_QDSUB>(cmd); break;
       
       case Cmd0SMLAxy  : setCmd<Cmd0_SMLAxy>(cmd); break;
       case Cmd0SMULWy  : setCmd<Cmd0_SMULWy>(cmd); break;
       case Cmd0SMLAWy  : setCmd<Cmd0_SMLAWy>(cmd); break;
       case Cmd0SMLALxy : setCmd<Cmd0_SMLALxy>(cmd); break;
       case Cmd0SMULxy  : setCmd<Cmd0_SMULxy>(cmd); break;
       
       case Cmd0LDRH  : setMemCmd<Cmd0_LDRH>(cmd); break;
       case Cmd0STRH  : setMemCmd<Cmd0_STRH>(cmd); break;
       case Cmd0LDRSB : setMemCmd<Cmd0_LDRSB>(cmd); break;
       case Cmd0LDRD  : setMemCmd<Cmd0_LDRD>(cmd); break;
       case Cmd0LDRSH : setMemCmd<Cmd0_LDRSH>(cmd); break;
       case Cmd0STRD  : setMemCmd<Cmd0_STRD>(cmd); break;
       
       case Cmd0MUL   : setCmd<Cmd0_MUL>(cmd); break;
       case Cmd0MLA   : setCmd<Cmd0_MLA>(cmd); break;
       case Cmd0UMULL : setCmd<Cmd0_UMULL>(cmd); break;
       case Cmd0UMLAL : setCmd<Cmd0_UMLAL>(cmd); break;
       case Cmd0SMULL : setCmd<Cmd0_SMULL>(cmd); break;
       case Cmd0SMLAL : setCmd<Cmd0_SMLAL>(cmd); break;
       
       case Cmd0SWP   : setMemCmd<Cmd0_SWP>(cmd); break;
       case Cmd0SWPB  : setMemCmd<Cmd0_SWPB>(cmd); break;
       
       // key 1
       
       case Cmd1AND : setCmd<Cmd1_AND>(cmd); break;
       case Cmd1EOR : setCmd<Cmd1_EOR>(cmd); break;
       case Cmd1SUB : setCmd<Cmd1_SUB>(cmd); break;
       case Cmd1RSB : setCmd<Cmd1_RSB>(cmd); break;
       
       case Cmd1ADD : setCmd<Cmd1_ADD>(cmd); break;
       case Cmd1ADC : setCmd<Cmd1_ADC>(cmd); break;
       case Cmd1SBC : setCmd<Cmd1_SBC>(cmd); break;
       case Cmd1RSC : setCmd<Cmd1_RSC>(cmd); break;
       
       case Cmd1TST : setCmd<Cmd1_TST>(cmd); break;
       case Cmd1TEQ : setCmd<Cmd1_TEQ>(cmd); break;
       case Cmd1CMP : setCmd<Cmd1_CMP>(cmd); break;
       case Cmd1CMN : setCmd<Cmd1_CMN>(cmd); break;
       
       case Cmd1ORR : setCmd<Cmd1_ORR>(cmd); break;
       case Cmd1MOV : setCmd<Cmd1_MOV>(cmd); break;
       case Cmd1BIC : setCmd<Cmd1_BIC>(cmd); break;
       case Cmd1MVN : setCmd<Cmd1_MVN>(cmd); break;
       
       case Cmd1MSR : setCmd<Cmd1_MSR>(cmd); break;

       // key 2
       
       case Cmd2STR  : setMemCmd<Cmd2_STR>(cmd); break;
       case Cmd2LDR  : setMemCmd<Cmd2_LDR>(cmd); break;
       case Cmd2STRB : setMemCmd<Cmd2_STRB>(cmd); break;
       case Cmd2LDRB : setMemCmd<Cmd2_LDRB>(cmd); break;
       
       case Cmd2PLD : setMemCmd<Cmd2_PLD>(cmd); break;
       
       // key 3
       
       case Cmd3STR  : setMemCmd<Cmd3_STR>(cmd); break;
       case Cmd3LDR  : setMemCmd<Cmd3_LDR>(cmd); break;
       case Cmd3STRB : setMemCmd<Cmd3_STRB>(cmd); break;
       case Cmd3LDRB : setMemCmd<Cmd3_LDRB>(cmd); break;
       
       case Cmd3PLD : setMemCmd<Cmd3_PLD>(cmd); break;
       
       // key 4
       
       case Cmd4LDM : setMemCmd<Cmd4_LDM>(cmd); break;
       case Cmd4STM : setMemCmd<Cmd4_STM>(cmd); break;
       
       // key 5
       
       case Cmd5B : setCmd<Cmd5_B>(cmd); break;
       
       // key 6
       
       case Cmd6LDC : setMemCmd<Cmd6_LDC>(cmd); break;
       case Cmd6STC : setMemCmd<Cmd6_STC>(cmd); break;
       
       case Cmd6MRRC : setCmd<Cmd6_MRRC>(cmd); break;
       case Cmd6MCRR : setCmd<Cmd6_MCRR>(cmd); break;
       
       // key 7
       
       case Cmd7SWI : setCmd<Cmd7_SWI>(cmd); break;
       
       case Cmd7MRC : setCmd<Cmd7_MRC>(cmd); break;
       case Cmd7MCR : setCmd<Cmd7_MCR>(cmd); break;
       case Cmd7CDP : setCmd<Cmd7_CDP>(cmd); break;
      }
   }
  
  CmdType execute(ARMState &state,Memory &mem,Log &log)
   {
    return (this->*exec_method)(state,mem,log);
   }

  // no-throw flags
  
  enum NoThrowFlagType
   {
    Default_no_throw = true,
    Copy_no_throw = true
   };
 };

/* struct ARMState_Copr */

struct ARMState_Copr : ARMState
 {
  CoProc copr;
 };

inline CoProc GetCopr(ARMState &state) { return static_cast<ARMState_Copr &>(state).copr; }

/* class Cache<T> */

template <class T> 
class Cache : NoCopy
 {
   static const ulen Len = 1<<20 ;
   static const ulen Count = 1<<12 ;
   
   struct Index
    {
     ulen base;
     ulen index;
     
     explicit Index(Word address)
      {
       base=address>>20;
       index=address&Field(20);
      }
    };
   
   DynArray<DynArray<T> > buf;
 
  public:
 
   Cache() : buf(Count) {}
   
   ~Cache() {}
   
   T * get(Word address)
    {
     Index idx(address);
     
     if( buf[idx.base].getLen()==0 ) return 0;
     
     T *ptr=buf[idx.base].getPtr()+idx.index;
     
     if( ptr->type==CmdLim ) return 0;
     
     return ptr;
    }
   
   T * set(Word address,Word cmd)
    {
     Index idx(address);
     
     if( buf[idx.base].getLen()==0 ) 
       {
        buf[idx.base].extend_default(Len);
       }
     
     T *ptr=buf[idx.base].getPtr()+idx.index;
     
     ptr->init(cmd);
     
     return ptr;
    }
 };

/* struct CPUCore<Memory,Log> */

template <class Memory,class Log> 
struct CPUCore : ARMState_Copr
 {
  Stat stat;
  
  typedef CmdAll<Memory,Log> CmdType; 
  
  Cache<CmdType> cache;
  
  // execute
  
  void reset(bool hi_vector=false);

  void stepFIQ(Log &log);

  void stepIRQ(Log &log);

  void step(Memory &mem,Log &log);
  
  static const char * Version() { return "ARMv5TE-nonT"; }
 };

 // execute

template <class Memory,class Log>
void CPUCore<Memory,Log>::reset(bool hi_vector_)
 {
  (ARMState_Copr &)*this=DefaultValue();
  
  setSRAll(SR_N|SR_Z|SR_C|SR_V|SR_Q|SR_I|SR_F|SR_M);

  SPSR=CPSR=SR_M_svc|SR_I|SR_F;
  PC()=hi_vector?0xFFFF0000:0x0000;
  
  copr.reset(hi_vector=hi_vector_);
  
  stat.reset();
 }

template <class Memory,class Log>
void CPUCore<Memory,Log>::stepFIQ(Log &log)
 {
  stat.count(CmdFIQ);
  
  toFIQ(log);
 }

template <class Memory,class Log>
void CPUCore<Memory,Log>::stepIRQ(Log &log)
 {
  stat.count(CmdIRQ);
  
  toIRQ(log);
 }

template <class Memory,class Log>
void CPUCore<Memory,Log>::step(Memory &mem,Log &log)
 {
  Word address=PC();
  CmdType *cmd=cache.get(address);
  
  if( !cmd )
    {
     MemUnit code=mem.getX(address);
     
     if( !code )
       {
        return toPrefetchAbort(log);
       }
     
     cmd=cache.set(address,code.value);
    }
  
  stat.count( cmd->execute(*this,mem,log) );
 }

/* ARM v5TE Command Set

--- Data Processing ------------------------------------------------------------

AND
EOR
ORR
BIC

ADD
SUB
RSB

ADC
SBC
RSC

TST
TEQ
CMP
CMN

MOV
MVN

--- Extended Data Processing ---------------------------------------------------

CLZ

QADD
QDADD
QDSUB
QSUB

--- Mul ------------------------------------------------------------------------

MLA
MUL
UMLAL
UMULL
SMLAL
SMULL

SMLAxy
SMLALxy
SMLAWy
SMULxy
SMULWy

--- Branch ---------------------------------------------------------------------

B
BL
BLX
BX

--- Interrupt ------------------------------------------------------------------

BKPT
SWI

--- Status Register ------------------------------------------------------------

MRS
MSR

--- Load-Store -----------------------------------------------------------------

LDR
LDRB

STR
STRB

PLD

LDRH
LDRD
LDRSB
LDRSH

STRH
STRD

--- Load-Store multiple --------------------------------------------------------

LDM TODO
STM TODO

--- Atomic ---------------------------------------------------------------------

SWP
SWPB

--- CP -------------------------------------------------------------------------

MCR  TODO
MCRR TODO

MRC  TODO
MRRC TODO

CDP  TODO

--- Load-Store CP --------------------------------------------------------------

LDC TODO
STC TODO

--------------------------------------------------------------------------------

*/ 

} // namespace ARMv5TE_nonT

} // namespace ARMCore
 
#endif

