START=$1
END=$2
STEP=$3

SIZE=$START
END=$(($END + 1))

mkdir -p lsm_db btree_db result bin
touch result/.gitkeep
mkdir -p result/btree
mkdir -p result/btree/create_database
mkdir -p result/btree/open
mkdir -p result/btree/search
mkdir -p result/btree/insert
mkdir -p result/btree/update
mkdir -p result/btree/delete
mkdir -p result/lsm
mkdir -p result/lsm/create_database
mkdir -p result/lsm/open
mkdir -p result/lsm/search
mkdir -p result/lsm/insert
mkdir -p result/lsm/update
mkdir -p result/lsm/delete

while [ "$SIZE" -lt "$END" ]; do
    # database dir
    mkdir -p lsm_db/$SIZE
    touch lsm_db/$SIZE/.gitkeep
    mkdir -p btree_db/$SIZE
    touch btree_db/$SIZE/.gitkeep

    # result dir with corresponding size
    mkdir -p result/btree/create_database/$SIZE
    touch result/lsm/create_database/$SIZE/.gitkeep

    mkdir -p result/btree/open/$SIZE
    touch result/btree/open/$SIZE/.gitkeep

    mkdir -p result/btree/search/$SIZE
    touch result/btree/search/$SIZE/.gitkeep

    mkdir -p result/btree/insert/$SIZE
    touch result/btree/insert/$SIZE/.gitkeep
    
    mkdir -p result/btree/update/$SIZE
    touch result/btree/update/$SIZE/.gitkeep

    mkdir -p result/btree/delete/$SIZE
    touch result/btree/delete/$SIZE/.gitkeep
    
    mkdir -p result/lsm/create_database/$SIZE
    touch result/lsm/create_database/$SIZE/.gitkeep

    mkdir -p result/lsm/open/$SIZE
    touch result/lsm/open/$SIZE/.gitkeep

    mkdir -p result/lsm/search/$SIZE
    touch result/lsm/search/$SIZE/.gitkeep

    mkdir -p result/lsm/insert/$SIZE
    touch result/lsm/insert/$SIZE/.gitkeep

    mkdir -p result/lsm/update/$SIZE
    touch result/lsm/update/$SIZE/.gitkeep
    
    mkdir -p result/lsm/delete/$SIZE
    touch result/lsm/delete/$SIZE/.gitkeep

    SIZE=$(($SIZE + $STEP))
done

# mkdir -p lsm_db/1000000000
# mkdir -p btree_db/1000000000
# mkdir -p result/lsm/stress_test
# mkdir -p result/btree/stress_test
# i=1
# while [ "$i" -lt 11 ]; do
#     mkdir -p result/lsm/stress_test/$i
#     mkdir -p result/btree/stress_test/$i
#     i=$(($i + 1))
# done
