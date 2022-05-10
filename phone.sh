#!/bin/bash
tcpdump tcp port 7890 -i lo  -w `date "+%Y-%m-%d-%H-%M-%S.phone.cap"`
