/***********************************************************************
Matr.-Nr:                     3085596
Nachname/Surname:             Haque
Vorname/Given name:           Md Anamul
Uni-Email:                    md.haque.696@stud.uni-due.de
Studiengang/Course of studis: ISE(Software Engineering)
***********************************************************************/

#include<iostream>
#include<string>
#include<iomanip>
using namespace std;

const int annualAverageConsumptionPerPerson = 200;
const int annualAverageConsumptionPerSquareMeter = 9;
const int annual_average_consumption_per_person_with_electric_water_heating = 550;

// 1. Define a enumeration structure called use
enum Use 
{ 
    once, 
    daily, 
    mo_fr, 
    sa_su, 
    weekly 
};

// 2. Function to input frequency of use
void input_use( string c, Use& use) 
{
    cout<<"how often it will be used?";
    cout<<"(d) daily";
    cout<<"(m) mo_fr";
    cout<<"(o) once";
    cout<<"(s) sa_su";
    cout<<"(w) weekly";
    
    cout << c;
    char choice;
    cin >> choice;

    switch (choice) 
    {
        case 'd': use =  daily;  break;
        case 'm': use =  mo_fr;  break;
        case 'o': use =  once;   break;
        case 's': use =  sa_su;  break;
        case 'w': use =  weekly; break;
        default:
            cout << "Invalid choice. Using 'once' as default." << endl;
            use = once;
            break;
    }
}

// 3. Define a structure called Consumer
struct consumer 
{
    string description;
    float watt;
    float watt_standby;
    float hours;
    Use use;
    consumer* next;
};

// 4. Difine a Extend structer household with pointer Consumer
struct Household 
{
    string city;
    int numPersons;
    int squareMeters;
    bool Hot_water;
    consumer* consumers;
};


// from task A1
float calculateAnnualPowerConsumption(Household& house) 
{
    //      Ternary operator
    // Expression1(always condition) ? Expression2 : Expression3
    // if condition true evaluated Expression 2, else Expression3
    float annualPowerConsumptionPerPerson = house.Hot_water ? annual_average_consumption_per_person_with_electric_water_heating : annualAverageConsumptionPerPerson;
    return ((house.numPersons * annualPowerConsumptionPerPerson) + (house.squareMeters * annualAverageConsumptionPerSquareMeter));
}



// From task A1
float calculateAnnualPowerCosts(Household& house, float pricePerKWh) 
{
    return calculateAnnualPowerConsumption(house) * pricePerKWh;
}

// 5. Function to add new Consumer in Household
void addConsumerToHousehold(Household& house, consumer* newConsumer) 
{
    newConsumer->next = house.consumers;
    house.consumers = newConsumer;
}

// 6. Function to calculate annual hours for each Consumer
float annualHoursOfUse(consumer* cons) 
{
    switch (cons->use) 
    {
        case once: return cons->hours;
        case daily: return cons->hours * 365;
        case mo_fr: return cons->hours * 260;
        case sa_su: return cons->hours * 104;
        case weekly: return cons->hours * 52;
        default: return 0;
    }
}

// 7. Function to calcualte annual hours standby
float annualHoursOfStandby(consumer* cons) 
{
    return 8760 - annualHoursOfUse(cons);
}

// 8. Function to calculate annual kwh
float annualKWh(consumer* cons) 
{
    return (((annualHoursOfUse(cons) * cons->watt) 
          + (annualHoursOfStandby(cons) * cons->watt_standby)) / 1000);
}


// 9. move_up power consumer from consumer list
consumer* move_up(consumer* Current_Head, int k) 
{
    if (k <= 1) 
    {
        return Current_Head;  
    }
 
    else
    {    
        consumer* current = Current_Head;
        consumer* next_consumer = current->next;

        if (k==2 && next_consumer != nullptr) 
        {
            current->next = next_consumer->next;
            next_consumer->next = Current_Head;
            Current_Head = next_consumer;
            return Current_Head;
        }
   
        else
        {       

             while (current != nullptr) 
            {
                int i = 1;
                    while (i < k - 2) 
                    {
                        if (current->next == nullptr) 
                        {
                            return Current_Head;
                        }
                        current = current->next;
                        i++;
                    }

                if (current->next == nullptr || current->next->next == nullptr) 
                {
                    return Current_Head;
                }

                consumer*kth_node = current->next->next;
                current->next->next =kth_node->next;
                kth_node->next = current->next;
                current->next =kth_node;

                return Current_Head;
            }

        }
    }
    
}

