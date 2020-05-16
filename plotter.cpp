#include <iostream>
#include <fstream>
#include <string> 
#include <TH2D.h>
#include <TCanvas.h>
#include <TGraph.h>

int main()
{
    Int_t nSamples = 131;
    std::ifstream datafile ("data.txt");
    TH2D *h = new TH2D("h2","",nSamples,0,4000,nSamples,0,2000);
    TGraph *gr = new TGraph(nSamples);
    TCanvas *c = new TCanvas;

    std::string x, y, xsec, s95exp, s95obs;
    TArrayD xs(nSamples), ys(nSamples), sigs(nSamples);

    // remove first line of junk
    datafile >> y >> x >> xsec >> s95exp >> s95obs;

    int i;
    while(datafile >> y >> x >> xsec >> s95exp >> s95obs){
        xs[i] = std::stod(x);
        ys[i] = std::stod(y);
        sigs[i] = std::stod(s95exp) / std::stod(xsec);

        //std::cout << xs[i] << " " << ys[i] << " " << sigs[i] << '\n';

        //h->Fill(std::stod(x), std::stod(y));
        h->Fill(std::stod(x), std::stod(y), sigs[i]);
        i++;
    }

    h->Smooth();
    h->Draw("COLZ CONTZ");

    c->Update();
    c->Print("plot.png");

    return 0; 
}
