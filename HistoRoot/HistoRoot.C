/**	HistoRoot.C -- implement a HistoScope like program for Root
 *
 *	HistoRoot presents the user with a GUI window that permits one to
 *	open Root files, select one or more NTuples, and define plots using the
 *	fields of the NTuple, along with C functions and operators.
 *	Four double-sliders are available to apply cuts. The following
 *	plots types are supported:
 *		1-d histograms (wih optional sqrt(sum weights^2) errorbars)
 *		2-d histograms (includes scatter plots, contour plots,
 *				and lego plots; the latter can be rotated)
 *		X-Y plots      (with optional X and Y errorbars)
 *	HistoRoot can also convert an ASCII file to an NTuple (see the Help).
 *
 *	USAGE: root HistoRoot.C
 *	The environment variable ARGS can contain a whitespace-separated
 *	list of files to open (used by the historoot script). Adding filenames
 *	to the root command-line will open them in root, but HistoRoot will
 *	not see them.
 *
 *	Note that the global variable gTntuple is always set to the most
 *	recently selected TNtuple. This makes it easy to do things like
 *	scan the TNtuple via the command-line window:
 *		gTntuple->Scan("EventID:PDGid","PDGid==-13||PDGid==13")
 *	Similarly, gTh1d, gTh2d, and gTgraph point to the most recently
 *	created 1-d hist, 2-d hist, and x-y plot.
 *
 *	This file runs in Root 5.26 using either ACLiC or Cint. That is,
 *	both of these work:
 *		gROOT->ProcessLineSync("-L HistoRoot.C");
 *		gROOT->ProcessLineSync("-L HistoRoot.C+");
 *
 *	Copyright 2007, 2008 by Tom Roberts. All rights reserved.
 *	This program is released under the Gnu Public License.
 *	http://www.gnu.org/copyleft/gpl.html
 *
 *	Acknowledgement:
 *	This program was inspired by the HistoScope program, but it looks
 *	and feels completely differently.
 *
 **/

#include <TGClient.h>	// force Root to load libGui.
#include <TROOT.h>
#include <TSystem.h>
#include <TEnv.h>
#include <TError.h>
#include <TApplication.h>
#include <TFile.h>
#include <TNtuple.h>
#include <TH1.h>
#include <TH2.h>
#include <TGraphErrors.h>
#include <TTreeFormula.h>
#include <TGFrame.h>
#include <TGLabel.h>
#include <TCanvas.h>
#include <TGButton.h>
#include <TString.h>
#include <TGTextEntry.h>
#include <TGMenu.h>
#include <TGFrame.h>
#include <TGListBox.h>
#include <TObjArray.h>
#include <TObjString.h>
#include <TGFileDialog.h>
#include <TList.h>
#include <TKey.h>
#include <TGTextEntry.h>
#include <TGComboBox.h>
#include <TDirectory.h>
#include <TGListBox.h>
#include <TGTextEdit.h>
#include <TGDoubleSlider.h>
#include <TGNumberEntry.h>
#include <TStyle.h>
#include <TBrowser.h>
#include <TGMsgBox.h>
#include <RQ_OBJECT.h>


//@extern TStyle *gStyle;

TNtuple *gTntuple=0;    // global pointing to most recently selected TNtuple
TH1D *gTh1d=0;          // global pointing to most recently created 1-d hist
TH2D *gTh2d=0;          // global pointing to most recently created 2-d hist
TGraph *gTGraph=0;      // global pointing to most recently created X-Y plot


enum PlotType {PLOT_NONE, PLOT_TH1D, PLOT_TH2D, PLOT_XY, PLOT_COMBO};

// Arrays are used for the many different entries -- these are indices in them
enum Entry {X,Y,S1,S2,S3,S4,W,ERRX,ERRY,MAXEV,PDGID,EVID};
#define ALL (EVID+1)
const char *EntryName[] = {"x","y","s1","s2","s3","s4","w","errx","erry",
			"maxev","pdgid","evid"};

/** struct Limits holds all the slider values
 **/
struct Limits {
	float x_min, x_max;
	float y_min, y_max;
	float s1_min, s1_max;
	float s2_min, s2_max;
	float s3_min, s3_max;
	float s4_min, s4_max;
	Limits() { // std::numeric_limits<T> is missing
		x_min = 1.0e99; x_max = -1.0e99;
		y_min = 1.0e99; y_max = -1.0e99;
		s1_min = 1.0e99; s1_max = -1.0e99;
		s2_min = 1.0e99; s2_max = -1.0e99;
		s3_min = 1.0e99; s3_max = -1.0e99;
		s4_min = 1.0e99; s4_max = -1.0e99;
	}
	void set(Entry e, float _min, float _max) {
		if(e==X) {x_min=_min; x_max=_max; }
		if(e==Y) {y_min=_min; y_max=_max; }
		if(e==S1) {s1_min=_min; s1_max=_max; }
		if(e==S2) {s2_min=_min; s2_max=_max; }
		if(e==S3) {s3_min=_min; s3_max=_max; }
		if(e==S4) {s4_min=_min; s4_max=_max; }
	}
	float minimum(Entry e) {
		if(e==X) return x_min;
		if(e==Y) return y_min;
		if(e==S1) return s1_min;
		if(e==S2) return s2_min;
		if(e==S3) return s3_min;
		if(e==S4) return s4_min;
		return 0.0f;
	}
	float maximum(Entry e) {
		if(e==X) return x_max;
		if(e==Y) return y_max;
		if(e==S1) return s1_max;
		if(e==S2) return s2_max;
		if(e==S3) return s3_max;
		if(e==S4) return s4_max;
		return 0.0f;
	}
	void set_x(float v) { if(x_min>v) x_min=v; if(x_max<v) x_max=v; }
	void set_y(float v) { if(y_min>v) y_min=v; if(y_max<v) y_max=v; }
	void set_s1(float v) { if(s1_min>v) s1_min=v; if(s1_max<v) s1_max=v; }
	void set_s2(float v) { if(s2_min>v) s2_min=v; if(s2_max<v) s2_max=v; }
	void set_s3(float v) { if(s3_min>v) s3_min=v; if(s3_max<v) s3_max=v; }
	void set_s4(float v) { if(s4_min>v) s4_min=v; if(s4_max<v) s4_max=v; }
	bool check_s1(float v) { return v >= s1_min && v <= s1_max; }
	bool check_s2(float v) { return v >= s2_min && v <= s2_max; }
	bool check_s3(float v) { return v >= s3_min && v <= s3_max; }
	bool check_s4(float v) { return v >= s4_min && v <= s4_max; }
};

/** class SliderLimits displays a slider and two NumberEntryFields.
 *  It maintains the values of *min and *max, and sends the signal Changed().
 *  The values of *min and *max at the Constructor are used as the range limits.
 **/
class SliderLimits {
	RQ_OBJECT("SliderLimits")
private:
	Float_t *min;
	Float_t *max;
	TGDoubleHSlider *slider;
	TGNumberEntryField *min_entry;
	TGNumberEntryField *max_entry;
public:
	SliderLimits(TGCompositeFrame *f, const char *name, const char *title, Float_t *_min, Float_t *_max) {
		min = _min;
		max = _max;
		TGGroupFrame *g = new TGGroupFrame(f,name);
		TGLabel *l = new TGLabel(g,title);
		g->AddFrame(l,new TGLayoutHints(kLHintsCenterX|kLHintsExpandX));
		slider = new TGDoubleHSlider(g,160);
		slider->SetRange(*min,*max);
		slider->SetPosition(*min,*max);
		slider->Connect("PositionChanged()","SliderLimits",this,"positionChanged()");
		g->AddFrame(slider,new TGLayoutHints(kLHintsExpandX));
		TGHorizontalFrame *h = new TGHorizontalFrame(g);
		min_entry = new TGNumberEntryField(h,101);
		min_entry->SetNumber(*min);
		min_entry->Connect("ReturnPressed()","SliderLimits",this,"returnPressed()");
		min_entry->SetWidth(80);
		h->AddFrame(min_entry);
		max_entry = new TGNumberEntryField(h,102);
		max_entry->SetNumber(*max);
		max_entry->Connect("ReturnPressed()","SliderLimits",this,"returnPressed()");
		max_entry->SetWidth(80);
		h->AddFrame(max_entry);
		g->AddFrame(h);
		f->AddFrame(g);
	}
	virtual ~SliderLimits() {
		//delete slider;
		//delete min_entry;
		//delete max_entry;
	}
	void positionChanged() {
		slider->GetPosition(min,max);
		min_entry->SetNumber(*min);
		max_entry->SetNumber(*max);
		Changed();
	}
	void returnPressed() {
		*min = min_entry->GetNumber();
		*max = max_entry->GetNumber();
		slider->SetPosition(*min,*max);
		Changed();
	}
	void Changed() { Emit("Changed()"); }	//*SIGNAL*
};


/** class PlotList holds a list of all Plot-s.
 *  Note that Cint cannot handle std::vector<> correctly, so this is 
 *  a work-around.
 **/
const int MAX_PLOT=1000;
class Plot;
class PlotList {
public:
	static int size;
	static Plot *array[MAX_PLOT];
	static void append(Plot *p) {
		if(size < MAX_PLOT) array[size++] = p;
	}
	static void remove(Plot *p) {
		for(int i=0; i<size; ++i) {
			if(array[i] == p) {
				for(int j=i+1; j<size; ++j) {
					array[i++] = array[j];
				}
				--size;
				break;
			}
		}
	}
};
int PlotList::size = 0;
Plot *PlotList::array[MAX_PLOT];


const int NPARTICLES=50000;
/** class Particle computes and prints the numbers of particles.
 * (Cint won't let me use std::map<int,int>.)
 **/
class Particle {
	static unsigned int num[NPARTICLES];
	static unsigned int other;
	static bool flag;
public:
	static void clear() {
		for(int i=0; i<NPARTICLES; ++i)
			num[i] = 0;
		other = 0;
		flag = false;
	}
	static void incr(int id) {
		flag = true;
		id += NPARTICLES/2;
		if(id >=0 && id < NPARTICLES)
			++num[id];
		else
			++other;
	}
	static void print(bool cuts) {
		if(!flag) return;
		if(cuts)
		    printf("Summary of Particle Types (after slider cuts):\n");
		else
		    printf("Summary of Particle Types:\n");
		for(int i=0; i<NPARTICLES; ++i) {
			const char *p = "";
			int j = i - NPARTICLES/2;
			if(j == -2212) p = "anti_proton";
			if(j == -2112) p = "anti_neutron";
			if(j == -321) p = "kaon-";
			if(j == -311) p = "anti_kaon0";
			if(j == -211) p = "pi-";
			if(j == -16) p = "anti_nu_tau";
			if(j == -14) p = "anti_nu_mu";
			if(j == -13) p = "mu+";
			if(j == -12) p = "anti_nu_e";
			if(j == -11) p = "e+";
			if(j == 11) p = "e-";
			if(j == 12) p = "nu_e";
			if(j == 13) p = "mu-";
			if(j == 14) p = "nu_mu";
			if(j == 16) p = "nu_tau";
			if(j == 22) p = "gamma";
			if(j == 111) p = "pi0";
			if(j == 211) p = "pi+";
			if(j == 311) p = "kaon0";
			if(j == 321) p = "kaon+";
			if(j == 2112) p = "neutron";
			if(j == 2212) p = "proton";
			if(num[i] != 0)
			    printf("%5d %8u %s\n",j,num[i],p);
		}
		if(other != 0)
			printf("Other particles (mostly ions and nuclei): %u entries\n",other);
	}
};
unsigned int Particle::num[NPARTICLES];
unsigned int Particle::other;
bool Particle::flag=false;



