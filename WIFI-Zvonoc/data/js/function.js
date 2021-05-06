var xmlHttp=createXmlHttpObject();
var doc = document;
var activ=true,preloud=true;
doc.addEventListener("click",function(){if(document.activeElement.id=="time_in"){cekbox();doc.getElementById("scales").checked=0;}})
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
 if(data2["flag1"]==1){
   doc.getElementById("predupbutn").value="Да";
   doc.getElementById("predupbutn").className="predupbutn_da";
 }
 else{
	 doc.getElementById("predupbutn").value="Нет";
	 doc.getElementById("predupbutn").className="predupbutn_net";
 }
if (data2["flag2"]==0) {doc.getElementById("ring_aut").innerHTML="Одинаковые";doc.getElementById("ring_aut").className=0;}
   else if (data2["flag2"]==1) {
	       console.log("ok");
	       doc.getElementById("ring_aut").className=0;
		   ring_levo();

		   doc.getElementById("dlina_inputon1").value=data2["flag5"];
   }
   if(data2["saturday"]==1) {doc.getElementById("box").checked=true; tumbler=1;}
   else tumbler=0;
   setInterval(function(){
   if(activ){
   var data = new Date(),str="";
   str+=data.getFullYear()+"-";
   if(data.getMonth()+1>=10)str+=(parseInt(data.getMonth())+1)+"-";
   else str+="0"+(parseInt(data.getMonth())+1)+"-";
   if(data.getDate()>=10)str+=data.getDate()+"T";
   else str+="0"+data.getDate()+"T";
   if(data.getHours()>=10)str+=data.getHours()+":";
   else str+="0"+data.getHours()+":";
   if(data.getMinutes()>=10)str+=data.getMinutes()+":";
   else str+="0"+data.getMinutes()+":";
   if(data.getSeconds()>=10)str+=data.getSeconds();
   else str+="0"+data.getSeconds();
  doc.getElementById("time_in").value=str;}
   }, 1000);
  if(preloud){
 setTimeout(function(){doc.getElementById("page-preloader").style.opacity="0";},1000);
  setTimeout(function(){doc.getElementById("page-preloader").parentNode.removeChild(doc.getElementById("page-preloader"));},2000);preloud=false;}
 handleServerResponse();
}

function val(id){
 var v = doc.getElementById(id).value;
 return v;
}
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
 submit.value = 'Подождите...';
 submit_disabled(true);
}
function submit_disabled(request){
 var inputs = doc.getElementsByTagName("input");
 for (var i = 0; i < inputs.length; i++) {
  if (inputs[i].type === 'submit') {inputs[i].disabled = request;}
 }
}
function toggle(target) {
 var curVal = doc.getElementById(target).className;
 doc.getElementById(target).className = (curVal === 'hidden') ? 'show' : 'hidden';
}
