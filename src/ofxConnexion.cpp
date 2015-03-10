#include "ofxConnexion.h"

bool ConnexionData::getButton(int button) {
	return (buttonState & (1 << button)) != 0;
}

ofEvent<ConnexionData> ofxConnexion::connexionEvent;
ConnexionData ofxConnexion::connexionData;
UInt16 ofxConnexion::clientId;

void ofxConnexion::start() {
	InstallConnexionHandlers(driverHandler, 0L, 0L);
	clientId = RegisterConnexionClient(0, NULL, kConnexionClientModeTakeOver, kConnexionMaskAll);
}

void ofxConnexion::stop() {
	UnregisterConnexionClient(clientId);
	CleanupConnexionHandlers();
}

// http://www.3dconnexion.com/forum/viewtopic.php?t=4266
#define OFX_CONNEXION_LED_ON (0x00010001)
#define OFX_CONNEXION_LED_OFF (0x00010000)

void ofxConnexion::setLed(bool state) {
	SInt32 result;
	ConnexionClientControl(clientId, kConnexionCtlSetLEDState, state ? OFX_CONNEXION_LED_ON : OFX_CONNEXION_LED_OFF, &result);
}

void ofxConnexion::driverHandler(io_connect_t connection, natural_t messageType, void *messageArgument) {
	ConnexionDeviceStatePtr msg = (ConnexionDeviceStatePtr)messageArgument;
	switch(messageType) {
		case kConnexionMsgDeviceState:
			switch (msg->command) {
				case kConnexionCmdHandleAxis: {
					memcpy(connexionData.translation, &(msg->axis[0]), 3 * sizeof(short));
					memcpy(connexionData.rotation, &(msg->axis[3]), 3 * sizeof(short));
				}
				case kConnexionCmdHandleButtons: {
					connexionData.deviceId = msg->address;
					connexionData.buttonState = msg->buttons;
					
					ofNotifyEvent(connexionEvent, connexionData);
				}
			}
	}
}
