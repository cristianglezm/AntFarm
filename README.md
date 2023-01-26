# AntFarm

|Linux \| windows(MinGW) | ![Build Status](https://github.com/cristianglezm/antfarm/actions/workflows/ci.yml/badge.svg)|
|---|---|
|Android |![Build Status](https://github.com/cristianglezm/antfarm/actions/workflows/ci.yml/badge.svg)|

AntFarm is a game about ants that are trapped and they have to escape.

[Game Manual(Spanish)](https://bitbucket.org/cristian_glez_m/antfarm/wiki/Manual%20de%20Juego)

[Video](https://www.youtube.com/watch?v=o17TOI_zKAY)

[Download](https://bitbucket.org/cristian_glez_m/antfarm/downloads)

Requires CMake and one of the following compilers:

* GCC 8.1 or newer;
* Clang 3.3 or newer (Not Tested);
* Visual Studio 2010 or newer (Not Tested);

Building
===

AntFarm requires the following dependencies:

* [SFML](http://sfml-dev.org) 2.6.x

* [JsonBox](https://github.com/cristianglezm/JsonBox) 0.6.2 or newer

Use CMake to build the project.

```cmake
mkdir build && cd build
cmake -G"MinGW Makefiles" -DSFML_ROOT=<baseDir> -DJSONBOX_ROOT=<baseDir> \ 
	-DAntFarm_WITH_FULLSCREEN=FALSE -DAntFarm_WITH_GUI=FALSE \
	-DAntFarm_RENDER_QTREE=FALSE ..
make
make install
```

Android
==

You should replace <android_sdk> and <android_ndk> with the actual folder.

```cmake
export SDK_DIR=<android_sdk>
export NDK_DIR=<android_ndk>
git clone https://github.com/SFML/SFML SFML
cd SFML
mkdir build && cd build && mkdir armeabi-v7a && cd armeabi-v7a
cmake -DCMAKE_SYSTEM_NAME=Android -DCMAKE_ANDROID_NDK=$NDK_DIR \
        -DCMAKE_ANDROID_ARCH_ABI=armeabi-v7a -DCMAKE_ANDROID_STL_TYPE=c++_shared \
        -DCMAKE_BUILD_TYPE=Release -DCMAKE_ANDROID_NDK_TOOLCHAIN_VERSION=clang -DCMAKE_ANDROID_API=27 \
        -DCMAKE_INSTALL_PREFIX=$NDK_DIR/sources/third_party/sfml ../..
make install
cd ../../..
git clone https://github.com/cristianglezm/JsonBox JsonBox
cd JsonBox && mkdir build && cd build && mkdir armeabi-v7a && cd armeabi-v7a
cmake -DCMAKE_SYSTEM_NAME=Android -DCMAKE_ANDROID_NDK=$NDK_DIR \
        -DCMAKE_ANDROID_ARCH_ABI=armeabi-v7a -DCMAKE_ANDROID_STL_TYPE=c++_shared \
        -DCMAKE_BUILD_TYPE=Release -DCMAKE_ANDROID_NDK_TOOLCHAIN_VERSION=clang -DCMAKE_ANDROID_API=27 \
        -DCMAKE_INSTALL_PREFIX=$NDK_DIR/sources/third_party/JsonBox ../..
make install
cd ../../..
git clone https://github.com/cristianglezm/antfarm Antfarm
cd Antfarm && cd android
echo "sdk.dir=$SDK_DIR" > local.properties
echo "ndk.dir=$NDK_DIR" >> local.properties
gradle build
[gradle installDebug]

```

Contributions
===

You can contribute adding new features from the list.

For example a new action:

* Create a function in [Constructions](https://github.com/cristianglezm/AntFarm/blob/master/src/Systems/constructorSystem/Constructions.cpp)

```cpp
constructorSystem::command Constructions::your_function = [](Entity* e,sf::VertexArray* map, sf::FloatRect bounds){
		// do something
	};
```

* then add a key to GameState::handleEvent and send your command With an event.

```cpp
	eventQueue->push(std::make_shared<EventsAlias::change_command>(EventType::CHANGE_COMMAND,
				Constructions::your_function));
```

Documentation
===

The documentation can be generated with cmake adding the option -DAntFarm_BUILD_DOCS=TRUE

