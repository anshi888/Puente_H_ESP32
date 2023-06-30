#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
//Headers
#include "CWifi.h"

///credenciales conexion
//const char* wifi_network_ssid = "STAMM-939";
//const char* wifi_network_password =  "Stammnet939";
const char *wifi_network_ssid = "STAMM-311";
const char *wifi_network_password ="Stammnet311";
const char *soft_ap_ssid = "PuenteH";
const char *soft_ap_password = "puente12345";
String outputString = "100";
String outputString2 = "100";
String outputString3 = "100";

int ton=300;
int ton_vi=300;
int toff_v=300;
String ton_t="";
String ton_v="";
String toff_vi="";
bool bandera= false;
bool encendido=false;
/// 
//Iniciar Wifi 939
//IPAddress ip(10,1,1,125);
//IPAddress gateway(10, 10, 10, 1);
//IPAddress subnet(255, 255, 255, 0);
//Iniciar Wifi
IPAddress ip(10,31,110,83);     
IPAddress gateway(10,31,110,1);   
IPAddress subnet(255,255,255,0);  
void wifi(){
  int tiempoespera=0;
  WiFi.mode(WIFI_MODE_APSTA);
  WiFi.softAP(soft_ap_ssid, soft_ap_password);
  WiFi.begin(wifi_network_ssid, wifi_network_password);
  while ((WiFi.status() != WL_CONNECTED ) && (tiempoespera<20)) {
   // delay(500);
   // Serial.println("Connecting to WiFi..");
    tiempoespera++;
  }

///////////////borra y lee por puerto serie la ip aleatoria
  WiFi.config(ip, gateway, subnet);

  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
  Serial.print("ESP32 IP as soft AP: ");
  Serial.println(WiFi.softAPIP());
  Serial.print("ESP32  IP on the WiFi network: ");
  Serial.println(WiFi.localIP());
  }
 // void updatePage()
//{
  ////page.replace("tonxx", (String)ton);
    //page.toCharArray(pagechar, 500);
    
//}
//Variables del formulario para realizar el METODO POST
 void handleFormText(AsyncWebServerRequest *request)
{
//variable de frecuencia
 ton_t = request->arg("ton"); 
 ton= ton_t.toInt();
 //Tiempo de encendido 
 encendido=false;

 outputString=(String)ton;
 bandera=true;
//updatePage();
request->redirect("/");
}
//Variables del formulario para realizar el METODO POST
 void handleFormTextdos(AsyncWebServerRequest *request)
{
 encendido=true;

 //Tiempo de encendido 
 ton_v=request->arg("ton_on");
 ton_vi=ton_v.toInt();
 //
 toff_vi=request->arg("ton_off");
 toff_v=toff_vi.toInt();

 outputString2=(String)ton_vi;
 outputString3=(String)toff_v;

 bandera=true;
//updatePage();
request->redirect("/");
}

void get_service(){
   // updatePage();

    //---------- GET ------------------------//
      server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    if (ON_STA_FILTER(request)) {
       //request->send(SD, "/index.html");
        request->send_P(200, "text/html", mediciones);
      return;
    } else if (ON_AP_FILTER(request)) {
       
       //request->send(SD, "/index.html");
        request->send_P(200, "text/html",  mediciones);

      return;
    }
    //request->send( SD, "/index.html");
        request->send_P(200, "text/html",  mediciones);

  });
       server.on("/stop", HTTP_GET, [](AsyncWebServerRequest * request) {
    if (ON_STA_FILTER(request)) {
       //request->send(SD, "/index.html");
       bandera=false;
        request->redirect("/");

      return;
    } else if (ON_AP_FILTER(request)) {
       
       //request->send(SD, "/index.html");
       bandera=false;
        request->redirect("/");


      return;
    }
    //request->send( SD, "/index.html");
    bandera=false;
        request->redirect("/");


  });
  //--------------POST------------------
  server.on("/get", HTTP_POST, handleFormText);
  server.on("/get2", HTTP_POST, handleFormTextdos);

  server.onNotFound([](AsyncWebServerRequest *request) {
      request->send(400, "text/plain", "Not found");
   });
  server.begin(); //abro el server_
  }

