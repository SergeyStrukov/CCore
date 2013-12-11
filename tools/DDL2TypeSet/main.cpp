/* main.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: DDL2TypeSet 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/Print.h>
#include <CCore/inc/Exception.h>

#include <CCore/inc/StrKey.h>
#include <CCore/inc/CompactMap.h>
#include <CCore/inc/OwnPtr.h>
#include <CCore/inc/Sort.h>

#include <CCore/inc/ddl2/DDL2Engine.h>

#include <CCore/inc/FileName.h>
#include <CCore/inc/FileToMem.h>

namespace App {

/* using */ 

using namespace CCore;

/* const MaxLevel */

const unsigned MaxLevel = 100 ;

/* class Data */

class Data : NoCopy
 {
   PrintCon out;
   DDL2::FileEngine<FileName,FileToMem> engine;
   DDL2::EngineResult result;
   
  public: 
  
   explicit Data(StrLen file_name);
   
   ~Data() {}
   
   DDL2::BodyNode * operator -> () const { return result.body; }
 };

Data::Data(StrLen file_name)
 : out(Con),
   engine(out)
 {
  result=engine.process(file_name);
  
  out.flush();
  
  if( !result ) Printf(Exception,"Input file processing error");
 }

/* type PrintName */

using PrintName = DDL2::PrintName ;

/* class PrintType */

class PrintType : NoCopy
 {
   DDL2::TypeNode *type;
   unsigned level;
   bool use_alias;
   
  private: 
  
   template <class P>
   struct PrintFunc
    {
     P &out;
     unsigned level;
     bool use_alias;
     
     PrintFunc(P &out_,unsigned level_,bool use_alias_) : out(out_),level(level_),use_alias(use_alias_) {}
     
     void operator () (DDL2::TypeNode::Base *type_ptr)
      {
       switch( type_ptr->type )
         {
          case DDL2::TypeNode::Base::Type_sint : Printf(out,"DDL2::sint_type"); break; 
          case DDL2::TypeNode::Base::Type_uint : Printf(out,"DDL2::uint_type"); break; 
          case DDL2::TypeNode::Base::Type_ulen : Printf(out,"DDL2::ulen_type"); break;
          
          case DDL2::TypeNode::Base::Type_sint8 : Printf(out,"sint8"); break; 
          case DDL2::TypeNode::Base::Type_uint8 : Printf(out,"uint8"); break;
          case DDL2::TypeNode::Base::Type_sint16 : Printf(out,"sint16"); break; 
          case DDL2::TypeNode::Base::Type_uint16 : Printf(out,"uint16"); break; 
          case DDL2::TypeNode::Base::Type_sint32 : Printf(out,"sint32"); break; 
          case DDL2::TypeNode::Base::Type_uint32 : Printf(out,"uint32"); break; 
          case DDL2::TypeNode::Base::Type_sint64 : Printf(out,"sint64"); break; 
          case DDL2::TypeNode::Base::Type_uint64 : Printf(out,"uint64"); break;
          
          case DDL2::TypeNode::Base::Type_text : Printf(out,"DDL2::MapText"); break;
          case DDL2::TypeNode::Base::Type_ip : Printf(out,"uint32"); break;
         }
      }
     
     void operator () (DDL2::AliasNode *alias_node)
      {
       if( use_alias )
         {
          Printf(out,"A#;",alias_node->index);
         }
       else
         {
          alias_node->result_type->ptr.apply(*this);
         }
      }
     
     void operator () (DDL2::StructNode *struct_node)
      {
       Printf(out,"S#;",struct_node->index);
      }
     
     void operator () (DDL2::TypeNode::Ref *type_ptr)
      {
       type_ptr->ptr.apply(*this);
      }
     
     void operator () (DDL2::TypeNode::Ptr *type_ptr)
      {
       Printf(out,"DDL2::MapPtr< #; >",PrintType(type_ptr->type_node,level-1,use_alias));
      }
     
     void operator () (DDL2::TypeNode::PolyPtr *type_ptr)
      {
       Printf(out,"DDL2::MapPolyPtr< ");
       
       auto *type_list=type_ptr->type_list;
       
       TempArray<DDL2::TypeNode *,25> temp(type_list->count);
       
       auto *ptr=temp.getPtr();
       
       for(auto &node : *type_list )
         {
          *(ptr++)=node.type_node;
         }
       
       for(ulen cnt=type_list->count; cnt ;cnt--)
         {
          auto type=*(--ptr);
          
          Printf(out,"#;",PrintType(type,level-1,use_alias));
          
          if( cnt>1 ) Putobj(out," , ");
         }
       
       Putobj(out," >");
      }
     
     void operator () (DDL2::TypeNode::Array *type_ptr)
      {
       Printf(out,"DDL2::MapRange< #; >",PrintType(type_ptr->type_node,level-1,use_alias));
      }
     
     void operator () (DDL2::TypeNode::ArrayLen *type_ptr)
      {
       Printf(out,"DDL2::MapRange< #; >",PrintType(type_ptr->type_node,level-1,use_alias));
      }
     
     void operator () (DDL2::TypeNode::Struct *type_ptr)
      {
       (*this)(type_ptr->struct_node);
      }
    };
   
  public:

   explicit PrintType(DDL2::TypeNode *type_,unsigned level_,bool use_alias_=false) 
    : type(type_),level(level_),use_alias(use_alias_) 
    {
     if( !level )
       {
        Printf(Exception,"App : too deep type");
       }
    }
  
   template <class P>
   void print(P &out) const
    {
     type->ptr.apply(PrintFunc<P>(out,level,use_alias));
    }
 };

