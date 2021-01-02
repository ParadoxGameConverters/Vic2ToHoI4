#!/bin/bash

# **Create blankMod**
rm -r "Release-Linux/Vic2ToHoI4/blankMod"
cp -r "Vic2ToHoI4/Data_Files/blankMod" "Release-Linux/Vic2ToHoI4/blankMod"


# **Copy flags**
rm -r "Release-Linux/Vic2ToHoI4/flags"
cp -r "Vic2ToHoI4/Data_Files/flags" "Release-Linux/Vic2ToHoI4/flags"
