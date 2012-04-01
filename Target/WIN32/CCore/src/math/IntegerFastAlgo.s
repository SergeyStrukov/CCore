# IntegerFastAlgo.s
#-----------------------------------------------------------------------------------------
#
#  Project: CCore 1.02
#
#  Tag: Target/WIN32
#
#  License: Boost Software License - Version 1.0 - August 17th, 2003 
#
#            see http://www.boost.org/LICENSE_1_0.txt or the local copy
#
#  Copyright (c) 2011 Sergey Strukov. All rights reserved.
#
#-----------------------------------------------------------------------------------------

        .text
        
#-----------------------------------------------------------------------------------------

        .global __ZN5CCore4Math15IntegerFastAlgo12CountZeroMSBEj
         
        .p2align 4,,15

__ZN5CCore4Math15IntegerFastAlgo12CountZeroMSBEj:       #  unsigned CCore::Math::IntegerFastAlgo::CountZeroMSB(Unit a)

        pushl   %ebp
        movl    %esp, %ebp
        
        movl    8(%ebp), %eax       # a
        
        testl   %eax, %eax
        je      1f
         
        bsrl    %eax, %eax
        subl    $31, %eax 
        negl    %eax 
        
        popl    %ebp
        ret
        
1:        
        movl    $32, %eax 

        popl    %ebp
        ret

#-----------------------------------------------------------------------------------------

        .global __ZN5CCore4Math15IntegerFastAlgo12CountZeroLSBEj
         
        .p2align 4,,15

__ZN5CCore4Math15IntegerFastAlgo12CountZeroLSBEj:       #  unsigned CCore::Math::IntegerFastAlgo::CountZeroLSB(Unit a)

        pushl   %ebp
        movl    %esp, %ebp
        
        movl    8(%ebp), %eax       # a
        
        testl   %eax, %eax
        je      1f
         
        bsfl    %eax, %eax
        
        popl    %ebp
        ret
        
1:        
        movl    $32, %eax 

        popl    %ebp
        ret

#-----------------------------------------------------------------------------------------

        .global __ZN5CCore4Math15IntegerFastAlgo10DoubleUDivEjjj
         
        .p2align 4,,15

__ZN5CCore4Math15IntegerFastAlgo10DoubleUDivEjjj:       #  Unit CCore::Math::IntegerFastAlgo::DoubleUDiv(Unit hi,Unit lo,Unit den)  

        pushl   %ebp
        movl    %esp, %ebp
        
        movl     8(%ebp), %edx      # hi
        movl    12(%ebp), %eax      # lo
        
        divl    16(%ebp)            # den
        
        popl    %ebp
        ret

#-----------------------------------------------------------------------------------------

        .global __ZN5CCore4Math15IntegerFastAlgo4UAddEPjPKjj
         
        .p2align 4,,15

__ZN5CCore4Math15IntegerFastAlgo4UAddEPjPKjj:           #  Unit CCore::Math::IntegerFastAlgo::UAdd(Unit *restrict b,const Unit *a,ulen nab)  

        pushl   %ebp
        movl    %esp, %ebp
        
        pushl   %ebx
        pushl   %edi
        
        movl     8(%ebp), %edi      # b
        movl    12(%ebp), %edx      # a
        subl        %edi, %edx  
        movl    16(%ebp), %ecx      # nab

        shrl    $1, %ecx
        jnc     2f
        
        shrl    $1, %ecx
        jnc     1f
        
        # 3
        
        movl     (%edi), %eax
        movl    4(%edi), %ebx
      
        addl     (%edi,%edx), %eax 
        adcl    4(%edi,%edx), %ebx
        
        movl    %eax,  (%edi)
        movl    %ebx, 4(%edi)
        
        movl    8(%edi), %eax
        
        adcl    8(%edi,%edx), %eax
        
        movl    %eax, 8(%edi)
        
        leal    12(%edi), %edi
        
        jmp     4f
1:        
        # 1
            
        movl    (%edi), %eax
        
        addl    (%edi,%edx), %eax
         
        movl    %eax,  (%edi)
        
        leal    4(%edi), %edi
            
        jmp     4f
2:        
        shrl    $1, %ecx
        jnc     4f
        
        # 2
        
        movl     (%edi), %eax
        movl    4(%edi), %ebx
      
        addl     (%edi,%edx), %eax 
        adcl    4(%edi,%edx), %ebx
        
        movl    %eax,  (%edi)
        movl    %ebx, 4(%edi)
        
        leal    8(%edi), %edi
4:
        jecxz   6f
5:
        movl     (%edi), %eax
        movl    4(%edi), %ebx
      
        adcl     (%edi,%edx), %eax 
        adcl    4(%edi,%edx), %ebx
        
        movl    %eax,  (%edi)
        movl    %ebx, 4(%edi)
        
        movl     8(%edi), %eax
        movl    12(%edi), %ebx
      
        adcl     8(%edi,%edx), %eax 
        adcl    12(%edi,%edx), %ebx
        
        movl    %eax,  8(%edi)
        movl    %ebx, 12(%edi)
        
        leal    16(%edi), %edi    
        
        loop    5b
6:        
        sbbl    %eax, %eax
        negl    %eax 
        
        popl    %edi
        popl    %ebx
        
        popl    %ebp
        ret

#-----------------------------------------------------------------------------------------

        .global __ZN5CCore4Math15IntegerFastAlgo4USubEPjPKjj
         
        .p2align 4,,15

__ZN5CCore4Math15IntegerFastAlgo4USubEPjPKjj:           #  Unit CCore::Math::IntegerFastAlgo::USub(Unit *restrict b,const Unit *a,ulen nab)  

        pushl   %ebp
        movl    %esp, %ebp
        
        pushl   %ebx
        pushl   %edi
        
        movl     8(%ebp), %edi      # b
        movl    12(%ebp), %edx      # a
        subl        %edi, %edx  
        movl    16(%ebp), %ecx      # nab

        shrl    $1, %ecx
        jnc     2f
        
        shrl    $1, %ecx
        jnc     1f
        
        # 3
        
        movl     (%edi), %eax
        movl    4(%edi), %ebx
      
        subl     (%edi,%edx), %eax 
        sbbl    4(%edi,%edx), %ebx
        
        movl    %eax,  (%edi)
        movl    %ebx, 4(%edi)
        
        movl    8(%edi), %eax
        
        sbbl    8(%edi,%edx), %eax
        
        movl    %eax, 8(%edi)
        
        leal    12(%edi), %edi
        
        jmp     4f
1:        
        # 1
            
        movl    (%edi), %eax
        
        subl    (%edi,%edx), %eax
         
        movl    %eax,  (%edi)
        
        leal    4(%edi), %edi
            
        jmp     4f
2:        
        shrl    $1, %ecx
        jnc     4f
        
        # 2
        
        movl     (%edi), %eax
        movl    4(%edi), %ebx
      
        subl     (%edi,%edx), %eax 
        sbbl    4(%edi,%edx), %ebx
        
        movl    %eax,  (%edi)
        movl    %ebx, 4(%edi)
        
        leal    8(%edi), %edi
4:
        jecxz   6f
5:
        movl     (%edi), %eax
        movl    4(%edi), %ebx
      
        sbbl     (%edi,%edx), %eax 
        sbbl    4(%edi,%edx), %ebx
        
        movl    %eax,  (%edi)
        movl    %ebx, 4(%edi)
        
        movl     8(%edi), %eax
        movl    12(%edi), %ebx
      
        sbbl     8(%edi,%edx), %eax 
        sbbl    12(%edi,%edx), %ebx
        
        movl    %eax,  8(%edi)
        movl    %ebx, 12(%edi)
        
        leal    16(%edi), %edi    
        
        loop    5b
6:        
        sbbl    %eax, %eax
        negl    %eax 
        
        popl    %edi
        popl    %ebx
        
        popl    %ebp
        ret
        
#-----------------------------------------------------------------------------------------

        .global __ZN5CCore4Math15IntegerFastAlgo7URevSubEPjPKjj 
         
        .p2align 4,,15

__ZN5CCore4Math15IntegerFastAlgo7URevSubEPjPKjj:        #  Unit CCore::Math::IntegerFastAlgo::URevSub(Unit *restrict b,const Unit *a,ulen nab)  

        pushl   %ebp
        movl    %esp, %ebp
        
        pushl   %ebx
        pushl   %edi
        
        movl     8(%ebp), %edi      # b
        movl    12(%ebp), %edx      # a
        subl        %edi, %edx  
        movl    16(%ebp), %ecx      # nab

        shrl    $1, %ecx
        jnc     2f
        
        shrl    $1, %ecx
        jnc     1f
        
        # 3
        
        movl     (%edi,%edx), %eax
        movl    4(%edi,%edx), %ebx
      
        subl     (%edi), %eax 
        sbbl    4(%edi), %ebx
        
        movl    %eax,  (%edi)
        movl    %ebx, 4(%edi)
        
        movl    8(%edi,%edx), %eax
        
        sbbl    8(%edi), %eax
        
        movl    %eax, 8(%edi)
        
        leal    12(%edi), %edi
        
        jmp     4f
