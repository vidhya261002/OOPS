#include <iostream>
#include <string>
using namespace std;
// Base class Equipment
class Equipment {
protected:
   string name;
   int efficiency; // Efficiency as a percentage (0-100)
   int operatingCost; // Cost per hour
public:
   Equipment(string n, int eff, int cost) : name(n), efficiency(eff), operatingCost(cost) {}
   virtual void optimize() = 0; // Pure virtual method to optimize equipment
   void display() {
       cout << "Equipment: " << name << ", Efficiency: " << efficiency << "%, Operating Cost: $" << operatingCost << " per hour" << endl;
   }
   int getOperatingCost() { return operatingCost; }
   int getEfficiency() { return efficiency; }
};
// Derived class WeldingMachine
class WeldingMachine : public Equipment {
public:
   WeldingMachine(string n, int eff, int cost) : Equipment(n, eff, cost) {}
   void optimize() {
       efficiency += 10; // Simulate optimization by increasing efficiency
       cout << "Optimizing " << name << " with improved welding techniques." << endl;
   }
};
// Derived class PaintBooth
class PaintBooth : public Equipment {
public:
   PaintBooth(string n, int eff, int cost) : Equipment(n, eff, cost) {}
   void optimize() {
       efficiency += 5; // Simulate optimization by increasing efficiency
       cout << "Optimizing " << name << " with faster drying methods." << endl;
   }
};
// Worker class
class Worker {
public:
   string name;
   int hourlyRate;
   Worker(string n, int rate) : name(n), hourlyRate(rate) {}
   void display() {
       cout << "Worker: " << name << ", Hourly Rate: $" << hourlyRate << endl;
   }
};
// Step class
class Step {
public:
   string description;
   int timeRequired; // Time required in hours
   Equipment* equipment; // Pointer to the Equipment used in this step
   Worker* worker; // Pointer to the Worker performing the task
   Step(string desc, int time, Equipment* eq, Worker* wrk)
       : description(desc), timeRequired(time), equipment(eq), worker(wrk) {}
   void perform() {
       cout << "Performing Step: " << description << endl;
       equipment->display();
       worker->display();
       cout << "Time Required: " << timeRequired << " hours" << endl;
   }
};
// Process class to hold all steps
class Process {
private:
   Step** steps;
   int numSteps;
public:
   Process(int num) : numSteps(num) {
       steps = new Step*[numSteps];
   }
   void addStep(int index, Step* step) {
       steps[index] = step;
   }
   void performAllSteps() {
       cout << "\nStarting manufacturing process...\n";
       for (int i = 0; i < numSteps; ++i) {
           steps[i]->perform();
       }
   }
   void optimizeEquipment() {
       cout << "\nOptimizing manufacturing process...\n";
       for (int i = 0; i < numSteps; ++i) {
           steps[i]->equipment->optimize();
       }
   }
   void performAllStepsAfterOptimization() {
       cout << "\nPerforming steps after optimization...\n";
       for (int i = 0; i < numSteps; ++i) {
           steps[i]->perform();
       }
   }
   ~Process() {
       for (int i = 0; i < numSteps; ++i) {
           delete steps[i];
       }
       delete[] steps;
   }
};
int main() {
   // Input number of equipment
   int numEquipment;
   cout << "Enter the number of equipment types to add: ";
   cin >> numEquipment;
   Equipment* equipments[10]; // Array to hold equipment
   for (int i = 0; i < numEquipment; ++i) {
       int type;
       string name;
       int efficiency, cost;
       cout << "Enter the type of equipment (1: Welding Machine, 2: Paint Booth): ";
       cin >> type;
       cout << "Enter the name of equipment: ";
       cin.ignore();  // To clear the input buffer
       getline(cin, name);
       cout << "Enter the efficiency percentage (0-100): ";
       cin >> efficiency;
       cout << "Enter the operating cost per hour: ";
       cin >> cost;
       if (type == 1) {
           equipments[i] = new WeldingMachine(name, efficiency, cost);
       } else if (type == 2) {
           equipments[i] = new PaintBooth(name, efficiency, cost);
       }
   }
   // Input number of workers
   int numWorkers;
   cout << "Enter the number of workers: ";
   cin >> numWorkers;
   Worker* workers[10]; // Array to hold workers
   for (int i = 0; i < numWorkers; ++i) {
       string name;
       int hourlyRate;
       cout << "Enter the name of worker: ";
       cin.ignore();
       getline(cin, name);
       cout << "Enter the worker's hourly rate: ";
       cin >> hourlyRate;
       workers[i] = new Worker(name, hourlyRate);
   }
   // Input number of steps in the process
   int numSteps;
   cout << "Enter the number of steps in the process: ";
   cin >> numSteps;
   Process process(numSteps); // Create Process object to hold all steps
   for (int i = 0; i < numSteps; ++i) {
       string description;
       int time;
       int eqIndex, wrkIndex;
       cout << "Enter the description of step " << i + 1 << ": ";
       cin.ignore();
       getline(cin, description);
       cout << "Enter the time required for this step (in hours): ";
       cin >> time;
       // Select equipment for this step
       cout << "Select equipment for this step: " << endl;
       for (int j = 0; j < numEquipment; ++j) {
           cout << j + 1 << ": ";
           equipments[j]->display();
       }
       cout << "Enter the number corresponding to the equipment: ";
       cin >> eqIndex;
       // Select worker for this step
       cout << "Select worker for this step: " << endl;
       for (int j = 0; j < numWorkers; ++j) {
           cout << j + 1 << ": ";
           workers[j]->display();
       }
       cout << "Enter the number corresponding to the worker: ";
       cin >> wrkIndex;
       process.addStep(i, new Step(description, time, equipments[eqIndex - 1], workers[wrkIndex - 1]));
   }
   process.performAllSteps();
   process.optimizeEquipment();
   process.performAllStepsAfterOptimization();
   // Clean up dynamically allocated equipment and workers
   for (int i = 0; i < numEquipment; ++i) {
       delete equipments[i];
   }
   for (int i = 0; i < numWorkers; ++i) {
       delete workers[i];
   }
   return 0;
}
