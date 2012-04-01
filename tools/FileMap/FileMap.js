/* FileMap.js */
//----------------------------------------------------------------------------------------
//
//  Project: FileMap 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2011 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

/* element functions */

function GetElements(tag,cls)
{
 var list=document.getElementsByTagName(tag);
 
 var ret=new Array();
 
 var j=0;
 
 for(var i=0; i<list.length ;i++)
   {
    var item=list.item(i);
    
    if( item.className==cls ) ret[j++]=item; 
   }

 return ret; 
}

function BuildElementList(parent,cls)
{
 var list=parent.childNodes;
 var ret=new Array();
 
 var j=0;
 
 for(var i=0; i<list.length ;i++)
   {
    var item=list[i];
    
    if( item.className==cls ) ret[j++]=item; 
   }
   
 return ret;  
}

function FindElement(parent,cls)
{
 var list=parent.childNodes;
 
 for(var i=0; i<list.length ;i++)
   {
    var item=list[i];
    
    if( item.className==cls ) return item; 
   }
   
 return null;  
}

function BuildDirList(elem_ulist)
{
 var list=elem_ulist.childNodes;
 var ret=new Array();
 
 var j=0;
 
 for(var i=0; i<list.length ;i++)
   {
    var item=FindElement(list[i],"dir_name");
    
    if( item ) ret[j++]=item; 
   }
   
 return ret;  
}

function FindDir(elem_li)
{
 if( elem_li.tagName!="LI" ) return null;

 var dir_id=elem_li.parentNode.id.split("_")[0];

 return document.getElementById(dir_id);
}

function FindList(dir)
{
 return document.getElementById(dir.id+"_list"); 
}

/* Prepare_dir_button() */

function DirOn()
{
 this.custom.flag=true;
 this.innerHTML="&minus;";
    
 this.custom.ulist.style.display="";
}

function DirOff()
{
 this.custom.flag=false;
 this.innerHTML="+";
    
 this.custom.ulist.style.display="none";
}

function Click_dir()
{
 if( this.custom.flag )
   {
    this.dirOff();
   }
 else
   {
    this.dirOn();
   }
}

function Prepare_dir_button(btn)
{
 btn.onclick=Click_dir;
 btn.dirOn=DirOn;
 btn.dirOff=DirOff;
 
 btn.custom=new Object();
 
 btn.custom.flag=true;
 btn.custom.ulist=btn.parentNode.custom.ulist;
}

/* Prepare_dir_button_all() */

function Click_dir_all()
{
 var list=this.parentNode.custom.blist;
 
 for(var i=0; i<list.length ;i++) list[i].dirOn();
}

function Prepare_dir_button_all(btn)
{
 btn.onclick=Click_dir_all;
}

/* Prepare_dir_button_none() */

function Click_dir_none()
{
 var list=this.parentNode.custom.blist;
 
 for(var i=0; i<list.length ;i++) list[i].dirOff();
}

function Prepare_dir_button_none(btn)
{
 btn.onclick=Click_dir_none;
}

/* SetRadio() */

function SetRadio(state)
{
 var cls="G_color";

 if( state==0 )
   cls="R_color";
 else if( state==1 )
   cls="Y_color";

 var btn=FindElement(this,cls);

 btn.checked=true;
}

function SetRadioState(state)
{
 this.custom.state=state;

 this.setCustomRadio(state);
}

/* Prepare_dir_name() */

function SetDirState(state)
{
 if( confirm("Are you sure to make the Global State Reset?") )
   {
    this.updateCustomComplete(state);
    
    this.setCustomStateDown(state);
    
    AspectNotSaved();
   }
 else
   {
    this.setCustomRadio(this.custom.state);
   }
}

function SetDirStateDown(state)
{
 for(var i=0; i<this.custom.flist.length ;i++) 
   {
    var file=this.custom.flist[i];
   
    file.setCustomRadioState(state);
   }

 for(var i=0; i<this.custom.dlist.length ;i++) 
   {
    var dir=this.custom.dlist[i];
   
    dir.setCustomRadioState(state);
    dir.setCustomStateDown(state);
   }
 
 this.custom.state_count[0]=0;
 this.custom.state_count[1]=0;
 this.custom.state_count[2]=0;
 
 this.custom.state_count[state]=this.custom.flist.length+this.custom.dlist.length;
}

