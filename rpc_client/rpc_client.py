import xmlrpc.client
import argparse


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


parser = argparse.ArgumentParser()
parser.add_argument('-c', '--car', help="car id to get data from", required=True)
parser.add_argument('-s', '--sensor', help="sensor id to get data from", required=True)
args = parser.parse_args()

proxy = xmlrpc.client.ServerProxy("http://localhost:8000")

incoming = proxy.get_data(args.car, args.sensor)


for x in range(len(incoming)):
    print(incoming[x])
