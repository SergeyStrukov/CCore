/* main.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: DDLTypeSet 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/Exception.h>
#include <CCore/inc/Cmp.h>
#include <CCore/inc/Sort.h>

#include "Data.h"

namespace App {

/* class PrintType */

class PrintType : NoCopy
 {
   struct ProcessSwitch : DDL::TypeSwitch
    {
     PrintType *pro;
     bool use_alias;
     DDL::TypeNode *type_node;
     
     explicit ProcessSwitch(PrintType *pro_,bool use_alias_) : DDL::TypeSwitch(this),pro(pro_),use_alias(use_alias_) {}
     
     void set(StrLen name)
      {
       type_node=0;
       pro->add(name);
      }
     
     void do_sint8(DDL::TypeNode_suint<DDL::imp_sint8> *) { set("DDL::imp_sint8"); }
     void do_uint8(DDL::TypeNode_suint<DDL::imp_uint8> *) { set("DDL::imp_uint8"); }

     void do_sint16(DDL::TypeNode_suint<DDL::imp_sint16> *) { set("DDL::imp_sint16"); }
     void do_uint16(DDL::TypeNode_suint<DDL::imp_uint16> *) { set("DDL::imp_uint16"); }

     void do_sint32(DDL::TypeNode_suint<DDL::imp_sint32> *) { set("DDL::imp_sint32"); }
     void do_uint32(DDL::TypeNode_suint<DDL::imp_uint32> *) { set("DDL::imp_uint32"); }

     void do_sint64(DDL::TypeNode_suint<DDL::imp_sint64> *) { set("DDL::imp_sint64"); }
     void do_uint64(DDL::TypeNode_suint<DDL::imp_uint64> *) { set("DDL::imp_uint64"); }

     void do_text(DDL::TypeNode_text *) { set("StrLen"); }
     void do_ip(DDL::TypeNode_ip *) { set("DDL::imp_uint32"); }

     void do_ptr(DDL::TypeNode_ptr *ptr_node) 
      {
       type_node=ptr_node->type_node;
       pro->addSuffix(" *");
      }

     void do_array(DDL::TypeNode_array *array_node) 
      {
       type_node=array_node->type_node;
       pro->add("PtrLen<"," >");
      }
     
     void do_array_len(DDL::TypeNode_array_len *array_node) 
      {
       type_node=array_node->type_node;
       pro->add("PtrLen<"," >");
      }
     
     void do_struct(DDL::StructNode *struct_node)
      {
       type_node=0;
       pro->addStruct(struct_node->index);
      }
     
     void do_struct(DDL::TypeNode_struct *type) { do_struct(type->base_struct); }

     void do_ref(DDL::TypeNode_ref *type) 
      {
       if( DDL::AliasNode *alias=type->alias_node )
         {
          if( use_alias )
            {
             type_node=0;
             pro->addAlias(alias->index);
            }
          else
            {
             alias->result_type->dispatch(*this);
            }
         }
       else
         {
          do_struct(type->struct_node);
         }
      }
    };
    
   ProcessSwitch ts_process;
   
   static DynArray<StrLen> PrefixList;
   static DynArray<StrLen> SuffixList;
   
   ulen struct_index;
   ulen alias_index;
   
  private:
   
   void add(StrLen name) 
    { 
     PrefixList.append_copy(name); 
    }
   
   void add(StrLen prefix,StrLen suffix)
    {
     PrefixList.append_copy(prefix);
     SuffixList.append_copy(suffix);
    }
   
   void addSuffix(StrLen suffix)
    {
     SuffixList.append_copy(suffix);
    }
   
   void addStruct(ulen index) 
    { 
     struct_index=index; 
    }
   
   void addAlias(ulen index) 
    { 
     alias_index=index; 
    }
   
  public:
 
   explicit PrintType(DDL::TypeNode *type_node,bool use_alias=false)
    : ts_process(this,use_alias),
      struct_index(0),
      alias_index(0)
    {
     PrefixList.shrink_all();
     SuffixList.shrink_all();
    
     while( type_node )
       {
        type_node->dispatch(ts_process);
        
        type_node=ts_process.type_node;
       }
    }
   
   ~PrintType()
    {
    }
   
   template <class P>
   void print(P &out) const
    {
     for(StrLen str : PrefixList ) Putobj(out,str);
     
     if( struct_index ) Printf(out,"S#;",struct_index);
     
     if( alias_index ) Printf(out,"A#;",alias_index);
     
     for(StrLen str : RangeReverse(SuffixList) ) Putobj(out,str);
    }
 };

