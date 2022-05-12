#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#ifndef STASSID
#define STASSID "Redmix"
#define STAPSK  "redmi1021"
#endif
const int led = 12;
const char* ssid = STASSID;
const char* password = STAPSK;

ESP8266WebServer server(80);
const char* ind = {"<!DOCTYPE html>\n<html lang=\"en\">\n<head>\n    <meta charset=\"UTF-8\">\n    <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\n    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js\"></script>\n    <title>Document</title>\n</head>\n<body>\n<div class = \"card\">\n<div class = \"heading\">ESP LED CONTROL</div>\n<div class = \"btngrp\">\n<button id = \"on\">Turn on LED</button>\n<button id  = \"off\">Turn off LED</button>\n</div>\n</div>\n</body>\n<style>\n  body{\n      background-color: bisque;\n  }\n  .heading{\n      display:block;\n      font-size: 25px;\n      padding: 20px;\n      color:white;\n      box-shadow: 0 2px 3px white;\n     background-color: rgb(0, 0, 0);\n     opacity: 0.8;\n  }\n.card{\n       background-color: white;\n       box-shadow: 0 2px 3px #ccc;\n       height:fit-content;\n       border-radius: 10px;\n       width: 40%;\n       margin: auto;\n       margin-top: 180px;\n      display: flex;\n      justify-content: center;\n   }\n   #on{\n \n       background-color: #41ce00;\n       font-size: 30px;\n       color:white;\n       border:none;\n       border-radius: 10px;\n       display: block;\n       padding: 20px;\n       margin: 20px;\n       box-shadow: 0 2px 3px #41ce00;\n       text-decoration: none;\n   } \n   #off{\n       font-size: 30px;\n       background-color: #ff003c;\n       color:white;\n       border:none;\n       border-radius: 10px;\n       display: block;\n       padding: 20px;\n       margin: 20px;\n       box-shadow: 0 2px 3px #ff003c;\n       text-decoration: none;\n   }\n   #on:hover,#off:hover{\n       opacity: 0.8;\n       background-color: black;\n       box-shadow: 0 2px 3px #ccc;\n   }\n   #on:active,#off:active{\n       opacity: 1;\n       background-color: black;\n       box-shadow: 0 5px 10px #ccc;\n   }\n</style>\n<script>\n\nonbtn = document.getElementById('on');\noffbtn = document.getElementById('off');\n\nfunction turn_on()\n{\n    var xhttp = new XMLHttpRequest();\n  xhttp.onreadystatechange = function() {\n  \n    if (this.readyState == 4 && this.status == 200) {\n    \n    }\n   \n  \n  };\n  xhttp.open(\"POST\", \"/on\", true);\n  xhttp.send();\n\n}\nonbtn.addEventListener('click',turn_on);\nfunction turn_off()\n{\n    var xhttp = new XMLHttpRequest();\n  xhttp.onreadystatechange = function() {\n  \n    if (this.readyState == 4 && this.status == 200) {\n    \n    }\n   \n  \n  };\n  xhttp.open(\"POST\", \"/off\", true);\n  xhttp.send();\n\n}\noffbtn.addEventListener('click',turn_off);    \n</script>\n</html>"};
void handleroot(){
  server.send(200,"text/html",ind);
}
void handleon(){
  Serial.write('1');
  }
  void handleoff(){
    Serial.write('0');
    }



void setup(void) {
 
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }



  server.on("/", HTTP_GET, handleroot);  
  server.on("/on",HTTP_POST,handleon);
    server.on("/off",HTTP_POST,handleoff);



//////////////////////////////////////////////

  server.begin();
}

void loop(void) {
  server.handleClient();
  MDNS.update();
}
