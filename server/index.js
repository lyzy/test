var express=require('express');
var app=express();
var path=require('path');
var context;
app.set('port',process.env.PORT || 3000);
app.use(require('body-parser')());

//set the handlebars
var handlebars=require('express-handlebars')
	.create({defaultLayout:'main'});
app.engine('handlebars',handlebars.engine);
//app.set('views',path.join(__dirname,'views'));
app.set('view engine','handlebars');

app.get('/',function(req,res){
	res.render('home');
})

app.post('/',function(req,res){
	console.log('Form: '+req.body.nombre+' '+req.body.hehe);
	context={title:"Muchas Gracias!",content:req.body.hehe,name:req.body.nombre};
	res.redirect(303,'/thanks');
})

app.get('/about',function(req,res){
	res.render('about');
})

app.get('/gpa',function(req,res){
	res.render('GPAcal');
})

app.get('/thanks',function(req,res){
	res.render('thanks',context);
})

app.get('/newhome',function(req,res){
	res.render('newhome');
})

app.use(express.static(__dirname+'/public'));

app.get('/consejo',function(req,res){
	res.render('consejo');
})

app.post('/consejo',function(req,res){
	console.log('Consejo: '+req.body.nombre+': '+req.body.consejo);
	context={title:"Muchas Gracias!",content:req.body.consejo,name:req.body.nombre};
	res.redirect(303,'/thanks');
})

app.use(function(req,res){
	res.type('text/plain');
	res.status(404);
	res.send('404-Not Found');
});

app.use(function(err,req,res,next){
	console.error(err.stack);
	res.type('text/plain');
	res.status(500);
	res.send('500-Server Error');
})

app.listen(app.get('port'),function(){
	console.log('Express stared on http://localhost:'+app.get('port')+': press Ctrl+C to terminate.');
});