DynArray<StrLen> PrintType::PrefixList(DoReserve,100);
DynArray<StrLen> PrintType::SuffixList(DoReserve,100);

/* class PrintName */

class PrintName : NoCopy
 {
   static DynArray<StrLen> Stack;
   
   StrLen name;
   
  public:

   template <class T>  
   explicit PrintName(const T &node)
    {
     name=node.name.name.token.str;
     
     Stack.shrink_all();
     
     for(auto *scope=node.parent; scope ;scope=scope->parent)
       {
        Stack.append_copy(scope->name.name.token.str);
       }
    }
   
   ~PrintName()
    {
    }
   
   template <class P>
   void print(P &out) const
    {
     for(StrLen str : RangeReverse(Stack) ) Putobj(out,str,"#");
     
     Putobj(out,name);
    }
 };

DynArray<StrLen> PrintName::Stack(DoReserve,100);

/* struct Elem */

struct Elem : CmpComparable<Elem>
 {
  StrLen name;
  DDL::ScopeNode *parent;
  DDL::ScopeNode *scope;
  ulen index;
  bool is_struct;
  
  template <class T>
  void set(T &node)
   {
    name=node.name.name.token.str;
    parent=node.parent;
    index=node.index;
    
    if( auto ptr=parent )
      {
       while( auto next=ptr->parent ) ptr=next;
       
       scope=ptr;
      }
    else
      {
       scope=0;
      }
   }
  
  explicit Elem(DDL::StructNode &node)
   {
    set(node);
    is_struct=true;
   }
  
  explicit Elem(DDL::AliasNode &node)
   {
    set(node);
    is_struct=false;
   }
  
  void upScope()
   {
    if( scope )
      {
       if( scope==parent )
         {
          scope=0;
         }
       else
         {
          auto ptr=parent;
          
          while( ptr->parent!=scope ) ptr=ptr->parent;
          
          scope=ptr;
         }
      }
   }
  
  // cmp objects
  
  CmpResult objCmp(const Elem &obj) const
   {
    if( !scope )
      {
       if( obj.scope ) return CmpLess;
       
       return CmpEqual;
      }
     
    if( !obj.scope ) return CmpGreater;
    
    return StrCmp(scope->name.name.token.str,obj.scope->name.name.token.str);
   }
  
  // print object
  
  template <class P>
  void print(P &out) const
   {
    if( is_struct )
      Printf(out,"TypeDefCore::S#;",index);
    else
      Printf(out,"TypeDefCore::A#;",index);
   }
  
  // no-throw flags
  
  enum NoThrowFlagType
   {
    Default_no_throw = true,
    Copy_no_throw = true
   };
 };

/* PrintElems() */

template <class P>
void PrintElems(P &out,PtrLen<Elem> r,ulen off=0)
 {
  Sort(r);
  
  for(; +r && !r->scope ;++r)
    {
     Printf(out,"#;using #; = #; ;\n\n",RepeatChar(off+2,' '),r->name,*r);
    }
  
  while( +r )
    {
     StrLen name=r->scope->name.name.token.str;
     
     Printf(out,"#;namespace #; {\n\n",RepeatChar(off+2,' '),name);
     
     auto s=r;
     
     s->upScope();
     
     for(++s; +s && !StrCmp(s->scope->name.name.token.str,name) ;++s) s->upScope();
     
     PrintElems(out,r.prefix(s),off+2);
     
     r=s;
     
     Printf(out,"#;} // namespace #;\n\n",RepeatChar(off+2,' '),name);
    }
 }

