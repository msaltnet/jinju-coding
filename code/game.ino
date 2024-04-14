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

#define MISS_NUM 3 // 술래를 몇 명으로 할지 정하는 상수
int missPinNum[MISS_NUM]; // 버튼 핀 번호를 무작위로 뽑아서 저장하는 배열

// makeSound 함수는 핀 번호가 missPinNum 배열 중 하나이면 탈락 소리를 낸다.
void makeSound(int pinNum) {
    if (isPass(pinNum)) {
        Serial.println("Pass");
        tone(BUZZER_PIN, NOTE_E4);
        delay(100);
        tone(BUZZER_PIN, NOTE_G4);
        delay(100);
        tone(BUZZER_PIN, NOTE_C5);
        delay(150);
        tone(BUZZER_PIN, NOTE_G4);
        delay(250);
        noTone(BUZZER_PIN);
    } else {
        Serial.println("Miss");
        tone(BUZZER_PIN, NOTE_D4);
        delay(120);
        noTone(BUZZER_PIN);
        delay(30);
        tone(BUZZER_PIN, NOTE_D4);
        delay(450);
        noTone(BUZZER_PIN);
    }
}

// makeMiss 함수는 술래를 정하는 함수이다.
// 이 함수는 3~10사이 숫자로 랜덤으로 술래를 정해서 전역 변수에 저장한다.
void makeMiss() {
    //랜덤 씨드를 설정해줘야 매번 다른 값이 나온다.
    //랜덤 씨드를 아날로그 0번핀의 값을 이용해서 설정한다.
    Serial.print("Start makeMiss: ");
    Serial.println(analogRead(0));
    randomSeed(analogRead(0));
    //missPinNum에 3~10사이의 같지 않은 무작위 숫자를 저장한다.
    for (int i = 0; i < MISS_NUM; i++) {
        int num = random(3, 11);
        while(1) {
            bool isSame = false;
            for (int j = 0; j < i; j++) {
                if (missPinNum[j] == num) {
                    isSame = true;
                    break;
                }
            }
            if (isSame) {
                num = random(3, 11);
            } else {
                break;
            }
        }
        missPinNum[i] = num;
        Serial.print("missPinNum: ");
        Serial.println(num);
    }
}

bool isPass(int pinNum) {
    for (int i = 0; i < MISS_NUM; i++) {
        if (missPinNum[i] == pinNum) {
            return false;
        }
    }
    return true;
}

void setup() {
    Serial.begin(9600);  // 디버깅을 위한 시리얼 통신 설정
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
    makeMiss(); // 술래를 정한다.
} 

void loop() {
    digitalWrite(LED_RED_PIN, LOW);   // LED의 R 핀을 출력을 LOW으로 변경
    digitalWrite(LED_GREEN_PIN, LOW); // LED의 G 핀을 출력을 LOW으로 변경
    digitalWrite(LED_BLUE_PIN, LOW);  // LED의 B 핀을 출력을 LOW으로 변경

    if (digitalRead(3) == HIGH) {         // 만약 10번핀에 HIGH신호가 입력되면
        makeSound(3);
        digitalWrite(LED_RED_PIN, HIGH);  // LED_RED_PIN 핀의 출력을 HIGH로 설정하여 LED 모듈(빨간색) 발광
        Serial.println("3 on");          // 아두이노 IDE 시리얼 모니터에 "9 on" 출력
    }

    else if (digitalRead(4) == HIGH) {    // 위 조건이 해당 하지 않고 만약 8번에 HIGH 신호가 입력되면
        makeSound(4);
        digitalWrite(LED_GREEN_PIN, HIGH);// LED_GREEN_PIN핀의 출력을 HIGH로 설정하여 LED 모듈(초록색) 발광
        Serial.println("4 on");
    }

    else if (digitalRead(5) == HIGH) {    // 위 조건이 해당 하지 않고 만약 9번핀에 HIGH신호가 입력되면
        makeSound(5);
        digitalWrite(LED_BLUE_PIN,HIGH);  // LED_BLUE_PIN핀의 출력을 HIGH로 설정하여 LED 모듈(파란색) 발광
        Serial.println("5 on");
    }

    else if (digitalRead(6) == HIGH) {
        makeSound(6);
        digitalWrite(LED_RED_PIN,HIGH);
        Serial.println("6 on");
    }

    else if (digitalRead(7) == HIGH) {
        makeSound(7);
        digitalWrite(LED_GREEN_PIN, HIGH);
        Serial.println("7 on");
    }

    else if (digitalRead(8) == HIGH) {
        makeSound(8);
        digitalWrite(LED_BLUE_PIN, HIGH);
        Serial.println("8 on");
    }

    else if (digitalRead(9) == HIGH) {
        makeSound(9);
        digitalWrite(LED_RED_PIN, HIGH);
        Serial.println("9 on");
    }

    else if (digitalRead(10) == HIGH) {
        makeSound(10);
        digitalWrite(LED_GREEN_PIN, HIGH);
        Serial.println("10 on");
    }

    else{
        noTone(BUZZER_PIN);              // 아무 입력이 없을때 2번 핀의 Tone 함수 사용 안함
    }
}
