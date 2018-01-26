#!/bin/bash

echo "Initializing submodules"
printf "%20.20s" "SFML"
git submodule update --init lib/SFML > /dev/null
printf "\t\e[1;34m[done]\e[0m\n"
printf "%20.20s" "Boost.Program_options"
git submodule update --init lib/boost > /dev/null
pushd ./lib/boost > /dev/null
git submodule update --init libs/program_options > /dev/null
popd > /dev/null
printf "\t\e[1;34m[done]\e[0m\n"

check_install() {
	printf "%20.20s" "$1"
	apt-get install -qq -o=Dpkg::Use-Pty=0 $2 > /dev/null
	printf "\t\e[1;34m[installed]\e[0m\n"
}

echo "Installing dependencies..."

check_install freetype libfreetype6-dev

check_install JPEG libjpeg-dev

check_install X11 libx11-xcb-dev

check_install Xrandr libxrandr-dev

check_install XCB libxcb1-dev

check_install XCB-randr libxcb-randr0-dev

check_install XCB-image libxcb-image0-dev

check_install openGL freeglut3-dev

check_install FLAC libflac-dev

check_install ogg libogg-dev

check_install vorbis libvorbis-dev

check_install openAL libopenal-dev

check_install pthread libpthread-stubs0-dev

check_install udev libudev-dev

if [ ! -f ./lib/SFML/lib/libsfml-all-s.a ] 
	then
		pushd ./lib/SFML/
		if [ ! -f ./lib/libsfml-graphics-s.a ]
			then
				cmake -G"Unix Makefiles" -DBUILD_SHARED_LIBS=OFF .
				make sfml-graphics
				pushd ./lib
				ar x libsfml-system-s.a
				ar x libsfml-window-s.a
				ar x libsfml-graphics-s.a
				ar rc libsfml-all-s.a *.o
				rm *.o
				popd
				make clean
		fi
		popd
fi


echo "Building Boost.Program_options..."

pushd ./lib/boostorg/boost/
if test -f ./b2; then ./bootstrap.sh gcc; fi
if test ./b2 --build-type=minimal --build-dir=./build --layout=system --with-program_options toolset=gcc variant=release link=static threading=multi runtime-link=shared
