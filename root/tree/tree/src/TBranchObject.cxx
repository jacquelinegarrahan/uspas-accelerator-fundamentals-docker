// @(#)root/tree:$Id$
// Author: Rene Brun   11/02/96

/*************************************************************************
 * Copyright (C) 1995-2000, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TBranchObject                                                        //
//                                                                      //
// A Branch for the case of an object                                   //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "TBranchObject.h"

#include "TBasket.h"
#include "TBranchClones.h"
#include "TBrowser.h"
#include "TClass.h"
#include "TClonesArray.h"
#include "TDataMember.h"
#include "TDataType.h"
#include "TFile.h"
#include "TLeafObject.h"
#include "TRealData.h"
#include "TStreamerInfo.h"
#include "TTree.h"
#include "TVirtualPad.h"

ClassImp(TBranchObject)

//______________________________________________________________________________
TBranchObject::TBranchObject()
: TBranch()
{
   // Default constructor for BranchObject.

   fNleaves = 1;
   fOldObject = 0;
}

//______________________________________________________________________________
TBranchObject::TBranchObject(TTree *tree, const char* name, const char* classname, void* addobj, Int_t basketsize, Int_t splitlevel, Int_t compress, Bool_t isptrptr /* = kTRUE */)
: TBranch()
{
   // Create a BranchObject.

   Init(tree,0,name,classname,addobj,basketsize,splitlevel,compress,isptrptr);
}

//______________________________________________________________________________
TBranchObject::TBranchObject(TBranch *parent, const char* name, const char* classname, void* addobj, Int_t basketsize, Int_t splitlevel, Int_t compress, Bool_t isptrptr /* = kTRUE */)
: TBranch()
{
   // Create a BranchObject.

   Init(0,parent,name,classname,addobj,basketsize,splitlevel,compress,isptrptr);
}

//______________________________________________________________________________
void TBranchObject::Init(TTree *tree, TBranch *parent, const char* name, const char* classname, void* addobj, Int_t basketsize, Int_t /*splitlevel*/, Int_t compress, Bool_t isptrptr)
{
   // Initialization routine (run from the constructor so do not make this function virtual)

   if (tree==0 && parent!=0) tree = parent->GetTree();
   fTree   = tree;
   fMother = parent ? parent->GetMother() : this;
   fParent = parent;

   TClass* cl = TClass::GetClass(classname);

   if (!cl) {
      Error("TBranchObject", "Cannot find class:%s", classname);
      return;
   }

   if (!isptrptr) {
      fOldObject = (TObject*)addobj;
      addobj = &fOldObject;
   }

   char** apointer = (char**) addobj;
   TObject* obj = (TObject*) (*apointer);

   Bool_t delobj = kFALSE;
   if (!obj) {
      obj = (TObject*) cl->New();
      delobj = kTRUE;
   }

   tree->BuildStreamerInfo(cl, obj);

   if (delobj) {
      cl->Destructor(obj);
   }

   SetName(name);
   SetTitle(name);

   fCompress = compress;
   if ((compress == -1) && tree->GetDirectory()) {
      TFile* bfile = tree->GetDirectory()->GetFile();
      if (bfile) {
         fCompress = bfile->GetCompressionLevel();
      }
   }
   if (basketsize < 100) {
      basketsize = 100;
   }
   fBasketSize = basketsize;
   fAddress = (char*) addobj;
   fClassName = classname;
   fBasketBytes = new Int_t[fMaxBaskets];
   fBasketEntry = new Long64_t[fMaxBaskets];
   fBasketSeek = new Long64_t[fMaxBaskets];
   fOldObject = 0;

   for (Int_t i = 0; i < fMaxBaskets; ++i) {
      fBasketBytes[i] = 0;
      fBasketEntry[i] = 0;
      fBasketSeek[i] = 0;
   }

   TLeaf* leaf = new TLeafObject(this, name, classname);
   leaf->SetAddress(addobj);
   fNleaves = 1;
   fLeaves.Add(leaf);
   tree->GetListOfLeaves()->Add(leaf);

   // Set the bit kAutoDelete to specify that when reading
   // in TLeafObject::ReadBasket, the object should be deleted
   // before calling Streamer.
   // It is foreseen to not set this bit in a future version.
   SetAutoDelete(kTRUE);

   fDirectory = fTree->GetDirectory();
   fFileName = "";

}

