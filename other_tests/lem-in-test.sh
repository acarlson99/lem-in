#!/usr/bin/env bash
ONE='flone'
TEN='flten'
THOUSAND='flthousand'
BIG='big'
SOUP='soup'
TMP='/tmp/lem_tmp'
TIME='/usr/bin/time'

if [ -x './generator' ]; then
	VALID='e67102127fa3fcf80786a62bec266895'
	TEST=$(md5 -r generator | cut -d' ' -f1)
	if [ $TEST = $VALID ]; then
		GEN=./generator
	else
		echo "lem-in-test: Error: incorrect checksum"
		exit 1
	fi
else
	echo "lem-in-test: Error: could not find generator binary"
	exit 1
fi

if [ -x './lem-in' ]; then
	BIN='./lem-in'
elif [ -x './lem_in' ]; then
	BIN='./lem_in'
elif [ -x './../lem-in' ]; then
	BIN='./../lem-in'
elif [ -x './../d_lem-in' ]; then
	BIN='./../d_lem-in'
else
	echo "lem-in-test: Error: could not find lem-in binary"
	exit 1
fi

if [ $1 -a $1 = 'one' ]; then
	$GEN --flow-one > $ONE
	$TIME $BIN < $ONE > $TMP
	echo '--------------------------------------------------------------------'
	NODES=$(grep -Ec '^\w+ ' $ONE)
	EDGES=$(grep -Ec '^\w+-' $ONE)
	echo "Total Nodes: $NODES"
	echo "Total Edges: $EDGES"
	echo '--------------------------------------------------------------------'
	printf "Total Ants: $(head -n2 $ONE | sed 's/: /:\\t/g')\n"
	printf "Number of lines from your lem-in:\t$(grep -c '^L' $TMP)\n"
elif [ $1 -a $1 = 'ten' ]; then
	$GEN --flow-ten > $TEN
	$TIME $BIN < $TEN > $TMP
	echo '--------------------------------------------------------------------'
	NODES=$(grep -Ec '^\w+ ' $TEN)
	EDGES=$(grep -Ec '^\w+-' $TEN)
	echo "Total Nodes: $NODES"
	echo "Total Edges: $EDGES"
	echo '--------------------------------------------------------------------'
	printf "Total Ants: $(head -n2 $TEN | sed 's/: /:\\t/g')\n"
	printf "Number of lines from your lem-in:\t$(grep -c '^L' $TMP)\n"
elif [ $1 -a $1 = 'thousand' ]; then
	$GEN --flow-thousand > $THOUSAND
	$TIME $BIN < $THOUSAND > $TMP
	echo '--------------------------------------------------------------------'
	NODES=$(grep -Ec '^\w+ ' $THOUSAND)
	EDGES=$(grep -Ec '^\w+-' $THOUSAND)
	echo "Total Nodes: $NODES"
	echo "Total Edges: $EDGES"
	echo '--------------------------------------------------------------------'
	printf "Total Ants: $(head -n2 $THOUSAND | sed 's/: /:\\t/g')\n"
	printf "Number of lines from your lem-in:\t$(grep -c '^L' $TMP)\n"
elif [ $1 -a $1 = 'big' ]; then
	$GEN --big > $BIG
	$TIME $BIN < $BIG > $TMP
	echo '--------------------------------------------------------------------'
	NODES=$(grep -Ec '^\w+ ' $BIG)
	EDGES=$(grep -Ec '^\w+-' $BIG)
	echo "Total Nodes: $NODES"
	echo "Total Edges: $EDGES"
	echo '--------------------------------------------------------------------'
	printf "Total Ants: $(head -n2 $BIG | sed 's/: /:\\t/g')\n"
	printf "Number of lines from your lem-in:\t$(grep -c '^L' $TMP)\n"
elif [ $1 -a $1 = 'soup' ]; then
	$GEN --big-superposition > $SOUP
	$TIME $BIN < $SOUP > $TMP
	echo '--------------------------------------------------------------------'
	NODES=$(grep -Ec '^\w+ ' $SOUP)
	EDGES=$(grep -Ec '^\w+-' $SOUP)
	echo "Total Nodes: $NODES"
	echo "Total Edges: $EDGES"
	echo '--------------------------------------------------------------------'
	printf "$(head -n2 $SOUP | sed 's/: /:\\t/g')\n"
	printf "Number of lines from your lem-in:\t$(grep -c '^L' $TMP)\n"
elif [ $1 -a $1 = 'clean' ]; then
	rm -f $ONE $TEN $THOUSAND $BIG $SOUP $TMP
elif [ $1 -a $1 = 'help' ]; then
	echo "Usage: $0 [ help | one | ten | thousand | big | soup | clean ]"
	echo "help      show this help summary"
	echo "one       runs the generator with --flow-one"
	echo "ten       runs the generator with --flow-ten"
	echo "thousand  runs the generator with --flow-thousand"
	echo "big       runs the generator with --big"
	echo "soup      runs the generator with --big-superposition"
	echo "clean     removes output map files\n"
	exit 0
else
	echo "lem-in-test: error: invalid argument"
	echo "Usage: $0 [ help | one | ten | thousand | big | soup | clean ]"
	exit 1
fi
