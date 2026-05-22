import processing.serial.*;
import java.awt.event.KeyEvent;
import java.io.IOException;

Serial myPort;

// Variables
String angle = "";
String distance = "";
String data = "";

float pixsDistance;
int iAngle, iDistance;
int index1 = 0;

// Radar positioning
float radarX;
float radarY;

void setup()
{
  fullScreen(P2D);
  smooth(8);

  radarX = width / 2;
  radarY = height * 0.97;

  myPort = new Serial(this, "COM4", 115200);
  myPort.bufferUntil('\n');
}

void draw()
{
  //
  // Motion blur fade
  //

  noStroke();
  fill(0, 8);
  rect(0, 0, width, height);

  //
  // Radar
  //

  drawRadar();
  drawLine();
  drawObject();
}

void serialEvent(Serial myPort)
{
  data = myPort.readStringUntil('\n');

  if (data == null)
    return;

  data = trim(data);

  index1 = data.indexOf(",");

  if (index1 == -1)
    return;

  angle = data.substring(0, index1);
  distance = data.substring(index1 + 1);

  iAngle = int(angle);
  iDistance = int(distance);
}

void drawRadar()
{
  pushMatrix();

  translate(radarX, radarY);

  noFill();

  //
  // Dim radar grid
  //

  stroke(40, 120, 40);
  strokeWeight(1.5);

  //
  // Radar arcs
  //

  arc(0, 0, width * 0.94, width * 0.94, PI, TWO_PI);
  arc(0, 0, width * 0.73, width * 0.73, PI, TWO_PI);
  arc(0, 0, width * 0.52, width * 0.52, PI, TWO_PI);
  arc(0, 0, width * 0.31, width * 0.31, PI, TWO_PI);

  //
  // Angle lines
  //

  line(-width / 2, 0, width / 2, 0);

  line(0, 0,
       (-width / 2) * cos(radians(30)),
       (-width / 2) * sin(radians(30)));

  line(0, 0,
       (-width / 2) * cos(radians(60)),
       (-width / 2) * sin(radians(60)));

  line(0, 0,
       (-width / 2) * cos(radians(90)),
       (-width / 2) * sin(radians(90)));

  line(0, 0,
       (-width / 2) * cos(radians(120)),
       (-width / 2) * sin(radians(120)));

  line(0, 0,
       (-width / 2) * cos(radians(150)),
       (-width / 2) * sin(radians(150)));

  popMatrix();
}

void drawObject()
{
  pushMatrix();

  translate(radarX, radarY);

  //
  // Object line
  //

  stroke(255, 80, 80);
  strokeWeight(5);

  //
  // Distance conversion
  //

  pixsDistance = iDistance * ((height * 0.8) * 0.025);

  //
  // Draw detection beam
  //

  if (iDistance < 30)
  {
    line(
      pixsDistance * cos(radians(iAngle)),
      -pixsDistance * sin(radians(iAngle)),

      (height * 0.88) * cos(radians(iAngle)),
      -(height * 0.88) * sin(radians(iAngle))
    );
  }

  popMatrix();
}

void drawLine()
{
  pushMatrix();

  translate(radarX, radarY);

  //
  // Sweep line
  //

  stroke(30, 250, 60);
  strokeWeight(3);

  line(
    0,
    0,

    (height * 0.88) * cos(radians(iAngle)),
    -(height * 0.88) * sin(radians(iAngle))
  );

  popMatrix();
}
