from typing import List, Any, Set
from time import sleep
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


parser = argparse.ArgumentParser()
parser.add_argument('-t', '--target', help="target mqtt host", required=True)
args = parser.parse_args()

measurements = set()
my_request = False


def send_updates(car, sensor):
    sensor = sensor[:-1]
    for each in measurements:
        print("car: " + car + " each.car: " + each.car + " sensor: " + sensor + " each.sensor " + each.sensor)
        if car == each.car and sensor == each.sensor:
            print("pub update")
            pub.publish("update", each.car + " " + each.sensor + " " + each.value + " " + each.timestamp)


def get_data(car, sensor):

    global my_request
    my_request = True
    print("about to pub.single")

    pub.publish("update", "GET " + str(car) + " " + str(sensor))

    sleep(2)

    to_return = list()
    for each in measurements:
        if car == each.car and sensor == each.sensor:
            to_return.append(each.to_string())
    my_request = False
    return to_return


def on_connect(client, userdata, flags, rc):
    print("Connected with result code " + str(rc))

    client.subscribe("test")
    client.subscribe("update")


def on_message(client, userdata, msg):
    print(msg.topic + " " + str(msg.payload))

    global my_request

    data = str(msg.payload)
    data_l = list(data.split(" "))

    data_l[0] = data_l[0][-3:]

    if msg.topic == "update":
        if data_l[0] == "GET":
            if my_request is False:
                print("about so send updates")
                send_updates(data_l[1], data_l[2])
        else:
            data_l[3] = data_l[3][:-2]
            measurements.add(Measurement(data_l[0], data_l[1], data_l[2], data_l[3]))

    if msg.topic == "test":
        data_l[3] = data_l[3][:-2]
        measurements.add(Measurement(data_l[0], data_l[1], data_l[2], data_l[3]))


pub = mqtt.Client()
client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

pub.connect(args.target, 1883, 60)
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