/** class Plot is a single plot
 **/
class Plot {
	RQ_OBJECT("Plot")
public:
	char name[16];
	TNtuple **ntuples;
	int nNtuples;
	PlotType type;
	const char *expr[ALL];
	long max_events;
	TH1D *th1d;
	TH2D *th2d;
	TGraphErrors *tgraph;
	TCanvas *canvas;
	TGCompositeFrame *dataWindow;
	Limits limits;
	SliderLimits *sliderLimits[ALL];
	int nx_bins;
	int ny_bins;
	TGNumberEntryField *nx_entry;
	TGNumberEntryField *ny_entry;
	TGNumberEntryField *maxev_entry;
	TTreeFormula *formula[ALL];
	bool h1errorbars;
	static int number;
public:
	/// Constructor.
	// The first arg should be TNtuple *_nt[], but CINT has a bug
	// that makes that fail in Root 5.18. void* is a workaround
	// (with dynamic_cast<TNtuple**> below). Ditto for _e.
	Plot(void *_nt, int _nNtuples, PlotType _type,
						void *_e, bool _h1errorbars);

	/// Destructor.
	virtual ~Plot();

	/// drawCanvas() will draw the window/canvas containing the Plot
	void drawCanvas();

	/// drawDataWindow() will draw the window that controls the data
	/// into the plot (binning, sliders for cuts, etc.).
	void drawDataWindow();

	/// plotClosed() is connected to CloseWindow() of Plot window.
	/// closing plot window also closes dataWindow.
	void plotClosed() {
		if(dataWindow) dataWindow->DestroyWindow();
		dataWindow = 0;
		PlotList::remove(this);
	}

	/// dataWindowClosed() is connected to CloseWindow() of dataWindow.
	/// dataWindow can be closed independent of the plot window.
	void dataWindowClosed() {
		dataWindow->Disconnect();
		dataWindow = 0;
	}

	/// setNtuple() will setup to process one TNtuple
	void setNtuple(TNtuple *nt);

	/// scanForLimits() will scan the NTuple to determine the limits.
	void scanForLimits();

	/// scan() will scan the NTuple, re-building the plot.
	void scan();

	/// slider() is connected to the sliders.
	void slider();

	/// saveConfig() writes this Plot's config to out.
	void saveConfig(FILE *out);

	/// getTitle() returns the title of the plot.
	const char *getTitle() {
		if(th1d) return th1d->GetTitle();
		if(th2d) return th2d->GetTitle();
		if(tgraph) return tgraph->GetTitle();
		return "";
	}
};
int Plot::number=0;

const int MAXVAR=1000;
/** class VariableList maintains the list of variable definitions
 **/
class VariableList {
	char **names;
	char **exprs;
	int nvar;
	char *filename;
	TGTransientFrame *dialog;
	TGTextEdit *textEdit;
public:
	/// constructor -- read $HOME/.historoot.
	VariableList() { 
		names = new char*[MAXVAR];
		exprs = new char*[MAXVAR];
		nvar = 0;
		dialog = 0;
		textEdit = 0;
		char line[1024];
		strcpy(line,gSystem->HomeDirectory());
		strcat(line,"/.historoot");
		assert(strlen(line)<sizeof(line));
		filename = StrDup(line);
		clearAndRead();
	}

	void clearAndRead() {
		for(int i=0; i<nvar; ++i)
			free(names[i]);
		nvar = 0;
		FILE *in = fopen(filename,"r");
		if(in) {
			char line[1024];
			while(fgets(line,sizeof(line),in)) {
				char *p = strpbrk(line,"\r\n");
				if(p) *p = '\0';
				if(line[0] == '#' || line[0] == '\0') continue;
				add(line);
			}
			fclose(in);
		} else {
			// one default variable as an example
			add("Ptot=sqrt(Px*Px+Py*Py+Pz*Pz)");
		}
	}

	/// size() returns the # of variables defined.
	int size() { return nvar; }

	/// name() returns the name of the i-th variable.
	const char *name(int i) 
	    { return (const char *)names[i]; }

	/// expr() returns the expression of the i-th variable.
	const char *expr(int i) 
	    { return (const char *)exprs[i]; }

	// isValid() returns true if the i-th variable is valid for the ntuple
	bool isValid(int i, TNtuple *nt) {
		if(i < 0 || i >= nvar || nt == 0) return false;
		TTreeFormula t("test",exprs[i],nt);
		return t.GetTree() != 0;
	}

	/// apply() will apply the variable to the NTuple.
	bool apply(int i, TNtuple *nt) 
		{ return nt->SetAlias(names[i],exprs[i]); }

	/// applyAll() will apply all variables to the NTuple
	void applyAll(TNtuple *nt) {
		for(int i=0; i<nvar; ++i)
			apply(i,nt);
	}

	/// add() will add a new variable from "name=expr".
	/// If name is already present, its expression is changed
	void add(const char *line) {
		char *n = StrDup(line); // deliberate small memory leak
		char *v = strchr(n,'=');
		if(v) {
			*v++ = '\0';
			for(int i=0; i<nvar; ++i) {
				assert(names[i] != 0);
				if(strcmp(names[i],n) == 0) {
					exprs[i] = v;
					return;
				}
			}
			if(nvar >= MAXVAR) {
				printf("Too many variables (> 1000)\n");
				return;
			}
			names[nvar] = n;
			exprs[nvar++] = v;
		}
	}

	void edit();

	void save() {
		closeEditWindow();
		if(textEdit) {
			textEdit->GetText()->Save(filename);
			clearAndRead();
		}
	}

	void closeEditWindow() {
		if(dialog) dialog->CloseWindow();
		dialog = 0;
	}

	/// expand() will expand s, replacing all variable names with their
	/// expressions. returns a pointer to a string that should be
	/// deleted when it is no longer needed. fields is a colon-separated
	/// list of fields that should never be expanded; MUST have bookend :s.
	/// (Calls itself recursively in case some variable(s) are defined in
	/// terms of other variable(s)).
	const char *expand(const char *s, TString fields="") {
		TString out;
		bool again=false;
		assert(s != 0);
		int n = strlen(s);
		for(int i=0; i<n; ++i) {
			char c = s[i];
			if(isdigit(c)) {
				while(i<n) {
					c = s[i];
					if(isdigit(c) || c=='.') { 
						out += c;
						++i;
					} else if(c=='e' || c=='E' ||
					          c=='d' || c=='D') {
						out += c;
						++i;
						c = s[i];
						if(c=='+' || c=='-') {
							out += c;
							++i;
						}
					} else {
						break;
					}
				}
				--i;
			} else if(isalpha(c) || c=='_') {
				int j;
				for(j=i+1; j<n; ++j) {
					c = s[j];
					if(!isalpha(c) && !isdigit(c) && c!='_')
						break;
				}
				TString id;
				for(int k=i; k<j; ++k) id += s[k];
				int k=-1;
				if(!isfield(id,fields))
					k = find(id.Data());
				if(k >= 0) {
					out += '(';
					out += exprs[k];
					out += ')';
					again = true;
				} else {
					out += id;
				}
				i = j - 1;
			} else {
				out += c;
			}
		}
		// expand recursively until no variables were found
		if(again) return expand(out.Data(),fields);
		return StrDup(out.Data());
	}

	/// find() will return the index in names for the string, -1 if none
	int find(const char *s) {
		assert(s != 0);
		for(int i=0; i<nvar; ++i) {
			assert(names[i] != 0);
			if(strcmp(s,names[i]) == 0) return i;
		}
		return -1;
	}

	/// isfield() will return true if :s: is found in fields.
	/// fields must have bookend colons.
	bool isfield(TString s, TString fields) {
		TString tmp(':'); tmp+=s; tmp+=':';
		return fields.Contains(tmp);
	}
};


const int MAXTAB=16;

/** class Tab manages tabs between fields.
 *
 *  Because of the limitations of SetFocus(), only works for TGTextEntry-s.
 *  Widgets must be registered in tab order (circular).
 **/
class Tab {
	int index;
	static TGTextEntry *entry[MAXTAB];
	static int nTab;
public:
	Tab() { index=nTab; }
	void tab() {
		for(int i=index+1; i!= index; ++i) {
			if(i >= nTab) i=0;
			if(!entry[i]->IsEnabled()) continue;
			entry[i]->SetFocus();
			break;
		}
	}
	static void registerWidget(TGTextEntry *_entry) {
		if(nTab >= MAXTAB) return;
		_entry->Connect("TabPressed()","Tab",new Tab(),"tab()");
		entry[nTab++] = _entry;
	}
};
TGTextEntry *Tab::entry[MAXTAB];
int Tab::nTab = 0;

/** class HistoRootWindow is the main program (dialog box)
 **/
class HistoRootWindow {
	RQ_OBJECT("HistoRootWindow")
private:
	TList ntuples;
	TObjArray asciiNtuples;
	TGListBox *ntupleListBox;
	PlotType type;
	TGCheckButton *h1errorbars;
	TGListBox *fieldListBox;
	TGTextEntry *expr[ALL];
	TGTransientFrame *dialog;
	TGTextEntry *comboPlotTitle;
	TGListBox *comboPlotListBox;
	int firstToSave;
	static TGRadioButton *radio[3];
	friend class FieldMenu;
public:
	static HistoRootWindow *singleton;
	static TString *directory; // preserves previous directory
	static TGMainFrame *window;
	static UInt_t w, h;
	static TNtuple *selectedNtuple;
	VariableList *variables;
public:
	/// Constructor (defaults work fine)
	HistoRootWindow();

	/// Destructor.
	virtual ~HistoRootWindow();

	/// refresh() will refresh the contents of the TNtuple list
	void refresh();

	/// doCommand() handles all of the menu item (etc.) commands.
	void doCommand(Int_t id);

	/// openFileDialog() opens a file (via OpenFile dialog)
	void openFileDialog();
	
	/// openFile() will open either a Root or an ASCII file, using
	/// an intelligent algorithm to determine which type it is.
	/// Returns false if failure.
	bool openFile(const TString& filename);

	/// closeAllFiles() closes all open Root files
	void closeAllFiles();

	/// selectNTuple() is called when the user selects an NTuple.
	/// id is the index in ntuples.
	void selectNTuple(int id);

	/// createPlot() will create a new plot using expressions from expr[]
	void createPlot();

	/// createPlot() will create a new plot
	void createPlot(char *arg[ALL]);

	/// createComboPlotDialog() will open a dialog for a new Combo Plot
	void createComboPlotDialog();

	/// createComboPlot() will create a new combo-plot
	void createComboPlot();

	/// saveConfig() will save the Plot configuration(s) for the
	/// currently selected NTuple(s).
	void saveConfig();

	/// loadConfig() will load a previously saved config (dialog box)
	void loadConfig();

