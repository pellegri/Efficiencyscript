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

double FitFunction(double *x, double *pars){return exp(pars[0] * pow(log(x[0]),0)+pars[1] * pow(log(x[0]),1)+pars[2] * pow(log(x[0]),2));}


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
   gre->SetName("Eff_152Eu");
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
   
   TF1 * fit1 = new TF1("f1",FitFunction,200,1500,3);
    fit1->SetParameter(0,1);
    fit1->SetParameter(1,0);
    fit1->SetParameter(2,0);
    fit1->SetLineColor(5);
    fit1->SetLineStyle(2);
    
    gre->Fit(f1,"BRME");
    gre->Draw("ap");
    fit1->Draw("same");
    
    Double_t a0,a1,a2, par[3];
    fit1->GetParameters(par);
    
    a0=par[0];a1=par[1];a2=par[2];
    
    cout << endl << " par0  " << a0 <<"; par1 " << a1 << "; par2 " << a2 << endl;
    //gStyle->SetOptFit(1);
    
   /*
   
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
   
    
   */
    
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
    
    TF1 *fit2 = new TF1("fit2",FitFunction,400,10000,3);
    fit2->SetParameter(0,fit1->GetParameter(0));
    fit2->SetParameter(1,fit1->GetParameter(1));
    fit2->SetParameter(1,fit1->GetParameter(2));
    fit2->SetLineColor(3);
    fit2->SetLineStyle(2);
    
    Eff_Geant->Fit(fit2,"BRME");
    Eff_Geant->Draw("AP");
    fit2->Draw("same");
    
    Double_t b0,b1,b2, parb[3];
    fit2->GetParameters(parb);
    
    b0=parb[0]; b1=parb[1]; b2=parb[2];
    
    cout << endl << " Fit2 par0  " << b0 <<"; Fit2 par1 " << b1 <<"; Fit2 par2 " << b2 << endl;
    //gStyle->SetOptFit(1);
    
    Double_t Eff_norm[20], normfact=0;

    normfact=exp(a0 * pow(log(1000),0)+ a1 * pow(log(1000),1)+ a2 * pow(log(1000),2))/exp(b0 * pow(log(1000),0)+b1 * pow(log(1000),1)+b2 * pow(log(1000),2)); //at 1000keV
    cout << "normfact= " << normfact << endl;
    
    for (int i=0; i<n; i++)
    {
        Eff_norm[i]=Eff[i]*normfact;
    }
    
    TGraphErrors *Eff_Geant_norm = new TGraphErrors(n,En,Eff_norm,0,Err);
    Eff_Geant_norm->SetName("Eff_Geant_norm");
    Eff_Geant_norm->SetMarkerStyle(20);
    Eff_Geant_norm->SetMarkerColor(1);
    
    
    TF1 *fit3 = new TF1("fit3",FitFunction,400,10000,3);
    fit3->SetParameter(0,fit2->GetParameter(0));
    fit3->SetParameter(1,fit2->GetParameter(1));
    fit3->SetParameter(1,fit2->GetParameter(2));
    fit3->SetLineColor(2);
    fit3->SetLineStyle(2);
    
    Eff_Geant_norm->Fit(fit3,"BRME");
    Eff_Geant_norm->Draw("AP");
    fit3->Draw("same");
    
    Double_t d0,d1,d2, pard[3];
    fit3->GetParameters(pard);
    
    d0=pard[0]; d1=pard[1]; d2=pard[2];
    
    cout << endl << " Fit3 par0  " << d0 <<"; Fit3 par1 " << d1 <<"; Fit3 par2 " << d2 << endl;
    
    
    TGraphErrors *g[3];
    TMultiGraph *mg = new TMultiGraph();
    
    g[0]=gre;
    g[1]=Eff_Geant;
    g[2]=Eff_Geant_norm;
    
    for (int j=0; j<3; j++) {
        mg->Add(g[j]);
    }
    
    mg->Draw("AP");
    
    mg->SetTitle("Absolute Efficiency of all Clovers - Singles");
    mg->GetXaxis()->SetTitle("Energy (keV)");
    mg->GetXaxis()->SetLabelFont(42);
    mg->GetXaxis()->SetLabelSize(0.035);
    mg->GetXaxis()->SetTitleSize(0.035);
    mg->GetXaxis()->SetTitleFont(42);
    mg->GetYaxis()->SetTitle("Absolute Efficiency");
    mg->GetYaxis()->SetLabelFont(42);
    mg->GetYaxis()->SetLabelSize(0.035);
    mg->GetYaxis()->SetTitleSize(0.035);
    mg->GetYaxis()->SetTitleOffset(1.4);
    mg->GetYaxis()->SetTitleFont(42);
    
    
    
   
    
    
   c1->Modified();
   c1->Update();
   //c1->cd();
   //c1->SetSelected(c1);
  
    
   return 0;
}




