#include <fstream>
#include <iostream>
#include <conio.h>
#include <iomanip>
#include <ctime>
#include <string>
#include <windows.h>
using namespace std;
//////////////////////////FUNCTION FOR DATE AND TIME///////////////////////////////////////////
char* gtm()
{
    time_t t;
    time(&t);
    return ctime(&t);
}

class vehicle
{   int vid;
    char dname[20]; //driver name
    char dnum[20];  //driver contact
    char model[20];
	char destination[20];
	char time[20]; //vehicle departure time
	char status[10];
	int fare;
	public:
    vehicle()
    {
        strcpy(status,"Available");
    }
	void input();
	void show();
	void display();
	void astat()
    {
        strcpy(status,"Reserved");
    }
    void restat()
    {
        strcpy(status,"Available");
    }
    int getid()
	{
	return vid;
	}
	char* getstat()
	{
	    return status;
	}
};
///////////////////////////Member functions for Vehicle class///////////////////////////////
void vehicle::input()
{
	cout<<"Enter vehicle id ";
	cin>>vid;
    cin.ignore();
	cout<<"Enter vehicle destination ";
	cin.getline(destination,20);
	cout<<"Enter vehicle model ";
	cin.getline(model,20);
	cout<<"Enter departure time  ";
	cin.getline(time,20);
	cout<<"Enter driver name ";
    cin.getline(dname,20);
    cout<<"Enter driver contact ";
    cin.getline(dnum,20); //10 digit number can contain characters such as +, - (+977-01-4765677)
	cout<<"Enter fare ";
	cin>>fare;

}
void vehicle::display()
{
    cout<<vid<<setw(16)<<dname<<setw(12)<<model<<setw(14)<<destination<<setw(16)<<fare<<setw(12)<<status<<"\n \n";
}
void vehicle::show()
{   cout<<"------VEHICLE-DETAILS--------"<<endl<<endl;
	cout<<"Bus Id: "<<vid<<endl;
	cout<<"Desination: "<<destination<<endl;
	cout<<"Departure Time: "<<time<<endl;
	cout<<"Fare (in Rs.): "<<fare<<endl;
	cout<<"-----------------------------"<<"\n \n";
	cout<<"------DRIVER-DETAILS---------"<<endl<<endl;
    cout<<"Name: "<<dname<<endl;
    cout<<"Contact number: "<<dnum<<endl;
	cout<<"-----------------------------"<<"\n \n";
}


/////////////////////////////////Customer details class////////////////////////////////////////////////////

class customer
{
	char name[20];
	char time[50]; //time storing variable
	char cnum[20];
	vehicle c;
	public:
	void initialize(char cstname[], vehicle tb, char ctemp[])
	{
		strcpy(name,cstname);
		c=tb;
		strcpy(cnum,ctemp);
	}
	void settime()
	{
	    strcpy(time,gtm());
	}
	void cdisplay()
	{
     c.show();
	 cout<<"------RESERVED-BY------------"<<endl<<endl;
	 cout<<"Name: "<<name<<endl;
	 cout<<"Contact Number: "<<cnum<<endl;
	 cout<<"Date Reserved: "<<time<<endl;
	 cout<<"-----------------------------"<<"\n \n";
    }

};

/////////////////////////// FUNCTION FOR MAINSCREEN////////////////////////////
void mainscreen()
{       cout<<setw(75)<<"+------------------------------------------------------------------+"<<endl;
        cout<<setw(75)<<"+----------------VEHICLE RESERVATION SYSTEM------------------------+"<<endl;
        cout<<setw(75)<<"+------------------------------------------------------------------+"<<"\n \n \n";
        cout<<"\t\t\t"<<"1 - Add a New Vehicle"<<endl;
		cout<<"\t\t\t"<<"2 - Display all vehicles"<<endl;
		cout<<"\t\t\t"<<"3 - Reserve vehicle"<<endl;
		cout<<"\t\t\t"<<"4 - Reservation History"<<endl;
		cout<<"\t\t\t"<<"5 - Reset vehicle status"<<endl;
		cout<<"\t\t\t"<<"6 - Remove vehicle"<<endl;
		cout<<"\t\t\t"<<"7 - Exit "<<"\n \n";
		cout<<"\t\t\t"<<"Enter your choice ";
}
///////////////////////////FUNCTION FOR FORMATTING OUTPUT///////////////////////////////////
void format()
{
    cout<<"\n \n"<<setw(72)<<"+----------------LIST OF VEHICLES------------------------+"<<endl;
    cout<<"\n \n"<<"Vehicle id"<<setw(10)<<"Driver"<<setw(10)<<"Model"<<setw(16)<<"Destination"<<setw(15)<<"Fare(in Rs.)"<<setw(10)<<"Status"<<endl;
    cout<<"------------------------------------------------------------------------------"<<endl;
}

