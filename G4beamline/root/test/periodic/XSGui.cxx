/*
 * $Header$
 * $Log$
 *
 * The graphical user interface for the Neutron Cross section database
 */

#define __XSGUI_CXX

#include <stdio.h>
#include <stdlib.h>

#include <TROOT.h>
#include <TGraph.h>
#include <TFrame.h>
#include <TCanvas.h>
#include <TSystem.h>
#include <TApplication.h>
#include <Riostream.h>

#include "XSGui.h"
#include "XSVarious.h"
#include "XSElementDlg.h"
#include "XSReactionDlg.h"

//ClassImp(XSGui)

const char *filetypes[] = { "All files", "*",
   "Data file", "*.dat",
   "ENDF files", "*.endf",
   0,    0 };

/* ----- XSGui ----- */
XSGui::XSGui(const TGWindow *p, UInt_t w, UInt_t h)
: TGMainFrame(p, w, h)
{
   // Create the main frame. A TGMainFrame is a top level window.

   // Create menubar and popup menus. The hint objects are used to place
   // and group the different menu widgets with respect to eachother.
   menuBarLayout = new TGLayoutHints(
                                     kLHintsTop | kLHintsLeft | kLHintsExpandX,
                                     0, 0, 1, 1);
   menuBarItemLayout = new TGLayoutHints(kLHintsTop | kLHintsLeft,
                                         0, 4, 0, 0);
   menuBarHelpLayout = new TGLayoutHints(kLHintsTop | kLHintsRight);

   // Build up the menus
   // First the Main (FILE) menu
   fileMenu = new TGPopupMenu(fClient->GetRoot());
   fileMenu->AddEntry("&Open...", M_FILE_OPEN);
   fileMenu->AddEntry("&Save", M_FILE_SAVE);
   fileMenu->AddEntry("S&ave as...", M_FILE_SAVEAS);
   fileMenu->AddEntry("&Close", M_FILE_CLOSE);
   fileMenu->AddSeparator();
   fileMenu->AddEntry("&Print", M_FILE_PRINT);
   fileMenu->AddEntry("P&rint setup...", M_FILE_PRINT_SETUP);
   fileMenu->AddSeparator();
   fileMenu->AddEntry("E&xit", M_FILE_EXIT);

   fileMenu->DisableEntry(M_FILE_SAVEAS);
   fileMenu->DisableEntry(M_FILE_CLOSE);

   // The database menu and the current elements in graph
   elemMenu = new TGPopupMenu(fClient->GetRoot());
   elemMenu->AddEntry("&Reaction", M_ELEM_REACTION);
   elemMenu->AddEntry("&Modify", M_ELEM_MODIFY);
   elemMenu->AddEntry("&Clear", M_ELEM_CLEAR);
   elemMenu->AddSeparator();
   elemMenu->AddLabel("Current Elements in Graph");

   // The Currently Editing elements menu
   optMenu = new TGPopupMenu(fClient->GetRoot());
   optMenu->AddEntry("&Zoom", -1);
   optMenu->AddEntry("&Options", -1);

   // The Help Menu
   helpMenu = new TGPopupMenu(fClient->GetRoot());
   helpMenu->AddEntry("&About",M_HELP_ABOUT);

   // Menu button messages are handled by the main frame (i.e. "this")
   // ProcessMessage() method.
   fileMenu->Associate(this);
   elemMenu->Associate(this);
   optMenu->Associate(this);
   helpMenu->Associate(this);

   menuBar = new TGMenuBar(this, 1, 1, kHorizontalFrame);
   menuBar->AddPopup("&File", fileMenu, menuBarItemLayout);
   menuBar->AddPopup("&Element", elemMenu, menuBarItemLayout);
   menuBar->AddPopup("&Options", optMenu, menuBarItemLayout);
   menuBar->AddPopup("&Help", helpMenu, menuBarHelpLayout);

   AddFrame(menuBar, menuBarLayout);

   // Create a ROOT Canvas used for drawing...
   canvasWindow = new TRootEmbeddedCanvas("Canvas",this,
                                          600,400);

   // Initialise the canvas
   canvas = canvasWindow->GetCanvas();
   canvas->SetFillColor(42);
   canvas->SetGrid();
   canvas->GetFrame()->SetFillColor(21);
   canvas->GetFrame()->SetBorderSize(6);
   canvas->SetLogx();
   canvas->SetLogy();
   canvas->Update();

   AddFrame(canvasWindow,
            new TGLayoutHints(kLHintsExpandX | kLHintsExpandY,
                              0, 0, 2, 2));

   statusBar = new TGStatusBar(this, 60, 20);
   AddFrame(statusBar, new TGLayoutHints(kLHintsBottom | kLHintsExpandX,
                                         0, 0, 1, 0));
   statusBar->SetText(PRGNAME);

   SetWindowName(PRGNAME);

   MapSubwindows();

   // we need to use GetDefault...() to initialize the layout algorithm...
   Resize(GetDefaultSize());

   MapWindow();
} // XSGui

