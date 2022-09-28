/***
 * D:Dependency Inversion Principle 依赖倒置原则
 * 高层模块不能依赖低层模块，应该令两者都依赖抽象模块
 * 抽象不能依赖实现，实现应该依赖抽象
*/

class AbsBook {
public:
    virtual string Story() = 0;
};

class Book : public AbsBook {
public:
    string Story() override {
        return "西游记";
    }
};

class Book1 : public AbsBook {
public:
    string Story() override {
        return "红楼梦";
    }
};

class Book2 : public AbsBook {
public:
    string Story() override {
        return "三国演义";
    }
};

class Mather {
public:
    void Read(AbsBook *book) {
        cout << book->Story() << endl;
    }
};

void process() {
    Mother *mother = new Mother();
    AbsBook *book = new Book();
    mother->Read(book);

    AbsBook* book1 = new Book1();
    mother->Read(book1);

    AbsBook* book2 = new Book2();
    mother->Read(book2);
}

/**
 * 我们让其他的具体类依附于AbsBook这个抽象类（接口）
 * 这样无论Book里面的方法怎么变化我们的Mother里的方法永远是不变的
 * 将高层和底层的中间用一个抽象类隔开都依赖于中间的抽象抽象层，两个层次怎么改变都不会相互影响
 * 体现了c++的多态性，更好的帮助我们管理代码。
 */
