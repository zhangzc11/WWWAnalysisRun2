

    //************************************************************************************************************************************************************************************************
    //
    //
    //
    // USER DEFINED ADDITIONAL REGIONS
    //
    //
    //
    //************************************************************************************************************************************************************************************************

    // In this user defined example, I add the two loose lepton regions
    // This is for studying isolation studies

    // Two Loose Dilep selection for studying isolation
    ana.cutflow.getCut("CutTrigger"); // Retrieve the CutTrigger and add CutLRDilep to the CutTrigger node
    ana.cutflow.addCutToLastActiveCut("CutLRDilep",
            // Cut definition
            [&]()
            {
                // The sub-leading can be lowered to 20 as our dilepton trigger thresholds are (23/12, 23/12,23/8, 17/8 for ee, me,em, mm)
                // Can't go lower than 20 due to pre-selection applied at baby making steps
                return (www.nVlep() == 2) * (www.nLlep() == 2) * (www.lep_pt()[0]>25.) * (www.lep_pt()[1]>20.);
            },
            // Weight definition (lepton scale factors)
            [&] ()
            {
                return 1;
            });

    // Trilep selection for signal region plots
    ana.cutflow.getCut("CutTrigger"); // Retrieve the CutTrigger and add CutLRTrilep to the CutTrigger node
    ana.cutflow.addCutToLastActiveCut("CutLRTrilep",
            // Cut definition
            [&]()
            {
                // The pt thresholds for tri-lepton is kept the same
                // Can't go lower than 20 due to pre-selection applied at baby making steps
                return (www.nVlep() == 3) * (www.nLlep() == 3) * (www.lep_pt()[0]>25.) * (www.lep_pt()[1]>20.) * (www.lep_pt()[2]>20.);
            },
            // Weight definition (lepton scale factors)
            [&] ()
            {
                // the 2017 and 2018 doesn't have lepton scale factors saved to the branches in the WWW ttree
                if (input.year == 2017 or input.year == 2018)
                    return leptonScaleFactors.getScaleFactors(true, ana.do_fake_estimation, input.is_data);
                else
                    return www.lepsf();
            });


    // Same-sign Mjj on-W region
    ana.cutflow.getCut("CutLRDilep");
    ana.cutflow.addCutToLastActiveCut("LRSSmm"                , [&]() { return (www.passSSmm())*(www.MllSS()>40.)               ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("LRSSmmTVeto"           , [&]() { return www.nisoTrack_mt2_cleaned_VVV_cutbased_veto()==0 ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("LRSSmmNj2"             , [&]() { return www.nj30()>= 2                                   ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("LRSSmmNb0"             , [&]() { return www.nb()==0                                      ; }        , [&]() { return www.weight_btagsf() ; } ); 
    ana.cutflow.addCutToLastActiveCut("LRSSmmMjjW"            , [&]() { return fabs(www.Mjj()-80.)<15.                          ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("LRSSmmMjjL"            , [&]() { return www.MjjL()<400.                                  ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("LRSSmmDetajjL"         , [&]() { return www.DetajjL()<1.5                                ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("LRSSmmMET"             , [&]() { return 1.                                               ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("LRSSmmMllSS"           , [&]() { return www.MllSS()>40.                                  ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("LRSSmmFull"            , [&]() { return 1                                                ; }        , UNITY                                  ); 
    ana.cutflow.getCut("CutLRDilep");
    ana.cutflow.addCutToLastActiveCut("LRSSem"                , [&]() { return (www.passSSem())*(www.MllSS()>30.)               ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("LRSSemTVeto"           , [&]() { return www.nisoTrack_mt2_cleaned_VVV_cutbased_veto()==0 ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("LRSSemNj2"             , [&]() { return www.nj30()>= 2                                   ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("LRSSemNb0"             , [&]() { return www.nb()==0                                      ; }        , [&]() { return www.weight_btagsf() ; } ); 
    ana.cutflow.addCutToLastActiveCut("LRSSemMjjW"            , [&]() { return fabs(www.Mjj()-80.)<15.                          ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("LRSSemMjjL"            , [&]() { return www.MjjL()<400.                                  ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("LRSSemDetajjL"         , [&]() { return www.DetajjL()<1.5                                ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("LRSSemMET"             , [&]() { return www.met_pt()>60.                                 ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("LRSSemMllSS"           , [&]() { return www.MllSS()>30.                                  ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("LRSSemMTmax"           , [&]() { return www.MTmax()>90.                                  ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("LRSSemFull"            , [&]() { return 1                                                ; }        , UNITY                                  ); 
    ana.cutflow.getCut("CutLRDilep");
    ana.cutflow.addCutToLastActiveCut("LRSSee"                , [&]() { return (www.passSSee())*(1)*(www.MllSS()>40.)           ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("LRSSeeZeeVt"           , [&]() { return fabs(www.MllSS()-91.1876)>10.                    ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("LRSSeeTVeto"           , [&]() { return www.nisoTrack_mt2_cleaned_VVV_cutbased_veto()==0 ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("LRSSeeNj2"             , [&]() { return www.nj30()>= 2                                   ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("LRSSeeNb0"             , [&]() { return www.nb()==0                                      ; }        , [&]() { return www.weight_btagsf() ; } ); 
    ana.cutflow.addCutToLastActiveCut("LRSSeeMjjW"            , [&]() { return fabs(www.Mjj()-80.)<15.                          ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("LRSSeeMjjL"            , [&]() { return www.MjjL()<400.                                  ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("LRSSeeDetajjL"         , [&]() { return www.DetajjL()<1.5                                ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("LRSSeeMET"             , [&]() { return www.met_pt()>60.                                 ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("LRSSeeMllSS"           , [&]() { return www.MllSS()>40.                                  ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("LRSSeeFull"            , [&]() { return 1                                                ; }        , UNITY                                  ); 

    // Same-sign Mjj off-W region
    ana.cutflow.getCut("CutLRDilep")                                                                                                              ;
    ana.cutflow.addCutToLastActiveCut("LRSSSidemm"            , [&]() { return (www.passSSmm())*(www.MllSS()>40.)                                 ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("LRSSSidemmTVeto"       , [&]() { return www.nisoTrack_mt2_cleaned_VVV_cutbased_veto()==0                   ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("LRSSSidemmNj2"         , [&]() { return www.nj30()>= 2                                                     ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("LRSSSidemmNb0"         , [&]() { return www.nb()==0                                                        ; }, [&]() { return www.weight_btagsf(); } );
    ana.cutflow.addCutToLastActiveCut("LRSSSidemmMjjW"        , [&]() { return fabs(www.Mjj()-80.)>=15.                                           ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("LRSSSidemmMjjL"        , [&]() { return www.MjjL()<400.                                                    ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("LRSSSidemmDetajjL"     , [&]() { return www.DetajjL()<1.5                                                  ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("LRSSSidemmMET"         , [&]() { return www.met_pt()>60.                                                   ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("LRSSSidemmMllSS"       , [&]() { return www.MllSS()>40.                                                    ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("LRSSSidemmFull"        , [&]() { return 1                                                                  ; }, UNITY                                 );
    ana.cutflow.getCut("CutLRDilep")                                                                                                              ;
    ana.cutflow.addCutToLastActiveCut("LRSSSideem"            , [&]() { return (www.passSSem())*(www.MllSS()>30.)                                 ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("LRSSSideemTVeto"       , [&]() { return www.nisoTrack_mt2_cleaned_VVV_cutbased_veto()==0                   ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("LRSSSideemNj2"         , [&]() { return www.nj30()>= 2                                                     ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("LRSSSideemNb0"         , [&]() { return www.nb()==0                                                        ; }, [&]() { return www.weight_btagsf(); } );
    ana.cutflow.addCutToLastActiveCut("LRSSSideemMjjW"        , [&]() { return fabs(www.Mjj()-80.)>=15.                                           ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("LRSSSideemMjjL"        , [&]() { return www.MjjL()<400.                                                    ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("LRSSSideemDetajjL"     , [&]() { return www.DetajjL()<1.5                                                  ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("LRSSSideemMET"         , [&]() { return www.met_pt()>60.                                                   ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("LRSSSideemMllSS"       , [&]() { return www.MllSS()>30.                                                    ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("LRSSSideemMTmax"       , [&]() { return www.MTmax()>90.                                                    ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("LRSSSideemFull"        , [&]() { return 1                                                                  ; }, UNITY                                 );
    ana.cutflow.getCut("CutLRDilep")                                                                                                              ;
    ana.cutflow.addCutToLastActiveCut("LRSSSideee"            , [&]() { return (www.passSSee())*(1)*(www.MllSS()>40.)                             ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("LRSSSideeeZeeVt"       , [&]() { return fabs(www.MllSS()-91.1876)>10.                                      ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("LRSSSideeeTVeto"       , [&]() { return www.nisoTrack_mt2_cleaned_VVV_cutbased_veto()==0                   ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("LRSSSideeeNj2"         , [&]() { return www.nj30()>= 2                                                     ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("LRSSSideeeNb0"         , [&]() { return www.nb()==0                                                        ; }, [&]() { return www.weight_btagsf(); } );
    ana.cutflow.addCutToLastActiveCut("LRSSSideeeMjjW"        , [&]() { return fabs(www.Mjj()-80.)>=15.                                           ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("LRSSSideeeMjjL"        , [&]() { return www.MjjL()<400.                                                    ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("LRSSSideeeDetajjL"     , [&]() { return www.DetajjL()<1.5                                                  ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("LRSSSideeeMET"         , [&]() { return www.met_pt()>60.                                                   ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("LRSSSideeeMllSS"       , [&]() { return www.MllSS()>40.                                                    ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("LRSSSideeeFull"        , [&]() { return 1                                                                  ; }, UNITY                                 );

    // Trilep regions
    ana.cutflow.getCut("CutLRTrilep");
    ana.cutflow.addCutToLastActiveCut("LR0SFOS"               , [&]() { return (www.nSFOS()==0)                                 ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("LR0SFOSNj1"            , [&]() { return www.nj()<=1                                      ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("LR0SFOSNb0"            , [&]() { return www.nb()==0                                      ; }        , [&]() { return www.weight_btagsf() ; } ); 
    ana.cutflow.addCutToLastActiveCut("LR0SFOSPt3l"           , [&]() { return 1.                                               ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("LR0SFOSDPhi3lMET"      , [&]() { return www.DPhi3lMET()>2.5                              ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("LR0SFOSMET"            , [&]() { return www.met_pt()>30.                                 ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("LR0SFOSMll"            , [&]() { return www.Mll3L() > 20.                                ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("LR0SFOSM3l"            , [&]() { return abs(www.M3l()-91.1876) > 10.                     ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("LR0SFOSZVt"            , [&]() { return abs(www.Mee3L()-91.1876) > 15.                   ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("LR0SFOSMTmax"          , [&]() { return www.MTmax3L()>90.                                ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("LR0SFOSFull"           , [&]() { return 1                                                ; }        , UNITY                                  ); 
    ana.cutflow.getCut("CutLRTrilep");
    ana.cutflow.addCutToLastActiveCut("LR1SFOS"               , [&]() { return (www.nSFOS()==1)                                 ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("LR1SFOSNj1"            , [&]() { return www.nj()<=1                                      ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("LR1SFOSNb0"            , [&]() { return www.nb()==0                                      ; }        , [&]() { return www.weight_btagsf() ; } ); 
    ana.cutflow.addCutToLastActiveCut("LR1SFOSPt3l"           , [&]() { return www.Pt3l()>60.                                   ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("LR1SFOSDPhi3lMET"      , [&]() { return www.DPhi3lMET()>2.5                              ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("LR1SFOSMET"            , [&]() { return www.met_pt()>40.                                 ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("LR1SFOSMll"            , [&]() { return www.Mll3L() > 20.                                ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("LR1SFOSM3l"            , [&]() { return abs(www.M3l()-91.1876) > 10.                     ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("LR1SFOSZVt"            , [&]() { return www.nSFOSinZ() == 0                              ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("LR1SFOSMT3rd"          , [&]() { return www.MT3rd()>90.                                  ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("LR1SFOSFull"           , [&]() { return 1                                                ; }        , UNITY                                  ); 
    ana.cutflow.getCut("CutLRTrilep");
    ana.cutflow.addCutToLastActiveCut("LR2SFOS"               , [&]() { return (www.nSFOS()==2)                                 ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("LR2SFOSNj1"            , [&]() { return www.nj()<=1                                      ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("LR2SFOSNb0"            , [&]() { return www.nb()==0                                      ; }        , [&]() { return www.weight_btagsf() ; } ); 
    ana.cutflow.addCutToLastActiveCut("LR2SFOSPt3l"           , [&]() { return www.Pt3l()>60.                                   ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("LR2SFOSDPhi3lMET"      , [&]() { return www.DPhi3lMET()>2.5                              ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("LR2SFOSMET"            , [&]() { return www.met_pt()>55.                                 ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("LR2SFOSMll"            , [&]() { return (www.Mll3L() > 20. && www.Mll3L1() > 20.)        ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("LR2SFOSM3l"            , [&]() { return abs(www.M3l()-91.1876) > 10.                     ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("LR2SFOSZVt"            , [&]() { return www.nSFOSinZ() == 0                              ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("LR2SFOSFull"           , [&]() { return 1                                                ; }        , UNITY                                  ); 



    //************************************************************************************************************************************************************************************************
    //
    //
    //
    // USER DEFINED ADDITIONAL HISTOGRAMS
    //
    //
    //
    //************************************************************************************************************************************************************************************************

    ana.histograms.addHistogram("lep_relIso03EAv2LepMaxSS" ,  180 , 0.0     , 0.2    , [&]() { return std::max(www.lep_relIso03EAv2Lep()[0], www.lep_relIso03EAv2Lep()[1]) ; });
    ana.histograms.addHistogram("el_relIso03EAv2Lep"       ,  180 , 0.0     , 0.2    , [&]() { return (abs(www.lep_pdgId()[0]) == 11) * (www.lep_relIso03EAv2Lep()[0]) + (abs(www.lep_pdgId()[1]) == 11) * (www.lep_relIso03EAv2Lep()[1]); });
    ana.histograms.addHistogram("mu_relIso03EAv2Lep"       ,  180 , 0.0     , 0.2    , [&]() { return (abs(www.lep_pdgId()[0]) == 13) * (www.lep_relIso03EAv2Lep()[0]) + (abs(www.lep_pdgId()[1]) == 13) * (www.lep_relIso03EAv2Lep()[1]); });

    // Different Mjj scheme (30/20 closest DR)
    ana.histograms.addHistogram("Mjj3020", 180, 0., 300.,
            [&]()
            {
                // To cache result the caching will be determined by run/lumi/evt of the event
                static float result;
                static int run;
                static int lumi;
                static unsigned long long evt;

                // Check if I can just use cached result
                if (www.run() == run and www.lumi() == lumi and www.evt() == evt)
                {
                    return result;
                }

                // "www" objects contain jets 4-vectors
                std::vector<LV> jets_p4 = www.jets_p4();

                // Loop over and for each opposite sign pair compute DR and choose the smallest
                float minDR = 999;
                float Mjj = -999;
                bool os_pair_found = false;
                for (unsigned int ii = 0; ii < jets_p4.size(); ++ii)
                {
                    for (unsigned int jj = ii + 1; jj < jets_p4.size(); ++jj)
                    {

                        if (jets_p4[ii].pt() > 30. and jets_p4[jj].pt() > 20.) // If pt condition met
                        {
                            os_pair_found = true;
                            float thisDR = RooUtil::Calc::DeltaR(jets_p4[ii], jets_p4[jj]);
                            if (thisDR < minDR)
                            {
                                minDR = thisDR;
                                Mjj = (jets_p4[ii] + jets_p4[jj]).mass();
                            }
                        }
                    }
                }

                if (not os_pair_found) // If same-sign event it will not find anything, then set to -999
                    Mjj = -999;

                // Cache result
                result = Mjj;
                run = www.run();
                lumi = www.lumi();
                evt = www.evt();

                return result;
            });

