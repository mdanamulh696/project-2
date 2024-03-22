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

// 10. Define global integer constants
const int columnWidth = 35;

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
    cout<<"daily  (d)";
    cout<<"mo_fr  (m)";
    cout<<"once   (o)";
    cout<<"sa_su  (s)";
    cout<<"weekly (w)";
    
    char choice;
    cout << c;
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
    int annualPowerConsumptionPerPerson = house.Hot_water ? annual_average_consumption_per_person_with_electric_water_heating : annualAverageConsumptionPerPerson;
    return (house.numPersons * annualPowerConsumptionPerPerson) + (house.squareMeters * annualAverageConsumptionPerSquareMeter);
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
    switch (cons->use) {
        case once:
            return cons->hours;
        case daily:
            return cons->hours * 365;
        case sa_su:
            return cons->hours * 104;
        case mo_fr:
            return cons->hours * 260;
        case weekly:
            return cons->hours * 52;
        default:
            return 0;
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
    return (((annualHoursOfUse(cons) * cons->watt) + (annualHoursOfStandby(cons) * cons->watt_standby)) / 1000);
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
        consumer* kNode = current->next;

        if (k==2 && kNode != nullptr) 
        {
            current->next = kNode->next;
            kNode->next = Current_Head;
            Current_Head = kNode;
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

                consumer*positionNode = current->next->next;
                current->next->next =positionNode->next;
                positionNode->next = current->next;
                current->next =positionNode;

                return Current_Head;
            }

        }
    }
    
}

// 11. Define a function with consumer details
void printConsumer(consumer* cons, int index) 
{
    cout << right << setw(33) <<index << ": " << left << cons->description << endl;
    cout << right << setw(columnWidth) << "power consumption: " << left << cons->watt << " W" << endl;
    cout << right << setw(columnWidth) << "power consumption standby: " << left << cons->watt_standby << " W" << endl;
    cout << right << setw(columnWidth) << "annual hours of use: " << left << annualHoursOfUse(cons) << " h" << endl;
    cout << right << setw(columnWidth) << "annual hours of standby: " << left << annualHoursOfStandby(cons) << " h" << endl;
}

// 12. Funtion print household
void printHousehold(Household* house, float pricePerKWh) 
{
    string heater = (house->Hot_water) ? "yes" : "no";

    cout << "H O U S E H O L D   P O W E R   C O N S U M P T I O N" << endl;
    cout << string(columnWidth * 2, '-') << endl;
    cout << right << setw(columnWidth) << "city: " << left << house->city << endl;
    cout << right << setw(columnWidth) << "price for one kWh: " << fixed << setprecision(2) << left << pricePerKWh << " ct/kWh" << endl;
    cout << right << setw(columnWidth) << "square meters: " << left << house->squareMeters << " qm" << endl;
    cout << right << setw(columnWidth) << "persons: " << left << house->numPersons << endl;
    cout << right << setw(columnWidth) << "water heated using electricity: " << left << heater << endl;
    cout << right << setw(columnWidth) << "list of consumers" << endl;
    cout << string(columnWidth * 2, '-') << endl;

    float powerConsumptionSquareMeters = (house->squareMeters * annualAverageConsumptionPerSquareMeter);
    float powerConsumptionPersons = (house->numPersons * (house->Hot_water ? annual_average_consumption_per_person_with_electric_water_heating : annualAverageConsumptionPerPerson));
    float totalConsumption = (powerConsumptionSquareMeters + powerConsumptionPersons);
    float totalCosts = (totalConsumption * (pricePerKWh));
    int index = 1;

    consumer* currentConsumer = house->consumers;

    while (currentConsumer != nullptr) 
    {
        totalConsumption += annualKWh(currentConsumer) ;
        printConsumer(currentConsumer, index);
        cout << right << setw(columnWidth) << "annual consumption: " << left << annualKWh(currentConsumer)<< " kWh" << endl;
        cout << right << setw(columnWidth) << "annual costs: " << left << (annualKWh(currentConsumer)*pricePerKWh) << " EUR" << endl;
        currentConsumer = currentConsumer->next;
        index++;
    }

    cout << string(columnWidth * 2, '-') << endl;
    cout << right << setw(columnWidth) << "power consumption square meters: " << left << powerConsumptionSquareMeters << " kWh" << endl;
    cout << right << setw(columnWidth) << "power consumption all persons: " << left << powerConsumptionPersons << " kWh" << endl;
    cout << right << setw(columnWidth) << "total annual power consumption: " << left << totalConsumption<< " kWh" << endl;
    cout << right << setw(columnWidth) << "total annual power costs: " << left << (totalConsumption*pricePerKWh) << " EUR" << endl;
}

// 13. Main Function
int main() 
{
    Household* house = new Household;
    house->consumers = nullptr;
    float pricePerKWh;
    char hotwater;
    
    cout << "CALCULATION OF AVERAGE POWER COSTS FOR A HOUSEHOLD\n";
    cout << "In which city is the household located: ";
    cin >> house->city;
    cout << "what is the price for one kWh in EUR?";
    cin >> pricePerKWh;
    cout << "How many square meters does the household have: ";
    cin >> house->squareMeters;
    cout << "how many persons live in this household?";
    cin >> house->numPersons;
    cout << "is hot water heated using electricity? (y(es) or n(o)) ";
    cin >> hotwater;

    if (hotwater == 'y')
        house->Hot_water = true;
    else
        house->Hot_water=false;

    while (true) 
    {
        cout << "q quit" << endl;
        cout << "i input power consumer" << endl;
        cout << "u move up power consumer" << endl;
        cout << "p print household" << endl;
        char choice;
        cin >> choice;

        if (choice == 'q') 
        {
            delete house;
            exit(0);
            break;
        }
        else if (choice == 'i') 
        {
            consumer *newConsumer,*NewTemp;
            newConsumer = new consumer;
            cout << "what is the description of the power consumer? ";
            cin>> newConsumer->description;
            cout << "how many watt it will have? ";
            cin >> newConsumer->watt;
            cout << "how many watt standby it will have? ";
            cin >> newConsumer->watt_standby;
            cout<<"how often it will be used?" << endl;
            cout<<"daily  (d)" << endl;
            cout<<"mo_fr  (m)" << endl;
            cout<<"once   (o)" << endl;
            cout<<"sa_su  (s)" << endl;
            cout<<"weekly (w)" << endl;
            
            char useChoice;
            cin >> useChoice;

            switch (useChoice) 
            {
                case 'd': newConsumer->use = daily; break;
                case 'm': newConsumer->use = mo_fr; break;
                case 'o': newConsumer->use = once; break;
                case 's': newConsumer->use = sa_su; break;
                case 'w': newConsumer->use = weekly; break;
                 default: newConsumer->use = once;
            }

            cout << "how many hours it will be operating then? ";
            cin >> newConsumer->hours;

            addConsumerToHousehold(*house, newConsumer);
        }
        else if (choice == 'u') 
        {
            int k;
            cout << "which one? ";
            cin >> k;
            house->consumers = move_up(house->consumers, k);
        }
        else if (choice == 'p') 
        {
            printHousehold(house, pricePerKWh);
        }
        else 
        {
            cout << "sorry wrong choice" << endl;
        }
    }

    return 0;
}