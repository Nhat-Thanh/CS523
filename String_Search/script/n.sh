TEST_NAME=$1
TH=$2
SIZE=$3
grep -f ./test/$TEST_NAME.txt <./$TH/n/n_$SIZE.txt >~/output.txt
exit 0
