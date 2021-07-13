START=$1  # the smallest database size
END=$2    # the biggest database size
STEP=$3   # discrepacy between 2 adjacent database size

SIZE=$START
END=$(($END + 1))

mkdir -p lsm_db btree_db result bin
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
    mkdir -p btree_db/$SIZE

    # result dir with corresponding size
    mkdir -p result/btree/create_database/$SIZE
    mkdir -p result/btree/open/$SIZE
    mkdir -p result/btree/search/$SIZE
    mkdir -p result/btree/insert/$SIZE
    mkdir -p result/btree/update/$SIZE
    mkdir -p result/btree/delete/$SIZE
    mkdir -p result/lsm/create_database/$SIZE
    mkdir -p result/lsm/open/$SIZE
    mkdir -p result/lsm/search/$SIZE
    mkdir -p result/lsm/insert/$SIZE
    mkdir -p result/lsm/update/$SIZE
    mkdir -p result/lsm/delete/$SIZE

    SIZE=$(($SIZE + $STEP))
done
exit 0
