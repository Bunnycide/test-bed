#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
    // create a JSON number
    json value = 17;

    // explicitly getting pointers
    auto p1 = value.template get<const json::number_integer_t*>();
    auto p2 = value.template get<json::number_integer_t*>();
    auto p3 = value.template get<json::number_integer_t* const>();
    auto p4 = value.template get<const json::number_integer_t* const>();
    auto p5 = value.template get<json::number_float_t*>();

    // print the pointees
    std::cout << *p1 << ' ' << *p2 << ' ' << *p3 << ' ' << *p4 << '\n';
    std::cout << std::boolalpha << (p5 == nullptr) << '\n';
}
