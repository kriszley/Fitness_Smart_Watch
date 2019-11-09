var express = require('express');
var login = require('./routes/loginroutes');
var records = require('./routes/recordsroutes');
var profile = require('./routes/profileroutes');
var bodyParser = require('body-parser');

var app = express();
app.use(bodyParser.urlencoded({ extended: true }));
app.use(bodyParser.json());

app.use(function(req, res, next) {
    res.header("Access-Control-Allow-Origin", "*");
    res.header("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
    next();
});
var auth_router = express.Router();
var records_router = express.Router();
var profile_router = express.Router();

// test route
auth_router.get('/', function(req, res){
    res.json({ message: 'welcome to our upload module apis' });
});

records_router.get('/', function(req, res){
    res.json({ message: 'welcome to our exercise records apis' });
});

profile_router.get('/', function(req, res){
    res.json({ message: 'welcome to our profile apis' });
});

//route to handle user registration
auth_router.post('/register', login.register);
auth_router.post('/login', login.login);

records_router.post('/read', records.read);
records_router.post('/write', records.write);

profile_router.post('/edit_age', profile.edit_age);
profile_router.post('/edit_email', profile.edit_email);
profile_router.post('/edit_first_name', profile.edit_first_name);
profile_router.post('/edit_last_name', profile.edit_last_name);
profile_router.post('/edit_password', profile.edit_password);
profile_router.post('/edit_weight', profile.edit_weight);

app.use('/auth', auth_router);
app.use('/records', records_router);
app.use('/profile', profile_router);

app.listen(3000);

  
