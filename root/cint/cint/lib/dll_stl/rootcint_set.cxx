//
// File generated by core/utils/src/rootcint_tmp at Thu Jul  9 18:13:08 2020

// Do NOT change. Changes will be lost next time file is generated
//

#define R__DICTIONARY_FILENAME cintdIcintdIlibdIdll_stldIrootcint_set
#include "RConfig.h" //rootcint 4834
#if !defined(R__ACCESS_IN_SYMBOL)
//Break the privacy of classes -- Disabled for the moment
#define private public
#define protected public
#endif

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;
#include "rootcint_set.h"

#include "TCollectionProxyInfo.h"
#include "TClass.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"

// START OF SHADOWS

namespace ROOT {
   namespace Shadow {
   } // of namespace Shadow
} // of namespace ROOT
// END OF SHADOWS

namespace ROOT {
   void setlEcharmUgR_ShowMembers(void *obj, TMemberInspector &R__insp);
   static void setlEcharmUgR_Dictionary();
   static void *new_setlEcharmUgR(void *p = 0);
   static void *newArray_setlEcharmUgR(Long_t size, void *p);
   static void delete_setlEcharmUgR(void *p);
   static void deleteArray_setlEcharmUgR(void *p);
   static void destruct_setlEcharmUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const set<char*>*)
   {
      set<char*> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(set<char*>),0);
      static ::ROOT::TGenericClassInfo 
         instance("set<char*>", -2, "prec_stl/set", 49,
                  typeid(set<char*>), DefineBehavior(ptr, ptr),
                  0, &setlEcharmUgR_Dictionary, isa_proxy, 0,
                  sizeof(set<char*>) );
      instance.SetNew(&new_setlEcharmUgR);
      instance.SetNewArray(&newArray_setlEcharmUgR);
      instance.SetDelete(&delete_setlEcharmUgR);
      instance.SetDeleteArray(&deleteArray_setlEcharmUgR);
      instance.SetDestructor(&destruct_setlEcharmUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Insert< set<char*> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const set<char*>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static void setlEcharmUgR_Dictionary() {
      ::ROOT::GenerateInitInstanceLocal((const set<char*>*)0x0)->GetClass();
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_setlEcharmUgR(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) set<char*> : new set<char*>;
   }
   static void *newArray_setlEcharmUgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) set<char*>[nElements] : new set<char*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_setlEcharmUgR(void *p) {
      delete ((set<char*>*)p);
   }
   static void deleteArray_setlEcharmUgR(void *p) {
      delete [] ((set<char*>*)p);
   }
   static void destruct_setlEcharmUgR(void *p) {
      typedef set<char*> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class set<char*>

namespace ROOT {
   void setlEdoublegR_ShowMembers(void *obj, TMemberInspector &R__insp);
   static void setlEdoublegR_Dictionary();
   static void *new_setlEdoublegR(void *p = 0);
   static void *newArray_setlEdoublegR(Long_t size, void *p);
   static void delete_setlEdoublegR(void *p);
   static void deleteArray_setlEdoublegR(void *p);
   static void destruct_setlEdoublegR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const set<double>*)
   {
      set<double> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(set<double>),0);
      static ::ROOT::TGenericClassInfo 
         instance("set<double>", -2, "prec_stl/set", 49,
                  typeid(set<double>), DefineBehavior(ptr, ptr),
                  0, &setlEdoublegR_Dictionary, isa_proxy, 0,
                  sizeof(set<double>) );
      instance.SetNew(&new_setlEdoublegR);
      instance.SetNewArray(&newArray_setlEdoublegR);
      instance.SetDelete(&delete_setlEdoublegR);
      instance.SetDeleteArray(&deleteArray_setlEdoublegR);
      instance.SetDestructor(&destruct_setlEdoublegR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Insert< set<double> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const set<double>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static void setlEdoublegR_Dictionary() {
      ::ROOT::GenerateInitInstanceLocal((const set<double>*)0x0)->GetClass();
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_setlEdoublegR(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) set<double> : new set<double>;
   }
   static void *newArray_setlEdoublegR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) set<double>[nElements] : new set<double>[nElements];
   }
   // Wrapper around operator delete
   static void delete_setlEdoublegR(void *p) {
      delete ((set<double>*)p);
   }
   static void deleteArray_setlEdoublegR(void *p) {
      delete [] ((set<double>*)p);
   }
   static void destruct_setlEdoublegR(void *p) {
      typedef set<double> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class set<double>

namespace ROOT {
   void setlEfloatgR_ShowMembers(void *obj, TMemberInspector &R__insp);
   static void setlEfloatgR_Dictionary();
   static void *new_setlEfloatgR(void *p = 0);
   static void *newArray_setlEfloatgR(Long_t size, void *p);
   static void delete_setlEfloatgR(void *p);
   static void deleteArray_setlEfloatgR(void *p);
   static void destruct_setlEfloatgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const set<float>*)
   {
      set<float> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(set<float>),0);
      static ::ROOT::TGenericClassInfo 
         instance("set<float>", -2, "prec_stl/set", 49,
                  typeid(set<float>), DefineBehavior(ptr, ptr),
                  0, &setlEfloatgR_Dictionary, isa_proxy, 0,
                  sizeof(set<float>) );
      instance.SetNew(&new_setlEfloatgR);
      instance.SetNewArray(&newArray_setlEfloatgR);
      instance.SetDelete(&delete_setlEfloatgR);
      instance.SetDeleteArray(&deleteArray_setlEfloatgR);
      instance.SetDestructor(&destruct_setlEfloatgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Insert< set<float> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const set<float>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static void setlEfloatgR_Dictionary() {
      ::ROOT::GenerateInitInstanceLocal((const set<float>*)0x0)->GetClass();
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_setlEfloatgR(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) set<float> : new set<float>;
   }
   static void *newArray_setlEfloatgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) set<float>[nElements] : new set<float>[nElements];
   }
   // Wrapper around operator delete
   static void delete_setlEfloatgR(void *p) {
      delete ((set<float>*)p);
   }
   static void deleteArray_setlEfloatgR(void *p) {
      delete [] ((set<float>*)p);
   }
   static void destruct_setlEfloatgR(void *p) {
      typedef set<float> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class set<float>

namespace ROOT {
   void setlEintgR_ShowMembers(void *obj, TMemberInspector &R__insp);
   static void setlEintgR_Dictionary();
   static void *new_setlEintgR(void *p = 0);
   static void *newArray_setlEintgR(Long_t size, void *p);
   static void delete_setlEintgR(void *p);
   static void deleteArray_setlEintgR(void *p);
   static void destruct_setlEintgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const set<int>*)
   {
      set<int> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(set<int>),0);
      static ::ROOT::TGenericClassInfo 
         instance("set<int>", -2, "prec_stl/set", 49,
                  typeid(set<int>), DefineBehavior(ptr, ptr),
                  0, &setlEintgR_Dictionary, isa_proxy, 0,
                  sizeof(set<int>) );
      instance.SetNew(&new_setlEintgR);
      instance.SetNewArray(&newArray_setlEintgR);
      instance.SetDelete(&delete_setlEintgR);
      instance.SetDeleteArray(&deleteArray_setlEintgR);
      instance.SetDestructor(&destruct_setlEintgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Insert< set<int> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const set<int>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static void setlEintgR_Dictionary() {
      ::ROOT::GenerateInitInstanceLocal((const set<int>*)0x0)->GetClass();
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_setlEintgR(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) set<int> : new set<int>;
   }
   static void *newArray_setlEintgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) set<int>[nElements] : new set<int>[nElements];
   }
   // Wrapper around operator delete
   static void delete_setlEintgR(void *p) {
      delete ((set<int>*)p);
   }
   static void deleteArray_setlEintgR(void *p) {
      delete [] ((set<int>*)p);
   }
   static void destruct_setlEintgR(void *p) {
      typedef set<int> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class set<int>

namespace ROOT {
   void setlElonggR_ShowMembers(void *obj, TMemberInspector &R__insp);
   static void setlElonggR_Dictionary();
   static void *new_setlElonggR(void *p = 0);
   static void *newArray_setlElonggR(Long_t size, void *p);
   static void delete_setlElonggR(void *p);
   static void deleteArray_setlElonggR(void *p);
   static void destruct_setlElonggR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const set<long>*)
   {
      set<long> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(set<long>),0);
      static ::ROOT::TGenericClassInfo 
         instance("set<long>", -2, "prec_stl/set", 49,
                  typeid(set<long>), DefineBehavior(ptr, ptr),
                  0, &setlElonggR_Dictionary, isa_proxy, 0,
                  sizeof(set<long>) );
      instance.SetNew(&new_setlElonggR);
      instance.SetNewArray(&newArray_setlElonggR);
      instance.SetDelete(&delete_setlElonggR);
      instance.SetDeleteArray(&deleteArray_setlElonggR);
      instance.SetDestructor(&destruct_setlElonggR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Insert< set<long> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const set<long>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static void setlElonggR_Dictionary() {
      ::ROOT::GenerateInitInstanceLocal((const set<long>*)0x0)->GetClass();
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_setlElonggR(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) set<long> : new set<long>;
   }
   static void *newArray_setlElonggR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) set<long>[nElements] : new set<long>[nElements];
   }
   // Wrapper around operator delete
   static void delete_setlElonggR(void *p) {
      delete ((set<long>*)p);
   }
   static void deleteArray_setlElonggR(void *p) {
      delete [] ((set<long>*)p);
   }
   static void destruct_setlElonggR(void *p) {
      typedef set<long> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class set<long>

namespace ROOT {
   void setlEstringgR_ShowMembers(void *obj, TMemberInspector &R__insp);
   static void setlEstringgR_Dictionary();
   static void *new_setlEstringgR(void *p = 0);
   static void *newArray_setlEstringgR(Long_t size, void *p);
   static void delete_setlEstringgR(void *p);
   static void deleteArray_setlEstringgR(void *p);
   static void destruct_setlEstringgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const set<string>*)
   {
      set<string> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(set<string>),0);
      static ::ROOT::TGenericClassInfo 
         instance("set<string>", -2, "prec_stl/set", 49,
                  typeid(set<string>), DefineBehavior(ptr, ptr),
                  0, &setlEstringgR_Dictionary, isa_proxy, 0,
                  sizeof(set<string>) );
      instance.SetNew(&new_setlEstringgR);
      instance.SetNewArray(&newArray_setlEstringgR);
      instance.SetDelete(&delete_setlEstringgR);
      instance.SetDeleteArray(&deleteArray_setlEstringgR);
      instance.SetDestructor(&destruct_setlEstringgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Insert< set<string> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const set<string>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static void setlEstringgR_Dictionary() {
      ::ROOT::GenerateInitInstanceLocal((const set<string>*)0x0)->GetClass();
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_setlEstringgR(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) set<string> : new set<string>;
   }
   static void *newArray_setlEstringgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) set<string>[nElements] : new set<string>[nElements];
   }
   // Wrapper around operator delete
   static void delete_setlEstringgR(void *p) {
      delete ((set<string>*)p);
   }
   static void deleteArray_setlEstringgR(void *p) {
      delete [] ((set<string>*)p);
   }
   static void destruct_setlEstringgR(void *p) {
      typedef set<string> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class set<string>

namespace ROOT {
   void setlEvoidmUgR_ShowMembers(void *obj, TMemberInspector &R__insp);
   static void setlEvoidmUgR_Dictionary();
   static void *new_setlEvoidmUgR(void *p = 0);
   static void *newArray_setlEvoidmUgR(Long_t size, void *p);
   static void delete_setlEvoidmUgR(void *p);
   static void deleteArray_setlEvoidmUgR(void *p);
   static void destruct_setlEvoidmUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const set<void*>*)
   {
      set<void*> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(set<void*>),0);
      static ::ROOT::TGenericClassInfo 
         instance("set<void*>", -2, "prec_stl/set", 49,
                  typeid(set<void*>), DefineBehavior(ptr, ptr),
                  0, &setlEvoidmUgR_Dictionary, isa_proxy, 0,
                  sizeof(set<void*>) );
      instance.SetNew(&new_setlEvoidmUgR);
      instance.SetNewArray(&newArray_setlEvoidmUgR);
      instance.SetDelete(&delete_setlEvoidmUgR);
      instance.SetDeleteArray(&deleteArray_setlEvoidmUgR);
      instance.SetDestructor(&destruct_setlEvoidmUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Insert< set<void*> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const set<void*>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static void setlEvoidmUgR_Dictionary() {
      ::ROOT::GenerateInitInstanceLocal((const set<void*>*)0x0)->GetClass();
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_setlEvoidmUgR(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) set<void*> : new set<void*>;
   }
   static void *newArray_setlEvoidmUgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) set<void*>[nElements] : new set<void*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_setlEvoidmUgR(void *p) {
      delete ((set<void*>*)p);
   }
   static void deleteArray_setlEvoidmUgR(void *p) {
      delete [] ((set<void*>*)p);
   }
   static void destruct_setlEvoidmUgR(void *p) {
      typedef set<void*> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class set<void*>

/********************************************************
* cint/cint/lib/dll_stl/rootcint_set.cxx
* CAUTION: DON'T CHANGE THIS FILE. THIS FILE IS AUTOMATICALLY GENERATED
*          FROM HEADER FILES LISTED IN G__setup_cpp_environmentXXX().
*          CHANGE THOSE HEADER FILES AND REGENERATE THIS FILE.
********************************************************/

#ifdef G__MEMTEST
#undef malloc
#undef free
#endif

#if defined(__GNUC__) && __GNUC__ >= 4 && ((__GNUC_MINOR__ == 2 && __GNUC_PATCHLEVEL__ >= 1) || (__GNUC_MINOR__ >= 3))
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif

extern "C" void G__cpp_reset_tagtablerootcint_set();

extern "C" void G__set_cpp_environmentrootcint_set() {
  G__add_compiledheader("TObject.h");
  G__add_compiledheader("TMemberInspector.h");
  G__add_compiledheader("set");
  G__cpp_reset_tagtablerootcint_set();
}
#include <new>
extern "C" int G__cpp_dllrevrootcint_set() { return(30051515); }

/*********************************************************
* Member function Interface Method
*********************************************************/

/* Setting up global function */

/*********************************************************
* Member function Stub
*********************************************************/

/*********************************************************
* Global function Stub
*********************************************************/

/*********************************************************
* Get size of pointer to member function
*********************************************************/
class G__Sizep2memfuncrootcint_set {
 public:
  G__Sizep2memfuncrootcint_set(): p(&G__Sizep2memfuncrootcint_set::sizep2memfunc) {}
    size_t sizep2memfunc() { return(sizeof(p)); }
  private:
    size_t (G__Sizep2memfuncrootcint_set::*p)();
};

size_t G__get_sizep2memfuncrootcint_set()
{
  G__Sizep2memfuncrootcint_set a;
  G__setsizep2memfunc((int)a.sizep2memfunc());
  return((size_t)a.sizep2memfunc());
}


/*********************************************************
* virtual base class offset calculation interface
*********************************************************/

   /* Setting up class inheritance */

/*********************************************************
* Inheritance information setup/
*********************************************************/
extern "C" void G__cpp_setup_inheritancerootcint_set() {

   /* Setting up class inheritance */
}

/*********************************************************
* typedef information setup/
*********************************************************/
extern "C" void G__cpp_setup_typetablerootcint_set() {

   /* Setting up typedef entry */
   G__search_typename2("vector<ROOT::TSchemaHelper>",117,G__get_linked_tagnum(&G__rootcint_setLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<const_iterator>",117,G__get_linked_tagnum(&G__rootcint_setLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__rootcint_setLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<iterator>",117,G__get_linked_tagnum(&G__rootcint_setLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__rootcint_setLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("vector<TVirtualArray*>",117,G__get_linked_tagnum(&G__rootcint_setLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<const_iterator>",117,G__get_linked_tagnum(&G__rootcint_setLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__rootcint_setLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<iterator>",117,G__get_linked_tagnum(&G__rootcint_setLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__rootcint_setLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR));
   G__setnewtype(-1,NULL,0);
}

/*********************************************************
* Data Member information setup/
*********************************************************/

   /* Setting up class,struct,union tag member variable */
extern "C" void G__cpp_setup_memvarrootcint_set() {
}
/***********************************************************
************************************************************
************************************************************
************************************************************
************************************************************
************************************************************
************************************************************
***********************************************************/

/*********************************************************
* Member function information setup for each class
*********************************************************/

/*********************************************************
* Member function information setup
*********************************************************/
extern "C" void G__cpp_setup_memfuncrootcint_set() {
}

/*********************************************************
* Global variable information setup for each class
*********************************************************/
static void G__cpp_setup_global0() {

   /* Setting up global variables */
   G__resetplocal();

}

static void G__cpp_setup_global1() {

   G__resetglobalenv();
}
extern "C" void G__cpp_setup_globalrootcint_set() {
  G__cpp_setup_global0();
  G__cpp_setup_global1();
}

/*********************************************************
* Global function information setup for each class
*********************************************************/
static void G__cpp_setup_func0() {
   G__lastifuncposition();

}

static void G__cpp_setup_func1() {
}

static void G__cpp_setup_func2() {

   G__resetifuncposition();
}

extern "C" void G__cpp_setup_funcrootcint_set() {
  G__cpp_setup_func0();
  G__cpp_setup_func1();
  G__cpp_setup_func2();
}

/*********************************************************
* Class,struct,union,enum tag information setup
*********************************************************/
/* Setup class/struct taginfo */
G__linked_taginfo G__rootcint_setLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR = { "vector<ROOT::TSchemaHelper,allocator<ROOT::TSchemaHelper> >" , 99 , -1 };
G__linked_taginfo G__rootcint_setLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR = { "reverse_iterator<vector<ROOT::TSchemaHelper,allocator<ROOT::TSchemaHelper> >::iterator>" , 99 , -1 };
G__linked_taginfo G__rootcint_setLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR = { "vector<TVirtualArray*,allocator<TVirtualArray*> >" , 99 , -1 };
G__linked_taginfo G__rootcint_setLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR = { "reverse_iterator<vector<TVirtualArray*,allocator<TVirtualArray*> >::iterator>" , 99 , -1 };

/* Reset class/struct taginfo */
extern "C" void G__cpp_reset_tagtablerootcint_set() {
  G__rootcint_setLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR.tagnum = -1 ;
  G__rootcint_setLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR.tagnum = -1 ;
  G__rootcint_setLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR.tagnum = -1 ;
  G__rootcint_setLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR.tagnum = -1 ;
}


extern "C" void G__cpp_setup_tagtablerootcint_set() {

   /* Setting up class,struct,union tag entry */
   G__get_linked_tagnum_fwd(&G__rootcint_setLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR);
   G__get_linked_tagnum_fwd(&G__rootcint_setLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR);
   G__get_linked_tagnum_fwd(&G__rootcint_setLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR);
   G__get_linked_tagnum_fwd(&G__rootcint_setLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR);
}
extern "C" void G__cpp_setuprootcint_set(void) {
  G__check_setup_version(30051515,"G__cpp_setuprootcint_set()");
  G__set_cpp_environmentrootcint_set();
  G__cpp_setup_tagtablerootcint_set();

  G__cpp_setup_inheritancerootcint_set();

  G__cpp_setup_typetablerootcint_set();

  G__cpp_setup_memvarrootcint_set();

  G__cpp_setup_memfuncrootcint_set();
  G__cpp_setup_globalrootcint_set();
  G__cpp_setup_funcrootcint_set();

   if(0==G__getsizep2memfunc()) G__get_sizep2memfuncrootcint_set();
  return;
}
class G__cpp_setup_initrootcint_set {
  public:
    G__cpp_setup_initrootcint_set() { G__add_setup_func("rootcint_set",(G__incsetup)(&G__cpp_setuprootcint_set)); G__call_setup_funcs(); }
   ~G__cpp_setup_initrootcint_set() { G__remove_setup_func("rootcint_set"); }
};
G__cpp_setup_initrootcint_set G__cpp_setup_initializerrootcint_set;

