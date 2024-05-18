void FitPeak(){
    ifstream f;
    f.open("cluster.dat",ios::in);

    double x,y;
    vector<double> v, t;
    double t0;
    double delta_t = 1;
    for (;;){
        f >> x >> y;
        v.push_back(y);
        t.push_back(x);

        if(f.eof()){
			cout << "End of file reached "<< endl;
			break;
		}		
	}
    t0 = t[0];

    TH1F* h= new TH1F("h", "Ampiezza misurata con 5 campionamenti", 50, 0.3, 0.5);
    TH2F* h2= new TH2F("h", "Ampiezza misurata con 5 campionamenti", 60, -0.9, 0.7, 75, -75, 0);
    TRandom3 *ran = new TRandom3(1234);
    TCanvas* bro = new TCanvas("bro", "bro");
    for(int i =0; i< 5000; i++){
        //int index_start = ran->Uniform(25,100);
        int index_start = ran->Gaus(25,5);
        //cout << index_start << endl;
        TGraph* g = new TGraph();
        for(int j=0;j<5;j++){
            g->SetPoint(j, t0+ delta_t*(index_start + j*25), v[index_start + j*25]);
            //cout << j << "\t" << t0+ delta_t*(index_start + j*25) << "\t" << v[index_start + j*25] << endl;
        }
        TF1* f = new TF1("pol2","[0]+[1]*x+ [2]*x*x", -100, 400);
        g->Fit(f, "Q","", t0+ delta_t*(index_start + 10), t0+ delta_t*(index_start + 125));
        
        double t_max = -1.*f->GetParameter(1) /2. / f->GetParameter(2);
        double ampl = f->Eval(t_max) - v[index_start];
        //cout << ampl << endl;
        h->Fill(ampl);
        h2->Fill(ampl, t0+ delta_t*index_start);
        g->GetYaxis()->SetTitle("Segnale campionato [V]");
        g->GetXaxis()->SetTitle("Tempo [ns]");
        g->SetMarkerStyle(8);
        g->Draw("APL");
    }

    TCanvas* c = new TCanvas("c","c");
    h->GetXaxis()->SetTitle("Ampiezza del picco [V]");
    h->GetYaxis()->SetTitle("Counts");
    h->Draw();
    cout << h->Integral(43, 54) << endl;
    gStyle->SetOptStat(111111);
    //c->SaveAs("samp_Gaus_70_5.png");

    

    TCanvas* c3 = new TCanvas("c3","c3");
    h2->GetXaxis()->SetTitle("Ampiezza del picco [V]");
    h2->GetYaxis()->SetTitle("Tempo di inizio del campionamento t_{0} [ns]");
    h2->GetZaxis()->SetTitle("Counts");
    h2->Draw("");
    //c3->SaveAs("samp3_Gaus_70_5.png");


    TCanvas* c2 = new TCanvas("c2","c2");
    h2->GetXaxis()->SetTitle("Ampiezza del picco [V]");
    h2->GetXaxis()->SetTitleOffset(2);
    h2->GetYaxis()->SetTitle("t_{0} [ns]");
    h2->GetYaxis()->SetTitleOffset(2);
    h2->GetZaxis()->SetTitle("Counts");
    h2->Draw("LEGO");
    gStyle->SetOptStat(0000);
    //c2->SaveAs("samp2_Unif_25_100.png");
}