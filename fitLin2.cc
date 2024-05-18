void fitLin2(){
    string title = "lin_scatoletta_spice";
    string title1 = title + ".dat";
    ifstream f;
    f.open(title1.c_str(),ios::in);
    Double_t x, y, sigma_y;
    TGraphErrors *f1= new TGraphErrors();
    TGraphErrors *f2= new TGraphErrors();
    int i= 0;
    for (;;){
        f >> x >> y >> sigma_y;
        f1->SetPoint(i, x, y);
        if(i < 4){f2->SetPoint(i, x, y);
            f2->SetPointError(i, 0.01, sigma_y);
            f1->SetPointError(i, 0.01, sigma_y);}
        else{
            if(y < 16) sigma_y = sqrt(sigma_y*sigma_y + 16.*16./256./256.);
            if(y > 16) sigma_y = sqrt(sigma_y*sigma_y + 1.1*y*1.1*y/256./256.);
            f1->SetPointError(i, x*0.01, sigma_y);
        }
        
        i++;
        
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
    f1->SetTitle("Linearita' rivelatore");
    f1->GetXaxis()->SetTitle("V_{in} [mV]");
    f1->GetYaxis()->SetTitle("V_{out} [mV]");
    f1->GetYaxis()->SetRangeUser(0,18);
    //f1->SetLineColor(kRed+2);
    
    f2->SetMarkerColor(kBlue);
    f2->Draw("*same");
    //f2->Fit("pol1");

    TF1* t = new TF1("line","[0]+[1]*x", 0, 2050);
    f1->Fit(t, "L", "" , 0,2050);
    t->Draw("same");

    TLegend *leg = new TLegend(0.15, 0.7, 0.45, 0.85);
    leg->AddEntry(f1, "Data points", "lp");
    leg->AddEntry(f2, "LTspice simulation", "lp");
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
    
    title = title +".png";
    c1->SaveAs(title.c_str());

}