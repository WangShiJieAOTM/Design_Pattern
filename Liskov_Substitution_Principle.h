/***
 * L:Liskov Substitution Principle 里氏替换原则
 * 如果一个接口接受一个父类对象为参数,则他也应该在不做任何变更的条件下接受一个子类对象为参数
*/
class Rectangle {
protected:
    double height, width;
public:
    Rectangle(double _height, double _width) : height(_height), width(_width) {}

    double get_height() const { return height; }

    double get_width() const { return width; }

    virtual void set_height(const double _height) { height = _height; }

    virtual void set_width(const double _width) { width = _width; }

    double area() const { return height * width; }
};

class Square : public Rectangle {
public:
    Square(double _size) : Rectangle(_size, _size) {}

    void set_height(const double _height) override {
        height = _width = _height;
    }

    void set_width(const double _width) override {
        height = _width = _width;
    }
};

void process(Rectangle *rect) {
    double w = rect->get_width();
    rect->set_height(1.25);
    cout << "expected area = " << (w * 1.25) << ", got " << rect->area() << endl;
    cout << "actual area = " << rect->area() << endl;
}
/**
 * 传入Rectangle(2,4),输出 expected area = 5,actual area = 5,结果正确
 * 传入Square(4),输出 expected area = 5,actual area = 1.5625,结果错误
 * 出现了子类不能使用父类接口的情况.
*/