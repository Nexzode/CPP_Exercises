#include <unordered_map>

struct Point2D
{
    int x, y;
    Point2D(int x, int y)
    : x(x), y(y)
    {}

    bool operator==(Point2D other) const
    {
        return x == other.x && y == other.y;
    }
};

namespace std {   // il faut se placer dans le bon namespace
    template <>
    struct hash<Point2D>
    {
       std::size_t operator()(const Point2D& p) const
    {
        std::hash<int> hash_fcn;
        return hash_fcn(p.x) ^ hash_fcn(p.y);
    }
    };
}

class Point2dHash
{
public:
    std::size_t operator()(const Point2D& p) const
    {
        std::hash<int> hash_fcn;
        return hash_fcn(p.x) ^ hash_fcn(p.y);
    }


};

class Point2dEqual
{
public:
    bool operator()(const Point2D& p1, const Point2D& p2) const
    {
        return p1.x == p2.x && p1.y == p2.y;
    }
};

enum Content{ Empty, Red, Yellow};

int main()
{
    auto grid = std::unordered_map<Point2D, Content>();
    grid.emplace(Point2D(1,2), Empty);
    grid[Point2D(1,2)];
    return 0;
}