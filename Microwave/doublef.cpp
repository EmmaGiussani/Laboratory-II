/*
c++ -o doublef doublef.cpp `root-config --cflags --glibs`
*/

#include <iostream>

#include <TStyle.h>
#include <TApplication.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TGraphErrors.h>
#include <TAxis.h>
#include <cmath>
#include <math.h>

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
  myGraph->SetTitle("Doppia fenditura d=7,5 cm");
  myGraph->GetXaxis()->SetTitle("#theta [rad]");
  myGraph->GetYaxis()->SetTitle("V [V]");
  
  TF1* myFun = new TF1 ("myFun","[0]*(cos(3.14*0.075*sin(x)/[1]))^2");
  //[0]*cos(3.14*0.06*sin(x)/[1])*cos(3.14*0.06*sin(x)/[1])*(sin(3.14*0.015*sin(x)/[1])/(3.14*0.015*sin(x)/[1]))*(sin(3.14*0.015*sin(x)/[1])/(3.14*0.015*sin(x)/[1]))
  //[0]*cos(3.14*0.09*sin(x)/[1])*cos(3.14*0.09*sin(x)/[1])
  //myFun->SetParName(1,"L [H]");
  //myC->SetLogx();
  myFun->SetParName(0,"p_{0} [W/m^{2}]");
  myFun->SetParName(1,"#lambda [m]");
  //myFun->SetParameter(1,0.04);
  myFun->SetParameter(0,0);
  myFun->SetParameter(1,0.0285);

  myC->cd();
  myGraph->Draw("AP");
  myGraph->Fit("myFun");   
  myC->Modified();
  myC->Update();

  myApp->Run();
  return 0;
}


