/********************************************************************
* core/cont/src/G__Cont.h
* CAUTION: DON'T CHANGE THIS FILE. THIS FILE IS AUTOMATICALLY GENERATED
*          FROM HEADER FILES LISTED IN G__setup_cpp_environmentXXX().
*          CHANGE THOSE HEADER FILES AND REGENERATE THIS FILE.
********************************************************************/
#ifdef __CINT__
#error core/cont/src/G__Cont.h/C is only for compilation. Abort cint.
#endif
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define G__ANSIHEADER
#define G__DICTIONARY
#define G__PRIVATE_GVALUE
#include "G__ci.h"
#include "FastAllocString.h"
extern "C" {
extern void G__cpp_setup_tagtableG__Cont();
extern void G__cpp_setup_inheritanceG__Cont();
extern void G__cpp_setup_typetableG__Cont();
extern void G__cpp_setup_memvarG__Cont();
extern void G__cpp_setup_globalG__Cont();
extern void G__cpp_setup_memfuncG__Cont();
extern void G__cpp_setup_funcG__Cont();
extern void G__set_cpp_environmentG__Cont();
}


#include "TObject.h"
#include "TMemberInspector.h"
#include "TArrayC.h"
#include "TArrayD.h"
#include "TArrayF.h"
#include "TArray.h"
#include "TArrayI.h"
#include "TArrayL64.h"
#include "TArrayL.h"
#include "TArrayS.h"
#include "TBits.h"
#include "TBtree.h"
#include "TClassTable.h"
#include "TClonesArray.h"
#include "TCollection.h"
#include "TCollectionProxyInfo.h"
#include "TExMap.h"
#include "THashList.h"
#include "THashTable.h"
#include "TIterator.h"
#include "TList.h"
#include "TMap.h"
#include "TObjArray.h"
#include "TObjectTable.h"
#include "TOrdCollection.h"
#include "TRefArray.h"
#include "TRefTable.h"
#include "TSeqCollection.h"
#include "TSortedList.h"
#include "TVirtualCollectionProxy.h"
#include <algorithm>
namespace std { }
using namespace std;

#ifndef G__MEMFUNCBODY
#endif

