> > "나는 2D 세카이로 가고 싶어!"
>
> 미소년 박창우 군이 있다. 이 소년은 2D에 빠져 있다.
>
> 이런 박창우 군의 취향을 3D로 바꾸어 보자.

# Credit

- 김도영
- 연동경

# 스크립트 작성 요령

`script.txt`에 작성하면 된다.

- `[이름]` 화자 이름. 그 아래로 줄바꿈 하고 대사 치면 된다.
- `> 선택지 (+1|-1)` 대화 아래에 선택지를 이렇게 구성하면 된다. 그 뒤에 붙는 건 호감도 상승 / 하강이다. (ex. `> 그래 (+2)` - 선택 시 호감도 2 상승)
  - 그 아래에 이어질 대사는 스페이스 4개(``) 로 작성한다.
- `_` 대화 청크 끝.
- `{END: 엔딩 이름}` 엔딩 및 게임 종료

예시

(주: 아래 쓰여질 대사는 저의 공식 입장이 아닙니다. 저는 이런 성향을 지지하지 않습니다.)

```
[박창우]
너는 어떤 노래를 자주 들어?

> K-POP (-1)
    음... そうか
> J-POP (+3)
    역시 君は 들을 줄 아는구나!
> POP (+1)
    えーと... 팝도 좋지
_
```