1:        
        # 1
            
        movl    (%edi,%edx), %eax
        
        subl    (%edi), %eax
         
        movl    %eax,  (%edi)
        
        leal    4(%edi), %edi
            
        jmp     4f
2:        
        shrl    $1, %ecx
        jnc     4f
        
        # 2
        
        movl     (%edi,%edx), %eax
        movl    4(%edi,%edx), %ebx
      
        subl     (%edi), %eax 
        sbbl    4(%edi), %ebx
        
        movl    %eax,  (%edi)
        movl    %ebx, 4(%edi)
        
        leal    8(%edi), %edi
4:
        jecxz   6f
5:
        movl     (%edi,%edx), %eax
        movl    4(%edi,%edx), %ebx
      
        sbbl     (%edi), %eax 
        sbbl    4(%edi), %ebx
        
        movl    %eax,  (%edi)
        movl    %ebx, 4(%edi)
        
        movl     8(%edi,%edx), %eax
        movl    12(%edi,%edx), %ebx
      
        sbbl     8(%edi), %eax 
        sbbl    12(%edi), %ebx
        
        movl    %eax,  8(%edi)
        movl    %ebx, 12(%edi)
        
        leal    16(%edi), %edi    
        
        loop    5b
6:        
        sbbl    %eax, %eax
        negl    %eax 
        
        popl    %edi
        popl    %ebx
        
        popl    %ebp
        ret
        
#-----------------------------------------------------------------------------------------

        .global __ZN5CCore4Math15IntegerFastAlgo7ULShiftEPjjj
         
        .p2align 4,,15

__ZN5CCore4Math15IntegerFastAlgo7ULShiftEPjjj:          #  Unit CCore::Math::IntegerFastAlgo::ULShift(Unit *a,ulen na,unsigned shift)  

        pushl   %ebp
        movl    %esp, %ebp
        
        movl    12(%ebp), %edx      # na
        
        testl   %edx, %edx
        je      4f
        
        pushl   %ebx
        pushl   %esi
        pushl   %edi
        
        movl     8(%ebp), %ebx      # a
        movl    16(%ebp), %ecx      # shift
        
        movl    (%ebx), %esi
        movl    %esi, %eax
        shll    %cl, %esi 
        movl    %esi, (%ebx)
        
        subl    $1, %edx
        je      3f  
        
        shrl    $1, %edx
        jnc     1f
        
        movl    4(%ebx), %esi
        movl    %esi, %edi
        shld    %cl, %eax, %esi
        movl    %esi, 4(%ebx)
        
        movl    %edi, %eax
        leal    4(%ebx), %ebx
1:
        test    %edx, %edx
        je      3f
2:        
        movl    4(%ebx), %esi
        movl    %esi, %edi
        shld    %cl, %eax, %esi
        movl    %esi, 4(%ebx)
        
        movl    8(%ebx), %esi
        movl    %esi, %eax         
        shld    %cl, %edi, %esi
        movl    %esi, 8(%ebx)
        
        leal    8(%ebx), %ebx
        
        subl    $1, %edx  
        jne     2b 
3:
        shld    %cl, %eax, %edx
        movl    %edx, %eax
        
        popl    %edi 
        popl    %esi
        popl    %ebx
        
        popl    %ebp
        ret
4:        
        xorl    %eax, %eax 

        popl    %ebp
        ret
        
#-----------------------------------------------------------------------------------------

        .global __ZN5CCore4Math15IntegerFastAlgo6LShiftEPjPKjjj
         
        .p2align 4,,15

__ZN5CCore4Math15IntegerFastAlgo6LShiftEPjPKjjj:        #  Unit CCore::Math::IntegerFastAlgo::LShift(Unit *restrict b,const Unit *a,ulen nab,unsigned shift)  

        pushl   %ebp
        movl    %esp, %ebp
        
        movl    16(%ebp), %edx      # nab
        
        testl   %edx, %edx
        je      4f
        
        pushl   %ebx
        pushl   %esi
        pushl   %edi
        
        movl     8(%ebp), %ebx      # b
        movl    12(%ebp), %edi      # a
        subl    %ebx, %edi
        movl    20(%ebp), %ecx      # shift
        
        movl    (%ebx,%edi), %esi
        movl    %esi, %eax
        shll    %cl, %esi
        movl    %esi, (%ebx)
        
        subl    $1, %edx
        je      3f
        
        shrl    $1, %edx
        jnc     1f

        movl    4(%ebx,%edi), %esi
        movl    %esi, %ebp
        shld    %cl, %eax, %esi       
        movl    %esi, 4(%ebx)
        
        movl    %ebp, %eax        
        leal    4(%ebx), %ebx
1:
        testl   %edx, %edx
        je      3f
2:                          
        movl    4(%ebx,%edi), %esi
        movl    %esi, %ebp
        shld    %cl, %eax, %esi       
        movl    %esi, 4(%ebx)

        movl    8(%ebx,%edi), %esi
        movl    %esi, %eax
        shld    %cl, %ebp, %esi       
        movl    %esi, 8(%ebx)
        
        leal    8(%ebx), %ebx
        
        subl    $1, %edx
        jne     2b
3:        
        cdq     
        shld    %cl, %eax, %edx
        movl    %edx, %eax
                
        popl    %edi
        popl    %esi        
        popl    %ebx
        
        popl    %ebp
        ret
4:
        xorl    %eax, %eax
        
        popl    %ebp
        ret
        
#-----------------------------------------------------------------------------------------

        .global __ZN5CCore4Math15IntegerFastAlgo8UShiftUpEPjjjj
         
        .p2align 4,,15

__ZN5CCore4Math15IntegerFastAlgo8UShiftUpEPjjjj:        #  Unit CCore::Math::IntegerFastAlgo::UShiftUp(Unit *a,ulen na,ulen delta,unsigned shift)  

        pushl   %ebp
        movl    %esp, %ebp
        
        movl    12(%ebp), %edx      # na
        
        testl   %edx, %edx
        je      6f
        
        pushl   %ebx
        pushl   %esi
        pushl   %edi
        
        movl     8(%ebp), %ebx      # a
        movl    16(%ebp), %edi      # delta
        movl    20(%ebp), %ecx      # shift
        shll    $2, %edi
        
        leal    -4(%ebx,%edx,4), %ebx
        
        shrl    $1, %edx
        jnc     1f
        je      5f

        movl    (%ebx), %esi
        push    %esi 
        
        movl    -4(%ebx), %eax
        shld    %cl, %eax, %esi
        movl    %esi, (%ebx,%edi)
        leal    -4(%ebx), %ebx        
                
        jmp     2f        
1:
        movl    (%ebx), %eax
        push    %eax
2:         
        subl    $1, %edx 
        je      4f
3:
        movl    -4(%ebx), %esi
        shld    %cl, %esi, %eax
        movl    %eax, (%ebx,%edi)        
        
        movl    -8(%ebx), %eax
        shld    %cl, %eax, %esi
        movl    %esi, -4(%ebx,%edi)

        leal    -8(%ebx), %ebx        
        subl    $1, %edx
        
        jne     3b
4:
        movl    -4(%ebx), %esi
        shld    %cl, %esi, %eax
        movl    %eax, (%ebx,%edi)        
        
        shll    %cl, %esi
        movl    %esi, -4(%ebx,%edi)

        popl    %eax  
        xorl    %edx, %edx     
        shld    %cl, %eax, %edx
        movl    %edx, %eax
        
        popl    %edi
        popl    %esi        
        popl    %ebx
        
        popl    %ebp
        ret
5:
        movl    (%ebx), %eax
        xorl    %edx, %edx     
        shld    %cl, %eax, %edx
        shll    %cl, %eax
        movl    %eax, (%ebx,%edi)
        movl    %edx, %eax
 
        popl    %edi
        popl    %esi        
        popl    %ebx
        
        popl    %ebp
        ret
6:
        xorl    %eax, %eax
        
        popl    %ebp
        ret

#-----------------------------------------------------------------------------------------

        .global __ZN5CCore4Math15IntegerFastAlgo7ShiftUpEPjjjj
         
        .p2align 4,,15

__ZN5CCore4Math15IntegerFastAlgo7ShiftUpEPjjjj:         #  Unit CCore::Math::IntegerFastAlgo::ShiftUp(Unit *a,ulen na,ulen delta,unsigned shift)  

        pushl   %ebp
        movl    %esp, %ebp
        
        movl    12(%ebp), %edx      # na
        
        testl   %edx, %edx
        je      6f
        
        pushl   %ebx
        pushl   %esi
        pushl   %edi
        
        movl     8(%ebp), %ebx      # a
        movl    16(%ebp), %edi      # delta
        movl    20(%ebp), %ecx      # shift
        shll    $2, %edi
        
        leal    -4(%ebx,%edx,4), %ebx
        
        shrl    $1, %edx
        jnc     1f
        je      5f

        movl    (%ebx), %esi
        push    %esi 
        
        movl    -4(%ebx), %eax
        shld    %cl, %eax, %esi
        movl    %esi, (%ebx,%edi)
        leal    -4(%ebx), %ebx        
                
        jmp     2f        
