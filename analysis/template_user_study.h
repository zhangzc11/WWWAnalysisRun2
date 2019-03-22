
    // NOTE:
    // Copy this code to "my_user_study.h" and re-compile

    //************************************************************************************************************************************************************************************************
    // USER DEFINED ADDITIONAL SELECTION REGIONS
    //************************************************************************************************************************************************************************************************

    // Call "getCut" to activate the cut "SRSSmmFull" which is full mm selection at Mjj-in (defined in main.cc)
    ana.cutflow.getCut("SRSSmmFull");
    // Now add a new cut "SRSSmmFullPP" with the cut definition defined in the lambda being passed on as second argument (third argument = weight to apply for this cut. and it's just "UNITY" which is returning float of 1)
    ana.cutflow.addCutToLastActiveCut("SRSSmmFullPP", [&]()
            {
                if (www.lep_pdgId()[0] < 0 and www.lep_pdgId()[1] < 0)
                    return true;
                else
                    return false;
            }, UNITY);

    // Call "getCut" to activate the cut "SRSSmmFull" which is full mm selection at Mjj-in
    ana.cutflow.getCut("SRSSmmFull");
    // Now add a new cut "SRSSmmFullMM" with the cut definition defined in the lambda being passed on as second argument (third argument = weight to apply for this cut. and it's just "UNITY" which is returning float of 1)
    ana.cutflow.addCutToLastActiveCut("SRSSmmFullMM", [&]()
            {
                if (www.lep_pdgId()[0] > 0 and www.lep_pdgId()[1] > 0)
                    return true;
                else
                    return false;
            }, UNITY);

    /// .... add extra selection regions....

    //************************************************************************************************************************************************************************************************
    // USER DEFINED ADDITIONAL HISTOGRAMS
    //************************************************************************************************************************************************************************************************

    // User defined variable
    // e.g. Mlljj variable
    // arguments: Name of the histogram, nbin, low bound, high bound, lambda that returns the value of the variable
    ana.histograms.addHistogram("Mlljj", 180, 0., 300.,
            [&]()
            {

                // "www" objects contain jets 4-vectors
                std::vector<LV> jets_p4 = www.jets_p4();

                // Loop over and for each opposite sign pair compute DR and choose the smallest
                float minDR = 999;
                LV W_jet_0;
                LV W_jet_1;
                for (unsigned int ii = 0; ii < jets_p4.size(); ++ii)
                {
                    for (unsigned int jj = ii + 1; jj < jets_p4.size(); ++jj)
                    {

                        if (jets_p4[ii].pt() > 30. and jets_p4[jj].pt() > 30. and fabs(jets_p4[ii].eta()) < 2.5 and fabs(jets_p4[jj].eta()) < 2.5) // If pt condition and eta condition met
                        {
                            float thisDR = RooUtil::Calc::DeltaR(jets_p4[ii], jets_p4[jj]);
                            if (thisDR < minDR)
                            {
                                minDR = thisDR;
                                W_jet_0 = jets_p4[ii];
                                W_jet_1 = jets_p4[jj];
                            }
                        }
                    }
                }

                float Mlljj = -999;

                // This means we found a pair of jets to tag as W
                if (minDR < 100)
                {
                    // "www" objects contain lepton 4-vectors
                    std::vector<LV> lep_p4 = www.lep_p4();

                    Mlljj = (lep_p4[0] + lep_p4[1] + W_jet_0 + W_jet_1).mass();

                }

                return Mlljj;
            });

