' use strict'

var mongoose = require('mongoose');
var app = require('./app.js');
var portServerExpress = 3700;

mongoose.Promise = global.Promise;
mongoose.connect('mongodb://localhost:27017/crmmio')
	.then(() => {
		console.log("crmmio database connection successfully established ... ")

		// create express server
		app.listen(portServerExpress, () => {
			console.log("Server Express running on url: localhost:3700")
		});

	})
	.catch(err => console.log(err));



