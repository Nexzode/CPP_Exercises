#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include <functional>
#include <unordered_map>

// Liste des entitées à construire
std::string desc = R"(Object
Person
Dog
Cat
Tree
House
)";

class Entity
{
public:
    virtual void print() const = 0;
};

class Factory
{
public:
    using Builder = std::function<std::unique_ptr<Entity>()>;

    template <typename TDerivedEntity, typename... Targs>
    void register_entity(std::string id, Targs&&... args)
    {
        _builders.emplace(std::move(id), [&args...]() -> std::unique_ptr<Entity>{
            return std::make_unique<TDerivedEntity>(std::forward<Targs>(args)...);
        });
    }

    std::unique_ptr<Entity> build(const std::string& id) const {
        auto it = _builders.find(id);
        if(it != _builders.end()) {
            return it->second();
         }
        return nullptr;
    } 

private:
    std::unordered_map<std::string, Builder> _builders;
};

class Object : public Entity
{
public:
    void print() const override { std::cout << "Object" << std::endl; }
};

class Tree : public Object
{
public:
    void print() const override { std::cout << "Tree" << std::endl; }
};

class Person : public Entity
{
public:
    explicit Person(std::string name)
        : _name { std::move(name) }
    {}

    void print() const override { std::cout << _name << std::endl; }

    void               set_name(std::string name) { _name = std::move(name); }
    const std::string& get_name() const { return _name; }

private:
    std::string _name;
};

class Animal : public Entity
{
public:
    explicit Animal(std::string species)
        : _species { std::move(species) }
    {}

    void print() const override { std::cout << _species << std::endl; }

private:
    std::string _species;
};

class House : public Object
{
public:
    explicit House(Person& owner)
        : _owner { owner }
    {}

    void print() const override { std::cout << "House owned by " << _owner.get_name() << std::endl; }

private:
    Person& _owner;
};

int main()
{
    Factory factory;
    factory.register_entity<Object>("Object");
    factory.register_entity<Tree>("Tree");
    factory.register_entity<Person>("Person", "Jean");
    factory.register_entity<Animal>("Dog", "cezr");

    std::vector<std::unique_ptr<Entity>> entities;

    std::stringstream s;
    s << desc;
    while (!s.eof())
    {
        std::string e;
        s >> e;

        entities.emplace_back(factory.build(e));
    }

    for (const auto& e : entities)
    {
        if (e != nullptr)
        {
            e->print();
        }
    }

    return 0;
}
