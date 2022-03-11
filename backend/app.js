' use strict'

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
	res.status(200).send(
		"<h1>successful API test</h1>"
	);

});


// export
module.exports = app;
