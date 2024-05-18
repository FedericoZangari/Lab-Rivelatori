void fitLin(){
    //string title = "lin_scatoletta";
    //string title = "lin_preamp_new";
    //string title = "lin_shaper0_new";
    string title = "lin_shaper500";
    //string title = "lin_triangolo";
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
        f >> x >> y >> sigma_y;
        f1->SetPoint(i, x, y);

        if(y < 16) {sigma_y_tot = sqrt(sigma_y*sigma_y + 16.*16./256./256.);
        o << x << "\t" << x*0.01 << "\t" << y << "\t" << sigma_y << "\t" << 16./256. << "\t" << sigma_y_tot << endl;
        }
        if(y > 16) {sigma_y_tot = sqrt(sigma_y*sigma_y + 1.1*y*1.1*y/256./256.);
        o << x << "\t" << x*0.01 << "\t" << y << "\t" << sigma_y << "\t" << 1.1*y/256. << "\t" << sigma_y_tot << endl;
        }
        f1->SetPointError(i, x*0.01, sigma_y_tot);
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
    f1->SetTitle("Linearita' rivelatore + preamplificatore");
    
    f1->SetTitle("Linearita' rivelatore con impulso triangolare");
    //f1->SetTitle("Linearita' catena #tau = 0 ns");
    f1->GetXaxis()->SetTitle("V_{out riv} [mV]");
    f1->GetXaxis()->SetTitle("V_{in} [mV]");
    f1->GetYaxis()->SetTitle("V_{out riv} [mV]");
    //f1->GetYaxis()->SetTitle("V_{out shaper} [mV]");
    //f1->SetLineColor(kRed+2);

    TF1* t = new TF1("line","[0]+[1]*x", 400, 4500);
    f1->Fit(t, "L", "" , 400, 4500);
    t->Draw("same");

    TLegend *leg = new TLegend(0.15, 0.7, 0.45, 0.85);
    leg->AddEntry(f1, "Data points", "lp");
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
    //c1->SaveAs(title.c_str());

}