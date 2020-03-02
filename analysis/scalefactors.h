#ifndef scalefactors_h
#define scalefactors_h

#include "wwwtree.h"
#include "rooutil/rooutil.h"
#include "InputConfig.h"
#include "ElectronScaleFactors.h"

#ifndef __CINT__
extern ElectronScaleFactors electronScaleFactors;
#endif

namespace Lambdas
{
    extern std::function<float()> PassTightIsolationAR;
}


//_______________________________________________________________________________________________________
class TriggerScaleFactors
{
    public:
	RooUtil::HistMap* histmap_eeeta00_TwoSS_2d_sf_ttbar_2016;
	RooUtil::HistMap* histmap_eeeta00_TwoSS_2d_sf_ttbar_2017;
	RooUtil::HistMap* histmap_eeeta00_TwoSS_2d_sf_ttbar_2018;
	RooUtil::HistMap* histmap_eeeta01_TwoSS_2d_sf_ttbar_2016;
	RooUtil::HistMap* histmap_eeeta01_TwoSS_2d_sf_ttbar_2017;
	RooUtil::HistMap* histmap_eeeta01_TwoSS_2d_sf_ttbar_2018;
	RooUtil::HistMap* histmap_eeeta10_TwoSS_2d_sf_ttbar_2016;
	RooUtil::HistMap* histmap_eeeta10_TwoSS_2d_sf_ttbar_2017;
	RooUtil::HistMap* histmap_eeeta10_TwoSS_2d_sf_ttbar_2018;
	RooUtil::HistMap* histmap_eeeta11_TwoSS_2d_sf_ttbar_2016;
	RooUtil::HistMap* histmap_eeeta11_TwoSS_2d_sf_ttbar_2017;
	RooUtil::HistMap* histmap_eeeta11_TwoSS_2d_sf_ttbar_2018;
	RooUtil::HistMap* histmap_emeta00_TwoSS_2d_sf_ttbar_2016;
	RooUtil::HistMap* histmap_emeta00_TwoSS_2d_sf_ttbar_2017;
	RooUtil::HistMap* histmap_emeta00_TwoSS_2d_sf_ttbar_2018;
	RooUtil::HistMap* histmap_emeta01_TwoSS_2d_sf_ttbar_2016;
	RooUtil::HistMap* histmap_emeta01_TwoSS_2d_sf_ttbar_2017;
	RooUtil::HistMap* histmap_emeta01_TwoSS_2d_sf_ttbar_2018;
	RooUtil::HistMap* histmap_emeta10_TwoSS_2d_sf_ttbar_2016;
	RooUtil::HistMap* histmap_emeta10_TwoSS_2d_sf_ttbar_2017;
	RooUtil::HistMap* histmap_emeta10_TwoSS_2d_sf_ttbar_2018;
	RooUtil::HistMap* histmap_emeta11_TwoSS_2d_sf_ttbar_2016;
	RooUtil::HistMap* histmap_emeta11_TwoSS_2d_sf_ttbar_2017;
	RooUtil::HistMap* histmap_emeta11_TwoSS_2d_sf_ttbar_2018;
	RooUtil::HistMap* histmap_mmeta00_TwoSS_2d_sf_ttbar_2016;
	RooUtil::HistMap* histmap_mmeta00_TwoSS_2d_sf_ttbar_2017;
	RooUtil::HistMap* histmap_mmeta00_TwoSS_2d_sf_ttbar_2018;
	RooUtil::HistMap* histmap_mmeta01_TwoSS_2d_sf_ttbar_2016;
	RooUtil::HistMap* histmap_mmeta01_TwoSS_2d_sf_ttbar_2017;
	RooUtil::HistMap* histmap_mmeta01_TwoSS_2d_sf_ttbar_2018;
	RooUtil::HistMap* histmap_mmeta10_TwoSS_2d_sf_ttbar_2016;
	RooUtil::HistMap* histmap_mmeta10_TwoSS_2d_sf_ttbar_2017;
	RooUtil::HistMap* histmap_mmeta10_TwoSS_2d_sf_ttbar_2018;
	RooUtil::HistMap* histmap_mmeta11_TwoSS_2d_sf_ttbar_2016;
	RooUtil::HistMap* histmap_mmeta11_TwoSS_2d_sf_ttbar_2017;
	RooUtil::HistMap* histmap_mmeta11_TwoSS_2d_sf_ttbar_2018;

	TriggerScaleFactors()
	{
            histmap_eeeta00_TwoSS_2d_sf_ttbar_2016  = new RooUtil::HistMap("/nfs-7/userdata/zhicaiz/scalefactors/trigger/eeeta00_TwoSS_2d_sf_ttbar_2016.root:numer_data");
            histmap_eeeta00_TwoSS_2d_sf_ttbar_2017  = new RooUtil::HistMap("/nfs-7/userdata/zhicaiz/scalefactors/trigger/eeeta00_TwoSS_2d_sf_ttbar_2017.root:numer_data");
            histmap_eeeta00_TwoSS_2d_sf_ttbar_2018  = new RooUtil::HistMap("/nfs-7/userdata/zhicaiz/scalefactors/trigger/eeeta00_TwoSS_2d_sf_ttbar_2018.root:numer_data");
            histmap_eeeta01_TwoSS_2d_sf_ttbar_2016  = new RooUtil::HistMap("/nfs-7/userdata/zhicaiz/scalefactors/trigger/eeeta01_TwoSS_2d_sf_ttbar_2016.root:numer_data");
            histmap_eeeta01_TwoSS_2d_sf_ttbar_2017  = new RooUtil::HistMap("/nfs-7/userdata/zhicaiz/scalefactors/trigger/eeeta01_TwoSS_2d_sf_ttbar_2017.root:numer_data");
            histmap_eeeta01_TwoSS_2d_sf_ttbar_2018  = new RooUtil::HistMap("/nfs-7/userdata/zhicaiz/scalefactors/trigger/eeeta01_TwoSS_2d_sf_ttbar_2018.root:numer_data");
            histmap_eeeta10_TwoSS_2d_sf_ttbar_2016  = new RooUtil::HistMap("/nfs-7/userdata/zhicaiz/scalefactors/trigger/eeeta10_TwoSS_2d_sf_ttbar_2016.root:numer_data");
            histmap_eeeta10_TwoSS_2d_sf_ttbar_2017  = new RooUtil::HistMap("/nfs-7/userdata/zhicaiz/scalefactors/trigger/eeeta10_TwoSS_2d_sf_ttbar_2017.root:numer_data");
            histmap_eeeta10_TwoSS_2d_sf_ttbar_2018  = new RooUtil::HistMap("/nfs-7/userdata/zhicaiz/scalefactors/trigger/eeeta10_TwoSS_2d_sf_ttbar_2018.root:numer_data");
            histmap_eeeta11_TwoSS_2d_sf_ttbar_2016  = new RooUtil::HistMap("/nfs-7/userdata/zhicaiz/scalefactors/trigger/eeeta11_TwoSS_2d_sf_ttbar_2016.root:numer_data");
            histmap_eeeta11_TwoSS_2d_sf_ttbar_2017  = new RooUtil::HistMap("/nfs-7/userdata/zhicaiz/scalefactors/trigger/eeeta11_TwoSS_2d_sf_ttbar_2017.root:numer_data");
            histmap_eeeta11_TwoSS_2d_sf_ttbar_2018  = new RooUtil::HistMap("/nfs-7/userdata/zhicaiz/scalefactors/trigger/eeeta11_TwoSS_2d_sf_ttbar_2018.root:numer_data");
            histmap_emeta00_TwoSS_2d_sf_ttbar_2016  = new RooUtil::HistMap("/nfs-7/userdata/zhicaiz/scalefactors/trigger/emeta00_TwoSS_2d_sf_ttbar_2016.root:numer_data");
            histmap_emeta00_TwoSS_2d_sf_ttbar_2017  = new RooUtil::HistMap("/nfs-7/userdata/zhicaiz/scalefactors/trigger/emeta00_TwoSS_2d_sf_ttbar_2017.root:numer_data");
            histmap_emeta00_TwoSS_2d_sf_ttbar_2018  = new RooUtil::HistMap("/nfs-7/userdata/zhicaiz/scalefactors/trigger/emeta00_TwoSS_2d_sf_ttbar_2018.root:numer_data");
            histmap_emeta01_TwoSS_2d_sf_ttbar_2016  = new RooUtil::HistMap("/nfs-7/userdata/zhicaiz/scalefactors/trigger/emeta01_TwoSS_2d_sf_ttbar_2016.root:numer_data");
            histmap_emeta01_TwoSS_2d_sf_ttbar_2017  = new RooUtil::HistMap("/nfs-7/userdata/zhicaiz/scalefactors/trigger/emeta01_TwoSS_2d_sf_ttbar_2017.root:numer_data");
            histmap_emeta01_TwoSS_2d_sf_ttbar_2018  = new RooUtil::HistMap("/nfs-7/userdata/zhicaiz/scalefactors/trigger/emeta01_TwoSS_2d_sf_ttbar_2018.root:numer_data");
            histmap_emeta10_TwoSS_2d_sf_ttbar_2016  = new RooUtil::HistMap("/nfs-7/userdata/zhicaiz/scalefactors/trigger/emeta10_TwoSS_2d_sf_ttbar_2016.root:numer_data");
            histmap_emeta10_TwoSS_2d_sf_ttbar_2017  = new RooUtil::HistMap("/nfs-7/userdata/zhicaiz/scalefactors/trigger/emeta10_TwoSS_2d_sf_ttbar_2017.root:numer_data");
            histmap_emeta10_TwoSS_2d_sf_ttbar_2018  = new RooUtil::HistMap("/nfs-7/userdata/zhicaiz/scalefactors/trigger/emeta10_TwoSS_2d_sf_ttbar_2018.root:numer_data");
            histmap_emeta11_TwoSS_2d_sf_ttbar_2016  = new RooUtil::HistMap("/nfs-7/userdata/zhicaiz/scalefactors/trigger/emeta11_TwoSS_2d_sf_ttbar_2016.root:numer_data");
            histmap_emeta11_TwoSS_2d_sf_ttbar_2017  = new RooUtil::HistMap("/nfs-7/userdata/zhicaiz/scalefactors/trigger/emeta11_TwoSS_2d_sf_ttbar_2017.root:numer_data");
            histmap_emeta11_TwoSS_2d_sf_ttbar_2018  = new RooUtil::HistMap("/nfs-7/userdata/zhicaiz/scalefactors/trigger/emeta11_TwoSS_2d_sf_ttbar_2018.root:numer_data");
            histmap_mmeta00_TwoSS_2d_sf_ttbar_2016  = new RooUtil::HistMap("/nfs-7/userdata/zhicaiz/scalefactors/trigger/mmeta00_TwoSS_2d_sf_ttbar_2016.root:numer_data");
            histmap_mmeta00_TwoSS_2d_sf_ttbar_2017  = new RooUtil::HistMap("/nfs-7/userdata/zhicaiz/scalefactors/trigger/mmeta00_TwoSS_2d_sf_ttbar_2017.root:numer_data");
            histmap_mmeta00_TwoSS_2d_sf_ttbar_2018  = new RooUtil::HistMap("/nfs-7/userdata/zhicaiz/scalefactors/trigger/mmeta00_TwoSS_2d_sf_ttbar_2018.root:numer_data");
            histmap_mmeta01_TwoSS_2d_sf_ttbar_2016  = new RooUtil::HistMap("/nfs-7/userdata/zhicaiz/scalefactors/trigger/mmeta01_TwoSS_2d_sf_ttbar_2016.root:numer_data");
            histmap_mmeta01_TwoSS_2d_sf_ttbar_2017  = new RooUtil::HistMap("/nfs-7/userdata/zhicaiz/scalefactors/trigger/mmeta01_TwoSS_2d_sf_ttbar_2017.root:numer_data");
            histmap_mmeta01_TwoSS_2d_sf_ttbar_2018  = new RooUtil::HistMap("/nfs-7/userdata/zhicaiz/scalefactors/trigger/mmeta01_TwoSS_2d_sf_ttbar_2018.root:numer_data");
            histmap_mmeta10_TwoSS_2d_sf_ttbar_2016  = new RooUtil::HistMap("/nfs-7/userdata/zhicaiz/scalefactors/trigger/mmeta10_TwoSS_2d_sf_ttbar_2016.root:numer_data");
            histmap_mmeta10_TwoSS_2d_sf_ttbar_2017  = new RooUtil::HistMap("/nfs-7/userdata/zhicaiz/scalefactors/trigger/mmeta10_TwoSS_2d_sf_ttbar_2017.root:numer_data");
            histmap_mmeta10_TwoSS_2d_sf_ttbar_2018  = new RooUtil::HistMap("/nfs-7/userdata/zhicaiz/scalefactors/trigger/mmeta10_TwoSS_2d_sf_ttbar_2018.root:numer_data");
            histmap_mmeta11_TwoSS_2d_sf_ttbar_2016  = new RooUtil::HistMap("/nfs-7/userdata/zhicaiz/scalefactors/trigger/mmeta11_TwoSS_2d_sf_ttbar_2016.root:numer_data");
            histmap_mmeta11_TwoSS_2d_sf_ttbar_2017  = new RooUtil::HistMap("/nfs-7/userdata/zhicaiz/scalefactors/trigger/mmeta11_TwoSS_2d_sf_ttbar_2017.root:numer_data");
            histmap_mmeta11_TwoSS_2d_sf_ttbar_2018  = new RooUtil::HistMap("/nfs-7/userdata/zhicaiz/scalefactors/trigger/mmeta11_TwoSS_2d_sf_ttbar_2018.root:numer_data");

	}

	~TriggerScaleFactors()
        {
	delete histmap_eeeta00_TwoSS_2d_sf_ttbar_2016;
	delete histmap_eeeta00_TwoSS_2d_sf_ttbar_2017;
	delete histmap_eeeta00_TwoSS_2d_sf_ttbar_2018;
	delete histmap_eeeta01_TwoSS_2d_sf_ttbar_2016;
	delete histmap_eeeta01_TwoSS_2d_sf_ttbar_2017;
	delete histmap_eeeta01_TwoSS_2d_sf_ttbar_2018;
	delete histmap_eeeta10_TwoSS_2d_sf_ttbar_2016;
	delete histmap_eeeta10_TwoSS_2d_sf_ttbar_2017;
	delete histmap_eeeta10_TwoSS_2d_sf_ttbar_2018;
	delete histmap_eeeta11_TwoSS_2d_sf_ttbar_2016;
	delete histmap_eeeta11_TwoSS_2d_sf_ttbar_2017;
	delete histmap_eeeta11_TwoSS_2d_sf_ttbar_2018;
	delete histmap_emeta00_TwoSS_2d_sf_ttbar_2016;
	delete histmap_emeta00_TwoSS_2d_sf_ttbar_2017;
	delete histmap_emeta00_TwoSS_2d_sf_ttbar_2018;
	delete histmap_emeta01_TwoSS_2d_sf_ttbar_2016;
	delete histmap_emeta01_TwoSS_2d_sf_ttbar_2017;
	delete histmap_emeta01_TwoSS_2d_sf_ttbar_2018;
	delete histmap_emeta10_TwoSS_2d_sf_ttbar_2016;
	delete histmap_emeta10_TwoSS_2d_sf_ttbar_2017;
	delete histmap_emeta10_TwoSS_2d_sf_ttbar_2018;
	delete histmap_emeta11_TwoSS_2d_sf_ttbar_2016;
	delete histmap_emeta11_TwoSS_2d_sf_ttbar_2017;
	delete histmap_emeta11_TwoSS_2d_sf_ttbar_2018;
	delete histmap_mmeta00_TwoSS_2d_sf_ttbar_2016;
	delete histmap_mmeta00_TwoSS_2d_sf_ttbar_2017;
	delete histmap_mmeta00_TwoSS_2d_sf_ttbar_2018;
	delete histmap_mmeta01_TwoSS_2d_sf_ttbar_2016;
	delete histmap_mmeta01_TwoSS_2d_sf_ttbar_2017;
	delete histmap_mmeta01_TwoSS_2d_sf_ttbar_2018;
	delete histmap_mmeta10_TwoSS_2d_sf_ttbar_2016;
	delete histmap_mmeta10_TwoSS_2d_sf_ttbar_2017;
	delete histmap_mmeta10_TwoSS_2d_sf_ttbar_2018;
	delete histmap_mmeta11_TwoSS_2d_sf_ttbar_2016;
	delete histmap_mmeta11_TwoSS_2d_sf_ttbar_2017;
	delete histmap_mmeta11_TwoSS_2d_sf_ttbar_2018;
	}
	
