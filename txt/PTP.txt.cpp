/* PTP.txt.cpp */ 
//----------------------------------------------------------------------------------------
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

                             /*                                  */ 
                             /* Packet Transaction Protocol 1.00 */ 
                             /*                                  */ 
                             
/* 1) Constants */ 

   const unsigned MaxPacketLen = 1472 ; // max UDP data len if( Eth.MTU == 1500 )
   const unsigned DeltaInfoLen =   32 ;
   const unsigned MaxInfoLen   = 1440 ; // MaxPacketLen-DeltaInfoLen
   
   const unsigned MinTimeout   =   300 ; // msec, 0.3 sec   
   const unsigned MaxTimeout   = 10000 ; // msec, 10  sec  
   const unsigned DeltaTimeout =   100 ; // msec, 0.1 sec 
   
   enum PacketDirection
    {
     ClientToServer,
     ServerToClient
    };
 
/* 2) Data types */ 

   /* basic types */ 

   typedef ??? uint8;
   
   typedef ??? uint16;
   
   typedef ??? uint32;
   
   typedef ??? uint64;
   
   #define ASSERT(S) ???
 
   /* derived types */ 

   typedef uint32 PacketType;

   typedef uint32 SlotId;
   
   typedef uint32 RecallNumber;
 
   struct TransId
    {
     uint64 number;
     uint64 clock;
     
     friend bool operator == (TransId a,TransId b)
      {
       return a.number==b.number && a.clock==b.clock ;
      } 
     
     friend bool operator != (TransId a,TransId b) { return !(a==b); }
    };
 
   struct Info
    {
     uint32 len : len<=MaxInfoLen ; 
     uint8 data[len];
    };
    
/* 3) Packet types */ 

   /* data packets */ 

   struct Packet_CALL
    {
     static const PacketType Type = 1 ;
     static const PacketDirection Direction = ClientToServer ;
    
     PacketType type;
     TransId tid;
     SlotId client_slot;
     
     Info client_info;
    };
 
   struct Packet_RET
    {
     static const PacketType Type = 2 ;
     static const PacketDirection Direction = ServerToClient ;
    
     PacketType type;
     TransId tid;
     SlotId client_slot;
     SlotId server_slot;
     
     Info server_info;
    };
 
   struct Packet_RECALL
    {
     static const PacketType Type = 3 ;
     static const PacketDirection Direction = ClientToServer ;
    
     PacketType type;
     TransId tid;
     SlotId client_slot;
     
     RecallNumber number;
     Info client_info;
    };
    
   /* control packets */  
 
   struct Packet_ACK
    {
     static const PacketType Type = 4 ;
     static const PacketDirection Direction = ClientToServer ;
    
     PacketType type;
     TransId tid;
     SlotId client_slot;
     SlotId server_slot;
    };
    
   struct Packet_NOINFO
    {
     static const PacketType Type = 5 ;
     static const PacketDirection Direction = ServerToClient ;
    
     PacketType type;
     TransId tid;
     SlotId client_slot;
     SlotId server_slot;
    }; 
    
   struct Packet_RERET
    {
     static const PacketType Type = 6 ;
     static const PacketDirection Direction = ServerToClient ;
    
     PacketType type;
     TransId tid;
     SlotId client_slot;
     SlotId server_slot;
    }; 
    
   struct Packet_SENDRET
    {
     static const PacketType Type = 7 ;
     static const PacketDirection Direction = ClientToServer ;
    
     PacketType type;
     TransId tid;
     SlotId client_slot;
     SlotId server_slot;
    }; 
    
   struct Packet_CANCEL
    {
     static const PacketType Type = 8 ;
     static const PacketDirection Direction = ServerToClient ;
    
     PacketType type;
     TransId tid;
     SlotId client_slot;
     SlotId server_slot;
    }; 
    
   concept CondTrue<bool Cond>;
    
   concept ToClientPacket<class Packet> // Packet_RET,Packet_NOINFO,Packet_RERET,Packet_CANCEL
    {
     requires CondTrue< Packet::PacketDirection == ServerToClient >;
    };
    
   concept ToServerPacket<class Packet> // Packet_CALL,Packet_RECALL,Packet_ACK,Packet_SENDRET
    {
     requires CondTrue< Packet::PacketDirection == ClientToServer >;
    };
    
