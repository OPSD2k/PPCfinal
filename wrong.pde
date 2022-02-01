SoundFile alarm;

class Wrong {
  float initX;
  float initY;
  Wrong(float x, float y) { 
    initX=x;
    initY=y;

    alarm = new SoundFile(security.this, "alert01.mp3");
  }

  void popUp() {
    float posChangeX;
    float posChangeY;

    posChangeX = random(-initX, initX);
    posChangeY = random(-initY, initY);



    fill(255);
    strokeWeight(10); 
    stroke(255, 0, 0);

    pushMatrix();
    translate(posChangeX, posChangeY);
    triangle(-100, 100, 100, 100, 0, -100);
    fill(0);
    text("ACCESS DENIED", -50, 150);
    popMatrix();
  }

  void alert() {
    
    if (!playing) {
      playing = true;
      alarm.loop();
    }
    
  }
  
  void securityLog() {
    int min = minute();  
    int h = hour();  
    int d = day();
    int mon = month(); 
    int y = year();   
    String attempt="login attempt on: "+ str(y) + "/" + str(mon)+ "/" + str(d)+ "/" +str(h)+ ":" +str(min);
    String[] list = split(attempt, " ");
    saveStrings("login4.txt", list);
  }
}