/* Process() */

void Process(StrLen input_file_name,StrLen output1_file_name,StrLen output2_file_name)
 {
  Data data(input_file_name);
  PrintFile out1(output1_file_name);
  PrintFile out2(output2_file_name);
  
  // 1
  {
   Putobj(out1,"/* struct TypeDefCore */\n\n");
   
   Putobj(out1,"struct TypeDefCore\n"); 
   Putobj(out1," {\n"); 
   Putobj(out1,"  // types\n\n"); 
  }
  
  // 2
  {
   ulen ind=1; 
    
   for(auto &node : data->struct_list )
     {
      Printf(out1,"  struct S#;; // #;\n",ind,PrintName(node));
      
      node.index=ind++;
     }
   
   Putch(out1,'\n');
  }
  
  // 3
  {
   ulen ind=1; 
    
   for(auto &node : data->alias_list )
     {
      Printf(out1,"  using A#; = #; ; // #;\n",ind,PrintType(node.result_type),PrintName(node));
      
      node.index=ind++;
     }
   
   Putch(out1,'\n');
  }
  
  // 4
  {
   Putobj(out1,"  // structures\n\n");
  }
  
  // 5
  {
   for(auto &node : data->struct_list )
     {
      Printf(out1,"  struct S#;\n",node.index);
      Putobj(out1,"   {\n");
      
      for(auto &field : node.field_list )
        {
         Printf(out1,"    #; #;;\n",PrintType(field.type_node,true),field.name.name.token.str);
        }
      
      Putobj(out1,"   };\n\n");
     }
  }
  
  // 99
  {
   Putobj(out1," };\n\n"); 
  }
  
  // 100
  {
   Putobj(out1,"namespace TypeDef {\n\n"); 
  }
  
  // 101
  {
   DynArray<Elem> buf;
   
   for(auto &node : data->struct_list ) buf.append_fill(node);
   
   for(auto &node : data->alias_list ) buf.append_fill(node);
   
   PrintElems(out1,Range(buf));
  }
  
  // 199
  {
   Putobj(out1,"\n} // namespace TypeDef\n\n"); 
  }
  
  // 200
  {
   Putobj(out2,"/* struct TypeSet */\n\n");
   
   Putobj(out2,"struct TypeSet : TypeDefCore , DDL::MapHackPtr\n"); 
   Putobj(out2," {\n");
   Printf(out2,"  ulen indexes[#;];\n\n",Max<ulen>(data->struct_list.count,1));
   
   Putobj(out2,"  DDL::FindStructMap map;\n\n");
  }
  
  // 201
  {
   Putobj(out2,"  TypeSet()\n");
   Putobj(out2,"   {\n");
   Putobj(out2,"    Range(indexes).set(ulen(-1));\n\n");
     
   for(auto &node : data->struct_list )
     {
      Printf(out2,"    map.add(#;,#.q;",node.index,node.name.name.token.str);
      
      for(auto *scope=node.parent; scope ;scope=scope->parent)
        {
         Printf(out2,",#.q;",scope->name.name.token.str);
        }
      
      Printf(out2,");\n");
     }
     
   Putobj(out2,"   }\n\n");
  }
  
  // 202
  {
   Putobj(out2,"  ulen findStruct(DDL::StructNode *struct_node)\n");
   Putobj(out2,"   {\n");
   Putobj(out2,"    return map.find(struct_node);\n");
   Putobj(out2,"   }\n\n");
  }
  
  // 203
  {
   Putobj(out2,"  DDL::MapSizeInfo structSizeInfo(DDL::StructNode *struct_node)\n");
   Putobj(out2,"   {\n");
   Putobj(out2,"    DDL::MapSizeInfo ret;\n\n");
   
   Putobj(out2,"    switch( findStruct(struct_node) )\n");
   Putobj(out2,"      {\n");
   
   for(auto &node : data->struct_list )
     {
      Printf(out2,"       case #; :\n",node.index);
      Putobj(out2,"        {\n");
      Printf(out2,"         indexes[#;]=struct_node->index;\n\n",node.index-1);
      
      Printf(out2,"         ret.set<S#;>();\n\n",node.index);
      
      Putobj(out2,"         DDL::SetFieldOffsets(struct_node,\n");
      
      for(auto &field : node.field_list )
        {
         Printf(out2,"                              #.q;,offsetof(S#;,#;)",field.name.name.token.str,node.index,field.name.name.token.str);
         
         if( field.next ) Putch(out2,',');
         
         Putch(out2,'\n');
        }
      
      Putobj(out2,"                             );\n");

      Putobj(out2,"        }\n");
      Putobj(out2,"       return ret;\n\n");
     }
   
   Putobj(out2,"       default: Printf(Exception,\"Unknown structure\"); return ret;\n");
   Putobj(out2,"      }\n");
   Putobj(out2,"   }\n\n");
  }
  
  // 204
  {
   Putobj(out2,"  template <class T> struct IsStruct;\n\n");
   
   Putobj(out2,"  template <class T>\n");
   Putobj(out2,"  bool isStruct(DDL::StructNode *struct_node) const { return IsStruct<T>::Do(indexes,struct_node->index); }\n\n");
  }
  
  // 205
  {
   Putobj(out2,"  void guardFieldTypes(DDL::MapTypeCheck &type_check,DDL::StructNode *struct_node) const\n");
   Putobj(out2,"   {\n");
   
   for(auto &node : data->struct_list )
     {
      Printf(out2,"    if( struct_node->index==indexes[#;] )\n",node.index-1);
      Putobj(out2,"      {\n");
      Putobj(out2,"       DDL::GuardFieldTypes<\n");
      
      for(auto &field : node.field_list )
        {
         Putobj(out2,"                            ",PrintType(field.type_node,true));
         
         if( field.next ) Putch(out2,',');
         
         Putch(out2,'\n');
        }
      
      Putobj(out2,"                           >(*this,type_check,struct_node);\n");
      Putobj(out2,"      }\n\n");
     }
   
   Putobj(out2,"   }\n");
  }
  
  // 206
  {
   Putobj(out2," };\n\n"); 
  }
  
  // 207
  {
   Putobj(out2,"template <class T>\n"); 
   Putobj(out2,"struct TypeSet::IsStruct\n"); 
   Putobj(out2," {\n"); 
   Putobj(out2,"  static bool Do(const ulen *,ulen) { return false; }\n"); 
   Putobj(out2," };\n\n"); 
  }
  
  // 208
  {
   for(auto &node : data->struct_list )
     {
      Putobj(out2,"template <>\n");
      Printf(out2,"struct TypeSet::IsStruct<TypeDefCore::S#;>\n",node.index); 
      Putobj(out2," {\n");
      Printf(out2,"  static bool Do(const ulen *indexes,ulen index) { return index==indexes[#;]; }\n",node.index-1);
      Putobj(out2," };\n\n"); 
     }
  }
 }

} // namespace App

/* main() */ 

using namespace App;

int main(int argc,const char *argv[])
 {
  ReportException report;
  
  try
    {
     {
      Putobj(Con,"--- DDLTypeSet 1.00 ---\n--- Copyright (c) 2012 Sergey Strukov. All rights reserved. ---\n\n");

      if( argc!=4 ) 
        {
         Putobj(Con,"Usage: DDLTypeSet <input-file-name> <typedef-output-file-name> <typeset-output-file-name>\n");
         
         return 1;
        }

      Process(argv[1],argv[2],argv[3]);
     }
     
     report.guard();
     
     return 0;
    }
  catch(CatchType)
    {
     return 1;
    }
 }
 