/* struct NameS */

struct NameS
 {
  ulen index;
  
  explicit NameS(ulen index_) : index(index_) {}
 };

/* struct NameA */

struct NameA
 {
  ulen index;
  
  explicit NameA(ulen index_) : index(index_) {}
 };

/* struct Name */

struct Name
 {
  enum Type
   {
    Type_S = 1,
    Type_A = 2
   };
  
  Type type;
  ulen index;
  
  Name(NameS name) : type(Type_S),index(name.index) {}
  
  Name(NameA name) : type(Type_A),index(name.index) {}
  
  // print object
  
  friend const char * GetTextDesc(Type type)
   {
    switch( type )
      {
       case Type_S : return "S"; 
       case Type_A : return "A";
       
       default: return "???";
      }
   }
  
  template <class P>
  void print(P &out) const
   {
    Printf(out,"#;#;",type,index);
   }
 };

/* class NameDirectory */

class NameDirectory : NoCopy
 {
   static DynArray<StrLen> Stack;
   
   struct Entry
    {
     Name result;
     
     explicit Entry(Name result_) : result(result_) {}
     
     // print object
     
     template <class P>
     void print(P &out) const
      {
       Putobj(out,result);
      }
    };
   
   struct DirName
    {
     ulen index;
     ulen extra_index;
     
     DirName() : index(0),extra_index(0) {}
     
     // print object
     
     template <class P>
     void print(P &out) const
      {
       if( index )
         Printf(out,"S#;",index);
       else
         Printf(out,"D#;",extra_index);
      }
    };
   
   struct Dir : DirName , MemBase_nocopy
    {
     CompactRBTreeMap<StrKey,Entry> entries;
     CompactRBTreeMap<StrKey,OwnPtr<Dir> > dirs;
     
     Dir() {}

     DirName getName() const { return *this; }
     
     Dir * dir(StrLen name) 
      { 
       StrKey key(name);
       OwnPtr<Dir> *ptr=dirs.find_or_add(key);
       
       if( !*ptr ) ptr->set(new Dir());
       
       if( entries.find(key) )
         {
          Printf(Exception,"Unexpected name duplication");
         }
       
       return ptr->getPtr(); 
      }
     
     void entry(StrLen name,Name result) 
      { 
       StrKey key(name);
       
       if( !entries.find_or_add(key,result).new_flag )
         {
          Printf(Exception,"Unexpected name duplication");
         }
       
       if( dirs.find(key) )
         {
          Printf(Exception,"Unexpected name duplication");
         }
      }
     
     void setIndex(ulen index_)
      {
       if( index )
         {  
          Printf(Exception,"Unexpected name duplication");
         }
       
       index=index_;
      }
     
     void complete(DynArray<Dir *> &struct_list,DynArray<Dir *> &extra_list)
      {
       if( index )
         {
          struct_list[index]=this;
         }
       else
         {
          extra_index=extra_list.getLen();
         
          extra_list.append_copy(this);
         }
       
       dirs.applyIncr( [&] (const StrKey &,const OwnPtr<Dir> &dir) { dir->complete(struct_list,extra_list); } );
      }
     
     void complete_root(DynArray<Dir *> &struct_list,DynArray<Dir *> &extra_list)
      {
       dirs.applyIncr( [&] (const StrKey &,const OwnPtr<Dir> &dir) { dir->complete(struct_list,extra_list); } );
      }
     
     template <class P>
     void printUsing(P &out,StrLen prefix) const
      {
       if( entries.getCount()+dirs.getCount() ) Putch(out,'\n');
       
       entries.applyIncr( [&,prefix] (const StrKey &key,const Entry &entry) { Printf(out,"    using #; = #;#; ;\n",key.str,prefix,entry); } );
       
       dirs.applyIncr( [&,prefix] (const StrKey &key,const OwnPtr<Dir> &dir) { Printf(out,"    using #; = #;#; ;\n",key.str,prefix,dir->getName()); } );
      }
     
     // print object
     
     template <class P>
     void print(P &out,StrLen name={},ulen off=0) const
      {
       if( index ) 
         Printf(out,"#;#; -> S#;\n",RepeatChar(off,' '),name,index);
       else if( extra_index )
         Printf(out,"#;#; -> D#;\n",RepeatChar(off,' '),name,extra_index);
       else
         Printf(out,"#;(root)\n",RepeatChar(off,' '));
       
       entries.applyIncr_const( [&out,off] (const StrKey &key,const Entry &entry) { Printf(out,"#;#; = #;\n",RepeatChar(off+2,' '),key.str,entry); } );
       
       dirs.applyIncr_const( [&out,off] (const StrKey &key,const OwnPtr<Dir> &dir) { dir->print(out,key.str,off+2); } );
      }
    };
   
   Dir root;
   DynArray<Dir *> struct_list;
   DynArray<Dir *> extra_list;
  
  public:
 
   NameDirectory() : extra_list(DoReserve,100) { extra_list.append_default(); }
   
   ~NameDirectory() {}
   
   void add(PtrLenReverse<StrLen> path,StrLen name,NameS result)
    {
     Dir *ptr=&root;
     
     for(; +path ;++path) ptr=ptr->dir(*path); 

     ptr->dir(name)->setIndex(result.index);
    }
   
   void add(PtrLenReverse<StrLen> path,StrLen name,NameA result)
    {
     Dir *ptr=&root;
     
     for(; +path ;++path) ptr=ptr->dir(*path); 

     ptr->entry(name,result);
    }
   
   template <class T,class N>
   void add(T &node,N name)
    {
     Stack.shrink_all();
     
     for(auto *scope=node.parent; scope ;scope=scope->parent)
       {
        Stack.append_copy(scope->name.getStr());
       }
     
     add(RangeReverse(Stack),node.name.getStr(),name);
    }
   
   void add(DDL2::StructNode &node)
    {
     add(node,NameS(node.index));
    }
   
   void add(DDL2::AliasNode &node)
    {
     add(node,NameA(node.index));
    }
 
   void complete(ulen struct_lim)
    {
     struct_list.extend_default(struct_lim);
     
     root.complete_root(struct_list,extra_list);
    }
   
   template <class P>
   void printStruct(P &out,StrLen prefix,DDL2::StructNode &node) const
    {
     Dir *dir=struct_list[node.index];
     
     dir->printUsing(out,prefix);
    }
   
   template <class P>
   void printExtra(P &out,StrLen prefix,ulen ind) const
    {
     Dir *dir=extra_list[ind];
     
     dir->printUsing(out,prefix);
    }
   
   template <class P>
   void printRoot(P &out,StrLen prefix) const
    {
     root.printUsing(out,prefix);
    }
   
   ulen getExtraLim() const { return extra_list.getLen(); }
   
   // print object
   
   template <class P>
   void print(P &out) const
    {
     Putobj(out,root);
    }
 };

