'use strict'

var express = require('express');
var bodyParser = require('body-parser');

var app = express();

// paths files

// middlewares
app.use(bodyParser.urlencoded({extended:false}));
app.use(bodyParser.json());

// cors

// paths

app.get('/test',(req,res) => {
	res.status(200).send({
		message: "successful API test"
	});

});

app.get('/',(req,res) => {
	let arduinoResponse = {
		action: "close"
	}
	console.log(JSON.stringify(req.headers))
	res.status(200).send(
		arduinoResponse
	);


});


// export
module.exports = app;
