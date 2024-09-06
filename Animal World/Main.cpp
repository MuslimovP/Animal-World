#include <iostream>
#include <cstring>

using namespace std;

// Абстрактный класс для травоядных животных
class Herbivore 
{
protected:
    int weight;  // вес травоядного
    bool alive;  // живое ли существо

public:
    Herbivore(int w) : weight(w), alive(true) {}
    virtual ~Herbivore() {}

    virtual void eatGrass() = 0;  // метод кушать траву
    int getWeight() const { return weight; }
    bool isAlive() const { return alive; }
    void die() { alive = false; }
};

// Абстрактный класс для хищников
class Carnivore 
{
protected:
    int power;  // сила хищника

public:
    Carnivore(int p) : power(p) {}
    virtual ~Carnivore() {}

    virtual void eat(Herbivore* herbivore) = 0;  // метод кушать травоядное
    int getPower() const { return power; }
};
// Класс для антилопы Гну
class Wildebeest : public Herbivore 
{
public:
    Wildebeest(int w) : Herbivore(w) {}

    void eatGrass() override 
    {
        if (alive) {
            weight += 10;  // травоядное кушает траву и набирает вес
            cout << "Wildebeest eats grass, weight: " << weight << endl;
        }
    }
};

// Класс для бизона
class Bison : public Herbivore 
{
public:
    Bison(int w) : Herbivore(w) {}

    void eatGrass() override {
        if (alive) {
            weight += 10;  // травоядное кушает траву и набирает вес
            cout << "Bison eats grass, weight: " << weight << endl;
        }
    }
};
// Класс для льва
class Lion : public Carnivore 
{
public:
    Lion(int p) : Carnivore(p) {}

    void eat(Herbivore* herbivore) override {
        if (herbivore->isAlive()) {
            if (power > herbivore->getWeight()) {
                power += 10;  // если сила больше веса травоядного
                herbivore->die();
                cout << "Lion eats herbivore, power: " << power << endl;
            }
            else {
                power -= 10;  // если сила меньше, то теряет силу
                cout << "Lion tried to eat herbivore but failed, power: " << power << endl;
            }
        }
        else {
            cout << "Lion can't eat, herbivore is already dead." << endl;
        }
    }
};

// Класс для волка
class Wolf : public Carnivore 
{
public:
    Wolf(int p) : Carnivore(p) {}

    void eat(Herbivore* herbivore) override 
    {
        if (herbivore->isAlive()) {
            if (power > herbivore->getWeight()) {
                power += 10;  // если сила больше веса травоядного
                herbivore->die();
                cout << "Wolf eats herbivore, power: " << power << endl;
            }
            else {
                power -= 10;  // если сила меньше, то теряет силу
                cout << "Wolf tried to eat herbivore but failed, power: " << power << endl;
            }
        }
        else {
            cout << "Wolf can't eat, herbivore is already dead." << endl;
        }
    }
};
// Абстрактный класс для континентов
class Continent 
{
public:
    virtual Herbivore* createHerbivore() = 0;
    virtual Carnivore* createCarnivore() = 0;
};

// Класс Африка
class Africa : public Continent {
public:
    Herbivore* createHerbivore() override 
    {
        return new Wildebeest(50);  // создаем антилопу Гну
    }

    Carnivore* createCarnivore() override 
    {
        return new Lion(60);  // создаем льва
    }
};

// Класс Северная Америка
class NorthAmerica : public Continent 
{
public:
    Herbivore* createHerbivore() override 
    {
        return new Bison(70);  // создаем бизона
    }

    Carnivore* createCarnivore() override 
    {
        return new Wolf(50);  // создаем волка
    }
};
// Класс для мира животных
class AnimalWorld 
{
private:
    Herbivore* herbivores[2];
    Carnivore* carnivores[2];
    int herbivoreCount;
    int carnivoreCount;

public:
    AnimalWorld(Continent* continent1, Continent* continent2) 
    {
        herbivoreCount = 0;
        carnivoreCount = 0;

        // Создаем по одному травоядному и хищнику для двух континентов
        herbivores[herbivoreCount++] = continent1->createHerbivore();
        carnivores[carnivoreCount++] = continent1->createCarnivore();

        herbivores[herbivoreCount++] = continent2->createHerbivore();
        carnivores[carnivoreCount++] = continent2->createCarnivore();
    }

    ~AnimalWorld() {
        for (int i = 0; i < herbivoreCount; i++) 
        {
            delete herbivores[i];
        }
        for (int i = 0; i < carnivoreCount; i++) 
        {
            delete carnivores[i];
        }
    }

    void mealsHerbivores() 
    {
        for (int i = 0; i < herbivoreCount; i++) 
        {
            herbivores[i]->eatGrass();  // травоядные кушают траву
        }
    }

    void nutritionCarnivores()
    {
        for (int i = 0; i < carnivoreCount; i++) 
        {
            carnivores[i]->eat(herbivores[i]);  // хищники охотятся на травоядных
        }
    }
};
int main() 
{
    // Создаем мир животных в Африке и Северной Америке
    Africa africa;
    NorthAmerica northAmerica;
    AnimalWorld world(&africa, &northAmerica);


    // Травоядные кушают траву
    world.mealsHerbivores();

    // Хищники охотятся на травоядных
    world.nutritionCarnivores();

    return 0;
}
