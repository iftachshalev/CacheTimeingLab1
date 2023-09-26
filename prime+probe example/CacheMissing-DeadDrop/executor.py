import os


core_number = 4
receiver_path = "/path/to/receiver"
sender_path = "/path/to/sender"

os.system(f"gnome-terminal -- bash -c 'taskset -c {core_number} {receiver_path}; read -p \"Press Enter to close...\"'")
os.system(f"gnome-terminal -- bash -c 'taskset -c {core_number} {sender_path}; read -p \"Press Enter to close...\"'")
