# AntFarm

[![Build Status](https://travis-ci.org/cristianglezm/AntFarm.svg)](https://travis-ci.org/cristianglezm/AntFarm)

AntFarm is a game about ants that are trapped and they have to escape.

[Game Manual(Spanish)](https://bitbucket.org/cristian_glez_m/antfarm/wiki/Manual%20de%20Juego)

[Video](https://www.youtube.com/watch?v=o17TOI_zKAY)

[Download](https://bitbucket.org/cristian_glez_m/antfarm/downloads)

Requires CMake and one of the following compilers:

* GCC 5.0 or newer;
* Clang 3.3 or newer (Not Tested);
* Visual Studio 2010 or newer (Not Tested);

Building
===

AntFarm requires the following dependencies:

* [SFML](http://sfml-dev.org) 2.3.2 or newer

* [JsonBox](https://github.com/anhero/JsonBox) 0.6.2 or newer

Use CMake to build the project.

```
mkdir build && cd build
cmake -G"MinGW Makefiles" -DSFML_ROOT=<baseDir> -DJSONBOX_ROOT=<baseDir> \ 
	-DAntFarm_WITH_FULLSCREEN=FALSE -DAntFarm_WITH_GUI=FALSE \
	-DAntFarm_RENDER_QTREE=FALSE ..
make
make install
```

Android
==

```
cd android
android update project --name AntFarm --target android-19 --path .
ndk-build
ant debug
```

Contributions
===

You can contribute adding new features from the list.

For example a new action:

* Create a function in [Constructions](https://github.com/cristianglezm/AntFarm/blob/master/src/Systems/constructorSystem/Constructions.cpp)

```
#!c++

constructorSystem::command Constructions::your_function = [](Entity* e,sf::VertexArray* map,sf::FloatRect bounds){
		// do something
	};
```

* then add a key to GameState::handleEvent and send your command With an event.

```
#!c++

	eventQueue->push(std::make_shared<EventsAlias::change_command>(EventType::CHANGE_COMMAND, Constructions::your_function));
```

Documentation
===

The documentation can be generated with cmake adding the option -DAntFarm_BUILD_DOCS=TRUE

