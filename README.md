## Projektowanie Elektrycznych Układów Sterowania (PEUS)

### Description
This is home assitant designed to be used with Raspberry Pi.
The assistant will require sensor of humidity, temeprature, pressure and switch On-Off. 
In our project we used:  
-Raspberry Pi 4  
-Sensor BME280  
-Switch  

### System configuration:  
To use above program we need to install/update required libraries for the project by doing the steps below.

#### Libraries to instal
#### Qt5 :
```sudo apt-get update```  
```sudo apt-get upgrade```  
```sudo apt-get install qtbase5-dev libqt5webkit5-dev libqt5websockets5-dev libqt5sql5-mysql```

#### WiringPI:    
```sudo apt-get install libi2c-dev i2c-tools```    
```wget https://project-downloads.drogon.net/wiringpi-latest.deb```    
```sudo dpkg -i wiringpi-latest.deb```  
```gpio -v```  

#### IDE:  
```sudo apt-get install qtcreator```  

In our project we used twp-way bus I2C which we need to enable
#### Enable I2C in Raspberry Pi:   
```sudo raspi-config```    
Interface Options -> I2C -> Yes    

### Hardware:
Check the values of ports in linux to know what to input in program
```gpio readall```

Picture of Raspberry Pi 4
![Alt data](./Images/Zdjecie_portow_raspberry_PI_4.png)  

#### Connection of the sensors

Picture of connected sensor BME 280 to Raspberry Pi 4

Picture of connected limit switch

### Bibliography:
https://roboticsbackend.com/wiringpi-i2c-tutorial-rasperry-pi-adxl345/  
https://github.com/andreiva/raspberry-pi-bme280  
