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
#include <queue>
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
        int weight = 0;
        int color  = 0;
        vertex* v = nullptr;

        bool operator<(const vertex& two) const{
            if(x != two.x) {
                return x < two.x;
            }
            return y < two.y;
        }



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

    bool isInAdjacencyList(map<vertex,vector<vertex>> s, vertex v,vertex v2) {
        for(int i = 0; i < s[v].size();++i) {
            if(s[v].at(i).x==v2.x && s[v].at(i).y==v2.y) {
                return true;
            }
        }
        return false;
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

    DIRECTION nextMove() {
        static vector<vertex> s;
        static map<vertex,vector<vertex>> adjacency_list;
        static bool start = true;
        static int numRun = 0;
        DIRECTION d = NORTH;


        vertex v(0,0,NORTH,0,NORTH);
        if(car->getLocation().x == 0 && car->getLocation().y==0) {
            s.clear();
            s.emplace(s.begin(),v);
            ++numRun;
            start = false;
        }
            v = s.at(0);

        if(numRun==1) {
            while(v.iteration < 4) {
                if(!car->look(v.d) && !isOn(s,addDirection(v,v.d))) {
                    vertex v2 = addDirection(v,v.d);
                    if(!isInAdjacencyList(adjacency_list,v,v2)) {
                        adjacency_list[v].push_back(v2);
                        adjacency_list[v2].push_back(v);
                    }
                    v.status=1;
                    d = v.d;
                    v2.dPrev = d;
                    // prev = DIRECTION(v.d%4);
                    v.d = DIRECTION((v.d+1) % 4);
                    v.iteration+=1;
                    s[0] = v;
                    v2.status = 0;
                    v2.iteration = 0;
                    v2.d = NORTH;

                    s.emplace(s.begin(),v2);
                    return d;
                }
                v.d = DIRECTION((v.d+1)%4);
                v.iteration+=1;

            }
        }
            v.status=2;

            s.erase(s.begin());


            if(s.empty()) {
                start = true;
                return d;
            }


            if(v.dPrev == NORTH) {
                return SOUTH;
            }
            if( v.dPrev == SOUTH) {
                return NORTH;
            }
            if( v.dPrev == EAST) {
                return WEST;
            }
            return EAST;
        }


        /*
            queue<vertex> q;
            q.push(v);
            vertex prevVert = v;
            while(!q.empty()) {
                vertex v3 = q.front();
                v3.color = 0;
                q.pop();
                for(int i = 0; i < adjacency_list[v3].size();++i) {
                    vertex v4 = adjacency_list[v3].at(i);
                    if(v4.color==0) {
                        v4.color = 1;
                        v4.d = DIRECTION((v.d+1)%4);
                        v4.v = &v;
                        q.push(v4);
                        for(int i = 0; i < 4; ++i) {
                            if(addDirection(v3,DIRECTION((v3.d+i)%4)).x==v4.x
                                && addDirection(v3,DIRECTION((v3.d+i)%4)).y==v4.y) {
                                return d;
                                }
                        }
                    }
                }
                v3.color = 2;

            }
            */




};


#endif /* RACECARDRIVER_H_ */
