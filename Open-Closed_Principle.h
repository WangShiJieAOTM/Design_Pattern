/***
 * O:Open-Closed Principle 开放封闭原则
 * 对拓展开放,对修改封闭
 * 对于已经编译好的模块不允许再更改(然后进入重新编译,测试的循环),但允许添加新的模块,从而只需要重新编译新添加的模块然后将其链接进系统
*/

enum class Color {
    Red, Green, Blue
};
enum class Size {
    Small, Medium, Large
};
//一个以颜色和尺寸区分的产品
struct Product {
    std::string name;
    Color color;
    Size size;
};

//产品筛选器
class ProductFilter {
public:
    using Items = std::vector<Product *>;

    //按颜色筛选
    Items by_color(Item items, Color color) {
        Items result;
        for (auto &i:items) {
            if (i.color == color)
                result.push_back(i);
        }
        return result;
    }

    //按尺寸筛选
    Items by_size(Item items, Size size) {
        Items result;
        for (auto &i:items) {
            if (i.size == size)
                result.push_back(i);
        }
        return result;
    }

    //按颜色和尺寸筛选
    Items by_color_and_size(Item items, Color color, Size size) {
        Items result;
        for (auto &i:items) {
            if (i.color == color && i.size == size)
                result.push_back(i);
        }
        return result;
    }

    //按颜色或尺寸筛选
    Items by_color_or_size(Item items, Color color, Size size) {
        Items result;
        for (auto &i:items) {
            if (i.color == color || i.size == size)
                result.push_back(i);
        }
        return result;
    }
};

/**
* 上面的代码的问题是每次更改筛选条件都需要修改ProductFilter类,然后重新编译测试,再次修改则需要再次编译测试,以此类推
*/

/**
 * 新的产品筛选器:
 * 首先将每一种筛选方案设计为抽象基类的子类
*/
class ProductSpecification {
public:
    virtual bool is_satisfied(Product *item) = 0;//纯虚函数,提供统一不变的接口,并将真正的匹配推迟到子类
};

class ColorSpecification : public ProductSpecification {
private:
    Color color;
public:
    explicit ColorSpecification(Color _color) : color(_color) {}

    bool is_satisfied(Product *item) override {
        return item->color == color;
    }
};

class SizeSpecification : public ProductSpecification {
private:
    Size size;
public:
    explicit SizeSpecification(Size _size) : size(_size) {}

    bool is_satisfied(Product *item) override {
        return item->size == size;
    }
};

class ColorAndSizeSpecification : public ProductSpecification {
private:
    Color color;
    Size size;
public:
    ColorAndSizeSpecification(Color _color, Size _size) : color(_color), size(_size) {}

    bool is_satisfied(Product *item) override {
        return item->color == color && item->size == size;
    }
};

class ColorOrSizeSpecification : public ProductSpecification {
private:
    Color color;
    Size size;
public:
    ColorOrSizeSpecification(Color _color, Size _size) : color(_color), size(_size) {}

    bool is_satisfied(Product *item) override {
        return item->color == color || item->size == size;
    }
};

/**
 * 注意:以上每一个子类都在一个单独的模块内分别编译
 * 如果需要别的筛选方案,只需要添加一个新的子类,然后重新编译即可
*/

class NewProductFilter {
public:
    Items filter(Items items, ProductSpecification &spec) {
        Items result;
        for (auto &i:items) {
            if (spec.is_satisfied(i))//通过同一个接口is_satisfied()来进行不同的筛选
                result.push_back(i);
        }
        return result;
    }
};

/**
* 筛选器的使用:
*/
Product apple{"Apple", Color::Green, Size::Small};
Product tree{"Tree", Color::Green, Size::Large};
Product house{"House", Color::Blue, Size::Large};
Product car{"Car", Color::Red, Size::Medium};

vector<Product *> items{&apple, &tree, &house, &car};
NewProductFilter pl;
ColorSpecification green(Color::Green);
SizeSpecification small(Size::Small);
auto green_item = pf.filter(items, green);
auto small_item = pf.filter(items, small);