	float getScaleFactors(int year, bool doFakeEstimation, bool isData, int variation=0)
        {
		if(www.nVlep() == 3) return 1.0; // only apply sf for SS
		if(isData) return 1.0;
		int id_type = 0; // 0: ee; 1: em; 2: mm
		if(abs(www.lep_pdgId()[0]) * abs(www.lep_pdgId()[1]) == 121) id_type = 0;
		if(abs(www.lep_pdgId()[0]) * abs(www.lep_pdgId()[1]) == 143) id_type = 1;
		if(abs(www.lep_pdgId()[0]) * abs(www.lep_pdgId()[1]) == 169) id_type = 2;
		int idx1 = 0;
		int idx2 = 1;
		if((id_type == 1) && (abs(www.lep_pdgId()[0]) == 13)) 
		{
			idx1 = 1;
			idx2 = 0;
		}
		int idx_eta = 0;
		float lep_pt0 = www.lep_pt()[idx1];
		float lep_pt1 = www.lep_pt()[idx2];
		if(lep_pt0 <= 25.0) lep_pt0 = 25.1;
		if(lep_pt0 >= 2055.0) lep_pt0 = 204.9;
		if(lep_pt1 <= 25.0) lep_pt1 = 25.1;
		if(lep_pt1 >= 2055.0) lep_pt1 = 204.9;

		if(abs(www.lep_eta()[idx1]) < 1.2 && abs(www.lep_eta()[idx2]) < 1.2) idx_eta = 0;//00
		if(abs(www.lep_eta()[idx1]) < 1.2 && abs(www.lep_eta()[idx2]) >= 1.2) idx_eta = 1;//01
		if(abs(www.lep_eta()[idx1]) >= 1.2 && abs(www.lep_eta()[idx2]) < 1.2) idx_eta = 2;//10
		if(abs(www.lep_eta()[idx1]) >= 1.2 && abs(www.lep_eta()[idx2]) >= 1.2) idx_eta = 3;//11
	
		float sf_return = 1.0;	
		if(year == 2016)
		{
			if(variation > 0)
			{
				if(id_type == 0)
				{
					if(idx_eta == 0) sf_return = histmap_eeeta00_TwoSS_2d_sf_ttbar_2016 -> eval_up(lep_pt0, lep_pt1);
					else if(idx_eta == 1) sf_return = histmap_eeeta01_TwoSS_2d_sf_ttbar_2016 -> eval_up(lep_pt0, lep_pt1);
					else if(idx_eta == 2) sf_return = histmap_eeeta10_TwoSS_2d_sf_ttbar_2016 -> eval_up(lep_pt0, lep_pt1);
					else if(idx_eta == 3) sf_return = histmap_eeeta11_TwoSS_2d_sf_ttbar_2016 -> eval_up(lep_pt0, lep_pt1);
				}
				else if(id_type == 1)
				{
					if(idx_eta == 0) sf_return = histmap_emeta00_TwoSS_2d_sf_ttbar_2016 -> eval_up(lep_pt0, lep_pt1);
					else if(idx_eta == 1) sf_return = histmap_emeta01_TwoSS_2d_sf_ttbar_2016 -> eval_up(lep_pt0, lep_pt1);
					else if(idx_eta == 2) sf_return = histmap_emeta10_TwoSS_2d_sf_ttbar_2016 -> eval_up(lep_pt0, lep_pt1);
					else if(idx_eta == 3) sf_return = histmap_emeta11_TwoSS_2d_sf_ttbar_2016 -> eval_up(lep_pt0, lep_pt1);
				}
				else if(id_type == 2)
				{
					if(idx_eta == 0) sf_return = histmap_mmeta00_TwoSS_2d_sf_ttbar_2016 -> eval_up(lep_pt0, lep_pt1);
					else if(idx_eta == 1) sf_return = histmap_mmeta01_TwoSS_2d_sf_ttbar_2016 -> eval_up(lep_pt0, lep_pt1);
					else if(idx_eta == 2) sf_return = histmap_mmeta10_TwoSS_2d_sf_ttbar_2016 -> eval_up(lep_pt0, lep_pt1);
					else if(idx_eta == 3) sf_return = histmap_mmeta11_TwoSS_2d_sf_ttbar_2016 -> eval_up(lep_pt0, lep_pt1);
				}
			}

			else if(variation < 0)
			{
				if(id_type == 0)
				{
					if(idx_eta == 0) sf_return = histmap_eeeta00_TwoSS_2d_sf_ttbar_2016 -> eval_down(lep_pt0, lep_pt1);
					else if(idx_eta == 1) sf_return = histmap_eeeta01_TwoSS_2d_sf_ttbar_2016 -> eval_down(lep_pt0, lep_pt1);
					else if(idx_eta == 2) sf_return = histmap_eeeta10_TwoSS_2d_sf_ttbar_2016 -> eval_down(lep_pt0, lep_pt1);
					else if(idx_eta == 3) sf_return = histmap_eeeta11_TwoSS_2d_sf_ttbar_2016 -> eval_down(lep_pt0, lep_pt1);
				}
				else if(id_type == 1)
				{
					if(idx_eta == 0) sf_return = histmap_emeta00_TwoSS_2d_sf_ttbar_2016 -> eval_down(lep_pt0, lep_pt1);
					else if(idx_eta == 1) sf_return = histmap_emeta01_TwoSS_2d_sf_ttbar_2016 -> eval_down(lep_pt0, lep_pt1);
					else if(idx_eta == 2) sf_return = histmap_emeta10_TwoSS_2d_sf_ttbar_2016 -> eval_down(lep_pt0, lep_pt1);
					else if(idx_eta == 3) sf_return = histmap_emeta11_TwoSS_2d_sf_ttbar_2016 -> eval_down(lep_pt0, lep_pt1);
				}
				else if(id_type == 2)
				{
					if(idx_eta == 0) sf_return = histmap_mmeta00_TwoSS_2d_sf_ttbar_2016 -> eval_down(lep_pt0, lep_pt1);
					else if(idx_eta == 1) sf_return = histmap_mmeta01_TwoSS_2d_sf_ttbar_2016 -> eval_down(lep_pt0, lep_pt1);
					else if(idx_eta == 2) sf_return = histmap_mmeta10_TwoSS_2d_sf_ttbar_2016 -> eval_down(lep_pt0, lep_pt1);
					else if(idx_eta == 3) sf_return = histmap_mmeta11_TwoSS_2d_sf_ttbar_2016 -> eval_down(lep_pt0, lep_pt1);
				}
			}

			else if(variation == 0)
			{
				if(id_type == 0)
				{
					if(idx_eta == 0) sf_return = histmap_eeeta00_TwoSS_2d_sf_ttbar_2016 -> eval(lep_pt0, lep_pt1);
					else if(idx_eta == 1) sf_return = histmap_eeeta01_TwoSS_2d_sf_ttbar_2016 -> eval(lep_pt0, lep_pt1);
					else if(idx_eta == 2) sf_return = histmap_eeeta10_TwoSS_2d_sf_ttbar_2016 -> eval(lep_pt0, lep_pt1);
					else if(idx_eta == 3) sf_return = histmap_eeeta11_TwoSS_2d_sf_ttbar_2016 -> eval(lep_pt0, lep_pt1);
				}
				else if(id_type == 1)
				{
					if(idx_eta == 0) sf_return = histmap_emeta00_TwoSS_2d_sf_ttbar_2016 -> eval(lep_pt0, lep_pt1);
					else if(idx_eta == 1) sf_return = histmap_emeta01_TwoSS_2d_sf_ttbar_2016 -> eval(lep_pt0, lep_pt1);
					else if(idx_eta == 2) sf_return = histmap_emeta10_TwoSS_2d_sf_ttbar_2016 -> eval(lep_pt0, lep_pt1);
					else if(idx_eta == 3) sf_return = histmap_emeta11_TwoSS_2d_sf_ttbar_2016 -> eval(lep_pt0, lep_pt1);
				}
				else if(id_type == 2)
				{
					if(idx_eta == 0) sf_return = histmap_mmeta00_TwoSS_2d_sf_ttbar_2016 -> eval(lep_pt0, lep_pt1);
					else if(idx_eta == 1) sf_return = histmap_mmeta01_TwoSS_2d_sf_ttbar_2016 -> eval(lep_pt0, lep_pt1);
					else if(idx_eta == 2) sf_return = histmap_mmeta10_TwoSS_2d_sf_ttbar_2016 -> eval(lep_pt0, lep_pt1);
					else if(idx_eta == 3) sf_return = histmap_mmeta11_TwoSS_2d_sf_ttbar_2016 -> eval(lep_pt0, lep_pt1);
				}
			}
		}

		else if(year == 2017)
		{
			if(variation > 0)
			{
				if(id_type == 0)
				{
					if(idx_eta == 0) sf_return = histmap_eeeta00_TwoSS_2d_sf_ttbar_2017 -> eval_up(lep_pt0, lep_pt1);
					else if(idx_eta == 1) sf_return = histmap_eeeta01_TwoSS_2d_sf_ttbar_2017 -> eval_up(lep_pt0, lep_pt1);
					else if(idx_eta == 2) sf_return = histmap_eeeta10_TwoSS_2d_sf_ttbar_2017 -> eval_up(lep_pt0, lep_pt1);
					else if(idx_eta == 3) sf_return = histmap_eeeta11_TwoSS_2d_sf_ttbar_2017 -> eval_up(lep_pt0, lep_pt1);
				}
				else if(id_type == 1)
				{
					if(idx_eta == 0) sf_return = histmap_emeta00_TwoSS_2d_sf_ttbar_2017 -> eval_up(lep_pt0, lep_pt1);
					else if(idx_eta == 1) sf_return = histmap_emeta01_TwoSS_2d_sf_ttbar_2017 -> eval_up(lep_pt0, lep_pt1);
					else if(idx_eta == 2) sf_return = histmap_emeta10_TwoSS_2d_sf_ttbar_2017 -> eval_up(lep_pt0, lep_pt1);
					else if(idx_eta == 3) sf_return = histmap_emeta11_TwoSS_2d_sf_ttbar_2017 -> eval_up(lep_pt0, lep_pt1);
				}
				else if(id_type == 2)
				{
					if(idx_eta == 0) sf_return = histmap_mmeta00_TwoSS_2d_sf_ttbar_2017 -> eval_up(lep_pt0, lep_pt1);
					else if(idx_eta == 1) sf_return = histmap_mmeta01_TwoSS_2d_sf_ttbar_2017 -> eval_up(lep_pt0, lep_pt1);
					else if(idx_eta == 2) sf_return = histmap_mmeta10_TwoSS_2d_sf_ttbar_2017 -> eval_up(lep_pt0, lep_pt1);
					else if(idx_eta == 3) sf_return = histmap_mmeta11_TwoSS_2d_sf_ttbar_2017 -> eval_up(lep_pt0, lep_pt1);
				}
			}

			else if(variation < 0)
			{
				if(id_type == 0)
				{
					if(idx_eta == 0) sf_return = histmap_eeeta00_TwoSS_2d_sf_ttbar_2017 -> eval_down(lep_pt0, lep_pt1);
					else if(idx_eta == 1) sf_return = histmap_eeeta01_TwoSS_2d_sf_ttbar_2017 -> eval_down(lep_pt0, lep_pt1);
					else if(idx_eta == 2) sf_return = histmap_eeeta10_TwoSS_2d_sf_ttbar_2017 -> eval_down(lep_pt0, lep_pt1);
					else if(idx_eta == 3) sf_return = histmap_eeeta11_TwoSS_2d_sf_ttbar_2017 -> eval_down(lep_pt0, lep_pt1);
				}
				else if(id_type == 1)
				{
					if(idx_eta == 0) sf_return = histmap_emeta00_TwoSS_2d_sf_ttbar_2017 -> eval_down(lep_pt0, lep_pt1);
					else if(idx_eta == 1) sf_return = histmap_emeta01_TwoSS_2d_sf_ttbar_2017 -> eval_down(lep_pt0, lep_pt1);
					else if(idx_eta == 2) sf_return = histmap_emeta10_TwoSS_2d_sf_ttbar_2017 -> eval_down(lep_pt0, lep_pt1);
					else if(idx_eta == 3) sf_return = histmap_emeta11_TwoSS_2d_sf_ttbar_2017 -> eval_down(lep_pt0, lep_pt1);
				}
				else if(id_type == 2)
				{
					if(idx_eta == 0) sf_return = histmap_mmeta00_TwoSS_2d_sf_ttbar_2017 -> eval_down(lep_pt0, lep_pt1);
					else if(idx_eta == 1) sf_return = histmap_mmeta01_TwoSS_2d_sf_ttbar_2017 -> eval_down(lep_pt0, lep_pt1);
					else if(idx_eta == 2) sf_return = histmap_mmeta10_TwoSS_2d_sf_ttbar_2017 -> eval_down(lep_pt0, lep_pt1);
					else if(idx_eta == 3) sf_return = histmap_mmeta11_TwoSS_2d_sf_ttbar_2017 -> eval_down(lep_pt0, lep_pt1);
				}
			}

			else if(variation == 0)
			{
				if(id_type == 0)
				{
					if(idx_eta == 0) sf_return = histmap_eeeta00_TwoSS_2d_sf_ttbar_2017 -> eval(lep_pt0, lep_pt1);
					else if(idx_eta == 1) sf_return = histmap_eeeta01_TwoSS_2d_sf_ttbar_2017 -> eval(lep_pt0, lep_pt1);
					else if(idx_eta == 2) sf_return = histmap_eeeta10_TwoSS_2d_sf_ttbar_2017 -> eval(lep_pt0, lep_pt1);
					else if(idx_eta == 3) sf_return = histmap_eeeta11_TwoSS_2d_sf_ttbar_2017 -> eval(lep_pt0, lep_pt1);
				}
				else if(id_type == 1)
				{
					if(idx_eta == 0) sf_return = histmap_emeta00_TwoSS_2d_sf_ttbar_2017 -> eval(lep_pt0, lep_pt1);
					else if(idx_eta == 1) sf_return = histmap_emeta01_TwoSS_2d_sf_ttbar_2017 -> eval(lep_pt0, lep_pt1);
					else if(idx_eta == 2) sf_return = histmap_emeta10_TwoSS_2d_sf_ttbar_2017 -> eval(lep_pt0, lep_pt1);
					else if(idx_eta == 3) sf_return = histmap_emeta11_TwoSS_2d_sf_ttbar_2017 -> eval(lep_pt0, lep_pt1);
				}
				else if(id_type == 2)
				{
					if(idx_eta == 0) sf_return = histmap_mmeta00_TwoSS_2d_sf_ttbar_2017 -> eval(lep_pt0, lep_pt1);
					else if(idx_eta == 1) sf_return = histmap_mmeta01_TwoSS_2d_sf_ttbar_2017 -> eval(lep_pt0, lep_pt1);
					else if(idx_eta == 2) sf_return = histmap_mmeta10_TwoSS_2d_sf_ttbar_2017 -> eval(lep_pt0, lep_pt1);
					else if(idx_eta == 3) sf_return = histmap_mmeta11_TwoSS_2d_sf_ttbar_2017 -> eval(lep_pt0, lep_pt1);
				}
			}
		}
	
		else if(year == 2018)
		{
			if(variation > 0)
			{
				if(id_type == 0)
				{
					if(idx_eta == 0) sf_return = histmap_eeeta00_TwoSS_2d_sf_ttbar_2018 -> eval_up(lep_pt0, lep_pt1);
					else if(idx_eta == 1) sf_return = histmap_eeeta01_TwoSS_2d_sf_ttbar_2018 -> eval_up(lep_pt0, lep_pt1);
					else if(idx_eta == 2) sf_return = histmap_eeeta10_TwoSS_2d_sf_ttbar_2018 -> eval_up(lep_pt0, lep_pt1);
					else if(idx_eta == 3) sf_return = histmap_eeeta11_TwoSS_2d_sf_ttbar_2018 -> eval_up(lep_pt0, lep_pt1);
				}
				else if(id_type == 1)
				{
					if(idx_eta == 0) sf_return = histmap_emeta00_TwoSS_2d_sf_ttbar_2018 -> eval_up(lep_pt0, lep_pt1);
					else if(idx_eta == 1) sf_return = histmap_emeta01_TwoSS_2d_sf_ttbar_2018 -> eval_up(lep_pt0, lep_pt1);
					else if(idx_eta == 2) sf_return = histmap_emeta10_TwoSS_2d_sf_ttbar_2018 -> eval_up(lep_pt0, lep_pt1);
					else if(idx_eta == 3) sf_return = histmap_emeta11_TwoSS_2d_sf_ttbar_2018 -> eval_up(lep_pt0, lep_pt1);
				}
				else if(id_type == 2)
				{
					if(idx_eta == 0) sf_return = histmap_mmeta00_TwoSS_2d_sf_ttbar_2018 -> eval_up(lep_pt0, lep_pt1);
					else if(idx_eta == 1) sf_return = histmap_mmeta01_TwoSS_2d_sf_ttbar_2018 -> eval_up(lep_pt0, lep_pt1);
					else if(idx_eta == 2) sf_return = histmap_mmeta10_TwoSS_2d_sf_ttbar_2018 -> eval_up(lep_pt0, lep_pt1);
					else if(idx_eta == 3) sf_return = histmap_mmeta11_TwoSS_2d_sf_ttbar_2018 -> eval_up(lep_pt0, lep_pt1);
				}
			}

			else if(variation < 0)
			{
				if(id_type == 0)
				{
					if(idx_eta == 0) sf_return = histmap_eeeta00_TwoSS_2d_sf_ttbar_2018 -> eval_down(lep_pt0, lep_pt1);
					else if(idx_eta == 1) sf_return = histmap_eeeta01_TwoSS_2d_sf_ttbar_2018 -> eval_down(lep_pt0, lep_pt1);
					else if(idx_eta == 2) sf_return = histmap_eeeta10_TwoSS_2d_sf_ttbar_2018 -> eval_down(lep_pt0, lep_pt1);
					else if(idx_eta == 3) sf_return = histmap_eeeta11_TwoSS_2d_sf_ttbar_2018 -> eval_down(lep_pt0, lep_pt1);
				}
				else if(id_type == 1)
				{
					if(idx_eta == 0) sf_return = histmap_emeta00_TwoSS_2d_sf_ttbar_2018 -> eval_down(lep_pt0, lep_pt1);
					else if(idx_eta == 1) sf_return = histmap_emeta01_TwoSS_2d_sf_ttbar_2018 -> eval_down(lep_pt0, lep_pt1);
					else if(idx_eta == 2) sf_return = histmap_emeta10_TwoSS_2d_sf_ttbar_2018 -> eval_down(lep_pt0, lep_pt1);
					else if(idx_eta == 3) sf_return = histmap_emeta11_TwoSS_2d_sf_ttbar_2018 -> eval_down(lep_pt0, lep_pt1);
				}
				else if(id_type == 2)
				{
					if(idx_eta == 0) sf_return = histmap_mmeta00_TwoSS_2d_sf_ttbar_2018 -> eval_down(lep_pt0, lep_pt1);
					else if(idx_eta == 1) sf_return = histmap_mmeta01_TwoSS_2d_sf_ttbar_2018 -> eval_down(lep_pt0, lep_pt1);
					else if(idx_eta == 2) sf_return = histmap_mmeta10_TwoSS_2d_sf_ttbar_2018 -> eval_down(lep_pt0, lep_pt1);
					else if(idx_eta == 3) sf_return = histmap_mmeta11_TwoSS_2d_sf_ttbar_2018 -> eval_down(lep_pt0, lep_pt1);
				}
			}

			else if(variation == 0)
			{
				if(id_type == 0)
				{
					if(idx_eta == 0) sf_return = histmap_eeeta00_TwoSS_2d_sf_ttbar_2018 -> eval(lep_pt0, lep_pt1);
					else if(idx_eta == 1) sf_return = histmap_eeeta01_TwoSS_2d_sf_ttbar_2018 -> eval(lep_pt0, lep_pt1);
					else if(idx_eta == 2) sf_return = histmap_eeeta10_TwoSS_2d_sf_ttbar_2018 -> eval(lep_pt0, lep_pt1);
					else if(idx_eta == 3) sf_return = histmap_eeeta11_TwoSS_2d_sf_ttbar_2018 -> eval(lep_pt0, lep_pt1);
				}
				else if(id_type == 1)
				{
					if(idx_eta == 0) sf_return = histmap_emeta00_TwoSS_2d_sf_ttbar_2018 -> eval(lep_pt0, lep_pt1);
					else if(idx_eta == 1) sf_return = histmap_emeta01_TwoSS_2d_sf_ttbar_2018 -> eval(lep_pt0, lep_pt1);
					else if(idx_eta == 2) sf_return = histmap_emeta10_TwoSS_2d_sf_ttbar_2018 -> eval(lep_pt0, lep_pt1);
					else if(idx_eta == 3) sf_return = histmap_emeta11_TwoSS_2d_sf_ttbar_2018 -> eval(lep_pt0, lep_pt1);
				}
				else if(id_type == 2)
				{
					if(idx_eta == 0) sf_return = histmap_mmeta00_TwoSS_2d_sf_ttbar_2018 -> eval(lep_pt0, lep_pt1);
					else if(idx_eta == 1) sf_return = histmap_mmeta01_TwoSS_2d_sf_ttbar_2018 -> eval(lep_pt0, lep_pt1);
					else if(idx_eta == 2) sf_return = histmap_mmeta10_TwoSS_2d_sf_ttbar_2018 -> eval(lep_pt0, lep_pt1);
					else if(idx_eta == 3) sf_return = histmap_mmeta11_TwoSS_2d_sf_ttbar_2018 -> eval(lep_pt0, lep_pt1);
				}
			}
		}
		
		if(abs(sf_return) < 0.000001) sf_return = 1.0;
		//cout<<"DEBUG TRIG SF ...... "<<sf_return<<endl;
		return sf_return;
	}	
};
//_______________________________________________________________________________________________________
class LeptonScaleFactors
{
    public:
        RooUtil::HistMap* histmap2016_mu_recoid_GH_sf; // POG muon // Because MuonPOG has split the 2016 scale factors into two parts. WHY????!?!?
        RooUtil::HistMap* histmap2016_mu_recoid_sf;    // POG muon
        RooUtil::HistMap* histmap2016_el_recoid_sf;    // POG electron tracking ID
        RooUtil::HistMap* histmap2016_el_mva_sf;       // POG electron MVA
        RooUtil::HistMap* histmap2016_mu_veto_sf;      // our veto ID SF muon
        RooUtil::HistMap* histmap2016_mu_ss_sf;        // our SS ID SF muon
        RooUtil::HistMap* histmap2016_mu_3l_sf;        // our 3l ID SF muon
        RooUtil::HistMap* histmap2016_el_veto_sf;      // our veto ID SF electron
        RooUtil::HistMap* histmap2016_el_ss_sf;        // our SS ID SF electron
        RooUtil::HistMap* histmap2016_el_3l_sf;        // our 3l ID SF electron