	/// isValidIdentifier() returns true for valid C identifiers.
	static bool isValidIdentifier(const char *s);

	/// checkExpr() will check an expression for validity
	bool checkExpr(const char *e);

	/// command() is Connect-ed to all of the menu signals
	static void command(Int_t);

	/// radioButton() is the Comand for all of the radio buttons
	static void radioButton(Int_t);

	/// command2() is Connect-ed to the NTuple ListBox
	static void command2(Int_t,Int_t);

	/// ProcessedEvent() is connected to the TGTextEntry-s that handle mouse
	static void ProcessedEvent(Event_t*);

	/// showHelpWindow() will display the Help window.
	static void showHelpWindow();

	/// listNtuples() puts all TNtuple-s from *d into the ntuples list,
	/// recursively.
	/// d=0 means clear ntuples and scan all open TFile-s and add the
	/// asciiNtuples.
	void listNtuples(TDirectory *d=0);
};
TGRadioButton *HistoRootWindow::radio[3] = {0,0,0};
TString *HistoRootWindow::directory = 0;
HistoRootWindow *HistoRootWindow::singleton=0;
TGMainFrame *HistoRootWindow::window=0;
UInt_t HistoRootWindow::w=0, HistoRootWindow::h=0;
TNtuple *HistoRootWindow::selectedNtuple=0;

/** class FieldMenu handles a popup menu with the current field names
 *
 **/
class FieldMenu {
	RQ_OBJECT("FieldMenu")
	static FieldMenu *fieldMenu;
	TGPopupMenu *menu;
	TGTextEntry *entry;
public:
	FieldMenu(TGTextEntry *_entry, int x, int y);
	~FieldMenu();

	/// doCommand() executes a command
	void doCommand(Int_t id);

	/// popup will populate the menu and pop it up
	static void popup(TGTextEntry *entry, int x, int y);
};
FieldMenu *FieldMenu::fieldMenu = 0;
void FieldMenu::popup(TGTextEntry *entry, int x, int y)
{
	if(!HistoRootWindow::selectedNtuple) return;
	if(fieldMenu) delete fieldMenu;
	fieldMenu = new FieldMenu(entry,x,y);
}

FieldMenu::FieldMenu(TGTextEntry *_entry, int x, int y)
{
	entry = _entry;

	const TGFrame *f = entry->GetFrameFromPoint(x,y);
	for(int i=0; i<4; ++i) {
		x += f->GetX();
		y += f->GetY();
		f = dynamic_cast<const TGFrame*>(f->GetParent());
	}
	menu = new TGPopupMenu(f);
	menu->AddLabel("NTuple Fields");
	TGListBox *lb = HistoRootWindow::singleton->fieldListBox;
	int n = lb->GetNumberOfEntries();
	if(n <= 16) {
		for(int i=0; i<n; ++i)
			menu->AddEntry(lb->GetEntry(i)->GetTitle(),i);
	} else {
		TGPopupMenu *m=0;
		int j=999;
		for(int i=0; i<n; ++i) {
			if(++j >= 16) {
				m = new TGPopupMenu(f);
				menu->AddPopup("More Fields",m);
				j = 0;
			}
			m->AddEntry(lb->GetEntry(i)->GetTitle(),i);
		}
	}
	menu->Connect("Activated(Int_t)","FieldMenu",this,"doCommand(Int_t)");
	menu->PlaceMenu(x,y,false,true);
}

FieldMenu::~FieldMenu()
{
	if(menu) delete menu;
	menu = 0;
}

void FieldMenu::doCommand(Int_t id)
{
	entry->AppendText(HistoRootWindow::singleton->fieldListBox->GetEntry(id)->GetTitle());
}


const int MAXTOKEN=1024;	// Max # tokens in an AsciiFile line
const int MAXLINE=4096;		// Max # characters in an AsciiFile line
const int MAXNAME=32;		// Max # characters in an AsciiFile field name

/** class AsciiFile will convert an ASCII file to a TNtuple
 **/
class AsciiFile {
	static char *token[MAXTOKEN];
	static char *fieldname[MAXTOKEN];
public:
	/// tokenize() will split the tokens of line into token[].
	/// The line is trim()-ed, then tokens are separated by /[ \t,] */ 
	/// NOTE: modifies line, and token[] points into it.
	static int tokenize(char *line);

	/// convert() will convert an ASCII file to a TNtuple.
	static TNtuple *convert(const char *filename);
};
char *AsciiFile::token[MAXTOKEN] = { 0 };
char *AsciiFile::fieldname[MAXTOKEN] = { 0 };

int AsciiFile::tokenize(char *line)
{
	assert(line != 0);
	// remove trailing whitespace (incl \r and \n)
	int i=strlen(line)-1;
	while(i >= 0 && isspace(line[i])) line[i--] = '\0';

	char *p = line;
	int n=0;
	while(n < MAXTOKEN) {
		while(isspace(*p)) ++p;
		if(*p == '\0') break;
		token[n++] = p;
		while(*p != ' ' && *p != '\t' && *p != ',' && *p != '\0') ++p;
		if(*p == '\0') break;
		*p++ = '\0';
	}

	return n;
}

TNtuple *AsciiFile::convert(const char *filename)
{
	char line[MAXLINE];

	FILE *f = fopen(filename,"r");
	if(!f) {
		fprintf(stderr,"Cannot read '%s'\n",filename);
		return 0;
	}

	// find first non-comment line, count fields
	int nfields=0;
	while(fgets(line,sizeof(line),f)) {
		nfields = tokenize(line);
		if(*token[0] != '#') break;
		nfields = 0;
	}
	if(nfields == 0) {
		fprintf(stderr,"File '%s' invalid format (no row found).\n",
							filename);
		fclose(f);
		return 0;
	}

	// verify the first-row fields are all doubles
	for(int i=0; i<nfields; ++i) {
		char *p=0;
		assert(token[i] != 0);
		strtod(token[i],&p);
		if(p == 0 || *p != '\0') {
		    fprintf(stderr,"File '%s' invalid format (non-float).\n",
							filename);
		    fclose(f);
		    return 0;
		}
	}

	// set default field names
	for(int i=0; i<nfields; ++i) {
		fieldname[i] = new char[MAXNAME];
		sprintf(fieldname[i],"c%d",i+1);
	} 
	for(int i=nfields; i<MAXTOKEN; ++i)
		fieldname[i] = 0;

	// look for comment containing field names
	rewind(f);
	while(fgets(line,sizeof(line),f)) {
		if(line[0] != '#') break;
		if(tokenize(line+1) == nfields) {
			for(int i=0; i<nfields; ++i) {
				assert(fieldname[i] != 0);
				assert(token[i] != 0);
				if(HistoRootWindow::isValidIdentifier(token[i]))
					strncpy(fieldname[i],token[i],MAXNAME);
			}
			break;
		}
	}
	rewind(f);

	// construct varlist
	char varlist[MAXLINE] = "";
	for(int i=0; i<nfields; ++i) {
		if(i > 0) strcat(varlist,":");
		strcat(varlist,fieldname[i]);
	}

	// get name of the TNtuple
	assert(filename != 0);
#ifdef STUB
	const char *name = strrchr(filename,'/');
#else // STUB
	const char *name=0;
	name = strrchr(filename,'/');
#endif //STUB
	if(!name) name = strrchr(filename,'\\');
	if(name) 
		++name;
	else
		name = filename;

	// construct the TNtuple and fill it
	gROOT->cd(); // put it into this directory
	TNtuple *nt = new TNtuple(name,name,varlist);
	float *vars = new float[nfields];
	printf("AsciiFile::convert reading '%s'...\r",name); fflush(stdout);
	int nLines=0;
	while(fgets(line,sizeof(line),f)) {
		if(line[0] == '#') continue;
		int n = tokenize(line);
		if(n <= 0) continue;
		if(n > nfields) n = nfields;
		for(int i=0; i<n; ++i)
			vars[i] = atof(token[i]);
		while(n < nfields)
			vars[n++] = 0.0;
		nt->Fill(vars);
		if(++nLines%1000 == 0)
			printf("AsciiFile::convert reading '%s' %d\r",name,
						nLines); fflush(stdout);
	}
	delete vars;
	printf("AsciiFile::convert reading '%s' %d done.\n",name,nLines);
	fflush(stdout);

	fclose(f);

	return nt;
}


