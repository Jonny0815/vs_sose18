import paho.mqtt.client as mqtt
from xmlrpc.server import SimpleXMLRPCServer
import argparse


class Measurement:
    car = 000
    sensor = 000
    value = 000
    timestamp = 00.0000

    def __init__(self, car_h, sensor_h, value_h, timestamp_h):
        self.car = car_h
        self.sensor = sensor_h
        self.value = value_h
        self.timestamp = timestamp_h

    def print_me(self):
        print(self.car + self.sensor + self.value + self.timestamp)


parser = argparse.ArgumentParser()
parser.add_argument('-t', '--target', help="target mqtt host", required= "true")
args = parser.parse_args()

measurements = list()


def get_data(car, sensor):
    for x in range(len(measurements)):
        if car == measurements[x].car & sensor == measurements[x].sensor:
            return measurements[x].print_me()


def on_connect(client, userdata, flags, rc):
    print("Connected with result code " + str(rc))

    client.subscribe("test")


def on_message(client, userdata, msg):
    print(msg.topic + " " + str(msg.payload))

    data = str(msg.payload)
    data_l = list(data.split(" "))

    measurements.append(Measurement(data_l[0], data_l[1], data_l[2], data_l[3]))


client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

client.connect(args.target, 1883, 60)

server = SimpleXMLRPCServer(("localhost", 8000))
server.register_function(get_data, 'get_data')
client.loop_forever()