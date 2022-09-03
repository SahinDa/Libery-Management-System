#include<iostream>
#include<cstring>
#include<string.h>
#include<fstream>
#include<stdio.h>
using namespace std;
 int pass(char*,int);
 class book
{
    private :
     int bookid;
     char title[20];
     float price;
     public : 
       book()
       {
           bookid=0;
         strcpy(title,"no title");
           price=0;
       }
       void getbookdata()
       {
           cout<<"\n Enter bookid ,title and price of a book \n";
           cin>>bookid;
           fflush(stdin);
           cin.getline(title,19);
           cin>>price;
       }
       int storebook();
       void viewallbook();
        void searchbook(char*);
       void deletebook(char*);
       void showbookdata(int);
       void updatebook(char *);
       int take_price()
       {
       	  return price;
	   }
       char* get_title()
       {
       	return title;
	   }
};
class user : protected book
{
    private : 
         char name[20];
         char user_name[20];
         char password[20];
         char dob[20];
         char secret[20];
    public:
         void get_input();
         void display();
         void sign_up();
         int log_in(char*,char*,int);
         void search(char*);
         void delete_user(char*,char*);
         void show_user();  
		 void finalpass(); 
		 void finaluser();  
		 void finalname();
		 void finalsecret();
		 void finaldob();
		 void update_user(char*,char*);
		 void recovery(int);
		 void addnewbook(char*,char*);
		 void user_deletebook(char *);
		 int view(char*,int,int);
		 int get_price()
		 {
		 	return take_price();
		 }
		 char* get_userid()
		 {
		 	return user_name;
		 }
		 char* get_password()
		 {
		 	return password;
		 }
};
int user::view(char *us,int m,int j)
{
	ifstream file;
	book b1;
	int count=0;
	 int cost=0;
	 	 char *n;
	    if(j!=1)
		 n=(strcat(us,".dat")); 
		 else strcpy(n,us);
	file.open(n,ios::in | ios::binary);
	if((!file)&&(m==1))
	return cost;
	if((!file)&&(m==0))
	cout<<"\nYou don't take book yet !! ";
	else{
		  file.read((char*)&b1,sizeof(b1));
		  while(!file.eof())
		  { 
		    if(m==0)
		  	b1.showbookdata(count);
		  	 cost=cost+b1.take_price();
		  	file.read((char*)&b1,sizeof(b1));
		    count++;
		   }//while
		  file.close();
		  if(m==0)
		  cout<<"\n\tTotal Cost : "<<cost;
		}//else
		if(m==1)
		return cost;
		else return m;
}
void user ::user_deletebook(char *us)
{
	ifstream file;
	book b1;
	 char *n;
	 n=(strcat(us,".dat"));
	file.open(n,ios::in | ios::binary);
	if(!file)
	cout<<"\nYou don't take any book yet !! ";
	else {
	        	char title[20];
	        	int c=0;
		 		cout<<"\nEnter the Book you Want to Return  : ";
		 		fflush(stdin);
		 		cin.getline(title,19);
		 		ofstream fout;
		 		fout.open("temp.dat",ios::app|ios::binary);
		       file.read((char*)&b1,sizeof(b1));
		       while(!file.eof())
		       {
		       	  if(strcmp(title,b1.get_title())){
					 c=1;
		       	  fout.write((char*)&b1,sizeof(b1));
					 }
		       	  file.read((char*)&b1,sizeof(b1));
		       	  
			   }//while
			   fout.close();
			   file.close()	;
			   remove(n);
			   rename("temp.dat",n);
			   if(c==1)
			   cout<<"\nYou successfully Return The Book....\n";	
		
	}//else
}
void user::addnewbook(char *us,char *pas)
{
	ifstream file;
	int p=1;
	file.open("userid.dat",ios::in |ios::binary);
	if(!file)
	cout<<"\nBeacause of some internal reason file not open!!\nTry again";
	else {
		 file.read((char*)this,sizeof(*this));
		 while((!file.eof())&&(p==1))
		 {
		 	if((!strcmp(user_name,us)) &&(!strcmp(password,pas)))
		 	{
		 		int m=1;
		 	    fflush(stdin);
		 		char title[20];
		 	
	 		cout<<"\nEnter the Book you Want : ";
	 		fflush(stdin);
		 		cin.getline(title,19);
		 		     ifstream fin;
		 		     fin.open("file1.dat",ios::in|ios::binary);
		 		     if(!fin)
		 		     cout<<"\n Sorry for this internal issue !!\nTry again :\n";
		 		     else{
		 		     	  book b1;
					  fin.read((char*)&b1,sizeof(b1));
					  while((!fin.eof())&&(m==1))
					  {
					  	if(!strcmp(title,b1.get_title()))
					  	m=0;
					  	else fin.read((char*)&b1,sizeof(b1));
					  }
					ofstream fout;
					char *n;
					  n=strcat(us,".dat");
					  ifstream fi;
					  fi.open(n,ios::in |ios::binary);
					  if(fi)
					 m=view(us,1,1);
					if(m<2000){
					fout.open(n,ios::app|ios::binary);
					fout.write((char*)&b1,sizeof(b1));
					fout.close();
				}
				else {
				cout<<"\nsorry Plase Clear Your Due before Further take !!";
					  fin.close();
					  }
		 		}//if-else
			   p=0;
			}//if
			else file.read((char*)this,sizeof(*this));
		 }//first while
	}//else	
}
void user :: recovery(int i)
{
	   if(i==0){
      cout<<"\n 1.Forgot User Name : ";
      cout<<"\n2.Forgot Password : ";
      cout<<"\nEnter Your Choice : ";
      cin>>i;}
      user hmm;
      int p=1;
      char nname[20];
      static int m=0;
      m++;
      if(m>5) cout<<"\n Sorry..You can't change now !!Try later ...";
     else try{
      	     fstream file;
      	     file.open("userid.dat",ios::in|ios::out |ios::ate |ios::binary);
      	     if(!file)
      	     cout<<"\nfile not found";
      	     else {
       switch(i)
      {
      	case 1: hmm.finalsecret();
      	   	         hmm.finaldob();
      	   	         hmm.finalname();
      	   	         break;
      	 case 2: 
      	   	        fflush(stdin);
      	   	        cout<<"Enter your user name : ";
      	   	        cin.getline(nname,19);
      	   	       hmm.finalsecret();
				break;			 	         
	  }
	            file.seekg(0);
	            file.read((char*)this,sizeof(*this));
	            while((!file.eof())&&(p==1)){
      	      switch(i)
      	      {
      	   	case 1:  if((!strcmp(secret,hmm.secret))&&(!strcmp(name,hmm.name))&&(!strcmp(dob,hmm.dob)))
      	   	         { 
      	   	            hmm.finaluser();
      	   	            strcpy(user_name,hmm.user_name);
      	   	            	file.seekp((file.tellp())-(sizeof(*this)));
      	   	       file.write((char*)this,sizeof(*this));
      	   	       p=3;
						  }
						  break;
      	   	case 2: 
      	   	       if((!strcmp(user_name,nname))&&(!strcmp(secret,hmm.secret)))
      	   	       { 
      	   	          hmm.finalpass();
      	   	          strcpy(password,hmm.password);
						file.seekp((file.tellp())-(sizeof(*this)));
      	   	       file.write((char*)this,sizeof(*this));
      	   	       p=2;
      	   	        }
      	   	        break;
      	   			default: cout<<"\nInvalid choice : ";
			 }
			 file.read((char*)this,sizeof(*this));
			 
		}
	     file.close();
	     if(p==2 )
	     cout<<"\nPassword change successfully !!";
	     else if(p==3)
	     cout<<"\nUser name change successfully !!";
	     else throw 1;
		}
	  }
	  catch(int n)
		{
			cout<<"\n Wrong information!!!\nTry Again :\n ";
			recovery(i);
		}
}
void user::update_user(char *us,char *pa)
{ 
  int p=1;
  cout<<" \n"<<us<<"\n "<<pa<<endl;
      while(p==1){
   int i=0;
	cout<<"\nWhat you want to change: \n1.Name : \n2.Date of Birth \n3.User Id \n 4.Password\n5.Favorite sports person : \n6.All \n7.exit \n";
	cin>>i;
	int g=1;
	user oi;
	fstream file;
	file.open("userid.dat",ios::in|ios::ate |ios::out|ios::binary);
	if(!file)
	cout<<"\nfile not found ";
	else{ 
	       file.seekg(0);
	     file.read((char*)this,sizeof(*this));
	     while((!file.eof())&&(g==1))
	     { 
	     	if((!strcmp(user_name,us))&&(!strcmp(password,pa)))
			 {
			 g=0;
            	switch(i)
	       {
		case 1:oi.finalname();
		        strcpy(name,oi.name);
		        file.seekp(file.tellp()-sizeof(*this));
		        file.write((char*)this,sizeof(*this));
		        break;
		case 2:oi.finaldob();
		        strcpy(dob,oi.dob);
		        file.seekp(file.tellp()-sizeof(*this));
		        file.write((char*)this,sizeof(*this));
		        break;
		case 3:oi.finaluser();
		        strcpy(user_name,oi.user_name);
				 file.seekp(file.tellp()-sizeof(*this));
		        file.write((char*)this,sizeof(*this));
		        break; 
		case 4:oi.finalpass();
		        strcpy(password,oi.password);
		         file.seekp(file.tellp()-sizeof(*this));
		        file.write((char*)this,sizeof(*this));
		        break;
		case 5:oi.finalsecret();
		        strcpy(secret,oi.secret);
		         file.seekp(file.tellp()-sizeof(*this));
		        file.write((char*)this,sizeof(*this));
		        break;
		case 6:oi.get_input();
		        file.seekp(file.tellp()-sizeof(*this));
		        file.write((char*)&oi,sizeof(oi));
		        break;
		case 7:exit(0);
		default: cout<<"\nInvalid choice !!! ";        
	}
}
	else file.read((char*)this,sizeof(*this));
} 
file.close();
if(g==1)
cout<<"\nInvalid username or password ";
}
cout<<"\nDo you want to continue : press 1 ";
cin>>p;
}
}
void user :: get_input()
{
    finalname();
     finaluser();
    finaldob();
     finalpass();
      finalsecret();
}
void user :: finaldob()
{
	int i,d=0,m=0,y=0;
	try {  
	     cout<<"Enter date of birth :(--/--/----) ";
		fflush(stdin);
		cin.getline(dob,19);
		 int p=strlen(dob);
		 int an[3];
		 int b=0;
		 for(int l=0;l<p;l++)
		 {
		 	if((dob[l]=='/')||(dob[l]=='.'))
			 {
		 	an[b]=l;
		 	b++;
		     }
		 }
		 if((p>=6)&&(b==2))
		 {  
		     if(an[0]==2 && an[1]==5){
		 	d=(dob[0]-48)*10+(dob[1]-48);
		 	m=(dob[3]-48)*10+(dob[4]-48);
		 	y=(dob[6]-48)*1000+(dob[7]-48)*100+(dob[8]-48)*10+(dob[9]-48);
		    }
		    else if(an[0]==2 && an[1]==4)
		    {
		    		d=(dob[0]-48)*10+(dob[1]-48);
		 	       m=(dob[3]-48);
		 	       y=(dob[5]-48)*1000+(dob[6]-48)*100+(dob[7]-48)*10+(dob[8]-48);
		 }
		    else if(an[0]==1 && an[1]==4)
		    {
		    		d=(dob[0]-48);
		 	     m=(dob[2]-48)*10+(dob[3]-48);
				y=(dob[5]-48)*1000+(dob[6]-48)*100+(dob[7]-48)*10+(dob[8]-48);
			}
		    else if(an[0]==1&&an[1]==3)
		    {
		    		d=(dob[0]-48);
		 	        m=(dob[2]-48);
		 	        y=(dob[4]-48)*1000+(dob[5]-48)*100+(dob[6]-48)*10+(dob[7]-48);
			}
		 	if(y>=1920 &&y<=2021&&((an[1]+4)==(strlen(dob))))
		 	{
		 		if(m==1||m==3||m==5||m==7||m==8 ||m==10||m==12)
		 		{
		 			if(d>=1&&d<=31);
		 			else throw 'c';
				 }
				else if(m==4||m==6||m==9||m==11) 
				{
					if(d>=1&&d<=30);
					else throw 'c';
				}
				else if(m==2)
				{
					if(y%4==0&&(d>=1&&d<=29));
					else if(y%4!=0&&(d>=1&&d<=28));
					else throw 'c';
					
				}
				else throw 'c';
			 }
		 	else throw 'c';
		 }
		 else throw 'c';
	}
	 catch(char p)
	 {
	 	cout<<"/n Invalid Date of Birth input : \n please Re-";
	 	finaldob();
	 }
	 
}
void user :: finalsecret()
{
	int i;
	try{
		cout<<"Enter your Favorite sports person : ";
		fflush(stdin);
		cin.getline(secret,19);
		if(strlen(secret)==0)
		 throw(1.2);
		else if(strlen(secret)<=2)
		throw i;
		
	}
	catch(int n)
	{
		cout<<"\nInvalid name !!\n Re-";
		finalsecret();
	}
	catch(double m)
	{
		cout<<"\nYou forgot to enter your favorite player \n please ";
		finalsecret();
	}
}
void user::finalname()
{
	int i;
	try{
		cout<<" Enter your name : ";
		fflush(stdin);
		cin.getline(name,19);
		if(strlen(name)==0)
		 throw(1.2);
		else if(strlen(name)<=2)
		throw i;
		
	}
	catch(int n)
	{
		cout<<"\nInvalid name !!\n Re-";
		finalname();
	}
	catch(double m)
	{
		cout<<"\nYou forgot to enter your name \n please enter your name :";
		finalname();
	}
	
 } 