HistoRootWindow::HistoRootWindow() : ntuples(), asciiNtuples()
{
#ifdef __CINT__
	printf("Running as a macro.\n");
#else
	printf("Running compiled version.\n");
#endif
	singleton = this;
	selectedNtuple = 0;
	ntupleListBox = 0;
	type = PLOT_NONE;
	h1errorbars = 0;
	for(int i=0; i<ALL; ++i) expr[i] = 0;
	dialog = 0;
	comboPlotTitle = 0;
	comboPlotListBox = 0;
	directory = new TString(".");
	firstToSave = 0;

	printf("\n\nThis Root command window gets error messages and status "
		"information.\nIt can usually be ignored.\n\n\n");

	// have all new canvases show the editor initially.
	gEnv->SetValue("Canvas.ShowEditor",1);

	// set window icon (Mac OS X, Windows, Linux -- .png alays present)
	window = new TGMainFrame(gClient->GetRoot(),200,200,kVerticalFrame);
	char tmp[1024];
	sprintf(tmp,"%s/historooticon.png",getenv("HISTO_DIR"));
	assert(strlen(tmp)<sizeof(tmp)); // snprintf() not available
	window->SetIconPixmap(tmp);

	// get the size of an "M" (for layout)
	gVirtualX->GetTextExtent(w,h,"M");
	if(w < 8) w = 8;
	if(h < 10) h = 10;

	// Menu
	TGMenuBar *menu = new TGMenuBar(window);
	window->AddFrame(menu, 
		     new TGLayoutHints(kLHintsTop|kLHintsLeft|kLHintsExpandX,0,0,1,1));
	TGPopupMenu *fileMenu = menu->AddPopup("&File");
	fileMenu->AddEntry("&Open File...",1);
	fileMenu->AddSeparator();
	fileMenu->AddEntry("&Close ALL Files",2);
	fileMenu->AddSeparator();
	fileMenu->AddEntry("&Edit Variables...",5);
	fileMenu->AddSeparator();
	fileMenu->AddEntry("&Root Browser...",11);
	fileMenu->AddSeparator();
	fileMenu->AddEntry("E&xit",99);
	fileMenu->Connect("Activated(Int_t)","HistoRootWindow",this,"command(Int_t)");
	TGPopupMenu *plotMenu = menu->AddPopup("&Plot");
	plotMenu->AddEntry("Combo Plot",31);
	plotMenu->AddSeparator();
	plotMenu->AddEntry("&Save Config...",3);
	plotMenu->AddEntry("&Load Config...",4);
	plotMenu->Connect("Activated(Int_t)","HistoRootWindow",this,"command(Int_t)");
	TGPopupMenu *helpMenu = menu->AddPopup("&Help");
	helpMenu->AddEntry("Help",70);
	helpMenu->AddEntry("About",71);
	helpMenu->Connect("Activated(Int_t)","HistoRootWindow",this,"command(Int_t)");

	// Layout the main HistoRoot window
	TGLabel *l1 = new TGLabel(window,"Use the File menu to open file(s), select an NTuple and Plot type, then enter expressions below.");
	window->AddFrame(l1,
		     new TGLayoutHints(kLHintsCenterX,5,5,5,5));
	TGGroupFrame *f1 = new TGGroupFrame(window,"NTuple",kVerticalFrame);
	window->AddFrame(f1,new TGLayoutHints(kLHintsExpandX,5,5,5,5));
	ntupleListBox = new TGListBox(f1,30);
	ntupleListBox->SetMultipleSelections(true);
	f1->AddFrame(ntupleListBox, 
		     new TGLayoutHints(kLHintsExpandX,5,5,5,5));
	ntupleListBox->IntegralHeight(true);
	ntupleListBox->Resize(64*w,10*h);
	ntupleListBox->IntegralHeight(true);
	ntupleListBox->Connect("Selected(Int_t,Int_t)","HistoRootWindow",this,
				"command2(Int_t,Int_t)");
	f1 = new TGGroupFrame(window,"Plot Type",kVerticalFrame);
	window->AddFrame(f1,new TGLayoutHints(kLHintsExpandX,5,5,5,5));
	TGHorizontalFrame *f1a = new TGHorizontalFrame(f1);
	f1->AddFrame(f1a,new TGLayoutHints(kLHintsExpandX,0,0,0,0));
	radio[0] = new TGRadioButton(f1a,"1d Histogram                        ",41);
	radio[0]->SetCommand("HistoRootWindow::radioButton(41)");
	f1a->AddFrame(radio[0]);
	h1errorbars = new TGCheckButton(f1a,"errorbars: sqrt(sum of weights squared)",49);
	f1a->AddFrame(h1errorbars);
	radio[1] = new TGRadioButton(f1,"2d Histogram (scatter plot, ...)",42);
	radio[1]->SetCommand("HistoRootWindow::radioButton(42)");
	f1->AddFrame(radio[1]);
	radio[2] = new TGRadioButton(f1,"X-Y Plot",43);
	radio[2]->SetCommand("HistoRootWindow::radioButton(43)");
	f1->AddFrame(radio[2]);
	TGHorizontalFrame *f2 = new TGHorizontalFrame(window);
	window->AddFrame(f2,
			new TGLayoutHints(kLHintsExpandX|kLHintsExpandY,0,0,0,0));
	fieldListBox = new TGListBox(f2);
	f2->AddFrame(fieldListBox,
			new TGLayoutHints(kLHintsLeft|kLHintsExpandY,5,5,5,5));
	fieldListBox->IntegralHeight(true);
	fieldListBox->Resize(20*w,25*h);
	fieldListBox->IntegralHeight(true);
	fieldListBox->AddEntry("(no NTuple selected)",0);
	TGVerticalFrame *f3 = new TGVerticalFrame(f2);
	f2->AddFrame(f3,
			new TGLayoutHints(kLHintsExpandX|kLHintsExpandY,5,5,5,5));
	f3->AddFrame(new TGLabel(f3,"     Enter expressions below using the fields of the NTuple (listed on left)"));
	f3->AddFrame(new TGLabel(f3,"     and C arithmetic functions and operators."));
	f3->AddFrame(new TGLabel(f3,"     A right-click will insert from the list of fields of the NTuple."));
	// x
	TGHorizontalFrame *fx = new TGHorizontalFrame(f3);
	TGLabel *lx = new TGLabel(fx,"x: ");
	fx->AddFrame(lx, new TGLayoutHints(kLHintsLeft,10,0,0,0));
	expr[X] = new TGTextEntry(fx,"");
	expr[X]->Resize(50*w,2*h);
	expr[X]->Connect("ProcessedEvent(Event_t*)","HistoRootWindow",this,"ProcessedEvent(Event_t*)");
	expr[X]->Connect("ReturnPressed()","HistoRootWindow",this,"command(=50)");
	Tab::registerWidget(expr[X]);
	fx->AddFrame(expr[X]);
	f3->AddFrame(fx);
	// y
	TGHorizontalFrame *fy = new TGHorizontalFrame(f3);
	TGLabel *ly = new TGLabel(fy,"y: ");
	fy->AddFrame(ly, new TGLayoutHints(kLHintsLeft,9,0,0,0));
	expr[Y] = new TGTextEntry(fy,"");
	expr[Y]->Resize(50*w,2*h);
	expr[Y]->Connect("ProcessedEvent(Event_t*)","HistoRootWindow",this,"ProcessedEvent(Event_t*)");
	expr[Y]->Connect("ReturnPressed()","HistoRootWindow",this,"command(=50)");
	Tab::registerWidget(expr[Y]);
	fy->AddFrame(expr[Y]);
	f3->AddFrame(fy);
	// w
	TGHorizontalFrame *fw = new TGHorizontalFrame(f3);
	TGLabel *lw = new TGLabel(fw,"weight:  ");
	fw->AddFrame(lw, new TGLayoutHints(kLHintsLeft,7,0,0,0));
	expr[W] = new TGTextEntry(fw,"");
	expr[W]->Resize(46*w,2*h);
	expr[W]->Connect("ProcessedEvent(Event_t*)","HistoRootWindow",this,"ProcessedEvent(Event_t*)");
	expr[W]->Connect("ReturnPressed()","HistoRootWindow",this,"command(=50)");
	Tab::registerWidget(expr[W]);
	fw->AddFrame(expr[W]);
	f3->AddFrame(fw);
	// errorbar_x
	TGHorizontalFrame *ferrx = new TGHorizontalFrame(f3);
	TGLabel *lerrx = new TGLabel(ferrx,"errorbar X: ");
	ferrx->AddFrame(lerrx, new TGLayoutHints(kLHintsLeft,7,0,0,0));
	expr[ERRX] = new TGTextEntry(ferrx,"");
	expr[ERRX]->Resize(44*w,2*h);
	expr[ERRX]->Connect("ProcessedEvent(Event_t*)","HistoRootWindow",this,"ProcessedEvent(Event_t*)");
	expr[ERRX]->Connect("ReturnPressed()","HistoRootWindow",this,"command(=50)");
	Tab::registerWidget(expr[ERRX]);
	ferrx->AddFrame(expr[ERRX]);
	f3->AddFrame(ferrx);
	// errorbar_y
	TGHorizontalFrame *ferry = new TGHorizontalFrame(f3);
	TGLabel *lerry = new TGLabel(ferry,"errorbar Y: ");
	ferry->AddFrame(lerry, new TGLayoutHints(kLHintsLeft,7,0,0,0));
	expr[ERRY] = new TGTextEntry(ferry,"");
	expr[ERRY]->Resize(44*w,2*h);
	expr[ERRY]->Connect("ProcessedEvent(Event_t*)","HistoRootWindow",this,"ProcessedEvent(Event_t*)");
	expr[ERRY]->Connect("ReturnPressed()","HistoRootWindow",this,"command(=50)");
	Tab::registerWidget(expr[ERRY]);
	ferry->AddFrame(expr[ERRY]);
	f3->AddFrame(ferry);
	//
	f3->AddFrame(new TGLabel(f3,"        The sliders below impose range cuts on the NTuple:"));
	// s1
	TGHorizontalFrame *fs1 = new TGHorizontalFrame(f3);
	TGLabel *ls1 = new TGLabel(fs1,"s1: ");
	fs1->AddFrame(ls1, new TGLayoutHints(kLHintsLeft,3,0,0,0));
	expr[S1] = new TGTextEntry(fs1,"");
	expr[S1]->Resize(50*w,2*h);
	expr[S1]->Connect("ProcessedEvent(Event_t*)","HistoRootWindow",this,"ProcessedEvent(Event_t*)");
	expr[S1]->Connect("ReturnPressed()","HistoRootWindow",this,"command(=50)");
	Tab::registerWidget(expr[S1]);
	fs1->AddFrame(expr[S1]);
	f3->AddFrame(fs1);
	// s2
	TGHorizontalFrame *fs2 = new TGHorizontalFrame(f3);
	TGLabel *ls2 = new TGLabel(fs2,"s2: ");
	fs2->AddFrame(ls2, new TGLayoutHints(kLHintsLeft,3,0,0,0));
	expr[S2] = new TGTextEntry(fs2,"");
	expr[S2]->Resize(50*w,2*h);
	expr[S2]->Connect("ProcessedEvent(Event_t*)","HistoRootWindow",this,"ProcessedEvent(Event_t*)");
	expr[S2]->Connect("ReturnPressed()","HistoRootWindow",this,"command(=50)");
	Tab::registerWidget(expr[S2]);
	fs2->AddFrame(expr[S2]);
	f3->AddFrame(fs2);
	// s3
	TGHorizontalFrame *fs3 = new TGHorizontalFrame(f3);
	TGLabel *ls3 = new TGLabel(fs3,"s3: ");
	fs3->AddFrame(ls3, new TGLayoutHints(kLHintsLeft,3,0,0,0));
	expr[S3] = new TGTextEntry(fs3,"");
	expr[S3]->Resize(50*w,2*h);
	expr[S3]->Connect("ProcessedEvent(Event_t*)","HistoRootWindow",this,"ProcessedEvent(Event_t*)");
	expr[S3]->Connect("ReturnPressed()","HistoRootWindow",this,"command(=50)");
	Tab::registerWidget(expr[S3]);
	fs3->AddFrame(expr[S3]);
	f3->AddFrame(fs3);
	// s4
	TGHorizontalFrame *fs4 = new TGHorizontalFrame(f3);
	TGLabel *ls4 = new TGLabel(fs4,"s4: ");
	fs4->AddFrame(ls4, new TGLayoutHints(kLHintsLeft,3,0,0,0));
	expr[S4] = new TGTextEntry(fs4,"");
	expr[S4]->Resize(50*w,2*h);
	expr[S4]->Connect("ProcessedEvent(Event_t*)","HistoRootWindow",this,"ProcessedEvent(Event_t*)");
	expr[S4]->Connect("ReturnPressed()","HistoRootWindow",this,"command(=50)");
	Tab::registerWidget(expr[S4]);
	fs4->AddFrame(expr[S4]);
	f3->AddFrame(fs4);
	//
	f3->AddFrame(new TGLabel(f3,"      See the Help for explanations of the following fields:"));
	// max events
	TGHorizontalFrame *fs5 = new TGHorizontalFrame(f3);
	ls4 = new TGLabel(fs5,"Max Events:");
	fs5->AddFrame(ls4, new TGLayoutHints(kLHintsLeft,3,0,0,0));
	expr[MAXEV] = new TGTextEntry(fs5,"");
	expr[MAXEV]->Resize(6*h,2*h);
	expr[MAXEV]->Connect("ReturnPressed()","HistoRootWindow",this,"command(=50)");
	Tab::registerWidget(expr[MAXEV]);
	fs5->AddFrame(expr[MAXEV]);
	ls4 = new TGLabel(fs5,"    ParticleType:");
	fs5->AddFrame(ls4, new TGLayoutHints(kLHintsLeft,3,0,0,0));
	expr[PDGID] = new TGTextEntry(fs5,"");
	expr[PDGID]->Resize(6*h,2*h);
	expr[PDGID]->Connect("ProcessedEvent(Event_t*)","HistoRootWindow",this,"ProcessedEvent(Event_t*)");
	expr[PDGID]->Connect("ReturnPressed()","HistoRootWindow",this,"command(=50)");
	Tab::registerWidget(expr[PDGID]);
	fs5->AddFrame(expr[PDGID]);
	ls4 = new TGLabel(fs5,"    EventID:");
	fs5->AddFrame(ls4, new TGLayoutHints(kLHintsLeft,3,0,0,0));
	expr[EVID] = new TGTextEntry(fs5,"");
	expr[EVID]->Resize(6*h,2*h);
	expr[EVID]->Connect("ProcessedEvent(Event_t*)","HistoRootWindow",this,"ProcessedEvent(Event_t*)");
	expr[EVID]->Connect("ReturnPressed()","HistoRootWindow",this,"command(=50)");
	Tab::registerWidget(expr[EVID]);
	fs5->AddFrame(expr[EVID]);
	f3->AddFrame(fs5);
	//
	TGTextButton *create = new TGTextButton(f3,"Create Plot",50);
	f3->AddFrame(create, 
		new TGLayoutHints(kLHintsCenterX,4,4,4,4));
	create->SetCommand("HistoRootWindow::command(50)");

	// pre-select 1d histogram
	radio[0]->SetState(kButtonDown);
	doCommand(41);

	// setup variables -- read $HOME/.historoot as lines of name=expr
	variables = new VariableList();

	// open files given in environment variable ARGS
	const char *args = gSystem->Getenv("ARGS");
	if(!args) args = "";
	TObjArray *files = TString(args).Tokenize(" \t");
	for(int i=0; i<files->GetEntries(); ++i) {
		TObjString *s = (TObjString *)files->At(i);
		if(!s || s->String().Length() == 0) continue;
		if(!openFile(s->String()))
			fprintf(stderr,"File '%s' could not be read\n",
				s->String().Data());
	}
	files->Delete();
	delete files;

	// display window
	window->Connect("CloseWindow()","HistoRootWindow",this,"command(=99)");
	window->Layout();
	window->SetWindowName("HistoRoot");
	window->MapSubwindows();
	window->Resize(window->GetDefaultSize());
	window->MapWindow();

	refresh();
}

