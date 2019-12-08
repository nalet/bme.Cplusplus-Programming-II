Producer Consumer Pattern
=========================
This repo contains a basic example of a producer-consumer pattern

## Exercises ##

Exercise 06: Observer Pattern
------------------------------
 * Implement the observer pattern to reduce coupling and increase code reuse. In particular, remove compile time dependencies by:
 1. decoupling module Control from Module VCamera, i.e. VCamera should compile without the knowledge of module Control
 2. decoupling module Widget from Module Control, i.e. Control should compile without the knowledge of module Widget
 * Therefore, you have to implement an abstract interface IVCamera for VCamera and IControl for Control
    
Exercise 07: Factory Method
------------------------------
 * Implement the Factory Method allowing to choose the camera device at run-time. In particular:
 1. implement an ABC for camera (_e.g._ named _BaseCamera_ ) providing pure virtual methods for all "common" methods of camera, _i.e._:
    - void startPlayData();
    - void stop();
    - bool isPlaying();
    - void setPlayRate(int playRate);
* The constructor takes _host_ interface and _dataBufferPool_ as arguments (see exercise 06).
* _VCamera_ should now inherit from _BaseCamera_ and implement its functionality
* Use _initializer_ _lists_ to initialise the base classes.
* Add a new camera _e.g._ named _VRgbCamera_ as second camera. Let this camera produces coloured images.

 2. Implement the camera factory returning unique pointers to the respective camera class.
 3. In control, create an instance of the camera factory and get the desired camera, which e.g. can be chosen from a _QCombobox_ on the GUI.
    