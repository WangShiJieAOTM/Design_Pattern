/***
 * Decorator:装饰器模式
 * 允许你通过将对象放入包含行为的特殊封装对象来为原对象绑定新的行为
*/

//基本 Component 接口定义了可以由装饰器更改的操作。
//通知类
class Component {
public:
    virtual ~Component() {}

    virtual std::string Operation() const = 0;
};

//具体组件提供操作的默认实现。这些类可能有几种变体。
//默认通知类
class ConcreteComponent : public Component {
public:
    std::string Operation() const override {
        return "ConcreteComponent";
    }
};

//基本的 Decorator 类遵循与其他组件相同的接口。
//此类的主要目的是为所有具体装饰器定义包装接口。
//包装代码的默认实现可能包括一个用于存储包装组件的字段以及初始化它的方法。
class Decorator : public Component {
protected:
    Component *component_;

public:
    Decorator(Component *component) : component_(component) {
    }

    //装饰器将所有工作委托给包装的组件。
    std::string Operation() const override {
        return this->component_->Operation();
    }
};

//具体的装饰器调用被包装的对象并以某种方式改变它的结果。
class ConcreteDecoratorA : public Decorator {
//装饰器可以调用操作的父实现，而不是直接调用被包装的对象。这种方法简化了装饰器类的扩展。
public:
    ConcreteDecoratorA(Component *component) : Decorator(component) {
    }

    std::string Operation() const override {
        return "ConcreteDecoratorA(" + Decorator::Operation() + ")";
    }
};

//装饰器可以在调用包装对象之前或之后执行它们的行为。
class ConcreteDecoratorB : public Decorator {
public:
    ConcreteDecoratorB(Component *component) : Decorator(component) {
    }

    std::string Operation() const override {
        return "ConcreteDecoratorB(" + Decorator::Operation() + ")";

        //Component *decorator2 = new ConcreteDecoratorB(decorator1);  这里的Decorator是decorator1
        //然后调用 Component *decorator1 = new ConcreteDecoratorA(simple);
        //DecoratorA的Decorator是simple
    }
};

//客户端代码使用 Component 接口与所有对象一起工作。这样，它就可以独立于它所使用的具体组件类。
void ClientCode(Component *component) {
    // ...
    std::cout << "RESULT: " << component->Operation();
    // ...
}

int main() {
    //这样，客户端代码可以支持两个简单的组件......
    Component *simple = new ConcreteComponent;
    std::cout << "Client: I've got a simple component:\n";
    ClientCode(simple);
    std::cout << "\n\n";
    //输出 RESULT: ConcreteComponent

    //注意装饰器不仅可以包装简单的组件，还可以包装其他装饰器。
    Component *decorator1 = new ConcreteDecoratorA(simple);
    Component *decorator2 = new ConcreteDecoratorB(decorator1);
    std::cout << "Client: Now I've got a decorated component:\n";
    ClientCode(decorator2);
    std::cout << "\n";

    //输出  RESULT: ConcreteDecoratorB(ConcreteDecoratorA(ConcreteComponent))

    delete simple;
    delete decorator1;
    delete decorator2;

    return 0;
}
/***
 * 几个子类的装饰器可以包装同一个组件，从而实现不同的装饰效果。
 * 实现方法:在装饰器类中定义一个指向组件的指针，然后将该指针初始化为指向被包装的组件。
 * 实现成一层一层包装装饰的效果,和套娃一样
*/