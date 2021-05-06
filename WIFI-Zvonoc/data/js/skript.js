var doc = document;
var lessons,saturday;
var lessons2=0;
var i=0;
var vstavka1,vstavka2;
var flag=false;
var screen=window.innerWidth;
if(matchMedia){
	window.matchMedia("(max-width:767px)").addListener(changes);
    changes();
}
function changes(){
	if( saturday==1){
	screen=window.innerWidth;
	var elem=doc.createElement("div");
		elem.innerHTML="<h2>Суббота</h2>";
        elem.id="ss";
	if(screen>=767) {
		doc.getElementById("wrapper_2").removeChild(doc.getElementById("ss"));
		doc.getElementById("wrapper_2").insertBefore(elem,doc.getElementById("wrapperboodni"));}
	else {doc.getElementById("wrapper_2").removeChild(doc.getElementById("ss"));doc.getElementById("wrapper_2").insertBefore(elem,doc.getElementById("wrappersubota"));}
}}
function bild(){
	lessons=doc.getElementById("lessons").value;
	saturday=doc.getElementById("saturday").value;
   if (saturday==0){
	   doc.getElementById("wrapper").id="wrapper_1";
	   vstavka1=doc.getElementById("wrapper_1");
	   var tresh=[4+lessons*3];
   }
   else{
	   lessons2=doc.getElementById("lessonsSaturday").value;
	   doc.getElementById("wrapper").id="wrapper_2";
	   vstavka1=doc.getElementById("wrapper_2");
       var tresh=[12+lessons*3+lessons2*3];
   }
   tresh[i]=doc.createElement("div");
   tresh[i].id="wrapperboodni";i++;//0
   tresh[i]=doc.createElement("div");
   tresh[i].innerHTML="<h2>№</h2>";i++;//1
   tresh[i]=doc.createElement("div");
   tresh[i].innerHTML="<h2>Начало</h2>";i++;//2
   tresh[i]=doc.createElement("div");
   tresh[i].innerHTML="<h2>Конец</h2>";i++;//3
   if(saturday==1){
   tresh[i]=doc.createElement("div");
   tresh[i].id="wrappersubota";i++;//4
   tresh[i]=doc.createElement("div");
   tresh[i].innerHTML="<h2>№</h2>";i++;//5
   tresh[i]=doc.createElement("div");
   tresh[i].innerHTML="<h2>Начало</h2>";i++;//6
   tresh[i]=doc.createElement("div");
   tresh[i].innerHTML="<h2>Конец</h2>";i++;//7
   tresh[i]=doc.createElement("div");
   tresh[i].innerHTML="<h2>Будни</h2>";
   vstavka1.appendChild(tresh[i]);i++;//8
   tresh[i]=doc.createElement("div");
   tresh[i].innerHTML="<h2>Суббота</h2>";
   tresh[i].id="ss";
   vstavka1.appendChild(tresh[i]);i++;//9
   if(screen<767){vstavka1.removeChild(tresh[i-1]);flag=false;}
   doc.getElementById("plus_minus").id="plus_minus_4"; 
   
   tresh[i]=doc.createElement("div");
   tresh[i].innerHTML='<button class="minus" onclick="minus_s();"><div class="min">-</div></button>';
   doc.getElementById("plus_minus_4").appendChild(tresh[i]);i++;
   tresh[i]=doc.createElement("div");
   tresh[i].innerHTML='<button class="plus" onclick="plus_s();"><div class="plu">+</div></button>';
   doc.getElementById("plus_minus_4").appendChild(tresh[i]);i++;
   vstavka1.appendChild(tresh[0]);
   if(screen<767)vstavka1.appendChild(tresh[9]);
   vstavka1.appendChild(tresh[4]);
   vstavka1=tresh[0];
   vstavka2=tresh[4];
   for(var h=1;h<=3;h++){
	   vstavka1.appendChild(tresh[h]);
	   vstavka2.appendChild(tresh[h+4]);
	   }
   }
   else{
	 vstavka1.appendChild(tresh[0]);
     vstavka1=tresh[0]; 
     for(var h=1;h<=3;h++) vstavka1.appendChild(tresh[h]);	 
   }
   for (var rix=1;rix<=lessons;rix++){
	   tresh[i]=doc.createElement("div");
	   tresh[i].id="box_t"+rix;
       tresh[i].innerHTML="<h2>"+rix+" Урок</h2>";
	   vstavka1.appendChild(tresh[i]);i++;
	   tresh[i]=doc.createElement("div"); 
	   tresh[i].id="box_i"+rix;
	   tresh[i].innerHTML='<input class="input1" type="time" value="00:00" min="00:00" max="24:00" id="start'+rix+'">';
       vstavka1.appendChild(tresh[i]);i++;
	   tresh[i]=doc.createElement("div"); 
	   tresh[i].id="box_e"+rix;
	   tresh[i].innerHTML='<input class="input1" type="time" value="00:00"  min="00:00" max="24:00" id="end'+rix+'">';
       vstavka1.appendChild(tresh[i]);i++;
   }
   if(saturday==1){
	   var h=1;
	   for (var rix=parseInt(lessons,10)+1;rix<=parseInt(lessons,10)+parseInt(lessons2,10);rix++){
	   tresh[i]=doc.createElement("div");
	   tresh[i].id="box_ts"+rix;
       tresh[i].innerHTML="<h2>"+h+" Урок</h2>";h++;
	   vstavka2.appendChild(tresh[i]);i++;
	   tresh[i]=doc.createElement("div"); 
	   tresh[i].id="box_is"+rix;
	   tresh[i].innerHTML='<input class="input1" type="time" value="00:00" min="00:00" max="24:00" id="start'+rix+'">';
       vstavka2.appendChild(tresh[i]);i++;
	   tresh[i]=doc.createElement("div"); 
	   tresh[i].id="box_es"+rix;
	   tresh[i].innerHTML='<input class="input1" type="time" value="00:00"  min="00:00" max="24:00" id="end'+rix+'">';
       vstavka2.appendChild(tresh[i]);i++;
   }
   }
display();
}
function display(){
	var data = "";
      $.getJSON("config.json",function(result){
         $.each(result,function(i,res){
            data=data+"\u0022"+i+"\u0022"+":"+"\u0022"+res+"\u0022"+",";
         });
         data="{"+data.substring(0,data.length-1) +"}";
          var temp=JSON.parse(data);
          var olllessons;
	      if (saturday==1) olllessons=parseInt(lessons,10)+parseInt(lessons2,10); else olllessons=lessons;		  
		    for(var i =1;i<=olllessons;i++){
			 if(temp["start"+i]!="")doc.getElementById("start"+i).value =  temp["start"+i];
			 if(temp["end"+i]!="")doc.getElementById("end"+i).value =  temp["end"+i];
		 }
      });
	setTimeout(function(){doc.getElementById("page-preloader").style.opacity="0";},1000);
	setTimeout(function(){doc.getElementById("page-preloader").parentNode.removeChild(doc.getElementById("page-preloader"));},2000);
}
function plus(){
	if(saturday==0 && lessons==50) alert("Колличество уроков не может быть больше чем 50");
	if(saturday==1 && lessons==25) alert("Колличество уроков не может быть больше чем 25");
	if(saturday==0 && lessons<50||saturday==1 && lessons <25){
	var dop=[3];
	if(saturday==1)for (var rix=parseInt(lessons,10)+parseInt(lessons2,10);rix!=parseInt(lessons,10);rix--){
		doc.getElementById("start"+rix).id="start"+(rix+1);
		doc.getElementById("end"+rix).id="end"+(rix+1);
		doc.getElementById("box_ts"+rix).id="box_ts"+(rix+1);
		doc.getElementById("box_is"+rix).id="box_is"+(rix+1);
		doc.getElementById("box_es"+rix).id="box_es"+(rix+1);
	}
	lessons++;
	doc.getElementById("lessons").value++;
	dop[0]=doc.createElement("div");
    dop[0].id="box_t"+lessons;
    dop[0].innerHTML="<h2>"+lessons+" Урок</h2>";
	vstavka1.appendChild(dop[0]);
    dop[1]=doc.createElement("div");
    dop[1].id="box_i"+lessons;
    dop[1].innerHTML='<input class="input1" type="time" value="00:00" min="00:00" max="24:00" id="start'+lessons+'">';
	vstavka1.appendChild(dop[1]);
    dop[2]=doc.createElement("div");
    dop[2].id="box_e"+lessons;
    dop[2].innerHTML='<input class="input1" type="time" value="00:00"  min="00:00" max="24:00" id="end'+lessons+'">';
	vstavka1.appendChild(dop[2]);	
	send_request(this,'lessons?lessons='+lessons);
	}
	
}
function plus_s(){
	if(lessons2<25){
	var dop=[3];
	lessons2++;
	doc.getElementById("lessonsSaturday").value++;
    dop[0]=doc.createElement("div");
    dop[0].id="box_ts"+(parseInt(lessons,10)+parseInt(lessons2,10));
    dop[0].innerHTML="<h2>"+lessons2+" Урок</h2>";
	vstavka2.appendChild(dop[0]);
    dop[1]=doc.createElement("div");
    dop[1].id="box_is"+(parseInt(lessons,10)+parseInt(lessons2,10));
    dop[1].innerHTML='<input class="input1" type="time" value="00:00" min="00:00" max="24:00" id="start'+(parseInt(lessons,10)+parseInt(lessons2,10))+'">';
	vstavka2.appendChild(dop[1]);
    dop[2]=doc.createElement("div");
    dop[2].id="box_es"+(parseInt(lessons,10)+parseInt(lessons2,10));
    dop[2].innerHTML='<input class="input1" type="time" value="00:00"  min="00:00" max="24:00" id="end'+(parseInt(lessons,10)+parseInt(lessons2,10))+'">';
	vstavka2.appendChild(dop[2]);
    send_request(this,'lessonsSaturday?lessonsSaturday='+lessons2);	
	}
	else alert("Колличество уроков не может быть больше чем 25");
}
function minus(){
	     if(lessons>1){
			 doc.getElementById("lessons").value--;
			 vstavka1.removeChild(doc.getElementById("box_t"+lessons));
			 vstavka1.removeChild(doc.getElementById("box_i"+lessons));
			 vstavka1.removeChild(doc.getElementById("box_e"+lessons));
			 if(saturday==1)for (var rix=parseInt(lessons,10)+1;rix<=parseInt(lessons,10)+parseInt(lessons2,10);rix++){
		         doc.getElementById("start"+rix).id="start"+(rix-1);
		         doc.getElementById("end"+rix).id="end"+(rix-1);
		         doc.getElementById("box_ts"+rix).id="box_ts"+(rix-1);
		         doc.getElementById("box_is"+rix).id="box_is"+(rix-1);
		         doc.getElementById("box_es"+rix).id="box_es"+(rix-1);
	          }
			
			 lessons--; 
			 send_request(this,'lessons?lessons='+lessons);
		 }
		 else alert("Количество уроков не может быть меньше чем 1 в будни");
}
function minus_s(){
	if(lessons2>0){
	doc.getElementById("lessonsSaturday").value--;
	vstavka2.removeChild(doc.getElementById("box_ts"+(parseInt(lessons,10)+parseInt(lessons2,10))));
	vstavka2.removeChild(doc.getElementById("box_is"+(parseInt(lessons,10)+parseInt(lessons2,10))));
	vstavka2.removeChild(doc.getElementById("box_es"+(parseInt(lessons,10)+parseInt(lessons2,10))));
	lessons2--;
	send_request(this,'lessonsSaturday?lessonsSaturday='+lessons2);
	}
	else alert("Количество уроков не может быть меньше чем 0");
}
function btnsave(){
	var error=false,h=0,error1=0,errorlast=false,errorlast1="";
	if(saturday==1)var massiv=[lessons*2+lessons2*2];
	else massiv=[lessons*2];
	for(var rix=1;rix<=(parseInt(lessons,10)+parseInt(lessons2,10));rix++){
		massiv[h]=doc.getElementById("start"+rix).value;h++;
		massiv[h]=doc.getElementById("end"+rix).value;h++;
	}
	errorlast=false;error1=0;errorlast1="";
	for(h=0;h<parseInt(lessons*2,10)-1;h++){
		for(var k=h+1;k<parseInt(lessons*2,10);k++){
			if(massiv[h]==massiv[k]&&massiv[h]!="00:00"){
				error=true;
				error1++;
				errorlast1=massiv[h];
				if(h%2!=0){doc.getElementById("end"+((h+1)/2)).style.border = "2px solid red";}
				if(k%2!=0)doc.getElementById("end"+((k+1)/2)).style.border="2px solid red";
				if(h%2==0){doc.getElementById("start"+(h/2+1)).style.border = "2px solid red";}
				if(k%2==0)doc.getElementById("start"+(k/2+1)).style.border="2px solid red";
				if(k==(parseInt(lessons*2,10)-1))errorlast=true;
				}
		}
		if(error1==0&&errorlast1!=massiv[h]){
		if(h%2!=0){doc.getElementById("end"+((h+1)/2)).style.border = "none";}
		if(h%2==0){doc.getElementById("start"+(h/2+1)).style.border = "none";}
		}
		else error1=0;
	}
	if(!errorlast&&parseInt(lessons*2,10)>0)doc.getElementById("end"+lessons).style.border = "none";
	if (saturday==1){
	errorlast=false;error1=0;errorlast1="";
	for(h=parseInt(lessons*2,10);h<parseInt(lessons*2,10)+parseInt(lessons2*2,10)-1;h++){
		for(var k=h+1;k<parseInt(lessons*2,10)+parseInt(lessons2*2,10);k++){
			if(massiv[h]==massiv[k]&&massiv[h]!="00:00"){
				error=true;
				error1++;
				errorlast1=massiv[h];
				if(h%2!=0){doc.getElementById("end"+((h+1)/2)).style.border = "2px solid red";}
				if(k%2!=0)doc.getElementById("end"+((k+1)/2)).style.border="2px solid red";
				if(h%2==0){doc.getElementById("start"+(h/2+1)).style.border = "2px solid red";}
				if(k%2==0)doc.getElementById("start"+(k/2+1)).style.border="2px solid red";
				if(k==(parseInt(lessons*2,10)+parseInt(lessons2*2,10)-1))errorlast=true;
				}
		}
		if(error1==0&&errorlast1!=massiv[h]){
		if(h%2!=0){doc.getElementById("end"+((h+1)/2)).style.border = "none";}
		if(h%2==0){doc.getElementById("start"+(h/2+1)).style.border = "none";}
		}
		else error1=0;
	}
	if(!errorlast&&(lessons>0||lessons2>0))doc.getElementById("end"+(parseInt(lessons,10)+parseInt(lessons2,10))).style.border = "none";
	}
	
	if(lessons>0 && !error){
	var str="ring?";
	for( var rix =1;rix<=lessons;rix++){
		str+="start"+rix+"="+doc.getElementById("start"+rix).value+"&";
		if(rix!=lessons)str+="end"+rix+"="+doc.getElementById("end"+rix).value+"&";
	}
	if(saturday==0)str+="end"+lessons+"="+doc.getElementById("end"+lessons).value;
	else{
		
		str+="end"+lessons+"="+doc.getElementById("end"+lessons).value+"&";
		for(var rix =parseInt(lessons,10)+1;rix<=(parseInt(lessons,10)+parseInt(lessons2,10));rix++){
		str+="start"+rix+"="+doc.getElementById("start"+rix).value+"&";
		if(rix!=(parseInt(lessons,10)+parseInt(lessons2,10)))str+="end"+rix+"="+doc.getElementById("end"+rix).value+"&";
	  }
	  str+="end"+(parseInt(lessons,10)+parseInt(lessons2,10))+"="+doc.getElementById("end"+(parseInt(lessons,10)+parseInt(lessons2,10))).value;
	}
	send_request(this,str);
	}
	if(!error&&(lessons==0&&saturday==0)||(lessons==0&&saturday==1&&lessons2==0)) alert("Вам нечего сохранять");
	if(error)alert("Разница между звонками должна быть больше 1 минуты");
}
//Загрузка
var xmlHttp=createXmlHttpObject();
function createXmlHttpObject(){
 if(window.XMLHttpRequest){
  xmlHttp=new XMLHttpRequest();
 }else{
  xmlHttp=new ActiveXObject('Microsoft.XMLHTTP');
 }
 return xmlHttp;
}
function load(){
 if(xmlHttp.readyState==0 || xmlHttp.readyState==4){
  xmlHttp.open('PUT','/configs.json',true);
  xmlHttp.send(null);
  xmlHttp.onload = function(e) {
   jsonResponse=JSON.parse(xmlHttp.responseText);
   loadBlock();
  }
 }
}
function loadBlock(data2) {
 data2 = JSON.parse(xmlHttp.responseText);
 data = doc.getElementsByTagName('body')[0].innerHTML;
 var new_string;
for (var key in data2) {
 new_string = data.replace(new RegExp('{{'+key+'}}', 'g'), data2[key]);
 data = new_string;
}
 doc.getElementsByTagName('body')[0].innerHTML = new_string;
 bild();
}
//СОХРАНЕНИЕ
function send_request(submit,server){
 request = new XMLHttpRequest();
 request.open("POST", server, true);
 request.send();
 save_status(submit,request);
}
function save_status(submit,request){
 old_submit = submit.value;
 request.onreadystatechange = function() {
  if (request.readyState != 4) return;
  submit.value = request.responseText;
  setTimeout(function(){
   submit.value=old_submit;
   submit_disabled(false);
  }, 1000);
 }
 submit_disabled(true);
}
function submit_disabled(request){
 var inputs = doc.getElementsByTagName("input");
 for (var i = 0; i < inputs.length; i++) {
  if (inputs[i].type === 'submit') {inputs[i].disabled = request;}
 }
}