void user :: finaluser()
{
    int i=0;
    try { 
          cout<<" Enter your  User name  : ";
    	fflush(stdin);
    	cin.getline(user_name,19);
    	i=pass(user_name,1);
    	if(i)
    	{
    		ifstream fin;
    		user ai;
    		fin.open("userid.dat",ios::in | ios::binary);
    		if(!fin);
    		else {
    		 fin.read((char*) &ai,sizeof(ai));
    		 while(!fin.eof())
    		 {
    		      if(!strcmp(ai.user_name,user_name))
				  {  
				  cout<<"\nUser name already Taken !!\nRE-enter user name : ";
				  finaluser();
					  }	
				  else fin.read((char*)&ai,sizeof(ai));	  
			 }//while
		}//else
		}else if(i==0)
    	throw('c');
	}
	catch(char c)
	{
		cout<<"\n Invalid user Name !!\n Re-enter User name : ";
		finaluser();
	}
}
 void user:: finalpass()
 {
       int i;
     try{ 
           cout<<"Enter password : ";
     	  fflush(stdin);
     	  cin.getline(password,19);
         i=pass(password,0);
    if(i==0)
    throw('c');
        }
     catch( char c)
     {
         cout<<"\nInvalid password :\n Re- ";
		 finalpass();
     }
 };
 int pass(char *an,int sp)
 {
     int len=strlen(an);
     int n=0,c=0,s=0,space=1;
     int p=sp;
     if(len>=8)
     {  
          int i=0;
         while(i<len)
         {
             if(an[i]>=65 && an[i]<=90)  
             c++;
             else if (an[i]>=97 && an[i]<=122)
                s++;
             else if(an[i]>=48 && an[i]<=57)
             n++;
             else if(an[i]==32)
                   space=0;
             else
			  sp++;
             i++;
             
         }
         if(p==1){
         	if(n && c&& s&&(p==sp)&&space)
         return 1;
         else return 0;
		 }
         else if(p==0){
		 if(n&&c&&s&&(p<sp)&&space)
		 return 1;
		  else return 0;
	}
        
     }
     else return 0;
 }
 void user :: display()
 {
     cout<<"\n\t\tUser Data : : ";
     cout<<"\n Name : "<<name;
     cout<<"\n User Name : "<<user_name;
     cout<<"\n Date of Birth : "<<dob;
     cout<<"\n Favorite sports person :  "<<secret;
     cout<<"\n\n";
 }
