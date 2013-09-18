AtomClass Atom::GetWordClass(StrLen str)
 {
  if( !str ) return Atom_Name;

  switch( str[0] )
    {
     case 'c' :
      {
       ++str;

       if( str.len==4 && str[0]=='o' && str[1]=='n' && str[2]=='s' && str[3]=='t' ) return Atom_const; else return Atom_Name;
      }

     case 'i' :
      {
       ++str;

       if( !str ) return Atom_Name;

       switch( str[0] )
         {
          case 'n' :
           {
            ++str;

            if( !str ) return Atom_Name;

            switch( str[0] )
              {
               case 'c' :
                {
                 ++str;

                 if( str.len==4 && str[0]=='l' && str[1]=='u' && str[2]=='d' && str[3]=='e' ) return Atom_include; else return Atom_Name;
                }

               case 't' :
                {
                 ++str;

                 if( str.len==0 ) return Atom_int; else return Atom_Name;
                }

               default: return Atom_Name;
              }
           }

          case 'p' :
           {
            ++str;

            if( str.len==0 ) return Atom_ip; else return Atom_Name;
           }

          default: return Atom_Name;
         }
      }

     case 'n' :
      {
       ++str;

       if( str.len==3 && str[0]=='u' && str[1]=='l' && str[2]=='l' ) return Atom_null; else return Atom_Name;
      }

     case 's' :
      {
       ++str;

       if( !str ) return Atom_Name;

       switch( str[0] )
         {
          case 'c' :
           {
            ++str;

            if( str.len==3 && str[0]=='o' && str[1]=='p' && str[2]=='e' ) return Atom_scope; else return Atom_Name;
           }

          case 'i' :
           {
            ++str;

            if( !str ) return Atom_Name;

            switch( str[0] )
              {
               case 'n' :
                {
                 ++str;

                 if( !str ) return Atom_Name;

                 switch( str[0] )
                   {
                    case 't' :
                     {
                      ++str;

                      if( !str ) return Atom_sint;

                      switch( str[0] )
                        {
                         case '1' :
                          {
                           ++str;

                           if( str.len==1 && str[0]=='6' ) return Atom_sint16; else return Atom_Name;
                          }

                         case '3' :
                          {
                           ++str;

                           if( str.len==1 && str[0]=='2' ) return Atom_sint32; else return Atom_Name;
                          }

                         case '6' :
                          {
                           ++str;

                           if( str.len==1 && str[0]=='4' ) return Atom_sint64; else return Atom_Name;
                          }

                         case '8' :
                          {
                           ++str;

                           if( str.len==0 ) return Atom_sint8; else return Atom_Name;
                          }

                         default: return Atom_Name;
                        }
                     }

                    default: return Atom_Name;
                   }
                }

               default: return Atom_Name;
              }
           }

          case 't' :
           {
            ++str;

            if( str.len==4 && str[0]=='r' && str[1]=='u' && str[2]=='c' && str[3]=='t' ) return Atom_struct; else return Atom_Name;
           }

          default: return Atom_Name;
         }
      }

     case 't' :
      {
       ++str;

       if( !str ) return Atom_Name;

       switch( str[0] )
         {
          case 'e' :
           {
            ++str;

            if( str.len==2 && str[0]=='x' && str[1]=='t' ) return Atom_text; else return Atom_Name;
           }

          case 'y' :
           {
            ++str;

            if( str.len==2 && str[0]=='p' && str[1]=='e' ) return Atom_type; else return Atom_Name;
           }

          default: return Atom_Name;
         }
      }

     case 'u' :
      {
       ++str;

       if( !str ) return Atom_Name;

       switch( str[0] )
         {
          case 'i' :
           {
            ++str;

            if( !str ) return Atom_Name;

            switch( str[0] )
              {
               case 'n' :
                {
                 ++str;

                 if( !str ) return Atom_Name;

                 switch( str[0] )
                   {
                    case 't' :
                     {
                      ++str;

                      if( !str ) return Atom_uint;

                      switch( str[0] )
                        {
                         case '1' :
                          {
                           ++str;

                           if( str.len==1 && str[0]=='6' ) return Atom_uint16; else return Atom_Name;
                          }

                         case '3' :
                          {
                           ++str;

                           if( str.len==1 && str[0]=='2' ) return Atom_uint32; else return Atom_Name;
                          }

                         case '6' :
                          {
                           ++str;

                           if( str.len==1 && str[0]=='4' ) return Atom_uint64; else return Atom_Name;
                          }

                         case '8' :
                          {
                           ++str;

                           if( str.len==0 ) return Atom_uint8; else return Atom_Name;
                          }

                         default: return Atom_Name;
                        }
                     }

                    default: return Atom_Name;
                   }
                }

               default: return Atom_Name;
              }
           }

          case 'l' :
           {
            ++str;

            if( str.len==2 && str[0]=='e' && str[1]=='n' ) return Atom_ulen; else return Atom_Name;
           }

          default: return Atom_Name;
         }
      }

     default: return Atom_Name;
    }
 }

