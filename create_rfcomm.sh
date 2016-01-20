#!/usr/bin/env bash

mac_addr="98:D3:34:90:4F:6B"

echo "rfcomm0 {"                                >> /etc/bluetooth/rfcomm.conf
echo "    bind no;"                             >> /etc/bluetooth/rfcomm.conf
echo "    device $mac_addr;"                    >> /etc/bluetooth/rfcomm.conf
echo "    channel 1;"                           >> /etc/bluetooth/rfcomm.conf
echo '    comment "present_hero bluetooth";'    >> /etc/bluetooth/rfcomm.conf
echo "}"                                        >> /etc/bluetooth/rfcomm.conf

rfcomm bind rfcomm0 $mac_addr