//______________________________________________________________________________
TBranchObject::~TBranchObject()
{
   // Destructor for a BranchObject.
   fBranches.Delete();
}

//______________________________________________________________________________
void TBranchObject::Browse(TBrowser* b)
{
   // Browse the branch content.

   Int_t nbranches = fBranches.GetEntriesFast();
   if (nbranches > 1) {
      fBranches.Browse(b);
   }
   if (GetBrowsables() && GetBrowsables()->GetSize()) {
      GetBrowsables()->Browse(b);
   }
}

//______________________________________________________________________________
Int_t TBranchObject::Fill()
{
   // Loop on all leaves of this branch to fill Basket buffer.

   Int_t nbytes = 0;
   Int_t nbranches = fBranches.GetEntriesFast();
   if (nbranches) {
      ++fEntries;
      UpdateAddress();
      for (Int_t i = 0; i < nbranches; ++i)  {
         TBranch* branch = (TBranch*) fBranches[i];
         if (!branch->TestBit(kDoNotProcess)) {
            Int_t bc = branch->Fill();
            nbytes += bc;
         }
      }
   } else {
      if (!TestBit(kDoNotProcess)) {
         Int_t bc = TBranch::Fill();
         nbytes += bc;
      }
   }
   return nbytes;
}

//______________________________________________________________________________
Int_t TBranchObject::GetEntry(Long64_t entry, Int_t getall)
{
   // Read all branches of a BranchObject and return total number of bytes.
   //
   //   If entry = 0 take current entry number + 1
   //   If entry < 0 reset entry number to 0
   //
   //  The function returns the number of bytes read from the input buffer.
   //  If entry does not exist  the function returns 0.
   //  If an I/O error occurs,  the function returns -1.

   if (TestBit(kDoNotProcess) && !getall) {
      return 0;
   }
   Int_t nbytes;
   Int_t nbranches = fBranches.GetEntriesFast();

   if (nbranches) {
      if (fAddress == 0) {
         SetupAddresses();
      }
      nbytes = 0;
      Int_t nb;
      for (Int_t i = 0; i < nbranches; ++i)  {
         TBranch* branch = (TBranch*) fBranches[i];
         if (branch) {
            nb = branch->GetEntry(entry, getall);
            if (nb < 0) {
               return nb;
            }
            nbytes += nb;
         }
      }
   } else {
      nbytes = TBranch::GetEntry(entry, getall);
   }
   return nbytes;
}

//______________________________________________________________________________
Bool_t TBranchObject::IsFolder() const
{
   // Return TRUE if more than one leaf or if fBrowsables, FALSE otherwise.

   Int_t nbranches = fBranches.GetEntriesFast();

   if (nbranches >= 1) {
      return kTRUE;
   }

   TList* browsables = const_cast<TBranchObject*>(this)->GetBrowsables();

   return browsables && browsables->GetSize();
}

//______________________________________________________________________________
void TBranchObject::Print(Option_t* option) const
{
   // Print TBranch parameters.

   Int_t nbranches = fBranches.GetEntriesFast();
   if (nbranches) {
      Printf("*Branch  :%-9s : %-54s *", GetName(), GetTitle());
      Printf("*Entries : %8d : BranchObject (see below)                               *", Int_t(fEntries));
      Printf("*............................................................................*");
      for (Int_t i = 0; i < nbranches; ++i)  {
         TBranch* branch = (TBranch*) fBranches.At(i);
         if (branch) {
            branch->Print(option);
         }
      }
   } else {
      TBranch::Print(option);
   }
}

//______________________________________________________________________________
void TBranchObject::Reset(Option_t* option)
{
   // Reset a branch.
   //
   // Existing buffers are deleted.
   // Entries, max and min are reset.

   TBranch::Reset(option);

   Int_t nbranches = fBranches.GetEntriesFast();
   for (Int_t i = 0; i < nbranches; ++i)  {
      TBranch* branch = (TBranch*) fBranches[i];
      branch->Reset(option);
   }
}

