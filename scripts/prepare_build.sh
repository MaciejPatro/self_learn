
repo_dir=$(pwd)
cd ..
if [ ! -d "build" ]; then
    mkdir build
fi
cd build
if [ ! -d $1 ]; then
    mkdir $1
fi
cd $1
cmake -D CMAKE_CXX_COMPILER=clang++ -D $2 $repo_dir