1:
        movl    (%ebx), %eax
        push    %eax
2:         
        subl    $1, %edx 
        je      4f
3:
        movl    -4(%ebx), %esi
        shld    %cl, %esi, %eax
        movl    %eax, (%ebx,%edi)        
        
        movl    -8(%ebx), %eax
        shld    %cl, %eax, %esi
        movl    %esi, -4(%ebx,%edi)

        leal    -8(%ebx), %ebx        
        subl    $1, %edx
        
        jne     3b
4:
        movl    -4(%ebx), %esi
        shld    %cl, %esi, %eax
        movl    %eax, (%ebx,%edi)        
        
        shll    %cl, %esi
        movl    %esi, -4(%ebx,%edi)

        popl    %eax  
        cdq     
        shld    %cl, %eax, %edx
        movl    %edx, %eax
        
        popl    %edi
        popl    %esi        
        popl    %ebx
        
        popl    %ebp
        ret
5:
        movl    (%ebx), %eax
        cdq
        shld    %cl, %eax, %edx
        shll    %cl, %eax
        movl    %eax, (%ebx,%edi)
        movl    %edx, %eax
 
        popl    %edi
        popl    %esi        
        popl    %ebx
        
        popl    %ebp
        ret
6:
        xorl    %eax, %eax
        
        popl    %ebp
        ret

#-----------------------------------------------------------------------------------------

        .global __ZN5CCore4Math15IntegerFastAlgo7URShiftEPjjj
         
        .p2align 4,,15

__ZN5CCore4Math15IntegerFastAlgo7URShiftEPjjj:          #  void CCore::Math::IntegerFastAlgo::URShift(Unit *a,ulen na,unsigned shift) 

        pushl   %ebp
        movl    %esp, %ebp
        
        movl    12(%ebp), %edx      # na
        testl   %edx, %edx
        je      3f
        
        pushl   %ebx
        pushl   %esi
        pushl   %edi
        
        movl     8(%ebp), %ebx      # a
        movl    16(%ebp), %ecx      # shift
        
        movl    (%ebx), %eax
        
        subl    $1, %edx
        je      2f
                
        shrl    $1, %edx    
        jnc     1f
        
        movl    4(%ebx), %esi
        shrd    %cl, %esi, %eax
        movl    %eax, (%ebx)
        movl    %esi, %eax
        leal    4(%ebx), %ebx
        
        testl   %edx, %edx
        je      2f
1:        
        movl    4(%ebx), %esi
        movl    8(%ebx), %edi
        shrd    %cl, %esi, %eax
        movl    %eax, (%ebx)
        shrd    %cl, %edi, %esi
        movl    %edi, %eax        
        movl    %esi, 4(%ebx)
        
        leal    8(%ebx), %ebx
        subl    $1, %edx
        
        jne     1b 
2:        
        shrl    %cl, %eax
        movl    %eax, (%ebx)
        
        popl    %edi
        popl    %esi        
        popl    %ebx
3:        
        popl    %ebp
        ret

#-----------------------------------------------------------------------------------------

        .global __ZN5CCore4Math15IntegerFastAlgo6RShiftEPjPKjjj
         
        .p2align 4,,15

__ZN5CCore4Math15IntegerFastAlgo6RShiftEPjPKjjj:        #  void CCore::Math::IntegerFastAlgo::RShift(Unit *restrict b,const Unit *a,ulen nab,unsigned shift)  

        pushl   %ebp
        movl    %esp, %ebp
        
        movl    16(%ebp), %edx      # nab
        
        testl   %edx, %edx
        je      4f
        
        pushl   %ebx
        pushl   %esi
        pushl   %edi
        
        movl     8(%ebp), %ebx      # b
        movl    12(%ebp), %edi      # a
        subl    %ebx, %edi
        movl    20(%ebp), %ecx      # shift
RShift:
        movl    (%ebx,%edi), %eax
        
        subl    $1, %edx
        je      3f

        shrl    $1, %edx
        jnc     1f
        
        movl    4(%ebx,%edi), %esi        
        shrd    %cl, %esi, %eax
        movl    %eax, (%ebx)
        movl    %esi, %eax
  
        leal    4(%ebx), %ebx
1:
        testl   %edx, %edx
        je      3f
2:
        movl    4(%ebx,%edi), %esi        
        shrd    %cl, %esi, %eax
        movl    %eax, (%ebx)
  
        movl    8(%ebx,%edi), %eax        
        shrd    %cl, %eax, %esi
        movl    %esi, 4(%ebx)
  
        leal    8(%ebx), %ebx
        
        subl    $1, %edx
        jne     2b        
3:                
        sarl    %cl, %eax
        movl    %eax, (%ebx)
        
        popl    %edi
        popl    %esi        
        popl    %ebx
        
        popl    %ebp
        ret
4:
        popl    %ebp
        ret

#-----------------------------------------------------------------------------------------

        .global __ZN5CCore4Math15IntegerFastAlgo10UShiftDownEPjjjj
         
        .p2align 4,,15

__ZN5CCore4Math15IntegerFastAlgo10UShiftDownEPjjjj:     #  void CCore::Math::IntegerFastAlgo::UShiftDown(Unit *a,ulen na,ulen delta,unsigned shift)  

        pushl   %ebp
        movl    %esp, %ebp
        
        movl    12(%ebp), %edx      # na
        
        testl   %edx, %edx
        je      4f
        
        pushl   %ebx
        pushl   %esi
        pushl   %edi
        
        movl     8(%ebp), %ebx      # a
        movl    16(%ebp), %edi      # delta
        movl    20(%ebp), %ecx      # shift
        shll    $2, %edi
        
        movl    (%ebx,%edi), %eax
        
        subl    $1, %edx
        je      3f

        shrl    $1, %edx
        jnc     1f
        
        movl    4(%ebx,%edi), %esi        
        shrd    %cl, %esi, %eax
        movl    %eax, (%ebx)
        movl    %esi, %eax
  
        leal    4(%ebx), %ebx
1:
        testl   %edx, %edx
        je      3f
2:
        movl    4(%ebx,%edi), %esi        
        shrd    %cl, %esi, %eax
        movl    %eax, (%ebx)
  
        movl    8(%ebx,%edi), %eax        
        shrd    %cl, %eax, %esi
        movl    %esi, 4(%ebx)
  
        leal    8(%ebx), %ebx
        
        subl    $1, %edx
        jne     2b        
3:                
        shrl    %cl, %eax
        movl    %eax, (%ebx)
        
        popl    %edi
        popl    %esi        
        popl    %ebx
        
        popl    %ebp
        ret
4:
        popl    %ebp
        ret

#-----------------------------------------------------------------------------------------

        .global __ZN5CCore4Math15IntegerFastAlgo9ShiftDownEPjjjj
         
        .p2align 4,,15

__ZN5CCore4Math15IntegerFastAlgo9ShiftDownEPjjjj:       #  void CCore::Math::IntegerFastAlgo::ShiftDown(Unit *a,ulen na,ulen delta,unsigned shift)  

        pushl   %ebp
        movl    %esp, %ebp
        
        movl    12(%ebp), %edx      # na
        
        testl   %edx, %edx
        je      4f
        
        pushl   %ebx
        pushl   %esi
        pushl   %edi
        
        movl     8(%ebp), %ebx      # a
        movl    16(%ebp), %edi      # delta
        movl    20(%ebp), %ecx      # shift
        shll    $2, %edi
        
        jmp     RShift
4:
        popl    %ebp
        ret

#-----------------------------------------------------------------------------------------

        .global __ZN5CCore4Math15IntegerFastAlgo7RawUMulEPjPKjjS4_j
         
        .p2align 4,,15

__ZN5CCore4Math15IntegerFastAlgo7RawUMulEPjPKjjS4_j:    #  void CCore::Math::IntegerFastAlgo::RawUMul(Unit *restrict c,const Unit *a,ulen na,const Unit *b,ulen nb)

        pushl   %ebp
        movl    %esp, %ebp

        #         
        #   8(%ebp)  c
        #  12(%ebp)  a
        #  16(%ebp)  na
        #  20(%ebp)  b
        #  24(%ebp)  nb
        #
        
        pushl   %ebx
        pushl   %esi
        pushl   %edi
        
        subl    $20, %esp
        
        #
        #  -16(%ebp) acc2
        #  -20(%ebp) acc1
        #  -24(%ebp) acc0
        #  -28(%ebp) k
        #  -32(%ebp) na-1
        #  

        movl     8(%ebp), %ebx
        
        movl    12(%ebp), %esi
        movl    20(%ebp), %edi
        
        movl    (%esi), %eax
        mull    (%edi)
        
        movl    %eax, (%ebx)
        leal    4(%ebx), %ebx
        
        movl    %edx, -24(%ebp)
        movl    $0, -20(%ebp)
        movl    $0, -16(%ebp)
        
        movl    $1, %ecx
