/***
*  Prototype:原型模式
*/

using std::string;

//原型的类型
enum Type {
    PROTOTYPE_1 = 0,
    PROTOTYPE_2
};

//具有克隆能力的类
class Prototype {
protected:
    string prototype_name_;
    float prototype_field_;

public:
    Prototype() {}

    Prototype(string prototype_name)
            : prototype_name_(prototype_name) {
    }

    virtual ~Prototype() {}

    virtual Prototype *Clone() const = 0;

    virtual void Method(float prototype_field) {
        this->prototype_field_ = prototype_field;
        std::cout << "Call Method from " << prototype_name_ << " with field : " << prototype_field << std::endl;
    }
};

/**
 * ConcretePrototype1 是 Prototype 的子类，实现了 Clone 方法
 * 在这个例子中，Prototype 类的所有数据成员都在 Stack 中。
 * 如果您的属性中有 ex: String name_ 的指针，您将需要实现 Copy-Constructor 以确保您有来自 clone 方法的深层副本
 */

class ConcretePrototype1 : public Prototype {
private:
    float concrete_prototype_field1_;

public:
    ConcretePrototype1(string prototype_name, float concrete_prototype_field)
            : Prototype(prototype_name), concrete_prototype_field1_(concrete_prototype_field) {
    }

    /**
     * 请注意，Clone 方法返回一个指向新的 ConcretePrototype1 副本的指针。
     * 因此，客户端（调用 clone 方法）有责任释放该内存。
     * 如果你有智能指针知识，你可能更喜欢在这里使用 unique_pointer。
     */
    Prototype *Clone() const override {
        return new ConcretePrototype1(*this);
    }
};

class ConcretePrototype2 : public Prototype {
private:
    float concrete_prototype_field2_;

public:
    ConcretePrototype2(string prototype_name, float concrete_prototype_field)
            : Prototype(prototype_name), concrete_prototype_field2_(concrete_prototype_field) {
    }

    Prototype *Clone() const override {
        return new ConcretePrototype2(*this);
    }
};

//在 PrototypeFactory中你有两个具体原型，每个具体原型类一个，所以每次你想创建一个子弹，你可以使用现有的并克隆它们。
class PrototypeFactory {
private:
    std::unordered_map<Type, Prototype *, std::hash < int>> prototypes_;

public:
    PrototypeFactory() {
        //有两个具体的模型  每次使用都调用clone方法
        prototypes_[Type::PROTOTYPE_1] = new ConcretePrototype1("PROTOTYPE_1 ", 50.f);
        prototypes_[Type::PROTOTYPE_2] = new ConcretePrototype2("PROTOTYPE_2 ", 60.f);
    }

    //小心释放所有分配的内存。同样，如果您有智能指针知识，最好在这里使用它。
    ~PrototypeFactory() {
        delete prototypes_[Type::PROTOTYPE_1];
        delete prototypes_[Type::PROTOTYPE_2];
    }

    //请注意，您只需指定所需原型的类型，该方法将从具有此类型的对象创建。
    Prototype *CreatePrototype(Type type) {
        return prototypes_[type]->Clone();
    }
};

void Client(PrototypeFactory &prototype_factory) {
    std::cout << "Let's create a Prototype 1\n";

    Prototype *prototype = prototype_factory.CreatePrototype(Type::PROTOTYPE_1);//创建一个类型1的原型
    prototype->Method(90);//调用函数
    delete prototype;

    std::cout << "\n";

    std::cout << "Let's create a Prototype 2 \n";

    prototype = prototype_factory.CreatePrototype(Type::PROTOTYPE_2);
    prototype->Method(10);

    delete prototype;
}

int main() {
    PrototypeFactory *prototype_factory = new PrototypeFactory();
    Client(*prototype_factory);
    delete prototype_factory;

    return 0;
}