extern G__linked_taginfo G__G__ContLN_type_info;
extern G__linked_taginfo G__G__ContLN_TClass;
extern G__linked_taginfo G__G__ContLN_TBuffer;
extern G__linked_taginfo G__G__ContLN_TMemberInspector;
extern G__linked_taginfo G__G__ContLN_TObject;
extern G__linked_taginfo G__G__ContLN_TString;
extern G__linked_taginfo G__G__ContLN_TVirtualCollectionProxy;
extern G__linked_taginfo G__G__ContLN_ROOT;
extern G__linked_taginfo G__G__ContLN_basic_ostreamlEcharcOchar_traitslEchargRsPgR;
extern G__linked_taginfo G__G__ContLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR;
extern G__linked_taginfo G__G__ContLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR;
extern G__linked_taginfo G__G__ContLN_TList;
extern G__linked_taginfo G__G__ContLN_TBrowser;
extern G__linked_taginfo G__G__ContLN_TObjArray;
extern G__linked_taginfo G__G__ContLN_TProcessID;
extern G__linked_taginfo G__G__ContLN_TClonesArray;
extern G__linked_taginfo G__G__ContLN_TRefTable;
extern G__linked_taginfo G__G__ContLN_TStreamerInfoActions;
extern G__linked_taginfo G__G__ContLN_TStreamerInfoActionscLcLTActionSequence;
extern G__linked_taginfo G__G__ContLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR;
extern G__linked_taginfo G__G__ContLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR;
extern G__linked_taginfo G__G__ContLN_TArray;
extern G__linked_taginfo G__G__ContLN_TArrayC;
extern G__linked_taginfo G__G__ContLN_TArrayD;
extern G__linked_taginfo G__G__ContLN_TArrayF;
extern G__linked_taginfo G__G__ContLN_TArrayI;
extern G__linked_taginfo G__G__ContLN_TArrayL64;
extern G__linked_taginfo G__G__ContLN_TArrayL;
extern G__linked_taginfo G__G__ContLN_TArrayS;
extern G__linked_taginfo G__G__ContLN_TBits;
extern G__linked_taginfo G__G__ContLN_TBitscLcLTReference;
extern G__linked_taginfo G__G__ContLN_TCollection;
extern G__linked_taginfo G__G__ContLN_TIterator;
extern G__linked_taginfo G__G__ContLN_TPRegexp;
extern G__linked_taginfo G__G__ContLN_TObjectTable;
extern G__linked_taginfo G__G__ContLN_TCollectioncLcLdA;
extern G__linked_taginfo G__G__ContLN_TIter;
extern G__linked_taginfo G__G__ContLN_TSeqCollection;
extern G__linked_taginfo G__G__ContLN_TBtNode;
extern G__linked_taginfo G__G__ContLN_TBtreeIter;
extern G__linked_taginfo G__G__ContLN_TBtree;
extern G__linked_taginfo G__G__ContLN_iteratorlEbidirectional_iterator_tagcOTObjectmUcOlongcOconstsPTObjectmUmUcOconstsPTObjectmUaNgR;
extern G__linked_taginfo G__G__ContLN_TClassRec;
extern G__linked_taginfo G__G__ContLN_ROOTcLcLTMapTypeToClassRec;
extern G__linked_taginfo G__G__ContLN_TClassTable;
extern G__linked_taginfo G__G__ContLN_TClassTablecLcLdA;
extern G__linked_taginfo G__G__ContLN_TObjArrayIter;
extern G__linked_taginfo G__G__ContLN_TClonesArraycLcLdA;
extern G__linked_taginfo G__G__ContLN_vectorlEboolcOallocatorlEboolgRsPgR;
extern G__linked_taginfo G__G__ContLN_reverse_iteratorlEvectorlEboolcOallocatorlEboolgRsPgRcLcLiteratorgR;
extern G__linked_taginfo G__G__ContLN_TExMapIter;
extern G__linked_taginfo G__G__ContLN_TExMap;
extern G__linked_taginfo G__G__ContLN_TExMapcLcLAssoc_t;
extern G__linked_taginfo G__G__ContLN_TObjLink;
extern G__linked_taginfo G__G__ContLN_TListIter;
extern G__linked_taginfo G__G__ContLN_THashTable;
extern G__linked_taginfo G__G__ContLN_THashList;
extern G__linked_taginfo G__G__ContLN_THashTableIter;
extern G__linked_taginfo G__G__ContLN_TMapIter;
extern G__linked_taginfo G__G__ContLN_TPair;
extern G__linked_taginfo G__G__ContLN_TMap;
extern G__linked_taginfo G__G__ContLN_TMapcLcLdA;
extern G__linked_taginfo G__G__ContLN_TOrdCollectionIter;
extern G__linked_taginfo G__G__ContLN_TOrdCollection;
extern G__linked_taginfo G__G__ContLN_TOrdCollectioncLcLdA;
extern G__linked_taginfo G__G__ContLN_TRefArrayIter;
extern G__linked_taginfo G__G__ContLN_TRefArray;
extern G__linked_taginfo G__G__ContLN_vectorlEstringcOallocatorlEstringgRsPgR;
extern G__linked_taginfo G__G__ContLN_reverse_iteratorlEvectorlEstringcOallocatorlEstringgRsPgRcLcLiteratorgR;
extern G__linked_taginfo G__G__ContLN_vectorlEintcOallocatorlEintgRsPgR;
extern G__linked_taginfo G__G__ContLN_vectorlEintcOallocatorlEintgRsPgRcLcLiterator;
extern G__linked_taginfo G__G__ContLN_reverse_iteratorlEvectorlEintcOallocatorlEintgRsPgRcLcLiteratorgR;
extern G__linked_taginfo G__G__ContLN_TRefTablecLcLdA;
extern G__linked_taginfo G__G__ContLN_TSortedList;
extern G__linked_taginfo G__G__ContLN_TClassRef;
extern G__linked_taginfo G__G__ContLN_maplEstringcOTObjArraymUcOlesslEstringgRcOallocatorlEpairlEconstsPstringcOTObjArraymUgRsPgRsPgR;
extern G__linked_taginfo G__G__ContLN_EDataType;
extern G__linked_taginfo G__G__ContLN_TVirtualCollectionProxycLcLEProperty;

/* STUB derived class for protected member access */
typedef vector<int,allocator<int> > G__vectorlEintcOallocatorlEintgRsPgR;
typedef vector<int,allocator<int> >::iterator G__vectorlEintcOallocatorlEintgRsPgRcLcLiterator;
typedef reverse_iterator<vector<int,allocator<int> >::iterator> G__reverse_iteratorlEvectorlEintcOallocatorlEintgRsPgRcLcLiteratorgR;