        RooUtil::HistMap* histmap2017_mu_recoid_sf;    // POG muon
        RooUtil::HistMap* histmap2017_el_recoid_sf;    // POG electron tracking ID
        RooUtil::HistMap* histmap2017_el_mva_sf;       // POG electron MVA
        RooUtil::HistMap* histmap2017_mu_veto_sf;      // our veto ID SF muon
        RooUtil::HistMap* histmap2017_mu_ss_sf;        // our SS ID SF muon
        RooUtil::HistMap* histmap2017_mu_3l_sf;        // our 3l ID SF muon
        RooUtil::HistMap* histmap2017_el_veto_sf;      // our veto ID SF electron
        RooUtil::HistMap* histmap2017_el_ss_sf;        // our SS ID SF electron
        RooUtil::HistMap* histmap2017_el_3l_sf;        // our 3l ID SF electron

        RooUtil::HistMap* histmap2018_mu_recoid_sf;    // POG muon
        RooUtil::HistMap* histmap2018_el_recoid_sf;    // POG electron tracking ID
        RooUtil::HistMap* histmap2018_el_mva_sf;       // POG electron MVA
        RooUtil::HistMap* histmap2018_mu_veto_sf;      // our veto ID SF muon
        RooUtil::HistMap* histmap2018_mu_ss_sf;        // our SS ID SF muon
        RooUtil::HistMap* histmap2018_mu_3l_sf;        // our 3l ID SF muon
        RooUtil::HistMap* histmap2018_el_veto_sf;      // our veto ID SF electron
        RooUtil::HistMap* histmap2018_el_ss_sf;        // our SS ID SF electron
        RooUtil::HistMap* histmap2018_el_3l_sf;        // our 3l ID SF electron


        LeptonScaleFactors()
        {

            histmap2016_mu_recoid_GH_sf  = new RooUtil::HistMap("/nfs-7/userdata/phchang/scalefactors/EfficiencyStudies_2016_rootfiles_RunGH_SF_ID.root:NUM_LooseID_DEN_genTracks_eta_pt");
            histmap2016_mu_recoid_sf     = new RooUtil::HistMap("/nfs-7/userdata/phchang/scalefactors/EfficiencyStudies_2016_rootfiles_RunBCDEF_SF_ID.root:NUM_LooseID_DEN_genTracks_eta_pt");
            histmap2016_el_recoid_sf     = new RooUtil::HistMap("/nfs-7/userdata/phchang/scalefactors/EGM2D_BtoH_GT20GeV_RecoSF_Legacy2016.root:EGamma_SF2D");
            histmap2016_el_mva_sf        = new RooUtil::HistMap("/nfs-7/userdata/phchang/scalefactors/2016LegacyReReco_ElectronMVA80noiso_Fall17V2.root:EGamma_SF2D");
            histmap2016_mu_veto_sf       = new RooUtil::HistMap("/nfs-7/userdata/haweber/scalefactors/sf_2016_muon_vetoID_20191115.root:h_sf_pt_vs_eta");
            histmap2016_mu_ss_sf         = new RooUtil::HistMap("/nfs-7/userdata/haweber/scalefactors/sf_2016_muon_ssID_20191115.root:h_sf_pt_vs_eta");
            histmap2016_mu_3l_sf         = new RooUtil::HistMap("/nfs-7/userdata/haweber/scalefactors/sf_2016_muon_3lID_20191115.root:h_sf_pt_vs_eta");
            histmap2016_el_veto_sf       = new RooUtil::HistMap("/nfs-7/userdata/haweber/scalefactors/sf_2016_electron_vetoID_20191115.root:h_sf_pt_vs_eta");
            histmap2016_el_ss_sf         = new RooUtil::HistMap("/nfs-7/userdata/haweber/scalefactors/sf_2016_electron_ssID_20191115.root:h_sf_pt_vs_eta");
            histmap2016_el_3l_sf         = new RooUtil::HistMap("/nfs-7/userdata/haweber/scalefactors/sf_2016_electron_3lID_20191115.root:h_sf_pt_vs_eta");
            
            histmap2017_mu_recoid_sf     = new RooUtil::HistMap("/nfs-7/userdata/phchang/scalefactors/RunBCDEF_SF_ID.root:NUM_LooseID_DEN_genTracks_pt_abseta");
            histmap2017_el_recoid_sf     = new RooUtil::HistMap("/nfs-7/userdata/phchang/scalefactors/egammaEffi.txt_EGM2D_runBCDEF_passingRECO.root:EGamma_SF2D");
            histmap2017_el_mva_sf        = new RooUtil::HistMap("/nfs-7/userdata/phchang/scalefactors/gammaEffi.txt_EGM2D_runBCDEF_passingMVA94Xwp80noiso.root:EGamma_SF2D");
            histmap2017_mu_veto_sf       = new RooUtil::HistMap("/nfs-7/userdata/haweber/scalefactors/sf_2017_muon_vetoID_20191115.root:h_sf_pt_vs_eta");
            histmap2017_mu_ss_sf         = new RooUtil::HistMap("/nfs-7/userdata/haweber/scalefactors/sf_2017_muon_ssID_20191115.root:h_sf_pt_vs_eta");
            histmap2017_mu_3l_sf         = new RooUtil::HistMap("/nfs-7/userdata/haweber/scalefactors/sf_2017_muon_3lID_20191115.root:h_sf_pt_vs_eta");
            histmap2017_el_veto_sf       = new RooUtil::HistMap("/nfs-7/userdata/haweber/scalefactors/sf_2017_electron_vetoID_20191115.root:h_sf_pt_vs_eta");
            histmap2017_el_ss_sf         = new RooUtil::HistMap("/nfs-7/userdata/haweber/scalefactors/sf_2017_electron_ssID_20191115.root:h_sf_pt_vs_eta");
            histmap2017_el_3l_sf         = new RooUtil::HistMap("/nfs-7/userdata/haweber/scalefactors/sf_2017_electron_3lID_20191115.root:h_sf_pt_vs_eta");

            histmap2018_mu_recoid_sf     = new RooUtil::HistMap("/nfs-7/userdata/phchang/scalefactors/EfficienciesStudies_2018_rootfiles_RunABCD_SF_ID.root:NUM_LooseID_DEN_TrackerMuons_pt_abseta");
            histmap2018_el_recoid_sf     = new RooUtil::HistMap("/nfs-7/userdata/phchang/scalefactors/egammaEffi.txt_EGM2D_updatedAll.root:EGamma_SF2D");
            histmap2018_el_mva_sf        = new RooUtil::HistMap("/nfs-7/userdata/phchang/scalefactors/2018_ElectronMVA80noiso.root:EGamma_SF2D");
            histmap2018_mu_veto_sf       = new RooUtil::HistMap("/nfs-7/userdata/haweber/scalefactors/sf_2018_muon_vetoID_20191115.root:h_sf_pt_vs_eta");
            histmap2018_mu_ss_sf         = new RooUtil::HistMap("/nfs-7/userdata/haweber/scalefactors/sf_2018_muon_ssID_20191115.root:h_sf_pt_vs_eta");
            histmap2018_mu_3l_sf         = new RooUtil::HistMap("/nfs-7/userdata/haweber/scalefactors/sf_2018_muon_3lID_20191115.root:h_sf_pt_vs_eta");
            histmap2018_el_veto_sf       = new RooUtil::HistMap("/nfs-7/userdata/haweber/scalefactors/sf_2018_electron_vetoID_20191115.root:h_sf_pt_vs_eta");
            histmap2018_el_ss_sf         = new RooUtil::HistMap("/nfs-7/userdata/haweber/scalefactors/sf_2018_electron_ssID_20191115.root:h_sf_pt_vs_eta");
            histmap2018_el_3l_sf         = new RooUtil::HistMap("/nfs-7/userdata/haweber/scalefactors/sf_2018_electron_3lID_20191115.root:h_sf_pt_vs_eta");
        
        }

        ~LeptonScaleFactors()
        {
            delete histmap2016_mu_recoid_GH_sf;
            delete histmap2016_mu_recoid_sf;
            delete histmap2016_el_recoid_sf;
            delete histmap2016_el_mva_sf;
            delete histmap2016_mu_veto_sf;
            delete histmap2016_mu_ss_sf;
            delete histmap2016_mu_3l_sf;
            delete histmap2016_el_veto_sf;
            delete histmap2016_el_ss_sf;
            delete histmap2016_el_3l_sf;
            delete histmap2017_mu_recoid_sf;
            delete histmap2017_el_recoid_sf;
            delete histmap2017_el_mva_sf;
            delete histmap2017_mu_veto_sf;
            delete histmap2017_mu_ss_sf;
            delete histmap2017_mu_3l_sf;
            delete histmap2017_el_veto_sf;
            delete histmap2017_el_ss_sf;
            delete histmap2017_el_3l_sf;
            delete histmap2018_mu_recoid_sf;
            delete histmap2018_el_recoid_sf;
            delete histmap2018_el_mva_sf;
            delete histmap2018_mu_veto_sf;
            delete histmap2018_mu_ss_sf;
            delete histmap2018_mu_3l_sf;
            delete histmap2018_el_veto_sf;
            delete histmap2018_el_ss_sf;
            delete histmap2018_el_3l_sf;
        }

