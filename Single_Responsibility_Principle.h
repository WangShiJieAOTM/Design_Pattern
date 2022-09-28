/***
 * S:Single Responsibility Principle 单一职责原则
 * 每一个类只负责一项职责,因此也就只有一个变化点
 * 如果在一个结构体系中,经常需要在多个类中同步地进行修改,那么通常意味着设计不良
 * 杜绝 "万能类"
*/

class Journal {
public:
    explicit Journal(const std::string &_title) : title(_title) {}

    void add(const std::string &entry);//这是Journal的职责
    void save(const std::string &filename);//NO!!! 这不是Journal的职责
private:
    std::string title;
    std::vector <std::string> entries;
};

/**不良设计:
 * 将日志保存到文件的功能不是Journal的职责,应该由专门的类来实现
 * 如果存在一系列与Journal相似的的类,又存在多种存储方案
 * 则代码必定出现"牵一发而动全身",对存储方案会引起多处代码变动
 */
void Journal::save(const std::string &filename) {
    std::ofstream ofs(filename);
    for (auto &e : entries) {
        ofs << e << std::endl;
    }
}

/**
 * 设计专门的存储类:
 */
class SaveManage {
public:
    void save(const Journal &j, const std::string &filename) {
        std::ofstream ofs(filename);
        for (auto &e : j.entries) {
            ofs << e << std::endl;
        }
    }
};

/**
 * 这样添加一些和Journey相似的需要save功能时,修改SaveManage而不是在那个类中添加save功能
 * 同时对Journey需要添加不同的save行为时(比如上传到云端),也不需要修改Journey类.
 * 修改职责只对这一职责的类做修改,而不会影响其他类
 */