/* ----- ~XSGui ----- */
XSGui::~XSGui()
{
   // Delete all created widgets.
   delete menuBarLayout;
   delete menuBarItemLayout;
   delete menuBarHelpLayout;

   delete fileMenu;
   delete elemMenu;
   delete optMenu;
   delete helpMenu;

   delete statusBar;
   delete canvasWindow;
} // ~XSGui

/* ----- CloseWindow ----- */
void
XSGui::CloseWindow()
{
   // Got close message for this MainFrame. Calls parent CloseWindow()
   // (which destroys the window) and terminate the application.
   // The close message is generated by the window manager when its close
   // window menu item is selected.

   TGMainFrame::CloseWindow();
   gApplication->Terminate(0);
} // CloseWindow

/* ----- ProcessMenuMessage ----- */
Bool_t
XSGui::ProcessMenuMessage( Long_t param )
{
   switch (param) {
      case M_FILE_OPEN:
      {
         static TString dir(".");
         TGFileInfo fi;
         fi.fFileTypes = filetypes;
         fi.fIniDir    = StrDup(dir);
         new TGFileDialog(fClient->GetRoot(), this, kFDOpen, &fi);
         dir = fi.fIniDir;
      }
      break;

      case M_FILE_SAVE:
      printf("M_FILE_SAVE\n");
      break;

      case M_FILE_EXIT:
      // this also terminates theApp
      CloseWindow();
      break;

      case M_ELEM_REACTION:
      new XSReactionDlg(fClient->GetRoot(), this, 1, 500,600);
      break;

      case M_HELP_ABOUT:
      // About();
      int   retval;
      new TGMsgBox(fClient->GetRoot(), this,
                   "About", "About....",
                   kMBIconAsterisk, kMBOk, &retval );
      break;

      default:
      break;
   }
   return kTRUE;
} // ProcessMenuMessage

/* ----- ProcessMessage ----- */
Bool_t
XSGui::ProcessMessage(Long_t msg, Long_t param1, Long_t)
{
   // Handle messages send to the XSGui object.
   char   str[100];

   switch (GET_MSG(msg)) {

      case kC_COMMAND:
      switch (GET_SUBMSG(msg)) {

         case kCM_BUTTON:
         snprintf(str,100,
                  "Button was pressed, id = %ld\n",
                  param1);
         statusBar->SetText(str);
         break;

         case kCM_MENUSELECT:
         if (param1>=0)
         statusBar->SetText(menuTip[param1]);
         else
         statusBar->SetText("Undefined Menu!");
         break;

         case kCM_MENU:
         ProcessMenuMessage(param1);
         break;

         default:
         break;
      }
      default:
      break;
   }
   return kTRUE;
} // ProcessMessage

//---- Main program ----------------------------------------------------------

TROOT root("GUI", "GUI test environment");

/* ----- main ----- */
int main(int ac, char *av[])
{
   TApplication theApp("App", &ac, av);

   XSGui mainWindow(gClient->GetRoot(), 400, 220);
   
   XSinitialise();
   
   theApp.Run();
   
   XSfinalise();
   return 0;
} // main
