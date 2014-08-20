# AntFarm #

AntFarm es un juego sobre hormigas que están atrapadas y tienen que escapar.

[Manual del Juego](https://bitbucket.org/cristian_glez_m/antfarm/wiki/Manual%20de%20Juego)

[Video](https://www.youtube.com/watch?v=o17TOI_zKAY)

[Download](https://bitbucket.org/cristian_glez_m/antfarm/downloads)

Requires CMake and one of the following compilers:

* GCC 4.8 or newer;
* Clang 3.3 or newer (Xcode 5.0 or newer on OS X);
* Visual Studio 2010 or newer;

Building
===

AntFarm requires the following dependencies:

* [SFML](http://sfml-dev.org) 2.1 or newer

* [JsonBox](https://github.com/anhero/JsonBox) 0.4.4 or newer

Use CMake to build the project.

* select the root directory of JsonBox

* select the root directory of SFML

* press configure and then generate Project.


Contributions
===

You can contribute adding new features from the list.

For example a new action:

* Create a function in Constructions (Systems/constructorSystems/constructions)

```
#!c++

constructorSystem::command Constructions::your_function = [](Entity* e,sf::VertexArray* map,sf::FloatRect bounds){
		// do something
	};
```

* then add a key to GameState::processInput and send your command With an event.

```
#!c++

	eventQueue->push(std::shared_ptr<baseEvent>(
                            new Event<constructorSystem::command>(EventType::CHANGE_COMMAND,
                                                    Constructions::your_function
                                                    ))
                                 );
```

Documentation
===

The documentation can be found on "doc" or be generated with doxygen(it needs to be configured)