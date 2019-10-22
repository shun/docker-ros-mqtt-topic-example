#include <mosquitto.h>

#include <string>
#include <ros/ros.h>
#include <std_msgs/Int32.h>

struct mosquitto* mqttclient = NULL;

void
connect_callback(
  struct mosquitto *mosq,
  void *obj,
  int result) {

  ROS_INFO("connect_callback: %d\n", result);
}

void
message_callback(
  struct mosquitto *mosq,
  void *obj,
  const struct mosquitto_message *message) {

  ROS_INFO("message_callback\n");

}

void
exampleCallback(
  const std_msgs::Int32::ConstPtr& msg) {

  ROS_INFO("[INFO]: %d", msg->data);

  if (NULL == mqttclient) return;

  const std::string topic = "/MQTTTopic";
  int ret = mosquitto_publish(mqttclient,
      NULL,
      topic.c_str(),
      sizeof(msg->data),
      &msg->data,
      0,
      false);

  ROS_INFO("[INFO] mosquitto_publish: %d\n", ret);
}

int
main(
  int argc,
  char **argv) {

  ros::init(argc, argv, "mqtt_publisher");
  ros::NodeHandle n;

  std::string clientid = "mqttclient1";
  mosquitto_lib_init();
  mqttclient = mosquitto_new(clientid.c_str(), true, NULL);
  if (NULL == mqttclient) {
    ROS_ERROR("fail to create mosquitto client\n");

  } else {
    mosquitto_connect_callback_set(mqttclient, connect_callback);
    mosquitto_message_callback_set(mqttclient, message_callback);
    int ret = mosquitto_connect(mqttclient, "cloud", 1883, 60);
    ROS_INFO("[INFO] mosquitto_connect: %d\n", ret);
    ret = mosquitto_loop_start(mqttclient);
  }

  ros::Subscriber sub = n.subscribe("/example", 1, exampleCallback);
  ros::spin();

  return 0;
}

