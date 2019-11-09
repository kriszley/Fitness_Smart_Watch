var mysql = require('mysql'); //create mysql module instance
var tokenGenerator = require('token-generator')({ //create token-generator for user authentication (User ID)
      salt: 'your secret ingredient for this magic recipe',
      timestampMap: 'abcdefghij',
      });

var connection = mysql.createConnection({
  host  : 'de-rds.cmhqpqcb1nfr.us-west-2.rds.amazonaws.com',
  user  : 'group3',
  password  : 'cpengroup3',
  database : 'dewatch'
}); //create connection instance
connection.connect(function(err){
    if(err){
      console.log("Error connecting database ... @login_route");
      throw err;
    }
    console.log('Database is connected ... @login_route');
});

exports.register = function(req, res){ //Declares register function that is to be used in the server.js
  // console.log("req", req.body);
  var today = new Date();
  var token = tokenGenerator.generate();

  var users ={  //declare JSON variables to store data from request body
    "first_name":req.body.first_name, //These are comming from the Android Retrofit body format instances
    "last_name":req.body.last_name,
    "gender":req.body.gender,
    "age":req.body.age,
    "weight":req.body.weight,
    "email":req.body.email,
    "password":req.body.password,
    "created":today,
    "modified":today,
    "uid":token
  }
  connection.query('INSERT INTO users SET ?', users, function(error, results, fields){
      if(error){
        console.log("error ocurred", error);
        res.send({
            "code":400,
            "failed":"error ocurred"
        })
      }
      else{
        console.log('The solution is: ', results);
        //res.send({
        //    "code": 200,
        //    "success":"user registered successfully"
        //      });
        res.send({
            "first_name":req.body.first_name,
            "last_name":req.body.last_name,
            "email":req.body.email,
            "uid":token,
            "gender":req.body.gender,
            "age":req.body.age,
            "weight":req.body.weight,
            "code": 200
            });
      }
    });
}

exports.login = function(req, res){ //create login function to be used in server.js for client to call post function
  var email = req.body.email;
  var password = req.body.password;
  connection.query('SELECT * FROM users WHERE email = ?', [email], function(error, results, fields){ // res is in an array form i don't know why I did that I think it returned an error when not used it. But not too sure what happened.
      if(error){
        console.log("ERROR occured",error);
        res.send({
            "code":400,
            "failed":"error occured"
        })
      }
      else{
        console.log("The solution is: ", results);
        if(results.length > 0){
          if(results[0].password == password){
            res.send({
                "first_name":results[0].first_name,
                "last_name":results[0].last_name,
                "email":results[0].email,
                "uid":results[0].uid,
                "gender":results[0].gender,
                "age":results[0].age,
                "weight":results[0].weight,
                "code":200
                });
            //res.end(JSON.stringify(results));
          }
          else{
            console.log("Should be : ", results[0].password);
            console.log("Has : ", password);
            res.send({
                "code":204,
                "success": "Email and password does not match!"
              });
          }
        }
        else{
          res.send({
              "code":204,
              "success":"Email does not exits"
                });
        }
      }
      });
    }
