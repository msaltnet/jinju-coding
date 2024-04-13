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

#define MUTE 0 //무음 처리를 위해서 추가

#define TEMPO 300 //템포를 바꾸면 멜로디가 빨리 재생됩니다.

//tone과 beat라는 변수를 갖는 sound 구조체를 정의합니다.
struct sound {
    int tone;
    int beat;
};

//주파수와 음의 길이 정보를 갖는 구조체의 배열
//위에서 정한 sound 구조체를 여러개 가지고 있는 리스트를 정의합니다.
//15개의 정보를 리스트에 넣어주었습니다.
struct sound littleStar[] = { //주파수와 음의 길이 정보를 갖는 구조체의 배열
  {NOTE_C5, 1}, {NOTE_C5, 1}, {NOTE_G5, 1}, {NOTE_G5, 1}, {NOTE_A5, 1},
  {NOTE_A5, 1}, {NOTE_G5, 2}, {MUTE, 1}, {NOTE_F5, 1}, {NOTE_F5, 1},
  {NOTE_E5, 1}, {NOTE_E5, 1}, {NOTE_D5, 1}, {NOTE_D5, 2}, {NOTE_C5, 4},
};
int littleStarCount = 15; //리스트 길이를 정해줍니다.

//playMelody 함수는 멜로디를 연주하는 함수입니다.
void playMelody(sound soundList[], int soundListCount) {
    //soundListCount 만큼 반복하면서 차례대로 소리를 연주합니다
    for(int i = 0; i < soundListCount; i++)
    {
        if (soundList[i].tone == MUTE) { //주파수가 MUTE인 경우
            noTone(BUZZER_PIN); //소리를 내지 않습니다
        } else {
            tone(BUZZER_PIN, soundList[i].tone); //soundList의 i번째 주파수를 재생
        }
        delay(soundList[i].beat * TEMPO); //beat * TEMPO 만큼 연주

        noTone(BUZZER_PIN); //재생중지
        delay(TEMPO/2); //음과 음사이 반박자 대기
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
        tone (BUZZER_PIN, NOTE_G4);
        digitalWrite(LED_GREEN_PIN, HIGH);
        Serial.println("7 on");
    }

    else if (digitalRead(8) == HIGH) {
        tone (BUZZER_PIN, NOTE_A4);
        digitalWrite(LED_BLUE_PIN, HIGH);
        Serial.println("8 on");
    }

    else if (digitalRead(9) == HIGH) {
        tone (BUZZER_PIN, NOTE_B4);
        digitalWrite(LED_RED_PIN, HIGH);
        Serial.println("9 on");
    }

    else if (digitalRead(10) == HIGH) {
        digitalWrite(LED_RED_PIN, HIGH);
        digitalWrite(LED_BLUE_PIN, HIGH);
        //멜로디를 연주하는 함수 playMelody를 호출합니다.
        playMelody(littleStar, littleStarCount);
        Serial.println("10 on");
    }

    else{
        noTone(BUZZER_PIN); // 아무 입력이 없을때 2번 핀의 Tone 함수 사용 안함
        Serial.println("off");
    }
}
