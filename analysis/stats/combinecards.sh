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

# 9 bin fit
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

# 6 bin fit with SS channel only
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

# 3 bin fit with 3L channel only
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

# 14 bin fit w/ CRs
if [ -f $DIR/datacard_s1.txt ]; then

    # The 14 bin fit needs some modification in order to correlate CR with Signal region yields

    cat $DIR/datacard_s1.txt > $DIR/.tmp.datacard_s1.txt
    cat $DIR/datacard_s2.txt > $DIR/.tmp.datacard_s2.txt
    cat $DIR/datacard_s3.txt > $DIR/.tmp.datacard_s3.txt
    cat $DIR/datacard_s4.txt > $DIR/.tmp.datacard_s4.txt
    cat $DIR/datacard_s5.txt > $DIR/.tmp.datacard_s5.txt
    cat $DIR/datacard_s6.txt > $DIR/.tmp.datacard_s6.txt
    cat $DIR/datacard_s7.txt > $DIR/.tmp.datacard_s7.txt
    cat $DIR/datacard_s8.txt > $DIR/.tmp.datacard_s8.txt
    cat $DIR/datacard_s9.txt > $DIR/.tmp.datacard_s9.txt
    cat $DIR/datacard_c1.txt > $DIR/.tmp.datacard_c1.txt
    cat $DIR/datacard_c2.txt > $DIR/.tmp.datacard_c2.txt
    cat $DIR/datacard_c3.txt > $DIR/.tmp.datacard_c3.txt
    cat $DIR/datacard_c8.txt > $DIR/.tmp.datacard_c8.txt
    cat $DIR/datacard_c9.txt > $DIR/.tmp.datacard_c9.txt

    echo "---"                               >> $DIR/.tmp.datacard_s1.txt
    echo "---"                               >> $DIR/.tmp.datacard_s2.txt
    echo "---"                               >> $DIR/.tmp.datacard_s3.txt
    echo "---"                               >> $DIR/.tmp.datacard_s4.txt
    echo "---"                               >> $DIR/.tmp.datacard_s5.txt
    echo "---"                               >> $DIR/.tmp.datacard_s6.txt
    # nothing to be done for 0SFOS channel $DIR/.tmp.datacard_s7.txt
    echo "---"                               >> $DIR/.tmp.datacard_s8.txt
    echo "---"                               >> $DIR/.tmp.datacard_s9.txt
    echo "---"                               >> $DIR/.tmp.datacard_c1.txt
    echo "---"                               >> $DIR/.tmp.datacard_c2.txt
    echo "---"                               >> $DIR/.tmp.datacard_c3.txt
    echo "---"                               >> $DIR/.tmp.datacard_c8.txt
    echo "---"                               >> $DIR/.tmp.datacard_c9.txt

    echo "R_in_ee rateParam s1 lostlep 1.71" >> $DIR/.tmp.datacard_s1.txt
    echo "R_in_em rateParam s2 lostlep 0.83" >> $DIR/.tmp.datacard_s2.txt
    echo "R_in_mm rateParam s3 lostlep 0.97" >> $DIR/.tmp.datacard_s3.txt
    echo "R_in_ee rateParam s4 lostlep 1.71" >> $DIR/.tmp.datacard_s4.txt
    echo "R_in_em rateParam s5 lostlep 0.83" >> $DIR/.tmp.datacard_s5.txt
    echo "R_in_mm rateParam s6 lostlep 0.97" >> $DIR/.tmp.datacard_s6.txt
    # nothing to be done for 0SFOS channel $DIR/.tmp.datacard_s7.txt
    echo "R_1sfos rateParam s8 lostlep 0.92" >> $DIR/.tmp.datacard_s8.txt
    echo "R_2sfos rateParam s9 lostlep 1.00" >> $DIR/.tmp.datacard_s9.txt
    echo "R_in_ee rateParam c1 lostlep 1.71" >> $DIR/.tmp.datacard_c1.txt
    echo "R_in_em rateParam c2 lostlep 0.83" >> $DIR/.tmp.datacard_c2.txt
    echo "R_in_mm rateParam c3 lostlep 0.97" >> $DIR/.tmp.datacard_c3.txt
    echo "R_1sfos rateParam c8 lostlep 0.92" >> $DIR/.tmp.datacard_c8.txt
    echo "R_2sfos rateParam c9 lostlep 1.00" >> $DIR/.tmp.datacard_c9.txt

    combineCards.py \
        s1=$DIR/.tmp.datacard_s1.txt \
        s2=$DIR/.tmp.datacard_s2.txt \
        s3=$DIR/.tmp.datacard_s3.txt \
        s4=$DIR/.tmp.datacard_s4.txt \
        s5=$DIR/.tmp.datacard_s5.txt \
        s6=$DIR/.tmp.datacard_s6.txt \
        s7=$DIR/.tmp.datacard_s7.txt \
        s8=$DIR/.tmp.datacard_s8.txt \
        s9=$DIR/.tmp.datacard_s9.txt \
        c1=$DIR/.tmp.datacard_c1.txt \
        c2=$DIR/.tmp.datacard_c2.txt \
        c3=$DIR/.tmp.datacard_c3.txt \
        c8=$DIR/.tmp.datacard_c8.txt \
        c9=$DIR/.tmp.datacard_c9.txt \
        > $DIR/datacard_combined_w_cr.txt

    rm $DIR/.tmp.datacard_*.txt

