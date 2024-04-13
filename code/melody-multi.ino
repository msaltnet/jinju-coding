#define BUZZER_PIN 2   // LED의 R 핀과 연결된 아두이노 핀 번호 
#define LED_RED_PIN 13   // LED의 R 핀과 연결된 아두이노 핀 번호 
#define LED_GREEN_PIN 12 // LED의 G 핀과 연결된 아두이노 핀 번호
#define LED_BLUE_PIN 11  // LED의 B 핀과 연결된 아두이노 핀 번호

#define NOTE_C4  262 //4옥타브 도에 해당하는 주파수
#define NOTE_D4  294 //4옥타브 레에 해당하는 주파수
#define NOTE_E4  330 //4옥타브 미에 해당하는 주파수
#define NOTE_F4  349 //4옥타브 파에 해당하는 주파수
#define NOTE_G4  392 //4옥타브 솔에 해당하는 주파수
#define NOTE_A4  440 //4옥타브 라에 해당하는 주파수
#define NOTE_B4  494 //4옥타브 시에 해당하는 주파수
#define NOTE_C5  523 //5옥타브 도에 해당하는 주파수
#define NOTE_D5  587
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_G5  784
#define NOTE_A5  880
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_D6  1175
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_G6  1568
#define NOTE_A6  1760
#define NOTE_B6  1976
#define NOTE_C7  2093

#define MUTE 0 //무음 처리를 위해서 추가

int tempo = 300; //노래마다 tempo를 다르게 설정하기 위해 전역변수로 설정

//tone과 beat라는 변수를 갖는 sound 구조체를 정의합니다.
struct sound {
  int tone;
  int beat;
};

// 반짝 반짝 작은 별
struct sound littleStar[] = { //주파수와 음의 길이 정보를 갖는 구조체의 배열
  {NOTE_C5, 1}, {NOTE_C5, 1}, {NOTE_G5, 1}, {NOTE_G5, 1}, {NOTE_A5, 1},
  {NOTE_A5, 1}, {NOTE_G5, 2}, {MUTE, 1}, {NOTE_F5, 1}, {NOTE_F5, 1},
  {NOTE_E5, 1}, {NOTE_E5, 1}, {NOTE_D5, 1}, {NOTE_D5, 2}, {NOTE_C5, 4},
};
int littleStarCount = 15;

// 학교종이 땡땡땡
struct sound schoolBell[] = { //주파수와 음의 길이 정보를 갖는 구조체의 배열
  {NOTE_G4, 1}, {NOTE_G4, 1}, {NOTE_A4, 1}, {NOTE_A4, 1}, // 솔솔라라
  {NOTE_G4, 1}, {NOTE_G4, 1}, {NOTE_E4, 2}, // 솔솔미
  {NOTE_G4, 1}, {NOTE_G4, 1}, {NOTE_E4, 1}, {NOTE_E4, 1}, // 솔솔미미
  {NOTE_D4, 3}, {MUTE, 1}, // 레
  {NOTE_G4, 1}, {NOTE_G4, 1}, {NOTE_A4, 1}, {NOTE_A4, 1}, // 솔솔라라
  {NOTE_G4, 1}, {NOTE_G4, 1}, {NOTE_E4, 2}, // 솔솔미
  {NOTE_G4, 1}, {NOTE_E4, 1}, {NOTE_D4, 1}, {NOTE_E4, 1}, // 솔미레미
  {NOTE_C4, 3}, {MUTE, 1} // 도
};
int schoolBellCount = 25;

// 징글벨
struct sound jingleBell[] = {
    {NOTE_E5, 1}, {NOTE_E5, 1}, {NOTE_E5, 2}, {NOTE_E5, 1}, {NOTE_E5, 1},
    {NOTE_E5, 2}, {NOTE_E5, 1}, {NOTE_G5, 1}, {NOTE_C5, 1}, {NOTE_D5, 1},
    {NOTE_E5, 4}, {MUTE, 1}, {NOTE_F5, 1}, {NOTE_F5, 1}, {NOTE_F5, 1},
    {NOTE_F5, 1}, {NOTE_F5, 1}, {NOTE_E5, 1}, {NOTE_E5, 1}, {NOTE_E5, 1},
    {NOTE_E5, 1}, {NOTE_D5, 1}, {NOTE_D5, 1}, {NOTE_E5, 1}, {NOTE_D5, 2},
    {NOTE_G5, 2}
};
int jingleBellCount = 26;

// 생일축하
struct sound happyBirthday[] = {
    {NOTE_G5, 4}, {NOTE_G5, 4}, {NOTE_A5, 8}, {NOTE_G5, 8}, {NOTE_C6, 8},
    {NOTE_B5, 16}, {MUTE, 2},
    {NOTE_G5, 4}, {NOTE_G5, 4}, {NOTE_A5, 8}, {NOTE_G5, 8}, {NOTE_D6, 8},
    {NOTE_C6, 16}, {MUTE, 2},
    {NOTE_G5, 4}, {NOTE_G5, 4}, {NOTE_G6, 8}, {NOTE_E6, 8}, {NOTE_C6, 8},
    {NOTE_B5, 8}, {NOTE_A5, 16}, {MUTE, 2},
    {NOTE_F6, 4}, {NOTE_F6, 4}, {NOTE_E6, 8}, {NOTE_C6, 8}, {NOTE_D6, 8},
    {NOTE_C6, 16},
};
int happyBirthdayCount = 28;

