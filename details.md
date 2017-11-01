# 최종 구조

<img src="../img/UI proto.png"></image>

## UI

전체적인 매커니즘은..

- Backend에 처리를 요청
    - Capture, Stop, Load, Save
- Backend에서는 작업 처리 후 notification을 보냄(WINAPI SendMessage함수처럼)
- 이를 받으면 자료구조에서 update된 data를 받아옴.

### MAIN UI

상황에서 불가능한 선택지는 클릭 못하도록 설정
- 패킷 캡쳐를 하지도 않았는데 저장 버튼이 눌리지 않도록
- 

상단 메뉴바
- file
    - load(open), save as, exit 필요.
    - 파일 경로를 입력받아야 되므로, WINAPI 에서 파일 위치 찾는 창 띄우기.
    - 메모장 `파일` 메뉴처럼 누르면 바로 아래에 뜨게끔.
- options
    - 누르면 체크박스로 `primiscuous mode` 를 toggle(체크/체크해제) 하는 버튼이 아래에 뜨게 하기
    - options 라는 flag 변수를 하나 두어, 캡쳐링 함수 호출시 인자로 넘겨줘야 함.
- capture
    - capturing 루틴으로 들어가기
    - options를 인자값으로 넣어줘야 함
    - 
- 회색/초록 네모
    - 캡쳐 중에는 초록, 아닐 때에는 회색으로 색 설정되게끔 하기.

preview 보여줄 section

- 

### SUB UI

-

## BACKEND

## DATA