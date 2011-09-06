# ofxConnexion wraps 3dConnexionClient for openFrameworks on OSX

http://www.3dconnexion.com/
http://openframeworks.cc/

Using ofxConnexion with your project requires three important steps:

* Adding the ofxConnexion/src to your project
* Adding 3dConnexionClient.framework to your project
* Adding this line to Project.xcconfig: `GCC_PREPROCESSOR_DEFINITIONS = EXECUTABLE_NAME="\"$(EXECUTABLE_NAME)\""`