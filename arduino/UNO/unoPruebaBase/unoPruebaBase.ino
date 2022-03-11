/*
  Hola Mundo
  Muestra un mensaje Hola mundo.
  Enciende un led durante un segundo, entonces lo apaga durante un segundo en un bucle infinito.
*/
// Solo se ejecuta una vez y se utiliza para inicializar las variables que después serán utilizadas.
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);//Inicializamos el led incorporado en la propia placa como una salida 
  Serial.begin(9600);//Inicializamos el puerto serie como salida para poder ver mensajes en el monitor del mencionado puerto serie a 9600 baudios
}
// Se ejecuta en bucle infinito, es decir mientras Arduino esté encendido las instrucciones que pongamos se ejecutarán una y otra vez sin ad infinitum.
void loop() {
  Serial.print("¡Hola mundo!\n");//Mostramos el mensaje "¡Hola mundo!"
  digitalWrite(LED_BUILTIN, HIGH);//Encendemos el led, HIGH es el voltaje en alta
  delay(1000);//Pausamos la ejecución durante 1 segundo
  digitalWrite(LED_BUILTIN, LOW);//Apagamos el led haciendo que el voltaje pase a baja
  delay(1000);//Pausamos la ejecución durante 1 segundo
}
