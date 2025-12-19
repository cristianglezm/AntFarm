#!/bin/bash

PLATFORM=$1
BUILD_TYPE=$2
SFML_VERSION="2.6.x"
JSONBOX_REPO="https://github.com/cristianglezm/JsonBox"
SFML_REPO="https://github.com/SFML/SFML"

case "$PLATFORM" in
    Linux*)
        echo ">> Building dependencies for Linux..."
        if [ ! -d "JsonBox" ]; then git clone $JSONBOX_REPO; fi
        cd JsonBox && mkdir -p build && cd build
        export JsonBox_ROOT=$(pwd)/install
        cmake -DCMAKE_INSTALL_PREFIX=$JsonBox_ROOT -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DCMAKE_CXX_FLAGS=-fPIC ..
        cmake --build . -j 4 --target install --config $BUILD_TYPE
        cd ../..

        if [ ! -d "SFML" ]; then git clone $SFML_REPO; fi
        cd SFML && git checkout $SFML_VERSION && mkdir -p build && cd build
        export SFML_ROOT=$(pwd)/install
        cmake -DCMAKE_INSTALL_PREFIX=$SFML_ROOT -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DSFML_BUILD_AUDIO=ON -DSFML_BUILD_GRAPHICS=ON ..
        cmake --build . -j 4 --target install --config $BUILD_TYPE
        cd ../..
    ;;

    mac*)
        echo ">> Building dependencies for macOS..."
        if [ ! -d "JsonBox" ]; then git clone $JSONBOX_REPO; fi
        cd JsonBox && mkdir -p build && cd build
        export JsonBox_ROOT=$(pwd)/install
        cmake -DCMAKE_INSTALL_PREFIX=$JsonBox_ROOT -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DCMAKE_CXX_FLAGS="-fPIC" ..
        cmake --build . -j 4 --target install --config $BUILD_TYPE
        cd ../..

        if [ ! -d "SFML" ]; then git clone $SFML_REPO; fi
        cd SFML && git checkout $SFML_VERSION && mkdir -p build && cd build
        export SFML_ROOT=$(pwd)/install
        cmake -DCMAKE_INSTALL_PREFIX=$SFML_ROOT -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DSFML_BUILD_AUDIO=ON -DSFML_BUILD_GRAPHICS=ON ..
        cmake --build . -j 4 --target install --config $BUILD_TYPE
        cd ../..
    ;;

    "Windows MinGW"*)
        echo ">> Building dependencies for Windows (MinGW)..."
        if [ ! -d "JsonBox" ]; then git clone $JSONBOX_REPO; fi
        cd JsonBox && mkdir -p build && cd build
        export JsonBox_ROOT=$(pwd)/install
        cmake -DCMAKE_INSTALL_PREFIX=$JsonBox_ROOT -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -GNinja ..
        cmake --build . -j 4 --target install --config $BUILD_TYPE
        cd ../..

        if [ ! -d "SFML" ]; then git clone $SFML_REPO; fi
        cd SFML && git checkout $SFML_VERSION && mkdir -p build && cd build
        export SFML_ROOT=$(pwd)/install
        cmake -DCMAKE_INSTALL_PREFIX=$SFML_ROOT \
              -DCMAKE_BUILD_TYPE=$BUILD_TYPE \
              -DCMAKE_C_COMPILER=gcc \
              -DCMAKE_CXX_COMPILER=g++ \
              -DSFML_BUILD_AUDIO=ON \
              -DSFML_BUILD_GRAPHICS=ON \
              -GNinja ..
        cmake --build . -j 4 --target install --config $BUILD_TYPE
        cd ../..
    ;;

    Android*)
        echo ">> Building dependencies for Android..."
        export ANDROID_NDK=$ANDROID_SDK_ROOT/ndk/26.2.11394342
        export ANDROID_SOURCES=$ANDROID_NDK/sources/third_party
        export ARCH_ABIS="armeabi-v7a arm64-v8a x86 x86_64"
        export JsonBox_ROOT=$ANDROID_SOURCES/JsonBox
        if [ ! -d "JsonBox" ]; then git clone $JSONBOX_REPO; fi
        cd JsonBox && mkdir -p build && cd build
        for arch in $ARCH_ABIS;do
            cmake --fresh -DCMAKE_INSTALL_PREFIX=$JsonBox_ROOT \
                            -DCMAKE_BUILD_TYPE=$BUILD_TYPE \
                            -DCMAKE_SYSTEM_NAME=Android \
                            -DCMAKE_ANDROID_NDK=$ANDROID_NDK \
                            -DCMAKE_ANDROID_ARCH_ABI="$arch" \
                            -DCMAKE_ANDROID_STL_TYPE=c++_shared \
                            -DCMAKE_ANDROID_API=33 \
                            -DCMAKE_ANDROID_NDK_TOOLCHAIN_VERSION=clang \
                            -DBUILD_SHARED_LIBS=TRUE \
                            -DCMAKE_CXX_FLAGS=-fPIC ..
            cmake --build . -j 4 --target install --config $BUILD_TYPE
        done
        cd ../..

        export SFML_ANDROID_ROOT=${ANDROID_SOURCES}/SFML
        if [ ! -d "SFML" ]; then git clone $SFML_REPO; fi
        cd SFML && git checkout $SFML_VERSION && mkdir -p build && cd build
        for arch in $ARCH_ABIS;do
             rm -rf * 
             cmake -DCMAKE_INSTALL_PREFIX=${SFML_ANDROID_ROOT} \
                   -DCMAKE_BUILD_TYPE=$BUILD_TYPE \
                   -DCMAKE_SYSTEM_NAME=Android \
                   -DCMAKE_ANDROID_NDK=$ANDROID_NDK \
                   -DCMAKE_ANDROID_ARCH_ABI=${arch} \
                   -DCMAKE_ANDROID_STL_TYPE=c++_shared \
                   -DCMAKE_ANDROID_API=33 \
                   -DCMAKE_ANDROID_NDK_TOOLCHAIN_VERSION=clang \
                   ..
             cmake --build . -j 4 --target install --config $BUILD_TYPE
        done
        cd ../..
    ;;

    *)
      echo "Platform '$PLATFORM' not supported in dependency script yet."
      echo "usage:"
      echo "$0 <platform> <build_type>"
      echo "where platforms:"
      echo "    Linux"
      echo "    Windows MinGW"
      echo "    Mac"
      echo "    Android"
      echo "and build_types:"
      echo "    Release"
      echo "    Debug"
    ;;
esac
