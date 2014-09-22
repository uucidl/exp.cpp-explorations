#include <vector>
#include <string>

struct A
{
        std::string name;
};

struct B
{
        std::string name;
        std::vector<A> otherNames;
};

std::string extractor(A value)
{
        return value.name;
}

size_t extractor2(A value, B collection)
{
        size_t i = 0;
        for (auto const &element : collection.otherNames) {
                if (element.name == value.name) {
                        break;
                }
                i++;
        }

        return i;
}

void test_initializer_lists()
{
        auto value = extractor({ "Hello, World" });
        printf("should be a greeting: %s\n", value.c_str());

        auto index = extractor2(
            { "b" }, { "collection", { { "a" }, { "b" }, { "c" } } });
        printf("should be 1: %lu\n", index);
}

int main()
{
        test_initializer_lists();
}
