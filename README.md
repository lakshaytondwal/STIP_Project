# Network Spoofing and Port Scanning Utility

This project contains a Bash script and a C program for network-related tasks, including hostname and MAC address spoofing and TCP port scanning.

## Contents

- **`macch`**: A Bash script to spoof hostname and MAC addresses on a Linux system.
- **`list`**: A JSON file containing list of hostname and MAC addresses.
- **`port_scanner.c`**: A simple TCP port scanner written in C.

---

## Setup

### Prerequisites

Ensure the following dependencies are installed:
- **jq**: A lightweight and flexible command-line JSON processor.
- **macchanger**: A utility for manipulating MAC addresses.
- **gcc**: For compiling the C program.

### Requirements

- A Linux distribution.
- Sufficient privileges to change MAC addresses (root or sudo).
- Network connectivity for testing port scanning.

## Usage

### Running the Bash Script

To spoof the hostname and MAC address, execute the following command:

```bash
chmod +x macch
./macch

