#include "configuration.h"
#include "input/InputBroker.h"
#include "input/RotaryEncoderInterruptImpl1.h"
#include "modules/AdminModule.h"
#include "modules/CannedMessageModule.h"
#include "modules/ExternalNotificationModule.h"
#include "modules/NodeInfoModule.h"
#include "modules/PositionModule.h"
#include "modules/RemoteHardwareModule.h"
#include "modules/ReplyModule.h"
#include "modules/RoutingModule.h"
#include "modules/TextMessageModule.h"
#ifndef PORTDUINO
#include "modules/Telemetry/Telemetry.h"
#endif
#ifndef NO_ESP32
#include "modules/esp32/RangeTestPlugin.h"
#include "modules/esp32/SerialPlugin.h"
#include "modules/esp32/StoreForwardPlugin.h"
#endif

/**
 * Create plugin instances here.  If you are adding a new plugin, you must 'new' it here (or somewhere else)
 */
void setupPlugins()
{
    inputBroker = new InputBroker();
    adminPlugin = new AdminPlugin();
    nodeInfoPlugin = new NodeInfoPlugin();
    positionPlugin = new PositionPlugin();
    textMessagePlugin = new TextMessagePlugin();
    
    // Note: if the rest of meshtastic doesn't need to explicitly use your plugin, you do not need to assign the instance
    // to a global variable.

    new RemoteHardwarePlugin();
    new ReplyPlugin();
    rotaryEncoderInterruptImpl1 = new RotaryEncoderInterruptImpl1();
    rotaryEncoderInterruptImpl1->init();
    cannedMessagePlugin = new CannedMessagePlugin();
#ifndef PORTDUINO
    new TelemetryPlugin();
#endif
#ifndef NO_ESP32
    // Only run on an esp32 based device.

    /*
        Maintained by MC Hamster (Jm Casler) jm@casler.org
    */
    new SerialPlugin();
    new ExternalNotificationPlugin();

    // rangeTestPlugin = new RangeTestPlugin();
    storeForwardPlugin = new StoreForwardPlugin();

    new RangeTestPlugin();
    // new StoreForwardPlugin();
#endif

    // NOTE! This plugin must be added LAST because it likes to check for replies from other plugins and avoid sending extra acks
    routingPlugin = new RoutingPlugin();
}