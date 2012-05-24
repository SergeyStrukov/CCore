/* ARMState.h */
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

#ifndef ARMGo_inc_ARMState_h
#define ARMGo_inc_ARMState_h

#include <inc/ARMBase.h>

namespace ARMCore {

/* consts */ 

enum SRBits : Word
 {
  // bits
  
  SR_N   = Bit(31),
  SR_Z   = Bit(30),
  SR_C   = Bit(29),
  SR_V   = Bit(28),
  SR_Q   = Bit(27),
  
  SR_J   = Bit(24),
  
  SR_GE3 = Bit(19),
  SR_GE2 = Bit(18),
  SR_GE1 = Bit(17),
  SR_GE0 = Bit(16),
  
  SR_E   = Bit(9),
  SR_A   = Bit(8),
  SR_I   = Bit(7),
  SR_F   = Bit(6),
  SR_T   = Bit(5),
  
  // fields
  
  SR_GE   = Field(4,16),
  
  SR_M    = Field(5),
  
  SR_cond = SR_N|SR_Z|SR_C|SR_V,
  SR_usr  = SR_N|SR_Z|SR_C|SR_V|SR_Q|SR_GE|SR_E,
  
  // modes
  
  SR_M_usr = 0x10,
  SR_M_fiq = 0x11,
  SR_M_irq = 0x12,
  SR_M_svc = 0x13,
  SR_M_abt = 0x17,
  SR_M_und = 0x1B,
  SR_M_sys = 0x1F
 };

enum CondCode : Word
 {
  Cond_EQ, //  Z
  Cond_NE, // !Z
  Cond_CS, //  C
  Cond_CC, // !C
  
  Cond_MI, //  N
  Cond_PL, // !N
  Cond_VS, //  V
  Cond_VC, // !V
  
  Cond_HI, //  C && !Z
  Cond_LS, // !C ||  Z
  Cond_GE, //  N == V
  Cond_LT, //  N != V
  
  Cond_GT, // !Z && ( N == V )
  Cond_LE, //  Z || ( N != V )
  Cond_AL,
  Cond_Undefined
 };
 
/* classes */

struct BitsNZ;

struct ARMState;
 
/* struct BitsNZ */

struct BitsNZ
 {
  bool bitN;
  bool bitZ;
  
  explicit BitsNZ(Word val) 
   {
    bitN=val&Bit(31);
    bitZ=!val;
   }
  
  explicit BitsNZ(Word hi,Word lo) 
   {
    bitN=hi&Bit(31);
    bitZ=!(hi|lo);
   }
  
  template <class P>
  void print(P &out) const
   {
    Printf(out,"N = #; Z = #;",(unsigned)bitN,(unsigned)bitZ);
   }
 };

/* struct ARMState */

struct ARMState
 {
  // modes
  
  bool hi_vector;
  Word SR_all;
  Word bitE;
  Word bitA;
  Word bitT;
  
  // state
  
  Word R[16];
  Word CPSR;
   
  Word SPSR;
  
  // special registers
   
  Word & PC() { return R[15]; }
  Word & LR() { return R[14]; }
  
  void nextPC() { PC()+=4; }

  // banking

  Word R8_usr,R9_usr,R10_usr,R11_usr,R12_usr,R13_usr,R14_usr;

  Word R13_svc,R14_svc,SPSR_svc;
  Word R13_abt,R14_abt,SPSR_abt;
  Word R13_und,R14_und,SPSR_und;
  Word R13_irq,R14_irq,SPSR_irq;

  Word R8_fiq,R9_fiq,R10_fiq,R11_fiq,R12_fiq,R13_fiq,R14_fiq,SPSR_fiq;

  void saveBank_usr();
  void saveBank_sys();
  void saveBank_svc();
  void saveBank_abt();
  void saveBank_und();
  void saveBank_irq();
  void saveBank_fiq();

  void loadBank_usr();
  void loadBank_sys();
  void loadBank_svc();
  void loadBank_abt();
  void loadBank_und();
  void loadBank_irq();
  void loadBank_fiq();

  void saveBank(Word mode);
  void loadBank(Word mode);

  // switch mode

  template <class Log>
  void toPrefetchAbort(Log &log);
  
  template <class Log>
  void toIRQ(Log &log);
  
  template <class Log>
  void toFIQ(Log &log);
  
  template <class Log>
  void toSVC(Log &log);
  
  template <class Log>
  void cmdUndefined(Log &log);

  template <class Log>
  void cmdUndefined(Word cmd,Log &log);
  
  template <class Log>
  void dataAbort(Word address,MemTag tag,Log &log);
  
  // set PC 
  
