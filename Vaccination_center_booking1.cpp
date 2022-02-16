#include<bits/stdc++.h>
using namespace std;
int id=0;
class Address
{
    string state,district;
public:
    Address(vector<string>loc)
    {
        state=loc[0];
        district=loc[1];
    }
    string get_state()
    {
        return state;
    }
    string get_district()
    {
        return district;
    }

};
class Booking
{
    string u_id,c_id;
    int day,b_id;
public:
    Booking(string u, string c,int d)
    {
        u_id=u;
        c_id=c;
        day=d;
        b_id=id+1;
        id++;
    }
    string get_uid()
    {
        return u_id;
    }
    string get_cid()
    {
        return c_id;
    }
    int get_day()
    {
        return day;
    }
    int get_bid()
    {
        return b_id;
    }
    void set_bid(int b)
    {
        b_id=b;
    }
    void set_uid(string uid)
    {
        u_id=uid;
    }
    void set_cid(string cid)
    {
        c_id=cid;
    }
    void set_day(int d)
    {
        day=d;
    }
};

class User
{
    string uid,name,gender;
    Address *ads;
    bool book_status;
    Booking *booked_slots;
    int age;
public:
    User(vector<string>u,int ag)
    {
        uid=u[0];
        name=u[1];
        gender=u[2];
        age=ag;
        book_status=false;
    }
    string get_uid()
    {
        return uid;
    }
    string get_name()
    {
        return name;
    }
    string get_gender()
    {
        return gender;
    }
    int get_age()
    {
        return age;
    }
    Address* get_address()
    {
        return ads;
    }
    void set_address(Address * adss)
    {
        ads=adss;
    }
    bool get_bookstatus()
    {
        return book_status;
    }
    void set_bookstatus(bool st)
    {
        book_status=st;
    }
    Booking * get_bookingslots()
    {
        return booked_slots;
    }
    void set_bookingslots(Booking * st)
    {
        booked_slots=st;
    }
};



class capacity
{
    int day,cap,aval;
public:
    capacity(int d, int c)
    {
        day=d;
        cap=c;
        aval=c;
    }
    int get_day()
    {
        return day;
    }
    int get_cap()
    {
        return cap;
    }
    int get_aval()
    {
        return aval;
    }
    void set_aval(int c)
    {
        aval=c;
    }
    void set_day(int d)
    {
        day=d;
    }
    void set_cap(int c)
    {
        cap=c;
    }
};

class VCenter
{
    string state,district,c_id;
    set<Booking *>bookk;
    set<capacity *>cap;
public:
    VCenter(string cd,string st, string dist)
    {
        state=st;
        district=dist;
        c_id=cd;
    }
    string get_state()
    {
        return state;
    }
    string get_district()
    {
        return district;
    }
    string get_cid()
    {
        return c_id;
    }
    set<Booking *> get_booking()
    {
        return bookk;
    }
    set<capacity *>get_capacity()
    {
        return cap;
    }

    void set_booking(set<Booking *>ss)
    {
        bookk=ss;
    }
    void set_capacity(set<capacity *>c)
    {
        cap=c;
    }
};



class Covid_Portal
{
    map<string,User *>user_detail;
    map<string,VCenter *>vac_center;
public:
    Covid_Portal()
    {

    }
    void Register_user(vector<string>user,int age,vector<string>loc)
    {
        string u_id=user[0];
        if(user_detail.find(u_id)==user_detail.end())
        {
            User *u=new User(user,age);
            Address *ads=new Address(loc);
            u->set_address(ads);
            user_detail[u_id]=u;
        }
        else
        {
            cout<<"\nUser id is Already Registered : ";
            User *u=user_detail[u_id];
            Address *addss=u->get_address();
            cout<<"\n--------------------------User Details----------------------";
            cout<<"\nUser id: "<<u->get_uid()<<"\nUser name: "<<u->get_name()<<"\ngender: "<<u->get_gender();
            cout<<"\nAge: "<<u->get_age();
            cout<<"\nState: "<<addss->get_state()<<"\nDistrict: "<<addss->get_district();
        }
    }
    void Add_vaccination_center(vector<string>vc)
    {
        string cid=vc[0];
        if(vac_center.find(cid)==vac_center.end())
        {
            VCenter *vv=new VCenter(cid,vc[1],vc[2]);
            vac_center[cid]=vv;
        }
        else
        {
            cout<<"\nCenter id already exists";
        }
    }

