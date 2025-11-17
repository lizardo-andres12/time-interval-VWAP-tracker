#include <cstdint>
#include <deque>
#include <iostream>
#include <iomanip>


struct Order
{
    std::uint32_t timestamp;
    double price;
    int quantity;
};


int main() 
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cout << std::fixed << std::setprecision(6);

    std::deque<Order> orders;
    double priceByVolume {0};
    int totalVolume {0};

    std::uint32_t windowSize;
    if (!(std::cin >> windowSize))
    {
	std::cerr << "Invalid input format, window size must come first" << '\n';
	return 1;
    }

    std::uint32_t timestamp;
    double price;
    int quantity;

    while (std::cin >> timestamp >> price >> quantity)
    {
	std::uint32_t minTimeForInclusion {timestamp - windowSize};
	
	while (!orders.empty() && orders.front().timestamp <= minTimeForInclusion)
	{
	    const Order& order = orders.front();
	    priceByVolume -= order.price * order.quantity;
	    totalVolume -= order.quantity;
	    orders.pop_front();
	}

	priceByVolume += price * quantity;
	totalVolume += quantity;
	orders.push_back({timestamp, price, quantity});

	std::cout << (priceByVolume / totalVolume) << '\n';
    }

    return 0;
}
