/* struct TypeSet */

struct TypeSet : TypeDefCore , DDL::MapHackPtr
 {
  ulen indexes[13];
  DynArray<ulen> ind_map;

  DDL::FindNodeMap map;

  explicit TypeSet(ulen len)
   : ind_map(len)
   {
    Range(indexes).set(ulen(-1));

    map.add(1,"Action","Final");
    map.add(2,"Final");
    map.add(3,"Transition","State");
    map.add(4,"State");
    map.add(5,"Arg","TopRule");
    map.add(6,"TopRule");
    map.add(7,"Arg","Rule");
    map.add(8,"Rule");
    map.add(9,"Element");
    map.add(10,"Kind");
    map.add(11,"Synt");
    map.add(12,"Atom");
    map.add(13,"Lang");

    map.complete();
   }

  DDL::MapSizeInfo structSizeInfo(DDL::StructNode *struct_node)
   {
    DDL::MapSizeInfo ret;

    switch( map.find(struct_node) )
      {
       case 1 :
        {
         indexes[0]=struct_node->index;
         ind_map[struct_node->index]=1;

         ret.set<S1>();

         DDL::SetFieldOffsets(struct_node,
                              "atom",offsetof(S1,atom),
                              "rule",offsetof(S1,rule)
                             );
        }
       return ret;

       case 2 :
        {
         indexes[1]=struct_node->index;
         ind_map[struct_node->index]=2;

         ret.set<S2>();

         DDL::SetFieldOffsets(struct_node,
                              "index",offsetof(S2,index),
                              "actions",offsetof(S2,actions)
                             );
        }
       return ret;

       case 3 :
        {
         indexes[2]=struct_node->index;
         ind_map[struct_node->index]=3;

         ret.set<S3>();

         DDL::SetFieldOffsets(struct_node,
                              "element",offsetof(S3,element),
                              "state",offsetof(S3,state)
                             );
        }
       return ret;

       case 4 :
        {
         indexes[3]=struct_node->index;
         ind_map[struct_node->index]=4;

         ret.set<S4>();

         DDL::SetFieldOffsets(struct_node,
                              "index",offsetof(S4,index),
                              "final",offsetof(S4,final),
                              "transitions",offsetof(S4,transitions)
                             );
        }
       return ret;

       case 5 :
        {
         indexes[4]=struct_node->index;
         ind_map[struct_node->index]=5;

         ret.set<S5>();

         DDL::SetFieldOffsets(struct_node,
                              "atom",offsetof(S5,atom),
                              "kind",offsetof(S5,kind)
                             );
        }
       return ret;

       case 6 :
        {
         indexes[5]=struct_node->index;
         ind_map[struct_node->index]=6;

         ret.set<S6>();

         DDL::SetFieldOffsets(struct_node,
                              "index",offsetof(S6,index),
                              "name",offsetof(S6,name),
                              "bottom",offsetof(S6,bottom),
                              "result",offsetof(S6,result),
                              "args",offsetof(S6,args)
                             );
        }
       return ret;

       case 7 :
        {
         indexes[6]=struct_node->index;
         ind_map[struct_node->index]=7;

         ret.set<S7>();

         DDL::SetFieldOffsets(struct_node,
                              "atom",offsetof(S7,atom),
                              "synt",offsetof(S7,synt)
                             );
        }
       return ret;

       case 8 :
        {
         indexes[7]=struct_node->index;
         ind_map[struct_node->index]=8;

         ret.set<S8>();

         DDL::SetFieldOffsets(struct_node,
                              "index",offsetof(S8,index),
                              "name",offsetof(S8,name),
                              "result",offsetof(S8,result),
                              "args",offsetof(S8,args)
                             );
        }
       return ret;

       case 9 :
        {
         indexes[8]=struct_node->index;
         ind_map[struct_node->index]=9;

         ret.set<S9>();

         DDL::SetFieldOffsets(struct_node,
                              "index",offsetof(S9,index),
                              "atom",offsetof(S9,atom),
                              "kind",offsetof(S9,kind)
                             );
        }
       return ret;

       case 10 :
        {
         indexes[9]=struct_node->index;
         ind_map[struct_node->index]=10;

         ret.set<S10>();

         DDL::SetFieldOffsets(struct_node,
                              "kindex",offsetof(S10,kindex),
                              "index",offsetof(S10,index),
                              "name",offsetof(S10,name),
                              "synt",offsetof(S10,synt),
                              "element",offsetof(S10,element),
                              "rules",offsetof(S10,rules)
                             );
        }
       return ret;

       case 11 :
        {
         indexes[10]=struct_node->index;
         ind_map[struct_node->index]=11;

         ret.set<S11>();

         DDL::SetFieldOffsets(struct_node,
                              "index",offsetof(S11,index),
                              "name",offsetof(S11,name),
                              "kinds",offsetof(S11,kinds),
                              "rules",offsetof(S11,rules)
                             );
        }
       return ret;

       case 12 :
        {
         indexes[11]=struct_node->index;
         ind_map[struct_node->index]=12;

         ret.set<S12>();

         DDL::SetFieldOffsets(struct_node,
                              "index",offsetof(S12,index),
                              "name",offsetof(S12,name),
                              "element",offsetof(S12,element)
                             );
        }
       return ret;

       case 13 :
        {
         indexes[12]=struct_node->index;
         ind_map[struct_node->index]=13;

         ret.set<S13>();

         DDL::SetFieldOffsets(struct_node,
                              "atoms",offsetof(S13,atoms),
                              "synts",offsetof(S13,synts),
                              "lang",offsetof(S13,lang),
                              "elements",offsetof(S13,elements),
                              "rules",offsetof(S13,rules),
                              "top_rules",offsetof(S13,top_rules),
                              "states",offsetof(S13,states),
                              "finals",offsetof(S13,finals)
                             );
        }
       return ret;

       default: Printf(Exception,"Unknown structure"); return ret;
      }
   }

  template <class T> struct IsStruct;

  template <class T>
  bool isStruct(DDL::StructNode *struct_node) const { return IsStruct<T>::Do(indexes,struct_node->index); }

  void guardFieldTypes(DDL::MapTypeCheck &type_check,DDL::StructNode *struct_node) const
   {
    switch( ind_map[struct_node->index] )
      {
       case 1 :
        {
         DDL::GuardFieldTypes<
                              S12 *,
                              S8 *
                             >(*this,type_check,struct_node);
        }
       break;

       case 2 :
        {
         DDL::GuardFieldTypes<
                              A1,
                              PtrLen<S1 >
                             >(*this,type_check,struct_node);
        }
       break;

       case 3 :
        {
         DDL::GuardFieldTypes<
                              S9 *,
                              S4 *
                             >(*this,type_check,struct_node);
        }
       break;

       case 4 :
        {
         DDL::GuardFieldTypes<
                              A2,
                              S2 *,
                              PtrLen<S3 >
                             >(*this,type_check,struct_node);
        }
       break;

       case 5 :
        {
         DDL::GuardFieldTypes<
                              S12 *,
                              S10 *
                             >(*this,type_check,struct_node);
        }
       break;

       case 6 :
        {
         DDL::GuardFieldTypes<
                              A3,
                              StrLen,
                              S8 *,
                              S10 *,
                              PtrLen<S5 >
                             >(*this,type_check,struct_node);
        }
       break;

       case 7 :
        {
         DDL::GuardFieldTypes<
                              S12 *,
                              S11 *
                             >(*this,type_check,struct_node);
        }
       break;

       case 8 :
        {
         DDL::GuardFieldTypes<
                              A3,
                              StrLen,
                              S10 *,
                              PtrLen<S7 >
                             >(*this,type_check,struct_node);
        }
       break;

       case 9 :
        {
         DDL::GuardFieldTypes<
                              A4,
                              S12 *,
                              S10 *
                             >(*this,type_check,struct_node);
        }
       break;

       case 10 :
        {
         DDL::GuardFieldTypes<
                              A5,
                              A5,
                              StrLen,
                              S11 *,
                              S9 *,
                              PtrLen<S6 * >
                             >(*this,type_check,struct_node);
        }
       break;

       case 11 :
        {
         DDL::GuardFieldTypes<
                              A6,
                              StrLen,
                              PtrLen<S10 >,
                              PtrLen<S8 * >
                             >(*this,type_check,struct_node);
        }
       break;

       case 12 :
        {
         DDL::GuardFieldTypes<
                              A7,
                              StrLen,
                              S9 *
                             >(*this,type_check,struct_node);
        }
       break;

       case 13 :
        {
         DDL::GuardFieldTypes<
                              PtrLen<S12 >,
                              PtrLen<S11 >,
                              PtrLen<S11 * >,
                              PtrLen<S9 >,
                              PtrLen<S8 >,
                              PtrLen<S6 >,
                              PtrLen<S4 >,
                              PtrLen<S2 >
                             >(*this,type_check,struct_node);
        }
       break;

       default: Printf(Exception,"Unknown structure");
      }
   }
 };

template <class T>
struct TypeSet::IsStruct
 {
  static bool Do(const ulen *,ulen) { return false; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S1>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[0]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S2>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[1]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S3>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[2]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S4>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[3]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S5>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[4]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S6>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[5]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S7>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[6]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S8>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[7]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S9>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[8]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S10>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[9]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S11>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[10]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S12>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[11]; }
 };

template <>
struct TypeSet::IsStruct<TypeDefCore::S13>
 {
  static bool Do(const ulen *indexes,ulen index) { return index==indexes[12]; }
 };