function UpdateDirComplete(state)
{
 if( this.custom.state!=state )
   {
    this.setCustomRadio(state);

    var dir=this.custom.dir;

    if( dir!=null ) dir.updateCustomState(this.custom.state,state);

    this.custom.state=state;
   }
}

function UpdateDirState(from,to)
{
 this.custom.state_count[from]--;
 this.custom.state_count[to]++;

 var state=2;

 if( this.custom.state_count[0]!=0 )
   {
    state=0;
   }
 else if( this.custom.state_count[1]!=0 )
   {
    state=1;
   }

 this.updateCustomComplete(state);
}

function BuildButtonList(btn,ulist)
{
 var blist=new Array();
 var j=0;
    
 blist[j++]=btn;
 
 var list=ulist.childNodes;
  
 for(var i=0; i<list.length ;i++)
   {
    var dir=FindElement(list[i],"dir_name");
       
    if( dir!=null )
      {   
       Prepare_dir_name(dir);
       
       var sublist=dir.custom.blist;
             
       if( sublist!=null )
         {
          for(var k=0; k<sublist.length ;k++) blist[j++]=sublist[k];
         }
      }
   }
 
 return blist;     
}

function Prepare_dir_name(dir)
{
 if( dir.custom==null ) 
   {
    dir.custom=new Object();
    
    dir.custom.ulist=FindList(dir);
    
    dir.custom.blist=BuildButtonList(FindElement(dir,"dir_button"),dir.custom.ulist);
    
    dir.custom.flist=BuildElementList(dir.custom.ulist,"file_name");
    dir.custom.dlist=BuildDirList(dir.custom.ulist);

    dir.custom.state=2;
    dir.custom.state_count=new Array(0,0,0);

    dir.custom.dir=FindDir(dir.parentNode);

    dir.setCustomRadio=SetRadio;
    dir.setCustomRadioState=SetRadioState;
    
    dir.setCustomState=SetDirState;
    dir.setCustomStateDown=SetDirStateDown;
    
    dir.updateCustomComplete=UpdateDirComplete;
    dir.updateCustomState=UpdateDirState;
   }
}

/* Prepare_file_name() */

function SetFileState(state)
{
 if( this.custom.state!=state )
   {
    this.custom.dir.updateCustomState(this.custom.state,state);

    this.custom.state=state;
    
    AspectNotSaved();
   }
}

function Prepare_file_name(file)
{
 file.custom=new Object();

 file.custom.state=2;

 file.custom.dir=FindDir(file);

 file.setCustomRadio=SetRadio;
 file.setCustomRadioState=SetRadioState;
 file.setCustomState=SetFileState;
}

/* Prepare_X_color() */

function Click_color()
{
 this.custom.target.setCustomState(this.custom.state);
}

function Prepare_X_color(color,state)
{
 color.onclick=Click_color;

 color.custom=new Object();

 color.custom.state=state;

 var target_id=color.name.split("_")[0];

 color.custom.target=document.getElementById(target_id);
}

/* Prepare() */

function Prepare()
{
 {
  var list=GetElements("li","file_name");
 
  for(var i=0; i<list.length ;i++) Prepare_file_name(list[i]);
 }
 {
  var list=GetElements("h3","dir_name");
 
  for(var i=0; i<list.length ;i++) Prepare_dir_name(list[i]);
 }
 {
  var list=GetElements("input","R_color");

  for(var i=0; i<list.length ;i++) Prepare_X_color(list[i],0);
 }
 {
  var list=GetElements("input","Y_color");
 
  for(var i=0; i<list.length ;i++) Prepare_X_color(list[i],1);
 }
 {
  var list=GetElements("input","G_color");
 
  for(var i=0; i<list.length ;i++) Prepare_X_color(list[i],2);
 }
 {
  var list=GetElements("button","dir_button");
 
  for(var i=0; i<list.length ;i++) Prepare_dir_button(list[i]);
 }
 {
  var list=GetElements("button","dir_button_all");
 
  for(var i=0; i<list.length ;i++) Prepare_dir_button_all(list[i]);
 }
 {
  var list=GetElements("button","dir_button_none");
 
  for(var i=0; i<list.length ;i++) Prepare_dir_button_none(list[i]);
 }
 
 PrepareAspectList();
}

/* ResetState() */

function ResetFileState(file)
{
 file.setCustomRadioState(2);
}

function ResetDirState(dir)
{
 dir.custom.state_count[0]=0;
 dir.custom.state_count[1]=0;
 dir.custom.state_count[2]=0;
 
 dir.setCustomRadioState(2);
}

