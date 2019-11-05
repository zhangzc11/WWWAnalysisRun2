
#python skim.py ../data/All/lostlep_prompt.root ../data/All/lostlep_prompt_SS2JPreSel.root  "SRSSeePreSel || SRSSemPreSel || SRSSmmPreSel"
#python skim.py ../data/All/photon_fakes.root ../data/All/photon_fakes_SS2JPreSel.root  "SRSSeePreSel || SRSSemPreSel || SRSSmmPreSel"
#python skim.py ../data/All/lostlep_prompt.root ../data/All/lostlep_prompt_SS1JPreSel.root  "SRSS1Jee1JPre || SRSS1Jem1JPre || SRSS1Jmm1JPre"
#python skim.py ../data/All/photon_fakes.root ../data/All/photon_fakes_SS1JPreSel.root  "SRSS1Jee1JPre || SRSS1Jem1JPre || SRSS1Jmm1JPre"

#python skim.py ../data/All/lostlep_prompt.root ../data/All/lostlep_prompt_SS.root  "SRSSee || SRSSem || SRSSmm"
#python skim.py ../data/All/photon_fakes.root ../data/All/photon_fakes_SS.root  "SRSSee || SRSSem || SRSSmm"

python skim.py ../data/All/signal.root ../data/All/signal_SS2J.root  "(SRSSee || SRSSem || SRSSmm) && nj30 >= 2"
python skim.py ../data/All/lostlep_prompt.root ../data/All/lostlep_prompt_SS2J.root  "(SRSSee || SRSSem || SRSSmm) && nj30 >= 2"
python skim.py ../data/All/photon_fakes.root ../data/All/photon_fakes_SS2J.root  "(SRSSee || SRSSem || SRSSmm) && nj30 >= 2"

python skim.py ../data/All/signal.root ../data/All/signal_SS1J.root  "(SRSSee || SRSSem || SRSSmm) && nj30 == 1"
python skim.py ../data/All/lostlep_prompt.root ../data/All/lostlep_prompt_SS1J.root  "(SRSSee || SRSSem || SRSSmm) && nj30 == 1"
python skim.py ../data/All/photon_fakes.root ../data/All/photon_fakes_SS1J.root  "(SRSSee || SRSSem || SRSSmm) && nj30 == 1"

python skim.py ../data/All/signal.root ../data/All/signal_SS1J.root  "(passSSee || passSSem || passSSmm ) && CutSRDilep && MllSS > 20 && nj30 == 1"
python skim.py ../data/All/lostlep_prompt.root ../data/All/lostlep_prompt_SS1J.root "(passSSee || passSSem || passSSmm ) && CutSRDilep && MllSS > 20 && nj30 == 1"
python skim.py ../data/All/photon_fakes.root ../data/All/photon_fakes_SS1J.root  "(passSSee || passSSem || passSSmm ) && CutSRDilep && MllSS > 20 && nj30 == 1"

python skim.py ../data/All/signal.root ../data/All/signal_SFOS.root  "(SR0SFOS&& lep1Pt > 25 && lep2Pt > 25 && lep3Pt > 25) || SR1SFOS || SR2SFOS"
python skim.py ../data/All/lostlep_prompt.root ../data/All/lostlep_prompt_SFOS.root  "(SR0SFOS&& lep1Pt > 25 && lep2Pt > 25 && lep3Pt > 25) || SR1SFOS || SR2SFOS"
python skim.py ../data/All/photon_fakes.root ../data/All/photon_fakes_SFOS.root  "(SR0SFOS&& lep1Pt > 25 && lep2Pt > 25 && lep3Pt > 25) || SR1SFOS || SR2SFOS"

python skim.py ../data/All/signal.root ../data/All/signal_SFOS_cutMll3L.root  "(SR0SFOS && lep1Pt > 25 && lep2Pt > 25 && lep3Pt > 25) || (SR1SFOS && abs(Mll3L - 91.1876) > 20.0 ) || ( SR2SFOS && abs(Mll3L - 91.1876) > 20.0  && abs(Mll3L1 - 91.1876) > 20.0 )"
python skim.py ../data/All/lostlep_prompt.root ../data/All/lostlep_prompt_SFOS_cutMll3L.root  "(SR0SFOS&& lep1Pt > 25 && lep2Pt > 25 && lep3Pt > 25) || (SR1SFOS && abs(Mll3L - 91.1876) > 20.0 ) || ( SR2SFOS && abs(Mll3L - 91.1876) > 20.0 && abs(Mll3L1 - 91.1876) > 20.0 )"
python skim.py ../data/All/photon_fakes.root ../data/All/photon_fakes_SFOS_cutMll3L.root  "(SR0SFOS&& lep1Pt > 25 && lep2Pt > 25 && lep3Pt > 25) || (SR1SFOS && abs(Mll3L - 91.1876) > 20.0 ) || ( SR2SFOS && abs(Mll3L - 91.1876) > 20.0 && abs(Mll3L1 - 91.1876) > 20.0 )"

'''
python skim.py ../data/All/lostlep_prompt.root ../data/All/lostlep_prompt_SFOSPreSel.root  "SR0SFOSPreSel || SR1SFOSPreSel || SR2SFOSPreSel"
python skim.py ../data/All/photon_fakes.root ../data/All/photon_fakes_SFOSPreSel.root  "SR0SFOSPreSel || SR1SFOSPreSel || SR2SFOSPreSel"

python skim.py ../data/All/lostlep_prompt.root ../data/All/lostlep_prompt_0SFOS.root  "SR0SFOS"
python skim.py ../data/All/photon_fakes.root ../data/All/photon_fakes_0SFOS.root  "SR0SFOS"

python skim.py ../data/All/lostlep_prompt.root ../data/All/lostlep_prompt_0SFOSPreSel.root  "SR0SFOSPreSel"
python skim.py ../data/All/photon_fakes.root ../data/All/photon_fakes_0SFOSPreSel.root  "SR0SFOSPreSel"

python skim.py ../data/All/lostlep_prompt.root ../data/All/lostlep_prompt_12SFOS.root  "SR1SFOS || SR2SFOS"
python skim.py ../data/All/photon_fakes.root ../data/All/photon_fakes_12SFOS.root  "SR1SFOS || SR2SFOS"

python skim.py ../data/All/lostlep_prompt.root ../data/All/lostlep_prompt_12SFOSPreSel.root  "SR1SFOSPreSel || SR2SFOSPreSel"
python skim.py ../data/All/photon_fakes.root ../data/All/photon_fakes_12SFOSPreSel.root  "SR1SFOSPreSel || SR2SFOSPreSel"

'''
