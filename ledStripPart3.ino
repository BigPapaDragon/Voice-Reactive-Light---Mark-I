#define SENSOR_PIN 6
#define RED_PIN 3
#define GREEN_PIN 5
#define BLUE_PIN 9

#define NUM_LEDS 204

#define DELAY 1

int currentLevel = 0;

int mode = 0;

void setColor(int r, int g, int b){
  analogWrite(RED_PIN,r);
  analogWrite(GREEN_PIN,g);
  analogWrite(BLUE_PIN,b);
}

void spinThatShit(){
  int level = digitalRead(SENSOR_PIN);

  if(level == 1){
    if(currentLevel - 1>= 0){
      currentLevel = currentLevel - 1;
    } else if(currentLevel - 1< 0){
      currentLevel = currentLevel;
    }
  } else if(level == 0){
    
    if(currentLevel + 1 <= NUM_LEDS){
      currentLevel = currentLevel + 1;
    } else if(currentLevel + 1 > NUM_LEDS){
      currentLevel = currentLevel;
    }
  }

   switch(currentLevel) {

    case 204:
     setColor(0,0,255);
      break;
    case 203:
    setColor(0,5,255);
      break;
    case 202:
    setColor(0,10,255);
      break;
    case 201:
    setColor(0,15,255);
      break;
    case 200:
    setColor(0,20,255);
      break;
    case 199:
    setColor(0,25,255);
      break;
    case 198:
    setColor(0,30,255);
      break;
    case 197:
    setColor(0,35,255);
      break;
    case 196:
    setColor(0,40,255);
      break;
    case 195:
    setColor(0,45,255);
      break;
    case 194:
    setColor(0,50,255);
      break;
    case 193:
    setColor(0,55,255);
      break;
    case 192:
    setColor(0,60,255);
      break;
    case 191:
    setColor(0,65,255);
      break;
    case 190:
    setColor(0,70,255);
      break;
    case 189:
    setColor(0,75,255);
      break;
    case 188:
    setColor(0,80,255);
      break;
    case 187:
    setColor(0,85,255);
      break;
    case 186:
    setColor(0,90,255);
      break;
    case 185:
    setColor(0,95,255);
      break;
    case 184:
    setColor(0,100,255);
      break;
    case 183:
    setColor(0,105,255);
      break;
    case 182:
    setColor(0,110,255);
      break;
    case 181:
    setColor(0,115,255);
      break;
    case 180:
    setColor(0,120,255);
      break;
    case 179:
    setColor(0,125,255);
      break;
    case 178:
    setColor(0,130,255);
      break;
    case 177:
    setColor(0,135,255);
      break;
    case 176:
    setColor(0,140,255);
      break;
    case 175:
    setColor(0,145,255);
      break;
    case 174:
    setColor(0,150,255);
      break;
    case 173:
    setColor(0,155,255);
      break;
    case 172:
    setColor(0,160,255);
      break;
    case 171:
    setColor(0,165,255);;
      break;
    case 170:
    setColor(0,170,255);
      break;
    case 169:
    setColor(0,175,255);
      break;
    case 168:
    setColor(0,180,255);
      break;
    case 167:
    setColor(0,185,255);
      break;
    case 166:
    setColor(0,190,255);
      break;
    case 165:
    setColor(0,195,255);
      break;
    case 164:
    setColor(0,200,255);
      break;
    case 163:
    setColor(0,205,255);
      break;
    case 162:
    setColor(0,210,255);
      break;
    case 161:
    setColor(0,215,255);
      break;
    case 160:
    setColor(0,220,255);
      break;
    case 159:
    setColor(0,225,255);
      break;
    case 158:
    setColor(0,230,255);
      break;
    case 157:
    setColor(0,235,255);
      break;
    case 156:
    setColor(0,240,255);
      break;
    case 155:
    setColor(0,245,255);
      break;
    case 154:
    setColor(0,250,255);
      break;
    case 153:
    setColor(0,255,255);
      break;
    case 152:
    setColor(0,255,250);
      break;
    case 151:
    setColor(0,255,245);
      break;
    case 150:
    setColor(0,255,240);
      break;
    case 149:
    setColor(0,255,235);
      break;
    case 148:
    setColor(0,255,230);
      break;
    case 147:
    setColor(0,255,225);
      break;
    case 146:
    setColor(0,255,220);
      break;
    case 145:
    setColor(0,255,215);
      break;
    case 144:
    setColor(0,255,210);
      break;
    case 143:
    setColor(0,255,205);
      break;
    case 142:
    setColor(0,255,200);
      break;
    case 141:
    setColor(0,255,195);
      break;
    case 140:
    setColor(0,255,190);
      break;
    case 139:
    setColor(0,255,185);
      break;
    case 138:
    setColor(0,255,180);
      break;
    case 137:
    setColor(0,255,175);
      break;
    case 136:
    setColor(0,255,170);
      break;
    case 135:
    setColor(0,255,165);
      break;
    case 134:
    setColor(0,255,160);
      break;
    case 133:
    setColor(0,255,155);
      break;
    case 132:
    setColor(0,255,150);
      break;
    case 131:
    setColor(0,255,145);
      break;
    case 130:
    setColor(0,255,140);
      break;
    case 129:
    setColor(0,255,135);
      break;
    case 128:
    setColor(0,255,130);
      break;
    case 127:
    setColor(0,255,125);
      break;
    case 126:
    setColor(0,255,120);
      break;
    case 125:
    setColor(0,255,115);
      break;
    case 124:
    setColor(0,255,110);
      break;
    case 123:
    setColor(0,255,105);
      break;
    case 122:
    setColor(0,255,100);
      break;
    case 121:
    setColor(0,255,95);
      break;
    case 120:
    setColor(0,255,90);
      break;
    case 119:
    setColor(0,255,85);
      break;
    case 118:
    setColor(0,255,80);
      break;
    case 117:
    setColor(0,255,75);
      break;
    case 116:
    setColor(0,255,70);
      break;
    case 115:
    setColor(0,255,65);
      break;
    case 114:
    setColor(0,255,60);
      break;
    case 113:
    setColor(0,255,55);
      break;
    case 112:
    setColor(0,255,50);
      break;
    case 111:
    setColor(0,255,45);
      break;
    case 110:
    setColor(0,255,40);
      break;
    case 109:
    setColor(0,255,35);
      break;
    case 108:
    setColor(0,255,30);
      break;
    case 107:
    setColor(0,255,25);
      break;
    case 106:
    setColor(0,255,20);
      break;
    case 105:
    setColor(0,255,15);
      break;
    case 104:
    setColor(0,255,10);
      break;
    case 103:
    setColor(0,255,5);
      break;
    case 102:
    setColor(0,255,0);
      break;
    case 101:
    setColor(5,255,0);
      break;
    case 100:
    setColor(10,255,0);
      break;
    case 99:
    setColor(15,255,0);
      break;
    case 98:
    setColor(20,255,0);
      break;
    case 97:
    setColor(25,255,0);
      break;
    case 96:
    setColor(30,255,0);
      break;
    case 95:
    setColor(35,255,0);
      break;
    case 94:
    setColor(40,255,0);
      break;
    case 93:
    setColor(45,255,0);
      break;
    case 92:
    setColor(50,255,0);
      break;
    case 91:
    setColor(55,255,0);
      break;
    case 90:
    setColor(60,255,0);
      break;
    case 89:
    setColor(65,255,0);
      break;
    case 88:
    setColor(70,255,0);
      break;
    case 87:
    setColor(75,255,0);
      break;
    case 86:
    setColor(80,255,0);
      break;
    case 85:
    setColor(85,255,0);
      break;
    case 84:
    setColor(90,255,0);
      break;
    case 83:
    setColor(95,255,0);
      break;
    case 82:
    setColor(100,255,0);
      break;
    case 81:
    setColor(105,255,0);
      break;
    case 80:
    setColor(110,255,0);
      break;
    case 79:
    setColor(115,255,0);
      break;
    case 78:
    setColor(120,255,0);
      break;
    case 77:
    setColor(125,255,0);
      break;
    case 76:
    setColor(130,255,0);
      break;
    case 75:
    setColor(135,255,0);
      break;
    case 74:
    setColor(140,255,0);
      break;
    case 73:
    setColor(145,255,0);
      break;
    case 72:
    setColor(150,255,0);
      break;
    case 71:
    setColor(155,255,0);
      break;
    case 70:
    setColor(160,255,0);
      break;
    case 69:
    setColor(165,255,0);
      break;
    case 68:
    setColor(170,255,0);
      break;
    case 67:
    setColor(175,255,0);
      break;
    case 66:
    setColor(180,255,0);
      break;
    case 65:
    setColor(185,255,0);
      break;
    case 64:
    setColor(190,255,0);
      break;
    case 63:
    setColor(195,255,0);
      break;
    case 62:
    setColor(200,255,0);
      break;
    case 61:
    setColor(205,255,0);
      break;
    case 60:
    setColor(210,255,0);
      break;
    case 59:
    setColor(215,255,0);
      break;
    case 58:
    setColor(220,255,0);
      break;
    case 57:
    setColor(225,255,0);
      break;
    case 56:
    setColor(230,255,0);
      break;
    case 55:
    setColor(235,255,0);
      break;
    case 54:
    setColor(240,255,0);
      break;
    case 53:
    setColor(245,255,0);
      break;
    case 52:
    setColor(250,255,0);
      break;
    case 51:
    setColor(255,255,0);
      break;
    case 50:
    setColor(255,250,0);
      break;
    case 49:
    setColor(255,245,0);
      break;
    case 48:
    setColor(255,240,0);
      break;
    case 47:
    setColor(255,235,0);
      break;
    case 46:
    setColor(255,230,0);
      break;
    case 45:
    setColor(255,225,0);
      break;
    case 44:
    setColor(255,220,0);
      break;
    case 43:
    setColor(255,215,0);
      break;
    case 42:
    setColor(255,210,0);
      break;
    case 41:
    setColor(255,205,0);
      break;
    case 40:
    setColor(255,200,0);
      break;
    case 39:
    setColor(255,195,0);
      break;
    case 38:
    setColor(255,190,0);
      break;
    case 37:
    setColor(255,185,0);
      break;
    case 36:
    setColor(255,180,0);
      break;
    case 35:
    setColor(255,175,0);
      break;
    case 34:
    setColor(255,170,0);
      break;
    case 33:
    setColor(255,165,0);
      break;
    case 32:
    setColor(255,160,0);
      break;
    case 31:
    setColor(255,155,0);
      break;
    case 30:
    setColor(255,150,0);
      break;
    case 29:
    setColor(255,145,0);
      break;
    case 28:
    setColor(255,140,0);
      break;
    case 27:
    setColor(255,135,0);
      break;
    case 26:
    setColor(255,130,0);
      break;
    case 25:
    setColor(255,125,0);
      break;
    case 24:
    setColor(255,120,0);
      break;
    case 23:
    setColor(255,115,0);
      break;
    case 22:
    setColor(255,110,0);
      break;
    case 21:
    setColor(255,105,0);
      break;
    case 20:
    setColor(255,100,0);
      break;
    case 19:
    setColor(255,95,0);
      break;
    case 18:
    setColor(255,90,0);
      break;
    case 17:
    setColor(255,85,0);
      break;
    case 16:
    setColor(255,80,0);
      break;
    case 15:
    setColor(255,75,0);
      break;
    case 14:
    setColor(255,70,0);
      break;
    case 13:
    setColor(255,65,0);
      break;
    case 12:
    setColor(255,60,0);
      break;
    case 11:
    setColor(255,55,0);
      break;
    case 10:
    setColor(255,45,0);
      break;
    case 9:
    setColor(255,40,0);
      break;
    case 8:
    setColor(255,35,0);
      break;
    case 7:
    setColor(255,30,0);
      break;
    case 6:
    setColor(255,25,0);
      break;
    case 5:
    setColor(255,20,0);
      break;
    case 4:
    setColor(255,15,0);
      break;
    case 3:
    setColor(255,10,0);
      break;
    case 2:
    setColor(255,5,0);
      break;
    case 1:
    setColor(255,0,0);
      break;
   }
}

void setup() {
  Serial.begin(9600);
  pinMode(SENSOR_PIN,INPUT);
  pinMode(RED_PIN,OUTPUT);
  pinMode(GREEN_PIN,OUTPUT);
  pinMode(BLUE_PIN,OUTPUT);
  setColor(255,0,0);
}

void loop() {

  switch(mode) {

    case 0:

      spinThatShit();

      break;

    default:

      break;

  }

    delay(DELAY); // delay in between reads for stability
}
