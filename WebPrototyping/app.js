var express = require('express');
var app = express();
var server = app.listen(80, function(){
    console.log("Linknode Server Started at :80");
});

app.get('/',function(req,res){
   res.render('index')
});

app.get('/d3example',function(req,res){
   res.render('d3example')
});

// Views
app.set('views', './views');
app.set('view engine', 'ejs');
app.use(express.static(__dirname));

//socket-io
const io = require('socket.io').listen(server);

var socketID;

io.on('connection', function(socket){
    console.log("[LOG] Client Connected")
    console.log(socket.id);
    socketID = socket.id;
    socket.on('message', function(data){
        console.log(data);
        io.to(socketID).emit('value', data); // web to web
        // io.emit(~~~)
        // udp.send(JSON.stringify(data), UDP_PORT, ARDUINO_IP, function(){
        // })
    });
    socket.on('fromarduino', function(data){
      console.log(socket.id + "/ Received: " + JSON.stringify(data));
    });
});
