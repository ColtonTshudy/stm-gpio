import serial.tools.list_ports

# from logger_custom import CustomFormatter
import logging


class PortScan:

    def __init__(self, log_level=logging.INFO):
        ports = None

        # Set up logging
        self.logger = logging.getLogger(self.__class__.__name__)
        self.logger.setLevel(log_level)

        if not self.logger.handlers:
            handler = logging.StreamHandler()
            formatter = logging.Formatter("%(levelname)s: %(message)s")
            # handler.setFormatter(CustomFormatter())
            self.logger.addHandler(handler)

    def scan(self):
        # Get a list of all available serial ports
        self.ports = serial.tools.list_ports.comports()

    def print_ports(self):
        # Print details of each port
        if self.ports:
            print("Available serial ports:")
            print("-" * 40)
            for port in self.ports:
                print(f"Port: {port.device}")
                print(f"Description: {port.description}")
                print(f"Hardware ID: {port.hwid}")
                print(f"Product: {port.product}")
                print(f"Manufacturer: {port.manufacturer}")
                print(f"PID: {port.pid}")
                print("-" * 40)
        else:
            print("No serial ports detected.")

    def get_device_by_description(self, description):
        if self.ports:
            print("Available serial ports:")
            print("-" * 40)
            for port in self.ports:
                if port.description == description:
                    print(f"Device {description} found on device {port.device}")
                    return port.device
        else:
            print(f"Device {description} not found.")
        return None

    def get_first_device_by_pid(self, pid):
        if self.ports:
            print("Available serial ports:")
            print("-" * 40)
            for port in self.ports:
                if port.pid == pid:
                    print(f"USB with PID {pid} found on device {port.device}")
                    return port.device
        else:
            print(f"Device with PID: {pid} not found.")
        return None

    def get_all_devices_by_pid(self, pid):
        list_of_devices = []
        if self.ports:
            print("Available serial ports:")
            print("-" * 40)
            for port in self.ports:
                if port.pid == pid:
                    print(f"USB with PID {pid} found on device {port.device}")
                    list_of_devices.append(port.device)
        else:
            print(f"Device with PID: {pid} not found.")
            return None

        return list_of_devices


if __name__ == "__main__":
    port_scanner = PortScan(logging.DEBUG)
    port_scanner.scan()
    port_scanner.print_ports()