  template <class Log>
  void setPC(Word val,Log &log);
  
  template <class Log>
  void setPCLR(Word val,Log &log);
  
  template <class Log>
  void setPCT(Word val,Log &log);
  
  template <class Log>
  void setPCLRT(Word val,Log &log);
  
  template <class Log>
  void setPC_T(Word val,Log &log);
  
  template <class Log>
  void setPCLR_T(Word val,Log &log);
  
  // set CPSR
  
  static bool TestMode(Word mode);

  template <class Log>
  void popCPSR(Log &log);
  
  template <class Log>
  void setCPSR(Word mask,Word val,Log &log);
  
  template <class Log>
  void setSPSR(Word mask,Word val,Log &log);
  
  // getReg()
  
  Word getReg(Word num) const
   {
    if( num<15 ) return R[num];
    
    return R[15]+8;
   }
  
  // set flags
  
  void setFlags(BitsNZ bits)
   {
    BitClear(CPSR,SR_N|SR_Z);
    
    CPSR|=BitAt(bits.bitN,31)|BitAt(bits.bitZ,30);
   }
  
  void setFlags(BitsNZ bits,bool bitC)
   {
    BitClear(CPSR,SR_N|SR_Z|SR_C);
    
    CPSR|=BitAt(bits.bitN,31)|BitAt(bits.bitZ,30)|BitAt(bitC,29);
   }
  
  void setFlags(BitsNZ bits,bool bitC,bool bitV)
   {
    BitClear(CPSR,SR_N|SR_Z|SR_C|SR_V);
    
    CPSR|=BitAt(bits.bitN,31)|BitAt(bits.bitZ,30)|BitAt(bitC,29)|BitAt(bitV,28);
   }
  
  // pass()
  
  static bool EQorNULL(Word a,Word b) { return (a==b) || (a==0) ; }

  template <class Log>
  bool pass(Word cond,Log &log) const;
  
  // exception bits
  
  void setSRAll(Word bits)
   {
    SR_all=bits;
    bitA=bits&SR_A; 
    bitT=bits&SR_T;
   } 
  
  void setE(bool bit) 
   { 
    bitE=BitAt(bit,9); 
   }
  
  void setHiVector(bool hi_vector_)
   {
    hi_vector=hi_vector_;
   }
 };

 // switch mode

template <class Log>
void ARMState::toPrefetchAbort(Log &log)
 {
  log.toPrefetchAbort(PC());
  
  saveBank(CPSR&SR_M);

  log.trace("LR = #9.h; SPSR = #9.h;",PC()+4,CPSR);
  
  R14_abt=PC()+4;
  SPSR_abt=CPSR;

  CPSR=(CPSR&~(SR_M|SR_T))|SR_M_abt|SR_I|bitE|bitA;
  PC()=hi_vector?0xFFFF000C:0x000C;

  loadBank_abt();
 }

template <class Log>
void ARMState::toIRQ(Log &log)
 {
  log.toIRQ(PC());
  
  saveBank(CPSR&SR_M);
  
  log.trace("LR = #9.h; SPSR = #9.h;",PC()+4,CPSR);

  R14_irq=PC()+4;
  SPSR_irq=CPSR;

  CPSR=(CPSR&~(SR_M|SR_T))|SR_M_irq|SR_I|bitE|bitA;
  PC()=hi_vector?0xFFFF0018:0x0018;

  loadBank_irq();
 }

template <class Log>
void ARMState::toFIQ(Log &log)
 {
  log.toFIQ(PC());
  
  saveBank(CPSR&SR_M);

  log.trace("LR = #9.h; SPSR = #9.h;",PC()+4,CPSR);
  
  R14_fiq=PC()+4;
  SPSR_fiq=CPSR;

  CPSR=(CPSR&~(SR_M|SR_T))|SR_M_fiq|SR_I|SR_F|bitE|bitA;
  PC()=hi_vector?0xFFFF001C:0x001C;

  loadBank_fiq();
 }

template <class Log>
void ARMState::toSVC(Log &log)
 {
  log.toSVC(PC());
  
  saveBank(CPSR&SR_M);

  log.trace("LR = #9.h; SPSR = #9.h;",PC()+4,CPSR);
  
  R14_svc=PC()+4;
  SPSR_svc=CPSR;

  CPSR=(CPSR&~(SR_M|SR_T))|SR_M_svc|SR_I|bitE;
  PC()=hi_vector?0xFFFF0008:0x0008;

  loadBank_svc();
 }

template <class Log>
void ARMState::cmdUndefined(Log &log)
 {
  saveBank(CPSR&SR_M);
  
  log.trace("LR = #9.h; SPSR = #9.h;",PC()+4,CPSR);
  
  R14_und=PC()+4;
  SPSR_und=CPSR;
  
  CPSR=(CPSR&~(SR_M|SR_T))|SR_M_und|SR_I|bitE;
  PC()=hi_vector?0xFFFF0004:0x0004;
  
  loadBank_und();
 }

template <class Log>
void ARMState::cmdUndefined(Word cmd,Log &log)
 {
  log.cmdUndefined(PC(),cmd);
  
  cmdUndefined(log);
 }

template <class Log>
void ARMState::dataAbort(Word address,MemTag tag,Log &log)
 {
  log.dataAbort(PC(),address,tag);
  
  saveBank(CPSR&SR_M);

  log.trace("LR = #9.h; SPSR = #9.h;",PC()+8,CPSR);
  
  R14_abt=PC()+8;
  SPSR_abt=CPSR;

  CPSR=(CPSR&~(SR_M|SR_T))|SR_M_abt|SR_I|bitE|bitA;
  PC()=hi_vector?0xFFFF0010:0x0010;

  loadBank_abt();
 }