function ResetState()
{
 {
  var list=GetElements("li","file_name");
 
  for(var i=0; i<list.length ;i++) ResetFileState(list[i]);
 }
 {
  var list=GetElements("h3","dir_name");
 
  for(var i=0; i<list.length ;i++) ResetDirState(list[i]);
 }
}

/* Hide/Show */

function HideGreen()
{
 {
  var list=GetElements("li","file_name");
 
  for(var i=0; i<list.length ;i++) 
    {
     var file=list[i];
     
     if( file.custom.state==2 ) file.style.display="none";
    }
 }
}

function ShowAll()
{
 {
  var list=GetElements("li","file_name");
 
  for(var i=0; i<list.length ;i++) list[i].style.display="";
 }
}

/* Save/Load Aspect */

var FSO=null;
var FileList=null;

function PrepareFSO()
{
 if( FSO==null ) FSO=new ActiveXObject("Scripting.FileSystemObject"); 
}

function PrepareFileList()
{
 if( FileList==null ) FileList=GetFileList();
}

var Aspect=null;
var AspectSaved=true;

function AspectIsSaved()
{
 AspectSaved=true;
 
 if( Aspect!=null )
   {
    var list=GetElements("input","aspect_button_mod");
    
    for(var i=0; i<list.length ;i++)
      if( list[i].value==Aspect )
        list[i].className="aspect_button";
   }

 ShowStat();
}

function AspectNotSaved()
{
 AspectSaved=false;
 
 if( Aspect!=null )
   {
    var list=GetElements("input","aspect_button");
    
    for(var i=0; i<list.length ;i++)
      if( list[i].value==Aspect )
        list[i].className="aspect_button_mod";
   }

 ShowStat();
}

function ProcessFileName()
{
 var str=document.URL;
 
 if( str.slice(0,7)!="file://" ) return null;
 
 str=str.slice(7);
 
 if( str.slice(-5)!=".html" ) return null;
 
 str=str.slice(0,-5);
 
 return str;
}

function GetAspectFileName(aspect)
{
 var str=ProcessFileName();
 
 if( str==null ) 
   {
    alert("Bad document URL: "+document.URL);
   
    return null;
   }
 
 return str+"."+aspect+".txt";
}

function SaveAspect(ask)
{
 if( ask==undefined ) ask=true;

 PrepareFileList();
 PrepareFSO();
 
 if( Aspect==null )
   {
    alert("Aspect is not defined");
    
    return;
   }
   
 if( ask && !confirm("Are you sure to overwrite this aspect?") ) return;  

 var file_name=GetAspectFileName(Aspect);
 
 if( file_name==null ) return;
 
 var file=FSO.CreateTextFile(file_name,true);
 
 if( file==null )
   {
    alert("Cannot open file");
   
    return;
   }
 
 for(var i=0; i<FileList.length ;i++)
   {
    file.WriteLine( "\""+FileList[i]+"\" "+document.getElementById("file"+i).custom.state );
   }

 file.Close();

 AspectIsSaved(); 
}

function StateRec(line)
{
 var from=line.indexOf("\"");
 var to=line.lastIndexOf("\"");

 var name=line.slice(from+1,to);
 var state=Number(line.slice(to+1));

 this.name=name;
 this.is_state=true;
 this.index_state=state;
}

function IndexRec(name,index)
{
 this.name=name;
 this.is_state=false;
 this.index_state=index;
}

function CmpRec(a,b)
{
 if( a.name<b.name ) return -1; 
 if( a.name>b.name ) return 1;
 
 if( a.is_state<b.is_state ) return -1;
 if( a.is_state>b.is_state ) return 1;
 
 return 0; 
}

function LoadFileState(index,state)
{
 var file=document.getElementById("file"+index);
 
 file.setCustomRadio(state);
 file.setCustomState(state);
}

