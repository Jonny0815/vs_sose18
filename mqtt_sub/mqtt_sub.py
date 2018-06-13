import paho.mqtt.client as mqtt

import argparse

parser = argparse.ArgumentParser()
parser.add_argument('-t', '--target', help="target mqtt host", required= "true")
args = parser.parse_args()

messurements = list()

def on_connect(client, userdata, flags, rc):
    print("Connected with result code " + str(rc))

    client.subscribe("test")

def on_message(client, userdata, msg):
    print(msg.topic + " " + str(msg.payload))
    messurements.append(msg.payload)

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

client.connect(args.target, 1883, 60)

client.loop_forever()