/*
c++ -o fitstaz2 fit_stazionarie2.cpp `root-config --cflags --glibs`

./fitstaz2 dati_fitstaz.txt dati_staz.txt
*/

#include <iostream>

#include <TStyle.h>
#include <TApplication.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TGraphErrors.h>
#include <TMultiGraph.h>
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
  TMultiGraph* myC = new TMultiGraph();
  TGraphErrors* myGraph1 = new TGraphErrors(argv[1]);
  myGraph1->SetMarkerStyle(20);
  myGraph1->SetTitle("I vs R");
  myGraph1->GetXaxis()->SetTitle("R [cm]");
  myGraph1->GetYaxis()->SetTitle("V[V]");
  
  TF1* myFun = new TF1 ("myFun","[0]/(4*3.14*x^2)");
  myFun->SetParName(0,"P [W]");
  //myFun->SetParName(1,"B");
  myFun->SetParameter(0,0);
  //myFun->SetParameter(1,0.004);
  
  TGraphErrors* myGraph2 = new TGraphErrors(argv[2]);
  myGraph2->SetMarkerStyle(20);
  //myGraph2->Draw("C");
 
  
  myC->Add(myGraph2, "C");
  myGraph1->Fit("myFun"); 
  //myGraph2->Draw("AP"); 
  myC->SetTitle("Intensita' in funzione della distanza") ;
  myC->GetXaxis()->SetTitle("R [cm]");
  myC->GetYaxis()->SetTitle("V[V]");
  myC->Add(myGraph1);
  myC->Draw("AP");
  
 

  cout << "\nThe result of the fit with the model y(x) = A+Bx is:" << endl;
  cout << "A = " << myFun->GetParameter(0) << " +/- " << myFun->GetParError(0) << endl;
  cout << "B = " << myFun->GetParameter(1) << " +/- " << myFun->GetParError(1) << endl;
    
  myApp->Run();
  return 0;
}