        //std::tuple<float, float, float, float> getScaleFactors(bool is2017, bool doFakeEstimation, bool isData, int variation=0)
        //variation: 0 = none, +1: ele/muo up, -1: ele/muo down, +11: ele up, -11: ele down, +13: muo up, -13: muo down
        float getScaleFactors(int year, bool doFakeEstimation, bool isData, int variation=0)
        {
            // return 1;
          int variationmu = 0;
          int variationel = 0;
          if(variation == +1 || variation == +13) variationmu = +1;
          if(variation == -1 || variation == -13) variationmu = -1;
          if(variation == +1 || variation == +11) variationel = +1;
          if(variation == -1 || variation == -11) variationel = -1;
            if (isData)
            {
                return 1;
            }
            else if (year == 2018)
            {
                const double b500 = 499.9;
                const double b120 = 119.9;
                float lead_mu_recoid_sf = variationmu > 0 ? histmap2018_mu_recoid_sf -> eval_up(min((double)www.lep_pt()[0],b120)   ,abs((double)www.lep_eta()[0])     ) : variationmu < 0 ? histmap2018_mu_recoid_sf -> eval_down(min((double)www.lep_pt()[0],b120)   ,abs((double)www.lep_eta()[0])     ) : histmap2018_mu_recoid_sf -> eval(min((double)www.lep_pt()[0],b120)   ,abs((double)www.lep_eta()[0])     );
                float subl_mu_recoid_sf = variationmu > 0 ? histmap2018_mu_recoid_sf -> eval_up(min((double)www.lep_pt()[1],b120)   ,abs((double)www.lep_eta()[1])     ) : variationmu < 0 ? histmap2018_mu_recoid_sf -> eval_down(min((double)www.lep_pt()[1],b120)   ,abs((double)www.lep_eta()[1])     ) : histmap2018_mu_recoid_sf -> eval(min((double)www.lep_pt()[1],b120)   ,abs((double)www.lep_eta()[1])     );
                float tert_mu_recoid_sf = variationmu > 0 ? histmap2018_mu_recoid_sf -> eval_up(min((double)www.lep_pt()[2],b120)   ,abs((double)www.lep_eta()[2])     ) : variationmu < 0 ? histmap2018_mu_recoid_sf -> eval_down(min((double)www.lep_pt()[2],b120)   ,abs((double)www.lep_eta()[2])     ) : histmap2018_mu_recoid_sf -> eval(min((double)www.lep_pt()[2],b120)   ,abs((double)www.lep_eta()[2])     );
                float lead_el_recoid_sf = variationel > 0 ? histmap2018_el_recoid_sf -> eval_up(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b500) ) : variationel < 0 ? histmap2018_el_recoid_sf -> eval_down(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b500) ) : histmap2018_el_recoid_sf -> eval(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b500) );
                float subl_el_recoid_sf = variationel > 0 ? histmap2018_el_recoid_sf -> eval_up(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b500) ) : variationel < 0 ? histmap2018_el_recoid_sf -> eval_down(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b500) ) : histmap2018_el_recoid_sf -> eval(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b500) );
                float tert_el_recoid_sf = variationel > 0 ? histmap2018_el_recoid_sf -> eval_up(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b500) ) : variationel < 0 ? histmap2018_el_recoid_sf -> eval_down(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b500) ) : histmap2018_el_recoid_sf -> eval(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b500) );
                float lead_el_mva_sf    = variationel > 0 ? histmap2018_el_mva_sf    -> eval_up(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b500) ) : variationel < 0 ? histmap2018_el_mva_sf    -> eval_down(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b500) ) : histmap2018_el_mva_sf    -> eval(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b500) );
                float subl_el_mva_sf    = variationel > 0 ? histmap2018_el_mva_sf    -> eval_up(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b500) ) : variationel < 0 ? histmap2018_el_mva_sf    -> eval_down(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b500) ) : histmap2018_el_mva_sf    -> eval(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b500) );
                float tert_el_mva_sf    = variationel > 0 ? histmap2018_el_mva_sf    -> eval_up(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b500) ) : variationel < 0 ? histmap2018_el_mva_sf    -> eval_down(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b500) ) : histmap2018_el_mva_sf    -> eval(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b500) );
                float lead_mu_veto_sf   = variationmu > 0 ? histmap2018_mu_veto_sf   -> eval_up(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b120) ) : variationmu < 0 ? histmap2018_mu_veto_sf   -> eval_down(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b120) ) : histmap2018_mu_veto_sf   -> eval(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b120) );
                float subl_mu_veto_sf   = variationmu > 0 ? histmap2018_mu_veto_sf   -> eval_up(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b120) ) : variationmu < 0 ? histmap2018_mu_veto_sf   -> eval_down(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b120) ) : histmap2018_mu_veto_sf   -> eval(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b120) );
                float tert_mu_veto_sf   = variationmu > 0 ? histmap2018_mu_veto_sf   -> eval_up(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b120) ) : variationmu < 0 ? histmap2018_mu_veto_sf   -> eval_down(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b120) ) : histmap2018_mu_veto_sf   -> eval(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b120) );
                float lead_mu_ss_sf     = variationmu > 0 ? histmap2018_mu_ss_sf     -> eval_up(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b120) ) : variationmu < 0 ? histmap2018_mu_ss_sf     -> eval_down(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b120) ) : histmap2018_mu_ss_sf     -> eval(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b120) );
                float subl_mu_ss_sf     = variationmu > 0 ? histmap2018_mu_ss_sf     -> eval_up(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b120) ) : variationmu < 0 ? histmap2018_mu_ss_sf     -> eval_down(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b120) ) : histmap2018_mu_ss_sf     -> eval(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b120) );
                float tert_mu_ss_sf     = variationmu > 0 ? histmap2018_mu_ss_sf     -> eval_up(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b120) ) : variationmu < 0 ? histmap2018_mu_ss_sf     -> eval_down(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b120) ) : histmap2018_mu_ss_sf     -> eval(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b120) );
                float lead_mu_3l_sf     = variationmu > 0 ? histmap2018_mu_3l_sf     -> eval_up(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b120) ) : variationmu < 0 ? histmap2018_mu_3l_sf     -> eval_down(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b120) ) : histmap2018_mu_3l_sf     -> eval(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b120) );
                float subl_mu_3l_sf     = variationmu > 0 ? histmap2018_mu_3l_sf     -> eval_up(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b120) ) : variationmu < 0 ? histmap2018_mu_3l_sf     -> eval_down(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b120) ) : histmap2018_mu_3l_sf     -> eval(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b120) );
                float tert_mu_3l_sf     = variationmu > 0 ? histmap2018_mu_3l_sf     -> eval_up(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b120) ) : variationmu < 0 ? histmap2018_mu_3l_sf     -> eval_down(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b120) ) : histmap2018_mu_3l_sf     -> eval(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b120) );
                float lead_el_veto_sf   = variationel > 0 ? histmap2018_el_veto_sf   -> eval_up(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b500) ) : variationel < 0 ? histmap2018_el_veto_sf   -> eval_down(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b500) ) : histmap2018_el_veto_sf   -> eval(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b500) );
                float subl_el_veto_sf   = variationel > 0 ? histmap2018_el_veto_sf   -> eval_up(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b500) ) : variationel < 0 ? histmap2018_el_veto_sf   -> eval_down(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b500) ) : histmap2018_el_veto_sf   -> eval(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b500) );
                float tert_el_veto_sf   = variationel > 0 ? histmap2018_el_veto_sf   -> eval_up(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b500) ) : variationel < 0 ? histmap2018_el_veto_sf   -> eval_down(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b500) ) : histmap2018_el_veto_sf   -> eval(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b500) );
                float lead_el_ss_sf     = variationel > 0 ? histmap2018_el_ss_sf     -> eval_up(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b500) ) : variationel < 0 ? histmap2018_el_ss_sf     -> eval_down(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b500) ) : histmap2018_el_ss_sf     -> eval(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b500) );
                float subl_el_ss_sf     = variationel > 0 ? histmap2018_el_ss_sf     -> eval_up(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b500) ) : variationel < 0 ? histmap2018_el_ss_sf     -> eval_down(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b500) ) : histmap2018_el_ss_sf     -> eval(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b500) );
                float tert_el_ss_sf     = variationel > 0 ? histmap2018_el_ss_sf     -> eval_up(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b500) ) : variationel < 0 ? histmap2018_el_ss_sf     -> eval_down(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b500) ) : histmap2018_el_ss_sf     -> eval(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b500) );
                float lead_el_3l_sf     = variationel > 0 ? histmap2018_el_3l_sf     -> eval_up(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b500) ) : variationel < 0 ? histmap2018_el_3l_sf     -> eval_down(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b500) ) : histmap2018_el_3l_sf     -> eval(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b500) );
                float subl_el_3l_sf     = variationel > 0 ? histmap2018_el_3l_sf     -> eval_up(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b500) ) : variationel < 0 ? histmap2018_el_3l_sf     -> eval_down(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b500) ) : histmap2018_el_3l_sf     -> eval(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b500) );
                float tert_el_3l_sf     = variationel > 0 ? histmap2018_el_3l_sf     -> eval_up(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b500) ) : variationel < 0 ? histmap2018_el_3l_sf     -> eval_down(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b500) ) : histmap2018_el_3l_sf     -> eval(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b500) );

                //temp until mva WPLoose is there
                lead_el_mva_sf = 1.;
                subl_el_mva_sf = 1.;
                tert_el_mva_sf = 1.;
                
                float frst_el_ss_sf = lead_el_recoid_sf * lead_el_mva_sf * lead_el_veto_sf * lead_el_ss_sf;
                float scnd_el_ss_sf = subl_el_recoid_sf * subl_el_mva_sf * subl_el_veto_sf * subl_el_ss_sf;
                float thrd_el_ss_sf = tert_el_recoid_sf * tert_el_mva_sf * tert_el_veto_sf * tert_el_ss_sf;
                float frst_el_3l_sf = lead_el_recoid_sf * lead_el_mva_sf * lead_el_veto_sf * lead_el_3l_sf;
                float scnd_el_3l_sf = subl_el_recoid_sf * subl_el_mva_sf * subl_el_veto_sf * subl_el_3l_sf;
                float thrd_el_3l_sf = tert_el_recoid_sf * tert_el_mva_sf * tert_el_veto_sf * tert_el_3l_sf;
                float frst_mu_ss_sf = lead_mu_recoid_sf * lead_mu_veto_sf * lead_mu_ss_sf;
                float scnd_mu_ss_sf = subl_mu_recoid_sf * subl_mu_veto_sf * subl_mu_ss_sf;
                float thrd_mu_ss_sf = tert_mu_recoid_sf * tert_mu_veto_sf * tert_mu_ss_sf;
                float frst_mu_3l_sf = lead_mu_recoid_sf * lead_mu_veto_sf * lead_mu_3l_sf;
                float scnd_mu_3l_sf = subl_mu_recoid_sf * subl_mu_veto_sf * subl_mu_3l_sf;
                float thrd_mu_3l_sf = tert_mu_recoid_sf * tert_mu_veto_sf * tert_mu_3l_sf;

                // **** Over writing previous scale factors with Jonas' scale factors **** //
                // **** Over writing previous scale factors with Jonas' scale factors **** //
                // **** Over writing previous scale factors with Jonas' scale factors **** //
                // CODE COULD BE CLEANER //
                if (variationel >  0) frst_el_ss_sf = electronScaleFactors(input.year, LeptonID::SameSign, www.lep_eta()[1], min((double)www.lep_pt()[1],b500), SystematicVariation::Up);
                if (variationel <  0) frst_el_ss_sf = electronScaleFactors(input.year, LeptonID::SameSign, www.lep_eta()[1], min((double)www.lep_pt()[1],b500), SystematicVariation::Down);
                if (variationel == 0) frst_el_ss_sf = electronScaleFactors(input.year, LeptonID::SameSign, www.lep_eta()[1], min((double)www.lep_pt()[1],b500), SystematicVariation::Nominal);

                if (variationel >  0) scnd_el_ss_sf = electronScaleFactors(input.year, LeptonID::SameSign, www.lep_eta()[1], min((double)www.lep_pt()[1],b500), SystematicVariation::Up);
                if (variationel <  0) scnd_el_ss_sf = electronScaleFactors(input.year, LeptonID::SameSign, www.lep_eta()[1], min((double)www.lep_pt()[1],b500), SystematicVariation::Down);
                if (variationel == 0) scnd_el_ss_sf = electronScaleFactors(input.year, LeptonID::SameSign, www.lep_eta()[1], min((double)www.lep_pt()[1],b500), SystematicVariation::Nominal);

                if (www.nVlep() == 3)
                {
                    if (variationel >  0) thrd_el_ss_sf = electronScaleFactors(input.year, LeptonID::SameSign, www.lep_eta()[2], min((double)www.lep_pt()[2],b500), SystematicVariation::Up);
                    if (variationel <  0) thrd_el_ss_sf = electronScaleFactors(input.year, LeptonID::SameSign, www.lep_eta()[2], min((double)www.lep_pt()[2],b500), SystematicVariation::Down);
                    if (variationel == 0) thrd_el_ss_sf = electronScaleFactors(input.year, LeptonID::SameSign, www.lep_eta()[2], min((double)www.lep_pt()[2],b500), SystematicVariation::Nominal);
                }

                if (variationel >  0) frst_el_3l_sf = electronScaleFactors(input.year, LeptonID::SameSign, www.lep_eta()[1], min((double)www.lep_pt()[1],b500), SystematicVariation::Up);
                if (variationel <  0) frst_el_3l_sf = electronScaleFactors(input.year, LeptonID::SameSign, www.lep_eta()[1], min((double)www.lep_pt()[1],b500), SystematicVariation::Down);
                if (variationel == 0) frst_el_3l_sf = electronScaleFactors(input.year, LeptonID::SameSign, www.lep_eta()[1], min((double)www.lep_pt()[1],b500), SystematicVariation::Nominal);

                if (variationel >  0) scnd_el_3l_sf = electronScaleFactors(input.year, LeptonID::SameSign, www.lep_eta()[1], min((double)www.lep_pt()[1],b500), SystematicVariation::Up);
                if (variationel <  0) scnd_el_3l_sf = electronScaleFactors(input.year, LeptonID::SameSign, www.lep_eta()[1], min((double)www.lep_pt()[1],b500), SystematicVariation::Down);
                if (variationel == 0) scnd_el_3l_sf = electronScaleFactors(input.year, LeptonID::SameSign, www.lep_eta()[1], min((double)www.lep_pt()[1],b500), SystematicVariation::Nominal);

                if (www.nVlep() == 3)
                {
                    if (variationel >  0) thrd_el_3l_sf = electronScaleFactors(input.year, LeptonID::SameSign, www.lep_eta()[1], min((double)www.lep_pt()[1],b500), SystematicVariation::Up);
                    if (variationel <  0) thrd_el_3l_sf = electronScaleFactors(input.year, LeptonID::SameSign, www.lep_eta()[1], min((double)www.lep_pt()[1],b500), SystematicVariation::Down);
                    if (variationel == 0) thrd_el_3l_sf = electronScaleFactors(input.year, LeptonID::SameSign, www.lep_eta()[1], min((double)www.lep_pt()[1],b500), SystematicVariation::Nominal);
                }

                // Scale factors
                if (www.nVlep() == 2)
                {
                    if (abs(www.lep_pdgId()[0]) * abs(www.lep_pdgId()[1]) == 121)
                    {
                      return (doFakeEstimation ? 1. : (frst_el_ss_sf * scnd_el_ss_sf));
                    }
                    else if (abs(www.lep_pdgId()[0]) * abs(www.lep_pdgId()[1]) == 143)
                    {
                        if(abs(www.lep_pdgId()[0])==11){
                           return (doFakeEstimation ? 1. : (frst_el_ss_sf * scnd_mu_ss_sf));
                        }
                        else {
                           return (doFakeEstimation ? 1. : (frst_mu_ss_sf * scnd_el_ss_sf));
                        }
                    }
                    else if (abs(www.lep_pdgId()[0]) * abs(www.lep_pdgId()[1]) == 169)
                    {
                        return (doFakeEstimation ? 1. : (frst_mu_ss_sf * scnd_mu_ss_sf));
                    }
                    else
                    {
                        std::cout << "Error: should not be here " << __FUNCTION__ << std::endl;
                        return 1;
                    }
                }
                else if (www.nVlep() == 3)
                {
                    float threelep_sf = 1.;
                    if(www.nSFOS()==0 && ((abs(www.lep_pdgId()[0])+abs(www.lep_pdgId()[1])+abs(www.lep_pdgId()[2])) == 35)){//eem
                        threelep_sf = ((abs(www.lep_pdgId()[0])==11)*(frst_el_ss_sf)+(abs(www.lep_pdgId()[0])!=11)*(frst_mu_3l_sf))
                          *((abs(www.lep_pdgId()[1])==11)*(scnd_el_ss_sf)+(abs(www.lep_pdgId()[1])!=11)*(scnd_mu_3l_sf))
                          *((abs(www.lep_pdgId()[2])==11)*(thrd_el_ss_sf)+(abs(www.lep_pdgId()[2])!=11)*(thrd_mu_3l_sf));
                    }
                    else if(www.nSFOS()==0 && ((abs(www.lep_pdgId()[0])+abs(www.lep_pdgId()[1])+abs(www.lep_pdgId()[2])) == 37)){//emm
                        threelep_sf = ((abs(www.lep_pdgId()[0])==11)*(frst_el_3l_sf)+(abs(www.lep_pdgId()[0])!=11)*(frst_mu_ss_sf))
                          *((abs(www.lep_pdgId()[1])==11)*(scnd_el_3l_sf)+(abs(www.lep_pdgId()[1])!=11)*(scnd_mu_ss_sf))
                          *((abs(www.lep_pdgId()[2])==11)*(thrd_el_3l_sf)+(abs(www.lep_pdgId()[2])!=11)*(thrd_mu_ss_sf));
                    }
                    else {
                        threelep_sf = ((abs(www.lep_pdgId()[0])==11)*(frst_el_3l_sf)+(abs(www.lep_pdgId()[0])!=11)*(frst_mu_3l_sf))
                          *((abs(www.lep_pdgId()[1])==11)*(scnd_el_3l_sf)+(abs(www.lep_pdgId()[1])!=11)*(scnd_mu_3l_sf))
                          *((abs(www.lep_pdgId()[2])==11)*(thrd_el_3l_sf)+(abs(www.lep_pdgId()[2])!=11)*(thrd_mu_3l_sf));
                    }
                    return (doFakeEstimation ? 1. : (threelep_sf));
                }
                else
                {
                    return 1;
                }

            }
            else if (year == 2017)
            {
                const double b500 = 499.9;
                const double b120 = 119.9;
                float lead_mu_recoid_sf = variationmu > 0 ? histmap2017_mu_recoid_sf -> eval_up(min((double)www.lep_pt()[0],b120)   ,abs((double)www.lep_eta()[0])     ) : variationmu < 0 ? histmap2017_mu_recoid_sf -> eval_down(min((double)www.lep_pt()[0],b120)   ,abs((double)www.lep_eta()[0])     ) : histmap2017_mu_recoid_sf -> eval(min((double)www.lep_pt()[0],b120)   ,abs((double)www.lep_eta()[0])     );
                float subl_mu_recoid_sf = variationmu > 0 ? histmap2017_mu_recoid_sf -> eval_up(min((double)www.lep_pt()[1],b120)   ,abs((double)www.lep_eta()[1])     ) : variationmu < 0 ? histmap2017_mu_recoid_sf -> eval_down(min((double)www.lep_pt()[1],b120)   ,abs((double)www.lep_eta()[1])     ) : histmap2017_mu_recoid_sf -> eval(min((double)www.lep_pt()[1],b120)   ,abs((double)www.lep_eta()[1])     );
                float tert_mu_recoid_sf = variationmu > 0 ? histmap2017_mu_recoid_sf -> eval_up(min((double)www.lep_pt()[2],b120)   ,abs((double)www.lep_eta()[2])     ) : variationmu < 0 ? histmap2017_mu_recoid_sf -> eval_down(min((double)www.lep_pt()[2],b120)   ,abs((double)www.lep_eta()[2])     ) : histmap2017_mu_recoid_sf -> eval(min((double)www.lep_pt()[2],b120)   ,abs((double)www.lep_eta()[2])     );
                float lead_el_recoid_sf = variationel > 0 ? histmap2017_el_recoid_sf -> eval_up(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b500) ) : variationel < 0 ? histmap2017_el_recoid_sf -> eval_down(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b500) ) : histmap2017_el_recoid_sf -> eval(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b500) );
                float subl_el_recoid_sf = variationel > 0 ? histmap2017_el_recoid_sf -> eval_up(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b500) ) : variationel < 0 ? histmap2017_el_recoid_sf -> eval_down(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b500) ) : histmap2017_el_recoid_sf -> eval(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b500) );
                float tert_el_recoid_sf = variationel > 0 ? histmap2017_el_recoid_sf -> eval_up(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b500) ) : variationel < 0 ? histmap2017_el_recoid_sf -> eval_down(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b500) ) : histmap2017_el_recoid_sf -> eval(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b500) );
                float lead_el_mva_sf    = variationel > 0 ? histmap2017_el_mva_sf    -> eval_up(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b500) ) : variationel < 0 ? histmap2017_el_mva_sf    -> eval_down(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b500) ) : histmap2017_el_mva_sf    -> eval(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b500) );
                float subl_el_mva_sf    = variationel > 0 ? histmap2017_el_mva_sf    -> eval_up(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b500) ) : variationel < 0 ? histmap2017_el_mva_sf    -> eval_down(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b500) ) : histmap2017_el_mva_sf    -> eval(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b500) );
                float tert_el_mva_sf    = variationel > 0 ? histmap2017_el_mva_sf    -> eval_up(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b500) ) : variationel < 0 ? histmap2017_el_mva_sf    -> eval_down(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b500) ) : histmap2017_el_mva_sf    -> eval(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b500) );
                float lead_mu_veto_sf   = variationmu > 0 ? histmap2017_mu_veto_sf   -> eval_up(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b120) ) : variationmu < 0 ? histmap2017_mu_veto_sf   -> eval_down(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b120) ) : histmap2017_mu_veto_sf   -> eval(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b120) );
                float subl_mu_veto_sf   = variationmu > 0 ? histmap2017_mu_veto_sf   -> eval_up(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b120) ) : variationmu < 0 ? histmap2017_mu_veto_sf   -> eval_down(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b120) ) : histmap2017_mu_veto_sf   -> eval(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b120) );
                float tert_mu_veto_sf   = variationmu > 0 ? histmap2017_mu_veto_sf   -> eval_up(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b120) ) : variationmu < 0 ? histmap2017_mu_veto_sf   -> eval_down(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b120) ) : histmap2017_mu_veto_sf   -> eval(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b120) );
                float lead_mu_ss_sf     = variationmu > 0 ? histmap2017_mu_ss_sf     -> eval_up(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b120) ) : variationmu < 0 ? histmap2017_mu_ss_sf     -> eval_down(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b120) ) : histmap2017_mu_ss_sf     -> eval(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b120) );
                float subl_mu_ss_sf     = variationmu > 0 ? histmap2017_mu_ss_sf     -> eval_up(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b120) ) : variationmu < 0 ? histmap2017_mu_ss_sf     -> eval_down(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b120) ) : histmap2017_mu_ss_sf     -> eval(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b120) );
                float tert_mu_ss_sf     = variationmu > 0 ? histmap2017_mu_ss_sf     -> eval_up(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b120) ) : variationmu < 0 ? histmap2017_mu_ss_sf     -> eval_down(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b120) ) : histmap2017_mu_ss_sf     -> eval(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b120) );
                float lead_mu_3l_sf     = variationmu > 0 ? histmap2017_mu_3l_sf     -> eval_up(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b120) ) : variationmu < 0 ? histmap2017_mu_3l_sf     -> eval_down(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b120) ) : histmap2017_mu_3l_sf     -> eval(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b120) );
                float subl_mu_3l_sf     = variationmu > 0 ? histmap2017_mu_3l_sf     -> eval_up(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b120) ) : variationmu < 0 ? histmap2017_mu_3l_sf     -> eval_down(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b120) ) : histmap2017_mu_3l_sf     -> eval(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b120) );
                float tert_mu_3l_sf     = variationmu > 0 ? histmap2017_mu_3l_sf     -> eval_up(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b120) ) : variationmu < 0 ? histmap2017_mu_3l_sf     -> eval_down(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b120) ) : histmap2017_mu_3l_sf     -> eval(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b120) );
                float lead_el_veto_sf   = variationel > 0 ? histmap2017_el_veto_sf   -> eval_up(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b500) ) : variationel < 0 ? histmap2017_el_veto_sf   -> eval_down(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b500) ) : histmap2017_el_veto_sf   -> eval(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b500) );
                float subl_el_veto_sf   = variationel > 0 ? histmap2017_el_veto_sf   -> eval_up(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b500) ) : variationel < 0 ? histmap2017_el_veto_sf   -> eval_down(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b500) ) : histmap2017_el_veto_sf   -> eval(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b500) );
                float tert_el_veto_sf   = variationel > 0 ? histmap2017_el_veto_sf   -> eval_up(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b500) ) : variationel < 0 ? histmap2017_el_veto_sf   -> eval_down(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b500) ) : histmap2017_el_veto_sf   -> eval(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b500) );
                float lead_el_ss_sf     = variationel > 0 ? histmap2017_el_ss_sf     -> eval_up(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b500) ) : variationel < 0 ? histmap2017_el_ss_sf     -> eval_down(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b500) ) : histmap2017_el_ss_sf     -> eval(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b500) );
                float subl_el_ss_sf     = variationel > 0 ? histmap2017_el_ss_sf     -> eval_up(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b500) ) : variationel < 0 ? histmap2017_el_ss_sf     -> eval_down(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b500) ) : histmap2017_el_ss_sf     -> eval(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b500) );
                float tert_el_ss_sf     = variationel > 0 ? histmap2017_el_ss_sf     -> eval_up(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b500) ) : variationel < 0 ? histmap2017_el_ss_sf     -> eval_down(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b500) ) : histmap2017_el_ss_sf     -> eval(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b500) );
                float lead_el_3l_sf     = variationel > 0 ? histmap2017_el_3l_sf     -> eval_up(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b500) ) : variationel < 0 ? histmap2017_el_3l_sf     -> eval_down(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b500) ) : histmap2017_el_3l_sf     -> eval(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b500) );
                float subl_el_3l_sf     = variationel > 0 ? histmap2017_el_3l_sf     -> eval_up(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b500) ) : variationel < 0 ? histmap2017_el_3l_sf     -> eval_down(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b500) ) : histmap2017_el_3l_sf     -> eval(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b500) );
                float tert_el_3l_sf     = variationel > 0 ? histmap2017_el_3l_sf     -> eval_up(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b500) ) : variationel < 0 ? histmap2017_el_3l_sf     -> eval_down(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b500) ) : histmap2017_el_3l_sf     -> eval(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b500) );

                //temp until mva WPLoose is there
                lead_el_mva_sf = 1.;
                subl_el_mva_sf = 1.;
                tert_el_mva_sf = 1.;

                float frst_el_ss_sf = lead_el_recoid_sf * lead_el_mva_sf * lead_el_veto_sf * lead_el_ss_sf;
                float scnd_el_ss_sf = subl_el_recoid_sf * subl_el_mva_sf * subl_el_veto_sf * subl_el_ss_sf;
                float thrd_el_ss_sf = tert_el_recoid_sf * tert_el_mva_sf * tert_el_veto_sf * tert_el_ss_sf;
                float frst_el_3l_sf = lead_el_recoid_sf * lead_el_mva_sf * lead_el_veto_sf * lead_el_3l_sf;
                float scnd_el_3l_sf = subl_el_recoid_sf * subl_el_mva_sf * subl_el_veto_sf * subl_el_3l_sf;
                float thrd_el_3l_sf = tert_el_recoid_sf * tert_el_mva_sf * tert_el_veto_sf * tert_el_3l_sf;
                float frst_mu_ss_sf = lead_mu_recoid_sf * lead_mu_veto_sf * lead_mu_ss_sf;
                float scnd_mu_ss_sf = subl_mu_recoid_sf * subl_mu_veto_sf * subl_mu_ss_sf;
                float thrd_mu_ss_sf = tert_mu_recoid_sf * tert_mu_veto_sf * tert_mu_ss_sf;
                float frst_mu_3l_sf = lead_mu_recoid_sf * lead_mu_veto_sf * lead_mu_3l_sf;
                float scnd_mu_3l_sf = subl_mu_recoid_sf * subl_mu_veto_sf * subl_mu_3l_sf;
                float thrd_mu_3l_sf = tert_mu_recoid_sf * tert_mu_veto_sf * tert_mu_3l_sf;
                
                // **** Over writing previous scale factors with Jonas' scale factors **** //
                // **** Over writing previous scale factors with Jonas' scale factors **** //
                // **** Over writing previous scale factors with Jonas' scale factors **** //
                // CODE COULD BE CLEANER //
                if (variationel >  0) frst_el_ss_sf = electronScaleFactors(input.year, LeptonID::SameSign, www.lep_eta()[1], min((double)www.lep_pt()[1],b500), SystematicVariation::Up);
                if (variationel <  0) frst_el_ss_sf = electronScaleFactors(input.year, LeptonID::SameSign, www.lep_eta()[1], min((double)www.lep_pt()[1],b500), SystematicVariation::Down);
                if (variationel == 0) frst_el_ss_sf = electronScaleFactors(input.year, LeptonID::SameSign, www.lep_eta()[1], min((double)www.lep_pt()[1],b500), SystematicVariation::Nominal);

                if (variationel >  0) scnd_el_ss_sf = electronScaleFactors(input.year, LeptonID::SameSign, www.lep_eta()[1], min((double)www.lep_pt()[1],b500), SystematicVariation::Up);
                if (variationel <  0) scnd_el_ss_sf = electronScaleFactors(input.year, LeptonID::SameSign, www.lep_eta()[1], min((double)www.lep_pt()[1],b500), SystematicVariation::Down);
                if (variationel == 0) scnd_el_ss_sf = electronScaleFactors(input.year, LeptonID::SameSign, www.lep_eta()[1], min((double)www.lep_pt()[1],b500), SystematicVariation::Nominal);

                if (www.nVlep() == 3)
                {
                    if (variationel >  0) thrd_el_ss_sf = electronScaleFactors(input.year, LeptonID::SameSign, www.lep_eta()[2], min((double)www.lep_pt()[2],b500), SystematicVariation::Up);
                    if (variationel <  0) thrd_el_ss_sf = electronScaleFactors(input.year, LeptonID::SameSign, www.lep_eta()[2], min((double)www.lep_pt()[2],b500), SystematicVariation::Down);
                    if (variationel == 0) thrd_el_ss_sf = electronScaleFactors(input.year, LeptonID::SameSign, www.lep_eta()[2], min((double)www.lep_pt()[2],b500), SystematicVariation::Nominal);
                }

                if (variationel >  0) frst_el_3l_sf = electronScaleFactors(input.year, LeptonID::SameSign, www.lep_eta()[1], min((double)www.lep_pt()[1],b500), SystematicVariation::Up);
                if (variationel <  0) frst_el_3l_sf = electronScaleFactors(input.year, LeptonID::SameSign, www.lep_eta()[1], min((double)www.lep_pt()[1],b500), SystematicVariation::Down);
                if (variationel == 0) frst_el_3l_sf = electronScaleFactors(input.year, LeptonID::SameSign, www.lep_eta()[1], min((double)www.lep_pt()[1],b500), SystematicVariation::Nominal);

                if (variationel >  0) scnd_el_3l_sf = electronScaleFactors(input.year, LeptonID::SameSign, www.lep_eta()[1], min((double)www.lep_pt()[1],b500), SystematicVariation::Up);
                if (variationel <  0) scnd_el_3l_sf = electronScaleFactors(input.year, LeptonID::SameSign, www.lep_eta()[1], min((double)www.lep_pt()[1],b500), SystematicVariation::Down);
                if (variationel == 0) scnd_el_3l_sf = electronScaleFactors(input.year, LeptonID::SameSign, www.lep_eta()[1], min((double)www.lep_pt()[1],b500), SystematicVariation::Nominal);

                if (www.nVlep() == 3)
                {
                    if (variationel >  0) thrd_el_3l_sf = electronScaleFactors(input.year, LeptonID::SameSign, www.lep_eta()[1], min((double)www.lep_pt()[1],b500), SystematicVariation::Up);
                    if (variationel <  0) thrd_el_3l_sf = electronScaleFactors(input.year, LeptonID::SameSign, www.lep_eta()[1], min((double)www.lep_pt()[1],b500), SystematicVariation::Down);
                    if (variationel == 0) thrd_el_3l_sf = electronScaleFactors(input.year, LeptonID::SameSign, www.lep_eta()[1], min((double)www.lep_pt()[1],b500), SystematicVariation::Nominal);
                }

                // Scale factors
                if (www.nVlep() == 2)
                {
                    if (abs(www.lep_pdgId()[0]) * abs(www.lep_pdgId()[1]) == 121)
                    {
                      return (doFakeEstimation ? 1. : (frst_el_ss_sf * scnd_el_ss_sf));
                    }
                    else if (abs(www.lep_pdgId()[0]) * abs(www.lep_pdgId()[1]) == 143)
                    {
                        if(abs(www.lep_pdgId()[0])==11){
                           return (doFakeEstimation ? 1. : (frst_el_ss_sf * scnd_mu_ss_sf));
                        }
                        else {
                           return (doFakeEstimation ? 1. : (frst_mu_ss_sf * scnd_el_ss_sf));
                        }
                    }
                    else if (abs(www.lep_pdgId()[0]) * abs(www.lep_pdgId()[1]) == 169)
                    {
                        return (doFakeEstimation ? 1. : (frst_mu_ss_sf * scnd_mu_ss_sf));
                    }
                    else
                    {
                        std::cout << "Error: should not be here " << __FUNCTION__ << std::endl;
                        return 1;
                    }
                }
                else if (www.nVlep() == 3)
                {
                    float threelep_sf = 1.;
                    if(www.nSFOS()==0 && ((abs(www.lep_pdgId()[0])+abs(www.lep_pdgId()[1])+abs(www.lep_pdgId()[2])) == 35)){//eem
                        threelep_sf = ((abs(www.lep_pdgId()[0])==11)*(frst_el_ss_sf)+(abs(www.lep_pdgId()[0])!=11)*(frst_mu_3l_sf))
                          *((abs(www.lep_pdgId()[1])==11)*(scnd_el_ss_sf)+(abs(www.lep_pdgId()[1])!=11)*(scnd_mu_3l_sf))
                          *((abs(www.lep_pdgId()[2])==11)*(thrd_el_ss_sf)+(abs(www.lep_pdgId()[2])!=11)*(thrd_mu_3l_sf));
                    }
                    else if(www.nSFOS()==0 && ((abs(www.lep_pdgId()[0])+abs(www.lep_pdgId()[1])+abs(www.lep_pdgId()[2])) == 37)){//emm
                        threelep_sf = ((abs(www.lep_pdgId()[0])==11)*(frst_el_3l_sf)+(abs(www.lep_pdgId()[0])!=11)*(frst_mu_ss_sf))
                          *((abs(www.lep_pdgId()[1])==11)*(scnd_el_3l_sf)+(abs(www.lep_pdgId()[1])!=11)*(scnd_mu_ss_sf))
                          *((abs(www.lep_pdgId()[2])==11)*(thrd_el_3l_sf)+(abs(www.lep_pdgId()[2])!=11)*(thrd_mu_ss_sf));
                    }
                    else {
                        threelep_sf = ((abs(www.lep_pdgId()[0])==11)*(frst_el_3l_sf)+(abs(www.lep_pdgId()[0])!=11)*(frst_mu_3l_sf))
                          *((abs(www.lep_pdgId()[1])==11)*(scnd_el_3l_sf)+(abs(www.lep_pdgId()[1])!=11)*(scnd_mu_3l_sf))
                          *((abs(www.lep_pdgId()[2])==11)*(thrd_el_3l_sf)+(abs(www.lep_pdgId()[2])!=11)*(thrd_mu_3l_sf));
                    }
                    return (doFakeEstimation ? 1. : (threelep_sf));
                }
                else
                {
                    return 1;
                }

            }
            else if (year == 2016)
            {
                const double b500 = 499.9;
                const double b120 = 119.9;
                float lead_mu_recoid_GH_sf = variationmu > 0 ? histmap2016_mu_recoid_GH_sf -> eval_up(   ((double)www.lep_eta()[0]),min((double)www.lep_pt()[0],b120)        ) : variationmu < 0 ? histmap2016_mu_recoid_GH_sf -> eval_down(   ((double)www.lep_eta()[0]),min((double)www.lep_pt()[0],b120)        ) : histmap2016_mu_recoid_GH_sf -> eval(   ((double)www.lep_eta()[0]),min((double)www.lep_pt()[0],b120)        );
                float subl_mu_recoid_GH_sf = variationmu > 0 ? histmap2016_mu_recoid_GH_sf -> eval_up(   ((double)www.lep_eta()[1]),min((double)www.lep_pt()[1],b120)        ) : variationmu < 0 ? histmap2016_mu_recoid_GH_sf -> eval_down(   ((double)www.lep_eta()[1]),min((double)www.lep_pt()[2],b120)        ) : histmap2016_mu_recoid_GH_sf -> eval(   ((double)www.lep_eta()[1]),min((double)www.lep_pt()[1],b120)        );
                float tert_mu_recoid_GH_sf = variationmu > 0 ? histmap2016_mu_recoid_GH_sf -> eval_up(   ((double)www.lep_eta()[2]),min((double)www.lep_pt()[2],b120)        ) : variationmu < 0 ? histmap2016_mu_recoid_GH_sf -> eval_down(   ((double)www.lep_eta()[1]),min((double)www.lep_pt()[2],b120)        ) : histmap2016_mu_recoid_GH_sf -> eval(   ((double)www.lep_eta()[2]),min((double)www.lep_pt()[2],b120)        );
                float lead_mu_recoid_sf = variationmu > 0 ? histmap2016_mu_recoid_sf -> eval_up(   ((double)www.lep_eta()[0]),min((double)www.lep_pt()[0],b120)        ) : variationmu < 0 ? histmap2016_mu_recoid_sf -> eval_down(   ((double)www.lep_eta()[0]),min((double)www.lep_pt()[0],b120)        ) : histmap2016_mu_recoid_sf -> eval(   ((double)www.lep_eta()[0]),min((double)www.lep_pt()[0],b120)        );
                float subl_mu_recoid_sf = variationmu > 0 ? histmap2016_mu_recoid_sf -> eval_up(   ((double)www.lep_eta()[1]),min((double)www.lep_pt()[1],b120)        ) : variationmu < 0 ? histmap2016_mu_recoid_sf -> eval_down(   ((double)www.lep_eta()[1]),min((double)www.lep_pt()[2],b120)        ) : histmap2016_mu_recoid_sf -> eval(   ((double)www.lep_eta()[1]),min((double)www.lep_pt()[1],b120)        );
                float tert_mu_recoid_sf = variationmu > 0 ? histmap2016_mu_recoid_sf -> eval_up(   ((double)www.lep_eta()[2]),min((double)www.lep_pt()[2],b120)        ) : variationmu < 0 ? histmap2016_mu_recoid_sf -> eval_down(   ((double)www.lep_eta()[1]),min((double)www.lep_pt()[2],b120)        ) : histmap2016_mu_recoid_sf -> eval(   ((double)www.lep_eta()[2]),min((double)www.lep_pt()[2],b120)        );
                float lead_el_recoid_sf = variationel > 0 ? histmap2016_el_recoid_sf -> eval_up(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b500) ) : variationel < 0 ? histmap2016_el_recoid_sf -> eval_down(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b500) ) : histmap2016_el_recoid_sf -> eval(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b500) );
                float subl_el_recoid_sf = variationel > 0 ? histmap2016_el_recoid_sf -> eval_up(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b500) ) : variationel < 0 ? histmap2016_el_recoid_sf -> eval_down(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b500) ) : histmap2016_el_recoid_sf -> eval(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b500) );
                float tert_el_recoid_sf = variationel > 0 ? histmap2016_el_recoid_sf -> eval_up(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b500) ) : variationel < 0 ? histmap2016_el_recoid_sf -> eval_down(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b500) ) : histmap2016_el_recoid_sf -> eval(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b500) );
                float lead_el_mva_sf    = variationel > 0 ? histmap2016_el_mva_sf    -> eval_up(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b500) ) : variationel < 0 ? histmap2016_el_mva_sf    -> eval_down(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b500) ) : histmap2016_el_mva_sf    -> eval(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b500) );
                float subl_el_mva_sf    = variationel > 0 ? histmap2016_el_mva_sf    -> eval_up(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b500) ) : variationel < 0 ? histmap2016_el_mva_sf    -> eval_down(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b500) ) : histmap2016_el_mva_sf    -> eval(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b500) );
                float tert_el_mva_sf    = variationel > 0 ? histmap2016_el_mva_sf    -> eval_up(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b500) ) : variationel < 0 ? histmap2016_el_mva_sf    -> eval_down(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b500) ) : histmap2016_el_mva_sf    -> eval(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b500) );
                float lead_mu_veto_sf   = variationmu > 0 ? histmap2016_mu_veto_sf   -> eval_up(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b120) ) : variationmu < 0 ? histmap2016_mu_veto_sf   -> eval_down(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b120) ) : histmap2016_mu_veto_sf   -> eval(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b120) );
                float subl_mu_veto_sf   = variationmu > 0 ? histmap2016_mu_veto_sf   -> eval_up(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b120) ) : variationmu < 0 ? histmap2016_mu_veto_sf   -> eval_down(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b120) ) : histmap2016_mu_veto_sf   -> eval(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b120) );
                float tert_mu_veto_sf   = variationmu > 0 ? histmap2016_mu_veto_sf   -> eval_up(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b120) ) : variationmu < 0 ? histmap2016_mu_veto_sf   -> eval_down(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b120) ) : histmap2016_mu_veto_sf   -> eval(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b120) );
                float lead_mu_ss_sf     = variationmu > 0 ? histmap2016_mu_ss_sf     -> eval_up(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b120) ) : variationmu < 0 ? histmap2016_mu_ss_sf     -> eval_down(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b120) ) : histmap2016_mu_ss_sf     -> eval(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b120) );
                float subl_mu_ss_sf     = variationmu > 0 ? histmap2016_mu_ss_sf     -> eval_up(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b120) ) : variationmu < 0 ? histmap2016_mu_ss_sf     -> eval_down(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b120) ) : histmap2016_mu_ss_sf     -> eval(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b120) );
                float tert_mu_ss_sf     = variationmu > 0 ? histmap2016_mu_ss_sf     -> eval_up(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b120) ) : variationmu < 0 ? histmap2016_mu_ss_sf     -> eval_down(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b120) ) : histmap2016_mu_ss_sf     -> eval(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b120) );
                float lead_mu_3l_sf     = variationmu > 0 ? histmap2016_mu_3l_sf     -> eval_up(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b120) ) : variationmu < 0 ? histmap2016_mu_3l_sf     -> eval_down(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b120) ) : histmap2016_mu_3l_sf     -> eval(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b120) );
                float subl_mu_3l_sf     = variationmu > 0 ? histmap2016_mu_3l_sf     -> eval_up(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b120) ) : variationmu < 0 ? histmap2016_mu_3l_sf     -> eval_down(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b120) ) : histmap2016_mu_3l_sf     -> eval(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b120) );
                float tert_mu_3l_sf     = variationmu > 0 ? histmap2016_mu_3l_sf     -> eval_up(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b120) ) : variationmu < 0 ? histmap2016_mu_3l_sf     -> eval_down(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b120) ) : histmap2016_mu_3l_sf     -> eval(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b120) );
                float lead_el_veto_sf   = variationel > 0 ? histmap2016_el_veto_sf   -> eval_up(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b500) ) : variationel < 0 ? histmap2016_el_veto_sf   -> eval_down(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b500) ) : histmap2016_el_veto_sf   -> eval(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b500) );
                float subl_el_veto_sf   = variationel > 0 ? histmap2016_el_veto_sf   -> eval_up(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b500) ) : variationel < 0 ? histmap2016_el_veto_sf   -> eval_down(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b500) ) : histmap2016_el_veto_sf   -> eval(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b500) );
                float tert_el_veto_sf   = variationel > 0 ? histmap2016_el_veto_sf   -> eval_up(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b500) ) : variationel < 0 ? histmap2016_el_veto_sf   -> eval_down(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b500) ) : histmap2016_el_veto_sf   -> eval(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b500) );
                float lead_el_ss_sf     = variationel > 0 ? histmap2016_el_ss_sf     -> eval_up(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b500) ) : variationel < 0 ? histmap2016_el_ss_sf     -> eval_down(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b500) ) : histmap2016_el_ss_sf     -> eval(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b500) );
                float subl_el_ss_sf     = variationel > 0 ? histmap2016_el_ss_sf     -> eval_up(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b500) ) : variationel < 0 ? histmap2016_el_ss_sf     -> eval_down(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b500) ) : histmap2016_el_ss_sf     -> eval(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b500) );
                float tert_el_ss_sf     = variationel > 0 ? histmap2016_el_ss_sf     -> eval_up(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b500) ) : variationel < 0 ? histmap2016_el_ss_sf     -> eval_down(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b500) ) : histmap2016_el_ss_sf     -> eval(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b500) );
                float lead_el_3l_sf     = variationel > 0 ? histmap2016_el_3l_sf     -> eval_up(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b500) ) : variationel < 0 ? histmap2016_el_3l_sf     -> eval_down(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b500) ) : histmap2016_el_3l_sf     -> eval(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b500) );
                float subl_el_3l_sf     = variationel > 0 ? histmap2016_el_3l_sf     -> eval_up(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b500) ) : variationel < 0 ? histmap2016_el_3l_sf     -> eval_down(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b500) ) : histmap2016_el_3l_sf     -> eval(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b500) );
                float tert_el_3l_sf     = variationel > 0 ? histmap2016_el_3l_sf     -> eval_up(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b500) ) : variationel < 0 ? histmap2016_el_3l_sf     -> eval_down(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b500) ) : histmap2016_el_3l_sf     -> eval(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b500) );

                //temp until mva WPLoose is there
                lead_el_mva_sf = 1.;
                subl_el_mva_sf = 1.;
                tert_el_mva_sf = 1.;

                float frst_el_ss_sf = lead_el_recoid_sf * lead_el_mva_sf * lead_el_veto_sf * lead_el_ss_sf;
                float scnd_el_ss_sf = subl_el_recoid_sf * subl_el_mva_sf * subl_el_veto_sf * subl_el_ss_sf;
                float thrd_el_ss_sf = tert_el_recoid_sf * tert_el_mva_sf * tert_el_veto_sf * tert_el_ss_sf;
                float frst_el_3l_sf = lead_el_recoid_sf * lead_el_mva_sf * lead_el_veto_sf * lead_el_3l_sf;
                float scnd_el_3l_sf = subl_el_recoid_sf * subl_el_mva_sf * subl_el_veto_sf * subl_el_3l_sf;
                float thrd_el_3l_sf = tert_el_recoid_sf * tert_el_mva_sf * tert_el_veto_sf * tert_el_3l_sf;
                float frst_mu_ss_sf = (0.550 * lead_mu_recoid_sf + 0.450 * lead_mu_recoid_GH_sf) * lead_mu_veto_sf * lead_mu_ss_sf;
                float scnd_mu_ss_sf = (0.550 * subl_mu_recoid_sf + 0.450 * subl_mu_recoid_GH_sf) * subl_mu_veto_sf * subl_mu_ss_sf;
                float thrd_mu_ss_sf = (0.550 * tert_mu_recoid_sf + 0.450 * tert_mu_recoid_GH_sf) * tert_mu_veto_sf * tert_mu_ss_sf;
                float frst_mu_3l_sf = (0.550 * lead_mu_recoid_sf + 0.450 * lead_mu_recoid_GH_sf) * lead_mu_veto_sf * lead_mu_3l_sf;
                float scnd_mu_3l_sf = (0.550 * subl_mu_recoid_sf + 0.450 * subl_mu_recoid_GH_sf) * subl_mu_veto_sf * subl_mu_3l_sf;
                float thrd_mu_3l_sf = (0.550 * tert_mu_recoid_sf + 0.450 * tert_mu_recoid_GH_sf) * tert_mu_veto_sf * tert_mu_3l_sf;

                // **** Over writing previous scale factors with Jonas' scale factors **** //
                // **** Over writing previous scale factors with Jonas' scale factors **** //
                // **** Over writing previous scale factors with Jonas' scale factors **** //
                // CODE COULD BE CLEANER //
                if (variationel >  0) frst_el_ss_sf = electronScaleFactors(input.year, LeptonID::SameSign, www.lep_eta()[1], min((double)www.lep_pt()[1],b500), SystematicVariation::Up);
                if (variationel <  0) frst_el_ss_sf = electronScaleFactors(input.year, LeptonID::SameSign, www.lep_eta()[1], min((double)www.lep_pt()[1],b500), SystematicVariation::Down);
                if (variationel == 0) frst_el_ss_sf = electronScaleFactors(input.year, LeptonID::SameSign, www.lep_eta()[1], min((double)www.lep_pt()[1],b500), SystematicVariation::Nominal);

                if (variationel >  0) scnd_el_ss_sf = electronScaleFactors(input.year, LeptonID::SameSign, www.lep_eta()[1], min((double)www.lep_pt()[1],b500), SystematicVariation::Up);
                if (variationel <  0) scnd_el_ss_sf = electronScaleFactors(input.year, LeptonID::SameSign, www.lep_eta()[1], min((double)www.lep_pt()[1],b500), SystematicVariation::Down);
                if (variationel == 0) scnd_el_ss_sf = electronScaleFactors(input.year, LeptonID::SameSign, www.lep_eta()[1], min((double)www.lep_pt()[1],b500), SystematicVariation::Nominal);

                if (www.nVlep() == 3)
                {
                    if (variationel >  0) thrd_el_ss_sf = electronScaleFactors(input.year, LeptonID::SameSign, www.lep_eta()[2], min((double)www.lep_pt()[2],b500), SystematicVariation::Up);
                    if (variationel <  0) thrd_el_ss_sf = electronScaleFactors(input.year, LeptonID::SameSign, www.lep_eta()[2], min((double)www.lep_pt()[2],b500), SystematicVariation::Down);
                    if (variationel == 0) thrd_el_ss_sf = electronScaleFactors(input.year, LeptonID::SameSign, www.lep_eta()[2], min((double)www.lep_pt()[2],b500), SystematicVariation::Nominal);
                }

                if (variationel >  0) frst_el_3l_sf = electronScaleFactors(input.year, LeptonID::SameSign, www.lep_eta()[1], min((double)www.lep_pt()[1],b500), SystematicVariation::Up);
                if (variationel <  0) frst_el_3l_sf = electronScaleFactors(input.year, LeptonID::SameSign, www.lep_eta()[1], min((double)www.lep_pt()[1],b500), SystematicVariation::Down);
                if (variationel == 0) frst_el_3l_sf = electronScaleFactors(input.year, LeptonID::SameSign, www.lep_eta()[1], min((double)www.lep_pt()[1],b500), SystematicVariation::Nominal);

                if (variationel >  0) scnd_el_3l_sf = electronScaleFactors(input.year, LeptonID::SameSign, www.lep_eta()[1], min((double)www.lep_pt()[1],b500), SystematicVariation::Up);
                if (variationel <  0) scnd_el_3l_sf = electronScaleFactors(input.year, LeptonID::SameSign, www.lep_eta()[1], min((double)www.lep_pt()[1],b500), SystematicVariation::Down);
                if (variationel == 0) scnd_el_3l_sf = electronScaleFactors(input.year, LeptonID::SameSign, www.lep_eta()[1], min((double)www.lep_pt()[1],b500), SystematicVariation::Nominal);

                if (www.nVlep() == 3)
                {
                    if (variationel >  0) thrd_el_3l_sf = electronScaleFactors(input.year, LeptonID::SameSign, www.lep_eta()[1], min((double)www.lep_pt()[1],b500), SystematicVariation::Up);
                    if (variationel <  0) thrd_el_3l_sf = electronScaleFactors(input.year, LeptonID::SameSign, www.lep_eta()[1], min((double)www.lep_pt()[1],b500), SystematicVariation::Down);
                    if (variationel == 0) thrd_el_3l_sf = electronScaleFactors(input.year, LeptonID::SameSign, www.lep_eta()[1], min((double)www.lep_pt()[1],b500), SystematicVariation::Nominal);
                }

                // Scale factors
                if (www.nVlep() == 2)
                {
                    if (abs(www.lep_pdgId()[0]) * abs(www.lep_pdgId()[1]) == 121)
                    {
                      return (doFakeEstimation ? 1. : (frst_el_ss_sf * scnd_el_ss_sf));
                    }
                    else if (abs(www.lep_pdgId()[0]) * abs(www.lep_pdgId()[1]) == 143)
                    {
                        if(abs(www.lep_pdgId()[0])==11){
                           return (doFakeEstimation ? 1. : (frst_el_ss_sf * scnd_mu_ss_sf));
                        }
                        else {
                           return (doFakeEstimation ? 1. : (frst_mu_ss_sf * scnd_el_ss_sf));
                        }
                    }
                    else if (abs(www.lep_pdgId()[0]) * abs(www.lep_pdgId()[1]) == 169)
                    {
                        return (doFakeEstimation ? 1. : (frst_mu_ss_sf * scnd_mu_ss_sf));
                    }
                    else
                    {
                        std::cout << "Error: should not be here " << __FUNCTION__ << std::endl;
                        return 1;
                    }
                }
                else if (www.nVlep() == 3)
                {
                    float threelep_sf = 1.;
                    if(www.nSFOS()==0 && ((abs(www.lep_pdgId()[0])+abs(www.lep_pdgId()[1])+abs(www.lep_pdgId()[2])) == 35)){//eem
                        threelep_sf = ((abs(www.lep_pdgId()[0])==11)*(frst_el_ss_sf)+(abs(www.lep_pdgId()[0])!=11)*(frst_mu_3l_sf))
                          *((abs(www.lep_pdgId()[1])==11)*(scnd_el_ss_sf)+(abs(www.lep_pdgId()[1])!=11)*(scnd_mu_3l_sf))
                          *((abs(www.lep_pdgId()[2])==11)*(thrd_el_ss_sf)+(abs(www.lep_pdgId()[2])!=11)*(thrd_mu_3l_sf));
                    }
                    else if(www.nSFOS()==0 && ((abs(www.lep_pdgId()[0])+abs(www.lep_pdgId()[1])+abs(www.lep_pdgId()[2])) == 37)){//emm
                        threelep_sf = ((abs(www.lep_pdgId()[0])==11)*(frst_el_3l_sf)+(abs(www.lep_pdgId()[0])!=11)*(frst_mu_ss_sf))
                          *((abs(www.lep_pdgId()[1])==11)*(scnd_el_3l_sf)+(abs(www.lep_pdgId()[1])!=11)*(scnd_mu_ss_sf))
                          *((abs(www.lep_pdgId()[2])==11)*(thrd_el_3l_sf)+(abs(www.lep_pdgId()[2])!=11)*(thrd_mu_ss_sf));
                    }
                    else {
                        threelep_sf = ((abs(www.lep_pdgId()[0])==11)*(frst_el_3l_sf)+(abs(www.lep_pdgId()[0])!=11)*(frst_mu_3l_sf))
                          *((abs(www.lep_pdgId()[1])==11)*(scnd_el_3l_sf)+(abs(www.lep_pdgId()[1])!=11)*(scnd_mu_3l_sf))
                          *((abs(www.lep_pdgId()[2])==11)*(thrd_el_3l_sf)+(abs(www.lep_pdgId()[2])!=11)*(thrd_mu_3l_sf));
                    }
                    return (doFakeEstimation ? 1. : (threelep_sf));
                }
                else
                {
                    return 1;
                }

            }
            else
            {
                // Set the lepton scale factors based on
                std::cout << "Error: should not be here " << __FUNCTION__ << std::endl;
                return 1;
            }
        }
};

