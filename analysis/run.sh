#!/bin/bash

# The script does three things in serial
# 1. This script loops over the baby directory area and aggregates all the commands that need to be called to run the job.
#    The output will be stored into .jobs.txt
# 2. Then rooutil/xargs.sh will call the .jobs.txt to execute the jobs in parallel (36 cores)
# 3. Afterwards, the outputs will be hadded into background groups for easier histogramming


#_____________________________________________________________________________________________
# Help message
help()
{
    echo "Error - Usage:"
    echo "$0 INPUT_BABY_VERSION TAG_FOR_ANALYSIS_RUN [REGIONS=all]"
    exit
}

if [ -z $1 ]; then help; fi
if [ -z $2 ]; then help; fi


#_____________________________________________________________________________________________
# The first argument will be the WWW baby tag (e.g. WWW2017_v4.0.5 produced around November of 2018)
VERSION=$1

# The second argument will be the tag for this run of the analysis job.
LOOPTAG=$2

# The third argument will decide which regions to run over.
# If set to "all" it runs over all regions defined in the analysis program.
if [ -z $3 ]; then
    regions="all"
else
    regions=$3
fi

# The fourth argument will decide whether to run histograms (no systematics)
if [ -z $4 ]; then
    dohist=""
else
    dohist=$4
fi


#_____________________________________________________________________________________________
# Set the number of events to process per file
# Normally this would be set to -1 to run over all events to get correct yields and histograms
# But this can also be used to speed things up and test whether things work
NEVENTS=-1
#NEVENTS=500



#_____________________________________________________________________________________________
# These are constant variables that do not need to be changed
TREEVARIATIONS="qflip photon fakes prompt lostlep"

# Now create the output directory
OUTPUTDIR=outputs/${VERSION}/${LOOPTAG}/
mkdir -p ${OUTPUTDIR}

# Clear the output .jobs.txt
rm .jobs.txt


#_____________________________________________________________________________________________

