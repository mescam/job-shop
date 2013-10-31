#!/bin/bash
function simple_test {
    mkdir -p tests/output/simple-orlib
    for i in tests/instances/simple-orlib/*; do
        echo "Testing $i ..."
        x=`echo -n $i | cut -d'/' -f3`
        ./bin/jobshop -f $i -t orlib > tests/output/simple-orlib/$x -a greedy
        echo "Done $x... checking with chk_jsorl.exe"
        wine tests/bin/chk_jsorl.exe $i tests/output/simple-orlib/$x
    done
    exit
}

function eff1_test {
    exit
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

echo -n "Selected option: "
read option

case "$option" in
    "1") simple_test ;;
    "2") eff1_test ;;
    "3") eff2_test ;;
    *) echo "Something went wrong..." ;;
esac
