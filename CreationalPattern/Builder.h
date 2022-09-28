/***
 * Builder:建造者模式/生成器模式
*/

/**
 * 当产品非常复杂且需要大量配置时,使用Builder模式才有意义
 */

// 产品类(房子)
class Product1 {
public:
    std::vector <std::string> parts_;

    void ListParts() const {
        std::cout << "Product parts: ";
        for (size_t i = 0; i < parts_.size(); i++) {
            if (parts_[i] == parts_.back()) {
                std::cout << parts_[i];
            } else {
                std::cout << parts_[i] << ", ";
            }
        }
        std::cout << "\n\n";
    }
};


//Builder类用于创建各个产品的各个部件
class Builder {
public:
    virtual ~Builder() {}

    virtual void ProducePartA() const = 0;//普通房子

    virtual void ProducePartB() const = 0;//游泳池

    virtual void ProducePartC() const = 0;//花园
};

//Concrete Builder 类遵循 Builder 接口并提供构建步骤的特定实现。您的程序可能有几种不同的构建器，实现方式不同。
class ConcreteBuilder1 : public Builder {
private:
    Product1 *product;
public:

    ConcreteBuilder1() {
        this->Reset();
    }

    ~ConcreteBuilder1() {
        delete product;
    }

    void Reset() {
        this->product = new Product1();
    }

    //所有生产步骤都使用相同的产品实例。

    void ProducePartA() const override {//普通房子
        this->product->parts_.push_back("PartA1");
    }

    void ProducePartB() const override {//游泳池
        this->product->parts_.push_back("PartB1");
    }

    void ProducePartC() const override {//花园
        this->product->parts_.push_back("PartC1");
    }


    //通常在调用GetProduct之后会创建下一个产品  但是这不是强制的
    //注意:一旦这个函数调用就会创建一个新的产品,这个函数就有义务管理好这个新的产品,为了避免内存泄漏,这个地方是使用智能指针的好选择
    Product1 *GetProduct() {
        Product1 *result = this->product;
        this->Reset();
        return result;
    }
};

//主管(Director)类负责执行构建过程中的各个步骤
class Director {
private:
    Builder *builder;
    //Director与客户端代码传递给它的任何构建器实例一起工作。这样，客户端代码可能会改变新组装产品的最终类型。
public:

    void set_builder(Builder *builder) {
        this->builder = builder;
    }

    //Director 可以使用相同的构建步骤构建多个产品变体。
    void BuildMinimalViableProduct() {
        this->builder->ProducePartA();
    }

    void BuildFullFeaturedProduct() {
        this->builder->ProducePartA();
        this->builder->ProducePartB();
        this->builder->ProducePartC();
    }
};

//客户端代码创建一个构建器对象，将其传递给主管(Director)，然后启动构建过程。最终结果是从构建器对象中检索的
void ClientCode(Director &director) {
    ConcreteBuilder1 *builder = new ConcreteBuilder1();//创建一个builder(房子)的构建器
    director.set_builder(builder);//主管设定builder什么
    std::cout << "Standard basic product:\n";
    director.BuildMinimalViableProduct();//builder 普通房子

    //列出builder现在需要建造的内容
    Product1 *p = builder->GetProduct();
    p->ListParts();
    delete p;

    std::cout << "Standard full featured product:\n";
    director.BuildFullFeaturedProduct();//builder 普通房子+游泳池+花园

    //列出builder现在需要建造的内容
    p = builder->GetProduct();
    p->ListParts();
    delete p;

    //请记住，Builder 模式可以在没有 Director 类的情况下使用。
    std::cout << "Custom product:\n";
    builder->ProducePartA();
    builder->ProducePartC();
    p = builder->GetProduct();
    p->ListParts();
    delete p;

    delete builder;
}

int main() {
    Director *director = new Director();
    ClientCode(*director);
    delete director;
    return 0;
}