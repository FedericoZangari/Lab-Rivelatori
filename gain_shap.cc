void gain_shap(){
    
    string title = "gain_shap";
    string title1 = title + ".dat";
    ifstream f;
    f.open(title1.c_str(),ios::in);
    title1 = title + "_out.dat";
    ofstream o;
    o.open(title1.c_str(),ios::out);
    Double_t x, y, sigma_y;
    TGraphErrors *f1= new TGraphErrors();

    double R = 0.00825;
    double s_R=0.00004;
    double P = 58.06;
    double s_P=0.37;

    int i= 0;
    for (;;){
        f >> x >> y  >> sigma_y;
        f1->SetPoint(i, x, 10.*y/R/P);
        sigma_y = sqrt(pow(10.*sigma_y/R/P,2) + pow(10.*y*s_R/R/R/P, 2) + pow(10.*y*s_P/P/P/R, 2));
        f1->SetPointError(i, 0, sigma_y);
        o << x << "\t" << 10.*y/R/P << "\t" << sigma_y << endl;
        cout << x << "\t" << 10.*y/R/P << "\t" << sigma_y << endl;
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
    f1->SetMarkerColor(kRed+3);
    f1->SetTitle("Guadagno shaper in funzione di #tau");
    f1->GetXaxis()->SetTitle("Shaping time [ns]");
	f1->GetYaxis()->SetTitle("Gain");
    f1->GetXaxis()->SetRangeUser(-15,520);
    //f1->SetLineColor(kOrange);

    
    //c1->GetYaxis()->SetRangeUser(0,10);

    title = title+".png";
    c->SaveAs(title.c_str());
    f.close();
    o.close();
}