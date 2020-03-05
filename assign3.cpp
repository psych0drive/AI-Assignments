#include <bits/stdc++.h> 
using namespace std;

#define nos 10
#define population_size 100
#define gens 1000
float round(int var) 
{ 

    float value = (float)var/10;
    
    return value; 
} 

float random_num(int start, int end) 
{ 
    int range = (end-start)+1; 
    int random_int = start+(rand()%range); 
    
    return round(random_int); 
}
enum group{g1=0,g2=1,g3=2};
struct student
{
	group g;
	float marks;
	int pos;
};

bool check(const student s[nos])
{
	int a,b,c;
	a=b=c=0;
	
	for(int i=0;i<nos;i++)
	{
		if(s[i].g==g1)
		{
			a++;
		}
		
		else if(s[i].g==g2)
		{
			b++;
		}
		
		else if(s[i].g==g3)
		{
			c++;
		}
	}
	
	if(a==(int)((float)nos/3+ 0.5) || a==nos-2*(int)((float)nos/3+ 0.5))
	{
		if(a==b||a==c)
			return true;
			
		else if(b==c)
			return true;
	}
	
	return false;
}

class individual
{
	public:
		student *s;
		float fitness;
		individual();
		individual(const student total[nos]);
    	individual mate(individual parent2);
    	void mutate();
    	float cal_fitness();
};

individual::individual()
{
	s= new student[nos];
	
	for(int i=0;i<nos;i++)
	{
		s[i].marks=0;
		s[i].g=g1;
		s[i].pos=0;
	}
	
	fitness=-1;
}

individual::individual(const student total[nos])
{
	s= new student[nos];
	vector<student> temp;
	int j;
	
	for(int i=0;i<nos;i++)
		temp.push_back(total[i]);
		
	for(int i=0;i<(int)((float)nos/3 + 0.5);i++)
	{
		j=rand()%(temp.size());
		s[temp[j].pos].marks=temp[j].marks;
		s[temp[j].pos].g=g1;
		s[temp[j].pos].pos=temp[j].pos;
		temp.erase(temp.begin()+ j);
	}
	
	for(int i=0;i<(int)((float)nos/3 + 0.5);i++)
	{
		j=rand()%(temp.size());
		s[temp[j].pos].marks=temp[j].marks;
		s[temp[j].pos].g=g2;
		s[temp[j].pos].pos=temp[j].pos;
		temp.erase(temp.begin()+ j);
	}
	
	for(int i=0;i<temp.size();i++)
	{
		s[temp[i].pos].marks=temp[i].marks;
		s[temp[i].pos].g=g3;
		s[temp[i].pos].pos=temp[i].pos;
	}
	
	if(check(s))
		fitness= cal_fitness();
		
	temp.clear();
}

float individual::cal_fitness()
{
	float m1=0, m2=0, m3=0,sd1=0,sd2=0,sd3=0, total;
	int c1=0, c2=0, c3=0;
	
	for(int i=0;i<nos;i++)
	{
		if(s[i].g==g1)
		{
			m1=m1+ s[i].marks;
			c1++;
		}
		
		else if(s[i].g==g2)
		{
			m2=m2+ s[i].marks;
			c2++;
		}
		
		else if(s[i].g==g3)
		{
			m3=m3+ s[i].marks;
			c3++;
		}
	}
	m1=(float)m1/c1;
	m2=(float)m2/c2;
	m3=(float)m3/c3;
	
	for(int i=0;i<nos;i++)
	{
		if(s[i].g==g1)
		{
			sd1 += pow(s[i].marks - m1, 2);
		}
		
		else if(s[i].g==g2)
		{
			sd2 += pow(s[i].marks - m2, 2);
		}
		
		else if(s[i].g==g3)
		{
			sd3 += pow(s[i].marks - m3, 2);
		}
	}
	sd1= sqrt(sd1/c1);
	sd2= sqrt(sd2/c2);
	sd3= sqrt(sd3/c3);
	total = (sd1 +sd2 +sd3)/3;
	
	return total;
}

void individual:: mutate()
{
	int p= rand()%100;
	
	if(p<50)
	{
		int i,j;
		int m= rand()%(population_size/10);
		
		for(int x= 0; x<m;x++)
		{
			i=rand()%nos;
			j=rand()%nos;
			student temp;
			temp.g=s[i].g;
			s[i].g= s[j].g;
			s[j].g=temp.g;
		}
	}
}

bool comp_f(const individual &i1, const individual &i2)
{
	return( i1.fitness<i2.fitness);
}
bool comp_m(const student &s1, const student &s2)
{
	return( s1.marks<s2.marks);
}
individual individual::mate(individual parent2)
{
	individual new_pop;
	int j;
	
	for(int i =0 ;i<nos ;) 
    {
        float p = (float)random_num(1, 100)/10; 
        if(p <= 0.50) 
        {
        	for( j=i; j<i+1;j++)
            	new_pop.s[j]=this->s[j];
            i=j;
        }

        else if(p <= 1.0 && p >0.50)
        {
        	for( j=i; j<i+1;j++)
            	new_pop.s[j]=parent2.s[j];
            i=j;
        }
    }
    mutate();
    
    if(check(new_pop.s))
    	new_pop.fitness=new_pop.cal_fitness();
    	
    return new_pop;
}

int main()
{
	srand((unsigned)(time(0)));
	student total[nos];
	vector<individual> population;
	
	for(int i=0;i<nos;i++)
	{
		total[i].marks=random_num(10,1000);
		total[i].pos=i;
	}
	sort(total,total+nos,comp_m);
	for(int i=0;i<population_size;i++)
		population.push_back(individual(total));
		
	sort(population.begin(),population.end(),comp_f);
	
	for(int x=1;x<=gens;x++)
	{
		vector<individual> new_gen;
		int e= population_size/100;
		
		for(int i=0;i<e;i++)
		{
			new_gen.push_back(population[i]);
		}
		
		int m= population_size/2, p1, p2;
		int r= (9*population_size)/10;
		
		for(int i=0; i<population_size;)
		{
			p1=rand()%m;
			p2=rand()%m;
			individual new_pop= population[p1].mate(population[p2]);
			
			if(new_pop.fitness!=-1)
			{
				new_gen.push_back(new_pop);
			}
			
			i++;
		}
		
		sort(new_gen.begin(),new_gen.end(),comp_f);
		cout<<"Gen: "<<x-1<<" fitness: "<<population[0].fitness<<endl;
		population=new_gen;
	}
	
	cout<<"Gen: "<<gens<<" fitness: "<<population[0].fitness<<endl;
	sort(population[0].s, population[0].s+nos, comp_m);
	for(int i=0;i<nos ;i++ )
		{
			cout<<population[0].s[i].marks<<"\t"<<population[0].s[i].g<<endl;
		}
}

