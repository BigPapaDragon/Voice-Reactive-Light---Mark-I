//The number of levels 
#define NUM_LEDS 204

//The pin that controls the LEDs
#define RED_PIN 3
#define GREEN_PIN 5
#define BLUE_PIN 9

//The pin that we read sensor values form
#define ANALOG_INPUT A0

//Sound Sensor Min value, and Max value
#define SOUND_SENSOR_LOW 400.0
#define SOUND_SENSOR_HIGH 600.0

//Number of previous sensor values to save for calculating the average
#define AVG_LEN 15

//Number of previous sensor values to decides if we are on a peak in a song
#define LONG_AVG_LEN 20

//Mneumonics
#define HIGH 3
#define NORMAL 2

//How long do we keep the "current average" sound, before restarting the measuring
//Time keeping averages
#define MSECS 30 * 1000
#define CYCLES MSECS / DELAY

//Max allowed deviation in sensor value
#define DEV_THRESHOLD 0.8

//Arduino loop delay for syncing and fluidic variantions of light
#define DELAY 1

//Function signatures
float scalingFunction( float originalMin, float originalMax, float newBegin, float newEnd, float inputValue, float curve);
void insert(int val, int *avgs, int len);
int compute_average(int *avgs, int len);
void visualize_music();
void mood_light();
void setColor(int red, int green, int blue);

//Current level variable
int currentLevel = NUM_LEDS;

//Working mode selection variable
int mode = 0;

//Song mode selector variable
int songmode = NORMAL;

//Average sound measurement the last CYCLES
unsigned long songAverage;

//The amount of iterations since the songAverage was reset
int iter = 0;

//The speed the LEDs fade to black 
float fade_scale = 1.2;

//Array to store to past values for average value calculation
int avgs[AVG_LEN] = {-1};

//Longer Array to decide song mode
int long_avg[LONG_AVG_LEN] = {-1};

/*//Keeping track how often, and how long times we hit a certain mode
struct time_keeping {
  unsigned long times_start;
  short times;
};

//How much to increment or decrement each color every cycle
struct color {
  int r;
  int g;
  int b;
};

//The colour that will be set to the RGB LED strip
struct Leds{
  int r;
  int g;
  int b;
};

struct time_keeping high;
struct color Color; 
struct Leds leds;*/

void setup() {
  Serial.begin(9600);
  delay(1000);  
  
  //bootstrap average with some low values
  for (int i = 0; i < AVG_LEN; i++) {  
    insert(500, avgs, AVG_LEN);
  }

 /* //Initial values
  high.times = 0;
  high.times_start = millis();
  Color.r = 2; 
  Color.g = 2;
  Color.b = 2;
  leds.r = 20;
  leds.g = 20;  
  leds.b = 20;  
  setColor(leds.r,leds.g,leds.b);*/
}

void loop() {
  switch(mode) {
    case 0:
      visualize_music();
      break;

    case 1:
      mood_light();
    
    default:
      break;
  }
  delay(DELAY);
}



/**Funtion to check if the lamp should either enter a HIGH mode,

or revert to NORMAL if already in HIGH. If the sensors report values

that are higher than 1.1 times the average values, and this has happened

more than 30 times the last few milliseconds, it will enter HIGH mode. 

TODO: Not very well written, remove hardcoded values, and make it more

reusable and configurable. */

/*void check_high(int avg) {
  if (avg > (songAverage/iter * 1.1)) {
    if (high.times != 0) {
      if (millis() - high.times_start > 200.0) {
        high.times = 0;
        songmode = NORMAL;
      } else {
        high.times_start = millis();  
        high.times++; 
      }
    } else {
      high.times++;
      high.times_start = millis();
    }
  }
  if (high.times > 30 && millis() - high.times_start < 50.0){
    songmode = HIGH;
  }
  else if (millis() - high.times_start > 200) {
    high.times = 0;
    songmode = NORMAL;
  }

}*/