1:
        movl    12(%ebp), %esi
        movl    20(%ebp), %edi
        
        leal    (%edi,%ecx,4), %edi
        addl    $1, %ecx
        movl    %ecx, -28(%ebp)
9:
        movl    (%esi), %eax
        leal     4(%esi), %esi
        mull    (%edi) 
        leal    -4(%edi), %edi
        addl    %eax, -24(%ebp)
        adcl    %edx, -20(%ebp)
        adcl    $0,   -16(%ebp)
        
        loop    9b
        
        movl    -24(%ebp), %eax
        movl    -20(%ebp), %edx
        movl    -16(%ebp), %ecx
        movl    %eax, (%ebx)
        leal    4(%ebx), %ebx
        movl    %edx, -24(%ebp)
        movl    %ecx, -20(%ebp) 
        movl    $0,   -16(%ebp)
        
        movl    -28(%ebp), %ecx
        cmpl    %ecx, 16(%ebp)
        jne     1b  
       
        cmpl    %ecx, 24(%ebp)
        je      3f 
2:
        movl    12(%ebp), %esi
        movl    20(%ebp), %edi
        
        leal    (%edi,%ecx,4), %edi
        addl    $1, %ecx
        movl    %ecx, -28(%ebp)
        movl    16(%ebp), %ecx        
9:
        movl    (%esi), %eax
        leal     4(%esi), %esi
        mull    (%edi) 
        leal    -4(%edi), %edi
        addl    %eax, -24(%ebp)
        adcl    %edx, -20(%ebp)
        adcl    $0,   -16(%ebp)
        
        loop    9b
        
        movl    -24(%ebp), %eax
        movl    -20(%ebp), %edx
        movl    -16(%ebp), %ecx
        movl    %eax, (%ebx)
        leal    4(%ebx), %ebx
        movl    %edx, -24(%ebp)
        movl    %ecx, -20(%ebp) 
        movl    $0,   -16(%ebp)
        
        movl    -28(%ebp), %ecx
        cmpl    %ecx, 24(%ebp)
        jne     2b  
3:
        movl    20(%ebp), %edi
        leal    -4(%edi,%ecx,4), %edi
        movl    %edi, 20(%ebp)         

        movl    16(%ebp), %eax
        subl    $1, %eax
        movl    %eax, -32(%ebp)
        movl    $1, %ecx

        cmpl    %ecx, %eax        
        je      5f
4:
        movl    12(%ebp), %esi
        movl    20(%ebp), %edi

        leal    (%esi,%ecx,4), %esi
        addl    $1, %ecx
        movl    %ecx, -28(%ebp)
        subl    $1, %ecx   
        subl    16(%ebp), %ecx 
        neg     %ecx    
9:
        movl    (%esi), %eax
        leal     4(%esi), %esi
        mull    (%edi) 
        leal    -4(%edi), %edi
        addl    %eax, -24(%ebp)
        adcl    %edx, -20(%ebp)
        adcl    $0,   -16(%ebp)
        
        loop    9b
        
        movl    -24(%ebp), %eax
        movl    -20(%ebp), %edx
        movl    -16(%ebp), %ecx
        movl    %eax, (%ebx)
        leal    4(%ebx), %ebx
        movl    %edx, -24(%ebp)
        movl    %ecx, -20(%ebp) 
        movl    $0,   -16(%ebp)
        
        movl    -28(%ebp), %ecx
        cmpl    %ecx, -32(%ebp)        
        jne     4b
5:        
        movl    12(%ebp), %esi
        movl    20(%ebp), %edi

        movl    (%edi), %eax
        leal    (%esi,%ecx,4), %esi
        mull    (%esi) 
        addl    -24(%ebp), %eax 
        adcl    -20(%ebp), %edx 

        movl    %eax,  (%ebx)
        movl    %edx, 4(%ebx)
 
        addl    $20, %esp
        
        popl    %edi
        popl    %esi        
        popl    %ebx
        
        popl    %ebp
        ret

#-----------------------------------------------------------------------------------------

        .global __ZN5CCore4Math15IntegerFastAlgo8RawUMul1EPjjPKjj
         
        .p2align 4,,15

__ZN5CCore4Math15IntegerFastAlgo8RawUMul1EPjjPKjj:      #  void CCore::Math::IntegerFastAlgo::RawUMul1(Unit *restrict c,Unit a,const Unit *b,ulen nb)  

        pushl   %ebp
        movl    %esp, %ebp
        
        pushl   %ebx
        pushl   %esi
        pushl   %edi
        
        movl     8(%ebp), %ebx      # c
        movl    12(%ebp), %edi      # a
        movl    16(%ebp), %esi      # b
        movl    20(%ebp), %ecx      # nb
        
UMul1:        
        movl    %edi, %ebp
        
        movl    (%esi), %eax
        mull    %ebp
        movl    %eax, (%ebx)
        movl    %edx, %edi
        leal    4(%ebx), %ebx
        subl    $1, %ecx
1:
        movl    4(%esi), %eax
        leal    4(%esi), %esi
        mull    %ebp
        add     %edi, %eax
        adc     $0, %edx
        movl    %eax, (%ebx)
        movl    %edx, %edi
        leal    4(%ebx), %ebx
        
        loop    1b
        
        movl    %edi, (%ebx)             
        
        popl    %edi
        popl    %esi        
        popl    %ebx
        
        popl    %ebp
        ret

#-----------------------------------------------------------------------------------------

        .global __ZN5CCore4Math15IntegerFastAlgo9RawUMul11EPjjj
         
        .p2align 4,,15

__ZN5CCore4Math15IntegerFastAlgo9RawUMul11EPjjj:        #  void CCore::Math::IntegerFastAlgo::RawUMul11(Unit *c,Unit a,Unit b)  

        pushl   %ebp
        movl    %esp, %ebp
        
        movl     8(%ebp), %ecx      # c
        movl    12(%ebp), %eax      # a
        mull    16(%ebp)            # b
        
        movl    %eax,  (%ecx)     
        movl    %edx, 4(%ecx)     
        
        popl    %ebp
        ret

#-----------------------------------------------------------------------------------------

        .global __ZN5CCore4Math15IntegerFastAlgo7RawUMacEPjPKjjS4_jj
         
        .p2align 4,,15

__ZN5CCore4Math15IntegerFastAlgo7RawUMacEPjPKjjS4_jj:   #  Unit CCore::Math::IntegerFastAlgo::RawUMac(Unit *restrict c,const Unit *a,ulen na,const Unit *b,ulen nb,Unit carry)  

        pushl   %ebp
        movl    %esp, %ebp
        
        #         
        #   8(%ebp)  c
        #  12(%ebp)  a
        #  16(%ebp)  na
        #  20(%ebp)  b
        #  24(%ebp)  nb
        #  28(%ebp)  carry
        #
        
        pushl   %ebx
        pushl   %esi
        pushl   %edi
        
        subl    $20, %esp
        
        #
        #  -16(%ebp) acc2
        #  -20(%ebp) acc1
        #  -24(%ebp) acc0
        #  -28(%ebp) k
        #  -32(%ebp) na-1
        #  

        movl     8(%ebp), %ebx
        
        movl    12(%ebp), %esi
        movl    20(%ebp), %edi
        
        movl    (%esi), %eax
        mull    (%edi)
        
        btl     $0, 28(%ebp)
        adcl    %eax, (%ebx)
        setc    28(%ebp)
        
        leal    4(%ebx), %ebx
        
        movl    %edx, -24(%ebp)
        movl    $0, -20(%ebp)
        movl    $0, -16(%ebp)
        
        movl    $1, %ecx
1:
        movl    12(%ebp), %esi
        movl    20(%ebp), %edi
        
        leal    (%edi,%ecx,4), %edi
        addl    $1, %ecx
        movl    %ecx, -28(%ebp)
9:
        movl    (%esi), %eax
        leal     4(%esi), %esi
        mull    (%edi) 
        leal    -4(%edi), %edi
        addl    %eax, -24(%ebp)
        adcl    %edx, -20(%ebp)
        adcl    $0,   -16(%ebp)
        
        loop    9b
        
        movl    -24(%ebp), %eax
        movl    -20(%ebp), %edx
        movl    -16(%ebp), %ecx
        
        btl     $0, 28(%ebp)
        adcl    %eax, (%ebx)
        setc    28(%ebp)
        
        leal    4(%ebx), %ebx
        movl    %edx, -24(%ebp)
        movl    %ecx, -20(%ebp) 
        movl    $0,   -16(%ebp)
        
        movl    -28(%ebp), %ecx
        cmpl    %ecx, 16(%ebp)
        jne     1b  
       
        cmpl    %ecx, 24(%ebp)
        je      3f 