//_______________________________________________________________________________________________________
class FakeRates
{
    public:
        RooUtil::HistMap* histmap_fr_ss_el;
        RooUtil::HistMap* histmap_fr_ss_mu;
        RooUtil::HistMap* histmap_fr_3l_el;
        RooUtil::HistMap* histmap_fr_3l_mu;
        RooUtil::HistMap* histmap_fr_3l_el_medium;
        RooUtil::HistMap* histmap_fr_3l_mu_medium;
        RooUtil::HistMap* histmap_fr_ss_el_closure;
        RooUtil::HistMap* histmap_fr_ss_mu_closure;
        RooUtil::HistMap* histmap_fr_3l_el_closure;
        RooUtil::HistMap* histmap_fr_3l_mu_closure;
        RooUtil::HistMap* histmap_fr_3l_el_medium_closure;
        RooUtil::HistMap* histmap_fr_3l_mu_medium_closure;

        RooUtil::HistMap* histmap_2016_fr_ss_el;
        RooUtil::HistMap* histmap_2016_fr_ss_mu;
        RooUtil::HistMap* histmap_2016_fr_3l_el;
        RooUtil::HistMap* histmap_2016_fr_3l_mu;
        RooUtil::HistMap* histmap_2016_fr_3l_el_medium;
        RooUtil::HistMap* histmap_2016_fr_3l_mu_medium;
        RooUtil::HistMap* histmap_2016_fr_ss_el_closure;
        RooUtil::HistMap* histmap_2016_fr_ss_mu_closure;
        RooUtil::HistMap* histmap_2016_fr_3l_el_closure;
        RooUtil::HistMap* histmap_2016_fr_3l_mu_closure;
        RooUtil::HistMap* histmap_2016_fr_3l_el_medium_closure;
        RooUtil::HistMap* histmap_2016_fr_3l_mu_medium_closure;