//Main function for visualizing the sounds in the lamp
void visualize_music() {
  int sensor_value, check, avg, longavg;

  //Actual sensor value
  sensor_value = analogRead(ANALOG_INPUT);

  //If 0, discard immediately. Probably not right and save CPU.
  if (sensor_value == 0){
  return;
  }

  //Discard readings that deviates too much from the past avg.
  check = (float)scalingFunction(SOUND_SENSOR_LOW, SOUND_SENSOR_HIGH, SOUND_SENSOR_LOW, (float)SOUND_SENSOR_HIGH, (float)sensor_value, 2.0);

  avg = compute_average(avgs, AVG_LEN);

  if (((avg-check)>avg*DEV_THRESHOLD)){
    return;
  }

  //Insert new average value to the average array
  insert(check, avgs, AVG_LEN); 
  insert(avg, long_avg, LONG_AVG_LEN); 
  
  //Compute the "song average" sensor value
  songAverage += avg;
  iter++;

  if(iter>CYCLES){  
    songAverage = songAverage / iter;
    iter = 1;
  }

  longavg = compute_average(long_avg, LONG_AVG_LEN);

  //Check if we enter HIGH mode 
//  check_high(longavg);  


  /*if (songmode == HIGH) {
    fade_scale = 3;
    Color.r = 5;
    Color.g = 3;
    Color.b = -1;
  }
  else if (songmode == NORMAL) {
    fade_scale = 2;
    Color.r = -1;
    Color.b = 2;
    Color.g = 1;
  }*/

  //Decide the colour to be displayed based on currentLevel
  currentLevel = scalingFunction(SOUND_SENSOR_LOW, SOUND_SENSOR_HIGH, 0.0, (float)NUM_LEDS, (float)avg, -1);

  
  Serial.println(currentLevel);
  Serial.println(analogRead(ANALOG_INPUT));
  
  switch(currentLevel){


  
    /*case 66:
     setColor(0,0,20);
      break;
    case 65:
     setColor(0,0,40);
      break;
    case 64:
     setColor(0,0,60);
      break;
    case 63:
     setColor(0,0,80);
      break;
    case 62:
     setColor(0,0,100);
      break;
    case 61:
     setColor(0,0,120);
      break;
    case 60:
     setColor(0,0,140);
      break;
    case 59:
     setColor(0,0,160);
      break;
    case 58:
     setColor(0,0,180);
      break;
    case 57:
     setColor(0,0,200);
      break;
    case 56:
     setColor(0,0,220);
      break;
    case 55:
     setColor(0,0,240);
      break;
    case 54:
     setColor(0,0,255);
      break;
    case 53:
     setColor(0,20,255);
      break;
    case 52:
     setColor(0,40,255);
      break;
    case 51:
     setColor(0,60,255);
      break;
    case 50:
     setColor(0,80,255);
      break;
    case 49:
     setColor(0,100,255);
      break;
    case 48:
     setColor(0,120,255);
      break;
    case 47:
     setColor(0,140,255);
      break;
    case 46:
     setColor(0,160,255);
      break;
    case 45:
     setColor(0,180,255);
      break;
    case 44:
     setColor(0,200,255);
      break;
    case 43:
     setColor(0,220,255);
      break;
    case 42:
     setColor(0,240,255);
      break;
    case 41:
     setColor(0,255,255);
      break;
    case 40:
     setColor(0,255,240);
      break;
    case 39:
     setColor(0,255,220);
      break;
    case 38:
     setColor(0,255,200);
      break;
    case 37:
     setColor(0,255,200);
      break;
    case 36:
     setColor(0,255,180);
      break;
    case 35:
     setColor(0,255,160);
      break;
    case 34:
     setColor(0,255,140);
      break;
    case 33:
     setColor(0,255,120);
      break;
    case 32:
     setColor(0,255,100);
      break;
    case 31:
     setColor(0,255,80);
      break;
    case 30:
     setColor(0,255,60);
      break;
    case 29:
     setColor(0,255,40);
      break;
    case 28:
     setColor(0,255,20);
      break;
    case 27:
     setColor(0,255,0);
      break;
    case 26:
     setColor(20,255,0);
      break;
    case 25:
     setColor(40,255,0);
      break;
    case 24:
     setColor(60,255,0);
      break;
    case 23:
     setColor(80,255,0);
      break;
    case 22:
     setColor(100,255,0);
      break;
    case 21:
     setColor(120,255,0);
      break;
    case 20:
     setColor(140,255,0);
      break;
    case 19:
     setColor(160,255,0);
      break;
    case 18:
     setColor(180,255,0);
      break;
    case 17:
     setColor(200,255,0);
      break;
    case 16:
     setColor(220,255,0);
      break;
    case 15:
     setColor(240,255,0);
      break;
    case 14:
     setColor(255,255,0);
      break;
    case 13:
     setColor(255,240,0);
      break;
    case 12:
     setColor(255,220,0);
      break;
    case 11:
     setColor(255,200,0);
      break;
    case 10:
     setColor(255,180,0);
      break;
    case 9:
     setColor(255,160,0);
      break;
    case 8:
     setColor(255,140,0);
      break;
    case 7:
     setColor(255,120,0);
      break;
    case 6:
     setColor(255,100,0);
      break;
    case 5:
     setColor(255,80,0);
      break;
    case 4:
     setColor(255,60,0);
      break;
    case 3:
     setColor(255,40,0);
      break;
    case 2:
     setColor(255,20,0);
      break;
    case 1:
     setColor(255,0,0);
      break;*/

    case 1:
    setColor(0,0,255);
      break;
    case 2:
    setColor(0,5,255);
      break;
    case 3:
    setColor(0,10,255);
      break;
    case 4:
    setColor(0,15,255);
      break;
    case 5:
    setColor(0,20,255);
      break;
    case 6:
    setColor(0,25,255);
      break;
    case 7:
    setColor(0,30,255);
      break;
    case 8:
    setColor(0,35,255);
      break;
    case 9:
    setColor(0,40,255);
      break;
    case 10:
    setColor(0,45,255);
      break;
    case 11:
    setColor(0,50,255);
      break;
    case 12:
    setColor(0,55,255);
      break;
    case 13:
    setColor(0,60,255);
      break;
    case 14:
    setColor(0,65,255);
      break;
    case 15:
    setColor(0,70,255);
      break;
    case 16:
    setColor(0,75,255);
      break;
    case 17:
    setColor(0,80,255);
      break;
    case 18:
    setColor(0,85,255);
      break;
    case 19:
    setColor(0,90,255);
      break;
    case 20:
    setColor(0,95,255);
      break;
    case 21:
    setColor(0,100,255);
      break;
    case 22:
    setColor(0,105,255);
      break;
    case 23:
    setColor(0,110,255);
      break;
    case 24:
    setColor(0,115,255);
      break;
    case 25:
    setColor(0,120,255);
      break;
    case 26:
    setColor(0,125,255);
      break;
    case 27:
    setColor(0,130,255);
      break;
    case 28:
    setColor(0,135,255);
      break;
    case 29:
    setColor(0,140,255);
      break;
    case 30:
    setColor(0,145,255);
      break;
    case 31:
    setColor(0,150,255);
      break;
    case 32:
    setColor(0,155,255);
      break;
    case 33:
    setColor(0,160,255);
      break;
    case 34:
    setColor(0,165,255);;
      break;
    case 35:
    setColor(0,170,255);
      break;
    case 36:
    setColor(0,175,255);
      break;
    case 37:
    setColor(0,180,255);
      break;
    case 38:
    setColor(0,185,255);
      break;
    case 39:
    setColor(0,190,255);
      break;
    case 40:
    setColor(0,195,255);
      break;
    case 41:
    setColor(0,200,255);
      break;
    case 42:
    setColor(0,205,255);
      break;
    case 43:
    setColor(0,210,255);
      break;
    case 44:
    setColor(0,215,255);
      break;
    case 45:
    setColor(0,220,255);
      break;
    case 46:
    setColor(0,225,255);
      break;
    case 47:
    setColor(0,230,255);
      break;
    case 48:
    setColor(0,235,255);
      break;
    case 49:
    setColor(0,240,255);
      break;
    case 50:
    setColor(0,245,255);
      break;
    case 51:
    setColor(0,250,255);
      break;
    case 52:
    setColor(0,255,255);
      break;
    case 53:
    setColor(0,255,250);
      break;
    case 54:
    setColor(0,255,245);
      break;
    case 55:
    setColor(0,255,240);
      break;
    case 56:
    setColor(0,255,235);
      break;
    case 57:
    setColor(0,255,230);
      break;
    case 58:
    setColor(0,255,225);
      break;
    case 59:
    setColor(0,255,220);
      break;
    case 60:
    setColor(0,255,215);
      break;
    case 61:
    setColor(0,255,210);
      break;
    case 62:
    setColor(0,255,205);
      break;
    case 63:
    setColor(0,255,200);
      break;
    case 64:
    setColor(0,255,195);
      break;
    case 65:
    setColor(0,255,190);
      break;
    case 66:
    setColor(0,255,185);
      break;
    case 67:
    setColor(0,255,180);
      break;
    case 68:
    setColor(0,255,175);
      break;
    case 69:
    setColor(0,255,170);
      break;
    case 70:
    setColor(0,255,165);
      break;
    case 71:
    setColor(0,255,160);
      break;
    case 72:
    setColor(0,255,155);
      break;
    case 73:
    setColor(0,255,150);
      break;
    case 74:
    setColor(0,255,145);
      break;
    case 75:
    setColor(0,255,140);
      break;
    case 76:
    setColor(0,255,135);
      break;
    case 77:
    setColor(0,255,130);
      break;
    case 78:
    setColor(0,255,125);
      break;
    case 79:
    setColor(0,255,120);
      break;
    case 80:
    setColor(0,255,115);
      break;
    case 81:
    setColor(0,255,110);
      break;
    case 82:
    setColor(0,255,105);
      break;
    case 83:
    setColor(0,255,100);
      break;
    case 84:
    setColor(0,255,95);
      break;
    case 85:
    setColor(0,255,90);
      break;
    case 86:
    setColor(0,255,85);
      break;
    case 87:
    setColor(0,255,80);
      break;
    case 88:
    setColor(0,255,75);
      break;
    case 89:
    setColor(0,255,70);
      break;
    case 90:
    setColor(0,255,65);
      break;
    case 91:
    setColor(0,255,60);
      break;
    case 92:
    setColor(0,255,55);
      break;
    case 93:
    setColor(0,255,50);
      break;
    case 94:
    setColor(0,255,45);
      break;
    case 95:
    setColor(0,255,40);
      break;
    case 96:
    setColor(0,255,35);
      break;
    case 97:
    setColor(0,255,30);
      break;
    case 98:
    setColor(0,255,25);
      break;
    case 99:
    setColor(0,255,20);
      break;
    case 100:
    setColor(0,255,15);
      break;
    case 101:
    setColor(0,255,10);
      break;
    case 102:
    setColor(0,255,5);
      break;
    case 103:
    setColor(0,255,0);
      break;
    case 104:
    setColor(5,255,0);
      break;
    case 105:
    setColor(10,255,0);
      break;
    case 106:
    setColor(15,255,0);
      break;
    case 107:
    setColor(20,255,0);
      break;
    case 108:
    setColor(25,255,0);
      break;
    case 109:
    setColor(30,255,0);
      break;
    case 110:
    setColor(35,255,0);
      break;
    case 111:
    setColor(40,255,0);
      break;
    case 112:
    setColor(45,255,0);
      break;
    case 113:
    setColor(50,255,0);
      break;
    case 114:
    setColor(55,255,0);
      break;
    case 115:
    setColor(60,255,0);
      break;
    case 116:
    setColor(65,255,0);
      break;
    case 117:
    setColor(70,255,0);
      break;
    case 118:
    setColor(75,255,0);
      break;
    case 119:
    setColor(80,255,0);
      break;
    case 120:
    setColor(85,255,0);
      break;
    case 121:
    setColor(90,255,0);
      break;
    case 122:
    setColor(95,255,0);
      break;
    case 123:
    setColor(100,255,0);
      break;
    case 124:
    setColor(105,255,0);
      break;
    case 125:
    setColor(110,255,0);
      break;
    case 126:
    setColor(115,255,0);
      break;
    case 127:
    setColor(120,255,0);
      break;
    case 128:
    setColor(125,255,0);
      break;
    case 129:
    setColor(130,255,0);
      break;
    case 130:
    setColor(135,255,0);
      break;
    case 131:
    setColor(140,255,0);
      break;
    case 132:
    setColor(145,255,0);
      break;
    case 133:
    setColor(150,255,0);
      break;
    case 134:
    setColor(155,255,0);
      break;
    case 135:
    setColor(160,255,0);
      break;
    case 136:
    setColor(165,255,0);
      break;
    case 137:
    setColor(170,255,0);
      break;
    case 138:
    setColor(175,255,0);
      break;
    case 139:
    setColor(180,255,0);
      break;
    case 140:
    setColor(185,255,0);
      break;
    case 141:
    setColor(190,255,0);
      break;
    case 142:
    setColor(195,255,0);
      break;
    case 143:
    setColor(200,255,0);
      break;
    case 144:
    setColor(205,255,0);
      break;
    case 145:
    setColor(210,255,0);
      break;
    case 146:
    setColor(215,255,0);
      break;
    case 147:
    setColor(220,255,0);
      break;
    case 148:
    setColor(225,255,0);
      break;
    case 149:
    setColor(230,255,0);
      break;
    case 150:
    setColor(235,255,0);
      break;
    case 151:
    setColor(240,255,0);
      break;
    case 152:
    setColor(245,255,0);
      break;
    case 153:
    setColor(250,255,0);
      break;
    case 154:
    setColor(255,255,0);
      break;
    case 155:
    setColor(255,250,0);
      break;
    case 156:
    setColor(255,245,0);
      break;
    case 157:
    setColor(255,240,0);
      break;
    case 158:
    setColor(255,235,0);
      break;
    case 159:
    setColor(255,230,0);
      break;
    case 160:
    setColor(255,225,0);
      break;
    case 161:
    setColor(255,220,0);
      break;
    case 162:
    setColor(255,215,0);
      break;
    case 163:
    setColor(255,210,0);
      break;
    case 164:
    setColor(255,205,0);
      break;
    case 165:
    setColor(255,200,0);
      break;
    case 166:
    setColor(255,195,0);
      break;
    case 167:
    setColor(255,190,0);
      break;
    case 168:
    setColor(255,185,0);
      break;
    case 169:
    setColor(255,180,0);
      break;
    case 170:
    setColor(255,175,0);
      break;
    case 171:
    setColor(255,170,0);
      break;
    case 172:
    setColor(255,165,0);
      break;
    case 173:
    setColor(255,160,0);
      break;
    case 174:
    setColor(255,155,0);
      break;
    case 175:
    setColor(255,150,0);
      break;
    case 176:
    setColor(255,145,0);
      break;
    case 177:
    setColor(255,140,0);
      break;
    case 178:
    setColor(255,135,0);
      break;
    case 179:
    setColor(255,130,0);
      break;
    case 180:
    setColor(255,125,0);
      break;
    case 181:
    setColor(255,120,0);
      break;
    case 182:
    setColor(255,115,0);
      break;
    case 183:
    setColor(255,110,0);
      break;
    case 184:
    setColor(255,105,0);
      break;
    case 185:
    setColor(255,100,0);
      break;
    case 186:
    setColor(255,95,0);
      break;
    case 187:
    setColor(255,90,0);
      break;
    case 188:
    setColor(255,85,0);
      break;
    case 189:
    setColor(255,80,0);
      break;
    case 190:
    setColor(255,75,0);
      break;
    case 191:
    setColor(255,70,0);
      break;
    case 192:
    setColor(255,65,0);
      break;
    case 193:
    setColor(255,60,0);
      break;
    case 194:
    setColor(255,55,0);
      break;
    case 195:
    setColor(255,45,0);
      break;
    case 196:
    setColor(255,40,0);
      break;
    case 197:
    setColor(255,35,0);
      break;
    case 198:
    setColor(255,30,0);
      break;
    case 199:
    setColor(255,25,0);
      break;
    case 200:
    setColor(255,20,0);
      break;
    case 201:
    setColor(255,15,0);
      break;
    case 202:
    setColor(255,10,0);
      break;
    case 203:
    setColor(255,5,0);
      break;
    case 204:
    setColor(255,0,0);
      break;

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
    case 0:
    setColor(255,0,0);
      break;
    
  }
  
/*for (int i = 0; i < NUM_LEDS; i++) 
   //The leds we want to show
    if (i < currentLevel) {
      if (leds.r + Color.r > 255)
        leds.r = 255;
      else if (leds.r + Color.r < 0)
        leds.r = 0;
      else
        leds.r = leds.r + Color.r;

      if (leds.g + Color.g > 255)
        leds.g = 255;
      else if (leds.g + Color.g < 0)
        leds.g = 0;
      else 
        leds.g = leds.g + Color.g;


      if (leds.b + Color.b > 255)
        leds.b = 255;
      else if (leds.b + Color.b < 0)
        leds.b = 0;
      else 
        leds.b = leds.b + Color.b;  
    
    } else {  
   leds.r = leds.r/fade_scale;
   leds.g = leds.g/fade_scale;
   leds.b = leds.b/fade_scale;
   }
  setColor(leds.r,leds.g,leds.b);*/

}

