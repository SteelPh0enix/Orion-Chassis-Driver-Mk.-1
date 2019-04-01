import json
import serial


class ChassisCommunicator:
    def __init__(self, serial_port, baud_rate):
        self.busy = False
        self.power_limit = 150
        self.maximum_power_limit = 250
        self.power_step = 25

        self.arduino = serial.Serial(serial_port, baud_rate, timeout=1)

    def drive_forward(self):
        if not self.busy:
            self.busy = True
            data = json.dumps({"SPD": self.power_limit, "ROT": 0}) + '\n'
            print("Sending", data)
            self.arduino.write(data.encode())
            print(self.arduino.readline())
        return True

    def drive_backward(self):
        if not self.busy:
            self.busy = True
            data = json.dumps({"SPD": -self.power_limit, "ROT": 0}) + '\n'
            print("Sending", data)
            self.arduino.write(data.encode())
            print(self.arduino.readline())
        return True

    def rotate_left(self):
        if not self.busy:
            self.busy = True
            data = json.dumps({"SPD": 0, "ROT": -self.power_limit}) + '\n'
            print("Sending", data)
            self.arduino.write(data.encode())
            print(self.arduino.readline())
        return True

    def rotate_right(self):
        if not self.busy:
            self.busy = True
            data = json.dumps({"SPD": 0, "ROT": self.power_limit}) + '\n'
            print("Sending", data)
            self.arduino.write(data.encode())
            print(self.arduino.readline())
        return True

    def stop(self):
        data = json.dumps({"SPD": 0, "ROT": 0}) + '\n'
        self.arduino.write(data.encode())
        self.busy = False
        return True

    def increase_power_limit(self):
        if (self.power_limit + self.power_step <= self.maximum_power_limit):
            self.power_limit += self.power_step
        return True

    def decrease_power_limit(self):
        if (self.power_limit - self.power_step > 0):
            self.power_limit -= self.power_step
        return True