2:
        movl    12(%ebp), %esi
        movl    20(%ebp), %edi
        
        leal    (%edi,%ecx,4), %edi
        addl    $1, %ecx
        movl    %ecx, -28(%ebp)
        movl    16(%ebp), %ecx        
9:
        movl    (%esi), %eax
        leal     4(%esi), %esi
        mull    (%edi) 
        leal    -4(%edi), %edi
        addl    %eax, -24(%ebp)
        adcl    %edx, -20(%ebp)
        adcl    $0,   -16(%ebp)
        
        loop    9b
        
        movl    -24(%ebp), %eax
        movl    -20(%ebp), %edx
        movl    -16(%ebp), %ecx
        
        btl     $0, 28(%ebp)
        adcl    %eax, (%ebx)
        setc    28(%ebp)
        
        leal    4(%ebx), %ebx
        movl    %edx, -24(%ebp)
        movl    %ecx, -20(%ebp) 
        movl    $0,   -16(%ebp)
        
        movl    -28(%ebp), %ecx
        cmpl    %ecx, 24(%ebp)
        jne     2b  
3:
        movl    20(%ebp), %edi
        leal    -4(%edi,%ecx,4), %edi
        movl    %edi, 20(%ebp)         

        movl    16(%ebp), %eax
        subl    $1, %eax
        movl    %eax, -32(%ebp)
        movl    $1, %ecx

        cmpl    %ecx, %eax        
        je      5f
4:
        movl    12(%ebp), %esi
        movl    20(%ebp), %edi

        leal    (%esi,%ecx,4), %esi
        addl    $1, %ecx
        movl    %ecx, -28(%ebp)
        subl    $1, %ecx   
        subl    16(%ebp), %ecx 
        neg     %ecx    
9:
        movl    (%esi), %eax
        leal     4(%esi), %esi
        mull    (%edi) 
        leal    -4(%edi), %edi
        addl    %eax, -24(%ebp)
        adcl    %edx, -20(%ebp)
        adcl    $0,   -16(%ebp)
        
        loop    9b
        
        movl    -24(%ebp), %eax
        movl    -20(%ebp), %edx
        movl    -16(%ebp), %ecx
        
        btl     $0, 28(%ebp)
        adcl    %eax, (%ebx)
        setc    28(%ebp)
        
        leal    4(%ebx), %ebx
        movl    %edx, -24(%ebp)
        movl    %ecx, -20(%ebp) 
        movl    $0,   -16(%ebp)
        
        movl    -28(%ebp), %ecx
        cmpl    %ecx, -32(%ebp)        
        jne     4b
5:        
        movl    12(%ebp), %esi
        movl    20(%ebp), %edi

        movl    (%edi), %eax
        leal    (%esi,%ecx,4), %esi
        mull    (%esi) 
        addl    -24(%ebp), %eax 
        adcl    -20(%ebp), %edx 

        btl     $0, 28(%ebp)
        adcl    %eax, (%ebx)
        adcl    %edx, 4(%ebx)
        sbbl    %eax, %eax
        negl    %eax   
 
        addl    $20, %esp
        
        popl    %edi
        popl    %esi        
        popl    %ebx
        
        popl    %ebp
        ret

#-----------------------------------------------------------------------------------------

        .global __ZN5CCore4Math15IntegerFastAlgo8RawUMac1EPjjPKjjj
         
        .p2align 4,,15

__ZN5CCore4Math15IntegerFastAlgo8RawUMac1EPjjPKjjj:     #  Unit CCore::Math::IntegerFastAlgo::RawUMac1(Unit *restrict c,Unit a,const Unit *b,ulen nb,Unit carry)  

        pushl   %ebp
        movl    %esp, %ebp
        
        pushl   %ebx
        pushl   %esi
        pushl   %edi
        
        movl     8(%ebp), %ebx      # c
        movl    12(%ebp), %edi      # a
        movl    16(%ebp), %esi      # b
        movl    20(%ebp), %ecx      # nb
        
        #
        #  36(%esp) carry
        #
        
        movl    %edi, %ebp
        
        movl    (%esi), %eax
        mull    %ebp
        
        btl     $0, 36(%esp) 
        adcl    %eax, (%ebx)
        setc    36(%esp)
        
        movl    %edx, %edi
        leal    4(%ebx), %ebx
        subl    $1, %ecx
1:
        movl    4(%esi), %eax
        leal    4(%esi), %esi
        mull    %ebp
        add     %edi, %eax
        adc     $0, %edx
        
        btl     $0, 36(%esp) 
        adcl    %eax, (%ebx)
        setc    36(%esp)
        
        movl    %edx, %edi
        leal    4(%ebx), %ebx
        
        loop    1b
        
        btl     $0, 36(%esp) 
        adcl    %edi, (%ebx)
        sbbl    %eax, %eax
        negl    %eax             
        
        popl    %edi
        popl    %esi        
        popl    %ebx
        
        popl    %ebp
        ret

#-----------------------------------------------------------------------------------------

        .global __ZN5CCore4Math15IntegerFastAlgo9RawUMac11EPjjjj
         
        .p2align 4,,15

__ZN5CCore4Math15IntegerFastAlgo9RawUMac11EPjjjj:       #  Unit CCore::Math::IntegerFastAlgo::RawUMac11(Unit *c,Unit a,Unit b,Unit carry)  

        pushl   %ebp
        movl    %esp, %ebp
        
        movl     8(%ebp), %ecx      # c
        movl    12(%ebp), %eax      # a
        mull    16(%ebp)            # b

        btl     $0, 20(%ebp)
        adcl    %eax,  (%ecx)     
        adcl    %edx, 4(%ecx)
        
        sbbl    %eax, %eax
        negl    %eax
             
        popl    %ebp
        ret

#-----------------------------------------------------------------------------------------

        .global __ZN5CCore4Math15IntegerFastAlgo9RawUMulLoEPjjPKjjS4_j
         
        .p2align 4,,15

__ZN5CCore4Math15IntegerFastAlgo9RawUMulLoEPjjPKjjS4_j: #  void CCore::Math::IntegerFastAlgo::RawUMulLo(Unit *restrict c,ulen nc,const Unit *a,ulen na,const Unit *b,ulen nb)  

        pushl   %ebp
        movl    %esp, %ebp


        #         
        #   8(%ebp)  c
        #  12(%ebp)  nc
        #  16(%ebp)  a
        #  20(%ebp)  na
        #  24(%ebp)  b
        #  28(%ebp)  nb
        #
        
        pushl   %ebx
        pushl   %esi
        pushl   %edi
        
        subl    $20, %esp
        
        #
        #  -16(%ebp) acc2
        #  -20(%ebp) acc1
        #  -24(%ebp) acc0
        #  -28(%ebp) k
        #  -32(%ebp) na-1
        #  

        movl     8(%ebp), %ebx
        
        movl    16(%ebp), %esi
        movl    24(%ebp), %edi
        
        movl    (%esi), %eax
        mull    (%edi)
        
        movl    %eax, (%ebx)
        subl    $1, 12(%ebp)
        je      6f
        leal    4(%ebx), %ebx
        
        movl    %edx, -24(%ebp)
        movl    $0, -20(%ebp)
        movl    $0, -16(%ebp)
        
        movl    $1, %ecx
1:
        movl    16(%ebp), %esi
        movl    24(%ebp), %edi
        
        leal    (%edi,%ecx,4), %edi
        addl    $1, %ecx
        movl    %ecx, -28(%ebp)
9:
        movl    (%esi), %eax
        leal     4(%esi), %esi
        mull    (%edi) 
        leal    -4(%edi), %edi
        addl    %eax, -24(%ebp)
        adcl    %edx, -20(%ebp)
        adcl    $0,   -16(%ebp)
        
        loop    9b
        
        movl    -24(%ebp), %eax
        movl    -20(%ebp), %edx
        movl    -16(%ebp), %ecx
        movl    %eax, (%ebx)
        subl    $1, 12(%ebp)
        je      6f
        leal    4(%ebx), %ebx
        movl    %edx, -24(%ebp)
        movl    %ecx, -20(%ebp) 
        movl    $0,   -16(%ebp)
        
        movl    -28(%ebp), %ecx
        cmpl    %ecx, 20(%ebp)
        jne     1b  
       
        cmpl    %ecx, 28(%ebp)
        je      3f 
2:
        movl    16(%ebp), %esi
        movl    24(%ebp), %edi
        
        leal    (%edi,%ecx,4), %edi
        addl    $1, %ecx
        movl    %ecx, -28(%ebp)
        movl    20(%ebp), %ecx        
