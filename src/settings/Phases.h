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

        list<Object2D*> load_scenario() {
            list<Object2D*> scenario;

            for(list<tuple<int, int, int, int, Object2DType>>::iterator it=this->scenario_data.begin();
                it != this->scenario_data.end(); it++) {
                tuple<int, int, int, int, Object2DType> scenario_object_data = *it;

                Object2D *scenario_object = new Object2D(
                    get<0>(scenario_object_data),
                    get<1>(scenario_object_data),
                    get<2>(scenario_object_data),
                    get<3>(scenario_object_data),
                    get<4>(scenario_object_data)
                );

                scenario.push_back(scenario_object);
            }

            return scenario;
        }
};


class Phase1: public Phase {
    public:

        Phase1(): Phase() {
            this->player_data = tuple<int, int, int, int>(100, 450, 20, 35);

            this->enemies_data.push_back(tuple<int, int, int, int>{300, 300, 30, 30});
            this->enemies_data.push_back(tuple<int, int, int, int>{200, 300, 30, 30});
            this->enemies_data.push_back(tuple<int, int, int, int>{550, 400, 30, 30});
            this->enemies_data.push_back(tuple<int, int, int, int>{500, 100, 30, 30});
            this->enemies_data.push_back(tuple<int, int, int, int>{530, 450, 30, 30});

            this->scenario_data.push_back(
                tuple<int, int, int, int, Object2DType>{320, 475, 600, 0, OBJECT_PLATFORM}
            );
            this->scenario_data.push_back(
                tuple<int, int, int, int, Object2DType>{250, 320, 200, 0, OBJECT_PLATFORM}
            );
            this->scenario_data.push_back(
                tuple<int, int, int, int, Object2DType>{550, 420, 100, 0, OBJECT_PLATFORM}
            );
            this->scenario_data.push_back(
                tuple<int, int, int, int, Object2DType>{500, 120, 200, 0, OBJECT_PLATFORM}
            );
            this->scenario_data.push_back(
                tuple<int, int, int, int, Object2DType>{270, 450, 50, 0, OBJECT_PLATFORM}
            );
            this->scenario_data.push_back(
                tuple<int, int, int, int, Object2DType>{270, 425, 50, 0, OBJECT_PLATFORM}
            );
            this->scenario_data.push_back(
                tuple<int, int, int, int, Object2DType>{270, 400, 50, 0, OBJECT_PLATFORM}
            );
            this->scenario_data.push_back(
                tuple<int, int, int, int, Object2DType>{370, 420, 140, 50, OBJECT_BLOCK}
            );
            this->scenario_data.push_back(
                tuple<int, int, int, int, Object2DType>{340, 385, 5, 20, OBJECT_BLOCK}
            );
            this->scenario_data.push_back(
                tuple<int, int, int, int, Object2DType>{420, 370, 5, 20, OBJECT_BLOCK}
            );
            this->scenario_data.push_back(
                tuple<int, int, int, int, Object2DType>{410, 370, 10, 0, OBJECT_PLATFORM}
            );
            this->scenario_data.push_back(
                tuple<int, int, int, int, Object2DType>{450, 350, 50, 0, OBJECT_PLATFORM}
            );
            this->scenario_data.push_back(
                tuple<int, int, int, int, Object2DType>{70, 455, 10, 40, OBJECT_BLOCK}
            );
            this->scenario_data.push_back(
                tuple<int, int, int, int, Object2DType>{50, 450, 20, 0, OBJECT_PLATFORM}
            );
            this->scenario_data.push_back(
                tuple<int, int, int, int, Object2DType>{80, 450, 10, 0, OBJECT_PLATFORM}
            );
        }
        ~Phase1() {}
};


Phase load_phase(string name) {
    if(name.compare("1") == 0) {
        return Phase1();
    }

    return Phase();
}
