#!/bin/bash
conan install . -if build/ -s build_type=Debug -s arch=x86_64 --build=missing