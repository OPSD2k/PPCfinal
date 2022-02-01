PImage checkmark;
SoundFile granted;
boolean playing=false;

class Access {
  float initX;
  float initY;

  Access(float x, float y) {
    initX=x;
    initY=y;

    checkmark = loadImage("checkmark.png");

    background(152, 190, 100);

    granted = new SoundFile(security.this, "granted.mp3");
  }

  void display() {
    pushMatrix();

    translate(initX/8, initY/8);
    image(checkmark, 0, 0);
    fill(0);
    text("ACCESS GRANTED", 200, 550);

    popMatrix();
  }
  void check() {

    if (!playing) {
      playing = true;
      granted.play();
    }
  }
}
