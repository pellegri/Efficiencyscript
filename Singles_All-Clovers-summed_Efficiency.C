#include <fstream>
#include <TMath.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TGraphErrors.h>
#include <TStyle.h>
#include <TMultiGraph.h>
#include <TH1.h>
#include <TPaveText.h>
using namespace std;

double FitFunction(double *x, double *pars){return exp(pars[0] * pow(log(x[0]),pars[1]));}

int main()
{
//=========Macro generated from canvas: c1/c1
//=========  (Thu Apr 25 15:00:14 2019) by ROOT version5.34/36
   TCanvas *c1 = new TCanvas("c1", "c1",166,68,1200,700);
   
   c1->Range(-46.1314,0.002303113,1698.837,0.04047684);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   

   TGraphErrors *gre = new TGraphErrors(12);
   gre->SetName("Graph0");
   gre->SetTitle("Absolute Efficiency of all Clovers - Singles");
   gre->SetFillColor(1);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(21);
   gre->SetPoint(0,244.6975,0.0324822);
   gre->SetPointError(0,0.0008,0.001632357);
   gre->SetPoint(1,344.2785,0.02576979);
   gre->SetPointError(1,0.0012,0.001347628);
   gre->SetPoint(2,411.1163,0.02283475);
   gre->SetPointError(2,0.0011,0.001163405);
   gre->SetPoint(3,443.965,0.02338382);
   gre->SetPointError(3,0.003,0.001196228);
   gre->SetPoint(4,778.904,0.0137653);
   gre->SetPointError(4,0.0018,0.0006921999);
   gre->SetPoint(5,867.378,0.01347688);
   gre->SetPointError(5,0.004,0.0006875311);
   gre->SetPoint(6,964.079,0.01204269);
   gre->SetPointError(6,0.018,0.0006056074);
   gre->SetPoint(7,1085.869,0.0123782);
   gre->SetPointError(7,0.024,0.0006240398);
   gre->SetPoint(8,1112.074,0.0107745);
   gre->SetPointError(8,0.004,0.000542429);
   gre->SetPoint(9,1212.948,0.009336342);
   gre->SetPointError(9,0.011,0.0005004792);
   gre->SetPoint(10,1299.14,0.01030731);
   gre->SetPointError(10,0.01,0.0005460565);
   gre->SetPoint(11,1408.006,0.009123962);
   gre->SetPointError(11,0.003,0.0004585596);
   
   TF1 * f1 = new TF1("f1",FitFunction,200,1500,2);
   //c1->SetLogy();
   //c1->SetLogx();
    f1->SetParameter(0,1);
    f1->SetParameter(1,0);
    //f1->SetParameter(2,1);
    gre->Fit(f1,"BRME");
    gre->Draw("ap");
    f1->Draw("same");
    
    Double_t a0,a1,a2, par[2];
    //fit->GetParameters(par);
    f1->GetParameters(par);
    
    a0=par[0];a1=par[1];
    
    cout << endl << " par0  " << a0 <<"; par1 " << a1 << endl;
    gStyle->SetOptFit(1);
    
   
   
    TH1F *Graph_Graph1 = new TH1F("Graph_Graph1","Absolute Efficiency of all Clovers - Singles",100,128.3655,1524.34);
   Graph_Graph1->SetMinimum(0.006120487);
   Graph_Graph1->SetMaximum(0.03665947);
   Graph_Graph1->SetDirectory(0);
   Graph_Graph1->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   Graph_Graph1->SetLineColor(ci);
   Graph_Graph1->GetXaxis()->SetTitle("Energy (keV)");
   Graph_Graph1->GetXaxis()->SetLabelFont(42);
   Graph_Graph1->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph1->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph1->GetXaxis()->SetTitleFont(42);
   Graph_Graph1->GetYaxis()->SetTitle("Absolute Efficiency");
   Graph_Graph1->GetYaxis()->SetLabelFont(42);
   Graph_Graph1->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph1->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph1->GetYaxis()->SetTitleOffset(1.4);
   Graph_Graph1->GetYaxis()->SetTitleFont(42);
   Graph_Graph1->GetZaxis()->SetLabelFont(42);
   Graph_Graph1->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph1->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph1->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph1);
   
   //gre->Draw("ap");
   

    
   TPaveText *pt = new TPaveText(0.1940902,0.9343759,0.8059098,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *text = pt->AddText("Absolute Efficiency of all Clovers - Singles");
   pt->Draw();
   
    

    
    Int_t n = 20; //number of energy in the simulation
    
    Double_t En[20], Eff[20], Err[20];
    
    ifstream my_input_file;
    my_input_file.open("PR251-Efficiency-noAddback.dat");
    
    if (!my_input_file) {
        cerr << "Unable to open file";
        exit(1);   // call system to stop
    }

    for (int i=0; i<n; i++)
      {
        my_input_file >> En[i] >> Eff[i] >> Err[i];
        En[i]=En[i]*1000;
        Eff[i]=Eff[i]/100;
        Err[i]=Err[i]/100;
        //cout << En[i] << " keV " << Eff[i] << " " << Err[i] << endl;
      }
    
    my_input_file.close();
    
    
    TGraphErrors *Eff_Geant = new TGraphErrors(n,En,Eff,0,Err);
    Eff_Geant->SetName("Eff_Geant");
    Eff_Geant->SetMarkerStyle(20);
    Eff_Geant->SetMarkerColor(4);
    //Eff_Geant->Draw("AP");
    
    TF1 *fit2 = new TF1("fit2",FitFunction,200,10000,2);
    fit2->SetParameter(0,f1->GetParameter(0));
    fit2->SetParameter(1,f1->GetParameter(1));
    fit2->SetLineColor(3);
    
    Eff_Geant->Fit(fit2,"BRME");
    Eff_Geant->Draw("AP");
    fit2->Draw("same");
    
    Double_t b0,b1, parb[2];
    fit2->GetParameters(parb);
    
    b0=parb[0]; b1=parb[1];
    
    cout << endl << " Fit2 par0  " << b0 <<"; Fit2 par1 " << b1 << endl;
    gStyle->SetOptFit(1);
    
    
    
    TGraphErrors *g[2];
    TMultiGraph *mg = new TMultiGraph();
    
    g[0]=gre;
    g[1]=Eff_Geant;
    
    for (int j=0; j<2; j++) {
        mg->Add(g[j]);
    }
    
    //mg->Draw("AP");
    

    
   
    
    
   c1->Modified();
   c1->Update();
   //c1->cd();
   //c1->SetSelected(c1);
  
    
   return 0;
}




