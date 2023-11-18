
//Llamado de libreríaas a utilizar y definición de pines para la lcd
#include <WiFi.h> //Conexión WiFi
#include <WiFiClient.h> //
#include <WebServer.h> //Librería para realización del WebServer 
#include <ESPmDNS.h> //Librería para definir IP estable
#include <LiquidCrystal.h> //Librería para la pantalla LCD
#define RS 25
#define EN 26
#define D4 27
#define D5 14
#define D6 19
#define D7 18

const char* ssid = "RABT(2)"; //Nombre de la red WiFi
const char* password = "berganzaT"; //Contraseña de la red WiFi
char tiva1; //Variable para datos que vienen de la Tiva 1
char tiva2; //Variable para datos que vienen de la Tiva 2

//Variables para los parqueos
bool lugar1 = false;
bool lugar2 = false;
bool lugar3 = false;
bool lugar4 = false;
bool lugar5 = false;
bool lugar6 = false;
bool lugar7 = false;
bool lugar8 = false;

//Variables para los valores de los parqueos en la lcd
uint8_t valor1;
uint8_t valor2;
uint8_t valor3;
uint8_t valor4;
uint8_t valor5;
uint8_t valor6;
uint8_t valor7;
uint8_t valor8;
uint8_t lugares1;
uint8_t lugares2;
uint8_t espacioslibres;

WebServer server(80); //Elaboración del WebServer en el puerto 80 del ESP
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7); 

//Función para enviar nuestro código HTML al webserver
void handleRoot() {
  server.send(200, "text/html", HTML()); //Código HTML de la página web
}

//Función para definir el estado del parqueo
void sensor1(){
  if (lugar1 == false) {
    server.send(200, "text/plain", "parqueoestado libre"); 
  } else {
    server.send(200, "text/plain", "parqueoestado ocupado"); 
  }
}

void sensor2(){
  if (lugar2 == false) {
    server.send(200, "text/plain", "parqueoestado libre"); 
    server.send(200, "text/plain", "parqueoestado ocupado"); 
  }
}

void sensor3(){
  if (lugar3 == false) {
    server.send(200, "text/plain", "parqueoestado libre"); 
  } else {
    server.send(200, "text/plain", "parqueoestado ocupado");
  }
}

void sensor4(){
  if (lugar4 == false) {
    server.send(200, "text/plain", "parqueoestado libre"); 
  } else {
    server.send(200, "text/plain", "parqueoestado ocupado");
  }
}

void sensor5(){
  if (lugar5 == false) {
    server.send(200, "text/plain", "parqueoestado libre"); 
  } else {
    server.send(200, "text/plain", "parqueoestado ocupado"); 
  }
}

void sensor6(){
  if (lugar6 == false) {
    server.send(200, "text/plain", "parqueoestado libre"); 
  } else {
    server.send(200, "text/plain", "parqueoestado ocupado"); 
  }
}

void sensor7(){
  if (lugar7 == false) {
    server.send(200, "text/plain", "parqueoestado libre"); 
  } else {
    server.send(200, "text/plain", "parqueoestado ocupado"); 
  }
}

void sensor8(){
  if (lugar8 == false) {
    server.send(200, "text/plain", "parqueoestado libre"); 
  } else {
    server.send(200, "text/plain", "parqueoestado ocupado"); 
  }
}

//Funcion por si no se encuentra la dirección del servidor
void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void setup(void) {
  Serial.begin(115200); 
  Serial1.begin(115200, SERIAL_8N1, 21, 23); //comunicación serial para la TIVA 2
  Serial2.begin(115200, SERIAL_8N1, 16, 17); //Comunicación serial para la TIVA 1
  lcd.begin(16, 2); //Setup de la LCD 
  lcd.setCursor(0,0); 
  lcd.print("Parqueomatic"); //Escribir parqueomatic
  lcd.setCursor(12,0); 
  lcd.print("P:"); //Escribir los parqueos totales
  lcd.setCursor(0,1); 
  lcd.print("valor1:"); //Escribir valor1
  lcd.setCursor(8,1); 
  lcd.print("valor2:"); //Escribir valor2
  WiFi.mode(WIFI_STA); 
  WiFi.begin(ssid, password); //Inicio de conexión WiFi 
  Serial.println("");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP()); //Escribir la dirección IP en el puerto serial
  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }

  //Establecer nombre de dirección a las variables a utilizar en el código html
  server.on("/", handleRoot);
  server.on("/l1", sensor1);
  server.on("/l2", sensor2);
  server.on("/l3", sensor3);
  server.on("/l4", sensor4);
  server.on("/l5", sensor5);
  server.on("/l6", sensor6);
  server.on("/l7", sensor7);
  server.on("/l8", sensor8);

  server.onNotFound(handleNotFound); //Cuando se pida una direccion inexistente llamar a la función necesaria

  server.begin(); //Inicio del server
  Serial.println("HTTP server started");
}

