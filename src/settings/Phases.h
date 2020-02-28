#pragma once

#include <list>
#include <string>
#include <tuple>
using namespace std;

#include "../base/Object2D.h"


Object2D* load_object(tuple<int, int, int, int> tuple_data, Object2DType object_type) {
    return new Object2D(
        get<0>(tuple_data),
        get<1>(tuple_data),
        get<2>(tuple_data),
        get<3>(tuple_data),
        object_type
    );
}


class Phase {
    protected:
        tuple<int, int, int, int> player_data;
        list<tuple<int, int, int, int>> enemies_data;
        list<tuple<int, int, int, int, Object2DType>> scenario_data;

    public:
        Phase() {}
        ~Phase() {}

        Object2D* load_player() {
            return load_object(this->player_data, OBJECT_PLAYER);
        }

        list<Object2D*> load_enemies() {
            list<Object2D*> enemies;

            for(list<tuple<int, int, int, int>>::iterator it=this->enemies_data.begin();
                it != this->enemies_data.end(); it++) {
                tuple<int, int, int, int> enemy_data = *it;
                Object2D *enemy = load_object(enemy_data, OBJECT_ENEMY);
                enemies.push_back(enemy);
            }

            return enemies;
        }
};


class Phase1: public Phase {
    public:

        Phase1(): Phase() {
            this->player_data = tuple<int, int, int, int>(100, 400, 20, 35);

            this->enemies_data.push_back(tuple<int, int, int, int>{300, 300, 30, 30});
            this->enemies_data.push_back(tuple<int, int, int, int>{500, 300, 30, 30});
            this->enemies_data.push_back(tuple<int, int, int, int>{500, 100, 30, 30});
        }
        ~Phase1() {}
};


Phase load_phase(string name) {
    if(name.compare("1") == 0) {
        return Phase1();
    }

    return Phase();
}