9:
        movl    (%esi), %eax
        leal     4(%esi), %esi
        mull    (%edi) 
        leal    -4(%edi), %edi
        addl    %eax, -24(%ebp)
        adcl    %edx, -20(%ebp)
        adcl    $0,   -16(%ebp)
        
        loop    9b
        
        movl    -24(%ebp), %eax
        movl    -20(%ebp), %edx
        movl    -16(%ebp), %ecx
        movl    %eax, (%ebx)
        subl    $1, 12(%ebp)
        je      6f
        leal    4(%ebx), %ebx
        movl    %edx, -24(%ebp)
        movl    %ecx, -20(%ebp) 
        movl    $0,   -16(%ebp)
        
        movl    -28(%ebp), %ecx
        cmpl    %ecx, 28(%ebp)
        jne     2b  
3:
        movl    24(%ebp), %edi
        leal    -4(%edi,%ecx,4), %edi
        movl    %edi, 24(%ebp)         

        movl    20(%ebp), %eax
        subl    $1, %eax
        movl    %eax, -32(%ebp)
        movl    $1, %ecx

        cmpl    %ecx, %eax        
        je      5f
4:
        movl    16(%ebp), %esi
        movl    24(%ebp), %edi

        leal    (%esi,%ecx,4), %esi
        addl    $1, %ecx
        movl    %ecx, -28(%ebp)
        subl    $1, %ecx   
        subl    20(%ebp), %ecx 
        neg     %ecx    
9:
        movl    (%esi), %eax
        leal     4(%esi), %esi
        mull    (%edi) 
        leal    -4(%edi), %edi
        addl    %eax, -24(%ebp)
        adcl    %edx, -20(%ebp)
        adcl    $0,   -16(%ebp)
        
        loop    9b
        
        movl    -24(%ebp), %eax
        movl    -20(%ebp), %edx
        movl    -16(%ebp), %ecx
        movl    %eax, (%ebx)
        subl    $1, 12(%ebp)
        je      6f
        leal    4(%ebx), %ebx
        movl    %edx, -24(%ebp)
        movl    %ecx, -20(%ebp) 
        movl    $0,   -16(%ebp)
        
        movl    -28(%ebp), %ecx
        cmpl    %ecx, -32(%ebp)        
        jne     4b
5:        
        movl    16(%ebp), %esi
        movl    24(%ebp), %edi

        movl    (%edi), %eax
        leal    (%esi,%ecx,4), %esi
        mull    (%esi) 
        addl    -24(%ebp), %eax 
        adcl    -20(%ebp), %edx 

        movl    %eax,  (%ebx)
        subl    $1, 12(%ebp)
        je      6f
        movl    %edx, 4(%ebx)
6: 
        addl    $20, %esp
        
        popl    %edi
        popl    %esi        
        popl    %ebx
        
        popl    %ebp
        ret

#-----------------------------------------------------------------------------------------

        .global __ZN5CCore4Math15IntegerFastAlgo10RawUMulLo1EPjjjPKjj
         
        .p2align 4,,15

__ZN5CCore4Math15IntegerFastAlgo10RawUMulLo1EPjjjPKjj:  #  void CCore::Math::IntegerFastAlgo::RawUMulLo1(Unit *restrict c,ulen nc,Unit a,const Unit *b,ulen nb)  

        pushl   %ebp
        movl    %esp, %ebp
        
        pushl   %ebx
        pushl   %esi
        pushl   %edi
        
        movl     8(%ebp), %ebx      # c
        movl    12(%ebp), %ecx      # nc
        movl    16(%ebp), %edi      # a
        movl    20(%ebp), %esi      # b
        
        subl    $1, %ecx
        cmpl    %ecx, 24(%ebp)      # nb
        je      UMul1
        
        movl    %edi, %ebp
        
        movl    (%esi), %eax
        mull    %ebp
        movl    %eax, (%ebx)
        movl    %edx, %edi
        leal    4(%ebx), %ebx
        jecxz   2f
1:
        movl    4(%esi), %eax
        leal    4(%esi), %esi
        mull    %ebp
        add     %edi, %eax
        adc     $0, %edx
        movl    %eax, (%ebx)
        movl    %edx, %edi
        leal    4(%ebx), %ebx
        
        loop    1b
2:        
        popl    %edi
        popl    %esi        
        popl    %ebx
        
        popl    %ebp
        ret

#-----------------------------------------------------------------------------------------

        .global __ZN5CCore4Math15IntegerFastAlgo11RawUMulLo11EPjjjj
         
        .p2align 4,,15

__ZN5CCore4Math15IntegerFastAlgo11RawUMulLo11EPjjjj:    #  void CCore::Math::IntegerFastAlgo::RawUMulLo11(Unit *c,ulen nc,Unit a,Unit b)  

        pushl   %ebp
        movl    %esp, %ebp
        
        movl     8(%ebp), %ecx      # c
        movl    16(%ebp), %eax      # a
        mull    20(%ebp)            # b
        
        movl    %eax,  (%ecx)
        
        cmpl    $1, 12(%ebp)
        je      1f
            
        movl    %edx, 4(%ecx)     
1:        
        popl    %ebp
        ret

#-----------------------------------------------------------------------------------------

        .global __ZN5CCore4Math15IntegerFastAlgo6RawUSqEPjPKjj
         
        .p2align 4,,15

__ZN5CCore4Math15IntegerFastAlgo6RawUSqEPjPKjj:         #  void CCore::Math::IntegerFastAlgo::RawUSq(Unit *restrict c,const Unit *a,ulen na)

        pushl   %ebp
        movl    %esp, %ebp
        
        pushl   %ebx
        pushl   %esi
        pushl   %edi
        
        movl    12(%ebp), %eax      # a
        leal    4(%eax), %ebx
        
        pushl   %ebx
        
        movl    16(%ebp), %ebx      # na
        leal    -4(%eax,%ebx,4), %ebx
        
        pushl   %ebx
        
        #
        # 28(%esp)  c
        # 32(%esp)  a  
        # 36(%esp)  na
        #  4(%esp)  p
        #   (%esp)  end 
        #
        
        movl    (%eax), %eax
        movl    28(%esp), %esi
        mull    %eax
        movl    %eax, (%esi)
        leal    4(%esi), %esi
        movl    %esi, 28(%esp)
        movl    %edx, %ecx
        xorl    %ebx, %ebx
        xorl    %ebp, %ebp   
        
        movl    32(%esp), %esi
        movl     4(%esp), %edi  
9:        
        movl    (%esi), %eax
        leal     4(%esi), %esi
        mull    (%edi)
        leal    -4(%edi), %edi
        
        shld    $1, %eax, %edx
        adcl    $0, %ebp                 
        shll    $1, %eax

        addl    %eax, %ecx 
        adcl    %edx, %ebx 
        adcl    $0, %ebp
        
        cmpl    %esi, %edi
        ja      9b
        jb      8f
        
        movl    (%esi), %eax
        mull    %eax
               
        addl    %eax, %ecx 
        adcl    %edx, %ebx 
        adcl    $0, %ebp
8:       
        movl    28(%esp), %eax
        movl    %ecx, (%eax)
        leal    4(%eax), %eax
        movl    %eax, 28(%esp)
        movl    %ebx, %ecx
        movl    %ebp, %ebx
        xorl    %ebp, %ebp
              
        movl    32(%esp), %esi
        movl     4(%esp), %edi
        cmpl    %edi, (%esp)
        je      1f
        
        leal    4(%edi), %edi
        movl    %edi, 4(%esp)
        
        jmp     9b  
1:
        movl    32(%esp), %esi
2:        
        leal     4(%esi), %esi
        movl     %esi, 4(%esp)
        movl    (%esp), %edi
        cmpl    %esi, %edi
        je      3f
9:        
        movl    (%esi), %eax
        leal     4(%esi), %esi
        mull    (%edi)
        leal    -4(%edi), %edi
        
        shld    $1, %eax, %edx
        adcl    $0, %ebp                 
        shll    $1, %eax

        addl    %eax, %ecx 
        adcl    %edx, %ebx 
        adcl    $0, %ebp
        
        cmpl    %esi, %edi
        ja      9b
        jb      8f
        
        movl    (%esi), %eax
        mull    %eax
               
        addl    %eax, %ecx 
        adcl    %edx, %ebx 
        adcl    $0, %ebp
8:       
        movl    28(%esp), %eax
        movl    %ecx, (%eax)
        leal    4(%eax), %eax
        movl    %eax, 28(%esp)
        movl    %ebx, %ecx
        movl    %ebp, %ebx
        xorl    %ebp, %ebp
        
        movl    4(%esp), %esi
        jmp     2b 
3:        
        movl    (%esi), %eax
        movl    28(%esp), %edi
        mull    %eax
         
        addl    %eax, %ecx 
        adcl    %edx, %ebx 
        
        movl    %ecx, (%edi)          
        movl    %ebx, 4(%edi)
        
        add     $8, %esp          
        
        popl    %edi
        popl    %esi        
        popl    %ebx
        
        popl    %ebp
        ret

#-----------------------------------------------------------------------------------------

        .global __ZN5CCore4Math15IntegerFastAlgo7RawUSq1EPjj 
         
        .p2align 4,,15

