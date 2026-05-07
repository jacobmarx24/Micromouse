/*
 * Integration requirements:
 * vertexTeam5 struct
 * isInAdjacencyListTeamFive()
 * isOnTeamFive()
 * addDirectionTeamFive()
 * findTeam5()
 * BFSTeamFive()
 * DFS1TeamFive()
 * DFS2TeamFive()
 * nextMoveTeamFive()
 */

/*
* Author: Group Five
* Elias Tovar, Jacob Marx, Jeffery Rajkumar, Gavin Pena, Kenneth Falato
* Assignment Title: Micromouse
* Assignment Description: Drives micromouse through maze for fast times.
* Due Date: 5/6/2026
* Date Created: 4/29/2026
* Date Last Modified: 5/6/2026
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
    struct vertexTeam5 {

        vertexTeam5(int x1, int y1, DIRECTION d1, int iteration1, DIRECTION prev) {
            x = x1;
            y = y1;
            d = d1;
            iteration = iteration1;
            dPrev = prev;
        }

        vertexTeam5() {
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
        bool explored = false;

        bool operator<(const vertexTeam5& two) const {
            if(x != two.x) {
                return x < two.x;
            }
            return y < two.y;
        }

    };

public:
    RaceCarDriver(Racer* p = nullptr): car{p} {}

    /*
 * description: returns true if vertex v is in vector p.
 * return: bool
 * precondition: p and v are valid
 * postcondition: returns true or false, no edit to given variables.
 *
*/
    bool isOnTeamFive(vector<vertexTeam5> p, vertexTeam5 v) {
        for(int i = 0; i < p.size(); ++i) {
            if(p.at(i).x == v.x && p.at(i).y == v.y) {
                return true;
            }
        }
        return false;
    }

    /*
 * description: returns true if given vertex is in graph
 * return: bool
 * precondition: s, v1 and v2 are valid
 * postcondition: returns true or false, no edit to given variables.
 *
*/
    bool isInAdjacencyListTeamFive(map<vertexTeam5,vector<vertexTeam5>> s, vertexTeam5 v, vertexTeam5 v2) {
        for(int i = 0; i < s[v].size(); ++i) {
            if(s[v].at(i).x == v2.x && s[v].at(i).y == v2.y) {
                return true;
            }
        }
        return false;
    }

    /*
* description: returns the next vertex in the given direction from the given vertex
* return: vertex
* precondition: v and d are valid
* postcondition: returns new vertex
*
*/
    vertexTeam5 addDirectionTeamFive(vertexTeam5 v, DIRECTION d) {
        if(d == NORTH) {
            v.y -= 1;
        }
        if(d == SOUTH) {
            v.y += 1;
        }
        if(d == EAST) {
            v.x += 1;
        }
        if(d == WEST) {
            v.x -= 1;
        }
        return v;
    }

    bool findTeam5(vector<vertexTeam5> v, vertexTeam5 x) {
        for(vertexTeam5 u: v) {
            if(u.x == x.x && u.y == x.y) {
                return true;
            }
        }
        return false;
    }


    /*
* description: Breadth First Search
* return: vector<vertex>
* precondition: given graph is filled with nodes
* postcondition: returns a vector<vertex> as the path through
*
*/
    static vector<vertexTeam5> BFSTeamFive(map<vertexTeam5,vector<vertexTeam5>> adj_list, vertexTeam5 word, vertexTeam5 end, queue<vertexTeam5> q) {
        map<vertexTeam5,vertexTeam5> prev;
        set<pair<int,int>> visited;
        vertexTeam5 start = word;
        prev[word] = word;
        q.push(word);
        vertexTeam5 endLocation = end;
        bool isEnd = false;

        while(isEnd == false && !q.empty()) {
            word = q.front();
            q.pop();
            for(int i = 0; i < adj_list[word].size(); ++i) {
                if(visited.find({adj_list[word].at(i).x, adj_list[word].at(i).y}) == visited.end()) {
                    visited.insert({adj_list[word].at(i).x, adj_list[word].at(i).y});
                    prev[adj_list[word].at(i)] = word;
                    q.push(adj_list[word].at(i));

                    if(adj_list[word].at(i).x == endLocation.x &&
                        adj_list[word].at(i).y == endLocation.y) {
                        prev[adj_list[word].at(i)] = word;
                        isEnd = true;
                    }
                }
            }
        }

        stack<vertexTeam5> rev;
        while(!(endLocation.x == 0 && endLocation.y == 0)){
            rev.push(endLocation);
            endLocation = prev[endLocation];
        }

        vector<vertexTeam5> actual;
        while(!rev.empty()) {
            actual.push_back(rev.top());
            rev.pop();
        }

        actual.emplace(actual.begin(),start);
        return actual;
    }

    /*
* description: Depth First Search, first run
* return: DIRECTION, used in recursion
* precondition: given graph is filled with nodes
* postcondition: moves the car following DFS
*
*/
    DIRECTION DFS1TeamFive(vertexTeam5& v, vector<vertexTeam5>& s,
        vertexTeam5& toEnd, map<vertexTeam5,vector<vertexTeam5>>& adjacency_list,vector<vertexTeam5>& visited) {
        DIRECTION d = NORTH;

        while(v.iteration < 4) {
            vertexTeam5 v2 = addDirectionTeamFive(v, v.d);
            if(!car->look(v.d)) {
                v2.d = v.d;
                if(v.d == SOUTH) {
                    v2.dPrev = NORTH;
                }
                else if(v.d == NORTH) {
                    v2.dPrev = SOUTH;
                }
                else if(v.d == EAST) {
                    v2.dPrev = WEST;
                }
                else {
                    v2.dPrev = EAST;
                }
                if(!isInAdjacencyListTeamFive(adjacency_list,v,v2)) {
                    adjacency_list[v].push_back(v2);
                    adjacency_list[v2].push_back(v);
                }
            }
            if(!car->look(v.d) && !isOnTeamFive(s, addDirectionTeamFive(v, v.d)) &&
                !isOnTeamFive(visited,v2)) {
                visited.push_back(v2);
                v.status = 1;
                d = v.d;
                v2.dPrev = d;
                if(d == SOUTH) {
                    v2.dPrev = NORTH;
                }
                else if(d == NORTH) {
                    v2.dPrev = SOUTH;
                }
                else if(d == EAST) {
                    v2.dPrev = WEST;
                }
                else {
                    v2.dPrev = EAST;
                }
                v2.d = NORTH;
                v.d = DIRECTION((v.d + 1) % 4);
                v.iteration += 1;
                s[0] = v;
                v2.status = 0;
                v2.iteration = 0;
                toEnd = v2;
                s.emplace(s.begin(), v2);
                return d;
            }
            v.d = DIRECTION((v.d + 1) % 4);
            v.iteration += 1;
        }

        v.status = 2;
        s.erase(s.begin());

        if(s.empty()) {
            return d;
        }

        if(v.dPrev == NORTH) {
            return NORTH;
        }
        if(v.dPrev == SOUTH) {
            return SOUTH;
        }
        if(v.dPrev == EAST) {
            return EAST;
        }
        return WEST;
    }

    /*
* description: Depth First Search, second run
* return: DIRECTION, used in recursion
* precondition: given graph is filled with nodes
* postcondition: moves the car following DFS
*
*/
   DIRECTION DFS2TeamFive(vertexTeam5& v, vector<vertexTeam5>& s,
        vertexTeam5& toEnd, map<vertexTeam5,vector<vertexTeam5>>& adjacency_list, vector<vertexTeam5>& visited,vertexTeam5& end, vector<vertexTeam5> &done) {
        DIRECTION d = NORTH;
        DIRECTION oldV = v.d;
        while(v.iteration < 4) {
            vertexTeam5 v2 = addDirectionTeamFive(v, v.d);
            if(!car->look(v.d)) {
                if(!isInAdjacencyListTeamFive(adjacency_list,v,v2)) {
                    v2.d = v.d;
                    if(v.d == SOUTH) {
                        v2.dPrev = NORTH;
                    }
                    else if(v.d == NORTH) {
                        v2.dPrev = SOUTH;
                    }
                    else if(v.d == EAST) {
                        v2.dPrev = WEST;
                    }
                    else {
                        v2.dPrev = EAST;

                    }
                        adjacency_list[v].push_back(v2);
                        adjacency_list[v2].push_back(v);
                }
            }
            if(!car->look(v.d) && !isOnTeamFive(s, addDirectionTeamFive(v, v.d))
                && !findTeam5(visited,v2) && !isOnTeamFive(done,v2)) {
                    visited.push_back(v2);

                    v.status = 1;
                    d = v.d;
                    v2.dPrev = d;
                    if(d == SOUTH) {
                        v2.dPrev = NORTH;
                    }
                    else if(d == NORTH) {
                        v2.dPrev = SOUTH;
                    }
                    else if(d == EAST) {
                        v2.dPrev = WEST;
                    }
                    else {
                        v2.dPrev = EAST;
                    }
                    v2.d = NORTH;
                    v.d = DIRECTION((v.d + 1) % 4);
                    v.iteration += 1;
                    s[0] = v;
                    v2.status = 0;
                    v2.iteration = 0;
                    toEnd = v2;
                    s.emplace(s.begin(), v2);
                    return d;
            }


            v.d = DIRECTION((v.d + 1) % 4);
            v.iteration += 1;
        }

        v.iteration = 0;
        v.d=oldV;

        while(v.iteration < 4) {
            vertexTeam5 v2 = addDirectionTeamFive(v, v.d);
            if(!car->look(v.d) && !isOnTeamFive(s, addDirectionTeamFive(v, v.d))
                && !isOnTeamFive(done,v2)) {
                v.status = 1;
                d = v.d;
                v2.dPrev = d;
                if(d == SOUTH) {
                    v2.dPrev = NORTH;
                }
                else if(d == NORTH) {
                    v2.dPrev = SOUTH;
                }
                else if(d == EAST) {
                    v2.dPrev = WEST;
                }
                else {
                    v2.dPrev = EAST;
                }
                v2.d = NORTH;
                v.d = DIRECTION((v.d + 1) % 4);
                v.iteration += 1;
                s[0] = v;
                v2.status = 0;
                v2.iteration = 0;
                toEnd = v2;
                s.emplace(s.begin(), v2);
                return d;
            }
            v.d = DIRECTION((v.d + 1) % 4);
            v.iteration += 1;
        }

        v.status = 2;
        s.erase(s.begin());
        done.push_back(v);

        if(s.empty()) {
            return d;
        }

        if(v.dPrev == NORTH) {
            return NORTH;
        }
        if(v.dPrev == SOUTH) {
            return SOUTH;
        }
        if(v.dPrev == EAST) {
            return EAST;
        }
        return WEST;

    }

    /*
* description: called by the driver, this is the next move of the car
* return: DIRECTION
* precondition: car is constructed
* postcondition: determines run# and moves the car depending on the run#
*
*/
    DIRECTION nextMoveTeamFive(int run = 0) {
        static queue<vertexTeam5> q;
        static vector<vertexTeam5> s;
        static map<vertexTeam5,vector<vertexTeam5>> adjacency_list;
        static bool start = true;
        static int pathInd = 0;
        static vertexTeam5 end;
        static vertexTeam5 toEnd;
        static vector<vertexTeam5> rev;
        static map<vertexTeam5,vertexTeam5> path;
        static int currRun = -1;
        static vector<vertexTeam5> visited;
        static vector<vertexTeam5> done;


        DIRECTION d = NORTH;

        vertexTeam5 v(0, 0, NORTH, 0, NORTH);

        if(currRun < run) {
            if(run == 1) {
                start = false;
                end = toEnd;
            }
            s.clear();
            s.emplace(s.begin(), v);
            ++currRun;
            pathInd = 0;

        }


        v = s.at(0);


        if(run == 0) {
            return DFS1TeamFive(v, s, toEnd, adjacency_list,visited);
        }

        if(run == 1) {
            return DFS2TeamFive(v, s, toEnd, adjacency_list,visited,end,done);
        }

        if(run > 1) {
            if(pathInd == 0) {
                rev = BFSTeamFive(adjacency_list, v, end, q);
            }
            DIRECTION gd = WEST;
            DIRECTION n = NORTH;
            for(int i = 0; i < 4; ++i) {
                gd = DIRECTION(n+i);
                vertexTeam5 u(rev.at(pathInd).x,rev.at(pathInd).y,
                    NORTH,0,NORTH);
                u = addDirectionTeamFive(u,gd);
                if(u.x==rev.at(pathInd+1).x && u.y==rev.at(pathInd+1).y) {
                    ++pathInd;
                    return gd;
                }

            }

        }

        return d;
    }

};


#endif /* RACECARDRIVER_H_ */