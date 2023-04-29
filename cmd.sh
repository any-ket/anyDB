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

run(){
	app=$1; shift;
  [[ ! -z "$app" ]] && [[ -f "$PROJ_BIN_PATH/$app" ]] && $PROJ_BIN_PATH/$app $@
}

help(){
  echo "Usage:"
  echo "  b - build"
  echo "  r - run [target]"
  echo "  c - clean all"
}

ACTION="$1";
[[ -z "$ACTION" ]] && help;
shift;

if [[ $ACTION == "b" ]] ; then
  build $@; shift;
elif [[ $ACTION == "r" ]] ; then
  run $@
elif [[ $ACTION == "br" ]] ; then
  build;
  run $@; shift;
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
