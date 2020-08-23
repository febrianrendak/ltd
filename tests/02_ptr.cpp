#include "../inc/ltd.h"

using namespace ltd;

int CounterA = 0;

struct Block
{
    int Data;

    Block() {
        Data = 0;
        CounterA++;
    }

    Block(int d) : Data(d) {}

    ~Block() {
        CounterA--; 
    }
};

class test_ptr : test_unit
{
public:
    void setup() 
    {
        this->test("Scoped", [](test_case *tc) -> error {

            tc->test(CounterA == 0, "CounterA initial value is 0");
            {
                ptr<Block> b1 = make_ptr<Block>();
                {
                    ptr<Block> b2 = make_ptr<Block>();
                    b2->Data = 2;

                    tc->test(CounterA == 2, "CounterA should have 2 Block object registered.");
                    tc->test(b2->Data == 2);

                    ptr<Block> b3(std::move(b2));
                    tc->test(CounterA == 2, "CounterA should have 2 Block object registered.");
                    tc->test(b2.is_null(), "b2 should be null");
                }
                b1->Data = 100;
                tc->test(CounterA == 1, "CounterA should return to 1 when b2 is destroyed.");
            }
            tc->test(CounterA == 0, "CounterA should return to 0 when b1 is destroyed.");

            ptr<Block> b4(999);
            tc->test(b4->Data == 999);
            
            return error::no_error;
        });
    }
};

test_ptr t;