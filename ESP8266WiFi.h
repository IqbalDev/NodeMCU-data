/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/
/*********
   Edited by     : Iqbal ID
   source code   : https://github.com/IqbalDev/esp8266
**********/
// Muat perpustakaan Wi-Fi
#include <ESP8266WiFi.h>

// Ganti dengan kredensial jaringan Anda
const char* ssid     = "iqbal id";
const char* password = "codinger";

// Atur nomor port server web ke 80
WiFiServer server(80);

// Variabel untuk menyimpan permintaan HTTP
String header;

// Variabel bantu untuk menyimpan status keluaran saat ini
String output16State = "off";
String output5State = "off";
String output4State = "off";
String output0State = "off";

// Tetapkan variabel output ke pin GPIO
const int output16 = 16;
const int output5 = 5;
const int output4 = 4;
const int output0 = 0;

// Waktu saat ini
unsigned long currentTime = millis();
// Waktu sebelumnya
unsigned long previousTime = 0; 
// Tetapkan batas waktu dalam milidetik (contoh: 2000 ms = 2d)
const long timeoutTime = 2000;

void setup() {
  Serial.begin(115200);
  // Inisialisasi variabel output sebagai output
  pinMode(output16, OUTPUT);
  pinMode(output5, OUTPUT);
  pinMode(output4, OUTPUT);
  pinMode(output0, OUTPUT);
  // Atur output ke RENDAH
  digitalWrite(output16, LOW);
  digitalWrite(output5, LOW);
  digitalWrite(output4, LOW);
  digitalWrite(output0, LOW);

  // Terhubung ke jaringan Wi-Fi dengan SSID dan kata sandi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print("");
    Serial.println(" [!] Lu lupa ngga nyalain Hostpotnya mungkin TOD..??");
    Serial.println(" [!] Atau SSID dan PASSWORD tidak sama dengan yang di setting...");
  }
  // Cetak alamat IP lokal dan mulai server web
  Serial.println("");  
  Serial.println("                 +===+                 ");
  Serial.println("                  +=+                  ");
  Serial.println("+=====================================+");
  Serial.println("[+] Alhamdulillah....");
  Serial.println("[+] WiFi Tersambung Broo... :)");
  Serial.println("[+] IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("+=====================================+");
  Serial.println("");
  server.begin();
}

