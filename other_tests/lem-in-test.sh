#!/usr/bin/env bash
# TODO: better handling of options and arguments
# option to append 'date +%Y-%m-%dT%H:%M:%S%z' to the output filename

ONE='flone_input'
TEN='flten_input'
THOUSAND='flthousand_input'
BIG='big_input'
SOUP='soup_input'
TMPIN='/tmp/lem_tmp_input'
TMPOUT='/tmp/lem_tmp_output'

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
	$GEN --flow-one > $TMPIN
	cp $TMPIN $ONE
	$BIN < $TMPIN > $TMPOUT
	cp $TMPOUT $(echo $ONE | sed 's/_input/_output/g')
	echo '--------------------------------------------------------------------'
	NODES=$(grep -Ec '^\w+ ' $TMPIN)
	EDGES=$(grep -Ec '^\w+-' $TMPIN)
	echo "Total Nodes: $NODES"
	echo "Total Edges: $EDGES"
	printf "Total Ants: $(head -n2 $TMPIN | sed 's/: /:\\t/g')\n"
	printf "Number of lines from your lem-in:\t$(grep -c '^L' $TMPOUT)\n"
	echo '--------------------------------------------------------------------'
elif [ $1 -a $1 = 'ten' ]; then
	$GEN --flow-ten > $TMPIN
	cp $TMPIN $TEN
	$BIN < $TMPIN > $TMPOUT
	cp $TMPOUT $(echo $TEN | sed 's/_input/_output/g')
	echo '--------------------------------------------------------------------'
	NODES=$(grep -Ec '^\w+ ' $TMPIN)
	EDGES=$(grep -Ec '^\w+-' $TMPIN)
	echo "Total Nodes: $NODES"
	echo "Total Edges: $EDGES"
	printf "Total Ants: $(head -n2 $TMPIN | sed 's/: /:\\t/g')\n"
	printf "Number of lines from your lem-in:\t$(grep -c '^L' $TMPOUT)\n"
	echo '--------------------------------------------------------------------'
elif [ $1 -a $1 = 'thousand' ]; then
	$GEN --flow-thousand > $TMPIN
	cp $TMPIN $THOUSAND
	$BIN < $TMPIN > $TMPOUT
	cp $TMPOUT $(echo $THOUSAND | sed 's/_input/_output/g')
	echo '--------------------------------------------------------------------'
	NODES=$(grep -Ec '^\w+ ' $TMPIN)
	EDGES=$(grep -Ec '^\w+-' $TMPIN)
	echo "Total Nodes: $NODES"
	echo "Total Edges: $EDGES"
	printf "Total Ants: $(head -n2 $TMPIN | sed 's/: /:\\t/g')\n"
	printf "Number of lines from your lem-in:\t$(grep -c '^L' $TMPOUT)\n"
	echo '--------------------------------------------------------------------'
elif [ $1 -a $1 = 'big' ]; then
	$GEN --big > $TMPIN
	cp $TMPIN $BIG
	$BIN < $TMPIN > $TMPOUT
	cp $TMPOUT $(echo $BIG | sed 's/_input/_output/g')
	echo '--------------------------------------------------------------------'
	NODES=$(grep -Ec '^\w+ ' $TMPIN)
	EDGES=$(grep -Ec '^\w+-' $TMPIN)
	echo "Total Nodes: $NODES"
	echo "Total Edges: $EDGES"
	printf "Total Ants: $(head -n2 $TMPIN | sed 's/: /:\\t/g')\n"
	printf "Number of lines from your lem-in:\t$(grep -c '^L' $TMPOUT)\n"
	echo '--------------------------------------------------------------------'
elif [ $1 -a $1 = 'soup' ]; then
	$GEN --big-superposition > $TMPIN
	cp $TMPIN $SOUP
	$BIN < $TMPIN > $TMPOUT
	cp $TMPOUT $(echo $SOUP | sed 's/_input/_output/g')
	echo '--------------------------------------------------------------------'
	NODES=$(grep -Ec '^\w+ ' $TMPIN)
	EDGES=$(grep -Ec '^\w+-' $TMPIN)
	echo "Total Nodes: $NODES"
	echo "Total Edges: $EDGES"
	printf "Total Ants: $(head -n2 $TMPIN | sed 's/: /:\\t/g')\n"
	printf "Number of lines from your lem-in:\t$(grep -c '^L' $TMPOUT)\n"
	echo '--------------------------------------------------------------------'
elif [ $1 -a $1 = 'clean' ]; then
	rm -f $TMPIN $TMPOUT
elif [ $1 -a $1 = 'fclean' ]; then
	rm -f $ONE $TEN $THOUSAND $BIG $SOUP $TMPIN $TMPOUT
	rm -f $(echo $ONE | sed 's/_input/_output/g')
	rm -f $(echo $TEN | sed 's/_input/_output/g')
	rm -f $(echo $THOUSAND | sed 's/_input/_output/g')
	rm -f $(echo $BIG | sed 's/_input/_output/g')
	rm -f $(echo $SOUP | sed 's/_input/_output/g')
elif [ $1 -a $1 = 'help' ]; then
	echo "Usage: $0 [ help | one | ten | thousand | big | soup | clean | fclean ]"
	echo "  help      show this help summary"
	echo "  one       runs the generator with --flow-one"
	echo "  ten       runs the generator with --flow-ten"
	echo "  thousand  runs the generator with --flow-thousand"
	echo "  big       runs the generator with --big"
	echo "  soup      runs the generator with --big-superposition"
	echo "  clean     removes temporary files"
	echo "  fclean    removes all output files"
	exit 0
else
	echo "lem-in-test: error: invalid argument"
	echo "Usage: $0 [ help | one | ten | thousand | big | soup | clean | fclean ]"
	exit 1
fi