        RooUtil::HistMap* histmap_2017_fr_ss_el;
        RooUtil::HistMap* histmap_2017_fr_ss_mu;
        RooUtil::HistMap* histmap_2017_fr_3l_el;
        RooUtil::HistMap* histmap_2017_fr_3l_mu;
        RooUtil::HistMap* histmap_2017_fr_3l_el_medium;
        RooUtil::HistMap* histmap_2017_fr_3l_mu_medium;
        RooUtil::HistMap* histmap_2017_fr_ss_el_closure;
        RooUtil::HistMap* histmap_2017_fr_ss_mu_closure;
        RooUtil::HistMap* histmap_2017_fr_3l_el_closure;
        RooUtil::HistMap* histmap_2017_fr_3l_mu_closure;
        RooUtil::HistMap* histmap_2017_fr_3l_el_medium_closure;
        RooUtil::HistMap* histmap_2017_fr_3l_mu_medium_closure;

        RooUtil::HistMap* histmap_2018_fr_ss_el;
        RooUtil::HistMap* histmap_2018_fr_ss_mu;
        RooUtil::HistMap* histmap_2018_fr_3l_el;
        RooUtil::HistMap* histmap_2018_fr_3l_mu;
        RooUtil::HistMap* histmap_2018_fr_3l_el_medium;
        RooUtil::HistMap* histmap_2018_fr_3l_mu_medium;
        RooUtil::HistMap* histmap_2018_fr_ss_el_closure;
        RooUtil::HistMap* histmap_2018_fr_ss_mu_closure;
        RooUtil::HistMap* histmap_2018_fr_3l_el_closure;
        RooUtil::HistMap* histmap_2018_fr_3l_mu_closure;
        RooUtil::HistMap* histmap_2018_fr_3l_el_medium_closure;
        RooUtil::HistMap* histmap_2018_fr_3l_mu_medium_closure;

        const float muiso_ss_thresh = 0.04;
        const float eliso_ss_thresh = 0.05;
        const float muiso_3l_thresh = 0.04;
        const float eliso_3l_thresh = 0.05;

        float closure_tight_ss_e ;
        float closure_tight_ss_m ;
        float closure_tight_3l_e ;
        float closure_tight_3l_m ;
        float closure_medium_3l_e;
        float closure_medium_3l_m;

