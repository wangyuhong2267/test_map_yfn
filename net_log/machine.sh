#!/bin/bash
tcpdump tcp port 7891 -w `date "+%Y-%m-%d-%H-%M-%S.machine.cap"`