####################
# I. Loop over ntuples and write out the commands for processing the analysis
####################
for f in $(ls /nfs-7/userdata/phchang/WWW_babies/${VERSION}/skim/*.root); do

    # These are to skip over the BSM interpretation files that was done for 2016 analysis.
    if [[ $f == *"hpmpm"* ]]; then continue; fi
    if [[ $f == *"wprime"* ]]; then continue; fi
    if [[ $f == *"whsusy"* ]]; then continue; fi
    if [[ $f == *"alp"* ]]; then continue; fi
    if [[ $f == *"sapta"* ]]; then continue; fi
    if [[ $f == *"_bw"* ]]; then continue; fi

    # Print out which ntuple is being considered to write out jobs to .jobs.txt
    echo "Writing jobs for $f to .jobs.txt"

    #
    # 1. WWW sample: If the file name matches "www_" then this is signal sample
    #
    if [[ $f == *"/www_"* ]]; then

        # The TTree that will be run over from this file is always t_"www" (i.e. TTree named "t_www")
        # So this variable will be used to write out the command with the proper argument set to "t_www"
        TREEVARIATION="www"

        # If the filename contains "_bw15_" this is the sample where Mia regenerated the official sample with proper W width set for the WWW sample. (Official WWW sample had narrow-width W which is incorrect.)
        # Ask around HJ, Mia, or Philip who worked on it during Nov. 2018
        if [[ $f == *"_bw15_"* ]]; then
            # if BW15
            echo 'if [ ! -f '${OUTPUTDIR}'/t_'${TREEVARIATION}'_'$(basename $f)' ]; then ./doAnalysis '$f' 't_${TREEVARIATION}' '${OUTPUTDIR}'/t_'${TREEVARIATION}'_'$(basename $f)' '${NEVENTS}' '${regions} ${dohist}'  > '${OUTPUTDIR}'/t_'${TREEVARIATION}'_'$(basename $f)'.log 2>&1; fi' >> .jobs.txt
        # Normally, you'd be falling under this category
        else
            # Write out signal sample job
            echo 'if [ ! -f '${OUTPUTDIR}'/t_'${TREEVARIATION}'_'$(basename $f)' ]; then ./doAnalysis '$f' 't' '${OUTPUTDIR}'/t_'${TREEVARIATION}'_'$(basename $f)' '${NEVENTS}' '${regions} ${dohist}'  > '${OUTPUTDIR}'/t_'${TREEVARIATION}'_'$(basename $f)'.log 2>&1; fi' >> .jobs.txt
        fi
    #
    # 2. VH sample: If the file name matches "vh_*" then this is also a signal sample. However, the non WH->WWW events in VH samples will also need to be included as backgrounds.
    #
    elif [[ $f == *"/vh_"* ]]; then

        # So first process the signal part of the "vh_*" sample
        # So this variable will be used to write out the command with the proper argument set to "t_www"
        TREEVARIATION="www"

        # Write out the VH signal portion of the command line
        echo 'if [ ! -f '${OUTPUTDIR}'/t_'${TREEVARIATION}'_'$(basename $f)' ]; then ./doAnalysis '$f' 't_${TREEVARIATION}' '${OUTPUTDIR}'/t_'${TREEVARIATION}'_'$(basename $f)' '${NEVENTS}' '${regions} ${dohist}'  > '${OUTPUTDIR}'/t_'${TREEVARIATION}'_'$(basename $f)'.log 2>&1; fi' >> .jobs.txt

        # Now write out the background part of the VH sample
        # Loop over the tree varations. (e.g. qflip, prompt, lostlep, etc.)
        for TREEVARIATION in ${TREEVARIATIONS}; do

            # Now write out the command to run over VH background events in various TTree's like t_qflip, t_lostlep, etc.
            echo 'if [ ! -f '${OUTPUTDIR}'/t_'${TREEVARIATION}'_'$(basename $f)' ]; then ./doAnalysis '$f' 't_${TREEVARIATION}' '${OUTPUTDIR}'/t_'${TREEVARIATION}'_'$(basename $f)' '${NEVENTS}' '${regions} ${dohist}'  > '${OUTPUTDIR}'/t_'${TREEVARIATION}'_'$(basename $f)'.log 2>&1; fi' >> .jobs.txt

        done
    # (NOTE: not used for 2017 and onwards)
    # 3. Data: If the file name matches "data_ss" this is for the 2016 analysis primarily for the sample used for final results.
    #    So at that time, the data_ss.root was the duplicate removed data hadded ntuple.
    #    (Normally, when you just had DoubleEG/MuonEG/DoubleMuon you get duplicate events, due to same event firing various trigger and ending up in various primary datasets.)
    #    So at the time, Philip merged but also duplicate removed and put all of them in one file called "data_ss.root"
    #    For 2017 and onwards, the duplicate removal was handled via a flag in the ntuple baby. (e.g. pass_duplicate_ee_em_mm, etc. See the implementation in github.com:cmstas/VVVBabyMaker for more detail)
    #
    #    There are mainly two things to do. (1) processing as data events, and (2) data-driven fake estimate
    #
    elif [[ $f == *"/data_ss"* ]]; then

        # Write out the job command for processing data events
        echo 'if [ ! -f '${OUTPUTDIR}'/t_ss_'$(basename $f)' ]; then ./doAnalysis '$f' 't_ss' '${OUTPUTDIR}'/t_ss_'$(basename $f)' '${NEVENTS}' '${regions} ${dohist}'  > '${OUTPUTDIR}'/'$(basename $f)'.log 2>&1; fi' >> .jobs.txt

        # Write out the job command for data-driven fake estimate
        # The analysis source file (i.e. process.cc) recognizes the output file pattern "ddfakes" and flips the internal switch to process it as a data-driven fake estimate
        echo 'if [ ! -f '${OUTPUTDIR}'/t_ddfakes_'$(basename $f)' ]; then ./doAnalysis '$f' 't_ss' '${OUTPUTDIR}'/t_ddfakes_'$(basename $f)' '${NEVENTS}' '${regions} ${dohist}'  > '${OUTPUTDIR}'/t_ddfakes_'$(basename $f)'.log 2>&1; fi' >> .jobs.txt

    #
    # 4. Data: If the file name starts with "data*", then process the data events.
    #    There are mainly two things to do. (1) processing as data events, and (2) data-driven fake estimate
    #
    elif [[ $f == *"/data"* ]]; then

        # If the sample is for 2017 events or v4 and above for 2016
        if [[ $f == *"Loose2017"* ]] || [[ $f == *"WWW2017"*  ]] || [[ $f == *"WWW2016_v4"* ]] || [[ $f == *"WWW2016_v5"* ]]; then

            # Write out the job command for processing data events
            echo 'if [ ! -f '${OUTPUTDIR}'/t_ss_'$(basename $f)' ]; then ./doAnalysis '$f' 't' '${OUTPUTDIR}'/t_ss_'$(basename $f)' '${NEVENTS}' '${regions} ${dohist}'  > '${OUTPUTDIR}'/'t_ss_$(basename $f)'.log 2>&1; fi' >> .jobs.txt

            # Write out the job command for data-driven fake estimate
            # The analysis source file (i.e. process.cc) recognizes the output file pattern "ddfakes" and flips the internal switch to process it as a data-driven fake estimate
            echo 'if [ ! -f '${OUTPUTDIR}'/t_ddfakes_'$(basename $f)' ]; then ./doAnalysis '$f' 't' '${OUTPUTDIR}'/t_ddfakes_'$(basename $f)' '${NEVENTS}' '${regions} ${dohist}'  > '${OUTPUTDIR}'/'t_ddfakes_$(basename $f)'.log 2>&1; fi' >> .jobs.txt

        # TODO: The consistent treatment of 2016 analysis with the same version of baby maker hasn't been done yet. (As of Nov. 2018)
        #       Once the VVVBabyMaker/master version produced 2016 AND 2017 with a same setup, this will be implemented and the section "3." will be deprecated.
        else
            :
            # if data but not data_ss nor WWW_2017, then skip
            #echo './doAnalysis '$f' 't' '${OUTPUTDIR}'/'$(basename $f)' '${NEVENTS}' '${regions}'  > '${OUTPUTDIR}'/'$(basename $f)'.log 2>&1' >> .jobs.txt
        fi
    #
    # 5. Background MC
    #    There are two parts (1) regular job processing, (2) bkg subtraction for dd-fake estimates
    #
    else

        # The tzq samples are HUGE and is very TINY. We skip it. Just takes up time and does nothing.
        if [[ $f == *"tzq"* ]]; then continue; fi
        if [[ $f == *"wz_3lnu0"* ]]; then continue; fi
        if [[ $f == *"wz_3lnu1"* ]]; then continue; fi
        if [[ $f == *"wz_3lnu2"* ]]; then continue; fi
        if [[ $f == *"wz_3lnu3"* ]]; then continue; fi

        # Loop over the various TTree suffixes and write out jobs for each TTree
        for TREEVARIATION in ${TREEVARIATIONS}; do

            # Write out jobs for t_{$TREEVARIATION} for regular mc bkg processing
            echo 'if [ ! -f '${OUTPUTDIR}'/t_'${TREEVARIATION}'_'$(basename $f)' ]; then ./doAnalysis '$f' 't_${TREEVARIATION}' '${OUTPUTDIR}'/t_'${TREEVARIATION}'_'$(basename $f)' '${NEVENTS}' '${regions} ${dohist}'  > '${OUTPUTDIR}'/t_'${TREEVARIATION}'_'$(basename $f)'.log 2>&1; fi' >> .jobs.txt

        done

        # Write out job commands for processing non-"non-prompt" backgrounds in application regions
        echo 'if [ ! -f '${OUTPUTDIR}'/t_ewksubt_'$(basename $f)' ]; then ./doAnalysis '$f' 't_ss' '${OUTPUTDIR}'/t_ewksubt_'$(basename $f)' '${NEVENTS}' '${regions} ${dohist}'  > '${OUTPUTDIR}'/t_ewksubt_'$(basename $f)'.log 2>&1; fi' >> .jobs.txt

        # Write out job commands for processing as a whole
        echo 'if [ ! -f '${OUTPUTDIR}'/t_ss_'$(basename $f)' ]; then ./doAnalysis '$f' 't_ss' '${OUTPUTDIR}'/t_ss_'$(basename $f)' '${NEVENTS}' '${regions} ${dohist}'  > '${OUTPUTDIR}'/t_ss_'$(basename $f)'.log 2>&1; fi' >> .jobs.txt
    fi
done

#_____________________________________________________________________________________________

####################
# II. Now launch 36 core jobs (if you wish to change the number of cores running, change the number in the rooutil.xargs.sh)
####################
time sh rooutil/xargs.sh .jobs.txt



#_____________________________________________________________________________________________

####################
# III. Hadd the outputs in to "qflip", "lostlep", "prompt" etc. for easier histogramming later
####################
TAG=${VERSION}
DIRPATH=${OUTPUTDIR}
OUTPATH=${OUTPUTDIR}

lostlep=$(ls $DIRPATH/*t_lostlep_*.root                                  | grep -v wz_incl | grep -v wz_3lv_amc | grep -v wz_3lv_pow                                                  ) 
photon=$(ls $DIRPATH/*t_photon_*.root                                    | grep -v wz_incl | grep -v wz_3lv_amc | grep -v wz_3lv_pow                                                  ) 
qflip=$(ls $DIRPATH/*t_qflip_*.root                                      | grep -v wz_incl | grep -v wz_3lv_amc | grep -v wz_3lv_pow                                                  ) 
ddfakes=$(ls $DIRPATH/*t_ddfakes_*.root                                  | grep -v wz_incl | grep -v wz_3lv_amc | grep -v wz_3lv_pow                                                  ) 
ewksubt=$(ls $DIRPATH/*t_ewksubt_*.root                                  | grep -v wz_incl | grep -v wz_3lv_amc | grep -v wz_3lv_pow | grep -v "wjets_incl"                           ) 
fakes=$(ls $DIRPATH/*t_fakes_*.root                                      | grep -v wz_incl | grep -v wz_3lv_amc | grep -v wz_3lv_pow                                                  ) 
prompt=$(ls $DIRPATH/*t_prompt_*.root                                    | grep -v wz_incl | grep -v wz_3lv_amc | grep -v wz_3lv_pow                                                  ) 
vbsww=$(ls $DIRPATH/*t_ss_*vbsww_*.root $DIRPATH/*t_ss_*wpwpjj_*.root    | grep -v wz_incl | grep -v wz_3lv_amc | grep -v wz_3lv_pow                                                  ) 
ttw=$(ls $DIRPATH/*t_ss_*ttw_*.root                                      | grep -v wz_incl | grep -v wz_3lv_amc | grep -v wz_3lv_pow                                                  ) 
lostlep_fit=$(ls $DIRPATH/*t_lostlep_*.root                              | grep -v wz_incl | grep -v wz_3lv_amc | grep -v wz_3lv_pow | grep -v _ttw_ | grep -v vbsww | grep -v wpwpjj ) 
photon_fit=$(ls $DIRPATH/*t_photon_*.root                                | grep -v wz_incl | grep -v wz_3lv_amc | grep -v wz_3lv_pow | grep -v _ttw_ | grep -v vbsww | grep -v wpwpjj ) 
qflip_fit=$(ls $DIRPATH/*t_qflip_*.root                                  | grep -v wz_incl | grep -v wz_3lv_amc | grep -v wz_3lv_pow | grep -v _ttw_ | grep -v vbsww | grep -v wpwpjj ) 
fakes_fit=$(ls $DIRPATH/*t_fakes_*.root                                  | grep -v wz_incl | grep -v wz_3lv_amc | grep -v wz_3lv_pow | grep -v _ttw_ | grep -v vbsww | grep -v wpwpjj ) 
prompt_fit=$(ls $DIRPATH/*t_prompt_*.root                                | grep -v wz_incl | grep -v wz_3lv_amc | grep -v wz_3lv_pow | grep -v _ttw_ | grep -v vbsww | grep -v wpwpjj ) 
data=$(ls $DIRPATH/*t_ss_data*.root )
signal=$(ls $DIRPATH/t_www_vh_ww*.root $DIRPATH/t_www_www_private*.root $DIRPATH/t_www_vh_nonbb*.root $DIRPATH/t_www_www_2l*.root)
signalofficial=$(ls $DIRPATH/t_www_vh_nonbb*.root $DIRPATH/t_www_www_amc*.root)
smwwwofficial=$(ls $DIRPATH/t_www_www_amc*.root)
whwwwofficial=$(ls $DIRPATH/t_www_vh_nonbb*.root)
smwww=$(ls $DIRPATH/t_www_www_private*.root $DIRPATH/t_www_www_2l*.root $DIRPATH/t_www_www_amcatnlo_private*.root)
whwww=$(ls $DIRPATH/t_www_vh_ww*.root $DIRPATH/t_www_vh_nonbb*.root $DIRPATH/t_www_www_amcatnlo.root)

if [ -z "${lostlep}"        ] ; then echo "lostlep is empty"        ; exit ; fi
if [ -z "${photon}"         ] ; then echo "photon is empty"         ; exit ; fi
if [ -z "${qflip}"          ] ; then echo "qflip is empty"          ; exit ; fi
if [ -z "${ddfakes}"        ] ; then echo "ddfakes is empty"        ; exit ; fi
if [ -z "${ewksubt}"        ] ; then echo "ewksubt is empty"        ; exit ; fi
if [ -z "${fakes}"          ] ; then echo "fakes is empty"          ; exit ; fi
if [ -z "${prompt}"         ] ; then echo "prompt is empty"         ; exit ; fi
if [ -z "${vbsww}"          ] ; then echo "vbsww is empty"          ; exit ; fi
if [ -z "${ttw}"            ] ; then echo "ttw is empty"            ; exit ; fi
if [ -z "${lostlep_fit}"    ] ; then echo "lostlep_fit is empty"    ; exit ; fi
if [ -z "${photon_fit}"     ] ; then echo "photon_fit is empty"     ; exit ; fi
if [ -z "${qflip_fit}"      ] ; then echo "qflip_fit is empty"      ; exit ; fi
if [ -z "${fakes_fit}"      ] ; then echo "fakes_fit is empty"      ; exit ; fi
if [ -z "${prompt_fit}"     ] ; then echo "prompt_fit is empty"     ; exit ; fi
if [ -z "${data}"           ] ; then echo "data is empty"           ; exit ; fi
if [ -z "${signal}"         ] ; then echo "signal is empty"         ; exit ; fi
if [ -z "${signalofficial}" ] ; then echo "signalofficial is empty" ; exit ; fi
#if [ -z "${smwwwofficial}"  ] ; then echo "smwwwofficial is empty"  ; exit ; fi
#if [ -z "${whwwwofficial}"  ] ; then echo "whwwwofficial is empty"  ; exit ; fi
if [ -z "${smwww}"          ] ; then echo "smwww is empty"          ; exit ; fi
if [ -z "${whwww}"          ] ; then echo "whwww is empty"          ; exit ; fi

# Should already exist but just in case.
mkdir -p ${OUTPATH}

if [ ! -f ${OUTPATH}/lostlep.root        ]; then echo "hadd ${OUTPATH}/lostlep.root        ${lostlep}"; hadd ${OUTPATH}/lostlep.root        ${lostlep} & fi
if [ ! -f ${OUTPATH}/photon.root         ]; then echo "hadd ${OUTPATH}/photon.root         ${photon}"; hadd ${OUTPATH}/photon.root         ${photon} & fi
if [ ! -f ${OUTPATH}/qflip.root          ]; then echo "hadd ${OUTPATH}/qflip.root          ${qflip}"; hadd ${OUTPATH}/qflip.root          ${qflip} & fi
if [ ! -f ${OUTPATH}/ddfakes.root        ]; then echo "hadd ${OUTPATH}/ddfakes.root        ${ddfakes}"; hadd ${OUTPATH}/ddfakes.root        ${ddfakes} & fi
if [ ! -f ${OUTPATH}/ewksubt.root        ]; then echo "hadd ${OUTPATH}/ewksubt.root        ${ewksubt}"; hadd ${OUTPATH}/ewksubt.root        ${ewksubt} & fi
if [ ! -f ${OUTPATH}/fakes.root          ]; then echo "hadd ${OUTPATH}/fakes.root          ${fakes}"; hadd ${OUTPATH}/fakes.root          ${fakes} & fi
if [ ! -f ${OUTPATH}/prompt.root         ]; then echo "hadd ${OUTPATH}/prompt.root         ${prompt}"; hadd ${OUTPATH}/prompt.root         ${prompt} & fi
if [ ! -f ${OUTPATH}/vbsww.root          ]; then echo "hadd ${OUTPATH}/vbsww.root          ${vbsww}"; hadd ${OUTPATH}/vbsww.root          ${vbsww} & fi
if [ ! -f ${OUTPATH}/ttw.root            ]; then echo "hadd ${OUTPATH}/ttw.root            ${ttw}"; hadd ${OUTPATH}/ttw.root            ${ttw} & fi
if [ ! -f ${OUTPATH}/lostlep_fit.root    ]; then echo "hadd ${OUTPATH}/lostlep_fit.root    ${lostlep_fit}"; hadd ${OUTPATH}/lostlep_fit.root    ${lostlep_fit} & fi
if [ ! -f ${OUTPATH}/photon_fit.root     ]; then echo "hadd ${OUTPATH}/photon_fit.root     ${photon_fit}"; hadd ${OUTPATH}/photon_fit.root     ${photon_fit} & fi
if [ ! -f ${OUTPATH}/qflip_fit.root      ]; then echo "hadd ${OUTPATH}/qflip_fit.root      ${qflip_fit}"; hadd ${OUTPATH}/qflip_fit.root      ${qflip_fit} & fi
if [ ! -f ${OUTPATH}/fakes_fit.root      ]; then echo "hadd ${OUTPATH}/fakes_fit.root      ${fakes_fit}"; hadd ${OUTPATH}/fakes_fit.root      ${fakes_fit} & fi
if [ ! -f ${OUTPATH}/prompt_fit.root     ]; then echo "hadd ${OUTPATH}/prompt_fit.root     ${prompt_fit}"; hadd ${OUTPATH}/prompt_fit.root     ${prompt_fit} & fi
if [ ! -f ${OUTPATH}/data.root           ]; then echo "hadd ${OUTPATH}/data.root           ${data}"; hadd ${OUTPATH}/data.root           ${data} & fi
if [ ! -f ${OUTPATH}/signal.root         ]; then echo "hadd ${OUTPATH}/signal.root         ${signal}"; hadd ${OUTPATH}/signal.root         ${signal} & fi
if [ ! -f ${OUTPATH}/signalofficial.root ]; then echo "hadd ${OUTPATH}/signalofficial.root ${signalofficial}"; hadd ${OUTPATH}/signalofficial.root ${signalofficial} & fi
if [ -n "${smwwwofficial}" ]; then if [ ! -f ${OUTPATH}/smwwwofficial.root  ]; then echo "hadd ${OUTPATH}/smwwwofficial.root  ${smwwwofficial}"; hadd ${OUTPATH}/smwwwofficial.root  ${smwwwofficial} & fi; fi
if [ -n "${whwwwofficial}" ]; then if [ ! -f ${OUTPATH}/whwwwofficial.root  ]; then echo "hadd ${OUTPATH}/whwwwofficial.root  ${whwwwofficial}"; hadd ${OUTPATH}/whwwwofficial.root  ${whwwwofficial} & fi; fi
if [ ! -f ${OUTPATH}/smwww.root          ]; then echo "hadd ${OUTPATH}/smwww.root          ${smwww}"; hadd ${OUTPATH}/smwww.root          ${smwww} & fi
if [ ! -f ${OUTPATH}/whwww.root          ]; then echo "hadd ${OUTPATH}/whwww.root          ${whwww}"; hadd ${OUTPATH}/whwww.root          ${whwww} & fi

wait

echo ""
echo "Done!"
echo ""
echo "----"
echo "Finished running ${TAG} for ${VERSION}."
echo "Output should be located at ${OUTPATH}"
