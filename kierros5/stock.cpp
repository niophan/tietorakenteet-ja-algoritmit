#include <iostream>
#include <queue>
#include <stack>

using namespace std;

struct StockPurchase {
    int price;
    int quantity;
    
    StockPurchase(int p, int q) : price(p), quantity(q) {}
};

// FIFO calculation using Queue
double fifo_calculation() {
    queue<StockPurchase> fifo_queue;
    double total_gain_loss = 0;
    
    cout << "\n=== FIFO (Queue) Method ===" << endl;
    
    // Buy 100 shares in January, April, September at $10, $30, $50 respectively
    cout << "Jan: Buy 100 @ $10" << endl;
    fifo_queue.push(StockPurchase(10, 100));
    
    cout << "Apr: Buy 100 @ $30" << endl;
    fifo_queue.push(StockPurchase(30, 100));

    cout << "Sep: Buy 100 @ $50" << endl;
    fifo_queue.push(StockPurchase(50, 100));
    
    // Sell 100 shares in June at $20
    cout << "\nJun: Sell 100 @ $20" << endl;
    StockPurchase purchase = fifo_queue.front();
    fifo_queue.pop();

    int cost = purchase.quantity * purchase.price;
    int revenue = purchase.quantity * 20;
    int gain = revenue - cost;
        
    cout << "Cost: $" << cost << endl;
    cout << "Revenue: $" << revenue << endl;
    cout << "Gain/Loss: $" << gain << endl;
        
    total_gain_loss += gain;
        
    
    // Sell 100 shares in November at $30
    cout << "\nNov: Sell 100 @ $30" << endl;
    purchase = fifo_queue.front();
    fifo_queue.pop();

    cost = purchase.quantity * purchase.price;
    revenue = purchase.quantity * 30;
    gain = revenue - cost;
        
    cout << "Cost: $" << cost << endl;
    cout << "Revenue: $" << revenue << endl;
    cout << "Gain/Loss: $" << gain << endl;
        
    total_gain_loss += gain;

    cout << "\nRemaining shares in queue: " << purchase.quantity << endl;
    cout << "Total FIFO Gain/Loss: $" << total_gain_loss << endl;
    
    return total_gain_loss;
}

// LIFO calculation using Stack
double lifo_calculation() {
    stack<StockPurchase> lifo_stack;
    double total_gain_loss = 0;
    
    cout << "\n=== LIFO (Stack) Method ===" << endl;
    
    // Buy 100 shares in January, April, September at $10, $30, $50 respectively
    cout << "Jan: Buy 100 @ $10" << endl;
    lifo_stack.push(StockPurchase(10, 100));
    
    cout << "Apr: Buy 100 @ $30" << endl;
    lifo_stack.push(StockPurchase(30, 100));
    
    cout << "Sep: Buy 100 @ $50" << endl;
    lifo_stack.push(StockPurchase(50, 100));
    
    // Sell 100 shares in June at $20
    cout << "\nJun: Sell 100 @ $20" << endl;
    StockPurchase purchase = lifo_stack.top();
    lifo_stack.pop();
        
    int cost = purchase.quantity * purchase.price;
    int revenue = purchase.quantity * 20;
    int gain = revenue - cost;
        
    cout << "Cost: $" << cost << endl;
    cout << "Revenue: $" << revenue << endl;
    cout << "Gain/Loss: $" << gain << endl;
        
    total_gain_loss += gain;
  
    
    // Sell 100 shares in November at $30
    cout << "\nNov: Sell 100 @ $30" << endl;

    purchase = lifo_stack.top();
    lifo_stack.pop();
        
    cost = purchase.quantity * purchase.price;
    revenue = purchase.quantity * 30;
    gain = revenue - cost;
        
    cout << "Cost: $" << cost << endl;
    cout << "Revenue: $" << revenue << endl;
    cout << "Gain/Loss: $" << gain << endl;
        
    total_gain_loss += gain;

    cout << "\nRemaining shares in queue: " << purchase.quantity << endl;
    cout << "Total FIFO Gain/Loss: $" << total_gain_loss << endl;
    
    return total_gain_loss;
}

int main() {    
    double fifo_result = fifo_calculation();
    double lifo_result = lifo_calculation();
    
    cout << "\n=== Summary ===" << endl;
    cout << "FIFO Total Gain/Loss: $" << fifo_result << endl;
    cout << "LIFO Total Gain/Loss: $" << lifo_result << endl;    
    return 0;
}
