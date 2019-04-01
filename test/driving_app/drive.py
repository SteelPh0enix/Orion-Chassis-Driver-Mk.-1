from keyboard_controller import KeyboardController
from communicator import ChassisCommunicator
import sys


def main():
    if (len(sys.argv) < 2):
        print("Usage: drive.py (port) (baud rate)")
        exit(1)
    
    port = sys.argv[1]
    baud = int(sys.argv[2])

    print("Connecting to {0} @ {1}bps".format(port, baud))
    try:
        communicator = ChassisCommunicator(port, baud)
    except:
        print("Could not connect!")
        exit(2)

    controller = KeyboardController(communicator)
    controller.start()


if __name__ == '__main__':
    main()
