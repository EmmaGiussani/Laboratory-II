/*
c++ -o fitV_R fitV_R.cpp `root-config --cflags --glibs`
*/

#include <iostream>

#include <TStyle.h>
#include <TApplication.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TGraphErrors.h>
#include <TAxis.h>

using namespace std;

int main(int argc, char** argv)
{
  if (argc < 2)
    {
      cout << "Not enough parameters: ./fitretta filedati.txt" << endl;
      return 1;
    }
  
  gStyle->SetOptFit(1112);

  TApplication* myApp = new TApplication("myApp", NULL, NULL);
  TCanvas* myC = new TCanvas("myC","myC",0,0,700,500);
  TGraphErrors* myGraph = new TGraphErrors(argv[1]);
  myGraph->SetMarkerStyle(20);
  myGraph->SetTitle("V_{L}(t)");
  myGraph->GetXaxis()->SetTitle("t [#museconds]");
  myGraph->GetYaxis()->SetTitle("V(t) [Volt]");
  
  TF1* myFun = new TF1 ("myFun","[0]*exp(-x/[1])");
  myFun->SetParName(0,"V_{0} [Volt]");
  myFun->SetParName(1,"#tau [#museconds]");
  myFun->SetParameter(0,8);
  myFun->SetParameter(1,2);

  myC->cd();
  myGraph->Draw("AP");
  myGraph->Fit("myFun");   
  myC->Modified();
  myC->Update();

  cout << "\nThe result of the fit with the model I(p1,p2) = p1*(exp(p2)-1) is:" << endl;
  cout << "A = " << myFun->GetParameter(0) << " +/- " << myFun->GetParError(0) << endl;
  cout << "B = " << myFun->GetParameter(1) << " +/- " << myFun->GetParError(1) << endl;
    
  myApp->Run();
  return 0;
}
