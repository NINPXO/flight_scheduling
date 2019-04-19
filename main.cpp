#include <bits/stdc++.h>
#include<fstream>
#include <string>
using namespace std;
class FlightData
{
    string origin;
    string destination;
    double cost;
    double time;

public:
    FlightData();
    FlightData(string,string, double, double);
    string getOrigin();
    void setOrigin(string);
    string getDestination();
    void setDestination(string);
    double getCost();
    void setCost(double);
    double getTime();
    void setTime(double);
    FlightData& operator=(const FlightData &);
    FlightData(const FlightData &);
};
FlightData::FlightData()
{
    setOrigin("");
    setDestination("");
    setCost(1);
    setTime(1);
}
FlightData::FlightData(string o,string d, double c, double t)
{
    setOrigin(o);
    setDestination(d);
    setCost(c);
    setTime(t);
}

string FlightData::getOrigin()
{
    return origin;
}

void FlightData::setOrigin(string o)
{
    origin = o;
}

string FlightData::getDestination()
{
    return destination;
}

void FlightData::setDestination(string d)
{
    destination = d;
}

double FlightData::getCost()
{
    return cost;
}

void FlightData::setCost(double c)
{
    if(c >= 0)
        cost = c;
    else
        cout << "Error: Invalid cost\n";
}

double FlightData::getTime()
{
    return time;
}

void FlightData::setTime(double t)
{
    if(t > 0)
        time = t;
    else
        cout << "Error: Invalid time\n";
}

FlightData& FlightData::operator=(const FlightData &arg)
{
    setOrigin(arg.origin);
    setDestination(arg.destination);
    setCost(arg.cost);
    setTime(arg.time);
    return *this;
}

FlightData::FlightData(const FlightData &arg)
{
    *this = arg;
}

template <class T>
class Node
{
    T data;
    Node<T>* next;

public:
    Node() : next(NULL) {}
    Node(T d) : data(d), next(NULL) {}
    void setData(T x)
    {
        data = x;
    }
    T getData()
    {
        return data;
    }
    template<class Type> friend class LinkedList;
    template<class Type> friend class AdjacencyList;
    template<class Type> friend class Stack;
    friend class FlightPlanner;
};

template <class T>
class LinkedList
{
    Node<T>* front;

public:
    LinkedList() : front(NULL) {}
    void push_front(T val)
    {
        Node<T>* x = new Node<T>;
        x->data = val;
        x->next = front;
        front = x;
    }
    void push_back(T val)
    {
        Node<T>* curr = front;
        if(front == NULL)
        {
            front = new Node<T> (val);
        }
        else{
            while(curr->next != NULL)
            {
                curr = curr->next;
            }
            curr->next = new Node<T> (val);
        }
    }
    T pop_front()
    {
        T temp = front->data;
        front = front->next;
        return temp;
    }
    void print()
    {
        Node<T>* curr = front;
        while(curr != NULL)
        {
            cout << curr->data.getDestination() << " ";
            curr = curr->next;
        }
    }

    template<class Type> friend class AdjacencyList;
    template<class Type> friend class Stack;
    friend class FlightPlanner;
};

template <class T>
class Stack
{
    LinkedList<T> elements;
    T top;

public:
    Stack(){}
    bool isEmpty()
    {
        return elements.front == NULL;
    }
    T getTop()
    {
        return top;
    }
    void push(T val)
    {
        elements.push_front(val);
        top = val;
    }
    T pop()
    {
        T returnValue;
        if(!isEmpty())
        {
            returnValue = elements.pop_front();
            if(elements.front != 0)
            {
                top = elements.front->data;
            }
            return returnValue;
        }
        cout << "Error: Attempt to pop from empty stack\n";
        return returnValue;
    }
};

template <class T>
class AdjacencyList
{
    LinkedList<LinkedList<T> > values;
public:
    AdjacencyList(){}
    void insert(FlightData flight)
    {
        Node<LinkedList<T> >* curr = values.front;
        if(values.front == NULL)
        {
            LinkedList<FlightData> temp;
            temp.push_back(flight);
            values.push_back(temp);
        }
        else
        {
            while(curr != NULL)
            {
                if(curr->data.front->data.getOrigin() == flight.getOrigin())
                {
                    curr->data.push_back(flight);
                    break;
                }
                curr = curr->next;
            }
            if(curr == NULL)
            {
                LinkedList<FlightData> temp;
                temp.push_back(flight);
                values.push_back(temp);
            }
        }
    }
    LinkedList<FlightData> getOriginCityList(string cityName)
    {
        Node<LinkedList<T> >* curr = values.front;
        while(curr != NULL)
        {
            if(curr->data.front->data.getOrigin() == cityName)
            {
                return curr->data;
            }
            curr = curr->next;
        }
        if(curr == NULL)
        {
            LinkedList<FlightData> empty;
            return empty;
        }
    }
    void print()
    {
        Node<LinkedList<T> >* curr = values.front;
        while(curr != NULL)
        {
            cout << curr->data.front->data.getOrigin() << " = ";
            curr->data.print();
            cout << "\n";
            curr = curr->next;
        }
    }
};

