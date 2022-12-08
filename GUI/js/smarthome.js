(function() {

    var myChart1;
    var myChart2;

    this.SmartHome = function() {

        this.temp_output = document.getElementById("current-temp");
        this.humi_output = document.getElementById("current-humidity");
        this.wind_checkBox = document.getElementById("toggle");

        var defaults = {
            currentTemp: 20,
            currentHumidity: 50,
	    setWindow: 0,
            dataTemp: [],
            dataHumidity: [],
            tempControlValue: [],
            humiControlValue: [],
            tempUchyb: [],
	    humiUchyb: [],
	    tempZakl: [],
	    humiZakl: [],
            isConnected: false
        }

        if (arguments[0] && typeof arguments[0] === "object") {
            this.options = extendDefaults(defaults, arguments[0]);
        }

    }

    function extendDefaults(source, properties) {
        var property;
        for (property in properties) {
        if (properties.hasOwnProperty(property)) {
            source[property] = properties[property];
        }
        }
        return source;
    }

    SmartHome.prototype.init = function() {
        this.createCharts();
    }

    SmartHome.prototype.update = function( newTemp, newHum, newWind, newTempCV, newHumiCV, newTempUchyb, newHumiUchyb, newTempZakl, newHumiZakl ) {
        if( this.options.dataTemp.length == 10 ) {
            this.options.dataTemp.shift();
        }
        if( this.options.dataHumidity.length == 10 ) {
            this.options.dataHumidity.shift();
        }
	if( this.options.tempControlValue.length == 10 ) {
            this.options.tempControlValue.shift();
        }
	if( this.options.humiControlValue.length == 10 ) {
            this.options.humiControlValue.shift();
        }
	if( this.options.tempUchyb.length == 10 ) {
            this.options.tempUchyb.shift();
        }
	if( this.options.humiUchyb.length == 10 ) {
            this.options.humiUchyb.shift();
        }
	if( this.options.tempZakl.length == 10 ) {
            this.options.tempZakl.shift();
        }
	if( this.options.humiZakl.length == 10 ) {
            this.options.humiZakl.shift();
        }
        this.options.dataTemp.push(newTemp);
        this.options.dataHumidity.push(newHum);
        this.options.tempControlValue.push(newTempCV);
        this.options.humiControlValue.push(newHumiCV);
        this.options.tempUchyb.push(newTempUchyb);
        this.options.humiUchyb.push(newHumiUchyb);
	this.options.tempZakl.push(newTempZakl);
	this.options.humiZakl.push(newHumiZakl);

	this.options.setWindow = newWind;
        
        myChart1.update();
        myChart2.update();

        this.temp_output.innerHTML = newTemp;
        this.humi_output.innerHTML = newHum;

        this.checkStatus();

        this.updateTime();

        console.log(this.options);
    }

    SmartHome.prototype.checkStatus = function() {
        var isOpenWindow = false;
        var isFireplace = false;
        var isHumidifier = false;
        if( parseInt($('#current-temp').text() ) < $("#sliderTemp")[0].value ) {
            $('#temp-icon').css('opacity', 1);
            isFireplace = true;
        } else {
            $('#temp-icon').css('opacity', 0.2);
            isFireplace = false;
        }
        if( parseInt($('#current-humidity').text() ) < $("#sliderHumidity")[0].value ) {
            $('#humidity-icon').css('opacity', 1);
            isHumidifier = true;
        } else {
            $('#humidity-icon').css('opacity', 0.2);
            isHumidifier = false;
        }
        if (this.options.setWindow) {
            isOpenWindow = true
        } else {
            isOpenWindow = false
        }

        var filename = '';
        if( isOpenWindow ) {
            filename += 'W';
        } else {
            filename += 'Wn';
        }
        if( isFireplace ) {
            filename += 'F';
        } else {
            filename += 'Fn';
        }
        if( isHumidifier ) {
            filename += 'H';
        } else {
            filename += 'Hn';
        }

        $('#image').attr('src', 'images/'+filename+'.png');

    }

    SmartHome.prototype.createCharts = function() {
        const labels1 = [
            '1',
            '2',
            '3',
            '4',
            '5',
            '6',
            '7',
            '8',
            '9',
            '10'
        ];
        const data1 = {
            labels: labels1,
            datasets: [{
                label: 'Temperatura',
                borderColor: 'rgb(255, 99, 132)',
                fill: false,
                data: this.options.dataTemp,
		order: 1,
		tension: 0,
	    }, {
		label: 'Sygnal Sterujacy',
                borderColor: 'rgb(255, 165, 0)',
                fill: false,
	        data: this.options.tempControlValue,
		order: 2,
		tension: 0,
	    }, {
		label: 'Uchyb',
                borderColor: 'rgb(112, 79, 112)',
                fill: false,
                data: this.options.tempUchyb,
		order: 3,
		tension: 0,
	    }, {
		label: 'Zaklocenie',
                borderColor: 'rgb(112, 255, 112)',
                fill: false,
                data: this.options.tempZakl,
		order: 4,
		tension: 0,
            }]
        };
        const config1 = {
        type: 'line',
        data: data1,
        options: {
            scales: {
                yAxes: [{
                    ticks: {
                        beginAtZero: true,
                        min: 0,
                        stepValue: 1,
                        max: 30,
			callback: function(value, index, values) {
						return value + '℃';
			}
                    },
                    gridLines: {
                    },
                }],
                xAxes: [{
                    ticks: {
                        display: false
                    },
                    gridLines: {
                        drawBorder: false,
                        display: false,
                    },
                }]
            },
            legend: {
                display: true
            },
	    interaction: {
		intersect: false
	    },
            tooltips: {
                enabled: false,
                callbacks: {
                    label: function(tooltipItem) {
                        return tooltipItem.yLabel;
                    }
                }
            },
        }
        };

        myChart1 = new Chart(
            document.getElementById('chart1'),
            config1
        );

        const labels2 = [
        '1',
        '2',
        '3',
        '4',
        '5',
        '6',
        '7',
        '8',
        '9',
        '10'
        ];
        const data2 = {
            labels: labels2,
            datasets: [{
                label: 'Wilgotnosc',
                borderColor: 'rgb(2, 132, 199)',
                fill: false,
                data: this.options.dataHumidity,
		tension: 0,
            }, {
		label: 'Sygnal Sterujacy',
                borderColor: 'rgb(255, 165, 0)',
                fill: false,
	        data: this.options.humiControlValue,
		order: 2,
		tension: 0,
	    }, {
		label: 'Uchyb',
                borderColor: 'rgb(112, 79, 112)',
                fill: false,
                data: this.options.humiUchyb,
		order: 3,
		tension: 0,
	    }, {
		label: 'Zaklocenie',
                borderColor: 'rgb(112, 255, 112)',
                fill: false,
                data: this.options.humiZakl,
		order: 4,
		tension: 0,
            }]
        };
        const config2 = {
        type: 'line',
        data: data2,
        options: {
            scales: {
                yAxes: [{
                    ticks: {
                        beginAtZero: true,
                        min: 0,
                        stepValue: 1,
                        max: 100,
			callback: function(value, index, values) {
				return value + '%';
			}
                    },
                    gridLines: {
                    },
                }],
                xAxes: [{
                    ticks: {
                        display: false
                    },
                    gridLines: {
                        drawBorder: false,
                        display: false,
                    },
                }]
            },
            legend: {
                display: true
            },
	    interaction: {
		intersect: false
	    },
            tooltips: {
                enabled: false,
                callbacks: {
                    label: function(tooltipItem) {
                        return tooltipItem.yLabel;
                    }
                }
            }
        }
        };

        myChart2 = new Chart(
            document.getElementById('chart2'),
            config2
        );
    }

    SmartHome.prototype.updateTime = function() {
        var today = new Date();
        var date = today.getDate()+'.'+(today.getMonth()+1)+'.'+today.getFullYear();
	var minutes = today.getMinutes();
	if (minutes <= 9)
		minutes = '0' + minutes;

        var time = today.getHours() + ":" + minutes;
    
        $('#current-time').html( date + ' - ' + time);
    }

}());
