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

#include <CCore/inc/Cmp.h>
#include <CCore/inc/Sort.h>
#include <CCore/inc/CompactMap.h>
#include <CCore/inc/OwnPtr.h>

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
   bool use_alias;
   
  private: 
  
   template <class P>
   struct PrintFunc
    {
     P &out;
     bool use_alias;
     
     PrintFunc(P &out_,bool use_alias_) : out(out_),use_alias(use_alias_) {}
     
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
       Printf(out,"DDL2::MapPtr< #; >",PrintType(type_ptr->type_node,use_alias));
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
          
          Printf(out,"#;",PrintType(type,use_alias));
          
          if( cnt>1 ) Putobj(out," , ");
         }
       
       Putobj(out," >");
      }
     
     void operator () (DDL2::TypeNode::Array *type_ptr)
      {
       Printf(out,"DDL2::MapRange< #; >",PrintType(type_ptr->type_node,use_alias));
      }
     
     void operator () (DDL2::TypeNode::ArrayLen *type_ptr)
      {
       Printf(out,"DDL2::MapRange< #; >",PrintType(type_ptr->type_node,use_alias));
      }
     
     void operator () (DDL2::TypeNode::Struct *type_ptr)
      {
       (*this)(type_ptr->struct_node);
      }
    };
   
  public:

   explicit PrintType(DDL2::TypeNode *type_,bool use_alias_=false) : type(type_),use_alias(use_alias_) {}
  
   template <class P>
   void print(P &out) const
    {
     type->ptr.apply(PrintFunc<P>(out,use_alias));
    }
 };

#if 0

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
   
   struct Key : CmpComparable<Key>
    {
     StrLen name;
     
     // constructors
     
     Key() {}
     
     Key(StrLen name_) : name(name_) {}
     
     // cmp objects
     
     CmpResult objCmp(Key obj) const { return StrCmp(name,obj.name); }
     
     // print object
     
     template <class P>
     void print(P &out) const
      {
       Putobj(out,name);
      }
    };
   
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
     CompactRBTreeMap<Key,Entry> entries;
     CompactRBTreeMap<Key,OwnPtr<Dir> > dirs;
     
     Dir() {}

     DirName getName() const { return *this; }
     
     Dir * dir(StrLen name) 
      { 
       OwnPtr<Dir> *ptr=dirs.find_or_add(name);
       
       if( !*ptr ) ptr->set(new Dir());
       
       if( entries.find(name) )
         {
          Printf(Exception,"Unexpected name duplication");
         }
       
       return ptr->getPtr(); 
      }
     
     void entry(StrLen name,Name result) 
      { 
       if( !entries.find_or_add(name,result).new_flag )
         {
          Printf(Exception,"Unexpected name duplication");
         }
       
       if( dirs.find(name) )
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
       
       dirs.applyIncr( [&] (const Key &,const OwnPtr<Dir> &dir) { dir->complete(struct_list,extra_list); } );
      }
     
     void complete_root(DynArray<Dir *> &struct_list,DynArray<Dir *> &extra_list)
      {
       dirs.applyIncr( [&] (const Key &,const OwnPtr<Dir> &dir) { dir->complete(struct_list,extra_list); } );
      }
     
     template <class P>
     void printUsing(P &out,StrLen prefix) const
      {
       if( entries.getCount()+dirs.getCount() ) Putch(out,'\n');
       
       entries.applyIncr( [&,prefix] (const Key &key,const Entry &entry) { Printf(out,"    using #; = #;#; ;\n",key,prefix,entry); } );
       
       dirs.applyIncr( [&,prefix] (const Key &key,const OwnPtr<Dir> &dir) { Printf(out,"    using #; = #;#; ;\n",key,prefix,dir->getName()); } );
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
       
       entries.applyIncr_const( [&out,off] (const Key &key,const Entry &entry) { Printf(out,"#;#; = #;\n",RepeatChar(off+2,' '),key,entry); } );
       
       dirs.applyIncr_const( [&out,off] (const Key &key,const OwnPtr<Dir> &dir) { dir->print(out,key.name,off+2); } );
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
        Stack.append_copy(scope->name.name.token.str);
       }
     
     add(RangeReverse(Stack),node.name.name.token.str,name);
    }
   
   void add(DDL::StructNode &node)
    {
     add(node,NameS(node.index));
    }
   
   void add(DDL::AliasNode &node)
    {
     add(node,NameA(node.index));
    }
 
   void complete(ulen struct_lim)
    {
     struct_list.extend_default(struct_lim);
     
     root.complete_root(struct_list,extra_list);
    }
   
   template <class P>
   void printStruct(P &out,StrLen prefix,DDL::StructNode &node) const
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

#endif

/* Process() */

void Process(StrLen input_file_name,StrLen typedef_file_name,StrLen typeset_file_name)
 {
  Data data(input_file_name);
  PrintFile out1(typedef_file_name);
  PrintFile out2(typeset_file_name);
  
  ulen struct_lim;
  //NameDirectory dir;
  
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
      Printf(out1,"  struct S#;; // #;\n",ind,PrintName(&node));
      
      node.index=ind++;
     }
   
   struct_lim=ind;
   
   Putch(out1,'\n');
  }
  
  // 3
  {
   ulen ind=1; 
    
   for(auto &node : data->alias_list )
     {
      Printf(out1,"  using A#; = #; ; // #;\n",ind,PrintType(node.result_type),PrintName(&node));
      
      node.index=ind++;
     }
   
   Putch(out1,'\n');
  }
  
