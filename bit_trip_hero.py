import os

from argparse import ArgumentParser
from serial import Serial

if os.name == 'nt':
    import win32api, win32con as e
    def keystroke(key):
        k = None
        if (key == "KEY_SLIDE"):
            k = 0x53
        elif (key == "KEY_JUMP"):
            k = 0x4A
        elif (key == "KEY_KICK"):
            k = 0x4B
        elif (key == "KEY_DANCE"):
            k = 0x41
        elif (key == "KEY_SPRING"):
            k = 0x57
        elif (key == "KEY_BLOCK"):
            k = 0x44
        elif (key == "KEY_ENTER"):
            k = e.VK_RETURN
        elif (key == "KEY_ESCAPE"):
            k = e.VK_ESCAPE
        else:
            raise("KEY ERROR")
        win32api.keybd_event(k, 0x25, e.KEYEVENTF_EXTENDEDKEY | 0, 0)
        win32api.keybd_event(k, 0x25, e.KEYEVENTF_EXTENDEDKEY | e.KEYEVENTF_KEYUP, 0)
elif os.name == 'posix':
    from evdev import uinput, ecodes as e

    def keystroke(key):
        k = None
        if (key == "KEY_DOWN"):
            k = e.KEY_DOWN
        elif (key == "KEY_UP"):
            k = e.KEY_UP
        elif (key == "KEY_F5"):
            k = e.KEY_F5
        elif (key == "KEY_ESC"):
            k = e.KEY_ESC
        elif (key == "KEY_B"):
            k = e.KEY_B
        else:
            raise("KEY ERROR")
        with uinput.UInput() as ui:
            ui.write(e.EV_KEY, k, 1)
            ui.syn()
            ui.write(e.EV_KEY, k, 0)
            ui.syn()

SELECT = 0b1;
START  = 0b10;
ORANGE = 0b100;
BLUE   = 0b1000;
YELLOW = 0b10000;
RED    = 0b100000;
GREEN  = 0b1000000;
UP     = 0b10000000;
DOWN   = 0b100000000;


def main():
    parser = ArgumentParser(description='Present Hero CLI')
    parser.add_argument("serial", metavar="SERIAL", type=str,
                        help='''Specify the serial to listen''')
    parser.add_argument("-d", "--debug", dest="debug", default=False, action="store_true")
    args = parser.parse_args()
    arduino_nano = Serial(args.serial)
    while arduino_nano.is_open:
        inputs = []
        line = arduino_nano.readline()[0:-1]
        try:
            input = int(line, base=2)
        except:
            input = 0
        if input & SELECT:
            inputs.append("Select")
            keystroke("KEY_ESCAPE")
        if input & START:
            inputs.append("Start")
            keystroke("KEY_ENTER")
        if input & ORANGE:
            inputs.append("Orange")
        if input & BLUE:
            inputs.append("Blue")
            keystroke("KEY_DANCE")
        if input & YELLOW:
            inputs.append("Yellow")
            keystroke("KEY_SPRING")
        if input & RED:
            inputs.append("Red")
            keystroke("KEY_BLOCK")
        if input & GREEN:
            inputs.append("Green")
            keystroke("KEY_KICK")
        if input & UP:
            inputs.append("Up")
            keystroke("KEY_JUMP")
        if input & DOWN:
            inputs.append("Down")
            keystroke("KEY_SLIDE")
        if args.debug : print (", ".join(inputs))

if __name__ == "__main__":
    main()
