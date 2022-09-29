/***
 * Facade:外观模式
 * 为程序库,框架或其他复杂提供一个简单的接口
*/

//Subsystem可以直接接受来自Facade或客户端的请求。无论如何，对于Subsystem来说，Facade是另一个客户端，它不是Subsystem的一部分。
class Subsystem1 {
public:
    std::string Operation1() const {
        return "Subsystem1: Ready!\n";
    }

    // ...
    std::string OperationN() const {
        return "Subsystem1: Go!\n";
    }
};

//一些Facade可以用于多种Subsystem
class Subsystem2 {
public:
    std::string Operation1() const {
        return "Subsystem2: Get ready!\n";
    }

    // ...
    std::string OperationZ() const {
        return "Subsystem2: Fire!\n";
    }
};

class Facade {
protected:
    Subsystem1 *subsystem1_;
    Subsystem2 *subsystem2_;
    //根据您的应用程序的需要，您可以为 Facade 提供现有的Subsystem对象或强制 Facade 自行创建它们。
public:
    Facade(
            Subsystem1 *subsystem1 = nullptr,
            Subsystem2 *subsystem2 = nullptr) {
        this->subsystem1_ = subsystem1 ?: new Subsystem1;
        this->subsystem2_ = subsystem2 ?: new Subsystem2;
    }

    ~Facade() {
        delete subsystem1_;
        delete subsystem2_;
    }

    std::string Operation() {
        std::string result = "Facade initializes subsystems:\n";
        result += this->subsystem1_->Operation1();
        result += this->subsystem2_->Operation1();
        result += "Facade orders subsystems to perform the action:\n";
        result += this->subsystem1_->OperationN();
        result += this->subsystem2_->OperationZ();
        return result;
    }
};

//客户端代码通过 Facade 提供的简单接口与复杂的Subsystem一起工作。
//当门面管理Subsystem的生命周期时，客户端可能甚至不知道Subsystem的存在。这种方法使您可以控制复杂性。
void ClientCode(Facade *facade) {
    // ...
    std::cout << facade->Operation();
    // ...
}

//客户端代码可能已经创建了一些Subsystem的对象。在这种情况下，可能值得用这些对象初始化 Facade，而不是让 Facade 创建新实例

int main() {
    Subsystem1 *subsystem1 = new Subsystem1;
    Subsystem2 *subsystem2 = new Subsystem2;
    Facade *facade = new Facade(subsystem1, subsystem2);
    ClientCode(facade);

    delete facade;

    return 0;
}

/***
* 就是给两个类套上一个类,然后调用这个类的函数  用户甚至不知道这两类的操作(不关心)
*/