//______________________________________________________________________________
void TBranchObject::SetAddress(void* add)
{
   // Set address of this branch.

   if (TestBit(kDoNotProcess)) {
      return;
   }

   // Special case when called from code generated by TTree::MakeClass.
   if (Long_t(add) == -1) {
      SetBit(kWarn);
      return;
   }

   fReadEntry = -1;
   Int_t nbranches = fBranches.GetEntriesFast();

   TLeaf* leaf = (TLeaf*) fLeaves.UncheckedAt(0);
   if (leaf) {
      leaf->SetAddress(add);
   }

   fAddress = (char*) add;
   char** ppointer = (char**) add;

   char* obj = 0;
   if (ppointer) {
      obj = *ppointer;
   }

   TClass* cl = TClass::GetClass(fClassName.Data());

   if (!cl) {
      for (Int_t i = 0; i < nbranches; ++i)  {
         TBranch* br = (TBranch*) fBranches[i];
         br->SetAddress(obj);
      }
      return;
   }

   if (ppointer && !obj) {
      obj = (char*) cl->New();
      *ppointer = obj;
   }

   if (!cl->GetListOfRealData()) {
      cl->BuildRealData(obj);
   }

   if (cl->InheritsFrom(TClonesArray::Class())) {
      if (ppointer) {
         TClonesArray* clones = (TClonesArray*) *ppointer;
         if (!clones) {
            Error("SetAddress", "Pointer to TClonesArray is null");
            return;
         }
         TClass* clm = clones->GetClass();
         if (clm) {
            clm->BuildRealData(); //just in case clm derives from an abstract class
            clm->GetStreamerInfo();
         }
      }
   }

   //
   // Loop over our data members looking
   // for sub-branches for them.  If we
   // find one, set its address.
   //

   char* fullname = new char[200];

   const char* bname = GetName();

   Int_t isDot = 0;
   if (bname[strlen(bname)-1] == '.') {
      isDot = 1;
   }

   char* pointer = 0;
   TRealData* rd = 0;
   TIter next(cl->GetListOfRealData());
   while ((rd = (TRealData*) next())) {
      if (rd->TestBit(TRealData::kTransient)) continue;

      TDataMember* dm = rd->GetDataMember();
      if (!dm || !dm->IsPersistent()) {
         continue;
      }
      const char* rdname = rd->GetName();
      TDataType* dtype = dm->GetDataType();
      Int_t code = 0;
      if (dtype) {
         code = dm->GetDataType()->GetType();
      }
      Int_t offset = rd->GetThisOffset();
      if (ppointer) {
         pointer = obj + offset;
      }
      TBranch* branch = 0;
      if (dm->IsaPointer()) {
         TClass* clobj = 0;
         if (!dm->IsBasic()) {
            clobj = TClass::GetClass(dm->GetTypeName());
         }
         if (clobj && clobj->InheritsFrom(TClonesArray::Class())) {
            if (isDot) {
               snprintf(fullname,200, "%s%s", bname, &rdname[1]);
            } else {
               snprintf(fullname,200, "%s", &rdname[1]);
            }
            branch = (TBranch*) fBranches.FindObject(fullname);
         } else {
            if (!clobj) {
               // this is a basic type we can handle only if
               // he has a dimension:
               const char* index = dm->GetArrayIndex();
               if (strlen(index) == 0) {
                  if (code == 1) {
                     // Case of a string ... we do not need the size
                     if (isDot) {
                        snprintf(fullname,200, "%s%s", bname, &rdname[0]);
                     } else {
                        snprintf(fullname,200, "%s", &rdname[0]);
                     }
                  } else {
                     continue;
                  }
               }
               if (isDot) {
                  snprintf(fullname,200, "%s%s", bname, &rdname[0]);
               } else {
                  snprintf(fullname,200, "%s", &rdname[0]);
               }
               // let's remove the stars!
               UInt_t cursor;
               UInt_t pos;
               for (cursor = 0, pos = 0; cursor < strlen(fullname); ++cursor) {
                  if (fullname[cursor] != '*') {
                     fullname[pos++] = fullname[cursor];
                  }
               }
               fullname[pos] = '\0';
               branch = (TBranch*) fBranches.FindObject(fullname);
            } else {
               if (!clobj->InheritsFrom(TObject::Class())) {
                  continue;
               }
               if (isDot) {
                  snprintf(fullname,200, "%s%s", bname, &rdname[1]);
               } else {
                  snprintf(fullname,200, "%s", &rdname[1]);
               }
               branch = (TBranch*) fBranches.FindObject(fullname);
            }
         }
      } else {
         if (dm->IsBasic()) {
            if (isDot) {
               snprintf(fullname,200, "%s%s", bname, &rdname[0]);
            } else {
               snprintf(fullname,200, "%s", &rdname[0]);
            }
            branch = (TBranch*) fBranches.FindObject(fullname);
         }
      }
      if (branch) {
         branch->SetAddress(pointer);
      }
   }

   delete[] fullname;
}