fi

# 12 bin fit with Nj 1
if [ -f $DIR/datacard_n1.txt ]; then
    combineCards.py \
        n1=$DIR/datacard_n1.txt \
        n2=$DIR/datacard_n2.txt \
        n3=$DIR/datacard_n3.txt \
        n4=$DIR/datacard_n4.txt \
        > $DIR/datacard_combined_nj1.txt
fi

# 12 bin fit with Nj 1
if [ -f $DIR/datacard_n1.txt ]; then
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
        n1=$DIR/datacard_n1.txt \
        n2=$DIR/datacard_n2.txt \
        n3=$DIR/datacard_n3.txt \
        n4=$DIR/datacard_n4.txt \
        > $DIR/datacard_combined_13.txt
fi

# 14 bin fit w/ CRs
if [ -f $DIR/datacard_s1.txt ]; then

    # The 14 bin fit needs some modification in order to correlate CR with Signal region yields

    cat $DIR/datacard_s1.txt > $DIR/.tmp.datacard_s1.txt
    cat $DIR/datacard_s2.txt > $DIR/.tmp.datacard_s2.txt
    cat $DIR/datacard_s3.txt > $DIR/.tmp.datacard_s3.txt
    cat $DIR/datacard_s4.txt > $DIR/.tmp.datacard_s4.txt
    cat $DIR/datacard_s5.txt > $DIR/.tmp.datacard_s5.txt
    cat $DIR/datacard_s6.txt > $DIR/.tmp.datacard_s6.txt
    cat $DIR/datacard_s7.txt > $DIR/.tmp.datacard_s7.txt
    cat $DIR/datacard_s8.txt > $DIR/.tmp.datacard_s8.txt
    cat $DIR/datacard_s9.txt > $DIR/.tmp.datacard_s9.txt
    cat $DIR/datacard_c1.txt > $DIR/.tmp.datacard_c1.txt
    cat $DIR/datacard_c2.txt > $DIR/.tmp.datacard_c2.txt
    cat $DIR/datacard_c3.txt > $DIR/.tmp.datacard_c3.txt
    cat $DIR/datacard_c8.txt > $DIR/.tmp.datacard_c8.txt
    cat $DIR/datacard_c9.txt > $DIR/.tmp.datacard_c9.txt
    cat $DIR/datacard_n1.txt > $DIR/.tmp.datacard_n1.txt
    cat $DIR/datacard_n2.txt > $DIR/.tmp.datacard_n2.txt
    cat $DIR/datacard_n3.txt > $DIR/.tmp.datacard_n3.txt
    cat $DIR/datacard_n4.txt > $DIR/.tmp.datacard_n4.txt

    echo "---"                               >> $DIR/.tmp.datacard_s1.txt
    echo "---"                               >> $DIR/.tmp.datacard_s2.txt
    echo "---"                               >> $DIR/.tmp.datacard_s3.txt
    echo "---"                               >> $DIR/.tmp.datacard_s4.txt
    echo "---"                               >> $DIR/.tmp.datacard_s5.txt
    echo "---"                               >> $DIR/.tmp.datacard_s6.txt
    # nothing to be done for 0SFOS channel $DIR/.tmp.datacard_s7.txt
    echo "---"                               >> $DIR/.tmp.datacard_s8.txt
    echo "---"                               >> $DIR/.tmp.datacard_s9.txt
    echo "---"                               >> $DIR/.tmp.datacard_c1.txt
    echo "---"                               >> $DIR/.tmp.datacard_c2.txt
    echo "---"                               >> $DIR/.tmp.datacard_c3.txt
    echo "---"                               >> $DIR/.tmp.datacard_c8.txt
    echo "---"                               >> $DIR/.tmp.datacard_c9.txt
    echo "---"                               >> $DIR/.tmp.datacard_n1.txt
    echo "---"                               >> $DIR/.tmp.datacard_n2.txt
    echo "---"                               >> $DIR/.tmp.datacard_n3.txt
    echo "---"                               >> $DIR/.tmp.datacard_n4.txt

    echo "R_in_ee rateParam s1 lostlep 1.71" >> $DIR/.tmp.datacard_s1.txt
    echo "R_in_em rateParam s2 lostlep 0.83" >> $DIR/.tmp.datacard_s2.txt
    echo "R_in_mm rateParam s3 lostlep 0.97" >> $DIR/.tmp.datacard_s3.txt
    echo "R_in_ee rateParam s4 lostlep 1.71" >> $DIR/.tmp.datacard_s4.txt
    echo "R_in_em rateParam s5 lostlep 0.83" >> $DIR/.tmp.datacard_s5.txt
    echo "R_in_mm rateParam s6 lostlep 0.97" >> $DIR/.tmp.datacard_s6.txt
    # nothing to be done for 0SFOS channel $DIR/.tmp.datacard_s7.txt
    echo "R_1sfos rateParam s8 lostlep 0.92" >> $DIR/.tmp.datacard_s8.txt
    echo "R_2sfos rateParam s9 lostlep 1.00" >> $DIR/.tmp.datacard_s9.txt
    echo "R_in_ee rateParam c1 lostlep 1.71" >> $DIR/.tmp.datacard_c1.txt
    echo "R_in_em rateParam c2 lostlep 0.83" >> $DIR/.tmp.datacard_c2.txt
    echo "R_in_mm rateParam c3 lostlep 0.97" >> $DIR/.tmp.datacard_c3.txt
    echo "R_1sfos rateParam c8 lostlep 0.92" >> $DIR/.tmp.datacard_c8.txt
    echo "R_2sfos rateParam c9 lostlep 1.00" >> $DIR/.tmp.datacard_c9.txt

    combineCards.py \
        s1=$DIR/.tmp.datacard_s1.txt \
        s2=$DIR/.tmp.datacard_s2.txt \
        s3=$DIR/.tmp.datacard_s3.txt \
        s4=$DIR/.tmp.datacard_s4.txt \
        s5=$DIR/.tmp.datacard_s5.txt \
        s6=$DIR/.tmp.datacard_s6.txt \
        s7=$DIR/.tmp.datacard_s7.txt \
        s8=$DIR/.tmp.datacard_s8.txt \
        s9=$DIR/.tmp.datacard_s9.txt \
        c1=$DIR/.tmp.datacard_c1.txt \
        c2=$DIR/.tmp.datacard_c2.txt \
        c3=$DIR/.tmp.datacard_c3.txt \
        c8=$DIR/.tmp.datacard_c8.txt \
        c9=$DIR/.tmp.datacard_c9.txt \
        n1=$DIR/.tmp.datacard_n1.txt \
        n2=$DIR/.tmp.datacard_n2.txt \
        n3=$DIR/.tmp.datacard_n3.txt \
        n4=$DIR/.tmp.datacard_n4.txt \
        > $DIR/datacard_combined_w_cr_13.txt

    rm $DIR/.tmp.datacard_*.txt

fi