// 10. Define global integer constants
const int columnWidth = 35;

// 11. Define a function with consumer details
void printConsumer(consumer* cons, int index) 
{
    cout << right << setw(columnWidth) <<index << ": " << left << cons->description<<"(at address: " <<cons<<")"<< endl; // Extension 1   
    cout << right << setw(columnWidth) << "power consumption"<< ": " << left << cons->watt << " W" << endl;
    cout << right << setw(columnWidth) << "power consumption standby"<< ": " << left << cons->watt_standby << " W" << endl;
    cout << right << setw(columnWidth) << "annual hours of use"<< ": " << left << annualHoursOfUse(cons) << " h" << endl;
    cout << right << setw(columnWidth) << "annual hours of standby"<< ": " << left << annualHoursOfStandby(cons) << " h" << endl;
}

// Extension 3. Define a function call input household
void input_household(Household* Ex_house)
{
    char hotwater;
    cout << "How many square meters does the household have: ";
    cin >> Ex_house->squareMeters;
    cout << "how many persons live in this household?";
    cin >> Ex_house->numPersons;
    cout << "is hot water heated using electricity? (y(es) or n(o)) ";
    cin >> hotwater;

        if (hotwater == 'y')
            Ex_house->Hot_water = true;
        else
            Ex_house->Hot_water=false;

    Ex_house->consumers = nullptr; 
}

 // Extension 4. Define a function call copy consumers

 Household* copy_consumers(Household* source_house, Household* destination_house) 
{
    // Copy all consumers from (source_house to destination_house)
    consumer* temp_house_consumer = source_house->consumers;
    consumer* destination_house_consumer= destination_house->consumers;
    consumer* temp_head = nullptr;
    consumer* temp_tail = nullptr;


    if(temp_house_consumer == nullptr)
     {
         return destination_house;
     }

    while (temp_house_consumer != nullptr)
     {
       
            consumer* New_consumer = new consumer;
            New_consumer->description  = temp_house_consumer->description;
            New_consumer->watt         = temp_house_consumer->watt;
            New_consumer->watt_standby = temp_house_consumer->watt_standby;
            New_consumer->hours        = temp_house_consumer->hours;
            New_consumer->use          = temp_house_consumer->use;
            New_consumer->next         = nullptr;
        

        if(temp_head == nullptr)
        {
            temp_head = New_consumer;
            temp_tail = New_consumer;
        }
        else
        {
            temp_tail->next = New_consumer;
            temp_tail = New_consumer;
        }

        temp_house_consumer = temp_house_consumer->next;
    }
    temp_tail->next = destination_house->consumers;
    destination_house->consumers = temp_head;

    return destination_house;
    
}



// 12. Funtion print household
void printHousehold(Household* house, float pricePerKWh, int number_of_household) // Extension 2. int number_of_household  
{
    string heater = (house->Hot_water) ? "yes" : "no"; // using Ternary operator

    cout << "H O U S E H O L D  N O  "<<" "<< number_of_household << "  P O W E R  C O N S U M P T I O N" << endl; 
    cout <<  "---------------------------------------------------------------------" << endl;
    cout << right << setw(columnWidth) << "city"<< ": " << left << house->city <<"(at address: "<<house<<")"<<endl;  // Extension 2. find address for city
    cout << right << setw(columnWidth) << "price for one kWh"<< ": "  << left << pricePerKWh << " ct/kWh" << endl;
    cout << right << setw(columnWidth) << "square meters"<< ": "  << left << house->squareMeters << " qm" << endl;
    cout << right << setw(columnWidth) << "persons"<< ": "  << left << house->numPersons << endl;
    cout << right << setw(columnWidth) << "water heated using electricity"<< ": "  << left << heater << endl;
    cout << right << setw(columnWidth) << "list of consumers"<< ": "  << endl;
    cout << "---------------------------------------------------------------------" << endl;

    float powerConsumptionSquareMeters = (house->squareMeters * annualAverageConsumptionPerSquareMeter);
    float powerConsumptionPersons = (house->numPersons * (house->Hot_water ? annual_average_consumption_per_person_with_electric_water_heating : annualAverageConsumptionPerPerson)); // using ternary operator
    float totalConsumption = (powerConsumptionSquareMeters + powerConsumptionPersons);
    float totalCosts = (totalConsumption * (pricePerKWh));
    int index = 1;

    consumer* currentConsumer = house->consumers;

    while (currentConsumer != nullptr) 
    {
        totalConsumption += annualKWh(currentConsumer) ;
        printConsumer(currentConsumer, index);
        cout << right << setw(columnWidth) << "annual consumption"<< ": " << left << annualKWh(currentConsumer)<< " kWh" << endl;
        cout << right << setw(columnWidth) << "annual costs"<< ": " << left << (annualKWh(currentConsumer)*pricePerKWh) << " EUR" << endl;
        currentConsumer = currentConsumer->next;
        index++;
    }

    cout << string(columnWidth * 2, '-') << endl;
    cout << right << setw(columnWidth) << "power consumption square meters"<< ": "  << left << powerConsumptionSquareMeters << " kWh" << endl;
    cout << right << setw(columnWidth) << "power consumption all persons"<< ": "  << left << powerConsumptionPersons << " kWh" << endl;
    cout << right << setw(columnWidth) << "total annual power consumption"<< ": "  << left << totalConsumption<< " kWh" << endl;
    cout << right << setw(columnWidth) << "total annual power costs"<< ": "  << left << (totalConsumption*pricePerKWh) << " EUR" << endl;
}