HistoRootWindow::~HistoRootWindow()
{
	if(!window) return;
	window->Cleanup();
//	delete window;
	window = 0;
}

void HistoRootWindow::command(Int_t id)
{
	singleton->doCommand(id);
}
void HistoRootWindow::radioButton(Int_t id)
{
	for(unsigned i=0; i<sizeof(radio)/sizeof(radio[0]); ++i) {
		if(radio[i]->WidgetId() != id)
			radio[i]->SetState(kButtonUp);
	}
	singleton->doCommand(id);
}
void HistoRootWindow::command2(Int_t widgetId,Int_t id)
{
	(void)widgetId;
	singleton->selectNTuple(id);
}
void HistoRootWindow::ProcessedEvent(Event_t *e)
{
//printf("ProcessedEvent fType=%d fCode=%d fState=%08X fWindow=%ld expr_x=%ld\n",e->fType,e->fCode,e->fState,e->fWindow,singleton->expr[X]->GetId()); fflush(stdout);
	if(e->fType != kButtonPress || e->fCode != kButton3)
		return; // CINT limits depth of braces in event handler to 2.
	for(int i=0; i<ALL; ++i) {
		if(!singleton->expr[i]) continue;
		if(e->fWindow == singleton->expr[i]->GetId()) {
			FieldMenu::popup(singleton->expr[i],e->fX,e->fY);
			break;
		}
	}
}


void HistoRootWindow::refresh()
{
	listNtuples();

	ntupleListBox->RemoveAll();
	TListIter next(&ntuples);
	TNtuple *p;
	for(int i=0; (p=(TNtuple*)next()); ++i) {
		char tmp[1024];
		sprintf(tmp,"%s/%s  (%lld entries)",p->GetDirectory()->GetPath(),
			p->GetName(),p->GetEntries());
		ntupleListBox->AddEntry(tmp,i);
	}
	ntupleListBox->Layout();
}

void HistoRootWindow::doCommand(Int_t id)
{
	switch(id) {
	case 1:
		openFileDialog();
		break;
	case 2:
		closeAllFiles();
		break;
	case 3:
		saveConfig();
		break;
	case 4:
		loadConfig();
		break;
	case 5:
		variables->edit();
		break;
	case 11:
		new TBrowser();
		break;
	case 31:
		createComboPlotDialog();
		break;
	case 41:
		type = PLOT_TH1D;
		expr[Y]->SetEnabled(kFALSE);
		expr[Y]->SetText("");
		expr[W]->SetEnabled(kTRUE);
		expr[ERRX]->SetEnabled(kFALSE);
		expr[ERRX]->SetText("");
		expr[ERRY]->SetEnabled(kFALSE);
		expr[ERRY]->SetText("");
		break;
	case 42:
		type = PLOT_TH2D;
		expr[Y]->SetEnabled(kTRUE);
		expr[W]->SetEnabled(kTRUE);
		expr[ERRX]->SetEnabled(kFALSE);
		expr[ERRX]->SetText("");
		expr[ERRY]->SetEnabled(kFALSE);
		expr[ERRY]->SetText("");
		break;
	case 43:
		type = PLOT_XY;
		expr[Y]->SetEnabled(kTRUE);
		expr[W]->SetEnabled(kFALSE);
		expr[W]->SetText("");
		expr[ERRX]->SetEnabled(kTRUE);
		expr[ERRX]->SetText("");
		expr[ERRY]->SetEnabled(kTRUE);
		expr[ERRY]->SetText("");
		break;
	case 50:
		createPlot();
		break;
	case 61:
		createComboPlot();
		break;
	case 62:
		if(dialog) dialog->CloseWindow();
		dialog = 0;
		comboPlotTitle = 0;
		comboPlotListBox = 0;
		break;
	case 65:
		variables->save();
		break;
	case 66:
		variables->closeEditWindow();
		break;
	case 70:
		showHelpWindow();
		break;
	case 71:
		new TGMsgBox(gClient->GetRoot(),window,"About HistoRoot",
				"HistoRoot\n"
				"Copyright 2007, 2008 by Tom Roberts, all rights reserved.\n"
				"\n"
				"This program may be freely distributed under the terms of the\n"
				"Gnu Public License.",
				kMBIconAsterisk,kMBDismiss,0,
				kVerticalFrame,kTextLeft);
		break;
	case 99:
		gApplication->Terminate(0);
	}
}

const char *filetypes[] = {"ROOT files","*.root",
			   "Text files","*.txt",
			   "All files","*",0,0};
void HistoRootWindow::openFileDialog()
{
	TGFileInfo fi;
	fi.fFilename = 0;
	fi.fIniDir = StrDup((const char *)*directory);
	fi.fFileTypes = filetypes;
	fi.fFileTypeIdx = 0;
	fi.fOverwrite = false;
	
	new TGFileDialog(gClient->GetRoot(),window,kFDOpen,&fi); //self-deleting
	if(fi.fFilename != 0) {
		*directory = fi.fIniDir;
		if(!openFile(fi.fFilename)) {
			new TGMsgBox(gClient->GetRoot(),window,"Error",
				"File could not be opened!");//self-deleting
		}
	}

	// refresh the window
	// (do this even if the OpenFile was canceled or failed)
	refresh();
}

bool HistoRootWindow::openFile(const TString &filename)
{
	if(filename.EndsWith(".root")) {
		TFile *f = new TFile(filename,"READ");
		if(f->IsZombie())
			return false;
	} else if(filename.EndsWith(".txt")) {
		TNtuple *nt = AsciiFile::convert((const char *)filename);
		if(nt != 0)
			asciiNtuples.AddLast(nt);
		else
			return false;
	} else {
		TFile *f = new TFile(filename,"READ");
		if(f->IsZombie()) {
			TNtuple *nt=AsciiFile::convert((const char *)filename);
			if(nt != 0)
				asciiNtuples.AddLast(nt);
			else
				return false;
		}
	}

	return true;
}

void HistoRootWindow::closeAllFiles()
{
	// loop over all open TFiles, closing them
	TIter next(gROOT->GetListOfFiles());
	TFile *f;
	while((f=(TFile *)next()))
		f->Close();

	// delete all asciiNtuples
	for(int i=0; i<asciiNtuples.GetEntriesFast(); ++i)
		delete asciiNtuples.At(i);
	asciiNtuples.RemoveAll();

	selectedNtuple = 0;
	fieldListBox->RemoveAll();

	// refresh the window
	refresh();
}

void HistoRootWindow::showHelpWindow()
{
	char tmp[1024];
	TGTransientFrame *msg = new TGTransientFrame(0,window);
	TGTextView *txt = new TGTextView(msg,75,30,"",99);
	sprintf(tmp,"%s/HistoRoot.help",getenv("HISTO_DIR"));
	FILE *help = fopen(tmp,"r");
	if(!help) {
		txt->AddLine("No help available -- cannot read file:");
		txt->AddLine(tmp);
	} else { 
		while(fgets(tmp,sizeof(tmp),help))
			txt->AddLine(tmp);
		fclose(help);
	}
	txt->AddLine(" ");
	msg->AddFrame(txt,new TGLayoutHints(kLHintsExpandX|kLHintsExpandY));
	msg->SetWindowName("HistoRoot Help");
	msg->MapSubwindows();
	msg->Resize(75*w,40*h);
	msg->MapWindow();
}

void HistoRootWindow::listNtuples(TDirectory *d)
{
	if(!d) {
		ntuples.Clear();
		// loop over asciiNtuples
		for(int i=0; i<asciiNtuples.GetEntriesFast(); ++i) {
			TNtuple *q = (TNtuple *)asciiNtuples.At(i);
			if(q) ntuples.AddLast(q);
		}
		// loop over all open TFiles, looking for NTuples
		TIter next(gROOT->GetListOfFiles());
		TFile *f;
		while((f=(TFile *)next()))
			listNtuples(f);
		return;
	}

	TIter next(d->GetListOfKeys());
	TKey *key;
	while((key=(TKey*)next())) {
		const char *name = key->GetName();
		TObject *p = d->Get(name); // reads it into memory, if needed
		if(p && p->IsA()->InheritsFrom("TDirectory")) {
			listNtuples((TDirectory *)p);
		} else if(p->IsA()->InheritsFrom("TNtuple")) {
			TNtuple *q = (TNtuple *)p;
			ntuples.AddLast(q);
		}
	}
}

void HistoRootWindow::selectNTuple(int id)
{
	firstToSave = PlotList::size;

	// for multiple selected NTuples, process only the first
	TList *l = new TList();
	ntupleListBox->GetSelectedEntries(l);
	int n = l->GetEntries();
	if(n != 1) {
		delete l;
		return;
	}
	// if an entry was deselected, id is that entry, not the first one
	id = ((TGLBEntry*)(l->First()))->EntryId();
	delete l;

	fieldListBox->RemoveAll();
	gTntuple = selectedNtuple = (TNtuple *)ntuples.At(id);
	if(!selectedNtuple) return;

	int entry=0;
	int save = gErrorIgnoreLevel;
	gErrorIgnoreLevel = kFatal;
	for(int i=0; i<variables->size(); ++i) {
		if(variables->isValid(i,selectedNtuple))
			fieldListBox->AddEntry(variables->name(i),entry++);
	}
	gErrorIgnoreLevel = save;

	TObjArray *branches = selectedNtuple->GetListOfBranches();
	for(int i=0; i<branches->GetEntriesFast(); ++i) {
		TBranch *b = (TBranch *)(*branches)[i];
		if(!b || !isValidIdentifier(b->GetName())) continue;
		fieldListBox->AddEntry(b->GetName(),entry++);
	}
	fieldListBox->Layout();
}