template <class T>
class Vector
{
public:
    Vector()
    {
        size = 0;
        capacity = CAPACITY_INCREMENT;
        data = new T[capacity];
    }
    int getSize()
    {
        return size;
    }
    int getCapacity()
    {
        return capacity;
    }
    bool isEmpty()
    {
        return size == 0;
    }
    void push_back(T value)
    {
        resize(0);
        data[size++] = value;
    }

    void insert(int loc, T value)
    {
        while(loc >= capacity || size==capacity)
        {
            resize(loc);
        }
        shiftRight(loc);
        data[loc] = value;
    }

    void shiftRight(int loc)
    {
        for(int i=size-1; i>=loc; i--)
        {
            data[i+1] = data[i];
        }
        size++;
    }

    void sortRange(int start, int end)
    {
        for(int j=0; j<end-start; j++)
        {
            for(int i=start; i<end; i++)
            {
                if(data[i] > data[i+1])
                {
                    T temp = data[i];
                    data[i] = data[i+1];
                    data[i+1] = temp;
                }
            }
        }
    }
    void removeAt(int loc)
    {
        if(validIndex(loc))
        {
            for(int i=loc; i<size-1; i++)
            {
                data[i] = data[i+1];
            }
            size--;
        }
    }

    T& operator[](int loc)
    {
        if(validIndex(loc))
            return data[loc];
    }

    int getLength(int index)
    {
        T number = data[index];
        int numDigits = 0;
        if(number==0)
        {
            numDigits++;
        }
        while(number)
        {
            number /= 10;
            numDigits++;
        }
        return numDigits;
    }
    Vector(const Vector& arg)
    {
        capacity = arg.capacity;
        size = arg.size;
        data = new T[size];
        for(int i=0; i<size; i++)
        {
            data[i] = arg.data[i];
        }
    }
    Vector& operator=(const Vector& arg)
    {
        delete[] data;
        capacity = arg.capacity;
        size = arg.size;
        data = new T[size];
        for(int i=0; i<size; i++)
        {
            data[i] = arg.data[i];
        }
        return *this;
    }
    void print()
    {
        for(int i=0; i<size; i++)
        {
            cout << "[" << i << "]: " << data[i] << "\n";
        }
    }

    bool validIndex(int loc)
    {
        if(loc>=0 && loc<size)
            return true;
        else
        {
            cout << "Vector index out of bounds\n";
            return false;
        }
    }
private:
    T* data;
    int size;
    int capacity;
    const int CAPACITY_INCREMENT = 10;
    void resize(int loc)
    {
        if(size==capacity || loc>=capacity)
        {
            T* tempData = new T[capacity+CAPACITY_INCREMENT];
            for(int i=0; i<size; i++)
                tempData[i] = data[i];
            delete[] data;
            data = tempData;
            capacity+=CAPACITY_INCREMENT;
        }

        else if(size<capacity-CAPACITY_INCREMENT)
        {
            T* tempData = new T[capacity-CAPACITY_INCREMENT];
            for(int i=0; i<size; i++)
                tempData[i] = data[i];
            delete[] data;
            data = tempData;
            capacity-=CAPACITY_INCREMENT;
        }
    }
};

class FlightPlan
{
private:
    string origin;
    string destination;
    string sortType;

public:
    FlightPlan(string, string, string);
    string getOrigin();
    void setOrigin(string);
    string getDestination();
    void setDestination(string);
    string getSortType();
    void setSortType(string);
};
FlightPlan::FlightPlan(string o, string d, string st)
{
    setOrigin(o);
    setDestination(d);
    setSortType(st);
}

string FlightPlan::getOrigin()
{
    return origin;
}

void FlightPlan::setOrigin(string o)
{
    origin = o;
}

string FlightPlan::getDestination()
{
    return destination;
}

void FlightPlan::setDestination(string d)
{
    destination = d;
}

string FlightPlan::getSortType()
{
    return sortType;
}

void FlightPlan::setSortType(string st)
{
    if(st == "C" || st == "T")
        sortType = st;
    else
        cout << "Error: Invalid sort type\n";
}


class FlightRoute
{
private:
    Vector<string> cities;
    double totalCost;
    double totalTime;

public:
    FlightRoute();
    void addCity(string);
    void setTotalCost(double);
    double getTotalCost();
    void setTotalTime(double);
    double getTotalTime();
    void print(int, ofstream &);
};
FlightRoute::FlightRoute()
{
    totalCost = 0;
    totalTime = 0;
}

