/* PTPCon.txt.cpp */ 
//----------------------------------------------------------------------------------------
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

                             /*                  */ 
                             /* PTP Console 1.00 */ 
                             /*                  */ 

/* 1) Data types */ 

   struct Name
    {
     LenType len : len<=MaxNameLen ;
     uint8 name[len];
    };
    
   struct ConId
    {
     uint32 slot;
     uint64 number;
     uint64 clock;
    }; 
    
/* 2) Constants */ 

   const unsigned MaxNameLen      =  128 ;
   const unsigned DeltaReadLen    =   20 ;
   const unsigned MaxReadDataLen  = 1420 ; // MaxInfoLen-DeltaReadLen
   const unsigned DeltaWriteLen   =   36 ;
   const unsigned MaxWriteDataLen = 1404 ; // MaxInfoLen-DeltaWriteLen

   const ServiceIdType ServiceId = 3 ;
   
   const FunctionIdType FunctionId_Open  = 1 ;
   const FunctionIdType FunctionId_Read  = 2 ;
   const FunctionIdType FunctionId_Write = 3 ;
   const FunctionIdType FunctionId_Close = 4 ;

/* 3) Functions */  

   /* Open */ 
   
   struct OpenInput
    {
     uint32 write_timeout_msec;
     uint32 read_timeout_msec;
     uint32 trigger_mask[8];
     
     void setbit(uint8 ch) { trigger_mask[ch>>5]|=(uint32(1)<<(ch&31)); }
     
     Name name;
    };
    
   struct OpenOutput
    {
     ConId con_id;
    }; 
   
   /* Read */ 
   
   struct ReadInput
    {
     ConId con_id;
     uint32 number;
     LenType len;
    };
   
   struct ReadOutput
    {
     uint32 number;
     LenType len : len<=MaxReadDataLen ;
     uint8 data[len];
    };
    
   /* Write */ 
   
   struct WriteInput
    {
     ConId con_id;
     uint32 number;
     LenType len : len<=MaxWriteDataLen ;
     uint8 data[len];
    };
    
   struct WriteOutput
    {
    }; 
    
   /* Close */ 
   
   struct CloseInput
    {
     ConId con_id;
    };
    
   struct CloseOutput
    {
    }; 

