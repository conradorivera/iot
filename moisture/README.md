# Moisture Sensor
This section shows how to connect a moisture sensor with SP8266 and how can be connected also with a Relay and Water Pump.

https://www.youtube.com/watch?v=FJ3FiRyYq1M.


## Connect the Moisture Sensor
![Moisture Connection](https://github.com/conradorivera/iot/blob/main/docs/connections/moisture_connection.png)

The Moisture sensor is connected to the soil probe with 2 wires. Then the A0 is connected with SP8266 A0, 
the GND and VCC as well with any GND and 3V in the SP8266.

## Connect the Relay + Water Pump
![Moisture Connection](https://github.com/conradorivera/iot/blob/main/docs/connections/waterpump_connection.png)

The pump has two wires, the neutro has to be connected with the 9V neutro. And the positive with the COM (in the middle) in the Relay. The 9V positive has to be connected with the NO (the LEFT one) in the Relay. The NC in the Relay is not used.

From the other side in the Relay, the IN (the LEFT one) can be connected with D2 (then this one is the pin 4 in code) in SP8266. Finally GND and VCC can be connected with any GND and 3V in the SP8266.
https://www.youtube.com/watch?v=pFwJBRpAI8w&t=194s