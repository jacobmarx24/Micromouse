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
#include <stack>
#include <map>
using namespace std;



class RaceCarDriver {
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

        vertex() {
            x = 0;
            y = 0;
            d = NORTH;
            iteration = 0;
            dPrev = NORTH;
        }

        DIRECTION d = NORTH;
        int status = 0;
        int x = 0;
        int y = 0;
        int iteration = 0;
        DIRECTION dPrev = NORTH;
        int visited = 0;

        bool operator<(const vertex& two) const{
            if(x != two.x) {
                return x < two.x;
            }
            return y < two.y;
        }
/*
        bool operator==(const vertex& two) const {
            if(x==two.x && y == two.y) {
                return true;
            }
            return false;
        }
        */


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


    static vector<vertex> BFS(map<vertex,vector<vertex>> adj_list,vertex word, vertex end,queue<vertex> q) {
        map<vertex,vertex> prev;
        set<pair<int,int>> visited;

        prev[word] = word;
        q.push(word);
        vertex endLocation = end;
        bool isEnd = false;
        while(isEnd == false && !q.empty()) {
            word = q.front();
            q.pop();
            for(int i = 0; i < adj_list[word].size();++i) {
                if(visited.find({adj_list[word].at(i).x,adj_list[word].at(i).y})==visited.end()) {
                    visited.insert({adj_list[word].at(i).x,adj_list[word].at(i).y});
                    prev[adj_list[word].at(i)] = word;
                    q.push(adj_list[word].at(i));

                    if(adj_list[word].at(i).x==endLocation.x &&
                        adj_list[word].at(i).y==endLocation.y) {
                        prev[endLocation] = word;
                        isEnd = true;
                        }
                }
            }
        }
        stack<vertex> rev;
        while(!(endLocation.x == 0 && endLocation.y == 0)) {
            rev.push(endLocation);
            endLocation = prev[endLocation];
        }
        vector<vertex> actual;
        while(!rev.empty()) {
            actual.push_back(rev.top());
            rev.pop();
        }


        return actual;
    }

    DIRECTION nextMove() {
        static queue<vertex> q;
        static vector<vertex> s;
        static map<vertex,vector<vertex>> adjacency_list;
        static bool start = true;
        static int numRun = 0;
        static int pathInd = 0;
        vertex starting;
        static vertex end;
        static vertex toEnd;
        static bool gotStart = false;
        vector<vertex> static rev;
        static map<vertex,vertex> path;

        DIRECTION d = NORTH;
        if(numRun==0 && !gotStart) {
            starting.x = car->getLocation().x;
            starting.y = car->getLocation().y;
            gotStart = true;
        }

        vertex v(0,0,NORTH,0,NORTH);
        if(car->getLocation().x==starting.x
            && car->getLocation().y==starting.y) {

            s.clear();
            s.emplace(s.begin(),v);
            ++numRun;
            start = false;
            pathInd = 0;
            if(numRun==2) {
                 end = vertex(toEnd.x,toEnd.y,toEnd.d,toEnd.iteration,toEnd.dPrev);
            }
        }
        v = s.at(0);

        if(numRun==1) {
            while(v.iteration < 4) {
                if(!car->look(v.d) && !isOn(s,addDirection(v,v.d))) {
                    vertex v2 = addDirection(v,v.d);
                    v.status=1;
                    d = v.d;
                    v2.dPrev = d;
                    if(d == SOUTH) {
                        v2.dPrev=NORTH;
                    }
                    else if(d == NORTH) {
                        v2.dPrev = SOUTH;
                    }
                    else if(d==EAST) {
                        v2.dPrev=WEST;
                    }
                    else {
                        v2.dPrev=EAST;
                    }
                    v2.d = d;
                    // prev = DIRECTION(v.d%4);
                    v.d = DIRECTION((v.d+1) % 4);
                    v.iteration+=1;
                    s[0] = v;
                    v2.status = 0;
                    v2.iteration = 0;
                    toEnd=v2;
                    if(!isInAdjacencyList(adjacency_list,v,v2)) {
                        adjacency_list[v].push_back(v2);
                        adjacency_list[v2].push_back(v);
                    }

                    s.emplace(s.begin(),v2);
                    return d;
                }
                v.d = DIRECTION((v.d+1)%4);
                v.iteration+=1;

            }

            v.status=2;

            s.erase(s.begin());


            if(s.empty()) {
                start = true;
                return d;
            }

            if(v.dPrev == NORTH) {
                return NORTH;
            }
            if( v.dPrev == SOUTH) {
                return SOUTH;
            }
            if( v.dPrev == EAST) {
                return EAST;
            }
            return WEST;
        }

        if(numRun>1) {
            if(pathInd==0) {
                rev = BFS(adjacency_list, v,end, q);
            }
            do {
                return rev.at(pathInd++).d;
            }while(rev.at(pathInd-1).x != end.x && rev.at(pathInd-1).y!=end.y);

        }
        return d;

    }



};


#endif /* RACECARDRIVER_H_ */