void FlightRoute::addCity(string cityName)
{
    cities.push_back(cityName);
}

void FlightRoute::setTotalCost(double tc)
{
    if(tc > 0)
        totalCost = tc;
    else
        cout << "Invalid total cost\n";
}

double FlightRoute::getTotalCost()
{
    return totalCost;
}

void FlightRoute::setTotalTime(double tt)
{
    if(tt > 0)
        totalTime = tt;
    else
        cout << "Invalid total time\n";
}

double FlightRoute::getTotalTime()
{
    return totalTime;
}

void FlightRoute::print(int pathNumber, ofstream &outFile)
{
    outFile << "Path " << pathNumber << ": ";
    for(int i=0; i<cities.getSize()-1; i++)
    {
        outFile << cities[i] << " -> ";
    }
    outFile << cities[cities.getSize()-1] << ". Time: " << fixed << setprecision(0)
         << totalTime << " Cost: " << fixed << setprecision(2) << totalCost << "\n";
}


class FlightPlanner
{
    ifstream inFlightData;
    ifstream inFlightPlans;
    ofstream outFlightInfo;
    AdjacencyList<FlightData> flights;
    int flightNumber;
    Vector<Stack<Node<FlightData>* > > findRoutes(FlightPlan);
    bool isCityOnStack(Stack<Node<FlightData>* >, string);
    Vector<FlightRoute> translateRoutes(Vector<Stack<Node<FlightData>* > >);
    Vector<FlightRoute> sortRoutes(Vector<FlightRoute>, string);
    void outputRoute(Vector<FlightRoute>, FlightPlan);
public:
    FlightPlanner();
    void readFlightData(string);
    void readFlightPlans(string);
    void openOutputFile(string);
    void closeFiles();
};
FlightPlanner::FlightPlanner()
{
    flightNumber = 1;
}

void FlightPlanner::readFlightData(string fileName)
{
    inFlightData.open("data.txt");
    if(!inFlightData)
    {
        cout << "Flight Data file not opened correctly";
        exit(EXIT_FAILURE);
    }
    string line;
    getline(inFlightData, line);
    int numTokens = stoi(line);

    string origin, destination;
    double cost, time;
    for(int i=0; i<numTokens; i++)
    {
        getline(inFlightData, origin, '|');
        getline(inFlightData, destination, '|');
        getline(inFlightData, line, '|');
        cost = stoi(line);
        getline(inFlightData, line, '\n');
        time = stoi(line);
        FlightData forward(origin, destination, cost, time);
        flights.insert(forward);
        FlightData backward(destination, origin, cost, time);
        flights.insert(backward);
    }
}

void FlightPlanner::readFlightPlans(string fileName)
{
    inFlightPlans.open("plans.txt");
    if(!inFlightPlans)
    {
        cout << "Flight Plans file not opened correctly";
        exit(EXIT_FAILURE);
    }
    string line;
    getline(inFlightPlans, line);
    int numTokens = stoi(line);

    string origin, destination, sortType;
    for(int i=0; i<numTokens; i++)
    {
        getline(inFlightPlans, origin, '|');
        getline(inFlightPlans, destination, '|');
        getline(inFlightPlans, sortType, '\n');
        if(sortType.length() > 1) {
            sortType = sortType[0];
        }
        FlightPlan fp(origin, destination, sortType);
        Vector<Stack<Node<FlightData>* > > currStacks = findRoutes(fp);
        Vector<FlightRoute> currentRoute = translateRoutes(currStacks);
        currentRoute = sortRoutes(currentRoute, sortType);
        outputRoute(currentRoute, fp);
    }
}

Vector<Stack<Node<FlightData>* > > FlightPlanner::findRoutes(FlightPlan plan)
{
    Vector<Stack<Node<FlightData>* > > currStacks;
    Stack<LinkedList<FlightData> > routeStack;
    routeStack.push(flights.getOriginCityList(plan.getOrigin()));
    Stack<Node<FlightData>*> currs;
    Node<FlightData> *curr = routeStack.getTop().front;

    do{
        if(curr == NULL)
        {
            bool allRoutesFound = false;
            while(curr == NULL)
            {
                routeStack.pop();
                if(routeStack.isEmpty())
                {
                    allRoutesFound = true;
                    break;
                }
                curr = currs.pop();
                curr = curr->next;
                while(curr != NULL && isCityOnStack(currs, curr->data.getDestination()))
                {
                    curr = curr->next;
                }
            }
            if(allRoutesFound)
                break;
        }
        if(curr->data.getDestination() == plan.getDestination())
        {
            currs.push(curr);
            currStacks.push_back(currs);
            currs.pop();
            curr = curr->next;
            while(curr != NULL && isCityOnStack(currs, curr->data.getDestination()))
            {
                curr = curr->next;
            }
        }
        if(curr != NULL)
        {
            currs.push(curr);
            routeStack.push(flights.getOriginCityList(curr->data.getDestination()));
            curr = routeStack.getTop().front;
            while(curr != NULL && isCityOnStack(currs, curr->data.getDestination()))
            {
                curr = curr->next;
            }
        }
    }while(true);

    return currStacks;
}

