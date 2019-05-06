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
//========= Macro generated from object: Graph/Absolute Efficiency of all Clovers - Addback
//========= by ROOT version5.34/36
   
   TGraphErrors *gre = new TGraphErrors(12);
   gre->SetName("Graph");
   gre->SetTitle("Absolute Efficiency of all Clovers - Addback");
   gre->SetFillColor(1);
   gre->SetMarkerColor(6);
   gre->SetMarkerStyle(21);
   gre->SetPoint(0,244.697,0.0328771);
   gre->SetPointError(0,0.0008,0.00165213);
   gre->SetPoint(1,344.279,0.028179);
   gre->SetPointError(1,0.0012,0.00147346);
   gre->SetPoint(2,411.116,0.025822);
   gre->SetPointError(2,0.0011,0.00131289);
   gre->SetPoint(3,443.965,0.0271977);
   gre->SetPointError(3,0.003,0.00138866);
   gre->SetPoint(4,778.904,0.0179226);
   gre->SetPointError(4,0.0018,0.000900158);
   gre->SetPoint(5,867.378,0.0178883);
   gre->SetPointError(5,0.004,0.000909007);
   gre->SetPoint(6,964.079,0.0163614);
   gre->SetPointError(6,0.018,0.000821636);
   gre->SetPoint(7,1085.87,0.0168883);
   gre->SetPointError(7,0.024,0.000849741);
   gre->SetPoint(8,1112.07,0.0148121);
   gre->SetPointError(8,0.004,0.000744407);
   gre->SetPoint(9,1212.95,0.0128204);
   gre->SetPointError(9,0.011,0.000675587);
   gre->SetPoint(10,1299.14,0.0143523);
   gre->SetPointError(10,0.01,0.000749492);
   gre->SetPoint(11,1408.01,0.0131459);
   gre->SetPointError(11,0.003,0.000659708);
   
    
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
    
    
   /*
   TH1F *Graph_Graph1 = new TH1F("Graph_Graph1","Absolute Efficiency of all Clovers - Addback",100,128.365,1524.34);
   Graph_Graph1->SetMinimum(0.00990643);
   Graph_Graph1->SetMaximum(0.0367676);
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
   
   gre->Draw("");
    
    */
    
    Int_t n = 20; //number of energy in the simulation
    
    Double_t En[20], Eff[20], Err[20];
    
    ifstream my_input_file;
    my_input_file.open("PR251-Efficiency-Addback.dat");
    
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
    
    mg->SetTitle("Absolute Efficiency of all Clovers - Addback");
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