void HistoRootWindow::createPlot()
{
	// get char* argument into arg[] -- NULL pointers, copies
	char *arg[ALL];
	for(int i=0; i<ALL; ++i) {
		arg[i] = 0;
		if(!expr[i]) continue;
		const char *q = expr[i]->GetText();
		arg[i] = (q!= 0 && strlen(q)>0 ? StrDup(q) : 0);
	}

	createPlot(arg);

	// *arg[] is used by the plot, so we cannot free them
}

void HistoRootWindow::createPlot(char *arg[ALL])
{
	if(!selectedNtuple) {
		new TGMsgBox(gClient->GetRoot(),window,"Error",
					"No NTuple selected!");
		return;
	}

	variables->applyAll(selectedNtuple);

	// check that required expressions are present, and all are valid
	TString msg;
	switch(type) {
	case PLOT_TH1D:
		if(!arg[X]) msg.Append("Missing expression for x");
		break;
	case PLOT_TH2D:
		if(!arg[X]) msg.Append("Missing expression for x");
		if(!arg[Y]) msg.Append("Missing expression for y");
		break;
	case PLOT_XY:
		if(!arg[X]) msg.Append("Missing expression for x");
		if(!arg[Y]) msg.Append("Missing expression for y");
		break;
	default:
		return;
	}
	for(int i=0; i<ALL; ++i) {
		if(!arg[i]) continue;
		if(!checkExpr(arg[i])) {
			char tmp[128];
			sprintf(tmp,"Invalid expression for %s: %s\n",
					EntryName[i],expr[i]->GetText());
			msg.Append(tmp);
		}
	}
	if(arg[MAXEV]) {
		TString t(arg[MAXEV]);
		if(t.Length() > 0 && !t.IsDigit())
			msg.Append("Invalid number for maxev");
	}
	if(msg.Length() > 1) {
		new TGMsgBox(gClient->GetRoot(),window,"Error",msg);
		return;
	}

	// get array of TNtuple pointers, and n
	TList *lst = new TList();
	ntupleListBox->GetSelectedEntries(lst);
	int n = lst->GetEntries();
	if(n <= 0 || (selectedNtuple->GetEntries() <= 0 && n == 1) ) {
		new TGMsgBox(gClient->GetRoot(),window,"Error",
			"Selected NTuple is empty");
		return;
	}
	TNtuple **nt = new TNtuple*[n];
	for(int j=0; j<n; ++j) {
		TGLBEntry *entry = (TGLBEntry *)lst->At(j);
		if(!entry) {
			nt[j] = 0;
		} else {
			nt[j] = (TNtuple *)ntuples.At(entry->EntryId());
			variables->applyAll(nt[j]);
		}
	}
	delete lst;

	new Plot(nt,n,type,arg,h1errorbars->IsDown());
	// Plot::~Plot() will delete nt
}

void HistoRootWindow::createComboPlotDialog()
{
	dialog = new TGTransientFrame(0,window);

	// get the size of an "M" (for layout)
	UInt_t w, h;
	gVirtualX->GetTextExtent(w,h,"M");
	if(w < 8) w = 8;
	if(h < 10) h = 10;

	// Layout the dialog box to select Plots
	TGLabel *l1 = new TGLabel(dialog,"Title:");
	dialog->AddFrame(l1,new TGLayoutHints(kLHintsLeft,5,5,5,5));
	comboPlotTitle = new TGTextEntry(dialog,"");
	comboPlotTitle->Resize(40*w,2*h);
	dialog->AddFrame(comboPlotTitle,new TGLayoutHints(kLHintsLeft,5,5,5,5));
	comboPlotListBox = new TGListBox(dialog);
	comboPlotListBox->SetMultipleSelections(true);
	for(int i=0; i<PlotList::size; ++i) {
		char entry[1024];
		switch(PlotList::array[i]->type) {
		case PLOT_NONE:
			continue;
		case PLOT_TH1D:
		case PLOT_TH2D:
		case PLOT_XY:
			sprintf(entry,"%s: %s",PlotList::array[i]->name,
					PlotList::array[i]->getTitle());
			break;
		case PLOT_COMBO:
			continue;
		}
		comboPlotListBox->AddEntry(entry,i);
	}
	comboPlotListBox->Resize(40*w,8*h);
	TGLabel *l2 = new TGLabel(dialog,"Select the plots to combine:");
	dialog->AddFrame(l2,new TGLayoutHints(kLHintsLeft,5,5,5,5));
	dialog->AddFrame(comboPlotListBox,new TGLayoutHints(kLHintsLeft,5,5,5,5));
	TGHorizontalFrame *f2 = new TGHorizontalFrame(dialog);
	TGTextButton *ok = new TGTextButton(f2,"OK",61);
	ok->SetCommand("HistoRootWindow::command(61)");
	f2->AddFrame(ok);
	f2->AddFrame(new TGLabel(f2,"                 "));
	TGTextButton *cancel = new TGTextButton(f2,"Cancel",62);
	cancel->SetCommand("HistoRootWindow::command(62)");
	f2->AddFrame(cancel);
	dialog->AddFrame(f2,new TGLayoutHints(kLHintsCenterX,5,5,5,5));

	dialog->Layout();
	dialog->SetWindowName("ComboPlot");
	dialog->MapSubwindows();
	dialog->Resize(dialog->GetDefaultSize());
	dialog->MapWindow();
}

void HistoRootWindow::createComboPlot()
{
	if(comboPlotTitle && comboPlotListBox) {
		Plot *plot = new Plot(0,0,PLOT_COMBO,0,false);
		const char *title = comboPlotTitle->GetText();
		plot->canvas->cd();
		plot->th1d = new TH1D(title,title,101,0.0,1.0);
		double xmin=1.e99,xmax=-1.e99,ymin=1.e99,ymax=-1.e99;
		TList l;
		comboPlotListBox->GetSelectedEntries(&l);
		TIter i(&l);
		TGLBEntry *e=0;
		while((e = (TGLBEntry *)i()) != 0) {
			int id = e->EntryId();
			if(id < 0 || id >= PlotList::size) continue;
			double x0,x1,y0,y1;
			PlotList::array[id]->canvas->GetRangeAxis(x0,y0,x1,y1);
			if(x0 < xmin) xmin = x0;
			if(x1 > xmax) xmax = x1;
			if(y0 < ymin) ymin = y0;
			if(y1 > ymax) ymax = y1;
		}
		plot->th1d->SetBins(101,xmin,xmax);
		plot->th1d->GetYaxis()->SetLimits(-1.e38,1.e38);
		plot->th1d->GetYaxis()->SetRangeUser(ymin,ymax);
		plot->th1d->SetStats(false);
		plot->th1d->Draw();
		i = TIter(&l);
		while((e = (TGLBEntry *)i()) != 0) {
			int id = e->EntryId();
			if(id < 0 || id >= PlotList::size) continue;
			if(PlotList::array[id]->th1d)
			    PlotList::array[id]->th1d->Clone()->Draw("same");
			if(PlotList::array[id]->th2d)
			    PlotList::array[id]->th2d->Clone()->Draw("same");
			if(PlotList::array[id]->tgraph)
			    PlotList::array[id]->tgraph->Clone()->Draw("P");
		}
	}

	if(dialog) dialog->CloseWindow();
	dialog = 0;
	comboPlotTitle = 0;
	comboPlotListBox = 0;
}

bool HistoRootWindow::isValidIdentifier(const char *s)
{
	if(!isalpha(s[0]) && s[0] != '_') return false;
	while(*s) {
		if(!isalpha(*s) && !isdigit(*s) && *s != '_') return false;
		++s;
	}
	return true;
}

bool HistoRootWindow::checkExpr(const char *e)
{
	if(!selectedNtuple) return false;
	if(!e || strlen(e) == 0) return false;

	char *tmp = StrDup(e);
	char *p = strchr(tmp,':');
	if(p) *p = '\0';
	TTreeFormula t("test",tmp,selectedNtuple);
	free(tmp);
	return t.GetTree() != 0;
}

const char *savetypes[] = {"HistoRoot files","*.hist",
			   "All files","*",0,0};

void HistoRootWindow::saveConfig()
{
	if(firstToSave >= PlotList::size) {
		new TGMsgBox(gClient->GetRoot(),window,"Error",
			"No Plot configuration to save.\n"
			"Only plots created since the last select Ntuple can be saved.");//self-deleting
		return;
	}

	TGFileInfo fi;
	fi.fFilename = 0;
	fi.fIniDir = StrDup((const char *)*directory);
	fi.fFileTypes = savetypes;
	fi.fFileTypeIdx = 0;
	fi.fOverwrite = false;
	
	new TGFileDialog(gClient->GetRoot(),window,kFDSave,&fi); //self-deleting
	if(fi.fFilename == 0) return;

	*directory = fi.fIniDir;
	TString fname(fi.fFilename);
	if(fi.fFileTypeIdx == 0 && !fname.EndsWith(".hist"))
		fname += ".hist";
	FILE *out = fopen(fname.Data(),"w");
	if(!out) {
		new TGMsgBox(gClient->GetRoot(),window,"Error",
			"File could not be opened!");//self-deleting
		return;
	}

	for(int i=firstToSave; i<PlotList::size; ++i) {
		PlotList::array[i]->saveConfig(out);
	}
	fclose(out);
}

// parse routines -- never increment beyond end of string.
// skips multiple instances of c, returns false if end of string is reached
bool skip(char **pp, char c)
{
	assert(c!='\0');
	while(*(*pp) == c) ++(*pp);
	return *(*pp) != '\0';
}
// returns ptr to span of chars != end; replaces end char with '\0'.
// if end==' ', end-of-string is allowed, otherwise end of string return null.
char *span(char **pp, char end)
{
	char *start=*pp;
	while(*(*pp) != end && *(*pp) != '\0') ++(*pp);
	if(*(*pp) == '\0' && end != ' ') return 0;
	if(*(*pp) != '\0') *(*pp)++ = '\0';
	if(*start == '\0') return 0;
	return start;
}

