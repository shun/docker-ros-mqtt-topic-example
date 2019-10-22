<template>
  <div class="mqtt">
    <h1>Mqtt Topic: {{ topic }}</h1>
  </div>
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'vue-property-decorator';
import * as Mqtt from 'mqtt';

@Component
export default class MqttClient extends Vue {
  private topic: string = 'unknown';
  private client!: Mqtt.MqttClient;

  constructor() {
    super();
    this.client = Mqtt.connect('ws://xxx.xxx.xxx.xxx:39090');
  }

  private mounted() {
    this.client.on('connect', () => {
      console.log('conect with broker server');
      this.client.subscribe('/MQTTTopic');
    });

    this.client.on('message', (topic: string, payload: Buffer) => {
      console.log({topic});
      this.topic = topic;
    });

  }

}
</script>

