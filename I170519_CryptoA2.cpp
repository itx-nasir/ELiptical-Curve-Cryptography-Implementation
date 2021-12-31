#include<iostream>
#include<string>
#include<cmath>
#include<cstdlib>
#include<ctime>
using namespace std;
class Point
{
	private:
		int X;
		int Y;
	public:
		Point()
		{
			X=0;
			Y=0;
		}
		Point(int x,int y)
		{
			X=x;
			Y=y;
		}
		void ScalarMultiplication(int k,Point P,int a,int p)
		{
			Point Q=P;
			for(int i=0;i<(k-1);i++)
				{
					Q=PointsAddition(Q,P,a,p);
					
				}
        X=Q.X;
        Y=Q.Y;
		}
		bool Isequal(Point A,Point B)
		{
			if(A.X==B.X&&A.Y==B.Y)
				return 1;
			return 0;
		}
		Point PointsAddition(Point P,Point Q,int a,int p)
		{
			int lambda=0;
			if(Isequal(P,Q))
			{
				lambda=((3*pow(P.X,2)+a)/(2*P.Y));
				lambda=lambda%(p);
				//cout<<lambda;
			}
			else
			{
				lambda=((Q.Y-P.Y)/(Q.X-P.X));
				lambda=lambda%(p);
			}
			Point PQ;
			PQ.X=(pow(lambda,2)-P.X-Q.X);
			PQ.X=PQ.X%(p);
			if(PQ.X<0)
		     {
		     	PQ.X=PQ.X+p;
			 }
			PQ.Y=(lambda*(P.X-Q.X)-P.Y);
			PQ.Y=PQ.Y%(p);
			if(PQ.Y<0)
		     {
		     	PQ.Y=PQ.Y+p;
			 }
			//cout<<Y3;
			return PQ;
		}
	int GetX()
	{
		return X;
	}
	int GetY()
	{
		return Y;
	}
	void SetX(int x)
	{
		X=x;
	}
	void SetY(int y)
	{
	    Y=y;
	}
};
class EllipticalCurve
{
	private:
		int p;
	public:
		int a;
		int b;
		EllipticalCurve()
		{
			this->a=0;
			this->b=0;
			this->p=0;	
		} 
		EllipticalCurve(int a,int b,int p)
		{
			this->a=a;
			this->b=b;
			this->p=p;	
		} 
		int CalcRHS(int x)
		{
			int y=pow(x,3)+(a*x)+b;
			return(y%p);
		}
		int GetP()
		{
			return p;
		}
		int GetA()
		{
			return a;
		}
		int GetB()
		{
			return b;
		}
		void DisplayEC()
		{
			cout<<"\n\t\t****Curve Parameters are****\n";
			cout<<" \t\ta= "<<a<<"    b= "<<b<<"P= "<<p<<endl;
			cout<<"The curve is  Y^2mod "<<p<<"=(X^3+"<<a<<"x+"<<b<<")mod "<<p<<endl;
			cout<<"\t\t*******************************************************\n";
		}
};
class Entity
{
	private:
		char EName;
		int PrivateKey;
		Point SecretKey;
		//int PublicKeyY;
		string Message;
		int *MsgAscii;
		int size;
		EllipticalCurve EC;
		//int *X;
		//int *Y;
		Point *Encoded;
		//Point *Encrypted;
	public:
		Point PublicKey;
		Entity(char EN,string PT)
		{
			EName=EN;
			PrivateKey=0;
			Message=PT;

		}
		void StringToAscii()
		{
			size=Message.length();
			MsgAscii=new int[size];
			for(int i=0;i<Message.length();i++)
				{
					MsgAscii[i]=Message[i];
				}
		}
		int FindY(int RHS)
		{
			for(int i=1;i<EC.GetP();i++)
			{
				if((i*i)%EC.GetP()==RHS)
				{
					return i;
				}
			}
			return 0;
		}
		
