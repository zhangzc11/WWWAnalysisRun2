#!/bin/bash

DIR=$1

help() {
    echo "Usage:"
    echo "  sh $0 /path/to/where/datacards/are/"
    exit
}

if [ -z $DIR ]; then
    help;
fi

if [ -f $DIR/datacard_b1.txt ]; then
    combineCards.py \
        b1=$DIR/datacard_b1.txt \
        b2=$DIR/datacard_b2.txt \
        b3=$DIR/datacard_b3.txt \
        b4=$DIR/datacard_b4.txt \
        b5=$DIR/datacard_b5.txt \
        b6=$DIR/datacard_b6.txt \
        b7=$DIR/datacard_b7.txt \
        b8=$DIR/datacard_b8.txt \
        b9=$DIR/datacard_b9.txt \
        > $DIR/datacard_combined.txt
else
    echo "ERROR: Could not find datacards"
    help
fi

if [ -f $DIR/datacard_b1.txt ]; then
    combineCards.py \
        b1=$DIR/datacard_b1.txt \
        b2=$DIR/datacard_b2.txt \
        b3=$DIR/datacard_b3.txt \
        b4=$DIR/datacard_b4.txt \
        b5=$DIR/datacard_b5.txt \
        b6=$DIR/datacard_b6.txt \
        > $DIR/datacard_combined_ss.txt
else
    echo "ERROR: Could not find datacards"
    help
fi
    
if [ -f $DIR/datacard_b7.txt ]; then
    combineCards.py \
        b7=$DIR/datacard_b7.txt \
        b8=$DIR/datacard_b8.txt \
        b9=$DIR/datacard_b9.txt \
        > $DIR/datacard_combined_3l.txt
else
    echo "ERROR: Could not find datacards"
    help
fi
