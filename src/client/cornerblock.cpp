#include "cornerblock.h"

CornerBlock::CornerBlock()
{
}


void CornerBlock::inCornerBlock(/*캐릭터 포인터를 인자로 받아서 네개에다가 각각 인자 넣어야함! */){
    switch(theBlockType)
    {
        case DORMITORY : CornerBlock::inDormitory();
            break;
        case THE61CALL : CornerBlock::in61Call();
            break;
        case BREAKSEMESTER : CornerBlock::inBreakSemester();
            break;
        case PLURALMAJOR : CornerBlock::inPluralMajor();
            break;
        default : printf("CornerBlock error!");
            break;
    }
}

void CornerBlock::inDormitory(){//character class가 만들어져야.. 그 포인터가지고 할듯!!
    //에너지 주기1
    /*
    character->setEnergy(getEnergy()+100(활동력을 주는 만큼))


    */

}
void CornerBlock::in61Call(){//원하는 블럭을 선택할 수 있게 함
    cout<<"You can choose any block."<<endl;
    int blocknumber;//block이 정수로 되어있다는 가정
    cin>>blocknumber;

    //moveTo 를 숫자로 넣을수 있도록 해야할듯!! 현재 있는 칸도 번호 저장해둬서 주사위 돌렸을 때 현재 숫자+주사위 눈 으로 이동하든지
    //이런 경우에 바로 숫자 입력해서 이동할 수 있도록 하든지/

}
void CornerBlock::inBreakSemester(){//무인도
    cout<<"You have to break the semester in this block."<<endl;

    /*
    Dice dice;
    dice.Roll();

    dice.isDouble();
    */


    //1.원래 무인도에 있다가 다시 턴이 된 경우 -> 주사위를 굴릴 수 있게 한다.
    //2.다른 칸에 있다가 갑자기 무인도에 온 경우->바로 쉬게 한다.
    //3.휴식 횟수 새는 기능.
    //dice class받을랭

}

void CornerBlock::inPluralMajor(){//복수전공
    cout<<"You have to take two major for graduation."<<endl;
    //졸업 요건... 아니면 여기에 걸리면 학과독점 해도 다시 해야하는.. 장치!

}
