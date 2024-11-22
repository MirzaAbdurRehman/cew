#!/bin/bash
export PATH=$PATH:/usr/bin:/usr/local/bin

echo "______Starting weather script_______"

# Navigate to the directory containing the script and code
cd /home/shafia-arif/CEW_cep || exit 1

# Compile the C program
/usr/bin/gcc -o weather_app main.c weather_alert_generator.c alert_notifier.c -lcurl

# Check if compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation successful, running weather_app"
    ./weather_app
else
    echo "Compilation failed"
fi

