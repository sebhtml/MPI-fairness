#!/bin/bash

mpicxx App.cpp -o App

mpiexec -n 30 ./App
