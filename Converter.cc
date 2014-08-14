#include "Converter.hh"

#include <iostream>
#include <iomanip>

#include "TMath.h"

#include "Utilities.hh"

Converter::Converter(std::vector<std::string>& inputFileNames, const std::string& outputFileName, Settings* settings)
  : fSettings(settings) {
  //create TChain to read in all input files
  for(auto fileName = inputFileNames.begin(); fileName != inputFileNames.end(); ++fileName) {
    if(!FileExists(*fileName)) {
      std::cerr<<"Failed to find file '"<<*fileName<<"', skipping it!"<<std::endl;
      continue;
    }
    //add sub-directory and tree name to file name
    fileName->append("/ntuple/ntuple");
    fChain.Add(fileName->c_str());
  }

  //add branches to input chain
  fChain.SetBranchAddress("eventNumber", &fEventNumber);
  fChain.SetBranchAddress("trackID", &fTrackID);
  fChain.SetBranchAddress("parentID", &fParentID);
  fChain.SetBranchAddress("stepNumber", &fStepNumber);
  fChain.SetBranchAddress("particleType", &fParticleType);
  fChain.SetBranchAddress("processType", &fProcessType);
  fChain.SetBranchAddress("systemID", &fSystemID);
  fChain.SetBranchAddress("detNumber", &fDetNumber);
  fChain.SetBranchAddress("cryNumber", &fCryNumber);
  fChain.SetBranchAddress("depEnergy", &fDepEnergy);
  fChain.SetBranchAddress("posx", &fPosx);
  fChain.SetBranchAddress("posy", &fPosy);
  fChain.SetBranchAddress("posz", &fPosz);
  fChain.SetBranchAddress("time", &fTime);

  //create output file
  fOutput = new TFile(outputFileName.c_str(),"recreate");
  if(!fOutput->IsOpen()) {
    std::cerr<<"Failed to open file '"<<outputFileName<<"', check permissions on directory and disk space!"<<std::endl;
    throw;
  }

  SetUpFragmentTree();

  //set tree to belong to output file
  if(fSettings->WriteTree())
    fFragmentTree->SetDirectory(fOutput);

  //create branches for output tree
  // GRIFFIN
  fGriffinCrystal = new std::vector<Detector>;
  fGriffinDetector = new std::vector<Detector>;
  fGriffinBgo = new std::vector<Detector>;
  fGriffinBgoBack = new std::vector<Detector>;
  // LaBr
  fLaBrDetector = new std::vector<Detector>;
  // Ancillary Detector
  fAncillaryBgoCrystal = new std::vector<Detector>;
  fAncillaryBgoDetector = new std::vector<Detector>;
  // SCEPTAR
  fSceptarDetector = new std::vector<Detector>;
}

Converter::~Converter() {
  if(fOutput->IsOpen()) {
    if(fSettings->WriteTree())
      fFragmentTree->Write("FragmentTree");
    fOutput->Close();
  }
}

