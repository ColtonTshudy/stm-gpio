import serial
import time
import inspect
from datetime import datetime
from typing import List


class NetlistCard:
    # INSTANCE VARIABLES
    serial = None  # serial instance
    _id = 255  # default to impossible id (possible ids: 0-127)
    # _io_offset = (_id * 72) # pin offset for backplane
    _active_pin = (
        0  # default to no active pin (0 = inactive, 1-72 = active on that pin)
    )
    end_flag = b"\r\n"

    # COMMANDS
    GET_ID = "-id"
    SET_PIN = "-sp"
    RESET_PINS = "-rst"
    BLINK_LED = "-blink"
    SET_LED = "-led"
    READ_PINS = "-read"
    SET_PULLDOWN = "-sp"

    def __init__(self, device_path, baudrate=115200):
        self.baudrate = baudrate
        self.serial = serial.Serial(device_path, self.baudrate, timeout=1)
        self._id = self.get_id()
        self.reset_gpio()
        self._debug(f"init complete! GPIO reset, and got ID {self._id}")
        self.blink_led()

    def __repr__(self):
        return f"NetlistCard(id='{self._id}')"

    def _send_command(self, command, argument=b""):
        if argument != b"":
            argument = b" " + argument

        command_formatted = command.encode() + argument + self.end_flag
        self._debug(f"sending command {command_formatted}...")

        self.start_time = time.time()
        self.serial.write(command_formatted)

        response = bytearray()
        response = self._get_response(100)

        # return code byte, data byte(s)
        return response[0], response[1:]

    def reset_gpio(self):
        rc = self._send_command(self.RESET_PINS)[0]
        if rc != 1:
            raise ValueError(f"Reset command responded with return code {rc}")
        self.set_led(0)
        return rc

    def set_pulldown(self, pulldown_enable):
        rc, pulldown_enable_set = self._send_command(
            self.SET_PULLDOWN, bytes([pulldown_enable])
        )
        pulldown_enable_set = int.from_bytes(
            pulldown_enable_set, byteorder="big", signed=False
        )
        if rc != 1:
            raise ValueError(f"Set pulldown command responded with return code {rc}")
        if pulldown_enable_set != pulldown_enable:
            raise ValueError(
                f"Set pulldown command state mismatch! (tried setting {pulldown_enable}, got {pulldown_enable_set})"
            )
        self.set_led(1)
        return rc

    def get_id(self):
        id = int.from_bytes(
            self._send_command(self.GET_ID)[1], byteorder="big", signed=False
        )
        return id

    def set_gpio(self, io_number):
        rc, io_set = self._send_command(self.SET_PIN, bytes([io_number]))
        io_set = int.from_bytes(io_set, byteorder="big", signed=False)
        if rc != 1:
            raise ValueError(f"Set GPIO command responded with return code {rc}")
        if io_set != io_number:
            raise ValueError(
                f"Set GPIO command io_number mismatch! (tried setting {io_number}, got {io_set})"
            )
        self.set_led(1)
        return rc

    def set_led(self, state: bool):
        rc, io_set = self._send_command(self.SET_LED, bytes([state]))
        state_set = int.from_bytes(io_set, byteorder="big", signed=False)
        if rc != 1:
            raise ValueError(f"Set LED command responded with return code {rc}")
        if state_set != state:
            raise ValueError(
                f"Set LED command state mismatch! (tried setting {state}, got {state_set})"
            )
        return rc

    def read_gpio(self):
        rc, gpio_states = self._send_command(self.READ_PINS)
        if rc != 1:
            raise ValueError(f"Read GPIO command responded with return code {rc}")
        int_gpio_array = [byte_value for byte_value in gpio_states]
        return int_gpio_array

    def blink_led(self):
        rc = self._send_command(self.BLINK_LED)[0]
        if rc != 1:
            raise ValueError(f"Blink LED command responded with return code {rc}")
        return rc

    def _get_response(self, timeout):
        """Get response with timeout in milliseconds"""
        response = bytearray()

        # self._debug(f"awaiting response with timeout {timeout}ms...")

        while 1:
            if (time.time() - self.start_time) > timeout / 1000:
                raise TimeoutError(f"Device did not respond within {timeout}ms")

            if self.serial.in_waiting:
                chunk = self.serial.read(self.serial.in_waiting)
                self._debug(f"got chunk: {chunk}")
                response.extend(chunk)

            if self.end_flag in response:
                self._debug(f"({time.time() - self.start_time} seconds round-trip)")
                break

        return response[:-2]

    def _debug(self, str):
        now = datetime.now()
        timestamp = now.strftime("%H:%M:%S.%f")
        calling_function = inspect.currentframe().f_back.f_code.co_name
        print(f"{timestamp} [DBG] - [CARD {self._id}] - [{calling_function}]: {str}")


if __name__ == "__main__":
    # TODO: Update test code to work with new pulldown enable/disable scheme
    from serial_scan import PortScan

    # port_scanner = PortScan()
    # port_scanner.scan()
    # device_path = port_scanner.get_first_device_by_pid(49239)

    # Get list of all cards with the same VID / PID
    cards: List[NetlistCard] = []

    port_scanner = PortScan()
    port_scanner.scan()
    device_paths = port_scanner.get_all_devices_by_pid(49239)

    for device_path in device_paths:
        cards.append(NetlistCard(device_path))
    time.sleep(0.5)  # wait for cards to boot up

    cards = sorted(cards, key=lambda card: card._id)  # put the cards in order

    # identify all cards
    for card in cards:
        print(card._id)  # print id of all cards
        card.reset_gpio()  # reset all cards
    time.sleep(0.5)  # let gpio resets settle

    # Select a specific card to test
    card1 = cards[0]
    print(f"id: {card1._id}")
    time.sleep(1)  # Let the LED finish blinking (aesthetics only)
    card1.set_gpio(1)
    time.sleep(1)
    print(card1.read_gpio())

    card1.reset_gpio()
    # for i in range(1, 73):
    #     card1.set_gpio(i)
    #     print(f"set GPIO {i}")
    #     time.sleep(0.01)
    #     print(card1.read_gpio())
    #     if card1.read_gpio()[i - 1] != 1:
    #         print("Fail! ==========================")
    #         time.sleep(1000)
    #     else:
    #         print("Pass")
    #     card1.reset_gpio()
    #     input()

    row = []
    ez_view = []
    for pin in range(1, 73):
        card1.reset_gpio()
        time.sleep(0.1)
        card1.set_gpio(pin)
        print(f"Setting pin {pin} on card {card1._id}")
        input()

        # card1.set_led(1)
        # time.sleep(0.005)

        gpio_read_list = card1.read_gpio()  # read sub card's GPIO

        row.extend(gpio_read_list)
        gpio_read_list.insert(0, card1._id)
        ez_view.append(gpio_read_list)
        # sub_card.blink_led()
        # card1.set_led(0)

        print(f"Card {ez_view[0][0]}: {ez_view[0][1:]}")
        input()
        # time.sleep(1000)