bool FlightPlanner::isCityOnStack(Stack<Node<FlightData>*> stack, string city)
{
    Node<FlightData>* top = NULL;
    while(!stack.isEmpty())
    {
        top = stack.pop();
        if(top->data.getOrigin() == city || top->data.getDestination() == city)
            return true;
    }
    return false;
}

Vector<FlightRoute> FlightPlanner::translateRoutes(Vector<Stack<Node<FlightData>* > > currStacks)
{
    Stack<FlightData> flightStack;
    Vector<FlightRoute> flightRouteVect;
    for(int i=0; i < currStacks.getSize(); i++)
    {
        while(!currStacks[i].isEmpty())
        {
            Node<FlightData>* current = currStacks[i].pop();
            flightStack.push(current->data);
        }
        FlightRoute flightRoute;
        int timeSum = 0;
        int costSum = 0;
        FlightData flight = flightStack.pop();
        flightRoute.addCity(flight.getOrigin());
        flightRoute.addCity(flight.getDestination());
        costSum += flight.getCost();
        timeSum += flight.getTime();
        while(!flightStack.isEmpty())
        {
            flight = flightStack.pop();
            flightRoute.addCity(flight.getDestination());
            costSum += flight.getCost();
            timeSum += flight.getTime();
        }
        flightRoute.setTotalCost(costSum);
        flightRoute.setTotalTime(timeSum);
        flightRouteVect.push_back(flightRoute);
    }
    return flightRouteVect;
}

Vector<FlightRoute> FlightPlanner::sortRoutes(Vector<FlightRoute> routeVect, string sortType)
{
    Vector<FlightRoute> flightRouteVect;
    if(sortType == "T")
    {
        int minIndex;
        for(int i=0; i<routeVect.getSize()-1; i++)
        {
            minIndex = i;
            for(int j=i+1; j<routeVect.getSize(); j++)
            {
                if(routeVect[j].getTotalTime() < routeVect[minIndex].getTotalTime())
                    minIndex = j;
            }
            if(minIndex != i)
            {
                FlightRoute temp = routeVect[i];
                routeVect[i] = routeVect[minIndex];
                routeVect[minIndex] = temp;
            }
        }
    }
    else
    {
        int minIndex;
        for(int i=0; i<routeVect.getSize()-1; i++)
        {
            minIndex = i;
            for(int j=i+1; j<routeVect.getSize(); j++)
            {
                if(routeVect[j].getTotalCost() < routeVect[minIndex].getTotalCost())
                    minIndex = j;
            }
            if(minIndex != i)
            {
                FlightRoute temp = routeVect[i];
                routeVect[i] = routeVect[minIndex];
                routeVect[minIndex] = temp;
            }
        }
    }
    for(int k=0; k<3 && k<routeVect.getSize(); k++)
    {
        flightRouteVect.push_back(routeVect[k]);
    }
    return flightRouteVect;
}

void FlightPlanner::outputRoute(Vector<FlightRoute> routeVect, FlightPlan plan)
{
    outFlightInfo << "Flight " << flightNumber << ": " << plan.getOrigin() << ", " << plan.getDestination();
    if(plan.getSortType() == "T")
        outFlightInfo << " (Time)\n";
    else
        outFlightInfo << " (Cost)\n";
    for(int i=0; i<routeVect.getSize(); i++)
    {
        routeVect[i].print(i+1, outFlightInfo);
    }
    if(routeVect.getSize() == 0)
    {
        outFlightInfo << "No routes found.\n";
    }
    outFlightInfo << "\n";
    flightNumber++;
}


void FlightPlanner::openOutputFile(string fileName)
{
    outFlightInfo.open("out.txt");
    if(!outFlightInfo)
    {
        cout << "Output file not opened correctly";
        exit(EXIT_FAILURE);
    }
}

void FlightPlanner::closeFiles()
{
    inFlightData.close();
    inFlightPlans.close();
    outFlightInfo.close();
}


int main(int argc, char* argv[])
{
    FlightPlanner plan;
    plan.readFlightData(argv[1]);
    plan.openOutputFile(argv[3]);
    plan.readFlightPlans(argv[2]);
    plan.closeFiles();
}
