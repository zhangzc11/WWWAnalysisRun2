
for model in \
www_vs_photon_fakes_SFOS_noBtag \
www_vs_photon_fakes_SS2J_noBtag \
www_vs_photon_fakes_SS1J_noBtag \
www_vs_lostlep_prompt_SFOS \
www_vs_lostlep_prompt_SS2J \
www_vs_lostlep_prompt_SS1J 

#www_vs_photon_fakes_SFOS \
#www_vs_photon_fakes_SS2J \
#www_vs_photon_fakes_SS1J 

do
	python raw_to_cpp.py --xgb_dump=../models/model_xgb_${model}.txt --num_classes=1 --func_name=${model}
	mv ${model}.h ../models/cpp/
done
