#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

# Help
usage()
{
    echo "ERROR - Usage:"
    echo
    echo "      sh $(basename $0) OPTIONSTRINGS ..."
    echo
    echo "Options with arguments:"
    echo "  -t    tag used when running the looper (e.g. test_2019_10_12_0610)"
    echo "  -b    baby type                        (e.g. Loose or WWW or VVV or etc.)"
    echo "  -v    baby version                     (e.g. v5.3.0  <- always start with 'v')"
    echo
    exit
}

# Default value
CUTFLOW="-C"

# Command-line opts
while getopts ":t:b:v:h" OPTION; do
  case $OPTION in
    t) TAG=${OPTARG};;
    b) BABYTYPE=${OPTARG};;
    v) VERSION=${OPTARG};;
    h) usage;;
    :) usage;;
  esac
done

if [ -z ${TAG} ]; then usage; fi
if [ -z ${BABYTYPE}  ]; then usage; fi
if [ -z ${VERSION} ]; then usage; fi

# to shift away the parsed options
shift $(($OPTIND - 1))

# Verbose
date
echo "================================================"
echo "$(basename $0) $*"
echo "$(basename $0) $*" >> $DIR/.$(basename $0).history
echo "------------------------------------------------"
echo "TAG                 : ${TAG}"
echo "BABYTYPE            : ${BABYTYPE}"
echo "VERSION             : ${VERSION}"
echo "================================================"

YEAR2016=hists/${BABYTYPE}2016_${VERSION}/${TAG}
YEAR2017=hists/${BABYTYPE}2017_${VERSION}/${TAG}
YEAR2018=hists/${BABYTYPE}2018_${VERSION}/${TAG}

YEARCOMB=hists/combineyears${BABYTYPE}_${VERSION}/${TAG}

if [ ! -d "$YEARCOMB" ]; then
    echo "making dir $YEARCOMB"
    mkdir -p "$YEARCOMB"
fi

rm -f .hadd.cmds

find "$YEAR2016" -maxdepth 1 -type f -name '*.root' -printf '%f\n' | while read line; do
    if [ ! -f "$YEAR2016/$line" ]; then
        echo "File $YEAR2016/$line does not exist. continue."
        continue
    fi
    if [ ! -f "$YEAR2017/$line" ]; then
        echo "File $YEAR2017/$line does not exist. continue."
        continue
    fi
    if [ ! -f "$YEAR2018/$line" ]; then
        echo "File $YEAR2018/$line does not exist. continue."
        continue
    fi
    echo "hadd -f $YEARCOMB/$line $YEAR2016/$line $YEAR2017/$line $YEAR2018/$line > $YEARCOMB/hadd_log_${line}.log" >> .hadd.cmds
    # hadd -f $YEARCOMB/$line $YEAR2016/$line $YEAR2017/$line $YEAR2018/$line
done

echo "Running hadd in parallel...."
echo "Below are jobs launched ========================================>>>>>"

sh rooutil/xargs.sh .hadd.cmds

