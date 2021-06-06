TEST_NAME=$1
TH=$2
SIZE=$3

/usr/bin/time -v -o ./result/TH1/k/$SIZE/$TEST_NAME.txt \
	grep -f ./test/$TEST_NAME.txt <./TH1/k/k_"$SIZE".txt >ouput.txt

exit 0