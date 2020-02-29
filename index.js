var mosca = require('mosca');
var mqtt = require('mqtt')

var settings = {
		port:1883
		}

var server = new mosca.Server(settings);

server.on('ready', function(){
console.log("ready");
console.log(process.env.port)
});

var client  = mqtt.connect('mqtt://192.168.43.127')
client.on('connect', function () {
    client.subscribe('/pind0')
})
client.on('message', function (topic, message) {
context = message.toString();
console.log(context)
})
