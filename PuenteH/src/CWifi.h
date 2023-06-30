#include <ESPAsyncWebServer.h>
#ifndef CWIFI_H
#define CWIFI_H

void wifi();
void get_service(); 
extern const char* wifi_network_ssid;
extern const char* wifi_network_password ;
extern const char *soft_ap_ssid;
extern const char *soft_ap_password;
extern int ton;
extern int ton_vi;
extern String ton_t;
extern String outputString;
extern String outputString2;
extern String outputString3;
extern bool encendido;

extern bool bandera;

//________WebPage para server______________________________
const char mediciones[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<style>
    body {
        background-color: rgb(135, 205, 170);
    }
    h2 {
        text-align: center;
        font-size: 45px;
    }
    
    label {
        text-align: center;
        font-size: 40px;
        margin: 10px;
    }
    
    #ingres {
        height: 40px;
        width: 400px;
        border-radius: 23px;
        margin-left: 20px;
        font-size: 20px;
        text-align: center;
    }
    
    form {
        text-align: center;
    }
    
    #stop {
        height: 40px;
        width: 400px;
        border-radius: 23px;
        margin-left: 20px;
        font-size: 20px;
    }
    
    #start {
        height: 40px;
        width: 400px;
        border-radius: 23px;
        margin-left: 20px;
        font-size: 20px;
    }
</style>

<body>
    <h2>Parametros de Onda Cuadrada</h2>
    <br>
    <br>
    <hr>
    <hr>
    <form action="/get" method="post">
        <br>
        <br>
        <label>  F [Hz]  :<input id="ingres" type="text" name="ton" value=""></label>
        <br>
        <br>
        <br>
        
        <input id="start" type="submit" value="Start">
    </form>
    <br>
    <hr>
    <hr>
    <br>
    <form action="/get2" method="post">
        <br>
        <br>
        <label>Toff[us]:<input id="ingres" type="text" name="ton_on" value=""></label>
        <br>
        <br>
        <label>Ton[us]:<input id="ingres" type="text" name="ton_off" value=""></label>
        <br>
        <br>
        <br>

        <input id="start" type="submit" value="Start">
    </form>
    <br>
    <hr>
    <hr>
    <br>
    <form action="/stop" method="get">
        <input id="stop" type="submit" value="Stop">
    </form>

    <br>
    
</body>

</html>
)=====";
//________WebPage para server______________________________
extern AsyncWebServer server;
#endif