        FakeRates()
        {
            histmap_fr_ss_el = 0;
            histmap_fr_ss_mu = 0;
            histmap_fr_3l_el = 0;
            histmap_fr_3l_mu = 0;
            histmap_fr_ss_el_closure = 0;
            histmap_fr_ss_mu_closure = 0;
            histmap_fr_3l_el_closure = 0;
            histmap_fr_3l_mu_closure = 0;

            histmap_2016_fr_ss_el = 0;
            histmap_2016_fr_ss_mu = 0;
            histmap_2016_fr_3l_el = 0;
            histmap_2016_fr_3l_mu = 0;
            histmap_2016_fr_3l_el_medium = 0;
            histmap_2016_fr_3l_mu_medium = 0;
            histmap_2016_fr_ss_el_closure = 0;
            histmap_2016_fr_ss_mu_closure = 0;
            histmap_2016_fr_3l_el_closure = 0;
            histmap_2016_fr_3l_mu_closure = 0;
            histmap_2016_fr_3l_el_medium_closure = 0;
            histmap_2016_fr_3l_mu_medium_closure = 0;

            histmap_2017_fr_ss_el = 0;
            histmap_2017_fr_ss_mu = 0;
            histmap_2017_fr_3l_el = 0;
            histmap_2017_fr_3l_mu = 0;
            histmap_2017_fr_3l_el_medium = 0;
            histmap_2017_fr_3l_mu_medium = 0;
            histmap_2017_fr_ss_el_closure = 0;
            histmap_2017_fr_ss_mu_closure = 0;
            histmap_2017_fr_3l_el_closure = 0;
            histmap_2017_fr_3l_mu_closure = 0;
            histmap_2017_fr_3l_el_medium_closure = 0;
            histmap_2017_fr_3l_mu_medium_closure = 0;

            histmap_2018_fr_ss_el = 0;
            histmap_2018_fr_ss_mu = 0;
            histmap_2018_fr_3l_el = 0;
            histmap_2018_fr_3l_mu = 0;
            histmap_2018_fr_3l_el_medium = 0;
            histmap_2018_fr_3l_mu_medium = 0;
            histmap_2018_fr_ss_el_closure = 0;
            histmap_2018_fr_ss_mu_closure = 0;
            histmap_2018_fr_3l_el_closure = 0;
            histmap_2018_fr_3l_mu_closure = 0;
            histmap_2018_fr_3l_el_medium_closure = 0;
            histmap_2018_fr_3l_mu_medium_closure = 0;

        }

        ~FakeRates()
        {
            delete histmap_fr_ss_el;
            delete histmap_fr_ss_mu;
            delete histmap_fr_3l_el;
            delete histmap_fr_3l_mu;
            delete histmap_fr_3l_el_medium;
            delete histmap_fr_3l_mu_medium;
            delete histmap_fr_ss_el_closure;
            delete histmap_fr_ss_mu_closure;
            delete histmap_fr_3l_el_closure;
            delete histmap_fr_3l_mu_closure;
            delete histmap_fr_3l_el_medium_closure;
            delete histmap_fr_3l_mu_medium_closure;
        }

        void load2016()
        {
            if (not histmap_2016_fr_ss_el        ) histmap_2016_fr_ss_el         = new RooUtil::HistMap("/nfs-7/userdata/phchang/scalefactors/FR_v5.3.2/fakerate_2016_ss.root:El_ptcorretarolled_data_fakerate");
            if (not histmap_2016_fr_ss_mu        ) histmap_2016_fr_ss_mu         = new RooUtil::HistMap("/nfs-7/userdata/phchang/scalefactors/FR_v5.3.2/fakerate_2016_ss.root:Mu_ptcorretarolled_data_fakerate");
            if (not histmap_2016_fr_3l_el        ) histmap_2016_fr_3l_el         = new RooUtil::HistMap("/nfs-7/userdata/phchang/scalefactors/FR_v5.3.2/fakerate_2016_3l.root:El_ptcorretarolled_data_fakerate");
            if (not histmap_2016_fr_3l_mu        ) histmap_2016_fr_3l_mu         = new RooUtil::HistMap("/nfs-7/userdata/phchang/scalefactors/FR_v5.3.2/fakerate_2016_3l.root:Mu_ptcorretarolled_data_fakerate");
            if (not histmap_2016_fr_ss_el_closure) histmap_2016_fr_ss_el_closure = new RooUtil::HistMap("/nfs-7/userdata/phchang/scalefactors/FR_v5.3.2/fakerate_2016_ss.root:El_ptcorretarolled_data_fakerateclosure");
            if (not histmap_2016_fr_ss_mu_closure) histmap_2016_fr_ss_mu_closure = new RooUtil::HistMap("/nfs-7/userdata/phchang/scalefactors/FR_v5.3.2/fakerate_2016_ss.root:Mu_ptcorretarolled_data_fakerateclosure");
            if (not histmap_2016_fr_3l_el_medium        ) histmap_2016_fr_3l_el_medium         = new RooUtil::HistMap("/nfs-7/userdata/phchang/scalefactors/FR_v5.3.2/fakerate_2016_3l_medium.root:El_ptcorretarolled_data_fakerate");
            if (not histmap_2016_fr_3l_mu_medium        ) histmap_2016_fr_3l_mu_medium         = new RooUtil::HistMap("/nfs-7/userdata/phchang/scalefactors/FR_v5.3.2/fakerate_2016_3l_medium.root:Mu_ptcorretarolled_data_fakerate");
            if (not histmap_2016_fr_3l_el_medium_closure) histmap_2016_fr_3l_el_medium_closure = new RooUtil::HistMap("/nfs-7/userdata/phchang/scalefactors/FR_v5.3.2/fakerate_2016_3l_medium.root:El_ptcorretarolled_data_fakerateclosure");
            if (not histmap_2016_fr_3l_mu_medium_closure) histmap_2016_fr_3l_mu_medium_closure = new RooUtil::HistMap("/nfs-7/userdata/phchang/scalefactors/FR_v5.3.2/fakerate_2016_3l_medium.root:Mu_ptcorretarolled_data_fakerateclosure");
            histmap_fr_ss_el         = histmap_2016_fr_ss_el;
            histmap_fr_ss_mu         = histmap_2016_fr_ss_mu;
            histmap_fr_3l_el         = histmap_2016_fr_3l_el;
            histmap_fr_3l_mu         = histmap_2016_fr_3l_mu;
            histmap_fr_ss_el_closure = histmap_2016_fr_ss_el_closure;
            histmap_fr_ss_mu_closure = histmap_2016_fr_ss_mu_closure;
            histmap_fr_3l_el_closure = histmap_2016_fr_3l_el_closure;
            histmap_fr_3l_mu_closure = histmap_2016_fr_3l_mu_closure;
            histmap_fr_3l_el_medium         = histmap_2016_fr_3l_el_medium;
            histmap_fr_3l_mu_medium         = histmap_2016_fr_3l_mu_medium;
            histmap_fr_3l_el_medium_closure = histmap_2016_fr_3l_el_medium_closure;
            histmap_fr_3l_mu_medium_closure = histmap_2016_fr_3l_mu_medium_closure;
            closure_tight_ss_e  = 0.27;
            closure_tight_ss_m  = 0.40;
            closure_tight_3l_e  = 0.14;
            closure_tight_3l_m  = 0.32;
            closure_medium_3l_e = 0.12;
            closure_medium_3l_m = 0.17;

        }

        void load2017()
        {
            if (not histmap_2017_fr_ss_el        ) histmap_2017_fr_ss_el         = new RooUtil::HistMap("/nfs-7/userdata/phchang/scalefactors/FR_v5.3.2/fakerate_2017_ss.root:El_ptcorretarolled_data_fakerate");
            if (not histmap_2017_fr_ss_mu        ) histmap_2017_fr_ss_mu         = new RooUtil::HistMap("/nfs-7/userdata/phchang/scalefactors/FR_v5.3.2/fakerate_2017_ss.root:Mu_ptcorretarolled_data_fakerate");
            if (not histmap_2017_fr_3l_el        ) histmap_2017_fr_3l_el         = new RooUtil::HistMap("/nfs-7/userdata/phchang/scalefactors/FR_v5.3.2/fakerate_2017_3l.root:El_ptcorretarolled_data_fakerate");
            if (not histmap_2017_fr_3l_mu        ) histmap_2017_fr_3l_mu         = new RooUtil::HistMap("/nfs-7/userdata/phchang/scalefactors/FR_v5.3.2/fakerate_2017_3l.root:Mu_ptcorretarolled_data_fakerate");
            if (not histmap_2017_fr_ss_el_closure) histmap_2017_fr_ss_el_closure = new RooUtil::HistMap("/nfs-7/userdata/phchang/scalefactors/FR_v5.3.2/fakerate_2017_ss.root:El_ptcorretarolled_data_fakerateclosure");
            if (not histmap_2017_fr_ss_mu_closure) histmap_2017_fr_ss_mu_closure = new RooUtil::HistMap("/nfs-7/userdata/phchang/scalefactors/FR_v5.3.2/fakerate_2017_ss.root:Mu_ptcorretarolled_data_fakerateclosure");
            if (not histmap_2017_fr_3l_el_closure) histmap_2017_fr_3l_el_closure = new RooUtil::HistMap("/nfs-7/userdata/phchang/scalefactors/FR_v5.3.2/fakerate_2017_3l.root:El_ptcorretarolled_data_fakerateclosure");
            if (not histmap_2017_fr_3l_mu_closure) histmap_2017_fr_3l_mu_closure = new RooUtil::HistMap("/nfs-7/userdata/phchang/scalefactors/FR_v5.3.2/fakerate_2017_3l.root:Mu_ptcorretarolled_data_fakerateclosure");
            if (not histmap_2017_fr_3l_el_medium        ) histmap_2017_fr_3l_el_medium         = new RooUtil::HistMap("/nfs-7/userdata/phchang/scalefactors/FR_v5.3.2/fakerate_2017_3l_medium.root:El_ptcorretarolled_data_fakerate");
            if (not histmap_2017_fr_3l_mu_medium        ) histmap_2017_fr_3l_mu_medium         = new RooUtil::HistMap("/nfs-7/userdata/phchang/scalefactors/FR_v5.3.2/fakerate_2017_3l_medium.root:Mu_ptcorretarolled_data_fakerate");
            if (not histmap_2017_fr_3l_el_medium_closure) histmap_2017_fr_3l_el_medium_closure = new RooUtil::HistMap("/nfs-7/userdata/phchang/scalefactors/FR_v5.3.2/fakerate_2017_3l_medium.root:El_ptcorretarolled_data_fakerateclosure");
            if (not histmap_2017_fr_3l_mu_medium_closure) histmap_2017_fr_3l_mu_medium_closure = new RooUtil::HistMap("/nfs-7/userdata/phchang/scalefactors/FR_v5.3.2/fakerate_2017_3l_medium.root:Mu_ptcorretarolled_data_fakerateclosure");
            histmap_fr_ss_el         = histmap_2017_fr_ss_el;
            histmap_fr_ss_mu         = histmap_2017_fr_ss_mu;
            histmap_fr_3l_el         = histmap_2017_fr_3l_el;
            histmap_fr_3l_mu         = histmap_2017_fr_3l_mu;
            histmap_fr_ss_el_closure = histmap_2017_fr_ss_el_closure;
            histmap_fr_ss_mu_closure = histmap_2017_fr_ss_mu_closure;
            histmap_fr_3l_el_closure = histmap_2017_fr_3l_el_closure;
            histmap_fr_3l_mu_closure = histmap_2017_fr_3l_mu_closure;
            histmap_fr_3l_el_medium         = histmap_2017_fr_3l_el_medium;
            histmap_fr_3l_mu_medium         = histmap_2017_fr_3l_mu_medium;
            histmap_fr_3l_el_medium_closure = histmap_2017_fr_3l_el_medium_closure;
            histmap_fr_3l_mu_medium_closure = histmap_2017_fr_3l_mu_medium_closure;
            closure_tight_ss_e  = 0.29;
            closure_tight_ss_m  = 0.22;
            closure_tight_3l_e  = 0.13;
            closure_tight_3l_m  = 0.18;
            closure_medium_3l_e = 0.07;
            closure_medium_3l_m = 0.11;
        }

        void load2018()
        {
            if (not histmap_2018_fr_ss_el        ) histmap_2018_fr_ss_el         = new RooUtil::HistMap("/nfs-7/userdata/phchang/scalefactors/FR_v5.3.2/fakerate_2018_ss.root:El_ptcorretarolled_data_fakerate");
            if (not histmap_2018_fr_ss_mu        ) histmap_2018_fr_ss_mu         = new RooUtil::HistMap("/nfs-7/userdata/phchang/scalefactors/FR_v5.3.2/fakerate_2018_ss.root:Mu_ptcorretarolled_data_fakerate");
            if (not histmap_2018_fr_3l_el        ) histmap_2018_fr_3l_el         = new RooUtil::HistMap("/nfs-7/userdata/phchang/scalefactors/FR_v5.3.2/fakerate_2018_3l.root:El_ptcorretarolled_data_fakerate");
            if (not histmap_2018_fr_3l_mu        ) histmap_2018_fr_3l_mu         = new RooUtil::HistMap("/nfs-7/userdata/phchang/scalefactors/FR_v5.3.2/fakerate_2018_3l.root:Mu_ptcorretarolled_data_fakerate");
            if (not histmap_2018_fr_ss_el_closure) histmap_2018_fr_ss_el_closure = new RooUtil::HistMap("/nfs-7/userdata/phchang/scalefactors/FR_v5.3.2/fakerate_2018_ss.root:El_ptcorretarolled_data_fakerateclosure");
            if (not histmap_2018_fr_ss_mu_closure) histmap_2018_fr_ss_mu_closure = new RooUtil::HistMap("/nfs-7/userdata/phchang/scalefactors/FR_v5.3.2/fakerate_2018_ss.root:Mu_ptcorretarolled_data_fakerateclosure");
            if (not histmap_2018_fr_3l_el_closure) histmap_2018_fr_3l_el_closure = new RooUtil::HistMap("/nfs-7/userdata/phchang/scalefactors/FR_v5.3.2/fakerate_2018_3l.root:El_ptcorretarolled_data_fakerateclosure");
            if (not histmap_2018_fr_3l_mu_closure) histmap_2018_fr_3l_mu_closure = new RooUtil::HistMap("/nfs-7/userdata/phchang/scalefactors/FR_v5.3.2/fakerate_2018_3l.root:Mu_ptcorretarolled_data_fakerateclosure");
            if (not histmap_2018_fr_3l_el_medium        ) histmap_2018_fr_3l_el_medium         = new RooUtil::HistMap("/nfs-7/userdata/phchang/scalefactors/FR_v5.3.2/fakerate_2018_3l_medium.root:El_ptcorretarolled_data_fakerate");
            if (not histmap_2018_fr_3l_mu_medium        ) histmap_2018_fr_3l_mu_medium         = new RooUtil::HistMap("/nfs-7/userdata/phchang/scalefactors/FR_v5.3.2/fakerate_2018_3l_medium.root:Mu_ptcorretarolled_data_fakerate");
            if (not histmap_2018_fr_3l_el_medium_closure) histmap_2018_fr_3l_el_medium_closure = new RooUtil::HistMap("/nfs-7/userdata/phchang/scalefactors/FR_v5.3.2/fakerate_2018_3l_medium.root:El_ptcorretarolled_data_fakerateclosure");
            if (not histmap_2018_fr_3l_mu_medium_closure) histmap_2018_fr_3l_mu_medium_closure = new RooUtil::HistMap("/nfs-7/userdata/phchang/scalefactors/FR_v5.3.2/fakerate_2018_3l_medium.root:Mu_ptcorretarolled_data_fakerateclosure");
            histmap_fr_ss_el         = histmap_2018_fr_ss_el;
            histmap_fr_ss_mu         = histmap_2018_fr_ss_mu;
            histmap_fr_3l_el         = histmap_2018_fr_3l_el;
            histmap_fr_3l_mu         = histmap_2018_fr_3l_mu;
            histmap_fr_ss_el_closure = histmap_2018_fr_ss_el_closure;
            histmap_fr_ss_mu_closure = histmap_2018_fr_ss_mu_closure;
            histmap_fr_3l_el_closure = histmap_2018_fr_3l_el_closure;
            histmap_fr_3l_mu_closure = histmap_2018_fr_3l_mu_closure;
            histmap_fr_3l_el_medium         = histmap_2018_fr_3l_el_medium;
            histmap_fr_3l_mu_medium         = histmap_2018_fr_3l_mu_medium;
            histmap_fr_3l_el_medium_closure = histmap_2018_fr_3l_el_medium_closure;
            histmap_fr_3l_mu_medium_closure = histmap_2018_fr_3l_mu_medium_closure;
            closure_tight_ss_e  = 0.31;
            closure_tight_ss_m  = 0.29;
            closure_tight_3l_e  = 0.14;
            closure_tight_3l_m  = 0.23;
            closure_medium_3l_e = 0.10;
            closure_medium_3l_m = 0.10;
        }

