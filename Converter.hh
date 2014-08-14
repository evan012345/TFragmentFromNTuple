#ifndef __CONVERTER_HH
#define __CONVERTER_HH

#include <vector>

#include "TFragment.hh"

#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TRandom3.h"
#include "TH1F.h"
#include "TH2F.h"

#include "Settings.hh"
#include "Griffin.hh"

class Converter {
public:
  Converter(std::vector<std::string>&, const std::string&, Settings*);
  ~Converter();

  bool Run();

private:
  bool AboveThreshold(double, int);

  //TFragment Stuff
  void SetUpFragmentTree();
  void FillFragmentTree(TFragment *frag);
  TTree *fFragmentTree;
  TFragment *fBufferFrag;

  void PrintStatistics();
  
  Settings* fSettings;
  TChain fChain;
  TFile* fOutput;
  TRandom3 fRandom;

  //branches of input tree/chain
  Int_t fEventNumber;
  Int_t fTrackID;
  Int_t fParentID;
  Int_t fStepNumber;
  Int_t fParticleType;
  Int_t fProcessType;
  Int_t fSystemID;
  Int_t fCryNumber;
  Int_t fDetNumber;
  Double_t fDepEnergy;
  Double_t fPosx;
  Double_t fPosy;
  Double_t fPosz;
  Double_t fTime;

  double fSmearedEnergy;
  bool   fSceptarHit;

  //branches of output tree
  // GRIFFIN
  std::vector<Detector>* fGriffinCrystal;
  std::vector<Detector>* fGriffinDetector;
  std::vector<Detector>* fGriffinNeighbour;
  Detector* fGriffinArray;
  std::vector<Detector>* fGriffinBgo;
  std::vector<Detector>* fGriffinBgoBack;

  // LaBr
  Detector* fLaBrArray;
  std::vector<Detector>* fLaBrDetector;

  // Ancillary BGO
  Detector* fAncillaryBgoArray;
  std::vector<Detector>* fAncillaryBgoCrystal;
  std::vector<Detector>* fAncillaryBgoDetector;

  // Sceptar
  Detector* fSceptarArray;
  std::vector<Detector>* fSceptarDetector;

  //histograms
  std::map<std::string,TList*> fHistograms;
};

#endif