void HistoRootWindow::loadConfig()
{
	TGFileInfo fi;
	fi.fFilename = 0;
	fi.fIniDir = StrDup((const char *)*directory);
	fi.fFileTypes = savetypes;
	fi.fFileTypeIdx = 0;
	fi.fOverwrite = false;
	
	new TGFileDialog(gClient->GetRoot(),window,kFDOpen,&fi); //self-deleting
	if(fi.fFilename == 0) return;

	*directory = fi.fIniDir;
	TString fname(fi.fFilename);
	if(fi.fFileTypeIdx == 0 && !fname.EndsWith(".hist"))
		fname += ".hist";
	printf("loadConfig file='%s'\n",fname.Data());
	FILE *in = fopen(fname.Data(),"r");
	if(!in) {
		printf("Cannot read file '%s'\n",fname.Data());
		new TGMsgBox(gClient->GetRoot(),window,"Error",
			"File could not be opened!");//self-deleting
		return;
	}

	char line[1024];
	while(fgets(line,sizeof(line),in)) {
		bool error=false;
		char *tmp = StrDup(line);
		char *arg[ALL];
		for(int i=0; i<ALL; ++i) arg[i] = 0;
		char *p = tmp;
		while((p=strchr(p,'\t')) != 0) *p = ' '; // tab => space
		if((p=strchr(tmp,'\r')) != 0) *p = '\0'; // remove <CR>
		if((p=strchr(tmp,'\n')) != 0) *p = '\0'; // remove <NL>
		// now the only whitespace present is ' '
		p = tmp;
		skip(&p,' ');
		char *cmd=span(&p,' ');
		if(!cmd || *cmd == '#') {
			free(tmp);
			continue;
		}
		for(;;) { // loop over name='expr'
			if(!skip(&p,' ')) break;
			char *name=span(&p,'=');
			if(!name) break;
			char *value=0;
			if(*p == '\'') {
				++p;
				value = span(&p,'\'');
			} else if(*p == '"') {
				++p;
				value = span(&p,'"');
			} else {
				value = span(&p,' ');
			}
			if(!value) {
				error = true;
				break;
			}
			int i;
			for(i=0; i<ALL; ++i) {
				if(strcmp(name,EntryName[i]) == 0) {
					arg[i] = StrDup(value);
					break;
				}
			}
			if(i == ALL) {
				error = true;
				break;
			}
		}
		if(!error) {
			type = PLOT_NONE;
			if(strcmp(cmd,"hist1d") == 0) type = PLOT_TH1D;
			if(strcmp(cmd,"hist2d") == 0) type = PLOT_TH2D;
			if(strcmp(cmd,"xyplot") == 0) type = PLOT_XY;
			if(type != PLOT_NONE) {
			    printf("%s",line);
			    createPlot(arg);
			    // *arg[] is used by the plot, cannot free them
			} else {
			    printf("loadConfig: syntax error in line: %s",line);
			}
		} else {
			printf("loadConfig: syntax error in line: %s",line);
		}
		free(tmp);
	}

	fclose(in);
}

void VariableList::edit() 
{
	dialog = new TGTransientFrame(0,HistoRootWindow::singleton->window);
	// get the size of an "M" (for layout)
	UInt_t w, h;
	gVirtualX->GetTextExtent(w,h,"M");
	if(w < 8) w = 8;
	if(h < 10) h = 10;

	textEdit = new TGTextEdit(dialog);
	for(int i=0; i<nvar; ++i) {
		char tmp[1024];
		sprintf(tmp,"%s=%s",names[i],exprs[i]);
		textEdit->AddLineFast(tmp);
	}
	textEdit->Resize(60*w,20*h);
	dialog->AddFrame(textEdit,new TGLayoutHints(kLHintsCenterX|kLHintsExpandX|kLHintsExpandY));

	TGHorizontalFrame *f2 = new TGHorizontalFrame(dialog);
	TGTextButton *ok = new TGTextButton(f2,"OK",65);
	ok->SetCommand("HistoRootWindow::command(65)");
	f2->AddFrame(ok);
	f2->AddFrame(new TGLabel(f2,"                 "));
	TGTextButton *cancel = new TGTextButton(f2,"Cancel",66);
	cancel->SetCommand("HistoRootWindow::command(66)");
	f2->AddFrame(cancel);
	dialog->AddFrame(f2,new TGLayoutHints(kLHintsCenterX,5,5,5,5));

	dialog->Layout();
	dialog->SetWindowName("Edit Variables");
	dialog->MapSubwindows();
	dialog->Resize(60*w,20*h);
	//dialog->Resize(dialog->GetDefaultSize());
	dialog->MapWindow();
}

Plot::Plot(void *_nt, int _nNtuples, PlotType _type,
					void *_e, bool _h1errorbars) : limits()
{
	sprintf(name,"Plot%d",++number);
	// workaround for CINT bug
	ntuples = (TNtuple**)_nt;
	assert(ntuples!=0 || _type==PLOT_COMBO);
	char **_expr = (char**)_e;
	assert(_expr!=0 || _type==PLOT_COMBO);
	// end workaround
	nNtuples = _nNtuples;
	type = _type;
	canvas = 0;
	dataWindow = 0;
	th1d = 0;
	th2d = 0;
	tgraph = 0;
	max_events = 0;
	maxev_entry = 0;
	h1errorbars = _h1errorbars;
	nx_bins = 101;
	ny_bins = 101;
	nx_entry = 0;
	ny_entry = 0;

	PlotList::append(this);

	// ComboPlot has reduced data in the Plot object
	if(type == PLOT_COMBO) { 
		drawCanvas();
		return;
	}

	// get NULL pointers in expr[], not empty strings
	for(int i=0; i<ALL; ++i) {
		expr[i] = _expr[i];
		sliderLimits[i] = 0;
		formula[i] = 0;
	}

	if(expr[MAXEV]) max_events = strtol(expr[MAXEV],0,10);

	// use the first selected NTuple for expressions
	TNtuple *nt = ntuples[0];

	// interpret "expr:min:max" for expressions
	bool needScan=false;
	for(int i=0; i<ALL; ++i) {
		if(!expr[i]) continue;
		char *p = (char *)strchr(expr[i],':');
		if(p) {
			*p++ = '\0';
			char *q = strchr(p,':');
			if(q) {
				*q++ = '\0';
				limits.set((Entry)i,strtod(p,0),strtod(q,0));
			} else {
				p = 0;
			}
		}
		if(!p && i <= S4) needScan = true;
	} 

	// get :-separated list of fields (with : bookends)
	TString fields(":");
	TObjArray *branches = ntuples[0]->GetListOfBranches();
	for(int i=0; i<branches->GetEntriesFast(); ++i) {
		TBranch *b = (TBranch *)(*branches)[i];
		if(!b) continue;
		fields += b->GetName();
		fields += ":";
	}

	// create formulas for expressions
	for(int i=0; i<ALL; ++i) {
		if(expr[i]) {
		    // expand variables, as there is a bug in setting up
		    // variables for multiple TNtuples (fields are fine).
//printf("expression:%s\n  expanded:%s\n",expr[i],HistoRootWindow::singleton->variables->expand(expr[i],""));
		    formula[i] = new TTreeFormula(EntryName[i],
			HistoRootWindow::singleton->variables->expand(expr[i],fields),
		nt);
		    if(formula[i]->GetTree() == 0) { 
			delete formula[i];
			formula[i] = 0; 
		    }
		}
	}

	if(needScan) scanForLimits();

	// draw the plot and its data window
	drawCanvas();
	drawDataWindow();
}

void Plot::drawCanvas()
{ 
	// draw the plot in its own window (canvas)
	canvas = new TCanvas(name,name);
	canvas->SetFolder(true);
	canvas->Connect("Closed()","Plot",this,"plotClosed()");
	int save = gErrorIgnoreLevel;
	gErrorIgnoreLevel = kFatal;
	switch(type) {
	case PLOT_TH1D:
		th1d = new TH1D(expr[X],expr[X],nx_bins,limits.x_min,limits.x_max);
		gTh1d = th1d;
		if(h1errorbars) {
			th1d->Sumw2();
			th1d->SetMarkerStyle(7); // larger filled box
			gStyle->SetErrorX(0); // the X0 doesn't seem to work
		}
		scan();
		th1d->SetOption(h1errorbars ? "E1 X0" : "");
		th1d->Draw();
		canvas->Selected(canvas,canvas->FindObject(th1d),1);
		break;
	case PLOT_TH2D:
		{ char title[1024];
		  sprintf(title,"%s vs. %s",expr[Y],expr[X]);
		  th2d = new TH2D(title,title,nx_bins,limits.x_min,limits.x_max,
				ny_bins,limits.y_min,limits.y_max);
		  gTh2d = th2d;
		}
		scan();
		th2d->Draw("");
		canvas->Selected(canvas,canvas->FindObject(th2d),1);
		break;
	case PLOT_XY:
		tgraph = new TGraphErrors(2); // 2 is # points (updated in scan)
		{ char title[1024];
		  sprintf(title,"%s vs. %s",expr[Y],expr[X]);
		  tgraph->SetNameTitle(title,title);
		  gTGraph = tgraph;
		}
		scan();
		tgraph->SetMarkerStyle(7);
		tgraph->Draw("AP");
		canvas->Selected(canvas,canvas->FindObject(tgraph),1);
		break;
	case PLOT_COMBO:
	case PLOT_NONE:
		break;
	}
	gErrorIgnoreLevel = save;
}

Plot::~Plot()
{
	if(canvas) canvas->Disconnect();
	// deleting stuff has thorns, accept the modest memory leak
}

void Plot::setNtuple(TNtuple *nt)
{
	for(int i=0; i<ALL; ++i) {
		if(formula[i]) {
			formula[i]->SetTree(nt);
			formula[i]->UpdateFormulaLeaves();
		}
	}
	HistoRootWindow::singleton->variables->applyAll(nt);
}

void Plot::scanForLimits()
{
	const int PRINT_INTERVAL=10000;
	int ntotal=0;
	for(int j=0; j<nNtuples; ++j) {
		TNtuple *ntuple = ntuples[j];
		ntotal += ntuple->GetEntries();
	}
	Particle::clear();

	bool need[ALL];
	need[X] = (formula[X] != 0 && limits.x_min > limits.x_max);
	need[Y] = (formula[Y] != 0 && limits.y_min > limits.y_max);
	need[S1] = (formula[S1] != 0 && limits.s1_min > limits.s1_max);
	need[S2] = (formula[S2] != 0 && limits.s2_min > limits.s2_max);
	need[S3] = (formula[S3] != 0 && limits.s3_min > limits.s3_max);
	need[S4] = (formula[S4] != 0 && limits.s4_min > limits.s4_max);
	need[PDGID] = (formula[PDGID] != 0);

	if(ntotal >= PRINT_INTERVAL) printf("\r"); // erase root prompt
	int nread=0;
	for(int j=0; j<nNtuples; ++j) {
		if(max_events > 0 && nread >= max_events) break;
		TNtuple *ntuple = ntuples[j];
		setNtuple(ntuple);
		int n = ntuple->GetEntries();
		for(int i=0; i<n; ++i) {
			if(max_events > 0 && nread >= max_events) break;
			if(++nread%PRINT_INTERVAL == 0) {
				printf("%s scanForLimits %d/%d\r",name,
							nread,ntotal);
				fflush(stdout);
			}
			ntuple->LoadTree(i);
			if(need[X])
				limits.set_x(formula[X]->EvalInstance(0));
			if(need[Y])
				limits.set_y(formula[Y]->EvalInstance(0));
			if(need[S1])
				limits.set_s1(formula[S1]->EvalInstance(0));
			if(need[S2])
				limits.set_s2(formula[S2]->EvalInstance(0));
			if(need[S3])
				limits.set_s3(formula[S3]->EvalInstance(0));
			if(need[S4])
				limits.set_s4(formula[S4]->EvalInstance(0));
			if(need[PDGID])
				Particle::incr((int)formula[PDGID]->EvalInstance(0));
			// others not used in scanForLimits
		}
	}
	if(ntotal >= PRINT_INTERVAL) printf("\n");

	Particle::print(false);

	// include the uppermost bin
	if(need[X])
	 limits.set_x(limits.x_max+(limits.x_max-limits.x_min)/(nx_bins-1));
	if(need[Y])
	 limits.set_y(limits.y_max+(limits.y_max-limits.y_min)/(ny_bins-1));

	// expand slider limits by 1 part per million (avoid float==float)
	if(need[S1]) {
		double v=(limits.s1_max-limits.s1_min)*1.0e-6;
		limits.s1_min -= v;
		limits.s1_max += v;
	}
	if(need[S2]) {
		double v=(limits.s2_max-limits.s2_min)*1.0e-6;
		limits.s2_min -= v;
		limits.s2_max += v;
	}
	if(need[S3]) {
		double v=(limits.s3_max-limits.s3_min)*1.0e-6;
		limits.s3_min -= v;
		limits.s3_max += v;
	}
	if(need[S4]) {
		double v=(limits.s4_max-limits.s4_min)*1.0e-6;
		limits.s4_min -= v;
		limits.s4_max += v;
	}

	return;
}

