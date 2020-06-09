NAME=$1
NUM=$2
FULL="${1}_${2}"
echo $FULL
sed "s/___/$FULL/g" ./boilerplate.cpp > ../"$FULL".cpp
sed "s/___/$FULL/g" ./config.yml > ../.github/workflows/"$FULL".yml
echo "" | tee ../test_cases/"$FULL"_1_in.txt ../test_cases/"$FULL"_1_out.txt