__ZN5CCore4Math15IntegerFastAlgo7RawUSq1EPjj:           #  void CCore::Math::IntegerFastAlgo::RawUSq1(Unit *c,Unit a)  

        pushl   %ebp
        movl    %esp, %ebp
        
        movl     8(%ebp), %ecx      # c
        movl    12(%ebp), %eax      # a
        mull    %eax
        
        movl    %eax,  (%ecx)     
        movl    %edx, 4(%ecx)
             
        popl    %ebp
        ret

#-----------------------------------------------------------------------------------------

        .global __ZN5CCore4Math14IntegerExtAlgo5UNeg3EPj
         
        .p2align 4,,15

__ZN5CCore4Math14IntegerExtAlgo5UNeg3EPj:               #  void CCore::Math::IntegerExtAlgo::UNeg3(Unit *a)  

        pushl   %ebp
        movl    %esp, %ebp

        movl    8(%ebp), %ecx       # a
        
        xorl    %eax, %eax
        xorl    %edx, %edx
        negl    (%ecx)
        
        sbbl    4(%ecx), %eax
        movl    %eax, 4(%ecx)
        
        sbbl    8(%ecx), %edx
        movl    %edx, 8(%ecx)
        
        popl    %ebp
        ret

#-----------------------------------------------------------------------------------------

        .global __ZN5CCore4Math14IntegerExtAlgo5UAdd3EPjPKj
         
        .p2align 4,,15

__ZN5CCore4Math14IntegerExtAlgo5UAdd3EPjPKj:            #  Unit CCore::Math::IntegerExtAlgo::UAdd3(Unit *restrict a,const Unit *b)  

        pushl   %ebp
        movl    %esp, %ebp
        
        movl    12(%ebp), %edx      # b
        movl     8(%ebp), %ecx      # a
        
        movl     (%edx), %eax 
        movl    4(%edx), %ebp
         
        addl    %eax,  (%ecx)
        adcl    %ebp, 4(%ecx)
        
        movl    8(%edx), %eax 
        
        adcl    %eax, 8(%ecx)
        
        sbbl    %eax, %eax
        negl    %eax
        
        popl    %ebp
        ret

#-----------------------------------------------------------------------------------------

        .global __ZN5CCore4Math14IntegerExtAlgo5USub3EPjPKj
         
        .p2align 4,,15

__ZN5CCore4Math14IntegerExtAlgo5USub3EPjPKj:            #  void CCore::Math::IntegerExtAlgo::USub3(Unit *restrict a,const Unit *b)

        pushl   %ebp
        movl    %esp, %ebp
        
        movl    12(%ebp), %edx      # b
        movl     8(%ebp), %ecx      # a
        
        movl     (%edx), %eax 
        movl    4(%edx), %ebp
         
        subl    %eax,  (%ecx)
        sbbl    %ebp, 4(%ecx)
        
        movl    8(%edx), %eax 
        
        sbbl    %eax, 8(%ecx)
        
        popl    %ebp
        ret

#-----------------------------------------------------------------------------------------

        .global __ZN5CCore4Math14IntegerExtAlgo7UMulLo3EPjPKjS4_
         
        .p2align 4,,15

__ZN5CCore4Math14IntegerExtAlgo7UMulLo3EPjPKjS4_:       #  void CCore::Math::IntegerExtAlgo::UMulLo3(Unit *restrict c,const Unit *a,const Unit *b)  

        pushl   %ebp
        movl    %esp, %ebp
        
        pushl   %ebx
        pushl   %esi
        pushl   %edi
        
        movl     8(%ebp), %ecx      # c
        movl    12(%ebp), %esi      # a
        movl    16(%ebp), %edi      # b

        xorl    %ebp, %ebp
        
        # 0

        movl    (%esi), %eax
        mull    (%edi)
        movl    %edx, %ebx
        
        movl    %eax,  (%ecx)
        
        # 1
        
        movl    (%esi), %eax
        mull    4(%edi)
        addl    %eax, %ebx 
        adcl    %edx, %ebp

        movl    4(%esi), %eax
        mull    (%edi)
        addl    %eax, %ebx 
        adcl    %edx, %ebp
        
        movl    %ebx, 4(%ecx)
        
        # 2
        
        movl    (%esi), %eax
        mull    8(%edi)
        addl    %eax, %ebp
        
        movl    4(%esi), %eax
        mull    4(%edi)
        addl    %eax, %ebp
        
        movl    8(%esi), %eax
        mull    (%edi)
        addl    %eax, %ebp
        
        movl    %ebp, 8(%ecx)
        
        popl    %edi
        popl    %esi        
        popl    %ebx
        
        popl    %ebp
        ret

#-----------------------------------------------------------------------------------------

        .global __ZN5CCore4Math14IntegerExtAlgo6USqLo3EPjPKj
         
        .p2align 4,,15

__ZN5CCore4Math14IntegerExtAlgo6USqLo3EPjPKj:           #  void CCore::Math::IntegerExtAlgo::USqLo3(Unit *restrict c,const Unit *a)

        pushl   %ebp
        movl    %esp, %ebp
        
        pushl   %ebx
        pushl   %esi
        pushl   %edi
        
        movl     8(%ebp), %ecx      # c
        movl    12(%ebp), %esi      # a

        xorl    %ebp, %ebp
        movl    (%esi), %edi
        
        # 0

        movl    %edi, %eax
        mull    %edi
        movl    %edx, %ebx
        
        movl    %eax,  (%ecx)
        
        # 1
        
        movl    %edi, %eax
        mull    4(%esi)
        addl    %eax, %ebx 
        adcl    %edx, %ebp
        addl    %eax, %ebx 
        adcl    %edx, %ebp
        
        movl    %ebx, 4(%ecx)
        
        # 2
        
        movl    %edi, %eax
        mull    8(%esi)
        addl    %eax, %ebp
        addl    %eax, %ebp
        
        movl    4(%esi), %eax
        mull    %eax
        addl    %eax, %ebp
        
        movl    %ebp, 8(%ecx)

        popl    %edi
        popl    %esi        
        popl    %ebx
        
        popl    %ebp
        ret

#-----------------------------------------------------------------------------------------

        .global __ZN5CCore4Math14IntegerExtAlgo8URShift3EPjj
         
        .p2align 4,,15

__ZN5CCore4Math14IntegerExtAlgo8URShift3EPjj:           #  void CCore::Math::IntegerExtAlgo::URShift3(Unit *a,unsigned shift)  

        pushl   %ebp
        movl    %esp, %ebp
        
        movl     8(%ebp), %edx      # a
        movl    12(%ebp), %ecx      # shift
        
        movl     (%edx), %eax
        movl    4(%edx), %ebp
        
        shrd    %cl, %ebp, %eax
        movl    %eax, (%edx)
         
        movl    8(%edx), %eax
        
        shrd    %cl, %eax, %ebp
        movl    %ebp, 4(%edx)
        
        shrl    %cl, %eax
        movl    %eax, 8(%edx)
        
        popl    %ebp
        ret

#-----------------------------------------------------------------------------------------

        .global __ZN5CCore4Math14IntegerExtAlgo5UNeg4EPj
         
        .p2align 4,,15

__ZN5CCore4Math14IntegerExtAlgo5UNeg4EPj:               #  void CCore::Math::IntegerExtAlgo::UNeg4(Unit *a)  

        pushl   %ebp
        movl    %esp, %ebp
        
        movl    8(%ebp), %ecx       # a
        
        xorl    %eax, %eax
        xorl    %edx, %edx
        xorl    %ebp, %ebp
        negl    (%ecx)
        
        sbbl    4(%ecx), %eax
        movl    %eax, 4(%ecx)
        
        sbbl    8(%ecx), %edx
        movl    %edx, 8(%ecx)
        
        sbbl    12(%ecx), %ebp
        movl    %ebp, 12(%ecx)
        
        popl    %ebp
        ret

#-----------------------------------------------------------------------------------------

        .global __ZN5CCore4Math14IntegerExtAlgo5UAdd4EPjPKj
         
        .p2align 4,,15

__ZN5CCore4Math14IntegerExtAlgo5UAdd4EPjPKj:            #  Unit CCore::Math::IntegerExtAlgo::UAdd4(Unit *restrict a,const Unit *b)  

        pushl   %ebp
        movl    %esp, %ebp
        
        movl    12(%ebp), %edx      # b
        movl     8(%ebp), %ecx      # a
        
        movl     (%edx), %eax 
        movl    4(%edx), %ebp
         
        addl    %eax,  (%ecx)
        adcl    %ebp, 4(%ecx)
        
        movl     8(%edx), %eax 
        movl    12(%edx), %ebp
        
        adcl    %eax,  8(%ecx)
        adcl    %ebp, 12(%ecx)
        
        sbbl    %eax, %eax
        negl    %eax
        
        popl    %ebp
        ret

