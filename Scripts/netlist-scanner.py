from device import NetlistCard
from serial_scan import PortScan

cards = []

port_scanner = PortScan()
port_scanner.scan()
device_paths = port_scanner.get_all_devices_by_pid(49239)

for device_path in device_paths:
    cards.append(NetlistCard(device_path))

for card in cards:
    print(card._id)

cards = sorted(cards, key=lambda card: card._id)

print(f"Found {len(cards)} cards:")
print(cards)

cards[0].set_gpio(1)
print(cards[0].read_gpio())
print(cards[1].read_gpio())
