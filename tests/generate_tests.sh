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
    x="tai20 tai21 tai22 tai23 tai24 tai25"
    mkdir -p tests/output/tailard
    mkdir -p tests/output/eff1
    touch tests/output/eff1/data
    echo $x > tests/output/eff1/data
    echo "1591 2297 2099 2326 2223 2291" >> tests/output/eff1/data
    z=""
    for i in $x; do
        echo "Testing... $i"
        ./bin/jobshop -f tests/instances/tailard/$i.txt -t taillard > tests/output/tailard/$i.txt -a greedy -m
        echo "Done $i"
        z=z+`cat tests/output/tailard/$i.txt | tail -n 1`+" "
    done
    echo $z > tests/output/eff1/data
}

function eff2_test {
    exit
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
