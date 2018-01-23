#!/bin/bash

pushd lib/SFML/
cmake -DBUILD_SHARED_LIBS=NO .
make

if [ ! -f lib/SFML/lib/libsfml-all-s.a ]; then
pushd lib/
ar -M <<EOF
   CREATE libsfml-all-s.a
   ADDLIB libsfml-graphics-s.a
   ADDLIB libsfml-system-s.a
   ADDLIB libsfml-network-s.a
   ADDLIB libsfml-window-s.a
   SAVE
   END
EOF
popd
fi

popd