//Función para chequear la información de la Tiva1
void check_tiva1(){
  tiva1 = Serial2.read(); //Leer de UART2
  if (tiva1 == 0){
    lugar1 = false;
    lugar2 = false;
    lugar3 = false;
    lugar4 = false;
  }
  else if (tiva1 == 1){
    lugar1 = true;
    lugar2 = false;
    lugar3 = false;
    lugar4 = false;
  }
  else if (tiva1 == 2){
    lugar1 = false;
    lugar2 = true;
    lugar3 = false;
    lugar4 = false;
  }
  else if (tiva1 == 3){
    lugar1 = true;
    lugar2 = true;
    lugar3 = false;
    lugar4 = false;
  }
  else if (tiva1 == 4){
    lugar1 = false;
    lugar2 = false;
    lugar3 = true;
    lugar4 = false;
  }
  else if (tiva1 == 5){
    lugar1 = true;
    lugar2 = false;
    lugar3 = true;
    lugar4 = false;
  }
  else if (tiva1 == 6){
    lugar1 = false;
    lugar2 = true;
    lugar3 = true;
    lugar4 = false;
  }
  else if (tiva1 == 7){
    lugar1 = true;
    lugar2 = true;
    lugar3 = true;
    lugar4 = false;
  }
  else if (tiva1 == 8){
    lugar1 = false;
    lugar2 = false;
    lugar3 = false;
    lugar4 = true;
  }
  else if (tiva1 == 9){
    lugar1 = true;
    lugar2 = false;
    lugar3 = false;
    lugar4 = true;
  }
  else if (tiva1 == 10){
    lugar1 = false;
    lugar2 = true;
    lugar3 = false;
    lugar4 = true;
  }
  else if (tiva1 == 11){
    lugar1 = true;
    lugar2 = true;
    lugar3 = false;
    lugar4 = true;
  }
  else if (tiva1 == 12){
    lugar1 = false;
    lugar2 = false;
    lugar3 = true;
    lugar4 = true;
  }
  else if (tiva1 == 13){
    lugar1 = true;
    lugar2 = false;
    lugar3 = true;
    lugar4 = true;
  }
  else if (tiva1 == 14){
    lugar1 = false;
    lugar2 = true;
    lugar3 = true;
    lugar4 = true;
  }
  else if (tiva1 == 15){
    lugar1 = true;
    lugar2 = true;
    lugar3 = true;
    lugar4 = true;
  }
}

