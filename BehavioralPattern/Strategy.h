/***
 * Strategy:策略模式
 * 定义一系列算法,并将每种算法分别放入独立的类中,以使算法对象能够相互替换
*/

//Strategy声明了某些算法的所有支持版本的通用操作。Context使用这个接口来调用由Concrete Strategy定义的算法。
class Strategy {
public:
    virtual ~Strategy() = default;

    virtual std::string doAlgorithm(std::string_view data) const = 0;
};

//Context 定义了需要的接口
class Context {
//Context保持对Strategy对象之一的引用。Context不知道Strategy的具体类别。它应该通过策略界面与所有策略一起工作。
private:
    std::unique_ptr <Strategy> strategy_;
public:
    explicit Context(std::unique_ptr <Strategy> &&strategy = {}) : strategy_(std::move(strategy)) {
    }

    void set_strategy(std::unique_ptr <Strategy> &&strategy) {
        strategy_ = std::move(strategy);
    }

    void doSomeBusinessLogic() const {
        if (strategy_) {
            std::cout << "Context: Sorting data using the strategy (not sure how it'll do it)\n";
            std::string result = strategy_->doAlgorithm("aecbd");
            std::cout << result << "\n";
        } else {
            std::cout << "Context: Strategy isn't set\n";
        }
    }
};

//Concrete Strategy 定义了具体的算法
class ConcreteStrategyA : public Strategy {
public:
    std::string doAlgorithm(std::string_view data) const override {
        std::string result(data);
        std::sort(std::begin(result), std::end(result));

        return result;
    }
};

class ConcreteStrategyB : public Strategy {
    std::string doAlgorithm(std::string_view data) const override {
        std::string result(data);
        std::sort(std::begin(result), std::end(result), std::greater<>());

        return result;
    }
};

void clientCode() {
    Context context(std::make_unique<ConcreteStrategyA>());//设置上下文的策略
    std::cout << "Client: Strategy is set to normal sorting.\n";
    context.doSomeBusinessLogic();
    std::cout << "\n";
    std::cout << "Client: Strategy is set to reverse sorting.\n";
    context.set_strategy(std::make_unique<ConcreteStrategyB>());
    context.doSomeBusinessLogic();
}

int main() {
    clientCode();
    return 0;
}