    void Add_capacity(string cid,int day, int cap)
    {
        if(vac_center.find(cid)!=vac_center.end())
        {
            VCenter *vv=vac_center[cid];
            set<capacity *>cc=vv->get_capacity();
            bool flag=0;
            for(auto it :cc)
            {
                if(it->get_day()==day)
                {
                    flag=1;
                    int sum=it->get_cap()+cap;
                    it->set_cap(sum);
                    break;
                }
            }
            if(flag==0)
            {
                capacity *cp1=new capacity(day,cap);
                cc.insert(cp1);
            }
            vv->set_capacity(cc);
            vac_center[cid]=vv;
        }
        else
        {
            cout<<"\nIncorrect center id, doesn't exist";
        }
    }
    void print_capacity(string cid)
    {
        if(vac_center.find(cid)!=vac_center.end())
        {
            VCenter *vv=vac_center[cid];
            set<capacity *>cc=vv->get_capacity();
            for(auto it :cc)
            {
                cout<<"\nDay: "<<it->get_day()<<" - "<<it->get_cap();
            }
        }
        else
        {
            cout<<"\nIncorrect center id, doesn't exist";
        }
    }
    void list_center(string dist)
    {
        for(auto it=vac_center.begin();it!=vac_center.end();it++)
        {
            VCenter *vv=it->second;
            if(vv->get_district()==dist)
            {
                cout<<"\nCenter id: "<<it->first<<" State: "<<vv->get_state();
            }
        }
    }

    int book_vaccine(string c_id,int day, string u_id)
    {
        if(vac_center.find(c_id)!=vac_center.end() && user_detail.find(u_id)!=user_detail.end())
        {
            User *u=user_detail[u_id];
            if(u->get_bookstatus())
            {
                Booking *bbb=u->get_bookingslots();
                cout<<"\nAlready booked slot for UID: "<< u_id<<"\nBooking id: "<<bbb->get_bid()<<"\ncenter id: "<<bbb->get_cid()<<"\nday: "<<bbb->get_day();
                    return bbb->get_bid();
            }
            else
            {
                VCenter * vc=vac_center[c_id];
                set<capacity *>cc=vc->get_capacity();
                for(auto it : cc)
                {
                    if(it->get_day()==day && it->get_aval()>0)
                    {
                        Booking *bb=new Booking(u_id,c_id,day);
                        int bid=bb->get_bid();
                        it->set_aval(it->get_aval()-1);
                        vc->set_capacity(cc);
                        set<Booking *>b=vc->get_booking();
                        b.insert(bb);
                        vc->set_booking(b);
                        vac_center[c_id]=vc;
                        u->set_bookstatus(true);
                        u->set_bookingslots(bb);
                        user_detail[u_id]=u;
                        return bid;
                    }
                }
                cout<<"\n No slots available for this day, please select some other day: ";
                return 0;
            }
        }
        else
        {
            cout<<"\nIncorrect cid or uid ";
            return 0;
        }
    }
    void list_booking(string c_id,int day)
    {
        if(vac_center.find(c_id)!=vac_center.end())
        {
            for(auto it=user_detail.begin(); it!=user_detail.end();it++)
            {
                User *u=it->second;
                if(u->get_bookstatus())
                {
                    Booking *b=u->get_bookingslots();
                    Address *a=u->get_address();
                    if(b->get_day()==day && b->get_cid()==c_id)
                    {
                        cout<<"\n-B_id: "<<b->get_bid()<<" User name: "<<u->get_name()<<" C_id: "<<c_id<<" district: "<<a->get_district();
                    }
                }
            }
        }
        else
        {
            cout<<"\nThis vaccination center is not available";
        }
    }
    void cancel_booking(string c_id,int b_id,string u_id)
    {
        if(vac_center.find(c_id)!=vac_center.end() && user_detail.find(u_id)!=user_detail.end())
        {
            for(auto it=user_detail.begin(); it!=user_detail.end();it++)
            {
                User *u=it->second;
                if(u->get_bookstatus())
                {
                    Booking *b=u->get_bookingslots();
                    if(b->get_cid()==c_id && b->get_bid()==b_id)
                    {
                        u->set_bookstatus(false);
                        Booking *bb;
                        u->set_bookingslots(bb);
                        int day=b->get_day();
                        VCenter *vc=vac_center[c_id];
                        set<Booking *>sb=vc->get_booking();
                        sb.erase(b);
                        set<capacity *>cc=vc->get_capacity();
                        for(auto it1:cc)
                        {
                            if(it1->get_day()==day)
                            {
                                it1->set_aval(it1->get_aval()+1);
                                vc->set_capacity(cc);
                                break;
                            }
                        }
                        vac_center[c_id]=vc;
                        user_detail[u_id]=u;
                        break;

                    }
                }
            }
        }
        else
        {
            cout<<"\nThe center id/user id is not correct";
        }
    }
};