// 13. Main Function
int main() 
{
    Household* house = new Household;
    house->consumers = nullptr;
    float pricePerKWh;
    char hotwater;
    int n;     
    cout << "CALCULATION OF AVERAGE POWER COSTS FOR A HOUSEHOLD\n";
    cout << "how many households does the house have? ";
    cin>>n;
    Household* number_of_household[n];
    for(int i=0 ; i<n ; i++)
     {
        number_of_household[i] = nullptr;
     }
    cout << "In which city is the household located: ";
    cin >> house->city;
    cout << "what is the price for one kWh in EUR?";
    cin >> pricePerKWh;
    
    
    while (true) 
    {
        
        cout << "q quit" << endl;
        cout << "i input power consumer" << endl;
        cout << "u move up power consumer" << endl;
        cout << "p print household" << endl;
        cout << "a print all households" << endl;
        cout << "n new household" << endl;
        cout << "c copy all cosumers (added to already existing ones)" << endl;


        char choice;
        cin >> choice;

         if (choice == 'q') 
        {
            delete house;
            break;
        }
        else if (choice == 'i') 
        {
            consumer *newConsumer,*NewTemp;
            newConsumer = new consumer;
            int num;
            cout<<"number of household?";
            cin>>num;

            cout << "what is the description of the power consumer? ";
            cin>> newConsumer->description;
            cout << "how many watt it will have? ";
            cin >> newConsumer->watt;
            cout << "how many watt standby it will have? ";
            cin >> newConsumer->watt_standby;
            input_use("How often is it used?\n(d) daily\n(m) mo_fr\n(o) once\n(s) sa_su\n(w) weekly? ", newConsumer->use);
            cout << "How many hours will it be operating? ";
            cin >> newConsumer->hours;

            addConsumerToHousehold(*number_of_household[num], newConsumer);
        }
        else if (choice == 'u') 
        {
            int k,num;
            cout<<"number of household?";
            cin>>num;
            cout << "which one? ";
            cin >> k;
            number_of_household[num]->consumers = move_up(number_of_household[num]->consumers, k);
        }
        else if (choice == 'p') 
        {
            int number;
            cout<<"number of household";
            cin >>number;
            printHousehold(number_of_household[number], pricePerKWh, number); // number_of_household,
        }
        else if(choice == 'a')
        {
            for(int i=0; i<n; i++)
                {
                    if(number_of_household[i] != nullptr)
                    printHousehold(number_of_household[i], pricePerKWh, i);

                }  
        }

        else if (choice == 'n')
        {
            int x;
            cout<< "number of household? ";
            cin >>x;

            if(number_of_household[x]!= nullptr)
            {
                cout << "household already exists" << endl;                            
            }
            else 
            {
              Household* new_household = new Household;
              new_household->city = house->city;
              input_household(new_household);
              number_of_household[x] = new_household;           
            }
        }
        else if(choice == 'c')
        {
            int num1,num2;
            cout<<"number of household from which to copy consumers?";
            cin>>num1;
            cout<<"nnumber of household to copy to?";
            cin>>num2;
            if(number_of_household[num1] == nullptr && number_of_household[num2] == nullptr)
            {
               cout<<" Both are not exsit ";
            }
            else
            {
                number_of_household[num2] = copy_consumers(number_of_household[num1],number_of_household[num2]);
            }

        }
        else 
        {
            cout << "sorry wrong choice" << endl;
        }
    }

    return 0;
}