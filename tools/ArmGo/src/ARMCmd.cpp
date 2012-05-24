/* ARMCmd.cpp */ 
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

#include <inc/ARMCmd.h>

namespace ARMCore {

/* namespace ARMv5TE_nonT */

namespace ARMv5TE_nonT {

/* consts */

const char * GetTextDesc(CmdType type)
 {
  static const char *const Table[]=
   {
    "Undefined",
     
    // key 0
    
    "AND",
    "EOR",
    "SUB",
    "RSB",
     
    "ADD",
    "ADC",
    "SBC",
    "RSC",
     
    "TST",
    "TEQ",
    "CMP",
    "CMN",
     
    "ORR",
    "MOV",
    "BIC",
    "MVN",
     
    "MSR",
    "MRS",
     
    "BLX",
    "BX",
    "CLZ",
    "BKPT",
     
    "QADD",
    "QSUB",
    "QDADD",
    "QDSUB",
     
    "SMLAxy",
    "SMULWy",
    "SMLAWy",
    "SMLALxy",
    "SMULxy",
     
    "LDRH",
    "STRH",
    "LDRSB",
    "LDRD",
    "LDRSH",
    "STRD",
     
    "MUL",
    "MLA",
    "UMULL",
    "UMLAL",
    "SMULL",
    "SMLAL",
     
    "SWP",
    "SWPB",
     
    // key 1
     
    "AND imm",
    "EOR imm",
    "SUB imm",
    "RSB imm",
     
    "ADD imm",
    "ADC imm",
    "SBC imm",
    "RSC imm",
     
    "TST imm",
    "TEQ imm",
    "CMP imm",
    "CMN imm",
     
    "ORR imm",
    "MOV imm",
    "BIC imm",
    "MVN imm",
     
    "MSR imm",

    // key 2
     
    "STR imm",
    "LDR imm",
    "STRB imm",
    "LDRB imm",
     
    "PLD",
     
     // key 3
     
    "STR",
    "LDR",
    "STRB",
    "LDRB",
     
    "PLD",
     
    // key 4
     
    "LDM",
    "STM",
     
    // key 5
     
    "B",
     
    // key 6
     
    "LDC",
    "STC",
     
    "MRRC",
    "MCRR",
     
    // key 7
     
    "SWI",
     
    "MRC",
    "MCR",
    "CDP",
     
    // special
    
    "IRQ",
    "FIQ",
    "SKIP",
     
    ""
   };
  
  return Table[type];
 }

/* Decode() */

static bool ValidAMode3(Word cmd)
 {
  if( (cmd&Bit(22))==0 && (cmd&Field(4,8))!=0 ) return false;
   
  return (cmd&Bits(24,21))!=Bit(21); 
 }

CmdType Decode(Word cmd)
 {
  Word cond=cmd>>28;
  
  if( cond==Cond_Undefined )
    {
     Word key=(cmd>>25)&7;
     
     switch( key )
       {
        case 2 :
         {
          if( (cmd&(Bits(24,22,21,20)|Field(4,12)))==(Bits(24,22,20)|Field(4,12)) ) return Cmd2PLD; 
         }
        break;
        
        case 3 :
         {
          if( (cmd&(Bits(24,22,21,20)|Field(4,12)))==(Bits(24,22,20)|Field(4,12)) ) return Cmd3PLD;
         }
        break;
        
        case 6 :
         {
          if( cmd&Bit(20) )
            {
             if( (cmd&Bits(24,23,22))!=Bit(23) )
               {
                return Cmd6LDC;
               }
            }
          else
            {
             if( (cmd&Bits(24,23,22))!=Bit(23) )
               {
                return Cmd6STC;
               }
            }
         }
        break;
      
        case 7 : 
         {
          if( (cmd&Bit(24))==0 )
            {
             if( cmd&Bit(4) )
               {
                if( cmd&Bit(20) )
                  {
                   return Cmd7MRC;
                  }
                else
                  {
                   return Cmd7MCR;
                  }
               }
             else
               {
                return Cmd7CDP;
               }
            }
         }
        break;
       }
     
     return CmdUndefined;
    }
  
  Word key=(cmd>>25)&7;
  
  switch( key )
    {
     case 0 :
      {
       if( (cmd&Bits(7,4))==Bits(7,4) )
         {
          switch( (cmd>>5)&3 )
            {
             case 0 :
              {
               switch( (cmd>>21)&15 )
                 {
                  case 0 : if( (cmd&Field(4,12))==0 ) return Cmd0MUL; break;
                  
                  case 1 : return Cmd0MLA; break;
                  case 4 : return Cmd0UMULL; break;
                  case 5 : return Cmd0UMLAL; break;
                  case 6 : return Cmd0SMULL; break;
                  case 7 : return Cmd0SMLAL; break;
                  case 8 : return Cmd0SWP; break;
                  case 9 : return Cmd0SWPB; break;
                 }
              }
             break; 
              
             case 1 :
              {
               if( cmd&Bit(20) )
                 {
                  if( ValidAMode3(cmd) ) return Cmd0LDRH;
                 }
               else
                 {
                  if( ValidAMode3(cmd) ) return Cmd0STRH;
                 }
              }
             break;
             
             case 2 :
              {
               if( cmd&Bit(20) )
                 {
                  if( ValidAMode3(cmd) ) return Cmd0LDRSB;
                 }
               else
                 {
                  if( ValidAMode3(cmd) ) return Cmd0LDRD;
                 }
              }
             break;
             
             case 3 :
              {
               if( cmd&Bit(20) )
                 {
                  if( ValidAMode3(cmd) ) return Cmd0LDRSH;
                 }
               else
                 {
                  if( ValidAMode3(cmd) ) return Cmd0STRD;
                 }
              }
             break; 
            }
         }
       else
         {
          Word opcode=(cmd>>21)&15;
 
          switch( opcode )
            {
             case Op_AND :
             case Op_EOR :
             case Op_SUB :
             case Op_RSB :
              
             case Op_ADD :
             case Op_ADC :
             case Op_SBC :
             case Op_RSC :
              
             case Op_ORR :
             case Op_BIC :
              {
               return CmdType( Cmd0AND+opcode );
              }
             break; 
              
             case Op_TST :
             case Op_TEQ :
             case Op_CMP :
             case Op_CMN :
              {
               if( (cmd&Bit(20))==0 )
                 {
                  if( cmd&Bit(7) )
                    {
                     switch( (cmd>>21)&3 )
                       {
                        case 0 : 
                         {
                          if( (cmd&Bit(4))==0 ) return Cmd0SMLAxy;
                         }
                        break;
                         
                        case 1 : 
                         {
                          if( cmd&Bit(5) )
                            {
                             if( (cmd&(Bit(4)|Field(4,12)))==0 ) return Cmd0SMULWy;
                            }
                          else
                            {
                             if( (cmd&Bit(4))==0 ) return Cmd0SMLAWy;
                            }
                         }
                         
                        case 2 : 
                         {
                          if( (cmd&Bit(4))==0 ) return Cmd0SMLALxy;
                         }
                        break; 
                         
                        case 3 : 
                         {
                          if( (cmd&(Bit(4)|Field(4,12)))==0 ) return Cmd0SMULxy;
                         }
                        break; 
                       }
                    }
                  else
                    {
                     switch( (cmd>>4)&7 )
                       {
                        case 0 :
                         {
                          if( cmd&Bit(21) )
                            {
                             if( (cmd&Field(8,8))==Field(4,12) ) return Cmd0MSR;
                            }
                          else
                            {
                             if( (cmd&(Field(4,16)|Field(12)))==Field(4,16) ) return Cmd0MRS;
                            }
                         }
                        break;
                         
                        case 1 :
                         {
                          if( cmd&Bit(22) )
                            {
                             if( (cmd&(Bit(21)|Field(4,16)|Field(4,8)))==(Bit(21)|Field(4,16)|Field(4,8)) ) return Cmd0CLZ;
                            }
                          else
                            {
                             if( (cmd&(Bit(21)|Field(12,8)))==(Bit(21)|Field(12,8)) ) return Cmd0BX;
                            }
                         }
                        break;
                        
                        case 3 :
                         {
                          if( (cmd&(Bits(22,21)|Field(12,8)))==(Bit(21)|Field(12,8)) ) return Cmd0BLX;
                         }
                        break;
                        
                        case 5 :
                         {
                          switch( (cmd>>21)&3 )
                            {
                             case 0 : if( (cmd&Field(4,8))==0 ) return Cmd0QADD; break;
                             case 1 : if( (cmd&Field(4,8))==0 ) return Cmd0QSUB; break;
                             case 2 : if( (cmd&Field(4,8))==0 ) return Cmd0QDADD; break;
                             case 3 : if( (cmd&Field(4,8))==0 ) return Cmd0QDSUB; break;
                            }
                         }
                        break;
                        
                        case 7 :
                         {
                          if( (cmd&(Bits(22,21)))==Bit(21) && cond==Cond_AL ) return Cmd0BKPT;
                         }
                        break; 
                       }
                    }
                 }
               else
                 {
                  if( (cmd&Field(4,12))==0 ) return CmdType( Cmd0AND+opcode );
                 }
              }
             break; 
              
             case Op_MOV :
             case Op_MVN :
              {
               if( (cmd&Field(4,16))==0 ) return CmdType( Cmd0AND+opcode );
              }
             break; 
            }
         }
      }
     break; 
      
     case 1 :
      {
       Word opcode=(cmd>>21)&15;
       
       switch( opcode )
         {
          case Op_AND :
          case Op_EOR :
          case Op_SUB :
          case Op_RSB :
           
          case Op_ADD :
          case Op_ADC :
          case Op_SBC :
          case Op_RSC :
           
          case Op_ORR :
          case Op_BIC :
           {
            return CmdType( Cmd1AND+opcode );
           }
          break; 
           
          case Op_TST :
          case Op_TEQ :
          case Op_CMP :
          case Op_CMN :
           {
            if( (cmd&Bit(20))==0 )
              {
               if( (cmd&Bits(21,15,14,13,12))==Bits(21,15,14,13,12) ) return Cmd1MSR;
              }
            else
              {
               if( (cmd&Field(4,12))==0 ) return CmdType( Cmd1AND+opcode );
              }
           }
          break; 
           
          case Op_MOV :
          case Op_MVN :
           {
            if( (cmd&Field(4,16))==0 ) return CmdType( Cmd1AND+opcode );
           }
          break; 
         }
      }
     break; 
      
     case 2 :
      {
       switch( cmd&Bits(22,20) )
         {
          case           0 : return Cmd2STR; break;
          case     Bit(20) : return Cmd2LDR; break;
          case     Bit(22) : return Cmd2STRB; break;
          case Bits(22,20) : return Cmd2LDRB; break;
         }
      }
     break;
     
     case 3 :
      {
       if( cmd&Bit(4) )
         {
          // no instructions here
         }
       else
         {
          switch( cmd&Bits(22,20) )
            {
             case           0 : return Cmd3STR; break;
             case     Bit(20) : return Cmd3LDR; break;
             case     Bit(22) : return Cmd3STRB; break;
             case Bits(22,20) : return Cmd3LDRB; break;
            }
         }
      }
     break;
     
     case 4 :
      {
       if( cmd&Bit(20) )
         {
          return Cmd4LDM;
         }
       else
         {
          return Cmd4STM;
         }
      }
     break;
     
     case 5 :
      {
       return Cmd5B;
      }
     break;
     
     case 6 :
      {
       if( cmd&Bit(20) )
         {
          if( (cmd&Bits(24,23,22))==Bit(23) )
            {
             return Cmd6MRRC;
            }
          else
            {
             return Cmd6LDC;
            }
         }
       else
         {
         if( (cmd&Bits(24,23,22))==Bit(23) )
           {
            return Cmd6MCRR;
           }
         else
           {
            return Cmd6STC;
           }
         }
      }
     break;
     
     case 7 : 
      {
       if( cmd&Bit(24) )
         {
          return Cmd7SWI;
         }
       else
         {
          if( cmd&Bit(4) )
            {
             if( cmd&Bit(20) )
               {
                return Cmd7MRC;
               }
             else
               {
                return Cmd7MCR;
               }
            }
          else
            {
             return Cmd7CDP;
            }
         }
      }
     break;
    }
  
  return CmdUndefined;
 }

/* struct CoProc */

void CoProc::reset(bool hi_vector)
 {
  regID=0x69054200;
  regCacheType=0x0B1AA1AA;
  
  regControl=Field(4,3)|Bit(7)|Bit(1);
  regAuxControl=0;
  
  regTTBase=0;
  regDomainAC=0;
  regPID=0;
  
  if( hi_vector ) regControl|=Bit(13);
 }

ExtWord CoProc::get(Word cp_num,Word opcode1,Word opcode2,Word CRn,Word CRm)
 {
  if( cp_num!=15 || CRm!=0 || opcode1!=0 ) return ExtWord(0,true);
  
  if( opcode2==0 )
    {
     switch( CRn )
       {
        case  0 : return ExtWord(regID,false);
        case  1 : return ExtWord(regControl,false);
        case  2 : return ExtWord(regTTBase,false); 
        case  3 : return ExtWord(regDomainAC,false);
        case 13 : return ExtWord(regPID,false);
       }
    }
  else if( opcode2==1 )
    {
     switch( CRn )
       {
        case  0 : return ExtWord(regCacheType,false); 
        case  1 : return ExtWord(regAuxControl,false); 
       }
    }
  else
    {
     return ExtWord(0,true);
    }
  
  return ExtWord(0,true);
 }
  
bool /* bitC */ CoProc::put(Word cp_num,Word opcode1,Word opcode2,Word CRn,Word CRm,Word val)
 {
  if( cp_num!=15 || CRm!=0 || opcode1!=0 ) return true;
   
  if( opcode2==0 )
    {
     switch( CRn )
       {
        case  0 : return false;
        case  1 : regControl=val; return false;
        case  2 : regTTBase=val; return false;
        case  3 : regDomainAC=val; return false; 
        case 13 : regPID=val; return false;
       }
    }
  else if( opcode2==1 )
    {
     switch( CRn )
       {
        case  0 : return false;
        case  1 : regAuxControl=val; return false;
       }
    }
  else
    {
     return true;
    }
  
  return true;
 }

bool /* bitC */ CoProc::get2(Word cp_num,Word opcode,Word CRm,Word &a1,Word &a2)
 {
  Used(cp_num);
  Used(opcode);
  Used(CRm);
  Used(a1);
  Used(a2);
  
  return true; 
 }

bool /* bitC */ CoProc::put2(Word cp_num,Word opcode,Word CRm,Word a1,Word a2)
 {
  Used(cp_num);
  Used(opcode);
  Used(CRm);
  Used(a1);
  Used(a2);
  
  return true;
 }

bool /* bitC */ CoProc::exec(Word cp_num,Word opcode1,Word opcode2,Word CRd,Word CRn,Word CRm)
 {
  Used(cp_num);
  Used(opcode1);
  Used(opcode2);
  Used(CRd);
  Used(CRn);
  Used(CRm);
  
  return true;
 }

} // namespace ARMv5TE_nonT

} // namespace ARMCore


