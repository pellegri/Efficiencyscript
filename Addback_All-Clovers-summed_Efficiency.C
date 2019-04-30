{
//========= Macro generated from object: Graph/Absolute Efficiency of all Clovers - Addback
//========= by ROOT version5.34/36
   
   TGraphErrors *gre = new TGraphErrors(12);
   gre->SetName("Graph");
   gre->SetTitle("Absolute Efficiency of all Clovers - Addback");
   gre->SetFillColor(1);
   gre->SetMarkerColor(4);
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
}
