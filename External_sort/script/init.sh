mkdir -p bin
mkdir -p result
mkdir -p result/buffer
mkdir -p result/parallel
mkdir -p result/complexity
mkdir -p result/complexity/4000_trieu

SIZE=1
while [ "$SIZE" -lt 51 ]; do
    mkdir -p result/complexity/"$SIZE"_trieu
    SIZE=$(($SIZE + 1))
done

CORE=1
while [ "$CORE" -lt 9 ]; do
    mkdir -p result/parallel/$CORE
    CORE=$(($CORE + 1))
done

BUFFER=50
while [ "$BUFFER" -lt 1001 ]; do
    mkdir -p result/buffer/"$BUFFER"M
    BUFFER=$(($BUFFER + 50))
done
