#include <com.badlogic.gdx.controllers.desktop.ois.Ois.h>

//@line:47

	#include <OISJoyStick.h>
	#include <OISInputManager.h>
	#include <sstream>
	JNIEXPORT jlong JNICALL Java_com_badlogic_gdx_controllers_desktop_ois_Ois_createInputManager(JNIEnv* env, jobject object, jlong hwnd) {


//@line:53

		std::ostringstream hwndStr;
		hwndStr << hwnd;
		OIS::ParamList params;
		params.insert(std::make_pair("WINDOW", hwndStr.str()));
		//params.insert(std::make_pair("w32_joystick", "DISCL_BACKGROUND"));
		//params.insert(std::make_pair("w32_joystick", "DISCL_NONEXCLUSIVE"));
		OIS::InputManager *inputManager = OIS::InputManager::createInputSystem(params);
		return (jlong)inputManager;
	

}

JNIEXPORT jobjectArray JNICALL Java_com_badlogic_gdx_controllers_desktop_ois_Ois_getJoystickNames(JNIEnv* env, jobject object, jlong inputManagerPtr) {


//@line:64

		OIS::InputManager* inputManager = (OIS::InputManager*)inputManagerPtr;
		OIS::DeviceList map = inputManager->listFreeDevices();
		int joystickCount = inputManager->getNumberOfDevices(OIS::OISJoyStick);
		jobjectArray names = (jobjectArray)env->NewObjectArray(joystickCount, env->FindClass("java/lang/String"), env->NewStringUTF(""));
		int index = 0;
		for (OIS::DeviceList::iterator i = map.begin(); i != map.end(); ++i) {
			if (i->first != OIS::OISJoyStick) continue;
			env->SetObjectArrayElement(names, index++, env->NewStringUTF(i->second.c_str()));
		}
		return names;
	

}

JNIEXPORT jint JNICALL Java_com_badlogic_gdx_controllers_desktop_ois_Ois_getVersionNumber(JNIEnv* env, jobject object, jlong inputManagerPtr) {


//@line:77

		OIS::InputManager* inputManager = (OIS::InputManager*)inputManagerPtr;
	 	return inputManager->getVersionNumber();
	

}

JNIEXPORT jstring JNICALL Java_com_badlogic_gdx_controllers_desktop_ois_Ois_getVersionName(JNIEnv* env, jobject object, jlong inputManagerPtr) {


//@line:82

		OIS::InputManager* inputManager = (OIS::InputManager*)inputManagerPtr;
	 	return env->NewStringUTF(inputManager->getVersionName().c_str());
	 

}

JNIEXPORT jstring JNICALL Java_com_badlogic_gdx_controllers_desktop_ois_Ois_getInputSystemName(JNIEnv* env, jobject object, jlong inputManagerPtr) {


//@line:87

		OIS::InputManager* inputManager = (OIS::InputManager*)inputManagerPtr;
	 	return env->NewStringUTF(inputManager->inputSystemName().c_str());
	 

}

JNIEXPORT jlong JNICALL Java_com_badlogic_gdx_controllers_desktop_ois_Ois_createJoystick(JNIEnv* env, jobject object, jlong inputManagerPtr) {


//@line:92

		OIS::InputManager* inputManager = (OIS::InputManager*)inputManagerPtr;
		try {
			return (jlong)static_cast<OIS::JoyStick*>(inputManager->createInputObject(OIS::OISJoyStick, true));
		} catch (std::exception &ex) {
			printf("Error creating joystick: %s\n", ex.what());
			fflush(stdout);
			return 0;
		}
	

}

