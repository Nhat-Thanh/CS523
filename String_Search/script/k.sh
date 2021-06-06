TEST_NAME=$1
TH=$2
SIZE=$3
grep -f ./test/$TEST_NAME.txt <./TH1/k/k_$SIZE.txt >~/ouput.txt
exit 0
