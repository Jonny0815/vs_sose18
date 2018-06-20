from typing import List, Any

import paho.mqtt.client as mqtt
from xmlrpc.server import SimpleXMLRPCServer
import argparse
import threading


class Measurement:
    car = int()
    sensor = int()
    value = int()
    timestamp = str()

    def __init__(self, car_h, sensor_h, value_h, timestamp_h):
        self.car = car_h
        self.sensor = sensor_h
        self.value = value_h
        self.timestamp = timestamp_h

    def print_me(self):
        print(self.car + self.sensor + self.value + self.timestamp)

    def to_string(self):
        return str("Card-ID: " + self.car + " Sensor-ID: " + self.sensor + " Value: " + self.value + " Timestamp: " + self.timestamp)

    def to_dict(self):
        return dict(car=self.car, sensor=self.sensor,value = self.value, timestamp=self.timestamp)


parser = argparse.ArgumentParser()
parser.add_argument('-t', '--target', help="target mqtt host", required=True)
args = parser.parse_args()

measurements: List[Measurement] = list()


def get_data(car, sensor):
    to_return = list()
    for x in range(len(measurements)):
        if car == measurements[x].car and sensor == measurements[x].sensor:
            to_return.append(measurements[x].to_string())
    return to_return


def on_connect(client, userdata, flags, rc):
    print("Connected with result code " + str(rc))

    client.subscribe("test")


def on_message(client, userdata, msg):
    print(msg.topic + " " + str(msg.payload))

    data = str(msg.payload)
    data_l = list(data.split(" "))

    data_l[0] = data_l[0][-3:]
    data_l[3] = data_l[3][:-2]

    measurements.append(Measurement(data_l[0], data_l[1], data_l[2], data_l[3]))


client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

client.connect(args.target, 1883, 60)

server = SimpleXMLRPCServer(("localhost", 8000))
server.register_function(get_data, 'get_data')

threads = []
t1 = threading.Thread(target=client.loop_forever)
threads.append(t1)
t2 = threading.Thread(target=server.serve_forever)
threads.append(t2)

for y in range(len(threads)):
    threads[y].start()