//playMelody 함수는 멜로디를 연주하는 함수입니다.
void playMelody(sound soundList[], int soundListCount) {
    for(int i = 0; i < soundListCount; i++) //soundListCount 만큼 반복
    {
        if (soundList[i].tone == MUTE) { //무음인 경우
            noTone(BUZZER_PIN);
        } else {
            tone(BUZZER_PIN, soundList[i].tone); //soundList의 i번째 주파수를 재생
        }
        delay(soundList[i].beat * tempo); //beat * tempo 만큼 연주

        noTone(BUZZER_PIN); //재생중지
        delay(tempo/2); //음과 음사이 반박자 대기
    }
}

void setup() {
    pinMode(3, INPUT);   // 디지털 3번핀을 입력모드로 설정
    pinMode(4, INPUT);   // 디지털 4번핀을 입력모드로 설정
    pinMode(5, INPUT);   // 디지털 5번핀을 입력모드로 설정
    pinMode(6, INPUT);   // 디지털 6번핀을 입력모드로 설정
    pinMode(7, INPUT);   // 디지털 7번핀을 입력모드로 설정
    pinMode(8, INPUT);   // 디지털 8번핀을 입력모드로 설정
    pinMode(9, INPUT);   // 디지털 9번핀을 입력모드로 설정
    pinMode(10, INPUT);  // 디지털 10번핀을 입력모드로 설정

    pinMode(BUZZER_PIN, OUTPUT);     // 디지털 2번핀을 출력모드로 설정
    pinMode(LED_RED_PIN, OUTPUT);    // 디지털 11번핀을 출력모드로 설정
    pinMode(LED_GREEN_PIN, OUTPUT);  // 디지털 12번핀을 출력모드로 설정
    pinMode(LED_BLUE_PIN, OUTPUT);   // 디지털 13번핀을 출력모드로 설정
    Serial.begin(9600);              // 디버깅을 위한 시리얼 통신 설정
}

void loop() {
    digitalWrite(LED_RED_PIN, LOW);   // LED의 R 핀을 출력을 LOW으로 변경
    digitalWrite(LED_GREEN_PIN, LOW); // LED의 G 핀을 출력을 LOW으로 변경
    digitalWrite(LED_BLUE_PIN, LOW);  // LED의 B 핀을 출력을 LOW으로 변경

    if (digitalRead(3) == HIGH) {         // 만약 10번핀에 HIGH신호가 입력되면
        tone (BUZZER_PIN, NOTE_C4);           // 2번핀에 주파수 246의 신호를 출력
        digitalWrite(LED_RED_PIN, HIGH);  // LED_RED_PIN 핀의 출력을 HIGH로 설정하여 LED 모듈(빨간색) 발광
        Serial.println("3 on");          // 아두이노 IDE 시리얼 모니터에 "9 on" 출력
    }

    else if (digitalRead(4) == HIGH) {    // 위 조건이 해당 하지 않고 만약 8번에 HIGH 신호가 입력되면
        tone (BUZZER_PIN, NOTE_D4);           // 2번핀에 주파수 261의 신호를 출력
        digitalWrite(LED_GREEN_PIN, HIGH);// LED_GREEN_PIN핀의 출력을 HIGH로 설정하여 LED 모듈(초록색) 발광
        Serial.println("4 on");
    }

    else if (digitalRead(5) == HIGH) {    // 위 조건이 해당 하지 않고 만약 9번핀에 HIGH신호가 입력되면
        tone (BUZZER_PIN, NOTE_E4);           // 2번핀에 주파수 294의 신호를 출력
        digitalWrite(LED_BLUE_PIN,HIGH);  // LED_BLUE_PIN핀의 출력을 HIGH로 설정하여 LED 모듈(파란색) 발광
        Serial.println("5 on");
    }

    else if (digitalRead(6) == HIGH) {
        tone (BUZZER_PIN, NOTE_F4);
        digitalWrite(LED_RED_PIN,HIGH);
        Serial.println("6 on");
    }

    else if (digitalRead(7) == HIGH) {
        // 생일축하 멜로디는 tempo를 50으로 설정
        tempo = 50;
        digitalWrite(LED_GREEN_PIN, HIGH);
        playMelody(happyBirthday, happyBirthdayCount);
        // 멜로디가 끝나면 tempo를 다시 300으로 설정
        tempo = 300;
        Serial.println("7 on");
    }

    else if (digitalRead(8) == HIGH) {
        digitalWrite(LED_BLUE_PIN, HIGH);
        playMelody(jingleBell, jingleBellCount);
        Serial.println("8 on");
    }

    else if (digitalRead(9) == HIGH) {
        digitalWrite(LED_RED_PIN, HIGH);
        playMelody(schoolBell, schoolBellCount);
        Serial.println("9 on");
    }

    else if (digitalRead(10) == HIGH) {
        digitalWrite(LED_RED_PIN, HIGH);
        digitalWrite(LED_BLUE_PIN, HIGH);
        playMelody(littleStar, littleStarCount);
        Serial.println("10 on");
    }

    else{
        noTone(BUZZER_PIN);   // 아무 입력이 없을때 2번 핀의 Tone 함수 사용 안함
        Serial.println("off");
    }
}
