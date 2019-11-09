var mysql = require('mysql');

var connection = mysql.createConnection({
  host  : 'de-rds.cmhqpqcb1nfr.us-west-2.rds.amazonaws.com',
  user  : 'group3',
  password  : 'cpengroup3',
  database  : 'dewatch'
});
connection.connect(function(err){
    if(err){
      console.log("Error connecting database ... @records_route");
      throw err;
    }
    console.log("Database is connected ... @records_route");
});

exports.read = function(req, res){
  var uid = req.body.uid;
  var date = req.body.date;

  if(req.body.date == null){ // used for retrieving all the records from the user
    connection.query('SELECT * FROM exer_records WHERE uid = ?', [uid], function(error, results, fields){
        if(error){
          console.log("ERROR occured", error);
          res.send({
              "code":400,
              "failed":"error occured"
          })
        }
        else{
          console.log("The solution is : ", results);
          res.json(results);
        }

  });
  }
  else{
    connection.query('SELECT * FROM exer_records WHERE uid = ? AND date = ?', [uid, date], function(error, results, fields){ // records for specific date
        if(error){
          console.log("ERROR occured", error);
          res.send({
              "code":400,
              "failed":"error occured"
          })
        }
        else{
          console.log("The solution is : ", results);
          res.json(results);
        }
  });
  }
}

exports.write = function(req, res){
 var content = {
   "uid":req.body.uid,
   "date":req.body.date,
   "time":req.body.time,
   "distance":req.body.distance,
   "time_traveled":req.body.time_traveled,
   "avg_speed":req.body.avg_speed,
   "avg_hr":req.body.avg_hr,
   "avg_o2":req.body.avg_o2,
   "gps_coord":req.body.gps_coord,
   "speeds":req.body.speeds,
   "hrs":req.body.hrs,
   "o2s":req.body.o2s,
   "time_list":req.body.time_list
  }

 connection.query('INSERT INTO exer_records SET ?', content, function(error, results, fields){
     if(error){
      console.log("error ocurred", error);
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
      
