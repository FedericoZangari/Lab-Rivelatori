void fitLin3(){
    string title = "lin_preamp";
    string title1 = title + ".dat";
    ifstream f;
    f.open(title1.c_str(),ios::in);
    Double_t x, y, sigma_x, sigma_y;

    TGraphErrors *f1= new TGraphErrors();
    TGraphErrors *f2= new TGraphErrors();
    int i= 0;
    for (;;){
        f >> x >> y >> sigma_x >> sigma_y;
        f1->SetPoint(i, x, y);
        f1->SetPointError(i, sigma_x, sigma_y);
        i++;
        
        if(f.eof()){
			cout << "End of file reached "<< endl;
			break;
		}		
	}
    //double m = 0.008226;
    //double q = 0.00655;
    //double sigma_m = 0.00002141;
    //double sigma_q = 0.007971;
    double m = 0.00815;
    double q = 0.08;
    double sigma_m = 0.00005;
    double sigma_q = 0.05;
    double v_riv;
    double sigma_v_riv;
    f.close();
    title1 = title + "2.dat";
    f.open(title1.c_str(),ios::in);
    int j =0;
    for(;;){
        f >> x >> y >> sigma_y;
        v_riv=x*m+q;
        sigma_v_riv = sqrt(sigma_m*sigma_m*x*x+ sigma_q*sigma_q);
        cout << v_riv << "\t +- \t" << sigma_v_riv << endl;
        f1->SetPoint(i, v_riv, y);
        f1->SetPointError(i, sigma_v_riv, sigma_y);
        f2->SetPoint(j, v_riv, y);
        f2->SetPointError(j, sigma_v_riv, sigma_y);
        i++; j++;
        if(f.eof()){
			cout << "End of file reached "<< endl;
			break;
		}	
    }
    
    TCanvas *c1 =new TCanvas("c1","c1");
    f1->Draw("APL");
    f1->SetMarkerStyle(8);
	f1->SetMarkerSize(1);
    f1->SetMarkerColor(kSpring);
    f1->SetTitle("Linearita' rivelatore + preamplificatore");
    f1->GetXaxis()->SetTitle("V_{riv} [mV]");
    f1->GetYaxis()->SetTitle("V_{out} [mV]");
    //f1->GetYaxis()->SetRangeUser(0,18);
    //f1->SetLineColor(kRed+2);
    
    f2->SetMarkerColor(kBlue);
    f2->Draw("*same");
    //f2->Fit("pol1");

    TF1* t = new TF1("line","[0]+[1]*x", 0, 2050);
    f1->Fit(t, "L", "" , 0,2050);
    t->Draw("same");

    TLegend *leg = new TLegend(0.15, 0.7, 0.45, 0.85);
    leg->AddEntry(f1, "Data points", "lp");
    leg->AddEntry(f2, "Extrapolation of V_{riv}", "lp");
    leg->AddEntry(t, "Linear  fit", "l");
    leg->SetTextSize(0.04);
    leg->SetTextFont(42);
    leg->SetBorderSize(0);
    leg->SetFillColor(0);
    leg->Draw();
    gStyle->SetOptFit(1111);
    TPaveStats *st = (TPaveStats*)f1->FindObject("stats");
    st->SetY1NDC(0.2); //new x start position
    st->SetY2NDC(0.4); //new x end position
    
    title = title +"2_noSpice.png";
    c1->SaveAs(title.c_str());

}