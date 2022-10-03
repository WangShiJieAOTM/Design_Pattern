/***
 * Template Method:模板方法模式
 * 在超类中定义一个算法的框架,允许子类在不修改结构的情况下重写算法的特定步骤
*/
//抽象基类
class AbstractClass {
public:
    //TemplateMethod()定义了算法的基本骨架(步骤)
    void TemplateMethod() const {
        this->BaseOperation1();
        this->RequiredOperations1();
        this->BaseOperation2();
        this->Hook1();
        this->RequiredOperation2();
        this->BaseOperation3();
        this->Hook2();
    }
//这些操作的基本实现
protected:
    void BaseOperation1() const {
        std::cout << "AbstractClass says: I am doing the bulk of the work\n";
    }

    void BaseOperation2() const {
        std::cout << "AbstractClass says: But I let subclasses override some operations\n";
    }

    void BaseOperation3() const {
        std::cout << "AbstractClass says: But I am doing the bulk of the work anyway\n";
    }
    //这些操作必须在子类中实现
    virtual void RequiredOperations1() const = 0;

    virtual void RequiredOperation2() const = 0;

    //这些hook函数可以在子类中实现,也可以不实现,为算法提供的扩展点
    virtual void Hook1() const {}

    virtual void Hook2() const {}
};

//具体类必须实现基类的所有抽象操作。他们还可以使用默认实现覆盖某些操作。
class ConcreteClass1 : public AbstractClass {
protected:
    void RequiredOperations1() const override {
        std::cout << "ConcreteClass1 says: Implemented Operation1\n";
    }

    void RequiredOperation2() const override {
        std::cout << "ConcreteClass1 says: Implemented Operation2\n";
    }
};

//通常，具体类只覆盖一部分基类的操作。
class ConcreteClass2 : public AbstractClass {
protected:
    void RequiredOperations1() const override {
        std::cout << "ConcreteClass2 says: Implemented Operation1\n";
    }

    void RequiredOperation2() const override {
        std::cout << "ConcreteClass2 says: Implemented Operation2\n";
    }

    void Hook1() const override {
        std::cout << "ConcreteClass2 says: Overridden Hook1\n";
    }
};

//客户端代码调用模板方法来执行算法。客户端代码不必知道它使用的对象的具体类，只要它通过对象的基类的接口使用对象即可。
void ClientCode(AbstractClass *class_) {
    // ...
    class_->TemplateMethod();
    // ...
}

int main() {
    std::cout << "Same client code can work with different subclasses:\n";
    ConcreteClass1 *concreteClass1 = new ConcreteClass1;//具体类1在模板上更改了默认的算法实现
    ClientCode(concreteClass1);
    std::cout << "\n";
    std::cout << "Same client code can work with different subclasses:\n";
    ConcreteClass2 *concreteClass2 = new ConcreteClass2;//具体类2在模板上更改了默认的算法实现
    ClientCode(concreteClass2);
    delete concreteClass1;
    delete concreteClass2;
    return 0;
}