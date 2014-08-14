#ifndef __SETTINGS_HH
#define __SETTINGS_HH

#include <string>
#include <map>
#include <vector>

#include "TF1.h"

class Settings {
public:
  Settings(std::string, int);
  ~Settings(){};

  int VerbosityLevel() {
    return fVerbosityLevel;
  }

  int BufferSize() {
    return fBufferSize;
  }

  int SortNumberOfEvents() {
    return fSortNumberOfEvents;
  }

  bool WriteTree() {
    return fWriteTree;
  }

  double Resolution(int systemID, int detectorID, int crystalID, double en) {
    if(fResolution.find(systemID) != fResolution.end()) {
      return fResolution[systemID].at(detectorID).at(crystalID).Eval(en);
    }
    return 0.;
  }
  double Threshold(int systemID, int detectorID, int crystalID) {
    if(fThreshold.find(systemID) != fThreshold.end()) {
      return fThreshold[systemID].at(detectorID).at(crystalID);
    }
    return 0.001;
  }
  double ThresholdWidth(int systemID, int detectorID, int crystalID) {
    if(fThresholdWidth.find(systemID) != fThresholdWidth.end()) {
      return fThresholdWidth[systemID].at(detectorID).at(crystalID);
    }
    return 0.;
  }

  int NofBins(std::string directoryName) {
    if(fNofBins.find(directoryName) != fNofBins.end()) {
      return fNofBins[directoryName];
    }
    return 10000;
  }
  double RangeLow(std::string directoryName) {
    if(fRangeLow.find(directoryName) != fRangeLow.end()) {
      return fRangeLow[directoryName];
    }
    return 0.5;
  }
  double RangeHigh(std::string directoryName) {
    if(fRangeHigh.find(directoryName) != fRangeHigh.end()) {
      return fRangeHigh[directoryName];
    }
    return 10000.5;
  }

private:
  int fVerbosityLevel;
  int fBufferSize;
  int fSortNumberOfEvents;

  bool fWriteTree;

  std::map<int,std::vector<std::vector<TF1> > > fResolution;
  std::map<int,std::vector<std::vector<double> > > fThreshold;
  std::map<int,std::vector<std::vector<double> > > fThresholdWidth;

  std::map<std::string,int> fNofBins;
  std::map<std::string,double> fRangeLow;
  std::map<std::string,double> fRangeHigh;
};

#endif