void Plot::scan()
{
	const int PRINT_INTERVAL=10000;
	int ntotal=0;
	for(int j=0; j<nNtuples; ++j) {
		TNtuple *ntuple = ntuples[j];
		ntotal += ntuple->GetEntries();
	}

	if(th1d) th1d->Reset();
	if(th2d) th2d->Reset();
	if(tgraph) tgraph->Set(ntotal);
	Particle::clear();

	FILE *ev_file=0;
	TString ev_filename = *HistoRootWindow::directory + "/histo_event.txt";
	if(formula[EVID] != 0) {
		ev_file = fopen((const char *)ev_filename,"w");
		if(!ev_file) printf("Cannot write '%s'\n",
						(const char *)ev_filename);
	}

	int nread=0;
	int k=0; // # entries that pass the slider cuts 
	for(int j=0; j<nNtuples; ++j) {
		if(max_events > 0 && nread >= max_events) break;
		TNtuple *ntuple = ntuples[j];
		setNtuple(ntuple);
		int n = ntuple->GetEntries();
		for(int i=0; i<n; ++i) {
			if(max_events > 0 && nread >= max_events) break;
			if(++nread%PRINT_INTERVAL == 0) {
				printf("%s scan %d/%d\r",name,nread,ntotal);
				fflush(stdout);
			}
			ntuple->LoadTree(i);
			if(formula[S1] && 
			   !limits.check_s1(formula[S1]->EvalInstance(0))) 
				continue;
			if(formula[S2] && 
			   !limits.check_s2(formula[S2]->EvalInstance(0))) 
				continue;
			if(formula[S3] && 
			   !limits.check_s3(formula[S3]->EvalInstance(0))) 
				continue;
			if(formula[S4] && 
			   !limits.check_s4(formula[S4]->EvalInstance(0))) 
				continue;
			if(formula[W]) {
			    if(th1d) th1d->Fill(formula[X]->EvalInstance(0),
			    			formula[W]->EvalInstance(0));
			    if(th2d) th2d->Fill(formula[X]->EvalInstance(0),
			    	      formula[Y]->EvalInstance(0),
				      formula[W]->EvalInstance(0));
			    if(tgraph) {
				double ex = (formula[ERRX]?formula[ERRX]->EvalInstance(0):0.0);
				double ey = (formula[ERRY]?formula[ERRY]->EvalInstance(0):0.0);
				if(formula[ERRX] || formula[ERRY])
					tgraph->SetPointError(k,ex,ey);
			    	tgraph->SetPoint(k,formula[X]->EvalInstance(0),
						formula[Y]->EvalInstance(0));
			    }
			} else {
			    if(th1d) th1d->Fill(formula[X]->EvalInstance(0));
			    if(th2d) th2d->Fill(formula[X]->EvalInstance(0),
			    			formula[Y]->EvalInstance(0));
			    if(tgraph) {
				double ex = (formula[ERRX]?formula[ERRX]->EvalInstance(0):0.0);
				double ey = (formula[ERRY]?formula[ERRY]->EvalInstance(0):0.0);
				if(formula[ERRX] || formula[ERRY])
					tgraph->SetPointError(k,ex,ey);
			    	tgraph->SetPoint(k,formula[X]->EvalInstance(0),
						formula[Y]->EvalInstance(0));
			    }
			}
			if(formula[PDGID]) 
			   Particle::incr((int)formula[PDGID]->EvalInstance(0));
			if(ev_file) {
				fprintf(ev_file,"%d\n",
					(int)formula[EVID]->EvalInstance(0));
			}
			++k;
		}
	}
	if(ev_file) {
		fclose(ev_file);
		printf("wrote '%s'  %d events\n",(const char *)ev_filename,k);
	}
	if(ntotal >= PRINT_INTERVAL) printf("\n");
	if(tgraph) tgraph->Set(k);
	Particle::print(true);
}

void Plot::drawDataWindow()
{
	// don't draw an empty dataWindow
	if(type == PLOT_XY && !expr[S1] && !expr[S2] && !expr[S3] && 
	   !expr[S4] && max_events <= 0)
		return;

	// get the size of an "M" (for layout)
	UInt_t w, h;
	gVirtualX->GetTextExtent(w,h,"M");
	if(w < 8) w = 8;
	if(h < 10) h = 10;

	if(!dataWindow)
		dataWindow = new TGMainFrame(gClient->GetRoot(),20*w,20*h,
							kVerticalFrame);

	// Layout the plot's data window
	char tmp[1024];
	sprintf(tmp,"%s Data Control",name);
	TGLabel *l = new TGLabel(dataWindow,tmp);
	dataWindow->AddFrame(l,new TGLayoutHints(kLHintsExpandX,0,0,1,1));

	// no bins or limits for PLOT_XY
	if(type != PLOT_XY) {
	    TGHorizontalFrame *f = new TGHorizontalFrame(dataWindow);
	    TGLabel *l = new TGLabel(f," # Bins X: ");
	    f->AddFrame(l);
	    nx_entry = new TGNumberEntryField(f,14,nx_bins);
	    nx_entry->Connect("ReturnPressed()","Plot",this,"slider()");
	    nx_entry->SetWidth(60);
	    f->AddFrame(nx_entry);
	    dataWindow->AddFrame(f);
	    if(expr[Y]) {
	    	TGHorizontalFrame *f = new TGHorizontalFrame(dataWindow);
	    	TGLabel *l = new TGLabel(f," # Bins Y: ");
	    	f->AddFrame(l);
	    	ny_entry = new TGNumberEntryField(f,14,ny_bins);
	        ny_entry->Connect("ReturnPressed()","Plot",this,"slider()");
	        ny_entry->SetWidth(60);
	    	f->AddFrame(ny_entry);
	    	dataWindow->AddFrame(f);
	    }
	    SliderLimits *slider_x = new SliderLimits(dataWindow,"X - Horizontal Axis",expr[X],&limits.x_min,&limits.x_max);
	    slider_x->Connect("Changed()","Plot",this,"slider()");
	    if(expr[Y]) {
	        SliderLimits *slider_y = new SliderLimits(dataWindow,"Y - Vertical Axis",expr[Y],&limits.y_min,&limits.y_max);
	        slider_y->Connect("Changed()","Plot",this,"slider()");
	    }
	}
	if(max_events > 0) {
	    TGHorizontalFrame *f = new TGHorizontalFrame(dataWindow);
	    TGLabel *l = new TGLabel(f," Max Events: ");
	    f->AddFrame(l);
	    maxev_entry = new TGNumberEntryField(f,14,max_events);
	    maxev_entry->Connect("ReturnPressed()","Plot",this,"slider()");
	    maxev_entry->SetWidth(70);
	    f->AddFrame(maxev_entry);
	    dataWindow->AddFrame(f);
	}
	if(expr[S1]) {
		sliderLimits[S1] = new SliderLimits(dataWindow,"Slider 1",expr[S1],
					&limits.s1_min,&limits.s1_max);
		sliderLimits[S1]->Connect("Changed()","Plot",this,"slider()");
	}
	if(expr[S2]) {
		sliderLimits[S2] = new SliderLimits(dataWindow,"Slider 2",expr[S2],
					&limits.s2_min,&limits.s2_max);
		sliderLimits[S2]->Connect("Changed()","Plot",this,"slider()");
	}
	if(expr[S3]) {
		sliderLimits[S3] = new SliderLimits(dataWindow,"Slider 3",expr[S3],
					&limits.s3_min,&limits.s3_max);
		sliderLimits[S3]->Connect("Changed()","Plot",this,"slider()");
	}
	if(expr[S4]) {
		sliderLimits[S4] = new SliderLimits(dataWindow,"Slider 4",expr[S4],
					&limits.s4_min,&limits.s4_max);
		sliderLimits[S4]->Connect("Changed()","Plot",this,"slider()");
	}

	// display dataWindow
	dataWindow->Layout();
	sprintf(tmp,"%s Data",name);
	dataWindow->SetWindowName(tmp);
	dataWindow->MapSubwindows();
	dataWindow->Resize(dataWindow->GetDefaultSize());
	dataWindow->MapWindow();
	dataWindow->Connect("CloseWindow()","Plot",this,"dataWindowClosed()");
}

void Plot::slider()
{
	if(nx_entry) nx_bins = nx_entry->GetIntNumber();
	if(ny_entry) ny_bins = ny_entry->GetIntNumber();
	if(th1d) th1d->SetBins(nx_bins,limits.x_min,limits.x_max);
	if(th2d) th2d->SetBins(nx_bins,limits.x_min,limits.x_max,
					ny_bins,limits.y_min,limits.y_max);
	if(maxev_entry) {
		const char *p = maxev_entry->GetText();
		if(p) max_events = strtol(p,0,10);
	}

	// update the plot and the canvas
	scan();
	canvas->cd();
	if(th1d) th1d->Draw("");
	if(th2d) th2d->Draw("");
	if(tgraph) tgraph->Draw("AP");
	canvas->Update();
}

void Plot::saveConfig(FILE *out)
{
	switch(type) {
	case PLOT_NONE: return;
	case PLOT_TH1D: fprintf(out,"hist1d "); break;
	case PLOT_TH2D: fprintf(out,"hist2d "); break;
	case PLOT_XY:   fprintf(out,"xyplot "); break;
	case PLOT_COMBO: return;
	}

	for(int i=0; i<ALL; ++i) {
		if(expr[i] == 0) continue;
		if(i <= S4)
			fprintf(out,"%s='%s:%.6g:%.6g' ", EntryName[i],expr[i],
			    limits.minimum((Entry)i),limits.maximum((Entry)i));
		else
			fprintf(out,"%s='%s' ", EntryName[i],expr[i]);
	}
	fprintf(out,"\n");
}


// here is the macro function
void HistoRoot() 
{
#ifdef __CINT__
	// default optimization ".O 4" fails miserably in HistoRootWindow.
	gROOT->ProcessLineSync(".O 3");
#endif
	new HistoRootWindow(); 
}
