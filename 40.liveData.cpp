//
//  main.cpp
//  LiveData
//
//  Created by Sathya Babu on 08/02/24.
//

#include <functional>
#include <vector>

// reffer line 113  17_Concept_Good

//template <typename T>
//concept Copyable = std::is_copy_constructible_v< T >;

template <typename T>
class LiveData {
public:
    LiveData() = default;

    LiveData(const T& value)
        : mValue(value)
    {
    }

    LiveData(T&& value)
        : mValue( std::move(value) ) // std::move just an obsession! works without
    {
    }

    LiveData& operator=(const T& value)
    {
        setValue(value);
        return *this;
    }

    LiveData& operator=(T&& value)
    {
        setValue( std::move(value) ); // std::move just an obsession! works without
        return *this;
    }

    template <typename Observer>
    void observe(Observer&& observer)
    {
        mObservers.emplace_back( std::forward< Observer >( observer) );
        observer( mValue );
    }

    void setValue(const T& value)
    {
        if (value != mValue) {
            mValue = value;
            notifyObservers();
        }
    }

    void setValue(T&& value)
    {
        if (value != mValue) {
            mValue = std::move(value); // std::move just an obsession!
            notifyObservers();
        }
    }

private:
    void notifyObservers()
    {
        for (auto& observer : mObservers) {
            observer(mValue);
        }
    }

private:
    T mValue;
    std::vector<std::function<void(const T&)>> mObservers;
};
#include <iostream>

int main()
{
    LiveData<int> data{42}; // data : T type is copy-constructible.

    data.observe(  [](const auto& value) {
        std::cout << "Observer 1: " << value << std::endl;
    });

    data.observe([](const auto& value) {
        std::cout << "Observer 2: " << value << std::endl;
    });

    data.setValue(43);
    data.setValue(44);

    return 0;
}