int main()
{
    int t,age,day,cap,b_id;
    string Req_type,u_id,u_name,gender,state,district,c_id;
    cout<<"Enter total number of cases: ";
    cin>>t;
    Covid_Portal *cp=new Covid_Portal();
    while(t--)
    {
        cout<<"\nEnter Request Type: ";
        cin>>Req_type;
        if(Req_type=="AddUser")
        {
            cout<<"\nEnter User id, Name ,gender and age of User: ";
            cin>>u_id>>u_name>>gender>>age;
            cout<<"\nEnter Users location (state and district): ";
            cin>>state>>district;
            vector<string> user = {u_id,u_name,gender};
            vector<string> loc = {state,district};
            if(age>=18)
                cp->Register_user(user,age,loc);
            else
                cout<<"\n Jao beta pogo dekho : ";
        }
        else if(Req_type=="AddVaccinationCenter")
        {
            cout<<"\nEnter New Vaccination Center : \n";
            cout<<"Enter State, District, Center_id: ";
            cin>>state>>district>>c_id;
            vector<string>vc={c_id,state,district};
            cp->Add_vaccination_center(vc);
        }
        else if(Req_type=="AddCapacity")
        {
            cout<<"Enter center_id, day and capacity to add capacity: ";
            cin>>c_id>>day>>cap;
            cp->Add_capacity(c_id,day,cap);
            cp->print_capacity(c_id);
        }
        else if(Req_type=="ListVaccinationCenter")
        {
            cout<<"\nEnter district: ";
            cin>>district;
            cp->list_center(district);
        }
        else if(Req_type=="BookVaccination")
        {
            cout<<"\nEnter details to book : ";
            cout<<"\nEnter center id , day and user id: ";
            cin>>c_id>>day>>u_id;
            int bid= cp->book_vaccine(c_id,day,u_id);
            cout<<"\nBooking id generated: "<< bid;
        }
        else if(Req_type=="ListAllBooking")
        {
            cout<<"Enter center id and day to list out all bookings: ";
            cin>>c_id>>day;
            cp->list_booking(c_id,day);
        }
        else if(Req_type=="CancelBooking")
        {
            cout<<"\nEnter center id ,booking id and user id to cancel booking: ";
            cin>>c_id>>b_id>>u_id;
            cp->cancel_booking(c_id,b_id,u_id);
        }
        else if(Req_type=="SearchVaccinationCenter")
        {

        }
        else
        {
            cout<<"\nNo more Requests";
            exit(0);
        }
    }
    return 0;
}

