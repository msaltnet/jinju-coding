author: Jeong Seongmoon
summary: 멜로디 연주하기
id: play-button
categories: codelab
environments: Web
status: Published
feedback link: https://github.com/msaltnet/jinju-coding

# 멜로디 연주하기

## 시작하기
Duration: 0:01:00

[버튼으로 소리내기](../button/)에서 버튼을 눌러서 신호를 발생시키고, 특정 주파수의 신호를 버저에 보내서 피아노를 만들어 보았습니다. 그 회로를 그대로 사용해서 멜로디를 연주해보는 프로그램을 만들어 보겠습니다.

우선 멜로디를 연주하는 방법에 대해서 알아보고, 버튼을 눌렀을 때 멜로디가 연주되도록 프로그램을 만들어 보고, 마지막으로 버튼마다 다른 멜로디가 연주되도록 프로그램을 만들어 보겠습니다.

### 사전 준비
1. [버튼으로 소리내기](../button/)에서 완성한 보드와 회로
1. 아두이노와 연결 가능한 PC와 IDE

### 배우게 될 것
1. 멜로디를 연주하게 만드는 방법
1. 버튼을 눌렀을때 LED가 켜지고, 저장된 멜로디가 연주되는 회로와 프로그램을 만드는 방법

## 멜로디 연주하기
Duration: 0:10:00

멜로디는 정해진 시간 동안 특정 주파수의 소리를 연속적으로 발생시키는 것입니다.

아래 프로그램을 보드에 업로드해서 멜로디가 1회 연주되는 것을 확인해 보세요.

1회만 연주되도록 프로그래밍되어 있으니까, 다시 재생하고 싶을 때는 아두이노 보드에 붙어있는 빨간색 리셋 버튼을 눌러서 아두이노를 껐다켜보세요.

프로그램은 아래와 같고, [`melody.ino`](https://github.com/msaltnet/jinju-coding/blob/main/code/melody.ino) 파일을 열어서 사용할 수 있습니다.

프로그램 코드에 설명을 잘 적어두었으니 읽어보고 원하는대로 바꿔서 프로그래밍해보세요.

```c
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
struct sound soundList[] = { 
    {NOTE_C5, 1}, {NOTE_C5, 1}, {NOTE_G5, 1}, {NOTE_G5, 1}, {NOTE_A5, 1},
    {NOTE_A5, 1}, {NOTE_G5, 2}, {MUTE, 1}, {NOTE_F5, 1}, {NOTE_F5, 1},
    {NOTE_E5, 1}, {NOTE_E5, 1}, {NOTE_D5, 1}, {NOTE_D5, 2}, {NOTE_C5, 3},
};
int soundListCount = 15; //리스트 길이를 정해줍니다.

//멜로디 재생 여부를 저장하는 변수
//한 번만 재생 될 수 있도록 재생 되었음을 기록합니다.
bool isPlayed = false; 

void setup() {
    pinMode(BUZZER_PIN, OUTPUT);     // 디지털 2번핀을 출력모드로 설정
    pinMode(LED_RED_PIN, OUTPUT);    // 디지털 11번핀을 출력모드로 설정
    pinMode(LED_GREEN_PIN, OUTPUT);  // 디지털 12번핀을 출력모드로 설정
    pinMode(LED_BLUE_PIN, OUTPUT);   // 디지털 13번핀을 출력모드로 설정
}

void loop() {
    if (isPlayed == true) { //멜로디가 재생된 경우 재생하지 않고 종료함
        return;
    }
    isPlayed = true; //멜로디 재생 여부를 true로 설정해서 1회만 재생되도록 함

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
```

## 버튼 눌러서 멜로디 연주하기
Duration: 0:10:00

앞에서 정해진 멜로디가 딱 한 번 연주되도록 프로그램을 만들었습니다. 이번에는 버튼을 이용해서 버튼을 눌렀을 때 멜로디가 연주되도록 프로그램을 만들어 보겠습니다.

프로그램이 복잡해지면서, 프로그램 코드가 많이 길어졌습니다.

프로그램은 아래와 같고, [`melody-button.ino`](https://github.com/msaltnet/jinju-coding/blob/main/code/melody-button.ino) 파일을 열어서 사용할 수 있습니다.

직접 아두이노 보드에 업로드해서 실행해보세요. 코드를 보고 어느 버튼을 눌러야 멜로디가 연주되는지 먼저 맞춰보세요.

```c
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
        noTone(BUZZER_PIN);  // 아무 입력이 없을때 2번 핀의 Tone 함수 사용 안함
        Serial.println("off");
    }
}
```

## 여러 멜로디를 연주하기
Duration: 0:10:00

이번에는 마지막으로 버튼마다 다른 멜로디가 연주되도록 프로그램을 만들어 보겠습니다.

프로그램이 더 길어졌지만 멜로디 정보가 추가되었을 뿐 앞에서 만들 프로그램이랑 구조는 동일합니다. 이해하기 어렵지 않으니 천천히 읽어보고, 마음대로 바꿔가면서 실험해보세요.

프로그램은 아래와 같고, [`melody-multi.ino`](https://github.com/msaltnet/jinju-coding/blob/main/code/melody-multi.ino) 파일을 열어서 사용할 수 있습니다.

직접 아두이노 보드에 업로드해서 실행해보세요. 코드를 바꿔서 원하를 멜로디를 추가해보세요.

```c
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
```

## 정리
Duration: 0:02:00

멜로디를 연주하기 위해서 조금 더 복잡하게 프로그래밍을 했습니다. 처음에는 어렵다고 생각될 수 있지만 코드를 자주 읽어보면 어떤 내용인지 이해할 수 있고, 내 마음대로 바꿔가면서 프로그램을 만들면서 재미를 느낄 수 있습니다.

프로그램은 얼마든지 바꿔가면서 실험을 해도 보드가 망가지지 않으니 마음껏 실험을 해보세요. 그리고, 동작이 원하는 대로 잘 안되면 앞에서 알려준 프로그램을 다시 업로드하면 됩니다.

원하는대로 프로그램을 만드는것이 잘 안되면 인터넷에서 검색을 해보면서 문제를 해결해 보세요.

- [아두이노 시작하기(2) - 아두이노 IDE 시리얼 모니터 사용해보기](https://blog.naver.com/rence92/220736278731)