bool Converter::Run() {
  int status;
  int eventNumber = 0;
  double smearedEnergy;
  std::map<int,int> belowThreshold;

  long int nEntries = fChain.GetEntries();

  TFragment *EventFrag = new TFragment();

  double cfd,led,charge,datatype,detectortype,channelid;

  for(int i = 0; i < nEntries; ++i) {
    status = fChain.GetEntry(i);
    if(status == -1) {
      std::cerr<<"Error occured, couldn't read entry "<<i<<" from tree "<<fChain.GetName()<<" in file "<<fChain.GetFile()->GetName()<<std::endl;
      continue;
    } else if(status == 0) {
      std::cerr<<"Error occured, entry "<<i<<" in tree "<<fChain.GetName()<<" in file "<<fChain.GetFile()->GetName()<<" doesn't exist"<<std::endl;
      return false;
    }

    if((fEventNumber != eventNumber) && ((fSettings->SortNumberOfEvents()==0)||(fSettings->SortNumberOfEvents()>=eventNumber))) {

//      EventFrag->MidasTimeStamp = (time_t)(0);
//      EventFrag->MidasId = (uint32_t)(0);
//      EventFrag->TriggerId = (uint64_t)(0);
//      EventFrag->FragmentId = (uint32_t)(0);
//      EventFrag->TriggerBitPattern = (uint32_t)(0);

//      EventFrag->ChannelNumber = (int32_t)(0);
//      EventFrag->ChannelAddress = (int32_t)(0);

//      EventFrag->TimeStampLow = (int32_t)(0);
//      EventFrag->TimeStampHigh = (int32_t)(0);
//      EventFrag->TimeToTrig = (int32_t)(0);

//      EventFrag->PPG = (int32_t)(0);
//      EventFrag->DeadTime = (uint16_t)(0);
//      EventFrag->NumberOfFilters = (uint16_t)(0);;
//      EventFrag->NumberOfPileups = (uint16_t)(0);

      // FILL THE FRAGMENT TREE
      for(size_t firstDet = 0; firstDet < fGriffinCrystal->size(); ++firstDet) {
        cfd         = 0;
        led         = 0;
        charge      = fGriffinCrystal->at(firstDet).Energy();
        datatype    = 0;
        detectortype= 0;
        channelid   = 4*(fGriffinCrystal->at(firstDet).DetectorId())+fGriffinCrystal->at(firstDet).CrystalId();

        EventFrag->Cfd.push_back((int32_t)(cfd));
        EventFrag->Led.push_back((int32_t)(led));
        EventFrag->Charge.push_back((int32_t)(charge));
        EventFrag->DataType = (uint16_t)(datatype);
        EventFrag->DetectorType = (uint16_t)(detectortype);
        EventFrag->ChannelId = (uint32_t)(channelid);
        FillFragmentTree(EventFrag);
        EventFrag->Clear();
      }

      for(size_t firstDet = 0; firstDet < fGriffinBgo->size(); ++firstDet) {
        cfd         = 0;
        led         = 0;
        charge      = fGriffinBgo->at(firstDet).Energy();
        datatype    = 0;
        detectortype= 0;
        channelid   = 4*(fGriffinBgo->at(firstDet).DetectorId())+fGriffinBgo->at(firstDet).CrystalId();

        EventFrag->Cfd.push_back((int32_t)(cfd));
        EventFrag->Led.push_back((int32_t)(led));
        EventFrag->Charge.push_back((int32_t)(charge));
        EventFrag->DataType = (uint16_t)(datatype);
        EventFrag->DetectorType = (uint16_t)(detectortype);
        EventFrag->ChannelId = (uint32_t)(channelid);
        FillFragmentTree(EventFrag);
        EventFrag->Clear();
      }


      fGriffinCrystal->clear();
      fGriffinDetector->clear();

      fGriffinBgo->clear();
      fGriffinBgoBack->clear();

      fLaBrDetector->clear();

      fAncillaryBgoCrystal->clear();
      fAncillaryBgoDetector->clear();

      fSceptarDetector->clear();

      eventNumber = fEventNumber;
      belowThreshold.clear();

      EventFrag->Clear();
    }

    // if fSystemID is NOT GRIFFIN, then set fCryNumber to zero
    // This is a quick fix to solve resolution and threshold values from Settings.cc
    if(fSystemID >= 2000) {
        fCryNumber = 0;
    }
    //create energy-resolution smeared energy
    smearedEnergy = fRandom.Gaus(fDepEnergy,fSettings->Resolution(fSystemID,fDetNumber,fCryNumber,fDepEnergy));

    if((fSettings->SortNumberOfEvents()==0)||(fSettings->SortNumberOfEvents()>=fEventNumber) ) {
        //if the hit is above the threshold, we add it to the vector
        if(AboveThreshold(smearedEnergy, fSystemID)) {
          switch(fSystemID) {
          case 1000:
            fGriffinCrystal->push_back(Detector(fEventNumber, fDetNumber, fCryNumber, fDepEnergy, smearedEnergy, TVector3(fPosx,fPosy,fPosz), fTime));
            break;
          case 1010:
          case 1020:
          case 1030:
          case 1040:
            fGriffinBgo->push_back(Detector(fEventNumber, fDetNumber, fCryNumber, fDepEnergy, smearedEnergy, TVector3(fPosx,fPosy,fPosz), fTime));
            break;
          case 1050:
            fGriffinBgoBack->push_back(Detector(fEventNumber, fDetNumber, fCryNumber, fDepEnergy, smearedEnergy, TVector3(fPosx,fPosy,fPosz), fTime));
            break;
          case 2000:
            fLaBrDetector->push_back(Detector(fEventNumber, fDetNumber, fCryNumber, fDepEnergy, smearedEnergy, TVector3(fPosx,fPosy,fPosz), fTime));
            break;
          case 3000:
            fAncillaryBgoCrystal->push_back(Detector(fEventNumber, fDetNumber, fCryNumber, fDepEnergy, smearedEnergy, TVector3(fPosx,fPosy,fPosz), fTime));
            break;
          case 5000:
            fSceptarDetector->push_back(Detector(fEventNumber, fDetNumber, fCryNumber, fDepEnergy, smearedEnergy, TVector3(fPosx,fPosy,fPosz), fTime));
            fSceptarHit = true;
            break;
          default:
            std::cerr<<"Unknown detector system ID "<<fSystemID<<std::endl;
            break;
          }
        } else {
          ++belowThreshold[fSystemID];
        }
    }

    if(i%1000 == 0 && fSettings->VerbosityLevel() > 0) {
      std::cout<<std::setw(3)<<100*i/nEntries<<"% done\r"<<std::flush;
    }
  }

  if(fSettings->VerbosityLevel() > 0) {
    std::cout<<"100% done"<<std::endl;

    if(fSettings->VerbosityLevel() > 1) {
      PrintStatistics();
    }
  }  

  return true;
}

