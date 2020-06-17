#include <iostream>
#include <fstream>
#include <string> 
#include <TH2D.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TGraph2D.h>
#include <TStyle.h>
#include <RooNDKeysPdf.h>

int main()
{
    Int_t nSamples = 131;
    std::ifstream datafile ("data.txt");
    TCanvas *c = new TCanvas;

    std::string x, y, xsec, s95exp, s95obs;
    Double_t xs[nSamples], ys[nSamples], sigs[nSamples];

    // remove first line of junk
    datafile >> y >> x >> xsec >> s95exp >> s95obs;

    TH2D *h = new TH2D("","",nSamples,0,4000,nSamples,0,2000);
    int i;
    while(datafile >> y >> x >> xsec >> s95exp >> s95obs){
        xs[i] = std::stod(x);
        ys[i] = std::stod(y);
        sigs[i] = std::log(std::stod(s95exp) / std::stod(xsec));

        //std::cout << xs[i] << " " << ys[i] << " " << sigs[i] << '\n';

        //h->Fill(std::stod(x), std::stod(y));
        h->Fill(std::stod(x), std::stod(y), sigs[i]);
        i++;
    }
    //gStyle->SetPalette(54);

    TGraph2D *gr = new TGraph2D(nSamples, xs, ys, sigs);

    gr->Draw("CONTZ");
    gr->GetHistogram()->SetContour(104);
    gr->GetHistogram()->Smooth(1);

    //h->Smooth();
    //h->Draw("CONT3Z");

    c->Update();
    c->Print("plot.png");

    return 0; 
}