void user:: sign_up()
{
    ofstream fout;
    fout.open("userid.dat",ios::app|ios::binary);
    fout.write((char*)this,sizeof(*this));
    fout.close();
}
 int user:: log_in(char *pass,char *userid,int m)
 {
     ifstream fin;
       int i=1;
     fin.open("userid.dat",ios::in | ios::binary);
     if(!fin)
     cout<<"file not found ";
     else 
     {   
          fin.read((char*)this,sizeof(*this));
          while(!fin.eof()&& i==1){
           if((!strcmp(pass,password))&&(!strcmp(userid,user_name))){
	     if(m==1) display();
           i=0;
          }
           else
           fin.read((char*)this,sizeof(*this));
           }
           if(i==1)
           cout<<"\n User doesn't exies \n";
     }
     fin.close();
     return i;
 }
  void user:: search(char *userid)
  {
      ifstream fin;
      fin.open("userid.dat",ios::in | ios::binary);
      if(!fin)
      cout<<"file not found ";
      else{
          fin.read((char*)this,sizeof(*this));
          int i=1;
          while(!fin.eof()&& i==1)
          {
              if(!strcmp(userid,user_name))
			  {
                  display();
                  i=0;
              }
              else fin.read((char*)this,sizeof(*this));
          }
          if(i==1)
          cout<<"\n Search element not found  ";
      }
      fin.close();
  }

