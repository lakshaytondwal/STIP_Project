# Network Spoofer

This project contains a Bash script and a C program for network-related tasks, including hostname and MAC address spoofing.

## Contents

- **`macch`**: A Bash script to spoof hostname and MAC addresses on a Linux system by acting as an interface.
- **`list`**: A JSON file containing list of hostname and MAC addresses.
- **`mac.c`**: A code which changes the MAC address written in C.
- **`macc`**: Compiled output of mac.c code.

---

## Setup

### Prerequisites

Ensure the following dependencies are installed:
- **jq**: A lightweight and flexible command-line JSON processor.
- **gcc**: For compiling the C program if required.

### Requirements

- A Linux distribution.
- Sufficient privileges to change MAC addresses (root or sudo).
- Network connectivity for testing port scanning.

## Usage

### Running the Bash Script

To spoof the hostname and MAC address, execute the following command:

```bash
chmod +x macch macc
./macch

