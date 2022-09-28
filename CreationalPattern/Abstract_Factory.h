/***
 * Abstract Factory:抽象工厂模式
 * 抽象工厂是一种创建型设计模式,可让你生成一系列相关的对象,而无需指定它们具体的类
*/

//抽象产品类1(鼠标)
class AbstractProductA {
public:
    virtual ~AbstractProductA() {};

    virtual std::string UsefulFunctionA() const = 0;
};

//具体产品类1(苹果鼠标)
class ConcreteProductA1 : public AbstractProductA {
public:
    std::string UsefulFunctionA() const override {
        return "The result of the product A1.";
    }
};

//具体产品类2(戴尔鼠标)
class ConcreteProductA2 : public AbstractProductA {
    std::string UsefulFunctionA() const override {
        return "The result of the product A2.";
    }
};

//抽象产品类2(键盘)
class AbstractProductB {
public:
    virtual ~AbstractProductB() {};

    virtual std::string UsefulFunctionB() const = 0;

 std::string AnotherUsefulFunctionB(const AbstractProductA &collaborator) const = 0;
};

//具体产品类3(苹果键盘)
class ConcreteProductB1 : public AbstractProductB {
public:
    std::string UsefulFunctionB() const override {
        return "The result of the product B1.";
    }
    std::string AnotherUsefulFunctionB(const AbstractProductA &collaborator) const override {
        const std::string result = collaborator.UsefulFunctionA();
        return "The result of the B1 collaborating with ( " + result + " )";
    }
};
//具体产品类4(戴尔键盘)
class ConcreteProductB2 : public AbstractProductB {
public:
    std::string UsefulFunctionB() const override {
        return "The result of the product B2.";
    }
    std::string AnotherUsefulFunctionB(const AbstractProductA &collaborator) const override {
        const std::string result = collaborator.UsefulFunctionA();
        return "The result of the B2 collaborating with ( " + result + " )";
    }
};

//抽象工厂类
class AbstractFactory {
public:
    virtual AbstractProductA *CreateProductA() const = 0;

    virtual AbstractProductB *CreateProductB() const = 0;
};

//具体工厂类1(苹果工厂)
class ConcreteFactory1 : public AbstractFactory {
public:
    AbstractProductA *CreateProductA() const override {
        return new ConcreteProductA1();
    }

    AbstractProductB *CreateProductB() const override {
        return new ConcreteProductB1();
    }
};

//具体工厂类2(戴尔工厂)
class ConcreteFactory2 : public AbstractFactory {
public:
    AbstractProductA *CreateProductA() const override {
        return new ConcreteProductA2();
    }

    AbstractProductB *CreateProductB() const override {
        return new ConcreteProductB2();
    }
};

//客户端代码
void ClientCode(const AbstractFactory &factory) {
    const AbstractProductA *product_a = factory.CreateProductA();
    const AbstractProductB *product_b = factory.CreateProductB();
    std::cout << product_b->UsefulFunctionB() << "\n";
    std::cout << product_b->AnotherUsefulFunctionB(*product_a) << "\n";
    delete product_a;
    delete product_b;
}

int main() {
    std::cout << "Client: Testing client code with the first factory type:\n";
    ConcreteFactory1 *f1 = new ConcreteFactory1();//苹果工厂
    ClientCode(*f1);//客户端代码 只会使用苹果工厂的产品
    delete f1;
    std::cout << std::endl;
    std::cout << "Client: Testing the same client code with the second factory type:\n";
    ConcreteFactory2 *f2 = new ConcreteFactory2();//戴尔工厂
    ClientCode(*f2);//客户端代码 只会使用戴尔工厂的产品
    delete f2;
    return 0;
}