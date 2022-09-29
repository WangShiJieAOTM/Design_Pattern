/***
 * Bridge:桥接模式
 * 将一个大类或一组紧密相关的类拆分成两个独立的层次结构,从而使两个层次结构可以独立地扩展.
*/

//实现定义了所有实现类的接口。它不必匹配抽象的接口。
//事实上，这两个接口可以完全不同。通常，实现接口只提供原语操作，而抽象定义基于这些原语的更高级别的操作。
class Implementation {
public:
    virtual ~Implementation() {}

    virtual std::string OperationImplementation() const = 0;
};

//每个具体实现都对应一个特定平台，并使用该平台的 API 实现实现接口。
class ConcreteImplementationA : public Implementation {
public:
    std::string OperationImplementation() const override {
        return "ConcreteImplementationA: Here's the result on the platform A.\n";
    }
};

class ConcreteImplementationB : public Implementation {
public:
    std::string OperationImplementation() const override {
        return "ConcreteImplementationB: Here's the result on the platform B.\n";
    }
};

//Abstraction定义了两个类层次结构的“控制”部分的接口。它维护对实现层次结构对象的引用，并将所有实际工作委托给该对象。
class Abstraction {
protected:
    Implementation *implementation_;

public:
    Abstraction(Implementation *implementation) : implementation_(implementation) {
    }

    virtual ~Abstraction() {
    }

    virtual std::string Operation() const {
        return "Abstraction: Base operation with:\n" +
               this->implementation_->OperationImplementation();
    }
};

//您可以在不更改实现类的情况下扩展抽象。
class ExtendedAbstraction : public Abstraction {
public:
    ExtendedAbstraction(Implementation *implementation) : Abstraction(implementation) {
    }

    std::string Operation() const override {
        return "ExtendedAbstraction: Extended operation with:\n" +
               this->implementation_->OperationImplementation();
    }
};

//除了初始化阶段，抽象对象与特定的实现对象链接，客户端代码应该只依赖于抽象类。这样，客户端代码可以支持任何抽象-实现组合。
void ClientCode(const Abstraction &abstraction) {
    // ...
    std::cout << abstraction.Operation();
    // ...
}

//客户端代码应该能够使用任何预先配置的抽象-实现组合。
int main() {
    Implementation *implementation = new ConcreteImplementationA;//使用ConcreteImplementationA
    Abstraction *abstraction = new Abstraction(implementation);//使用原始的内容
    ClientCode(*abstraction);
    std::cout << std::endl;
    delete implementation;
    delete abstraction;

    implementation = new ConcreteImplementationB;//使用ConcreteImplementationB
    abstraction = new ExtendedAbstraction(implementation);//使用扩展的内容
    ClientCode(*abstraction);

    delete implementation;
    delete abstraction;

    return 0;
}
/**
 * 其实就是增加一个Extension的子类来进行运行期多态
 */

