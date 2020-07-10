/********************************************************************
* geom/geom/src/G__Geom1.h
* CAUTION: DON'T CHANGE THIS FILE. THIS FILE IS AUTOMATICALLY GENERATED
*          FROM HEADER FILES LISTED IN G__setup_cpp_environmentXXX().
*          CHANGE THOSE HEADER FILES AND REGENERATE THIS FILE.
********************************************************************/
#ifdef __CINT__
#error geom/geom/src/G__Geom1.h/C is only for compilation. Abort cint.
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
extern void G__cpp_setup_tagtableG__Geom1();
extern void G__cpp_setup_inheritanceG__Geom1();
extern void G__cpp_setup_typetableG__Geom1();
extern void G__cpp_setup_memvarG__Geom1();
extern void G__cpp_setup_globalG__Geom1();
extern void G__cpp_setup_memfuncG__Geom1();
extern void G__cpp_setup_funcG__Geom1();
extern void G__set_cpp_environmentG__Geom1();
}


#include "TObject.h"
#include "TMemberInspector.h"
#include "TGeoAtt.h"
#include "TGeoBoolNode.h"
#include "TGeoMedium.h"
#include "TGeoMaterial.h"
#include "TGeoMatrix.h"
#include "TGeoVolume.h"
#include "TGeoNode.h"
#include "TGeoVoxelFinder.h"
#include "TGeoShape.h"
#include "TGeoBBox.h"
#include "TGeoPara.h"
#include "TGeoTube.h"
#include "TGeoTorus.h"
#include "TGeoSphere.h"
#include "TGeoEltu.h"
#include "TGeoHype.h"
#include "TGeoCone.h"
#include "TGeoPcon.h"
#include "TGeoPgon.h"
#include "TGeoArb8.h"
#include "TGeoTrd1.h"
#include "TGeoTrd2.h"
#include "TGeoManager.h"
#include "TGeoCompositeShape.h"
#include "TGeoShapeAssembly.h"
#include "TGeoScaledShape.h"
#include "TVirtualGeoPainter.h"
#include "TVirtualGeoTrack.h"
#include "TGeoPolygon.h"
#include "TGeoXtru.h"
#include "TGeoPhysicalNode.h"
#include "TGeoHelix.h"
#include "TGeoParaboloid.h"
#include "TGeoElement.h"
#include "TGeoHalfSpace.h"
#include "TGeoBuilder.h"
#include "TGeoNavigator.h"
#include <algorithm>
namespace std { }
using namespace std;

#ifndef G__MEMFUNCBODY
#endif