void check_tiva2(){
  tiva2 = Serial1.read(); //Leer del UART1
  Serial.print(tiva2-48);
  if (tiva2 == 0){
    lugar5 = false;
    lugar6 = false;
    lugar7 = false;
    lugar8 = false;
  }
  else if (tiva2 == 1){
    lugar5 = true;
    lugar6 = false;
    lugar7 = false;
    lugar8 = false;
  }
  else if (tiva2 == 2){
    lugar5 = false;
    lugar6 = true;
    lugar7 = false;
    lugar8 = false;
  }
  else if (tiva2 == 3){
    lugar5 = true;
    lugar6 = true;
    lugar7 = false;
    lugar8 = false;
  }
  else if (tiva2 == 4){
    lugar5 = false;
    lugar6 = false;
    lugar7 = true;
    lugar8 = false;
  }
  else if (tiva2 == 5){
    lugar5 = true;
    lugar6 = false;
    lugar7 = true;
    lugar8 = false;
  }
  else if (tiva2 == 6){
    lugar5 = false;
    lugar6 = true;
    lugar7 = true;
    lugar8 = false;
  }
  else if (tiva2 == 7){
    lugar5 = true;
    lugar6 = true;
    lugar7 = true;
    lugar8 = false;
  }
  else if (tiva2 == 8){
    lugar5 = false;
    lugar6 = false;
    lugar7 = false;
    lugar8 = true;
  }
  else if (tiva2 == 9){
    lugar5 = true;
    lugar6 = false;
    lugar7 = false;
    lugar8 = true;
  }
  else if (tiva2 == 10){
    lugar5 = false;
    lugar6 = true;
    lugar7 = false;
    lugar8 = true;
  }
  else if (tiva2 == 11){
    lugar5 = true;
    lugar6 = true;
    lugar7 = false;
    lugar8 = true;
  }
  else if (tiva2 == 12){
    lugar5 = false;
    lugar6 = false;
    lugar7 = true;
    lugar8 = true;
  }
  else if (tiva2 == 13){
    lugar5 = true;
    lugar6 = false;
    lugar7 = true;
    lugar8 = true;
  }
  else if (tiva2 == 14){
    lugar5 = false;
    lugar6 = true;
    lugar7 = true;
    lugar8 = true;
  }
  else if (tiva2 == 15){
    lugar5 = true;
    lugar6 = true;
    lugar7 = true;
    lugar8 = true;
  }
}

//Función para las sumas para la lcd
void check(){
  if (lugar1 == true){
    valor1 = 1;
  }
  else{
    valor1 = 0;
  }
  if (lugar2 == true){
    valor2 = 1;
  }
  else{
    valor2 = 0;
  }
  if (lugar3 == true){
    valor3 = 1;
  }
  else{
    valor3 = 0;
  }
  if (lugar4 == true){
    valor4 = 1;
  }
  else{
    valor4 = 0;
  }
  if (lugar5 == true){
    valor5 = 1;
  }
  else{
    valor5 = 0;
  }
  if (lugar6 == true){
    valor6 = 1;
  }
  else{
    valor6 = 0;
  }
  if (lugar7 == true){
    valor7 = 1;
  }
  else{
    valor7 = 0;
  }
  if (lugar8 == true){
    valor8 = 1;
  }
  else{
    valor8 = 0;
  }
}

void loop(void) {
  server.handleClient(); //Mantener el servidor 
  check_tiva1(); //revisar los datos de la tiva 1
  check_tiva2(); //revisar los datos de la tiva 2
  check(); //suma de los parqueos
  lugares1 = valor1 + valor2 + valor3 + valor4; //Suma de parqueos en tiva 1
  lugares2 = valor5 + valor6 + valor7 + valor8; //Suma de parqueos en tiva 2
  espacioslibres = valor1 + valor2 + valor3 + valor4 + valor5 + valor6 + valor7 +valor8; //Suma de espacioslibres totales
  lcd.setCursor(13, 0); 
  lcd.print(String(espacioslibres)); //Mostrar parqueos totales dispnibles
  lcd.setCursor(3,1); 
  lcd.print(String(lugares1)); //Mostrar los parqueos dispnibles en la tiva 1
  lcd.setCursor(12,1); 
  lcd.print(String(lugares2)); //Mostrar los parqueos espacioslibres en la tiva 2
}

