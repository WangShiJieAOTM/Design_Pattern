/***
 * Flyweight:享元模式
 * 摒弃了在每一个对象中保存所有数据的方式
 * 通过共享多个对象所共有的相同状态,让你能在有限的内存容量后载入更多对象
*/

//享元设计模式意图:
//通过在多个对象之间共享状态的公共部分，而不是将所有数据保留在每个对象中，让您将更多对象放入可用的 RAM 量。
struct SharedState {
    std::string brand_;
    std::string model_;
    std::string color_;

    SharedState(const std::string &brand, const std::string &model, const std::string &color)
            : brand_(brand), model_(model), color_(color) {
    }

    friend std::ostream &operator<<(std::ostream &os, const SharedState &ss) {
        return os << "[ " << ss.brand_ << " , " << ss.model_ << " , " << ss.color_ << " ]";
    }
};

struct UniqueState {
    std::string owner_;
    std::string plates_;

    UniqueState(const std::string &owner, const std::string &plates)
            : owner_(owner), plates_(plates) {
    }

    friend std::ostream &operator<<(std::ostream &os, const UniqueState &us) {
        return os << "[ " << us.owner_ << " , " << us.plates_ << " ]";
    }
};

//Flyweight 存储属于多个真实业务实体的公共部分状态（也称为内在状态）。享元通过其方法参数接受状态的其余部分（外部状态，每个实体唯一）。
class Flyweight {
private:
    SharedState *shared_state_;

public:
    Flyweight(const SharedState *shared_state) : shared_state_(new SharedState(*shared_state)) {
    }

    Flyweight(const Flyweight &other) : shared_state_(new SharedState(*other.shared_state_)) {
    }

    ~Flyweight() {
        delete shared_state_;
    }

    SharedState *shared_state() const {
        return shared_state_;
    }

    //接受非共享变量操作
    void Operation(const UniqueState &unique_state) const {
        std::cout << "Flyweight: Displaying shared (" << *shared_state_ << ") and unique (" << unique_state
                  << ") state.\n";
    }
};

//Flyweight Factory 创建和管理 Flyweight 对象。
//它确保正确共享享元。当客户端请求一个享元时，工厂要么返回一个现有实例，要么创建一个新实例（如果它尚不存在）
class FlyweightFactory {
private:
    std::unordered_map <std::string, Flyweight> flyweights_;

    //返回给定状态的享元的字符串哈希。
    std::string GetKey(const SharedState &ss) const {
        return ss.brand_ + "_" + ss.model_ + "_" + ss.color_;
    }

public:
    FlyweightFactory(std::initializer_list <SharedState> share_states) {
        for (const SharedState &ss : share_states) {
            this->flyweights_.insert(std::make_pair<std::string, Flyweight>(this->GetKey(ss), Flyweight(&ss)));
        }
    }

    //返回具有给定状态的现有享元或创建新享元。
    Flyweight GetFlyweight(const SharedState &shared_state) {
        std::string key = this->GetKey(shared_state);
        if (this->flyweights_.find(key) == this->flyweights_.end()) {
            std::cout << "FlyweightFactory: Can't find a flyweight, creating new one.\n";
            this->flyweights_.insert(std::make_pair(key, Flyweight(&shared_state)));
        } else {
            std::cout << "FlyweightFactory: Reusing existing flyweight.\n";
        }
        return this->flyweights_.at(key);
    }

    void ListFlyweights() const {
        size_t count = this->flyweights_.size();
        std::cout << "\nFlyweightFactory: I have " << count << " flyweights:\n";
        for (std::pair <std::string, Flyweight> pair : this->flyweights_) {
            std::cout << pair.first << "\n";
        }
    }
};

//添加进数据库
void AddCarToPoliceDatabase(
        FlyweightFactory &ff, const std::string &plates, const std::string &owner,
        const std::string &brand, const std::string &model, const std::string &color) {
    std::cout << "\nClient: Adding a car to database.\n";
    const Flyweight &flyweight = ff.GetFlyweight({brand, model, color});//在哈希表中搜索出flyweight(共享资源)之后就可以使用对应的方法
    //比如给xxx 牌xxx型号xxx颜色的车的车主进行操作

    //客户端代码存储或计算外部状态并将其传递给享元的方法。
    flyweight.Operation({owner, plates});
}

//客户端代码通常会在应用程序的初始化阶段创建一堆预先填充的享元。

int main() {
    FlyweightFactory *factory = new FlyweightFactory({{"Chevrolet",     "Camaro2018", "pink"},
                                                      {"Mercedes Benz", "C300",       "black"},
                                                      {"Mercedes Benz", "C500",       "red"},
                                                      {"BMW",           "M5",         "red"},
                                                      {"BMW",           "X6",         "white"}});
    factory->ListFlyweights();

    AddCarToPoliceDatabase(*factory,
                           "CL234IR",
                           "James Doe",
                           "BMW",
                           "M5",
                           "red");

    AddCarToPoliceDatabase(*factory,
                           "CL234IR",
                           "James Doe",
                           "BMW",
                           "X1",
                           "red");
    factory->ListFlyweights();
    delete factory;

    return 0;
}