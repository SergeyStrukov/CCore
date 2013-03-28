/* struct TypeSet */

struct TypeSet : TypeDefCore , DDL::MapHackPtr
 {
  ulen indexes[6];
  DynArray<ulen> ind_map;

  DDL::FindNodeMap map;

  explicit TypeSet(ulen len)
   : ind_map(len)
   {
    Range(indexes).set(ulen(-1));

    map.add(1,"Transition","State");
    map.add(2,"State");
    map.add(3,"Action","Final");
    map.add(4,"Final");
    map.add(5,"Rule");
    map.add(6,"Element");

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
                              "final",offsetof(S2,final)
                             );
        }
       return ret;

       case 3 :
        {
         indexes[2]=struct_node->index;
         ind_map[struct_node->index]=3;

         ret.set<S3>();

         DDL::SetFieldOffsets(struct_node,
                              "atom",offsetof(S3,atom),
                              "rule",offsetof(S3,rule)
                             );
        }
       return ret;

       case 4 :
        {
         indexes[3]=struct_node->index;
         ind_map[struct_node->index]=4;

         ret.set<S4>();

         DDL::SetFieldOffsets(struct_node,
                              "final",offsetof(S4,final),
                              "actions",offsetof(S4,actions)
                             );
        }
       return ret;

       case 5 :
        {
         indexes[4]=struct_node->index;
         ind_map[struct_node->index]=5;

         ret.set<S5>();

         DDL::SetFieldOffsets(struct_node,
                              "rule",offsetof(S5,rule),
                              "name",offsetof(S5,name),
                              "result",offsetof(S5,result),
                              "args",offsetof(S5,args)
                             );
        }
       return ret;

       case 6 :
        {
         indexes[5]=struct_node->index;
         ind_map[struct_node->index]=6;

         ret.set<S6>();

         DDL::SetFieldOffsets(struct_node,
                              "element",offsetof(S6,element),
                              "name",offsetof(S6,name),
                              "rules",offsetof(S6,rules)
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
                              S6 *,
                              S2 *
                             >(*this,type_check,struct_node);
        }
       break;

       case 2 :
        {
         DDL::GuardFieldTypes<
                              A1,
                              PtrLen<S1 >,
                              S4 *
                             >(*this,type_check,struct_node);
        }
       break;

       case 3 :
        {
         DDL::GuardFieldTypes<
                              S6 *,
                              S5 *
                             >(*this,type_check,struct_node);
        }
       break;

       case 4 :
        {
         DDL::GuardFieldTypes<
                              A2,
                              PtrLen<S3 >
                             >(*this,type_check,struct_node);
        }
       break;

       case 5 :
        {
         DDL::GuardFieldTypes<
                              A3,
                              StrLen,
                              S6 *,
                              PtrLen<S6 * >
                             >(*this,type_check,struct_node);
        }
       break;

       case 6 :
        {
         DDL::GuardFieldTypes<
                              A4,
                              StrLen,
                              PtrLen<S5 * >
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

