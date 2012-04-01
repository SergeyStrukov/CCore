/* PTPSupport.txt.cpp */ 
//----------------------------------------------------------------------------------------
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------


                             /*                          */ 
                             /* PTP Support Service 1.00 */ 
                             /*                          */ 

/* 1) Constants */ 

   const ServiceIdType ServiceId = 1 ;
   
   const FunctionIdType FunctionId_Len       = 1 ;
   const FunctionIdType FunctionId_Seed      = 2 ;
   const FunctionIdType FunctionId_Session   = 3 ;
   const FunctionIdType FunctionId_Echo      = 4 ;
   const FunctionIdType FunctionId_ErrorDesc = 5 ;
   const FunctionIdType FunctionId_Exist     = 6 ;
   
   const uint32 MaxDelay = 1000*60*60 ; // 1 hour
   
/* 2) Functions */  

   /* Len */ 

   struct LenInput
    {
     LenType to_server_info_len;
     LenType to_client_info_len;
    };
 
   struct LenOutput
    {
     LenType to_server_info_len;
     LenType to_client_info_len;
    }; 

   /* Seed */ 
   
   struct SeedInput
    {
    };
    
   struct SeedOutput
    {
     uint64 seed1;
     uint64 seed2;
    };

   /* Session */ 
   
   struct SessionInput
    {
    };

   struct SessionOutput
    {
    };
    
   /* Echo */  
   
   struct EchoInput
    {
     uint32 delay_msec;
     uint8 len;
     uint8 data[len];
    };
    
   struct EchoOutput
    {
     uint8 len;
     uint8 data[len];
    };
    
   /* ErrorDesc */  
   
   struct ErrorDescInput
    {
     ServiceIdType service_id;
     FunctionIdType function_id;
     ErrorIdType error;
    };
    
   struct ErrorDescOutput
    {
     uint8 len;
     uint8 str[len];
    }; 
   
   /* Exist */ 
   
   struct ExistInput
    {
     ServiceIdType service_id;
     FunctionIdType function_id;
    };
    
   struct ExistOutput
    {
     ServiceIdType service_id;
     FunctionIdType function_id;
     ErrorIdType error;
    };
    
     