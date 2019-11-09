var mysql = require('mysql'); //create mysql dependency module instance

var connection = mysql.createConnection({ //create connection instance
  host  : 'de-rds.cmhqpqcb1nfr.us-west-2.rds.amazonaws.com',
  user  : 'group3',
  password  : 'cpengroup3',
  database  : 'dewatch'
});
connection.connect(function(err){
    if(err){
      console.log("Error connecting database ... @profile_route");
      throw err;
    }
    console.log("Database is connected ... @profile_route");
});

exports.edit_age = function(req, res){
  var uid = req.body.uid;
  var age = req.body.age;

  connection.query('UPDATE users SET age = ? WHERE uid = ?', [age, uid],
      function(error, results, fields){
        if(error){
          console.log("ERROR OCCURED AGE", error);
          res.send({
              "code":400,
              "failed":"error occured"
          })
        }
        else{
          console.log('The solution is: ', results);
          res.send({
              "code":200,
              "success":"successful!"
          });
        }
      });
}

exports.edit_email = function(req, res){
  var uid = req.body.uid;
  var email = req.body.email;

  connection.query('UPDATE users SET email = ? WHERE uid = ?', [email, uid],
      function(error, results, fields){
        if(error){
          console.log("ERROR OCCURED EMAIL", error);
          res.send({
              "code":400,
              "failed":"error occured"
          })
        }
        else{
          console.log('The solution is: ', results);
          res.send({
              "code":200,
              "success":"successful!"
          });
        }
      });
}
exports.edit_first_name = function(req, res){
  var uid = req.body.uid;
  var first_name = req.body.first_name;

  connection.query('UPDATE users SET first_name = ? WHERE uid = ?', [first_name, uid],
      function(error, results, fields){
        if(error){
          console.log("ERROR OCCURED FIRST NAME", error);
          res.send({
              "code":400,
              "failed":"error occured"
          })
        }
        else{
          console.log('The solution is: ', results);
          res.send({
              "code":200,
              "success":"successful!"
          });
        }
      });

}
exports.edit_last_name = function(req, res){
  var uid = req.body.uid;
  var last_name = req.body.last_name;

  connection.query('UPDATE users SET last_name = ? WHERE uid = ?', [last_name, uid],
      function(error, results, fields){
        if(error){
          console.log("ERROR OCCURED LAST NAME", error);
          res.send({
              "code":400,
              "failed":"error occured"
          })
        }
        else{
          console.log('The solution is: ', results);
          res.send({
              "code":200,
              "success":"successful!"
          });
        }
      });
}
exports.edit_password = function(req, res){
  var uid = req.body.uid;
  var password = req.body.password;

  connection.query('UPDATE users SET password = ? WHERE uid = ?', [password, uid],
      function(error, results, fields){
        if(error){
          console.log("ERROR OCCURED PASSWORD", error);
          res.send({
              "code":400,
              "failed":"error occured"
          })
        }
        else{
          console.log('The solution is: ', results);
          res.send({
              "code":200,
              "success":"successful!"
          });
        }
      });
}
exports.edit_weight = function(req, res){
  var uid = req.body.uid;
  var weight = req.body.weight;

  connection.query('UPDATE users SET weight = ? WHERE uid = ?', [weight, uid],
      function(error, results, fields){
        if(error){
          console.log("ERROR OCCURED WEIGHT", error);
          res.send({
              "code":400,
              "failed":"error occured"
          })
        }
        else{
          console.log('The solution is: ', results);
          res.send({
              "code":200,
              "success":"successful!"
          }); 
        }
      });
}