/////////////////////////////////////MAIN FUNCTION START/////////////////////////////////////////
int main()
{
	int ch;
	fstream F,G; //F for vehicles and G for customer
	vehicle b;
	customer a;
	do
	{   Start:
		system("cls");
		mainscreen();
		cin>>ch;
		switch(ch)
		{
		case 1: //ADD NEW VEHICLE
		  {
			F.open("vehicle.dat",ios::app | ios::binary);
			b.input();
			F.write((char*)&b, sizeof(b));
			F.close();
			cout<<"Vehicle added Successfully "<<endl;
			getch();
			system("cls");
		break;}
		case 2: //DISPLAY ALL VEHICLES

            system("cls");
			format();
		    F.open("vehicle.dat",ios::in | ios::binary);
			if(F.fail())
				cout<<"No data entered yet "<<endl;
			else
			{
				while(F.read((char*)&b,sizeof(b)))
					b.display();
			}
			F.close();
			getch();
			system("cls");
		break;
		case 3:  //RESERVE A VEHICLE
		   {
            top:
            system("cls");
		    int idres; //id for matching vehicles
		    int ch = 0;
		    char cname[20]; //customer name
		    char ctemp[20]; //customer contact
            format();
		    F.open("vehicle.dat",ios::in | ios::binary);
			if(F.fail())
				{cout<<"No data entered yet "<<endl;
				 getch();
				 system("cls");
				 goto Start; }
			else
			{
				while(F.read((char*)&b,sizeof(b)))
					b.display();
			}
			F.close();
			cout<<"------------------------------------------------------------------------------"<<endl;
            cout<<setw(25)<<"Enter the vehicle id to reserve"<<endl;
            cin>>idres;
            F.open("vehicle.dat",ios::in |ios::out | ios::binary);
			if(F.fail())
				cout<<"Can't open file "<<endl;
			else
			{
				while(F.read((char*)&b,sizeof(b)))
				{
					if(b.getid()==idres)
					{
					    if(strcmp(b.getstat(),"Available")==0)
                      {
						b.show();
						ch=1;
						cout<<"Enter the customer name ";
						cin>>cname;
						cout<<endl<<"Enter contact number ";
						cin>>ctemp;
						a.initialize(cname,b,ctemp);
						a.settime();
						G.open("reservations.dat",ios::app | ios::binary);
						G.write((char*)&a,sizeof(a));
						G.close();
                    F.seekp(F.tellg()-sizeof(b),ios::beg);
                    b.astat();
                    F.write((char*)&b,sizeof(b));
					cout<<"Vehicle reserved successfully"<<endl;
					getch();
					break;
                            }
					else
                    {
                        cout<<"Vehicle already reserved"<<endl;
                        F.close();
                        getch();
                        system("cls");
                        goto top;
                    }
					}
				}
				if(ch==0)
					{cout<<"Invalid vehicle id."<<endl;
					F.close();
                    getch();
                    system("cls");
                    goto top;}
			}
			F.close();
			break;}

        case 4: //RESERVATION HISTORY//
        {
            F.open("reservations.dat",ios::in | ios::binary);
			if(F.fail())
				cout<<"Can't open file "<<endl;
			else
			{
				while(F.read((char*)&a,sizeof(a)))
					a.cdisplay();
			}
			F.close();
			getch();
			break;}

		case 5: //RESET VEHICLE STATUS//

        {
            system("cls");
		    int idres;
		    int ch = 0;
            format();
		    F.open("vehicle.dat",ios::in | ios::binary);
			if(F.fail())
				{cout<<"No data entered yet "<<endl;
				 getch();
				 system("cls");
				 goto Start; }
			else
			{
				while(F.read((char*)&b,sizeof(b)))
					b.display();
			}
			F.close();
			cout<<"------------------------------------------------------------------------------"<<endl;
            cout<<setw(25)<<"Enter the vehicle id to reset"<<endl;
            cin>>idres;
            F.open("vehicle.dat",ios::in |ios::out | ios::binary);
			if(F.fail())
				cout<<"Can't open file "<<endl;
			else
			{
				while(F.read((char*)&b,sizeof(b)))
				{
					if(b.getid()==idres)
					{
					    if(strcmp(b.getstat(),"Reserved")==0)
                      {
                        ch=1;
                    F.seekp(F.tellg()-sizeof(b),ios::beg);
                    b.restat();
                    F.write((char*)&b,sizeof(b));
					cout<<"Reset successful"<<endl;
					getch();
					break;}
					else
                    {
                        cout<<"Vehicle already reset"<<endl;
                        F.close();
                        getch();
                        goto Start;
                    }
					}
				}
				if(ch==0)
					{cout<<"Invalid vehicle id."<<endl;
					F.close();
                    getch();
                    }
			}
			F.close();
			break;}

        case 6: //DELETE VEHICLE//
            system("cls");
		    int idres;
		    int ch = 0;
            format();
		    F.open("vehicle.dat",ios::in | ios::binary);
			if(F.fail())
				{cout<<"No data entered yet "<<endl;
				 getch();
				 system("cls");
				 goto Start; }
			else
			{
				while(F.read((char*)&b,sizeof(b)))
					b.display();
			}
			F.close();
			cout<<"------------------------------------------------------------------------------"<<endl;
            cout<<setw(25)<<"Enter the vehicle id to remove"<<endl;
            cin>>idres;
            F.open("vehicle.dat",ios::in| ios::binary);
            G.open("temp.dat",ios::out|ios::binary);
			if(F.fail())
				cout<<"Can't open file "<<endl;
			else
            {
              while(F.read((char*)&b,sizeof(b)))
              {
                  if(b.getid()!=idres)
                  {
                      G.write((char*)&b,sizeof(b));
                  }
                  else
                  {

                      ch=1;
                  }
              }
              if(ch==0)
                 {cout<<"Invalid vehicle id."<<endl;
					F.close();
                    getch();
                    }
                    else
                    {
                        cout<<"Vehicle deleted successfully"<<endl;
                        getch();
                    }
              }
F.close();
G.close();
remove("vehicle.dat");
rename("temp.dat","vehicle.dat");
break;
}
	}while(ch!=7);
	return 0;
}
