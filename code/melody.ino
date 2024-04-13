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