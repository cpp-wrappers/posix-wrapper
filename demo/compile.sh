demo=`dirname ${BASH_SOURCE[1]}`
name=`basename ${BASH_SOURCE[1]}`
name="${name%.*}"

pushd ${demo} > /dev/null
mkdir -p ../build
clang++ \
	--config=./compile_flags.txt \
	-o ../build/${name} ${name}.cpp
popd > /dev/null

exit 0