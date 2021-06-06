NUM_FILE=$1
i=0

mkdir -p ./result/TH1/;
mkdir -p ./result/TH2/;
mkdir -p ./result/TH1/n/;
mkdir -p ./result/TH1/k/;
mkdir -p ./result/TH2/n/;

while [ $i -lt "$NUM_FILE" ]
do
	mkdir -p ./result/TH1/n/$((505000 + 5000 * $i));
	mkdir -p ./result/TH1/k/$((100 + 100 * $i));
	mkdir -p ./result/TH2/n/$((10000000 + 10000000 * $i));
	i=$(($i + 1));
done
