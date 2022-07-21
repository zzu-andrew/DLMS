//
// Created by andrew on 2022/7/12.
//


#include <gtest/gtest.h>
#include <gmock/gmock.h>

class Turtle {
public:
    virtual ~Turtle() = default;
    virtual void PenUp() = 0;
    virtual void PenDown() = 0;
    virtual void Forward(int distance) = 0;
    virtual void Turn(int degrees) = 0;
    virtual void GoTo(int x, int y) = 0;
    virtual int GetX() const = 0;
    virtual int GetY() const = 0;
};



class MockTurtle : public Turtle {
public:
    MOCK_METHOD(void, PenUp, (), (override));
    MOCK_METHOD(void, PenDown, (), (override));
    MOCK_METHOD(void, Forward, (int distance), (override));
    MOCK_METHOD(void, Turn, (int degrees), (override));
    MOCK_METHOD(void, GoTo, (int x, int y), (override));
    MOCK_METHOD(int, GetX, (), (const, override));
    MOCK_METHOD(int, GetY, (), (const, override));

    uint32_t count_;
};


class Painter : public Turtle {
public:
    Painter(MockTurtle *pTurtle) {
        count_ = pTurtle->count_;
    }

    ~Painter() override = default;
    void PenUp() override {
        std::cout << __FUNCTION__ << std::endl;
    }
    void PenDown() override {
        std::cout << __FUNCTION__ << std::endl;
    }
    void Forward(int distance) override {
        std::cout << __FUNCTION__ << std::endl;
    }
    void Turn(int degrees) override {
        std::cout << __FUNCTION__ << std::endl;
    }
    void GoTo(int x, int y) override {
        std::cout << __FUNCTION__ << std::endl;
    }
    int GetX() const override {
        std::cout << __FUNCTION__ << std::endl;
        return 0;
    }

    int GetY() const override {
        std::cout << __FUNCTION__ << std::endl;
        return 0;
    }
    bool DrawCircle(uint32_t x, uint32_t y, uint32_t radius) const {

        return GetX() != 0;
    }

private:
    uint32_t count_;
};



using ::testing::AtLeast;                         // #1
using ::testing::Return;

TEST(PainterTest, CanDrawSomething) {
    MockTurtle turtle;                              // #2
    EXPECT_CALL(turtle, GetX()).Times(AtLeast(1)).WillRepeatedly(Return(1));

    Painter painter(&turtle);                       // #4

    EXPECT_TRUE(painter.DrawCircle(0, 0, 10));      // #5
}


int main(int argc, char **argv) {




    return 0;
}






