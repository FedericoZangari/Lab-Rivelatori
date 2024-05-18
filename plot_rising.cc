void plot_rising(){
    
    string title = "rising";
    string title1 = title + ".dat";
    ifstream f;
    f.open(title1.c_str(),ios::in);
    Double_t x, y, sigma_y;
    TGraphErrors *f1= new TGraphErrors();

    int i= 0;
    for (;;){
        f >> x >> y  >> sigma_y;
        f1->SetPoint(i, x, y);
        f1->SetPointError(i, 0, sigma_y);
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
    f1->SetMarkerColor(kBlue);
    f1->SetTitle("Rising time in funzione di #tau");
    f1->GetXaxis()->SetTitle("Shaping time [ns]");
	f1->GetYaxis()->SetTitle("Rising time [ns]");
    //f1->SetLineColor(kOrange);

    
    //c1->GetYaxis()->SetRangeUser(0,10);


    c->SaveAs("rising.png");
}