/***
 * Composite:组合模式
 * 将对象组合成树形结构,并且能像使用独立对象一样使用他们
*/
#include <algorithm>
#include <iostream>
#include <list>
#include <string>

//Component(组件)抽象类
class Component {
protected:
    Component *parent_;
    //可选地，基础组件可以声明一个接口，用于在树结构中设置和访问组件的父级。它还可以为这些方法提供一些默认实现。
public:
    virtual ~Component() {}

    void SetParent(Component *parent) {
        this->parent_ = parent;
    }

    Component *GetParent() const {
        return this->parent_;
    }

    //在某些情况下，在基础 Component 类中定义子管理操作权是有益的。这样，即使在对象树组装期间，您也不需要向客户端代码公开任何具体的组件类。缺点是这些方法对于叶级组件是空的。
    virtual void Add(Component *component) {}

    virtual void Remove(Component *component) {}

    //您可以提供一种方法，让客户端代码确定组件是否可以继续向下组合。
    virtual bool IsComposite() const {
        return false;
    }

    //基本组件可以实现一些默认行为或将其留给具体类（通过将包含该行为的方法声明为“抽象”）。
    virtual std::string Operation() const = 0;
};

//Leaf 类表示组合的最终对象。一片叶子不能有孩子。通常，实际工作的是 Leaf 对象，而 Composite 对象只委托给它们的子组件。
//叶子组件
class Leaf : public Component {
public:
    std::string Operation() const override {
        return "Leaf";
    }
};

//Composite 类表示可能有子级的复杂组件。通常，复合对象将实际工作委托给它们的子对象，然后“汇总”结果。
class Composite : public Component {
protected:
    std::list<Component *> children_;

public:
    //复合对象可以在其子列表中添加或删除其他组件（简单或复杂）。
    void Add(Component *component) override {
        this->children_.push_back(component);
        component->SetParent(this);
    }

    //请记住，此方法会删除指向列表的指针但不会释放内存，您应该手动执行或更好地使用智能指针。
    void Remove(Component *component) override {
        children_.remove(component);
        component->SetParent(nullptr);
    }

    bool IsComposite() const override {
        return true;
    }

    //Composite 以特定方式执行其主要逻辑。它递归地遍历它的所有孩子，收集并总结他们的结果。
    //由于复合体的孩子将这些调用传递给他们的孩子等等，因此会遍历整个对象树。
    std::string Operation() const override {
        std::string result;
        for (const Component *c : children_) {
            if (c == children_.back()) {
                result += c->Operation();
            } else {
                result += c->Operation() + "+";
            }
        }
        return "Branch(" + result + ")";
    }
};

//客户端代码通过基本接口与所有组件一起工作
void ClientCode(Component *component) {
    // ...
    std::cout << "RESULT: " << component->Operation();
    // ...
}

//由于子管理操作是在 Component 基类中声明的，因此客户端代码可以使用任何组件，无论是简单的还是复杂的，而不依赖于它们的具体类。
//添加为叶子节点
void ClientCode2(Component *component1, Component *component2) {
    // ...
    if (component1->IsComposite()) {
        component1->Add(component2);
    }
    std::cout << "RESULT: " << component1->Operation();
    // ...
}

//这样客户端代码可以支持简单的叶子组件......
int main() {
    Component *simple = new Leaf;
    std::cout << "Client: I've got a simple component:\n";
    ClientCode(simple);
    std::cout << "\n\n";
    /**
     * ...as well as the complex composites.
     */

    Component *tree = new Composite;
    Component *branch1 = new Composite;

    Component *leaf_1 = new Leaf;
    Component *leaf_2 = new Leaf;
    Component *leaf_3 = new Leaf;
    //添加为叶子节点
    branch1->Add(leaf_1);
    branch1->Add(leaf_2);
    Component *branch2 = new Composite;
    branch2->Add(leaf_3);
    //添加为复合体
    tree->Add(branch1);
    tree->Add(branch2);
    std::cout << "Client: Now I've got a composite tree:\n";
    ClientCode(tree);
    std::cout << "\n\n";

    std::cout << "Client: I don't need to check the components classes even when managing the tree:\n";
    ClientCode2(tree, simple);
    std::cout << "\n";

    delete simple;
    delete tree;
    delete branch1;
    delete branch2;
    delete leaf_1;
    delete leaf_2;
    delete leaf_3;

    return 0;
}