extern G__linked_taginfo G__G__Geom1LN_TClass;
extern G__linked_taginfo G__G__Geom1LN_TBuffer;
extern G__linked_taginfo G__G__Geom1LN_TMemberInspector;
extern G__linked_taginfo G__G__Geom1LN_TObject;
extern G__linked_taginfo G__G__Geom1LN_TNamed;
extern G__linked_taginfo G__G__Geom1LN_TString;
extern G__linked_taginfo G__G__Geom1LN_basic_ostreamlEcharcOchar_traitslEchargRsPgR;
extern G__linked_taginfo G__G__Geom1LN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR;
extern G__linked_taginfo G__G__Geom1LN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR;
extern G__linked_taginfo G__G__Geom1LN_TList;
extern G__linked_taginfo G__G__Geom1LN_TBrowser;
extern G__linked_taginfo G__G__Geom1LN_TObjArray;
extern G__linked_taginfo G__G__Geom1LN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR;
extern G__linked_taginfo G__G__Geom1LN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR;
extern G__linked_taginfo G__G__Geom1LN_TGeoAtt;
extern G__linked_taginfo G__G__Geom1LN_TGeoAttcLcLdA;
extern G__linked_taginfo G__G__Geom1LN_TGeoAttcLcLEGeoVisibilityAtt;
extern G__linked_taginfo G__G__Geom1LN_TGeoAttcLcLEGeoActivityAtt;
extern G__linked_taginfo G__G__Geom1LN_TGeoAttcLcLEGeoOptimizationAtt;
extern G__linked_taginfo G__G__Geom1LN_TGeoAttcLcLEGeoSavePrimitiveAtt;
extern G__linked_taginfo G__G__Geom1LN_TGeoShape;
extern G__linked_taginfo G__G__Geom1LN_TGeoMatrix;
extern G__linked_taginfo G__G__Geom1LN_TGeoHMatrix;
extern G__linked_taginfo G__G__Geom1LN_TGeoBoolNode;
extern G__linked_taginfo G__G__Geom1LN_TGeoBoolNodecLcLEGeoBoolType;
extern G__linked_taginfo G__G__Geom1LN_TGeoUnion;
extern G__linked_taginfo G__G__Geom1LN_TGeoIntersection;
extern G__linked_taginfo G__G__Geom1LN_TGeoSubtraction;
extern G__linked_taginfo G__G__Geom1LN_TAttFill;
extern G__linked_taginfo G__G__Geom1LN_TAttLine;
extern G__linked_taginfo G__G__Geom1LN_TAttMarker;
extern G__linked_taginfo G__G__Geom1LN_iteratorlEbidirectional_iterator_tagcOTObjectmUcOlongcOconstsPTObjectmUmUcOconstsPTObjectmUaNgR;
extern G__linked_taginfo G__G__Geom1LN_TGeoElementTable;
extern G__linked_taginfo G__G__Geom1LN_TGeoIsotope;
extern G__linked_taginfo G__G__Geom1LN_TGeoElement;
extern G__linked_taginfo G__G__Geom1LN_TGeoElementcLcLEGeoElement;
extern G__linked_taginfo G__G__Geom1LN_TGeoDecayChannel;
extern G__linked_taginfo G__G__Geom1LN_TGeoBatemanSol;
extern G__linked_taginfo G__G__Geom1LN_TGeoElementRN;
extern G__linked_taginfo G__G__Geom1LN_TGeoDecayChannelcLcLENuclearDecayMode;
extern G__linked_taginfo G__G__Geom1LN_TGeoBatemanSolcLcLBtCoef_t;
extern G__linked_taginfo G__G__Geom1LN_TGeoElemIter;
extern G__linked_taginfo G__G__Geom1LN_maplEintcOTGeoElementRNmUcOlesslEintgRcOallocatorlEpairlEconstsPintcOTGeoElementRNmUgRsPgRsPgR;
extern G__linked_taginfo G__G__Geom1LN_maplEintcOTGeoElementRNmUcOlesslEintgRcOallocatorlEpairlEconstsPintcOTGeoElementRNmUgRsPgRsPgRcLcLiterator;
extern G__linked_taginfo G__G__Geom1LN_TGeoElementTablecLcLEGeoETStatus;
extern G__linked_taginfo G__G__Geom1LN_TGeoMaterial;
extern G__linked_taginfo G__G__Geom1LN_TGeoMaterialcLcLEGeoMaterial;
extern G__linked_taginfo G__G__Geom1LN_TGeoMaterialcLcLEGeoMaterialState;
extern G__linked_taginfo G__G__Geom1LN_TGeoMixture;
extern G__linked_taginfo G__G__Geom1LN_TGeoMedium;
extern G__linked_taginfo G__G__Geom1LN_TGeoMediumcLcLEGeoMedium;
extern G__linked_taginfo G__G__Geom1LN_TGeoMatrixcLcLEGeoTransfTypes;
extern G__linked_taginfo G__G__Geom1LN_TGeoTranslation;
extern G__linked_taginfo G__G__Geom1LN_TGeoRotation;
extern G__linked_taginfo G__G__Geom1LN_TGeoScale;
extern G__linked_taginfo G__G__Geom1LN_TGeoCombiTrans;
extern G__linked_taginfo G__G__Geom1LN_TGeoGenTrans;
extern G__linked_taginfo G__G__Geom1LN_TGeoIdentity;
extern G__linked_taginfo G__G__Geom1LN_TAtt3D;
extern G__linked_taginfo G__G__Geom1LN_TGeoBBox;
extern G__linked_taginfo G__G__Geom1LN_TGeoVolume;
extern G__linked_taginfo G__G__Geom1LN_TBuffer3D;
extern G__linked_taginfo G__G__Geom1LN_TGeoShapecLcLEShapeType;
extern G__linked_taginfo G__G__Geom1LN_TH2F;
extern G__linked_taginfo G__G__Geom1LN_TGeoNode;
extern G__linked_taginfo G__G__Geom1LN_TGeoPatternFinder;
extern G__linked_taginfo G__G__Geom1LN_TGeoVoxelFinder;
extern G__linked_taginfo G__G__Geom1LN_TGeoManager;
extern G__linked_taginfo G__G__Geom1LN_TGeoVolumecLcLEGeoVolumeTypes;
extern G__linked_taginfo G__G__Geom1LN_TGeoVolumeMulti;
extern G__linked_taginfo G__G__Geom1LN_TGeoVolumeAssembly;
extern G__linked_taginfo G__G__Geom1LN_TGeoNodecLcLdA;
extern G__linked_taginfo G__G__Geom1LN_TGeoNodeMatrix;
extern G__linked_taginfo G__G__Geom1LN_TGeoNodeOffset;
extern G__linked_taginfo G__G__Geom1LN_TGeoIterator;
extern G__linked_taginfo G__G__Geom1LN_TGeoIteratorPlugin;
extern G__linked_taginfo G__G__Geom1LN_TGeoVoxelFindercLcLEVoxelsType;
extern G__linked_taginfo G__G__Geom1LN_TGeoPara;
extern G__linked_taginfo G__G__Geom1LN_TGeoTube;
extern G__linked_taginfo G__G__Geom1LN_TGeoTubeSeg;
extern G__linked_taginfo G__G__Geom1LN_TGeoCtub;
extern G__linked_taginfo G__G__Geom1LN_TGeoTorus;
extern G__linked_taginfo G__G__Geom1LN_TGeoSphere;
extern G__linked_taginfo G__G__Geom1LN_TGeoEltu;
extern G__linked_taginfo G__G__Geom1LN_TGeoHype;
extern G__linked_taginfo G__G__Geom1LN_TGeoCone;
extern G__linked_taginfo G__G__Geom1LN_TGeoConeSeg;
extern G__linked_taginfo G__G__Geom1LN_TGeoPcon;
extern G__linked_taginfo G__G__Geom1LN_TGeoPgon;
extern G__linked_taginfo G__G__Geom1LN_TGeoArb8;
extern G__linked_taginfo G__G__Geom1LN_TGeoArb8cLcLEGeoArb8Type;
extern G__linked_taginfo G__G__Geom1LN_TGeoTrap;
extern G__linked_taginfo G__G__Geom1LN_TGeoGtra;
extern G__linked_taginfo G__G__Geom1LN_TGeoTrd1;
extern G__linked_taginfo G__G__Geom1LN_TGeoTrd2;
extern G__linked_taginfo G__G__Geom1LN_TGeoCacheState;
extern G__linked_taginfo G__G__Geom1LN_TGeoNodeCache;
extern G__linked_taginfo G__G__Geom1LN_TGeoNavigator;
extern G__linked_taginfo G__G__Geom1LN_TVirtualGeoTrack;
extern G__linked_taginfo G__G__Geom1LN_TGeoPhysicalNode;
extern G__linked_taginfo G__G__Geom1LN_TGeoPNEntry;
extern G__linked_taginfo G__G__Geom1LN_TVirtualGeoPainter;
extern G__linked_taginfo G__G__Geom1LN_THashList;
extern G__linked_taginfo G__G__Geom1LN_TGeoCompositeShape;
extern G__linked_taginfo G__G__Geom1LN_TGeoShapeAssembly;
extern G__linked_taginfo G__G__Geom1LN_TGeoScaledShape;
extern G__linked_taginfo G__G__Geom1LN_TStopwatch;
extern G__linked_taginfo G__G__Geom1LN_TVirtualGeoPaintercLcLEGeoVisLevel;
extern G__linked_taginfo G__G__Geom1LN_TVirtualGeoPaintercLcLEGeoVisOption;
extern G__linked_taginfo G__G__Geom1LN_TVirtualGeoPaintercLcLEGeoBombOption;
extern G__linked_taginfo G__G__Geom1LN_TGeoPolygon;
extern G__linked_taginfo G__G__Geom1LN_TGeoPolygoncLcLdA;
extern G__linked_taginfo G__G__Geom1LN_TGeoXtru;
extern G__linked_taginfo G__G__Geom1LN_TGeoPhysicalNodecLcLdA;
extern G__linked_taginfo G__G__Geom1LN_TGeoPNEntrycLcLEPNEntryFlags;
extern G__linked_taginfo G__G__Geom1LN_TGeoHelix;
extern G__linked_taginfo G__G__Geom1LN_TGeoHelixcLcLEGeoHelixTypes;
extern G__linked_taginfo G__G__Geom1LN_TGeoParaboloid;
extern G__linked_taginfo G__G__Geom1LN_TGeoHalfSpace;
extern G__linked_taginfo G__G__Geom1LN_TGeoBuilder;

/* STUB derived class for protected member access */