void loop(){
  WiFiClient client = server.available();   // Dengarkan klien yang masuk
  
  if (client) {                             // Jika klien baru terhubung,
    Serial.println("New Client.");          // cetak pesan di port serial
    String currentLine = "";                // membuat String untuk menyimpan data yang masuk dari klien
    currentTime = millis();
    previousTime = currentTime;
    while (client.connected() && currentTime - previousTime <= timeoutTime) { // loop sementara klien terhubung
      currentTime = millis();         
      if (client.available()) {             // jika ada byte untuk dibaca dari klien,
        char c = client.read();             // baca byte, lalu
        Serial.write(c);                    // cetaklah monitor serialnya
        header += c;
        if (c == '\n') {                    // jika byte adalah karakter baris baru
          // jika baris saat ini kosong, Anda mendapat dua karakter baris baru berturut-turut.
          // itulah akhir dari permintaan HTTP klien, jadi kirim respons:
          if (currentLine.length() == 0) {
            // Header HTTP selalu diawali dengan kode respons (mis. HTTP / 1.1 200 OK)
            // dan tipe konten agar klien tahu apa yang akan terjadi, kemudian baris kosong:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // menyalakan dan mematikan GPIO
            if (header.indexOf("GET /16/on") >= 0) {
              Serial.println("GPIO 16 on");
              output16State = "on";
              digitalWrite(output16, HIGH);
            } else if (header.indexOf("GET /16/off") >= 0) {
              Serial.println("GPIO 16 off");
              output16State = "off";
              digitalWrite(output16, LOW);
            } else if (header.indexOf("GET /5/on") >= 0) {
              Serial.println("GPIO 5 on");
              output5State = "on";
              digitalWrite(output5, HIGH);
            } else if (header.indexOf("GET /5/off") >= 0) {
              Serial.println("GPIO 5 off");
              output5State = "off";
              digitalWrite(output5, LOW);
              ////////
             } else if (header.indexOf("GET /4/on") >= 0) {
              Serial.println("GPIO 4 on");
              output4State = "on";
              digitalWrite(output4, HIGH);
            } else if (header.indexOf("GET /4/off") >= 0) {
              Serial.println("GPIO 4 off");
              output4State = "off";
              digitalWrite(output4, LOW);
            } else if (header.indexOf("GET /0/on") >= 0) {
              Serial.println("GPIO 0 on");
              output0State = "on";
              digitalWrite(output0, HIGH);
            } else if (header.indexOf("GET /0/off") >= 0) {
              Serial.println("GPIO 0 off");
              output0State = "off";
              digitalWrite(output0, LOW);
            }
            
            // Tampilkan halaman web HTML
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS untuk menata tombol on / off
            // Jangan ragu untuk mengubah atribut warna latar dan ukuran font agar sesuai dengan preferensi Anda
            client.println("<style>html { background-color: #ffffff; background-position: 0 26px; background-repeat: no-repeat; background-size: cover; background-attachment: fixed; background-image: url('https://i.pinimg.com/originals/de/4d/91/de4d91d7e5aede2e414ee55f6c9cbd0b.jpg'); font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: rgba(0,0,0,0.7); border: none; font-weight: bold; color: lime; padding: 16px 30px; box-shadow: 0px 5px 10px 0px aqua; border-radius: 5px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: rgba(0,0,0,0.6); font-weight: bold; color: white;}");
            client.println(".footer {background-color: rgba(0,0,0,0.6); color: aqua; font-weight: bold; font-weight: bold; text-align: center; padding: 14px; }");
            client.println(".menu { background-color: #222; box-shadow: 0px 8px 16px 0px rgba(0,0,0,0.6); margin: -8px -8px; }");
            client.println(".menu ul { list-style-type: none; margin: 0; padding: 0; overflow: hidden; }");
            client.println(".menu > ul > li { float: left}");
            client.println(".menu li a { display: inline-block; color: aqua; text-align: center; font-weight: bold; padding: 20px; text-decoration: none; }");
            client.println(".menu li a:hover { bsckground-color: black; border-radius: 6px; font-weight: bold; color: white; }");
            client.println("li.dropdown { display: inline-block; }");
            client.println(".dropdown:hover .isi { display: block; }");
            client.println(".isi a:hover { color: green !important; }");
            client.println(".isi { position: absolute; display: none; box-shadow: 0px 8px 16px 0px rgba(0,0,0,0.6); z-index: 1; background-color: rgba(0,0,0,0.7); border-radius: 6px; }");
            client.println(".isi a { font-weight: bold; color: white; }");
            client.println(".isi a:hover { font-weight: bold; color: yellow !important; background: #222 !important; width: 160px; border-radius: 6px; }");
            client.println(".box { margin: auto; color: white; font-weight: bold; padding: 10px; font-size: 30px }");

            client.println(".iqbal { display: flex; } </style></head>");
                        

            // dropdown
            client.println("<div class='menu'> ");
            client.println("  <nav class='iqbal'>");
            client.println("  <ul> <li class='dropdown'> <a href='#'> Menu </a> ");
            client.println("    <ul class='isi'> ");
            client.println("      <li><a href='https://darkarticle.000webhostapp.com/' target='_blank'> Website Saya </a></li>");
            client.println("      <li><a href='https://wa.me/62895424726100?text=Hallo Iqbal' target='_blank'> Kontak Admin </a></li>");
            client.println("      <li><a href='https://www.github.com/IqbalDev' target='_blank'> Source Code  </a></li>");
            client.println("      <li><a href='https://www.codepolitan.com/cara-enjoy-memulai-belajar-pemrograman' target='_blank'> Belajar Coding </a></li>");
            client.println("    </ul>");
            client.println("  </li> </ul>");
            client.println("  <div class='box'><em>Iqbal Dev </em></div>");
            client.println("  </nav>");
            client.println("</div>");
            
            client.println("<body><h1>-----------</h1>");
//          client.println("Iqbal ID");
            // Tampilkan kondisi saat ini, dan tombol ON / OFF untuk GPIO 16 
            client.println("<p><b>.</b></p>");
            // Jika output16State mati, ini akan menampilkan tombol ON    
            if (output16State=="off") {
              client.println("<p><a href=\"/16/on\"><button class=\"button\">Listrik 1 ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/16/off\"><button class=\"button button2\">Listrik 1 OFF</button></a></p>");
            } 
               
           // Jika output5State mati, ini akan menampilkan tombol ON      
            if (output5State=="off") {
              client.println("<p><a href=\"/5/on\"><button class=\"button\">Listrik 2 ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/5/off\"><button class=\"button button2\">Listrik 2 OFF</button></a></p>");
            }
            /////////
        
            
            // Jika output4State mati, ini akan menampilkan tombol ON
            if (output4State=="off") {
              client.println("<p><a href=\"/4/on\"><button class=\"button\">Listrik 3 ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/4/off\"><button class=\"button button2\">Listrik 3 OFF</button></a></p>");
            } 
               
            
           // Jika output0State mati, ini akan menampilkan tombol ON     
            if (output0State=="off") {
              client.println("<p><a href=\"/0/on\"><button class=\"button\">Lampu LED ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/0/off\"><button class=\"button button2\">Lampu LED OFF</button></a></p>");
            }
              //client.println("<div class='footer'><p> https://www.github.com/IqbalDev </p></div>");
            client.println("</body></html>");
            
            // Respons HTTP berakhir dengan baris kosong lain
            client.println();
            // Keluar dari loop sementara
            break;
          } else { // jika Anda mendapat baris baru, maka bersihkan currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // jika Anda mendapatkan hal lain selain karakter carriage return,
          currentLine += c;      // tambahkan ke akhir currentLine
        }
      }
    }
    // Kosongkan variabel header
    header = "";
    // Tutup koneksi
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
