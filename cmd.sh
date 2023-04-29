current_directory=$(pwd)
PROJ_BUILD_PATH="$current_directory/build"
PROJ_BIN_PATH="$current_directory/bin"

build(){
	if [ ! -d PROJ_BUILD_PATH ]; then
		echo "Creating build directory"
	  mkdir build
	fi

	cd build

	echo "generating makefiles...." && cmake ../CMakeLists.txt
	echo "building target....." && make
}

runCli(){
	bin/cli
}

runServer(){
	bin/server
}

help(){
  echo "Usage:"
  echo "  b       - build"
  echo "  cli     - run cli"
  echo "  server  - run server"
  echo "  c       - clean all"
}

ACTION="$1";
[[ -z "$ACTION" ]] && help;
shift;

if [[ $ACTION == "b" ]] ; then
  build $@; shift;
elif [[ $ACTION == "cli" ]] ; then
  runCli $@
elif [[ $ACTION == "server" ]] ; then
  runServer $@
elif [[ $ACTION == "cb" ]] ; then
  rm -rf $PROJ_BUILD_PATH
  rm -rf $PROJ_BIN_PATH
  build;
elif [[ $ACTION == "c" ]]; then
  rm -rf $PROJ_BUILD_PATH;
  rm -rf $PROJ_BIN_PATH
elif [[ $ACTION == "h" ]]; then
  help
else
  echo "Invalid action: $ACTION"
  help
fi
