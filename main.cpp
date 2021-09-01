#include <iostream>
#include <vector>

using namespace std;

//Создай свою индивидуальную футболку

enum COLOR {
    WHITE,
    BLACK,
    RED,
    GREEN,
    BLUE,
    ORANGE,
    YELLOW,
    PINK,
    GREY,
    PURPLE,
    BROWN
};

enum PICTURE {
    P_NONE,
    P_FLOWERS,
    P_FOX,
    P_CHERRY,
    P_ANIME
};

enum TEXT {
    NONE,
    YES,
    NO,
    LOVE,
    FOREVER,
    I
};

class CreatT_Shirt {
    COLOR color;
public:
    CreatT_Shirt(COLOR color) : color(color) {
    }

    string toString()
    {
        switch (color) {
            case COLOR::WHITE: return "WHITE";
            case COLOR::BLACK: return "BLACK";
            case COLOR::RED: return "RED";
            case COLOR::GREEN:return "GREEN";
            case COLOR::BLUE: return "BLUE";
            case COLOR::ORANGE: return "ORANGE";
            case COLOR::YELLOW: return "YELLOW";
            case COLOR::PINK:return "PINK";
            case COLOR::GREY: return "GREY";
            case COLOR::PURPLE: return "PURPLE";
            case COLOR::BROWN:return "BROWN";
        }

        throw std::logic_error("err");
    }
};

class T_Shirt {
    vector<CreatT_Shirt *> items;
    PICTURE picture;
    TEXT text;

    friend class T_ShirtPictureTextBuilder;
    friend class CostBuilder;

public:
    string toString()
    {
        string s = "Text: ";

        switch (text) {
            case TEXT::YES: s += "Yes"; break;
            case TEXT::NO: s += "No"; break;
            case TEXT::LOVE: s += "Love"; break;
            case TEXT::FOREVER: s += "Forever"; break;
            case TEXT::I: s += "I am a boss"; break;
        }

        for (auto & item : items) {
            s += " | " + item->toString();
        }

        switch (picture) {
            case PICTURE::P_FLOWERS: s += "| P_FLOWERS"; break;
            case PICTURE:: P_FOX: s += "|  P_FOX"; break;
            case PICTURE::P_CHERRY: s += "| P_CHERRY"; break;
            case PICTURE:: P_ANIME: s += "|  P_ANIME"; break;
        }

        return s;
    }
};

class T_ShirtPictureBuild {
protected:
    COLOR color;
    PICTURE picture;

public:
    void addColor(COLOR color) {
        this->color = color;
    }

    void setPicture(PICTURE picture) {
        this->picture = picture;
    }

    virtual T_Shirt* build() = 0;
};

class T_ShirtPictureTextBuilder: public T_ShirtPictureBuild {
public:
    virtual T_Shirt* build() {
        T_Shirt* t_shirt = new T_Shirt();
        t_shirt->text = TEXT::LOVE;
        t_shirt->items.push_back(new CreatT_Shirt(color));
        t_shirt->picture = picture;

        return t_shirt;
    }
};

class CostBuilder: public T_ShirtPictureBuild {
public:
    virtual T_Shirt* build() {
        T_Shirt* t_shirt = new T_Shirt();
        t_shirt->items.push_back(new CreatT_Shirt(YELLOW));
        t_shirt->text = TEXT::I;
        return t_shirt;
    }
};

void userGUI(T_ShirtPictureBuild &builder) {
    builder.addColor(COLOR::BLUE);
    builder.setPicture(PICTURE::P_CHERRY);

    T_Shirt *t_shirt = builder.build();

    cout << "Ваша уникальная футболка: " << t_shirt->toString() << endl;
}

int main() {
    T_ShirtPictureTextBuilder builder1;
    CostBuilder builder2;

    userGUI(builder1);
    userGUI(builder2);
}