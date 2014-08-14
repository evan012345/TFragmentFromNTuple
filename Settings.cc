#include "Settings.hh"

#include "TEnv.h"
#include "TString.h"

Settings::Settings(std::string fileName, int verbosityLevel)
  : fVerbosityLevel(verbosityLevel) {
  TEnv env;
  env.ReadFile(fileName.c_str(),kEnvLocal);

//  env.PrintEnv();

//  std::cout << " WE ARE IN SETTINGS.CC " << std::endl;

  fBufferSize = env.GetValue("BufferSize",1024000);

  fSortNumberOfEvents = env.GetValue("SortNumberOfEvents",0);

  fWriteTree = env.GetValue("WriteTree",true);

  fResolution[1000].resize(16); 
  fThreshold[1000].resize(16,std::vector<double>(4)); 
  fThresholdWidth[1000].resize(16,std::vector<double>(4)); 

  fResolution[1010].resize(16); 
  fThreshold[1010].resize(16,std::vector<double>(4)); 
  fThresholdWidth[1010].resize(16,std::vector<double>(4)); 

  fResolution[1020].resize(16); 
  fThreshold[1020].resize(16,std::vector<double>(4)); 
  fThresholdWidth[1020].resize(16,std::vector<double>(4)); 

  fResolution[1030].resize(16); 
  fThreshold[1030].resize(16,std::vector<double>(4)); 
  fThresholdWidth[1030].resize(16,std::vector<double>(4)); 

  fResolution[1040].resize(16); 
  fThreshold[1040].resize(16,std::vector<double>(4)); 
  fThresholdWidth[1040].resize(16,std::vector<double>(4)); 

  fResolution[1050].resize(16); 
  fThreshold[1050].resize(16,std::vector<double>(4)); 
  fThresholdWidth[1050].resize(16,std::vector<double>(4)); 

  fResolution[2000].resize(16);
  fThreshold[2000].resize(16,std::vector<double>(1));
  fThresholdWidth[2000].resize(16,std::vector<double>(1));

//  fResolution[5000].resize(20);
//  fThreshold[5000].resize(20,std::vector<double>(4));
//  fThresholdWidth[5000].resize(20,std::vector<double>(4));

  double offset, linear, quadratic, cubic;
  for(int detector = 0; detector < 16; ++detector) {
    for(int crystal = 0; crystal < 4; ++crystal) {
      offset = env.GetValue(Form("Griffin.%d.%d.Resolution.Offset",detector,crystal),1.100);
      linear = env.GetValue(Form("Griffin.%d.%d.Resolution.Linear",detector,crystal),0.00183744);
      quadratic = env.GetValue(Form("Griffin.%d.%d.Resolution.Quadratic",detector,crystal),0.0000007);
      cubic = env.GetValue(Form("Griffin.%d.%d.Resolution.Cubic",detector,crystal),0.);
      fResolution[1000][detector].push_back(TF1(Form("Griffin.%d.%d.Resolution",detector,crystal),
						Form("(TMath::Sqrt((%f+%f*x+%f*x*x+%f*x*x*x)))/(2.*TMath::Sqrt(2.*TMath::Log(2.)))",offset, linear, quadratic, cubic),0.,100000.));
      fThreshold[1000][detector][crystal] = env.GetValue(Form("Griffin.%d.%d.Threshold.keV",detector,crystal),10.);
      fThresholdWidth[1000][detector][crystal] = env.GetValue(Form("Griffin.%d.%d.ThresholdWidth.keV",detector,crystal),2.);

      offset = env.GetValue(Form("Griffin.BGO.Front.Left.%d.%d.Resolution.Offset",detector,crystal),1.100);
      linear = env.GetValue(Form("Griffin.BGO.Front.Left.%d.%d.Resolution.Linear",detector,crystal),0.00183744);
      quadratic = env.GetValue(Form("Griffin.BGO.Front.Left.%d.%d.Resolution.Quadratic",detector,crystal),0.0000007);
      cubic = env.GetValue(Form("Griffin.BGO.Front.Left.%d.%d.Resolution.Cubic",detector,crystal),0.);
      fResolution[1010][detector].push_back(TF1(Form("Griffin.BGO.Front.Left.%d.%d.Resolution",detector,crystal),
						Form("(TMath::Sqrt((%f+%f*x+%f*x*x+%f*x*x*x)))/(2.*TMath::Sqrt(2.*TMath::Log(2.)))",offset, linear, quadratic, cubic),0.,100000.));
      fThreshold[1010][detector][crystal] = env.GetValue(Form("Griffin.BGO.Front.Left.%d.%d.Threshold.keV",detector,crystal),10.);
      fThresholdWidth[1010][detector][crystal] = env.GetValue(Form("Griffin.BGO.Front.Left.%d.%d.ThresholdWidth.keV",detector,crystal),2.);

      offset = env.GetValue(Form("Griffin.BGO.Front.Right.%d.%d.Resolution.Offset",detector,crystal),1.100);
      linear = env.GetValue(Form("Griffin.BGO.Front.Right.%d.%d.Resolution.Linear",detector,crystal),0.00183744);
      quadratic = env.GetValue(Form("Griffin.BGO.Front.Right.%d.%d.Resolution.Quadratic",detector,crystal),0.0000007);
      cubic = env.GetValue(Form("Griffin.BGO.Front.Right.%d.%d.Resolution.Cubic",detector,crystal),0.);
      fResolution[1020][detector].push_back(TF1(Form("Griffin.BGO.Front.Right.%d.%d.Resolution",detector,crystal),
						Form("(TMath::Sqrt((%f+%f*x+%f*x*x+%f*x*x*x)))/(2.*TMath::Sqrt(2.*TMath::Log(2.)))",offset, linear, quadratic, cubic),0.,100000.));
      fThreshold[1020][detector][crystal] = env.GetValue(Form("Griffin.BGO.Front.Right.%d.%d.Threshold.keV",detector,crystal),10.);
      fThresholdWidth[1020][detector][crystal] = env.GetValue(Form("Griffin.BGO.Front.Right.%d.%d.ThresholdWidth.keV",detector,crystal),2.);

      offset = env.GetValue(Form("Griffin.BGO.Side.Left.%d.%d.Resolution.Offset",detector,crystal),1.100);
      linear = env.GetValue(Form("Griffin.BGO.Side.Left.%d.%d.Resolution.Linear",detector,crystal),0.00183744);
      quadratic = env.GetValue(Form("Griffin.BGO.Side.Left.%d.%d.Resolution.Quadratic",detector,crystal),0.0000007);
      cubic = env.GetValue(Form("Griffin.BGO.Side.Left.%d.%d.Resolution.Cubic",detector,crystal),0.);
      fResolution[1030][detector].push_back(TF1(Form("Griffin.BGO.Side.Left.%d.%d.Resolution",detector,crystal),
						Form("(TMath::Sqrt((%f+%f*x+%f*x*x+%f*x*x*x)))/(2.*TMath::Sqrt(2.*TMath::Log(2.)))",offset, linear, quadratic, cubic),0.,100000.));
      fThreshold[1030][detector][crystal] = env.GetValue(Form("Griffin.BGO.Side.Left.%d.%d.Threshold.keV",detector,crystal),10.);
      fThresholdWidth[1030][detector][crystal] = env.GetValue(Form("Griffin.BGO.Side.Left.%d.%d.ThresholdWidth.keV",detector,crystal),2.);

      offset = env.GetValue(Form("Griffin.BGO.Side.Right.%d.%d.Resolution.Offset",detector,crystal),1.100);
      linear = env.GetValue(Form("Griffin.BGO.Side.Right.%d.%d.Resolution.Linear",detector,crystal),0.00183744);
      quadratic = env.GetValue(Form("Griffin.BGO.Side.Right.%d.%d.Resolution.Quadratic",detector,crystal),0.0000007);
      cubic = env.GetValue(Form("Griffin.BGO.Side.Right.%d.%d.Resolution.Cubic",detector,crystal),0.);
      fResolution[1040][detector].push_back(TF1(Form("Griffin.BGO.Side.Right.%d.%d.Resolution",detector,crystal),
						Form("(TMath::Sqrt((%f+%f*x+%f*x*x+%f*x*x*x)))/(2.*TMath::Sqrt(2.*TMath::Log(2.)))",offset, linear, quadratic, cubic),0.,100000.));
      fThreshold[1040][detector][crystal] = env.GetValue(Form("Griffin.BGO.Side.Right.%d.%d.Threshold.keV",detector,crystal),10.);
      fThresholdWidth[1040][detector][crystal] = env.GetValue(Form("Griffin.BGO.Side.Right.%d.%d.ThresholdWidth.keV",detector,crystal),2.);

      offset = env.GetValue(Form("Griffin.BGO.Back.%d.%d.Resolution.Offset",detector,crystal),1.100);
      linear = env.GetValue(Form("Griffin.BGO.Back.%d.%d.Resolution.Linear",detector,crystal),0.00183744);
      quadratic = env.GetValue(Form("Griffin.BGO.Back.%d.%d.Resolution.Quadratic",detector,crystal),0.0000007);
      cubic = env.GetValue(Form("Griffin.BGO.Back.%d.%d.Resolution.Cubic",detector,crystal),0.);
      fResolution[1050][detector].push_back(TF1(Form("Griffin.BGO.Back.%d.%d.Resolution",detector,crystal),
						Form("(TMath::Sqrt((%f+%f*x+%f*x*x+%f*x*x*x)))/(2.*TMath::Sqrt(2.*TMath::Log(2.)))",offset, linear, quadratic, cubic),0.,100000.));
      fThreshold[1050][detector][crystal] = env.GetValue(Form("Griffin.BGO.Back.%d.%d.Threshold.keV",detector,crystal),10.);
      fThresholdWidth[1050][detector][crystal] = env.GetValue(Form("Griffin.BGO.Back.%d.%d.ThresholdWidth.keV",detector,crystal),2.);
    }
  }



  //double offset, linear, quadratic, cubic;
  for(int detector = 0; detector < 16; ++detector) {
      offset = env.GetValue(Form("LaBr3.%d.Resolution.Offset",detector),1.7006116);
      linear = env.GetValue(Form("LaBr3.%d.Resolution.Linear",detector),0.5009382);
      quadratic = env.GetValue(Form("LaBr3.%d.Resolution.Quadratic",detector),0.000065451219);
      cubic = env.GetValue(Form("LaBr3.%d.Resolution.Cubic",detector),0.);
      fResolution[2000][detector].push_back(TF1(Form("LaBr3.%d.Resolution",detector),
                        Form("(TMath::Sqrt((%f+%f*x+%f*x*x+%f*x*x*x)))/(2.*TMath::Sqrt(2.*TMath::Log(2.)))",offset, linear, quadratic, cubic),0.,100000.));
      fThreshold[2000][detector][0] = env.GetValue(Form("LaBr3.%d.Threshold.keV",detector),10.);
      fThresholdWidth[2000][detector][0] = env.GetValue(Form("LaBr3.%d.ThresholdWidth.keV",detector),2.);
  }

  //  for(int detector = 0; detector < 20; ++detector) {
  //    for(int crystal = 0; crystal < 1; ++crystal) {
  //      offset = env.GetValue(Form("Sceptar.%d.%d.Resolution.Offset",detector,crystal),0.0);
  //      linear = env.GetValue(Form("Sceptar.%d.%d.Resolution.Linear",detector,crystal),0.0);
  //      quadratic = env.GetValue(Form("Sceptar.%d.%d.Resolution.Quadratic",detector,crystal),0.0);
  //      cubic = env.GetValue(Form("Sceptar.%d.%d.Resolution.Cubic",detector,crystal),0.0);
  //      fResolution[5000][detector].push_back(TF1(Form("Sceptar.%d.%d.Resolution",detector,crystal),
  //                        Form("(TMath::Sqrt((%f+%f*x+%f*x*x+%f*x*x*x)))/(2.*TMath::Sqrt(2.*TMath::Log(2.)))",offset, linear, quadratic, cubic),0.,100000.));
  //      fThreshold[5000][detector][crystal] = env.GetValue(Form("Sceptar.%d.%d.Threshold.keV",detector,crystal),50.);
  //      fThresholdWidth[5000][detector][crystal] = env.GetValue(Form("Sceptar.%d.%d.ThresholdWidth.keV",detector,crystal),1.);
  //    }
  //  }

  fNofBins["Statistics"] = env.GetValue("Histogram.Statistics.NofBins",16);
  fRangeLow["Statistics"] = env.GetValue("Histogram.Statistics.RangeLow.keV",0.);
  fRangeHigh["Statistics"] = env.GetValue("Histogram.Statistics.RangeHigh.keV",16.);
}
