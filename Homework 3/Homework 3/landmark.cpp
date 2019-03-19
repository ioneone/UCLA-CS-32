//
//  landmark.cpp
//  Homework 3
//
//  Created by Junhong Wang on 2/5/19.
//  Copyright © 2019 ioneone. All rights reserved.
//

// Your declarations and implementations would go here
class Landmark {
public:
    Landmark(const string& name) : m_name(name) {}
    
    string name() const { return m_name; }
    
    virtual string color() const = 0;
    
    virtual string icon() const = 0;
    
    virtual ~Landmark() {}
    
private:
    string m_name;
};

class YellowLandmark : public Landmark {
public:
    YellowLandmark(const string& name) : Landmark(name) {}
    
    virtual string color() const { return "yellow"; }
    
    virtual ~YellowLandmark() {}
};

class Hotel : public YellowLandmark {
public:
    Hotel(const string& name) : YellowLandmark(name) {}
    
    virtual string icon() const { return "bed"; }
    
    virtual ~Hotel() { cout << "Destroying the hotel " + name() + "." << endl; }
};

class Restaurant : public YellowLandmark {
public:
    Restaurant(const string& name, int seatingCapacity) : YellowLandmark(name), m_seatingCapacity(seatingCapacity) {}
    
    virtual string icon() const { return (m_seatingCapacity < 40) ? "small knife/fork" : "large knife/fork"; }
    
    virtual ~Restaurant() { cout << "Destroying the restaurant " + name() + "." << endl; }
    
private:
    int m_seatingCapacity;
};

class Hospital : public Landmark {
public:
    Hospital(const string& name) : Landmark(name) {}
    
    virtual string color() const { return "blue"; }
    
    virtual string icon() const { return "H"; }
    
    virtual ~Hospital() { cout << "Destroying the hospital " + name() + "." << endl; }
};


void display(const Landmark* lm)
{
    cout << "Display a " << lm->color() << " " << lm->icon() << " icon for "
    << lm->name() << "." << endl;
}

/*
 Here are the landmarks.
 Display a yellow bed icon for Westwood Rest Good.
 Display a yellow small knife/fork icon for Bruin Bite.
 Display a yellow large knife/fork icon for La Morsure de l'Ours.
 Display a blue H icon for UCLA Medical Center.
 Cleaning up.
 Destroying the hotel Westwood Rest Good.
 Destroying the restaurant Bruin Bite.
 Destroying the restaurant La Morsure de l'Ours.
 Destroying the hospital UCLA Medical Center.
 */