void user:: delete_user(char *userid,char *pass) 
{
        ifstream fin;
        ofstream fout;
        int p=0,q=0,h=1;
        fin.open("userid.dat",ios::in |ios::binary);
        if(!fin)
        cout<<"file not found ";
        else
        {    
            fout.open("temp.dat",ios::app | ios::binary);
            fin.read((char*)this,sizeof(*this));
               while((!fin.eof())&&(h==1))
            {  
              cout<<"userid ="<<userid<<" "<<pass;
               cout<<"\n user_name"<<user_name<<" "<<password;
                  if((!strcmp(user_name,userid))&&(!strcmp(pass,password))){
					  int m=view(userid,1,0);
				 	 cout<<m;
				 	 if(m==0) cout<<m;
				 	 else {
				 	  cout<<"\nBefore deleting your account please pay"<<m;
				 	  cout<<"\nIf you want to pay then press 1";
				 	  int i;
				 	  cin>>i;
				 	  if(i==1)
				 	  {
				 	  	char *n;
				 	  	strcpy(n,userid);
				 	  	    cout<<n;
				 	  	    remove(n);
					   }//if
					   else {
					   	h=0;
					   	cout<<"\nYou can't Delete your account ! To do so you have to return all book ";
		  	
					   }
				 }//if-else
				 }//comparison if
				 else {
				 	 fout.write((char*)this,sizeof(*this));
				 p++;
				 }
				 fin.read((char*)this,sizeof(*this));
                 q++;
				 }//while
              fout.close();
            fin.close();
            if(h!=0){
            remove("userid.dat");
            rename("temp.dat","userid.dat");    
            } else remove("temp.dat");
			}
           if((p<q)&&(h==1))
        cout<<"\n Deletion is successfully done !!";
        else if(h==1) cout<<"\n User name or password wrong  !!"; 
        }
