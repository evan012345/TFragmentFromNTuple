#include"TFragment.hh"

#include <TClass.h>

ClassImp(TFragment)


TFragment::TFragment(){
   Class()->IgnoreTObjectStreamer(true);
   Clear();
}

TFragment::~TFragment(){
	//Clear();
}

void TFragment::Clear(Option_t *opt){  
   MidasTimeStamp    = 0;
   MidasId           = 0;

   TriggerId         = 0;
   FragmentId        = 0;
   TriggerBitPattern = 0;

   ChannelAddress    = -1;
   Cfd.clear();//              = -1;
   Led.clear();//               = -1;
   Charge.clear();//            = -1;
  
   //TimeStamp         = -1;
   TimeStampLow  = 0;
   TimeStampHigh = 0;


   PPG                = 0; 
   DeadTime           = 0; 
   NumberOfFilters    = 0; 
   NumberOfPileups    = 0; 
   DataType           = 0; 
   DetectorType       = 0; 
   ChannelId          = 0; 



   if(!wavebuffer.empty())
      wavebuffer.clear();

   if(!KValue.empty())     //->
   	KValue.clear();      //->

}

void TFragment::Print(Option_t *opt)	{
//	printf("not written yet.\n");

//   TChannel *chan = TChannel::GetChannel(this->ChannelAddress);
//   if(chan) {
//	   //printf("%s Event at	%i:\n", chan->GetDigitizerType().c_str(), MidasId);
//	   printf("MidasId    	%i\n", MidasId);
//	   printf("TriggerId: 	%lu\n", TriggerId);
//	   printf("FragmentId:   %i\n", FragmentId);
//	   printf("TriggerBit:	0x%08x\n", TriggerBitPattern);
//	   //printf("Channel: %i\tName: %s\n", chan->GetNumber(), chan->GetChannelName().c_str());
//	   printf("\tChannel Address: 0x%08x", ChannelAddress);
//	   printf("\t\tChannel Num:      %i\n", chan->GetNumber());
//	   printf("\tCharge		  "); for(int x=0;x<Charge.size();x++){printf( "     0x%08x\n", Charge.at(x));} printf("\n");
//	   printf("\tCfd		  "); for(int x=0;x<Cfd.size();x++) {printf( "     0x%08x\n", Cfd.at(x));} printf("\n");
//	   printf("\t\tTimeStamp High: 0x%08x\n", TimeStampHigh);
//	   printf("\t\tTimeStamp Low:    0x%08x\n", TimeStampLow);
//	   printf("\tTimeToTrig:  %i\n", TimeToTrig);
//	   //unsigned short temptime = (TimeStampLow & 0x0000ffff) - ((Cfd >> 4) & 0x0000ffff);   //TimeStampLow&0x0000ffff;
//	   //printf("\ttime from timestamp(to the nearest 10ns):    0x%04x\t%ins\n", temptime, temptime * 10);
//	   if (!wavebuffer.empty())
//	      printf("Has a wave form stored.\n");
//	   else
//	      printf("Does Not have a wave form stored.\n");
//	}


}











