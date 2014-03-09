#include "playkickoffopp.h"

PlayKickoffOpp::PlayKickoffOpp(WorldModel *wm, StrategyResult *sr, Knowledge *kn, QObject *parent) :
    Play(wm, sr, kn, "PlayKickoffOpp", parent)
{
    _ts = new TacticStop(wm, kn, this);
    _tb1 = new TacticBlock(wm, kn, this);
    _tb2 = new TacticBlock(wm, kn, this);
    _tg  = new TacticGoalie(wm, kn, this);
    _td1 = new TacticDefend(wm, kn, this);
    _td2 = new TacticDefend(wm, kn, this);
    _rg = new RoleGoalie(this);
    _rd = new RoleDefender(this);
}

bool PlayKickoffOpp::EnterCondition()
{
    if(_wm->cmgs.theirKickoff())
        return true;
    else
        return false;
}

bool PlayKickoffOpp::ExecutePlayEngine()
{
    QList<int> agents = _kn->ActiveAgents();

    if(agents.count()<1) return true;

    // Goalie
    _tg->setRID(agents[0]);
    _sr->roles[agents[0]] = _rg;
    _sr->tactics[agents[0]] = _tg;
    _sr->useSkill[agents[0]] = false;

    if(agents.count()<2) return true;

    // Defender 1
    if(agents.count()==2)
        _td1->setTotalDef(1);
    else if(agents.count()>2)
        _td1->setTotalDef(2);
    _td1->setMyDef(1);
    _td1->setRID(agents[1]);
    _td1->defs[1] = agents[1];
    _sr->roles[agents[1]] = _rd;
    _sr->tactics[agents[1]] = _td1;
    _sr->useSkill[agents[1]] = false;

    if(agents.count()<3) return true;

    // Defender 2
    _td2->setRID(agents[2]);
    _td2->setTotalDef(2);
    _td2->setMyDef(2);
    _td2->defs[2] = agents[2];
    _sr->roles[agents[2]] = _rd;
    _sr->tactics[agents[2]] = _td2;
    _sr->useSkill[agents[2]] = false;

    if(agents.count()<4) return true;

    // Stop
    if(agents.count()==4)
        _ts->setTotalStop(1);
    else if(agents.count()==5)
        _ts->setTotalStop(2);
    else if(agents.count()>5)
        _ts->setTotalStop(3);
    _ts->setMyStop(1);
    _ts->setRID(agents[3]);
    _ts->setTarget(_wm->ball.pos.loc,Vector2D(-3010,0),500,true);

    _sr->tactics[agents[3]] = _ts;
    _sr->useSkill[agents[3]] = false;

    if(agents.count()<5) return true;
    return true;
}