 // set PC

template <class Log>
void ARMState::setPC(Word val,Log &log)
 {
  log.trace("PC = #9.h;",val);
  
  if( val&3 )
    {
     log.trace("Not aligned PC value");
    
     return cmdUndefined(log);
    }
  
  PC()=val;
 }

template <class Log>
void ARMState::setPCLR(Word val,Log &log)
 {
  log.trace("PC = #9.h; LR = #9.h;",val,PC()+4);
  
  if( val&3 )
    {
     log.trace("Not aligned PC value");
    
     return cmdUndefined(log);
    }

  LR()=PC()+4;
  PC()=val;
 }

template <class Log>
void ARMState::setPCT(Word val,Log &log)
 {
  if( (CPSR&SR_M)==SR_M_usr ) return setPC(val,log);
  
  if( !(SR_all&SR_T) )
    {
     log.trace("No Thumb mode");
   
     return cmdUndefined(log);
    }
  
  log.trace("PC = #9.h; switch to Thumb",val);
  
  if( val&3 )
    {
     log.trace("Not aligned PC value");
    
     return cmdUndefined(log);
    }

  CPSR|=bitT;
  PC()=val;
 }

template <class Log>
void ARMState::setPCLRT(Word val,Log &log)
 {
  if( (CPSR&SR_M)==SR_M_usr ) return setPCLR(val,log);
  
  if( !(SR_all&SR_T) )
    {
     log.trace("No Thumb mode");
   
     return cmdUndefined(log);
    }
  
  log.trace("PC = #9.h; LR = #9.h; switch to Thumb",val,PC()+4);
  
  if( val&3 )
    {
     log.trace("Not aligned PC value");
    
     return cmdUndefined(log);
    }

  CPSR|=bitT;
  LR()=PC()+4;
  PC()=val;
 }

template <class Log>
void ARMState::setPC_T(Word val,Log &log)
 {
  if( val&1 )
    {
     BitClear(val,1);
    
     setPCT(val,log);
    }
  else
    {
     setPC(val,log);
    }
 }

template <class Log>
void ARMState::setPCLR_T(Word val,Log &log)
 {
  if( val&1 )
    {
     BitClear(val,1);
    
     setPCLRT(val,log);
    }
  else
    {
     setPCLR(val,log);
    }
 }

