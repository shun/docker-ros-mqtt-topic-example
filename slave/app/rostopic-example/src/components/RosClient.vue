<template>
  <div class="ros">
    <h1>Received topic: {{ topic }}</h1>
    <button v-on:click="pub">BUTTON</button>
  </div>
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'vue-property-decorator';
import { Ros, Topic, Message } from 'roslib'

@Component
export default class RosClient extends Vue {
  private topic: string = 'unkown';
  private ros: Ros;
  private bridge_server_uri: string;

  constructor() {
    super();
    this.bridge_server_uri = 'xxx.xxx.xxx.xxx';
    this.ros = new Ros({});
  }

  private mounted() {
    console.log('mounted');
    const uri = 'ws://' + this.bridge_server_uri + ':29090';
    try {
      this.ros.connect(uri);
      this.ros.on('connection', () => {
        console.log('[INFO]: connection');
      });

      this.ros.on('error', err  => {
        console.log('[ERROR]: ' + err);
      });

      this.ros.on('close', () => {
        console.log('[INFO]: close');
      });

      this.start_listen();

    } catch (e) {
      console.log('[ERROR]: ' + e);
    }
  }

  private start_listen() {
    const listener = new Topic({
      ros: this.ros,
      name: '/example',
      messageType: 'std_msgs/Int32'});

    listener.subscribe(message => {
      console.log('[INFO]: topic: ' + listener.name + ', payload: ' + message.data);
      this.topic = listener.name;
    });
  }

  private pub() {
    const topic = new Topic({
      ros: this.ros,
      name: '/example',
      messageType: 'std_msgs/Int32'});

    const msg = new Message({
                  data: 1234
                });
    topic.publish(msg);

  }
}
</script>