// Update the value to the RGB strip
void setColor(int red, int green, int blue){
    analogWrite(RED_PIN,red);
    analogWrite(GREEN_PIN,green);
    analogWrite(BLUE_PIN,blue);
}

//Compute average of the previous sensor values
int compute_average(int *avgs, int len) {
  int sum = 0;
  for (int i = 0; i < len; i++){
    sum += avgs[i];
  }
  return (int)(sum / len);
}


//Insert a value into the average array, and shift it down removing
void insert(int val, int *avgs, int len) {
  for (int i = 0; i < len; i++) {
    if (avgs[i] == -1) {
      avgs[i] = val;
      return;
    } 
  }
  for (int i = 1; i < len; i++) {
    avgs[i - 1] = avgs[i];
  }
  avgs[len - 1] = val;
}


//Function imported from the arduino website.
//Basically map, but with a curve on the scale (can be non-uniform).
//Produces a scaled value to control the colour of the LED
float scalingFunction( float originalMin, float originalMax, float newBegin, float newEnd, float inputValue, float curve){
  float OriginalRange = 0;
  float NewRange = 0;
  float zeroRefCurVal = 0;
  float normalizedCurVal = 0;
  float rangedValue = 0;
  boolean invFlag = 0;

  // condition curve parameter
  // limit range
  if (curve > 10){
  curve = 10;
  }
  
  if (curve < -10){
  curve = -10;
  }
  
  curve = (curve * -.1) ; // - invert and scale - this seems more intuitive - postive numbers give more weight to high end on output 
  curve = pow(10, curve); // convert linear scale into lograthimic exponent for other pow function

  // Check for out of range inputValues
  if (inputValue < originalMin) {
    inputValue = originalMin;
  }

  if (inputValue > originalMax) {
    inputValue = originalMax;
  }

  // Zero Refference the values
  OriginalRange = originalMax - originalMin;
  
  if (newEnd > newBegin){ 
    NewRange = newEnd - newBegin;
  }
  else
  {
    NewRange = newBegin - newEnd; 
    invFlag = 1;
  }

  zeroRefCurVal = inputValue - originalMin;
  normalizedCurVal = zeroRefCurVal / OriginalRange; // normalize to 0 - 1 float

  // Check for originalMin > originalMax - the math for all other cases i.e. negative numbers seems to work out fine 
  if (originalMin > originalMax ) {
    return 0;
  }

  if (invFlag == 0){
    rangedValue = (pow(normalizedCurVal, curve) * NewRange) + newBegin;
  }
  else // invert the ranges
  { 
    rangedValue = newBegin - (pow(normalizedCurVal, curve) * NewRange); 
  }

  return rangedValue;
}