bool Converter::AboveThreshold(double energy, int systemID) {
  if(systemID == 5000) {
    // apply hard threshold of 50 keV on Sceptar
    // SCEPTAR in reality saturates at an efficiency of about 80%. In simulation we get an efficiency of 90%
    // 0.9 * 1.11111111 = 100%, 0.8*1.1111111 = 0.888888888
    if(energy > 50.0 && (fRandom.Uniform(0.,1.) < 0.88888888 )) {
      return true;
    }
    else {
      return false;
    }
  }
  else if(energy > fSettings->Threshold(fSystemID,fDetNumber,fCryNumber)+10*fSettings->ThresholdWidth(fSystemID,fDetNumber,fCryNumber)) {
    return true;
  }

  if(fRandom.Uniform(0.,1.) < 0.5*(TMath::Erf((energy-fSettings->Threshold(fSystemID,fDetNumber,fCryNumber))/fSettings->ThresholdWidth(fSystemID,fDetNumber,fCryNumber))+1)) {
    return true;
  }

  return false;  
}

void Converter::PrintStatistics() {

}

void Converter::SetUpFragmentTree() {
   //if(foutfile)
   //   foutfile->cd();
   //fTimesFillCalled = 0;
   fFragmentTree = new TTree("FragmentTree","FragmentTree");
   fBufferFrag = 0;
   fFragmentTree->Branch("TFragment","TFragment",&fBufferFrag,100000,99);

}

void Converter::FillFragmentTree(TFragment *frag) {
  // if(!fFragmentTree)
  //    return;
   fBufferFrag = frag;

   int bytes =  fFragmentTree->Fill();
   if(bytes < 1)
      printf("\n fill failed with bytes = %i\n",bytes);

   //fTimesFillCalled++;
}
