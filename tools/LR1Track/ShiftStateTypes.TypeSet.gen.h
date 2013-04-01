/* struct TypeSet */

struct TypeSet : TypeDefCore , DDL::MapHackPtr
 {
  ulen indexes[8];
  DynArray<ulen> ind_map;

  DDL::FindNodeMap map;

  explicit TypeSet(ulen len)
   : ind_map(len)
   {
    Range(indexes).set(ulen(-1));

    map.add(1,"Transition","ShiftState");
    map.add(2,"ShiftState");
    map.add(3,"Transition","State");
    map.add(4,"State");
    map.add(5,"Action","Final");
    map.add(6,"Final");
    map.add(7,"Rule");
    map.add(8,"Element");

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
                              "element",offsetof(S1,element),
                              "state",offsetof(S1,state)
                             );
        }
       return ret;

       case 2 :
        {
         indexes[1]=struct_node->index;
         ind_map[struct_node->index]=2;

         ret.set<S2>();

         DDL::SetFieldOffsets(struct_node,
                              "state",offsetof(S2,state),
                              "transitions",offsetof(S2,transitions),
                              "states",offsetof(S2,states),
                              "finals",offsetof(S2,finals),
                              "shift",offsetof(S2,shift)
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
                              "state",offsetof(S4,state),
                              "transitions",offsetof(S4,transitions),
                              "final",offsetof(S4,final)
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
                              "rule",offsetof(S5,rule)
                             );
        }
       return ret;

       case 6 :
        {
         indexes[5]=struct_node->index;
         ind_map[struct_node->index]=6;

         ret.set<S6>();

         DDL::SetFieldOffsets(struct_node,
                              "final",offsetof(S6,final),
                              "actions",offsetof(S6,actions)
                             );
        }
       return ret;

       case 7 :
        {
         indexes[6]=struct_node->index;
         ind_map[struct_node->index]=7;

         ret.set<S7>();

         DDL::SetFieldOffsets(struct_node,
                              "rule",offsetof(S7,rule),
                              "name",offsetof(S7,name),
                              "result",offsetof(S7,result),
                              "args",offsetof(S7,args)
                             );
        }
       return ret;

       case 8 :
        {
         indexes[7]=struct_node->index;
         ind_map[struct_node->index]=8;

         ret.set<S8>();

         DDL::SetFieldOffsets(struct_node,
                              "element",offsetof(S8,element),
                              "name",offsetof(S8,name),
                              "rules",offsetof(S8,rules)
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
                              S8 *,
                              S2 *
                             >(*this,type_check,struct_node);
        }
       break;

       case 2 :
        {
         DDL::GuardFieldTypes<
                              A1,
                              PtrLen<S1 >,
                              PtrLen<S4 * >,
                              PtrLen<S6 * >,
                              PtrLen<S8 * >
                             >(*this,type_check,struct_node);
        }
       break;

       case 3 :
        {
         DDL::GuardFieldTypes<
                              S8 *,
                              S4 *
                             >(*this,type_check,struct_node);
        }
       break;

       case 4 :
        {
         DDL::GuardFieldTypes<
                              A1,
                              PtrLen<S3 >,
                              S6 *
                             >(*this,type_check,struct_node);
        }
       break;

       case 5 :
        {
         DDL::GuardFieldTypes<
                              S8 *,
                              S7 *
                             >(*this,type_check,struct_node);
        }
       break;

       case 6 :
        {
         DDL::GuardFieldTypes<
                              A2,
                              PtrLen<S5 >
                             >(*this,type_check,struct_node);
        }
       break;

       case 7 :
        {
         DDL::GuardFieldTypes<
                              A3,
                              StrLen,
                              S8 *,
                              PtrLen<S8 * >
                             >(*this,type_check,struct_node);
        }
       break;

       case 8 :
        {
         DDL::GuardFieldTypes<
                              A4,
                              StrLen,
                              PtrLen<S7 * >
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