//Código HTML
String HTML(){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr += "<meta charset=\"UTF-8\">\n";
  ptr +="<title>PARQUEOMATIC</title>\n";
  ptr +="  <style>\n";
  ptr +="    /* CSS Styling */\n";
  /* Estilos para la página */
  ptr +="    body {\n";
  ptr +="      background-color: #001f3f;\n";  //color azul marino de fondo 
  ptr +="      font-family: 'Arial', sans-serif;\n"; //tipo de letra
  ptr +="      color: #ffffff;\n"; // color de letra
  ptr +="    }\n";
  ptr +="\n";
  ptr +="    h1 {\n";
  ptr +="      color: #ffffff;\n";
  ptr +="    }\n";
  ptr +="\n";
  ptr +="    table {\n";
  ptr +="      border-collapse: collapse;\n";
  ptr +="      width: 50%;\n";
  ptr +="      margin: 20px auto;\n";
  ptr +="    }\n";
  ptr +="\n";
  ptr +="    th, td {\n";
  ptr +="      border: 1px solid #dddddd;\n";
  ptr +="      text-align: center;\n";
  ptr +="      padding: 8px;\n";
  ptr +="    }\n";
  ptr +="\n";
  ptr +="    th {\n";
  ptr +="      background-color: #ff0000;\n"; //color rojo para los títulos de la tabla
  ptr +="      color: #ffffff;\n"; // color blanco para las letras
  ptr +="    }\n";
  ptr +="\n";
  //estilos para la tabla y cuadros
  ptr +="    .parqueoestado {\n";
  ptr +="      width: 20px;\n";
  ptr +="      height: 20px;\n";
  ptr +="      margin-right: 5px;\n";
  ptr +="      display: inline-block;\n";
  ptr +="      transition: background-color 0.3s ease;\n";
  ptr +="    }\n";
  ptr +="\n";
  ptr +="    .libre {\n";
  ptr +="      background-color: #34c759;\n";
  ptr +="    }\n";
  ptr +="\n";
  ptr +="    .ocupado {\n";
  ptr +="      background-color: #ff3b30;\n";
  ptr +="    }\n";
  ptr +="  </style>\n";
  ptr +="</head>\n";
  ptr +="<body onload=\"process()\">\n";
  ptr +="  <h1>PARQUEMATIC UVG &#128526</h1>\n";
  ptr +="  <table>\n";
  ptr +="  <tr>\n";
  ptr +="   <th>Parqueo</th>\n";
  ptr +="   <th>Estado</th>\n";
  ptr +="  </tr>\n";
  ptr +="\n";
  ptr +="  <tr>\n";
  ptr +="  <td>1</td>\n";
  ptr +="<td><div id=\"spot1\" class=\"parqueoestado\"></div></td>\n";
  ptr +="  </tr>\n";
  ptr +="  <tr>\n";
  ptr +="  <td>2</td>\n";
  ptr +="<td><div id=\"spot2\" class=\"parqueoestado\"></div></td>\n";
  ptr +="  </tr>\n";
  ptr +="  <tr>\n";
  ptr +="  <td>3</td>\n";
  ptr +="<td><div id=\"spot3\" class=\"parqueoestado\"></div></td>\n";
  ptr +="  </tr>\n";
  ptr +="  <tr>\n";
  ptr +="  <td>4</td>\n";
  ptr +="<td><div id=\"spot4\" class=\"parqueoestado\"></div></td>\n";
  ptr +="  </tr>\n";
  ptr +="  <tr>\n";
  ptr +="  <td>5</td>\n";
  ptr +="<td><div id=\"spot5\" class=\"parqueoestado\"></div></td>\n";
  ptr +="  </tr>\n";
  ptr +="  <tr>\n";
  ptr +="  <td>6</td>\n";
  ptr +="<td><div id=\"spot6\" class=\"parqueoestado\"></div></td>\n";
  ptr +="  </tr>\n";
  ptr +="  <tr>\n";
  ptr +="  <td>7</td>\n";
  ptr +="<td><div id=\"spot7\" class=\"parqueoestado\"></div></td>\n";
  ptr +="  </tr>\n";
  ptr +="  <tr>\n";
  ptr +="  <td>8</td>\n";
  ptr +="<td><div id=\"spot8\" class=\"parqueoestado\"></div></td>\n";
  ptr +="  </tr>\n";
  ptr +="  </div>\n";
  ptr +="\n";
  ptr +="<script>\n";
  ptr +="function updateColor1() {\n";
  ptr +="var xhttp = new XMLHttpRequest();\n";
  ptr +="xhttp.onreadystatechange = function() {\n";
  ptr +="if (this.readyState == 4 && this.status == 200) {\n";
  ptr +="document.getElementById('spot1').className = this.responseText;\n";
  ptr +="}\n";
  ptr +="};\n";
  ptr +="xhttp.open('GET', '/l1', true);\n";
  ptr +="xhttp.send();\n";
  ptr +="setTimeout(updateColor1, 500);}\n";

  ptr +="function updateColor2() {\n";
  ptr +="var xhttp = new XMLHttpRequest();\n";
  ptr +="xhttp.onreadystatechange = function() {\n";
  ptr +="if (this.readyState == 4 && this.status == 200) {\n";
  ptr +="document.getElementById('spot2').className = this.responseText;\n";
  ptr +="}\n";
  ptr +="};\n";
  ptr +="xhttp.open('GET', '/l2', true);\n";
  ptr +="xhttp.send();\n";
  ptr +="setTimeout(updateColor2, 500);}\n";

  ptr +="function updateColor3() {\n";
  ptr +="var xhttp = new XMLHttpRequest();\n";
  ptr +="xhttp.onreadystatechange = function() {\n";
  ptr +="if (this.readyState == 4 && this.status == 200) {\n";
  ptr +="document.getElementById('spot3').className = this.responseText;\n";
  ptr +="}\n";
  ptr +="};\n";
  ptr +="xhttp.open('GET', '/l3', true);\n";
  ptr +="xhttp.send();\n";
  ptr +="setTimeout(updateColor3, 500);}\n";

  ptr +="function updateColor4() {\n";
  ptr +="var xhttp = new XMLHttpRequest();\n";
  ptr +="xhttp.onreadystatechange = function() {\n";
  ptr +="if (this.readyState == 4 && this.status == 200) {\n";
  ptr +="document.getElementById('spot4').className = this.responseText;\n";
  ptr +="}\n";
  ptr +="};\n";
  ptr +="xhttp.open('GET', '/l4', true);\n";
  ptr +="xhttp.send();\n";
  ptr +="setTimeout(updateColor4, 500);}\n";

  ptr +="function updateColor5() {\n";
  ptr +="var xhttp = new XMLHttpRequest();\n";
  ptr +="xhttp.onreadystatechange = function() {\n";
  ptr +="if (this.readyState == 4 && this.status == 200) {\n";
  ptr +="document.getElementById('spot5').className = this.responseText;\n";
  ptr +="}\n";
  ptr +="};\n";
  ptr +="xhttp.open('GET', '/l5', true);\n";
  ptr +="xhttp.send();\n";
  ptr +="setTimeout(updateColor5, 500);}\n";

  ptr +="function updateColor6() {\n";
  ptr +="var xhttp = new XMLHttpRequest();\n";
  ptr +="xhttp.onreadystatechange = function() {\n";
  ptr +="if (this.readyState == 4 && this.status == 200) {\n";
  ptr +="document.getElementById('spot6').className = this.responseText;\n";
  ptr +="}\n";
  ptr +="};\n";
  ptr +="xhttp.open('GET', '/l6', true);\n";
  ptr +="xhttp.send();\n";
  ptr +="setTimeout(updateColor6, 500);}\n";

  ptr +="function updateColor7() {\n";
  ptr +="var xhttp = new XMLHttpRequest();\n";
  ptr +="xhttp.onreadystatechange = function() {\n";
  ptr +="if (this.readyState == 4 && this.status == 200) {\n";
  ptr +="document.getElementById('spot7').className = this.responseText;\n";
  ptr +="}\n";
  ptr +="};\n";
  ptr +="xhttp.open('GET', '/l7', true);\n";
  ptr +="xhttp.send();\n";
  ptr +="setTimeout(updateColor7, 500);}\n";

  ptr +="function updateColor8() {\n";
  ptr +="var xhttp = new XMLHttpRequest();\n";
  ptr +="xhttp.onreadystatechange = function() {\n";
  ptr +="if (this.readyState == 4 && this.status == 200) {\n";
  ptr +="document.getElementById('spot8').className = this.responseText;\n";
  ptr +="}\n";
  ptr +="};\n";
  ptr +="xhttp.open('GET', '/l8', true);\n";
  ptr +="xhttp.send();\n";
  ptr +="setTimeout(updateColor8, 500);}\n";

  ptr +="updateColor1();\n";
  ptr +="updateColor2();\n";
  ptr +="updateColor3();\n";
  ptr +="updateColor4();\n";
  ptr +="updateColor5();\n";
  ptr +="updateColor6();\n";
  ptr +="updateColor7();\n";
  ptr +="updateColor8();\n";
  ptr +="</script>\n";
  
  ptr +="</table>\n";
  ptr +="</body>\n";
  ptr +="</html>";
  return ptr;
}

