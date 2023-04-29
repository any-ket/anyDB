current_directory=$(pwd)

if [ ! -d "$current_directory/build" ]; then
	echo "Creating build directory"
  mkdir build
fi

cd build

echo "generating makefiles...." && cmake ../CMakeLists.txt
echo "building target....." && make