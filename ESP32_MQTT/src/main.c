
#include "nvs_flash.h"
// MQTT Stuff
#include "mqtt.h"
// Host
#include "host.h"
// Debug
#include "esp_log.h"

const char* Wifi_SSID = "VirtualRealitySystem";
const char* Wifi_Pass = "guorui0905";

// AWS Stuff
#define CONFIG_AWS_IOT_MQTT_TX_BUF_LEN 100
#define CONFIG_AWS_IOT_MQTT_RX_BUF_LEN 100
#define CONFIG_AWS_IOT_MQTT_NUM_SUBSCRIBE_HANDLERS 4

const char* Mqtt_Broker_Url  = "mqtts://a2y8qdidr5a6vr-ats.iot.us-east-2.amazonaws.com";
// Host object
host_t host;
void send_env_data(host_t* host);

int nCount = 0;

void app_main(void)
{
  //Initialize NVS
  esp_err_t ret = nvs_flash_init();
  if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
    ESP_ERROR_CHECK(nvs_flash_erase());
    ret = nvs_flash_init();
  }
  ESP_ERROR_CHECK(ret);

  host.wifi_creds.Wifi_SSID = Wifi_SSID;
  host.wifi_creds.Wifi_Pass = Wifi_Pass;

  init_host(&host);

  mqtt_app_start(Mqtt_Broker_Url, &(host.mqtt_client));
  while(1)
  {
    send_env_data(&host);
    vTaskDelay(MS2TICK(3000));
  }
}

void send_env_data(host_t* host)
{
  int msg_id;
  char buff[40];
  // htu21_data_t env_data;
  // if(host->htu21.msg_queue == NULL)
  // {
  //   LOG_ERROR("MSG queue does not exist cannot send enviornment data.");
  // }

  // xQueuePeek(host->htu21.msg_queue, &env_data, 5);
  // sprintf(buff, "{\"temperature\": %.2f, \"humidity\": %.2f}",
  //   env_data.temperature, env_data.humidity);

  sprintf(buff, "{\"temperature\": 77.00, \"Count\": %d}", nCount);
  // strcpy(buff, "{\"temperature\": 77.00, \"humidity\": 30.25}");
  msg_id = esp_mqtt_client_publish(host->mqtt_client, "env_data",
    buff, 0, 1, 0);
  LOG_PRINTF("Sent publish successful, msg_id=%d", msg_id);
  nCount = nCount + 1;
}