//______________________________________________________________________________
void TBranchObject::SetAutoDelete(Bool_t autodel)
{
   // Set the AutoDelete bit.
   //
   //  This function can be used to instruct Root in TBranchObject::ReadBasket
   //  to not delete the object referenced by a branchobject before reading a
   //  new entry. By default, the object is deleted.
   //  If autodel is kTRUE, this existing object will be deleted, a new object
   //    created by the default constructor, then object->Streamer called.
   //  If autodel is kFALSE, the existing object is not deleted. Root assumes
   //    that the user is taking care of deleting any internal object or array
   //    This can be done in Streamer itself.
   //  If this branch has sub-branches, the function sets autodel for these
   //  branches as well.
   //  We STRONGLY suggest to activate this option by default when you create
   //  the top level branch. This will make the read phase more efficient
   //  because it minimizes the numbers of new/delete operations.
   //  Once this option has been set and the Tree is written to a file, it is
   //  not necessary to specify the option again when reading, unless you
   //  want to set the opposite mode.
   //

   TBranch::SetAutoDelete(autodel);

   Int_t nbranches = fBranches.GetEntriesFast();
   for (Int_t i=0;i<nbranches;i++)  {
      TBranch *branch = (TBranch*)fBranches[i];
      branch->SetAutoDelete(autodel);
   }
}

//______________________________________________________________________________
void TBranchObject::SetBasketSize(Int_t buffsize)
{
   // Reset basket size for all subbranches of this branch.

   TBranch::SetBasketSize(buffsize);

   Int_t nbranches = fBranches.GetEntriesFast();
   for (Int_t i = 0; i < nbranches; ++i)  {
      TBranch* branch = (TBranch*) fBranches[i];
      branch->SetBasketSize(fBasketSize);
   }
}

//______________________________________________________________________________
void TBranchObject::Streamer(TBuffer& R__b)
{
   // Stream an object of class TBranchObject.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TBranchObject::Class(), this);
   } else {
      TDirectory* dirsav = fDirectory;
      fDirectory = 0;  // to avoid recursive calls

      R__b.WriteClassBuffer(TBranchObject::Class(), this);

      // make sure that all TStreamerInfo objects referenced by
      // this class are written to the file
      R__b.ForceWriteInfo(TClass::GetClass(fClassName.Data())->GetStreamerInfo(), kTRUE);

      // if branch is in a separate file save this branch
      // as an independent key
      if (!dirsav) {
         return;
      }
      if (!dirsav->IsWritable()) {
         fDirectory = dirsav;
         return;
      }
      TDirectory* pdirectory = fTree->GetDirectory();
      if (!pdirectory) {
         fDirectory = dirsav;
         return;
      }
      const char* treeFileName = pdirectory->GetFile()->GetName();
      TBranch* mother = GetMother();
      const char* motherFileName = treeFileName;
      if (mother && (mother != this)) {
         motherFileName = mother->GetFileName();
      }
      if ((fFileName.Length() > 0) && strcmp(motherFileName, fFileName.Data())) {
         dirsav->WriteTObject(this);
      }
      fDirectory = dirsav;
   }
}

//______________________________________________________________________________
void TBranchObject::SetupAddresses()
{
   // -- If the branch address is not set,  we set all addresses starting with
   // the top level parent branch.  This is required to be done in order for
   // GetOffset to be correct and for GetEntry to run.
 
   if (fAddress == 0) {
      // try to create object
      if (!TestBit(kWarn)) {
         TClass* cl = TClass::GetClass(fClassName);
         if (cl) {
            TObject** voidobj = (TObject**) new Long_t[1];
            *voidobj = (TObject*) cl->New();
            SetAddress(voidobj);
         } else {
            Warning("GetEntry", "Cannot get class: %s", fClassName.Data());
            SetBit(kWarn);
         }
      }
   }   
}

//______________________________________________________________________________
void TBranchObject::UpdateAddress()
{
   // Update branch addresses if a new object was created.

   void** ppointer = (void**) fAddress;
   if (!ppointer) {
      return;
   }
   TObject* obj = (TObject*) (*ppointer);
   if (obj != fOldObject) {
      fOldObject = obj;
      SetAddress(fAddress);
   }
}
