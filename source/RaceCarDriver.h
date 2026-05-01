/*
* RaceCarDriver.h
 *
 *  Created on: Spring, 2026
 *      Author: bill_booth
 */

#ifndef RACECARDRIVER_H_
#define RACECARDRIVER_H_

#include "Racer.h"
#include <vector>
using namespace std;



class RaceCarDriver{
private:
    Racer* car;

    struct vertex {

        vertex(int x1, int y1, DIRECTION d1, int iteration1, DIRECTION prev) {
            x = x1;
            y = y1;
            d = d1;
            iteration = iteration1;
            dPrev = prev;
        }

        DIRECTION d = NORTH;
        int status = 0;
        int x = 0;
        int y = 0;
        int iteration = 0;
        DIRECTION dPrev = NORTH;

    };


public:
    RaceCarDriver(Racer* p = nullptr): car{p}{}




    bool isOn(vector<vertex> p,vertex v) {
        for(int i = 0; i<p.size();++i) {
            if(p.at(i).x==v.x && p.at(i).y==v.y) {
                return true;
            }
        }
        return false;
    }

    int findX(vector<vertex> p,vertex v) {
        for(int i = 0; i<p.size();++i) {
            if(p.at(i).x==v.x && p.at(1).y==v.y) {
                return i;
            }
        }
        return -1;
    }


    vertex addDirection(vertex v, DIRECTION d) {
        if(d == NORTH) {
            v.y+=1;
        }
        if(d==SOUTH) {
            v.y-=1;
        }
        if(d==EAST) {
            v.x+=1;
        }
        if(d==WEST) {
            v.x-=1;
        }
        return v;
    }
    vector<vertex> s;
    DIRECTION prev = NORTH;

    DIRECTION nextMove(){
        DIRECTION d = NORTH;


        vertex v(0,0,NORTH,0,NORTH);
        if(car->getLocation().x == 0 && car->getLocation().y==0) {
            s.clear();
            s.emplace(s.begin(),v);
        }
        v = s.at(0);


        int done = false;
        while(v.iteration < 4) {

            if(!car->look(v.d) && !isOn(s,addDirection(v,v.d))) {
                vertex v2 = addDirection(v,v.d);
                v.status=1;
                d = v.d;
                v2.dPrev = v.d;
                prev = DIRECTION(v.d%4);
                v.d = DIRECTION((v.d+1) % 4);
                v.iteration+=1;
                s[0] = v;
                v2.status = 0;
                v2.iteration = 0;
                v2.d = NORTH;

                s.emplace(s.begin(),v2);
                return d;
            }
            v.d = DIRECTION(v.d+1);
            v.iteration+=1;

        }
        v.status=2;
        prev = v.dPrev;
        s.erase(s.begin());


        if(s.empty()) {
            return d;
        }
        DIRECTION previous = s.at(0).d;

        if(prev == NORTH) {
            prev = SOUTH;
            return SOUTH;
        }
        if(prev == SOUTH) {
            prev = NORTH;
            return NORTH;
        }
        if(prev == EAST) {
            prev = WEST;
            return WEST;
        }
        prev = EAST;
        return EAST;
    }

};


#endif /* RACECARDRIVER_H_ */
