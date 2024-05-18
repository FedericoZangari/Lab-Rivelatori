void ampl_tau(){
    
    string title = "ampl_tau";
    string title1 = title + ".dat";
    ifstream f;
    f.open(title1.c_str(),ios::in);
    title1 = title + "_out.dat";
    ofstream o;
    o.open(title1.c_str(),ios::out);
    Double_t x, y, sigma_y, sigma_y_tot;
    TGraphErrors *f1= new TGraphErrors();

    int i= 0;
    for (;;){
        f >> x >> y  >> sigma_y;
        f1->SetPoint(i, x, y);
        sigma_y_tot = sqrt(sigma_y*sigma_y + 1.1*y*1.1*y/256./256.);
        f1->SetPointError(i, 0, sigma_y_tot);
        o << x << "\t" << y << "\t" << sigma_y << "\t" << 1.1*y/256. << "\t" << sigma_y_tot << endl;
        i++;
        
        if(f.eof()){
			cout << "End of file reached "<< endl;
			break;
		}		
	}   
        
    TCanvas *c =new TCanvas("c1","c1");
    f1->Draw("APL");
    f1->SetMarkerStyle(43);
	f1->SetMarkerSize(1.5);
    f1->SetMarkerColor(kMagenta+2);
    f1->SetTitle("Ampiezza in funzione di #tau");
    f1->GetXaxis()->SetTitle("Shaping time [ns]");
	f1->GetYaxis()->SetTitle("Peak amplitude [mV]");
    f1->GetXaxis()->SetRangeUser(-10,1050);
    //f1->SetLineColor(kOrange);
    TLegend *leg = new TLegend(0.7, 0.15, 0.85, 0.45);
    leg->AddEntry((TObject*)0, "V_{in} = 300mV", "");
    leg->SetTextSize(0.04);
    leg->SetTextFont(42);
    leg->SetBorderSize(0.1);
    leg->SetFillColor(0);
    leg->Draw();

    
    //c1->GetYaxis()->SetRangeUser(0,10);


    c->SaveAs("ampl_tau.png");
}