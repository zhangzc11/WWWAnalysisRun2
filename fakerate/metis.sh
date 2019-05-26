#!/bin/bash

PACKAGE=package.tar.gz

# Echo exact command
echo "$(basename $0) $*"


###################################################################################################
# ProjectMetis/CondorTask specific (Setting up some common environment)
###################################################################################################
#echo "To check whether it's on condor universe Vanilla or Local. The following variables are used."
#echo "If _CONDOR_SLOT is set, it's on Vanilla"
#echo "If X509_USER_PROXY is set, it's either on Vanilla or Local."
# if 
if [ "x${_CONDOR_JOB_AD}" == "x" ]; then
    :
    INPUTFILENAMES=$1
    shift;
else
    hostname
    uname -a
    date
    whoami
    pwd
    echo "ls'ing hadoop"
    ls -lh /hadoop/cms/store/user/phchang/
    echo "_CONDOR_SLOT" ${_CONDOR_SLOT}
    echo "X509_USER_PROXY" ${X509_USER_PROXY}
    echo "_CONDOR_SCRATCH_DIR"             ${_CONDOR_SCRATCH_DIR}
    echo "_CONDOR_SLOT"                    ${_CONDOR_SLOT}
    echo "CONDOR_VM"                       ${CONDOR_VM}
    echo "X509_USER_PROXY"                 ${X509_USER_PROXY}
    echo "_CONDOR_JOB_AD"                  ${_CONDOR_JOB_AD}
    echo "_CONDOR_MACHINE_AD"              ${_CONDOR_MACHINE_AD}
    echo "_CONDOR_JOB_IWD"                 ${_CONDOR_JOB_IWD}
    echo "_CONDOR_WRAPPER_ERROR_FILE"      ${_CONDOR_WRAPPER_ERROR_FILE}
    echo "CONDOR_IDS"                      ${CONDOR_IDS}
    echo "CONDOR_ID"                       ${CONDOR_ID}
    OUTPUTDIR=$1
    OUTPUTNAME=$2
    INPUTFILENAMES=$3
    IFILE=$4
    CMSSWVERSION=$5
    SCRAMARCH=$6
    BABYMODE=$7
    if [ "x${_CONDOR_SLOT}" == "x" ]; then
        WORKDIR=/tmp/phchang_condor_local_${OUTPUTDIR//\//_}_${OUTPUTNAME}_${IFILE}
        mkdir -p ${WORKDIR}
        ls
        cp package.tar.gz ${WORKDIR}
        cd ${WORKDIR}
        ls
        echo "This is in Condor session with Universe=Local."
        echo "WORKDIR=${WORKDIR}"
        echo "pwd"
        pwd
    fi
    echo "OUTPUTDIR     : $1"
    echo "OUTPUTNAME    : $2"
    echo "INPUTFILENAMES: $3"
    echo "IFILE         : $4"
    echo "CMSSWVERSION  : $5"
    echo "SCRAMARCH     : $6"
    echo "BABYMODE      : $7"
    shift 7
    md5sum package.tar.gz
    tar xvzf package.tar.gz
    if [ $? -eq 0 ]; then
        echo "Successfully untarred package."
        :
    else
        echo "Failed to untar package."
        exit
    fi
fi
###################################################################################################

echo ">>> source setup.sh"
source setup.sh
echo ">>> ls -l"
ls -l
echo ">>> export COREDIR=$PWD/CORE/"
export COREDIR=$PWD/CORE/
echo ">>> ./doAnalysis ${INPUTFILENAMES} output.root ${BABYMODE}"
./doAnalysis ${INPUTFILENAMES} output.root ${BABYMODE}

function lsroot {
    if [ -z $1 ];then
        echo "USAGE: lsroot rootfile"
    fi
    MACRONAME=$(mktemp stupid_numbers_XXXXXXXXX)
    MACRO=/tmp/${MACRONAME}.C
    for item in $*; do
        echo "{ TFile* f = new TFile(\"$item\"); f->ls(); }" > $MACRO
        root -l -b -q $MACRO
    done
    rm $MACRONAME
}
export -f lsroot

STR=$(lsroot output.root | grep filename | awk '{print $3}')
STR=${STR/.root/ }
STR=${STR/Root__/ }
STR=${STR/filename_/ }
STR=$(echo $STR | awk '{print $1}')
cp -v output.root ${STR}.root

###################################################################################################
# ProjectMetis/CondorTask specific (Copying files over to hadoop)
###################################################################################################
if [ "x${_CONDOR_JOB_AD}" == "x" ]; then
    :
else
    echo "==============================================================================="
    echo " Copying files to output directory"
    echo "==============================================================================="
    hostname
    uname -a
    date
    whoami
    pwd
    echo "ls'ing hadoop"
    ls -lh /hadoop/cms/store/user/phchang/
    if [[ ${OUTPUTDIR} == *"home/users/"* ]]; then
        mkdir -p ${OUTPUTDIR}
        INFILE=${OUTPUTROOTNAME}
        cp ${INFILE} ${OUTPUTDIR}/${OUTPUTNAME}_${IFILE}.root
    else
        if [ "x${X509_USER_PROXY}" == "x" ]; then
            echo "Copying outputs to Hadoop via cp."
            mkdir -p ${OUTPUTDIR}
            INFILE=${OUTPUTROOTNAME//.root/}
            INDEX=0
            #for OUTPUTFILE in $(ls ${INFILE}*.root); do
            for OUTPUTFILE in $(ls output.root); do
                if [ $INDEX -lt 1 ]; then
                    echo "cp ${OUTPUTFILE} ${OUTPUTDIR}/${OUTPUTNAME}_${IFILE}.root"
                    cp ${OUTPUTFILE} ${OUTPUTDIR}/${OUTPUTNAME}_${IFILE}.root
                else
                    echo "cp ${OUTPUTFILE} ${OUTPUTDIR}/${OUTPUTNAME}_${IFILE}_${INDEX}.root"
                    cp ${OUTPUTFILE} ${OUTPUTDIR}/${OUTPUTNAME}_${IFILE}_${INDEX}.root
                fi
                INDEX=$((INDEX+1))
            done
        else
            echo 'ls -l'
            ls -l
            echo 'gfal-copy'
            INFILE=${OUTPUTROOTNAME//.root/}
            INDEX=0
            #for OUTPUTFILE in $(ls ${INFILE}*.root); do
            for OUTPUTFILE in $(ls output.root); do
                if [ $INDEX -lt 1 ]; then
                    echo gfal-copy -p -f -t 4200 --verbose file://`pwd`/${OUTPUTFILE} gsiftp://gftp.t2.ucsd.edu/${OUTPUTDIR}/${OUTPUTNAME}_${IFILE}.root --checksum ADLER32
                    gfal-copy -p -f -t 4200 --verbose file://`pwd`/${OUTPUTFILE} gsiftp://gftp.t2.ucsd.edu/${OUTPUTDIR}/${OUTPUTNAME}_${IFILE}.root --checksum ADLER32
                    gfal-copy -p -f -t 4200 --verbose file://`pwd`/${STR}.root gsiftp://gftp.t2.ucsd.edu/${OUTPUTDIR}/${STR}.root --checksum ADLER32
                else
                    echo gfal-copy -p -f -t 4200 --verbose file://`pwd`/${OUTPUTFILE} gsiftp://gftp.t2.ucsd.edu/${OUTPUTDIR}/${OUTPUTNAME}_${IFILE}_${INDEX}.root --checksum ADLER32
                    gfal-copy -p -f -t 4200 --verbose file://`pwd`/${OUTPUTFILE} gsiftp://gftp.t2.ucsd.edu/${OUTPUTDIR}/${OUTPUTNAME}_${IFILE}_${INDEX}.root --checksum ADLER32
                fi
                INDEX=$((INDEX+1))
            done
        fi
    fi
    if [ $? -eq 0 ]; then
        echo "Hadoop Copy Job Success"
    else
        echo "HAdoop Copy Job Failed"
    fi
    date
fi
###################################################################################################