void user:: show_user()
{
             ifstream fin;
             fin.open("userid.dat",ios::in|ios::binary);
             if(!fin)
             cout<<"file not found ";
             else{
                 fin.read((char*)this,sizeof(*this));
                 while(!fin.eof())
                 {
                     display();
                     fin.read((char*)this,sizeof(*this));
                 }
             }
             fin.close();
         } 

int menu()
    {
        int choice;
        cout<<"\n\t\tUser Id : ";
        cout<<"\n\t\t1.Sign up";
        cout<<"\n\t\t2.Log in ";
        cout<<"\n\t\t3.Delete Account ";
        cout<<"\n\t\t4.Update Account ";
        cout<<"\n\t\t5.Forgot User id or Password  : ";
        cout<<"\n\t\t6.Exit";
        cout<<"\nEnter your choice : ";
        cin>>choice;
        return choice;
    } 
void book::showbookdata(int m)
{ 
    if(m==0)
      cout<<"\n\t\tBook DATA\n\tBookid \tTitle \tprice ";
	cout<<endl<<"\t"<<bookid<<"\t"<<title<<"\t"<<price;
}
void book :: deletebook(char *t )
{
    ifstream fin;
    ofstream fout;
    fin.open("file1.dat",ios::in | ios::binary);
    if(!fin)
    cout<<"\n file not found \n";
    else 
{
    fout.open("tempfile.dat",ios::out | ios :: binary);
    fin.read((char*)this,sizeof(*this));
    while(!fin.eof())
    {
        if(strcmp(t,title))
        fout.write((char *)this,sizeof(*this));
        fin.read((char*)this,sizeof(*this));
    }
    fin.close();
    fout.close();
    remove("file1.dat");
    rename("tempfile.dat","file1.dat");
}
}
void book :: searchbook(char *t)
{
    int counter=0;
    ifstream fin;
    fin.open("file1.dat",ios ::in |ios :: binary);
    if(!fin)
    cout<<"file not found \n";
    else
    {
        fin.read((char*)this,sizeof(*this));
        while(!fin.eof())
        {
            if(!strcmp(t,title)){
            showbookdata(0);
            counter++;
            }
            fin.read((char*)this,sizeof(*this));
        }
        fin.close();
        if(counter==0)
        cout<<"\n Record not found \n";
    }

}
void book :: viewallbook()
{
    ifstream fin;
    int count=0;
    fin.open("file1.dat",ios::in | ios::binary);
    if(!fin)
    cout<<"\n file not found \n";
    else{
        fin.read((char*)this,sizeof(*this));
        while(!fin.eof())
        {   
            showbookdata(count);
            fin.read((char*)this,sizeof(*this));
           count++;
		}
        fin.close();
    }
}
int book :: storebook()
{
    if(bookid==0 && price==0)
    {
        cout<<"\n book data not initialize\n";
        return 0;
    }
    else
    {
        ofstream fout;
        fout.open("file1.dat",ios::app | ios::binary);
        fout.write((char*)this,sizeof(*this));
        fout.close();
        return 1;
    }
}
void book :: updatebook(char *t)
{
    fstream file;
    file.open("file1.dat",ios::in |ios ::out |ios :: ate |ios::binary);
    file.seekg(0);
    file.read((char*)this,sizeof(*this));
    while(!file.eof()){
        if(!strcmp(t,title)){
            getbookdata();
            int p=file.tellp();
			int m=sizeof(*this);
			         file.seekp(p-m);
            file.write((char*)this,sizeof(*this));
        }
        file.read((char*)this,sizeof(*this));
    }
    file.close();
}
int men()
{
    int choice;
    cout<<"\n\t\tBook Management ";
    cout<<"\n1.Insert book record ";
    cout<<"\n2.View all book record ";
    cout<<"\n3.search book record ";
    cout<<"\n4. Delete book record ";
    cout<<"\n 5.update book record ";
    cout<<"\n\t\tUser Information :";
    cout<<"\n6.Search User ";
    cout<<"\n7.Show User ";
    cout<<"\n8.Exit";
    cout<<"\nEnter your choice : ";
    cin>>choice;
    return choice;
}
void bookdata()
{
    book b1;
    int p=1;
    while(p==1)
    {
    	char title[20];
        system("cls");
        user us;
        switch(men())
        {
            case 1: b1.getbookdata();
                    b1.storebook();
                    cout<<endl<<"Record inserted ....";
                    break;
             case 2: b1.viewallbook();
                     break;
             case 3: cout<<endl<<"Enter title of book to search \n";
                    fflush(stdin);
                    cin.getline(title,19);
                    b1.searchbook(title);
                    break;
             case 4 : cout<<endl<<"enter Book title to delete record \n";
                     cin.ignore();
                     cin.getline(title,19);
                     b1.deletebook(title);
                     break;
             case 5 : cout<<endl<<"enter book title so update record \n";
                     cin.ignore();
                    cin.getline(title,19);
                     b1.updatebook(title);
                     break;
             case 6:   char userid[20];
			        cout<<"\nenter User name :  ";
                        fflush(stdin);
                          cin.getline(userid,19);
						us.search(userid);
                        break; 
			 case 7:  us.show_user();
                      break;      
             case 8 : cout<<"\n Thank you for using this application \n";
                      p=0;
                      break;
              default: cout<<"\n Invalid choice : ";                                     
        }
        if(p==1){
      cout<<"\n Do you want to continue : press 1";
      cin>>p;
	  }
    }
}     
void user_book_entry(char *us,char *pas)
{          cout<<"\nWant to See all Library Book press 1\n";
       int p;
       cin>>p;
          if(p==1){
             book b1;
	         b1.viewallbook();  }
	cout<<"\n1.Take a new book : \n2.Return old book \n3.your Book Colection\n";
  	        cin>>p;
  	        user hmm;
  	          switch(p)
  	         {
  	         	case 1:hmm.addnewbook(us,pas);
  	         	        break;
  	         	case 2: hmm.user_deletebook(us); 
				        break;
				case 3:  hmm.view(us,0,0);
				        break;   
				default: 
				cout<<"\nInvalid choice ";			       
	  }
}