DynArray<StrLen> NameDirectory::Stack(DoReserve,100);

/* Process() */

void Process(StrLen input_file_name,StrLen typedef_file_name,StrLen typeset_file_name)
 {
  Data data(input_file_name);
  PrintFile outdef(typedef_file_name);
  PrintFile outset(typeset_file_name);
  
  ulen struct_lim;
  NameDirectory dir;
  
  // 101
  {
   Putobj(outdef,"/* struct TypeDefCore */\n\n");
   
   Putobj(outdef,"struct TypeDefCore\n"); 
   Putobj(outdef," {\n"); 
   Putobj(outdef,"  // types\n\n"); 
  }
  
  // 102
  {
   ulen ind=1; 
    
   for(auto &node : data->struct_list )
     {
      Printf(outdef,"  struct S#;; // #;\n",ind,PrintName(&node));
      
      node.index=ind++;
     }
   
   struct_lim=ind;
   
   Putch(outdef,'\n');
  }
  
  // 103
  {
   ulen ind=1; 
    
   for(auto &node : data->alias_list )
     {
      Printf(outdef,"  using A#; = #; ; // #;\n",ind,PrintType(node.result_type,MaxLevel),PrintName(&node));
      
      node.index=ind++;
     }
   
   Putch(outdef,'\n');
  }
  
  // 104
  {
   for(auto &node : data->struct_list ) dir.add(node);
   
   for(auto &node : data->alias_list ) dir.add(node);
   
   dir.complete(struct_lim);
  }
  
  // 105
  {
   for(ulen ind=1,lim=dir.getExtraLim(); ind<lim ;ind++) Printf(outdef,"  struct D#;;\n",ind);
   
   Putch(outdef,'\n');
  }
  
  // 106
  {
   Putobj(outdef,"  using XXX8226D906_9898_43AA_B1BE_D60B0A6E31C8 = TypeDefCore ;\n\n");
   
   Putobj(outdef,"  // structures\n\n");
  }
  
  // 107
  {
   for(auto &node : data->struct_list )
     {
      Printf(outdef,"  struct S#;\n",node.index);
      Putobj(outdef,"   {\n");
      
      for(auto &field : node.field_list )
        {
         Printf(outdef,"    #; #;;\n",PrintType(field.type_node,MaxLevel,true),field.name.getStr());
        }

      dir.printStruct(outdef,"XXX8226D906_9898_43AA_B1BE_D60B0A6E31C8::",node);
      
      Putobj(outdef,"\n    struct Ext;\n");
      Putobj(outdef,"   };\n\n");
     }
  }
  
  // 108
  {
   Putobj(outdef,"  // extra\n\n");
  }
  
  // 109
  {
   for(ulen ind=1,lim=dir.getExtraLim(); ind<lim ;ind++) 
     {
      Printf(outdef,"  struct D#;\n   {\n",ind);
      
      dir.printExtra(outdef,"XXX8226D906_9898_43AA_B1BE_D60B0A6E31C8::",ind);
      
      Printf(outdef,"   };\n\n");
     }
  }
  
  // 110
  {
   Putobj(outdef," };\n\n"); 
  }
  
  // 111
  {
   Putobj(outdef,"using XXX212CD757_09B3_4D89_BE20_65C1E4E5A819 = TypeDefCore ;\n\n");
   
   Putobj(outdef,"namespace TypeDef {\n");
   
   dir.printRoot(outdef,"XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::");
   
   Putobj(outdef,"\n} // namespace TypeDef\n\n"); 
  }
  
  // 200
  {
   Putobj(outset,"/* struct TypeSet */\n\n");
   
   Putobj(outset,"struct TypeSet : TypeDefCore\n"); 
   Putobj(outset," {\n");
   Printf(outset,"  ulen indexes[#;];\n",Max<ulen>(data->struct_list.count,1));
   Printf(outset,"  DynArray<ulen> ind_map;\n\n");
   
   Putobj(outset,"  DDL2::FindNodeMap map;\n\n");
  }
  
  // 201
  {
   Putobj(outset,"  explicit TypeSet(ulen len)\n");
   Putobj(outset,"   : ind_map(len)\n");
   Putobj(outset,"   {\n");
   Putobj(outset,"    Range(indexes).set(ulen(-1));\n\n");
     
   for(auto &node : data->struct_list )
     {
      Printf(outset,"    map.add(#;,#.q;",node.index,node.name.getStr());
      
      for(auto *scope=node.parent; scope ;scope=scope->parent)
        {
         Printf(outset,",#.q;",scope->name.getStr());
        }
      
      Printf(outset,");\n");
     }
   
   Putobj(outset,"\n    map.complete();\n");
   Putobj(outset,"   }\n\n");
  }
  
  // 202
  {
   Putobj(outset,"  DDL2::MapSizeInfo structSizeInfo(DDL2::StructNode *struct_node)\n");
   Putobj(outset,"   {\n");
   Putobj(outset,"    DDL2::MapSizeInfo ret;\n\n");
   
   Putobj(outset,"    switch( map.find(struct_node) )\n");
   Putobj(outset,"      {\n");
   
   for(auto &node : data->struct_list )
     {
      Printf(outset,"       case #; :\n",node.index);
      Putobj(outset,"        {\n");
      Printf(outset,"         indexes[#;]=struct_node->index;\n",node.index-1);
      Printf(outset,"         ind_map[struct_node->index]=#;;\n\n",node.index);
      
      Printf(outset,"         ret.set<S#;>();\n\n",node.index);
      
      Putobj(outset,"         DDL2::SetFieldOffsets(struct_node,\n");
      
      for(auto &field : node.field_list )
        {
         Printf(outset,"                               #.q;,offsetof(S#;,#;)",field.name.getStr(),node.index,field.name.getStr());
         
         if( field.next ) Putch(outset,',');
         
         Putch(outset,'\n');
        }
      
      Putobj(outset,"                              );\n");

      Putobj(outset,"        }\n");
      Putobj(outset,"       return ret;\n\n");
     }
   
   Putobj(outset,"       default: Printf(Exception,\"Unknown structure\"); return ret;\n");
   Putobj(outset,"      }\n");
   Putobj(outset,"   }\n\n");
  }
  
  // 203
  {
   Putobj(outset,"  template <class T> struct IsStruct;\n\n");
   
   Putobj(outset,"  template <class T>\n");
   Putobj(outset,"  bool isStruct(DDL2::StructNode *struct_node) const { return IsStruct<T>::Do(indexes,struct_node->index); }\n\n");
  }
  
  // 204
  {
   Putobj(outset,"  void guardFieldTypes(DDL2::StructNode *struct_node) const\n");
   Putobj(outset,"   {\n");
   Putobj(outset,"    switch( ind_map[struct_node->index] )\n");
   Putobj(outset,"      {\n");
   
   for(auto &node : data->struct_list )
     {
      Printf(outset,"       case #; :\n",node.index);
      Putobj(outset,"        {\n");
      Putobj(outset,"         DDL2::GuardFieldTypes<\n");
      
      for(auto &field : node.field_list )
        {
         Putobj(outset,"                               ",PrintType(field.type_node,MaxLevel,true));
         
         if( field.next ) Putch(outset,',');
         
         Putch(outset,'\n');
        }
      
      Putobj(outset,"                              >(*this,struct_node);\n");
      Putobj(outset,"        }\n");
      Putobj(outset,"       break;\n\n");
     }
   
   Putobj(outset,"       default: Printf(Exception,\"Unknown structure\");\n");
   Putobj(outset,"      }\n");
   Putobj(outset,"   }\n");
  }
  
  // 205
  {
   Putobj(outset," };\n\n"); 
  }
  
  // 206
  {
   Putobj(outset,"template <class T>\n"); 
   Putobj(outset,"struct TypeSet::IsStruct\n"); 
   Putobj(outset," {\n"); 
   Putobj(outset,"  static bool Do(const ulen *,ulen) { return false; }\n"); 
   Putobj(outset," };\n\n"); 
  }
  
  // 207
  {
   for(auto &node : data->struct_list )
     {
      Putobj(outset,"template <>\n");
      Printf(outset,"struct TypeSet::IsStruct<TypeDefCore::S#;>\n",node.index); 
      Putobj(outset," {\n");
      Printf(outset,"  static bool Do(const ulen *indexes,ulen index) { return index==indexes[#;]; }\n",node.index-1);
      Putobj(outset," };\n\n"); 
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
      Putobj(Con,"--- DDL2TypeSet 1.00 ---\n--- Copyright (c) 2013 Sergey Strukov. All rights reserved. ---\n\n");

      if( argc!=4 ) 
        {
         Putobj(Con,"Usage: DDL2TypeSet <input-file-name> <typedef-output-file-name> <typeset-output-file-name>\n");
         
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
 
