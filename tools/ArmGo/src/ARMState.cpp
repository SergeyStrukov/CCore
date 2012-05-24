/* ARMState.cpp */
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

#include <inc/ARMState.h>

namespace ARMCore {

/* struct ARMState */

 // banking

void ARMState::saveBank_usr()
 {
  R8_usr=R[8];
  R9_usr=R[9];
  R10_usr=R[10];
  R11_usr=R[11];
  R12_usr=R[12];

  R13_usr=R[13];
  R14_usr=R[14];
 }

void ARMState::saveBank_sys()
 {
  saveBank_usr();
 }

void ARMState::saveBank_svc()
 {
  R8_usr=R[8];
  R9_usr=R[9];
  R10_usr=R[10];
  R11_usr=R[11];
  R12_usr=R[12];

  R13_svc=R[13];
  R14_svc=R[14];
  SPSR_svc=SPSR;
 }

void ARMState::saveBank_abt()
 {
  R8_usr=R[8];
  R9_usr=R[9];
  R10_usr=R[10];
  R11_usr=R[11];
  R12_usr=R[12];

  R13_abt=R[13];
  R14_abt=R[14];
  SPSR_abt=SPSR;
 }

void ARMState::saveBank_und()
 {
  R8_usr=R[8];
  R9_usr=R[9];
  R10_usr=R[10];
  R11_usr=R[11];
  R12_usr=R[12];

  R13_und=R[13];
  R14_und=R[14];
  SPSR_und=SPSR;
 }

void ARMState::saveBank_irq()
 {
  R8_usr=R[8];
  R9_usr=R[9];
  R10_usr=R[10];
  R11_usr=R[11];
  R12_usr=R[12];

  R13_irq=R[13];
  R14_irq=R[14];
  SPSR_irq=SPSR;
 }

void ARMState::saveBank_fiq()
 {
  R8_fiq=R[8];
  R9_fiq=R[9];
  R10_fiq=R[10];
  R11_fiq=R[11];
  R12_fiq=R[12];

  R13_fiq=R[13];
  R14_fiq=R[14];
  SPSR_fiq=SPSR;
 }

void ARMState::loadBank_usr()
 {
  R[8]=R8_usr;
  R[9]=R9_usr;
  R[10]=R10_usr;
  R[11]=R11_usr;
  R[12]=R12_usr;

  R[13]=R13_usr;
  R[14]=R14_usr;
 }

void ARMState::loadBank_sys()
 {
  loadBank_usr();
 }

void ARMState::loadBank_svc()
 {
  R[8]=R8_usr;
  R[9]=R9_usr;
  R[10]=R10_usr;
  R[11]=R11_usr;
  R[12]=R12_usr;

  R[13]=R13_svc;
  R[14]=R14_svc;
  SPSR=SPSR_svc;
 }

void ARMState::loadBank_abt()
 {
  R[8]=R8_usr;
  R[9]=R9_usr;
  R[10]=R10_usr;
  R[11]=R11_usr;
  R[12]=R12_usr;

  R[13]=R13_abt;
  R[14]=R14_abt;
  SPSR=SPSR_abt;
 }

void ARMState::loadBank_und()
 {
  R[8]=R8_usr;
  R[9]=R9_usr;
  R[10]=R10_usr;
  R[11]=R11_usr;
  R[12]=R12_usr;

  R[13]=R13_und;
  R[14]=R14_und;
  SPSR=SPSR_und;
 }

void ARMState::loadBank_irq()
 {
  R[8]=R8_usr;
  R[9]=R9_usr;
  R[10]=R10_usr;
  R[11]=R11_usr;
  R[12]=R12_usr;

  R[13]=R13_irq;
  R[14]=R14_irq;
  SPSR=SPSR_irq;
 }

void ARMState::loadBank_fiq()
 {
  R[8]=R8_fiq;
  R[9]=R9_fiq;
  R[10]=R10_fiq;
  R[11]=R11_fiq;
  R[12]=R12_fiq;

  R[13]=R13_fiq;
  R[14]=R14_fiq;
  SPSR=SPSR_fiq;
 }

void ARMState::saveBank(Word mode)
 {
  switch( mode )
    {
     case SR_M_usr : saveBank_usr(); break;
     case SR_M_fiq : saveBank_fiq(); break;
     case SR_M_irq : saveBank_irq(); break;
     case SR_M_svc : saveBank_svc(); break;
     case SR_M_abt : saveBank_abt(); break;
     case SR_M_und : saveBank_und(); break;
     case SR_M_sys : saveBank_sys(); break;
    }
 }

void ARMState::loadBank(Word mode)
 {
  switch( mode )
    {
     case SR_M_usr : loadBank_usr(); break;
     case SR_M_fiq : loadBank_fiq(); break;
     case SR_M_irq : loadBank_irq(); break;
     case SR_M_svc : loadBank_svc(); break;
     case SR_M_abt : loadBank_abt(); break;
     case SR_M_und : loadBank_und(); break;
     case SR_M_sys : loadBank_sys(); break;
    }
 }

} // namespace ARMCore