        int getFakeLepIndex()
        {

            // First check that this event is part of application region
            if (not Lambdas::PassTightIsolationAR())
                return -1;

            // The 2016 version of EA correction uses "version-2"
            const std::vector<float>& reliso = (input.year == 2016) ? www.lep_relIso03EAv2Lep() : www.lep_relIso03EALep();

            // Loop over lepton container and find the lepton that pass loose but not tight
            std::vector<int> fake_lep_idxs;

            // If it is same-sign category
            if (www.nVlep() == 2)
            {

                for (unsigned int i = 0; i < www.lep_pdgId().size(); ++i)
                {

                    // Electron IDs
                    if (abs(www.lep_pdgId()[i]) == 11)
                    {
                        // Loose but not tight (Same-sign ID)
                        if ((www.lep_pass_VVV_fo()[i] and reliso[i] >= 0.05) and (www.lep_pass_VVV_fo()[i] and reliso[i] <  0.40))
                            fake_lep_idxs.push_back(i);
                    }

                    // Muon IDs
                    if (abs(www.lep_pdgId()[i]) == 13)
                    {
                        if ((www.lep_pass_VVV_fo()[i] and reliso[i] >= 0.04) and (www.lep_pass_VVV_fo()[i] and reliso[i] < 0.40))
                            fake_lep_idxs.push_back(i);
                    }

                }

                if (fake_lep_idxs.size() != 1)
                {
                    // Something is wrong!
                    std::cout << "I did not find the loose-but-not-tight lepton to apply the fake rate, although I think I should have found one" << std::endl;
                    return -1;
                }

            }

            // If it is three lepton category
            else if (www.nVlep() == 3)
            {

                // 0SFOS region eem
                if (www.nSFOS() == 0 and (abs(www.lep_pdgId()[0]) + abs(www.lep_pdgId()[1]) + abs(www.lep_pdgId()[2])) == 35) //eem
                {

                    for (unsigned int i = 0; i < www.lep_pdgId().size(); ++i)
                    {

                        // Electron IDs
                        if (abs(www.lep_pdgId()[i]) == 11)
                        {
                            // Loose but not tight (Same-sign ID)
                            if ((www.lep_pass_VVV_fo()[i] and reliso[i] >= 0.05) and (www.lep_pass_VVV_fo()[i] and reliso[i] <  0.40))
                                fake_lep_idxs.push_back(i);
                        }

                    }

                }

                // 0SFOS region emm
                else if (www.nSFOS() == 0 and (abs(www.lep_pdgId()[0]) + abs(www.lep_pdgId()[1]) + abs(www.lep_pdgId()[2])) == 37) //emm
                {

                    for (unsigned int i = 0; i < www.lep_pdgId().size(); ++i)
                    {

                        // Muon IDs
                        if (abs(www.lep_pdgId()[i]) == 13)
                        {
                            // Loose but not tight (Same-sign ID)
                            if ((www.lep_pass_VVV_fo()[i] and reliso[i] >= 0.04) and (www.lep_pass_VVV_fo()[i] and reliso[i] <  0.40))
                                fake_lep_idxs.push_back(i);
                        }

                    }


                }

                // The rest (i.e. 1SFOS or 2SFOS)
                else if (www.nSFOS() > 0)
                {

                    for (unsigned int i = 0; i < www.lep_pdgId().size(); ++i)
                    {

                        // Electron IDs
                        if (abs(www.lep_pdgId()[i]) == 11)
                        {
                            // Loose but not tight (three-lep ID)
                            if ((www.lep_pass_VVV_3l_fo()[i] and reliso[i] >= 0.1) and (www.lep_pass_VVV_3l_fo()[i] and reliso[i] <  0.40))
                                fake_lep_idxs.push_back(i);
                        }

                        // Muon IDs
                        if (abs(www.lep_pdgId()[i]) == 13)
                        {
                            // Loose but not tight (three-lep ID)
                            if ((www.lep_pass_VVV_fo()[i] and reliso[i] >= 0.15) and (www.lep_pass_VVV_fo()[i] and reliso[i] <  0.40))
                                fake_lep_idxs.push_back(i);
                        }

                    }

                }

                if (fake_lep_idxs.size() != 1)
                {
                    // Something is wrong!
                    std::cout << "I did not find the loose-but-not-tight lepton to apply the fake rate, although I think I should have found one" << std::endl;
                    return -1;
                }

            }

            // If neither nVlep == 2 or nVlep == 3 then it's not of interest to WWW
            else
            {
                return -1;
            }

            // By now, only one lepton index should be pushed to fake_lep_idxs.
            return fake_lep_idxs[0];

        }

        float getPtCorr()
        {
            int index = getFakeLepIndex();

            if (index < 0)
                return 0;

            // Create an int to indicate which lepton id fakerate to use
            float eliso_thresh;
            float muiso_thresh;
            if (www.nVlep() == 2)
            {
                eliso_thresh = 0.05;
                muiso_thresh = 0.04;
            }
            else if (www.nVlep() == 3 and www.nSFOS() == 0 and (abs(www.lep_pdgId()[0]) + abs(www.lep_pdgId()[1]) + abs(www.lep_pdgId()[2])) == 35)
            {
                eliso_thresh = 0.05;
                muiso_thresh = 0.04;
            }
            else if (www.nVlep() == 3 and www.nSFOS() == 0 and (abs(www.lep_pdgId()[0]) + abs(www.lep_pdgId()[1]) + abs(www.lep_pdgId()[2])) == 37)
            {
                eliso_thresh = 0.05;
                muiso_thresh = 0.04;
            }
            else if (www.nVlep() == 3 and www.nSFOS() > 0)
            {
                eliso_thresh = 0.10;
                muiso_thresh = 0.15;
            }
            else
            {
                eliso_thresh = -999;
                muiso_thresh = -999;
            }

            // The 2016 version of EA correction uses "version-2"
            const std::vector<float>& reliso = (input.year == 2016) ? www.lep_relIso03EAv2Lep() : www.lep_relIso03EALep();

            // Compute the ptcorr
            float ptcorr = -1;
            if (abs(www.lep_pdgId()[index]) == 11)
            {
                ptcorr = www.lep_pt()[index] * (1 + max((double) 0. , (double) reliso[index]-eliso_thresh));
            }
            else if (abs(www.lep_pdgId()[index]) == 13)
            {
                ptcorr = www.lep_pt()[index] * (1 + max((double) 0. , (double) reliso[index]-muiso_thresh));
            }

            return ptcorr;

        }

        float getFakeFactor(int err=0, int lepflav=0, bool doclosureerr=false)
        {
            int index = getFakeLepIndex();
            float ptcorr = getPtCorr();
            float fr = 0;

            // Create an int to indicate which lepton id fakerate to use
            int lepversion = 0;
            if (www.nVlep() == 2)
            {
                lepversion = 0;
            }
            else if (www.nVlep() == 3 and www.nSFOS() == 0 and (abs(www.lep_pdgId()[0]) + abs(www.lep_pdgId()[1]) + abs(www.lep_pdgId()[2])) == 35)
            {
                lepversion = 1;
            }
            else if (www.nVlep() == 3 and www.nSFOS() == 0 and (abs(www.lep_pdgId()[0]) + abs(www.lep_pdgId()[1]) + abs(www.lep_pdgId()[2])) == 37)
            {
                lepversion = 1;
            }
            else if (www.nVlep() == 3 and www.nSFOS() > 0)
            {
                lepversion = 2;
            }

            int lepid = abs(www.lep_pdgId()[index]);
            bool lepidmatchforerror = (abs(lepid) == abs(lepflav)) or (lepflav == 0);

            // The closure error needs a bit of special treatment to properly propagate the error
            // the percentage error used to save the fakerates are in percentage for the fakerate
            // But the properway to do it is to use the percentage error to the fake factors
            float nom_fr = 0;
            float closure_err_pct = 0;
            float closure_ff = 0;

            // std::cout <<  " index: " << index <<  " www.lep_pdgId()[index]: " << www.lep_pdgId()[index] <<  " lepversion: " << lepversion <<  std::endl;

            if (abs(www.lep_pdgId()[index]) == 11 and lepversion == 0)
            {
                if (doclosureerr)
                {
                    nom_fr = histmap_fr_ss_el_closure->eval(ptcorr, fabs(www.lep_eta()[index]));
                    if (err == 1 and lepidmatchforerror)
                        fr = nom_fr * (1. + closure_tight_ss_e);
                    else if (err ==-1 and lepidmatchforerror)
                        fr = nom_fr * (1. - closure_tight_ss_e);
                    else
                        fr = nom_fr;
                    closure_err_pct = fr / nom_fr;
                    closure_ff = (nom_fr / (1 - nom_fr)) * (closure_err_pct);
                    fr = (closure_ff / (1 + closure_ff));
                }
                else
                {
                    if (err == 1 and lepidmatchforerror)
                        fr = histmap_fr_ss_el->eval_up(ptcorr, fabs(www.lep_eta()[index]));
                    else if (err ==-1 and lepidmatchforerror)
                        fr = histmap_fr_ss_el->eval_down(ptcorr, fabs(www.lep_eta()[index]));
                    else
                        fr = histmap_fr_ss_el->eval(ptcorr, fabs(www.lep_eta()[index]));
                }
            }
            else if (abs(www.lep_pdgId()[index]) == 13 and lepversion == 0)
            {
                if (doclosureerr)
                {
                    nom_fr = histmap_fr_ss_mu_closure->eval(ptcorr, fabs(www.lep_eta()[index]));
                    if (err == 1 and lepidmatchforerror)
                        fr = nom_fr * (1. + closure_tight_ss_m);
                    else if (err ==-1 and lepidmatchforerror)
                        fr = nom_fr * (1. - closure_tight_ss_m);
                    else
                        fr = nom_fr;
                    closure_err_pct = fr / nom_fr;
                    closure_ff = (nom_fr / (1 - nom_fr)) * (closure_err_pct);
                    fr = (closure_ff / (1 + closure_ff));
                }
                else
                {
                    if (err == 1 and lepidmatchforerror)
                        fr = histmap_fr_ss_mu->eval_up(ptcorr, fabs(www.lep_eta()[index]));
                    else if (err ==-1 and lepidmatchforerror)
                        fr = histmap_fr_ss_mu->eval_down(ptcorr, fabs(www.lep_eta()[index]));
                    else
                        fr = histmap_fr_ss_mu->eval(ptcorr, fabs(www.lep_eta()[index]));
                }
            }
            else if (abs(www.lep_pdgId()[index]) == 11 and lepversion == 1)
            {
                if (doclosureerr)
                {
                    nom_fr = histmap_fr_3l_el->eval(ptcorr, fabs(www.lep_eta()[index]));
                    if (err == 1 and lepidmatchforerror)
                        fr = nom_fr * (1. + closure_tight_3l_e);
                    else if (err ==-1 and lepidmatchforerror)
                        fr = nom_fr * (1. - closure_tight_3l_e);
                    else
                        fr = nom_fr;
                    closure_err_pct = fr / nom_fr;
                    closure_ff = (nom_fr / (1 - nom_fr)) * (closure_err_pct);
                    fr = (closure_ff / (1 + closure_ff));
                }
                else
                {
                    if (err == 1 and lepidmatchforerror)
                        fr = histmap_fr_3l_el->eval_up(ptcorr, fabs(www.lep_eta()[index]));
                    else if (err ==-1 and lepidmatchforerror)
                        fr = histmap_fr_3l_el->eval_down(ptcorr, fabs(www.lep_eta()[index]));
                    else
                        fr = histmap_fr_3l_el->eval(ptcorr, fabs(www.lep_eta()[index]));
                }
            }
            else if (abs(www.lep_pdgId()[index]) == 13 and lepversion == 1)
            {
                if (doclosureerr)
                {
                    nom_fr = histmap_fr_3l_mu->eval(ptcorr, fabs(www.lep_eta()[index]));
                    if (err == 1 and lepidmatchforerror)
                        fr = nom_fr * (1. + closure_tight_3l_m);
                    else if (err ==-1 and lepidmatchforerror)
                        fr = nom_fr * (1. - closure_tight_3l_m);
                    else
                        fr = nom_fr;
                    closure_err_pct = fr / nom_fr;
                    closure_ff = (nom_fr / (1 - nom_fr)) * (closure_err_pct);
                    fr = (closure_ff / (1 + closure_ff));
                }
                else
                {
                    if (err == 1 and lepidmatchforerror)
                        fr = histmap_fr_3l_mu->eval_up(ptcorr, fabs(www.lep_eta()[index]));
                    else if (err ==-1 and lepidmatchforerror)
                        fr = histmap_fr_3l_mu->eval_down(ptcorr, fabs(www.lep_eta()[index]));
                    else
                        fr = histmap_fr_3l_mu->eval(ptcorr, fabs(www.lep_eta()[index]));
                }
            }
            else if (abs(www.lep_pdgId()[index]) == 11 and lepversion == 2)
            {
                if (doclosureerr)
                {
                    nom_fr = histmap_fr_3l_el_medium->eval(ptcorr, fabs(www.lep_eta()[index]));
                    if (err == 1 and lepidmatchforerror)
                        fr = nom_fr * (1. + closure_medium_3l_e);
                    else if (err ==-1 and lepidmatchforerror)
                        fr = nom_fr * (1. - closure_medium_3l_e);
                    else
                        fr = nom_fr;
                    closure_err_pct = fr / nom_fr;
                    closure_ff = (nom_fr / (1 - nom_fr)) * (closure_err_pct);
                    fr = (closure_ff / (1 + closure_ff));
                }
                else
                {
                    if (err == 1 and lepidmatchforerror)
                        fr = histmap_fr_3l_el_medium->eval_up(ptcorr, fabs(www.lep_eta()[index]));
                    else if (err ==-1 and lepidmatchforerror)
                        fr = histmap_fr_3l_el_medium->eval_down(ptcorr, fabs(www.lep_eta()[index]));
                    else
                        fr = histmap_fr_3l_el_medium->eval(ptcorr, fabs(www.lep_eta()[index]));
                }
            }
            else if (abs(www.lep_pdgId()[index]) == 13 and lepversion == 2)
            {
                if (doclosureerr)
                {
                    nom_fr = histmap_fr_3l_mu_medium->eval(ptcorr, fabs(www.lep_eta()[index]));
                    if (err == 1 and lepidmatchforerror)
                        fr = nom_fr * (1. + closure_medium_3l_m);
                    else if (err ==-1 and lepidmatchforerror)
                        fr = nom_fr * (1. - closure_medium_3l_m);
                    else
                        fr = nom_fr;
                    closure_err_pct = fr / nom_fr;
                    closure_ff = (nom_fr / (1 - nom_fr)) * (closure_err_pct);
                    fr = (closure_ff / (1 + closure_ff));
                }
                else
                {
                    if (err == 1 and lepidmatchforerror)
                        fr = histmap_fr_3l_mu_medium->eval_up(ptcorr, fabs(www.lep_eta()[index]));
                    else if (err ==-1 and lepidmatchforerror)
                        fr = histmap_fr_3l_mu_medium->eval_down(ptcorr, fabs(www.lep_eta()[index]));
                    else
                        fr = histmap_fr_3l_mu_medium->eval(ptcorr, fabs(www.lep_eta()[index]));
                }
            }
            else
            {
                return 0;
            }
            return fr / (1 - fr);
        }

};

//_______________________________________________________________________________________________________
class TheoryWeight
{
    public:
        RooUtil::HistMap* histmap_neventsinfile;
        float nominal_;
        float pdfup_;
        float pdfdn_;
        float alsup_;
        float alsdn_;
        float qsqup_;
        float qsqdn_;
        TheoryWeight() : histmap_neventsinfile(0), nominal_(1), pdfup_(1), pdfdn_(1), alsup_(1), alsdn_(1), qsqup_(1), qsqdn_(1) {}
        void setFile(TString fname)
        {
            histmap_neventsinfile = new RooUtil::HistMap(fname + ":h_neventsinfile");
            nominal_ = histmap_neventsinfile->hist->GetBinContent(1+1);
            pdfup_   = histmap_neventsinfile->hist->GetBinContent(1+10);
            pdfdn_   = histmap_neventsinfile->hist->GetBinContent(1+11);
            alsup_   = histmap_neventsinfile->hist->GetBinContent(1+13);
            alsdn_   = histmap_neventsinfile->hist->GetBinContent(1+12);
            qsqup_   = histmap_neventsinfile->hist->GetBinContent(1+5);
            qsqdn_   = histmap_neventsinfile->hist->GetBinContent(1+9);
        }
        float& nominal() { return nominal_; }
        float& pdfup()   { return pdfup_  ; }
        float& pdfdn()   { return pdfdn_  ; }
        float& alsup()   { return alsup_  ; }
        float& alsdn()   { return alsdn_  ; }
        float& qsqup()   { return qsqup_  ; }
        float& qsqdn()   { return qsqdn_  ; }
};

//_______________________________________________________________________________________________________
class PileupReweight
{
    public:
        RooUtil::HistMap* histmap_purwegt;
        RooUtil::HistMap* histmap_purwegt_up;
        RooUtil::HistMap* histmap_purwegt_dn;
        PileupReweight()
        {
          histmap_purwegt = 0;
          histmap_purwegt_up = 0;
          histmap_purwegt_dn = 0;
        }
        ~PileupReweight()
        {
          delete histmap_purwegt;
          delete histmap_purwegt_up;
          delete histmap_purwegt_dn;
        }
        void load(float inputyear){
          if(not (histmap_purwegt==NULL or histmap_purwegt_up==NULL or histmap_purwegt_dn==NULL) ) return;//already loaded
          if(inputyear==2016)
            {
              histmap_purwegt    = new RooUtil::HistMap("/nfs-7/userdata/phchang/scalefactors/puWeights_Run2.root:puWeight2016");
              histmap_purwegt_up = new RooUtil::HistMap("/nfs-7/userdata/phchang/scalefactors/puWeights_Run2.root:puWeight2016Up");
              histmap_purwegt_dn = new RooUtil::HistMap("/nfs-7/userdata/phchang/scalefactors/puWeights_Run2.root:puWeight2016Down");
            }
          if(inputyear==2017)
            {
              histmap_purwegt    = new RooUtil::HistMap("/nfs-7/userdata/phchang/scalefactors/puWeights_Run2.root:puWeight2017");
              histmap_purwegt_up = new RooUtil::HistMap("/nfs-7/userdata/phchang/scalefactors/puWeights_Run2.root:puWeight2017Up");
              histmap_purwegt_dn = new RooUtil::HistMap("/nfs-7/userdata/phchang/scalefactors/puWeights_Run2.root:puWeight2017Down");
            }
          if(inputyear==2018)
            {
              histmap_purwegt    = new RooUtil::HistMap("/nfs-7/userdata/phchang/scalefactors/puWeights_Run2.root:puWeight2018");
              histmap_purwegt_up = new RooUtil::HistMap("/nfs-7/userdata/phchang/scalefactors/puWeights_Run2.root:puWeight2018Up");
              histmap_purwegt_dn = new RooUtil::HistMap("/nfs-7/userdata/phchang/scalefactors/puWeights_Run2.root:puWeight2018Down");
            }
        }
        float purewgt()
        {
            return histmap_purwegt->eval(www.nTrueInt());
        }
        float purewgt_up()
        {
            return histmap_purwegt_up->eval(www.nTrueInt());
        }
        float purewgt_dn()
        {
            return histmap_purwegt_dn->eval(www.nTrueInt());
        }
};

#ifndef __CINT__
// Scale factors tools
extern LeptonScaleFactors leptonScaleFactors;
extern TriggerScaleFactors triggerScaleFactors;
extern FakeRates fakerates;
extern TheoryWeight theoryweight;
extern PileupReweight pileupreweight;
#endif

#endif