function LoadAspect(ask)
{
 if( ask==undefined ) ask=true;

 PrepareFileList();
 PrepareFSO();
 
 if( Aspect==null )
   {
    alert("Aspect is not defined");
    
    return;
   }

 if( ask && !confirm("Are you sure to load an aspect?") ) return;
   
 var file_name=GetAspectFileName(Aspect);

 if( file_name==null ) return;
   
 if( !FSO.FileExists(file_name) )
   {
    alert("There is no aspect file\nReset state");
    
    ResetState();
   
    return;
   }  

 var file=FSO.OpenTextFile(file_name,1,false);
 
 if( file==null )
   {
    alert("Cannot open file");
   
    return;
   }
   
 ResetState();  
   
 var list=new Array();
 
 var j=0;  

 while( !file.AtEndOfStream )
   {
    var line=file.ReadLine();
    
    list[j++]=new StateRec(line);
   }   
   
 file.Close();
 
 for(var i=0; i<FileList.length ;i++)
   {
    list[j++]=new IndexRec(FileList[i],i);   
   }
   
 list.sort(CmpRec);
 
 {
  var off=0;
  
  while( off<list.length )
    {
     var name=list[off].name;
     
     var next_off=off+1;
     
     for(; next_off<list.length && list[next_off].name==name ;next_off++);
     
     var state=0;
     
     if( list[next_off-1].is_state ) state=list[next_off-1].index_state;
     
     for(var i=off; i<next_off ;i++)
       {
        if( list[i].is_state ) break;
        
        LoadFileState(list[i].index_state,state);
       }
     
     off=next_off;
    }
 }
   
 AspectIsSaved(); 
}

/* Select Aspect */

function BuildAspectButtonText(aspect)
{
 return "<div class=\"aspect_div\"><input class=\"aspect_button\" type=\"radio\" name=\"aspects\" value=\""+aspect+"\" onclick=\"SelectAspect('"+aspect+"');\" />"+aspect+"</div>\n";
}

function PrepareAspectList()
{
 PrepareFSO();
 
 var str=ProcessFileName();
 
 if( str==null ) return;
 
 var off=str.lastIndexOf("/");
 
 if( off==-1 ) off=str.lastIndexOf("\\");
 
 var folder_name=".";
 
 if( off!=-1 ) folder_name=str.slice(0,off);
 
 var folder=FSO.GetFolder(folder_name);
 
 var htmlText="";
 
 for(var en=new Enumerator(folder.Files); !en.atEnd() ;en.moveNext())
   {
    var name=en.item().Path;
    
    if( name.slice(0,str.length)==str )
      {
       var ext=name.slice(str.length);
       
       if( ext.slice(-4)==".txt" )
         {
          ext=ext.slice(0,-4);
          
          if( ext.charAt(0)=="." )
            {
             ext=ext.slice(1);
            
             htmlText+=BuildAspectButtonText(ext);
            }
         }
      }
   }
  
 document.getElementById("aspect_section").innerHTML=htmlText;
}

function NewAspect()
{
 var htmlText=BuildAspectButtonText(document.getElementById("new_aspect_name").value);
 
 document.getElementById("aspect_section").innerHTML+=htmlText;
}

function DeleteAspect()
{
 PrepareFSO();
 
 if( Aspect!=null )
   {
    if( !confirm("Are you sure to delete this aspect?") ) return; 

    {    
     var list=GetElements("input","aspect_button");
    
     for(var i=0; i<list.length ;i++)
       if( list[i].value==Aspect )
         list[i].parentNode.style.display="none";
    }
        
    {    
     var list=GetElements("input","aspect_button_mod");
    
     for(var i=0; i<list.length ;i++)
       if( list[i].value==Aspect )
         list[i].parentNode.style.display="none";
    }
        
    var file_name=GetAspectFileName(Aspect);

    if( file_name!=null )
      {
       if( FSO.FileExists(file_name) ) FSO.DeleteFile(file_name);
      }
    
    Aspect=null;
    AspectSaved=true;
   }
}

function SelectAspect(aspect)
{
 if( !AspectSaved )
   {
    if( confirm("Aspect is not saved!\nDo you want to save changes?") ) SaveAspect(false); 
   }

 Aspect=aspect;
 AspectNotSaved(); 
 
 LoadAspect(false);
}

/* ShowStat */

function ShowStat()
{
 var list=GetElements("li","file_name");

 var stat_red=0;
 var stat_yellow=0;
 var stat_green=0;

 for(var i=0; i<list.length ;i++) 
   {
    switch( list[i].custom.state )
      {
       case 0 : stat_red++; break;
       case 1 : stat_yellow++; break;
       case 2 : stat_green++; break;
      }
   }

 document.getElementById("stat_red").innerHTML=stat_red;
 document.getElementById("stat_yellow").innerHTML=stat_yellow;
 document.getElementById("stat_green").innerHTML=stat_green;
}

