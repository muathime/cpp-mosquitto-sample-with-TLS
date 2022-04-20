#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <mosquitto.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
using namespace std;

#define MQTT_HOSTNAME "a1ek3lbmx2jfb9-ats.iot.eu-west-1.amazonaws.com"
#define MQTT_PORT 8883
#define MQTT_CLIENTID "1918171615"
#define MQTT_TOPIC "$aws/things/1918171615/shadow/update"

string payload = "{\"state\":{\"reported\":{\"Timestamp\":\"2022-04-07T18:10:46.000Z\",\"ignition\":100,\"movement\":100,\"latlng\":\"-1.2322516,36.9206783\",\"Latitude\":-1.2322516,\"Longitude\":36.9206783,\"Altitude\":1595,\"Speed\":100},\"desired\":null}}";
const char *text = payload.c_str();

static bool connected = true;
static bool disconnect_sent = false;
static int mid_sent = 0;
static int qos = 0;
static int retain = 0;

void my_connect_callback(struct mosquitto *mosq, void *obj, int result)
{
    int rc = MOSQ_ERR_SUCCESS;

    if (!result)
    {
        std::cout << "Sending message..." << std::endl;
        rc = mosquitto_publish(mosq, NULL, MQTT_TOPIC, strlen(text), text, qos, retain);
        if (rc)
        {
            switch (rc)
            {
            case MOSQ_ERR_INVAL:
                std::cout << "Error: Invalid input. Does your topic contain '+' or '#'?" << std::endl;
                break;
            case MOSQ_ERR_NOMEM:
                std::cout << "Error: Out of memory when trying to publish message." << std::endl;
                break;
            case MOSQ_ERR_NO_CONN:
                std::cout << "Error: Client not connected when trying to publish." << std::endl;
                break;
            case MOSQ_ERR_PROTOCOL:
                std::cout << "Error: Protocol error when communicating with broker." << std::endl;
                break;
            case MOSQ_ERR_PAYLOAD_SIZE:
                std::cout << "Error: Message payload is too large." << std::endl;
                break;
            }
            mosquitto_disconnect(mosq);
        }
    }
    else
    {
        if (result)
        {
            std::cout << mosquitto_connack_string(result) << "oops!" << std::endl;
        }
    }
}

void my_disconnect_callback(struct mosquitto *mosq, void *obj, int rc)
{
    std::cout << "Disconnected!" << std::endl;
    connected = false;
}

void my_publish_callback(struct mosquitto *mosq, void *obj, int mid)
{
    std::cout << "Published!" << std::endl;
    if (disconnect_sent == false)
    {
        mosquitto_disconnect(mosq);
        disconnect_sent = true;
    }
}

int main(int argc, char *argv[])
{
    struct mosquitto *mosq = NULL;

    mosquitto_lib_init();
    // mosquitto_tls_insecure_set(mosq, true);

    mosq = mosquitto_new(MQTT_CLIENTID, true, NULL);
    if (!mosq)
    {
        std::cout << "Cant initiallize mosquitto library" << std::endl;
        exit(-1);
    }

    mosquitto_connect_callback_set(mosq, my_connect_callback);
    mosquitto_disconnect_callback_set(mosq, my_disconnect_callback);
    mosquitto_publish_callback_set(mosq, my_publish_callback);

    // mosquitto_username_pw_set(mosq, MQTT_USERNAME, MQTT_PASSWORD);

    mosquitto_tls_set(mosq, "/home/antony/Downloads/1918171615/ca.pem", NULL, "/home/antony/Downloads/1918171615/cert.pem", "/home/antony/Downloads/1918171615/privkey.pem", NULL);

    int ret = mosquitto_connect(mosq, MQTT_HOSTNAME, MQTT_PORT, 60);
    if (ret)
    {
        std::cout << "Cant connect to mosquitto server 1" << std::endl;
        exit(-1);
    }

    int rc;
    do
    {
        rc = mosquitto_loop(mosq, -1, 1);
    } while (rc == MOSQ_ERR_SUCCESS && connected);

    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();

    return 0;
}