/* 4) Transaction processing */  

  /* All Side */ 

    /* basic routines */ 
    
    void SetTimer(SlotId slot,unsigned timeout); // msec 
    
    void CancelTimer(SlotId slot);

    /* input-output routines */ 

    template <class Packet>
    void SendPacket(Packet packet); 
    
  /* Client Side */ 
    
    /* basic routines */ 
    
    TransId GenTransId();
    
    RecallNumber SatInc(RecallNumber &number)
     {
      RecallNumber ret=number;
      
      if( RecallNumber next=ret+1 ) number=next;
      
      return ret;
     }
    
    void TransComplete(SlotId slot);
    
    void TransCancel(SlotId slot);
    
    /* inbound processing */  
     
    ClientSlot * Find(SlotId client_slot,TransId tid); 
     
    template <ToClientPacket Packet>
    void Process(Packet packet) 
     {
      if( ClientSlot *slot=Find(packet.client_slot,packet.tid) )
        {
         slot->process(packet);
        }
      else
        {
         Packet_ACK ack;
           
         ack.type=ack.Type;
         ack.tid=packet.tid;
         ack.client_slot=packet.client_slot;
         ack.server_slot=packet.server_slot;
           
         SendPacket(ack);
        }  
     }
     
    /* slot processing */ 
    
    struct ClientSlot
     {
      bool active;
      TransId tid;
      SlotId client_slot;
      SlotId server_slot;
      Info client_info;
      Info server_info;
      
      bool no_info;
      RecallNumber number;
      unsigned timeout; // msec 
      
      void init(SlotId client_slot_)
       {
        client_slot=client_slot_;
        active=false;
       }
       
      void stop()
       {
        ASSERT( active );
        
        CancelTimer(client_slot);
        active=false;
       } 
      
      void start(Info client_info_)
       {
        ASSERT( !active );
       
        active=true;
        tid=GenTransId();
        client_info=client_info_;
        
        no_info=false;
        number=1;
        timeout=MinTimeout;
        
        Packet_CALL call;
        
        call.type=call.Type;
        call.tid=tid;
        call.client_slot=client_slot;
        call.client_info=client_info;
        
        SendPacket(call);
        
        SetTimer(client_slot,timeout);
        
        if( timeout<MaxTimeout ) timeout+=DeltaTimeout;
       }
      
      void processTimeout()
       {
        ASSERT( active );
        
        if( no_info )
          {
           Packet_SENDRET sendret;
           
           sendret.type=sendret.Type;
           sendret.tid=tid;
           sendret.client_slot=client_slot;
           sendret.server_slot=server_slot;
           
           SendPacket(sendret);
          }
        else
          {
           Packet_RECALL recall;
        
           recall.type=recall.Type;
           recall.tid=tid;
           recall.client_slot=client_slot;
           recall.number=SatInc(number);
           recall.client_info=client_info;
        
           SendPacket(recall);
          }
        
        SetTimer(client_slot,timeout);
        
        if( timeout<MaxTimeout ) timeout+=DeltaTimeout;
       }
       
      void process(Packet_RET ret)
       {
        ASSERT( ret.client_slot==client_slot && active && ret.tid==tid );
       
        server_slot=ret.server_slot;
        server_info=ret.server_info;
           
        Packet_ACK ack;
           
        ack.type=ack.Type;
        ack.tid=tid;
        ack.client_slot=client_slot;
        ack.server_slot=server_slot;
           
        SendPacket(ack);
           
        TransComplete(client_slot);
           
        stop();
       } 
       
      void process(Packet_CANCEL cancel)
       {
        ASSERT( cancel.client_slot==client_slot && active && cancel.tid==tid );
           
        server_slot=cancel.server_slot;
        
        Packet_ACK ack;
           
        ack.type=ack.Type;
        ack.tid=tid;
        ack.client_slot=client_slot;
        ack.server_slot=server_slot;
           
        SendPacket(ack);
        
        TransCancel(client_slot);
           
        stop();
       } 
       
      void process(Packet_NOINFO noinfo)
       {
        ASSERT( noinfo.client_slot==client_slot && active && noinfo.tid==tid );
       
        server_slot=noinfo.server_slot;
           
        no_info=true;
       } 
       
      void process(Packet_RERET reret)
       {
        ASSERT( reret.client_slot==client_slot && active && reret.tid==tid );
       
        server_slot=reret.server_slot;
           
        Packet_SENDRET sendret;
           
        sendret.type=sendret.Type;
        sendret.tid=tid;
        sendret.client_slot=client_slot;
        sendret.server_slot=server_slot;
           
        SendPacket(sendret);
       } 
     };
     
  /* Server Side */ 
    
    /* basic routines */ 
    
    void StartProcessing(SlotId server_slot);
    
    void CancelProcessing(SlotId server_slot);
    
    /* inbound processing */  
    
    ServerSlot * Find(SlotId server_slot,TransId tid); 
    
    ServerSlot * Find(TransId tid);
    
    ServerSlot * FindFree();
     
    void Process(Packet_CALL call) 
     {
      if( Find(call.tid) ) return;
     
      if( ServerSlot *slot=FindFree() )
        {
         slot->process(call);
        }
     }
     
    void Process(Packet_RECALL recall) 
     {
      if( ServerSlot *slot=Find(recall.tid) )
        {
         slot->process(recall);
        }
      else if( ServerSlot *slot=FindFree() ) 
        {
         slot->process_first(recall);
        }
     }
     
    void Process(Packet_ACK ack) 
     {
      if( ServerSlot *slot=Find(ack.server_slot,ack.tid) )
        {
         slot->process(ack);
        }
     }
     
    void Process(Packet_SENDRET sendret) 
     {
      if( ServerSlot *slot=Find(sendret.server_slot,sendret.tid) )
        {
         slot->process(sendret);
        }
      else
        {
         Packet_CANCEL cancel;
              
         cancel.type=cancel.Type;
         cancel.tid=sendret.tid;
         cancel.client_slot=sendret.client_slot;
         cancel.server_slot=sendret.server_slot;
              
         SendPacket(cancel);
        }  
     }
    
    /* slot processing */ 
    
    struct ServerSlot
     {
      bool active;
      TransId tid;
      SlotId client_slot;
      SlotId server_slot;
      Info client_info;
      Info server_info;
      
      RecallNumber number;
      bool ready;
      bool canceled;
      unsigned timeout;
      
      void init(SlotId server_slot_)
       {
        server_slot=server_slot_;
        active=false;
       }
      
      void process(Packet_CALL call)
       {
        ASSERT( !active );
        
        tid=call.tid;
        client_slot=call.client_slot;
        client_info=call.client_info;
        
        number=0;
        ready=false;
        canceled=false;
        timeout=0;
        active=true;
        
        StartProcessing(server_slot);
       }
      
      void process(Packet_RECALL recall)
       {
        ASSERT( active && recall.tid==tid );
        
        if( client_slot!=recall.client_slot || client_info.len!=recall.client_info.len ) return;
           
        number=recall.number;

        if( ready )
          {
           Packet_RET ret;
              
           ret.type=ret.Type;
           ret.tid=tid;
           ret.client_slot=client_slot;
           ret.server_slot=server_slot;
           ret.server_info=server_info;
              
           SendPacket(ret);
          }
        else if( canceled )  
          {
           Packet_CANCEL cancel;
              
           cancel.type=cancel.Type;
           cancel.tid=tid;
           cancel.client_slot=client_slot;
           cancel.server_slot=server_slot;
              
           SendPacket(cancel);
          }
        else
          {
           Packet_NOINFO noinfo;
              
           noinfo.type=noinfo.Type;
           noinfo.tid=tid;
           noinfo.client_slot=client_slot;
           noinfo.server_slot=server_slot;
              
           SendPacket(noinfo);
          }
       }
       
      void process_first(Packet_RECALL recall)
       {
        ASSERT( !active );
        
        tid=recall.tid;
        client_slot=recall.client_slot;
        client_info=recall.client_info;
           
        number=recall.number;
        ready=false;
        canceled=false;
        timeout=0;
        active=true;
           
        StartProcessing(server_slot);
       }
       
      void complete(Info server_info_) 
       {
        ASSERT( active && !ready && !canceled );
        
        server_info=server_info_;
        
        ready=true;
        
        Packet_RET ret;
              
        ret.type=ret.Type;
        ret.tid=tid;
        ret.client_slot=client_slot;
        ret.server_slot=server_slot;
        ret.server_info=server_info;
              
        SendPacket(ret);
        
        timeout=MinTimeout;
        
        SetTimer(server_slot,timeout);
        
        if( timeout<MaxTimeout ) timeout+=DeltaTimeout;
       }
       
      void cancel()
       {
        ASSERT( active && !ready && !canceled );
        
        canceled=true;
        
        Packet_CANCEL cancel;
              
        cancel.type=cancel.Type;
        cancel.tid=tid;
        cancel.client_slot=client_slot;
        cancel.server_slot=server_slot;
              
        SendPacket(cancel);
        
        timeout=MinTimeout;
        
        SetTimer(server_slot,timeout);
        
        if( timeout<MaxTimeout ) timeout+=DeltaTimeout;
       } 
      
      void process(Packet_ACK ack)
       {
        ASSERT( ack.server_slot==server_slot && active && ack.tid==tid );
        
        if( !ready ) CancelProcessing(server_slot);
           
        if( timeout ) CancelTimer(server_slot);
          
        active=false;
       }
      
      void process(Packet_SENDRET sendret)
       {
        ASSERT( sendret.server_slot==server_slot && active && sendret.tid==tid );
        
        if( ready )
          {
           Packet_RET ret;
              
           ret.type=ret.Type;
           ret.tid=tid;
           ret.client_slot=client_slot;
           ret.server_slot=server_slot;
           ret.server_info=server_info;
              
           SendPacket(ret);
          }
        else if( canceled )  
          {
           Packet_CANCEL cancel;
              
           cancel.type=cancel.Type;
           cancel.tid=tid;
           cancel.client_slot=client_slot;
           cancel.server_slot=server_slot;
              
           SendPacket(cancel);
          }
       }
       
      void processTimeout()
       {
        Packet_RERET reret;
        
        reret.type=reret.Type;
        reret.tid=tid;
        reret.client_slot=client_slot;
        reret.server_slot=server_slot;
        
        SendPacket(reret);
       
        SetTimer(server_slot,timeout);
        
        if( timeout<MaxTimeout ) timeout+=DeltaTimeout;
       } 
     };
    
     
    
    
