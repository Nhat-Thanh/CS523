i=0

mkdir ./result/TH1/;
mkdir ./result/TH2/;
mkdir ./result/TH1/n/;
mkdir ./result/TH1/k/;
mkdir ./result/TH2/n/;

while [ $i -lt 100 ]
do
	mkdir ./result/TH1/n/$((505000 + 5000 * $i));
	mkdir ./result/TH1/k/$((100 + 100 * $i));
	mkdir ./result/TH2/n/$((10000000 + 10000000 * $i));
	i=$(($i + 1));
done
