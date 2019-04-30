#include "TFile.h"
#include "TMath.h"
#include "TH1.h"
#include "TF1.h"
#include "TROOT.h"
#include "TCanvas.h"
#include "TChain.h"
#include <iostream>
#include <vector>

int main()
{
    
    gROOT->Reset();
  
    TFile f("Analyse.root","recreate");

    double nrofThreads = 3;

    //----------------------------------------------------
    //      Path to the directory holding the .root files
   //  char rootFileDirectoryPath[] = "/Users/lunapellegri/Google Drive/GEANT4/BaGeL/K600-ALBA-MT";
    char rootFileDirectoryPath[] = "/home/luna/codes/geant_simulations/K600-ALBA-MT";

    char name[512];
    char filename[512];
    char condition[512];
    char command[512];

    
    TChain *DataTreeChain = new TChain("DataTreeSim","DataTreeSim");
    TChain *GeometryAnalysisTree = new TChain("GeometryAnalysisTree","GeometryAnalysisTree");
    TChain *InputVariableTree = new TChain("InputVariableTree","InputVariableTree");

    for(Int_t i=0; i<nrofThreads; i++)
    {
        //sprintf(name,"K600Output_t%d.root", i);
        sprintf(filename,"%s/K600Output_t%d.root", rootFileDirectoryPath, i);
        //sprintf(name,"%s/K600Output.root", rootFileDirectoryPath, i);
        
        DataTreeChain->Add(filename);
        GeometryAnalysisTree->Add(filename);
        InputVariableTree->Add(filename);
    }
    

    
    TCanvas * c1 = new TCanvas("c1", "c1", 1000, 700);
    
    //------------------------------------------------
    int nParticlesPerEnergy = 2000000;
    
    std::vector<double> initialParticleKineticEnergy; // keV
    
    /*
    initialParticleKineticEnergy.push_back(0.1);
    initialParticleKineticEnergy.push_back(0.1332);
    initialParticleKineticEnergy.push_back(0.2);
    initialParticleKineticEnergy.push_back(0.4);
    initialParticleKineticEnergy.push_back(0.7);
    initialParticleKineticEnergy.push_back(1.0);
    initialParticleKineticEnergy.push_back(1.332);
    initialParticleKineticEnergy.push_back(2.0);
    initialParticleKineticEnergy.push_back(4.0);
    initialParticleKineticEnergy.push_back(7.0);
    initialParticleKineticEnergy.push_back(10.0);
    initialParticleKineticEnergy.push_back(13.32);
    initialParticleKineticEnergy.push_back(20.0);
    */
    
    int nEnergies = 20;
    
    double energyMin = 0.5;
    double energyMax = 10.0;
    double energyDivision = ((energyMax-energyMin)/(nEnergies-1));
    
    for(int i=0; i<nEnergies; i++)
    {
        initialParticleKineticEnergy.push_back(((i*energyDivision) + energyMin));
    }

    ////================================================
    std::vector<double> integrals;
    std::vector<double> efficiencies;
    std::vector<double> efficiencyErrors;

    ////================================================
   // Luna std::vector<std::shared_ptr<TH1F>> hEnergy_noAddback_energy;
    
    ofstream outputFile;
    outputFile.open("PR251-Efficiency-noAddback.dat");

    
    std::cout << "No Add-back" << std::endl;
        
    for(int i=0; i<(int) initialParticleKineticEnergy.size(); i++)
    {
        sprintf(name,"hEnergy_noAddback_energy%d_%dkeV", i, 1000*initialParticleKineticEnergy[i]);
        std::cout << name << std::endl;
        TH1F *hE_noAddback = new TH1F(name,"noAddback",2*22000, 0.0, 22000.0); //Luna
      // Luna hEnergy_noAddback_energy.push_back(std::shared_ptr<TH1F>(new TH1F(name, "", 2*22000, 0.0, 22000.0)));
        
        double lowerE, higherE;
        lowerE = initialParticleKineticEnergy[i]-0.003;
        higherE = initialParticleKineticEnergy[i]+0.003;
        
        int lowerEBin, higherEBin;
        lowerEBin = (int) 2*1000*lowerE;
        higherEBin = (int) 2*1000*higherE;
        
        //--------------------------------
        //sprintf(command,"CLOVER_Energy>>%s", name);
        //sprintf(condition,"(%f)<InitialParticleKineticEnergy && InitialParticleKineticEnergy<(%f)", lowerE, higherE);
        
        //--------------------------------
        sprintf(command,"CLOVER_EnergyPerCrystal>>%s", name);
        std::cout << command << std::endl;
        //sprintf(condition,"(%f)<InitialParticleKineticEnergy && InitialParticleKineticEnergy<(%f) && ((CLOVER_NCrystalsTriggered[0]==1) || (CLOVER_NCrystalsTriggered[0]==2 && CLOVER_CrystalReflectionIndex[0]==-1))", lowerE, higherE);
        sprintf(condition,"(%f)<InitialParticleKineticEnergy && InitialParticleKineticEnergy<(%f)", lowerE, higherE);
        
        //--------------------------------
        
        DataTreeChain->Draw(command, condition, "");
        
        std::cout << "condition: " << condition << std::endl;
        std::cout << "lowerEBin: " << lowerEBin << std::endl;
        std::cout << "higherEBin: " << higherEBin << std::endl;

        
        integrals.push_back(hE_noAddback->Integral(lowerEBin, higherEBin));
        std::cout << "integrals: " << integrals.back() << std::endl;
        efficiencies.push_back(100.0*integrals.back()/nParticlesPerEnergy);
        std::cout << "efficiencies: " << efficiencies.back() << std::endl;
        efficiencyErrors.push_back(100.0*sqrt(integrals.back())/nParticlesPerEnergy);
    
        

        //------------------------------------------------
     //   hEnergy_noAddback_energy->GetXaxis()->SetRangeUser(0.0, (1.1)*1000.0*initialParticleKineticEnergy[i]);

        std::cout << "Energy [MeV]: " << initialParticleKineticEnergy[i] << ", Efficiency [%]: " << efficiencies.back() << " (" << efficiencyErrors.back() << ")" << std::endl;
        outputFile << initialParticleKineticEnergy[i] << " " << efficiencies.back() << " " << efficiencyErrors.back() << std::endl;
        
    }
    
    outputFile.close();
    cout << "File Efficiency noAddback Created!\n";
    
    std::cout << std::endl;

    ////================================================////
   //Luna std::vector<std::shared_ptr<TH1F>> hEnergy_energy;
    
    ofstream outputFile2;
    outputFile2.open("PR251-Efficiency-Addback.dat");


    std::cout << "Add-back, No Compton Suppression" << std::endl;

    integrals.clear();
    efficiencies.clear();
    efficiencyErrors.clear();

    for(int i=0; i<(int) initialParticleKineticEnergy.size(); i++)
    {
        sprintf(name,"hEnergy_Addback_energy%d_%dkeV", i, 1000.0*initialParticleKineticEnergy[i]);
        TH1F *hE_Addback = new TH1F(name,"Addback",2*22000, 0.0, 22000.0); //Luna
        // Luna hEnergy_energy.push_back(std::shared_ptr<TH1F>(new TH1F(name, "", 2*22000, 0.0, 22000.0)));
        
        double lowerE, higherE;
        lowerE = initialParticleKineticEnergy[i]-0.003;
        higherE = initialParticleKineticEnergy[i]+0.003;
        
        int lowerEBin, higherEBin;
        lowerEBin = (int) 2*1000*lowerE;
        higherEBin = (int) 2*1000*higherE;
        
        //--------------------------------
        //sprintf(command,"CLOVER_Energy>>%s", name);
        //sprintf(condition,"(%f)<InitialParticleKineticEnergy && InitialParticleKineticEnergy<(%f)", lowerE, higherE);
        
        //--------------------------------
        sprintf(command,"CLOVER_Energy[0]>>%s", name);
        sprintf(condition,"(%f)<InitialParticleKineticEnergy && InitialParticleKineticEnergy<(%f) && ((CLOVER_NCrystalsTriggered[0]==1) || (CLOVER_NCrystalsTriggered[0]==2 && CLOVER_CrystalReflectionIndex[0]==-1))", lowerE, higherE);
        //sprintf(condition,"(%f)<InitialParticleKineticEnergy && InitialParticleKineticEnergy<(%f) && ((CLOVER_NCrystalsTriggered[0]==1) || (CLOVER_NCrystalsTriggered[0]==2 && CLOVER_CrystalReflectionIndex[0]==-1) && CLOVER_BGOCrystalsTriggered[0]==0)", lowerE, higherE);
        
        //--------------------------------

        DataTreeChain->Draw(command, condition, "");
        std::cout << "condition: " << condition << std::endl;
        std::cout << "lowerEBin: " << lowerEBin << std::endl;
        std::cout << "higherEBin: " << higherEBin << std::endl;

        //Luna integrals.push_back(hEnergy_energy.back()->Integral(lowerEBin, higherEBin));
        integrals.push_back(hE_Addback->Integral(lowerEBin, higherEBin)); //Luna
        std::cout << "integrals: " << integrals.back() << std::endl;
        efficiencies.push_back(100.0*integrals.back()/nParticlesPerEnergy);
        std::cout << "efficiencies: " << efficiencies.back() << std::endl;
        efficiencyErrors.push_back(100.0*sqrt(integrals.back())/nParticlesPerEnergy);
        
        //------------------------------------------------
        //hEnergy_energy.back()->GetXaxis()->SetRangeUser(0.0, (1.1)*1000.0*initialParticleKineticEnergy[i]);
        
        std::cout << "Energy [MeV]: " << initialParticleKineticEnergy[i] << ", Efficiency [%]: " << efficiencies.back() << " (" << efficiencyErrors.back() << ")" << std::endl;
        outputFile2 << initialParticleKineticEnergy[i] << " " << efficiencies.back() << " " << efficiencyErrors.back() << std::endl;

        
    }
    std::cout << std::endl;
    outputFile.close();
    cout << "File Efficiency noAddback Created!\n";

    
    
/*
    ////================================================////
    std::vector<std::shared_ptr<TH1F>> hEnergy_ComptonSuppressed_energy;

    std::cout << "Add-back, Compton Suppression" << std::endl;

    integrals.clear();
    efficiencies.clear();
    efficiencyErrors.clear();
    
    for(int i=0; i<(int) initialParticleKineticEnergy.size(); i++)
    {
        sprintf(name,"hEnergy_ComptonSuppressed_energy%d_%fkeV", i, 1000.0*initialParticleKineticEnergy[i]);
        hEnergy_ComptonSuppressed_energy.push_back(std::shared_ptr<TH1F>(new TH1F(name, "", 2*22000, 0.0, 22000.0)));
        
        double lowerE, higherE;
        lowerE = initialParticleKineticEnergy[i]-0.003;
        higherE = initialParticleKineticEnergy[i]+0.003;
        
        int lowerEBin, higherEBin;
        lowerEBin = (int) 2*1000*lowerE;
        higherEBin = (int) 2*1000*higherE;
        
        //--------------------------------
        //sprintf(command,"CLOVER_Energy>>%s", name);
        //sprintf(condition,"(%f)<InitialParticleKineticEnergy && InitialParticleKineticEnergy<(%f)", lowerE, higherE);
        
        //--------------------------------
        sprintf(command,"CLOVER_Energy[0]>>%s", name);
        //sprintf(condition,"(%f)<InitialParticleKineticEnergy && InitialParticleKineticEnergy<(%f) && ((CLOVER_NCrystalsTriggered[0]==1) || (CLOVER_NCrystalsTriggered[0]==2 && CLOVER_CrystalReflectionIndex[0]==-1))", lowerE, higherE);
        sprintf(condition,"(%f)<InitialParticleKineticEnergy && InitialParticleKineticEnergy<(%f) && ((CLOVER_NCrystalsTriggered[0]==1) || (CLOVER_NCrystalsTriggered[0]==2 && CLOVER_CrystalReflectionIndex[0]==-1) && CLOVER_BGOCrystalsTriggered[0]==0)", lowerE, higherE);
        
        //--------------------------------
        
        DataTreeChain->Draw(command, condition, "");
        //std::cout << "condition: " << condition << std::endl;
        //std::cout << "lowerEBin: " << lowerEBin << std::endl;
        //std::cout << "higherEBin: " << higherEBin << std::endl;
        
        integrals.push_back(hEnergy_ComptonSuppressed_energy.back()->Integral(lowerEBin, higherEBin));
        std::cout << "integrals: " << integrals.back() << std::endl;
        efficiencies.push_back(100.0*integrals.back()/nParticlesPerEnergy);
        efficiencyErrors.push_back(100.0*sqrt(integrals.back())/nParticlesPerEnergy);
        
        //------------------------------------------------
        hEnergy_ComptonSuppressed_energy.back()->GetXaxis()->SetRangeUser(0.0, (1.1)*1000.0*initialParticleKineticEnergy[i]);

        std::cout << "Energy [MeV]: " << initialParticleKineticEnergy[i] << ", Efficiency [%]: " << efficiencies.back() << " (" << efficiencyErrors.back() << ")" << std::endl;
    }
    

    std::cout << std::endl;
*/
    
    f.Write();


    c1->Close();
    
    return 0;
    
}
