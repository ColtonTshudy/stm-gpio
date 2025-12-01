from device import NetlistCard
from serial_scan import PortScan
import csv
import time
from typing import List
from pprint import pprint

cards: List[NetlistCard] = []

port_scanner = PortScan()
port_scanner.scan()
device_paths = port_scanner.get_all_devices_by_pid(49239)

for device_path in device_paths:
    cards.append(NetlistCard(device_path))
time.sleep(0.5)  # wait for cards to boot up

cards = sorted(cards, key=lambda card: card._id)  # put the cards in order

# identify all cards (bringup tool)
for card in cards:
    print(card._id)  # print id of all cards
    card.reset_gpio()  # reset all cards
time.sleep(0.5)  # let gpio resets settle
# for card in cards:
#     card.set_led(1)
#     time.sleep(0.04)
#     card.set_led(0)

print(f"Found {len(cards)} cards:")
print(cards)

# Start up test: make sure all GPIO read 0
ez_view = []
print("Startup test: checking all GPIO read as OFF")
i = 0
for card in cards:
    gpio_read_list = card.read_gpio()
    ez_view.append(gpio_read_list)
    for gpio_state in gpio_read_list:
        if gpio_state == 1:
            raise ValueError(f"Found wrongly asserted GPIO! on card {card._id}")
for i in range(0, 27):
    print(f"card {i}: {ez_view[i]}")
print("PASS! No GPIOs asserted after reset.")
input()

# cards[0].set_gpio(1)
# print(cards[0].read_gpio())
# print(cards[1].read_gpio())

filename = "netlist_matrix.csv"
header = [str(i) for i in range(1, 1945)]
header.insert(0, " ")  # add empty space to top left corner of CSV for alignment

# time.sleep(1000)

# Columns (headed by col A): the (sole) pin that was intentionally excited
# Rows (headed by row 1): passive pins that were excited when the pin indicated in column A was excited
with open(filename, "w", newline="") as csvfile:
    writer = csv.writer(csvfile)
    writer.writerow(header)

    for card in cards:
        for pin in range(1, 73):
            # reset results holding lists
            row = []
            ez_view = []
            # get pin offset of the excited pin
            pin_offset = card._id * 72
            card.reset_gpio()
            time.sleep(0.01)
            card.set_gpio(pin)
            print(f"Setting pin {pin} on card {card._id}")
            input()
            for sub_card in cards:
                sub_card.set_led(1)
                # time.sleep(0.005)

                gpio_read_list = sub_card.read_gpio()  # read sub card's GPIO

                row.extend(gpio_read_list)
                ez_view.append(gpio_read_list)
                # sub_card.blink_led()
                sub_card.set_led(0)

                if card == sub_card:
                    # make sure we don't accidentally turn off the main card's LED
                    sub_card.set_led(1)

            # Print to console the results of this scan
            for i in range(0, 27):
                print(f"Card {i}: {ez_view[i]}")

            # Write row to array
            row.insert(0, i + pin_offset)  # column A: the excited pin
            writer.writerow(row)
            input()
            # time.sleep(1000)