#-----------------------------------------------------------------------------------------

        .global __ZN5CCore4Math14IntegerExtAlgo5USub4EPjPKj
         
        .p2align 4,,15

__ZN5CCore4Math14IntegerExtAlgo5USub4EPjPKj:            #  void CCore::Math::IntegerExtAlgo::USub4(Unit *restrict a,const Unit *b)  

        pushl   %ebp
        movl    %esp, %ebp

        movl    12(%ebp), %edx      # b
        movl     8(%ebp), %ecx      # a
        
        movl     (%edx), %eax 
        movl    4(%edx), %ebp
         
        subl    %eax,  (%ecx)
        sbbl    %ebp, 4(%ecx)
        
        movl     8(%edx), %eax 
        movl    12(%edx), %ebp
        
        sbbl    %eax,  8(%ecx)
        sbbl    %ebp, 12(%ecx)
        
        popl    %ebp
        ret

#-----------------------------------------------------------------------------------------

        .global __ZN5CCore4Math14IntegerExtAlgo7UMulLo4EPjPKjS4_
         
        .p2align 4,,15

__ZN5CCore4Math14IntegerExtAlgo7UMulLo4EPjPKjS4_:       #  void CCore::Math::IntegerExtAlgo::UMulLo4(Unit *restrict c,const Unit *a,const Unit *b)  

        pushl   %ebp
        movl    %esp, %ebp

        pushl   %ebx
        pushl   %esi
        pushl   %edi
        
        movl     8(%ebp), %ecx      # c
        movl    12(%ebp), %esi      # a
        movl    16(%ebp), %edi      # b
        
        xorl    %ebx, %ebx
        xorl    %ebp, %ebp
        
        # 0

        movl    (%esi), %eax
        mull    (%edi)
        movl    %eax,  (%ecx)
        movl    %edx, 4(%ecx)
        
        # 1
        
        movl    (%esi), %eax
        mull    4(%edi)
        addl    %eax, 4(%ecx)
        adcl    %edx, %ebx
        adcl    $0, %ebp 

        movl    4(%esi), %eax
        mull    (%edi)
        addl    %eax, 4(%ecx) 
        adcl    %edx, %ebx
        adcl    $0, %ebp 
        
        # 2
        
        movl    (%esi), %eax
        mull    8(%edi)
        addl    %eax, %ebx
        adcl    %edx, %ebp
        
        movl    4(%esi), %eax
        mull    4(%edi)
        addl    %eax, %ebx
        adcl    %edx, %ebp
        
        movl    8(%esi), %eax
        mull    (%edi)
        addl    %eax, %ebx
        adcl    %edx, %ebp
        
        movl    %ebx, 8(%ecx)
        
        # 3
        
        movl    (%esi), %eax
        mull    12(%edi)  
        addl    %eax, %ebp     
        
        movl    4(%esi), %eax
        mull    8(%edi)
        addl    %eax, %ebp     
               
        movl    8(%esi), %eax
        mull    4(%edi)
        addl    %eax, %ebp     
        
        movl    12(%esi), %eax
        mull    (%edi)
        addl    %eax, %ebp
        
        movl    %ebp, 12(%ecx)     
        
        popl    %edi
        popl    %esi        
        popl    %ebx
        
        popl    %ebp
        ret

#-----------------------------------------------------------------------------------------

        .global __ZN5CCore4Math14IntegerExtAlgo6USqLo4EPjPKj
         
        .p2align 4,,15

__ZN5CCore4Math14IntegerExtAlgo6USqLo4EPjPKj:           #  void CCore::Math::IntegerExtAlgo::USqLo4(Unit *restrict c,const Unit *a)  

        pushl   %ebp
        movl    %esp, %ebp
        
        pushl   %ebx
        pushl   %esi
        pushl   %edi
        
        movl     8(%ebp), %ecx      # c
        movl    12(%ebp), %esi      # a
        
        xorl    %ebx, %ebx
        xorl    %ebp, %ebp
        movl    (%esi), %edi
        
        # 0

        movl    %edi, %eax
        mull    %edi
        movl    %eax,  (%ecx)
        movl    %edx, 4(%ecx)
        
        # 1
        
        movl    %edi, %eax
        mull    4(%esi)
        addl    %eax, 4(%ecx)
        adcl    %edx, %ebx
        adcl    $0, %ebp 
        addl    %eax, 4(%ecx) 
        adcl    %edx, %ebx
        adcl    $0, %ebp 
        
        # 2
        
        movl    %edi, %eax
        mull    8(%esi)
        addl    %eax, %ebx
        adcl    %edx, %ebp
        addl    %eax, %ebx
        adcl    %edx, %ebp
        
        movl    4(%esi), %eax
        mull    %eax
        addl    %eax, %ebx
        adcl    %edx, %ebp
        
        movl    %ebx, 8(%ecx)
        
        # 3
        
        movl    %edi, %eax
        mull    12(%esi)  
        addl    %eax, %ebp     
        addl    %eax, %ebp     
        
        movl    4(%esi), %eax
        mull    8(%esi)
        addl    %eax, %ebp     
        addl    %eax, %ebp     
               
        movl    %ebp, 12(%ecx)     
        
        popl    %edi
        popl    %esi        
        popl    %ebx
        
        popl    %ebp
        ret

#-----------------------------------------------------------------------------------------

        .global __ZN5CCore4Math14IntegerExtAlgo8URShift4EPjj
         
        .p2align 4,,15

__ZN5CCore4Math14IntegerExtAlgo8URShift4EPjj:           #  void CCore::Math::IntegerExtAlgo::URShift4(Unit *a,unsigned shift)  

        pushl   %ebp
        movl    %esp, %ebp

        movl     8(%ebp), %edx      # a
        movl    12(%ebp), %ecx      # shift
        
        cmpl    $32, %ecx
        je      1f
        ja      2f 
        
        movl     (%edx), %eax
        movl    4(%edx), %ebp
        
        shrd    %cl, %ebp, %eax
        movl    %eax, (%edx)
         
        movl    8(%edx), %eax
        
        shrd    %cl, %eax, %ebp
        movl    %ebp, 4(%edx)

        movl    12(%edx), %ebp
        
        shrd    %cl, %ebp, %eax
        movl    %eax, 8(%edx)
        
        shrl    %cl, %ebp
        movl    %ebp, 12(%edx)
        
        popl    %ebp
        ret

1:
        movl     4(%edx), %eax
        movl     8(%edx), %ecx
        movl    12(%edx), %ebp
        
        movl    %eax,   (%edx)
        movl    %ecx,  4(%edx)
        movl    %ebp,  8(%edx)
        movl      $0, 12(%edx)

        popl    %ebp
        ret

2:        
        subl    $32, %ecx
        
        movl    4(%edx), %eax
        movl    8(%edx), %ebp
        
        shrd    %cl, %ebp, %eax
        movl    %eax, (%edx)
         
        movl    12(%edx), %eax
        
        shrd    %cl, %eax, %ebp
        movl    %ebp, 4(%edx)

        shrl    %cl, %eax
        movl    %eax, 8(%edx)
        movl      $0, 12(%edx)
        
        popl    %ebp
        ret

#-----------------------------------------------------------------------------------------

#        .global __ZN5CCore4Math15IntegerFastAlgo4NullEPjj
         
        .p2align 4,,15

__ZN5CCore4Math15IntegerFastAlgo4NullEPjj:              #  void CCore::Math::IntegerFastAlgo::Null(Unit *a,ulen na)

        pushl   %ebp
        movl    %esp, %ebp
        
        xorl    %eax, %eax
        movl     8(%ebp), %edx      # a
        movl    12(%ebp), %ecx      # na
        
        shrl    $1, %ecx
        jnc     1f
        
        movl    %eax, (%edx)
        
        leal    4(%edx), %edx           
1:      
        shrl    $1, %ecx
        jnc     2f

        movl    %eax,  (%edx)
        movl    %eax, 4(%edx)
        
        leal    8(%edx), %edx           
2:  
        shrl    $1, %ecx
        jnc     3f
        
        movl    %eax,   (%edx)
        movl    %eax,  4(%edx)
        movl    %eax,  8(%edx)
        movl    %eax, 12(%edx)
        
        leal    16(%edx), %edx           
3:
        jecxz   5f
4:        
        movl    %eax,   (%edx)
        movl    %eax,  4(%edx)
        movl    %eax,  8(%edx)
        movl    %eax, 12(%edx)
        movl    %eax, 16(%edx)
        movl    %eax, 20(%edx)
        movl    %eax, 24(%edx)
        movl    %eax, 28(%edx)
        
        leal    32(%edx), %edx           
        
        loop    4b
5:  
        popl    %ebp
        ret

#-----------------------------------------------------------------------------------------

#        .global SXXX
         
        .p2align 4,,15

SXXX:    #  

        pushl   %ebp
        movl    %esp, %ebp
        
        popl    %ebp
        ret

#-----------------------------------------------------------------------------------------



        
