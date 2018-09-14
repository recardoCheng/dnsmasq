#!/bin/sh

set -x
tar -cJf ../dnsmasq-2.75.tar.xz ../dnsmasq-2.75
cp ../dnsmasq-2.75.tar.xz ../openwrt_r1s/dl/
rm -rf ~/openwrt_r1s/build_dir/target-mipsel_1004kc+dsp_uClibc-0.9.33.2/dnsmasq-nodhcpv6
