/***
 * Adapter:适配器模式
 * 使得接口不兼容的对象能够相互合作
*/

//Target 定义了客户端代码使用的特定于域的接口。
class Target {
public:
    virtual ~Target() = default;

    virtual std::string Request() const {
        return "Target: The default target's behavior.";
    }
};

//Adaptee 包含一些有用的行为，但它的接口与现有的客户端代码不兼容。 Adaptee 需要在客户端代码使用它之前进行一些调整。
class Adaptee {
public:
    std::string SpecificRequest() const {
        return ".eetpadA eht fo roivaheb laicepS";
    }
};

//Adapter 使 Adaptee 的接口与 Target 的接口兼容。
class Adapter : public Target {
private:
    Adaptee *adaptee_;

public:
    Adapter(Adaptee *adaptee) : adaptee_(adaptee) {}

    std::string Request() const override {
        std::string to_reverse = this->adaptee_->SpecificRequest();
        std::reverse(to_reverse.begin(), to_reverse.end());
        return "Adapter: (TRANSLATED) " + to_reverse;
    }
};

//客户端代码支持所有遵循 Target 接口的类。
void ClientCode(const Target *target) {
    std::cout << target->Request();
}

int main() {
    std::cout << "Client: I can work just fine with the Target objects:\n";
    Target *target = new Target;
    ClientCode(target);
    std::cout << "\n\n";
    Adaptee *adaptee = new Adaptee;
    std::cout << "Client: The Adaptee class has a weird interface. See, I don't understand it:\n";
    std::cout << "Adaptee: " << adaptee->SpecificRequest();
    std::cout << "\n\n";
    std::cout << "Client: But I can work with it via the Adapter:\n";
    Adapter *adapter = new Adapter(adaptee);//adaptee的接口与target的接口不兼容，所以需要适配器
    ClientCode(adapter);
    std::cout << "\n";

    delete target;
    delete adaptee;
    delete adapter;

    return 0;
}