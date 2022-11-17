const socket = new WebSocket('ws://localhost:43434');

//konstruktor 
var smartHome = new SmartHome({});

// inicjalizacja
smartHome.init(); 

socket.onopen = function(evt) {
    //alert('Connected.');
    $('#status').css('background', 'green');
    send();
};
  
socket.onclose = function(evt) {
    //alert('Disconnected.');
    $('#status').css('background', 'red');
};
  
socket.onmessage = function(evt) {
    console.log(evt.data);
    obj = JSON.parse(evt.data);

    var temp_output = (Math.round(obj.act_temp * 10))/10;
    var humi_output = (Math.round(obj.act_humi * 10))/10;
    var temp_cv = (Math.round(obj.ster_temp * 10))/10;
    var humi_cv = (Math.round(obj.ster_humi * 10))/10;
    var temp_uchyb = (Math.round(obj.uchyb_temp * 10))/10;
    var humi_uchyb = (Math.round(obj.uchyb_humi * 10))/10;
    var temp_zakl = (Math.round(obj.zakl_temp * 10))/10;
    var humi_zakl = (Math.round(obj.zakl_humi * 10))/10;
    send();
    smartHome.update(temp_output, humi_output, temp_cv, humi_cv, temp_uchyb, humi_uchyb, temp_zakl, humi_zakl);

};
  
socket.onerror = function(evt) {
    alert('Error.');
    console.log(evt.data);
};

var temp_slider = document.getElementById("sliderTemp");
var temp_output = document.getElementById("current-temp");
temp_output.innerHTML = temp_slider.value;

var humi_slider = document.getElementById("sliderHumidity");
var humi_output = document.getElementById("current-humidity");
humi_output.innerHTML = humi_slider.value;

var wind_checkBox = document.getElementById("toggle");
var set_wind = false;

function send() {
	if (wind_checkBox.checked == true) {
		set_wind = true;
		
	} else {
		set_wind = false;
	}

	var message = {"set_temp": temp_slider.value, "set_humi": humi_slider.value, "set_wind": set_wind};

	console.log(message);
	console.log(JSON.stringify(message));
	socket.send(JSON.stringify(message));
};
