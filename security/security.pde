Wrong crazy;
Access bonkers;
//PImage checkmark;
void setup() {
  size(700, 700);
  crazy= new Wrong (width, height);
  bonkers = new Access (width,height);
}

void draw() {
    crazy.popUp();
    bonkers.display();
}

void mouseClicked() {
  crazy.securityLog();
}