void userdata()
 {
        user us;
        int p=1;
        char userid[20],pass[20];
        while(p==1)
        {
            switch(menu())
            {
                case 1: 
				         us.get_input();
                        us.sign_up();
                        cout<<"\nSign up Successfully done \n";
                        cout<<"\nDo you Want Further work : press 1";
                        int m;
						cin >>m;
                        if(m==1)
                        user_book_entry(us.get_userid(),us.get_password());
                        break;
               case 2: {
				 cout<<"\nEnter user name :";
                       fflush(stdin);
                       cin.getline(userid,19);
					   cout<<"\nEnter password : ";
                       fflush(stdin);
                       cin.getline(pass,19);
                       cout<<"\n Do you want to see your profile : press 1 for yes";
                       int m;
                       cin>>m;
					    int i=us.log_in(pass,userid,m);
					    if(!i)
					   user_book_entry(userid,pass);
                       break;}
            case 3 :   cout<<"\nEnter user name :";
                       fflush(stdin);
                        cin.getline(userid,19);
					   cout<<"\nEnter password : ";
                       fflush(stdin);
                       cin.getline(pass,19);
                       us.delete_user(userid,pass);
                       break;   
            case 4:      cout<<"\nEnter user name :";
                       fflush(stdin);
                        cin.getline(userid,19);
					   cout<<"\nEnter password : ";
                       fflush(stdin);
                       cin.getline(pass,19);
					   us.update_user(userid,pass);
					   break;
			case 5:us.recovery(0);
			        break;		        
            case 6 : p=0;
                     break;
            default :cout<<"\n Invalid choice ";                             
            }
            if(p==1){
            cout<<"\n Do you want to continue : press 1 ";
            cin>>p;
            }
        }
    }
 int main()
 {
 	int p=1;
 	while(p==1){
           system("cls");
   int choice ;
  cout<<"\n\t\t\tWelcome to My Dream Place Librery \n";
  cout<<"\n1.Owner ";
  cout<<"\n2.User ";
  cout<<"\n3.Exit ";
  cout<<"\nEnter your choice : ";
  cin>>choice;
  switch(choice)
  {
  	case 1:bookdata();
  	       break;
  	case 2: 	
	        userdata();
  	        break;
	case 3:cout<<"\nThank you for using this application !!";
	        exit(1);
	default:cout<<"\nInvalid choice : ";  	
 } //switch
 cout<<"\nAre you want to continue >press 1 : ";
 cin>>p;	
 }//while
}   
