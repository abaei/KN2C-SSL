#include "tactictest.h"

TacticTest::TacticTest(WorldModel *worldmodel, QObject *parent) :
    Tactic(worldmodel, parent)
{
    a = 0;
}

RobotCommand TacticTest::getCommand()
{
    RobotCommand rc;
    rc.maxSpeed = 1;
rc.fin_pos.dir = M_PI/2;
Vector2D kick_pos =  (wm->ball.pos.loc - Vector2D(3025,0));
kick_pos.setLength(ROBOT_RADIUS);
kick_pos = wm->ball.pos.loc + kick_pos;
    switch (a)
    {
    case 0:
        rc.fin_pos.loc = {0,1000};
        //rc.fin_pos.dir = M_PI;
        break;
    case 1:
        rc.fin_pos.loc = {0,1000};
       // rc.fin_pos.dir = 0;
        rc.fin_pos.loc = kick_pos;
        rc.fin_pos.dir = (Vector2D(3025,0) - wm->ourRobot[0].pos.loc  ).dir().radian();
        break;
    case 2:
        rc.fin_pos.loc = {1000,1000};
        break;
    case 3:
        rc.fin_pos.loc = {1000,-1000};
        break;
    }

    if((wm->ourRobot[0].pos.loc-wm->ball.pos.loc).length()<ROBOT_RADIUS+BALL_RADIUS && \
            fabs(( (wm->ball.pos.loc - wm->ourRobot[0].pos.loc).dir().radian() - wm->ourRobot[0].pos.dir)*AngleDeg::RAD2DEG) < 7 )
    {    cout<<"KIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIICK"<<endl;
        rc.kickspeedx=1;
    }
//cout <<a<<" "<< (wm->ourRobot[id].pos.dir - rc.fin_pos.dir)*AngleDeg::RAD2DEG<<endl;
    //if(fabs((wm->ourRobot[id].pos.dir - rc.fin_pos.dir)*AngleDeg::RAD2DEG)<20) a=1;
    if((wm->ourRobot[id].pos.loc - rc.fin_pos.loc).length() < 10) a = 1;//(a+1) % 2;

    return rc;
}
