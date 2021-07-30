import processing.serial.*;
import java.awt.event.KeyEvent;
import java.io.IOException;
import java.net.*;
import java.io.*;
import java.util.Arrays;

DatagramSocket socket;
DatagramPacket packet;

byte[] buf = new byte[12]; //Set your buffer size as desired
 
String angle="";
String distance="";
String data="";
String noObject;
float pixsDistance;
int iAngle, iDistance;
int index1=0;
int index2=0;
PFont orcFont;
 
 int rectX, rectY;
 int rectSize = 90;
 color rectColor;
 
 
 
 
void setup() {
 
  size (1366, 950);
  smooth();
    try {
    socket = new DatagramSocket(5050); // Set your port here
  }
  catch (Exception e) {
    e.printStackTrace(); 
    println(e.getMessage());
  }
  thread("udpCall");
  rectColor = color(0);
  rectX = width/2-rectSize-10;
  rectY = height/2-rectSize/2;
}
 
void draw() {
  
  thread("udpCall");
  fill(98, 245, 31);
 
  noStroke();
  fill(0, 4);
  rect(0, 0, width, 1010); 
 
  fill(98, 245, 31); // yeþil renk
 
  drawRadar(); 
  drawLine();
  drawObject();
  drawText();
  
}
 
void udpCall () { 
   try {
     
    DatagramPacket packet = new DatagramPacket(buf, buf.length);
    socket.receive(packet);
    InetAddress address = packet.getAddress();
    int port = packet.getPort();
    packet = new DatagramPacket(buf, buf.length, address, port);
    
    //Received as bytes:
    println(Arrays.toString(buf));
    
    //If you wish to receive as String:
    String received = new String(packet.getData(), 0, packet.getLength());
    println(received);
    data = received;
  }
  catch (IOException e) {
    e.printStackTrace(); 
    println(e.getMessage());
  }
  
  
  data = data.substring(0, data.length()-1);
 
  index1 = data.indexOf(",");
  angle= data.substring(0, index1);
  distance= data.substring(index1+1, data.length()); 
 
  iAngle = int(angle);
  iDistance = int(distance);
  println("A: "+iAngle+" D: "+iDistance);
}
 
void drawRadar() {
  pushMatrix();
  translate(683, 700);
  noFill();
  strokeWeight(2);
  stroke(98, 245, 31);
  // draws the arc lines
  arc(0, 0, 1300, 1300, PI, TWO_PI);
  arc(0, 0, 1000, 1000, PI, TWO_PI);
  arc(0, 0, 700, 700, PI, TWO_PI);
  arc(0, 0, 400, 400, PI, TWO_PI);
  // draws the angle lines
  line(-700, 0, 700, 0);
  line(0, 0, -700*cos(radians(30)), -700*sin(radians(30)));
  line(0, 0, -700*cos(radians(60)), -700*sin(radians(60)));
  line(0, 0, -700*cos(radians(90)), -700*sin(radians(90)));
  line(0, 0, -700*cos(radians(120)), -700*sin(radians(120)));
  line(0, 0, -700*cos(radians(150)), -700*sin(radians(150)));
  line(-700*cos(radians(30)), 0, 700, 0);
  popMatrix();
}
 
void drawObject() {
  pushMatrix();
  translate(683, 700);
  strokeWeight(9);
  stroke(255, 10, 10); // kýrmýzý renk
  pixsDistance = iDistance*22.5; 
  // 40 cm ye kadar ölçer
  if (iDistance<40) {
 
    line(pixsDistance*cos(radians(iAngle)), -pixsDistance*sin(radians(iAngle)), 700*cos(radians(iAngle)), -700*sin(radians(iAngle)));
  }
  popMatrix();
}
 
void drawLine() {
  pushMatrix();
  strokeWeight(9);
  stroke(30, 250, 60);
  translate(683, 700);
  line(0, 0, 700*cos(radians(iAngle)), -700*sin(radians(iAngle)));
  popMatrix();
}
 
void drawText() { 
 
  pushMatrix();
  if (iDistance>40) {
    noObject = "Out of Range";
  } else {
    noObject = "In Range";
  }
  fill(0, 0, 0);
  noStroke();
  rect(0, 1010, width, 1080);
  fill(98, 245, 31);
  textSize(25);
  text("10cm", 800, 690);
  text("20cm", 950, 690);
  text("30cm", 1100, 690);
  text("40cm", 1250, 690);
  textSize(40);
  text("Object: " + noObject, 240, 1050);
  text("Angle: " + iAngle +" °", 1050, 1050);
  text("Distance: ", 1380, 1050);
  if (iDistance<40) {
    text("        " + iDistance +" cm", 1400, 1050);
  }
  textSize(25);
  fill(98, 245, 60);
  translate(390+960*cos(radians(30)), 780-960*sin(radians(30)));
  rotate(-radians(-60));
  text("30°", 0, 0);
  resetMatrix();
  translate(490+960*cos(radians(60)), 920-960*sin(radians(60)));
  rotate(-radians(-30));
  text("60°", 0, 0);
  resetMatrix();
  translate(630+960*cos(radians(90)), 990-960*sin(radians(90)));
  rotate(radians(0));
  text("90°", 0, 0);
  resetMatrix();
  translate(760+960*cos(radians(120)), 1000-960*sin(radians(120)));
  rotate(radians(-38));
  text("120°", 0, 0);
  resetMatrix();
  translate(840+900*cos(radians(150)), 920-960*sin(radians(150)));
  rotate(radians(-60));
  text("150°", 0, 0);
  popMatrix();
}