#if 0  
  
  // 4
  {
   for(auto &node : data->struct_list ) dir.add(node);
   
   for(auto &node : data->alias_list ) dir.add(node);
   
   dir.complete(struct_lim);
  }
  
  // 5
  {
   for(ulen ind=1,lim=dir.getExtraLim(); ind<lim ;ind++) Printf(out1,"  struct D#;;\n",ind);
   
   Putch(out1,'\n');
  }
  
  // 6
  {
   Putobj(out1,"  using XXX8226D906_9897_43AA_B1BE_D60B0A6E31C8 = TypeDefCore ;\n\n");
   Putobj(out1,"  // structures\n\n");
  }
  
  // 7
  {
   for(auto &node : data->struct_list )
     {
      Printf(out1,"  struct S#;\n",node.index);
      Putobj(out1,"   {\n");
      
      for(auto &field : node.field_list )
        {
         Printf(out1,"    #; #;;\n",PrintType(field.type_node,true),field.name.name.token.str);
        }

      dir.printStruct(out1,"XXX8226D906_9897_43AA_B1BE_D60B0A6E31C8::",node);
      
      Putobj(out1,"\n    struct Ext;\n");
      Putobj(out1,"   };\n\n");
     }
  }
  
  // 8
  {
   Putobj(out1,"  // extra\n\n");
  }
  
  // 9
  {
   for(ulen ind=1,lim=dir.getExtraLim(); ind<lim ;ind++) 
     {
      Printf(out1,"  struct D#;\n   {\n",ind);
      
      dir.printExtra(out1,"XXX8226D906_9897_43AA_B1BE_D60B0A6E31C8::",ind);
      
      Printf(out1,"   };\n\n");
     }
  }
  
  // 99
  {
   Putobj(out1," };\n\n"); 
  }
  
  // 100
  {
   Putobj(out1,"using XXX212CD757_09B2_4D89_BE20_65C1E4E5A819 = TypeDefCore ;\n\n");
   
   Putobj(out1,"namespace TypeDef {\n"); 
  }
  
  // 101
  {
   dir.printRoot(out1,"XXX212CD757_09B2_4D89_BE20_65C1E4E5A819::");
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
   Printf(out2,"  ulen indexes[#;];\n",Max<ulen>(data->struct_list.count,1));
   Printf(out2,"  DynArray<ulen> ind_map;\n\n");
   
   Putobj(out2,"  DDL::FindNodeMap map;\n\n");
  }
  
  // 201
  {
   Putobj(out2,"  explicit TypeSet(ulen len)\n");
   Putobj(out2,"   : ind_map(len)\n");
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
   
   Putobj(out2,"\n    map.complete();\n");
   Putobj(out2,"   }\n\n");
  }
  
  // 202
  {
   Putobj(out2,"  DDL::MapSizeInfo structSizeInfo(DDL::StructNode *struct_node)\n");
   Putobj(out2,"   {\n");
   Putobj(out2,"    DDL::MapSizeInfo ret;\n\n");
   
   Putobj(out2,"    switch( map.find(struct_node) )\n");
   Putobj(out2,"      {\n");
   
   for(auto &node : data->struct_list )
     {
      Printf(out2,"       case #; :\n",node.index);
      Putobj(out2,"        {\n");
      Printf(out2,"         indexes[#;]=struct_node->index;\n",node.index-1);
      Printf(out2,"         ind_map[struct_node->index]=#;;\n\n",node.index);
      
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
  
  // 203
  {
   Putobj(out2,"  template <class T> struct IsStruct;\n\n");
   
   Putobj(out2,"  template <class T>\n");
   Putobj(out2,"  bool isStruct(DDL::StructNode *struct_node) const { return IsStruct<T>::Do(indexes,struct_node->index); }\n\n");
  }
  
  // 204
  {
   Putobj(out2,"  void guardFieldTypes(DDL::MapTypeCheck &type_check,DDL::StructNode *struct_node) const\n");
   Putobj(out2,"   {\n");
   Putobj(out2,"    switch( ind_map[struct_node->index] )\n");
   Putobj(out2,"      {\n");
   
   for(auto &node : data->struct_list )
     {
      Printf(out2,"       case #; :\n",node.index);
      Putobj(out2,"        {\n");
      Putobj(out2,"         DDL::GuardFieldTypes<\n");
      
      for(auto &field : node.field_list )
        {
         Putobj(out2,"                              ",PrintType(field.type_node,true));
         
         if( field.next ) Putch(out2,',');
         
         Putch(out2,'\n');
        }
      
      Putobj(out2,"                             >(*this,type_check,struct_node);\n");
      Putobj(out2,"        }\n");
      Putobj(out2,"       break;\n\n");
     }
   
   Putobj(out2,"       default: Printf(Exception,\"Unknown structure\");\n");
   Putobj(out2,"      }\n");
   Putobj(out2,"   }\n");
  }
  
  // 205
  {
   Putobj(out2," };\n\n"); 
  }
  
  // 206
  {
   Putobj(out2,"template <class T>\n"); 
   Putobj(out2,"struct TypeSet::IsStruct\n"); 
   Putobj(out2," {\n"); 
   Putobj(out2,"  static bool Do(const ulen *,ulen) { return false; }\n"); 
   Putobj(out2," };\n\n"); 
  }
  
  // 207
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
  
#endif  
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
 