 // set CPSR

inline bool ARMState::TestMode(Word mode)
 {
  switch( mode )
    {
     case SR_M_usr :
     case SR_M_fiq :
     case SR_M_irq :
     case SR_M_svc :
     case SR_M_abt :
     case SR_M_und :
     case SR_M_sys : return true;
    }
 
  return false;
 }

template <class Log>
void ARMState::popCPSR(Log &log)
 {
  Word cur_mode=CPSR&SR_M;
  
  if( cur_mode==SR_M_usr || cur_mode==SR_M_sys )
    {
     log.trace("No SPSR in the current CPU mode");
    
     return cmdUndefined(log);
    }
  
  Word new_mode=SPSR&SR_M;
  
  if( !TestMode(new_mode) )
    {
     log.trace("Bad CPU mode");
    
     return cmdUndefined(log);
    }
  
  if( cur_mode==new_mode )
    {
     log.trace("CPSR = SPSR #9.h;",SPSR);
   
     CPSR=SPSR;
    }
  else
    {
     log.trace("CPSR = SPSR #9.h; switch mode",SPSR);
   
     saveBank(cur_mode);
    
     CPSR=SPSR;
     
     loadBank(new_mode);
    }
 }

template <class Log>
void ARMState::setCPSR(Word mask,Word val,Log &log)
 {
  Word set_mask=0;
  
  if( mask&Bit(3) ) set_mask|=0xFF000000;
  if( mask&Bit(2) ) set_mask|=  0xFF0000;
  if( mask&Bit(1) ) set_mask|=    0xFF00;
  if( mask&Bit(0) ) set_mask|=      0xFF;
  
  Word cur_mode=CPSR&SR_M;
  
  if( cur_mode==SR_M_usr )
    {
     set_mask&=(SR_all&SR_usr);
     
     CPSR=Combine(set_mask,val,CPSR);
     
     log.trace("CPSR = #9.h;",CPSR);
    }
  else
    {
     if( val&(SR_T|SR_J) )
       {
        log.trace("Cannot set T or J bits");
       
        return cmdUndefined(log);
       }
    
     set_mask&=(SR_all&~(SR_T|SR_J));
     
     Word new_CPSR = Combine(set_mask,val,CPSR) ;
     Word new_mode = new_CPSR&SR_M ;
     
     if( !TestMode(new_mode) )
       {
        log.trace("Bad CPU mode");
        
        return cmdUndefined(log);
       }
     
     if( cur_mode==new_mode )
       {
        CPSR=new_CPSR;
        
        log.trace("CPSR = #9.h;",CPSR);
       }
     else
       {
        saveBank(cur_mode);
       
        CPSR=new_CPSR;
        
        loadBank(new_mode);
        
        log.trace("CPSR = #9.h; switch mode",CPSR);
       }
    }
  
  nextPC();
 }

template <class Log>
void ARMState::setSPSR(Word mask,Word val,Log &log)
 {
  Word cur_mode=CPSR&SR_M;

  if( cur_mode==SR_M_usr || cur_mode==SR_M_sys )
    {
     log.trace("No SPSR register");
    
     return cmdUndefined(log);
    }
 
  Word set_mask=0;
  
  if( mask&Bit(3) ) set_mask|=0xFF000000;
  if( mask&Bit(2) ) set_mask|=  0xFF0000;
  if( mask&Bit(1) ) set_mask|=    0xFF00;
  if( mask&Bit(0) ) set_mask|=      0xFF;
  
  set_mask&=SR_all;
  
  SPSR = Combine(set_mask,val,SPSR) ;
  
  log.trace("SPSR = #9.h;",SPSR);
  
  nextPC();
 }

 // pass()

template <class Log>
bool ARMState::pass(Word cond,Log &log) const
 {
  switch( cond )
    {
     case Cond_EQ : log.trace("Cond EQ"); return  (CPSR&SR_Z) ; //  Z
     case Cond_NE : log.trace("Cond NE"); return !(CPSR&SR_Z) ; // !Z
     case Cond_CS : log.trace("Cond CS"); return  (CPSR&SR_C) ; //  C
     case Cond_CC : log.trace("Cond CC"); return !(CPSR&SR_C) ; // !C
   
     case Cond_MI : log.trace("Cond MI"); return  (CPSR&SR_N) ; //  N
     case Cond_PL : log.trace("Cond PL"); return !(CPSR&SR_N) ; // !N
     case Cond_VS : log.trace("Cond VS"); return  (CPSR&SR_V) ; //  V
     case Cond_VC : log.trace("Cond VC"); return !(CPSR&SR_V) ; // !V
   
     case Cond_HI : log.trace("Cond HI"); return (CPSR&(SR_C|SR_Z))==SR_C ; //  C && !Z
     case Cond_LS : log.trace("Cond LS"); return (CPSR&(SR_C|SR_Z))!=SR_C ; // !C ||  Z
     
     case Cond_GE : log.trace("Cond GE"); return  EQorNULL( (CPSR&(SR_N|SR_V)) , (SR_N|SR_V) ) ; //  N == V
     case Cond_LT : log.trace("Cond LT"); return !EQorNULL( (CPSR&(SR_N|SR_V)) , (SR_N|SR_V) ) ; //  N != V
   
     case Cond_GT : log.trace("Cond GT"); return  EQorNULL( (CPSR&(SR_Z|SR_N|SR_V)) , (SR_N|SR_V) ) ; // !Z && ( N == V )
     case Cond_LE : log.trace("Cond LE"); return !EQorNULL( (CPSR&(SR_Z|SR_N|SR_V)) , (SR_N|SR_V) ) ; //  Z || ( N != V )
      
     case Cond_AL : return true;
     case Cond_Undefined : return true;
    }
  
  return false;
 }

} // namespace ARMCore
 
#endif


