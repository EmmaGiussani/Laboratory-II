/*
c++ -o fitretta0 fitretta0.cpp `root-config --cflags --glibs`
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
  myGraph->SetTitle("Capacità interna");
  myGraph->GetXaxis()->SetTitle("V");
  myGraph->GetYaxis()->SetTitle("I");
  
  TF1* myFun = new TF1 ("myFun","[0]*x");
  myFun->SetParName(0,"K");
  myFun->SetParameter(0,0.004);


  myC->cd();
  myGraph->Draw("AP");
  myGraph->Fit("myFun");   
  myC->Modified();
  myC->Update();

  cout << "\nThe result of the fit with the model y(x) = Kx is:" << endl;
  cout << "K = " << myFun->GetParameter(0) << " +/- " << myFun->GetParError(0) << endl;
    
  myApp->Run();
  return 0;
}
