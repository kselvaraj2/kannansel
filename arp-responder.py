from __future__ import print_function
from scapy.all import *
import time

# Your network broadcast address
broadcastNet = "192.168.100.255"

macDict = { "192.168.100.152" : "60:01:94:98:97:c6",
            "192.168.100.149" : "68:c6:3a:a7:d3:40"}

# Use MAC address of this machine as source. If not eth0, change this:
myMAC = get_if_hwaddr('Vlan500')

def handle_packet(packet):
    print("Someone is asking about " + str(packet[ARP].op))
    if packet[ARP].op == 1:
        print("Someone is asking about " + packet.pdst)
        print(packet.summary())

        print("Sending ARP response for " + packet.pdst)
        reply = ARP(op=2, hwsrc="0c:48:c6:c3:37:1e", psrc=packet.pdst, hwdst="0c:48:c6:c3:30:f8", pdst="5.5.5.6")
        go = Ether(dst="0c:48:c6:c3:30:f8", src=myMAC) / Dot1Q(vlan=500) / reply
        sendp(go,iface="PortChannel01")
    return

# Sniff for ARP packets. Run handle_packet() on each one
sniff(filter="arp",prn=handle_packet,iface='Vlan500')


#needed scapy of python 3.7
