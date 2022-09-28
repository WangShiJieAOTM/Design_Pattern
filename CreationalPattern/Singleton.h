/***
 * Singleton:单例模式
 * 保证一个类只有一个实例,并且提供一个访问该实例的全局节点
*/

//Singleton 类定义了 `GetInstance` 方法，该方法可作为构造函数的替代方法，并允许客户端一遍又一遍地访问此类的同一实例。
class Singleton {
//Singleton 的构造函数应该始终是私有的，以防止使用 `new` 操作符直接调用构造函数。->保证只存在一个实例
protected:
    Singleton(const std::string value) : value_(value) {
    }

    static Singleton *singleton_;

    std::string value_;

public:
    //阻止复制
    Singleton(Singleton &other) = delete;

    void operator=(const Singleton &) = delete;

    //这是控制对单例实例的访问的静态方法。
    //在第一次运行时，它会创建一个单例对象并将其放入静态字段中。在随后的运行中，它返回存储在静态字段中的客户端现有对象。

    static Singleton *GetInstance(const std::string &value);

    //最后，任何单例都应该定义一些可以在其实例上执行的业务逻辑。
    void SomeBusinessLogic() {
        // ...
    }

    std::string value() const {
        return value_;
    }
};

Singleton *Singleton::singleton_ = nullptr;

//静态方法应该在类之外定义。
Singleton *Singleton::GetInstance(const std::string &value) {
    //这是创建实例的方法。 instance = new Singleton 在两个实例线程想要同时访问的情况下是危险的
    //懒汉式↓ 解决这个问题的一个方案是双重检测加锁
    //饿汉式的单例模式在GetInstance外就进行了初始化  在GetInstance中直接返回静态对象
    if (singleton_ == nullptr) {
        singleton_ = new Singleton(value);
    }
    return singleton_;
}

void ThreadFoo() {
    // Following code emulates slow initialization.
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    Singleton *singleton = Singleton::GetInstance("FOO");
    std::cout << singleton->value() << "\n";
}

void ThreadBar() {
    // Following code emulates slow initialization.
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    Singleton *singleton = Singleton::GetInstance("BAR");
    std::cout << singleton->value() << "\n";
}


int main() {
    std::cout << "If you see the same value, then singleton was reused (yay!\n" <<
              "If you see different values, then 2 singletons were created (booo!!)\n\n" <<
              "RESULT:\n";
    std::thread t1(ThreadFoo);
    std::thread t2(ThreadBar);
    t1.join();
    t2.join();

    return 0;
}