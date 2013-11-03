#!/bin/bash
function simple_test {
    mkdir -p tests/output/simple-orlib
    for i in tests/instances/simple-orlib/*; do
        echo "Testing $i ..."
        x=`echo -n $i | cut -d'/' -f4`
        ./bin/jobshop -f $i -t orlib > tests/output/simple-orlib/$x -a greedy
        echo "Done $x... checking with chk_jsorl.exe"
        wine tests/bin/chk_jsorl.exe $i tests/output/simple-orlib/$x
    done
    exit
}

function full_orlib_test {
    mkdir -p tests/output/beasley
    for i in tests/instances/beasley/*; do
        echo "Testing $i..."
        x=`echo -n $i | cut -d'/' -f4`
        ./bin/jobshop -f $i -t orlib > tests/output/beasley/$x -a greedy
        echo "Done $x... checking with chk_jsorl.exe"
        wine tests/bin/chk_jsorl.exe $i tests/output/beasley/$x
    done
    exit
}

function eff1_test {
    x="tai20 tai21 tai22 tai23 tai24 tai25 tai26 tai27 tai28 tai29 tai30"
    IFS=' '
    mkdir -p tests/output/tailard
    mkdir -p tests/output/eff1
    touch tests/output/eff1/data
    touch tests/output/eff1/data2
    echo -n "" > tests/output/eff1/data
    echo -n "" > tests/output/eff1/data2
    lbound="1318 1573 1542 1474 1606 1518 1558 1617 1591 1525 1485"
    ubound="1348 1642 1600 1557 1644 1595 1643 1680 1603 1625 1584"
    larr=($(echo $lbound))
    uarr=($(echo $ubound))
    j=0
    for i in $x; do
        echo "Testing... $i"
        ./bin/jobshop -f tests/instances/tailard/$i.txt -t taillard > tests/output/tailard/$i.txt -a greedy -m
        echo "Done $i"
        z=`cat tests/output/tailard/$i.txt | head -n 1`
        a=`cat tests/output/tailard/$i.txt | tail -n 1`
        echo "$i ${larr[$j]} ${uarr[$j]} $z" >> tests/output/eff1/data
        echo "$i $a" >> tests/output/eff1/data2
        j=`expr $j + 1`
    done
    gnuplot tests/gnuplot/eff1-plot1.gplt
    gnuplot tests/gnuplot/eff1-plot2.gplt
}

function eff2_test {
    mkdir -p tests/output/eff2
    echo -n "" > tests/output/eff2/data
    for x in `seq 20`; do
        licznik=0
        echo "Testing tai25 for n=$x"
        for i in `seq 1000`; do
            ./bin/jobshop -f tests/instances/tailard/tai25.txt -n $x -t taillard -a greedy -m > temp
            t=`tail -n 1 temp`
            licznik=`perl -e "print $licznik+$t"`
        done
        t=`perl -e "print $licznik/1000"`
        echo "$x $t" >> tests/output/eff2/data
    done;
    rm temp
    gnuplot tests/gnuplot/eff2-plot.gplt
}

echo "*************************************************************************"
echo "* Welcome to Automated Testing System for Job-Shop Scheduling algorithm *"
echo "*                Combinatorial Optimisation Laboratory                  *"
echo "*                     Faculty of Computer Science                       *"
echo "*                   Poznan University of Technology                     *"
echo "*                    Jakub Wozniak, Marcin Zaremba                      *"
echo "*************************************************************************"
echo ""
echo "Available tests:"
echo "1) Simple test (for algorithm testing only)"
echo "2) Efficiency test (time and quality for ta20-ta25)"
echo "3) Efficiency test 2 (time for n=1..20 ta25)"
echo "4) Full orlib test"
read option

case "$option" in
    "1") simple_test ;;
    "2") eff1_test ;;
    "3") eff2_test ;;
    "4") full_orlib_test ;;
    *) echo "Something went wrong..." ;;
esac