		void KeyGeneration(EllipticalCurve E,Point G)
		{	EC=E;
			PrivateKey=rand()%EC.GetP()+2;             //(434,300)
			//PrivateKey=PK
			PublicKey.ScalarMultiplication(PrivateKey,G,EC.GetA(),EC.GetP());
			//cout<<PrivateKey<<endl;
		}
	/*	void Encryption(Point PubKey)
		{
			Encrypted=new Point[size];
			//cout<<"Hy";
			for(int i=0;i<size;i++)
			{	cout<<Encoded[i].GetX()<<endl;
				Encrypted[i]=Encrypted[i].PointsAddition(Encoded[i],PubKey,EC.a,EC.b);
				cout<<Encoded[i].GetX()<<endl;
			}
			
		}*/
		void Encoding(EllipticalCurve E,const int k)
		{   Encoded=new Point[size];
			//X=new int[size];
			//Y=new int[size];
			this->EC=E;
		 	for(int i=0;i<size;i++)
		 	{
		 		int x=MsgAscii[i]*k+1;
				int y=FindY(EC.CalcRHS(x));	
				while(y==0 && x<EC.GetP())
				{
					y=FindY(EC.CalcRHS(++x));	
				}
			Encoded[i].SetX(x);
			Encoded[i].SetY(y);
			}
		}
		void KeyExchang (Point PubKey)
		{
		  	SecretKey.ScalarMultiplication(PrivateKey,PubKey,EC.a,EC.GetP());
		}

	/*	void Decodig()
		{
			for(int i=0;i<size;i++)
			{
				cout<<X[i]/10<<endl;
			}
		}*/
		int FindP(const int k)
		{
			return(	MsgAscii[0]*k+1);
		}
		void DisplayField()
		{
			cout<<"\t\t*****Encode Points are.\n";
			for(int i=0;i<size;i++)
			{
				cout<<"("<<Encoded[i].GetX()<<","<<Encoded[i].GetY()<<")   ";
			}
				cout<<"\t\t*****Encode Points are.\n";
		/*	for(int i=0;i<size;i++)
			{
				cout<<"("<<Encrypted[i].GetX()<<","<<Encrypted[i].GetY()<<")   ";
			}*/
			
		}
		void PrintKeys(string Name)
		{
			cout<<"\n\t\t ****"<<Name<<": Keys*****";
			cout<<"\nPrivateKey= "<<PrivateKey<<endl<<"PubkeyA= R( "<<PublicKey.GetX()<<","<<PublicKey.GetY()<<")\n";
			cout<<" SecreteKey after Key Exchange: ("<<SecretKey.GetX()<<","<<SecretKey.GetY()<<")\n";
			cout<<"\n\t********************************************************************************************\n\n";
		}
		~Entity()
		{
			//delete [] X;
			//delete [] Y;
			delete [] MsgAscii;
			delete [] Encoded;
		//	delete [] Encrypted;
		}
};
bool Is_Prime(int n)
{
    for (int i=2;i<n;i++) 
    {
	
        if (n % i == 0)
            return 0;
     
    }
    return 1;
 }
 Point GeneratePointG(Entity E,EllipticalCurve EC)
 {
 	srand(time(0));
	int x = rand()%EC.GetP()+1;
	int y=E.FindY(EC.CalcRHS(x));	
	while(y==0 && x<EC.GetP())
	{
		y=E.FindY(EC.CalcRHS(++x));	
	}
 	Point G(x,y);
 	return G;
 }
int main()
{
	cout<<"\t\t\t\t*******************************************\n";
	cout<<"\t\t\t\t*****  ELLIPTICAL CURVE CRYPTOGRAPHY  *****\n";
	cout<<"\t\t\t\t*******************************************\n";
	const int k=10 ,a=9,b=7;
	Entity Sender('A',"ABCDE");
	Entity Reciever('B'," ");
	Sender.StringToAscii();
	int p=Sender.FindP(k)+100;
	while(!Is_Prime(p))
	{
		p++;
	}
	EllipticalCurve EC(a,b,p);
	Sender.Encoding(EC,k);
	Point G=GeneratePointG(Sender,EC);
//	cout<<"G("<<G.GetX()<<","<<G.GetY()<<")";
	srand(time(NULL));
	Sender.KeyGeneration(EC,G);
	Reciever.KeyGeneration(EC,G);
	Sender.KeyExchang(Reciever.PublicKey);
	Reciever.KeyExchang(Sender.PublicKey);
	Sender.DisplayField();
//	Sender.Encryption(Reciever.PublicKey);
//	Sender.DisplayField();
	EC.DisplayEC();
	Sender.PrintKeys("Sender(A)");
	Reciever.PrintKeys("Reciever(B)");	
//	cout<<"G("<<G.GetX()<<","<<G.GetY()<<")";
	//Sender.Display();
	//Sender.Decodig();
	return 0;
	
}
