/*
c++ -o fitretta fitretta.cpp `root-config --cflags --glibs`
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
  myGraph->SetTitle("Resistenze in parallelo");
  myGraph->GetXaxis()->SetTitle("V[V]");
  myGraph->GetYaxis()->SetTitle("I[A]");
  
  TF1* myFun = new TF1 ("myFun","[0]+[1]*x");
  myFun->SetParName(0,"A");
  myFun->SetParName(1,"B");
  myFun->SetParameter(0,8);
  myFun->SetParameter(1,0.004);

  myC->cd();
  myGraph->Draw("AP");
  myGraph->Fit("myFun");   
  myC->Modified();
  myC->Update();

  cout << "\nThe result of the fit with the model y(x) = A+Bx is:" << endl;
  cout << "A = " << myFun->GetParameter(0) << " +/- " << myFun->GetParError(0) << endl;
  cout << "B = " << myFun->GetParameter(1) << " +/- " << myFun->GetParError(1) << endl;
    
  myApp->Run();
  return 0;
}
