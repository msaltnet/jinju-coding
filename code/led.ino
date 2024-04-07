#define LED_RED_PIN 13   // LED의 R 핀과 연결된 아두이노 핀 번호 
#define LED_GREEN_PIN 12 // LED의 G 핀과 연결된 아두이노 핀 번호
#define LED_BLUE_PIN 11  // LED의 B 핀과 연결된 아두이노 핀 번호

void setup() { //setup은 처음 한 번 실행되는 함수 입니다.
  pinMode(LED_RED_PIN, OUTPUT);   // LED의 R 핀을 출력으로 설정
  pinMode(LED_GREEN_PIN, OUTPUT); // LED의 G 핀을 출력으로 설정
  pinMode(LED_BLUE_PIN, OUTPUT);  // LED의 B 핀을 출력으로 설정
}

void loop() { //loop는 계속 반복 실행되는 함수 입니다.
  digitalWrite(LED_RED_PIN, HIGH);   // LED와 연결된 핀에 전압을 5V로 설정
  delay(1000);                       // 1초(1000밀리초) 동안 대기
  digitalWrite(LED_RED_PIN, LOW);    // LED와 연결된 핀에 전압을 5V로 설정
  digitalWrite(LED_GREEN_PIN, HIGH); // LED와 연결된 핀에 전압을 0V로 설정
  delay(1000);
  digitalWrite(LED_GREEN_PIN, LOW);  // LED와 연결된 핀에 전압을 0V로 설정
  digitalWrite(LED_BLUE_PIN, HIGH);  // LED와 연결된 핀에 전압을 0V로 설정
  delay(1000);
  digitalWrite(LED_BLUE_PIN, LOW);   // LED와 연결된 핀에 전압을 0V로 설정
}