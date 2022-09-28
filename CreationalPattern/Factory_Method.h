/***
 * Factory Method:工厂方法模式
 * 在父类中提供一个创建对象的接口允许子类决定实例化对象的类型
*/


//抽象产品类(鼠标)
class Product {
public:
    virtual ~Product() {}

    virtual std::string Operation() const = 0;
};

//具体产品类1(苹果鼠标)
class ConcreteProduct1 : public Product {
public:
    std::string Operation() const override {
        return "{Result of the ConcreteProduct1}";
    }
};

//具体产品类2(戴尔鼠标)
class ConcreteProduct2 : public Product {
public:
    std::string Operation() const override {
        return "{Result of the ConcreteProduct2}";
    }
};

/**
 * Creator类声明工厂方法,该方法返回一个Product对象. Creator的子类通常会重写该方法,以便返回不同类型的Product对象
*/

class Creator {
public:
    virtual ~Creator() {};

    virtual Product *FactoryMethod() const = 0;

    std::string SomeOperation() const {
        // Call the factory method to create a Product object.
        Product *product = this->FactoryMethod();
        // Now, use the product.
        std::string result = "Creator: The same creator's code has just worked with " + product->Operation();
        delete product;
        return result;
    }
};

/**
 *  ConcreteCreator1类重写工厂方法以便返回一个ConcreteProduct实例
 */
//具体工厂类1(苹果鼠标工厂)
class ConcreteCreator1 : public Creator {
    /**
     * 注意,尽管这里的返回类型是Product,但实际上返回的是ConcreteProduct1
     * 这正是工厂方法模式的意图
     */
public:
    Product *FactoryMethod() const override {
        return new ConcreteProduct1();
    }
};
//具体工厂类2(戴尔鼠标工厂)
class ConcreteCreator2 : public Creator {
public:
    Product *FactoryMethod() const override {
        return new ConcreteProduct2();
    }
};

/**
 * 传递Creator的子类
 */
void ClientCode(const Creator &creator) {
    // ...
    std::cout << "Client: I'm not aware of the creator's class, but it still works.\n"
              << creator.SomeOperation() << std::endl;
    // ...
}

int main() {
    std::cout << "App: Launched with the ConcreteCreator1.\n";
    Creator *creator = new ConcreteCreator1();//传入苹果鼠标工厂
    ClientCode(*creator);
    std::cout << std::endl;
    std::cout << "App: Launched with the ConcreteCreator2.\n";
    Creator *creator2 = new ConcreteCreator2();//传入戴尔鼠标工厂
    ClientCode(*creator2);

    delete creator;
    delete creator2;
    return 0;
}
