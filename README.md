# PEUS
Projektowanie Elektrycznych Układów Sterowania

Konfiguracja Systemu:  
```sudo apt-get update```  
```sudo apt-get upgrade```  
```sudo apt-get install qtbase5-dev libqt5webkit5-dev libqt5websockets5-dev```    

WiringPI:    
```sudo apt-get install libi2c-dev i2c-tools```    
```wget https://project-downloads.drogon.net/wiringpi-latest.deb```    
```sudo dpkg -i wiringpi-latest.deb```  
```gpio -v```  

Enable I2C in Raspberry Pi:   
```sudo raspi-config```    
Interface Options -> I2C -> Yes    
 
IDE:  
```sudo apt-get install qtcreator```  

Bibliografia:  
https://roboticsbackend.com/wiringpi-i2c-tutorial-rasperry-pi-adxl345/  
https://github.com/andreiva/raspberry-pi-bme280  
