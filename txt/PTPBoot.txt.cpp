/* PTPBoot.txt.cpp */ 
//----------------------------------------------------------------------------------------
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

                             /*               */ 
                             /* PTP Boot 1.00 */ 
                             /*               */ 

/* 1) Data types */ 

   typedef uint64 AddressType;

   typedef uint32 IndexType;

/* 2) Constants */ 

   const unsigned DeltaWriteLen   =   24 ;
   const unsigned MaxWriteDataLen = 1416 ; // MaxInfoLen-DeltaWriteLen

   const ServiceIdType ServiceId = 4 ;
   
   const FunctionIdType FunctionId_Alloc = 1 ;
   const FunctionIdType FunctionId_Write = 2 ;
   const FunctionIdType FunctionId_Boot  = 3 ;

/* 3) Functions */  

   /* Alloc */ 
   
   struct AllocInput
    {
     AddressType address;
     AddressType len;
    };
    
   struct AllocOutput
    {
     IndexType index;
    }; 
   
   /* Write */ 
   
   struct WriteInput
    {
     IndexType index;
     AddressType off;
     LenType len : len<=MaxWriteDataLen ;
     uint8 data[len];
    };
    
   struct WriteOutput
    {
    }; 
   
   /* Boot */ 
   
   struct BootInput
    {
     AddressType entry_point;
     FlagType flags;
    };
    
   struct BootOutput
    {
    }; 
