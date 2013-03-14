/* struct TypeSet */

struct TypeSet : TypeDefCore , DDL::MapHackPtr
 {
  ulen indexes[6];

  TypeSet() { Range(indexes).set(ulen(-1)); }

  DDL::MapSizeInfo structSizeInfo(DDL::StructNode *struct_node)
   {
    DDL::MapSizeInfo ret;

    if( DDL::HasName(struct_node,"NonTerminal") )
      {
       indexes[0]=struct_node->index;

       ret.set<S1>();

       DDL::SetFieldOffsets(struct_node,
                            "nt",offsetof(S1,nt),
                            "name",offsetof(S1,name),
                            "rules",offsetof(S1,rules)
                           );

       return ret;
      }

    if( DDL::HasName(struct_node,"Rule") )
      {
       indexes[1]=struct_node->index;

       ret.set<S2>();

       DDL::SetFieldOffsets(struct_node,
                            "rule",offsetof(S2,rule),
                            "name",offsetof(S2,name),
                            "result",offsetof(S2,result),
                            "str",offsetof(S2,str)
                           );

       return ret;
      }

    if( DDL::HasName(struct_node,"Transition","State") )
      {
       indexes[2]=struct_node->index;

       ret.set<S3>();

       DDL::SetFieldOffsets(struct_node,
                            "ntt",offsetof(S3,ntt),
                            "state",offsetof(S3,state)
                           );

       return ret;
      }

    if( DDL::HasName(struct_node,"State") )
      {
       indexes[3]=struct_node->index;

       ret.set<S4>();

       DDL::SetFieldOffsets(struct_node,
                            "state",offsetof(S4,state),
                            "transitions",offsetof(S4,transitions),
                            "final",offsetof(S4,final)
                           );

       return ret;
      }

    if( DDL::HasName(struct_node,"Action","Final") )
      {
       indexes[4]=struct_node->index;

       ret.set<S5>();

       DDL::SetFieldOffsets(struct_node,
                            "t",offsetof(S5,t),
                            "rule",offsetof(S5,rule)
                           );

       return ret;
      }

    if( DDL::HasName(struct_node,"Final") )
      {
       indexes[5]=struct_node->index;

       ret.set<S6>();

       DDL::SetFieldOffsets(struct_node,
                            "final",offsetof(S6,final),
                            "actions",offsetof(S6,actions)
                           );

       return ret;
      }

    Printf(Exception,"Unknown structure");

    return ret;
   }

  template <class T> struct IsStruct;

  template <class T>
  bool isStruct(DDL::StructNode *struct_node) const { return IsStruct<T>::Do(indexes,struct_node->index); }

  void guardFieldTypes(DDL::MapTypeCheck &type_check,DDL::StructNode *struct_node) const
   {
    if( struct_node->index==indexes[0] )
      {
       DDL::GuardFieldTypes<
                            A4,
                            StrLen,
                            PtrLen<S2 * >
                           >(*this,type_check,struct_node);
      }

    if( struct_node->index==indexes[1] )
      {
       DDL::GuardFieldTypes<
                            A6,
                            StrLen,
                            A4,
                            PtrLen<A3 >
                           >(*this,type_check,struct_node);
      }

    if( struct_node->index==indexes[2] )
      {
       DDL::GuardFieldTypes<
                            A3,
                            S4 *
                           >(*this,type_check,struct_node);
      }

    if( struct_node->index==indexes[3] )
      {
       DDL::GuardFieldTypes<
                            A2,
                            PtrLen<S3 >,
                            S6 *
                           >(*this,type_check,struct_node);
      }

    if( struct_node->index==indexes[4] )
      {
       DDL::GuardFieldTypes<
                            A5,
                            S2 *
                           >(*this,type_check,struct_node);
      }

    if( struct_node->index==indexes[5] )
      {
       DDL::GuardFieldTypes<
                            A1,
                            PtrLen<S5 >
                           >(*this,type_check,struct_node);
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

