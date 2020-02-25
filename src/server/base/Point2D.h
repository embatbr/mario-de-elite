#pragma once


class Point2D {
    public:
        int x_axis;
        int y_axis;

        Point2D(int x_axis, int y_axis);
        ~Point2D();

        void move(int x_delta, int y_delta);
};
