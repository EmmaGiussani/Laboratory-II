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
  myGraph->SetTitle("Potenza sul carico senza trasformatore");
  myGraph->GetXaxis()->SetTitle("R_{load}");
  myGraph->GetYaxis()->SetTitle("P_{load}");
  
  
  myC->cd();
  myGraph->Draw("AP");
  myC->Modified();
  myC->Update();

  myApp->Run();
  return 0;
}
